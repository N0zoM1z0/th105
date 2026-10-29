"""Identify a private callee's source caller EH/cookie fields, not caller equality.

This narrowly admits one real cleanup-state caller. It does not canonicalize
that caller or waive any byte of the independently compared private callee.
"""
import hashlib
import re
import struct


def validate(contract, unit):
    eh = contract.get('caller_eh')
    address = lambda x: isinstance(x, str) and re.fullmatch(r'0x[0-9A-Fa-f]{8}', x)
    if (set(contract) != {'caller', 'site', 'caller_eh'}
            or not address(contract.get('caller')) or not address(contract.get('site'))
            or not isinstance(eh, dict) or set(eh) != {'handler', 'info'}
            or any(not address(x) for x in eh.values())
            or unit.get('link_runtime') != 'static'
            or unit.get('link_runtime_data') != ['___security_cookie']):
        raise ValueError('private EH caller needs one explicit edge, handler/FuncInfo and static CRT cookie')


def observe(contract, unit, caller, pe, functions, exports, cil_owner,
            source_instructions, target_instructions, read_target,
            bindings, game_range, internal_refs):
    import linked_pe as core
    import linked_lifecycle as life
    validate(contract, unit)
    symbol = caller['symbol_base']
    handler = life.private_entry(functions, exports, '__ehhandler$' + symbol,
                                 cil_owner, compiler=True)
    cookies = [r for r in internal_refs if r.get('kind') == 'runtime'
               and r.get('symbol') == '___security_cookie' and r.get('size') == 4]
    if len(cookies) != 1:
        raise ValueError('caller has no independently attested real static CRT cookie')
    cookie = cookies[0]
    target_handler = int(contract['caller_eh']['handler'], 0)
    target_info = int(contract['caller_eh']['info'], 0)
    source_raw = core.linked_body(pe, functions, handler)
    native_raw = life.target_handler(read_target, target_handler)

    def runtime_entry(name):
        found = [(a, owner) for a, aliases in functions.items()
                 for n, owner in aliases if n == name]
        if len(found) != 1 or 'libcmt:' not in found[0][1]:
            raise ValueError('caller EH branch is not a real pinned static CRT provider')
        return found[0][0]

    def packet(raw, start, check, unwind):
        # The exact 27-byte GS cleanup-handler family, with its own frame
        # offsets. No claim is made that source and target frames agree.
        if (len(raw) != 27 or raw[:6] != bytes.fromhex('8b5424088d42')
                or raw[7:9] != bytes.fromhex('8b4a')
                or raw[10:13] != bytes.fromhex('33c8e8')
                or raw[17] != 0xb8 or raw[22] != 0xe9
                or raw[6] < 0x84 or raw[9] != raw[6] - 4
                or start + 17 + struct.unpack_from('<i', raw, 13)[0] != check
                or start + 27 + struct.unpack_from('<i', raw, 23)[0] != unwind):
            raise ValueError('caller EH is outside the bounded GS cleanup-handler family')
        core.decode_closed_body(raw, start, tail=True)
        return struct.unpack_from('<I', raw, 18)[0]

    info = packet(source_raw, handler, runtime_entry('@__security_check_cookie@4'),
                  runtime_entry('___CxxFrameHandler3'))
    if packet(native_raw, target_handler, 0x00689D25, 0x006899E7) != target_info:
        raise ValueError('native caller handler does not select its declared FuncInfo')
    source_info = core.readonly_data(pe, info, 36)
    native_info = read_target(target_info, 36)
    for data in (source_info, native_info):
        if len(data) != 36:
            raise ValueError('truncated caller FuncInfo')
        words = struct.unpack('<9I', data)
        if words[:2] != (0x19930522, 1) or words[3:] != (0, 0, 0, 0, 0, 1):
            raise ValueError('caller EH must have one cleanup state and no catch metadata')

    source_map = struct.unpack('<9I', source_info)[2]
    native_map = struct.unpack('<9I', native_info)[2]
    cleanup = life.private_entry(functions, exports, '__unwindfunclet$' + symbol + '$0',
                                 cil_owner, compiler=True)
    source_unwind = core.readonly_data(pe, source_map, 8)
    native_unwind = read_target(native_map, 8)
    if (len(native_unwind) != 8 or struct.unpack('<iI', source_unwind) != (-1, cleanup)
            or struct.unpack('<i', native_unwind[:4])[0] != -1
            or not game_range[0] <= struct.unpack('<I', native_unwind[4:])[0] < game_range[1]):
        raise ValueError('caller has no unique one-state cleanup funclet')
    core.validate_body_relocations(pe, handler, len(source_raw), [{'field_offset': 18}])
    core.validate_body_relocations(pe, info, 36, [{'field_offset': 8}])
    core.validate_body_relocations(pe, source_map, 8, [{'field_offset': 4}])

    def fields(instructions, expected_handler, expected_cookie):
        found = []
        for i in instructions:
            control = i.group(core.capstone.CS_GRP_CALL) or core.is_branch(i)
            for op in i.operands:
                if op.type == core.capstone.x86.X86_OP_MEM:
                    if op.mem.base or op.mem.index or op.mem.segment in {
                            core.capstone.x86.X86_REG_FS, core.capstone.x86.X86_REG_GS}:
                        continue
                    value = op.mem.disp & 0xffffffff
                    if value != expected_cookie or op.size != 4 or i.mnemonic != 'mov':
                        raise ValueError('caller has another absolute memory field')
                    found.append('cookie')
                elif op.type == core.capstone.x86.X86_OP_IMM and not control:
                    value = op.imm & 0xffffffff
                    if value == expected_handler and i.mnemonic == 'push' and i.size == 5:
                        found.append('handler')
                    elif (game_range[0] <= value < game_range[1]
                          or pe.get_section_by_rva(value - core.IMAGE_BASE) is not None):
                        raise ValueError('caller has another mapped immediate field')
        if sorted(found) != ['cookie', 'handler']:
            raise ValueError('caller must install its unique handler and load its unique cookie')

    fields(source_instructions, handler, cookie['source_address'])
    fields(target_instructions, target_handler, cookie['address'])
    refs = core.caller_data_witness(pe, source_instructions, functions, bindings, game_range)
    if sorted(r.get('source_address', -1) for r in refs) != sorted([handler, cookie['source_address']]):
        raise ValueError('caller HIGHLOW fields exceed its typed EH/cookie roles')
    return {'source_only_address_fields': refs,
            'caller_eh_identity': {'source_handler': handler, 'target_handler': target_handler,
                'source_info': info, 'target_info': target_info,
                'source_handler_sha256': hashlib.sha256(source_raw).hexdigest(),
                'target_handler_sha256': hashlib.sha256(native_raw).hexdigest(),
                'source_info_sha256': hashlib.sha256(source_info).hexdigest(),
                'target_info_sha256': hashlib.sha256(native_info).hexdigest(),
                'caller_or_eh_exactness_claimed': False}}
