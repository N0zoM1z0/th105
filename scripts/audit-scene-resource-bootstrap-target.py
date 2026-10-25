#!/usr/bin/env python3
"""Pin the scene resource bootstrap CFG and optionally replay its complete COFF."""
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
ADDRESS, SIZE = 0x43E2E0, 3722
SHA = "6ed872ce668bf9f01a571e00f18e0879828a40ef79c854fc2f5a5f22efeccb4c"
UNIT = "exact-first-scene-resource-bootstrap"
# Actual initialized program strings, including their terminating NULs.
LITERALS = {
    0x6C17FC: b"sfjnv\0", 0x6C17F4: b"nbsjtb\0",
    0x6C17EC: b"tblvzb\0", 0x6C17E4: b"bmjdf\0",
    0x6C17D8: b"qbudipvmj\0", 0x6C17C8: b"zpvnv\0",
    0x6C17D0: b"sfnjmjb\0", 0x6C17C0: b"zvzvlp\0",
    0x6C17B8: b"zvlbsj\0", 0x6C17B0: b"tvjlb\0",
    0x6C17A8: b"vepohf\0", 0x6C17A0: b"lpnbdij\0",
    0x6C1798: b"ufotij\0",
}


def require(ok, message):
    if not ok:
        raise ValueError(message)


def literal_reads(instructions):
    """Validate each actual ROM load width, separately from DIR32 slice identity."""
    reads, referenced = [], set()
    for instruction in instructions:
        for operand in instruction.operands:
            if operand.type != x86.X86_OP_MEM:
                continue
            memory = operand.mem
            if memory.base or memory.index or not 0x6C1798 <= memory.disp < 0x6C1804:
                continue
            owners = [(base, data) for base, data in LITERALS.items()
                      if base <= memory.disp < base + len(data)]
            require(len(owners) == 1, "encoded literal load has no initialized owner")
            base, data = owners[0]
            require(memory.disp + operand.size <= base + len(data),
                    "encoded literal read crosses initialized object extent")
            require(instruction.mnemonic in ("mov", "movzx") and operand.access == capstone.CS_AC_READ,
                    "encoded literal reference is not the reviewed load")
            referenced.add(base)
            reads.append(dict(site=hex(instruction.address), object=hex(base),
                              addend=memory.disp - base, width=operand.size))
    require(referenced == set(LITERALS), "encoded literal object census changed")
    require(len(reads) == 33, "encoded literal read census changed")
    return reads


def audit(obj=None):
    spec = importlib.util.spec_from_file_location(
        "scene_resource_compare", ROOT / "scripts/compare-function.py")
    compare = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(compare)
    identity = compare.verify_target()
    code = compare.target_bytes(ADDRESS, SIZE)
    require(hashlib.sha256(code).hexdigest() == SHA, "complete body pin changed")
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    decoder.detail = True
    instructions = list(decoder.disasm(code, ADDRESS))
    require(sum(i.size for i in instructions) == SIZE, "incomplete decode")
    require(len(instructions) == 823, "instruction census changed")
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
            operand = instruction.operands[0]
            if operand.type == x86.X86_OP_IMM:
                calls[operand.imm] += 1
            else:
                require(instruction.op_str == "dword ptr [0x6c0210]",
                        "unreviewed indirect call")
        if instruction.group(capstone.CS_GRP_JUMP):
            require(instruction.operands[0].type == x86.X86_OP_IMM,
                    "unreviewed indirect jump")
            pending.append(instruction.operands[0].imm)
            if instruction.mnemonic == "jmp":
                continue
        pending.append(address + instruction.size)
    unreachable = {a: bytes(i.bytes).hex() for a, i in by_address.items() if a not in reached}
    require(len(reached) == 821 and returns == [0x43F169], "CFG/exit changed")
    require(unreachable == {0x43F006: "8da42400000000", 0x43F00D: "8d4900"},
            "internal alignment changed")
    require(compare.target_bytes(ADDRESS + SIZE, 6) == b"\xcc" * 6,
            "following independent function separation changed")
    require(compare.target_bytes(0x41E104, 5) == bytes.fromhex("e8d7010200"),
            "exact scene-manager caller edge changed")
    require(calls[0x4606E0] == 48 and calls[0x40A6C0] == 13
            and calls[0x6183F0] == 2, "application/provider call census changed")
    keys = []
    for index, instruction in enumerate(instructions):
        if instruction.mnemonic == "call" and instruction.operands[0].type == x86.X86_OP_IMM:
            if instruction.operands[0].imm == 0x40A6C0:
                push = instructions[index - 2]
                require(push.mnemonic == "push" and push.operands[0].type == x86.X86_OP_IMM,
                        "tracked-key argument changed")
                keys.append(push.operands[0].imm)
    require(keys == [1, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 87, 88],
            "tracked-key policy changed")
    # Local inputEx starts at ESP+BC: vptr, flag+64 and WORD+60 only.
    require(compare.target_bytes(0x43EFAB, 26).hex() ==
            "c78424bc00000054116c00889c242001000066899c241c010000",
            "observed inputEx constructor prefix changed")
    for base, data in LITERALS.items():
        require(compare.target_bytes(base, len(data)) == data, "encoded literal changed")
    native_reads = literal_reads(instructions)
    report = dict(
        result="target_cfg_closed", evidence_class="hash-attested target bytes/edges",
        target_sha256=identity, address=hex(ADDRESS), size=SIZE, code_sha256=SHA,
        end_exclusive=hex(ADDRESS + SIZE), instructions=len(instructions),
        reached=len(reached), escaping_edges=[], unreachable_instructions=unreachable,
        ret0_sites=[hex(a) for a in returns], following_int3_bytes=6,
        caller=dict(owner="0x0041E070", site="0x0041E104", target=hex(ADDRESS)),
        direct_calls={hex(a): n for a, n in sorted(calls.items())},
        indirect_call="SendMessageA IAT0x006C0210", tracked_keys=keys,
        literal_reads=native_reads, input_ex_unwritten_word="+0x62",
        exact_claim=False,
    )
    if obj is not None:
        function = load_manifest()["units"][UNIT]["functions"][0]
        targets = compare.known_targets()
        targets.update({n: int(a, 0) for n, a in
                        (m.split("=", 1) for m in function["rel32_targets"])})
        overrides = dict(m.split("=", 1) for m in function["dir32_targets"])
        candidate = compare.coff_symbol_bytes(
            obj, function["symbol_base"], ADDRESS, 0xFFFFFFFF,
            targets, compare.known_data_targets(), overrides)
        decoded = list(decoder.disasm(candidate, ADDRESS))
        require(sum(i.size for i in decoded) == len(candidate), "incomplete candidate decode")
        candidate_reads = literal_reads(decoded)
        differences = [dict(offset=i, address=hex(ADDRESS + i),
                            target=f"{a:02x}", candidate=f"{b:02x}")
                       for i, (a, b) in enumerate(zip(code, candidate)) if a != b]
        report["candidate"] = dict(
            object=str(obj), section_size=len(candidate),
            canonical_sha256=hashlib.sha256(candidate).hexdigest(),
            full_relocation_replay=True, unequal_bytes=len(differences),
            size_difference=len(candidate) - SIZE, differences=differences,
            literal_reads=candidate_reads,
        )
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
