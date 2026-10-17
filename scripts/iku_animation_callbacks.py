"""Pinned real animation callbacks for the Iku whole-root native fixture.

Only input objects are constructed. All callback code and return values come
from the original executable, including currently unclassified dependencies.
"""
import hashlib
import struct

import unicorn.x86_const as r

from giant_owner_audit import decode

# Address, extent, stack DWORDs, observed receiver, complete target-byte hash.
CONTRACTS = (
    (0x4351C0, 62, 0, "actor", "23d8fbc1b248a756adca80522ec8fc693b5f00bb4052cd7460199c5413ccffa7"),
    (0x45C1A0, 67, 0, "actor", "c84f98217d5fe39ac6d27d492f92002ec000f75015f2a2970265727e448fcdaf"),
    (0x45C110, 111, 0, "actor", "b78c7b8854657743b087dec05510ea49db063139a15a70548be5569bd30a16c6"),
    (0x45C180, 20, 1, "actor", "e6fc5a6dd6a2da083f32c7603cac01ba8664decbc5ddc106013960baabb4db50"),
    (0x45C220, 138, 0, "actor", "3f733b9abfed77ce68fee6e18df2747d434901dbc7b5d11179523080e5569ba5"),
    (0x436760, 335, 0, "actor", "403bd17fa27e733780e1a4b9845ac31cb741838e5c1d5c3e7e35e2aa1af368ec"),
    (0x40C100, 95, 1, "texture_vector", "5e3f98b1bb1af2f55df8be838ab3afab0be3bdddb8d390ed53e62646ed641840"),
    (0x407160, 193, 7, "sprite_ecx", "ff12481407a3f5e34a949c87db2943c48225bc0f5d048d643e217a504b9f6f40"),
    (0x407230, 261, 6, "sprite_eax", "83f2b73423fee824bd7eb03bbe0daee895f74dfa6394843f8c03c9263e7f4ba3"),
    (0x4073A0, 24, 0, "sprite_ecx", "dd0f784a642770eaeae6c2ef67115fd079cd0e2373278f636405c2c0e4beaf94"),
    (0x4073C0, 24, 0, "sprite_ecx", "06e46843811fd0dd16c4c1cfdffc0a2762912904e4e5e7ef24c66941ec73adde"),
    (0x4074A0, 61, 1, "sprite_ecx", "650785c98bfa79a62d3425e13f5c40d946057a392a044a07fa2e62b8ffee918a"),
    (0x407540, 61, 1, "sprite_ecx", "d49af1f11c7432fade6793ce30562ad2ebc76f7dda1f40e285f59044da03e133"),
)


def install(probe):
    records, owners = {}, {}
    for address, size, arguments, receiver, expected in CONTRACTS:
        body = probe.canonical.target_bytes(address, size)
        if hashlib.sha256(body).hexdigest() != expected:
            raise ValueError(f"animation dependency differs at {address:#x}")
        records[hex(address)] = dict(size=size, sha256=expected,
                                     argument_dwords=arguments, receiver=receiver)
        probe.helpers[address] = arguments
        if receiver != "actor":
            probe.no_receiver.add(address)
        for instruction in decode(body, address):
            probe.target_boundaries.add(instruction.address)
            owners[instruction.address] = hex(address)
    for slot, expected in ((0x14, 0x45C220), (0x1C, 0x45C180), (0x20, 0x45C1A0)):
        if struct.unpack("<I", probe.canonical.target_bytes(0x6C652C + slot, 4))[0] != expected:
            raise ValueError("original Iku animation vtable differs")
    probe.animation_instruction_owners = owners
    probe.animation_instructions = {}
    probe.animation_callback_contracts = records


def prepare(probe, case, owner):
    if not hasattr(probe, "animation_callback_contracts"):
        install(probe)
    # Execute these actual methods instead of stopping at their entry.
    probe.boundaries = {a: n for a, n in probe.boundaries.items()
                        if a not in (0x45C180, 0x45C220)}
    area = owner + 0xC000
    block, second = area, area + 0x20
    frames, next_frames = area + 0x100, area + 0x400
    vector, handles = area + 0x800, area + 0x900
    uc = probe.engine

    def write(address, fmt, *values):
        uc.mem_write(address, struct.pack("<" + fmt, *values))

    uc.mem_write(area, bytes(0x1000))
    count, link = case["frame_count"], case["block_link"]
    if count not in (1, 2, 3) or not 0 <= case["frame"] < count or link not in range(4):
        raise ValueError("animation fixture frame/link input outside its bounded arena")
    write(vector, "4I", 0, handles, handles + 4, handles + 4)
    write(handles, "I", 0)  # Genuine supported zero texture-handle path.
    write(block + 4, "2I", frames, frames + count * 0x88)
    write(block + 0x14, "B", case["block_mode"])
    write(block + 0x18, "2I", second if link == 1 else 0, second if link >= 2 else 0)
    write(second + 4, "2I", next_frames, next_frames + 0x88)
    write(second + 0x18, "I", block if link == 2 else 0)
    for first, length, duration in ((frames, count, case["frame_limit"]), (next_frames, 1, 3)):
        for index in range(length):
            address = first + index * 0x88
            write(address + 8, "6h", duration, 0, 0, 0, 16, 8)
            write(address + 0x14, "B", case["frame_format"])
    write(owner + 0x130, "I", vector)
    write(owner + 0x148, "h", count)
    write(owner + 0x14C, "h", case["frame_limit"])
    write(owner + 0x150, "I", frames + case["frame"] * 0x88)
    write(owner + 0x158, "2I", frames + case["frame"] * 0x88, block)
    probe.animation_owner, probe.animation_vector = owner, vector


def observe(probe, uc, address):
    if not hasattr(probe, "animation_callback_contracts"):
        return
    entry = probe.animation_instruction_owners.get(address)
    if entry is not None:
        probe.animation_instructions.setdefault(entry, set()).add(address)
    contract = probe.animation_callback_contracts.get(hex(address))
    if contract is None or contract["receiver"] == "actor":
        return  # The existing base fixture checks normal actor ECX receivers.
    kind = contract["receiver"]
    register = r.UC_X86_REG_EAX if kind == "sprite_eax" else r.UC_X86_REG_ECX
    expected = probe.animation_vector if kind == "texture_vector" else probe.animation_owner + 4
    if uc.reg_read(register) != expected:
        raise ValueError(f"animation {kind} receiver differs at {address:#x}")
