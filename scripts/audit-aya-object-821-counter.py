#!/usr/bin/env python3
"""Execute Aya821 sequence0 with original integer sine and independent WORD364/36C."""
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
sys.path.insert(0, str(ROOT / 'scripts'))
spec = importlib.util.spec_from_file_location('aya821_animation', ROOT / 'scripts/audit-aya-object-901-transition.py')
base = importlib.util.module_from_spec(spec)
sys.modules[spec.name] = base
spec.loader.exec_module(base)
from iku_native_math import lookup_fixture


class Probe(base.Probe):
    require_901_calls = False
    action_id = 821

    def __init__(self, table, obj=None):
        super().__init__(obj)
        self.uc.mem_write(0x6FE8B0, table)

    def prepare(self, case):
        phase, counter, unrelated, growth, cw = self.settings
        for off, fmt, value in ((0x364, 'h', counter), (0x36C, 'h', unrelated),
                                (0x370, 'I', growth), (0x11C, 'f', 1.0), (0x120, 'f', 1.0)):
            self.uc.mem_write(base.OWNER + off, struct.pack('<' + fmt, value))
        self.sine_arguments = []

    def step(self, uc, pc, size, data):
        if 0x406480 <= pc < pc + size <= 0x4064A2:
            assert bytes(uc.mem_read(pc, size)) == base.image[pc - 0x400000:pc - 0x400000 + size]
            if pc == 0x406480:
                sp = uc.reg_read(base.r.UC_X86_REG_ESP)
                self.sine_arguments.append(struct.unpack('<i', uc.mem_read(sp + 4, 4))[0])
                self.calls.append(pc)
            return
        super().step(uc, pc, size, data)

    def evaluate(self, case):
        self.settings = case
        phase, counter, unrelated, growth, cw = case
        result = super().run((0, phase, 100, cw, 20.0))
        assert result['stop'] == 'ret'
        assert len(self.sine_arguments) == int(phase != 5)
        result['sine_arguments'] = self.sine_arguments
        return result


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--object', type=Path, default=ROOT / base.unit['object'])
    parser.add_argument('--previous-object', type=Path)
    parser.add_argument('--output', type=Path, default=ROOT / 'build/aya821-counter.json')
    args = parser.parse_args()
    table, receipt = lookup_fixture(base.c)
    counters = (-32768, -1, 0, 83, 84, 85, 89, 90, 32761, 32762, 32767)
    unrelated = (-32768, 0, 84, 90, 32767)
    controls = (0x27F, 0x67F, 0xA7F, 0xE7F, 0x37F, 0x77F, 0xB7F, 0xF7F)
    cases = list(itertools.product((0,), counters, unrelated,
                                   (0, 0x80000000, 0x3E800000, 0x41200000, 0x7F7FFFFF, 0x7F800000, 0x7FC00123), controls))
    cases += list(itertools.product((5, 6), counters, unrelated, (0x3E800000,), (0x27F, 0x37F)))
    objects = ([args.previous_object] if args.previous_object else []) + [args.object]
    probes = [Probe(table)] + [Probe(table, obj) for obj in objects]
    selected_fields, previous_fields, calls = Counter(), Counter(), Counter()
    counts = dict(cases=0, selected_differences=0, previous_differences=0)
    examples = []
    for case in cases:
        values = [p.evaluate(case) for p in probes]
        counts['cases'] += 1
        calls.update(hex(a) for a in values[0]['calls'])
        if values[0] != values[-1]:
            counts['selected_differences'] += 1
            selected_fields.update(k for k in values[0] if values[0][k] != values[-1][k])
        if args.previous_object and values[0] != values[1]:
            counts['previous_differences'] += 1
            previous_fields.update(k for k in values[0] if values[0][k] != values[1][k])
        if any(v != values[0] for v in values[1:]) and len(examples) < 2:
            examples.append(dict(case=case, sine_arguments=[v['sine_arguments'] for v in values],
                                 counter_words=[bytes.fromhex(v['actor'])[0x364:0x36E].hex() for v in values]))
    helpers = {a: n for a, (n, _) in base.helpers.items()} | {0x406480: 34}
    delta = None
    if args.previous_object:
        def canonical(obj):
            co = base.mapper.CoffObject(obj, symbol_base=base.f['symbol_base'])
            return base.c.coff_symbol_bytes(
                obj, base.f['symbol_base'], base.A, len(co.text),
                {a: int(b, 0) for a, b in (z.split('=', 1) for z in base.f['rel32_targets'])},
                base.c.known_data_targets(), dict(z.split('=', 1) for z in base.f.get('dir32_targets', [])),
            )
        old, new = canonical(args.previous_object), canonical(args.object)
        changes = [dict(offset=hex(i), old=a, new=b)
                   for i, (a, b) in enumerate(itertools.zip_longest(old, new)) if a != b]
        delta = dict(sizes=[len(old), len(new)],
                     sha256=[hashlib.sha256(code).hexdigest() for code in (old, new)],
                     changed_byte_count=len(changes), changed_bytes=changes[:64],
                     all_changes_listed=len(changes) <= 64)
    report = dict(
        target_sha256=base.c.verify_target(),
        objects=[dict(path=str(obj), sha256=base.lp.sha(obj)) for obj in objects],
        canonical_delta=delta, counts=counts, selected_fields=dict(selected_fields), previous_fields=dict(previous_fields),
        target_calls=dict(calls), examples=examples,
        lookup={k: v for k, v in receipt.items() if k != 'trace'},
        original_helpers={hex(a): dict(size=n, sha256=hashlib.sha256(base.c.target_bytes(a, n)).hexdigest())
                          for a, n in helpers.items() if hex(a) in calls},
        input_sha256=hashlib.sha256(json.dumps(cases).encode()).hexdigest(),
        scope='action821 sequence0 actual root entry through original406480 and frame helper below virtual-dispatch threshold to RET; independent signed WORD364/36C, masked x87; no other sequences, arbitrary resources, callback/unmasked-exception or whole-root equivalence claim',
    )
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
    if counts['selected_differences']:
        raise SystemExit(1)


if __name__ == '__main__':
    main()
