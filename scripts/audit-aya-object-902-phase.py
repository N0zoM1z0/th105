#!/usr/bin/env python3
"""Execute Aya902 phase updates through actual animation/transition helpers."""

from pathlib import Path
import argparse
import hashlib
import importlib.util
import itertools
import json
import struct
import sys

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location(
    "aya902_animation", ROOT / "scripts/audit-aya-object-901-transition.py"
)
base = importlib.util.module_from_spec(spec)
sys.modules[spec.name] = base
spec.loader.exec_module(base)
parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument("--previous-object", type=Path)
parser.add_argument("--output", type=Path, default=ROOT / "build/aya902-phase.json")
args = parser.parse_args()


class Probe(base.Probe):
    require_901_calls = False
    action_id = 902

    def prepare(self, case):
        phase, health, cw, state, index, mode, counter, speed, facing = self.settings
        assert counter % 3 != 0
        fields = (
            (0x13C, "h", 902),
            (0x13E, "h", 1),
            (0x144, "i", counter),
            (0x180, "i", phase),
            (0x364, "h", state),
            (0x184, "B", index),
            (0xF4, "f", speed),
            (0x104, "b", facing),
        )
        for offset, fmt, value in fields:
            self.uc.mem_write(base.OWNER + offset, struct.pack("<" + fmt, value))
        self.uc.mem_write(0x6FA894, struct.pack("<i", mode))

    def evaluate(self, case):
        self.settings = case
        phase, health, cw, *_ = case
        result = super().run((1, phase, health, cw, 20.0))
        assert result["stop"] == "ret"
        return result


objects = [ROOT / base.unit["object"]]
if args.previous_object:
    objects.insert(0, args.previous_object)
probes = [Probe()] + [Probe(p) for p in objects]
cases = list(
    itertools.product(
        (0, 1, 4, 6, 8),
        (100,),
        (0x27F, 0x37F),
        (-1, 0, 2, 3, 4, 5, 6, 32767),
        (0, 1, 127, 128, 255),
        (4,),
        (1,),
        (2.0, 12.0),
        (-1, 1),
    )
)
# Mode-specific expiration on both sides of each bound, with spawn-free counters.
for mode, limit in enumerate((180, 320, 500, 600)):
    times = [t for t in (limit - 1, limit, limit + 1, limit + 2) if t % 3]
    cases += list(
        itertools.product(
            (0, 1, 6),
            (-1, 0, 100),
            (0x27F, 0x37F),
            (0, 5),
            (0, 1),
            (mode,),
            times,
            (12.0,),
            (-1, 1),
        )
    )
counts = dict(
    cases=0, selected_differences=0, previous_differences=0, target_callbacks=0
)
examples = []
used = set()
for case in cases:
    results = [p.evaluate(case) for p in probes]
    counts["cases"] += 1
    used.update(results[0]["calls"])
    counts["target_callbacks"] += results[0]["calls"].count(0x45C220)
    if results[0] != results[-1]:
        counts["selected_differences"] += 1
        if len(examples) < 3:
            examples.append(dict(case=case, results=results))
    if args.previous_object:
        counts["previous_differences"] += results[0] != results[1]
selected = objects[-1]
f = base.f
co = base.mapper.CoffObject(selected, symbol_base=f["symbol_base"])
code = base.c.coff_symbol_bytes(
    selected,
    f["symbol_base"],
    base.S,
    len(co.text),
    {a: int(b, 0) for a, b in (z.split("=", 1) for z in f["rel32_targets"])},
    base.c.known_data_targets(),
    dict(z.split("=", 1) for z in f.get("dir32_targets", [])),
)
phase_window = base.c.target_bytes(0x61E550, 77)
phase_offset = (
    0x4325  # Qualified current action902 interval, not another identical phase block.
)
assert code[phase_offset : phase_offset + 77] == phase_window, (
    "target902 phase update window differs"
)
report = dict(
    target_sha256=base.c.verify_target(),
    objects=[dict(path=str(p), sha256=base.lp.sha(p)) for p in objects],
    translated_phase_window=dict(
        target="0x61E550", source=hex(base.S + phase_offset), bytes=77
    ),
    counts=counts,
    examples=examples,
    original_helpers={
        hex(a): dict(
            size=base.helpers[a][0],
            sha256=hashlib.sha256(
                base.c.target_bytes(a, base.helpers[a][0])
            ).hexdigest(),
        )
        for a in sorted(used)
    },
    scope="902 sequence1; actual frame/next-block helpers and complete RET; spawn-free finite counters/phase/health fixture, masked x87; no arbitrary resources or full-root proof",
    input_sha256=hashlib.sha256(json.dumps(cases).encode()).hexdigest(),
)
args.output.parent.mkdir(parents=True, exist_ok=True)
args.output.write_text(json.dumps(report, indent=2) + "\n")
print(json.dumps(report, indent=2))
if counts["selected_differences"]:
    raise SystemExit(1)
