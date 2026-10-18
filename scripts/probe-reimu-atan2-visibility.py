#!/usr/bin/env python3
"""Probe the current real Reimu link with linker-visible strict-FP atan2 source.

This builds a diagnostic image only. It never executes the image or changes
the normal producer, accepted profiles, sources, or comparison rules.
"""
from __future__ import annotations

import argparse
import hashlib
import importlib.util
import json
import os
from pathlib import Path
import subprocess
import sys

import capstone
from capstone import x86_const as x
import pefile

import linked_pe

ROOT = Path(__file__).resolve().parents[1]
ROOT_SYMBOL = '?run_action_dispatch_root@ReimuActionStatePreludeView@th105@@QAEXXZ'
MATH_SYMBOL = '?atan2_degrees@th105@@YAMMM@Z'
MATH_UNIT = 'gpt-web-angle-atan2-natural'


def require(condition, message):
    if not condition:
        raise ValueError(message)


def load(filename):
    spec = importlib.util.spec_from_file_location('reimu_visibility_base', ROOT/'scripts'/filename)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def windows(path):
    return 'Z:' + str(path.resolve()).replace('/', '\\')


def linux(path):
    require(path.lower().startswith('z:\\'), 'expected a Wine Z-drive input')
    return Path('/' + path[3:].replace('\\', '/'))


def inspect(image, map_path, target):
    pe = pefile.PE(str(image))
    require(pe.FILE_HEADER.Machine == 0x14C, 'expected an x86 image')
    base = pe.OPTIONAL_HEADER.ImageBase
    functions = linked_pe.parse_map(map_path.read_text())
    names = {}
    for address, labels in functions.items():
        for name, _ in labels:
            names.setdefault(name, set()).add(address)
    require(len(names.get(ROOT_SYMBOL, ())) == len(names.get(MATH_SYMBOL, ())) == 1,
            'root/math symbols are absent or ambiguous')
    start, = names[ROOT_SYMBOL]
    math_start, = names[MATH_SYMBOL]
    exports = [base+row.address for row in pe.DIRECTORY_ENTRY_EXPORT.symbols
               if row.name == ROOT_SYMBOL.encode()]
    require(exports == [start], 'root export/MAP disagree')
    end = min(address for address in functions if address > start)
    raw = pe.get_data(start-base, end-start)
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    decoder.detail = True
    initial = list(decoder.disasm(raw[:1500], start))
    first = next(row.operands[0].mem.disp for row in initial
                 if row.mnemonic == 'jmp' and row.operands[0].type == x.X86_OP_MEM
                 and row.operands[0].mem.index and start < row.operands[0].mem.disp < end)
    preliminary = list(decoder.disasm(raw[:first-start], start))
    tables = sorted({row.operands[0].mem.disp for row in preliminary
                     if row.mnemonic == 'jmp' and row.operands[0].type == x.X86_OP_MEM
                     and row.operands[0].mem.index and start < row.operands[0].mem.disp < end})
    require(len(tables) == 11, 'unreviewed root switch-table inventory')
    prefix = tables[0]-start
    rows = list(decoder.disasm(raw[:prefix], start))
    require(sum(row.size for row in rows) == prefix, 'truncated root code observation')
    math_end = min(address for address in functions if address > math_start)
    math_envelope = pe.get_data(math_start-base, math_end-math_start)
    math_rows = []
    for row in decoder.disasm(math_envelope, math_start):
        require(not row.group(capstone.CS_GRP_JUMP), 'unreviewed math control flow')
        math_rows.append(row)
        if row.mnemonic == 'ret':
            break
    require(math_rows and math_rows[-1].mnemonic == 'ret', 'math RET boundary is absent')
    math_size = math_rows[-1].address+math_rows[-1].size-math_start
    tail = math_envelope[math_size:]
    require(math_end % 16 == 0 and len(tail) < 16 and tail == b'\xcc'*len(tail),
            'unreviewed bytes after math RET')
    math_body = math_envelope[:math_size]
    target_body = target.target_bytes(0x406540, 63)
    return {
        'root_start': hex(start), 'next_map_owner': hex(end),
        'root_envelope_bytes': len(raw), 'lowest_switch_table_offset': prefix,
        'root_switch_tables': [hex(address) for address in tables],
        'root_first_rows': [{'address': hex(row.address),
                            'instruction': row.mnemonic+' '+row.op_str} for row in rows[:12]],
        'root_direct_calls': sum(row.mnemonic == 'call'
                                 and row.operands[0].type == x.X86_OP_IMM for row in rows),
        'root_direct_math_calls': sum(row.mnemonic == 'call'
                                     and row.operands[0].type == x.X86_OP_IMM
                                     and row.operands[0].imm == math_start for row in rows),
        'root_first_target_difference': next(
            (i for i, (a, b) in enumerate(zip(raw[:18], target.target_bytes(0x478FA0, 18)))
             if a != b), None),
        'root_last_decoded_rows': [{'address': hex(row.address),
                                   'instruction': row.mnemonic+' '+row.op_str} for row in rows[-5:]],
        'math_start': hex(math_start), 'math_code_bytes': math_size, 'target_math_code_bytes': 63,
        'math_first_byte_equal': math_body[0] == target_body[0],
        'math_raw_sha256': hashlib.sha256(math_body).hexdigest(),
        'math_instructions': [{'address': hex(row.address), 'bytes': row.bytes.hex(),
                               'instruction': row.mnemonic+' '+row.op_str} for row in math_rows],
        'scope': 'symbol-backed layout and straight-line math boundary; no root canonical replay or execution',
    }


def probe(base, output):
    base, output = base.resolve(), output.resolve()
    build = (ROOT/'build').resolve()
    require(base.is_relative_to(build) and base != build
            and output.is_relative_to(build) and output != build,
            'base and output must be separate subdirectories of build/')
    require(not base.is_relative_to(output) and not output.is_relative_to(base),
            'base and output overlap')
    auditor = load('audit-reimu-linked-coff.py')
    proof = auditor.audit(base/'receipt.json')
    producer = json.loads((base/'receipt.json').read_text())
    normal = json.loads((base/(MATH_UNIT+'.compile-receipt.json')).read_text())
    source = ROOT/'src/engine/AngleAtan2.cpp'
    require(linked_pe.sha(source) == normal['inputs']['source_sha256']
            and linked_pe.sha(base/(MATH_UNIT+'.obj')) == normal['object_sha256'],
            'normal math source/object changed')
    require(not os.environ.get('CL') and not os.environ.get('_CL_'),
            'ambient compiler flags are unsupported')
    output.mkdir(parents=True, exist_ok=True)
    with (output/'normal-math.json').open('w') as log:
        subprocess.run([sys.executable, '-B', str(ROOT/'scripts/build.py'), '--unit', MATH_UNIT,
                        '--compare', '--json'], cwd=ROOT, stdout=log, check=True)
    anchor = json.loads((output/'normal-math.json').read_text())
    require(anchor['result'] == 'ok' and len(anchor['comparisons']) == 1
            and anchor['comparisons'][0]['result'] == 'exact'
            and anchor['comparisons'][0]['comparison']['size'] == 63,
            'normal math anchor is not exact63/63')
    environment = os.environ.copy()
    environment.update(WINEPREFIX=os.environ.get('TH105_WINEPREFIX', str(ROOT/'.tools/wine-msvc8')),
                       WINEARCH='win32', WINEDEBUG='-all')
    gl_object = output/'math-gl.obj'
    compile_command = [('/Fo'+windows(gl_object) if arg.startswith('/Fo') else arg)
                       for arg in normal['inputs']['command']]
    require(compile_command[0] == 'wine' and '/fp:strict' in compile_command
            and '/gl' not in [arg.lower() for arg in compile_command],
            'expected the existing Wine strict-FP math recipe')
    compile_command.insert(-1, '/GL')
    with (output/'math-gl-compile.log').open('w') as log:
        subprocess.run(compile_command, cwd=ROOT, env=environment, stdout=log,
                       stderr=subprocess.STDOUT, check=True)
    require(gl_object.read_bytes()[:4] == (base/'root.obj').read_bytes()[:4],
            'math object does not have the root IL signature')
    copied = output/'inputs'
    copied.mkdir(exist_ok=True)
    manifest, link_command, math_inputs = {}, [], 0
    for arg in producer['link_commands'][0]:
        if arg.upper().startswith('/OUT:'):
            arg = '/OUT:'+windows(output/'ReimuMathGl.dll')
        elif arg.upper().startswith('/MAP:'):
            arg = '/MAP:'+windows(output/'ReimuMathGl.map')
        elif arg.lower().startswith('z:\\') and arg.lower().endswith(('.obj', '.lib')):
            path = linux(arg)
            manifest[str(path)] = linked_pe.sha(path)
            if path.suffix.lower() == '.obj':
                require(path.parent == base, 'object input is outside the verified base')
                if path.name == MATH_UNIT+'.obj':
                    math_inputs += 1
                    arg = windows(gl_object)
                else:
                    destination = copied/path.name
                    destination.write_bytes(path.read_bytes())
                    arg = windows(destination)
        link_command.append(arg)
    require(math_inputs == 1, 'expected exactly one normal math input to replace')
    for name in ('receipt.json', 'ordinary.obj', 'ReimuRoot.dll', 'ReimuRoot.map'):
        manifest[str(base/name)] = linked_pe.sha(base/name)
    with (output/'math-gl-link.log').open('w') as log:
        subprocess.run(link_command, cwd=ROOT, env=environment, stdout=log,
                       stderr=subprocess.STDOUT, check=True)
    require(all(linked_pe.sha(Path(name)) == digest for name, digest in manifest.items()),
            'base inputs changed during private linking')
    target = linked_pe.comparator()
    result = {
        'schema': 'th105-reimu-atan2-visibility-v1', 'diagnostic_only': True,
        'target_sha256': target.verify_target(), 'probe_sha256': linked_pe.sha(Path(__file__)),
        'base_receipt_sha256': linked_pe.sha(base/'receipt.json'),
        'base_canonical_payload_sha256': proof['canonical_replayed_sha256'],
        'normal_math_comparison': anchor['comparisons'][0],
        'math_source_sha256': linked_pe.sha(source), 'tool_pins': producer['tool_pins'],
        'base_inputs_unchanged': manifest, 'compile_command': compile_command,
        'gl_object_sha256': linked_pe.sha(gl_object), 'link_command': link_command,
        'image_sha256': linked_pe.sha(output/'ReimuMathGl.dll'),
        'map_sha256': linked_pe.sha(output/'ReimuMathGl.map'),
        'observations': inspect(output/'ReimuMathGl.dll', output/'ReimuMathGl.map', target),
        'scope': 'genuine GL math visibility in one tested root/provider context; no default profile, '
                 'ABI, source, acceptance or aggregate-progress change; image is never executed',
    }
    (output/'receipt.json').write_text(json.dumps(result, indent=2)+'\n')
    return result


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--base-dir', type=Path, default=ROOT/'build/reimu-ltcg')
    parser.add_argument('--output-dir', type=Path, default=ROOT/'build/reimu-atan2-visibility')
    args = parser.parse_args()
    try:
        result = probe(args.base_dir, args.output_dir)
    except (KeyError, OSError, ValueError, StopIteration, subprocess.CalledProcessError) as error:
        parser.exit(2, f'Reimu atan2 visibility probe failed: {error}\n')
    print(json.dumps(result['observations'], indent=2))
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
