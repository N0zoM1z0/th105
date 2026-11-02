#!/usr/bin/env python3
"""Whole original Boost matcher family, real recursion arrays and remote EH."""
import importlib.util
import json
import struct
import sys
import capstone
import linked_pe as core
import upstream_boost as upstream
from coff_exception_rtti import Reader
from linked_logic_error_origins import require, digest
from workflow_manifest import ROOT, load_manifest, unit_input_digest, compiler_sha256
UNIT = 'boost-regex-iterator-search'
# root: code start, code size, handler offset, metadata start, action offsets
SCOPES = {
    0x4440a0: (0x6b9560, 44, 11, 0x6df420, [0]),
    0x443b30: (0x6b9400, 73, 46, 0x6df334, [0, 11, 22]),
    0x443aa0: (0x6b93c0, 49, 22, 0x6df300, [0, 11]),
    0x442f40: (0x6b92f0, 35, 8, 0x6df254, [0]),
}
sp = importlib.util.spec_from_file_location('boost_matcher_eh_sections', ROOT/'scripts/audit-select-constructor.py')
EH = importlib.util.module_from_spec(sp)
sp.loader.exec_module(EH)

def check_metadata(meta, start, code, offsets):
    count = len(offsets)
    require(len(meta) == 36 + 8*count, 'matcher full metadata extent differs')
    require(struct.unpack_from('<9I', meta, 8*count) == (0x19930522, count, start, 0, 0, 0, 0, 0, 1), 'matcher complete FuncInfo fields differ')
    for index, offset in enumerate(offsets):
        require(struct.unpack_from('<iI', meta, index*8) == (index-1, code+offset), 'matcher unwind state/action differs')

def check_array(raw, constructor):
    # Complete original construction/destruction call sites, including EH state.
    expected = ('682030440068003a44006a326a448d968800000052c644243001e818672400'
                if constructor else '68203044006a326a448d868800000050c744242401000000e8c4672400')
    require(raw == bytes.fromhex(expected), 'matcher real recursion array count/stride/member/callback differs')

def audit(read=None):
    c = core.comparator(); sha = c.verify_target(); read = read or c.target_bytes
    u = load_manifest()['units'][UNIT]
    require(u.get('source') == upstream.SEARCH_PROBE and u.get('profile') == 'vc8-sp1-probe-o2' and u.get('enable_gs') is True and u.get('boost_regex_headers') is True, 'matcher original public source contract differs')
    upstream.inputs(u)
    p = ROOT/u['object']; record = json.loads(p.with_suffix(p.suffix+'.provenance.json').read_text()); actual, _ = unit_input_digest(UNIT, u)
    require(record.get('unit') == UNIT and record.get('input_digest') == actual and record.get('object_sha256') == core.sha(p) and record.get('compiler_sha256') == compiler_sha256(), 'fresh original matcher provenance required')
    r = Reader(p); known = c.known_data_targets(); calls = c.known_targets()
    functions = {int(f['address'], 0): f for f in u['functions']}
    require(set(functions) == {0x4440a0, 0x443020, 0x443a00, 0x443b30, 0x443aa0}, 'matcher complete original family selection differs')
    for f in functions.values():
        for value in f.get('rel32_targets', []):
            name, at = value.rsplit('=', 1); calls[name] = int(at, 0)
    def name(prefix):
        found = [s.name for s in r.cf.symbols.values() if s.section_number > 0 and s.name.startswith(prefix)]
        require(len(found) == 1, 'matcher original helper name is ambiguous: '+prefix)
        return found[0]
    support = {0x442f40: (name('??1?$match_results'), 141),
               0x4439e0: (name('??1?$scoped_ptr'), 25),
               0x4422e0: (name('??1?$repeater_count'), 12),
               0x435f90: (name('??1?$vector@U?$sub_match'), 42)}
    for at, (n, size) in support.items(): calls[n] = at
    calls.update({'??3@YAXPAX@Z': 0x6898ea, '@__security_check_cookie@4': 0x689d25, '___CxxFrameHandler3': 0x6899e7})
    bodies = {}; regions = {}
    selected = {at: (functions[at]['symbol_base'], size) for at, size in [(0x4440a0,235),(0x443020,8),(0x443a00,44),(0x443b30,243),(0x443aa0,129)]}
    selected.update(support)
    for at, (n, size) in selected.items():
        require(r.symbol(n).value == 0 and r.section(n).raw_size == size, 'matcher whole source body extent differs: '+hex(at)+' '+str(r.section(n).raw_size)+' offset '+str(r.symbol(n).value))
        f = functions.get(at, {}); overrides = dict(x.rsplit('=',1) for x in f.get('dir32_targets',[]))
        body = c.coff_symbol_bytes(p, n, at, size, calls, known, overrides)
        require(len(body) == size, 'matcher full canonical body missing')
        exits = {at+3: 0x442f40} if at == 0x443020 else {}
        core.decode_closed_body(body, at, tail=bool(exits), external_exits=exits)
        bodies[at] = body; regions[hex(at)] = EH.region_result(body, read(at,size), at)
    ctor = functions[0x443b30]['symbol_base']; dtor = functions[0x443aa0]['symbol_base']; callback = functions[0x443020]['symbol_base']; initial = functions[0x443a00]['symbol_base']
    require(r.refs(ctor,31,165) == [(1,6,callback),(6,6,initial),(27,20,'??_L@YGXPAXIHP6EX0@Z1@Z')] and r.refs(dtor,29,40) == [(1,6,callback),(25,20,'??_M@YGXPAXIHP6EX0@Z@Z')], 'matcher paired array relocation roles differ')
    check_array(bodies[0x443b30][165:196], True); check_array(bodies[0x443aa0][40:69], False)
    scopes = []
    for at, (base, code_size, handler_offset, meta_base, offsets) in SCOPES.items():
        n = selected[at][0]; h = '__ehhandler$'+n; info = '__ehfuncinfo$'+n; unwind = '__unwindtable$'+n
        code_sec = r.section(h); meta_sec = r.section(info); count = len(offsets)
        require(code_sec.name == '.text$x' and code_sec.raw_size == code_size and r.symbol(h).value == handler_offset and known[h][0] == base+handler_offset and meta_sec.name == '.xdata$x' and meta_sec.raw_size == 36+8*count and r.symbol(unwind).value == 0 and r.symbol(info).value == count*8, 'matcher complete remote scope ownership differs')
        data = {info: (meta_base+count*8, read(meta_base+count*8,36), frozenset({0}), 'address'), unwind: (meta_base, read(meta_base,count*8), frozenset({0}), 'address'), callback: (0x443020,bodies[0x443020],frozenset({0}),'address')}
        actions = []
        for index, offset in enumerate(offsets):
            action = '__unwindfunclet$'+n+'$'+str(index); symbol = r.symbol(action)
            require(symbol.value == offset and symbol.section_number == r.symbol(h).section_number, 'matcher action owner/offset differs')
            actions.append(action); data[action] = (base+offset, read(base+offset,1), frozenset({0}), 'address')
        require(r.refs(unwind,count*8) == [(4+8*i,6,action) for i,action in enumerate(actions)] and r.refs(info,36) == [(8,6,unwind)], 'matcher metadata relocation roles differ')
        code = EH.replay_section(r.cf,code_sec,base,calls,data,read); meta = EH.replay_section(r.cf,meta_sec,meta_base,calls,data,read)
        check_metadata(meta,meta_base,base,offsets)
        for lo,hi in zip(offsets+[handler_offset], offsets[1:]+[handler_offset,code_size]):
            body = code[lo:hi]; md = capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32); instructions = list(md.disasm(body,base+lo)); exits = {}
            if instructions and instructions[-1].mnemonic == 'jmp':
                last = instructions[-1]; require(last.size == 5 and last.bytes[0] == 0xe9, 'matcher cleanup exit must be original E9')
                target = last.address+5+struct.unpack_from('<i',last.bytes,1)[0]; require(target in calls.values(), 'matcher cleanup exit must be named'); exits[last.address] = target
            core.decode_closed_body(body,base+lo,tail=bool(exits),external_exits=exits)
        regions[hex(base)] = EH.region_result(code,read(base,code_size),base); regions[hex(meta_base)] = EH.region_result(meta,read(meta_base,len(meta)),meta_base)
        scopes.append(dict(root=hex(at),code=hex(base),metadata=hex(meta_base),states=count))
    return dict(result='exact' if all(v['exact'] for v in regions.values()) else 'mismatch', target_sha256=sha, regions=regions, scopes=scopes, source_provenance_verified=True, scope='original public search and matcher lifetimes, complete remote EH and bounded member support; no new authored credit, inventory entries, full find/construct_init implementation proof or executed OS exception claim')

if __name__ == '__main__':
    try:
        result=audit(); print(json.dumps(result,indent=2)); raise SystemExit(result['result']!='exact')
    except (OSError, ValueError, KeyError, RuntimeError, struct.error) as exc: raise SystemExit(str(exc))
