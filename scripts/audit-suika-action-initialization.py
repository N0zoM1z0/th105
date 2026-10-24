#!/usr/bin/env python3
"""Compare complete Suika slot3C code and all adjacent switch metadata.

The optional loop window is a relocation-replayed diagnostic only. It never
replaces the strict whole-payload result or supplies provider return values.
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
UNIT = "exact-first-suika-action-initialization"
SYMBOL = "?initialize_action_entry@SuikaActionEntryView@th105@@UAEXXZ"
START, CALLABLE, PAYLOAD = 0x5AD4A0, 2577, 3171
MAIN_SHA = "7f8f830fa4b0f6e87494b8f34899215aba9bf38a77a0c2de30a451a7673c7f7d"
PAYLOAD_SHA = "497737f1cea8be3b66368574f3f72eb2833717a47121fbdc875f75edbfb034d0"


def load_compare():
    spec = importlib.util.spec_from_file_location(
        "suika_initialization_canonical", ROOT / "scripts/compare-function.py")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def decode_inventory(code):
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    decoder.detail = True
    prefix = list(decoder.disasm(code[:256], START))
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
    if struct.unpack("<I", c.target_bytes(0x6C5BC8, 4))[0] != START:
        raise ValueError("Suika primary slot3C changed")
    return c, identity, candidate, target


def loop_window(c, path, candidate, target):
    """Rebase the complete source before selecting the observed eight-spawn loop."""
    rows, _, _ = decode_inventory(candidate)
    source_start = next(row.address for index, row in enumerate(rows[:-1])
                        if row.mnemonic == "push" and row.operands[0].type == x86.X86_OP_IMM
                        and row.operands[0].imm == 40 and rows[index + 1].mnemonic == "call"
                        and rows[index + 1].operands[0].type == x86.X86_OP_IMM
                        and rows[index + 1].operands[0].imm == 0x4067D0)
    source_end = next(row.address + row.size for row in rows
                      if row.address > source_start and row.mnemonic == "ret")
    target_start, target_size = 0x5ADDE0, 197
    unit = load_manifest()["units"][UNIT]
    function = unit["functions"][0]
    targets = c.known_targets()
    for binding in function["rel32_targets"]:
        name, address = binding.rsplit("=", 1)
        targets[name] = int(address, 0)
    overrides = dict(binding.split("=", 1) for binding in function["dir32_targets"])
    rebase_root = START + target_start - source_start
    rebased = c.coff_symbol_bytes(path or ROOT / unit["object"], SYMBOL, rebase_root,
                                 0xFFFFFFFF, targets, c.known_data_targets(), overrides)
    code = rebased[source_start - START:source_end - START]
    expected = c.target_bytes(target_start, target_size)
    return dict(diagnostic_only=True, whole_root_exact=candidate == target,
                source_loop_start=hex(source_start), source_root_rebase=hex(rebase_root),
                target_loop_start=hex(target_start), target_size=target_size, source_size=len(code),
                all_section_relocations_replayed=True, exact=code == expected,
                source_sha256=hashlib.sha256(code).hexdigest(),
                first_mismatch=c.first_mismatch(expected, code, target_start),
                scope="first actual push40/RNG call through actual RET0; includes both RNG calls, real payload, spawn and float-loop back edge")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--object", type=Path)
    parser.add_argument("--loop-window", action="store_true")
    args = parser.parse_args()
    try:
        c, identity, candidate, target = load_candidate(args.object)
        rows, edges, target_inventory = decode_inventory(target)
        if [(t["dwords"], t["remap_bytes"]) for t in target_inventory["tables"]] != [(24, 119), (32, 247)]:
            raise ValueError("reviewed two-table ownership changed")
        report = dict(result="exact" if candidate == target else "mismatch", diagnostic_only=True,
                      unit=UNIT, target_sha256=identity, callable_size=CALLABLE,
                      complete_payload_size=PAYLOAD, object_section_tail_size=len(candidate),
                      all_section_relocations_replayed=True,
                      canonical_payload_sha256=hashlib.sha256(candidate).hexdigest(),
                      first_mismatch=c.first_mismatch(target, candidate, START),
                      unmasked_differing_bytes=sum(a != b for a, b in zip(candidate, target)) + abs(len(candidate) - len(target)),
                      target_cfg=target_cfg(rows, edges), target_inventory=target_inventory,
                      candidate_inventory=decode_inventory(candidate)[2])
        if args.loop_window:
            report["loop_window"] = loop_window(c, args.object, candidate, target)
    except (OSError, ValueError, RuntimeError, KeyError, StopIteration, struct.error) as error:
        print(json.dumps(dict(result="blocked", error=str(error)), indent=2))
        return 1
    print(json.dumps(report, indent=2))
    diagnostics_ok = not args.loop_window or report["loop_window"]["exact"]
    return 0 if report["result"] == "exact" and diagnostics_ok else 1


if __name__ == "__main__":
    raise SystemExit(main())
