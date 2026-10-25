#!/usr/bin/env python3
"""Pin the complete collision debug renderer, its callback entry and COFF replay."""
import argparse
from collections import Counter
import hashlib
import importlib.util
import json
from pathlib import Path
import struct

import capstone
from capstone import x86

from workflow_manifest import load_manifest

ROOT = Path(__file__).resolve().parents[1]
ADDRESS, SIZE = 0x45E950, 3087
SHA = "3aaec51dd009afb0b872650367815c5ea99d67598017ad342423cc5d6bb63e5a"
UNIT = "exact-first-collision-debug-geometry"


def require(ok, message):
    if not ok:
        raise ValueError(message)


def audit(obj=None):
    spec = importlib.util.spec_from_file_location(
        "collision_debug_compare", ROOT / "scripts/compare-function.py")
    compare = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(compare)
    identity = compare.verify_target()
    code = compare.target_bytes(ADDRESS, SIZE)
    require(hashlib.sha256(code).hexdigest() == SHA, "complete body pin changed")
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    decoder.detail = True
    instructions = list(decoder.disasm(code, ADDRESS))
    require(sum(i.size for i in instructions) == SIZE and len(instructions) == 892,
            "full instruction census changed")
    require(bytes(instructions[0].bytes).hex() == "83ec1c", "native scalar frame changed")
    by_address = {i.address: i for i in instructions}
    reached, pending, calls, returns = set(), [ADDRESS], Counter(), []
    while pending:
        address = pending.pop()
        if address in reached:
            continue
        require(address in by_address, f"escaping/noninstruction edge {address:#x}")
        reached.add(address)
        instruction = by_address[address]
        if instruction.mnemonic == "ret":
            require(bytes(instruction.bytes) == b"\xc3", "return cleanup changed")
            returns.append(address)
            continue
        if instruction.mnemonic == "call":
            require(instruction.operands[0].type == x86.X86_OP_IMM, "unreviewed indirect call")
            calls[instruction.operands[0].imm] += 1
        if instruction.group(capstone.CS_GRP_JUMP):
            require(instruction.operands[0].type == x86.X86_OP_IMM, "unreviewed indirect jump")
            pending.append(instruction.operands[0].imm)
            if instruction.mnemonic == "jmp":
                continue
        pending.append(address + instruction.size)
    unreachable = {hex(a): bytes(i.bytes).hex() for a, i in by_address.items() if a not in reached}
    require(len(reached) == 891 and returns == [0x45F55E], "CFG/return census changed")
    require(unreachable == {"0x45eb59": "8da42400000000"}, "internal alignment changed")
    require(compare.target_bytes(ADDRESS + SIZE, 1) == b"\xcc", "following function separation changed")
    require(calls == Counter({0x401180: 20, 0x4012A0: 1}), "drawing call census changed")
    # Each line's color is the last immediate pushed in its linear code region.
    # Both alternatives of each optional split block have the same packed color.
    colors, pushed = [], None
    for instruction in instructions:
        if instruction.mnemonic == "push" and instruction.operands[0].type == x86.X86_OP_IMM:
            pushed = instruction.operands[0].imm & 0xFFFFFFFF
        if instruction.mnemonic == "call" and instruction.operands[0].imm == 0x401180:
            colors.append(pushed)
    require(colors == [0xFF00FFFF] * 4 + [0xFF0000FF] * 8 + [0xFFFF0000] * 8,
            "packed line-color policy changed")
    caller = compare.target_bytes(0x53B1A0, 18)
    require(hashlib.sha256(caller).hexdigest() ==
            "c3b8386db90175da16d4b04aacee8d9fdf3aad7f5ee1b6775808fd67d723cfbc",
            "exact manager callback wrapper changed")
    require(caller[:3] == bytes.fromhex("33d2b8") and struct.unpack("<I", caller[3:7])[0] == ADDRESS
            and caller[7:12] == bytes.fromhex("525083c104"), "member-pointer code/adjustor changed")
    require(0x53B1B1 + struct.unpack("<i", caller[13:17])[0] == 0x58BEE0,
            "exact manager dispatch edge changed")
    require(hashlib.sha256(compare.target_bytes(0x58BEE0, 72)).hexdigest() ==
            "8c13d0e329bf5731e2192aa31085936b965fc0e9df14e3cc41b7b67abde194f5",
            "exact checked-list member dispatcher changed")
    helpers = []
    for address, size, digest, cleanup_sites, cleanup in [
        (0x401180, 148, "8fab1b24e1ad32aa03203b28ed4c80a795f9d83f6f21e9890e154bb531b3f28d", [0x401211], "c21400"),
        (0x4012A0, 395, "71aa186253ca2f14ce6ffc30ac72ef5a5ff29b01f2e2e85e3493c4f6d113b347", [0x401351, 0x401428], "c21800"),
    ]:
        require(hashlib.sha256(compare.target_bytes(address, size)).hexdigest() == digest,
                "drawing provider body changed")
        require(all(compare.target_bytes(a, 3).hex() == cleanup for a in cleanup_sites),
                "drawing provider argument cleanup changed")
        helpers.append(dict(address=hex(address), size=size, sha256=digest, cleanup=cleanup,
                            new_exact_or_origin_credit=False))
    report = dict(
        result="target_cfg_closed", evidence_class="hash-attested target bytes/edges",
        target_sha256=identity, address=hex(ADDRESS), size=SIZE, code_sha256=SHA,
        end_exclusive=hex(ADDRESS + SIZE), instructions=len(instructions), reached=len(reached),
        ret0_sites=[hex(a) for a in returns], escaping_edges=[], indirect_jumps=[],
        unreachable_instructions=unreachable, following_int3_bytes=1,
        direct_calls={hex(a): n for a, n in sorted(calls.items())},
        line_site_colors=[hex(n) for n in colors],
        callback=dict(owner="0x0053B1A0", code=hex(ADDRESS), this_adjustor=0,
                      dispatch_site="0x0053B1AC", dispatcher="0x0058BEE0"),
        drawing_providers=helpers,
    )
    if obj is not None:
        function = load_manifest()["units"][UNIT]["functions"][0]
        targets = compare.known_targets()
        targets.update({n: int(a, 0) for n, a in
                        (m.split("=", 1) for m in function["rel32_targets"])})
        candidate = compare.coff_symbol_bytes(
            obj, function["symbol_base"], ADDRESS, 0xFFFFFFFF,
            targets, compare.known_data_targets(), {})
        differences = [dict(offset=i, address=hex(ADDRESS + i),
                            target=f"{a:02x}", candidate=f"{b:02x}")
                       for i, (a, b) in enumerate(zip(code, candidate)) if a != b]
        report["candidate"] = dict(
            object=str(obj), section_size=len(candidate), size_difference=len(candidate) - SIZE,
            full_section_canonical_sha256=hashlib.sha256(candidate).hexdigest(),
            full_relocation_replay=True, unequal_positions=len(differences), differences=differences,
        )
        report["result"] = "candidate_exact" if candidate == code else "candidate_nonexact"
    return report


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--object", type=Path)
    args = parser.parse_args()
    try:
        report = audit(args.object)
    except (OSError, ValueError, KeyError) as failure:
        print(json.dumps(dict(result="blocked", error=str(failure)), indent=2))
        return 1
    print(json.dumps(report, indent=2))
    return int(report["result"] == "candidate_nonexact")


if __name__ == "__main__":
    raise SystemExit(main())
