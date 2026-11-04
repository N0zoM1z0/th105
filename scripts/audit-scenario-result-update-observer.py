#!/usr/bin/env python3
"""Compare bounded result-phase traces with mocked wave and result methods."""
import hashlib
import importlib.util
import json
import struct
import subprocess
import sys

import unicorn as uc
from unicorn import x86_const as reg
from workflow_manifest import ROOT, load_manifest

UNIT, ADDRESS = 'gpt-web-scenario-result-update', 0x454a50
NATIVE_SHA = 'f4e0aad65c899f67572a833c036a139fafafedd36dd8e360a6ea0809e0d6a871'
CANDIDATE_SHA = '1dfd4213426885ee44f1db6b2f00d489ac8fd3c74809966621f2025a0a74dd32'
OWNER, STACK, STOP, WAVE_VALUE = 0x1000000, 0x200f000, 0x710000, 0x1003000
CASES = ((0,0,0), (1,0,0), (1,0,30), (1,0,31), (1,1,0), (1,1,15),
         (1,1,45), (1,1,75), (1,2,99), (1,3,0), (1,3,10), (1,3,45),
         (1,3,60), (1,3,61))


def code_bodies():
    subprocess.run([sys.executable, str(ROOT / 'scripts/build.py'), '--unit', UNIT, '--json'],
                   cwd=ROOT, check=True, stdout=subprocess.DEVNULL)
    spec = importlib.util.spec_from_file_location('result_compare', ROOT / 'scripts/compare-function.py')
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
    native = compare.target_bytes(ADDRESS, 403)
    if (len(candidate) != 403 or hashlib.sha256(candidate).hexdigest() != CANDIDATE_SHA
            or hashlib.sha256(native).hexdigest() != NATIVE_SHA):
        raise ValueError('result update body or target changed; review the fixture')
    return native, candidate


def execute(code, state, phase, counter, wave):
    engine = uc.Uc(uc.UC_ARCH_X86, uc.UC_MODE_32)
    engine.mem_map(0x400000, 0x400000)
    engine.mem_map(OWNER, 0x10000)
    engine.mem_map(0x2000000, 0x10000)
    engine.mem_write(ADDRESS, code)
    engine.mem_write(0x6c2718, struct.pack('<d', -640.0))
    engine.mem_write(0x6c0ea0, struct.pack('<d', 640.0))
    engine.mem_write(WAVE_VALUE, struct.pack('<f', wave))
    # Mock each cdecl wave provider with FLD [fixture]; RET. The real lookup is
    # separately exact, but its table and full floating environment are not run.
    wave_stub = b'\xd9\x05' + struct.pack('<I', WAVE_VALUE) + b'\xc3'
    engine.mem_write(0x406480, wave_stub)
    engine.mem_write(0x4064b0, wave_stub)
    def put(address, value):
        engine.mem_write(address, struct.pack('<I', value & 0xffffffff))
    def get(address):
        return struct.unpack('<I', engine.mem_read(address, 4))[0]
    engine.mem_write(OWNER, bytes((state, phase)) + b'\0\0')
    put(OWNER + 4, counter)
    put(STACK, STOP)
    for index in range(4):
        obj = 0x1001000 + index * 0x100
        put(OWNER + 0x3c + 4 * index, obj)
        put(obj + 4, 0x42c80000)
        put(obj + 8, 0x42480000)
    engine.reg_write(reg.UC_X86_REG_ESP, STACK)
    engine.reg_write(reg.UC_X86_REG_ECX, OWNER)
    events, stopped = [], []
    def step(engine, address, size, _):
        if address == STOP:
            stopped.append(True)
            engine.emu_stop()
        elif address in (0x406480, 0x4064b0):
            esp = engine.reg_read(reg.UC_X86_REG_ESP)
            events.append(('wave', address, get(esp + 4)))
        elif address in (0x4549e0, 0x454950):
            esp = engine.reg_read(reg.UC_X86_REG_ESP)
            ret = get(esp)
            if address == 0x454950:
                events.append(('level', get(esp + 4), get(esp + 8)))
                argument_bytes = 8
            else:
                # Controlled reset outcome shared by both executions.
                events.append(('reset',))
                engine.mem_write(OWNER + 1, b'\0')
                put(OWNER + 4, 0)
                argument_bytes = 0
            engine.reg_write(reg.UC_X86_REG_ESP, esp + 4 + argument_bytes)
            engine.reg_write(reg.UC_X86_REG_EIP, ret)
    engine.hook_add(uc.UC_HOOK_CODE, step)
    engine.emu_start(ADDRESS, STOP + 1, count=3000)
    if not stopped:
        raise ValueError('result update did not return')
    positions = tuple(bytes(engine.mem_read(0x1001000 + i * 0x100 + 4, 8)) for i in range(4))
    return (events, bytes(engine.mem_read(OWNER, 8)), bytes(engine.mem_read(OWNER + 0x124, 1)),
            positions, engine.reg_read(reg.UC_X86_REG_EAX) & 255,
            engine.reg_read(reg.UC_X86_REG_ESP) - STACK)


def audit():
    native, candidate = code_bodies()
    count = 0
    for case in CASES:
        for wave in (0.0, 0.5):
            expected = execute(native, *case, wave)
            observed = execute(candidate, *case, wave)
            if expected != observed or observed[-1] != 4:
                raise ValueError(f'native/source trace differs for {case}, wave={wave}')
            count += 1
    return {'cases': count, 'result': 'bounded_traces_agree',
            'limitations': 'mock wave/reset/level functions; finite fixtures, no full-game, real table or EH execution'}

if __name__ == '__main__':
    print(json.dumps(audit(), indent=2))
