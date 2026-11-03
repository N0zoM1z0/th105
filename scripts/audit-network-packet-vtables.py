#!/usr/bin/env python3
"""Audit complete two-slot packet vtables and target RTTI; no byte credit."""
import json
import struct
from pathlib import Path
from coff_exception_rtti import Reader
import linked_pe as core
from workflow_manifest import ROOT, load_manifest, unit_input_digest, compiler_sha256

SPECS = [
    ('gpt-web-network-ack-info-senders-runtime', '??_7NetworkAckInfoPacket40@th105@@6B@', 0x6c2504, '.?AVCDPP_ACK_INFO@@', '?serialize@NetworkAckInfoPacket40@th105@@UAEIPAX@Z', '?parse@NetworkAckInfoPacket40@th105@@UAEXPBE@Z', 0x44df20, 0x44e0a0),
    ('gpt-web-network-client-secondary-dispatch-runtime', '??_7ReplayPacket28@th105@@6B@', 0x6c24f8, '.?AVCDPP_REPLAY@@', '?serialize@ReplayPacket28@th105@@UAEIPAX@Z', '?parse@ReplayPacket28@th105@@UAEXPBE@Z', 0x44d990, 0x44e160),
    ('gpt-web-network-client-secondary-runtime', '??_7NetworkRequestReplay10@th105@@6B@', 0x6c24e0, '.?AVCDPP_REQ_REPLAY@@', '?serialize@NetworkRequestReplay10@th105@@UAEIPAX@Z', '?parse@NetworkRequestReplay10@th105@@UAEXPBE@Z', 0x44d840, 0x44d860),
    ('gpt-web-network-base-constructor-runtime', '??_7InputPacket24@th105@@6B@', 0x6c24ec, '.?AVCDPP_INPUT@@', '?serialize@InputPacket24@th105@@UAEIPAX@Z', '?parse@InputPacket24@th105@@UAEXPBE@Z', 0x44d920, 0x44e050),
]


def require(ok, message):
    if not ok:
        raise ValueError(message)


def check_source_table(reader, symbol, serialize, parse):
    section = reader.section(symbol)
    require(section.name == '.rdata' and section.raw_size == 12 and reader.symbol(symbol).value == 4, 'source vtable extent/COL differs')
    require(reader.raw(symbol, 8) == bytes(8), 'source vtable addends differ')
    require(reader.refs(symbol, 8) == [(0, 6, serialize), (4, 6, parse)], 'source vtable slots differ')
    col = reader.pointer(symbol, -4)
    hierarchy = reader.pointer(col, 16)
    require(struct.unpack('<4I', reader.raw(hierarchy, 16))[:3] == (0, 0, 2), 'source hierarchy differs')
    array = reader.pointer(hierarchy, 12)
    base = reader.pointer(array, 4)
    require(struct.unpack('<7I', reader.raw(base, 28))[1:6] == (0, 0, 0xffffffff, 0, 0x40), 'source base adjustment differs')
    require(reader.typename(reader.pointer(base, 0)) == b'.?AUNetworkPacketBase8@th105@@\0', 'source base type differs')


def audit():
    c = core.comparator(); target_sha = c.verify_target(); units = load_manifest()['units']; facts = []
    read = c.target_bytes
    def u32(address): return struct.unpack('<I', read(address, 4))[0]
    def cstring(address): return read(address, 128).split(b'\0', 1)[0].decode('ascii')
    for unit_name, symbol, address, native_type, serialize, parse, serialize_at, parse_at in SPECS:
        unit = units[unit_name]; obj = ROOT / unit['object']; provenance = json.loads(obj.with_suffix(obj.suffix + '.provenance.json').read_text())
        digest, _ = unit_input_digest(unit_name, unit)
        require(provenance.get('unit') == unit_name and provenance.get('input_digest') == digest and provenance.get('object_sha256') == core.sha(obj) and provenance.get('compiler_sha256') == compiler_sha256(), 'fresh source object provenance required')
        reader = Reader(obj); check_source_table(reader, symbol, serialize, parse)
        require(read(address, 8) == struct.pack('<II', serialize_at, parse_at), 'native vtable slots differ')
        col = u32(address - 4); require((u32(col), u32(col + 4), u32(col + 8)) == (0, 0, 0), 'native COL differs')
        require(cstring(u32(col + 12) + 8) == native_type, 'native class differs')
        hierarchy = u32(col + 16); require(u32(hierarchy + 8) == 2, 'native hierarchy count differs')
        array = u32(hierarchy + 12); base = u32(array + 4)
        require(base == 0x6d870c and u32(base + 8) == 0 and cstring(u32(base) + 8) == '.?AVIPacket@@', 'native common base differs')
        facts.append(dict(unit=unit_name, vtable=hex(address), native_type=native_type, base_descriptor=hex(base), slots=[hex(serialize_at), hex(parse_at)]))
    return dict(result='verified', target_sha256=target_sha, tables=facts, scope='two concrete slots and offset-zero base; shared void parse signature is inferred; full link remains unproved')


if __name__ == '__main__':
    try:
        print(json.dumps(audit(), indent=2))
    except (OSError, ValueError, KeyError, RuntimeError, struct.error) as exc:
        raise SystemExit(str(exc))
