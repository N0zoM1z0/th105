#!/usr/bin/env python3
"""Compare complete Yukari slot3C code and all adjacent switch metadata.

The optional one-case native reset diagnostic retains the actual67-byte scratch
helper and checks action214 through RET0; it supplies no provider results.
"""
from __future__ import annotations

import argparse
from collections import Counter
import hashlib
import importlib.util
import json
from pathlib import Path
import struct
import sys

import capstone
from capstone import x86
from workflow_manifest import load_manifest

ROOT = Path(__file__).resolve().parents[1]
UNIT = "exact-first-yukari-action-initialization"
SYMBOL = "?initialize_action_entry@YukariActionEntryView@th105@@UAEXXZ"
START, CALLABLE, PAYLOAD = 0x58A4F0, 3455, 4381
MAIN_SHA = "765e801111cac9931a478958e39115b0f4a0128f6379d6a9657486aa688824d3"
PAYLOAD_SHA = "e0a7822f65f99607719fd6354ba4d14e4e182439d1aebae2ef0d2a1888135334"


def load_compare():
    spec = importlib.util.spec_from_file_location(
        "yukari_initialization_canonical", ROOT / "scripts/compare-function.py")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def decode_inventory(code):
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    decoder.detail = True
    prefix = list(decoder.disasm(code[:64], START))
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
    if len(tables) != 3:
        raise ValueError("expected three complete switches")
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
    if struct.unpack("<I", c.target_bytes(0x6C5908, 4))[0] != START:
        raise ValueError("Yukari primary slot3C changed")
    return c, identity, candidate, target


def scoped_reset(candidate, target):
    """Execute only actual action214 and the actual scratch reset to RET0."""
    import pefile
    import unicorn
    from unicorn import x86_const as r
    image = pefile.PE(str(ROOT / "resources/th105.exe")).get_memory_mapped_image()
    owner, stack, ret = 0x2000000, 0x2100000, 0x710000
    memory = bytearray(b"\xa5" * 0x900)
    struct.pack_into("<I", memory, 0, 0x6C58CC)
    struct.pack_into("<h", memory, 0x13C, 214)
    registers = (r.UC_X86_REG_EBX, r.UC_X86_REG_ESI, r.UC_X86_REG_EDI, r.UC_X86_REG_EBP)
    initial = (0x11223344, 0x22334455, 0x33445566, 0x44556677)
    outputs, entries = [], []
    for code in (target, candidate):
        uc = unicorn.Uc(unicorn.UC_ARCH_X86, unicorn.UC_MODE_32)
        uc.mem_map(0x400000, (len(image) + 0xFFF) & ~0xFFF)
        uc.mem_write(0x400000, image)
        uc.mem_write(START, code)
        uc.mem_map(owner, 0x1000)
        uc.mem_write(owner, bytes(memory))
        uc.mem_map(stack, 0x10000)
        sp = stack + 0x8000
        uc.mem_write(sp, struct.pack("<I", ret))
        uc.mem_map(ret, 0x1000)
        uc.reg_write(r.UC_X86_REG_ESP, sp)
        uc.reg_write(r.UC_X86_REG_ECX, owner)
        uc.reg_write(r.UC_X86_REG_EFLAGS, 2)
        uc.reg_write(r.UC_X86_REG_FPCW, 0x27F)
        uc.reg_write(r.UC_X86_REG_FPSW, 0)
        uc.reg_write(r.UC_X86_REG_FPTAG, 0xFFFF)
        for reg, value in zip(registers, initial):
            uc.reg_write(reg, value)
        state = dict(fault=None, scratch_entries=0)
        code_end = START + decode_inventory(code)[2]["code_and_alignment_to_first_table"]

        def trace(engine, address, size, user_data, state=state, code_end=code_end):
            if address == 0x435110:
                state["scratch_entries"] += 1
            if not (START <= address < code_end or 0x435110 <= address < 0x435153):
                state["fault"] = f"unreviewed provider/instruction {address:#x}"
                engine.emu_stop()

        uc.hook_add(unicorn.UC_HOOK_CODE, trace)
        try:
            uc.emu_start(START, ret, count=1000)
        except unicorn.UcError as error:
            raise ValueError(f"action214 native execution: {error}") from error
        if state["fault"]:
            raise ValueError(state["fault"])
        if (uc.reg_read(r.UC_X86_REG_EIP) != ret or uc.reg_read(r.UC_X86_REG_ESP) != sp + 4
                or tuple(uc.reg_read(reg) for reg in registers) != initial):
            raise ValueError("action214 did not preserve actual RET0 stack/nonvolatile ABI")
        if state["scratch_entries"] != 1:
            raise ValueError("action214 did not execute its actual scratch helper once")
        outputs.append(bytes(uc.mem_read(owner, len(memory))))
        entries.append(state["scratch_entries"])
    differences = [hex(i) for i, (a, b) in enumerate(zip(*outputs)) if a != b]
    return dict(diagnostic_only=True, cases=1, actual_scratch_helper_entries=entries,
                differing_owner_offsets=differences,
                target_73c_74c=list(struct.unpack_from("<f", outputs[0], off)[0] for off in (0x73C, 0x74C)),
                candidate_73c_74c=list(struct.unpack_from("<f", outputs[1], off)[0] for off in (0x73C, 0x74C)))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--object", type=Path)
    parser.add_argument("--scoped-reset", action="store_true")
    args = parser.parse_args()
    try:
        c, identity, candidate, target = load_candidate(args.object)
        rows, edges, target_inventory = decode_inventory(target)
        dimensions = [(t["dwords"], t["remap_bytes"]) for t in target_inventory["tables"]]
        if dimensions != [(14, 211), (26, 248), (17, 237)]:
            raise ValueError("reviewed three-table ownership changed")
        report = dict(result="exact" if candidate == target else "mismatch", unit=UNIT,
                      target_sha256=identity, callable_size=CALLABLE, complete_payload_size=PAYLOAD,
                      object_section_tail_size=len(candidate), all_section_relocations_replayed=True,
                      canonical_payload_sha256=hashlib.sha256(candidate).hexdigest(),
                      first_mismatch=c.first_mismatch(target, candidate, START),
                      unmasked_differing_bytes=sum(a != b for a, b in zip(candidate, target)) + abs(len(candidate) - len(target)),
                      target_cfg=target_cfg(rows, edges), target_inventory=target_inventory,
                      candidate_inventory=decode_inventory(candidate)[2])
        if args.scoped_reset:
            report["scoped_reset"] = scoped_reset(candidate, target)
    except (OSError, ValueError, RuntimeError, KeyError, StopIteration, struct.error) as error:
        print(json.dumps(dict(result="blocked", error=str(error)), indent=2))
        return 1
    print(json.dumps(report, indent=2))
    diagnostics_ok = not args.scoped_reset or not report["scoped_reset"]["differing_owner_offsets"]
    return 0 if report["result"] == "exact" and diagnostics_ok else 1


if __name__ == "__main__":
    raise SystemExit(main())
