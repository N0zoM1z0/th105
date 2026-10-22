#!/usr/bin/env python3
"""Execute Aya903 sequences2/3 with original math; distinguish read epochs from effects."""
from pathlib import Path
import argparse
from collections import Counter
import hashlib
import importlib.util
import itertools
import json
import struct
import sys
import tomllib

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))
spec = importlib.util.spec_from_file_location('aya903_animation', ROOT / 'scripts/audit-aya-object-901-transition.py')
base = importlib.util.module_from_spec(spec)
sys.modules[spec.name] = base
spec.loader.exec_module(base)
from iku_native_math import lookup_fixture

MATH = {0x435160: 57, 0x406360: 100, 0x4063D0: 94,
        0x68A1A0: 171, 0x68BAAE: 182, 0x696387: 39}


class Probe(base.Probe):
    require_901_calls = False
    action_id = 903

    def __init__(self, table, obj=None):
        super().__init__(obj)
        self.uc.mem_write(0x6FE8B0, table)

    def step(self, uc, pc, size, data):
        if any(a <= pc < pc + size <= a + n for a, n in MATH.items()):
            assert bytes(uc.mem_read(pc, size)) == base.image[pc - 0x400000:pc - 0x400000 + size]
            if pc in MATH:
                self.calls.append(pc)
            return
        super().step(uc, pc, size, data)

    def read(self, uc, access, address, size, value, data):
        if address == base.OWNER + 0x113 and size == 1:
            self.reads.append(dict(
                writes=len(self.writes), alpha=bytes(uc.mem_read(address, 1)).hex(),
                scale=bytes(uc.mem_read(base.OWNER + 0x120, 4)).hex(),
                status=uc.reg_read(base.r.UC_X86_REG_FPSW),
                tag=uc.reg_read(base.r.UC_X86_REG_FPTAG),
                live_registers=[
                    None if (uc.reg_read(base.r.UC_X86_REG_FPTAG) >> (2 * i)) & 3 == 3
                    else uc.reg_read(getattr(base.r, 'UC_X86_REG_FP' + str(i)))
                    for i in range(8)
                ],
            ))

    def prepare(self, case):
        phase, fade, alpha, scale, angle, speed, facing, counter = self.settings
        for off, fmt, val in (
            (0x180, 'i', phase), (0x364, 'h', fade), (0x113, 'B', alpha),
            (0x110, 'B', 7), (0x111, 'B', 250), (0x11C, 'I', scale),
            (0x120, 'I', scale), (0x104, 'b', facing), (0x144, 'i', counter),
        ):
            self.uc.mem_write(base.OWNER + off, struct.pack('<' + fmt, val))
        self.uc.mem_write(base.OWNER + 0x8000, struct.pack('<ff', angle, speed))

    def evaluate(self, case):
        seq, cw, health, *self.settings = case
        out = super().run((seq, 0, health, cw, 20.0))
        assert out['stop'] == 'ret'
        assert out['calls'].count(0x435160) == int(health > 0)
        return out


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--object', type=Path, default=ROOT / base.unit['object'])
    parser.add_argument('--diagnostic', action='store_true',
                        help='Diagnostic control only: report alpha snapshot/window differences without accepting them')
    parser.add_argument('--output', type=Path, default=ROOT / 'build/aya903-native.json')
    args = parser.parse_args()
    table, receipt = lookup_fixture(base.c)
    cw = (0x27F, 0x67F, 0xA7F, 0xE7F, 0x37F, 0x77F, 0xB7F, 0xF7F)
    cases = list(itertools.product(
        (2, 3), cw, (100,), (0, 6), (0, 1), (19, 20, 255),
        (0x3F800000, 0x3F800001), (45.0,), (12.0,), (-1, 1), (179, 180),
    ))
    cases += list(itertools.product(
        (2, 3), cw, (100,), (0,), (1,), (20,), (0x3F800000,),
        (-180.0, -90.0, -0.0, 0.0, 0.1, 89.9, 180.0, 359.9),
        (-12.0, 0.0, 12.0), (-1, 1), (180,),
    ))
    cases += list(itertools.product(
        (2, 3), cw, (100,), (0,), (0, 1), (19, 20, 255),
        (0, 0x80000000, 1, 0x7F7FFFFF, 0x7F800000, 0xFF800000, 0x7FC00123, 0x7F800001),
        (45.0,), (12.0,), (1,), (180,),
    ))
    cases += list(itertools.product(
        (2, 3), (0x27F, 0x37F), (-1, 0), (0, 6), (0, 1), (19, 20, 255),
        (0x3F800000,), (45.0,), (12.0,), (1,), (180,),
    ))
    probes = [Probe(table), Probe(table, args.object)]
    differences, epoch_fields, calls = Counter(), Counter(), Counter()
    examples = []
    for case in cases:
        values = [p.evaluate(case) for p in probes]
        changed = [k for k in values[0] if values[0][k] != values[1][k]]
        differences.update(changed)
        calls.update(hex(a) for a in values[0]['calls'])
        if values[0]['alpha_reads'] != values[1]['alpha_reads']:
            assert len(values[0]['alpha_reads']) == len(values[1]['alpha_reads']) == 1
            epoch_fields.update(k for k in values[0]['alpha_reads'][0]
                                if values[0]['alpha_reads'][0][k] != values[1]['alpha_reads'][0][k])
        if changed and len(examples) < 2:
            examples.append(dict(case=case, fields=changed,
                                 alpha_reads=[v['alpha_reads'] for v in values]))
    effect_differences = {k: v for k, v in differences.items() if k != 'alpha_reads'}
    # Pin this non-relocated read/store interval to the actual903 owner, not
    # an arbitrary identical sequence elsewhere in the complete root.
    co = base.mapper.CoffObject(args.object, symbol_base=base.f['symbol_base'])
    root = base.mapper.load_target_mapper().select_root(
        tomllib.loads((ROOT / 'config/giant-action-switches.toml').read_text()),
        'aya-object-vslot28',
    )
    mapping = base.mapper.build_candidate_map(co, root)
    primary = next(region for region in mapping['regions'] if region['name'] == 'actions')
    owned = [group for group in primary['groups'] if 903 in group['cases']]
    assert len(owned) == 1 and owned[0]['cases'] == [903]
    start = owned[0]['offset']
    size = owned[0]['span_to_next_destination']
    code = bytes(probes[-1].uc.mem_read(base.S + start, size))
    window = base.c.target_bytes(0x61E829, 14)
    count = code.count(window)
    window_equal = count == 1
    read_store_window = dict(target='0x61e829', bytes=14, matches=count,
                             sha256=hashlib.sha256(window).hexdigest(),
                             source=hex(base.S + start + code.index(window)) if window_equal else None)
    report = dict(
        result='effects_differ' if effect_differences else ('read_epoch_or_window_differs' if differences or not window_equal else 'equal'),
        target_sha256=base.c.verify_target(), object_sha256=base.lp.sha(args.object),
        cases=len(cases), read_store_window=read_store_window, differences=dict(differences), alpha_epoch_fields=dict(epoch_fields),
        target_calls=dict(calls), examples=examples,
        lookup={k: v for k, v in receipt.items() if k != 'trace'},
        original_helpers={hex(a): dict(size=n, sha256=hashlib.sha256(base.c.target_bytes(a, n)).hexdigest())
                          for a, n in ({a: size for a, (size, _) in base.helpers.items()} | MATH).items()
                          if hex(a) in calls},
        input_sha256=hashlib.sha256(json.dumps(cases).encode()).hexdigest(),
        scope='sequences2/3 actual root entry to RET, original math and frame helper, frame fixture below virtual-dispatch threshold; masked x87; no helper-result hooks, unmasked exception or complete903/root equivalence claim; empty physical x87 registers excluded from alpha snapshots',
    )
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
    if effect_differences or ((differences or not window_equal) and not args.diagnostic):
        raise SystemExit(1)


if __name__ == '__main__':
    main()
