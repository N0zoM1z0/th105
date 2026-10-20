#!/usr/bin/env python3
"""Observe817's parameter-pointer reads around two real RNG calls.

Checks native read/call/store order as well as outputs and ordered writes.
Opaque calls remain entry stops; this finite audit does not accept root exactness.
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

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location(
    "turn_lifetime_stores", ROOT / "scripts/audit-reimu-object-typed-stores.py"
)
stores = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(stores)
native = stores.native


class TurnProbe(stores.StoreProbe):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.uc.hook_add(native.unicorn.UC_HOOK_MEM_READ, self.read,
                         begin=native.OWNER + 0x340, end=native.OWNER + 0x343)

    def evaluate(self, case):
        self.lifetime = []
        self.entry_parameters = None
        result, writes = super().evaluate(case)
        if self.entry_parameters != native.entry.PARAMETERS:
            raise ValueError("fixture parameter pointer was not applied")
        return result, writes, self.lifetime

    def in_root(self, pc):
        return (any(lo <= pc < hi for lo, hi in native.facts.RANGES)
                if self.start == native.A else native.S <= pc < native.S + self.size)

    def read(self, uc, access, address, size, value, unused):
        pc = uc.reg_read(native.r.UC_X86_REG_EIP)
        if self.in_root(pc) and address == native.OWNER + 0x340 and size == 4:
            self.lifetime.append(("pointer_read", pc))

    def instruction(self, uc, pc, size, unused):
        if pc == self.start:
            self.entry_parameters = struct.unpack("<I", uc.mem_read(native.OWNER + 0x340, 4))[0]
        if pc == 0x4067D0:
            sp = uc.reg_read(native.r.UC_X86_REG_ESP)
            continuation, limit = struct.unpack("<II", uc.mem_read(sp, 8))
            if self.in_root(continuation):
                self.lifetime.append((f"rng{limit}", pc))
        super().instruction(uc, pc, size, unused)

    def write(self, uc, access, address, size, value, unused):
        pc = uc.reg_read(native.r.UC_X86_REG_EIP)
        if self.in_root(pc) and size == 4:
            if address == native.entry.PARAMETERS:
                self.lifetime.append(("turn_store", pc))
            elif address == native.entry.PARAMETERS + 4:
                self.lifetime.append(("speed_store", pc))
        super().write(uc, access, address, size, value, unused)


def cases():
    for amplitude, seed, control, facing, timer in itertools.product(
        (4.999999523162842, 5.0, 5.5, 127.9, 128.0, 255.0, 256.0, float("nan")),
        (0, 5489, 0xFFFFFFFF, 79, 137), (0x27F, 0x37F), (-1, 1), (0, 2),
    ):
        yield dict(action=817, seq=3, phase=0, counter=1, timer=timer,
                   amplitude=amplitude, seed=seed, cw=control, facing=facing)


def audit(obj):
    paths = [Path(__file__), obj, ROOT / "resources/th105.exe",
             ROOT / "src/characters/ReimuObjectActionStateStaging.cpp",
             ROOT / "src/characters/ReimuObjectActionStateStaging.hpp",
             ROOT / "config/match-units.toml", ROOT / "config/giant-action-switches.toml",
             *[ROOT / "scripts" / name for name in (
                 "audit-reimu-object-typed-stores.py", "audit-reimu-object-scalar-actions.py",
                 "audit-reimu-object-update-target.py", "audit-reimu-object-entry-calls.py",
                 "audit-common-fighter-animation-paths.py", "iku_native_math.py",
                 "compare-function.py")]]
    pins = lambda: {str(p): hashlib.sha256(p.read_bytes()).hexdigest() for p in paths}
    before = pins()
    facts = native.facts.audit()
    code = native.export(obj)
    image = bytearray(native.pefile.PE(str(ROOT / "resources/th105.exe")).get_memory_mapped_image())
    math = native.load("turn_lifetime_math", "scripts/iku_native_math.py")
    table, lookup_receipt = math.lookup_fixture(native.c)
    image[0x2FE8B0:0x2FE8B0 + len(table)] = table
    image = bytes(image)
    seeds = native.seed_fixtures(image, (0, 5489, 0xFFFFFFFF, 79, 137))
    probes = (TurnProbe(image, seeds=seeds), TurnProbe(image, code, seeds=seeds))
    expected = ["pointer_read", "rng360", "turn_store", "rng60", "pointer_read", "speed_store"]
    inputs = list(cases())
    differences, endpoints = Counter(), Counter()
    sites = [set(), set()]
    examples = []
    for case in inputs:
        a, aw, at = probes[0].evaluate(case)
        b, bw, bt = probes[1].evaluate(case)
        if [x[0] for x in at] != expected:
            raise ValueError(("target pointer/RNG lifetime differs", at))
        sites[0].add(tuple(at)); sites[1].add(tuple(bt))
        flags = dict(output=a != b, ordered_write=[x[1:] for x in aw] != [x[1:] for x in bw],
                     pointer_lifetime=[x[0] for x in bt] != expected)
        differences.update(k for k, value in flags.items() if value)
        endpoints[a["endpoint"]["kind"] if a["endpoint"] else "ret"] += 1
        if any(flags.values()) and len(examples) < 8:
            examples.append(dict(case=case, differences=flags, target=at, source=bt))
    if before != pins():
        raise ValueError("audit inputs changed during execution")
    return dict(result="equal_scoped_817_turn_lifetime" if not differences else "rejected",
                target_sha256=facts["target_sha256"], object_sha256=hashlib.sha256(obj.read_bytes()).hexdigest(),
                case_count=len(inputs), input_sha256=hashlib.sha256(json.dumps(inputs, sort_keys=True).encode()).hexdigest(),
                output_difference_count=differences["output"], event_difference_count=differences["ordered_write"],
                pointer_lifetime_difference_count=differences["pointer_lifetime"], expected_lifetime=expected,
                observed_sites=[sorted(side) for side in sites], endpoints=dict(endpoints), examples=examples,
                input_pins=before, pins_unchanged=True, lookup_fixture=lookup_receipt,
                build_provenance_verified=False,
                scope="320 actual817 sequence3 prefixes, real seeded RNG, read/call/store order and ordered writes; no opaque returns, arbitrary aliases, original TU or whole-root exactness")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("object", type=Path)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    report = audit(args.object)
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps({key: report[key] for key in (
        "result", "case_count", "output_difference_count", "event_difference_count",
        "pointer_lifetime_difference_count", "endpoints")}))
    return int(report["result"] != "equal_scoped_817_turn_lifetime")


if __name__ == "__main__":
    raise SystemExit(main())
