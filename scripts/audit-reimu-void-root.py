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
SUPPORT_PATHS = (Path(previous.__file__), ROOT / 'scripts/probe-reimu-action-source-shape.py', *previous.SUPPORT_PATHS)
SCHEMA = 'th105-reimu-void-root-native-v1'
SCOPE = ('void noargs thiscall candidate; actual helpers/RET and common-root defaults over the signed action domain; '
         '740 stops before indeterminate reads and world calls stop at real entry; no returning-world, '
         'arbitrary-stack, full-relocation or canonical-exact claim')
COHORTS = ('integration', 'defaults', 'common_return', 'unresolved740')
SMOKE_COUNT = 26
ALLOW_SWITCH_METADATA = True


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
            result = super().evaluate(case)
            if result['endpoint'] == 'ret':
                self.return_bytes[self.engine.reg_read(low.r.UC_X86_REG_EAX) & 0xFF] += 1
            return result

    contract = SimpleNamespace(**vars(sys.modules[__name__]))
    contract.Probe = previous.boundary_probe(facts, base=VoidProbe)
    contract.COHORT_COUNTS = {'integration': 1010, 'defaults': len(default_actions())*6,
                              'common_return': 16, 'unresolved740': 8}
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
