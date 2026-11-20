"""Full canonical COFF envelopes with bounded compact-switch tables.

No suffix bytes are ignored: code, original alignment, jump words and index
bytes must all match. This is deliberately not an arbitrary trailing-data gate.
"""
from __future__ import annotations
import csv
import hashlib
import importlib.util
from pathlib import Path
import re
import struct

import capstone
from capstone import x86_const as x

ROOT = Path(__file__).resolve().parents[1]
TABLE_FIELDS = {'alignment_hex', 'table_offset', 'table_entries', 'map_offset',
                'map_size', 'load_offset', 'jump_offset'}
FIELDS = TABLE_FIELDS | {'size', 'sha256'}
OPTIONAL_FIELDS = {'second_table', 'tail_jumps'}


def validate_contract(contract, code_size):
    if (not isinstance(contract, dict) or not FIELDS <= contract.keys()
            or contract.keys() - FIELDS - OPTIONAL_FIELDS):
        raise ValueError('compact switch requires exact payload fields')
    if type(code_size) is not int or not 0 < code_size <= 65536:
        raise ValueError('compact switch requires a bounded complete code size')
    if not re.fullmatch('[0-9a-f]{64}', str(contract['sha256'])):
        raise ValueError('compact switch requires a full target payload hash')
    tables = [{key: contract[key] for key in TABLE_FIELDS}]
    if 'second_table' in contract:
        tables.append(contract['second_table'])
    end = code_size
    for table in tables:
        if not isinstance(table, dict) or table.keys() != TABLE_FIELDS:
            raise ValueError('compact switch requires exact table fields')
        for key in TABLE_FIELDS - {'alignment_hex'}:
            if type(table[key]) is not int or table[key] < 0:
                raise ValueError('invalid compact switch integer: ' + key)
        if table['alignment_hex'] not in ('', '90', '8bff'):
            raise ValueError('unsupported compact switch alignment')
        if (table['table_offset'] != end + len(bytes.fromhex(table['alignment_hex']))
                or not 1 <= table['table_entries'] <= table['map_size'] <= 256
                or table['map_offset'] != table['table_offset'] + 4 * table['table_entries']
                or not 0 <= table['load_offset'] < table['jump_offset'] < code_size):
            raise ValueError('compact switch leaves overlapping/unaccounted payload bytes')
        end = table['map_offset'] + table['map_size']
    if type(contract['size']) is not int or contract['size'] != end:
        raise ValueError('compact switch leaves overlapping/unaccounted payload bytes')
    tail_jumps = contract.get('tail_jumps', [])
    if (not isinstance(tail_jumps, list)
            or any(type(offset) is not int or not 0 <= offset <= code_size - 5 for offset in tail_jumps)
            or len(set(tail_jumps)) != len(tail_jumps)):
        raise ValueError('compact switch requires distinct in-code tail jump offsets')
    return tables


def inspect_table(target, address, start, contract, relocations, ins, by):
    table, index = contract['table_offset'], contract['map_offset']
    if (address + table) % 4 or target[start:table] != bytes.fromhex(contract['alignment_hex']):
        raise ValueError('compact switch alignment/address differs')
    load = by.get(address + contract['load_offset'])
    jump = by.get(address + contract['jump_offset'])
    if (load is None or jump is None or load.mnemonic != 'movzx'
            or len(load.operands) != 2 or load.operands[0].type != x.X86_OP_REG
            or load.operands[0].size != 4 or load.operands[1].type != x.X86_OP_MEM
            or load.operands[1].size != 1 or jump.mnemonic != 'jmp'
            or len(jump.operands) != 1 or jump.operands[0].type != x.X86_OP_MEM
            or load.address + load.size != jump.address):
        raise ValueError('compact switch load/dispatch instruction shape differs')
    lm, jm = load.operands[1].mem, jump.operands[0].mem
    if (lm.segment or lm.index or not lm.base or lm.scale != 1
            or lm.disp & 0xffffffff != address + index
            or jm.segment or jm.base or jm.index != load.operands[0].reg
            or jm.scale != 4 or jm.disp & 0xffffffff != address + table):
        raise ValueError('compact switch index/table operands disagree')
    number = ins.index(load)
    if number < 2:
        raise ValueError('compact switch has no adjacent unsigned range guard')
    bound, guard = ins[number - 2:number]
    spill = None
    # VC8 can schedule one flags-preserving stack-byte store before JA.
    # It cannot write the range index or supply different condition flags.
    if bound.mnemonic == 'mov':
        spill = bound
        if (number < 3 or len(spill.operands) != 2
                or spill.operands[0].type != x.X86_OP_MEM or spill.operands[0].size != 1
                or spill.operands[1].type != x.X86_OP_REG or spill.operands[1].size != 1
                or spill.operands[0].mem.base != x.X86_REG_ESP
                or spill.operands[0].mem.index or spill.operands[0].mem.segment
                or not 0 <= spill.operands[0].mem.disp <= 65535):
            raise ValueError('unsupported instruction between compact-switch bound and guard')
        bound = ins[number - 3]
    if (bound.mnemonic != 'cmp' or len(bound.operands) != 2
            or bound.operands[0].type != x.X86_OP_REG or bound.operands[0].size != 4
            or bound.operands[0].reg != lm.base or bound.operands[1].type != x.X86_OP_IMM
            or bound.operands[1].imm != contract['map_size'] - 1
            or guard.mnemonic != 'ja' or len(guard.operands) != 1
            or guard.operands[0].type != x.X86_OP_IMM
            or guard.operands[0].imm not in by
            or bound.address <= guard.operands[0].imm < jump.address + jump.size):
        raise ValueError('compact switch bound/index/default disagree')
    for instruction in (load, jump):
        field = instruction.address - address + instruction.disp_offset
        hits = [r for r in relocations if r[0] == field]
        if (instruction.disp_size != 4 or len(hits) != 1 or hits[0][1] != 6
                or not hits[0][2].startswith('$')):
            raise ValueError('compact switch address lacks its local DIR32 proof')
    indices = target[index:index + contract['map_size']]
    if set(indices) != set(range(contract['table_entries'])):
        raise ValueError('compact switch indices omit or escape jump entries')
    destinations = struct.unpack_from('<' + 'I' * contract['table_entries'], target, table)
    forbidden = {load.address, jump.address, guard.address}
    if spill is not None:
        forbidden.add(spill.address)
    return jump.address, destinations, forbidden


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

    table_fields = {offset for table in tables
                    for offset in range(table['table_offset'], table['map_offset'], 4)}
    suffix_relocs = [r for r in relocations if r[0] >= code_size]
    if (len(suffix_relocs) != len(table_fields)
            or {r[0] for r in suffix_relocs} != table_fields
            or any(r[1] != 6 or not r[2].startswith('$') for r in suffix_relocs)):
        raise ValueError('compact switch needs every and only local DIR32 jump word')

    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    ins = list(md.disasm(target[:code_size], address))
    by = {i.address: i for i in ins}
    if not ins or ins[-1].address + ins[-1].size != address + code_size or ins[-1].mnemonic != 'ret':
        raise ValueError('compact switch code does not close at its complete RET boundary')
    dispatches = {}
    forbidden = set()
    start = code_size
    for table in tables:
        jump, destinations, protected = inspect_table(target, address, start, table, relocations, ins, by)
        if jump in dispatches:
            raise ValueError('compact switch dispatch is shared by multiple tables')
        dispatches[jump] = destinations
        forbidden.update(protected)
        start = table['map_offset'] + table['map_size']
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

    indirect = set()
    for instruction in ins:
        if instruction.group(capstone.CS_GRP_JUMP):
            operand = instruction.operands[0]
            if operand.type == x.X86_OP_IMM:
                if instruction.address not in tail_jumps and (operand.imm not in by or operand.imm in forbidden):
                    raise ValueError('branch escapes code or bypasses the compact-switch guard')
            else:
                indirect.add(instruction.address)
    if indirect != dispatches.keys():
        raise ValueError('unsupported additional indirect branch in compact-switch code')
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
    if reached != by.keys():
        raise ValueError('compact-switch code has unreachable or unowned instructions')
    return dict(code_size=code_size, payload_size=len(target),
                metadata_size=len(target) - code_size, switch_tables=len(tables),
                table_entries=len(table_fields), index_bytes=sum(t['map_size'] for t in tables),
                reachable_code_bytes=sum(by[a].size for a in reached),
                canonical_payload_sha256=hashlib.sha256(canonical).hexdigest(),
                target_payload_sha256=contract['sha256'])


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
    selected = [r for r in rows if int(r['address'], 0) == address]
    if len(selected) != 1:
        raise ValueError('compact switch has no unique candidate')
    code_size = int(selected[0]['size'])
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
