#!/usr/bin/env python3
"""Compare Aya804 call-separated sequence reads with original gate/math/frame code."""
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
spec = importlib.util.spec_from_file_location('aya804_math', ROOT / 'scripts/audit-aya-object-903-native.py')
math = importlib.util.module_from_spec(spec)
sys.modules[spec.name] = math
spec.loader.exec_module(math)
base = math.base


class Probe(math.Probe):
    action_id = 804

    def prepare(self, case):
        seq, phase, owner_action, counter, time, x, cw = self.settings
        for off, fmt, value in ((0x384, 'h', counter), (0x144, 'i', time), (0xEC, 'f', x)):
            self.uc.mem_write(base.OWNER + off, struct.pack('<' + fmt, value))
        self.uc.mem_write(base.OWNER + 0x113C, struct.pack('<h', owner_action))
        self.sequence_reads = []
        self.effect = None

    def step(self, uc, pc, size, data):
        if 0x5575C0 <= pc < pc + size <= 0x557688:
            assert bytes(uc.mem_read(pc, size)) == base.image[pc - 0x400000:pc - 0x400000 + size]
            if pc == 0x5575C0:
                self.calls.append(pc)
            return
        if pc == 0x435240:
            sp = uc.reg_read(base.r.UC_X86_REG_ESP)
            assert uc.reg_read(base.r.UC_X86_REG_ECX) == base.OWNER
            self.effect = list(struct.unpack('<5I', uc.mem_read(sp + 4, 20)))
            assert self.effect[0] == 200 and self.effect[4] == 1
            self.stop = 'original_effect_entry'
            uc.emu_stop()
            return
        super().step(uc, pc, size, data)

    def read(self, uc, access, address, size, value, data):
        pc = uc.reg_read(base.r.UC_X86_REG_EIP)
        if (self.start <= pc < self.start + self.size
                and address == base.OWNER + 0x13E and size == 2):
            self.sequence_reads.append((len(self.calls), len(self.writes),
                                        bytes(uc.mem_read(address, 2)).hex()))
        base.Probe.read(self, uc, access, address, size, value, data)

    def evaluate(self, case):
        self.settings = case
        seq, phase, owner_action, counter, time, x, cw = case
        result = base.Probe.run(self, (seq, phase, 100, cw, 20.0))
        prefix = phase != 5 and seq == 0 and 50 <= owner_action < 150
        assert result['stop'] == ('original_effect_entry' if prefix else 'ret')
        assert (self.effect is not None) == prefix
        result['sequence_reads'] = self.sequence_reads
        result['effect_entry_arguments'] = self.effect
        return result


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--object', type=Path, default=ROOT / base.unit['object'])
    parser.add_argument('--previous-object', type=Path)
    parser.add_argument('--output', type=Path, default=ROOT / 'build/aya804-sequence-read.json')
    args = parser.parse_args()
    table, receipt = math.lookup_fixture(base.c)
    cases = list(itertools.product(
        (0, 1, 2), (0, 1, 5, 6), (49, 50, 149, 150), (0, 9), (1, 61), (640.0, 1381.0),
        (0x27F, 0x67F, 0xA7F, 0xE7F, 0x37F, 0x77F, 0xB7F, 0xF7F),
    ))
    objects = ([args.previous_object] if args.previous_object else []) + [args.object]
    probes = [Probe(table)] + [Probe(table, obj) for obj in objects]
    counts = dict(cases=0, target_returns=0, target_effect_prefixes=0,
                  selected_differences=0, previous_differences=0)
    selected_fields, previous_fields, calls = Counter(), Counter(), Counter()
    examples = []
    for case in cases:
        results = [p.evaluate(case) for p in probes]
        counts['cases'] += 1
        counts['target_returns' if results[0]['stop'] == 'ret' else 'target_effect_prefixes'] += 1
        calls.update(hex(a) for a in results[0]['calls'])
        if results[0] != results[-1]:
            counts['selected_differences'] += 1
            selected_fields.update(k for k in results[0] if results[0][k] != results[-1][k])
        if args.previous_object and results[0] != results[1]:
            counts['previous_differences'] += 1
            previous_fields.update(k for k in results[0] if results[0][k] != results[1][k])
        if any(r != results[0] for r in results[1:]) and len(examples) < 2:
            examples.append(dict(case=case, reads=[r['sequence_reads'] for r in results]))
    helpers = {a: n for a, (n, _) in base.helpers.items()} | math.MATH | {0x5575C0: 200}
    report = dict(
        target_sha256=base.c.verify_target(),
        objects=[dict(path=str(obj), sha256=base.lp.sha(obj)) for obj in objects],
        counts=counts, selected_fields=dict(selected_fields), previous_fields=dict(previous_fields),
        target_calls=dict(calls), examples=examples,
        lookup={k: v for k, v in receipt.items() if k != 'trace'},
        original_helpers={hex(a): dict(size=n, sha256=hashlib.sha256(base.c.target_bytes(a, n)).hexdigest())
                          for a, n in helpers.items() if hex(a) in calls},
        input_sha256=hashlib.sha256(json.dumps(cases).encode()).hexdigest(),
        scope='804 original gate false paths, actual math/next-block/frame returns and true-gate prefixes stopped at original435240 entry; root WORD13E reads observed; no fabricated returns, effect execution, arbitrary resources, callback/unmasked-exception or whole-root proof',
    )
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
    if counts['selected_differences']:
        raise SystemExit(1)


if __name__ == '__main__':
    main()
