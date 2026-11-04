#!/usr/bin/env python3
"""One real-source CIL diagnostic; never award exact credit from this export."""
import json
from pathlib import Path
import linked_pe as core
from workflow_manifest import ROOT

PRIVATE = ROOT / '.analysis/frontier-input-real-cil-20261104/InputPipeline.cpp'
UNIT = {
    'kind': 'linked_candidate',
    'source': '.analysis/frontier-input-real-cil-20261104/InputPipeline.cpp',
    'object': 'build/frontier-input-real-cil-20261104/Actual.dll',
    'profile': 'vc8-sp1-ltcg-o2',
    'enable_gs': False,
    'link_runtime': 'static',
    'link_data_targets': [
        '?g_direct_input_backend@th105@@3UDirectInputBackend@1@A=?g_direct_input_backend@th105@@3UDirectInputBackend@1@A',
    ],
    # Real existing provider is a normal COFF input; no helper stubs or forced
    # exports. This diagnostic uses the lower-level builder, not a manifest unit.
    'linked_coff_sources': ['src/input/InputManager.cpp'],
    'functions': [{
        'address': '0x00409DA0',
        'symbol_base': '?update_player_input_counters_from_raw@CInputManager@th105@@UAEXXZ',
        'rel32_targets': [
            '?get_gamepad_state@DirectInputBackend@th105@@QAEPAURawGamepadState@2@H@Z=0x0040D990',
            '__invalid_parameter_noinfo=0x0068A143',
        ],
    }],
}


def main():
    source = (ROOT / 'src/input/InputPipeline.cpp').read_text()
    include = '#include "InputCluster.hpp"'
    definition = 'DirectInputBackend g_direct_input_backend;'
    if source.count(include) != 1 or source.count(definition) != 1:
        raise ValueError('input source no longer has the expected natural TU split')
    # Model a separate definition of the real backend; its target data address
    # is bound and verified by linked_pe, not replaced by a callable stub.
    source = source.replace(include, '#include "input/InputCluster.hpp"')
    source = source.replace(definition, 'extern DirectInputBackend g_direct_input_backend;')
    PRIVATE.parent.mkdir(parents=True, exist_ok=True)
    PRIVATE.write_text(source)
    core.build_linked('private-input-real-cil', UNIT)
    results = core.compare_linked('private-input-real-cil', UNIT, set())
    result = results[0]
    print(json.dumps({
        'scope': 'diagnostic root export, real source and real COFF provider; not a full game link',
        'result': result['result'], 'target_size': result['target_size'],
        'candidate_size': result['object_section_tail_size'],
        'candidate_sha256': result.get('object_compared_sha256'),
        'first_mismatch': result.get('first_mismatch'),
    }, indent=2))

if __name__ == '__main__':
    main()
