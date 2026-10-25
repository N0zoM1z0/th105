#!/usr/bin/env python3
"""Pin the complete effect resource loader and replay its full COFF section."""
import argparse
from collections import Counter
import hashlib
import importlib.util
import json
from pathlib import Path

import capstone
from capstone import x86

from workflow_manifest import load_manifest

ROOT = Path(__file__).resolve().parents[1]
ADDRESS, SIZE = 0x437EC0, 2528
SHA = "e0d31abb77468f60189ea2e9473f5896f0a08155057d03d81e74bfc40ce94566"
UNIT = "exact-first-effect-resources"


def require(condition, message):
    if not condition:
        raise ValueError(message)


def audit(obj=None):
    spec = importlib.util.spec_from_file_location("effect_resources_compare", ROOT / "scripts/compare-function.py")
    compare = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(compare)
    identity = compare.verify_target()
    code = compare.target_bytes(ADDRESS, SIZE)
    require(hashlib.sha256(code).hexdigest() == SHA, "complete body pin changed")
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    decoder.detail = True
    instructions = list(decoder.disasm(code, ADDRESS))
    require(len(instructions) == 794 and sum(i.size for i in instructions) == SIZE,
            "complete instruction census changed")
    by_address = {i.address: i for i in instructions}
    reached, pending, returns, calls = set(), [ADDRESS], [], Counter()
    while pending:
        address = pending.pop()
        if address in reached:
            continue
        require(address in by_address, "escaping/noninstruction edge")
        reached.add(address)
        instruction = by_address[address]
        if instruction.mnemonic == "ret":
            require(bytes(instruction.bytes).hex() == "c20400", "return cleanup changed")
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
    require(len(reached) == 794 and returns == [0x43889D], "full CFG/return census changed")
    require(compare.target_bytes(0x4388A0, 3).hex() == "83ec08", "adjacent independent entry changed")
    read_sizes, pushed = [], None
    for instruction in instructions:
        if instruction.mnemonic == "push" and instruction.operands[0].type == x86.X86_OP_IMM:
            pushed = instruction.operands[0].imm
        if instruction.mnemonic == "call":
            if instruction.operands[0].type == x86.X86_OP_REG:
                read_sizes.append(pushed)
            pushed = None
    require(read_sizes == [1, 2, 128, 4, 4, 4, 4, 1, 4, 4] + [2] * 7 + [1, 2] + [1] * 4 + [2] * 4,
            "27 static reader argument widths changed")
    require(calls["0x68a143"] == 25 and calls["edx"] + calls["eax"] == 27,
            "guard/virtual reader census changed")
    require(compare.target_bytes(0x437F36, 5).hex() == "b918297000", "path receiver changed")
    require(compare.target_bytes(0x6D6A18, 5) == b"%s%s\0", "filename prefix format changed")
    helpers = []
    for address, size, digest in [
        (0x422AE0, 131, "c239bf82be8b37b1b979760712cecabf841b0c7001bf1685819ec3dd63ffa24c"),
        (0x422660, 135, "659c36e18d9cd9aad6357657e888c17261c1aafd4e61e786834f76d73b362fbf"),
        (0x4229E0, 256, "66ab382bcab2bc89c43c64c840804ef6131be8c0880c351b176cf440c4eebd91"),
        (0x422E00, 117, "42ef1ee46bf66a1995ab50ce9689da75c8c0feca27913952dbceac3fb0285545"),
        (0x40C350, 123, "a02adc82307ea7507f3024cd6bb4d30229469d2464a73be1c15b8955745445e2"),
    ]:
        require(hashlib.sha256(compare.target_bytes(address, size)).hexdigest() == digest,
                "frame/group/range-error provider changed")
        helpers.append(dict(address=hex(address), size=size, sha256=digest, new_credit=False))
    for address, digest in [
        (0x46F900, "0080fac9ddd8e522418d08edd6d154ae9873ed5df40388ce757ced8860d588ec"),
        (0x4245B0, "7cf76ac8d5394c5094e69cbe37fe6ddbf1bfc153da35bafca97530609e34db44"),
        (0x4389B0, "2bd19b9f2e7e1b82dd45eeea6680335e96aae9da355c95c33090cf30a467629f"),
    ]:
        caller = compare.target_bytes(address, 30)
        require(hashlib.sha256(caller).hexdigest() == digest, "exact manager wrapper changed")
        call = next(i for i in decoder.disasm(caller, address) if i.mnemonic == "call")
        require(call.address == address + 8 and call.operands[0].imm == ADDRESS,
                "manager resource edge changed")
    report = dict(result="target_cfg_closed", target_sha256=identity, address=hex(ADDRESS),
                  size=SIZE, code_sha256=SHA, instructions=794, reached=794,
                  ret4_sites=[hex(a) for a in returns], escaping_edges=[], indirect_jumps=[],
                  direct_and_indirect_calls=dict(calls), static_read_sizes=read_sizes,
                  layout_providers=helpers, new_helper_credit=False)
    if obj is not None:
        function = load_manifest()["units"][UNIT]["functions"][0]
        targets = compare.known_targets()
        targets.update({name: int(address, 0) for name, address in
                        (value.split("=", 1) for value in function["rel32_targets"])})
        overrides = dict(value.split("=", 1) for value in function.get("dir32_targets", []))
        candidate = compare.coff_symbol_bytes(obj, function["symbol_base"], ADDRESS, 0xFFFFFFFF,
                                              targets, compare.known_data_targets(), overrides)
        differences = [dict(offset=index, address=hex(ADDRESS + index), target=f"{a:02x}", candidate=f"{b:02x}")
                       for index, (a, b) in enumerate(zip(code, candidate)) if a != b]
        report["candidate"] = dict(object=str(obj), section_size=len(candidate),
                                   size_difference=len(candidate) - SIZE,
                                   full_section_canonical_sha256=hashlib.sha256(candidate).hexdigest(),
                                   full_relocation_replay=True, unequal_positions=len(differences),
                                   differences=differences)
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
