#!/usr/bin/env python3
"""Compare all five returning Reimu815 requests and their real callbacks."""
from __future__ import annotations

import argparse
from collections import Counter
import hashlib
import importlib.util
import itertools
import json
from pathlib import Path
import struct
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location('trajectory_circular_native', ROOT/'scripts/audit-reimu-circular-returns.py')
circular = importlib.util.module_from_spec(spec)
sys.modules[spec.name] = circular
spec.loader.exec_module(circular)
owned, shared = circular.owned, circular.shared
HOST = owned.HOST
SCHEMA = 'th105-reimu-trajectory-returns-v1'
RESOURCE_FILES = owned.RESOURCE_FILES
SUPPORT_PATHS = (*circular.SUPPORT_PATHS, Path(circular.__file__))
RESOURCE_KEYS = (0, 9, 520, 521, 522, 523, 550, 551, 815)
SCOPE = ('all five returning815 requests for520..523, real 256-object manager/copy/callback/destruction; '
         'raw actor/object/copied-array/child/MT/pool/FP/texture-prefix snapshots without masks; '
         'supplied read-only untextured resources and frame wrap; no arbitrary-world/resources, '
         'later object ticks, exceptions, exact or aggregate-progress claim')


def require(condition, message):
    shared.require(condition, message)


def profiles(smoke):
    facings, words, seeds = ((1,), (0x27F,), (5489,)) if smoke else (
        (-128, -1, 0, 1, 127), (0x27F, 0x37F), (0, 5489))
    geometry = ((640.0, 100.0),) if smoke else ((640.0, 100.0), (33554432.0, 33554432.0))
    timings = ((0, 32),) if smoke else ((0, 32), (2, 3))
    for action, (x, airborne_y), (timer, duration), facing, cw, seed in itertools.product(
            (520, 521, 522, 523), geometry, timings, facings, words, seeds):
        yield dict(action=action, sequence=3, x=x, y=airborne_y if action >= 522 else 0.0,
                   counter=0, timer=timer, duration=duration, phase=5.0, texture=(0, 0), skill=4,
                   facing=facing, cw=cw, seed=seed, object_id=815, parameter_words=3, objects=5)


def fixture(output, smoke):
    return circular.fixture(output, smoke, cases=profiles(smoke), keys=RESOURCE_KEYS)


def expected_status(cases):
    return {'objects': 5*len(cases), 'texture_context': True}


def f32(value):
    return struct.pack('<f', value)


def check_target(case, row):
    actor = row['actor']
    timer = 0 if case['timer']+1 >= case['duration'] else case['timer']+1
    require(struct.unpack_from('<hhhi', actor, 0x13E) == (3, 0, timer, 1)
            and struct.unpack_from('<h', actor, 0x13C)[0] == case['action']
            and struct.unpack_from('<I', actor, 0x180)[0] == 1 and actor[0x17C] == 1,
            'target bypassed the complete request/frame/state continuation')
    require(len(row['objects']) == 5 and row['generation'] == 261 and row['free'] == 251,
            'target complete five-request pool accounting')
    require(row['cw'] == (0x8001F | (0x10000 if case['cw'] == 0x27F else 0)), 'target FP control')
    require(struct.unpack_from('<II', row['texture'], 0xD8) == (0x11223344, 0x55667788),
            'unexpected texture publication')
    x_offset, y_offset = (43, 107.0) if case['action'] >= 522 else (114, 96.0)
    position = f32(case['x']+case['facing']*x_offset)+f32(case['y']+y_offset)
    values = []
    for index, child in enumerate(row['objects']):
        body = child['bytes']
        require(struct.unpack_from('<hh', body, 0x13C) == (815, 0 if index == 0 else 2)
                and struct.unpack_from('<I', body, 0x334)[0] == ((257+index)<<16 | (255-index))
                and struct.unpack_from('<I', body, 0x330)[0] == 1
                and struct.unpack_from('<I', body, 0x34C)[0] == 0
                and child['children'] == () and child['words'] == 3,
                'target815 callback identity/sequence/parameter/topology')
        require(body[0xEC:0xF4] == position and body[0x104] == case['facing'] & 255,
                'target815 callback position/direction')
        values.append(struct.unpack('<fff', child['parameters']))
    fast = case['action'] in (521, 523)
    require(values[0] == (0.0, 25.0 if fast else 12.0, 0.0), 'target815 initial straight request')
    near, reverse_near, reverse_far, far = values[1:]
    require(near[2] == reverse_near[2] == reverse_far[2] == far[2] == 2.0
            and 0 < far[0] < near[0] <= 45.0
            and reverse_near[0] == -near[0] and reverse_far[0] == -far[0]
            and 0 < near[1] == reverse_near[1] < far[1] == reverse_far[1],
            'target complete signed near/far angle and reused-speed sequence')


def compare(output, cases):
    bodies = {name: (output/(name+'.bin')).read_bytes() for name in ('target', 'target-repeat', 'source')}
    require(bodies['target'] == bodies['target-repeat'], 'independent trajectory target snapshots differ')
    rows = {name: owned.snapshots(body, cases, texture_context=True) for name, body in bodies.items()}
    mismatches, examples, actions = 0, [], Counter()
    for index, case in enumerate(cases):
        target, source = rows['target'][index], rows['source'][index]
        try:
            check_target(case, target)
        except ValueError as error:
            raise ValueError(f'case{index} {case}: {error}') from error
        actions[case['action']] += 1
        if target['raw'] != source['raw']:
            mismatches += 1
            if len(examples) < 8:
                examples.append({'profile': case, 'first_snapshot_difference': next(
                    (i for i, (a, b) in enumerate(zip(target['raw'], source['raw'])) if a != b),
                    min(len(target['raw']), len(source['raw'])))})
    return {'cases': len(cases), 'mismatches': mismatches, 'examples': examples,
            'actions': dict(actions), 'target_repeat_equal': True, 'objects_per_process': 5*len(cases),
            'input_profiles_sha256': hashlib.sha256(json.dumps(cases, sort_keys=True).encode()).hexdigest(),
            'snapshot_bytes': {name: len(body) for name, body in bodies.items()},
            'snapshot_sha256': {name: hashlib.sha256(body).hexdigest() for name, body in bodies.items()}}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--base-dir', type=Path, default=ROOT/'build/reimu-ltcg')
    parser.add_argument('--object', type=Path)
    parser.add_argument('--output-dir', type=Path, default=ROOT/'build/reimu-trajectory-returns')
    parser.add_argument('--smoke', action='store_true')
    args = parser.parse_args()
    try:
        result = shared.audit(args.base_dir, args.object or args.base_dir/'ordinary.obj', args.output_dir,
                              args.smoke, contract=sys.modules[__name__])
    except (KeyError, OSError, ValueError, subprocess.SubprocessError) as error:
        parser.exit(2, f'Reimu trajectory-return audit failed: {error}\n')
    print(json.dumps(result['comparison'], indent=2))
    return 1 if result['comparison']['mismatches'] else 0


if __name__ == '__main__':
    raise SystemExit(main())
