#!/usr/bin/env python3
"""CSelect seven-slot dispatch and typed prefix evidence, not whole-class linkage."""
import importlib.util
import json
import struct
from pathlib import Path
import pefile
from coff_exception_rtti import Reader, RttiGraph
from linked_logic_error_origins import require, digest
import linked_pe as core

spec = importlib.util.spec_from_file_location('select_owner_helpers', Path(__file__).with_name('audit-ctile-real-owner.py'))
helpers = importlib.util.module_from_spec(spec)
spec.loader.exec_module(helpers)
SLOTS = [
 ('??_ECSelect@th105@@UAEPAXI@Z', 0x41e750),
 ('?update@CSelect@th105@@UAEHXZ', 0x421430),
 ('?render@CSelect@th105@@UAE_NXZ', 0x41ff00),
 ('?unknown_scene_method@CSelect@th105@@UAEXXZ', 0x41f890),
 ('?on_scene_enter@CSelect@th105@@UAEXH@Z', 0x421120),
 ('?on_scene_exit@CSelect@th105@@UAEXH@Z', 0x41fb70),
 ('?update_selection@CSelect@th105@@UAEHXZ', 0x4208e0),
]


def check_table(size, offset, refs, raw, native):
    require(size == 32 and offset == 4 and raw == bytes(28), 'CSelect complete seven-slot storage differs')
    require(refs == [(i*4, 6, n) for i, (n, _) in enumerate(SLOTS)], 'CSelect actual virtual declaration roles differ')
    require(native == struct.pack('<7I', *(a for _, a in SLOTS)), 'CSelect complete native slot identities differ')


def audit():
    c = core.comparator()
    sha = c.verify_target()
    u, p = helpers.fresh('exact-first-select-constructor')
    r = Reader(p)
    table = '??_7CSelect@th105@@6B@'
    check_table(r.section(table).raw_size, r.symbol(table).value, r.refs(table, 28), r.raw(table, 28), c.target_bytes(0x6c0bc4, 28))
    # Actual global tile identities are emitted by this constructor owner too.
    tiles = RttiGraph(r, pefile.PE(str(c.TARGET)), c.target_bytes, {'.?AVCTile@@', '.?AVCSpriteBase@@', '.?AUIColor@@'})
    tiles.table('??_7CTile@@6B@', 0x6c0718, 0, '.?AVCTile@@')
    t = '??_7CTile@@6B@'
    helpers.check_table(r.section(t).raw_size, r.symbol(t).value, r.refs(t, 16), r.raw(t, 16), c.target_bytes(0x6c0718, 16))
    ctor = helpers.canonical(c, u, p, u['functions'][0])
    for at, member in [(0x4232dd, 0x350), (0x42348a, 0x2cd0)]:
        store = b'\xc7\x86' + struct.pack('<II', member, 0x6c0718)
        require(ctor[at-0x4231a0:at-0x4231a0+10] == store == c.target_bytes(at, 10), 'CSelect actual tile member publication differs')
    bodies = []
    for name, size, expected in [('exact-first-select-scene-entry', 783, False), ('exact-first-select-scene-update', 685, False), ('exact-first-select-update-flow', 341, True), ('exact-first-select-stage-update', 890, True), ('exact-first-select-character-update', 619, False), ('exact-first-select-destructor', 845, True), ('exact-first-select-character-binding', 258, True), ('exact-first-select-render', 1497, False)]:
        unit, path = helpers.fresh(name)
        f = unit['functions'][0]
        body = helpers.canonical(c, unit, path, f)
        require(len(body) == size, 'CSelect complete consumer extent differs: ' + name)
        exact = body == c.target_bytes(int(f['address'], 0), size)
        require(exact == expected, 'CSelect consumer exactness changed: ' + name)
        if name == 'exact-first-select-scene-update':
            dispatch = bytes.fromhex('8b168b42188bceffd0')
            require(body[0x290:0x299] == dispatch and c.target_bytes(0x4216cc, 9) == dispatch, 'CSelect actual slot18 dispatch differs')
        bodies.append(dict(unit=name, address=f['address'], size=size, sha256=digest(body), exact=exact))
    return dict(target_sha256=sha, table_address='0x006C0BC4', table_size=28, slots=SLOTS, tile_rtti=tiles.records, tile_members=[0x350, 0x2cd0], bodies=bodies, scope='seven virtual roles and actual frame slot18 dispatch; typed state8/setupC/inputs10 replace raw prefix views; flow341 now uses the actual declared CSelect virtual method, stage890 and character619 share that owner; namespace RTTI and full-program linkage are not claimed recovered')


if __name__ == '__main__':
    print(json.dumps(audit(), indent=2))
