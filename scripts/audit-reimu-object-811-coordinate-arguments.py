#!/usr/bin/env python3
"""Observe 811's actual outgoing arguments before its two coordinate RNG calls.

Original RNG and initialized lookup helpers execute. The actual unparented
request is an opaque entry stop; finite prefix equality is not root exactness.
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
    "coordinate811_stores", ROOT / "scripts/audit-reimu-object-typed-stores.py"
)
stores = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(stores)
native = stores.native
tail = native.load("coordinate811_floating", "scripts/audit-reimu-object-999-tail.py")
SEEDS = (0, 5489, 0xFFFFFFFF, 79, 137)


def floating_state(engine):
    state = tail.floating_state(engine)
    return {key: state[key] for key in ("depth", "values")}


class ArgumentProbe(stores.StoreProbe):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.uc.hook_add(native.unicorn.UC_HOOK_MEM_READ, self.read,
                         begin=native.OWNER + 0x104, end=native.OWNER + 0x104)

    def in_root(self, pc):
        return (any(lo <= pc < hi for lo, hi in native.facts.RANGES)
                if self.start == native.A else native.S <= pc < native.S + self.size)

    def evaluate(self, case):
        self.order, self.pending, self.rolls, self.fp = [], [], [], []
        self.continuation = self.entry_sp = self.entry_facing = None
        self.expected_facing = case["facing"] & 0xFF
        result, writes = super().evaluate(case)
        if self.entry_facing != self.expected_facing:
            raise ValueError("fixture facing was not applied")
        return result, writes

    def read(self, uc, access, address, size, value, unused):
        pc = uc.reg_read(native.r.UC_X86_REG_EIP)
        if self.in_root(pc) and address == native.OWNER + 0x104 and size == 1:
            self.order.append(("facing", pc))

    def instruction(self, uc, pc, size, unused):
        if pc == self.start:
            self.entry_facing = uc.mem_read(native.OWNER + 0x104, 1)[0]
            self.entry_sp = uc.reg_read(native.r.UC_X86_REG_ESP)
        if self.continuation is not None and pc == self.continuation[0]:
            self.rolls.append((self.continuation[1], uc.reg_read(native.r.UC_X86_REG_EAX)))
            self.continuation = None
        if pc == 0x4067D0:
            sp = uc.reg_read(native.r.UC_X86_REG_ESP)
            continuation, limit = struct.unpack("<II", uc.mem_read(sp, 8))
            if self.in_root(continuation):
                index = len(self.rolls)
                self.continuation = (continuation, limit)
                self.order.append((f"rng{limit}", pc))
                self.fp.append((f"rng{index}", floating_state(uc)))
                offset = 8 if index == 0 else 12
                facing, variant, pointer, count = struct.unpack("<IIII", uc.mem_read(sp + offset, 16))
                prepared = (index in (0, 1) and facing == self.expected_facing
                            and variant == 1 and count == 3 and native.STACK <= pointer
                            and pointer + 12 <= native.STACK + 0x10000)
                self.pending.append(dict(
                    index=index, limit=limit, prepared=prepared,
                    payload=bytes(uc.mem_read(pointer, 12)).hex() if prepared else None,
                    packet_offset=pointer - self.entry_sp if prepared else None,
                    y=bytes(uc.mem_read(sp + 8, 4)).hex() if index == 1 else None,
                ))
        if pc == native.SPAWN:
            sp = uc.reg_read(native.r.UC_X86_REG_ESP)
            continuation = struct.unpack("<I", uc.mem_read(sp, 4))[0]
            if self.in_root(continuation):
                self.fp.append(("world", floating_state(uc)))
        super().instruction(uc, pc, size, unused)


def cases():
    for counter, facing, seed, control, coordinate in itertools.product(
        (-8, -4, 4, 8, 12, 16, 60, 64), (-1, 1), SEEDS, (0x27F, 0x37F),
        ((0.0, 0.0), (640.0, 100.0), (1023.9999389648438, 128.001), (float("nan"), 100.0)),
    ):
        yield dict(action=811, seq=0, phase=0, index=2, counter=counter, timer=1,
                   facing=facing, seed=seed, cw=control, x=coordinate[0], y=coordinate[1])


def audit(obj):
    paths = [Path(__file__), obj, ROOT / "resources/th105.exe",
             ROOT / "src/characters/ReimuObjectActionStateStaging.cpp",
             ROOT / "src/characters/ReimuObjectActionStateStaging.hpp",
             ROOT / "config/match-units.toml", ROOT / "config/giant-action-switches.toml",
             *[ROOT / "scripts" / name for name in (
                 "audit-reimu-object-typed-stores.py", "audit-reimu-object-scalar-actions.py",
                 "audit-reimu-object-update-target.py", "audit-reimu-object-entry-calls.py",
                 "audit-common-fighter-animation-paths.py", "audit-reimu-object-999-tail.py",
                 "iku_native_math.py", "compare-function.py")]]
    pins = lambda: {str(p): hashlib.sha256(p.read_bytes()).hexdigest() for p in paths}
    before = pins()
    facts = native.facts.audit()
    code = native.export(obj)
    image = bytearray(native.pefile.PE(str(ROOT / "resources/th105.exe")).get_memory_mapped_image())
    math = native.load("coordinate811_math", "scripts/iku_native_math.py")
    table, lookup_receipt = math.lookup_fixture(native.c)
    image[0x2FE8B0:0x2FE8B0 + len(table)] = table
    image = bytes(image)
    seeds = native.seed_fixtures(image, SEEDS)
    probes = (ArgumentProbe(image, seeds=seeds), ArgumentProbe(image, code, seeds=seeds))
    expected = ["facing", "rng32", "rng32"]
    inputs = list(cases())
    differences, endpoints = Counter(), Counter()
    sites, packet_offsets = [set(), set()], [set(), set()]
    examples = []
    for case in inputs:
        a, aw = probes[0].evaluate(case)
        b, bw = probes[1].evaluate(case)
        endpoint = a["endpoint"]
        if endpoint is None or endpoint["kind"] != "spawn" or endpoint["arguments"][0] != 811:
            raise ValueError(("target did not reach actual 811 request", case))
        target = probes[0]
        if [e[0] for e in target.order] != expected or [r[0] for r in target.rolls] != [32, 32]:
            raise ValueError(("target coordinate order differs", target.order, target.rolls))
        payload, y = endpoint["arguments"][5], struct.pack("<I", endpoint["arguments"][2]).hex()
        if (len(target.pending) != 2 or not all(p["prepared"] and p["payload"] == payload for p in target.pending)
                or target.pending[1]["y"] != y):
            raise ValueError("target pending arguments differ from actual request")
        flags = dict(
            output=a != b, ordered_write=[v[1:] for v in aw] != [v[1:] for v in bw],
            facing_order=[e[0] for e in probes[1].order] != expected,
            pending_arguments=target.pending != probes[1].pending,
            rng=target.rolls != probes[1].rolls, floating=target.fp != probes[1].fp,
        )
        differences.update(k for k, value in flags.items() if value)
        endpoints[endpoint["kind"]] += 1
        for side, probe in enumerate(probes):
            sites[side].add(tuple(probe.order))
            packet_offsets[side].update(p["packet_offset"] for p in probe.pending if p["prepared"])
        if any(flags.values()) and len(examples) < 8:
            examples.append(dict(case=case, differences=flags,
                                 target_order=target.order, source_order=probes[1].order,
                                 target_pending=target.pending, source_pending=probes[1].pending))
    if before != pins():
        raise ValueError("audit inputs changed during execution")
    return dict(result="equal_scoped_811_coordinate_arguments" if not differences else "rejected",
                target_sha256=facts["target_sha256"], object_sha256=hashlib.sha256(obj.read_bytes()).hexdigest(),
                case_count=len(inputs), input_sha256=hashlib.sha256(json.dumps(inputs, sort_keys=True).encode()).hexdigest(),
                differences={k: differences[k] for k in ("output", "ordered_write", "facing_order", "pending_arguments", "rng", "floating")},
                endpoints=dict(endpoints), expected_order=expected, observed_sites=[sorted(s) for s in sites],
                packet_offsets_from_entry_sp=[sorted(s) for s in packet_offsets],
                lookup_initialization=lookup_receipt, examples=examples,
                input_pins=before, pins_unchanged=True, build_provenance_verified=False,
                scope="640 actual811 sequence0 first unparented-request prefixes; original lookup initialization and RNG, facing/pending arguments and logical x87; excludes TOP/exception flags, opaque returns, arbitrary aliases and whole-root exactness")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("object", type=Path)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    report = audit(args.object)
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps({k: report[k] for k in ("result", "case_count", "differences", "endpoints")}))
    return int(report["result"] != "equal_scoped_811_coordinate_arguments")


if __name__ == "__main__":
    raise SystemExit(main())
