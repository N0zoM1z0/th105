#!/usr/bin/env python3
"""Compare every emitted Alice Fighter update byte, including switch metadata.

The instruction/table inventory diagnoses a complete hypothesis; it never masks
bytes or promotes a source-present/exact ledger claim.
"""
from __future__ import annotations

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
ADDRESS, MAIN_SIZE, PAYLOAD_SIZE = 0x4E9F50, 42721, 44080
PAYLOAD_SHA256 = "2bd6bb53be12d74e98f1fee7dfcedf2b1adcf71597fd89a9ce8185f4d0e1f823"
UNIT = "exact-first-alice-fighter-update"


def load_candidate(object_path=None):
    spec = importlib.util.spec_from_file_location(
        "alice_fighter_update_canonical", ROOT / "scripts/compare-function.py")
    comparator = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(comparator)
    identity = comparator.verify_target()
    unit = load_manifest()["units"][UNIT]
    function = unit["functions"][0]
    if int(function["address"], 0) != ADDRESS:
        raise ValueError("configured root address changed")
    targets = comparator.known_targets()
    for binding in function.get("rel32_targets", []):
        name, address = binding.rsplit("=", 1)
        targets[name] = int(address, 0)
    overrides = dict(binding.rsplit("=", 1) for binding in function.get("dir32_targets", []))
    if object_path is None:
        object_path = ROOT / unit["object"]
    candidate = comparator.coff_symbol_bytes(
        object_path, function["symbol_base"], ADDRESS, 0xFFFFFFFF,
        targets, comparator.known_data_targets(), overrides)
    target = comparator.target_bytes(ADDRESS, PAYLOAD_SIZE)
    if hashlib.sha256(target).hexdigest() != PAYLOAD_SHA256:
        raise ValueError("complete target payload pin changed")
    return comparator, identity, candidate, target


def inventory(raw):
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    decoder.detail = True
    prefix = list(decoder.disasm(raw[:2048], ADDRESS))
    primary = next(i.operands[0].mem.disp for i in prefix
                   if i.mnemonic == "jmp" and i.operands[0].type == x86.X86_OP_MEM)
    if not ADDRESS < primary < ADDRESS + len(raw):
        raise ValueError("first destination table escapes emitted payload")
    rows = list(decoder.disasm(raw[:primary - ADDRESS], ADDRESS))
    if sum(i.size for i in rows) != primary - ADDRESS:
        raise ValueError("complete code/alignment decoding failed")
    by_address = {i.address: i for i in rows}
    starts = sorted({i.operands[0].mem.disp for i in rows
                     if i.mnemonic == "jmp" and i.operands[0].type == x86.X86_OP_MEM})
    remaps = []
    for index, row in enumerate(rows):
        if (row.mnemonic != "movzx" or row.operands[1].type != x86.X86_OP_MEM
                or row.operands[1].size != 1 or row.operands[1].mem.disp < primary):
            continue
        memory = row.operands[1].mem
        preceding = rows[max(0, index - 8):index]
        guard = next((i for i in reversed(preceding)
                      if i.mnemonic == "cmp" and i.operands[0].type == x86.X86_OP_REG
                      and i.operands[0].reg in (memory.base, memory.index)
                      and i.operands[1].type == x86.X86_OP_IMM), None)
        if guard is None or not 0 <= guard.operands[1].imm < 1024:
            raise ValueError("remap has no bounded index comparison")
        if not any(i.mnemonic == "ja" and i.address > guard.address
                   and i.operands[0].imm in by_address for i in preceding):
            raise ValueError("remap has no unsigned out-of-range edge")
        jump = next((i for i in rows[index + 1:index + 4]
                     if i.mnemonic == "jmp" and i.operands[0].type == x86.X86_OP_MEM), None)
        if jump is None or jump.operands[0].mem.index != row.operands[0].reg:
            raise ValueError("remap does not feed the destination table")
        address, size = memory.disp, guard.operands[1].imm + 1
        if not primary <= address < address + size <= ADDRESS + len(raw):
            raise ValueError("remap escapes complete metadata")
        indices = raw[address - ADDRESS:address - ADDRESS + size]
        remaps.append(dict(address=address, size=size, table=jump.operands[0].mem.disp,
                           bytes=indices.hex()))
    boundaries = sorted(starts + [r["address"] for r in remaps] + [ADDRESS + len(raw)])
    tables = {}
    for address in starts:
        limit = next((b for b in boundaries if b > address), None)
        if limit is None or not primary <= address < limit <= ADDRESS + len(raw):
            raise ValueError("destination table extent escapes metadata")
        destinations = []
        while address + 4 * len(destinations) + 4 <= limit:
            value = struct.unpack_from("<I", raw, address + 4 * len(destinations) - ADDRESS)[0]
            if value not in by_address:
                break
            destinations.append(value)
        if not destinations:
            raise ValueError("empty destination table")
        tables[address] = destinations
    for remap in remaps:
        if remap["table"] not in tables or max(bytes.fromhex(remap["bytes"])) >= len(tables[remap["table"]]):
            raise ValueError("remap index escapes reviewed candidate destinations")
    visited, pending = set(), [ADDRESS]
    while pending:
        address = pending.pop()
        if address in visited:
            continue
        if address not in by_address:
            raise ValueError("candidate CFG edge escapes complete code")
        visited.add(address)
        row = by_address[address]
        if row.mnemonic == "ret":
            if row.op_str:
                raise ValueError("candidate root no longer has RET0 only")
            continue
        if row.mnemonic == "jmp":
            operand = row.operands[0]
            pending.extend(tables[operand.mem.disp] if operand.type == x86.X86_OP_MEM else [operand.imm])
            continue
        if row.group(capstone.CS_GRP_JUMP):
            pending.append(row.operands[0].imm)
        pending.append(address + row.size)
    calls = Counter(i.operands[0].imm for i in rows
                    if i.mnemonic == "call" and i.operands[0].type == x86.X86_OP_IMM)
    predicate_tests = []
    for index, row in enumerate(rows[:-1]):
        if (row.mnemonic != "call" or row.operands[0].type != x86.X86_OP_IMM
                or row.operands[0].imm not in (0x435DC0, 0x5F9310)):
            continue
        following = rows[index + 1]
        register = (following.op_str.split(",")[0] if following.mnemonic == "test"
                    and following.op_str in ("al, al", "eax, eax") else None)
        predicate_tests.append(dict(call=hex(row.address), target=hex(row.operands[0].imm),
                                    next_address=hex(following.address), register=register,
                                    next_instruction=following.mnemonic + " " + following.op_str))
    return dict(diagnostic_only=True, code_to_first_table=primary - ADDRESS,
                instructions=len(rows), conservatively_reached=len(visited),
                unreachable=[dict(address=hex(i.address), bytes=bytes(i.bytes).hex())
                             for i in rows if i.address not in visited],
                returns=sum(i.mnemonic == "ret" for i in rows),
                indirect_calls=sum(i.mnemonic == "call" and i.operands[0].type != x86.X86_OP_IMM for i in rows),
                direct_calls={hex(a): n for a, n in sorted(calls.items())},
                predicate_result_tests=predicate_tests,
                stack_allocation=[i.operands[1].imm for i in rows[:12]
                                  if i.mnemonic == "sub" and i.operands[0].reg == x86.X86_REG_ESP],
                tables=[dict(address=hex(a), dwords=len(ds)) for a, ds in sorted(tables.items())],
                remaps=[dict(address=hex(r["address"]), size=r["size"], bytes=r["bytes"])
                        for r in sorted(remaps, key=lambda r: r["address"])])


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--object", type=Path, help="override the configured COFF object")
    args = parser.parse_args()
    try:
        comparator, identity, candidate, target = load_candidate(args.object)
        exact = candidate == target
        # Comparison covers the entire emitted section before any diagnostic
        # decoding; every extra byte and relocation remains significant.
        report = dict(result="exact" if exact else "mismatch", unit=UNIT,
                      target_sha256=identity, callable_size=MAIN_SIZE,
                      complete_payload_size=PAYLOAD_SIZE, object_section_tail_size=len(candidate),
                      all_section_relocations_replayed=True,
                      canonical_payload_sha256=hashlib.sha256(candidate).hexdigest(),
                      first_mismatch=comparator.first_mismatch(target, candidate, ADDRESS),
                      unmasked_differing_bytes=sum(a != b for a, b in zip(target, candidate))
                      + abs(len(target) - len(candidate)), candidate_inventory=inventory(candidate),
                      target_predicate_result_tests=inventory(target)["predicate_result_tests"])
    except (OSError, ValueError, RuntimeError, KeyError, StopIteration, struct.error) as error:
        print(json.dumps(dict(result="blocked", error=str(error)), indent=2))
        return 1
    print(json.dumps(report, indent=2))
    return 0 if exact else 1


if __name__ == "__main__":
    raise SystemExit(main())
