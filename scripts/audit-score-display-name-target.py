#!/usr/bin/env python3
"""Verify the complete score display-name boundary, ABI and canonical source body."""
import argparse
from collections import Counter
import hashlib
import importlib.util
import json
from pathlib import Path

import capstone
from capstone import x86
from workflow_manifest import load_manifest

ROOT = Path(__file__).resolve().parents[1]
ADDRESS, SIZE = 0x42E990, 990
SHA = '848993bfd662100b1cb3b0792b6ad3ffca55dd03c30f240312707ea91d9fb6e6'
UNIT = 'exact-first-score-display-name'


def require(condition, message):
    if not condition:
        raise ValueError(message)


def audit(obj=None):
    spec = importlib.util.spec_from_file_location('score_display_compare', ROOT / 'scripts/compare-function.py')
    compare = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(compare)
    identity = compare.verify_target()
    raw = compare.target_bytes(ADDRESS, SIZE)
    require(hashlib.sha256(raw).hexdigest() == SHA, 'target body changed')
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    decoder.detail = True
    instructions = list(decoder.disasm(raw, ADDRESS))
    require(len(instructions) == 311 and sum(i.size for i in instructions) == SIZE, 'decode boundary changed')
    by_address = {i.address: i for i in instructions}
    pending, reached, returns, calls = [ADDRESS], set(), [], Counter()
    while pending:
        address = pending.pop()
        if address in reached:
            continue
        require(address in by_address, 'escaping/noninstruction control edge')
        reached.add(address)
        instruction = by_address[address]
        if instruction.mnemonic == 'ret':
            require(bytes(instruction.bytes) == b'\xc2\x08\x00', 'RET8 ABI changed')
            returns.append(address)
            continue
        if instruction.mnemonic == 'call':
            require(instruction.operands[0].type == x86.X86_OP_IMM, 'unexpected indirect call')
            calls[hex(instruction.operands[0].imm)] += 1
        if instruction.group(capstone.CS_GRP_JUMP):
            require(instruction.operands[0].type == x86.X86_OP_IMM, 'unexpected indirect branch')
            pending.append(instruction.operands[0].imm)
            if instruction.mnemonic == 'jmp':
                continue
        pending.append(address + instruction.size)
    require(len(reached) == 311 and returns == [0x42ED6B], 'full CFG closure changed')
    require(compare.target_bytes(ADDRESS + SIZE, 2) == b'\xcc\xcc', 'following INT3 separation changed')
    require(calls == Counter({'0x4067d0': 5, '0x68a143': 15, '0x42e880': 1,
        '0x6183f0': 2, '0x42cc90': 2, '0x42e900': 2, '0x420a80': 2,
        '0x42d1b0': 2, '0x432d20': 2, '0x4020d0': 2, '0x45c320': 4,
        '0x4606e0': 2, '0x408a50': 2, '0x434a10': 1, '0x433a80': 1}), 'callee/guard census changed')
    caller = next(decoder.disasm(compare.target_bytes(0x4405D2, 5), 0x4405D2))
    require(caller.mnemonic == 'call' and caller.operands[0].imm == ADDRESS, 'authored CMenuEnd caller changed')
    require(compare.target_bytes(0x4405D7, 2) == b'\x84\xc0', 'caller no longer consumes AL')
    require(compare.target_bytes(0x6C1168, 27) == b'<color FF8080> new</color>\0', 'markup literal changed')
    report = dict(result='target_cfg_closed', target_sha256=identity, address=hex(ADDRESS),
        size=SIZE, code_sha256=SHA, instructions=311, reached=311, ret8_sites=[hex(a) for a in returns],
        calls=dict(calls), caller='0x4405d2', return_register='AL',
        limitations='Raw CFG and source comparison only; RNG, I/O, STL services and EH unwinding are not executed. Original nominal class and TU are unknown; callees receive no new ownership credit.')
    if obj is not None:
        function = load_manifest()['units'][UNIT]['functions'][0]
        targets = compare.known_targets()
        targets.update({name: int(address, 0) for name, address in
            (value.split('=', 1) for value in function['rel32_targets'])})
        candidate = compare.coff_symbol_bytes(obj, function['symbol_base'], ADDRESS, 0xffffffff,
            targets, compare.known_data_targets(), {})
        require(candidate == raw, 'complete canonical candidate differs')
        report.update(result='candidate_exact', candidate=dict(object=str(obj), size=len(candidate),
            sha256=hashlib.sha256(candidate).hexdigest(), all_relocations_replayed=True, unequal_positions=0))
    return report


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--object', type=Path)
    args = parser.parse_args()
    print(json.dumps(audit(args.object), indent=2))
