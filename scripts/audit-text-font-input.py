#!/usr/bin/env python3
"""Compare render's first-character values and input reads on guarded pages.

Runs attested 1.06a and the supplied native COFF through the first glyph/end
entry or a read fault. The begin operation is a checked RET0 observer. Glyph,
GDI, allocation and EH are not executed. This is not an exact-match gate.
"""
from __future__ import annotations

import argparse
import gc
import hashlib
import importlib.util
import json
from pathlib import Path
import struct
import sys

from unicorn import (Uc, UcError, UC_ARCH_X86, UC_MODE_32, UC_HOOK_CODE,
                     UC_HOOK_MEM_READ, UC_HOOK_MEM_INVALID, UC_MEM_READ_UNMAPPED)
from unicorn.x86_const import (UC_X86_REG_EAX, UC_X86_REG_ECX, UC_X86_REG_EDX,
                              UC_X86_REG_ESI, UC_X86_REG_ESP, UC_X86_REG_EIP,
                              UC_X86_REG_EFLAGS)

import linked_pe
from workflow_manifest import load_manifest

ROOT = Path(__file__).resolve().parents[1]
ENTRY, TARGET_SIZE = 0x412670, 326
FONT, STACK, PAGE = 0x1000000, 0x2000000, 0x3000000


def packed(value):
    return struct.pack('<I', value & 0xffffffff)


def source_body(path, comparator):
    spec = importlib.util.spec_from_file_location(
        'font_input_coff', ROOT / 'scripts/compare-giant-action-switches.py')
    mapper = importlib.util.module_from_spec(spec)
    sys.modules[spec.name] = mapper
    spec.loader.exec_module(mapper)
    function = next(f for unit in load_manifest()['units'].values()
                    for f in unit['functions'] if f['address'] == '0x00412670')
    obj = mapper.CoffObject(path, symbol_base=function['symbol_base'])
    targets = {name: int(address, 0) for name, address in
               (value.split('=', 1) for value in function['rel32_targets'])}
    return comparator.coff_symbol_bytes(
        path, function['symbol_base'], ENTRY, len(obj.text), targets,
        comparator.known_data_targets())


class PrefixMachine:
    def __init__(self, body, payload, placement):
        self.body = body
        self.reads, self.fault, self.status = [], None, None
        self.character, self.error, self.decoding = None, None, False
        offset = {'aligned': 0x100, 'unaligned': 0x101,
                  'guard': 0x1000 - len(payload)}[placement]
        self.cursor = PAGE + offset
        self.uc = Uc(UC_ARCH_X86, UC_MODE_32)
        self.uc.mem_map(0x400000, 0x310000)
        self.uc.mem_write(ENTRY, body)
        self.uc.mem_map(FONT, 0x1000)
        self.uc.mem_map(STACK, 0x10000)
        self.uc.mem_map(PAGE, 0x1000)
        self.uc.mem_write(self.cursor, payload)
        top = STACK + 0x8000
        self.uc.mem_write(top, packed(0x700100) + packed(self.cursor)
                          + packed(0) + packed(0))
        self.uc.reg_write(UC_X86_REG_ESP, top)
        self.uc.reg_write(UC_X86_REG_ECX, FONT)
        self.uc.reg_write(UC_X86_REG_EFLAGS, 0x202)
        self.uc.hook_add(UC_HOOK_CODE, self.instruction)
        self.uc.hook_add(UC_HOOK_MEM_READ, self.memory)
        self.uc.hook_add(UC_HOOK_MEM_INVALID, self.invalid)

    def read(self, address):
        return struct.unpack('<I', bytes(self.uc.mem_read(address, 4)))[0]

    def instruction(self, uc, address, size, data):
        try:
            if address == 0x4119a0:
                assert uc.reg_read(UC_X86_REG_ESI) == FONT
                sp = uc.reg_read(UC_X86_REG_ESP)
                return_address = self.read(sp)
                for register, value in ((UC_X86_REG_EAX, 0xa5a5a5a5),
                                        (UC_X86_REG_ECX, 0xcccccccc),
                                        (UC_X86_REG_EDX, 0xdddddddd)):
                    uc.reg_write(register, value)
                uc.reg_write(UC_X86_REG_ESP, sp + 4)
                uc.reg_write(UC_X86_REG_EIP, return_address)
                self.decoding = True
            elif address == 0x411b80:
                assert self.decoding and uc.reg_read(UC_X86_REG_EAX) == FONT
                sp = uc.reg_read(UC_X86_REG_ESP)
                assert self.read(sp + 8) == self.read(sp + 12) == 0
                self.character = self.read(sp + 4)
                self.status = 'glyph-entry'
                uc.emu_stop()
            elif address == 0x411ad0:
                assert self.decoding and uc.reg_read(UC_X86_REG_ESI) == FONT
                self.status = 'finish-entry'
                uc.emu_stop()
            else:
                assert ENTRY <= address < ENTRY + len(self.body), hex(address)
        except BaseException as error:
            self.error = error
            uc.emu_stop()

    def memory(self, uc, access, address, size, value, data):
        if self.decoding and PAGE <= address < PAGE + 0x1000:
            self.reads.append(dict(offset=address - self.cursor, size=size,
                                   pc=hex(uc.reg_read(UC_X86_REG_EIP))))

    def invalid(self, uc, access, address, size, value, data):
        try:
            assert self.decoding and access == UC_MEM_READ_UNMAPPED
            assert PAGE + 0x1000 <= address < PAGE + 0x2000
            self.fault = dict(address=hex(address), size=size,
                              pc=hex(uc.reg_read(UC_X86_REG_EIP)))
            self.status = 'read-fault'
        except BaseException as error:
            self.error = error
        return False

    def run(self):
        try:
            self.uc.emu_start(ENTRY, 0x700100, count=10000)
        except UcError:
            if self.error:
                raise self.error
            assert self.fault is not None
        if self.error:
            raise self.error
        assert self.status is not None
        return dict(status=self.status, character=self.character,
                    reads=self.reads, fault=self.fault)


def audit(path):
    comparator = linked_pe.comparator()
    target_sha = comparator.verify_target()
    bodies = {'target': comparator.target_bytes(ENTRY, TARGET_SIZE),
              'source': source_body(path, comparator)}
    inputs = [bytes((lead, trail, 0)) for lead in (0x81, 0x9f, 0xe0, 0xfe)
              for trail in (1, 0x40, 0xfe)]
    inputs += [bytes((lead, 0x40, 0)) for lead in (0x41, 0x80, 0xa0, 0xdf, 0xff)]
    inputs += [b'\x81\0', b'\0']
    cases, value_mismatches, read_mismatches = [], 0, 0
    for payload in inputs:
        for placement in ('aligned', 'unaligned', 'guard'):
            case = dict(payload=payload.hex(), placement=placement, results={})
            for mode, body in bodies.items():
                machine = PrefixMachine(body, payload, placement)
                case['results'][mode] = machine.run()
                del machine
                gc.collect()
            expected, actual = (case['results'][mode] for mode in ('target', 'source'))
            # Pin the guarded fixture to the observed target, so an observer
            # accidentally skipping decoding cannot make both sides pass.
            dbcs = payload[0] in (0x81, 0x9f, 0xe0, 0xfe)
            status = ('read-fault' if dbcs and placement == 'guard' else
                      'finish-entry' if payload in (b'\0', b'\x81\0') else
                      'glyph-entry')
            assert expected['status'] == status, case
            value_mismatches += (actual['status'], actual['character']) != (
                expected['status'], expected['character'])
            reads = lambda result: [(event['offset'], event['size'])
                                    for event in result['reads']]
            read_mismatches += reads(actual) != reads(expected)
            cases.append(case)
    return dict(target_sha256=target_sha, address=f'0x{ENTRY:08X}',
                source_object=str(path), source_object_sha256=linked_pe.sha(path),
                body_hashes={mode: hashlib.sha256(body).hexdigest()
                             for mode, body in bodies.items()},
                case_count=len(cases), execution_count=2 * len(cases),
                target_fault_cases=sum(case['results']['target']['status'] == 'read-fault'
                                       for case in cases),
                source_fault_cases=sum(case['results']['source']['status'] == 'read-fault'
                                       for case in cases),
                value_mismatches=value_mismatches, read_mismatches=read_mismatches,
                result='all-pass' if not (value_mismatches or read_mismatches) else 'mismatch',
                scope='Actual first-character render prefixes with one guarded input page; '
                      'flat font and null output pointers; begin is an ABI observer; '
                      'stop at glyph/end entry or read fault. No glyph/GDI/allocation/EH '
                      'or whole-render equivalence or canonical exactness claim.',
                cases=cases)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('object', type=Path)
    parser.add_argument('--output', type=Path)
    args = parser.parse_args()
    result = audit(args.object)
    if args.output:
        args.output.parent.mkdir(parents=True, exist_ok=True)
        args.output.write_text(json.dumps(result, indent=2) + '\n')
    print(json.dumps({key: result[key] for key in (
        'result', 'case_count', 'value_mismatches', 'read_mismatches')}))
    return int(result['result'] != 'all-pass')


if __name__ == '__main__':
    raise SystemExit(main())
