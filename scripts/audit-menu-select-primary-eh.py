#!/usr/bin/env python3
"""Replay menu selection's complete emitted remote EH code and metadata."""
import hashlib
import importlib.util
import json
import struct

import linked_pe as core
from coff_exception_rtti import Reader
from workflow_manifest import ROOT, load_manifest, unit_input_digest, compiler_sha256

UNIT = 'exact-first-menu-select-primary'
SYMBOL = '?update_primary_selection@CMenuSelect@th105@@AAE_NXZ'
CODE, META = 0x6b9c40, 0x6df910
CODE_SHA = '29cf8183f85244dc06bf88d2e57348032b61e417c6845a0e0eb4835de86a77db'
META_SHA = '47a533d208459d7070d297acda22a7b4d73443a0ba896315ed10bdf42297abbd'


def require(value, message):
    if not value: raise ValueError(message)


def check_metadata(data):
    require(len(data) == 76, 'complete FuncInfo and unwind extent differs')
    info = struct.unpack_from('<9I', data)
    require(info == (0x19930522, 5, META + 36, 0, 0, 0, 0, 0, 1), 'FuncInfo fields differ')
    actions = [struct.unpack_from('<iI', data, 36 + 8 * i) for i in range(5)]
    require(actions == [(-1, CODE + 11 * i) for i in range(5)], 'unwind actions differ')


def audit():
    c = core.comparator(); target = c.verify_target(); unit = load_manifest()['units'][UNIT]
    require(unit.get('source') == 'src/ui/MenuSelectPrimary.cpp' and unit.get('enable_gs') is True,
            'source or compiler profile differs')
    obj = ROOT / unit['object']; record = json.loads(obj.with_suffix(obj.suffix + '.provenance.json').read_text())
    digest, _ = unit_input_digest(UNIT, unit)
    require(record.get('unit') == UNIT and record.get('input_digest') == digest and
            record.get('object_sha256') == core.sha(obj) and record.get('compiler_sha256') == compiler_sha256(),
            'fresh compiler provenance required')
    r = Reader(obj); handler = '__ehhandler$' + SYMBOL; info = '__ehfuncinfo$' + SYMBOL
    unwind = '__unwindtable$' + SYMBOL; actions = ['__unwindfunclet$' + SYMBOL + '$' + str(i) for i in range(5)]
    code_sec = r.section(handler); meta_sec = r.section(info)
    require(code_sec.name == '.text$x' and code_sec.raw_size == 82 and r.symbol(handler).value == 55 and
            meta_sec.name == '.xdata$x' and meta_sec.raw_size == 76 and r.symbol(info).value == 0 and
            r.symbol(unwind).value == 36 and all(r.symbol(a).value == 11*i for i, a in enumerate(actions)),
            'EH section ownership or extent differs')
    expected_code_refs = [(11*i + 5, 20, '??3@YAXPAX@Z') for i in range(5)] + [
        (68, 20, '@__security_check_cookie@4'), (73, 6, info), (78, 20, '___CxxFrameHandler3')]
    require(r.refs(actions[0], 82) == expected_code_refs, 'EH code relocation roles differ')
    require(r.refs(info, 36) == [(8, 6, unwind)] and
            r.refs(unwind, 40) == [(8*i + 4, 6, actions[i]) for i in range(5)], 'EH metadata relocation roles differ')
    spec = importlib.util.spec_from_file_location('menu_eh_sections', ROOT / 'scripts/audit-select-constructor.py')
    helper = importlib.util.module_from_spec(spec); spec.loader.exec_module(helper)
    targets = {info:(META, c.target_bytes(META,36), frozenset({0}), 'address'),
               unwind:(META+36, c.target_bytes(META+36,40), frozenset({0}), 'address')}
    for i, action in enumerate(actions):
        targets[action] = (CODE+11*i, c.target_bytes(CODE+11*i,1), frozenset({0}), 'address')
    calls = {'??3@YAXPAX@Z':0x6898ea, '@__security_check_cookie@4':0x689d25,
             '___CxxFrameHandler3':0x6899e7}
    code = helper.replay_section(r.cf, code_sec, CODE, calls, targets, c.target_bytes)
    meta = helper.replay_section(r.cf, meta_sec, META, calls, targets, c.target_bytes)
    check_metadata(meta)
    require(code == c.target_bytes(CODE,82) and hashlib.sha256(code).hexdigest() == CODE_SHA,
            'complete EH code differs')
    require(meta == c.target_bytes(META,76) and hashlib.sha256(meta).hexdigest() == META_SHA,
            'complete EH metadata differs')
    return {'result':'exact', 'target_sha256':target, 'code_size':82, 'metadata_size':76, 'states':5,
            'scope':'static remote EH code and metadata only; root remains nonexact and OS exceptions untested'}

if __name__ == '__main__':
    try: print(json.dumps(audit(), indent=2))
    except (OSError, ValueError, KeyError, TypeError, struct.error) as exc: raise SystemExit(str(exc))
