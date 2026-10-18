#!/usr/bin/env python3
"""Compare returning Reimu821 fans,822 rings/grids and869 radial requests."""
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
spec = importlib.util.spec_from_file_location('circular_owned_native', ROOT/'scripts/audit-reimu-owned-returns.py')
owned = importlib.util.module_from_spec(spec)
sys.modules[spec.name] = owned
spec.loader.exec_module(owned)
shared = owned.shared
HOST = owned.HOST
SCHEMA = 'th105-reimu-circular-returns-v1'
RESOURCE_FILES = owned.RESOURCE_FILES
SUPPORT_PATHS = (*owned.SUPPORT_PATHS, Path(owned.__file__))
SCOPE = ('complete real returning821/822/869 requests, actual preallocated manager and callbacks; '
         'raw actor/object/copied-array/child/MT/pool/texture-publication snapshots without masks; '
         'read-only untextured animation/texture-ID data and writable publication prefix; '
         'no rendering, arbitrary-world/heap/resource, exception-path, exact or aggregate-progress claim')
COHORTS = ('fan821', 'ring822', 'rays869')
SELECTED_COHORTS = COHORTS
RESOURCE_KEYS = (0, 545, 546, 550, 551, 669, 821, 822, 869)


def require(condition, message):
    shared.require(condition, message)


def profiles(smoke):
    facing, words, seeds = ((1,), (0x27F,), (5489,)) if smoke else (
        (-128, -1, 0, 1, 127), (0x27F, 0x37F), (0, 5489))
    if 'fan821' in SELECTED_COHORTS:
        variants = ((3, 4, 100.0),) if smoke else (
            (2, 3, 100.0), (2, 4, 330.0), (3, 3, 100.0),
            (3, 4, 100.0), (3, -128, 33554432.0), (3, 127, 100.0))
        for action, (sequence, skill, height), direction, cw, seed in itertools.product(
                (545, 546), variants, facing, words, seeds):
            yield dict(cohort='fan821', action=action, sequence=sequence, skill=skill, y=height,
                       counter=-1, timer=-1, duration=32, phase=5.0, texture=(0, 0),
                       facing=direction, cw=cw, seed=seed, object_id=821, parameter_words=3,
                       objects=1 if sequence == 2 else 12 if skill >= 4 else 7)
    if 'ring822' in SELECTED_COHORTS:
        variants = ((0, 32, False),) if smoke else (
            (0, 32, False), (3, 32, False), (-3, 32, False), (9, 32, False),
            (12, 32, False), (0, 3, False), (3, 3, False), (9, 3, False),
            (3, 4, True), (9, 4, True))
        for action, (timer, duration, transition), direction, cw, seed in itertools.product(
                (550, 551), variants, facing, words, seeds):
            yield dict(cohort='ring822', action=action, sequence=1, skill=4, y=100.0,
                       counter=5, timer=timer, duration=duration, transition=transition,
                       phase=5.0, texture=(0, 0),
                       facing=direction, cw=cw, seed=seed, object_id=822, parameter_words=4,
                       objects=(8 if timer % 3 == 0 and timer <= 9 else 0)+(25 if timer == 0 else 0))
    if 'rays869' in SELECTED_COHORTS:
        counters = (0,) if smoke else (0, 2, 8, 10, 180)
        geometry = ((5.0, 100.0),) if smoke else ((0.0, 100.0), (359.75, 33554432.0))
        textures = ((0, 0),) if smoke else ((0, 0), (1, 0), (0, 1))
        for counter, (phase, height), texture, direction, cw, seed in itertools.product(
                counters, geometry, textures, facing, words, seeds):
            yield dict(cohort='rays869', action=669, sequence=1, skill=4, y=height,
                       counter=counter, timer=0, duration=32, phase=phase, texture=texture,
                       facing=direction, cw=cw, seed=seed, object_id=869, parameter_words=3,
                       objects=(7 if counter % 2 == 0 else 0)+(counter % 8 == 0)+(counter % 10 == 0))
        if not smoke:
            for counter, cw in itertools.product((181, 240), (0x27F, 0x37F)):
                yield dict(cohort='rays869', action=669, sequence=1, skill=4, y=100.0,
                           counter=counter, timer=0, duration=32, phase=5.0, texture=(0, 0),
                           facing=1, cw=cw, seed=5489, object_id=869, parameter_words=3, objects=0)


def resource_image(duration, offset, transition, *, keys=RESOURCE_KEYS):
    module = shared.load('circular_resources_'+str(duration), 'reimu_late_low_fixture.py')
    for name in ('RESOURCE', 'TREE', 'HEAD', 'VECTOR', 'SLOT'):
        setattr(module, name, getattr(module, name)+offset)
    graph, blocks, frames, count = module.resource_graph(
        {'frame': 0, 'transition': 'unexpired', 'duration': duration}, keys,
        frame_capacity=14, sequence_capacity=9)
    require(len(graph) == 0x40000, 'circular resource envelope changed')
    graph = bytearray(graph)
    base = module.RESOURCE
    if transition:
        for action in (550, 551):
            graph[blocks[action]+0x20+0x14-base] = 0
    struct.pack_into('<8I', graph, 0xC00, base+0xC40, base+0xC60, 0, 0, 0, 0, 0, 0)
    struct.pack_into('<4I', graph, 0xC40, *(0xA1000000+i for i in range(4)))
    struct.pack_into('<4I', graph, 0xC60, *(0xA1000004+i for i in range(4)))
    return graph, module, blocks, frames, count


def fixture(output, smoke, *, cases=None, keys=RESOURCE_KEYS):
    data, layouts = bytearray(), {}
    for duration, transition, offset in ((32, False, 0), (3, False, 0x40000), (4, True, 0x80000)):
        graph, *layout = resource_image(duration, offset, transition, keys=keys)
        data.extend(graph);layouts[duration, transition] = layout
    (output/'actor-data.bin').write_bytes(data)
    cases = list(profiles(smoke) if cases is None else cases)
    with (output/'cases.bin').open('wb') as stream:
        stream.write(b'TH105OB2'+struct.pack('<I', len(cases)))
        for case in cases:
            module, blocks, frames, count = layouts[case['duration'], case.get('transition', False)]
            actor = bytearray(0x3000)
            frame = frames[case['action']]+case['sequence']*0x800
            fields = ((0, 'I', 0x6C412C), (0xEC, 'f', case.get('x', 640.0)), (0xF0, 'f', case['y']),
                      (0x104, 'b', case['facing']), (0x113, 'B', 255),
                      (0x11C, 'f', 1.0), (0x120, 'f', 1.0), (0x130, 'I', module.VECTOR),
                      (0x13C, 'h', case['action']), (0x13E, 'h', case['sequence']), (0x140, 'h', 0),
                      (0x142, 'h', case['timer']), (0x144, 'i', case['counter']), (0x148, 'h', count),
                      (0x14C, 'h', case['duration']), (0x150, 'I', frame), (0x158, 'I', frame),
                      (0x15C, 'I', blocks[case['action']]+case['sequence']*0x20),
                      (0x160, 'I', module.TREE), (0x164, 'I', module.RESOURCE+0xD00),
                      (0x170, 'I', owned.ACTOR+0x2000), (0x174, 'h', 1), (0x47E, 'B', 1),
                      (0x490, 'B', 1), (0x4D0, 'f', 1.25), (0x60A, 'b', case['skill']),
                      (0x690, 'I', module.RESOURCE+0xC00), (0x694, 'I', 8), (0x69C, 'I', 8),
                      (0x6A0, 'h', case['texture'][0]), (0x6C0, 'i', 1), (0x6C4, 'i', 1),
                      (0x73C, 'f', case['phase']), (0x2000, 'I', 0x6C412C),
                      (0x20EC, 'f', 800.0), (0x20F0, 'f', 200.0), (0x2174, 'h', 1),
                      (0x26A0, 'h', case['texture'][1]))
            for offset, fmt, value in fields:
                struct.pack_into('<'+fmt, actor, offset, value)
            stream.write(struct.pack('<IIIII', *(case[key] for key in
                         ('seed', 'cw', 'objects', 'object_id', 'parameter_words')))+actor)
    return cases


def expected_status(cases):
    return {'objects': sum(case['objects'] for case in cases), 'texture_context': True}


def expected_parameters(case):
    if case['cohort'] == 'fan821':
        if case['sequence'] == 2:
            return [(0.0, 0.0, 3.0)]
        result = []
        for i in range(6):
            if case['skill'] >= 4 and i <= 4:
                result.append((35.5-i*9.0 if case['action'] == 546 else i*9.0+34.5, 22.0, 0.0))
            result.append((40.0-i*9.0 if case['action'] == 546 else i*9.0+30.0, 25.0, 0.0))
        return result+[(0.0, 0.0, 4.0)]
    if case['cohort'] == 'ring822':
        # Random angles are observed from the target; no substitute RNG formula.
        return None
    if case['counter'] > 180:
        return []
    result = []
    if case['counter'] % 2 == 0:
        result += [(i*120.0+case['phase'], 30.0, 3.0) for i in range(3)]
        result += [(i*90.0-case['phase'], 30.0, 3.0) for i in range(4)]
    if case['counter'] % 8 == 0:
        result.append((0.0, 0.0, 4.0))
    if case['counter'] % 10 == 0:
        result.append(None)
    return result


def check_target(case, row):
    actor = row['actor']
    node = struct.unpack_from('<hhhi', actor, 0x13E)
    if case['cohort'] == 'rays869' and case['counter'] >= 240:
        expected_node = (2, 0, 0, 0)
        require(actor[0x100:0x104] == struct.pack('<f', 0.2), 'target cutoff acceleration')
    elif case['timer']+1 >= case['duration']:
        expected_node = ((case['sequence']+1, 0, 0, 0) if case.get('transition', False)
                         else (case['sequence'], 0, 0, case['counter']+1))
    else:
        expected_node = (case['sequence'], 0, case['timer']+1, case['counter']+1)
    require(node == expected_node, 'target post-request animation/cutoff continuation')
    if case.get('transition', False):
        require(struct.unpack_from('<ff', actor, 0xF4) == (-200.0, 2.0)
                and struct.unpack_from('<f', actor, 0xF0)[0] == case['y']+100.0
                and struct.unpack_from('<f', actor, 0x100)[0] == 0.5 and actor[0x113] == 0,
                'target returning ring-to-airborne continuation')
    require(len(row['objects']) == case['objects'] and row['generation'] == 256+case['objects']
            and row['free'] == 256-case['objects'], 'target complete circular pool accounting')
    require(row['cw'] == (0x8001F | (0x10000 if case['cw'] == 0x27F else 0)), 'target FP control')
    publication = struct.unpack_from('<II', row['texture'], 0xD8)
    if case['cohort'] == 'rays869':
        require(publication == (0xA1000006, 0x55667788 if any(case['texture']) else 0xA1000006)
                and actor[0x6A2] == 6
                and struct.unpack_from('<h', actor, 0x6A0)[0] == 2,
                'target real texture publication/deque/duration path')
        phase = case['phase']+(4.0 if case['counter'] <= 180 and case['counter'] % 2 == 0 else 0.0)
        require(actor[0x73C:0x740] == struct.pack('<f', phase), 'target post-volley radial phase')
    else:
        require(publication == (0x11223344, 0x55667788), 'unexpected texture publication')
    values = []
    for child in row['objects']:
        object_bytes = child['bytes']
        require(struct.unpack_from('<H', object_bytes, 0x13C)[0] in RESOURCE_KEYS,
                'target callback needs another resource action')
        require(struct.unpack_from('<H', object_bytes, 0x13C)[0] == case['object_id']
                and child['words'] == case['parameter_words'] and child['children'] == ()
                and struct.unpack_from('<I', object_bytes, 0x34C)[0] == 0,
                'target circular object identity/parameter/topology')
        values.append(struct.unpack('<'+'f'*child['words'], child['parameters']))
    if case['cohort'] == 'ring822':
        ring_count = 8 if case['timer'] % 3 == 0 and case['timer'] <= 9 else 0
        for i, value in enumerate(values[:ring_count]):
            require(i*45.0 <= value[0] < i*45.0+45.0 and value[1:] == (0.0, 4.0, 0.0),
                    'target complete random ring parameters')
        grid = [(sector*72.0+72.0, layer*18.0+8.0, 0.0, layer+30.0)
                for sector in range(5) for layer in range(5)] if case['timer'] == 0 else []
        require(values[ring_count:] == grid, 'target complete five-by-five grid parameters')
    else:
        expected = expected_parameters(case)
        require(len(values) == len(expected), 'target circular request count')
        for value, wanted in zip(values, expected):
            require((value[1:] == (0.0, 5.0) and 0.0 <= value[0] < 360.0) if wanted is None else value == wanted,
                    'target complete circular parameter sequence')


def compare(output, cases):
    bodies = {name: (output/(name+'.bin')).read_bytes() for name in ('target', 'target-repeat', 'source')}
    require(bodies['target'] == bodies['target-repeat'], 'repeated circular target snapshots differ')
    rows = {name: owned.snapshots(body, cases, texture_context=True) for name, body in bodies.items()}
    mismatches, examples, cohorts = 0, [], Counter()
    for index, case in enumerate(cases):
        target, source = rows['target'][index], rows['source'][index]
        try:
            check_target(case, target)
        except ValueError as error:
            raise ValueError(f'case{index} {case}: {error}') from error
        cohorts[case['cohort']] += 1
        if target['raw'] != source['raw']:
            mismatches += 1
            if len(examples) < 8:
                examples.append({'profile': case, 'first_snapshot_difference': next(
                    (i for i, (a, b) in enumerate(zip(target['raw'], source['raw'])) if a != b),
                    min(len(target['raw']), len(source['raw'])))})
    return {'cases': len(cases), 'mismatches': mismatches, 'examples': examples,
            'cohorts': dict(cohorts), 'target_repeat_equal': True, 'objects_per_process': expected_status(cases)['objects'],
            'snapshot_bytes': {name: len(body) for name, body in bodies.items()},
            'snapshot_sha256': {name: hashlib.sha256(body).hexdigest() for name, body in bodies.items()}}


def main():
    global SELECTED_COHORTS
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--base-dir', type=Path, default=ROOT/'build/reimu-ltcg')
    parser.add_argument('--object', type=Path)
    parser.add_argument('--output-dir', type=Path, default=ROOT/'build/reimu-circular-returns')
    parser.add_argument('--cohort', action='append', choices=COHORTS)
    parser.add_argument('--smoke', action='store_true')
    args = parser.parse_args()
    SELECTED_COHORTS = tuple(dict.fromkeys(args.cohort or COHORTS))
    try:
        result = shared.audit(args.base_dir, args.object or args.base_dir/'ordinary.obj', args.output_dir,
                              args.smoke, contract=sys.modules[__name__])
    except (KeyError, OSError, ValueError, subprocess.SubprocessError) as error:
        parser.exit(2, f'Reimu circular-return audit failed: {error}\n')
    print(json.dumps(result['comparison'], indent=2))
    return 1 if result['comparison']['mismatches'] else 0


if __name__ == '__main__':
    raise SystemExit(main())
