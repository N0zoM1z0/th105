#!/usr/bin/env python3
"""Audit all Reimu void-probe relocations; never accept an exact match unit."""
from __future__ import annotations

import argparse
from bisect import bisect_right
from collections import Counter, defaultdict
import csv
import hashlib
import importlib.util
import json
from pathlib import Path
import struct
import sys
import tomllib

import capstone
from capstone import x86_const as x
import pefile

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))
DEFAULT_BINDINGS = ROOT / 'config/reimu-root-probe-bindings.toml'
ADDRESS, SIZE, METADATA_END = 0x478FA0, 81550, 0x48D38C
TARGET_SHA = '56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e'
BODY_SHA = 'dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6'
SYMBOL = '?run_action_dispatch_root@ReimuActionStatePreludeView@th105@@QAEXXZ'


def load(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / filename)
    module = importlib.util.module_from_spec(spec)
    sys.modules[name] = module
    spec.loader.exec_module(module)
    return module


def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def validate_bindings(data):
    expected = {'schema', 'purpose', 'target_sha256', 'address', 'callable_size',
                'metadata_end', 'body_sha256', 'symbol', 'rel32', 'root_literals', 'pool_literals', 'data'}
    if (set(data) != expected or data['schema'] != 'th105-reimu-root-probe-bindings-v1'
            or data['purpose'] != 'probe-only' or data['target_sha256'] != TARGET_SHA
            or data['body_sha256'] != BODY_SHA or data['symbol'] != SYMBOL
            or not isinstance(data['address'], str) or int(data['address'], 0) != ADDRESS
            or data['callable_size'] != SIZE or not isinstance(data['metadata_end'], str)
            or int(data['metadata_end'], 0) != METADATA_END):
        raise ValueError('probe identity/scope/extent differs from the reviewed Reimu target')
    for name in ('rel32', 'root_literals', 'pool_literals', 'data'):
        if not isinstance(data[name], dict) or not data[name]:
            raise ValueError(f'empty or invalid binding table: {name}')
        for key, value in data[name].items():
            if not isinstance(key, str) or not isinstance(value, str) or not 0x401000 <= int(value, 0) < 0x706000:
                raise ValueError(f'invalid binding in {name}')
            if name in ('root_literals', 'pool_literals'):
                if len(key) not in (8, 16) or bytes.fromhex(key).hex() != key:
                    raise ValueError('numeric bindings require exact32/64-bit lowercase hex')
    if set(data['root_literals']) & set(data['pool_literals']):
        raise ValueError('a numeric value cannot be both root-owned and pool-only')
    return data


def load_bindings(path):
    return validate_bindings(tomllib.loads(path.read_text()))


def audit(path, bindings_path=DEFAULT_BINDINGS):
    bindings = load_bindings(bindings_path)
    canonical = load('reimu_relocations_canonical', 'compare-function.py')
    target_sha = canonical.verify_target()
    target = canonical.target_bytes(ADDRESS, SIZE)
    if target_sha != TARGET_SHA or hashlib.sha256(target).hexdigest() != BODY_SHA:
        raise ValueError('Reimu target bytes/boundary changed')
    mapper = load('reimu_relocations_coff', 'compare-giant-action-switches.py')
    tm = mapper.load_target_mapper()
    manifest = tomllib.loads((ROOT / 'config/giant-action-switches.toml').read_text())
    root = tm.select_root(manifest, 'reimu-vslot28')
    wanted_map = tm.map_root(tm.PeImage(ROOT / 'resources/th105.exe'), tm.load_function_rows(ROOT / 'config/functions.csv'), root)
    obj = mapper.CoffObject(path, symbol_base=SYMBOL)
    mapping = mapper.compare_maps(wanted_map, mapper.build_candidate_map(obj, root))
    prefix = mapping['candidate_metadata_start']
    if not 0 < prefix < len(obj.text) or len(obj.text) > METADATA_END-ADDRESS:
        raise ValueError('source code or metadata exceeds the reviewed diagnostic envelope')
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    decoder.detail = True
    ti, ci = list(decoder.disasm(target, ADDRESS)), list(decoder.disasm(obj.text[:prefix], 0))
    if sum(i.size for i in ti) != SIZE or sum(i.size for i in ci) != prefix:
        raise ValueError('target or source prefix did not decode completely')
    starts = [i.address for i in ci]
    start_set = set(starts)
    pe = pefile.PE(str(ROOT / 'resources/th105.exe'))
    section = next(s for s in pe.sections if s.Name.rstrip(b'\0') == b'.rdata')
    lo, hi = 0x400000+section.VirtualAddress, 0x400000+section.VirtualAddress+section.Misc_VirtualSize
    numeric = defaultdict(set)
    target_calls = Counter()
    target_data = Counter()
    for insn in ti:
        if insn.mnemonic == 'call' and insn.bytes[0] == 0xE8:
            target_calls[insn.operands[0].imm] += 1
        for operand in insn.operands:
            if operand.type != x.X86_OP_MEM or operand.mem.base or operand.mem.index:
                continue
            if insn.mnemonic.startswith('f') and lo <= operand.mem.disp < hi and operand.size in (4, 8):
                numeric[canonical.target_bytes(operand.mem.disp, operand.size)[::-1].hex()].add(operand.mem.disp)
            if operand.access & capstone.CS_AC_READ:
                target_data[(operand.mem.disp, operand.size)] += 1
    observed = {bits: next(iter(addresses)) for bits, addresses in numeric.items() if len(addresses) == 1}
    declared = {key: int(value, 0) for key, value in bindings['root_literals'].items()}
    if len(observed) != len(numeric) or observed != declared:
        raise ValueError('root numeric addresses are missing, ambiguous or differ from actual x87 reads')
    rel32 = {key: int(value, 0) for key, value in bindings['rel32'].items()}
    if not set(rel32.values()) <= set(target_calls):
        raise ValueError('call binding does not name an actual target-root E8 destination')
    with (ROOT / 'config/functions.csv').open() as stream:
        candidates = {int(row['address'], 0) for row in csv.DictReader(stream)}
    if not set(rel32.values()) <= candidates:
        raise ValueError('call binding lacks a tracked candidate start')
    known = canonical.known_data_targets()
    data_targets = {}
    for table in ('root_literals', 'pool_literals'):
        for bits, value in bindings[table].items():
            name, address, raw = '__real@'+bits, int(value, 0), bytes.fromhex(bits)[::-1]
            if not lo <= address <= address+len(raw) <= hi or canonical.target_bytes(address, len(raw)) != raw:
                raise ValueError('numeric binding is outside immutable target data or has wrong bits')
            if table == 'pool_literals' and (name not in known or known[name][0] != address or known[name][1] != raw or known[name][3] != 'literal'):
                raise ValueError('pool-only value lacks its existing canonical literal anchor')
            data_targets[name] = (address, raw, frozenset({0}), 'literal')
    for name, value in bindings['data'].items():
        address = int(value, 0)
        if (name not in known or known[name][0] != address or known[name][3] != 'address'
                or (address, 4) not in target_data):
            raise ValueError('external data binding lacks its known global and target-root read')
        data_targets[name] = known[name]
    rows, counts = [], Counter()
    source_calls = Counter()
    source_only = []
    for offset, (symbol, kind) in sorted(obj.relocations.items()):
        addend = int.from_bytes(obj.text[offset:offset+4], 'little', signed=True)
        instruction = ci[bisect_right(starts, offset)-1] if offset < prefix else None
        operand = None
        if instruction is not None:
            if not instruction.address <= offset < offset+4 <= instruction.address+instruction.size:
                raise ValueError('relocation does not belong to one decoded instruction')
            if instruction.disp_offset and instruction.address+instruction.disp_offset == offset:
                operand = next((op for op in instruction.operands if op.type == x.X86_OP_MEM), None)
        if kind == 20:
            if (instruction is None or instruction.mnemonic != 'call' or instruction.bytes[0] != 0xE8
                    or offset != instruction.address+1 or instruction.size != 5 or addend != 0
                    or symbol.section_number != 0 or symbol.name not in rel32):
                raise ValueError(f'unqualified external call relocation: {symbol.name} at {offset:#x}')
            category, destination = 'rel32_calls', rel32[symbol.name]
            source_calls[destination] += 1
        elif kind == 6 and symbol.section_number == obj.text_section_number:
            destination_offset = obj.relocated_text_value(offset)
            if offset < prefix:
                if (operand is None or instruction.mnemonic not in ('jmp', 'movzx')
                        or not prefix <= destination_offset < len(obj.text)):
                    raise ValueError('local code relocation does not reference owned switch metadata')
                category = 'local_metadata_addresses'
            else:
                if offset & 3 or destination_offset not in start_set:
                    raise ValueError('local table relocation does not reference a decoded code start')
                category = 'local_code_pointers'
            destination = ADDRESS+destination_offset
        elif kind == 6:
            if (addend != 0 or operand is None or operand.mem.base or operand.mem.index
                    or not operand.access & capstone.CS_AC_READ or symbol.name not in data_targets):
                raise ValueError(f'unqualified absolute data relocation: {symbol.name} at {offset:#x}')
            destination = data_targets[symbol.name][0]
            if symbol.name.startswith('__real@'):
                bits = symbol.name[7:]
                if operand.size != len(bytes.fromhex(bits)):
                    raise ValueError('numeric operand width differs from its COFF literal')
                category = 'numeric_literals'
                if bits in bindings['pool_literals']:
                    source_only.append({'offset': offset, 'symbol': symbol.name, 'address': hex(destination)})
            else:
                if symbol.section_number != 0 or operand.size != 4:
                    raise ValueError('external global is not an undefined DWORD source read')
                category = 'global_addresses'
        else:
            raise ValueError(f'unsupported root relocation kind {kind:#x}')
        counts[category] += 1
        rows.append({'offset': offset, 'symbol': symbol.name, 'kind': kind,
                     'category': category, 'address': destination})
    replay = canonical.coff_symbol_bytes(path, SYMBOL, ADDRESS, len(obj.text), rel32, data_targets, {})
    if len(replay) != len(obj.text):
        raise ValueError('canonical relocation replay changed section length')
    for row in rows:
        value = struct.unpack_from('<I', replay, row['offset'])[0]
        resolved = ((ADDRESS+row['offset']+4+struct.unpack_from('<i', replay, row['offset'])[0]) & 0xFFFFFFFF
                    if row['kind'] == 20 else value)
        if resolved != row['address']:
            raise ValueError('canonical replay differs from the independently classified relocation')
    compared = min(prefix, SIZE)
    last_ret = max(i.address+i.size for i in ci if i.mnemonic == 'ret')
    support = (Path(__file__), bindings_path, ROOT / 'scripts/compare-function.py',
               ROOT / 'scripts/compare-giant-action-switches.py', ROOT / 'scripts/map-giant-action-switches.py',
               ROOT / 'config/giant-action-switches.toml', ROOT / 'config/functions.csv',
               ROOT / 'config/known-symbols.csv', ROOT / 'config/known-globals.csv',
               ROOT / 'config/reccmp-relocations.csv')
    return {'schema': 'th105-reimu-root-relocations-v1', 'target_sha256': target_sha,
            'object_sha256': sha(path), 'symbol': SYMBOL, 'relocation_count': len(rows),
            'coverage': dict(counts), 'unresolved_relocations': 0, 'rows': rows,
            'source_only_literal_sites': source_only, 'source_text_bytes': len(obj.text),
            'source_metadata_start': prefix, 'last_decoded_ret_end': last_ret,
            'after_last_ret_byte_count': prefix-last_ret,
            'after_last_ret_sha256': hashlib.sha256(replay[last_ret:prefix]).hexdigest(),
            'source_replayed_sha256': hashlib.sha256(replay).hexdigest(),
            'target_callable_size': SIZE, 'compared_prefix_bytes': compared,
            'strict_prefix_differences': sum(a != b for a, b in zip(target[:compared], replay[:compared])),
            'first_mismatch': canonical.first_mismatch(target, replay[:prefix], ADDRESS),
            'target_numeric_values': len(numeric),
            'source_numeric_symbols': len({r['symbol'] for r in rows if r['category'] == 'numeric_literals'}),
            'unused_root_literals': sorted(set(bindings['root_literals'])-{r['symbol'][7:] for r in rows if r['category'] == 'numeric_literals'}),
            'call_count_deltas': [{'address': hex(a), 'target': target_calls[a], 'source': source_calls[a]}
                                  for a in sorted(target_calls.keys() | source_calls.keys()) if target_calls[a] != source_calls[a]],
            'capstone_version': capstone.__version__,
            'support_sha256': {str(p.relative_to(ROOT) if p.is_relative_to(ROOT) else p): sha(p) for p in support},
            'scope': 'probe-only complete relocation classification and strict replay; code-prefix/RET observations are provisional; '
                     'not callable-boundary acceptance, semantic ownership of every callee, a match unit or exact/partial credit'}


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('object', type=Path)
    parser.add_argument('--bindings', type=Path, default=DEFAULT_BINDINGS)
    args = parser.parse_args()
    try:
        result = audit(args.object, args.bindings.resolve())
    except (KeyError, OSError, ValueError) as error:
        parser.exit(2, f'Reimu root relocation audit failed: {error}\n')
    print(json.dumps(result, indent=2))
