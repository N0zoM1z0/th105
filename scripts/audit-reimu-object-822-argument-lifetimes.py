#!/usr/bin/env python3
"""Observe 822 sequence 4 packet publication and outgoing RNG argument lifetimes.

Uses original seeded RNG and stops at the real four-word object request.
Inactive timer controls execute real returns. This is a finite diagnostic.
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
    "argument822_stores", ROOT / "scripts/audit-reimu-object-typed-stores.py"
)
stores = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(stores)
native = stores.native
tail = native.load("argument822_floating", "scripts/audit-reimu-object-999-tail.py")
SEEDS = (0, 14, 43, 50, 76, 79, 137, 5489, 0xFFFFFFFF)


def logical_floating_state(engine):
    state = tail.floating_state(engine)
    return {key: state[key] for key in ("depth", "values")}


class ArgumentProbe(stores.StoreProbe):
    def in_root(self, pc):
        return (any(lo <= pc < hi for lo, hi in native.facts.RANGES)
                if self.start == native.A else native.S <= pc < native.S + self.size)

    def evaluate(self, case):
        self.timeline, self.pending, self.rolls = [], [], []
        self.fp, self.retirements = [], []
        self.continuation = None
        self.packet = self.entry_sp = None
        result, writes = super().evaluate(case)
        timeline = []
        for event in self.timeline:
            if event[0] == "rng":
                timeline.append((f"rng{event[1]}", event[2]))
            elif self.packet is not None and self.packet <= event[2] < self.packet + 16:
                if event[3] != 4 or (event[2] - self.packet) % 4:
                    raise ValueError("unreviewed packet write width")
                timeline.append((f"packet{(event[2] - self.packet) // 4}", event[1]))
        return result, writes, timeline

    def instruction(self, uc, pc, size, unused):
        if pc == self.start:
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
                self.timeline.append(("rng", index, pc))
                self.fp.append((f"rng{index}", logical_floating_state(uc)))
                if index:
                    offset = 8 if index < 3 else 12
                    if index == 1:
                        variant, pointer, count = struct.unpack("<III", uc.mem_read(sp + offset, 12))
                        facing = None
                    else:
                        facing, variant, pointer, count = struct.unpack("<IIII", uc.mem_read(sp + offset, 16))
                    valid = (variant == 1 and count == 4 and native.STACK <= pointer
                             and pointer + 16 <= native.STACK + 0x10000)
                    self.pending.append(dict(
                        index=index, limit=limit, prepared=valid, facing=facing,
                        payload=bytes(uc.mem_read(pointer, 16)).hex() if valid else None,
                        packet_offset=pointer - self.entry_sp if valid else None,
                        y=bytes(uc.mem_read(sp + 8, 4)).hex() if index == 3 else None,
                    ))
        if pc == native.SPAWN:
            sp = uc.reg_read(native.r.UC_X86_REG_ESP)
            continuation = struct.unpack("<I", uc.mem_read(sp, 4))[0]
            if self.in_root(continuation):
                self.packet = struct.unpack("<I", uc.mem_read(sp + 24, 4))[0]
                self.fp.append(("world", logical_floating_state(uc)))
        super().instruction(uc, pc, size, unused)

    def write(self, uc, access, address, size, value, unused):
        pc = uc.reg_read(native.r.UC_X86_REG_EIP)
        if self.in_root(pc):
            if native.STACK <= address and address + size <= native.STACK + 0x10000:
                self.timeline.append(("write", pc, address, size))
            if address == native.OWNER + 0x330 and size == 4:
                self.retirements.append(dict(value=value & 0xFFFFFFFF, **logical_floating_state(uc)))
        super().write(uc, access, address, size, value, unused)


def cases():
    for seed, control, facing, amplitude, coordinate in itertools.product(
        SEEDS, (0x27F, 0x37F), (-1, 1), (0.0, 3.5, -0.25, float("nan")),
        ((0.0, 0.0), (640.0, 100.0), (1023.9999389648438, 128.001), (float("nan"), 100.0)),
    ):
        yield dict(action=822, seq=4, phase=0, counter=1, timer=0, seed=seed,
                   cw=control, facing=facing, amplitude=amplitude,
                   x=coordinate[0], y=coordinate[1])
    for control, facing, amplitude, channel in itertools.product(
        (0x27F, 0x37F), (-1, 1), (0.0, 0.1, -0.1, float("nan")), (14, 15, 200),
    ):
        yield dict(action=822, seq=4, phase=0, counter=1, timer=1, seed=0,
                   cw=control, facing=facing, amplitude=amplitude,
                   channel=channel, channel2=channel)


def audit(obj):
    paths = [Path(__file__), obj, ROOT / "resources/th105.exe",
             ROOT / "src/characters/ReimuObjectActionStateStaging.cpp",
             ROOT / "src/characters/ReimuObjectActionStateStaging.hpp",
             ROOT / "config/match-units.toml", ROOT / "config/giant-action-switches.toml",
             *[ROOT / "scripts" / name for name in (
                 "audit-reimu-object-typed-stores.py", "audit-reimu-object-scalar-actions.py",
                 "audit-reimu-object-update-target.py", "audit-reimu-object-entry-calls.py",
                 "audit-common-fighter-animation-paths.py", "audit-reimu-object-999-tail.py",
                 "audit-reimu-object-world-sharing.py", "compare-function.py")]]
    pins = lambda: {str(p): hashlib.sha256(p.read_bytes()).hexdigest() for p in paths}
    before = pins()
    facts = native.facts.audit()
    code = native.export(obj)
    image = bytes(native.pefile.PE(str(ROOT / "resources/th105.exe")).get_memory_mapped_image())
    seeds = native.seed_fixtures(image, SEEDS)
    probes = (ArgumentProbe(image, seeds=seeds), ArgumentProbe(image, code, seeds=seeds))
    expected = ["packet0", "packet1", "rng0", "packet2", "packet3", "rng1", "rng2", "rng3"]
    inputs = list(cases())
    differences, endpoints, boundaries = Counter(), Counter(), set()
    sites, packet_offsets = [set(), set()], [set(), set()]
    examples = []
    for case in inputs:
        a, aw, at = probes[0].evaluate(case)
        b, bw, bt = probes[1].evaluate(case)
        active = case["timer"] == 0
        if active:
            if a["endpoint"] is None or a["endpoint"]["kind"] != "spawn":
                raise ValueError("target did not reach actual unparented request")
            rolls = probes[0].rolls
            if [r[0] for r in rolls] != [100, 100, 200, 200] or [e[0] for e in at] != expected:
                raise ValueError(("target822 evaluation order differs", rolls, at))
            payload = struct.pack("<ffff", 0.0, 0.0, 5.0 if rolls[0][1] < 50 else 6.0, 0.0).hex()
            facing = (1 - 2 * (rolls[1][1] > 50)) & 0xFF
            args = a["endpoint"]["arguments"]
            if args[3] != facing or args[5] != payload or args[6] != 4:
                raise ValueError("target packet/direction policy differs")
            if len(probes[0].pending) != 3 or not all(p["prepared"] and p["payload"] == payload for p in probes[0].pending):
                raise ValueError("target arguments were not ready before RNG")
            if probes[0].pending[1]["facing"] != facing or probes[0].pending[2]["y"] != struct.pack("<I", args[2]).hex():
                raise ValueError("target pending facing/Y argument differs")
            boundaries.update((i, rolls[i][1]) for i in (0, 1) if rolls[i][1] in (49, 50, 51))
            endpoints["spawn"] += 1
            for side, probe, timeline in ((0, probes[0], at), (1, probes[1], bt)):
                sites[side].add(tuple(timeline))
                if probe.packet is not None:
                    packet_offsets[side].add(probe.packet - probe.entry_sp)
        else:
            if a["endpoint"] != {"kind": "ret"} or probes[0].rolls:
                raise ValueError("inactive target did not execute real RET without RNG")
            endpoints["ret"] += 1
        flags = dict(
            output=a != b, ordered_write=[v[1:] for v in aw] != [v[1:] for v in bw],
            packet_order=[e[0] for e in at] != [e[0] for e in bt],
            pending_arguments=probes[0].pending != probes[1].pending,
            rng=probes[0].rolls != probes[1].rolls,
            floating=probes[0].fp != probes[1].fp,
            retirement=probes[0].retirements != probes[1].retirements,
        )
        differences.update(k for k, value in flags.items() if value)
        if any(flags.values()) and len(examples) < 10:
            examples.append(dict(case=case, differences=flags, target_timeline=at, source_timeline=bt,
                                 target_pending=probes[0].pending, source_pending=probes[1].pending))
    if boundaries != set(itertools.product((0, 1), (49, 50, 51))):
        raise ValueError("actual RNG49/50/51 boundary coverage is missing")
    if before != pins():
        raise ValueError("audit inputs changed during execution")
    return dict(result="equal_scoped_822_argument_lifetimes" if not differences else "rejected",
                target_sha256=facts["target_sha256"], object_sha256=hashlib.sha256(obj.read_bytes()).hexdigest(),
                case_count=len(inputs), input_sha256=hashlib.sha256(json.dumps(inputs, sort_keys=True).encode()).hexdigest(),
                differences={name: differences[name] for name in (
                    "output", "ordered_write", "packet_order", "pending_arguments", "rng", "floating", "retirement")},
                endpoints=dict(endpoints), rng_boundary_coverage=sorted(boundaries),
                packet_offsets_from_entry_sp=[sorted(s) for s in packet_offsets],
                observed_sites=[sorted(s) for s in sites], examples=examples,
                input_pins=before, pins_unchanged=True, build_provenance_verified=False,
                scope="576 actual822 sequence4 spawn prefixes and48 real inactive RETs; original RNG with both49/50/51 boundaries, packet publication/pending stack slots/logical x87; excludes TOP/flags, unmasked exceptions, opaque returns, arbitrary aliases and whole-root exactness")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("object", type=Path)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    report = audit(args.object)
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps({key: report[key] for key in ("result", "case_count", "differences", "endpoints")}))
    return int(report["result"] != "equal_scoped_822_argument_lifetimes")


if __name__ == "__main__":
    raise SystemExit(main())
