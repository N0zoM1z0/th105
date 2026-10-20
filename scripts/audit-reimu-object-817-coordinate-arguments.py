#!/usr/bin/env python3
"""Observe817's facing and outgoing arguments before coordinate RNG calls.

Original RNG executes; the owned-object request remains an opaque entry stop.
The finite prefix and stack-argument checks do not accept whole-root exactness.
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
    "coordinate_argument_stores", ROOT / "scripts/audit-reimu-object-typed-stores.py"
)
stores = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(stores)
native = stores.native


class ArgumentProbe(stores.StoreProbe):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.uc.hook_add(native.unicorn.UC_HOOK_MEM_READ, self.read,
                         begin=native.OWNER + 0x104, end=native.OWNER + 0x104)

    def in_root(self, pc):
        return (any(lo <= pc < hi for lo, hi in native.facts.RANGES)
                if self.start == native.A else native.S <= pc < native.S + self.size)

    def evaluate(self, case):
        self.order = []
        self.pending = []
        self.entry_facing = None
        self.entry_sp = None
        self.expected_facing = case["facing"] & 0xFF
        output, writes = super().evaluate(case)
        if self.entry_facing != self.expected_facing:
            raise ValueError("fixture facing was not applied")
        return output, writes, self.order, self.pending

    def read(self, uc, access, address, size, value, unused):
        pc = uc.reg_read(native.r.UC_X86_REG_EIP)
        if self.in_root(pc) and address == native.OWNER + 0x104 and size == 1:
            self.order.append(("facing", pc))

    def instruction(self, uc, pc, size, unused):
        if pc == self.start:
            self.entry_facing = uc.mem_read(native.OWNER + 0x104, 1)[0]
            self.entry_sp = uc.reg_read(native.r.UC_X86_REG_ESP)
        if pc == 0x4067D0:
            sp = uc.reg_read(native.r.UC_X86_REG_ESP)
            continuation, limit = struct.unpack("<II", uc.mem_read(sp, 8))
            if self.in_root(continuation):
                self.order.append((f"rng{limit}", pc))
                if limit in (100, 200):
                    # At rng200 the actual Y argument already precedes facing.
                    offset = 8 if limit == 100 else 12
                    facing, variant, packet, count = struct.unpack(
                        "<IIII", uc.mem_read(sp + offset, 16))
                    prepared = (facing == self.expected_facing and variant == 1
                                and count == 3 and native.STACK <= packet
                                and packet + 12 <= native.STACK + 0x10000)
                    self.pending.append(dict(
                        limit=limit, prepared=prepared,
                        payload=bytes(uc.mem_read(packet, 12)).hex() if prepared else None,
                        y=None if limit == 100 else bytes(uc.mem_read(sp + 8, 4)).hex(),
                        packet_offset=packet - self.entry_sp if prepared else None,
                    ))
        super().instruction(uc, pc, size, unused)


def cases():
    for sequence, counter, facing, seed, control, coordinate in itertools.product(
        (0, 9), (30, 32, 34, 60), (-1, 1),
        (0, 5489, 0xFFFFFFFF, 79, 137), (0x27F, 0x37F),
        ((0.0, 0.0), (640.0, 100.0), (1023.9999389648438, 128.001), (float("nan"), 100.0)),
    ):
        yield dict(action=817, seq=sequence, counter=counter, phase=0,
                   facing=facing, seed=seed, cw=control, x=coordinate[0], y=coordinate[1],
                   target_x=2000.0, target_y=100.0, vx=0.0)


def audit(obj):
    paths = [Path(__file__), obj, ROOT / "resources/th105.exe",
             ROOT / "src/characters/ReimuObjectActionStateStaging.cpp",
             ROOT / "src/characters/ReimuObjectActionStateStaging.hpp",
             ROOT / "config/match-units.toml", ROOT / "config/giant-action-switches.toml",
             *[ROOT / "scripts" / name for name in (
                 "audit-reimu-object-typed-stores.py", "audit-reimu-object-scalar-actions.py",
                 "audit-reimu-object-update-target.py", "audit-reimu-object-entry-calls.py",
                 "audit-common-fighter-animation-paths.py", "compare-function.py")]]
    pins = lambda: {str(p): hashlib.sha256(p.read_bytes()).hexdigest() for p in paths}
    before = pins()
    facts = native.facts.audit()
    code = native.export(obj)
    image = bytes(native.pefile.PE(str(ROOT / "resources/th105.exe")).get_memory_mapped_image())
    seeds = native.seed_fixtures(image, (0, 5489, 0xFFFFFFFF, 79, 137))
    probes = (ArgumentProbe(image, seeds=seeds), ArgumentProbe(image, code, seeds=seeds))
    expected = ["rng270", "rng40", "facing", "rng100", "rng200"]
    inputs = list(cases())
    differences, endpoints = Counter(), Counter()
    orders, packets = [set(), set()], [set(), set()]
    examples = []
    for case in inputs:
        a, aw, ao, ap = probes[0].evaluate(case)
        b, bw, bo, bp = probes[1].evaluate(case)
        endpoint = a["endpoint"]
        if endpoint is None or endpoint["kind"] != native.BOUNDARIES[0x465190][0]:
            raise ValueError(("target did not reach owned-world entry", case))
        if [x[0] for x in ao] != expected or [x["limit"] for x in ap] != [100, 200]:
            raise ValueError(("target coordinate evaluation order differs", ao))
        payload, y = endpoint["arguments"][5], struct.pack("<I", endpoint["arguments"][2]).hex()
        if not all(x["prepared"] and x["payload"] == payload for x in ap) or ap[1]["y"] != y:
            raise ValueError("target pending arguments differ from its real request")
        flags = dict(output=a != b, ordered_write=[x[1:] for x in aw] != [x[1:] for x in bw],
                     facing_order=[x[0] for x in bo] != expected, pending_arguments=ap != bp)
        differences.update(k for k, value in flags.items() if value)
        endpoints[endpoint["kind"]] += 1
        for side, order, pending in ((0, ao, ap), (1, bo, bp)):
            orders[side].add(tuple(order))
            packets[side].update(x["packet_offset"] for x in pending if x["prepared"])
        if any(flags.values()) and len(examples) < 8:
            examples.append(dict(case=case, differences=flags, target=ao, source=bo,
                                 target_pending=ap, source_pending=bp))
    if before != pins():
        raise ValueError("audit inputs changed during execution")
    return dict(result="equal_scoped_817_coordinate_arguments" if not differences else "rejected",
                target_sha256=facts["target_sha256"], object_sha256=hashlib.sha256(obj.read_bytes()).hexdigest(),
                case_count=len(inputs), input_sha256=hashlib.sha256(json.dumps(inputs, sort_keys=True).encode()).hexdigest(),
                output_difference_count=differences["output"], event_difference_count=differences["ordered_write"],
                facing_order_difference_count=differences["facing_order"],
                pending_argument_difference_count=differences["pending_arguments"], expected_order=expected,
                observed_sites=[sorted(side) for side in orders],
                packet_offsets_from_entry_sp=[sorted(side) for side in packets],
                endpoints=dict(endpoints), examples=examples, input_pins=before, pins_unchanged=True,
                build_provenance_verified=False,
                scope="640 actual817 sequence0/9 first owned-world prefixes and real coordinate RNG calls; pending scalars, packet contents and actual packet offsets from root-entry SP; no opaque return, arbitrary aliases, original TU or whole-root exactness")


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
        "facing_order_difference_count", "pending_argument_difference_count", "endpoints")}))
    return int(report["result"] != "equal_scoped_817_coordinate_arguments")


if __name__ == "__main__":
    raise SystemExit(main())
