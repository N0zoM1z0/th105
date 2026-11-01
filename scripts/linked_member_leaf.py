"""Qualify a relocation-free private HRESULT member through its real subobject call.

This is deliberately separate from source_only_caller and exact-parent paths.
The whole child must already equal the target without relocation or masking.
No private-register C++ declaration is accepted or created by this witness.
"""
import hashlib
import re
from capstone import CS_GRP_CALL, CS_GRP_JUMP
from capstone.x86 import X86_OP_IMM, X86_OP_MEM, X86_OP_REG


def validate(contract, function, unit):
    address = lambda v: isinstance(v, str) and re.fullmatch(r'0x[0-9A-Fa-f]{8}', v)
    if (not isinstance(contract, dict)
            or set(contract) != {'caller', 'site', 'relocation_free_member'}
            or contract['relocation_free_member'] is not True
            or not address(contract['caller']) or not address(contract['site'])):
        raise ValueError('relocation-free member needs one explicit direct caller/site')
    if not re.fullmatch(r'\?[A-Za-z_]\w*(?:@[A-Za-z_]\w*)*@@QAEJXZ', function['symbol_base']):
        raise ValueError('relocation-free leaf must be an ordinary nonvirtual noargs HRESULT member')
    if any(k in function for k in ('export_name', 'eh_cleanup', 'alignment_sites',
            'private_static_leaf', 'vtable_entry', 'private_global', 'private_texture_global')):
        raise ValueError('relocation-free leaf cannot use alternate entry, EH or alignment contracts')
    parents = [f for f in unit['functions'] if f['address'] == contract['caller']]
    if (len(parents) != 1 or parents[0] is function
            or any(k in parents[0] for k in ('private_from', 'private_global',
                'private_texture_global', 'vtable_entry'))):
        raise ValueError('relocation-free member needs its distinct ordinary exported caller')


def subobject_lea(rows, site):
    before = [i for i in rows if i.address + i.size == site]
    if len(before) != 1:
        raise ValueError('member call lacks a unique immediately preceding instruction')
    insn = before[0]
    if (insn.mnemonic != 'lea' or len(insn.operands) != 2
            or insn.operands[0].type != X86_OP_REG
            or insn.operands[1].type != X86_OP_MEM):
        raise ValueError('member call must receive an actual adjacent subobject LEA')
    dest, mem = insn.reg_name(insn.operands[0].reg), insn.operands[1].mem
    base = insn.reg_name(mem.base)
    if (insn.operands[0].size != 4 or dest not in ('esi', 'edi', 'ebx')
            or base not in ('esi', 'edi', 'ebx', 'ebp') or base == dest
            or mem.index or mem.segment or not 0 < mem.disp <= 0xffff or mem.disp % 4):
        raise ValueError('member LEA must name one aligned nonvolatile-register subobject')
    if any(i.group(CS_GRP_JUMP) and i.operands[0].type == X86_OP_IMM
           and insn.address < i.operands[0].imm <= site for i in rows):
        raise ValueError('a caller branch bypasses the subobject LEA')
    return {'receiver_register': dest, 'owner_register': base, 'offset': mem.disp}


def observe(core, function, pe, functions, start, ledger, read_target,
            source_rows, target_rows, source_site):
    row = ledger.get(function['address'], {})
    try:
        size = int(row['size'], 0)
    except (KeyError, ValueError, TypeError) as exc:
        raise ValueError('relocation-free leaf has no complete tracked extent') from exc
    raw = core.linked_body(pe, functions, start)
    target = read_target(int(function['address'], 0), size)
    if not 16 <= size <= 256 or len(raw) != size or len(target) != size or raw != target:
        raise ValueError('relocation-free member requires whole unmasked byte equality')
    source = core.decode_closed_body(raw, start)
    native = core.decode_closed_body(target, int(function['address'], 0))
    core.validate_body_relocations(pe, start, size, [])
    source_receiver = subobject_lea(source_rows, source_site)
    target_receiver = subobject_lea(target_rows, int(function['private_from']['site'], 0))
    if source_receiver != target_receiver:
        raise ValueError('source and target member subobject identities differ')
    receiver = source_receiver['receiver_register']
    register_aliases = {'esi': {'esi', 'si'}, 'edi': {'edi', 'di'},
                        'ebx': {'ebx', 'bx', 'bl', 'bh'}}[receiver]
    reads_receiver = False
    for insn in source:
        if insn.mnemonic.startswith('ret') and (insn.mnemonic != 'ret' or insn.op_str):
            raise ValueError('relocation-free member must have ordinary RET0 exits')
        if insn.group(CS_GRP_CALL) and insn.operands[0].type == X86_OP_IMM:
            raise ValueError('relocation-free member cannot bind direct external callees')
        for op in insn.operands:
            if op.type == X86_OP_MEM:
                if not op.mem.base or op.mem.segment:
                    raise ValueError('relocation-free member contains an absolute or segmented access')
                reads_receiver |= insn.reg_name(op.mem.base) == receiver
        if register_aliases & {insn.reg_name(r) for r in insn.regs_access()[1]}:
            raise ValueError('private member rewrites its preserved instance register')
    if not reads_receiver or not any(i.mnemonic == 'ret' for i in native):
        raise ValueError('private member lacks instance access or a normal return')
    return dict(**source_receiver, size=size, source_sha256=hashlib.sha256(raw).hexdigest(),
                target_sha256=hashlib.sha256(target).hexdigest(),
                source_instructions=len(source), target_instructions=len(native),
                absolute_relocations=0, scope='whole relocation-free member equality and actual subobject LEA; no caller equality')


def validate_canonical_identity(raw, canonical, calls, references):
    """Even an already-attested absolute immediate is outside this leaf scope."""
    if raw != canonical or calls or references:
        raise ValueError('relocation-free member cannot use canonical rewrites or address references')
