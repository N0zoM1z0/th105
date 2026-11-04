#!/usr/bin/env python3
"""Bounded native/source event-timer traces to the presentation tail."""
import hashlib
import importlib.util
import itertools
import json
import struct
import subprocess
import sys

import unicorn as uc
from unicorn import x86_const as reg
from workflow_manifest import ROOT, load_manifest

UNIT, ADDRESS = 'exact-first-battle-event-timer', 0x472a70
NATIVE_SHA = '744492ad5c29309680cba21f4271bdd559ae224fff1495cdb581576f5a3c6878'
SOURCE_SHA = 'a69ff764791c2b1381defff4fe0f267f87ff07e2dbf9b6cac4648edff3fc2bbb'
OWNER, STACK, STOP = 0x1000000, 0x200f000, 0x710000
MODE, EFFECT, TIMER, PAIR = 0x6fa880, 0x6fa884, 0x6fa88c, 0x6fbc98
RNG_RESULT = 7


def code_bodies():
    subprocess.run([sys.executable, str(ROOT / 'scripts/build.py'), '--unit', UNIT, '--json'],
                   cwd=ROOT, check=True, stdout=subprocess.DEVNULL)
    spec = importlib.util.spec_from_file_location('battle_timer_compare', ROOT / 'scripts/compare-function.py')
    compare = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(compare)
    compare.verify_target()
    unit = load_manifest()['units'][UNIT]
    function = unit['functions'][0]
    targets = compare.known_targets()
    for mapping in function['rel32_targets']:
        symbol, address = mapping.rsplit('=', 1)
        targets[symbol] = int(address, 0)
    data = dict(mapping.split('=', 1) for mapping in function['dir32_targets'])
    source = compare.coff_symbol_bytes(ROOT / unit['object'], function['symbol_base'], ADDRESS,
        0xffffffff, targets, compare.known_data_targets(), data)
    native = compare.target_bytes(ADDRESS, 172)
    if (len(native) != 172 or hashlib.sha256(native).hexdigest() != NATIVE_SHA or
        len(source) != 186 or hashlib.sha256(source).hexdigest() != SOURCE_SHA):
        raise ValueError('battle event timer body changed; review fixture')
    return native, source


def execute(code, case):
    phase, mode, effect, timer, pair = case
    engine = uc.Uc(uc.UC_ARCH_X86, uc.UC_MODE_32)
    engine.mem_map(0x400000, 0x400000)
    engine.mem_map(OWNER, 0x10000)
    engine.mem_map(0x2000000, 0x10000)
    engine.mem_write(ADDRESS, code)
    def put(address, value):
        engine.mem_write(address, struct.pack('<I', value & 0xffffffff))
    def get(address):
        return struct.unpack('<I', engine.mem_read(address, 4))[0]
    put(OWNER + 0x88, phase); put(MODE, mode); put(EFFECT, effect); put(PAIR, pair)
    engine.mem_write(TIMER, struct.pack('<h', timer)); put(STACK, STOP)
    engine.reg_write(reg.UC_X86_REG_ESP, STACK); engine.reg_write(reg.UC_X86_REG_ECX, OWNER)
    events, stopped = [], []
    def step(engine, address, size, _):
        if address == 0x46b160:
            events.append(('presentation', engine.reg_read(reg.UC_X86_REG_ECX)))
            stopped.append(True); engine.emu_stop(); return
        if address not in (0x435ce0, 0x434e40, 0x4067d0):
            return
        esp = engine.reg_read(reg.UC_X86_REG_ESP); receiver = engine.reg_read(reg.UC_X86_REG_ECX)
        if address == 0x435ce0:
            events.append(('mode', receiver, get(esp + 4), get(esp + 8))); cleanup = 8
        elif address == 0x434e40:
            events.append(('effect', receiver, get(esp + 4))); cleanup = 4
        else:
            events.append(('random', get(esp + 4))); cleanup = 0
            engine.reg_write(reg.UC_X86_REG_EAX, RNG_RESULT)
        engine.reg_write(reg.UC_X86_REG_EIP, get(esp))
        engine.reg_write(reg.UC_X86_REG_ESP, esp + 4 + cleanup)
    engine.hook_add(uc.UC_HOOK_CODE, step)
    engine.emu_start(ADDRESS, STOP + 1, count=1000)
    if not stopped:
        raise ValueError('presentation tail not reached')
    result = struct.unpack('<h', engine.mem_read(TIMER, 2))[0]
    return result, events


def expected(case):
    phase, mode, effect, timer, pair = case
    events = []
    if phase == 2:
        if mode != 16:
            timer = ((timer - (pair & 1) + 32768) % 65536) - 32768
            if timer <= 0:
                timer = 0; events.append(('mode', OWNER + 4, 16, 1))
        else:
            timer = ((timer + 1 + 32768) % 65536) - 32768
            if effect == 16 and timer >= 499:
                events += [('random', 15), ('effect', OWNER + 4, RNG_RESULT)]
            elif timer >= 999:
                timer = 999; events.append(('mode', OWNER + 4, effect, 1))
    return timer, events + [('presentation', OWNER)]


def audit():
    bodies = code_bodies()
    cases = list(itertools.product((1, 2), (0, 16), (3, 16),
                                   (-32768, -1, 0, 1, 498, 499, 998, 999, 32767), (0, 1)))
    for case in cases:
        for code in bodies:
            if execute(code, case) != expected(case):
                raise ValueError('battle timer trace differs for ' + repr(case))
    return {'cases': len(cases), 'result': 'bounded_traces_agree',
            'limitations': 'event/mode/random helpers mocked; stops before actual presentation tail; no full-game or EAX-return claim'}

if __name__ == '__main__':
    print(json.dumps(audit(), indent=2))
