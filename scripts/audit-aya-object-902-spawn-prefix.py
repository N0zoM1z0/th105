#!/usr/bin/env python3
"""Compare Aya902 real spawn-entry prefixes; never fabricate a spawn return."""

from pathlib import Path
import argparse
from collections import Counter
import hashlib
import importlib.util
import itertools
import json
import struct
import sys

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location(
    "aya902_spawn_animation", ROOT / "scripts/audit-aya-object-901-transition.py"
)
base = importlib.util.module_from_spec(spec)
sys.modules[spec.name] = base
spec.loader.exec_module(base)
parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument("--object", type=Path, default=ROOT / base.unit["object"])
parser.add_argument("--previous-object", type=Path)
parser.add_argument(
    "--output", type=Path, default=ROOT / "build/aya902-spawn-prefix.json"
)
args = parser.parse_args()


class Probe(base.Probe):
    require_901_calls = False
    action_id = 902

    def prepare(self, case):
        seq, angle, x, facing, speed, cw = self.settings
        fields = (
            (0x13E, "h", seq),
            (0x144, "i", 0),
            (0x370, "I", angle),
            (0xEC, "f", x),
            (0xF4, "f", speed),
            (0x104, "b", facing),
        )
        for offset, fmt, value in fields:
            self.uc.mem_write(base.OWNER + offset, struct.pack("<" + fmt, value))
        self.spawn = None

    def step(self, uc, pc, size, data):
        if pc == 0x64CCB0:
            esp = uc.reg_read(base.r.UC_X86_REG_ESP)
            words = list(struct.unpack("<7I", uc.mem_read(esp + 4, 28)))
            pointer = words[5]
            assert words[0] == 821 and words[6] == 3
            assert base.STACK <= pointer < pointer + 12 <= base.STACK + 0x10000
            assert uc.reg_read(base.r.UC_X86_REG_ECX) == base.OWNER
            words[5] = pointer - base.STACK
            self.spawn = dict(
                words=words,
                payload=bytes(uc.mem_read(pointer, 12)).hex(),
                stack_depth=base.STACK + 0xFF00 - esp,
            )
            self.stop = "spawn_entry"
            uc.emu_stop()
            return
        super().step(uc, pc, size, data)

    def evaluate(self, case):
        self.settings = case
        seq, angle, x, facing, speed, cw = case
        result = super().run((seq, 0, 100, cw, 20.0))
        assert (
            result["stop"] == "spawn_entry"
            and self.spawn is not None
            and not self.calls
        )
        result["spawn"] = self.spawn
        return result


objects = [args.object]
if args.previous_object:
    objects.insert(0, args.previous_object)
probes = [Probe()] + [Probe(p) for p in objects]
angles = [
    struct.unpack("<I", struct.pack("<f", v))[0]
    for v in (-165.0, -164.0, 0.0, 15.0, 16.0, 196.0, 197.0)
]
angles += [1, 0x80000000, 0x7F800000, 0xFF800000, 0x7FC00123, 0x7F800001]
cases = list(
    itertools.product(
        (-1, 0, 1),
        angles,
        (40.0, 640.0, 1240.0),
        (-1, 1),
        (2.0, 12.0),
        (0x27F, 0x67F, 0xA7F, 0xE7F, 0x37F, 0x77F, 0xB7F, 0xF7F),
    )
)
counts = dict(cases=0, selected_differences=0, previous_differences=0)
fields = Counter()
examples = []
for case in cases:
    results = [p.evaluate(case) for p in probes]
    counts["cases"] += 1
    if results[0] != results[-1]:
        counts["selected_differences"] += 1
        if len(examples) < 2:
            examples.append(dict(case=case, results=results))
    if args.previous_object and results[0] != results[1]:
        counts["previous_differences"] += 1
        fields.update(k for k in results[0] if results[0][k] != results[1][k])
report = dict(
    target_sha256=base.c.verify_target(),
    objects=[dict(path=str(p), sha256=base.lp.sha(p)) for p in objects],
    counts=counts,
    previous_differing_fields=dict(fields),
    examples=examples,
    scope="902 sequences-1/0/1 actual root-entry to original64CCB0; exact argument words/payload and pre-call actor/x87 state; no helper execution or fabricated return; finite input matrix with masked x87 exceptions, not whole-root/callback/exception proof",
    input_sha256=hashlib.sha256(json.dumps(cases).encode()).hexdigest(),
)
args.output.parent.mkdir(parents=True, exist_ok=True)
args.output.write_text(json.dumps(report, indent=2) + "\n")
print(json.dumps(report, indent=2))
if counts["selected_differences"]:
    raise SystemExit(1)
