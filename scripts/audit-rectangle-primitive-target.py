#!/usr/bin/env python3
"""Pin the rectangle CFG and resolve its x87 vertex-depth/call-order contract."""
import argparse
from collections import Counter
import hashlib
import importlib.util
import json
from pathlib import Path
import struct

import capstone
from capstone import x86
import pefile
from unicorn import Uc, UC_ARCH_X86, UC_MODE_32, UC_HOOK_CODE
from unicorn.x86_const import (
    UC_X86_REG_EAX, UC_X86_REG_ECX, UC_X86_REG_EDX, UC_X86_REG_EIP,
    UC_X86_REG_ESP, UC_X86_REG_ESI, UC_X86_REG_EDI, UC_X86_REG_FPCW,
    UC_X86_REG_FPTAG,
)

from workflow_manifest import load_manifest

ROOT = Path(__file__).resolve().parents[1]
ADDRESS, SIZE = 0x4012A0, 395
SHA = "71aa186253ca2f14ce6ffc30ac72ef5a5ff29b01f2e2e85e3493c4f6d113b347"
UNIT = "exact-first-rectangle-primitive"


def require(condition, message):
    if not condition:
        raise ValueError(message)


def f32(value):
    return struct.unpack("<f", struct.pack("<f", value))[0]


def execute(image, code, filled):
    """Run the full body; external calls are typed observers, not implementations."""
    machine = Uc(UC_ARCH_X86, UC_MODE_32)
    machine.mem_map(0x400000, (len(image) + 4095) & ~4095)
    machine.mem_write(0x400000, image)
    machine.mem_write(ADDRESS, code)
    machine.mem_map(0x800000, 0x10000)
    machine.mem_map(0x1000000, 0x20000)
    machine.mem_map(0xF00000, 0x1000)
    receiver, device, replacement, vtable = 0x801000, 0x802000, 0x802100, 0x803000
    set_fvf, draw = 0x800010, 0x800020
    write32 = lambda address, value: machine.mem_write(address, struct.pack("<I", value))
    read32 = lambda address: struct.unpack("<I", machine.mem_read(address, 4))[0]
    write32(receiver + 4, device)
    for pointer in (device, replacement):
        write32(pointer, vtable)
    write32(vtable + 0x164, set_fvf)
    write32(vtable + 0x14C, draw)
    stack = 0x1010000
    coordinates = [f32(v) for v in (-3.25, 7.125, 103.75, -19.5)]
    color = 0xC13579BD
    machine.mem_write(stack, struct.pack("<I4fII", 0xF00000, *coordinates, color, filled))
    for register, value in [(UC_X86_REG_ESP, stack), (UC_X86_REG_ECX, receiver),
                            (UC_X86_REG_ESI, 0x13579BDF), (UC_X86_REG_EDI, 0x2468ACE0),
                            (UC_X86_REG_FPCW, 0x37F), (UC_X86_REG_FPTAG, 0xFFFF)]:
        machine.reg_write(register, value)
    events, line_count = [], 0

    def hook(uc, address, size, user_data):
        nonlocal line_count
        if address == 0xF00000:
            uc.emu_stop()
            return
        if address not in (0x401180, 0x404DF0, set_fvf, draw):
            return
        sp = uc.reg_read(UC_X86_REG_ESP)
        if address == 0x401180:
            require(uc.reg_read(UC_X86_REG_ECX) == receiver, "line receiver changed")
            arguments = list(struct.unpack("<4fI", uc.mem_read(sp + 4, 20)))
            line_count += 1
            events.append(dict(kind="line", arguments=arguments))
            cleanup, result = 20, 0x12340000 + line_count
        elif address == 0x404DF0:
            require(uc.reg_read(UC_X86_REG_ECX) == 0x702798, "texture manager receiver changed")
            require([read32(sp + 4), read32(sp + 8)] == [0, 0], "texture clear arguments changed")
            events.append(dict(kind="clear_texture"))
            cleanup, result = 8, 0x12345678
        elif address == set_fvf:
            require([read32(sp + 4), read32(sp + 8)] == [device, 0x44], "SetFVF contract changed")
            # An external COM call may replace this field. The later draw must reload it.
            write32(receiver + 4, replacement)
            events.append(dict(kind="set_fvf", value=0x44))
            cleanup, result = 8, 0x87654321
        else:
            owner, primitive, count, vertices, stride = struct.unpack("<5I", uc.mem_read(sp + 4, 20))
            require((owner, primitive, count, stride) == (replacement, 5, 2, 20),
                    "DrawPrimitiveUP contract/device reload changed")
            rows = [list(struct.unpack("<4fI", uc.mem_read(vertices + index * 20, 20)))
                    for index in range(4)]
            events.append(dict(kind="draw", vertices=rows))
            cleanup, result = 20, 0x88776655
        uc.reg_write(UC_X86_REG_EAX, result)
        uc.reg_write(UC_X86_REG_ECX, 0xBAD0C0DE)
        uc.reg_write(UC_X86_REG_EDX, 0xBAD0DADA)
        uc.reg_write(UC_X86_REG_ESP, sp + 4 + cleanup)
        uc.reg_write(UC_X86_REG_EIP, read32(sp))

    machine.hook_add(UC_HOOK_CODE, hook)
    machine.emu_start(ADDRESS, 0, count=2000)
    require(machine.reg_read(UC_X86_REG_EIP) == 0xF00000, "body did not return")
    require(machine.reg_read(UC_X86_REG_ESP) == stack + 28, "RET24 stack contract changed")
    require(machine.reg_read(UC_X86_REG_ESI) == 0x13579BDF and
            machine.reg_read(UC_X86_REG_EDI) == 0x2468ACE0, "callee-save contract changed")
    left, top, right, bottom = coordinates
    if filled:
        require([event["kind"] for event in events] == ["clear_texture", "set_fvf", "draw"],
                "filled call order changed")
        expected = [[f32(x - 0.5), f32(y - 0.5), 0.5, 1.0, color]
                    for x, y in [(left, top), (right, top), (left, bottom), (right, bottom)]]
        require(events[-1]["vertices"] == expected, "filled coordinate/depth/rhw/color changed")
        result = 0x88776655
    else:
        expected = [[left, top, left, bottom, color], [right, top, right, bottom, color],
                    [left, top, right, top, color], [left, bottom, right, bottom, color]]
        require(events == [dict(kind="line", arguments=values) for values in expected],
                "outline order/coordinates/color changed")
        result = 0x12340004
    require(machine.reg_read(UC_X86_REG_EAX) == result, "last drawing-result propagation changed")
    return dict(filled=filled, events=events, return_eax=hex(result), stack_cleanup=24)


def audit(obj=None):
    spec = importlib.util.spec_from_file_location("rectangle_compare", ROOT / "scripts/compare-function.py")
    compare = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(compare)
    identity = compare.verify_target()
    code = compare.target_bytes(ADDRESS, SIZE)
    require(hashlib.sha256(code).hexdigest() == SHA, "complete rectangle body pin changed")
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    decoder.detail = True
    instructions = list(decoder.disasm(code, ADDRESS))
    require(len(instructions) == 128 and sum(i.size for i in instructions) == SIZE,
            "complete instruction census changed")
    by_address = {i.address: i for i in instructions}
    pending, reached, returns, calls = [ADDRESS], set(), [], Counter()
    while pending:
        address = pending.pop()
        if address in reached:
            continue
        require(address in by_address, "escaping/noninstruction CFG edge")
        reached.add(address)
        instruction = by_address[address]
        if instruction.mnemonic == "ret":
            require(bytes(instruction.bytes).hex() == "c21800", "return cleanup changed")
            returns.append(address)
            continue
        if instruction.mnemonic == "call":
            operand = instruction.operands[0]
            calls[hex(operand.imm) if operand.type == x86.X86_OP_IMM else instruction.op_str] += 1
        if instruction.group(capstone.CS_GRP_JUMP):
            require(instruction.operands[0].type == x86.X86_OP_IMM, "unreviewed indirect jump")
            pending.append(instruction.operands[0].imm)
            if instruction.mnemonic == "jmp":
                continue
        pending.append(address + instruction.size)
    require(len(reached) == 128 and sorted(returns) == [0x401351, 0x401428], "full CFG changed")
    require(calls == Counter({"0x401180": 4, "0x404df0": 1, "edx": 2}), "call census changed")
    require(compare.target_bytes(ADDRESS + SIZE, 5) == b"\xcc" * 5, "following padding changed")
    require(compare.target_bytes(0x6CD140, 4).hex() == "0000003f", "float half changed")
    pe = pefile.PE(str(ROOT / "resources/th105.exe"))
    image = bytes(pe.get_memory_mapped_image())
    native = [execute(image, code, filled) for filled in (0, 1, 255)]
    report = dict(result="target_cfg_closed", target_sha256=identity, address=hex(ADDRESS),
                  size=SIZE, code_sha256=SHA, instructions=128, reached=128,
                  ret24_sites=[hex(a) for a in sorted(returns)], following_int3_bytes=5,
                  calls=dict(calls), native_contracts=native,
                  limitations="Three finite call-observer cases; no full FP-environment/NaN equivalence claim.")
    if obj is not None:
        function = load_manifest()["units"][UNIT]["functions"][0]
        targets = compare.known_targets()
        targets.update({name: int(address, 0) for name, address in
                        (value.split("=", 1) for value in function["rel32_targets"])})
        candidate = compare.coff_symbol_bytes(obj, function["symbol_base"], ADDRESS, 0xFFFFFFFF,
                                              targets, compare.known_data_targets(), {})
        candidate_cases = [execute(image, candidate, filled) for filled in (0, 1, 255)]
        require(candidate_cases == native, "candidate call-observer cases differ from native")
        differences = [dict(offset=index, address=hex(ADDRESS + index), target=f"{a:02x}", candidate=f"{b:02x}")
                       for index, (a, b) in enumerate(zip(code, candidate)) if a != b]
        report["candidate"] = dict(object=str(obj), section_size=len(candidate),
                                   size_difference=len(candidate) - SIZE,
                                   full_section_canonical_sha256=hashlib.sha256(candidate).hexdigest(),
                                   full_relocation_replay=True, unequal_positions=len(differences),
                                   differences=differences, observed_contract_cases=3)
        report["result"] = "candidate_exact" if candidate == code else "candidate_nonexact"
    return report


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--object", type=Path)
    args = parser.parse_args()
    try:
        report = audit(args.object)
    except (OSError, ValueError, KeyError) as error:
        print(json.dumps(dict(result="blocked", error=str(error)), indent=2))
        return 1
    print(json.dumps(report, indent=2))
    return int(report["result"] == "candidate_nonexact")


if __name__ == "__main__":
    raise SystemExit(main())
