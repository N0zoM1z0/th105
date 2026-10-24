#!/usr/bin/env python3
"""Check eleven specific YukariObject initializer paths with native instructions.

Eight inputs complete a real RET; three stop at the real sequence-selector
entry, after the native FTOL helper. No helper result or return is injected.
Sampled agreement earns no canonical exact credit.
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
UNIT = "exact-first-yukari-object-entry"
ADDRESS, PAYLOAD_SIZE = 0x5964C0, 7920
PAYLOAD_SHA256 = "fb73594060287afb176b96a75a0a95832f6986ed9deb7afd8e5112f8896c7352"
OWNER, STACK, RETURN, VTABLE = 0x1000000, 0x2000000, 0x710000, 0x6C5844


def cases():
    for bits in (0, 0x80000000, 0x3F800000, 0xBF800000, 0x7FC00000):
        yield dict(action=850, sequence=2, facing=255, selector_bits=bits)
    for action in (851, 854):
        for sequence in (0, 1):
            yield dict(action=action, sequence=sequence, facing=1, selector_bits=0)
    for facing in (1, 255):
        yield dict(action=998, sequence=0, facing=facing, selector_bits=0)


def execute(image, code, selector, case):
    engine = unicorn.Uc(unicorn.UC_ARCH_X86, unicorn.UC_MODE_32)
    engine.mem_map(0x400000, (len(image)+4095)//4096*4096)
    engine.mem_write(0x400000, image)
    engine.mem_write(ADDRESS, code)
    engine.mem_map(OWNER, 4096)
    engine.mem_map(STACK, 65536)
    engine.mem_map(RETURN, 4096)

    def put(offset, fmt, value):
        engine.mem_write(OWNER+offset, struct.pack(fmt, value))

    put(0, "<I", VTABLE)
    put(0x13C, "<h", case["action"])
    put(0x13E, "<h", case["sequence"])
    put(0x104, "<B", case["facing"])
    for offset, value in ((0xEC,100.5), (0xF0,200.125), (0x11C,7.), (0x120,8.)):
        put(offset, "<f", value)
    put(0x344, "<h", 9)
    put(0x184, "<B", 17)
    put(0x340, "<I", OWNER+0x800)
    engine.mem_write(OWNER+0x800, struct.pack("<2fI", 37.5, 2.5, case["selector_bits"]))
    engine.mem_write(STACK+0xFF00, struct.pack("<I", RETURN))
    engine.reg_write(registers.UC_X86_REG_ECX, OWNER)
    engine.reg_write(registers.UC_X86_REG_ESP, STACK+0xFF00)
    engine.reg_write(registers.UC_X86_REG_FPCW, 0x27F)
    engine.reg_write(registers.UC_X86_REG_FPSW, 0)
    engine.reg_write(registers.UC_X86_REG_FPTAG, 65535)
    result = {}

    def step(uc, address, size, unused):
        if address not in (selector, RETURN):
            return
        esp = uc.reg_read(registers.UC_X86_REG_ESP)
        result.update(boundary="selector-entry" if address == selector else "ret",
                      actor=bytes(uc.mem_read(OWNER, 0x388)).hex(),
                      control=uc.reg_read(registers.UC_X86_REG_FPCW),
                      top=(uc.reg_read(registers.UC_X86_REG_FPSW) >> 11) & 7,
                      tags=uc.reg_read(registers.UC_X86_REG_FPTAG))
        if address == selector:
            result.update(receiver=uc.reg_read(registers.UC_X86_REG_ECX)-OWNER,
                          sequence_argument=struct.unpack("<I", uc.mem_read(esp+4,4))[0])
        else:
            result["stack_delta"] = esp-(STACK+0xFF00)
        uc.emu_stop()

    engine.hook_add(unicorn.UC_HOOK_CODE, step)
    engine.emu_start(ADDRESS, RETURN+1, count=20000)
    if not result:
        raise ValueError("did not reach the reviewed native boundary")
    return result


def confirm_target(case, result):
    actor = bytes.fromhex(result["actor"])
    value = lambda offset: struct.unpack_from("<f", actor, offset)[0]
    selects = case["action"] == 850 and case["selector_bits"] not in (0, 0x80000000)
    if selects:
        if result["boundary"] != "selector-entry" or result["receiver"] != 0:
            raise ValueError("target did not confirm the nonzero selector prefix")
    elif result["boundary"] != "ret" or result["stack_delta"] != 4:
        raise ValueError("target did not complete its ordinary RET0")
    if case["action"] == 850:
        if value(0x124) != 30. or value(0x128) != 60.:
            raise ValueError("target did not confirm signed facing/heading setup")
        if not selects and (value(0x11C),value(0x120)) != (2.5,2.5):
            raise ValueError("target did not confirm the zero-selector scale pair")
    if case["action"] in (851, 854):
        active = case["sequence"] == 0
        expected = (1.,0.,3.) if active else (0.,7.,8.)
        if (value(0x370),value(0x11C),value(0x120)) != expected:
            raise ValueError("target did not confirm the retained return suffix")
        if actor[0x184] != int(active and case["action"] == 854):
            raise ValueError("target did not confirm the854-only byte flag")
    if case["action"] == 998:
        if value(0x124) != (-30. if case["facing"] == 1 else 30.) or value(0x128) != 65.:
            raise ValueError("target did not confirm signed998 facing")


def audit(object_path):
    spec = importlib.util.spec_from_file_location(
        "yukari_object_entry_canonical", ROOT / "scripts/compare-function.py")
    canonical = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(canonical)
    identity = canonical.verify_target()
    target = canonical.target_bytes(ADDRESS, PAYLOAD_SIZE)
    if hashlib.sha256(target).hexdigest() != PAYLOAD_SHA256:
        raise ValueError("complete target payload changed")
    if struct.unpack("<I", canonical.target_bytes(VTABLE+0x3C,4))[0] != ADDRESS:
        raise ValueError("reviewed primary vtable cell changed")
    selector = struct.unpack("<I", canonical.target_bytes(VTABLE+0x0C,4))[0]
    unit = load_manifest()["units"][UNIT]
    function, = unit["functions"]
    if int(function["address"],0) != ADDRESS:
        raise ValueError("configured root changed")
    targets = canonical.known_targets()
    for binding in function["rel32_targets"]:
        name, value = binding.rsplit("=",1)
        targets[name] = int(value,0)
    candidate = canonical.coff_symbol_bytes(
        object_path, function["symbol_base"], ADDRESS, 0xFFFFFFFF,
        targets, canonical.known_data_targets())
    image = pefile.PE(str(ROOT / "resources/th105.exe")).get_memory_mapped_image()
    count, failures, digest = 0, [], hashlib.sha256()
    for case in cases():
        expected, actual = (execute(image, code, selector, case) for code in (target,candidate))
        confirm_target(case,expected)
        count += 1
        digest.update(json.dumps(case,sort_keys=True).encode())
        if expected != actual:
            failures.append(dict(case=case,differing_fields=[
                key for key in sorted(expected.keys() | actual.keys())
                if expected.get(key) != actual.get(key)]))
    return dict(diagnostic_only=True,target_sha256=identity,
                candidate_sha256=hashlib.sha256(candidate).hexdigest(),count=count,
                vector_sha256=digest.hexdigest(),mismatch_count=len(failures),failures=failures,
                scope="eight native RETs and three850 selector-entry prefixes; no whole-function behavioral or canonical claim")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--object",type=Path)
    args = parser.parse_args()
    unit = load_manifest()["units"][UNIT]
    report = audit(args.object or ROOT / unit["object"])
    print(json.dumps(report,indent=2))
    return int(report["mismatch_count"] != 0)


if __name__ == "__main__":
    raise SystemExit(main())
