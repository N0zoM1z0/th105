#!/usr/bin/env python3
"""Check Alice214's inactive-state landing routing through the real frame helper.

Six bounded root prefixes end at the first landing/scratch boundary. Native
4351C0 executes normally. No helper return or branch is injected. These inputs
do not cover active flying states, landing-helper results, or the whole root.
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

ROOT = Path(__file__).resolve().parents[1]
OWNER, PEER, STACK, RETURN = 0x1000000, 0x1100000, 0x2000000, 0x710000
VTABLE, FRAME_HELPER = 0x6C4BDC, 0x4351C0
BOUNDARIES = {0x5F9310: "landing_check", 0x435110: "scratch_reset"}


def load_audit():
    spec = importlib.util.spec_from_file_location(
        "alice_action214_whole", ROOT / "scripts/audit-alice-fighter-update.py")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def execute(image, code, case, address):
    engine = unicorn.Uc(unicorn.UC_ARCH_X86, unicorn.UC_MODE_32)
    engine.mem_map(0x400000, (len(image) + 4095) // 4096 * 4096)
    engine.mem_write(0x400000, image)
    engine.mem_write(address, code)
    for base in (OWNER, PEER, STACK):
        engine.mem_map(base, 0x10000)
    engine.mem_map(RETURN, 0x1000)
    engine.mem_write(STACK, b"\xa5" * 0x10000)

    def put(offset, fmt, value):
        engine.mem_write(OWNER + offset, struct.pack("<" + fmt, value))

    for offset, fmt, value in (
            (0, "I", VTABLE), (0x104, "b", 1), (0xF8, "f", -2), (0x100, "f", 0.5),
            (0x13C, "h", 214), (0x13E, "h", case["sequence"]), (0x140, "h", 1),
            (0x142, "h", 0), (0x144, "i", 1), (0x14C, "h", 3),
            (0x170, "I", PEER), (0x174, "h", 100), (0x482, "h", 1),
            (0x6C8, "i", case["held"]), (0x736, "h", 20)):
        put(offset, fmt, value)
    engine.mem_protect(PEER, 0x10000, unicorn.UC_PROT_READ)
    engine.mem_write(STACK + 0xFF00, struct.pack("<I", RETURN))
    engine.reg_write(registers.UC_X86_REG_ECX, OWNER)
    engine.reg_write(registers.UC_X86_REG_ESP, STACK + 0xFF00)
    engine.reg_write(registers.UC_X86_REG_FPCW, 0x27F)
    engine.reg_write(registers.UC_X86_REG_FPSW, 0)
    engine.reg_write(registers.UC_X86_REG_FPTAG, 65535)
    result, trace = {}, []

    def observe(uc, location, size, unused):
        if location == FRAME_HELPER:
            trace.append(hex(location))
        if location in BOUNDARIES:
            trace.append(hex(location))
            result.update(boundary=BOUNDARIES[location], helper_trace=trace,
                          receiver_offset=uc.reg_read(registers.UC_X86_REG_ECX) - OWNER,
                          observed_prefix=bytes(uc.mem_read(OWNER, 0x800)).hex(),
                          x87_top=(uc.reg_read(registers.UC_X86_REG_FPSW) >> 11) & 7,
                          x87_tag=uc.reg_read(registers.UC_X86_REG_FPTAG),
                          x87_control=uc.reg_read(registers.UC_X86_REG_FPCW))
            uc.emu_stop()

    engine.hook_add(unicorn.UC_HOOK_CODE, observe)
    engine.emu_start(address, RETURN + 1, count=3000)
    if not result:
        raise ValueError("no reviewed first-helper boundary within the instruction limit")
    if result["helper_trace"].count(hex(FRAME_HELPER)) != 1:
        raise ValueError("real frame helper did not execute exactly once")
    if result["x87_top"] != 0 or result["x87_tag"] != 65535 or result["x87_control"] != 0x27F:
        raise ValueError("x87 environment or live stack changed at boundary")
    return result


def audit(object_path=None):
    whole = load_audit()
    canonical, identity, candidate, target = whole.load_candidate(object_path)
    # The exact PE pin covers both actual helper bodies and the vtable. The
    # selected nonready frame must return normally without calling an asset
    # callback: counter0->1 remains below native duration3.
    if struct.unpack("<I", canonical.target_bytes(VTABLE + 0x28, 4))[0] != whole.ADDRESS:
        raise ValueError("Alice root vtable slot changed")
    image = pefile.PE(str(ROOT / "resources/th105.exe")).get_memory_mapped_image()
    results = []
    for sequence in (0, 5, 6):
        for held in (0, 1):
            case = dict(sequence=sequence, held=held)
            expected, actual = (execute(image, code, case, whole.ADDRESS)
                                for code in (target, candidate))
            if expected["boundary"] != "landing_check" or expected["receiver_offset"] != 0:
                raise ValueError("native inactive-state routing expectation changed")
            actor = bytes.fromhex(expected["observed_prefix"])
            if (struct.unpack_from("<i", actor, 0x144)[0] != 2
                    or struct.unpack_from("<h", actor, 0x142)[0] != 1
                    or struct.unpack_from("<f", actor, 0xF8)[0] != (-2 if sequence == 0 else -2.5)):
                raise ValueError("native frame/gravity expectation changed")
            results.append(dict(input=case, equal=expected == actual,
                                target=expected, candidate=actual))
    return dict(diagnostic_only=True, target_sha256=identity,
                candidate_sha256=hashlib.sha256(candidate).hexdigest(),
                cases=len(results), mismatches=sum(not row["equal"] for row in results),
                scope="Alice214 sequences0/5/6 root prefixes through real nonready frame helper; "
                      "stop before first landing/scratch body. Active states, later helper "
                      "results, private stack layout and real-game reachability are unproved.",
                results=results)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--object", type=Path)
    args = parser.parse_args()
    try:
        report = audit(args.object)
    except (OSError, ValueError, RuntimeError, KeyError, unicorn.UcError) as error:
        print(json.dumps(dict(result="blocked", error=str(error)), indent=2))
        return 1
    print(json.dumps(report, indent=2))
    return 1 if report["mismatches"] else 0


if __name__ == "__main__":
    raise SystemExit(main())
