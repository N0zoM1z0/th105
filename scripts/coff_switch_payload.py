"""Full canonical COFF envelopes with bounded compact-switch tables.

No suffix bytes are ignored: code, original alignment, jump words and index
bytes must all match. This is deliberately not an arbitrary trailing-data gate.
"""
from __future__ import annotations
import csv
import hashlib
import importlib.util
from itertools import groupby
from pathlib import Path
import re
import struct

import capstone
from capstone import x86_const as x

ROOT = Path(__file__).resolve().parents[1]
TABLE_FIELDS = {'alignment_hex', 'table_offset', 'table_entries', 'jump_offset'}
COMPACT_FIELDS = {'map_offset', 'map_size', 'load_offset'}
PAYLOAD_FIELDS = {'size', 'sha256'}
OPTIONAL_FIELDS = {'additional_tables', 'tail_jumps', 'virtual_tail_jumps'}
ALIGNMENT_NOPS = {bytes.fromhex(code) for code in (
    '90', '8bff', '8d4900', '8d642400', '8d9b00000000', '8da42400000000',
)}
NONVOLATILE_ALIASES = {
    x.X86_REG_EBX: {x.X86_REG_EBX, x.X86_REG_BX, x.X86_REG_BL, x.X86_REG_BH},
    x.X86_REG_EBP: {x.X86_REG_EBP, x.X86_REG_BP},
    x.X86_REG_ESI: {x.X86_REG_ESI, x.X86_REG_SI},
    x.X86_REG_EDI: {x.X86_REG_EDI, x.X86_REG_DI},
}


def is_absolute_double_load(inst):
    return (inst.mnemonic == 'fld' and len(inst.operands) == 1
            and inst.operands[0].type == x.X86_OP_MEM and inst.operands[0].size == 8
            and not inst.operands[0].mem.base and not inst.operands[0].mem.index
            and not inst.operands[0].mem.segment)


def allowed_dispatch_prefix(inst, index_reg):
    if is_absolute_double_load(inst):
        return True
    if (inst.mnemonic == 'push' and len(inst.operands) == 1
            and inst.operands[0].type == x.X86_OP_REG
            and inst.operands[0].reg in (x.X86_REG_EBX, x.X86_REG_EBP, x.X86_REG_EDI)):
        return True
    if (inst.mnemonic == 'mov' and len(inst.operands) == 2
            and inst.operands[0].type == x.X86_OP_REG
            and inst.operands[1].type == x.X86_OP_IMM):
        dst_reg = inst.operands[0].reg
        for parent, aliases in NONVOLATILE_ALIASES.items():
            if parent != x.X86_REG_ESI and dst_reg in aliases:
                return index_reg not in aliases
    return False


def validate_contract(contract, code_size):
    if not isinstance(contract, dict) or not PAYLOAD_FIELDS <= contract.keys():
        raise ValueError('compact switch requires exact payload fields')
    if type(code_size) is not int or not 0 < code_size <= 262144:
        raise ValueError('compact switch requires a bounded complete code size')
    if not re.fullmatch('[0-9a-f]{64}', str(contract['sha256'])):
        raise ValueError('compact switch requires a full target payload hash')
    additional = contract.get('additional_tables', [])
    if not isinstance(additional, list):
        raise ValueError('switch payload additional tables must be a list')
    tables = [{key: contract[key] for key in contract.keys() - PAYLOAD_FIELDS - OPTIONAL_FIELDS}, *additional]
    end = code_size
    for table in tables:
        if not isinstance(table, dict) or table.keys() not in (TABLE_FIELDS, TABLE_FIELDS | COMPACT_FIELDS):
            raise ValueError('compact switch requires exact table fields')
        for key in table.keys() - {'alignment_hex'}:
            if type(table[key]) is not int or table[key] < 0:
                raise ValueError('invalid compact switch integer: ' + key)
        if table['alignment_hex'] not in ('', '90', '8bff', '8d4900'):
            raise ValueError('unsupported compact switch alignment')
        if (table['table_offset'] != end + len(bytes.fromhex(table['alignment_hex']))
                or not 1 <= table['table_entries'] <= 256
                or table['jump_offset'] >= code_size):
            raise ValueError('compact switch leaves overlapping/unaccounted payload bytes')
        end = table['table_offset'] + 4 * table['table_entries']
        if 'map_offset' in table:
            if (table['map_offset'] != end
                    or not table['table_entries'] <= table['map_size'] <= 256
                    or table['load_offset'] >= table['jump_offset']):
                raise ValueError('compact switch leaves overlapping/unaccounted payload bytes')
            end += table['map_size']
    if type(contract['size']) is not int or contract['size'] != end:
        raise ValueError('compact switch leaves overlapping/unaccounted payload bytes')
    tail_jumps = contract.get('tail_jumps', [])
    if (not isinstance(tail_jumps, list)
            or any(type(offset) is not int or not 0 <= offset <= code_size - 5 for offset in tail_jumps)
            or len(set(tail_jumps)) != len(tail_jumps)):
        raise ValueError('compact switch requires distinct in-code tail jump offsets')
    virtual_tails = contract.get('virtual_tail_jumps', [])
    if (not isinstance(virtual_tails, list)
            or any(type(offset) is not int or not 0 <= offset <= code_size - 2 for offset in virtual_tails)
            or len(set(virtual_tails)) != len(virtual_tails)
            or set(virtual_tails) & set(tail_jumps)):
        raise ValueError('compact switch requires distinct in-code virtual tail jump offsets')
    return tables


def inspect_register_bound(ins, bound_index, expected):
    bound = ins[bound_index]
    reg = bound.operands[1].reg
    aliases = NONVOLATILE_ALIASES.get(reg)
    code_end = ins[-1].address + ins[-1].size
    if aliases and reg != bound.operands[0].reg:
        for index in range(bound_index - 1, -1, -1):
            inst = ins[index]
            if (inst.group(capstone.CS_GRP_JUMP) or inst.group(capstone.CS_GRP_RET)
                    or (inst.group(capstone.CS_GRP_CALL)
                        and (inst.operands[0].type != x.X86_OP_IMM
                             or ins[0].address <= inst.operands[0].imm < code_end))):
                return None
            if aliases.isdisjoint(inst.regs_access()[1]):
                continue
            if (inst.mnemonic == 'mov' and inst.operands[0].type == x.X86_OP_REG
                    and inst.operands[0].reg == reg and inst.operands[1].type == x.X86_OP_IMM
                    and inst.operands[1].imm == expected):
                # Direct out-of-span calls preserve the nonvolatile bound register.
                # Reject explicit entries that bypass the defining MOV.
                return {step.address for step in ins[index + 1:bound_index + 1]}
            break
    raise ValueError('compact switch register bound lacks a reaching constant')


def verify_cfg_register_bound(address, code_size, by, dispatches, tail_jumps, bound_addr, reg, expected):
    aliases = NONVOLATILE_ALIASES.get(reg)
    if not aliases:
        raise ValueError('compact switch register bound lacks a reaching constant')
    code_end = address + code_size
    # Track nonvolatile constants together: Alice derives EBX=4 from EBP=8
    # with LEA before the switch guard. Calls preserve these registers.
    registers = tuple(NONVOLATILE_ALIASES)
    unknown = {r: 'TOP' for r in registers}
    in_state = {address: unknown}
    worklist = [address]

    def merge(dst, val):
        prev = in_state.get(dst)
        if prev is None:
            in_state[dst] = val
            worklist.append(dst)
        else:
            joined = {r: prev[r] if prev[r] == val[r] else 'TOP' for r in registers}
            if joined != prev:
                in_state[dst] = joined
                worklist.append(dst)

    while worklist:
        at = worklist.pop()
        val = in_state[at]
        inst = by[at]
        if inst.mnemonic in ('ret', 'int3', 'ud2') or at in tail_jumps:
            continue
        if at in dispatches:
            for dst in dispatches[at]:
                merge(dst, val)
            continue
        out_val = val.copy()
        if inst.group(capstone.CS_GRP_CALL):
            if inst.operands[0].type == x.X86_OP_IMM and address <= inst.operands[0].imm < code_end:
                out_val = unknown
        else:
            written = inst.regs_access()[1]
            for register, register_aliases in NONVOLATILE_ALIASES.items():
                if register_aliases.isdisjoint(written):
                    continue
                value = 'TOP'
                if (len(inst.operands) == 2 and inst.operands[0].type == x.X86_OP_REG
                        and inst.operands[0].reg == register):
                    source = inst.operands[1]
                    if inst.mnemonic == 'mov':
                        if source.type == x.X86_OP_IMM:
                            value = source.imm & 0xffffffff
                        elif source.type == x.X86_OP_REG:
                            value = val.get(source.reg, 'TOP')
                    elif (inst.mnemonic == 'lea' and source.type == x.X86_OP_MEM
                          and not source.mem.index and not source.mem.segment
                          and isinstance(val.get(source.mem.base), int)):
                        value = (val[source.mem.base] + source.mem.disp) & 0xffffffff
                out_val[register] = value
        if inst.group(capstone.CS_GRP_JUMP):
            merge(inst.operands[0].imm, out_val)
            if inst.mnemonic == 'jmp':
                continue
        merge(at + inst.size, out_val)

    if in_state.get(bound_addr, unknown)[reg] != expected:
        raise ValueError('compact switch register bound lacks a reaching constant')


def inspect_table(target, address, start, contract, relocations, ins, by):
    table = contract['table_offset']
    if (address + table) % 4 or target[start:table] != bytes.fromhex(contract['alignment_hex']):
        raise ValueError('compact switch alignment/address differs')
    jump = by.get(address + contract['jump_offset'])
    if (jump is None or jump.mnemonic != 'jmp' or len(jump.operands) != 1
            or jump.operands[0].type != x.X86_OP_MEM):
        raise ValueError('switch dispatch instruction shape differs')
    jm = jump.operands[0].mem
    if jm.segment or jm.base or not jm.index or jm.scale != 4 or jm.disp & 0xffffffff != address + table:
        raise ValueError('compact switch index/table operands disagree')
    relocated = [jump]
    selector = jm.index
    case_count = contract['table_entries']
    dispatch_prefix = []
    if 'map_offset' in contract:
        index = contract['map_offset']
        load = by.get(address + contract['load_offset'])
        if (load is None or load.mnemonic != 'movzx'
                or len(load.operands) != 2 or load.operands[0].type != x.X86_OP_REG
                or load.operands[0].reg != jm.index or load.operands[1].type != x.X86_OP_MEM
                or load.operands[1].size != 1):
            raise ValueError('compact switch load/dispatch instruction shape differs')
        lm = load.operands[1].mem
        if lm.segment or lm.index or not lm.base or lm.scale != 1 or lm.disp & 0xffffffff != address + index:
            raise ValueError('compact switch index/table operands disagree')
        relocated.append(load)
        selector = lm.base
        case_count = contract['map_size']
        if set(target[index:index + case_count]) != set(range(contract['table_entries'])):
            raise ValueError('compact switch indices omit or escape jump entries')
        dispatch_prefix = ins[ins.index(load) + 1:ins.index(jump)]
        if len(dispatch_prefix) > 2 or any(
                not allowed_dispatch_prefix(inst, jm.index)
                for inst in dispatch_prefix):
            raise ValueError('unsupported instruction between switch selector load and dispatch')
    number = ins.index(relocated[-1])
    if number >= 3 and is_absolute_double_load(ins[number - 1]):
        dispatch_prefix = [ins[number - 1], *dispatch_prefix]
        number -= 1
    if number < 2:
        raise ValueError('compact switch has no adjacent unsigned range guard')
    guard = ins[number - 1]
    scheduled = []
    bound_index = number - 2
    # VC8 can schedule flag-preserving saves, stores and address setup between CMP and JA.
    while bound_index > 0 and ins[bound_index].mnemonic in ('push', 'mov', 'lea', 'fst', 'fstp'):
        store = ins[bound_index]
        dest = store.operands[0]
        # Youmu action720 schedules its two work-counter constants here.
        # Full-register MOV/LEA preserve CMP flags; neither may replace the selector.
        if (store.mnemonic == 'mov' and dest.type == x.X86_OP_REG
                and dest.reg == x.X86_REG_EDX and selector != x.X86_REG_EDX
                and store.operands[1].type == x.X86_OP_IMM):
            scheduled.append(store)
            bound_index -= 1
            continue
        # Tenshi story720 initializes its spread limit without changing CMP flags.
        if (store.mnemonic == 'mov' and dest.type == x.X86_OP_REG
                and dest.reg == x.X86_REG_EBX and selector != x.X86_REG_EBX
                and store.operands[1].type == x.X86_OP_IMM and store.operands[1].imm == 7):
            scheduled.append(store)
            bound_index -= 1
            continue
        if (store.mnemonic == 'lea' and dest.type == x.X86_OP_REG
                and dest.reg == x.X86_REG_ECX and selector != x.X86_REG_ECX
                and store.operands[1].type == x.X86_OP_MEM
                and store.operands[1].mem.base == x.X86_REG_EDX
                and not store.operands[1].mem.index and not store.operands[1].mem.segment):
            scheduled.append(store)
            bound_index -= 1
            continue
        if dest.type == x.X86_OP_REG and dest.reg == x.X86_REG_EDI:
            saves_edi = store.mnemonic == 'push' and selector != x.X86_REG_ESP
            sets_const = (store.mnemonic == 'mov' and selector != x.X86_REG_EDI
                          and store.operands[1].type == x.X86_OP_IMM and store.operands[1].imm in (1, 2, 5, 60, 0xc8, 0x190))
            if saves_edi or sets_const:
                scheduled.append(store)
                bound_index -= 1
                continue
        if (store.mnemonic == 'mov' and dest.type == x.X86_OP_REG
                and dest.reg == x.X86_REG_ECX and selector != x.X86_REG_ECX
                and store.operands[1].type == x.X86_OP_IMM and store.operands[1].imm in (2, 0x190)):
            scheduled.append(store)
            bound_index -= 1
            continue
        if dest.type == x.X86_OP_REG and dest.reg == x.X86_REG_EBP:
            saves_ebp = store.mnemonic == 'push' and selector != x.X86_REG_ESP
            sets_ebp_const = (store.mnemonic == 'mov' and selector != x.X86_REG_EBP
                              and store.operands[1].type == x.X86_OP_IMM and store.operands[1].imm == 2)
            if saves_ebp or sets_ebp_const:
                scheduled.append(store)
                bound_index -= 1
                continue
        if (store.mnemonic == 'lea' and dest.type == x.X86_OP_REG
                and dest.reg == x.X86_REG_EBP and selector != x.X86_REG_EBP
                and store.operands[1].type == x.X86_OP_MEM
                and store.operands[1].mem.base in (x.X86_REG_ECX, x.X86_REG_EDI)
                and not store.operands[1].mem.index and not store.operands[1].mem.segment):
            scheduled.append(store)
            bound_index -= 1
            continue
        if (dest.type != x.X86_OP_MEM or dest.mem.index or dest.mem.segment
                or not 0 <= dest.mem.disp <= 65535):
            raise ValueError('unsupported instruction between compact-switch bound and guard')
        receiver_store = dest.mem.base == x.X86_REG_ESI and (
            store.mnemonic != 'fstp' or dest.size == 4)
        stack_spill = dest.mem.base == x.X86_REG_ESP and (
            (dest.size == 1 and store.mnemonic == 'mov' and store.operands[1].type == x.X86_OP_REG)
            or (dest.size == 4 and store.mnemonic in ('fst', 'fstp')))
        if not receiver_store and not stack_spill:
            raise ValueError('unsupported instruction between compact-switch bound and guard')
        scheduled.append(store)
        bound_index -= 1
    bound = ins[bound_index]
    if (bound.mnemonic != 'cmp' or len(bound.operands) != 2
            or bound.operands[0].type != x.X86_OP_REG or bound.operands[0].size != 4
            or bound.operands[0].reg != selector
            or guard.mnemonic != 'ja' or len(guard.operands) != 1
            or guard.operands[0].type != x.X86_OP_IMM
            or guard.operands[0].imm not in by
            or bound.address <= guard.operands[0].imm < jump.address + jump.size):
        raise ValueError('compact switch bound/index/default disagree')
    limit = bound.operands[1]
    deferred_bound = None
    if limit.type == x.X86_OP_REG:
        protected_bound = inspect_register_bound(ins, bound_index, case_count - 1)
        if protected_bound is None:
            protected_bound = set()
            deferred_bound = (bound.address, limit.reg, case_count - 1)
    elif limit.type == x.X86_OP_IMM and limit.imm == case_count - 1:
        protected_bound = set()
    else:
        raise ValueError('compact switch bound/index/default disagree')
    for instruction in relocated:
        field = instruction.address - address + instruction.disp_offset
        hits = [r for r in relocations if r[0] == field]
        if (instruction.disp_size != 4 or len(hits) != 1 or hits[0][1] != 6
                or not hits[0][2].startswith('$')):
            raise ValueError('compact switch address lacks its local DIR32 proof')
    destinations = struct.unpack_from('<' + 'I' * contract['table_entries'], target, table)
    forbidden = {instruction.address for instruction in [*relocated, *scheduled, *dispatch_prefix, guard]}
    return jump.address, destinations, forbidden | protected_bound, deferred_bound


def virtual_tail_setup(ins, index):
    # VC8 loads a slot through the saved receiver, restores the Fighter frame
    # and jumps through the loaded register. ECX setup can be scheduled among
    # the restores when it has not already happened in the case body.
    tail = ins[index]
    if index < 6 or tail.mnemonic != 'jmp' or tail.operands[0].type != x.X86_OP_REG:
        raise ValueError('compact switch virtual tail is not a register jump with an epilogue')
    start = index - 6
    if ins[index - 4].mnemonic == 'mov' and ins[index - 4].op_str == 'ecx, esi':
        start -= 1
    if start < 0:
        raise ValueError('compact switch virtual tail is missing its setup')
    vtable, slot, *restores = ins[start:index]
    restores = [i for i in restores if (i.mnemonic, i.op_str) != ('mov', 'ecx, esi')]
    if ([(i.mnemonic, i.op_str) for i in restores] !=
            [('pop', 'edi'), ('pop', 'esi'), ('pop', 'ebx'), ('add', 'esp, 4')]):
        raise ValueError('compact switch virtual tail does not restore the Fighter frame')
    if any(i.mnemonic != 'mov' or i.operands[0].type != x.X86_OP_REG
           or i.operands[1].type != x.X86_OP_MEM or i.operands[1].size != 4
           or i.operands[1].mem.index or i.operands[1].mem.segment for i in (vtable, slot)):
        raise ValueError('compact switch virtual tail needs two unindexed DWORD loads')
    vptr = vtable.operands[1].mem
    target = slot.operands[1].mem
    if (vptr.base != x.X86_REG_ESI or vptr.disp != 0 or target.base != vtable.operands[0].reg
            or target.disp < 0 or target.disp % 4
            or slot.operands[0].reg != tail.operands[0].reg
            or tail.operands[0].reg not in (x.X86_REG_EAX, x.X86_REG_EDX)):
        raise ValueError('compact switch virtual tail register does not come from a vtable slot')
    return {i.address for i in ins[start + 1:index + 1]}


def inspect(canonical, target, address, code_size, contract, relocations, tail_targets=None):
    tables = validate_contract(contract, code_size)
    if (type(address) is not int or address < 0 or address + contract['size'] > 0x100000000
            or len(canonical) != contract['size'] or len(target) != contract['size']
            or hashlib.sha256(target).hexdigest() != contract['sha256']):
        raise ValueError('complete compact-switch payload size or target hash differs')
    if canonical != target:
        offset = next(i for i, (actual, expected) in enumerate(zip(canonical, target))
                      if actual != expected)
        raise ValueError(f'complete canonical compact-switch payload differs at {address + offset:#010x}')

    table_fields = {table['table_offset'] + 4 * entry
                    for table in tables for entry in range(table['table_entries'])}
    suffix_relocs = [r for r in relocations if r[0] >= code_size]
    if (len(suffix_relocs) != len(table_fields)
            or {r[0] for r in suffix_relocs} != table_fields
            or any(r[1] != 6 or not r[2].startswith('$') for r in suffix_relocs)):
        raise ValueError('compact switch needs every and only local DIR32 jump word')

    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    ins = list(md.disasm(target[:code_size], address))
    by = {i.address: i for i in ins}
    if not ins or ins[-1].address + ins[-1].size != address + code_size:
        raise ValueError('switch code does not decode through its complete boundary')
    dispatches = {}
    forbidden = set()
    deferred_bounds = []
    start = code_size
    for table in tables:
        jump, destinations, protected, deferred = inspect_table(
            target, address, start, table, relocations, ins, by)
        if jump in dispatches:
            raise ValueError('compact switch dispatch is shared by multiple tables')
        dispatches[jump] = destinations
        forbidden.update(protected)
        if deferred is not None:
            deferred_bounds.append(deferred)
        start = table['table_offset'] + 4 * table['table_entries'] + table.get('map_size', 0)
    virtual_tails = {address + offset for offset in contract.get('virtual_tail_jumps', [])}
    if virtual_tails:
        indices = {instruction.address: index for index, instruction in enumerate(ins)}
        for at in virtual_tails:
            if at not in indices or at in dispatches:
                raise ValueError('compact switch virtual tail is not a distinct instruction')
            forbidden.update(virtual_tail_setup(ins, indices[at]))
    if any(v not in by or v in forbidden for destinations in dispatches.values() for v in destinations):
        raise ValueError('compact switch destination is not an owned case instruction')

    tail_targets = tail_targets or {}
    tail_jumps = set()
    for offset in contract.get('tail_jumps', []):
        instruction = by.get(address + offset)
        hits = [r for r in relocations if r[0] == offset + 1]
        if (instruction is None or instruction.mnemonic != 'jmp' or instruction.size != 5
                or instruction.bytes[0] != 0xe9 or len(hits) != 1 or hits[0][1] != 20
                or address <= instruction.operands[0].imm < address + contract['size']
                or tail_targets.get(hits[0][2]) != instruction.operands[0].imm):
            raise ValueError('compact switch tail jump lacks an external REL32 binding')
        tail_jumps.add(instruction.address)
    tail_jumps.update(virtual_tails)
    last = ins[-1]
    internal_jump = (last.mnemonic == 'jmp' and last.operands[0].type == x.X86_OP_IMM
                     and last.operands[0].imm in by)
    if last.mnemonic != 'ret' and last.address not in tail_jumps and not internal_jump:
        raise ValueError('switch code does not end at a RET, internal jump or bound tail jump')

    indirect = set()
    for instruction in ins:
        if instruction.group(capstone.CS_GRP_JUMP):
            operand = instruction.operands[0]
            if operand.type == x.X86_OP_IMM:
                if instruction.address not in tail_jumps and (operand.imm not in by or operand.imm in forbidden):
                    raise ValueError('branch escapes code or bypasses the compact-switch guard '
                                     f'at {instruction.address:#010x} to {operand.imm:#010x}')
            else:
                indirect.add(instruction.address)
        elif instruction.group(capstone.CS_GRP_CALL):
            operand = instruction.operands[0]
            if operand.type == x.X86_OP_IMM and address <= operand.imm < address + code_size:
                if operand.imm not in by or operand.imm in forbidden:
                    raise ValueError('call bypasses the compact-switch guard or enters an instruction')
    if indirect != dispatches.keys() | virtual_tails:
        raise ValueError('unsupported additional indirect branch in compact-switch code')
    for bound_addr, reg, expected in deferred_bounds:
        verify_cfg_register_bound(
            address, code_size, by, dispatches, tail_jumps, bound_addr, reg, expected)
    # Close every reachable path without interpreting metadata as executable code.
    pending, reached = [address], set()
    while pending:
        at = pending.pop()
        if at in reached:
            continue
        instruction = by.get(at)
        if instruction is None:
            raise ValueError('reachable compact-switch path falls outside code')
        reached.add(at)
        if instruction.mnemonic in ('ret', 'int3', 'ud2') or at in tail_jumps:
            continue
        if at in dispatches:
            pending.extend(dispatches[at])
            continue
        if instruction.group(capstone.CS_GRP_JUMP):
            pending.append(instruction.operands[0].imm)
            if instruction.mnemonic == 'jmp':
                continue
        pending.append(at + instruction.size)
    alignment = []
    for reachable, instructions in groupby(ins, key=lambda i: i.address in reached):
        if reachable:
            continue
        padding = list(instructions)
        start = padding[0].address
        end = padding[-1].address + padding[-1].size
        if (end not in reached or end % 16 or end - start >= 16
                or any(bytes(i.bytes) not in ALIGNMENT_NOPS
                       and not (i.size == 2 and i.bytes[0] == 0xeb
                                and i.operands[0].imm == end)
                       for i in padding)):
            raise ValueError('compact-switch code has unreachable or unowned instructions')
        alignment.append((start - address, end - address))
    return dict(code_size=code_size, payload_size=len(target),
                metadata_size=len(target) - code_size, switch_tables=len(tables),
                table_entries=len(table_fields), index_bytes=sum(t.get('map_size', 0) for t in tables),
                reachable_code_bytes=sum(by[a].size for a in reached),
                internal_alignment=alignment,
                canonical_payload_sha256=hashlib.sha256(canonical).hexdigest(),
                target_payload_sha256=contract['sha256'])


def function_code_size(function, rows, *, require_bytes=False):
    address = int(function['address'], 0)
    selected = [row for row in rows if int(row['address'], 0) == address]
    if len(selected) != 1:
        raise ValueError('compact switch has no unique candidate')
    if function.get('contiguous_span'):
        raise ValueError('compact switch cannot use an unreviewed contiguous span')
    if function.get('owned_extent'):
        from function_byte_ownership import load
        ownership = load({int(row['address'], 0): row for row in rows},
                         require_bytes=require_bytes).get(address)
        if ownership is None:
            raise ValueError('compact switch requires reviewed function-byte ownership')
        return ownership['extent_end'] - address + 1
    return int(selected[0]['size'])


def verify(object_path, function, rows=None, read_target=None):
    import pefile
    from rank_retained_exact import read_coff_function
    spec = importlib.util.spec_from_file_location('compact_payload_comparator', ROOT / 'scripts/compare-function.py')
    c = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(c)
    c.verify_target()
    if rows is None:
        with (ROOT / 'config/functions.csv').open(newline='') as f:
            rows = list(csv.DictReader(f))
    address = int(function['address'], 0)
    code_size = function_code_size(function, rows, require_bytes=True)
    contract = function['switch_payload']
    validate_contract(contract, code_size)
    if any(address < int(r['address'], 0) < address + contract['size'] for r in rows):
        raise ValueError('compact-switch envelope overlaps another candidate entry')
    _, raw, _, relocations = read_coff_function(Path(object_path), function['symbol_base'], None)
    if len(raw) != contract['size']:
        raise ValueError('compact-switch contract is not the entire source COMDAT tail')
    known_data = c.known_data_targets()
    if any(kind == 6 and name.startswith('$') and name in known_data for _, kind, name in relocations):
        raise ValueError('local switch symbols cannot be external data aliases')
    tail_targets, overrides = {}, {}
    for mapping in function.get('rel32_targets', []):
        name, destination = mapping.rsplit('=', 1)
        tail_targets[name] = int(destination, 0)
    targets = c.known_targets() | tail_targets
    for mapping in function.get('dir32_targets', []):
        name, key = mapping.rsplit('=', 1)
        if name.startswith('$'):
            raise ValueError('local switch fields cannot use DIR32 overrides')
        overrides[name] = key
    canonical = c.coff_symbol_bytes(Path(object_path), function['symbol_base'], address,
                                    contract['size'], targets, known_data, overrides)
    target = (read_target or c.target_bytes)(address, contract['size'])
    pe = pefile.PE(str(c.TARGET))
    directory = pe.OPTIONAL_HEADER.DATA_DIRECTORY[5]
    if (not pe.FILE_HEADER.Characteristics & 1
            or pe.OPTIONAL_HEADER.DllCharacteristics & 0x40
            or pe.OPTIONAL_HEADER.ImageBase != 0x400000
            or directory.VirtualAddress or directory.Size):
        raise ValueError('compact-switch target must be the attested fixed-base stripped image')
    return inspect(canonical, target, address, code_size, contract, relocations, tail_targets)
