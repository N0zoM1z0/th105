#!/usr/bin/env python3
"""Actual design default lifetimes, shared IColor and real selection owner."""
import importlib.util
import json
from pathlib import Path
import struct
import pefile
from coff_exception_rtti import Reader, RttiGraph
from linked_logic_error_origins import require, digest
import linked_pe as core
spec = importlib.util.spec_from_file_location('design_owner_helpers', Path(__file__).with_name('audit-ctile-real-owner.py'))
h = importlib.util.module_from_spec(spec)
spec.loader.exec_module(h)
SLOTS = [
 ('??_ECDesignBase@th105@@UAEPAXI@Z', 0x421930),
 ('?set_color@CDesignBase@th105@@UAEXI@Z', 0x40bfe0),
 ('?set_vertex_colors@CDesignBase@th105@@UAEXPBI@Z', 0x40c040),
 ('?multiply_color@CDesignBase@th105@@UAEXI@Z', 0x40c0a0),
 ('?load@CDesignBase@th105@@UAEXPBD@Z', 0x40b000),
 ('?virtual_cleanup@CDesignBase@th105@@UAEXXZ', 0x40bb40),
 ('?render_offset_through@CDesignBase@th105@@UAEXMMI@Z', 0x40bec0),
 ('?render_offset@CDesignBase@th105@@UAEXMM@Z', 0x40be20),
 ('?render_through@CDesignBase@th105@@UAEXI@Z', 0x40bd10),
 ('?render@CDesignBase@th105@@UAEXXZ', 0x40bc80),
]


def check_table(size, offset, refs, raw, native):
    require(size == 44 and offset == 4 and raw == bytes(40), 'design complete ten-slot storage differs')
    require(refs == [(4*i, 6, n) for i, (n, _) in enumerate(SLOTS)], 'design actual virtual role identities differ')
    require(native == struct.pack('<10I', *(a for _, a in SLOTS)), 'design native slot destinations differ')


def audit():
    c = core.comparator()
    sha = c.verify_target()
    u, p = h.fresh('cross-v106a-design-base-lifetime')
    require(u['source'] == 'src/ui/SelectConstructor.cpp' and u['enable_gs'] is True, 'design lifetimes need the actual Select constructor source')
    r = Reader(p)
    game = pefile.PE(str(c.TARGET))
    g = RttiGraph(r, game, c.target_bytes, {'.?AUIColor@@'})
    g.table('??_7IColor@@6B@', 0x6c0624, 0, '.?AUIColor@@')
    table = '??_7CDesignBase@th105@@6B@'
    check_table(r.section(table).raw_size, r.symbol(table).value, r.refs(table, 40), r.raw(table, 40), c.target_bytes(0x6c08ac, 40))
    require(core.primary_type_name(game, 0x6c08ac) == '.?AVCDesignBase@@', 'native design primary owner differs')
    col = r.pointer(table, -4)
    native_col = struct.unpack('<I', c.target_bytes(0x6c08a8, 4))[0]
    native_words = struct.unpack('<5I', c.target_bytes(native_col, 20))
    require(struct.unpack('<3I', r.raw(col, 12)) == native_words[:3] == (0, 0, 0), 'design primary COL adjustment differs')
    hierarchy = r.pointer(col, 16)
    native_hierarchy = struct.unpack('<4I', c.target_bytes(native_words[4], 16))
    require(struct.unpack('<3I', r.raw(hierarchy, 12)) == native_hierarchy[:3] == (0, 0, 2), 'design must directly inherit one primary IColor base')
    base = r.pointer(r.pointer(hierarchy, 12), 4)
    native_base = struct.unpack('<I', c.target_bytes(native_hierarchy[3] + 4, 4))[0]
    nb = struct.unpack('<7I', c.target_bytes(native_base, 28))
    require(struct.unpack('<7I', r.raw(base, 28))[1:6] == nb[1:6] == (0, 0, 0xffffffff, 0, 0x40), 'design IColor base adjustments differ')
    g.descriptor(r.pointer(base, 0), nb[0], '.?AUIColor@@')
    require(sum(n for a, n in {(z['address'], z['size']) for z in g.records}) == 93, 'design shared IColor metadata extent differs')
    bodies = []
    for f, size in zip(u['functions'], [153, 154, 30]):
        body = h.canonical(c, u, p, f)
        require(len(body) == size and body == c.target_bytes(int(f['address'], 0), size), 'design complete canonical lifetime differs')
        core.decode_closed_body(body, int(f['address'], 0))
        bodies.append(dict(address=f['address'], size=size, sha256=digest(body)))
    parent = '??0CSelect@th105@@QAE@XZ'
    calls = [off for off, kind, name in r.refs(parent, r.section(parent).raw_size) if kind == 20 and name == '??0CDesignBase@th105@@QAE@XZ']
    require(len(calls) == 2, 'design actual two-member constructor uses missing')
    edges = []
    for off in calls:
        at = 0x4231a0 + off - 1
        require(c.target_bytes(at, 5) == b'\xe8' + struct.pack('<i', 0x4217f0 - at - 5), 'design actual native member-construction edge differs')
        edges.append(hex(at))
    return dict(target_sha256=sha, bodies=bodies, table_address='0x006C08AC', table_size=40, shared_IColor_rtti=g.records, unique_IColor_bytes=93, constructor_edges=edges, scope='153+154 pure implicit member-lifetime bytes withdrawn from authored credit; scalar30 already excluded; shared IColor metadata and ten virtual role identities, not exact namespace-qualified derived RTTI, loader/EH or full-program linkage')


if __name__ == '__main__':
    print(json.dumps(audit(), indent=2))
