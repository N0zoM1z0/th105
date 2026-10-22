#!/usr/bin/env python3
"""Audit Aya810's independent sequence read using original gate/terrain/math code."""
from pathlib import Path
from collections import Counter
import argparse
import hashlib
import importlib.util
import itertools
import json
import struct
import sys

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location('aya810_gate', ROOT / 'scripts/audit-aya-object-804-sequence-read.py')
gate = importlib.util.module_from_spec(spec)
sys.modules[spec.name] = gate
spec.loader.exec_module(gate)
base, math = gate.base, gate.math
TERRAIN = {0x435D60: 89, 0x435DC0: 42, 0x5F9310: 64}


class Probe(gate.Probe):
    action_id = 810

    def prepare(self, case):
        seq, phase, owner_action, counter, timer, x, y, vy, height, cw = self.settings
        for off, fmt, value in ((0x384, 'h', counter), (0x142, 'h', timer),
                                (0xEC, 'f', x), (0xF0, 'f', y), (0xF8, 'f', vy)):
            self.uc.mem_write(base.OWNER + off, struct.pack('<' + fmt, value))
        self.uc.mem_write(base.OWNER + 0x113C, struct.pack('<h', owner_action))
        self.uc.mem_write(0x6FA898, struct.pack('<f', height) * 0x500)
        self.sequence_reads, self.effect, self.spawn = [], None, None

    def step(self, uc, pc, size, data):
        if any(a <= pc < pc + size <= a + n for a, n in TERRAIN.items()):
            assert bytes(uc.mem_read(pc, size)) == base.image[pc - 0x400000:pc - 0x400000 + size]
            if pc in TERRAIN:
                self.calls.append(pc)
            return
        if pc == 0x64CCB0:
            sp = uc.reg_read(base.r.UC_X86_REG_ESP)
            assert uc.reg_read(base.r.UC_X86_REG_ECX) == base.OWNER
            words = list(struct.unpack('<7I', uc.mem_read(sp + 4, 28)))
            assert words[0] == 810 and words[4] == 1 and words[6] == 3
            payload = bytes(uc.mem_read(words[5], 12)).hex()
            # Stack payload addresses may differ; compare the pointed-to words.
            words[5] = 'payload'
            self.spawn = dict(arguments=words, payload=payload)
            self.stop = 'original_spawn_entry'
            uc.emu_stop()
            return
        super().step(uc, pc, size, data)

    def evaluate(self, case):
        self.settings = case
        seq, phase, owner_action, counter, timer, x, y, vy, height, cw = case
        result = base.Probe.run(self, (seq, phase, 100, cw, 20.0))
        assert result['stop'] in ('ret', 'original_effect_entry', 'original_spawn_entry')
        result['sequence_reads'] = self.sequence_reads
        result['effect_entry_arguments'] = self.effect
        result['spawn_entry'] = self.spawn
        return result


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--object', type=Path, default=ROOT / base.unit['object'])
    parser.add_argument('--previous-object', type=Path)
    parser.add_argument('--output', type=Path, default=ROOT / 'build/aya810-sequence-read.json')
    args = parser.parse_args()
    table, receipt = math.lookup_fixture(base.c)
    cws = (0x27F, 0x67F, 0xA7F, 0xE7F, 0x37F, 0x77F, 0xB7F, 0xF7F)
    cases = list(itertools.product(
        (0, 1, 2, 3), (0, 1, 5, 6), (49, 50, 149, 150), (9, 19), (0, 61),
        (640.0,), (0.0,), (-1.0, 0.0), (0.0,), (0x27F, 0x37F)))
    cases += list(itertools.product(
        (0, 1, 2, 3), (0,), (49,), (0,), (60,),
        (-101.0, -100.0, 0.0, 640.0, 1380.0, 1381.0),
        (-161.0, -160.0, -1.0, 0.0, 1.0, 1000.0, 1001.0),
        (-1.0,), (-1.0, 1.0), cws))
    cases += list(itertools.product(
        (0, 1, 2, 3), (6,), (49,), (0, 8, 9, 18, 19, 32767), (0,),
        (640.0,), (0.0,), (-1.0, 0.0), (0.0,), cws))
    objects = ([args.previous_object] if args.previous_object else []) + [args.object]
    probes = [Probe(table)] + [Probe(table, obj) for obj in objects]
    stops, calls, selected_fields, previous_fields = Counter(), Counter(), Counter(), Counter()
    examples = []
    for case in cases:
        results = [p.evaluate(case) for p in probes]
        stops.update([results[0]['stop']])
        calls.update(hex(a) for a in results[0]['calls'])
        selected_fields.update(k for k in results[0] if results[0][k] != results[-1][k])
        if args.previous_object:
            previous_fields.update(k for k in results[0] if results[0][k] != results[1][k])
        if any(r != results[0] for r in results[1:]) and len(examples) < 3:
            examples.append(dict(case=case, reads=[r['sequence_reads'] for r in results],
                                 differing_fields=[[k for k in results[0] if r[k] != results[0][k]] for r in results[1:]]))
    helpers = {a: n for a, (n, _) in base.helpers.items()} | math.MATH | TERRAIN | {0x5575C0: 200}
    report = dict(
        target_sha256=base.c.verify_target(), cases=len(cases), target_stops=dict(stops),
        selected_differing_fields=dict(selected_fields), previous_differing_fields=dict(previous_fields),
        objects=[dict(path=str(p), sha256=base.lp.sha(p)) for p in objects],
        target_calls=dict(calls), examples=examples,
        lookup={k: v for k, v in receipt.items() if k != 'trace'},
        original_helpers={hex(a): dict(size=n, sha256=hashlib.sha256(base.c.target_bytes(a, n)).hexdigest())
                          for a, n in helpers.items() if hex(a) in calls},
        input_sha256=hashlib.sha256(json.dumps(cases).encode()).hexdigest(),
        scope='810 original gate/terrain/math/animation returns, effect435240 and related-object64CCB0 entry prefixes; root WORD13E read epochs; finite uniform terrain and masked x87 only; no mocked return, spawn execution, arbitrary resources, callback or whole-root proof',
    )
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
    if selected_fields:
        raise SystemExit(1)


if __name__ == '__main__':
    main()
