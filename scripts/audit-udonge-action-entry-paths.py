#!/usr/bin/env python3
"""Execute ten specific Udonge initializer ambiguities with native helpers.

Nine inputs complete the real RET; action308 stops at the real object-request
entry. That helper and later gameplay are outside the prefix. No helper result
is injected, and sampled agreement earns no canonical exact credit.
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
ADDRESS, PAYLOAD_SIZE = 0x5D0E60, 5070
PAYLOAD_SHA256 = "8f038ebad8a86ccfd5a48f007796421cd0d68b741fec384e4540cc905cb917aa"
OWNER, STACK, RETURN = 0x1000000, 0x2000000, 0x710000


def cases():
    for bits in (0x40000000, 0xC0000000, 0, 0x7FC00000):
        yield dict(action=70, vx_bits=bits, skill=3)
    for action in (145, 149, 308):
        yield dict(action=action, vx_bits=0x40000000, skill=3)
    for skill in (3, 4, -1):
        yield dict(action=550, vx_bits=0x40000000, skill=skill)


def execute(image, code, case):
    engine = unicorn.Uc(unicorn.UC_ARCH_X86, unicorn.UC_MODE_32)
    engine.mem_map(0x400000, (len(image)+4095)//4096*4096)
    engine.mem_write(0x400000, image)
    engine.mem_write(ADDRESS, code)
    engine.mem_map(OWNER, 4096)
    engine.mem_map(STACK, 65536)
    engine.mem_map(RETURN, 4096)

    def put(offset, fmt, value):
        engine.mem_write(OWNER+offset, struct.pack(fmt, value))

    for offset, value in ((0xEC,100.5), (0xF0,200.125), (0xF4,9.),
                          (0xF8,-8.), (0xFC,1.25), (0x100,-.25),
                          (0x190,3.5), (0x12C,37.5), (0x7A8,.33)):
        put(offset, "<f", value)
    for offset, value in ((0x730,9), (0x732,4), (0x734,5), (0x736,6),
                          (0x4AE,5), (0x7A6,8)):
        put(offset, "<h", value)
    put(0x13C, "<h", case["action"])
    put(0x18C, "<I", case["vx_bits"])
    put(0x60E, "<b", case["skill"])
    put(0x104, "<B", 255)
    put(0x113, "<B", 52)
    put(0x184, "<B", 5)
    put(0x180, "<i", 9)
    engine.mem_write(STACK+0xFF00, struct.pack("<I", RETURN))
    engine.reg_write(registers.UC_X86_REG_ECX, OWNER)
    engine.reg_write(registers.UC_X86_REG_ESP, STACK+0xFF00)
    engine.reg_write(registers.UC_X86_REG_FPCW, 0x27F)
    engine.reg_write(registers.UC_X86_REG_FPSW, 0)
    engine.reg_write(registers.UC_X86_REG_FPTAG, 65535)
    result, calls = {}, []

    def stop(uc, kind):
        result.update(boundary=kind, actor=bytes(uc.mem_read(OWNER, 0x7AC)).hex(),
                      calls=calls, control=uc.reg_read(registers.UC_X86_REG_FPCW),
                      top=(uc.reg_read(registers.UC_X86_REG_FPSW) >> 11) & 7,
                      tags=uc.reg_read(registers.UC_X86_REG_FPTAG))
        uc.emu_stop()

    def step(uc, address, size, unused):
        if address in (0x5D06D0, 0x45AF40):
            calls.append([hex(address), uc.reg_read(registers.UC_X86_REG_ECX)-OWNER])
        if address == RETURN:
            stop(uc, "ret")
            result["stack_delta"] = uc.reg_read(registers.UC_X86_REG_ESP)-(STACK+0xFF00)
        if address == 0x465190:
            esp = uc.reg_read(registers.UC_X86_REG_ESP)
            args = struct.unpack("<7I", uc.mem_read(esp+4, 28))
            result["spawn_args"] = list(args[:5])+[args[6]]
            result["payload"] = bytes(uc.mem_read(args[5], args[6]*4)).hex()
            stop(uc, "spawn-entry")

    engine.hook_add(unicorn.UC_HOOK_CODE, step)
    engine.emu_start(ADDRESS, RETURN+1, count=20000)
    if not result:
        raise ValueError("did not complete the bounded initializer path")
    return result


def confirm_target(case, result):
    actor = bytes.fromhex(result["actor"])
    if case["action"] == 70:
        state = struct.unpack_from("<h", actor, 0x730)[0]
        expected = {0x40000000:-1, 0xC0000000:1, 0:0, 0x7FC00000:0}[case["vx_bits"]]
        if state != expected:
            raise ValueError("native target did not confirm the ordered motion sign")
    if case["action"] in (145, 149):
        heading = struct.unpack_from("<f", actor, 0x12C)[0]
        if heading != (0. if case["action"] == 145 else 37.5):
            raise ValueError("native target did not confirm heading preservation")
    if case["action"] == 550:
        state = struct.unpack_from("<h", actor, 0x736)[0]
        if state != (1 if case["skill"] == 4 else 0):
            raise ValueError("native target did not confirm the signed skill guard")
    if case["action"] == 308:
        if (result["boundary"] != "spawn-entry"
                or result["spawn_args"] != [848,0x42C90000,0x43482000,255,1,3]
                or result["payload"] != struct.pack("<3f", 9., -8., 5.).hex()):
            raise ValueError("native target did not confirm object-request arguments")
    elif result["boundary"] != "ret" or result["stack_delta"] != 4:
        raise ValueError("native target did not complete its ordinary RET0")


def audit(object_path):
    spec = importlib.util.spec_from_file_location(
        "udonge_entry_canonical", ROOT / "scripts/compare-function.py")
    canonical = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(canonical)
    identity = canonical.verify_target()
    target = canonical.target_bytes(ADDRESS, PAYLOAD_SIZE)
    if hashlib.sha256(target).hexdigest() != PAYLOAD_SHA256:
        raise ValueError("complete target payload changed")
    unit = load_manifest()["units"]["exact-first-udonge-action-entry"]
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
    count, failures, digest = 0, [], hashlib.sha256()
    for case in cases():
        expected, actual = (execute(image, code, case) for code in (target, candidate))
        confirm_target(case, expected)
        count += 1
        digest.update(json.dumps(case, sort_keys=True).encode())
        if expected != actual:
            failures.append(dict(case=case, differing_fields=[
                key for key in expected if expected[key] != actual[key]]))
    return dict(diagnostic_only=True, target_sha256=identity,
                candidate_sha256=hashlib.sha256(candidate).hexdigest(), count=count,
                vector_sha256=digest.hexdigest(), mismatch_count=len(failures),
                failures=failures, scope="nine complete native RET paths and one308 pre-spawn prefix; no whole-function behavioral or canonical claim")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--object", type=Path)
    args = parser.parse_args()
    unit = load_manifest()["units"]["exact-first-udonge-action-entry"]
    report = audit(args.object or ROOT / unit["object"])
    print(json.dumps(report, indent=2))
    return int(report["mismatch_count"] != 0)


if __name__ == "__main__":
    raise SystemExit(main())
