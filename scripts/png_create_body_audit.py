"""Replay native PNG create-read body and switch table from pinned upstream C."""
import hashlib
import json
from pathlib import Path
import sys

import linked_pe as core
import linked_png_sdk as sdk
from coff_exception_rtti import Reader

SYMBOL = '_png_create_read_struct_2'
ADDRESS, BODY_SIZE, TABLE_SIZE = 0x66CE20, 756, 28
BODY_HASH = '5d1b0245401ddd1f1fdf335139484df87a8cc7dec838549405044e15fa4b106e'
TABLE_HASH = '5dbb9933a0a2ec5bab767ba8b4766897cad7c4fd2383f54286cbd419611e3f31'
CALLS = {'_png_create_struct_2': 0x6705C0, '_png_set_longjmp_fn': 0x670370,
         '__setjmp3': 0x68CBD8, '_png_set_mem_fn': 0x670730,
         '_png_set_error_fn': 0x6703F0, '_png_get_header_ver': 0x66BF00,
         '__snprintf': 0x68C714, '_png_warning': 0x670410,
         '_png_malloc_warn': 0x670820, '_inflateInit_': 0x6679C0,
         '_png_free': 0x6707F0, '_png_destroy_struct_2': 0x670670,
         '@__security_check_cookie@4': 0x689D25, '_png_set_read_fn': 0x670280}
ADDRESSES = {'_longjmp': 0x68CB24, '__imp__ExitProcess@4': 0x6C013C,
             '_png_zalloc': 0x66B9A0, '_png_zfree': 0x66B9F0}
LITERALS = {'??_C@_0DL@EHOKEKFF@Application?5built?5with?5libpng?9?$CF?4@': 0x6CB0F8,
            '??_C@_05DFCKICEH@1?42?45?$AA@': 0x6CB0F0,
            '??_C@_0BC@MCPIPOGP@zlib?5memory?5error?$AA@': 0x6CB0DC,
            '??_C@_0BC@FMDEBEDH@zlib?5stream?5error?$AA@': 0x6CB0C8,
            '??_C@_0BD@LBMCPKOE@zlib?5version?5error?$AA@': 0x6CB0B4,
            '??_C@_0BD@CPDHIJBA@Unknown?5zlib?5error?$AA@': 0x6CB0A0}
EXPECTED_REFS = [
    (7,6,'___security_cookie'), (71,20,'_png_create_struct_2'), (124,6,'_longjmp'),
    (140,20,'_png_set_longjmp_fn'), (148,20,'__setjmp3'), (163,6,'__imp__ExitProcess@4'),
    (184,20,'_png_set_mem_fn'), (205,20,'_png_set_error_fn'),
    (227,20,'_png_get_header_ver'), (258,20,'_png_get_header_ver'),
    (309,20,'_png_get_header_ver'), (330,20,'_png_get_header_ver'),
    (363,20,'_png_get_header_ver'),
    (370,6,'??_C@_0DL@EHOKEKFF@Application?5built?5with?5libpng?9?$CF?4@'),
    (381,20,'__snprintf'), (394,20,'_png_warning'), (451,20,'_png_malloc_warn'),
    (497,6,'_png_zalloc'), (510,6,'_png_zfree'),
    (536,6,'??_C@_05DFCKICEH@1?42?45?$AA@'), (542,20,'_inflateInit_'),
    (560,6,'$LN34'), (565,6,'??_C@_0BC@MCPIPOGP@zlib?5memory?5error?$AA@'),
    (575,6,'??_C@_0BC@FMDEBEDH@zlib?5stream?5error?$AA@'),
    (586,6,'??_C@_0BD@LBMCPKOE@zlib?5version?5error?$AA@'),
    (594,6,'??_C@_0BD@CPDHIJBA@Unknown?5zlib?5error?$AA@'),
    (603,20,'_png_warning'), (635,20,'_png_free'), (665,20,'_png_destroy_struct_2'),
    (681,20,'@__security_check_cookie@4'), (731,20,'_png_set_read_fn'),
    (748,20,'@__security_check_cookie@4'), (756,6,'$LN3'), (760,6,'$LN2'),
    (764,6,'$LN5'), (768,6,'$LN2'), (772,6,'$LN4'), (776,6,'$LN2'), (780,6,'$LN7')]


def validate_references(refs):
    if refs != EXPECTED_REFS:
        raise ValueError('PNG create body relocation roles differ')


def audit(path):
    root = core.ROOT
    lock = root / 'config/png-source-lock.json'
    header_lock = root / 'config/png-zlib-header-lock.json'
    if core.sha(lock) != sdk.SOURCE_LOCK_SHA256 or core.sha(header_lock) != sdk.ZLIB_HEADER_LOCK_SHA256:
        raise ValueError('PNG source lock differs')
    sdk.verified_sources(root, json.loads(lock.read_text()))
    sdk.verified_zlib_headers(root, json.loads(header_lock.read_text()))
    sdk.materialize_png_config(root / '.tools/upstream/libpng-1.5.2')
    core.pinned_tools(False)
    c = core.comparator()
    sha = c.verify_target()
    r = Reader(path)
    if r.section(SYMBOL).raw_size != BODY_SIZE + TABLE_SIZE or r.symbol(SYMBOL).value != 0:
        raise ValueError('PNG create body extent differs')
    validate_references(r.refs(SYMBOL, BODY_SIZE + TABLE_SIZE))
    data = c.known_data_targets()
    for name, address in ADDRESSES.items():
        data[name] = (address, c.target_bytes(address, 1), frozenset({0}), 'address')
    for name, address in LITERALS.items():
        section = r.section(name)
        literal = r.raw(name, section.raw_size - r.symbol(name).value)
        if c.target_bytes(address, len(literal)) != literal:
            raise ValueError('PNG create literal differs: ' + name)
        data[name] = (address, literal, frozenset({0}), 'literal')
    body = c.coff_symbol_bytes(path, SYMBOL, ADDRESS, BODY_SIZE + TABLE_SIZE, CALLS, data, {})
    target = c.target_bytes(ADDRESS, BODY_SIZE + TABLE_SIZE)
    if (body != target or hashlib.sha256(body[:BODY_SIZE]).hexdigest() != BODY_HASH
            or hashlib.sha256(body[BODY_SIZE:]).hexdigest() != TABLE_HASH):
        raise ValueError('PNG create body or switch table differs')
    return {'result': 'exact', 'target_sha256': sha, 'body_size': BODY_SIZE,
            'body_sha256': BODY_HASH, 'switch_table_size': TABLE_SIZE, 'switch_sha256': TABLE_HASH,
            'scope': 'source body and switch table with explicit target-role bindings; no callee or whole-library equivalence claim'}


if __name__ == '__main__':
    try:
        print(json.dumps(audit(Path(sys.argv[1])), indent=2))
    except (OSError, ValueError, KeyError, RuntimeError, IndexError) as exc:
        raise SystemExit(str(exc))
