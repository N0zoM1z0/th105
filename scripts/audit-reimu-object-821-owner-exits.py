#!/usr/bin/env python3
"""Observe 821's owner guards, retirement x87 values and actual root RETs.

The first two target guards share a tail; the third has a private tail.
This finite native/physical-layout diagnostic does not accept root exactness.
"""

from __future__ import annotations

import argparse
from collections import Counter, defaultdict
import hashlib
import importlib.util
import itertools
import json
from pathlib import Path
import struct
import tomllib


ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location(
    "owner_exit_retirement", ROOT / "scripts/audit-reimu-object-retirement-fpu.py"
)
retirement = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(retirement)
native = retirement.native


class ExitProbe(retirement.RetirementProbe):
    def evaluate(self, case):
        self.observed_return = None
        self.entry_heading = None
        result = super().evaluate(case)
        if self.entry_heading != struct.pack("<f", case["heading"]):
            raise ValueError("requested heading input was not applied at root entry")
        return result

    def instruction(self, engine, address, size, unused):
        if address == self.start:
            self.entry_heading = bytes(engine.mem_read(native.OWNER + 0x12C, 4))
        if address in self.root_returns:
            self.observed_return = address
        super().instruction(engine, address, size, unused)


def cases():
    for sequence, action, sequence_owner, frame, heading, control in itertools.product(
        (3, 4),
        (-32768, -1, 0, 529, 530, 531, 532, 32767),
        (-32768, -1, 0, 2, 3, 4, 32767),
        (-32768, -1, 3, 4, 5, 32767),
        (0.0, 45.0, float("nan"), float("inf"), -float("inf")),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=821, seq=sequence, phase=0, counter=1, timer=1,
            owner_action=action, owner_seq=sequence_owner, owner_frame=frame,
            heading=heading, cw=control,
        )


def guard_class(case):
    if case["seq"] == 4:
        return "sequence4_control"
    if case["owner_action"] not in (530, 531):
        return "owner_action"
    if case["owner_seq"] == 3 and case["owner_frame"] >= 4:
        return "owner_frame"
    if case["owner_seq"] >= 4:
        return "owner_sequence"
    return "continuation"


def audit(obj):
    paths = [
        Path(__file__), obj, ROOT / "resources/th105.exe",
        ROOT / "src/characters/ReimuObjectActionStateStaging.cpp",
        ROOT / "src/characters/ReimuObjectActionStateStaging.hpp",
        ROOT / "config/match-units.toml",
        ROOT / "config/giant-action-switches.toml",
        *[ROOT / "scripts" / name for name in (
            "audit-reimu-object-retirement-fpu.py",
            "audit-reimu-object-typed-stores.py",
            "audit-reimu-object-999-tail.py",
            "audit-reimu-object-scalar-actions.py",
            "audit-reimu-object-update-target.py", "compare-function.py",
        )],
    ]
    pins = lambda: {str(p): hashlib.sha256(p.read_bytes()).hexdigest() for p in paths}
    before = pins()
    facts = native.facts.audit()
    code = native.export(obj)
    root = native.m.load_target_mapper().select_root(
        tomllib.loads((ROOT / "config/giant-action-switches.toml").read_text()),
        "reimu-object-vslot28",
    )
    mapping = native.m.build_candidate_map(
        native.m.CoffObject(obj, symbol_base=native.SYMBOL), root
    )
    target_rows = [
        row for lo, hi in native.facts.RANGES
        for row in native.facts.decode(native.c.target_bytes(lo, hi - lo), lo)
    ]
    source_rows = native.facts.decode(code[:mapping["metadata_start"]], native.S)
    image = native.pefile.PE(str(ROOT / "resources/th105.exe")).get_memory_mapped_image()
    probes = (ExitProbe(image), ExitProbe(image, code))
    for probe, rows in zip(probes, (target_rows, source_rows)):
        probe.root_returns = {row.address for row in rows if row.mnemonic == "ret"}
    visits = Counter()
    observed = [defaultdict(set), defaultdict(set)]
    differences = Counter()
    examples = []
    inputs = list(cases())
    logical = lambda rows: [{k: v for k, v in row.items() if k != "pc"} for row in rows]
    target_expected = {
        "owner_action": (0x4980E4, 0x4980F7),
        "owner_frame": (0x4980E4, 0x4980F7),
        "owner_sequence": (0x499CB2, 0x499CC5),
    }
    for case in inputs:
        kind = guard_class(case)
        visits[kind] += 1
        a, ae, ar = probes[0].evaluate(case)
        b, be, br = probes[1].evaluate(case)
        flags = dict(
            output=a != b,
            ordered_write=[v[1:] for v in ae] != [v[1:] for v in be],
            retirement=logical(ar) != logical(br),
        )
        differences.update(k for k, v in flags.items() if v)
        if any(flags.values()) and len(examples) < 12:
            examples.append(dict(case=case, differs=flags, target=ar, source=br))
        if kind in target_expected:
            if len(ar) != 1 or probes[0].observed_return is None:
                raise ValueError("target guard did not perform one retirement and root RET")
            if (ar[0]["pc"], probes[0].observed_return) != target_expected[kind]:
                raise ValueError("target owner guard/retirement/RET identity differs")
            for index, rows in enumerate((ar, br)):
                if len(rows) != 1 or probes[index].observed_return is None:
                    raise ValueError("source guard did not perform one retirement and root RET")
                observed[index][kind].add((rows[0]["pc"], probes[index].observed_return))
    if before != pins():
        raise ValueError("audit inputs changed during execution")
    if any(len(sites) != 1 for side in observed for sites in side.values()):
        raise ValueError("a guard's retirement/RET identity changes across fixtures")
    sides = [{kind: next(iter(sites)) for kind, sites in side.items()} for side in observed]
    if any(set(side) != set(target_expected) for side in sides):
        raise ValueError("missing owner guard coverage")
    sharing_equal = (
        sides[1]["owner_action"] == sides[1]["owner_frame"]
        and sides[1]["owner_sequence"] != sides[1]["owner_action"]
    )
    tails = []
    for index, side in enumerate(sides):
        encoded = {}
        for kind, (write, end) in side.items():
            if end < write:
                raise ValueError("retirement tail is not a forward linear span")
            data = (native.c.target_bytes(write, end - write + 1) if index == 0
                    else code[write - native.S:end - native.S + 1])
            rows = native.facts.decode(data, write)
            if rows[-1].mnemonic != "ret":
                raise ValueError("observed tail does not end at its root RET")
            encoded[kind] = data.hex()
        tails.append(encoded)
    tail_bytes_equal = tails[0] == tails[1]
    accepted = not differences and sharing_equal and tail_bytes_equal
    return dict(
        result="equal_scoped_821_owner_exits" if accepted else "rejected",
        target_sha256=facts["target_sha256"],
        object_sha256=hashlib.sha256(obj.read_bytes()).hexdigest(),
        case_count=len(inputs),
        input_sha256=hashlib.sha256(json.dumps(inputs, sort_keys=True).encode()).hexdigest(),
        output_difference_count=differences["output"],
        event_difference_count=differences["ordered_write"],
        retirement_difference_count=differences["retirement"],
        guard_visits=dict(visits), retirement_and_return_sites=sides,
        guard_sharing_equal=sharing_equal, retirement_tail_bytes_equal=tail_bytes_equal,
        retirement_tail_bytes=tails, examples=examples,
        input_pins=before, pins_unchanged=True, build_provenance_verified=False,
        scope="6720 actual821 sequence3/4 prefixes, ordered writes, logical retirement x87 and physical guard/RET sharing; no arbitrary aliases, unmasked exceptions, TOP/flags, opaque returns or whole-root exactness",
    )


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("object", type=Path)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    report = audit(args.object)
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps({k: report[k] for k in (
        "result", "case_count", "output_difference_count", "event_difference_count",
        "retirement_difference_count", "guard_sharing_equal", "retirement_tail_bytes_equal",
    )}))
    return int(report["result"] != "equal_scoped_821_owner_exits")


if __name__ == "__main__":
    raise SystemExit(main())
