#!/usr/bin/env python3
"""Pin the filtered spell CSV parser's full CFG; optionally replay its COFF body."""
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
ADDRESS, SIZE = 0x433B30, 1987
SHA = "7d09cf25edce166f13585697b544749512d2c6d8b968c555a97d75d1cdb19cb8"
UNIT = "exact-first-spell-filtered-csv"


def require(ok, message):
    if not ok:
        raise ValueError(message)


def audit(obj=None):
    spec = importlib.util.spec_from_file_location(
        "spell_filtered_compare", ROOT / "scripts/compare-function.py")
    compare = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(compare)
    identity = compare.verify_target()
    code = compare.target_bytes(ADDRESS, SIZE)
    require(hashlib.sha256(code).hexdigest() == SHA, "complete body pin changed")
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    decoder.detail = True
    instructions = list(decoder.disasm(code, ADDRESS))
    require(sum(i.size for i in instructions) == SIZE, "incomplete decode")
    require(len(instructions) == 478, "instruction census changed")
    by_address = {i.address: i for i in instructions}
    reached, pending, calls, returns = set(), [ADDRESS], Counter(), []
    while pending:
        address = pending.pop()
        if address in reached:
            continue
        require(address in by_address, f"escaping/noninstruction edge {address:#x}")
        reached.add(address)
        i = by_address[address]
        if i.mnemonic == "ret":
            require(bytes(i.bytes).hex() == "c21400", "return cleanup changed")
            returns.append(address)
            continue
        if i.mnemonic == "call":
            if i.operands[0].type == x86.X86_OP_IMM:
                calls[i.operands[0].imm] += 1
            else:
                require(address == 0x433DBC and i.op_str == "dword ptr [0x6c01d8]",
                        "unreviewed indirect call")
        if i.group(capstone.CS_GRP_JUMP):
            require(i.operands[0].type == x86.X86_OP_IMM, "unreviewed indirect jump")
            pending.append(i.operands[0].imm)
            if i.mnemonic == "jmp":
                continue
        pending.append(address + i.size)
    require(len(reached) == 478 and returns == [0x4341C6], "CFG/exit changed")
    require(compare.target_bytes(ADDRESS + SIZE, 13) == b"\xcc" * 13,
            "following independent wrapper separation changed")
    wrapper = list(decoder.disasm(compare.target_bytes(0x434300, 148), 0x434300))
    entries = [(n, i) for n, i in enumerate(wrapper)
               if i.mnemonic == "call" and i.operands[0].type == x86.X86_OP_IMM
               and i.operands[0].imm == ADDRESS]
    require(len(entries) == 1, "wrapper parser edge changed")
    index, edge = entries[0]
    require(bytes(wrapper[index - 1].bytes).hex() == "8bce", "this receiver changed")
    report = dict(
        result="target_cfg_closed", evidence_class="hash-attested target bytes/edges",
        target_sha256=identity, address=hex(ADDRESS), size=SIZE, code_sha256=SHA,
        end_exclusive=hex(ADDRESS + SIZE), instructions=len(instructions),
        reached=len(reached), escaping_edges=[], unreachable_instructions=[],
        ret20_sites=[hex(a) for a in returns], following_int3_bytes=13,
        member_caller=dict(owner="0x00434300", site=hex(edge.address),
                           preceding_bytes="8bce", target=hex(ADDRESS)),
        direct_calls={hex(a): n for a, n in sorted(calls.items())},
        indirect_calls={"0x00433DBC": "wsprintfA IAT0x006C01D8"},
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
        differences = [dict(offset=i, address=hex(ADDRESS + i),
                            target=f"{a:02x}", candidate=f"{b:02x}")
                       for i, (a, b) in enumerate(zip(code, candidate)) if a != b]
        report["candidate"] = dict(
            object=str(obj), section_size=len(candidate),
            canonical_sha256=hashlib.sha256(candidate).hexdigest(),
            full_relocation_replay=True, unequal_bytes=len(differences),
            size_difference=len(candidate) - SIZE, differences=differences,
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
