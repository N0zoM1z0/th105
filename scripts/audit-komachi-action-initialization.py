#!/usr/bin/env python3
"""Compare complete Komachi slot3C code and all adjacent switch metadata.

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
UNIT = "exact-first-komachi-action-initialization"
SYMBOL = "?initialize_action_entry@KomachiActionEntryView@th105@@UAEXXZ"
START, CALLABLE, PAYLOAD = 0x5F6700, 1971, 2496
MAIN_SHA = "b914a20a2cfa84638b160892ff82bc4094be80628d5644ba537844d80fd1a222"
PAYLOAD_SHA = "48a2fcaa2f8f97b95ab76e7a30edb91d0a0f552ad986c491e1a5be3bc8ce3b72"


def load_compare():
    spec = importlib.util.spec_from_file_location(
        "komachi_initialization_canonical", ROOT / "scripts/compare-function.py")
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
    if struct.unpack("<I", c.target_bytes(0x6C60A0, 4))[0] != START:
        raise ValueError("Komachi primary slot3C changed")
    return c, identity, candidate, target


def shared_initial_witness(candidate, target):
    """Execute only550/551, their actual zero helper and complete RET0 paths."""
    import pefile
    import unicorn
    from unicorn import x86_const as r
    image = pefile.PE(str(ROOT / "resources/th105.exe")).get_memory_mapped_image()
    owner, stack, ret = 0x2000000, 0x2100000, 0x710000
    registers = (r.UC_X86_REG_EBX, r.UC_X86_REG_ESI, r.UC_X86_REG_EDI, r.UC_X86_REG_EBP)
    initial = (0x11223344, 0x22334455, 0x33445566, 0x44556677)
    cases = []
    for action in (550, 551):
        memory = bytearray(b"\xa5" * 0x900)
        struct.pack_into("<I", memory, 0, 0x6C6064)
        struct.pack_into("<h", memory, 0x13C, action)
        outputs, helpers = [], []
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
            state = dict(fault=None, zero_entries=0)
            code_end = START + decode_inventory(code)[2]["code_and_alignment_to_first_table"]

            def trace(engine, address, size, user_data, state=state, code_end=code_end):
                if address == 0x45AF40:
                    state["zero_entries"] += 1
                if not (START <= address < code_end or 0x45AF40 <= address < 0x45AF5B):
                    state["fault"] = f"unreviewed provider/instruction {address:#x}"
                    engine.emu_stop()

            uc.hook_add(unicorn.UC_HOOK_CODE, trace)
            try:
                uc.emu_start(START, ret, count=1000)
            except unicorn.UcError as error:
                raise ValueError(f"action{action} native execution: {error}") from error
            if state["fault"]:
                raise ValueError(state["fault"])
            if (uc.reg_read(r.UC_X86_REG_EIP) != ret or uc.reg_read(r.UC_X86_REG_ESP) != sp + 4
                    or tuple(uc.reg_read(reg) for reg in registers) != initial):
                raise ValueError(f"action{action} did not preserve RET0 stack/nonvolatile ABI")
            if state["zero_entries"] != 1:
                raise ValueError(f"action{action} did not execute its actual zero helper once")
            outputs.append(bytes(uc.mem_read(owner, len(memory))))
            helpers.append(state["zero_entries"])
        cases.append(dict(action=action, actual_zero_helper_entries=helpers,
                          differing_owner_offsets=[hex(i) for i, (a, b) in enumerate(zip(*outputs)) if a != b],
                          target_73c=struct.unpack_from("<f", outputs[0], 0x73C)[0],
                          candidate_73c=struct.unpack_from("<f", outputs[1], 0x73C)[0]))
    return dict(diagnostic_only=True, fpcw="0x27f", cases=cases)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--object", type=Path)
    parser.add_argument("--shared-initial-witness", action="store_true")
    args = parser.parse_args()
    try:
        c, identity, candidate, target = load_candidate(args.object)
        rows, edges, target_inventory = decode_inventory(target)
        if [(t["dwords"], t["remap_bytes"]) for t in target_inventory["tables"]] != [(19, 119), (25, 228)]:
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
        if args.shared_initial_witness:
            report["shared_initial_witness"] = shared_initial_witness(candidate, target)
    except (OSError, ValueError, RuntimeError, KeyError, StopIteration, struct.error) as error:
        print(json.dumps(dict(result="blocked", error=str(error)), indent=2))
        return 1
    print(json.dumps(report, indent=2))
    return 0 if report["result"] == "exact" else 1


if __name__ == "__main__":
    raise SystemExit(main())
