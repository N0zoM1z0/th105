#!/usr/bin/env python3
"""Compare Reimu effect123 continuations using actual target code and Wine APIs.

The partial PE loader resolves kernel32 only; every other import fails closed.
No game callback, allocator, lock, effect result or instruction is substituted.
"""
from __future__ import annotations

import argparse
import hashlib
import importlib.util
import itertools
import json
import os
from pathlib import Path
import resource
import struct
import subprocess
import sys

import pefile

import linked_pe

ROOT = Path(__file__).resolve().parents[1]
HOST = ROOT/'scripts/native/reimu_effect_returns.cpp'
ACTOR, CANDIDATE = 0x2000000, 0x4000000
RECORD_SIZE = 0x1000+0x178+4+2496+8
SCHEMA = 'th105-reimu-effect-returns-v1'
RESOURCE_FILES = ('effect-data.bin', 'actor-data.bin')
SUPPORT_PATHS = (ROOT/'scripts/reimu_animation_fixture.py',)
SCOPE = ('single-thread Wine kernel32 backend; real canonical CRT, locks, manager, effect123 '
         'creation/finalizer/destruction and root RET; full raw snapshots without masks; '
         'supplied untextured resources, no game startup, other imports blocked; '
         'no owned-object, arbitrary-world, exception-path, exact or aggregate-progress claim')

def expected_status(profiles):
    return {}


def require(condition, message):
    if not condition:
        raise ValueError(message)


def load(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT/'scripts'/filename)
    module = importlib.util.module_from_spec(spec)
    sys.modules[name] = module
    spec.loader.exec_module(module)
    return module


def windows(path):
    return 'Z:'+str(path.resolve()).replace('/', '\\')


def fixture(output, smoke):
    module = load('effect_return_actor_fixture', 'reimu_animation_fixture.py')
    shape = {'frame': 0, 'transition': 'unexpired', 'duration': 3}
    actions = (208, 211, 220, 221, 222)
    graph, blocks, frames, count = module.resource_graph(shape, (0, *actions), linked_terminal=True)
    (output/'actor-data.bin').write_bytes(graph)
    effect = load('effect_return_effect_fixture', 'reimu_animation_fixture.py')
    for name in ('RESOURCE', 'TREE', 'HEAD', 'VECTOR', 'SLOT'):
        setattr(effect, name, getattr(effect, name)+0x200000)
    graph, *_ = effect.resource_graph(shape, (0, 123), linked_terminal=True)
    (output/'effect-data.bin').write_bytes(graph)
    profiles = list(itertools.product(actions, (-1, 1) if smoke else (-128, -1, 0, 1, 127),
                                     (2.5, 20.0), (640.0,) if smoke else (-0.0, 640.0, 33554432.0),
                                     (5489,) if smoke else (0, 5489), (0x27F, 0x37F)))
    with (output/'cases.bin').open('wb') as stream:
        stream.write(b'TH105FX1'+struct.pack('<I', len(profiles)))
        for action, facing, velocity, position, seed, cw in profiles:
            actor = bytearray(0x3000)
            fields = ((0, 'I', 0x6C412C), (0xEC, 'f', position), (0xF0, 'f', 100.0),
                      (0xF4, 'f', 3.0), (0xF8, 'f', velocity), (0x100, 'f', 0.65),
                      (0x104, 'b', facing), (0x130, 'I', module.VECTOR), (0x13C, 'h', action),
                      (0x13E, 'h', 1), (0x140, 'h', 0), (0x142, 'h', 0), (0x144, 'i', 5),
                      (0x148, 'h', count), (0x14C, 'h', 3), (0x150, 'I', frames[action]+0x200),
                      (0x158, 'I', frames[action]+0x200), (0x15C, 'I', blocks[action]+0x20),
                      (0x160, 'I', module.TREE), (0x170, 'I', ACTOR+0x2000),
                      (0x174, 'h', 1), (0x47E, 'B', 1), (0x490, 'B', 1))
            for offset, fmt, value in fields:
                struct.pack_into('<'+fmt, actor, offset, value)
            stream.write(struct.pack('<II', seed, cw)+actor)
    return profiles


def compare(output, profiles):
    bodies = {name: (output/(name+'.bin')).read_bytes() for name in ('target', 'target-repeat', 'source')}
    require(bodies['target'] == bodies['target-repeat'], 'repeated target snapshots differ')
    for name, body in bodies.items():
        require(len(body) == 4+len(profiles)*RECORD_SIZE
                and struct.unpack_from('<I', body)[0] == len(profiles), name+' snapshot schema/length')
    mismatches, examples = 0, []
    for index, profile in enumerate(profiles):
        action, facing, velocity, position, seed, cw = profile
        offset = 4+index*RECORD_SIZE
        target, source = (bodies[name][offset:offset+RECORD_SIZE] for name in ('target', 'source'))
        sequence, frame, timer, counter = struct.unpack_from('<hhhi', target, 0x13E)
        continued = action != 211 and velocity == 2.5
        require(sequence == (2 if continued else 1) and frame == 0 and timer == 1
                and counter == (1 if continued else 6), 'target bypassed advertised post-effect continuation')
        require(struct.unpack_from('<II', target, RECORD_SIZE-8) == (1, 0x8001F | (0x10000 if cw == 0x27F else 0)), 'target effect count/control word')
        if target != source:
            mismatches += 1
            if len(examples) < 8:
                examples.append({'profile': profile, 'first_snapshot_difference': next(
                    i for i, (a, b) in enumerate(zip(target, source)) if a != b)})
    return {'cases': len(profiles), 'mismatches': mismatches, 'examples': examples,
            'target_repeat_equal': True, 'snapshot_bytes_per_case': RECORD_SIZE,
            'snapshot_sha256': {name: hashlib.sha256(body).hexdigest() for name, body in bodies.items()}}


def audit(base, object_path, output, smoke, *, contract=None):
    contract = contract or sys.modules[__name__]
    host = contract.HOST
    base, object_path, output = base.resolve(), object_path.resolve(), output.resolve()
    build = ROOT/'build'
    require(output.is_relative_to(build) and output != build
            and not output.is_relative_to(base) and not base.is_relative_to(output),
            'output must be a separate subdirectory of build/')
    require(not os.environ.get('CL') and not os.environ.get('_CL_'), 'ambient compiler flags are unsupported')
    target = linked_pe.comparator()
    target_sha = target.verify_target()
    base_auditor = load('effect_return_base', 'audit-reimu-linked-coff.py')
    base_proof = base_auditor.audit(base/'receipt.json')
    stack = load('effect_return_stack', 'audit-reimu-root-stack.py')
    contracts = stack.audit(object_path, stack.SUPPORTED_ACTIONS)
    require(not contracts['callable_excess'] and not contracts['metadata_envelope_excess'],
            'selected object exceeds the reviewed callable/metadata windows')
    require(not contracts['buffer_partition_mismatches'] and not contracts['request_preparation_mismatches'],
            'selected object fails root stack/request contracts')
    relocations = stack.load('effect_return_relocations', 'audit-reimu-root-relocations.py')
    mapper = relocations.load('effect_return_coff', 'compare-giant-action-switches.py')
    obj = mapper.CoffObject(object_path, symbol_base=relocations.SYMBOL)
    bindings = relocations.load_bindings(relocations.DEFAULT_BINDINGS)
    data = dict(target.known_data_targets())
    for table in ('root_literals', 'pool_literals'):
        for bits, address in bindings[table].items():
            data['__real@'+bits] = (int(address, 0), bytes.fromhex(bits)[::-1], frozenset({0}), 'literal')
    candidate = target.coff_symbol_bytes(object_path, relocations.SYMBOL, CANDIDATE, len(obj.text),
                                         {key: int(value, 0) for key, value in bindings['rel32'].items()}, data, {})
    output.mkdir(parents=True, exist_ok=True)
    (output/'candidate.bin').write_bytes(candidate)
    profiles = contract.fixture(output, smoke)
    tools, pins = linked_pe.pinned_tools()
    normal = json.loads((base/'gpt-web-angle-atan2-natural.compile-receipt.json').read_text())
    command = [('/Fo'+windows(output/'host.obj') if arg.startswith('/Fo') else arg)
               for arg in normal['inputs']['command']]
    command[-1] = windows(host)
    environment = {**os.environ, 'WINEPREFIX': os.environ.get('TH105_WINEPREFIX', str(ROOT/'.tools/wine-msvc8')),
                   'WINEARCH': 'win32', 'WINEDEBUG': '-all', 'WINEPRELOADRESERVE': '00400000-00706000'}
    link = ['wine', str(tools/'bin/link.exe'), '/NOLOGO', '/SUBSYSTEM:CONSOLE', '/BASE:0x10000000',
            '/FIXED', '/OUT:'+windows(output/'host.exe'), '/LIBPATH:'+windows(tools/'lib'),
            '/LIBPATH:'+windows(tools/'PlatformSDK/Lib'), windows(output/'host.obj'), 'kernel32.lib']
    inputs = (Path(__file__), Path(contract.__file__), host, host.with_name('reimu_native_host.hpp'),
              object_path, base/'receipt.json', ROOT/'resources/th105.exe',
              *contract.SUPPORT_PATHS, tools/'lib/libcmt.lib',
              tools/'PlatformSDK/Lib/Kernel32.Lib')
    input_hashes = {str(path): linked_pe.sha(path) for path in inputs}
    for name, arguments in (('compile', command), ('link', link)):
        with (output/(name+'.log')).open('w') as log:
            subprocess.run(arguments, cwd=ROOT, env=environment, stdout=log,
                           stderr=subprocess.STDOUT, check=True, timeout=60)
    imports = pefile.PE(str(ROOT/'resources/th105.exe')).DIRECTORY_ENTRY_IMPORT
    kernel_count = sum(len(row.imports) for row in imports if row.dll.lower() == b'kernel32.dll')
    blocked_count = sum(len(row.imports) for row in imports if row.dll.lower() != b'kernel32.dll')
    native_inputs = ('host.exe', 'candidate.bin', 'cases.bin', *contract.RESOURCE_FILES)
    native_hashes = {name: linked_pe.sha(output/name) for name in native_inputs}
    executions = {}
    for name in ('target', 'target-repeat', 'source'):
        arguments = ['wine', str(output/'host.exe'), windows(ROOT/'resources/th105.exe'),
                     *[windows(output/name) for name in contract.RESOURCE_FILES],
                     windows(output/'candidate.bin'), windows(output/'cases.bin'),
                     'source' if name == 'source' else 'target', windows(output/(name+'.bin'))]
        with (output/(name+'.log')).open('w') as log:
            subprocess.run(arguments, cwd=ROOT, env=environment, stdout=log,
                           stderr=subprocess.STDOUT, check=True, timeout=60)
        status = json.loads((output/(name+'.log')).read_text())
        require(status == {'cases': len(profiles), 'kernel32_imports': kernel_count,
                           'blocked_imports': blocked_count, 'target_text_unchanged': True,
                           'candidate_unchanged': True, **contract.expected_status(profiles)}, 'native host status differs')
        executions[name] = {'command': arguments, 'status': status}
    require(all(linked_pe.sha(Path(path)) == digest for path, digest in input_hashes.items()),
            'inputs changed during native comparison')
    require(all(linked_pe.sha(output/name) == digest for name, digest in native_hashes.items()),
            'native executable/data inputs changed during execution')
    result = {'schema': contract.SCHEMA, 'target_sha256': target_sha,
              'base_canonical_payload_sha256': base_proof['canonical_replayed_sha256'],
              'selected_object_sha256': contracts['object_sha256'], 'tool_pins': pins,
              'input_hashes': input_hashes, 'compile_command': command, 'link_command': link,
              'executions': executions, 'comparison': contract.compare(output, profiles),
              'generated_sha256': {name: linked_pe.sha(output/name) for name in
                  ('candidate.bin', *contract.RESOURCE_FILES, 'cases.bin', 'host.obj', 'host.exe')},
              'host_children_peak_rss_kib': resource.getrusage(resource.RUSAGE_CHILDREN).ru_maxrss,
              'wine_version': subprocess.run(['wine', '--version'], capture_output=True, text=True,
                                              check=True).stdout.strip(),
              'scope': contract.SCOPE}
    (output/'receipt.json').write_text(json.dumps(result, indent=2)+'\n')
    return result


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--base-dir', type=Path, default=ROOT/'build/reimu-ltcg')
    parser.add_argument('--object', type=Path, help='qualified private control object; default is the base ordinary object')
    parser.add_argument('--output-dir', type=Path, default=ROOT/'build/reimu-effect-returns')
    parser.add_argument('--smoke', action='store_true')
    args = parser.parse_args()
    try:
        result = audit(args.base_dir, args.object or args.base_dir/'ordinary.obj', args.output_dir, args.smoke)
    except (KeyError, OSError, ValueError, subprocess.SubprocessError) as error:
        parser.exit(2, f'Reimu effect-return audit failed: {error}\n')
    print(json.dumps(result['comparison'], indent=2))
    return 1 if result['comparison']['mismatches'] else 0


if __name__ == '__main__':
    raise SystemExit(main())
