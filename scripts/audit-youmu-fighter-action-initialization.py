#!/usr/bin/env python3
"""Compare complete Youmu Fighter slot3C code and all adjacent switch metadata.

Both remapped tables, adjacent alignment and the complete COFF symbol
participate in canonical relocation replay without masking or partial credit.
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
UNIT = "exact-first-youmu-fighter-action-initialization"
SYMBOL = "?initialize_action_entry@YoumuFighterActionEntryView@th105@@UAEXXZ"
START, CALLABLE, PAYLOAD = 0x53A1D0, 1424, 1874
MAIN_SHA = "cc0458b925ef32d9195d351e0fa67642028edb5c7776d9cddead0ad44e2415b8"
PAYLOAD_SHA = "9ae1d2bcebc090193d038f6998f47199d9aac2ebeb60e6b9cdc540f0fefe2609"


def load_compare():
    spec = importlib.util.spec_from_file_location(
        "youmu-fighter_initialization_canonical", ROOT / "scripts/compare-function.py")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def decode_inventory(code):
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    decoder.detail = True
    prefix = list(decoder.disasm(code, START))
    primary = next(i.operands[0].mem.disp for i in prefix
                   if i.mnemonic == "jmp" and i.operands[0].type == x86.X86_OP_MEM)
    if not START < primary < START + len(code):
        raise ValueError("first destination table escapes payload")
    rows = list(decoder.disasm(code[:primary - START], START))
    if sum(i.size for i in rows) != primary - START:
        raise ValueError("incomplete main/alignment decode")
    tables, edges = [], {}
    for index, row in enumerate(rows):
        if row.mnemonic != "jmp" or row.operands[0].type != x86.X86_OP_MEM:
            continue
        base = row.operands[0].mem.disp
        history = rows[max(0, index - 8):index]
        remap = next(i.operands[1].mem.disp for i in reversed(history)
                     if i.mnemonic == "movzx" and i.operands[1].type == x86.X86_OP_MEM
                     and START < i.operands[1].mem.disp < START + len(code))
        lower = next(i.operands[1].imm for i in reversed(history)
                     if i.mnemonic == "sub" and i.operands[0].reg == x86.X86_REG_EAX
                     and i.operands[1].type == x86.X86_OP_IMM)
        count = 1 + next(i.operands[1].imm for i in reversed(history)
                         if i.mnemonic == "cmp" and i.operands[0].reg == x86.X86_REG_EAX
                         and i.operands[1].type == x86.X86_OP_IMM)
        if not primary <= base < remap <= START + len(code) - count or (remap - base) % 4:
            raise ValueError("switch metadata extent escapes payload")
        words = (remap - base) // 4
        destinations = struct.unpack_from("<" + "I" * words, code, base - START)
        indices = code[remap - START:remap - START + count]
        if not words or max(indices) >= words or any(not START <= a < primary for a in destinations):
            raise ValueError("switch destination/index is outside its code/table")
        edges[row.address] = sorted(set(destinations))
        tables.append(dict(site=hex(row.address), address=hex(base), dwords=words,
                           first_case=lower, remap_bytes=count,
                           remap_sha256=hashlib.sha256(indices).hexdigest()))
    if len(tables) != 2:
        raise ValueError("expected two complete switches")
    calls = Counter(i.operands[0].imm for i in rows
                    if i.mnemonic == "call" and i.operands[0].type == x86.X86_OP_IMM)
    tails = Counter(i.operands[0].imm for i in rows
                    if i.mnemonic == "jmp" and i.operands[0].type == x86.X86_OP_IMM
                    and not START <= i.operands[0].imm < primary)
    return rows, edges, dict(
        code_and_alignment_to_first_table=primary - START, instructions=len(rows),
        returns=sum(i.mnemonic == "ret" for i in rows), tables=tables,
        direct_calls={hex(a): n for a, n in sorted(calls.items())},
        external_tail_sites={hex(a): n for a, n in sorted(tails.items())})


def target_cfg(rows, edges):
    by_address = {i.address: i for i in rows if i.address < START + CALLABLE}
    pending, reached, tails = [START], set(), set()
    while pending:
        address = pending.pop()
        if address in reached:
            continue
        row = by_address.get(address)
        if row is None:
            raise ValueError("target CFG edge misses a main instruction")
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
            pending.extend([row.operands[0].imm, after])
        else:
            pending.append(after)
    if tails != {0x477830, 0x45AF40}:
        raise ValueError("unexpected external target CFG tail")
    covered = {a for start in reached for a in range(start, start + by_address[start].size)}
    return dict(reachable_instructions=len(reached), reachable_bytes=len(covered),
                unreachable_bytes=CALLABLE - len(covered), external_tails=[hex(a) for a in sorted(tails)],
                returns=sum(by_address[a].mnemonic == "ret" for a in reached))


def load_candidate(path=None):
    c = load_compare()
    identity = c.verify_target()
    target = c.target_bytes(START, PAYLOAD)
    if hashlib.sha256(target).hexdigest() != PAYLOAD_SHA or hashlib.sha256(target[:CALLABLE]).hexdigest() != MAIN_SHA:
        raise ValueError("reviewed target span changed")
    unit = load_manifest()["units"][UNIT]
    function = unit["functions"][0]
    if int(function["address"], 0) != START or function["symbol_base"] != SYMBOL:
        raise ValueError("configured root changed")
    targets = c.known_targets()
    for binding in function["rel32_targets"]:
        name, address = binding.rsplit("=", 1)
        targets[name] = int(address, 0)
    overrides = dict(binding.split("=", 1) for binding in function["dir32_targets"])
    candidate = c.coff_symbol_bytes(path or ROOT / unit["object"], SYMBOL, START, 0xFFFFFFFF,
                                     targets, c.known_data_targets(), overrides)
    if struct.unpack("<I", c.target_bytes(0x6C5180, 4))[0] != START:
        raise ValueError("Youmu Fighter primary slot3C changed")
    return c, identity, candidate, target


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--object", type=Path)
    args = parser.parse_args()
    try:
        c, identity, candidate, target = load_candidate(args.object)
        rows, edges, target_inventory = decode_inventory(target)
        if [(t["dwords"], t["remap_bytes"]) for t in target_inventory["tables"]] != [(14, 119), (12, 226)]:
            raise ValueError("reviewed two-table ownership changed")
        report = dict(result="exact" if candidate == target else "mismatch",
                      unit=UNIT, target_sha256=identity, callable_size=CALLABLE,
                      complete_payload_size=PAYLOAD, object_section_tail_size=len(candidate),
                      all_section_relocations_replayed=True,
                      canonical_payload_sha256=hashlib.sha256(candidate).hexdigest(),
                      first_mismatch=c.first_mismatch(target, candidate, START),
                      unmasked_differing_bytes=sum(a != b for a, b in zip(candidate, target)) + abs(len(candidate) - len(target)),
                      target_cfg=target_cfg(rows, edges), target_inventory=target_inventory,
                      candidate_inventory=decode_inventory(candidate)[2])
    except (OSError, ValueError, RuntimeError, KeyError, StopIteration, struct.error) as error:
        print(json.dumps(dict(result="blocked", error=str(error)), indent=2))
        return 1
    print(json.dumps(report, indent=2))
    return 0 if report["result"] == "exact" else 1


if __name__ == "__main__":
    raise SystemExit(main())
