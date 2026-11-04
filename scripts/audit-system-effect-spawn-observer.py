#!/usr/bin/env python3
"""Compare five bounded spawn traces using stubbed dependencies, not game I/O."""
from pathlib import Path
import hashlib
import importlib.util
import json
import struct
import subprocess
import sys

import unicorn as uc
from unicorn import x86_const as reg
from workflow_manifest import ROOT, load_manifest

UNIT = 'gpt-web-system-effect-manager-spawn'
ADDRESS = 0x458340
NATIVE_SHA = 'fb7c209236cf71b44bfd6bdebd6831442618fd0f2d5310c6c6744faec56182e1'
CANDIDATE_SHA = 'de9097da0f5e072f9fe6588040bdb36e7b285b6ac3842c60498fb48f3625b63e'
OBJECT, VTABLE, PATH, MANAGER, STACK = 0x1000000, 0x1001000, 0x1002000, 0x1003000, 0x2000000
STOP, RESET = 0x710000, 0x710100
CASES = ((-32768, -12.5, 0.0), (-1, 3.25, -9.5), (0, 0.0, 1.0),
         (1, 640.0, 480.0), (32767, -1.0, 1.5))


def code_bodies():
    """Rebuild the selected unit with its pinned profile before replay."""
    subprocess.run([sys.executable, str(ROOT / 'scripts/build.py'), '--unit', UNIT, '--json'],
                   cwd=ROOT, check=True, stdout=subprocess.DEVNULL)
    spec = importlib.util.spec_from_file_location('spawn_compare', ROOT / 'scripts/compare-function.py')
    compare = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(compare)
    compare.verify_target()
    unit = load_manifest()['units'][UNIT]
    function = unit['functions'][0]
    targets = compare.known_targets()
    for mapping in function['rel32_targets']:
        symbol, address = mapping.rsplit('=', 1)
        targets[symbol] = int(address, 0)
    data_targets = dict(mapping.split('=', 1) for mapping in function.get('dir32_targets', []))
    candidate = compare.coff_symbol_bytes(ROOT / unit['object'], function['symbol_base'],
        ADDRESS, 0xffffffff, targets, compare.known_data_targets(), data_targets)
    native = compare.target_bytes(ADDRESS, 125)
    if (len(candidate) != 125 or hashlib.sha256(candidate).hexdigest() != CANDIDATE_SHA
            or hashlib.sha256(native).hexdigest() != NATIVE_SHA):
        raise ValueError('spawn body or target changed; review the fixture')
    return native, candidate


def execute(code, mode, x, y):
    engine = uc.Uc(uc.UC_ARCH_X86, uc.UC_MODE_32)
    engine.mem_map(0x400000, 0x400000)
    engine.mem_map(OBJECT, 0x10000)
    engine.mem_map(STACK, 0x10000)
    engine.mem_write(ADDRESS, code)
    def put(address, value):
        engine.mem_write(address, struct.pack('<I', value & 0xffffffff))
    def get(address):
        return struct.unpack('<I', engine.mem_read(address, 4))[0]
    def bits(value):
        return struct.unpack('<I', struct.pack('<f', value))[0]
    put(OBJECT, VTABLE)
    put(VTABLE + 8, RESET)
    engine.mem_write(PATH, b'data/example.png\0')
    start_sp = STACK + 0xf000
    for index, value in enumerate((STOP, PATH, mode & 0xffff, bits(x), bits(y))):
        put(start_sp + 4 * index, value)
    engine.reg_write(reg.UC_X86_REG_ESP, start_sp)
    engine.reg_write(reg.UC_X86_REG_ECX, MANAGER)
    events, stopped = [], []
    def step(engine, address, size, _):
        if address == STOP:
            stopped.append(True)
            engine.emu_stop()
            return
        if address not in (0x457110, 0x404c90, 0x407160, RESET):
            return
        esp = engine.reg_read(reg.UC_X86_REG_ESP)
        ret, receiver = get(esp), engine.reg_read(reg.UC_X86_REG_ECX)
        if address == 0x457110:
            events.append(('acquire', receiver))
            engine.reg_write(reg.UC_X86_REG_EAX, OBJECT)
            argument_bytes = 0
        elif address == 0x404c90:
            result, path, width, height = [get(esp + 4 * i) for i in range(1, 5)]
            events.append(('load', receiver, path == PATH))
            put(result, 0x12345678)
            put(width, 73)
            put(height, 29)
            engine.reg_write(reg.UC_X86_REG_EAX, result)
            argument_bytes = 16
        elif address == 0x407160:
            values = tuple(get(esp + 4 * i) for i in range(1, 8))
            events.append(('texture', receiver - OBJECT, values))
            argument_bytes = 28
        else:
            events.append(('reset', receiver - OBJECT, get(OBJECT + 0x13c),
                           get(OBJECT + 0xf4), get(OBJECT + 0xf8)))
            argument_bytes = 0
        engine.reg_write(reg.UC_X86_REG_ESP, esp + 4 + argument_bytes)
        engine.reg_write(reg.UC_X86_REG_EIP, ret)
    engine.hook_add(uc.UC_HOOK_CODE, step)
    engine.emu_start(ADDRESS, STOP + 1, count=1000)
    if not stopped:
        raise ValueError('spawn did not reach its caller return')
    return events, engine.reg_read(reg.UC_X86_REG_EAX), engine.reg_read(reg.UC_X86_REG_ESP) - start_sp


def audit():
    native, candidate = code_bodies()
    for mode, x, y in CASES:
        expected = execute(native, mode, x, y)
        observed = execute(candidate, mode, x, y)
        if expected != observed:
            raise ValueError(f'native/source trace differs for mode {mode}: {expected!r} != {observed!r}')
        events, result, stack_delta = observed
        x_bits = struct.unpack('<I', struct.pack('<f', x))[0]
        y_bits = struct.unpack('<I', struct.pack('<f', y))[0]
        if (len(events) != 4 or [x[0] for x in events] != ['acquire', 'load', 'texture', 'reset']
                or events[0][1] != MANAGER or events[1] != ('load', 0x702798, True)
                or events[2] != ('texture', 12, (0x12345678, 0, 0, 73, 29, 0, 0))
                or events[3][1:] != (0, mode & 0xffffffff, x_bits, y_bits)
                or result != OBJECT or stack_delta != 20):
            raise ValueError(f'unexpected bounded native trace for mode {mode}: {observed!r}')
    return {'cases': len(CASES), 'result': 'bounded_traces_agree',
            'limitations': 'stubbed allocation, texture load, sprite setup and virtual reset; no real I/O or full-game execution'}

if __name__ == '__main__':
    print(json.dumps(audit(), indent=2))
