#!/usr/bin/env python3
"""Observe candidate-window initialization with mocked Win32/IME providers."""
import hashlib
import importlib.util
import json
import struct
import subprocess
import sys

import unicorn as uc
from unicorn import x86_const as reg
from workflow_manifest import ROOT, load_manifest

UNIT, ADDRESS = 'gpt-web-profile-ime-window-init', 0x40e780
STACK, STOP, WINDOW, SETRECT = 0x200f000, 0x710000, 0x1000100, 0x710100
CASES = (((0, 0, 640, 480), 0x1234), ((-100, -50, 300, 250), 0x4321),
         ((1, 1, 1, 1), 0), ((200, 300, 100, 80), 0xdeadbeef),
         ((-10000, 42, 10000, 42), 17))


def code_bodies():
    subprocess.run([sys.executable, str(ROOT / 'scripts/build.py'), '--unit', UNIT, '--json'],
                   cwd=ROOT, check=True, stdout=subprocess.DEVNULL)
    spec = importlib.util.spec_from_file_location('ime_compare', ROOT / 'scripts/compare-function.py')
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
    native = compare.target_bytes(ADDRESS, 111)
    if (len(candidate) != 111 or hashlib.sha256(candidate).hexdigest() !=
            'f4e320163f2f4f9ac534337564f8008d1755e992f951e76e9082e6c9a6acc504'
            or hashlib.sha256(native).hexdigest() !=
            '14e87791d01c7bba0ea9206214dbb68afed1bc60f1e00c5faf6cb7692775722a'):
        raise ValueError('IME body changed; review fixture')
    return native, candidate


def execute(code, rect, context):
    engine = uc.Uc(uc.UC_ARCH_X86, uc.UC_MODE_32)
    engine.mem_map(0x400000, 0x400000)
    engine.mem_map(0x1000000, 0x10000)
    engine.mem_map(0x2000000, 0x10000)
    engine.mem_write(ADDRESS, code)
    def put(address, value):
        engine.mem_write(address, struct.pack('<I', value & 0xffffffff))
    def get(address):
        return struct.unpack('<I', engine.mem_read(address, 4))[0]
    put(0x702a1c, WINDOW)
    put(0x702b80, 0xcccccccc)
    put(0x6c01e0, SETRECT)
    put(STACK, STOP)
    engine.reg_write(reg.UC_X86_REG_ESP, STACK)
    events, stopped = [], []
    def step(engine, address, size, _):
        if address == STOP:
            stopped.append(True)
            engine.emu_stop()
            return
        if address not in (0x66b824, SETRECT, 0x66b81e):
            return
        sp = engine.reg_read(reg.UC_X86_REG_ESP)
        ret = get(sp)
        if address == 0x66b824:
            events.append(('context', get(sp + 4)))
            engine.reg_write(reg.UC_X86_REG_EAX, context)
            pop = 4
        elif address == SETRECT:
            window, dest = get(sp + 4), get(sp + 8)
            events.append(('rect', window))
            engine.mem_write(dest, struct.pack('<4I', *(v & 0xffffffff for v in rect)))
            engine.reg_write(reg.UC_X86_REG_EAX, 1)
            pop = 8
        else:
            actual_context, form = get(sp + 4), get(sp + 8)
            events.append(('candidate', actual_context, get(form), get(form + 4),
                           *(get(form + offset) for offset in (16, 20, 24, 28))))
            engine.reg_write(reg.UC_X86_REG_EAX, 1)
            pop = 8
        engine.reg_write(reg.UC_X86_REG_ESP, sp + 4 + pop)
        engine.reg_write(reg.UC_X86_REG_EIP, ret)
    engine.hook_add(uc.UC_HOOK_CODE, step)
    engine.emu_start(ADDRESS, STOP + 1, count=1000)
    if not stopped:
        raise ValueError('IME setup did not return')
    return events, get(0x702b80), engine.reg_read(reg.UC_X86_REG_ESP) - STACK


def expected(rect, context):
    left, top, right, bottom = rect
    return ([('context', WINDOW), ('rect', WINDOW),
             ('candidate', context, 0, 0x80, 0, 0,
              (right - left) & 0xffffffff, (bottom - top) & 0xffffffff)], context, 4)


def audit():
    native, candidate = code_bodies()
    for case in CASES:
        if execute(native, *case) != expected(*case) or execute(candidate, *case) != expected(*case):
            raise ValueError('IME setup differs for ' + repr(case))
    return {'cases': len(CASES), 'result': 'bounded_traces_agree',
            'limitations': 'successful mocked window rectangle and IME providers; no actual OS, failed GetWindowRect or IME behavior'}

if __name__ == '__main__':
    print(json.dumps(audit(), indent=2))
