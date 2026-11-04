#!/usr/bin/env python3
"""Bounded DirectInput error dialog argument forwarding."""
import hashlib
import importlib.util
import json
import struct
import subprocess
import sys

import unicorn as uc
from unicorn import x86_const as reg
from workflow_manifest import ROOT, load_manifest

UNIT, ADDRESS = 'gpt-web-directinput-error-report', 0x40d540
STACK, STOP, MESSAGE_BOX = 0x200f000, 0x710000, 0x710100
CASES = ((0x1234, 0x1000000, 1), (0, 0x1000100, 2), (0x87654321, 0x1000200, 0))


def code_bodies():
    subprocess.run([sys.executable, str(ROOT / 'scripts/build.py'), '--unit', UNIT, '--json'],
                   cwd=ROOT, check=True, stdout=subprocess.DEVNULL)
    spec = importlib.util.spec_from_file_location('dinput_compare', ROOT / 'scripts/compare-function.py')
    compare = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(compare)
    compare.verify_target()
    unit = load_manifest()['units'][UNIT]
    function = unit['functions'][0]
    data_targets = dict(mapping.split('=', 1) for mapping in function.get('dir32_targets', []))
    candidate = compare.coff_symbol_bytes(ROOT / unit['object'], function['symbol_base'],
        ADDRESS, 0xffffffff, compare.known_targets(), compare.known_data_targets(), data_targets)
    native = compare.target_bytes(ADDRESS, 22)
    if (len(candidate) != 26 or hashlib.sha256(candidate[:22]).hexdigest() !=
            '1716053b3de014d5c73b03fc6d9e2be8118d226ab17ab6a03b70257ad6b0a6a5'
            or hashlib.sha256(native).hexdigest() !=
            '25778b72befce238d77f475d00ff88b237cd2e8c3f1f17b592512599636d11bd'):
        raise ValueError('error-report body changed; review fixture')
    return native, candidate


def execute(code, private_abi, window, message, result):
    engine = uc.Uc(uc.UC_ARCH_X86, uc.UC_MODE_32)
    engine.mem_map(0x400000, 0x400000)
    engine.mem_map(0x2000000, 0x10000)
    engine.mem_write(ADDRESS, code)
    def put(address, value):
        engine.mem_write(address, struct.pack('<I', value & 0xffffffff))
    def get(address):
        return struct.unpack('<I', engine.mem_read(address, 4))[0]
    put(0x702a28, window); put(0x6c0214, MESSAGE_BOX)
    put(STACK, STOP); put(STACK + 4, message)
    engine.reg_write(reg.UC_X86_REG_ESP, STACK)
    engine.reg_write(reg.UC_X86_REG_EAX, message if private_abi else 0)
    events, stopped = [], []
    def step(engine, address, size, _):
        if address == STOP:
            stopped.append(True); engine.emu_stop(); return
        if address != MESSAGE_BOX:
            return
        sp = engine.reg_read(reg.UC_X86_REG_ESP)
        ret = get(sp)
        events.append(tuple(get(sp + 4 + 4 * i) for i in range(4)))
        engine.reg_write(reg.UC_X86_REG_EAX, result)
        engine.reg_write(reg.UC_X86_REG_ESP, sp + 20)
        engine.reg_write(reg.UC_X86_REG_EIP, ret)
    engine.hook_add(uc.UC_HOOK_CODE, step)
    engine.emu_start(ADDRESS, STOP + 1, count=100)
    if not stopped:
        raise ValueError('error report did not return')
    return events, engine.reg_read(reg.UC_X86_REG_EAX), engine.reg_read(reg.UC_X86_REG_ESP) - STACK


def audit():
    native, candidate = code_bodies()
    for window, message, result in CASES:
        expected = ([(window, message, 0x6d6b34, 0)], result, 4)
        if execute(native, True, window, message, result) != expected:
            raise ValueError('native forwarding differs')
        if execute(candidate, False, window, message, result) != expected:
            raise ValueError('source forwarding differs')
    return {'cases': len(CASES), 'result': 'bounded_traces_agree',
            'limitations': 'MessageBoxA mocked; native receives message in EAX and ordinary source on stack; no actual GUI interaction'}

if __name__ == '__main__':
    print(json.dumps(audit(), indent=2))
