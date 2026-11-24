#!/usr/bin/env python3
"""Qualify a genuine Reimu link against its ordinary, target-pinned COFF witness.

This read-only correspondence audit grants no target match or execution permission.
Every relocation is checked before the entire canonical payload is compared.
"""
from __future__ import annotations

import argparse
from collections import Counter
import hashlib
import importlib.util
import json
from pathlib import Path
import re
import struct
import sys
import tomllib

import pefile

import linked_pe
from workflow_manifest import unit_input_digest

ROOT = Path(__file__).resolve().parents[1]
ADDRESS = 0x478FA0
SYMBOL = '?run_action_dispatch_root@ReimuActionStatePreludeView@th105@@QAEXXZ'
CATEGORIES = {'rel32_calls', 'numeric_literals', 'local_metadata_addresses',
              'local_code_pointers', 'global_addresses'}


def require(condition, message):
    if not condition:
        raise ValueError(message)


def load(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / filename)
    module = importlib.util.module_from_spec(spec)
    sys.modules[name] = module
    spec.loader.exec_module(module)
    return module


def read_immutable(pe, address, width):
    require(width in (4, 8), 'unsupported numeric literal width')
    rva = address - pe.OPTIONAL_HEADER.ImageBase
    section = pe.get_section_by_rva(rva)
    require(section is not None and section.Characteristics & 0x40000000
            and not section.Characteristics & 0xA0000000
            and section.contains_rva(rva + width - 1)
            and rva + width <= section.VirtualAddress + section.SizeOfRawData,
            'literal is not initialized immutable image data')
    data = pe.get_data(rva, width)
    require(len(data) == width, 'truncated literal')
    return data


def split_linker_alignment(payload, ordinary_size, start, highlow):
    """Separate only a complete INT3 gap to the next16-byte MAP owner.

    The ordinary section length and every payload byte remain significant.
    No field, pointer or relocation may use this independently checked gap.
    """
    require(0 < ordinary_size <= len(payload), 'linked envelope truncates the ordinary section')
    require(all(0 <= offset and offset + 4 <= ordinary_size for offset in highlow),
            'PE relocation crosses the payload/alignment boundary')
    padding = payload[ordinary_size:]
    if padding:
        wanted = (-(start + ordinary_size)) & 15
        require(start & 15 == 0 and 0 < len(padding) == wanted < 16,
                'linked tail is not the exact next-owner alignment gap')
        require(padding == b'\xcc' * wanted, 'linked alignment gap contains non-INT3 bytes')
    return payload[:ordinary_size], padding


def replay_fields(reference, payload, rows, highlow, start, metadata,
                  symbols, aliases, read_literal, target_bytes):
    """Require identical instruction/data layout, then independently resolve fields."""
    require(len(reference) == len(payload), 'linked and ordinary envelopes differ')
    covered = set()
    for row in rows:
        offset, category = row['offset'], row['category']
        require(category in CATEGORIES and 0 <= offset <= len(payload) - 4,
                'unknown or out-of-bounds relocation')
        field = set(range(offset, offset + 4))
        require(not field & covered, 'overlapping relocation fields')
        require(row['kind'] == (20 if category == 'rel32_calls' else 6),
                'relocation kind/category disagreement')
        covered.update(field)
    shape = next((n for n, (a, b) in enumerate(zip(reference, payload))
                  if n not in covered and a != b), None)
    require(shape is None, f'linked layout differs outside relocation fields at {shape}')
    expected_highlow = {r['offset'] for r in rows
                        if r['category'] not in ('rel32_calls', 'global_addresses')}
    require(set(highlow) == expected_highlow, 'PE HIGHLOW inventory differs from field ownership')
    linked, ordinary = bytearray(payload), bytearray(reference)
    counts, calls = Counter(), Counter()
    for row in rows:
        offset, category, expected = row['offset'], row['category'], row['address']
        value = struct.unpack_from('<I', payload, offset)[0]
        wanted = expected
        if category == 'rel32_calls':
            require(offset < metadata and offset > 0 and payload[offset - 1] == 0xE8,
                    'call field is not an ordinary E8')
            destination = (start + offset + 4 + struct.unpack_from('<i', payload, offset)[0]) & 0xFFFFFFFF
            name = aliases.get(row['symbol'], row['symbol'])
            require(symbols.get(name) == {destination}, f'call does not reach its named provider: {name}')
            value = wanted = (expected - (ADDRESS + offset + 4)) & 0xFFFFFFFF
            calls[name] += 1
        elif category == 'numeric_literals':
            require(offset < metadata and re.fullmatch(r'__real@(?:[0-9a-fA-F]{8}|[0-9a-fA-F]{16})', row['symbol']),
                    'literal lacks its qualified numeric symbol')
            bits = bytes.fromhex(row['symbol'].split('@', 1)[1])[::-1]
            observed = read_literal(value, len(bits))
            require(observed == bits == target_bytes(expected, len(bits)), 'literal bits/width/target anchor disagree')
            value = expected
        elif category in ('local_metadata_addresses', 'local_code_pointers'):
            require(start <= value < start + len(payload), 'local pointer escapes root envelope')
            value = ADDRESS + value - start
            require(value == expected, 'local pointer changes its ordinary owner/offset')
            require((offset < metadata and ADDRESS + metadata <= value < ADDRESS + len(payload))
                    if category == 'local_metadata_addresses'
                    else (offset >= metadata and ADDRESS <= value < ADDRESS + metadata),
                    'local code/metadata pointer role disagrees')
        else:
            require(offset < metadata and value == expected, 'absolute game-data binding changed')
        struct.pack_into('<I', linked, offset, value)
        struct.pack_into('<I', ordinary, offset, wanted)
        counts[category] += 1
    require(linked == ordinary, 'canonical linked/ordinary payloads differ')
    return bytes(linked), bytes(ordinary), dict(counts), len(calls)


def audit(receipt_path):
    receipt_path = receipt_path.resolve()
    receipt = json.loads(receipt_path.read_text())
    require(receipt.get('schema') == 'th105-reimu-real-link-v2'
            and receipt.get('diagnostic_only') is True, 'unsupported producer receipt')
    canonical = linked_pe.comparator()
    target_sha = canonical.verify_target()
    require(receipt['target_sha256'] == target_sha, 'producer target changed')
    require(linked_pe.sha(ROOT / 'scripts/probe-reimu-action-ltcg.py') == receipt['probe_sha256'],
            'producer script changed')
    for filename, digest in receipt['support_sha256'].items():
        require(linked_pe.sha(ROOT / 'scripts' / filename) == digest, 'producer support script changed')
    tools, pins = linked_pe.pinned_tools()
    require(receipt['tool_pins'] == pins, 'producer toolchain changed')
    for name, digest in receipt['libraries'].items():
        require(linked_pe.sha(tools / name) == digest, 'producer library changed')
    for name, digest in receipt['root_input']['source_sha256'].items():
        require(linked_pe.sha(ROOT / name) == digest, 'root source input changed')
    folder = receipt_path.parent
    require(linked_pe.sha(folder / 'root-input/ReimuActionStateDispatch.cpp')
            == receipt['root_input']['generated_source_sha256'], 'generated root input changed')
    for header in (folder / 'ReimuActionStateStaging.hpp',
                   folder / 'root-input/ReimuActionStateStaging.hpp'):
        require(linked_pe.sha(header) == receipt['root_input']['generated_header_sha256'],
                'generated root header changed')
    for filename, key in [('ReimuRoot.dll', 'image_sha256'), ('ReimuRoot.map', 'map_sha256'),
                          ('root.obj', 'root_object_sha256'), ('provider.obj', 'provider_object_sha256'),
                          ('data-bindings.obj', 'data_object_sha256')]:
        require(linked_pe.sha(folder / filename) == receipt[key], f'producer artifact changed: {filename}')
    require(linked_pe.sha(folder / 'NativeDeque.cpp') == receipt['provider_source_sha256']
            and linked_pe.sha(folder / 'ReimuRoot.cpp') == receipt['generated_source_sha256'],
            'generated producer source changed')
    units = tomllib.loads((ROOT / 'config/match-units.toml').read_text())['units']
    for name, dependency in receipt['dependencies'].items():
        require(linked_pe.sha(ROOT / dependency['source']) == dependency['source_sha256']
                and linked_pe.sha(ROOT / dependency['provider_source']) == dependency['provider_sha256']
                and linked_pe.sha(folder / (name + '.obj')) == dependency['object_sha256'],
                f'genuine provider input changed: {name}')
        if name != 'private-reimu-word48a':
            require(unit_input_digest(name, units[name])[0] == dependency['unit_input_digest'],
                    f'provider contract or headers changed: {name}')
    ordinary_path = folder / 'ordinary.obj'
    require(linked_pe.sha(ordinary_path) == receipt['ordinary_object_sha256'], 'ordinary witness changed')
    relocations = load('reimu_link_relocations', 'audit-reimu-root-relocations.py')
    qualification = relocations.audit(ordinary_path, diagnostic_oversize=True)
    providers = load('reimu_link_providers', 'probe-common-fighter-ltcg.py')
    definitions, expected_owners = {}, {}
    for row in qualification['rows']:
        if row['category'] == 'rel32_calls':
            key = hex(row['address'])
            provider = receipt['callee_symbols'].get(key)
            require(provider is not None and provider == receipt['same_target_symbol_aliases'].get(
                row['symbol'], row['symbol']), 'call alias changes its contracted target identity')
            name = receipt['address_providers'].get(key)
            if name is not None:
                dependency = receipt['dependencies'][name]
                require('/gl' not in [arg.lower() for arg in dependency['command']],
                        'provider has linker-visible IR and needs a separate ABI proof')
                if name not in definitions:
                    definitions[name] = providers.coff_symbols(folder / (name + '.obj'))[0]
                require(provider in definitions[name], 'callee is not defined in its ordinary provider')
                expected_owners[provider] = name + '.obj'
                if name == 'private-reimu-word48a':
                    require(row['address'] == 0x4776C0 and canonical.coff_symbol_bytes(
                        folder / (name + '.obj'), provider, 0x4776C0, 15, {},
                        canonical.known_data_targets(), {}) == canonical.target_bytes(0x4776C0, 15),
                        'private field-write provider changed')
                else:
                    functions = [f for f in units[name]['functions'] if int(f['address'], 0) == row['address']]
                    require(len(functions) == 1 and canonical.is_function_symbol(provider, functions[0]['symbol_base']),
                            'callee name is not the configured provider at this target address')
            else:
                require(row['address'] == 0x68A1A0 and provider == '__ftol2_sse',
                        'unaccounted external root callee')
                expected_owners[provider] = 'libcmt:ftol2.obj'
    mapper = load('reimu_link_mapper', 'compare-giant-action-switches.py')
    obj = mapper.CoffObject(ordinary_path, symbol_base=SYMBOL)
    pe = pefile.PE(str(folder / 'ReimuRoot.dll'))
    require(pe.OPTIONAL_HEADER.ImageBase == 0x10000000 and pe.FILE_HEADER.Machine == 0x14C,
            'unexpected producer image format/base')
    exports = [entry for entry in pe.DIRECTORY_ENTRY_EXPORT.symbols if entry.name == SYMBOL.encode()]
    require(len(exports) == 1, 'missing or ambiguous root export')
    start = pe.OPTIONAL_HEADER.ImageBase + exports[0].address
    functions = linked_pe.parse_map((folder / 'ReimuRoot.map').read_text())
    require(any(name == SYMBOL for name, _ in functions.get(start, [])), 'root export/MAP disagree')
    end = min(address for address in functions if address > start)
    payload = pe.get_data(exports[0].address, end - start)
    require(len(payload) == end - start, 'truncated linked MAP envelope')
    highlow = set()
    for block in pe.DIRECTORY_ENTRY_BASERELOC:
        for entry in block.entries:
            address = pe.OPTIONAL_HEADER.ImageBase + entry.rva
            if start <= address < end and entry.type:
                require(entry.type == 3, 'unsupported root PE relocation type')
                highlow.add(address - start)
    symbols = {}
    for address, names in functions.items():
        for name, owner in names:
            symbols.setdefault(name, set()).add(address)
            if name in expected_owners:
                require(owner.lower() == expected_owners[name].lower(),
                        'MAP provider ownership differs from the genuine input')
    payload, alignment = split_linker_alignment(payload, len(obj.text), start, highlow)
    linked, ordinary, counts, callees = replay_fields(
        obj.text, payload, qualification['rows'], highlow, start,
        qualification['source_metadata_start'], symbols, receipt['same_target_symbol_aliases'],
        lambda address, width: read_immutable(pe, address, width), canonical.target_bytes)
    require(hashlib.sha256(ordinary).hexdigest() == qualification['source_replayed_sha256'],
            'ordinary independent canonical replay disagrees')
    stack = load('reimu_link_stack', 'audit-reimu-root-stack.py').audit(ordinary_path, diagnostic_oversize=True)
    target = canonical.target_bytes(ADDRESS, 81550)
    mismatch = canonical.first_mismatch(target, linked[:len(target)], ADDRESS)
    digest = hashlib.sha256(linked).hexdigest()
    return {'schema': 'th105-reimu-linked-coff-replay-v1', 'target_sha256': target_sha,
            'producer_receipt_sha256': linked_pe.sha(receipt_path), 'image_sha256': receipt['image_sha256'],
            'ordinary_object_sha256': qualification['object_sha256'], 'linked_start': hex(start),
            'envelope_end': hex(end), 'payload_end': hex(start + len(payload)),
            'payload_bytes': len(payload), 'envelope_bytes': end - start,
            'linker_alignment_bytes': len(alignment),
            'linker_alignment_sha256': hashlib.sha256(alignment).hexdigest(),
            'code_prefix': qualification['source_metadata_start'], 'pe_highlow_fields': len(highlow),
            'replayed_fields': counts, 'direct_callee_symbols': callees,
            'canonical_replayed_sha256': digest, 'ordinary_replayed_sha256': digest,
            'all_payload_bytes_equal': True, 'ordinary_switches': 11,
            'ordinary_buffer_partition_mismatches': stack['buffer_partition_mismatches'],
            'target_first_mismatch': mismatch,
            'scope': 'strict complete linked/ordinary payload correspondence, inheriting the qualified ordinary CFG/metadata; '
                     'opaque normal-COFF providers, no DLL execution, returned-world or target exactness claim'}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('producer_receipt', type=Path)
    args = parser.parse_args()
    try:
        print(json.dumps(audit(args.producer_receipt), indent=2))
    except (OSError, KeyError, ValueError) as error:
        print(f'Reimu linked correspondence failed: {error}', file=sys.stderr)
        return 2
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
