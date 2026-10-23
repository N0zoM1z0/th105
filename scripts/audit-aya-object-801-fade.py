#!/usr/bin/env python3
"""Execute Aya801/854 fades with original helpers and observe alpha-read x87 snapshots."""
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
spec = importlib.util.spec_from_file_location('aya801_gate', ROOT / 'scripts/audit-aya-object-804-sequence-read.py')
gate = importlib.util.module_from_spec(spec)
sys.modules[spec.name] = gate
spec.loader.exec_module(gate)
base, math = gate.base, gate.math


class Probe(gate.Probe):
    action_id = 801

    def prepare(self, case):
        seq, phase, owner_action, counter, time, alpha, sx, sy, timer, cw = self.settings
        for off, fmt, value in ((0x384, 'h', counter), (0x144, 'i', time), (0x142, 'h', timer),
                               (0x113, 'B', alpha), (0x11C, 'I', sx), (0x120, 'I', sy)):
            self.uc.mem_write(base.OWNER + off, struct.pack('<' + fmt, value))
        self.uc.mem_write(base.OWNER + 0x113C, struct.pack('<h', owner_action))
        self.sequence_reads, self.effect, self.spawn = [], None, None

    def step(self, uc, pc, size, data):
        if pc == 0x64CCB0:
            sp = uc.reg_read(base.r.UC_X86_REG_ESP)
            assert uc.reg_read(base.r.UC_X86_REG_ECX) == base.OWNER
            words = list(struct.unpack('<7I', uc.mem_read(sp + 4, 28)))
            assert words[0] == self.action_id and words[4] == 1 and words[6] == 3
            payload = bytes(uc.mem_read(words[5], 12)).hex()
            words[5] = 'payload'
            self.spawn = dict(arguments=words, payload=payload)
            self.stop = 'original_spawn_entry'
            uc.emu_stop()
            return
        super().step(uc, pc, size, data)

    def read(self, uc, access, address, size, value, data):
        pc = uc.reg_read(base.r.UC_X86_REG_EIP)
        if self.start <= pc < self.start + self.size and address == base.OWNER + 0x13E and size == 2:
            self.sequence_reads.append((len(self.calls), len(self.writes), bytes(uc.mem_read(address, 2)).hex()))
        math.Probe.read(self, uc, access, address, size, value, data)

    def evaluate(self, case):
        self.settings = case
        seq, phase, owner_action, counter, time, alpha, sx, sy, timer, cw = case
        result = base.Probe.run(self, (seq, phase, 100, cw, 20.0))
        assert result['stop'] in ('ret', 'original_effect_entry', 'original_spawn_entry')
        if self.action_id == 854:
            assert 0x5575C0 not in result['calls'] and self.effect is None
        result['sequence_reads'] = self.sequence_reads
        result['effect_entry_arguments'] = self.effect
        result['spawn_entry'] = self.spawn
        return result


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--action', type=int, choices=(801, 854), default=801)
    parser.add_argument('--object', type=Path, default=ROOT / base.unit['object'])
    parser.add_argument('--previous-object', type=Path)
    parser.add_argument('--allow-sequence-read-differences', action='store_true',
                        help='Scope acceptance to effects and alpha-read snapshots; report unresolved sequence-read differences')
    parser.add_argument('--output', type=Path)
    args = parser.parse_args()
    if args.output is None:
        args.output = ROOT / f'build/aya{args.action}-fade.json'
    table, receipt = math.lookup_fixture(base.c)
    cws = (0x27F, 0x67F, 0xA7F, 0xE7F, 0x37F, 0x77F, 0xB7F, 0xF7F)
    cases = list(itertools.product(
        (1, 2), (0,), (49,), (0,), (0, 1), (0, 4, 5, 19, 20, 255),
        (0, 0x3F800000, 0x3F800001, 1, 0x7F7FFFFF, 0x7F800000, 0x7FC00123, 0x7F800001),
        (0x3F800001,), (0, 2), cws))
    cases += list(itertools.product(
        (0, 1, 2, 3), (0, 1, 5, 6), (49, 50, 149, 150), (3, 4, 32767),
        (0, 1), (20,), (0x3F800000,), (0x3F800001,), (0,), (0x27F, 0x37F)))
    objects = ([args.previous_object] if args.previous_object else []) + [args.object]
    probes = [Probe(table)] + [Probe(table, obj) for obj in objects]
    for probe in probes:
        probe.action_id = args.action
    stops, calls, selected, previous = Counter(), Counter(), Counter(), Counter()
    examples = []
    for case in cases:
        results = [p.evaluate(case) for p in probes]
        stops.update([results[0]['stop']])
        calls.update(hex(a) for a in results[0]['calls'])
        selected.update(k for k in results[0] if results[0][k] != results[-1][k])
        if args.previous_object:
            previous.update(k for k in results[0] if results[0][k] != results[1][k])
        if any(r != results[0] for r in results[1:]) and len(examples) < 2:
            examples.append(dict(case=case, alpha_reads=[r['alpha_reads'] for r in results],
                                 sequence_reads=[r['sequence_reads'] for r in results]))
    helpers = {a: n for a, (n, _) in base.helpers.items()} | math.MATH | {0x5575C0: 200}
    report = dict(target_sha256=base.c.verify_target(), action=args.action, cases=len(cases), target_stops=dict(stops),
                  selected_differing_fields=dict(selected), previous_differing_fields=dict(previous),
                  sequence_reads_required=not args.allow_sequence_read_differences,
                  objects=[dict(path=str(p), sha256=base.lp.sha(p)) for p in objects],
                  target_calls=dict(calls), examples=examples,
                  lookup={k: v for k, v in receipt.items() if k != 'trace'},
                  original_helpers={hex(a): dict(size=n, sha256=hashlib.sha256(base.c.target_bytes(a,n)).hexdigest())
                                    for a,n in helpers.items() if hex(a) in calls},
                  input_sha256=hashlib.sha256(json.dumps(dict(action=args.action, cases=cases)).encode()).hexdigest(),
                  scope=f'{args.action} original math/animation returns and spawn entry prefixes; original gate/effect prefixes only for801; alpha-read live x87 snapshots and WORD13E read epochs; masked x87 only; no fabricated returns, full spawn/effect, arbitrary resource, callback, exception or whole-root proof')
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
    allowed = {'sequence_reads'} if args.allow_sequence_read_differences else set()
    if set(selected) - allowed:
        raise SystemExit(1)


if __name__ == '__main__':
    main()
