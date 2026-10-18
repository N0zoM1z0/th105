#!/usr/bin/env python3
"""Compare real effect62 creation, virtual-next callbacks and Reimu root RET."""
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
spec = importlib.util.spec_from_file_location('shot_effect_return_base', ROOT/'scripts/audit-reimu-effect-returns.py')
shared = importlib.util.module_from_spec(spec)
sys.modules[spec.name] = shared
spec.loader.exec_module(shared)
HOST, RESOURCE_FILES, RECORD_SIZE = shared.HOST, shared.RESOURCE_FILES, shared.RECORD_SIZE
SUPPORT_PATHS = shared.SUPPORT_PATHS
COMPILE_DEFINES = ('TH105_EFFECT_ACTION=62',)
SCHEMA = 'th105-reimu-shot-effect-returns-v1'
SCOPE = ('410/414/416 effect62 creation and actual virtual-next/root RET; real canonical '
         'CRT/locks/manager/callback/destruction with Wine kernel32 only; complete raw '
         'actor/effect/MT/count/FP snapshots and checked pool slot/generation; supplied read-only untextured data; '
         'no arbitrary-world, later effect ticks, exceptions or exact claim')
expected_status = shared.expected_status


def fixture(output, smoke):
    actor = shared.load('shot_effect_actor_fixture', 'reimu_animation_fixture.py')
    shape = {'frame': 6, 'transition': 'unexpired', 'duration': 32}
    graph, blocks, frames, count = actor.resource_graph(
        shape, (0, 9, 410, 414, 416), linked_terminal=True, frame_capacity=7)
    shared.require(not any(graph[0x10000:]), 'shot actor data exceeds the reviewed native mapping')
    (output/'actor-data.bin').write_bytes(graph[:0x10000])
    effect = shared.load('shot_effect_object_fixture', 'reimu_animation_fixture.py')
    for name in ('RESOURCE', 'TREE', 'HEAD', 'VECTOR', 'SLOT'):
        setattr(effect, name, getattr(effect, name)+0x200000)
    graph, *_ = effect.resource_graph(
        {'frame': 0, 'transition': 'unexpired', 'duration': 3}, (0, 62), linked_terminal=True)
    (output/'effect-data.bin').write_bytes(graph)
    profiles = list(itertools.product(
        (410, 414, 416), (-1, 1) if smoke else (-128, -1, 0, 1, 127),
        (640.0,) if smoke else (640.0, 33554432.0), (0x27F, 0x37F)))
    with (output/'cases.bin').open('wb') as stream:
        stream.write(b'TH105FX1'+struct.pack('<I', len(profiles)))
        for action, facing, x, cw in profiles:
            frame = {410: 6, 414: 4, 416: 3}[action]
            data = bytearray(0x3000)
            fields = ((0, 'I', 0x6C412C), (0xEC, 'f', x), (0xF0, 'f', 0.0 if action == 410 else 100.0),
                      (0xF4, 'f', 3.0), (0xF8, 'f', 0.0), (0x100, 'f', 0.0),
                      (0x104, 'b', facing), (0x130, 'I', actor.VECTOR), (0x13C, 'h', action),
                      (0x13E, 'h', 0), (0x140, 'h', frame), (0x142, 'h', -1), (0x144, 'i', 7),
                      (0x148, 'h', count), (0x14C, 'h', 32), (0x150, 'I', frames[action]),
                      (0x158, 'I', frames[action]+frame*0x88), (0x15C, 'I', blocks[action]),
                      (0x160, 'I', actor.TREE), (0x170, 'I', shared.ACTOR+0x2000),
                      (0x174, 'h', 1), (0x47E, 'B', 1), (0x490, 'B', 1),
                      (0x6C4, 'i', 1), (0x750, 'B', 1), (0x7A4, 'h', 1))
            for offset, fmt, value in fields:
                struct.pack_into('<'+fmt, data, offset, value)
            stream.write(struct.pack('<II', 5489, cw)+data)
    return profiles


def compare(output, profiles):
    bodies = {name: (output/(name+'.bin')).read_bytes() for name in ('target', 'target-repeat', 'source')}
    shared.require(bodies['target'] == bodies['target-repeat'], 'independent effect62 target snapshots differ')
    for name, body in bodies.items():
        shared.require(len(body) == 4+len(profiles)*RECORD_SIZE
                       and struct.unpack_from('<I', body)[0] == len(profiles), name+' snapshot schema/length')
    mismatches, examples = 0, []
    for index, (action, facing, x, cw) in enumerate(profiles):
        offset = 4+index*RECORD_SIZE
        target, source = (bodies[name][offset:offset+RECORD_SIZE] for name in ('target', 'source'))
        shared.require(struct.unpack_from('<hhhi', target, 0x13E) == (1, 0, 0, 0)
                       and struct.unpack_from('<h', target, 0x13C)[0] == action,
                       'target bypassed its real post-effect virtual-next return')
        child = target[0x1000:0x1178]
        dx, dy = {410: (67, 57.0), 414: (62, 108.0), 416: (14, 197.0)}[action]
        shared.require(struct.unpack_from('<h', child, 0x13C)[0] == 62
                       and child[0xEC:0xF4] == struct.pack('<ff', x+facing*dx, dy+(0.0 if action == 410 else 100.0))
                       and child[0x104] == facing & 255,
                       'target effect62 identity/position/direction')
        shared.require(struct.unpack_from('<II', target, RECORD_SIZE-8)
                       == (1, 0x8001F | (0x10000 if cw == 0x27F else 0)), 'target effect count/FP control')
        if target != source:
            mismatches += 1
            if len(examples) < 8:
                examples.append({'profile': profiles[index], 'first_snapshot_difference': next(
                    i for i, (a, b) in enumerate(zip(target, source)) if a != b)})
    return {'cases': len(profiles), 'mismatches': mismatches, 'examples': examples,
            'target_repeat_equal': True, 'snapshot_bytes_per_case': RECORD_SIZE,
            'input_profiles_sha256': hashlib.sha256(json.dumps(profiles).encode()).hexdigest(),
            'snapshot_sha256': {name: hashlib.sha256(body).hexdigest() for name, body in bodies.items()}}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--base-dir', type=Path, default=ROOT/'build/reimu-ltcg')
    parser.add_argument('--object', type=Path)
    parser.add_argument('--output-dir', type=Path, default=ROOT/'build/reimu-shot-effect-returns')
    parser.add_argument('--smoke', action='store_true')
    args = parser.parse_args()
    try:
        result = shared.audit(args.base_dir, args.object or args.base_dir/'ordinary.obj', args.output_dir,
                              args.smoke, contract=sys.modules[__name__])
    except (KeyError, OSError, ValueError, subprocess.SubprocessError) as error:
        parser.exit(2, f'Reimu shot-effect-return audit failed: {error}\n')
    print(json.dumps(result['comparison'], indent=2))
    return 1 if result['comparison']['mismatches'] else 0


if __name__ == '__main__':
    raise SystemExit(main())
