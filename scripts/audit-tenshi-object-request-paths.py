#!/usr/bin/env python3
"""Check Tenshi caller argument width and floating transfers at real spawn entry.

Eight854 root prefixes and eight801 loop fragments run native helpers to the
first unparented request. Stack fill0/A5 makes unspecified byte-argument upper
bits visible. The prior801 setup, returning spawn bodies and later iterations
are outside scope. No helper result, return or instruction transfer is injected.
This is diagnostic evidence, not whole-function equivalence or exact acceptance.
"""
from __future__ import annotations

import argparse
import hashlib
import importlib.util
import json
import math
from pathlib import Path
import struct

import pefile
import unicorn
from unicorn import x86_const as registers

from workflow_manifest import load_manifest

ROOT = Path(__file__).resolve().parents[1]
OWNER, STACK, RESOURCE = 0x1000000, 0x2000000, 0x3000000
VTABLE, REQUEST = 0x6C670C, 0x64CCB0
NATIVE_ENTRIES = (0x435160, 0x406360, 0x4063D0, 0x4963A0, 0x64CD00, 0x4067D0)


def load_audit():
    spec = importlib.util.spec_from_file_location(
        "tenshi_request_canonical", ROOT/"scripts/audit-tenshi-object-update.py")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def fragment_entry(whole, code):
    """Identify801's actual loop input after the fifth native motion call."""
    rows, _, _ = whole.inventory(code, None)
    x86 = whole.x86
    motions = [index for index, row in enumerate(rows)
               if row.mnemonic == "call" and row.operands[0].type == x86.X86_OP_IMM
               and row.operands[0].imm == 0x435160]
    if len(motions) != 35:
        raise ValueError("reviewed motion inventory changed")
    start = motions[4]
    for index in range(start+1, start+30):
        row = rows[index]
        if not (row.mnemonic == "mov" and row.operands[0].type == x86.X86_OP_MEM
                and row.operands[0].mem.base == x86.X86_REG_ESI
                and row.operands[0].mem.disp == 0x364
                and row.operands[1].type == x86.X86_OP_IMM
                and row.operands[1].imm == 1):
            continue
        store, load, multiply, push, add = rows[index+1:index+6]
        if [item.mnemonic for item in (store, load, multiply, push, add)] != [
                "fstp", "fld", "fmul", "push", "fadd"]:
            raise ValueError("reviewed loop input sequence changed")
        operand = load.operands[0]
        if not (operand.type == x86.X86_OP_MEM
                and operand.mem.base == x86.X86_REG_ESP and not operand.mem.index
                and store.op_str == load.op_str
                and multiply.operands[0].type == x86.X86_OP_MEM
                and multiply.operands[0].mem.disp == 0x6C3CB8
                and add.operands[0].type == x86.X86_OP_MEM
                and add.operands[0].mem.disp == 0x6C1F48):
            raise ValueError("reviewed loop counter/36/18 inputs changed")
        return load.address, operand.mem.disp
    raise ValueError("reviewed801 loop entry missing")


def cases():
    for sequence, time in ((0, 3), (6, 1)):
        for facing in (1, 255):
            for poison in (0, 0xA5):
                yield dict(kind="root", sequence=sequence, time=time,
                           facing=facing, stack_fill=poison, control=0x27F)
    for counter in (0.0, 3.0):
        for facing in (1, 255):
            for poison in (0, 0xA5):
                yield dict(kind="fragment", sequence=4, time=0, facing=facing,
                           stack_fill=poison, control=0x27F, counter=counter)


def execute(whole, image, code, case):
    engine = unicorn.Uc(unicorn.UC_ARCH_X86, unicorn.UC_MODE_32)
    engine.mem_map(0x400000, (len(image)+4095)//4096*4096)
    engine.mem_write(0x400000, image)
    engine.mem_write(whole.START, code)
    for base, size in ((OWNER, 0x10000), (STACK, 0x10000), (RESOURCE, 0x1000)):
        engine.mem_map(base, size)
    engine.mem_write(STACK, bytes([case["stack_fill"]])*0x10000)

    def put(address, fmt, *values):
        engine.mem_write(address, struct.pack("<"+fmt, *values))

    fragment = case["kind"] == "fragment"
    for offset, fmt, value in (
            (0, "I", VTABLE), (0x13C, "h", 801 if fragment else 854),
            (0x13E, "h", case["sequence"]), (0x144, "i", case["time"]),
            (0x104, "B", case["facing"]), (0xEC, "f", 640.0), (0xF0, "f", 100.0),
            (0x11C, "f", 1.0), (0x120, "f", 1.0),
            (0x340, "I", RESOURCE), (0x348, "I", OWNER+0x1000)):
        put(OWNER+offset, fmt, value)
    put(RESOURCE, "3f", 30.0, 2.0, float(case["sequence"]))
    # A deterministic runtime data fixture; native table initialization is outside scope.
    engine.mem_write(0x6FE8B0, struct.pack(
        "<3600f", *[math.cos(n*math.pi/1800.0) for n in range(3600)]))
    put(0x6FA1FC, "I", 0)
    engine.mem_write(0x6FDEF0, struct.pack("<624I", 1, *range(1, 624)))
    put(STACK+0xFF00, "I", 0x710000)
    engine.reg_write(registers.UC_X86_REG_ECX, OWNER)
    engine.reg_write(registers.UC_X86_REG_ESP, STACK+0xFF00)
    engine.reg_write(registers.UC_X86_REG_FPCW, case["control"])
    engine.reg_write(registers.UC_X86_REG_FPSW, 0)
    engine.reg_write(registers.UC_X86_REG_FPTAG, 65535)
    start = whole.START
    if fragment:
        start, counter_home = fragment_entry(whole, code)
        put(OWNER+0x364, "h", 1)
        put(RESOURCE+4, "f", 0.0)
        engine.reg_write(registers.UC_X86_REG_ESI, OWNER)
        engine.reg_write(registers.UC_X86_REG_ESP, STACK+0xE000)
        put(STACK+0xE000+counter_home, "f", case["counter"])
    engine.mem_protect(RESOURCE, 0x1000, unicorn.UC_PROT_READ)
    result, calls, bounds = {}, [], []

    def observe(uc, address, size, unused):
        if address in NATIVE_ENTRIES:
            calls.append(hex(address))
        if address == 0x4067D0:
            esp = uc.reg_read(registers.UC_X86_REG_ESP)
            bounds.append(struct.unpack("<I", uc.mem_read(esp+4, 4))[0])
        if address != REQUEST:
            return
        esp = uc.reg_read(registers.UC_X86_REG_ESP)
        args = struct.unpack("<7I", uc.mem_read(esp+4, 28))
        result.update(actor=bytes(uc.mem_read(OWNER, 0x388)).hex(),
                      arguments=list(args[:5])+[args[6]],
                      packet=bytes(uc.mem_read(args[5], args[6]*4)).hex(),
                      receiver=uc.reg_read(registers.UC_X86_REG_ECX)-OWNER,
                      calls=calls, rng_bounds=bounds,
                      rng_index=struct.unpack("<I", uc.mem_read(0x6FA1FC, 4))[0],
                      top=(uc.reg_read(registers.UC_X86_REG_FPSW)>>11)&7,
                      control=uc.reg_read(registers.UC_X86_REG_FPCW))
        uc.emu_stop()

    engine.hook_add(unicorn.UC_HOOK_CODE, observe)
    engine.emu_start(start, REQUEST+1, count=50000)
    if not result:
        raise ValueError("no real request entry within reviewed instruction limit")
    return result


def audit(object_path=None):
    whole = load_audit()
    canonical = whole.load_compare()
    identity, target, _, _ = whole.target_facts(canonical)
    unit = load_manifest()["units"][whole.UNIT]
    function, = unit["functions"]
    if int(function["address"], 0) != whole.START or function["symbol_base"] != whole.SYMBOL:
        raise ValueError("configured root changed")
    targets = canonical.known_targets()
    for binding in function["rel32_targets"]:
        name, value = binding.rsplit("=", 1)
        targets[name] = int(value, 0)
    # Both provider-proven caller views are admitted for the recorded negative control.
    for name, value in list(targets.items()):
        if "@TenshiObjectUpdateView@" in name and name.startswith(("?spawn_parented@", "?spawn_unparented@")):
            targets[name.replace("HMMHHPBIH", "HMMEHPBIH")] = value
            targets[name.replace("HMMEHPBIH", "HMMHHPBIH")] = value
    overrides = dict(binding.split("=", 1) for binding in function["dir32_targets"])
    candidate = canonical.coff_symbol_bytes(
        object_path or ROOT/unit["object"], whole.SYMBOL, whole.START, 0xFFFFFFFF,
        targets, canonical.known_data_targets(), overrides)
    image = pefile.PE(str(ROOT/"resources/th105.exe")).get_memory_mapped_image()
    results = []
    for case in cases():
        expected, actual = (execute(whole, image, code, case) for code in (target, candidate))
        fragment = case["kind"] == "fragment"
        action = 801 if fragment else 854
        layer = (-1 if case["counter"] == 0.0 else 1) if fragment else 1
        if (expected["arguments"][0] != action or expected["arguments"][3:] != [
                case["facing"], layer & 0xFFFFFFFF, 3] or expected["receiver"] != 0
                or expected["rng_index"] != (0 if fragment else 3)
                or expected["rng_bounds"] != ([] if fragment else [360, 75, 200])):
            raise ValueError("native request/receiver/RNG contract changed")
        if expected["control"] != case["control"] or expected["top"] != 0:
            raise ValueError("native x87 environment changed")
        results.append(dict(input=case, equal=expected == actual, target=expected, candidate=actual))
    return dict(diagnostic_only=True, target_sha256=identity,
                candidate_sha256=hashlib.sha256(candidate).hexdigest(),
                cases=len(results), mismatches=sum(not row["equal"] for row in results),
                scope="eight854 root request prefixes/eight801 loop fragments; native helpers; "
                      "full DWORD arguments; prior801 setup/returning spawn bodies outside scope",
                results=results)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--object", type=Path)
    args = parser.parse_args()
    report = audit(args.object)
    print(json.dumps(report, indent=2))
    return int(report["mismatches"] != 0)


if __name__ == "__main__":
    raise SystemExit(main())
