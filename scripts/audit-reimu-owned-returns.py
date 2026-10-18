#!/usr/bin/env python3
"""Compare complete Reimu 801 shots and 810/811/812 volleys through real managers."""
from __future__ import annotations

import argparse
import hashlib
import importlib.util
import itertools
import json
from pathlib import Path
import struct
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location('reimu_owned_native_base', ROOT/'scripts/audit-reimu-effect-returns.py')
shared = importlib.util.module_from_spec(spec)
sys.modules[spec.name] = shared
spec.loader.exec_module(shared)
HOST = ROOT/'scripts/native/reimu_owned_returns.cpp'
SCHEMA = 'th105-reimu-owned-returns-v1'
RESOURCE_FILES = ('actor-data.bin',)
SUPPORT_PATHS = (ROOT/'scripts/reimu_late_low_fixture.py', ROOT/'scripts/reimu_animation_fixture.py')
SCOPE = ('actual canonical 256-object preallocation/release, reused-slot acquisition, parameter allocation/copy, '
         'ReimuObject selection/finalizer, complete returning shots/volleys and destruction under Wine kernel32; '
         'full raw active-object/actor/parameter/MT/pool snapshots without masks; supplied untextured resources; '
         'no arbitrary-world, frame-tick gameplay, other imports, exception-path, exact or aggregate-progress claim')
ACTOR = 0x2000000
FAN_ACTIONS = (500, 501, 502, 503, 505, 506, 507, 508, 510, 511, 512, 513)


def require(condition, message):
    shared.require(condition, message)


def fan_parameters(action, level):
    if action >= 510:
        angles = ((30, 0, -30), (45, 15, -15, -45), (60, 30, 0, -30, -60))[level]
        speeds = (15,)*len(angles)
    elif action >= 505:
        angles = ((10, 0, -10), (15, 5, -5, -15), (20, 10, 0, -10, -20))[level]
        speeds = ((23, 25, 23), (25, 27, 27, 25), (26, 27, 29, 27, 26))[level]
    else:
        angles = ((20, -20), (20, 40, -20, -40), (20, 40, 60, -20, -40, -60))[level]
        speeds = (15,)*len(angles)
    return tuple((angle, speed, 0) for angle, speed in zip(angles, speeds))


def fixture(output, smoke):
    module = shared.load('owned_return_resources', 'reimu_late_low_fixture.py')
    shape = {'frame': 8, 'transition': 'unexpired', 'duration': 3}
    graph, blocks, frames, count = module.resource_graph(
        shape, (0, 410, 414, *FAN_ACTIONS, 801, 810, 811, 812), frame_capacity=14, sequence_capacity=9)
    (output/'actor-data.bin').write_bytes(graph)
    profiles = []
    facings, words, seeds = ((-1, 1), (0x27F,), (5489,)) if smoke else (
        (-128, -1, 0, 1, 127), (0x27F, 0x37F), (0, 5489))
    for action, level, facing, cw, seed in itertools.product(
            (500, 505, 510) if smoke else FAN_ACTIONS, (2,) if smoke else (0, 1, 2), facings, words, seeds):
        aerial = action in (502, 503, 507, 508, 512, 513)
        profiles.append({'action': action, 'level': level, 'node': None, 'facing': facing,
                         'cw': cw, 'seed': seed, 'sequence': 2, 'frame': 1 if aerial else 2,
                         'timer': 0, 'y': 100.0 if aerial else 0.0,
                         'object_id': 812 if action >= 510 else 811 if action >= 505 else 810,
                         'parameter_words': 3, 'objects': len(fan_parameters(action, level))*(2 if 505 <= action <= 508 else 1)})
    for action, node, facing, cw, seed in itertools.product((410, 414), (0, 1), facings, words, seeds):
        profiles.append({'action': action, 'level': 0, 'node': node, 'facing': facing, 'cw': cw, 'seed': seed,
                         'sequence': node*2, 'frame': ((8, 2) if action == 410 else (5, 1))[node],
                         'timer': -1, 'y': 0.0 if action == 410 else 100.0,
                         'object_id': 801, 'parameter_words': 4, 'objects': 1})
    require(len(profiles) == (14 if smoke else 800), 'owned fixture dimensions changed')
    with (output/'cases.bin').open('wb') as stream:
        stream.write(b'TH105OB1'+struct.pack('<I', len(profiles)))
        for profile in profiles:
            action, sequence, frame = (profile[key] for key in ('action', 'sequence', 'frame'))
            actor = bytearray(0x3000)
            frame_base = frames[action]+sequence*0x800
            fields = ((0, 'I', 0x6C412C), (0xEC, 'f', 640.0), (0xF0, 'f', profile['y']),
                      (0x104, 'b', profile['facing']), (0x130, 'I', module.VECTOR),
                      (0x13C, 'h', action), (0x13E, 'h', sequence), (0x140, 'h', frame),
                      (0x142, 'h', profile['timer']), (0x144, 'i', 5), (0x148, 'h', count),
                      (0x14C, 'h', 3), (0x150, 'I', frame_base), (0x158, 'I', frame_base+frame*0x88),
                      (0x15C, 'I', blocks[action]+sequence*0x20), (0x160, 'I', module.TREE),
                      (0x164, 'I', module.RESOURCE+0xD00), (0x170, 'I', ACTOR+0x2000),
                      (0x174, 'h', 1), (0x47E, 'B', 1), (0x490, 'B', 1), (0x4D0, 'f', 1.25),
                      (0x6C0, 'i', 1), (0x6C4, 'i', 1), (0x736, 'h', profile['level']),
                      (0x20EC, 'f', 800.0), (0x20F0, 'f', 200.0))
            for offset, fmt, value in fields:
                struct.pack_into('<'+fmt, actor, offset, value)
            stream.write(struct.pack('<IIIII', *(profile[key] for key in
                         ('seed', 'cw', 'objects', 'object_id', 'parameter_words')))+actor)
    return profiles


def expected_status(profiles):
    return {'objects': sum(profile['objects'] for profile in profiles)}


def snapshots(body, profiles, *, texture_context=False):
    require(len(body) >= 4 and struct.unpack_from('<I', body)[0] == len(profiles), 'owned output count')
    cursor, rows = 4, []
    for profile in profiles:
        start = cursor
        fixed_size = 6612+(0xE0 if texture_context else 0)
        require(cursor+fixed_size <= len(body), 'truncated owned record')
        objects, cw, generation, free = struct.unpack_from('<IIII', body, cursor)
        actor = body[cursor+16:cursor+16+0x1000]
        texture = body[cursor+6612:cursor+fixed_size]
        cursor += fixed_size
        children = []
        for _ in range(objects):
            require(cursor+12+0x388 <= len(body), 'truncated object record')
            address, allocation, words = struct.unpack_from('<III', body, cursor)
            require(words <= 1024 and allocation == words*4 and cursor+12+0x388+words*4 <= len(body),
                    'object parameter extent')
            object_bytes = body[cursor+12:cursor+12+0x388]
            parameters = body[cursor+12+0x388:cursor+12+0x388+words*4]
            cursor += 12+0x388+words*4
            require(cursor+4 <= len(body), 'truncated child deque count')
            child_count, = struct.unpack_from('<I', body, cursor)
            cursor += 4
            require(child_count <= 256 and cursor+child_count*4 <= len(body), 'child deque extent')
            child_links = struct.unpack_from('<'+'I'*child_count, body, cursor)
            cursor += child_count*4
            children.append({'address': address, 'allocation': allocation, 'bytes': object_bytes,
                             'parameters': parameters, 'words': words, 'children': child_links})
        rows.append({'raw': body[start:cursor], 'actor': actor, 'objects': children,
                     'cw': cw, 'generation': generation, 'free': free, 'texture': texture})
    require(cursor == len(body), 'trailing owned output bytes')
    return rows


def compare(output, profiles):
    bodies = {name: (output/(name+'.bin')).read_bytes() for name in ('target', 'target-repeat', 'source')}
    require(bodies['target'] == bodies['target-repeat'], 'independent owned target snapshots differ')
    rows = {name: snapshots(body, profiles) for name, body in bodies.items()}
    mismatches, examples = 0, []
    for index, profile in enumerate(profiles):
        target, source = (rows[name][index] for name in ('target', 'source'))
        actor = target['actor']
        sequence, frame, timer, counter = struct.unpack_from('<hhhi', actor, 0x13E)
        require((sequence, frame, timer, counter) == (profile['sequence'], profile['frame'], profile['timer']+1, 6)
                and struct.unpack_from('<I', actor, 0x180)[0] == 1,
                'target bypassed post-request frame/state continuation')
        require(len(target['objects']) == profile['objects'] and target['generation'] == 256+profile['objects']
                and target['free'] == 256-profile['objects'], 'target complete volley/pool counters')
        require(target['cw'] == (0x8001F | (0x10000 if profile['cw'] == 0x27F else 0)), 'target FP control')
        for j, child in enumerate(target['objects']):
            companion = profile['object_id'] == 811 and j % 2 == 1
            expected_parent = target['objects'][j-1]['address'] if companion else 0
            expected_children = ((target['objects'][j+1]['address'],)
                                 if profile['object_id'] == 811 and not companion else ())
            require(struct.unpack_from('<I', child['bytes'], 0x34C)[0] == expected_parent
                    and child['children'] == expected_children
                    and struct.unpack_from('<H', child['bytes'], 0x13C)[0] == profile['object_id']
                    and struct.unpack_from('<I', child['bytes'], 0x334)[0] == ((257+j)<<16 | (255-j))
                    and struct.unpack_from('<I', child['bytes'], 0x330)[0] == 1,
                    'target complete owned-object identity/topology')
        if profile['node'] is None:
            parameters = fan_parameters(profile['action'], profile['level'])
            if profile['object_id'] == 811:
                parameters = tuple(child for values in parameters for child in (values, (values[0], 0, 1)))
        else:
            angle = struct.unpack_from('<h', actor, 0x734)[0]
            require(-10 <= angle <= 10, 'target aiming clamp')
            parameters = ((float(angle), 10.0, 1.0, float(profile['node'])),)
        require([child['parameters'] for child in target['objects']] ==
                [struct.pack('<'+'f'*len(values), *values) for values in parameters],
                'target complete copied-parameter sequence')
        if target['raw'] != source['raw']:
            mismatches += 1
            if len(examples) < 8:
                examples.append({'profile': profile, 'first_snapshot_difference': next(
                    i for i, (a, b) in enumerate(zip(target['raw'], source['raw'])) if a != b)})
    return {'cases': len(profiles), 'mismatches': mismatches, 'examples': examples,
            'target_repeat_equal': True, 'objects_per_process': expected_status(profiles)['objects'],
            'snapshot_bytes': {name: len(body) for name, body in bodies.items()},
            'snapshot_sha256': {name: hashlib.sha256(body).hexdigest() for name, body in bodies.items()}}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--base-dir', type=Path, default=ROOT/'build/reimu-ltcg')
    parser.add_argument('--object', type=Path, help='qualified private source control; default is the base ordinary object')
    parser.add_argument('--output-dir', type=Path, default=ROOT/'build/reimu-owned-returns')
    parser.add_argument('--smoke', action='store_true')
    args = parser.parse_args()
    try:
        result = shared.audit(args.base_dir, args.object or args.base_dir/'ordinary.obj', args.output_dir,
                              args.smoke, contract=sys.modules[__name__])
    except (KeyError, OSError, ValueError, subprocess.SubprocessError) as error:
        parser.exit(2, f'Reimu owned-return audit failed: {error}\n')
    print(json.dumps(result['comparison'], indent=2))
    return 1 if result['comparison']['mismatches'] else 0


if __name__ == '__main__':
    raise SystemExit(main())
