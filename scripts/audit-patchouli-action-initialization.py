#!/usr/bin/env python3
"""Compare complete Patchouli slot3C code and all three switch metadata regions.

The target closes every main instruction. This script replays all emitted
relocations and compares the entire payload without masking metadata or code.
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
UNIT = "exact-first-patchouli-action-initialization"
SYMBOL = "?initialize_action_entry@PatchouliActionEntryView@th105@@UAEXXZ"
START, CALLABLE, PAYLOAD = 0x51D650, 3132, 3868
MAIN_SHA = "e5b3f190f41d05e3f8fb86e2624d19334f67c26b967be6a17501d4a977aa7dc0"
PAYLOAD_SHA = "ec90d466db8f4cb187863f1125ed614967ba4547a6e557406c23328debfecd4c"


def comparator():
    spec = importlib.util.spec_from_file_location("patchouli_entry_comparator", ROOT / "scripts/compare-function.py")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def inventory(code):
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    decoder.detail = True
    prefix = list(decoder.disasm(code[:256], START))
    first = next(i.operands[0].mem.disp for i in prefix
                 if i.mnemonic == "jmp" and i.operands[0].type == x86.X86_OP_MEM)
    if not START < first < START + len(code):
        raise ValueError("first table escapes complete payload")
    rows = list(decoder.disasm(code[:first - START], START))
    if sum(i.size for i in rows) != first - START:
        raise ValueError("main/alignment decoding is incomplete")
    tables, switch_edges = [], {}
    for index, row in enumerate(rows):
        if row.mnemonic != "jmp" or row.operands[0].type != x86.X86_OP_MEM:
            continue
        base = row.operands[0].mem.disp
        history = rows[max(0, index - 8):index]
        bound_row = next(i for i in reversed(history)
                         if i.mnemonic == "cmp" and i.operands[0].type == x86.X86_OP_REG
                         and i.operands[0].reg == x86.X86_REG_EAX and i.operands[1].type == x86.X86_OP_IMM)
        bound = bound_row.operands[1].imm
        if not 0 <= bound <= 4096:
            raise ValueError("unsupported switch input range")
        count, lower = bound + 1, 0
        # Use the latest input normalization before this bound. A preceding
        # switch's SUB must not override the current direct table's LEA.
        normalizers = [i for i in history if i.address < bound_row.address
                       and i.mnemonic in {"add", "sub", "lea"}
                       and i.operands[0].type == x86.X86_OP_REG
                       and i.operands[0].reg == x86.X86_REG_EAX
                       and ((i.mnemonic in {"add", "sub"} and i.operands[1].type == x86.X86_OP_IMM)
                            or (i.mnemonic == "lea" and i.operands[1].type == x86.X86_OP_MEM
                                and i.operands[1].mem.base == x86.X86_REG_ECX
                                and not i.operands[1].mem.index))]
        if normalizers:
            step = normalizers[-1]
            lower = (-step.operands[1].mem.disp if step.mnemonic == "lea" else
                     step.operands[1].imm * (-1 if step.mnemonic == "add" else 1))
        maps = [i.operands[1].mem.disp for i in history
                if i.address > bound_row.address and i.mnemonic == "movzx" and i.operands[1].type == x86.X86_OP_MEM
                and first <= i.operands[1].mem.disp < START + len(code)]
        remap = maps[-1] if maps else None
        if remap is None:
            words, indices = count, bytes(range(count)) if count <= 256 else b""
        else:
            if not base < remap <= START + len(code) - count or (remap - base) % 4:
                raise ValueError("remap extent escapes payload")
            words = (remap - base) // 4
            indices = code[remap - START:remap - START + count]
        if not first <= base <= START + len(code) - words * 4 or not indices or max(indices) >= words:
            raise ValueError("destination table/index extent is invalid")
        destinations = struct.unpack_from("<" + "I" * words, code, base - START)
        if any(not START <= a < first for a in destinations):
            raise ValueError("switch destination is outside code")
        switch_edges[row.address] = sorted(set(destinations))
        tables.append(dict(site=hex(row.address), address=hex(base), first_case=lower,
                           dwords=words, remap_bytes=count if remap else 0,
                           remap_sha256=hashlib.sha256(indices).hexdigest() if remap else None,
                           destinations=destinations))
    if [(t["dwords"], t["remap_bytes"]) for t in tables] != [(23, 221), (33, 226), (15, 0)]:
        raise ValueError("reviewed three-table ownership changed")
    calls = Counter(i.operands[0].imm for i in rows if i.mnemonic == "call"
                    and i.operands[0].type == x86.X86_OP_IMM)
    tails = Counter(i.operands[0].imm for i in rows if i.mnemonic == "jmp"
                    and i.operands[0].type == x86.X86_OP_IMM and not START <= i.operands[0].imm < first)
    summary = dict(code_and_alignment_to_first_table=first - START, instructions=len(rows),
                   returns=sum(i.mnemonic == "ret" for i in rows),
                   direct_calls={hex(a): n for a, n in sorted(calls.items())},
                   external_tail_sites={hex(a): n for a, n in sorted(tails.items())},
                   tables=[{k: v for k, v in t.items() if k != "destinations"} for t in tables])
    return rows, switch_edges, tables, summary


def close_target_cfg(rows, edges):
    by_address = {i.address: i for i in rows if i.address < START + CALLABLE}
    pending, reached, tails = [START], set(), set()
    while pending:
        address = pending.pop()
        if address in reached:
            continue
        row = by_address.get(address)
        if row is None:
            raise ValueError("CFG edge misses a main instruction")
        reached.add(address)
        after = address + row.size
        if row.mnemonic == "ret":
            continue
        if row.mnemonic == "jmp":
            if row.operands[0].type == x86.X86_OP_IMM:
                destination = row.operands[0].imm
                if START <= destination < START + CALLABLE:
                    pending.append(destination)
                else:
                    tails.add(destination)
            else:
                pending.extend(edges[address])
        elif row.mnemonic.startswith("j"):
            pending.extend((row.operands[0].imm, after))
        else:
            pending.append(after)
    if tails != {0x45AF40, 0x477830}:
        raise ValueError("unreviewed external CFG tail")
    covered = {a for entry in reached for a in range(entry, entry + by_address[entry].size)}
    return dict(reachable_instructions=len(reached), reachable_bytes=len(covered),
                unreachable_bytes=CALLABLE - len(covered),
                returns=sum(by_address[a].mnemonic == "ret" for a in reached),
                external_tails=[hex(a) for a in sorted(tails)])


def load_candidate(path=None):
    c = comparator()
    identity = c.verify_target()
    target = c.target_bytes(START, PAYLOAD)
    if hashlib.sha256(target).hexdigest() != PAYLOAD_SHA or hashlib.sha256(target[:CALLABLE]).hexdigest() != MAIN_SHA:
        raise ValueError("reviewed target payload changed")
    unit = load_manifest()["units"][UNIT]
    function = unit["functions"][0]
    if int(function["address"], 0) != START or function["symbol_base"] != SYMBOL:
        raise ValueError("configured Patchouli initializer changed")
    targets = c.known_targets()
    for binding in function["rel32_targets"]:
        name, address = binding.rsplit("=", 1)
        targets[name] = int(address, 0)
    overrides = dict(binding.split("=", 1) for binding in function["dir32_targets"])
    candidate = c.coff_symbol_bytes(path or ROOT / unit["object"], SYMBOL, START, 0xFFFFFFFF,
                                    targets, c.known_data_targets(), overrides)
    if struct.unpack("<I", c.target_bytes(0x6C4EE8, 4))[0] != START:
        raise ValueError("Patchouli primary slot3C changed")
    return c, identity, candidate, target


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--object", type=Path)
    args = parser.parse_args()
    try:
        c, identity, candidate, target = load_candidate(args.object)
        rows, edges, _, target_inventory = inventory(target)
        report = dict(result="exact" if candidate == target else "mismatch", unit=UNIT,
                      target_sha256=identity, callable_size=CALLABLE, complete_payload_size=PAYLOAD,
                      object_section_tail_size=len(candidate), all_section_relocations_replayed=True,
                      canonical_payload_sha256=hashlib.sha256(candidate).hexdigest(),
                      first_mismatch=c.first_mismatch(target, candidate, START),
                      unmasked_differing_bytes=sum(a != b for a, b in zip(candidate, target)) + abs(len(candidate) - len(target)),
                      target_cfg=close_target_cfg(rows, edges), target_inventory=target_inventory,
                      candidate_inventory=inventory(candidate)[3])
    except (OSError, ValueError, RuntimeError, KeyError, StopIteration, struct.error) as error:
        print(json.dumps(dict(result="blocked", error=str(error)), indent=2))
        return 1
    print(json.dumps(report, indent=2))
    return 0 if report["result"] == "exact" else 1


if __name__ == "__main__":
    raise SystemExit(main())
