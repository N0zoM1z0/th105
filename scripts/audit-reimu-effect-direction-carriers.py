#!/usr/bin/env python3
"""Compare real Reimu effect115 entry arguments and airborne landing returns."""

import argparse
from collections import Counter
import importlib.util
import itertools
import json
from pathlib import Path
import struct
import sys


ROOT = Path(__file__).resolve().parents[1]
ACTIONS = (600, 601, 602, 604, 605, 606, 608, 650, 651, 658)
GROUND_ACTIONS = (600, 601, 602, 604, 605, 606)
# Observed CALL sites inside the hash-attested81550-byte v1.06a root.
EFFECT_CALLERS = {
    600: 0x4886C5, 601: 0x488902, 602: 0x4886C5,
    604: 0x488B96, 605: 0x488CEB, 606: 0x488EB9,
    608: 0x4890B2, 650: 0x4886C5, 651: 0x488902, 658: 0x48A7D3,
}
LANDING_CALLERS = {
    600: 0x488517, 601: 0x4886E8, 602: 0x488912,
    604: 0x488AD6, 605: 0x488C41, 606: 0x488DFC,
    608: 0x488F83, 650: 0x48A25A, 651: 0x48A45D, 658: 0x48A6AE,
}


def load_oracle():
    spec = importlib.util.spec_from_file_location(
        'reimu_effect_carrier_void', ROOT / 'scripts/audit-reimu-void-root.py')
    oracle = importlib.util.module_from_spec(spec)
    sys.modules[spec.name] = oracle
    spec.loader.exec_module(oracle)
    return oracle


def cases(oracle):
    base = {
        **next(oracle.cases(True)),
        'sequence': 0, 'counter': 0, 'timer': -1, 'frame': 2,
        'vy': 0x40A00000, 'ay': 0, 'transition': 'unexpired', 'duration': 3,
        'single_sequence': False, 'counter730': 0, 'counter732': 0,
        'counter734': 0, 'cohort': 'effect_carriers',
    }
    for action, facing, control_word, x, y in itertools.product(
            ACTIONS, (-128, -1, 0, 1, 127), (0x27F, 0x37F),
            (400.0, 640.0), (0.0, 150.0)):
        yield {
            **base, 'action': action, 'facing': facing,
            'control_word': control_word, 'x': x, 'y': y,
            'frame': 6 if action in (604, 605, 606)
                     else 4 if action in (608, 658) else 2,
            'timer': 0 if action in (604, 605, 606) else -1,
        }


def audit(path):
    oracle = load_oracle()
    rows = tuple(cases(oracle))
    if len(rows) != 400:
        raise ValueError('effect carrier input matrix changed')
    counts = Counter()
    original_audit = oracle.low.audit
    original_check = oracle.check_target_case

    def check_target(case, result, sites):
        original_check(case, result, sites)
        action = case['action']
        if ((LANDING_CALLERS[action] in sites) != (action in GROUND_ACTIONS)):
            raise ValueError('effect input bypassed its actual landing guard')
        airborne_miss = action in GROUND_ACTIONS and case['y'] == 150.0
        if airborne_miss:
            if (EFFECT_CALLERS[action] in sites or result['endpoint'] != 'ret'
                    or struct.unpack_from('<h', result['actor'], 0x13C)[0] != 9):
                raise ValueError('airborne ground action bypassed falling action9')
            counts[('airborne_ret', action)] += 1
        else:
            if EFFECT_CALLERS[action] not in sites or result['endpoint'] != 'request':
                raise ValueError('effect input bypassed its actual effect115 entry')
            counts[('effect', action)] += 1

    def adapter(object_path, smoke=False, selected_cohorts=None, *, contract=None):
        contract.cases = lambda smoke=False: iter(rows)
        contract.COHORT_COUNTS = {'effect_carriers': 400}
        contract.SUPPORT_PATHS = (*contract.SUPPORT_PATHS, Path(__file__))
        return original_audit(object_path, False, ['effect_carriers'], contract=contract)

    oracle.check_target_case = check_target
    oracle.low.audit = adapter
    try:
        result = oracle.audit(path)
    finally:
        oracle.low.audit = original_audit
        oracle.check_target_case = original_check
    if (sum(counts[('effect', action)] for action in ACTIONS) != 280
            or any(counts[('effect', action)] != (20 if action in GROUND_ACTIONS else 40)
                   for action in ACTIONS)
            or any(counts[('airborne_ret', action)] != 20 for action in GROUND_ACTIONS)):
        raise ValueError('required effect/airborne outcomes changed')
    result['required_effect115_entries'] = {
        str(action): {'site': hex(EFFECT_CALLERS[action]), 'count': counts[('effect', action)]}
        for action in ACTIONS
    }
    result['required_airborne_returns'] = {
        str(action): counts[('airborne_ret', action)] for action in GROUND_ACTIONS
    }
    result['scope'] += (
        ';400 inputs across ten actions, five facing bytes, two X/Y values and two x87 '
        'precisions;280 real effect115 entries and120 native action9 returns; actual '
        'landing guards/callbacks, entry arguments/state/trace; no returning effect '
        'construction or world proof')
    return result


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('object', type=Path, help='qualified complete void-root VC8 COFF object')
    args = parser.parse_args()
    result = audit(args.object)
    print(json.dumps(result, indent=2))
    return int(bool(result['mismatch_count']))


if __name__ == '__main__':
    raise SystemExit(main())
