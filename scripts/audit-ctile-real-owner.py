#!/usr/bin/env python3
"""Actual CTile RTTI/table/copy and ordinary owner evidence; no parent credit."""
import json
import struct
from pathlib import Path
import pefile
import linked_pe as core
from coff_exception_rtti import Reader, RttiGraph
from linked_logic_error_origins import require, digest
from workflow_manifest import ROOT, load_manifest, unit_input_digest, compiler_sha256

COPY = '??0CTile@@QAE@ABV0@@Z'
SCALAR = '??_GCTile@@UAEPAXI@Z'
WEAK = '??_ECTile@@UAEPAXI@Z'
SLOTS = [(WEAK, 0x40ae80), ('?set_color@CSpriteBase@@UAEXI@Z', 0x40ac50), ('?set_vertex_colors@CSpriteBase@@UAEXPBI@Z', 0x40ac70), ('?multiply_color@CSpriteBase@@UAEXI@Z', 0x40ac90)]


def fresh(name):
    u = load_manifest()['units'][name]
    p = ROOT / u['object']
    record = json.loads(p.with_suffix(p.suffix + '.provenance.json').read_text())
    actual, _ = unit_input_digest(name, u)
    require(record.get('unit') == name and record.get('input_digest') == actual and record.get('compiler_sha256') == compiler_sha256() and record.get('object_sha256') == core.sha(p), 'fresh CTile owner provenance required')
    return u, p


def canonical(c, u, p, f):
    calls = c.known_targets() | {n: int(a, 0) for n, a in (v.rsplit('=', 1) for v in f.get('rel32_targets', []))}
    return c.coff_symbol_bytes(p, f['symbol_base'], int(f['address'], 0), 0xffffffff, calls, c.known_data_targets(), dict(v.rsplit('=', 1) for v in f.get('dir32_targets', [])))


def check_table(raw_size, offset, refs, raw, native):
    require(raw_size == 20 and offset == 4, 'CTile four-slot table/COL extent differs')
    require(refs == [(4*i, 6, name) for i, (name, _) in enumerate(SLOTS)] and raw == bytes(16), 'CTile actual inherited virtual roles differ')
    require(native == struct.pack('<4I', *(at for _, at in SLOTS)), 'CTile full native virtual table differs')


def audit(read=None):
    c = core.comparator()
    sha = c.verify_target()
    read = read or c.target_bytes
    u, p = fresh('gpt-web-ctile-copy-lifetime')
    require(u['source'] == 'src/ui/FileListFinalize.cpp' and u['enable_gs'] is True and u['functions'] == [dict(address='0x004396A0', symbol_base=COPY)], 'CTile needs actual page owner, not an artificial copy-only probe')
    r = Reader(p)
    graph = RttiGraph(r, pefile.PE(str(c.TARGET)), read, {'.?AVCTile@@', '.?AVCSpriteBase@@', '.?AUIColor@@'})
    graph.table('??_7CTile@@6B@', 0x6c0718, 0, '.?AVCTile@@')
    table = '??_7CTile@@6B@'
    check_table(r.section(table).raw_size, r.symbol(table).value, r.refs(table, 16), r.raw(table, 16), read(0x6c0718, 16))
    unique = {(x['address'], x['size']) for x in graph.records}
    require(sum(n for a, n in unique) == 247, 'CTile complete RTTI graph extent differs')
    raw = p.read_bytes()
    ptr = struct.unpack_from('<I', raw, 8)[0]
    found = [(i, s) for i, s in r.cf.symbols.items() if s.name == WEAK]
    require(len(found) == 1, 'CTile weak deleting slot ambiguous')
    index, symbol = found[0]
    rec, aux = raw[ptr+18*index:ptr+18*(index+1)], raw[ptr+18*(index+1):ptr+18*(index+2)]
    require(symbol.section_number == 0 and symbol.value == 0 and rec[14:18] == bytes([32, 0, 105, 1]) and len(aux) == 18, 'CTile original deleting weak external differs')
    fallback, kind = struct.unpack_from('<II', aux)
    require(kind == 2 and aux[8:] == bytes(10) and fallback in r.cf.symbols and r.cf.symbols[fallback].name == SCALAR, 'CTile weak scalar fallback differs')
    scalar = c.coff_symbol_bytes(p, SCALAR, 0x40ae80, 0xffffffff, {'??3@YAXPAX@Z': 0x6898ea}, c.known_data_targets(), {})
    require(r.section(SCALAR).raw_size == len(scalar) == 31 and scalar == read(0x40ae80, 31), 'CTile complete scalar support differs')
    copy = canonical(c, u, p, u['functions'][0])
    require(len(copy) == 164 and copy == read(0x4396a0, 164), 'CTile complete implicit copy differs')
    parent = '?finalize@CFileList@th105@@UAEXXZ'
    refs = r.refs(parent, r.section(parent).raw_size)
    require(len([x for x in refs if x[1:] == (20, COPY)]) == 1, 'CTile actual page copy call missing')
    require(read(0x43a914, 5) == b'\xe8' + struct.pack('<i', 0x4396a0 - 0x43a919), 'CTile actual native page copy edge differs')
    wrapper_u, wrapper_p = fresh('gpt-web-ui-tile-texture')
    wrapper = canonical(c, wrapper_u, wrapper_p, wrapper_u['functions'][0])
    require(len(wrapper) == 37 and wrapper == read(0x4098b0, 37), 'CTile full texture wrapper differs')
    render_u, render_p = fresh('exact-first-ctile-render')
    render = canonical(c, render_u, render_p, render_u['functions'][0])
    require(len(render) == 756, 'CTile render complete extent differs')
    return dict(target_sha256=sha, rtti=graph.records, unique_rtti_bytes=247, table=dict(address='0x006C0718', size=16, slots=SLOTS), scalar=dict(address='0x0040AE80', size=31, sha256=digest(scalar)), copy=dict(address='0x004396A0', size=164, sha256=digest(copy)), wrapper=dict(address='0x004098B0', size=37, sha256=digest(wrapper)), native_copy_edge=dict(address='0x0043A914', size=5), render=dict(size=len(render), candidate_sha256=digest(render), exact=render == read(0x4099f0, 756)), scope='actual four-slot CTile directly derives CSpriteBase/IColor; compiler copy/scalar/RTTI remain excluded; page/EH and render remain nonexact; other legacy tile facades are not unified by this scope')


if __name__ == '__main__':
    print(json.dumps(audit(), indent=2))
