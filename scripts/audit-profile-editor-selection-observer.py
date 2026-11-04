#!/usr/bin/env python3
"""Bounded profile selection update with mocked controller and texture providers."""
import hashlib
import importlib.util
import json
import struct
import subprocess
import sys

import unicorn as uc
from unicorn import x86_const as reg
from workflow_manifest import ROOT, load_manifest

UNIT, ADDRESS = 'exact-first-profile-editor-selection', 0x427c60
OWNER, STACK, STOP = 0x1000000, 0x200f000, 0x710000
TEXTS = (0x1002000, 0x1002100)
CASES = ((0,0,1,1,3,4,15), (1,1,0,0,3,4,15), (1,1,0,0,0,4,16),
         (1,1,0,0,3,0,16), (1,0,0,0,3,4,16), (1,0,1,0,0,4,15),
         (1,0,0,1,3,0,-15), (1,0,1,1,3,4,16))


def code_bodies():
    subprocess.run([sys.executable, str(ROOT / 'scripts/build.py'), '--unit', UNIT, '--json'],
                   cwd=ROOT, check=True, stdout=subprocess.DEVNULL)
    spec = importlib.util.spec_from_file_location('selection_compare', ROOT / 'scripts/compare-function.py')
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
    native = compare.target_bytes(ADDRESS, 333)
    if (len(candidate) != 330 or hashlib.sha256(candidate).hexdigest() !=
            '943e3243acc518d1f3e1e0df5e8b1707a41328804c8067c70f126f482c7b1b85'
            or hashlib.sha256(native).hexdigest() !=
            '41df1dc4641c5c2094e1141e91a7d2f9de01e593b875d3fefa714d6f9eb6939b'):
        raise ValueError('selection body changed; review fixture')
    return native, candidate


def execute(code, mode, reset, primary, secondary, old_primary, old_secondary, width):
    engine = uc.Uc(uc.UC_ARCH_X86, uc.UC_MODE_32)
    engine.mem_map(0x400000, 0x400000)
    engine.mem_map(OWNER, 0x10000)
    engine.mem_map(0x2000000, 0x10000)
    engine.mem_write(ADDRESS, code)
    def put(address, value):
        engine.mem_write(address, struct.pack('<I', value & 0xffffffff))
    def get(address):
        return struct.unpack('<I', engine.mem_read(address, 4))[0]
    put(OWNER, old_primary); put(OWNER + 4, old_secondary)
    put(OWNER + 8, 0x1003000); put(OWNER + 0x154, width)
    put(OWNER + 0x158, 11); put(OWNER + 0x15c, 22); put(OWNER + 0x160, 9)
    engine.mem_write(0x70358f, bytes((mode,)))
    put(STACK, STOP)
    engine.reg_write(reg.UC_X86_REG_ESP, STACK)
    engine.reg_write(reg.UC_X86_REG_ECX, OWNER)
    events, stopped = [], []
    def step(engine, address, size, _):
        if address == STOP:
            stopped.append(True); engine.emu_stop(); return
        if address not in (0x40edc0, 0x40e7f0, 0x40eb60, 0x40eb70, 0x404d70, 0x404d00, 0x4098b0):
            return
        sp = engine.reg_read(reg.UC_X86_REG_ESP)
        ret, receiver = get(sp), engine.reg_read(reg.UC_X86_REG_ECX)
        args = lambda n: tuple(get(sp + 4 + 4 * i) for i in range(n))
        pop = 0
        if address == 0x40edc0:
            events.append(('reset?',)); engine.reg_write(reg.UC_X86_REG_EAX, reset)
        elif address == 0x40e7f0:
            events.append(('mode', *args(1))); pop = 4
        elif address in (0x40eb60, 0x40eb70):
            index = int(address == 0x40eb70)
            present = (primary, secondary)[index]
            events.append(('text', index, bool(present)))
            engine.reg_write(reg.UC_X86_REG_EAX, TEXTS[index] if present else 0)
        elif address == 0x404d70:
            events.append(('release', *args(1))); pop = 4
        elif address == 0x404d00:
            output, text, font, w, h, outw, outh = args(7)
            handle = 100 if text == TEXTS[0] else 200
            events.append(('create', text, font, w, h, outw, outh))
            put(output, handle); engine.reg_write(reg.UC_X86_REG_EAX, output); pop = 28
        else:
            events.append(('tile', receiver - OWNER, *args(5))); pop = 20
        engine.reg_write(reg.UC_X86_REG_ESP, sp + 4 + pop)
        engine.reg_write(reg.UC_X86_REG_EIP, ret)
    engine.hook_add(uc.UC_HOOK_CODE, step)
    engine.emu_start(ADDRESS, STOP + 1, count=2000)
    if not stopped:
        raise ValueError('selection update did not return')
    return (events, get(OWNER), get(OWNER + 4), get(OWNER + 0x160),
            engine.reg_read(reg.UC_X86_REG_EAX) & 255, engine.reg_read(reg.UC_X86_REG_ESP) - STACK)


def expected(mode, reset, primary, secondary, old_primary, old_secondary, width):
    events = []
    if not mode:
        return events, old_primary, old_secondary, 9, 255, 4
    events.append(('reset?',))
    if reset:
        if old_secondary: events.append(('release', old_secondary))
        if old_primary: events.append(('release', old_primary))
        events.append(('mode', 0))
        return events, 0, 0, 0, 1, 4
    handles = [old_primary, old_secondary]
    for index, present in enumerate((primary, secondary)):
        events.append(('text', index, bool(present)))
        if present:
            events.append(('release', handles[index]))
            events.append(('create', TEXTS[index], 0x1003000, 512, 32, 0, 0))
            handles[index] = (100, 200)[index]
            half = abs(width) // 2 * (-1 if width < 0 else 1)
            events.append(('tile', (0xc, 0xb0)[index], handles[index], 11, 22,
                           half & 0xffffffff, width & 0xffffffff))
    return events, handles[0], handles[1], 10, 0, 4


def audit():
    native, candidate = code_bodies()
    for case in CASES:
        if execute(native, *case) != expected(*case) or execute(candidate, *case) != expected(*case):
            raise ValueError('selection trace differs for ' + repr(case))
    return {'cases': len(CASES), 'result': 'bounded_traces_agree',
            'limitations': 'controller, texture and tile calls mocked; no real text rendering or game execution'}

if __name__ == '__main__':
    print(json.dumps(audit(), indent=2))
