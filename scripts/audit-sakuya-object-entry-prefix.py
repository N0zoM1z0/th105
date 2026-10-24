#!/usr/bin/env python3
"""Resolve SakuyaObject901's heading-read epoch before the first spawn.

Two bounded prefixes execute real motion/math/conversion code. The spawn itself
and subsequent gameplay are outside the observation; this earns no exact credit.
"""
from __future__ import annotations

import argparse
import hashlib
import importlib.util
import json
from pathlib import Path
import struct

import pefile
import unicorn
from unicorn import x86_const as registers
from workflow_manifest import load_manifest

ROOT = Path(__file__).resolve().parents[1]
ADDRESS = 0x4E8060
PAYLOAD_SIZE = 6868
TARGET_PAYLOAD_SHA256 = "3323c8c4ac1fa5c9725d0e921b4b343d15e8de8be40277216222b38e0a942c82"
OWNER = 0x1000000
STACK = 0x2000000


def prefix(image, code, alias):
    engine = unicorn.Uc(unicorn.UC_ARCH_X86, unicorn.UC_MODE_32)
    engine.mem_map(0x400000, (len(image)+4095)//4096*4096)
    engine.mem_write(0x400000, image)
    engine.mem_write(ADDRESS, code)
    engine.mem_map(OWNER, 4096)
    engine.mem_map(STACK, 65536)

    def put(address, fmt, value):
        engine.mem_write(address, struct.pack(fmt, value))

    put(OWNER, "<I", 0x6C488C)
    put(OWNER+0x13C, "<h", 901)
    put(OWNER+0x13E, "<h", 7)
    put(OWNER+0x104, "<B", 255)
    put(OWNER+0xEC, "<f", 100.5)
    put(OWNER+0xF0, "<f", 200.125)
    put(OWNER+0x11C, "<f", 1.)
    put(OWNER+0x120, "<f", 1.)
    # The prefix clears184 first. Its later byte1 write changes an aliased
    # float1.0 to1.000000119..., so a late read is observably wrong.
    heading = OWNER+0x184 if alias else OWNER+0x800
    put(OWNER+0x340, "<I", heading)
    engine.mem_write(heading, struct.pack("<4f", 1., 2., 0., 0.))
    put(STACK+0xFF00, "<I", 0x710000)
    engine.reg_write(registers.UC_X86_REG_ECX, OWNER)
    engine.reg_write(registers.UC_X86_REG_ESP, STACK+0xFF00)
    engine.reg_write(registers.UC_X86_REG_FPCW, 0x27F)
    engine.reg_write(registers.UC_X86_REG_FPSW, 0)
    engine.reg_write(registers.UC_X86_REG_FPTAG, 65535)
    result, calls = {}, []

    def step(uc, address, size, unused):
        esp = uc.reg_read(registers.UC_X86_REG_ESP)
        if address == 0x435160:
            calls.append(dict(receiver=uc.reg_read(registers.UC_X86_REG_ECX)-OWNER,
                              args=bytes(uc.mem_read(esp+4, 8)).hex()))
        if address == 0x4FCA60:
            action, x, y, facing, layer, payload, count = struct.unpack(
                "<7I", uc.mem_read(esp+4, 28))
            if action != 901 or count != 3:
                raise ValueError("unexpected spawn boundary")
            result.update(
                actor=bytes(uc.mem_read(OWNER, 0x388)).hex(),
                args=[action, x, y, facing, layer, count],
                payload=bytes(uc.mem_read(payload, 12)).hex(), calls=calls,
                heading=struct.unpack("<f", uc.mem_read(OWNER+0x12C, 4))[0],
                x87_control=uc.reg_read(registers.UC_X86_REG_FPCW),
                x87_top=(uc.reg_read(registers.UC_X86_REG_FPSW) >> 11) & 7,
                x87_tags=uc.reg_read(registers.UC_X86_REG_FPTAG))
            uc.emu_stop()

    engine.hook_add(unicorn.UC_HOOK_CODE, step)
    engine.emu_start(ADDRESS, 0x710000, count=20000)
    if not result:
        raise ValueError("prefix did not reach the parented-spawn entry")
    return result


def audit(object_path):
    spec = importlib.util.spec_from_file_location(
        "sakuya_prefix_canonical", ROOT / "scripts/compare-function.py")
    canonical = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(canonical)
    identity = canonical.verify_target()
    target = canonical.target_bytes(ADDRESS, PAYLOAD_SIZE)
    if hashlib.sha256(target).hexdigest() != TARGET_PAYLOAD_SHA256:
        raise ValueError("complete target payload changed")
    unit = load_manifest()["units"]["exact-first-sakuya-object-entry"]
    function, = unit["functions"]
    if int(function["address"], 0) != ADDRESS:
        raise ValueError("configured root changed")
    targets = canonical.known_targets()
    for binding in function["rel32_targets"]:
        name, value = binding.rsplit("=", 1)
        targets[name] = int(value, 0)
    candidate = canonical.coff_symbol_bytes(
        object_path, function["symbol_base"], ADDRESS, 0xFFFFFFFF,
        targets, canonical.known_data_targets())
    image = pefile.PE(str(ROOT / "resources/th105.exe")).get_memory_mapped_image()
    results = []
    for alias in (False, True):
        expected, actual = (prefix(image, code, alias) for code in (target, candidate))
        if expected["heading"] != 1.0 or len(expected["calls"]) != 1:
            raise ValueError("native prefix did not confirm the heading-read witness")
        results.append(dict(alias=alias, equal=expected == actual,
                            target_heading=expected["heading"],
                            candidate_heading=actual["heading"],
                            differing_fields=[key for key in expected
                                              if expected[key] != actual[key]]))
    return dict(diagnostic_only=True, target_sha256=identity,
                candidate_sha256=hashlib.sha256(candidate).hexdigest(), cases=2,
                mismatches=sum(not row["equal"] for row in results), results=results,
                scope="901 sequence7 to real spawn entry; real motion/math/FTOL execute; spawn and later gameplay excluded")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--object", type=Path)
    args = parser.parse_args()
    unit = load_manifest()["units"]["exact-first-sakuya-object-entry"]
    report = audit(args.object or ROOT / unit["object"])
    print(json.dumps(report, indent=2))
    return int(report["mismatches"] != 0)


if __name__ == "__main__":
    raise SystemExit(main())
