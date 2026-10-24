#!/usr/bin/env python3
"""Compare the complete Reimu slot3C source and resolve its three switch tables.

Optional native state cases address shared-tail entry and velocity-reset
ambiguities only. They never replace the unmasked full-payload comparison.
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
UNIT = "exact-first-reimu-action-initialization"
SYMBOL = "?initialize_action_entry@ReimuFinalizationView@th105@@UAEXXZ"
START, CALLABLE, PAYLOAD = 0x491C40, 3785, 4738
MAIN_SHA = "ab70f8336d04a7698b0acaa29ca0ea8784f7a80b36bc7abb3e155d7a5ac7b04b"
PAYLOAD_SHA = "ae72adaa4142577f69d3e97cf57e629c4bcce932a82457c8421dafdf9075f842"


def load_compare():
    spec = importlib.util.spec_from_file_location(
        "reimu_initialization_canonical", ROOT / "scripts/compare-function.py")
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
    return rows, edges, dict(
        code_and_alignment_to_first_table=primary - START, instructions=len(rows),
        returns=sum(i.mnemonic == "ret" for i in rows), tables=tables,
        direct_calls={hex(a): n for a, n in sorted(calls.items())})


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
    if tails != {0x477830}:
        raise ValueError("unexpected external target CFG tail")
    covered = {a for start in reached for a in range(start, start + by_address[start].size)}
    return dict(reachable_instructions=len(reached), reachable_bytes=len(covered),
                unreachable_bytes=CALLABLE - len(covered), external_tails=[hex(a) for a in tails],
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
    return c, identity, candidate, target


def byte_wrapper(c, path):
    symbol = "?emit_effect@ReimuFinalizationView@th105@@QAEXHMMEH@Z"
    overrides = {"?g_effect_sink@th105@@3PAUEffectSinkByteCall@1@A":
                 "?g_effect_sink@th105@@3PAUEffectSink@1@A"}
    code = c.coff_symbol_bytes(path, symbol, 0x435240, 0xFFFFFFFF,
                              c.known_targets(), c.known_data_targets(), overrides)
    expected = c.target_bytes(0x435240, 52)
    if hashlib.sha256(expected).hexdigest() != "766e73525d2dfc9742f5e6e054a58e61f65b5def458e9c42a3aff78b2c075fd8":
        raise ValueError("effect forwarder target changed")
    if struct.unpack("<I", c.target_bytes(0x6C149C, 4))[0] != 0x437C00:
        raise ValueError("actual effect-manager spawn slot changed")
    # Actual provider consumes bytes from direction/flag stack slots. These
    # are transport-width facts, not a claim to the original nominal types.
    if c.target_bytes(0x437C3F, 4) != bytes.fromhex("8a442418"):
        raise ValueError("effect provider direction width changed")
    return dict(exact=code == expected, candidate_size=len(code),
                candidate_sha256=hashlib.sha256(code).hexdigest(),
                first_mismatch=c.first_mismatch(expected, code, 0x435240))


def state_cases(candidate, target):
    """Run only scalar-entry/real-zero-helper paths through genuine RET0."""
    import pefile
    import unicorn
    from unicorn import x86_const as r
    image = pefile.PE(str(ROOT / "resources/th105.exe")).get_memory_mapped_image()
    owner, stack, ret = 0x2000000, 0x2100000, 0x710000
    registers = [r.UC_X86_REG_EBX, r.UC_X86_REG_ESI, r.UC_X86_REG_EDI, r.UC_X86_REG_EBP]
    initial = [0x11223344, 0x22334455, 0x33445566, 0x44556677]
    engines = []
    counters = [Counter(), Counter()]
    faults = [None, None]
    for index, code in enumerate((target, candidate)):
        uc = unicorn.Uc(unicorn.UC_ARCH_X86, unicorn.UC_MODE_32)
        uc.mem_map(0x400000, (len(image) + 0xFFF) & ~0xFFF)
        uc.mem_write(0x400000, image)
        uc.mem_write(START, code)
        uc.mem_map(owner, 0x1000)
        uc.mem_map(stack, 0x10000)
        uc.mem_map(ret, 0x1000)

        def trace(engine, address, size, user_data, index=index, limit=decode_inventory(code)[2]["code_and_alignment_to_first_table"]):
            counters[index][address] += 1
            if not (START <= address < START + limit or 0x45AF40 <= address < 0x45AF40 + 27):
                faults[index] = f"state case escaped its actual providers: {address:#x}"
                engine.emu_stop()

        uc.hook_add(unicorn.UC_HOOK_CODE, trace)
        engines.append(uc)
    actions = [70, 304, 306, 307, 321, 400, 404, 414, 500, 501, 502, 505, 506,
               507, 510, 511, 512, 513, 522,
               560, 565, 608, 669, 612, 616, 619, 797]
    seeds = [(0x40800000, 0xC0600000, 0, 0xFC),
             (0x80000000, 1, 1, 4), (0x7F7FFFFF, 0xFF7FFFFF, 0x80, 127)]
    cases = [(a, *seed) for a in actions for seed in seeds]
    cases += [(a, value, 0x3F800000, 1, 4) for a in (70, 404, 414, 502, 507, 522)
              for value in (0x7F800000, 0xFF800000, 0x7FC12345, 0x7F812345)]
    failures, count = [], 0
    for cw in (0x27F, 0x37F):
        for action, vx, vy, flag, threshold in cases:
            state = bytearray(b"\xa5" * 0x900)
            struct.pack_into("<h", state, 0x13C, action)
            for offset, value in ((0xF4, vx), (0xF8, vy), (0x18C, vx), (0x190, vy)):
                struct.pack_into("<I", state, offset, value)
            state[0x47E], state[0x607] = flag, threshold
            outputs = []
            for index, uc in enumerate(engines):
                uc.mem_write(owner, bytes(state))
                uc.mem_write(stack, bytes(0x10000))
                sp = stack + 0x8000
                uc.mem_write(sp, struct.pack("<I", ret))
                uc.reg_write(r.UC_X86_REG_ESP, sp)
                for register, value in zip(registers, initial):
                    uc.reg_write(register, value)
                uc.reg_write(r.UC_X86_REG_ECX, owner)
                uc.reg_write(r.UC_X86_REG_EFLAGS, 2)
                uc.reg_write(r.UC_X86_REG_FPCW, cw)
                uc.reg_write(r.UC_X86_REG_FPSW, 0)
                uc.reg_write(r.UC_X86_REG_FPTAG, 0xFFFF)
                try:
                    uc.emu_start(START, ret, count=2000)
                except unicorn.UcError as error:
                    raise ValueError(f"state case {action}/{index} at {uc.reg_read(r.UC_X86_REG_EIP):#x}: {error}") from error
                if faults[index]:
                    raise ValueError(faults[index])
                if uc.reg_read(r.UC_X86_REG_EIP) != ret or uc.reg_read(r.UC_X86_REG_ESP) != sp + 4:
                    raise ValueError("state case did not execute actual RET0")
                if [uc.reg_read(reg) for reg in registers] != initial:
                    raise ValueError("state case changed callee-saved registers")
                outputs.append(bytes(uc.mem_read(owner, len(state))))
            count += 1
            if outputs[0] != outputs[1]:
                differences = [i for i, pair in enumerate(zip(*outputs)) if pair[0] != pair[1]]
                failures.append(dict(action=action, control_word=hex(cw), vx=hex(vx), vy=hex(vy),
                                     differing_offsets=[hex(i) for i in differences]))
    return dict(diagnostic_only=True, cases=count, failures=failures,
                actual_zero_helper_entries=[counter[0x45AF40] for counter in counters])


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--object", type=Path)
    parser.add_argument("--byte-wrapper", type=Path)
    parser.add_argument("--scoped-state", action="store_true")
    args = parser.parse_args()
    try:
        c, identity, candidate, target = load_candidate(args.object)
        rows, edges, target_inventory = decode_inventory(target)
        source_inventory = decode_inventory(candidate)[2]
        report = dict(result="exact" if candidate == target else "mismatch", diagnostic_only=True,
                      unit=UNIT, target_sha256=identity, callable_size=CALLABLE,
                      complete_payload_size=PAYLOAD, object_section_tail_size=len(candidate),
                      all_section_relocations_replayed=True,
                      canonical_payload_sha256=hashlib.sha256(candidate).hexdigest(),
                      first_mismatch=c.first_mismatch(target, candidate, START),
                      unmasked_differing_bytes=sum(a != b for a, b in zip(candidate, target)) + abs(len(candidate) - len(target)),
                      target_cfg=target_cfg(rows, edges), target_inventory=target_inventory,
                      candidate_inventory=source_inventory)
        if args.byte_wrapper:
            report["byte_wrapper"] = byte_wrapper(c, args.byte_wrapper)
        if args.scoped_state:
            report["scoped_state"] = state_cases(candidate, target)
    except (OSError, ValueError, RuntimeError, KeyError, StopIteration, struct.error) as error:
        print(json.dumps(dict(result="blocked", error=str(error)), indent=2))
        return 1
    print(json.dumps(report, indent=2))
    diagnostics_ok = (not args.byte_wrapper or report["byte_wrapper"]["exact"]) and (
        not args.scoped_state or not report["scoped_state"]["failures"])
    return 0 if report["result"] == "exact" and diagnostics_ok else 1


if __name__ == "__main__":
    raise SystemExit(main())
