"""Validate original COFF internal assembly entries, never guessed byte slices."""
import struct
import hashlib


def entry_offset(obj: bytes, parent: str, entry: str) -> int:
    pointer, count = struct.unpack_from('<II', obj, 8)
    strings = pointer + count * 18
    found = {parent: [], entry: []}
    index = 0
    while index < count:
        at = pointer + index * 18
        raw = obj[at:at + 8]
        if raw[:4] == b'\0' * 4:
            start = strings + struct.unpack_from('<I', raw, 4)[0]
            end = obj.find(b'\0', start)
            if not strings + 4 <= start < end <= len(obj):
                raise ValueError('invalid original assembly symbol string')
            name = obj[start:end].decode('ascii')
        else:
            name = raw.rstrip(b'\0').decode('ascii')
        value, section, kind, storage, aux = struct.unpack_from('<IhHBB', obj, at + 8)
        if name in found:
            found[name].append((value, section, kind, storage))
        index += 1 + aux
    if parent == entry or any(len(found[name]) != 1 for name in found):
        raise ValueError('original enclosing function and entry label must be distinct and unique')
    owner, label = found[parent][0], found[entry][0]
    if owner[1] <= 0 or owner[2] != 0x20 or owner[3] != 2:
        raise ValueError('assembly parent is not an external original COFF function')
    if label[1] != owner[1] or label[2] != 0 or label[3] != 6:
        raise ValueError('assembly entry is not an original label in the enclosing section')
    offset = label[0] - owner[0]
    if offset <= 0:
        raise ValueError('assembly entry must follow its enclosing function entry')
    return offset


def verify_container(obj, parent, entry, body, relocations, native,
                     offset, call_offset):
    observed = entry_offset(obj, parent, entry)
    if observed != offset or not 0 < offset < len(body) or len(native) != len(body):
        raise ValueError('original assembly label offset or complete container size differs')
    wild = set()
    for at, kind, _name in relocations:
        if kind not in (6, 20) or at < 0 or at + 4 > len(body):
            raise ValueError('invalid relocation in original assembly container')
        if at < offset:
            raise ValueError('original assembly prefix must be relocation-free')
        wild.update(range(at, at + 4))
    if any(a != b and index not in wild for index, (a, b) in enumerate(zip(body, native))):
        raise ValueError('complete original assembly container fingerprint differs')
    # The entry is independently called by the original enclosing wrapper.
    # This call is local, fixed by original source bytes, and never relocated.
    if not 0 <= call_offset <= offset - 5 or any(i in wild for i in range(call_offset, call_offset + 5)):
        raise ValueError('assembly entry caller is not a fixed preceding source call')
    if body[call_offset] != 0xE8:
        raise ValueError('original assembly entry witness is not CALL')
    destination = call_offset + 5 + struct.unpack_from('<i', body, call_offset + 1)[0]
    if destination != offset:
        raise ValueError('original assembly wrapper does not call its named entry')
    return body[offset:], [(at - offset, kind, name) for at, kind, name in relocations if at >= offset]


def verify_readonly_sections(obj, specifications, read_pe):
    if not isinstance(specifications, list) or not specifications:
        raise ValueError('original assembly data sections must be explicit')
    count = struct.unpack_from('<H', obj, 2)[0]
    optional_size = struct.unpack_from('<H', obj, 16)[0]
    seen = set()
    for item in specifications:
        if not isinstance(item, dict) or set(item) != {'section', 'address', 'size', 'sha256'}:
            raise ValueError('invalid original read-only section evidence')
        number = int(item['section'])
        if not 1 <= number <= count or number in seen:
            raise ValueError('invalid or repeated original read-only section')
        seen.add(number)
        at = 20 + optional_size + 40 * (number - 1)
        name = obj[at:at + 8].rstrip(b'\0')
        size, pointer = struct.unpack_from('<II', obj, at + 16)
        relocations = struct.unpack_from('<H', obj, at + 32)[0]
        flags = struct.unpack_from('<I', obj, at + 36)[0]
        if name != b'.rdata' or relocations or flags & 0xA0000000 or size != int(item['size']):
            raise ValueError('original section is not complete relocation-free read-only data')
        original = obj[pointer:pointer + size]
        if len(original) != size or hashlib.sha256(original).hexdigest() != item['sha256']:
            raise ValueError('original complete read-only section hash differs')
        if read_pe(int(str(item['address']), 0), size) != original:
            raise ValueError('native complete read-only section differs from original archive')


def verify_internal_data_relocations(obj, body, relocations, native, specifications):
    bases = {int(item['section']): int(str(item['address']), 0) for item in specifications}
    pointer, count = struct.unpack_from('<II', obj, 8)
    strings = pointer + 18 * count
    definitions = {}
    index = 0
    while index < count:
        at = pointer + 18 * index
        raw = obj[at:at + 8]
        if raw[:4] == b'\0' * 4:
            start = strings + struct.unpack_from('<I', raw, 4)[0]
            end = obj.find(b'\0', start)
            if not strings + 4 <= start < end <= len(obj):
                raise ValueError('invalid original assembly symbol string')
            name = obj[start:end].decode('ascii')
        else:
            name = raw.rstrip(b'\0').decode('ascii')
        value, section, _kind, _storage, aux = struct.unpack_from('<IhHBB', obj, at + 8)
        definitions.setdefault(name, []).append((value, section))
        index += 1 + aux
    for at, kind, name in relocations:
        if kind != 6:
            continue
        matches = definitions.get(name, [])
        if len(matches) != 1 or matches[0][1] not in bases:
            raise ValueError('original assembly absolute reference lacks verified internal data')
        value, section = matches[0]
        addend = struct.unpack_from('<I', body, at)[0]
        expected = bases[section] + value + addend
        if struct.unpack_from('<I', native, at)[0] != expected:
            raise ValueError('original assembly data symbol/addend destination differs')
