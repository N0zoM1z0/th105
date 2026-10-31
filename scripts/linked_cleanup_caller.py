"""Reach an ordinary private destructor through a freshly exact caller cleanup."""
import hashlib
import re
import struct


def validate(contract, function, unit):
    address = lambda value: isinstance(value, str) and re.fullmatch(r'0x[0-9A-Fa-f]{8}', value)
    if (not isinstance(contract, dict)
            or set(contract) != {'caller', 'site', 'cleanup', 'through_exact_caller'}
            or not address(contract['caller']) or not address(contract['site'])
            or type(contract['cleanup']) is not int or not 0 <= contract['cleanup'] < 64
            or contract['through_exact_caller'] is not True):
        raise ValueError('private cleanup edge needs an explicit index/site and fresh exact caller')
    if not re.fullmatch(r'\?\?1[A-Za-z_]\w*(?:@[A-Za-z_]\w*)*@@QAE@XZ', function['symbol_base']):
        raise ValueError('private cleanup child must be an ordinary nonvirtual destructor')
    parents = [f for f in unit['functions'] if f['address'] == contract['caller']]
    if (len(parents) != 1 or parents[0] is function or 'eh_cleanup' not in parents[0]
            or any(k in parents[0] for k in ('private_global', 'vtable_entry'))
            or unit.get('link_runtime') != 'static'
            or unit.get('link_runtime_data') != ['___security_cookie']):
        raise ValueError('private cleanup child needs one exact caller with full static cleanup evidence')
    parent_edge = parents[0].get('private_from')
    if parent_edge is not None and (
            not isinstance(parent_edge, dict) or set(parent_edge) != {'caller', 'site'}
            or any(not address(value) for value in parent_edge.values())):
        raise ValueError('cleanup parent may only be public or independently direct-call witnessed')


def observe(core, function, caller, pe, functions, exports, cil_owner, child_start,
            read_target, report):
    import linked_lifecycle as life
    contract = function['private_from']
    if (not report or report.get('result') != 'exact'
            or report.get('address') != caller['address']
            or not report.get('validated_cleanup_eh')
            or ('private_from' in caller and not report.get('private_caller_witness'))):
        raise ValueError('private cleanup edge has no fresh complete exact caller/EH replay')
    index = contract['cleanup']
    packets = [r for r in report['validated_cleanup_eh']
               if r.get('kind') == f'cleanup funclet {index}']
    if len(packets) != 1:
        raise ValueError('private cleanup index is absent or duplicated')
    packet = packets[0]
    symbol = '__unwindfunclet$' + caller['symbol_base'] + '$' + str(index)
    start = life.private_entry(functions, exports, symbol, cil_owner, compiler=True)
    size = packet.get('size')
    if packet.get('source_address') != start or size not in (8, 11):
        raise ValueError('private cleanup edge lacks its complete bounded receiver/tail funclet')
    native_start = packet['target_address']
    source = core.linked_body(pe, functions, start)
    native = read_target(native_start, size)
    digest = hashlib.sha256(native).hexdigest()
    tail = size - 5
    if (packet.get('canonical_sha256') != digest or packet.get('target_sha256') != digest
            or len(source) != size or len(native) != size
            or source[:tail + 1] != native[:tail + 1]
            or source[1] & 0xc7 != 0x45 or source[tail] != 0xe9):
        raise ValueError('private cleanup receiver preparation or full canonical funclet differs')
    register = (source[1] >> 3) & 7
    if size == 8:
        if source[0] not in (0x8b, 0x8d):
            raise ValueError('cleanup receiver must be an actual stack-address/load')
    elif (source[0] != 0x8b or source[3] != 0x83
            or source[4] != 0xc0 + register or source[5] >= 0x80):
        raise ValueError('cleanup member offset must add to the same loaded receiver')
    destination = int(function['address'], 0)
    site = native_start + tail
    if (int(contract['site'], 0) != site
            or start + size + struct.unpack_from('<i', source, tail + 1)[0] != child_start
            or native_start + size + struct.unpack_from('<i', native, tail + 1)[0] != destination):
        raise ValueError('private cleanup does not tail-call the selected actual source/native destructor')
    calls = packet.get('replayed_rel32')
    expected = [{'offset': tail + 1, 'symbol': function['symbol_base'], 'target': destination}]
    if calls != expected:
        raise ValueError('private cleanup callee mapping is not the fully replayed destructor')
    mappings = [m for m in caller.get('rel32_targets', [])
                if m.split('=', 1)[0] == function['symbol_base']]
    if len(mappings) != 1 or int(mappings[0].split('=', 1)[1], 0) != destination:
        raise ValueError('exact caller must explicitly name its actual cleanup destructor')
    core.decode_closed_body(source, start, tail=True)
    core.decode_closed_body(native, native_start, tail=True)
    core.validate_body_relocations(pe, start, size, packet.get('data_references', []))
    return {
        'cleanup_index': index, 'target_site': f'0x{site:08X}',
        'source_site': f'0x{start + tail:08X}', 'branch': 'tail',
        'cleanup_source_symbol': symbol, 'cleanup_size': size,
        'cleanup_source_sha256': hashlib.sha256(source).hexdigest(),
        'cleanup_canonical_sha256': digest,
        'exact_caller': {**{k: report[k] for k in (
            'address', 'source_body_sha256', 'object_compared_sha256',
            'target_sha256', 'validated_cleanup_eh')},
            'private_caller_witness': report.get('private_caller_witness')},
    }
