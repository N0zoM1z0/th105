#!/usr/bin/env python3
"""Bounded native and ordinary-source package index node construction."""
import hashlib
import importlib.util
import json
import struct
import subprocess
import sys

import unicorn as uc
from unicorn import x86_const as reg
from workflow_manifest import ROOT, load_manifest

UNIT, ADDRESS = 'gpt-web-package-index-node-constructor', 0x41b7f0
OWNER, PATH, ALLOC, STACK, STOP = 0x1000000, 0x1002000, 0x1004000, 0x200f000, 0x710000
CASES = ((b'', 0, 0, 0), (b'a', 1, 2, 3),
         (b'data/scene/test.pat', 7, 0xffffffff, 0x87654321),
         (b'\x80\xff.dat', 0xffffffff, 0x12345678, 32),
         (b'x' * 200, 11, 200, 4096))


def code_bodies():
    subprocess.run([sys.executable, str(ROOT / 'scripts/build.py'), '--unit', UNIT, '--json'],
                   cwd=ROOT, check=True, stdout=subprocess.DEVNULL)
    spec = importlib.util.spec_from_file_location('package_node_compare', ROOT / 'scripts/compare-function.py')
    compare = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(compare)
    compare.verify_target()
    unit = load_manifest()['units'][UNIT]
    function = unit['functions'][0]
    targets = compare.known_targets()
    for mapping in function['rel32_targets']:
        symbol, address = mapping.rsplit('=', 1)
        targets[symbol] = int(address, 0)
    candidate = compare.coff_symbol_bytes(ROOT / unit['object'], function['symbol_base'],
        ADDRESS, 0xffffffff, targets, compare.known_data_targets(), {})
    native = compare.target_bytes(ADDRESS, 84)
    if (len(candidate) != 85 or hashlib.sha256(candidate[:84]).hexdigest() !=
            '74bd12c20741b5dbee259129c25f968d1d0fd99eaf633b68ed0c55b1fb8a5e6e'
            or hashlib.sha256(native).hexdigest() !=
            '94fe2301dec70d8fd04576336b868a5c1c6a6ca39a7720dc36c272e353dfb701'):
        raise ValueError('constructor body changed; review fixture')
    return native, candidate


def execute(code, private_abi, path, index, size, offset):
    engine = uc.Uc(uc.UC_ARCH_X86, uc.UC_MODE_32)
    engine.mem_map(0x400000, 0x400000)
    engine.mem_map(OWNER, 0x10000)
    engine.mem_map(0x2000000, 0x10000)
    engine.mem_write(ADDRESS, code)
    engine.mem_write(PATH, path + b'\0')
    def put(address, value):
        engine.mem_write(address, struct.pack('<I', value & 0xffffffff))
    def get(address):
        return struct.unpack('<I', engine.mem_read(address, 4))[0]
    for i, value in enumerate((STOP, PATH, index, size, offset)):
        put(STACK + 4 * i, value)
    engine.reg_write(reg.UC_X86_REG_ESP, STACK)
    engine.reg_write(reg.UC_X86_REG_ECX, OWNER)
    engine.reg_write(reg.UC_X86_REG_ESI, OWNER if private_abi else 0x13579bdf)
    engine.reg_write(reg.UC_X86_REG_EBX, 0x12345678)
    engine.reg_write(reg.UC_X86_REG_EDI, 0x87654321)
    events, stopped = [], []
    def step(engine, address, size, _):
        if address == STOP:
            stopped.append(True)
            engine.emu_stop()
            return
        if address not in (0x665b8a, 0x68ad95):
            return
        sp = engine.reg_read(reg.UC_X86_REG_ESP)
        ret = get(sp)
        if address == 0x665b8a:
            length = get(sp + 4)
            events.append(('new_array', length))
            engine.reg_write(reg.UC_X86_REG_EAX, ALLOC)
        else:
            destination, length, source = (get(sp + i) for i in (4, 8, 12))
            events.append(('copy', destination, length, source))
            if source != PATH or destination != ALLOC or length != len(path) + 1:
                raise ValueError('copy bounds or pointer mismatch')
            engine.mem_write(destination, bytes(engine.mem_read(source, length)))
            engine.reg_write(reg.UC_X86_REG_EAX, 0)
        engine.reg_write(reg.UC_X86_REG_ESP, sp + 4)
        engine.reg_write(reg.UC_X86_REG_EIP, ret)
    engine.hook_add(uc.UC_HOOK_CODE, step)
    engine.emu_start(ADDRESS, STOP + 1, count=10000)
    if not stopped:
        raise ValueError('constructor did not return')
    return (events, tuple(get(OWNER + 4 * i) for i in range(5)),
            bytes(engine.mem_read(ALLOC, len(path) + 1)),
            engine.reg_read(reg.UC_X86_REG_EAX), engine.reg_read(reg.UC_X86_REG_ESP) - STACK,
            engine.reg_read(reg.UC_X86_REG_EBX), engine.reg_read(reg.UC_X86_REG_EDI))


def expected(path, index, size, offset):
    return ([('new_array', len(path) + 1), ('copy', ALLOC, len(path) + 1, PATH)],
            (ALLOC, index, size, offset, 0), path + b'\0', OWNER, 20, 0x12345678, 0x87654321)


def audit():
    native, candidate = code_bodies()
    for case in CASES:
        if execute(native, True, *case) != expected(*case) or execute(candidate, False, *case) != expected(*case):
            raise ValueError('constructor trace differs for ' + repr(case))
    return {'cases': len(CASES), 'result': 'bounded_traces_agree',
            'limitations': 'valid NUL-terminated byte strings; allocation and strcpy_s mocked; no failure or full-game execution'}

if __name__ == '__main__':
    print(json.dumps(audit(), indent=2))
