#!/usr/bin/env python3
"""Build a real-source static-CRT CIL diagnostic; do not award exact credit."""
import json
import linked_pe as core

UNIT = {
    'kind': 'linked_candidate',
    'source': 'src/battle/BattleInfoRecordUpdate.cpp',
    'object': 'build/frontier-info-runtime-natural-20261104/ActualCil.dll',
    'profile': 'vc8-sp1-ltcg-o2',
    'enable_gs': False,
    'link_runtime': 'static',
    'link_data_targets': [],
    'functions': [{
        'address': '0x0046FF30',
        'symbol_base': '?update_runtime_46ff30@BattleInfoRecordF8@th105@@QAEXXZ',
        'rel32_targets': ['__invalid_parameter_noinfo=0x0068A143'],
    }],
}

if __name__ == '__main__':
    try:
        build = core.build_linked('private-info-update-real-cil', UNIT)
        comparisons = core.compare_linked('private-info-update-real-cil', UNIT, set())
        print(json.dumps(dict(scope='real source and static CRT; root export is diagnostic only',
                              build=build, comparisons=comparisons), indent=2))
    except (OSError, ValueError, KeyError, RuntimeError) as exc:
        raise SystemExit(str(exc))
