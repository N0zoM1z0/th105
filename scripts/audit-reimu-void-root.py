#!/usr/bin/env python3
"""Compare the generated void Reimu root, including actual upper defaults."""
from __future__ import annotations

import argparse
from collections import Counter
from functools import lru_cache
import importlib.util
import itertools
import json
from pathlib import Path
import struct
import sys
import tomllib
from types import SimpleNamespace

import unicorn

from reimu_740_mode_facts import load, packet

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location('reimu_void_previous', ROOT / 'scripts/audit-reimu-740-mode-shape.py')
previous = importlib.util.module_from_spec(spec)
sys.modules[spec.name] = previous
spec.loader.exec_module(previous)
low = previous.low
SYMBOL = '?run_action_dispatch_root@ReimuActionStatePreludeView@th105@@QAEXXZ'
HELPERS, CALL_TARGETS = previous.HELPERS, previous.CALL_TARGETS
LITERAL_BINDINGS = previous.LITERAL_BINDINGS
SUPPORT_PATHS = (Path(previous.__file__), ROOT / 'scripts/probe-reimu-action-source-shape.py',
                 ROOT / 'scripts/audit-reimu-late-low-actions.py',
                 ROOT / 'scripts/audit-reimu-movement-attack-actions.py', *previous.SUPPORT_PATHS)
SCHEMA = 'th105-reimu-void-root-native-v1'
SCOPE = ('void noargs thiscall candidate; actual helpers/RET and common-root defaults over the signed action domain; '
         '740 stops before indeterminate reads and world calls stop at real entry; no returning-world, '
         'arbitrary-stack, full-relocation or canonical-exact claim')
RANDOM_COHORTS = ('random_lifetimes', 'random124_lifetimes', 'movement_random_lifetimes')
LIFETIME_COHORTS = (*RANDOM_COHORTS, 'flight_effect_lifetimes')
COHORTS = ('integration', 'defaults', 'common_return', 'unresolved740', *LIFETIME_COHORTS)
SMOKE_COUNT = 26
ALLOW_SWITCH_METADATA = True


@lru_cache(maxsize=1)
def late_low_family():
    return load('reimu_void_random_effect_family', 'audit-reimu-late-low-actions.py')


def lifetime_families():
    family = late_low_family()
    return family, family.movement


@lru_cache(maxsize=1)
def default_actions():
    mapper = load('reimu_void_target_map', 'map-giant-action-switches.py')
    manifest = tomllib.loads((ROOT / 'config/giant-action-switches.toml').read_text())
    root = mapper.select_root(manifest, 'reimu-vslot28')
    target = mapper.map_root(mapper.PeImage(ROOT / 'resources/th105.exe'),
                             mapper.load_function_rows(ROOT / 'config/functions.csv'), root)
    known = {key for region in target['regions'] for group in region['groups']
             if group['destination'] != 0x48CE1F for key in group['cases']} | {300, 560}
    if len(known) != 128:
        raise ValueError('canonical nondefault action domain changed')
    choices = {-32768, -1, 799, 800, 1000, 32766, 32767}
    choices.update(value for key in known for value in (key-1, key+1)
                   if -32768 <= value <= 32767 and value not in known)
    return tuple(sorted(choices-known))


def cases(smoke=False):
    base = {**next(previous.cases(True)), 'effect': 1}
    for case in previous.cases(True):
        yield {**case, 'cohort': 'integration'}
    if not smoke:
        for case in previous.cases():
            if case['cohort'] == 'integration':
                yield case
        for family in lifetime_families():
            for case in family.cases():
                if case['cohort'] in LIFETIME_COHORTS:
                    yield {**base, **case}
    choices = (-32768, 799, 32767) if smoke else default_actions()
    gates = ((0, 0),) if smoke else ((0, 0), (1, 0), (0, 1))
    for action, (entry, peer), cw in itertools.product(choices, gates, (0x27F, 0x37F)):
        yield {**base, 'cohort': 'defaults', 'action': action, 'entry_gate': entry,
               'peer_gate': peer, 'control_word': cw}
    for action, count, cw in itertools.product((799, 32767) if smoke else (799, 800, 1000, 32767),
                                                (0,) if smoke else (-1, 0), (0x27F, 0x37F)):
        yield {**base, 'cohort': 'common_return', 'action': action,
               'counter': count, 'execute_common': True, 'control_word': cw}
    for sequence, mode, cw in itertools.product((1, 6), (4,) if smoke else (4, 0xFFFFFFFF), (0x27F, 0x37F)):
        yield {**base, 'cohort': 'unresolved740', 'action': 740, 'sequence': sequence,
               'match_selector': mode, 'control_word': cw}


def check_target_case(case, result, sites):
    if case['cohort'] == 'defaults':
        if case['entry_gate'] or case['peer_gate']:
            if result['endpoint'] != 'ret' or any(call[0] == 0x4740C0 for call in result['calls']):
                raise ValueError('default entry gate did not return before dispatch')
        elif result['spawn_request'] != (0x4740C0,) or 0x48CE1F not in sites:
            raise ValueError('default action did not reach the original common call')
    elif case['cohort'] in RANDOM_COHORTS:
        family = late_low_family().movement if case['cohort'] == 'movement_random_lifetimes' else late_low_family()
        family.check_target_case(case, result, sites)
        observations = [call for call in result['calls'] if call[0] == 'pending_effect_arguments']
        direction = -case['facing'] if case['action'] in (201, 203, 224, 225) else case['facing']
        tail = struct.pack('<II', direction & 0xFF, 1).hex()
        if (len(observations) != 2 or observations[0][1:] != (1, tail)
                or observations[1][1] != 2 or len(observations[1][2]) != 24
                or observations[1][2][-16:] != tail):
            raise ValueError('target random effect lacks its pending direction/trailing arguments')
    elif case['cohort'] == 'flight_effect_lifetimes':
        late_low_family().check_target_case(case, result, sites)
        observations = [call for call in result['calls'] if call[0] == 'pending_flight_effect_arguments']
        tail = struct.pack('<II', case['facing'] & 0xFF, 1).hex()
        if (len(observations) != 2 or observations[0][1:] != ('sine', tail)
                or observations[1][1] != 'cosine' or len(observations[1][2]) != 24
                or observations[1][2][-16:] != tail):
            raise ValueError('target flight effect lacks its pending direction/trailing arguments')
    else:
        previous.check_target_case(case, result, sites)
    if case['cohort'] == 'common_return' and 0x48CE1F not in sites:
        raise ValueError('upper default common-return case bypassed the actual root default')


def audit(path, smoke=False, cohorts=None):
    facts = packet(path, symbol=SYMBOL)
    instances = []

    class VoidProbe(previous.Probe):
        candidate_return_kind = 'void'
        handled_action_max = 32767

        def __init__(self, *args, **kwargs):
            super().__init__(*args, **kwargs)
            self.return_bytes = Counter()
            instances.append(self)

        def evaluate(self, case):
            self.track_random_tails = case['cohort'] in RANDOM_COHORTS
            self.random_draw_count = 0
            self.track_flight_tails = case['cohort'] == 'flight_effect_lifetimes'
            self.flight_lookup_counts = Counter()
            result = super().evaluate(case)
            if result['endpoint'] == 'ret':
                self.return_bytes[self.engine.reg_read(low.r.UC_X86_REG_EAX) & 0xFF] += 1
            return result

        def step(self, uc, address, size):
            super().step(uc, address, size)
            if address == 0x4066B0 and getattr(self, 'track_random_tails', False):
                sp = uc.reg_read(low.r.UC_X86_REG_ESP)
                caller, = struct.unpack('<I', uc.mem_read(sp, 4))
                if low.ADDRESS <= caller < low.ADDRESS + low.SIZE:
                    self.random_draw_count += 1
                    if self.random_draw_count not in (1, 2):
                        raise ValueError('random effect executes more than two root MT calls')
                    # Read only: both original MT calls continue to their RET.
                    count = self.random_draw_count + 1
                    self.calls.append(('pending_effect_arguments', self.random_draw_count,
                                       bytes(uc.mem_read(sp + 4, count * 4)).hex()))
            if address in (0x406360, 0x4063D0) and getattr(self, 'track_flight_tails', False):
                sp = uc.reg_read(low.r.UC_X86_REG_ESP)
                caller, = struct.unpack('<I', uc.mem_read(sp, 4))
                if low.ADDRESS <= caller < low.ADDRESS + low.SIZE:
                    self.flight_lookup_counts[address] += 1
                    if self.flight_lookup_counts[address] > 2:
                        raise ValueError('flight effect executes more than two lookups of one kind')
                    if self.flight_lookup_counts[address] == 2:
                        kind, count = ('sine', 2) if address == 0x406360 else ('cosine', 3)
                        # Read only, above this real cdecl lookup's phase argument.
                        self.calls.append(('pending_flight_effect_arguments', kind,
                                           bytes(uc.mem_read(sp + 8, count * 4)).hex()))

    contract = SimpleNamespace(**vars(sys.modules[__name__]))
    contract.Probe = previous.boundary_probe(facts, base=VoidProbe)
    contract.COHORT_COUNTS = {'integration': 1010, 'defaults': len(default_actions())*6,
                              'common_return': 16, 'unresolved740': 8,
                              **{name: count for family in lifetime_families()
                                 for name, count in family.COHORT_COUNTS.items() if name in LIFETIME_COHORTS}}
    result = low.audit(path, smoke, cohorts, contract=contract)
    result['mode_structure'] = facts
    result['observed_return_low_bytes'] = {('source' if p.candidate else 'target'): dict(p.return_bytes)
                                          for p in instances}
    result['default_action_samples'] = list(default_actions())
    return result


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('object', type=Path)
    selection = parser.add_mutually_exclusive_group()
    selection.add_argument('--smoke', action='store_true')
    selection.add_argument('--cohort', action='append', choices=COHORTS)
    args = parser.parse_args()
    try:
        result = audit(args.object, args.smoke, args.cohort)
    except (KeyError, OSError, ValueError, unicorn.UcError) as error:
        parser.exit(2, f'Reimu void-root audit failed: {error}\n')
    print(json.dumps(result, indent=2))
    raise SystemExit(1 if result['mismatch_count'] else 0)
