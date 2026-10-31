"""Full canonical COFF envelopes with one bounded compact-switch suffix.

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
FIELDS = {'size', 'sha256', 'alignment_hex', 'table_offset', 'table_entries',
          'map_offset', 'map_size', 'load_offset', 'jump_offset'}


def validate_contract(contract, code_size):
    if not isinstance(contract, dict) or set(contract) != FIELDS:
        raise ValueError('compact switch requires exact payload fields')
    if type(code_size) is not int or not 0 < code_size <= 65536:
        raise ValueError('compact switch requires a bounded complete code size')
    for key in FIELDS - {'sha256', 'alignment_hex'}:
        if type(contract[key]) is not int or contract[key] < 0:
            raise ValueError('invalid compact switch integer: ' + key)
    if not re.fullmatch('[0-9a-f]{64}', str(contract['sha256'])):
        raise ValueError('compact switch requires a full target payload hash')
    if contract['alignment_hex'] not in ('', '90', '8bff'):
        raise ValueError('unsupported compact switch alignment')
    pad = bytes.fromhex(contract['alignment_hex'])
    if (contract['table_offset'] != code_size + len(pad)
            or not 1 <= contract['table_entries'] <= 256
            or not contract['table_entries'] <= contract['map_size'] <= 256
            or contract['map_offset'] != contract['table_offset'] + 4 * contract['table_entries']
            or contract['size'] != contract['map_offset'] + contract['map_size']
            or not 0 <= contract['load_offset'] < contract['jump_offset'] < code_size):
        raise ValueError('compact switch leaves overlapping/unaccounted payload bytes')


def inspect(canonical, target, address, code_size, contract, relocations):
    validate_contract(contract, code_size)
    if (type(address) is not int or address < 0 or address + contract['size'] > 0x100000000
            or len(canonical) != contract['size'] or len(target) != contract['size']
            or hashlib.sha256(target).hexdigest() != contract['sha256']
            or canonical != target):
        raise ValueError('complete canonical compact-switch payload differs')
    table, index = contract['table_offset'], contract['map_offset']
    if (address + table) % 4 or target[code_size:table] != bytes.fromhex(contract['alignment_hex']):
        raise ValueError('compact switch alignment/address differs')
    table_fields = set(range(table, index, 4))
    suffix_relocs = [r for r in relocations if r[0] >= code_size]
    if (len(suffix_relocs) != len(table_fields)
            or {r[0] for r in suffix_relocs} != table_fields
            or any(r[1] != 6 or not r[2].startswith('$') for r in suffix_relocs)):
        raise ValueError('compact switch needs every and only local DIR32 jump word')
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    ins = list(md.disasm(target[:code_size], address))
    by = {i.address: i for i in ins}
    if (not ins or sum(i.size for i in ins) != code_size
            or ins[-1].address + ins[-1].size != address + code_size
            or ins[-1].mnemonic != 'ret'):
        raise ValueError('compact switch code does not close at its complete RET boundary')
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
    indices = target[index:]
    if set(indices) != set(range(contract['table_entries'])):
        raise ValueError('compact switch indices omit or escape jump entries')
    destinations = struct.unpack_from('<' + 'I' * contract['table_entries'], target, table)
    forbidden = {load.address, jump.address, guard.address}
    if spill is not None:
        forbidden.add(spill.address)
    if any(v not in by or v in forbidden for v in destinations):
        raise ValueError('compact switch destination is not an owned case instruction')
    indirect = []
    for instruction in ins:
        if instruction.group(capstone.CS_GRP_JUMP):
            operand = instruction.operands[0]
            if operand.type == x.X86_OP_IMM:
                if operand.imm not in by or operand.imm in forbidden:
                    raise ValueError('branch escapes code or bypasses the compact-switch guard')
            else:
                indirect.append(instruction.address)
    if indirect != [jump.address]:
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
        if instruction.mnemonic in ('ret', 'int3', 'ud2'):
            continue
        if at == jump.address:
            pending.extend(destinations)
            continue
        if instruction.group(capstone.CS_GRP_JUMP):
            pending.append(instruction.operands[0].imm)
            if instruction.mnemonic == 'jmp':
                continue
        pending.append(at + instruction.size)
    if load.address not in reached or jump.address not in reached or reached != set(by):
        raise ValueError('compact-switch code has unreachable or unowned instructions')
    return dict(code_size=code_size, payload_size=len(target),
                metadata_size=len(target) - code_size, table_entries=len(destinations),
                index_bytes=len(indices), reachable_code_bytes=sum(by[a].size for a in reached),
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
    targets, overrides = c.known_targets(), {}
    for mapping in function.get('rel32_targets', []):
        name, destination = mapping.rsplit('=', 1)
        targets[name] = int(destination, 0)
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
    return inspect(canonical, target, address, code_size, contract, relocations)
