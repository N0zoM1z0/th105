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
            or any(k in parents[0] for k in ('private_from', 'private_global', 'vtable_entry'))
            or unit.get('link_runtime') != 'static'
            or unit.get('link_runtime_data') != ['___security_cookie']):
        raise ValueError('private cleanup child needs one exported caller with full static cleanup evidence')


def observe(core, function, caller, pe, functions, exports, cil_owner, child_start,
            read_target, report):
    import linked_lifecycle as life
    contract = function['private_from']
    if (not report or report.get('result') != 'exact'
            or report.get('address') != caller['address']
            or not report.get('validated_cleanup_eh')):
        raise ValueError('private cleanup edge has no fresh complete exact caller/EH replay')
    index = contract['cleanup']
    packets = [r for r in report['validated_cleanup_eh']
               if r.get('kind') == f'cleanup funclet {index}']
    if len(packets) != 1:
        raise ValueError('private cleanup index is absent or duplicated')
    packet = packets[0]
    symbol = '__unwindfunclet$' + caller['symbol_base'] + '$' + str(index)
    start = life.private_entry(functions, exports, symbol, cil_owner, compiler=True)
    if packet.get('source_address') != start or packet.get('size') != 8:
        raise ValueError('private cleanup edge is not the verified original eight-byte funclet')
    native_start = packet['target_address']
    source = core.linked_body(pe, functions, start)
    native = read_target(native_start, 8)
    digest = hashlib.sha256(native).hexdigest()
    if (packet.get('canonical_sha256') != digest or packet.get('target_sha256') != digest
            or len(source) != 8 or len(native) != 8
            or source[:4] != native[:4] or source[0] != 0x8d
            or source[1] & 0xc7 != 0x45 or source[3] != 0xe9):
        raise ValueError('private cleanup receiver preparation or full canonical funclet differs')
    destination = int(function['address'], 0)
    site = native_start + 3
    if (int(contract['site'], 0) != site
            or start + 8 + struct.unpack_from('<i', source, 4)[0] != child_start
            or native_start + 8 + struct.unpack_from('<i', native, 4)[0] != destination):
        raise ValueError('private cleanup does not tail-call the selected actual source/native destructor')
    calls = packet.get('replayed_rel32')
    expected = [{'offset': 4, 'symbol': function['symbol_base'], 'target': destination}]
    if calls != expected:
        raise ValueError('private cleanup callee mapping is not the fully replayed destructor')
    mappings = [m for m in caller.get('rel32_targets', [])
                if m.split('=', 1)[0] == function['symbol_base']]
    if len(mappings) != 1 or int(mappings[0].split('=', 1)[1], 0) != destination:
        raise ValueError('exact caller must explicitly name its actual cleanup destructor')
    core.decode_closed_body(source, start, tail=True)
    core.decode_closed_body(native, native_start, tail=True)
    core.validate_body_relocations(pe, start, 8, packet.get('data_references', []))
    return {
        'cleanup_index': index, 'target_site': f'0x{site:08X}',
        'source_site': f'0x{start + 3:08X}', 'branch': 'tail',
        'cleanup_source_symbol': symbol, 'cleanup_size': 8,
        'cleanup_source_sha256': hashlib.sha256(source).hexdigest(),
        'cleanup_canonical_sha256': digest,
        'exact_caller': {k: report[k] for k in (
            'address', 'source_body_sha256', 'object_compared_sha256',
            'target_sha256', 'validated_cleanup_eh')},
    }
