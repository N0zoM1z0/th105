#!/usr/bin/env python3
"""Compare root496540's live x87 values at direct helper entry.

Uses original helpers and admitted native prefixes; opaque calls remain entry
stops. Logical live registers are compared, excluding empty registers, physical
TOP, and exception flags. This is a finite diagnostic, not canonical equality,
original TU provenance, or an ABI requirement that every helper receive an empty
x87 stack.
"""

from __future__ import annotations

import argparse
from collections import Counter
import hashlib
import importlib.util
import json
from pathlib import Path
import struct

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location(
    "helper_entry_tail", ROOT / "scripts/audit-reimu-object-999-tail.py"
)
tail = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(tail)
native, x = tail.native, tail.x


class EntryProbe(native.Probe):
    def evaluate(self, case):
        self.events = []
        result = super().evaluate(case)
        return result, self.events

    def instruction(self, engine, pc, size, unused):
        if pc in self.callees:
            stack = engine.reg_read(native.r.UC_X86_REG_ESP)
            continuation = struct.unpack("<I", engine.mem_read(stack, 4))[0]
            from_root = (
                any(lo <= continuation < hi for lo, hi in native.facts.RANGES)
                if self.start == native.A
                else native.S <= continuation < native.S + self.size
            )
            if from_root:
                state = tail.floating_state(engine)
                self.events.append({
                    "callee": pc,
                    "depth": state["depth"],
                    "values": state["values"],
                })
        super().instruction(engine, pc, size, unused)


def audit(obj, stride):
    paths = [
        Path(__file__), obj, ROOT / "resources/th105.exe",
        ROOT / "config/match-units.toml",
        ROOT / "config/giant-action-switches.toml",
        ROOT / "src/characters/ReimuObjectActionStateStaging.cpp",
        ROOT / "src/characters/ReimuObjectActionStateStaging.hpp",
        *[ROOT / "scripts" / name for name in (
            "audit-reimu-object-999-tail.py",
            "audit-reimu-object-world-sharing.py",
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
    code = native.export(obj)  # Attests target, root boundaries and relocations.
    pe = native.pefile.PE(str(ROOT / "resources/th105.exe"))
    rows = [
        row for lo, hi in native.facts.RANGES
        for row in native.facts.decode(pe.get_data(lo - 0x400000, hi - lo), lo)
    ]
    callees = {
        row.operands[0].imm for row in rows
        if row.mnemonic == "call" and row.operands[0].type == x.X86_OP_IMM
        and not any(lo <= row.operands[0].imm < hi for lo, hi in native.facts.RANGES)
    }
    image = bytearray(pe.get_memory_mapped_image())
    math = native.load("helper_entry_math", "scripts/iku_native_math.py")
    table, lookup_receipt = math.lookup_fixture(native.c)
    image[0x2FE8B0:0x2FE8B0 + len(table)] = table
    image = bytes(image)
    seeds = native.seed_fixtures(image, (0, 5489, 0xFFFFFFFF, 79, 137))
    surfaces, surface_receipt = native.surface_fixtures(image)
    target = EntryProbe(image, seeds=seeds, surfaces=surfaces)
    source = EntryProbe(image, code, seeds=seeds, surfaces=surfaces)
    target.callees = source.callees = callees
    generators = (
        native.cases, native.projectile_cases, native.sequence_cases,
        native.late_projectile_cases, native.owner_projectile_cases,
        native.follow_projectile_cases, native.sibling_projectile_cases,
        native.orbit_projectile_cases, native.upper_projectile_cases,
        native.actions_903_905_cases, native.final_action_cases,
    )
    cases = [case for generate in generators for case in generate()][::stride]
    output_count = event_count = 0
    examples = []
    actions, visits = Counter(), Counter()
    for case in cases:
        a, ae = target.evaluate(case)
        b, be = source.evaluate(case)
        visits.update(event["callee"] for event in ae)
        output_count += a != b
        event_count += ae != be
        if ae != be:
            actions[case["action"]] += 1
        if (a != b or ae != be) and len(examples) < 15:
            examples.append({
                "case": case, "outputs_equal": a == b,
                "target_events": ae, "source_events": be,
            })
    after = pins()
    if before != after:
        raise ValueError("audit inputs changed during execution")
    return {
        "result": "equal_scoped_helper_entries" if output_count == event_count == 0
        else "different_scoped_helper_entries",
        "case_count": len(cases), "stride": stride,
        "input_sha256": hashlib.sha256(
            json.dumps(cases, sort_keys=True).encode()
        ).hexdigest(),
        "output_difference_count": output_count,
        "event_difference_count": event_count,
        "event_difference_actions": dict(actions),
        "target_callee_visits": {hex(k): v for k, v in sorted(visits.items())},
        "unvisited_direct_callees": [hex(k) for k in sorted(callees - visits.keys())],
        "examples": examples, "input_pins": before, "pins_unchanged": True,
        "build_provenance_verified": False,
        "lookup_fixture": lookup_receipt, "surface_fixture": surface_receipt,
        "limitations": [
            "Finite prefixes; opaque calls stop without synthesized returns.",
            "Compares logical live x87 values/tags, not TOP or exception flags.",
            "Does not establish original TU ownership or whole-root exactness.",
        ],
    }


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("object", type=Path)
    parser.add_argument("--stride", type=int, default=37)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    if args.stride < 1:
        parser.error("--stride must be positive")
    report = audit(args.object, args.stride)
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps({k: report[k] for k in (
        "result", "case_count", "output_difference_count", "event_difference_count",
    )}))
    return int(report["result"] != "equal_scoped_helper_entries")


if __name__ == "__main__":
    raise SystemExit(main())
