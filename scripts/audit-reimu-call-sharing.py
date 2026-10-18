#!/usr/bin/env python3
"""Compare complete Reimu call-site action sets, without matching credit."""
from __future__ import annotations

import argparse
from collections import Counter, defaultdict
import hashlib
import importlib.util
import json
from pathlib import Path
import sys
import tomllib

from capstone import x86_const as x

ROOT = Path(__file__).resolve().parents[1]
DEFAULT_ENTRY = 0x48CE1F
DIRECT_ENTRIES = {300: 0x47CBBD, 560: 0x48790B}


def require(condition, message):
    if not condition:
        raise ValueError(message)


def load(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / filename)
    module = importlib.util.module_from_spec(spec)
    sys.modules[name] = module
    spec.loader.exec_module(module)
    return module


def compare_sites(target, source):
    """Keep physical-site multiplicity and complete sets, including empty sets."""
    groups = []
    for sites in (target, source):
        grouped = defaultdict(list)
        for site, actions in sorted(sites.items()):
            grouped[tuple(sorted(actions))].append(hex(site))
        groups.append(grouped)
    counts = [Counter({key: len(value) for key, value in side.items()}) for side in groups]
    actions = sorted({action for side in counts for key in side for action in key})
    deltas = []
    for action in actions:
        values = [sum(count for key, count in side.items() if action in key) for side in counts]
        if values[0] != values[1]:
            deltas.append({'action': action, 'target': values[0], 'source': values[1]})
    return {
        'partition_equal': counts[0] == counts[1],
        'per_action_count_deltas': deltas,
        'partitions': [
            {'actions': list(key), 'target_sites': groups[0].get(key, []),
             'source_sites': groups[1].get(key, [])}
            for key in sorted(groups[0].keys() | groups[1].keys())],
    }


def direct_entry(graph, action, address):
    """Require the reviewed WORD13C selector origin and an unmodified JE edge."""
    choices = []
    for index, row in enumerate(graph.rows):
        operands = row.operands
        if not (row.mnemonic == 'cmp' and operands[0].type == x.X86_OP_REG
                and operands[0].size == 4 and operands[1].type == x.X86_OP_IMM
                and operands[1].imm == action):
            continue
        origins = graph.reaching_writes(row.address, operands[0].reg)
        require(len(origins) == 1, 'direct selector has ambiguous reaching definitions')
        origin = next(iter(origins))
        require(origin.mnemonic == 'movsx' and origin.operands[0].type == x.X86_OP_REG
                and origin.operands[0].reg == operands[0].reg
                and origin.operands[1].type == x.X86_OP_MEM
                and origin.operands[1].size == 2
                and origin.operands[1].mem.base == x.X86_REG_ESI
                and not origin.operands[1].mem.index
                and not origin.operands[1].mem.segment
                and origin.operands[1].mem.disp == 0x13C,
                'direct selector is not the signed actor WORD13C load')
        receivers = graph.reaching_writes(origin.address, x.X86_REG_ESI)
        require(len(receivers) == 1, 'direct selector receiver is ambiguous')
        receiver = next(iter(receivers))
        require(receiver.address == address + 15 and receiver.mnemonic == 'mov'
                and receiver.operands[0].type == x.X86_OP_REG
                and receiver.operands[0].reg == x.X86_REG_ESI
                and receiver.operands[1].type == x.X86_OP_REG
                and receiver.operands[1].reg == x.X86_REG_ECX,
                'direct selector does not use the attested entry receiver copy')
        for branch in graph.rows[index + 1:index + 4]:
            if branch.mnemonic == 'je':
                require(branch.operands[0].type == x.X86_OP_IMM
                        and branch.operands[0].imm in graph.reachable,
                        'direct action edge is not a reachable instruction')
                choices.append(branch.operands[0].imm)
                break
            if (x.X86_REG_EFLAGS in branch.regs_access()[1]
                    or branch.mnemonic in ('jmp', 'ret', 'call')):
                break
    require(len(choices) == 1, 'direct action equality edge is absent or ambiguous')
    return choices[0]


def virtual_slot_candidates(graph):
    """Keep one uncertain slot domain per qualified physical indirect call."""
    indirect = {row.address: row for row in graph.rows
                if row.address in graph.reachable and row.mnemonic == 'call'
                and row.operands[0].type != x.X86_OP_IMM}
    require(all(row.operands[0].type == x.X86_OP_REG for row in indirect.values()),
            'indirect call is not a qualified register call')
    require(indirect.keys() == graph.virtual_definitions.keys(),
            'indirect calls and qualified slot definitions disagree')
    identities = {}
    for site, definitions in graph.virtual_definitions.items():
        slots = tuple(sorted(set(definitions.values())))
        require(slots and set(slots) <= {8, 12, 20}, 'unreviewed indirect slot domain')
        identities[site] = slots
    return identities


def collect_sites(graph, entries):
    calls = {row.address: row.operands[0].imm for row in graph.rows
             if row.address in graph.reachable and row.mnemonic == 'call'
             and row.operands[0].type == x.X86_OP_IMM}
    returns = {row.address for row in graph.rows
               if row.address in graph.reachable and row.mnemonic == 'ret'}
    virtual = virtual_slot_candidates(graph)
    owners = {site: set() for site in calls.keys() | returns | virtual.keys()}
    for action, start in entries.items():
        require(start in graph.reachable, 'action entry is not a reachable instruction')
        for site in graph.reachable_from(start) & owners.keys():
            owners[site].add(action)
    by_callee = defaultdict(dict)
    for site, callee in calls.items():
        by_callee[callee][site] = owners[site]
    by_slots = defaultdict(dict)
    for site, slots in virtual.items():
        by_slots[slots][site] = owners[site]
    return by_callee, {site: owners[site] for site in returns}, by_slots


def merge_slot_sites(groups):
    sites = {}
    for group in groups.values():
        require(not sites.keys() & group.keys(), 'physical indirect call has multiple slot identities')
        sites.update(group)
    return sites


def audit(path, *, diagnostic_oversize=False):
    stack = load('reimu_sharing_stack', 'audit-reimu-root-stack.py')
    graphs, original = [], stack.StackGraph

    class Capture(original):
        def __init__(self, *args, **kwargs):
            super().__init__(*args, **kwargs)
            graphs.append(self)

    stack.StackGraph = Capture
    try:
        qualification = stack.audit(path, stack.SUPPORTED_ACTIONS,
                                    diagnostic_oversize=diagnostic_oversize)
    finally:
        stack.StackGraph = original
    require(len(graphs) == 2, 'target/source graph inventory changed')
    require(not qualification['buffer_partition_mismatches']
            and not qualification['request_preparation_mismatches'],
            'root request/stack qualification failed')
    relocations = stack.load('reimu_sharing_relocations', 'audit-reimu-root-relocations.py')
    mapper = relocations.load('reimu_sharing_mapper', 'compare-giant-action-switches.py')
    tm = mapper.load_target_mapper()
    root = tm.select_root(tomllib.loads((ROOT / 'config/giant-action-switches.toml').read_text()),
                          'reimu-vslot28')
    obj = mapper.CoffObject(path, symbol_base=relocations.SYMBOL)
    mapping = mapper.compare_maps(
        tm.map_root(tm.PeImage(ROOT / 'resources/th105.exe'),
                    tm.load_function_rows(ROOT / 'config/functions.csv'), root),
        mapper.build_candidate_map(obj, root))
    entries = [{}, {}]
    for row in mapping['rows']:
        target = stack.ADDRESS + row['target_offset']
        if target == DEFAULT_ENTRY:
            continue
        require(len(row['candidate_offsets']) == 1, 'target primary group splits in source')
        for action in row['cases']:
            require(action not in entries[0], 'primary action appears in multiple groups')
            entries[0][action] = target
            entries[1][action] = stack.ADDRESS + row['candidate_offsets'][0]
    for action, target in DIRECT_ENTRIES.items():
        require(action not in entries[0], 'direct action also appears in a table')
        require(direct_entry(graphs[0], action, stack.ADDRESS) == target,
                'attested target direct edge changed')
        entries[0][action] = target
        entries[1][action] = direct_entry(graphs[1], action, stack.ADDRESS)
    require(len(entries[0]) == 128 and entries[0].keys() == entries[1].keys(),
            'nondefault action inventory changed')
    inventories = [collect_sites(graph, entry) for graph, entry in zip(graphs, entries)]
    callees = sorted(inventories[0][0].keys() | inventories[1][0].keys())
    rows = []
    for callee in callees:
        sides = [inventory[0].get(callee, {}) for inventory in inventories]
        rows.append({'callee': hex(callee), 'physical_counts': [len(side) for side in sides],
                     **compare_sites(*sides)})
    slot_rows = []
    for slots in sorted(inventories[0][2].keys() | inventories[1][2].keys()):
        sides = [inventory[2].get(slots, {}) for inventory in inventories]
        slot_rows.append({'slot_candidates': [hex(slot) for slot in slots],
                          'physical_counts': [len(side) for side in sides],
                          **compare_sites(*sides)})
    return {
        'schema': 'th105-reimu-call-sharing-v1', 'target_sha256': qualification['target_sha256'],
        'object_sha256': qualification['object_sha256'], 'nondefault_actions': 128,
        'entries': [{'action': action, 'target': hex(entries[0][action]),
                     'source': hex(entries[1][action])} for action in sorted(entries[0])],
        'callee_count': len(rows),
        'callees_with_partition_differences': sum(not row['partition_equal'] for row in rows),
        'actions_with_call_count_differences': sorted({delta['action'] for row in rows
                                                     for delta in row['per_action_count_deltas']}),
        'calls': rows, 'returns': compare_sites(*(inventory[1] for inventory in inventories)),
        'slot_identity_count': len(slot_rows),
        'slot_call_physical_counts': [sum(len(sites) for sites in inventory[2].values())
                                     for inventory in inventories],
        'slot_identities_with_partition_differences': sum(not row['partition_equal'] for row in slot_rows),
        'actions_with_slot_count_differences': sorted({delta['action'] for row in slot_rows
                                                     for delta in row['per_action_count_deltas']}),
        'slot_calls': slot_rows,
        'indirect_calls': compare_sites(*(merge_slot_sites(inventory[2]) for inventory in inventories)),
        'diagnostic_oversize': diagnostic_oversize,
        'callable_excess': qualification['callable_excess'],
        'metadata_envelope_excess': qualification['metadata_envelope_excess'],
        'graphs': {name: {key: report[key] for key in ('frame', 'reachable_instructions')}
                   for name, report in qualification['graphs'].items()},
        'first_mismatch': qualification['first_mismatch'],
        'support_sha256': {**qualification['support_sha256'],
                           str(Path(__file__).relative_to(ROOT)):
                               hashlib.sha256(Path(__file__).read_bytes()).hexdigest()},
        'scope': 'read-only complete action-set/multiplicity census over qualified CFGs; '
                 'indirect slot candidates are load displacements, not identified methods/receivers; '
                 'empty sets are sites outside nondefault-action reachability; no path feasibility, '
                 'dynamic counts, argument/behavior equivalence, byte equality or matching credit',
    }


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('object', type=Path)
    parser.add_argument('--diagnostic-oversize', action='store_true', help='read-only; no execution')
    args = parser.parse_args()
    try:
        result = audit(args.object, diagnostic_oversize=args.diagnostic_oversize)
    except (KeyError, OSError, TypeError, ValueError) as error:
        parser.exit(2, f'Reimu call-sharing audit failed: {error}\n')
    print(json.dumps(result, indent=2))
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
