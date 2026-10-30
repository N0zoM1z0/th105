"""Bounded readonly VC8 byte-string literal reads in real CIL objects."""
import hashlib


def byte_string_size(symbol):
    prefix = '??_C@_0'
    if not isinstance(symbol, str) or not symbol.startswith(prefix):
        raise ValueError('linked literal must be a named VC8 byte-string object')
    tail = symbol[len(prefix):]
    if tail and tail[0] in '0123456789':
        return int(tail[0]) + 1
    digits, separator, _ = tail.partition('@')
    if not separator or not digits or any(c not in 'ABCDEFGHIJKLMNOP' for c in digits):
        raise ValueError('invalid VC8 literal extent encoding')
    size = 0
    for c in digits:
        size = size * 16 + ord(c) - ord('A')
    if not 0 < size <= 4096:
        raise ValueError('linked literal extent is outside the bounded string contract')
    return size


def validate(unit, data_keys):
    entries = unit.get('link_literals', [])
    if not isinstance(entries, list):
        raise ValueError('linked literals must be an explicit list')
    seen = set()
    for e in entries:
        if (not isinstance(e, dict) or set(e) != {'symbol', 'target', 'read_offsets'}
                or not isinstance(e['symbol'], str) or not isinstance(e['target'], str)
                or e['symbol'] in seen or e['target'] != e['symbol'] or e['target'] not in data_keys):
            raise ValueError('linked literal requires its unique exact symbol/target identity')
        size = byte_string_size(e['symbol'])
        offsets = e['read_offsets']
        if (not isinstance(offsets, list) or not offsets
                or any(type(x) is not int or not 0 <= x < size for x in offsets)
                or offsets != sorted(set(offsets))):
            raise ValueError('linked literal needs explicit distinct in-bounds read offsets')
        seen.add(e['symbol'])


def witnesses(unit, source, target, symbols, cil_owner, known):
    import linked_pe as core
    validate(unit, set(known))
    refs = []
    for e in unit.get('link_literals', []):
        size = byte_string_size(e['symbol'])
        address, raw, allowed, kind = known[e['target']]
        found = symbols.get(e['symbol'], [])
        if (len(found) != 1 or found[0][1].split()[-1:] != [cil_owner]
                or kind != 'literal' or len(raw) != size or raw[-1:] != b'\0'
                or not set(e['read_offsets']) <= allowed):
            raise ValueError('literal ownership, declared extent or existing target offsets disagree')
        start = found[0][0]
        if core.readonly_data(source, start, size) != raw or core.readonly_data(target, address, size) != raw:
            raise ValueError('complete source/target readonly literal bytes differ')
        for offset in e['read_offsets']:
            refs.append({'kind':'literal', 'symbol':e['symbol'],
                'source_address':start+offset, 'address':address+offset,
                'size':size-offset, 'literal_size':size, 'read_offset':offset,
                'literal_sha256':hashlib.sha256(raw).hexdigest()})
    return refs
