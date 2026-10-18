#!/usr/bin/env python3
"""Test real method IR through a facade alias, a direct root call and small callers.

All linked images are read-only compiler experiments and are never executed.
The normal producer's separate provider-ABI requirement remains unchanged.
"""
from __future__ import annotations

import argparse
from collections import Counter
import hashlib
import importlib.util
import json
import os
from pathlib import Path
import resource
import subprocess
import sys

import capstone
from capstone import x86_const as x
import pefile

import linked_pe

ROOT = Path(__file__).resolve().parents[1]
UNIT = 'cross-v106a-fighter-landing-transition'
SOURCE = ROOT/'src/battle/FighterLandingTransition.cpp'
EVENT = '?dispatch_indexed_event_member@FighterLandingTransitionView@th105@@QAEXI@Z'
GLOBAL_EVENT = '?dispatch_indexed_event@th105@@YAXI@Z'
METHODS = (0x473DD0, 0x5F9310, 0x4359D0, 0x4359F0)


def require(condition, message):
    if not condition:
        raise ValueError(message)


def load(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT/'scripts'/filename)
    module = importlib.util.module_from_spec(spec)
    sys.modules[name] = module
    spec.loader.exec_module(module)
    return module


def run(arguments, log, environment):
    with log.open('w') as stream:
        subprocess.run(arguments, cwd=ROOT, env=environment, stdout=stream,
                       stderr=subprocess.STDOUT, check=True, timeout=120)


def root_replay(image, map_path, ordinary, qualification, producer, auditor):
    canonical = linked_pe.comparator()
    pe = pefile.PE(str(image))
    require(pe.FILE_HEADER.Machine == 0x14C and pe.OPTIONAL_HEADER.ImageBase == 0x10000000,
            'unexpected private image format/base')
    functions = linked_pe.parse_map(map_path.read_text())
    symbols = {}
    for address, labels in functions.items():
        for name, _ in labels:
            symbols.setdefault(name, set()).add(address)
    require(len(symbols.get(auditor.SYMBOL, ())) == 1, 'ambiguous root MAP symbol')
    start, = symbols[auditor.SYMBOL]
    require([pe.OPTIONAL_HEADER.ImageBase+entry.address
             for entry in pe.DIRECTORY_ENTRY_EXPORT.symbols
             if entry.name == auditor.SYMBOL.encode()] == [start], 'root export/MAP disagree')
    end = min(address for address in functions if address > start)
    highlow = set()
    for block in pe.DIRECTORY_ENTRY_BASERELOC:
        for entry in block.entries:
            address = pe.OPTIONAL_HEADER.ImageBase+entry.rva
            if start <= address < end and entry.type:
                require(entry.type == 3, 'unsupported root PE relocation')
                highlow.add(address-start)
    payload, alignment = auditor.split_linker_alignment(
        pe.get_data(start-pe.OPTIONAL_HEADER.ImageBase, end-start), len(ordinary), start, highlow)
    linked, reference, fields, _ = auditor.replay_fields(
        ordinary, payload, qualification['rows'], highlow, start,
        qualification['source_metadata_start'], symbols, producer['same_target_symbol_aliases'],
        lambda address, width: auditor.read_immutable(pe, address, width), canonical.target_bytes)
    digest = hashlib.sha256(linked).hexdigest()
    require(linked == reference and digest == qualification['source_replayed_sha256'],
            'complete private root differs from ordinary baseline')
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    decoder.detail = True
    rows = list(decoder.disasm(payload[:qualification['source_metadata_start']], start))
    require(sum(row.size for row in rows) == qualification['source_metadata_start'],
            'truncated root instruction observation')
    calls = Counter(row.operands[0].imm for row in rows
                    if row.mnemonic == 'call' and row.operands[0].type == x.X86_OP_IMM)
    counts = {}
    for target in METHODS:
        name = producer['callee_symbols'][hex(target)]
        require(len(symbols.get(name, ())) == 1, 'ambiguous method MAP symbol')
        address, = symbols[name]
        counts[hex(target)] = calls[address]
    return {'payload_bytes': len(linked), 'canonical_payload_sha256': digest,
            'code_prefix': qualification['source_metadata_start'],
            'replayed_fields': fields, 'highlow_fields': len(highlow),
            'linker_int3_bytes': len(alignment), 'root_direct_calls': sum(calls.values()),
            'method_calls': counts, 'target_first_mismatch': qualification['first_mismatch'],
            'image_sha256': linked_pe.sha(image), 'map_sha256': linked_pe.sha(map_path)}, pe, functions


def small_callers(pe, functions):
    symbols = {}
    for address, labels in functions.items():
        for name, _ in labels:
            symbols.setdefault(name, set()).add(address)
    require(len(symbols.get(EVENT, ())) == len(symbols.get(GLOBAL_EVENT, ())) == 1,
            'ambiguous event provider identities')
    member, = symbols[EVENT]
    global_event, = symbols[GLOBAL_EVENT]
    observations = {}
    for name, destination in (('_reimu_event_via_alias', member),
                              ('_reimu_event_direct', global_event)):
        require(len(symbols.get(name, ())) == 1, 'missing small caller')
        start, = symbols[name]
        end = min(address for address in functions if address > start)
        raw = pe.get_data(start-pe.OPTIONAL_HEADER.ImageBase, end-start)
        code = raw.rstrip(b'\xcc')
        require(end % 16 == 0 and len(raw)-len(code) < 16, 'unreviewed small-caller padding')
        rows = linked_pe.decode_closed_body(code, start)
        calls = [row for row in rows if row.mnemonic == 'call'
                 and row.operands[0].type == x.X86_OP_IMM]
        require(len(calls) == 1 and calls[0].operands[0].imm == destination,
                'small caller does not reach its expected real provider')
        observations[name] = {'bytes': len(code), 'call_destination': hex(destination),
                              'called_symbol': EVENT if destination == member else GLOBAL_EVENT,
                              'instructions': [{'bytes': row.bytes.hex(),
                                                'instruction': row.mnemonic+' '+row.op_str}
                                               for row in rows]}
    return observations


def probe(base, output):
    base, output = base.resolve(), output.resolve()
    build = (ROOT/'build').resolve()
    require(base.is_relative_to(build) and output.is_relative_to(build)
            and base != build and output != build
            and not base.is_relative_to(output) and not output.is_relative_to(base),
            'base/output must be separate subdirectories of build/')
    require(not os.environ.get('CL') and not os.environ.get('_CL_'),
            'ambient compiler flags are unsupported')
    helper = load('reimu_method_visibility_paths', 'probe-reimu-atan2-visibility.py')
    auditor = load('reimu_method_visibility_auditor', 'audit-reimu-linked-coff.py')
    proof = auditor.audit(base/'receipt.json')
    producer = json.loads((base/'receipt.json').read_text())
    recipe = json.loads((base/(UNIT+'.compile-receipt.json')).read_text())
    require(linked_pe.sha(SOURCE) == recipe['inputs']['source_sha256'], 'provider source changed')
    require(producer['callee_symbols']['0x4359f0'] == EVENT, 'event provider identity changed')
    output.mkdir(parents=True, exist_ok=True)
    (output/'receipt.json').unlink(missing_ok=True)
    environment = {**os.environ, 'WINEPREFIX': os.environ.get(
        'TH105_WINEPREFIX', str(ROOT/'.tools/wine-msvc8')), 'WINEARCH': 'win32', 'WINEDEBUG': '-all'}
    anchor_command = [sys.executable, '-B', str(ROOT/'scripts/build.py'),
                      '--unit', UNIT, '--compare', '--json']
    run(anchor_command, output/'normal-provider.json', environment)
    anchor = json.loads((output/'normal-provider.json').read_text())
    require(anchor['result'] == 'ok' and len(anchor['comparisons']) == 4
            and {int(row['address'], 0): row['comparison']['size'] for row in anchor['comparisons']}
            == dict(zip(METHODS, (442, 64, 21, 14)))
            and all(row['result'] == 'exact' for row in anchor['comparisons']),
            'ordinary provider anchor is not exact for all four methods')

    # Preserve the actual provider's complete class declaration and offset checks.
    marker = 'unsigned char FighterLandingTransitionView::resolve_stage_surface_landing_transition()'
    text = SOURCE.read_text()
    require(text.count(marker) == 1, 'provider declaration/body boundary changed')
    declaration = text[:text.index(marker)].replace(
        '#include "BattleBackgroundLayout.hpp"', '#include "battle/BattleBackgroundLayout.hpp"')
    (output/'FighterLandingDeclaration.hpp').write_bytes(
        ('#pragma once\n'+declaration+'} // namespace th105\n').replace('\n', '\r\n').encode())
    header = base/'ReimuActionStateStaging.hpp'
    (output/header.name).write_bytes(header.read_bytes())
    source = (base/'ReimuRoot.cpp').read_text()
    include, token = '#include "ReimuActionStateStaging.hpp"', 'dispatch_indexed_event_member('
    require(source.count(include) == 1 and source.count(token) > 0, 'root call/include boundary changed')
    source = source.replace(include, include+'\n#include "FighterLandingDeclaration.hpp"')
    source = source.replace(token, 'reinterpret_cast<FighterLandingTransitionView *>(this)->'+token)
    direct_source = output/'RootDirect.cpp'
    direct_source.write_bytes(source.replace('\n', '\r\n').encode())
    bindings = ROOT/'config/reimu-root-probe-bindings.toml'
    binding_text = bindings.read_text()
    require(binding_text.count('[rel32]') == 1 and '"'+EVENT+'"' not in binding_text,
            'private direct-call binding boundary changed')
    private_bindings = output/'direct-bindings.toml'
    private_bindings.write_text(binding_text.replace(
        '[rel32]', '[rel32]\n"'+EVENT+'" = "0x004359F0"', 1))
    caller_source = output/'callers.cpp'
    caller_source.write_bytes(('''#include "ReimuActionStateStaging.hpp"
#include "FighterLandingDeclaration.hpp"
extern "C" __declspec(dllexport) void reimu_event_via_alias(
    th105::ReimuActionStatePreludeView *actor, unsigned index) {
    actor->dispatch_indexed_event_member(index);
}
extern "C" __declspec(dllexport) void reimu_event_direct(
    th105::FighterLandingTransitionView *actor, unsigned index) {
    actor->dispatch_indexed_event_member(index);
}
''').replace('\n', '\r\n').encode())
    pinned_inputs = (Path(__file__), ROOT/'scripts/probe-reimu-atan2-visibility.py', SOURCE,
                     base/'receipt.json', base/'ReimuRoot.cpp', header, direct_source,
                     output/'FighterLandingDeclaration.hpp', output/header.name,
                     caller_source, private_bindings)
    hashes = {str(path): linked_pe.sha(path) for path in pinned_inputs}
    commands = {}

    def compile_object(label, original, source, extra=()):
        obj = output/(label+'.obj')
        command = [('/Fo'+helper.windows(obj) if arg.startswith('/Fo') else arg)
                   for arg in original]
        command[-1] = helper.windows(source)
        command[-1:-1] = extra
        run(command, output/(label+'.log'), environment)
        commands[label] = command
        return obj

    require('/gl' not in [arg.lower() for arg in recipe['inputs']['command']], 'provider already has IR')
    provider_gl = compile_object('provider-gl', recipe['inputs']['command'], SOURCE, ('/GL',))
    ordinary_recipe = json.loads((base/'ordinary.compile-receipt.json').read_text())['inputs']['command']
    gl_recipe = json.loads((base/'root.compile-receipt.json').read_text())['inputs']['command']
    direct_ordinary = compile_object('root-direct-ordinary', ordinary_recipe, direct_source)
    relocations = load('reimu_method_visibility_relocations', 'audit-reimu-root-relocations.py')
    direct_anchor = relocations.audit(direct_ordinary, private_bindings)
    require(direct_anchor['source_replayed_sha256'] == proof['canonical_replayed_sha256'],
            'ordinary direct-call root changed any canonical payload byte')
    direct_gl = compile_object('root-direct-gl', gl_recipe, direct_source)
    caller_gl = compile_object('callers-gl', gl_recipe, caller_source)
    signature = (base/'root.obj').read_bytes()[:4]
    require(all(path.read_bytes()[:4] == signature for path in (provider_gl, direct_gl, caller_gl)),
            'private objects do not share the genuine root IL signature')

    copied = output/'inputs'
    copied.mkdir(exist_ok=True)
    manifest = {}
    for arg in producer['link_commands'][0]:
        if arg.lower().startswith('z:\\') and arg.lower().endswith(('.obj', '.lib')):
            path = helper.linux(arg)
            manifest[str(path)] = linked_pe.sha(path)
            if path.suffix.lower() == '.obj':
                require(path.parent == base, 'object input is outside the verified base')
                (copied/path.name).write_bytes(path.read_bytes())
    for name in ('receipt.json', 'ordinary.obj', 'ReimuRoot.dll', 'ReimuRoot.map'):
        manifest[str(base/name)] = linked_pe.sha(base/name)
    qualification = relocations.audit(base/'ordinary.obj')
    mapper = load('reimu_method_visibility_coff', 'compare-giant-action-switches.py')
    ordinary = mapper.CoffObject(base/'ordinary.obj', symbol_base=auditor.SYMBOL).text
    links, replays = {}, {}
    witness_observations = None
    for label in ('alias', 'direct', 'witness'):
        image, map_path = output/(label+'.dll'), output/(label+'.map')
        link, replacements = [], Counter()
        for arg in producer['link_commands'][0]:
            if arg.upper().startswith('/OUT:'):
                arg = '/OUT:'+helper.windows(image)
            elif arg.upper().startswith('/MAP:'):
                arg = '/MAP:'+helper.windows(map_path)
            elif arg.lower().startswith('z:\\') and arg.lower().endswith('.obj'):
                path = helper.linux(arg)
                if path.name == UNIT+'.obj':
                    arg = helper.windows(provider_gl);replacements['provider'] += 1
                elif path.name == 'root.obj' and label == 'direct':
                    arg = helper.windows(direct_gl);replacements['root'] += 1
                else:
                    arg = helper.windows(copied/path.name)
            link.append(arg)
        require(replacements == {'provider': 1, **({'root': 1} if label == 'direct' else {})},
                'unexpected private provider/root replacement inventory')
        if label == 'witness':
            link.append(helper.windows(caller_gl))
        run(link, output/(label+'-link.log'), environment)
        links[label] = link
        replays[label], pe, functions = root_replay(
            image, map_path, ordinary, qualification, producer, auditor)
        if label == 'witness':
            witness_observations = small_callers(pe, functions)
    require(all(linked_pe.sha(Path(path)) == digest for path, digest in manifest.items()),
            'base object/library/producer files changed during private linking')
    require(all(linked_pe.sha(Path(path)) == digest for path, digest in hashes.items()),
            'source/declaration/probe inputs changed during the experiment')
    result = {'schema': 'th105-reimu-method-visibility-v1', 'diagnostic_only': True,
              'target_sha256': linked_pe.comparator().verify_target(),
              'base_canonical_payload_sha256': proof['canonical_replayed_sha256'],
              'tool_pins': producer['tool_pins'], 'input_hashes': hashes,
              'ordinary_provider_comparisons': anchor['comparisons'],
              'ordinary_direct_root': {'object_sha256': linked_pe.sha(direct_ordinary),
                                      'canonical_payload_sha256': direct_anchor['source_replayed_sha256']},
              'anchor_command': anchor_command, 'compile_commands': commands, 'link_commands': links,
              'base_inputs_unchanged': manifest, 'root_replays': replays,
              'small_callers': witness_observations,
              'generated_object_sha256': {path.name: linked_pe.sha(path)
                                         for path in (provider_gl, direct_ordinary, direct_gl, caller_gl)},
              'runner_cpu_affinity': sorted(os.sched_getaffinity(0)),
              'runner_nice': os.getpriority(os.PRIO_PROCESS, 0),
              'host_children_peak_rss_kib': resource.getrusage(resource.RUSAGE_CHILDREN).ru_maxrss,
              'scope': 'actual complete provider source and true forwarding witnesses; complete root caller '
                       'payload correspondence only; no execution, provider-IR ABI acceptance, original TU '
                       'or optimizer-size-threshold claim, root exact credit or default-profile change'}
    (output/'receipt.json').write_text(json.dumps(result, indent=2)+'\n')
    return result


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--base-dir', type=Path, default=ROOT/'build/reimu-ltcg')
    parser.add_argument('--output-dir', type=Path, default=ROOT/'build/reimu-method-visibility')
    args = parser.parse_args()
    try:
        result = probe(args.base_dir, args.output_dir)
    except (KeyError, OSError, ValueError, StopIteration, subprocess.SubprocessError) as error:
        parser.exit(2, f'Reimu method visibility probe failed: {error}\n')
    print(json.dumps({'root_replays': result['root_replays'], 'small_callers': result['small_callers'],
                      'host_children_peak_rss_kib': result['host_children_peak_rss_kib']}, indent=2))
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
