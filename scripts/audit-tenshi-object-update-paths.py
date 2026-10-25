#!/usr/bin/env python3
"""Check Tenshi825/default frame-return consumption with native helper execution.

Eight inputs distinguish a ready/nonready frame and sequence modes0/1 for825
and the default. The one-block animation fixture is readonly; real-game graph
reachability is not asserted. No helper result or control transfer is injected.
This scoped diagnostic does not establish whole-function equivalence or exactness.
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
OWNER, STACK, RESOURCE, RETURN = 0x1000000, 0x2000000, 0x3000000, 0x710000
VECTOR, SLOT, BLOCK, FRAME = (RESOURCE+x for x in (0x300, 0x400, 0x1000, 0x10000))
VTABLE = 0x6C670C
NATIVE_ENTRIES = (0x4351C0, 0x45C1A0, 0x45C220, 0x45C180,
                  0x45C110, 0x436760, 0x40C100, 0x4073C0)


def load_audit():
    spec = importlib.util.spec_from_file_location(
        "tenshi_update_canonical", ROOT/"scripts/audit-tenshi-object-update.py")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def execute(image, code, case, address):
    engine = unicorn.Uc(unicorn.UC_ARCH_X86, unicorn.UC_MODE_32)
    engine.mem_map(0x400000, (len(image)+4095)//4096*4096)
    engine.mem_write(0x400000, image)
    engine.mem_write(address, code)
    for base, size in ((OWNER, 0x10000), (STACK, 0x10000),
                       (RESOURCE, 0x40000), (RETURN, 0x1000)):
        engine.mem_map(base, size)

    def put(location, fmt, *values):
        engine.mem_write(location, struct.pack("<"+fmt, *values))

    put(VECTOR+4, "III", SLOT, SLOT+4, SLOT+4)
    put(BLOCK+4, "II", FRAME, FRAME+0x88)
    put(BLOCK+0x14, "B", case["mode"])
    put(BLOCK+0x18, "II", 0, 0)
    put(FRAME+8, "hhhhhhb", 3, 0, 1, 2, 16, 24, -1)
    for offset, fmt, value in (
            (0, "I", VTABLE), (0x13C, "h", case["action"]), (0x13E, "h", 1),
            (0x140, "h", 0), (0x142, "h", 2 if case["ready"] else 0),
            (0x144, "i", 12), (0x148, "i", 1), (0x14C, "h", 3),
            (0x130, "I", VECTOR), (0x15C, "I", BLOCK), (0x330, "i", 10)):
        put(OWNER+offset, fmt, value)
    engine.mem_protect(RESOURCE, 0x40000, unicorn.UC_PROT_READ)
    put(STACK+0xFF00, "I", RETURN)
    engine.reg_write(registers.UC_X86_REG_ECX, OWNER)
    engine.reg_write(registers.UC_X86_REG_ESP, STACK+0xFF00)
    engine.reg_write(registers.UC_X86_REG_FPCW, 0x27F)
    engine.reg_write(registers.UC_X86_REG_FPSW, 0)
    engine.reg_write(registers.UC_X86_REG_FPTAG, 65535)
    result, calls = {}, []

    def observe(uc, location, size, unused):
        if location in NATIVE_ENTRIES:
            calls.append(hex(location))
        if location == RETURN:
            result.update(actor=bytes(uc.mem_read(OWNER, 0x388)).hex(), calls=calls,
                          stack_delta=uc.reg_read(registers.UC_X86_REG_ESP)-(STACK+0xFF00),
                          top=(uc.reg_read(registers.UC_X86_REG_FPSW)>>11)&7,
                          control=uc.reg_read(registers.UC_X86_REG_FPCW))
            uc.emu_stop()

    engine.hook_add(unicorn.UC_HOOK_CODE, observe)
    engine.emu_start(address, RETURN+1, count=30000)
    if not result:
        raise ValueError("no real RET0 within reviewed instruction limit")
    if result["stack_delta"] != 4 or result["top"] != 0 or result["control"] != 0x27F:
        raise ValueError("native ABI/environment changed")
    return result


def audit(object_path=None):
    whole = load_audit()
    canonical = whole.load_compare()
    identity, target, _, _ = whole.target_facts(canonical)
    for slot, destination in ((0x14, 0x45C220), (0x20, 0x45C1A0), (0x28, whole.START)):
        if struct.unpack("<I", canonical.target_bytes(VTABLE+slot, 4))[0] != destination:
            raise ValueError("reviewed primary vtable cell changed")
    unit = load_manifest()["units"][whole.UNIT]
    function, = unit["functions"]
    if int(function["address"], 0) != whole.START or function["symbol_base"] != whole.SYMBOL:
        raise ValueError("configured root changed")
    targets = canonical.known_targets()
    for binding in function["rel32_targets"]:
        name, value = binding.rsplit("=", 1)
        targets[name] = int(value, 0)
    # Preserve the older825 negative control across the local caller-view change.
    # Both complete forwarding-provider forms have independent exact witnesses.
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
    for action in (825, 799):
        for mode in (0, 1):
            for ready in (False, True):
                case = dict(action=action, mode=mode, ready=ready)
                expected, actual = (execute(image, code, case, whole.START)
                                    for code in (target, candidate))
                actor = bytes.fromhex(expected["actor"])
                lifetime = 9 if action == 825 and mode == 0 and ready else 10
                if struct.unpack_from("<i", actor, 0x330)[0] != lifetime:
                    raise ValueError("native retirement expectation changed")
                if expected["calls"].count("0x4351c0") != 1:
                    raise ValueError("native frame dispatch expectation changed")
                block_wrap = expected["calls"].count("0x45c220")
                if block_wrap != int(mode == 0 and ready):
                    raise ValueError("native frame/block helper path changed")
                results.append(dict(input=case, equal=expected == actual,
                                    target=expected, candidate=actual))
    return dict(diagnostic_only=True, target_sha256=identity,
                candidate_sha256=hashlib.sha256(candidate).hexdigest(),
                cases=len(results), mismatches=sum(not row["equal"] for row in results),
                scope="825/default frame-return consumption; native root/helpers and readonly "
                      "one-block fixture; real-game graph reachability and other actions unproved",
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
