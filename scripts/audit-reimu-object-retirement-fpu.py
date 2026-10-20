#!/usr/bin/env python3
"""Compare live x87 values at root496540's state330 writes.

This finite diagnostic distinguishes decrement-before-pop from pop-before-
decrement even when final memory and helper-entry states agree. It executes
original helpers and stops at opaque entries, without fabricated returns.
It does not establish original source spelling or full-root exactness.
"""

from __future__ import annotations

import argparse
from collections import Counter
import hashlib
import importlib.util
import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location(
    "retirement_stores", ROOT / "scripts/audit-reimu-object-typed-stores.py"
)
stores = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(stores)
native = stores.native
SPEC = importlib.util.spec_from_file_location(
    "retirement_tail", ROOT / "scripts/audit-reimu-object-999-tail.py"
)
tail = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(tail)


class RetirementProbe(stores.StoreProbe):
    def evaluate(self, case):
        self.retirements = []
        result, events = super().evaluate(case)
        return result, events, self.retirements

    def write(self, engine, access, address, size, value, unused):
        pc = engine.reg_read(native.r.UC_X86_REG_EIP)
        in_root = (
            any(lo <= pc < hi for lo, hi in native.facts.RANGES)
            if self.start == native.A
            else native.S <= pc < native.S + self.size
        )
        if in_root and address == native.OWNER + 0x330 and size == 4:
            state = tail.floating_state(engine)
            self.retirements.append({
                "pc": pc, "value": value & 0xFFFFFFFF,
                "depth": state["depth"], "values": state["values"],
            })
        super().write(engine, access, address, size, value, unused)


def audit(obj, stride, cohorts):
    paths = [
        Path(__file__), obj, ROOT / "resources/th105.exe",
        ROOT / "src/characters/ReimuObjectActionStateStaging.cpp",
        ROOT / "src/characters/ReimuObjectActionStateStaging.hpp",
        ROOT / "config/match-units.toml",
        ROOT / "config/giant-action-switches.toml",
        *[ROOT / "scripts" / name for name in (
            "audit-reimu-object-typed-stores.py",
            "audit-reimu-object-999-tail.py",
            "audit-reimu-object-scalar-actions.py",
            "audit-reimu-object-update-target.py",
            "audit-reimu-object-entry-calls.py",
            "audit-common-fighter-animation-paths.py",
            "iku_native_math.py", "compare-function.py",
        )],
    ]

    def pins():
        return {str(p): hashlib.sha256(p.read_bytes()).hexdigest() for p in paths}

    before = pins()
    code = native.export(obj)  # Attests target, boundaries and relocation replay.
    pe = native.pefile.PE(str(ROOT / "resources/th105.exe"))
    image = bytearray(pe.get_memory_mapped_image())
    math = native.load("retirement_math", "scripts/iku_native_math.py")
    table, lookup_receipt = math.lookup_fixture(native.c)
    image[0x2FE8B0:0x2FE8B0 + len(table)] = table
    image = bytes(image)
    seeds = native.seed_fixtures(image, (0, 5489, 0xFFFFFFFF, 79, 137))
    surfaces, surface_receipt = native.surface_fixtures(image)
    target = RetirementProbe(image, seeds=seeds, surfaces=surfaces)
    source = RetirementProbe(image, code, seeds=seeds, surfaces=surfaces)
    generators = (
        native.cases, native.projectile_cases, native.sequence_cases,
        native.late_projectile_cases, native.owner_projectile_cases,
        native.follow_projectile_cases, native.sibling_projectile_cases,
        native.orbit_projectile_cases, native.upper_projectile_cases,
        native.actions_903_905_cases, native.final_action_cases,
    )
    cases = [case for generate in generators for case in generate()]
    available = {c.get("cohort", "scalar") for c in cases}
    if set(cohorts) - available:
        raise ValueError("unknown cohort")
    if cohorts:
        cases = [c for c in cases if c.get("cohort", "scalar") in cohorts]
    cases = cases[::stride]
    output_count = event_count = retirement_count = 0
    actions, visits = Counter(), Counter()
    examples = []
    for case in cases:
        a, ae, ar = target.evaluate(case)
        b, be, br = source.evaluate(case)
        output_count += a != b
        # Instruction PCs are evidence locations, not comparison operands.
        event_count += [e[1:] for e in ae] != [e[1:] for e in be]
        logical = lambda events: [
            {k: v for k, v in event.items() if k != "pc"} for event in events
        ]
        differs = logical(ar) != logical(br)
        retirement_count += differs
        visits.update(r["pc"] for r in ar)
        if differs:
            actions[case["action"]] += 1
            if len(examples) < 20:
                examples.append({"case": case, "target": ar, "source": br})
    if before != pins():
        raise ValueError("audit inputs changed during execution")
    return {
        "result": "equal_scoped_retirement_states"
        if output_count == event_count == retirement_count == 0
        else "different_scoped_retirement_states",
        "case_count": len(cases), "stride": stride, "cohorts": cohorts,
        "input_sha256": hashlib.sha256(
            json.dumps(cases, sort_keys=True).encode()
        ).hexdigest(),
        "output_difference_count": output_count,
        "event_difference_count": event_count,
        "retirement_difference_count": retirement_count,
        "retirement_difference_actions": dict(actions),
        "target_retirement_visits": {hex(k): v for k, v in sorted(visits.items())},
        "examples": examples, "input_pins": before, "pins_unchanged": True,
        "build_provenance_verified": False,
        "lookup_fixture": lookup_receipt, "surface_fixture": surface_receipt,
        "limitations": [
            "Finite prefixes; opaque calls stop without synthesized returns.",
            "Logical live x87 values/tags at the write, excluding physical TOP and flags.",
            "Does not establish source spelling, original TU, or whole-root exactness.",
        ],
    }


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("object", type=Path)
    parser.add_argument("--output", type=Path, required=True)
    parser.add_argument("--stride", type=int, default=37)
    parser.add_argument("--cohort", action="append", default=[])
    args = parser.parse_args()
    if args.stride < 1:
        parser.error("--stride must be positive")
    report = audit(args.object, args.stride, args.cohort)
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps({k: report[k] for k in (
        "result", "case_count", "output_difference_count", "event_difference_count",
        "retirement_difference_count",
    )}))
    return int(report["result"] != "equal_scoped_retirement_states")


if __name__ == "__main__":
    raise SystemExit(main())
