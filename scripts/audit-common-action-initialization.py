#!/usr/bin/env python3
"""Compare the complete common Fighter initializer and its switch metadata.

The optional native checks cover only input-guard decisions and the card-level
phase. They do not replace whole-source equality or invent provider returns.
"""
from __future__ import annotations

import argparse
from collections import Counter
import hashlib
import importlib.util
import itertools
import json
from pathlib import Path
import struct
import sys

import capstone
from capstone import x86
from workflow_manifest import load_manifest

ROOT = Path(__file__).resolve().parents[1]
UNIT = "exact-first-common-fighter-action-initialization"
SYMBOL = "?initialize_common_action_entry@CommonActionEntryView@th105@@QAEXXZ"
START, CALLABLE, PAYLOAD = 0x477830, 4849, 5521
MAIN_SHA = "dada4fa5c18e788409cb4ccf88e313b61aff32de4936d602cd8f8c24895a0181"
PAYLOAD_SHA = "2c1fe83f0501890e1eae9507b1a27c3a0a6d5d99577d4d341d706872162b2b49"


def comparator():
    spec = importlib.util.spec_from_file_location("common_entry_comparator", ROOT / "scripts/compare-function.py")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def inventory(code):
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    decoder.detail = True
    prefix = list(decoder.disasm(code[:64], START))
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
        arithmetic = [i for i in history if i.mnemonic in {"add", "sub"}
                      and i.operands[0].type == x86.X86_OP_REG
                      and i.operands[0].reg == x86.X86_REG_EAX
                      and i.operands[1].type == x86.X86_OP_IMM]
        if arithmetic:
            step = arithmetic[-1]
            lower = step.operands[1].imm * (-1 if step.mnemonic == "add" else 1)
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
    if [(t["dwords"], t["remap_bytes"]) for t in tables] != [(50, 227), (16, 0), (17, 109)]:
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
    if tails != {0x45AF40}:
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
        raise ValueError("configured common initializer changed")
    targets = c.known_targets()
    for binding in function["rel32_targets"]:
        name, address = binding.rsplit("=", 1)
        targets[name] = int(address, 0)
    overrides = dict(binding.split("=", 1) for binding in function["dir32_targets"])
    candidate = c.coff_symbol_bytes(path or ROOT / unit["object"], SYMBOL, START, 0xFFFFFFFF,
                                    targets, c.known_data_targets(), overrides)
    return c, identity, candidate, target


def width_witness(c, path):
    symbol = "?emit_effect@CommonActionEntryView@th105@@QAEXFMMEH@Z"
    overrides = {"?g_effect_sink@th105@@3PAUCommonEffectSinkWidthView@1@A":
                 "?g_effect_sink@th105@@3PAUEffectSink@1@A"}
    code = c.coff_symbol_bytes(path, symbol, 0x435240, 0xFFFFFFFF,
                              c.known_targets(), c.known_data_targets(), overrides)
    if c.target_bytes(0x435200, 5) != bytes.fromhex("668b442404"):
        raise ValueError("actual effect action setter no longer consumes a word")
    if struct.unpack("<I", c.target_bytes(0x6C14C4, 4))[0] != 0x435200:
        raise ValueError("actual effect action setter slot changed")
    return dict(exact=code == c.target_bytes(0x435240, 52), candidate_size=len(code),
                candidate_sha256=hashlib.sha256(code).hexdigest(),
                first_mismatch=c.first_mismatch(c.target_bytes(0x435240, 52), code, 0x435240))


def scoped_native(candidate, target):
    import pefile
    import unicorn
    from unicorn import x86_const as r
    image = pefile.PE(str(ROOT / "resources/th105.exe")).get_memory_mapped_image()
    owner, stack, ret = 0x2000000, 0x2100000, 0x710000
    worlds = []
    for code in (target, candidate):
        rows, _, tables, summary = inventory(code)
        uc = unicorn.Uc(unicorn.UC_ARCH_X86, unicorn.UC_MODE_32)
        uc.mem_map(0x400000, (len(image) + 0xFFF) & ~0xFFF)
        uc.mem_write(0x400000, image)
        uc.mem_write(START, code)
        uc.mem_map(owner, 0x1000)
        uc.mem_map(stack, 0x10000)
        uc.mem_map(ret, 0x1000)
        state = dict(stop=None, fault=None, zero_entries=0, phase=None)
        instructions = {i.address: i for i in rows}

        def trace(engine, address, size, user_data, state=state, instructions=instructions,
                  limit=START + summary["code_and_alignment_to_first_table"]):
            if address == 0x45AF40:
                state["zero_entries"] += 1
            if 0x45AF40 <= address < 0x45AF40 + 27:
                return
            row = instructions.get(address)
            if row is None or not START <= address < limit:
                state["fault"] = f"unreviewed provider/instruction {address:#x}"
                engine.emu_stop()
                return
            if row.mnemonic == "call":
                if row.operands[0].type == x86.X86_OP_IMM and row.operands[0].imm == 0x45AF40:
                    return
                if state["phase"] == "guard" and row.operands[0].type == x86.X86_OP_REG:
                    register = {x86.X86_REG_EAX: r.UC_X86_REG_EAX,
                                x86.X86_REG_EDX: r.UC_X86_REG_EDX}.get(row.operands[0].reg)
                    if register is None or engine.reg_read(register) != 0x45BFE0:
                        state["fault"] = "guard selected an unreviewed virtual provider"
                    else:
                        state["stop"] = "set_action"
                elif state["phase"] == "card" and row.operands[0].type == x86.X86_OP_IMM and row.operands[0].imm == 0x435240:
                    state["stop"] = "effect_request"
                else:
                    state["fault"] = "unexpected call inside bounded phase"
                engine.emu_stop()

        uc.hook_add(unicorn.UC_HOOK_CODE, trace)
        worlds.append((uc, tables, state))

    def run(world, memory, phase, index=0):
        uc, tables, state = world
        state.update(stop=None, fault=None, phase=phase)
        uc.mem_write(owner, bytes(memory))
        uc.mem_write(stack, bytes(0x10000))
        sp = stack + 0x8000
        uc.mem_write(sp, struct.pack("<I", ret))
        for register, value in ((r.UC_X86_REG_ESP, sp), (r.UC_X86_REG_EAX, index),
                                (r.UC_X86_REG_ECX, owner), (r.UC_X86_REG_EDX, 0),
                                (r.UC_X86_REG_ESI, owner if phase == "card" else 0x22334455),
                                (r.UC_X86_REG_EBX, 1 if phase == "card" else 0x11223344),
                                (r.UC_X86_REG_EDI, 0 if phase == "card" else 0x33445566),
                                (r.UC_X86_REG_EBP, 0x44556677),
                                (r.UC_X86_REG_EFLAGS, 2), (r.UC_X86_REG_FPCW, 0x27F),
                                (r.UC_X86_REG_FPSW, 0), (r.UC_X86_REG_FPTAG, 0xFFFF)):
            uc.reg_write(register, value)
        entry = START if phase == "guard" else tables[1]["destinations"][index]
        try:
            uc.emu_start(entry, ret, count=2000)
        except unicorn.UcError as error:
            raise ValueError(f"native {phase} phase at {uc.reg_read(r.UC_X86_REG_EIP):#x}: {error}") from error
        if state["fault"]:
            raise ValueError(state["fault"])
        stop = state["stop"]
        if stop is None:
            if phase != "guard" or uc.reg_read(r.UC_X86_REG_EIP) != ret or uc.reg_read(r.UC_X86_REG_ESP) != sp + 4:
                raise ValueError("bounded phase did not reach its actual stop")
            saved = [uc.reg_read(reg) for reg in (r.UC_X86_REG_EBX, r.UC_X86_REG_ESI,
                                                 r.UC_X86_REG_EDI, r.UC_X86_REG_EBP)]
            if saved != [0x11223344, 0x22334455, 0x33445566, 0x44556677]:
                raise ValueError("guard return changed callee-saved registers")
            packet = ("actual_RET0",)
        elif stop == "set_action":
            packet = (stop, uc.reg_read(r.UC_X86_REG_ECX), struct.unpack("<h", uc.mem_read(uc.reg_read(r.UC_X86_REG_ESP), 2))[0])
        else:
            if uc.reg_read(r.UC_X86_REG_ESP) != sp - 20:
                raise ValueError("card phase did not prepare five actual arguments")
            packet = (stop, uc.reg_read(r.UC_X86_REG_ECX), *struct.unpack("<5I", uc.mem_read(sp - 20, 20)))
        return bytes(uc.mem_read(owner, len(memory))), packet

    failures, guards, cards = [], 0, 0
    for action, bit, count, vertical, horizontal, facing, gate in itertools.product(
            (6, 7, 8), (False, True), (0, 1, 0xFFFFFFFF), (-1, 0), (-1, 0, 1), (-1, 1), (0, 1)):
        memory = bytearray(b"\xa5" * 0x900)
        struct.pack_into("<I", memory, 0, 0x6C412C)
        struct.pack_into("<h", memory, 0x13C, action)
        memory[0x724] = {6: 4, 7: 16, 8: 8}[action] if bit else 0
        struct.pack_into("<I", memory, 0x6C8, count)
        struct.pack_into("<i", memory, 0x6B8, vertical)
        struct.pack_into("<i", memory, 0x6B4, horizontal)
        memory[0x104], memory[0x47E] = facing & 255, gate
        outcomes = [run(world, memory, "guard") for world in worlds]
        guards += 1
        if outcomes[0] != outcomes[1]:
            failures.append(dict(phase="guard", action=action, bit=bit, count=count,
                                 vertical=vertical, horizontal=horizontal, facing=facing, gate=gate))
    for index, value in itertools.product(range(16), (-128, -2, -1, 0, 4, 127)):
        memory = bytearray(b"\xa5" * 0x900)
        memory[0x624:0x634] = bytes([2] * 16)
        memory[0x624 + index] = value & 255
        struct.pack_into("<h", memory, 0x738, 100 + index)
        struct.pack_into("<II", memory, 0xEC, 0x41200000, 0x41A00000)
        outcomes = [run(world, memory, "card", index) for world in worlds]
        cards += 1
        if outcomes[0] != outcomes[1]:
            failures.append(dict(phase="card", index=index, value=value))
    return dict(diagnostic_only=True, guard_cases=guards, card_phase_cases=cards, failures=failures,
                actual_zero_helper_entries=[world[2]["zero_entries"] for world in worlds],
                card_scope="observed table-entry preconditions through next effect CALL boundary; no provider result supplied")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--object", type=Path)
    parser.add_argument("--width-witness", type=Path)
    parser.add_argument("--scoped-native", action="store_true")
    args = parser.parse_args()
    try:
        c, identity, candidate, target = load_candidate(args.object)
        rows, edges, _, target_inventory = inventory(target)
        report = dict(result="exact" if candidate == target else "mismatch", diagnostic_only=True,
                      unit=UNIT, target_sha256=identity, callable_size=CALLABLE, complete_payload_size=PAYLOAD,
                      object_section_tail_size=len(candidate), all_section_relocations_replayed=True,
                      canonical_payload_sha256=hashlib.sha256(candidate).hexdigest(),
                      first_mismatch=c.first_mismatch(target, candidate, START),
                      unmasked_differing_bytes=sum(a != b for a, b in zip(candidate, target)) + abs(len(candidate) - len(target)),
                      target_cfg=close_target_cfg(rows, edges), target_inventory=target_inventory,
                      candidate_inventory=inventory(candidate)[3])
        if args.width_witness:
            report["width_witness"] = width_witness(c, args.width_witness)
        if args.scoped_native:
            report["scoped_native"] = scoped_native(candidate, target)
    except (OSError, ValueError, RuntimeError, KeyError, StopIteration, struct.error) as error:
        print(json.dumps(dict(result="blocked", error=str(error)), indent=2))
        return 1
    print(json.dumps(report, indent=2))
    diagnostics_ok = (not args.width_witness or report["width_witness"]["exact"]) and (
        not args.scoped_native or not report["scoped_native"]["failures"])
    return 0 if report["result"] == "exact" and diagnostics_ok else 1


if __name__ == "__main__":
    raise SystemExit(main())
