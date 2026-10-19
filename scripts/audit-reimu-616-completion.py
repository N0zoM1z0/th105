#!/usr/bin/env python3
"""Audit action616's native completion inside the qualified complete Reimu root."""

from collections import Counter
import argparse
import importlib.util
import itertools
import json
from pathlib import Path
import sys


ROOT = Path(__file__).resolve().parents[1]
COHORT_COUNTS = {
    'motion': 108, 'nodes': 252, 'hover': 1176, 'hover_shape': 10,
    'texture': 16, 'branches': 14, 'completion616': 320,
}
COMPLETED_BY_COHORT = {'motion': 2, 'texture': 8, 'completion616': 320}
# Observed target489EFC ->479486 ->47948F ->479498 inside root478FA0.
COMPLETION_ENTRY = 0x479486
COMPLETION_SITES = {0x489EF5, 0x489EFC, 0x479486, 0x47948F, 0x479498}


def load_oracle():
    spec = importlib.util.spec_from_file_location(
        'reimu_616_completion_void', ROOT / 'scripts/audit-reimu-void-root.py')
    oracle = importlib.util.module_from_spec(spec)
    sys.modules[spec.name] = oracle
    spec.loader.exec_module(oracle)
    return oracle


def cases(oracle, family):
    base = next(oracle.cases(True))
    for case in family.cases():
        if case['action'] == 616 and case['cohort'] not in ('integration', 'handoff', 'default'):
            yield {**base, **case}
    for facing, y, x, cw, player, own, peer in itertools.product(
            (-128, -1, 0, 1, 127), (0.0, 150.0), (400.0, 640.0),
            (0x27F, 0x37F), (0, 1), (0, 2), (0, 1)):
        yield {
            **base, 'action': 616, 'sequence': 0, 'single_sequence': True,
            'transition': 'terminal', 'facing': facing, 'y': y, 'x': x,
            'control_word': cw, 'player': player, 'texture_duration': own,
            'peer_texture_duration': peer, 'cohort': 'completion616',
        }


def audit(path):
    oracle = load_oracle()
    family = oracle.load('reimu_616_completion_middle', 'audit-reimu-high-middle-actions.py')
    rows = tuple(cases(oracle, family))
    if dict(Counter(case['cohort'] for case in rows)) != COHORT_COUNTS:
        raise ValueError('616 completion input matrix changed')
    original_audit = oracle.low.audit
    original_check = oracle.check_target_case
    outcomes, completed_by_cohort = Counter(), Counter()

    def check_target(case, result, sites):
        original_check(case, result, sites)
        completed = COMPLETION_ENTRY in sites
        if completed and (result['endpoint'] != 'ret'
                          or not COMPLETION_SITES.issubset(sites)):
            raise ValueError('616 completion bypassed actual advance/shared call/RET')
        forced = (case['cohort'] == 'completion616'
                  or (case['cohort'] == 'motion' and case.get('single_sequence')
                      and case['sequence'] == 0))
        if forced and not completed:
            raise ValueError('616 supplied terminal input bypassed shared completion')
        if not completed and 0x47948F in sites:
            raise ValueError('616 noncompletion unexpectedly called the shared setter')
        if (result['endpoint'] == 'request'
                and result['spawn_request'][:2] != (0x465190, 866)):
            raise ValueError('616 input bypassed its real first owned866 request')
        outcomes['completed' if completed else result['endpoint']] += 1
        if completed:
            completed_by_cohort[case['cohort']] += 1

    def adapter(object_path, smoke=False, selected_cohorts=None, *, contract=None):
        contract.cases = lambda smoke=False: iter(rows)
        contract.COHORT_COUNTS = COHORT_COUNTS
        contract.SUPPORT_PATHS = (*contract.SUPPORT_PATHS, Path(__file__), Path(family.__file__))
        return original_audit(object_path, False, list(COHORT_COUNTS), contract=contract)

    oracle.low.audit = adapter
    oracle.check_target_case = check_target
    try:
        result = oracle.audit(path)
    finally:
        oracle.low.audit = original_audit
        oracle.check_target_case = original_check
    if (dict(outcomes) != {'completed': 330, 'ret': 1423, 'request': 143}
            or dict(completed_by_cohort) != COMPLETED_BY_COHORT):
        raise ValueError('616 required native completion/return/request outcomes changed')
    result['required_completion_outcomes'] = dict(outcomes)
    result['required_completed_cohorts'] = dict(completed_by_cohort)
    result['scope'] += (
        ';1896 inputs inside the complete root, including320 supplied seq0 terminal '
        'states;330 actual native advance/shared-action0/RET chains,1423 other RETs '
        'and143 first owned866 entries; no returning owned-object/effect continuation '
        'or original616 function-boundary claim')
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
