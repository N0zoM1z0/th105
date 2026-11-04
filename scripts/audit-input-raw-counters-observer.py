#!/usr/bin/env python3
"""Bounded keyboard/gamepad hold-counter comparison with a mock state getter."""
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

UNIT, ADDRESS = 'gpt-web-input-raw-counters', 0x409da0
NATIVE_SHA = 'c24daf653f2aa593bc00ab6b851f9df8fc38d38cd9744ebd2056012ad5a86914'
CANDIDATE_SHA = '01b9dbc90c2c4f22ed83d80632135b7412f9b287dae981a2410a4e94a75f5bea'
OWNER, PAD, STACK, STOP, BACKEND = 0x1000000, 0x1004000, 0x200f000, 0x710000, 0x702a28
INITIAL = (2, -2, 3, -4, 5, -6, 7, -8, 9, -10)


def cases():
    yield (-2, 0, 0, (), True, False)
    yield (0, 0, 0, (), False, False)
    for x, y in itertools.product((-501, -500, 0, 500, 501), repeat=2):
        yield (0, x, y, (0, 2, 4, 6), True, False)
    for keys in ((), (10,12), (11,13), (10,11,12,13), (20,22,24,26), (12,20)):
        yield (-1, 0, 0, keys, True, False)
    yield (0, 501, -501, (0,1,2,3), True, True)
    yield (-1, 0, 0, (12,13,20,21), True, True)


def code_bodies():
    subprocess.run([sys.executable, str(ROOT / 'scripts/build.py'), '--unit', UNIT, '--json'],
                   cwd=ROOT, check=True, stdout=subprocess.DEVNULL)
    spec = importlib.util.spec_from_file_location('input_compare', ROOT / 'scripts/compare-function.py')
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
    native = compare.target_bytes(ADDRESS, 407)
    if (len(candidate) != 406 or hashlib.sha256(candidate).hexdigest() != CANDIDATE_SHA
            or hashlib.sha256(native).hexdigest() != NATIVE_SHA):
        raise ValueError('input update body or target changed; review the fixture')
    return native, candidate


def execute(code, source, x, y, pressed, present, disabled):
    engine = uc.Uc(uc.UC_ARCH_X86, uc.UC_MODE_32)
    engine.mem_map(0x400000, 0x400000)
    engine.mem_map(OWNER, 0x10000)
    engine.mem_map(0x2000000, 0x10000)
    engine.mem_write(ADDRESS, code)
    def put(address, value):
        engine.mem_write(address, struct.pack('<I', value & 0xffffffff))
    def get(address):
        return struct.unpack('<I', engine.mem_read(address, 4))[0]
    engine.mem_write(OWNER + 4, bytes((source & 255,)))
    bindings = [10, 11, 12, 13] + list(range(8) if source >= 0 else range(20, 28))
    if disabled:
        bindings[2] = -1
        bindings[5] = -1
    for index, value in enumerate(bindings):
        put(OWNER + 8 + 4 * index, value)
    for index, value in enumerate(INITIAL):
        put(OWNER + 0x38 + 4 * index, value)
    put(PAD, x)
    put(PAD + 4, y)
    for key in pressed:
        if source == -1:
            engine.mem_write(BACKEND + 0x20 + key, b'\x80')
        elif source >= 0:
            engine.mem_write(PAD + 0x30 + key, b'\x80')
    put(STACK, STOP)
    engine.reg_write(reg.UC_X86_REG_ESP, STACK)
    engine.reg_write(reg.UC_X86_REG_ECX, OWNER)
    calls, stopped = [], []
    def step(engine, address, size, _):
        if address == STOP:
            stopped.append(True)
            engine.emu_stop()
        elif address == 0x40d990:
            esp = engine.reg_read(reg.UC_X86_REG_ESP)
            calls.append((engine.reg_read(reg.UC_X86_REG_ECX), get(esp + 4)))
            engine.reg_write(reg.UC_X86_REG_EAX, PAD if present else 0)
            engine.reg_write(reg.UC_X86_REG_EIP, get(esp))
            engine.reg_write(reg.UC_X86_REG_ESP, esp + 8)
    engine.hook_add(uc.UC_HOOK_CODE, step)
    engine.emu_start(ADDRESS, STOP + 1, count=5000)
    if not stopped:
        raise ValueError('input update did not return')
    counters = struct.unpack('<10i', engine.mem_read(OWNER + 0x38, 40))
    return calls, counters, engine.reg_read(reg.UC_X86_REG_ESP) - STACK


def expected(case):
    source, x, y, pressed, present, disabled = case
    counters = list(INITIAL)
    calls = [(BACKEND, source)] if source >= 0 else []
    if source < -1:
        return calls, (0,) * 10, 4
    if source >= 0 and not present:
        return calls, tuple(counters), 4
    def update_axis(old, direction):
        if direction < 0:
            return min(old, 0) - 1
        if direction > 0:
            return max(old, 0) + 1
        return 0
    if source >= 0:
        counters[0] = update_axis(counters[0], -1 if x < -500 else (1 if x > 500 else 0))
        counters[1] = update_axis(counters[1], -1 if y < -500 else (1 if y > 500 else 0))
    else:
        if not disabled:
            counters[0] = update_axis(counters[0], -1 if 12 in pressed else (1 if 13 in pressed else 0))
        counters[1] = update_axis(counters[1], -1 if 10 in pressed else (1 if 11 in pressed else 0))
    for index in range(8):
        if disabled and index == 1:
            continue
        key = index if source >= 0 else 20 + index
        counters[2 + index] = counters[2 + index] + 1 if key in pressed else 0
    return calls, tuple(counters), 4


def audit():
    native, candidate = code_bodies()
    fixtures = list(cases())
    for case in fixtures:
        observed_native = execute(native, *case)
        observed_source = execute(candidate, *case)
        if observed_native != observed_source or observed_source != expected(case):
            raise ValueError(f'native/source input counters differ for {case!r}')
    return {'cases': len(fixtures), 'result': 'bounded_traces_agree',
            'limitations': 'mock gamepad accessor; finite valid bindings only, no DirectInput device, overflow or whole-game execution'}

if __name__ == '__main__':
    print(json.dumps(audit(), indent=2))
