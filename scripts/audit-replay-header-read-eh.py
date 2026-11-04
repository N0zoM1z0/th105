#!/usr/bin/env python3
"""Replay the complete replay-header reader's emitted EH code and metadata."""
import hashlib
import importlib.util
import json
from pathlib import Path
import struct

import linked_pe as core
from coff_exception_rtti import Reader
from workflow_manifest import ROOT, load_manifest, unit_input_digest, compiler_sha256

UNIT = 'exact-first-replay-header-read'
SYMBOL = '?read_header_code@ReplayHeaderServiceView@th105@@QAEHPBD@Z'
CODE, META = 0x6B7B40, 0x6DDC58
CODE_SHA = '5a41b7a61eee1df3bec6814f600a4bd60d18cef22cce476e17418dfd7aa975fc'
META_SHA = 'e4ea60fe9e86483656178fff1a48a4dd5bc490236133a188e2ab667061be8b26'

def require(value, message):
    if not value:
        raise ValueError(message)

def check_metadata(data):
    require(len(data) == 44, 'complete unwind/FuncInfo extent differs')
    require(struct.unpack('<iI9I', data) == (-1, CODE, 0x19930522, 1, META, 0, 0, 0, 0, 0, 1),
            'unwind action or FuncInfo fields differ')

def audit():
    c = core.comparator(); target_sha = c.verify_target()
    unit = load_manifest()['units'][UNIT]
    require(unit.get('source') == 'src/ui/ReplayHeaderRead.cpp' and unit.get('profile') == 'vc8-sp1-probe-o2'
            and unit.get('enable_gs') is True, 'reader source/compiler profile differs')
    obj = ROOT / unit['object']
    record = json.loads(obj.with_suffix(obj.suffix + '.provenance.json').read_text())
    digest, _ = unit_input_digest(UNIT, unit)
    require(record.get('unit') == UNIT and record.get('input_digest') == digest
            and record.get('object_sha256') == core.sha(obj)
            and record.get('compiler_sha256') == compiler_sha256(), 'fresh reader provenance required')
    r = Reader(obj); handler = '__ehhandler$' + SYMBOL; info = '__ehfuncinfo$' + SYMBOL
    unwind = '__unwindtable$' + SYMBOL; action = '__unwindfunclet$' + SYMBOL + '$0'
    code_sec = r.section(handler); meta_sec = r.section(info)
    require(code_sec.name == '.text$x' and code_sec.raw_size == 48 and r.symbol(handler).value == 8
            and meta_sec.name == '.xdata$x' and meta_sec.raw_size == 44 and r.symbol(info).value == 8
            and r.symbol(unwind).value == 0 and r.symbol(action).value == 0
            and r.symbol(handler).section_number == r.symbol(action).section_number,
            'EH section ownership or extent differs')
    require(r.refs(action, 48) == [(4, 20, '??1?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@QAE@XZ'),
            (21, 20, '@__security_check_cookie@4'), (34, 20, '@__security_check_cookie@4'),
            (39, 6, info), (44, 20, '___CxxFrameHandler3')], 'EH complete code relocation roles differ')
    require(r.refs(unwind, 8) == [(4, 6, action)] and r.refs(info, 36) == [(8, 6, unwind)],
            'EH metadata relocation roles differ')
    sp = importlib.util.spec_from_file_location('replay_header_eh_sections', ROOT / 'scripts/audit-select-constructor.py')
    helper = importlib.util.module_from_spec(sp); sp.loader.exec_module(helper)
    targets = {info: (META + 8, c.target_bytes(META + 8, 36), frozenset({0}), 'address'),
               unwind: (META, c.target_bytes(META, 8), frozenset({0}), 'address'),
               action: (CODE, c.target_bytes(CODE, 1), frozenset({0}), 'address')}
    calls = {'??1?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@QAE@XZ': 0x401E00,
             '@__security_check_cookie@4': 0x689D25, '___CxxFrameHandler3': 0x6899E7}
    code = helper.replay_section(r.cf, code_sec, CODE, calls, targets, c.target_bytes)
    meta = helper.replay_section(r.cf, meta_sec, META, calls, targets, c.target_bytes)
    check_metadata(meta)
    require(code == c.target_bytes(CODE, 48) and hashlib.sha256(code).hexdigest() == CODE_SHA,
            'complete EH code differs')
    require(meta == c.target_bytes(META, 44) and hashlib.sha256(meta).hexdigest() == META_SHA,
            'complete EH metadata differs')
    return dict(result='exact', target_sha256=target_sha, code_address=hex(CODE), code_size=48,
                code_sha256=CODE_SHA, metadata_address=hex(META), metadata_size=44,
                metadata_sha256=META_SHA, states=1, scope='static complete remote EH only; no OS exception execution')

if __name__ == '__main__':
    try:
        print(json.dumps(audit(), indent=2))
    except (OSError, ValueError, KeyError, TypeError, struct.error) as exc:
        raise SystemExit(str(exc))
