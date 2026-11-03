#!/usr/bin/env python3
"""Replay the complete network replay-dispatch cleanup code and metadata."""
import importlib.util
import json
from pathlib import Path
import sys

import linked_pe as core
from coff_exception_rtti import Reader
from workflow_manifest import ROOT, compiler_sha256, load_manifest, unit_input_digest

UNIT = 'exact-first-network-replay-request-dispatch'
OWNER = '?dispatch@DispatchOwner@th105@@QAEXIPBVNetworkRequestReplay10@2@@Z'


def audit():
    unit = load_manifest()['units'][UNIT]
    path = ROOT / unit['object']
    provenance = json.loads(path.with_suffix(path.suffix + '.provenance.json').read_text())
    digest, _ = unit_input_digest(UNIT, unit)
    if not (provenance.get('unit') == UNIT and provenance.get('input_digest') == digest
            and provenance.get('compiler_sha256') == compiler_sha256()
            and provenance.get('profile') == unit['profile']
            and provenance.get('enable_gs') == unit['enable_gs']
            and provenance.get('object_sha256') == core.sha(path)):
        raise ValueError('fresh replay-dispatch object provenance required')
    spec = importlib.util.spec_from_file_location('replay_eh_sections', ROOT / 'scripts/audit-select-constructor.py')
    eh = importlib.util.module_from_spec(spec)
    sys.modules[spec.name] = eh
    spec.loader.exec_module(eh)
    c = core.comparator()
    sha = c.verify_target()
    read = c.target_bytes
    r = Reader(path)
    handler, info, unwind = ('__ehhandler$' + OWNER, '__ehfuncinfo$' + OWNER, '__unwindtable$' + OWNER)
    f0, f1 = ('__unwindfunclet$' + OWNER + '$0', '__unwindfunclet$' + OWNER + '$1')
    code_sec, meta_sec = r.section(handler), r.section(info)
    if not (code_sec.name == '.text$x' and code_sec.raw_size == 59 and r.symbol(handler).value == 16
            and r.symbol(f0).value == 0 and r.symbol(f1).value == 8
            and meta_sec.name == '.xdata$x' and meta_sec.raw_size == 52
            and r.symbol(info).value == 16 and r.symbol(unwind).value == 0):
        raise ValueError('unexpected complete EH section layout')
    targets = {'??1NetworkAckInfoPacket40@th105@@QAE@XZ': 0x44daf0,
               '??1ReplayPacket28@th105@@QAE@XZ': 0x44dab0,
               '@__security_check_cookie@4': 0x689d25, '___CxxFrameHandler3': 0x6899e7}
    data = {n: (at, read(at, size), frozenset({0}), 'address') for n, at, size in
            [(info, 0x6dff7c, 36), (unwind, 0x6dff6c, 16), (f0, 0x6ba560, 1), (f1, 0x6ba568, 1)]}
    code = eh.replay_section(r.cf, code_sec, 0x6ba560, targets, data, read)
    meta = eh.replay_section(r.cf, meta_sec, 0x6dff6c, targets, data, read)
    regions = {'eh_code': eh.region_result(code, read(0x6ba560, 59), 0x6ba560),
               'eh_metadata': eh.region_result(meta, read(0x6dff6c, 52), 0x6dff6c)}
    return {'result': 'exact' if all(x['exact'] for x in regions.values()) else 'mismatch',
            'target_sha256': sha, 'regions': regions, 'source_provenance_verified': True,
            'scope': 'bounded complete remote EH code and metadata; no integrated-link or runtime exception claim'}


if __name__ == '__main__':
    try:
        result = audit()
        print(json.dumps(result, indent=2))
        raise SystemExit(result['result'] != 'exact')
    except (OSError, ValueError, KeyError, RuntimeError) as exc:
        raise SystemExit(str(exc))
