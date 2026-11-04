#!/usr/bin/env python3
"""Compare bounded config-menu secondary-selection traces with mocked UI calls."""
import hashlib
import importlib.util
import json
import struct
import subprocess
import sys

import unicorn as uc
from unicorn import x86_const as reg
from workflow_manifest import ROOT, load_manifest

UNIT, ADDRESS = 'gpt-web-menu-config-secondary', 0x440ff0
NATIVE_PAYLOAD_SHA = '0b8505b906fc038c352560f305c4a610b00a6f4fce591b63c5154f374edd8e6a'
CANDIDATE_SHA = '3507bac6220a037ecc3fbcc5ddf006ca3bbeb47e04e8da14a68edd8f89d04413'
OWNER, CONFIG, VTABLE, INPUT, STACK, STOP, TEXTURE = 0x1000000, 0x1001000, 0x1002000, 0x1003000, 0x200f000, 0x710000, 0x710100
PRIMARIES = (-1, 0, 1, 2, 3, 4, 5)
VALUES = (-11, 0, 3, 5, 100, 105)


def code_bodies():
    subprocess.run([sys.executable, str(ROOT / 'scripts/build.py'), '--unit', UNIT, '--json'],
                   cwd=ROOT, check=True, stdout=subprocess.DEVNULL)
    spec = importlib.util.spec_from_file_location('config_compare', ROOT / 'scripts/compare-function.py')
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
    native = compare.target_bytes(ADDRESS, 436)
    if (len(candidate) != 420 or hashlib.sha256(candidate).hexdigest() != CANDIDATE_SHA
            or hashlib.sha256(native).hexdigest() != NATIVE_PAYLOAD_SHA):
        raise ValueError('menu-config body/table or target changed; review the fixture')
    return native, candidate


def execute(code, primary, value):
    engine = uc.Uc(uc.UC_ARCH_X86, uc.UC_MODE_32)
    engine.mem_map(0x400000, 0x400000)
    engine.mem_map(OWNER, 0x10000)
    engine.mem_map(0x2000000, 0x10000)
    engine.mem_write(ADDRESS, code)
    def put(address, word):
        engine.mem_write(address, struct.pack('<I', word & 0xffffffff))
    def get(address):
        return struct.unpack('<I', engine.mem_read(address, 4))[0]
    put(OWNER + 4, CONFIG)
    put(OWNER + 0xb4, 0x1234)
    put(OWNER + 0xb8, VTABLE)
    put(OWNER + 0x14c, VTABLE)
    put(VTABLE + 0x14, TEXTURE)
    put(OWNER + 0x1e0, 320)
    put(OWNER + 0x1e4, 48)
    put(OWNER + 0x284, 0xdeadbeef)
    put(0x6fd030, INPUT)
    for offset in (0x64, 0x68, 0x6c):
        put(CONFIG + offset, value)
    engine.mem_write(CONFIG + 0x70, bytes((value & 255, (value + 1) & 255)))
    put(STACK, STOP)
    put(STACK + 4, primary)
    engine.reg_write(reg.UC_X86_REG_ESP, STACK)
    engine.reg_write(reg.UC_X86_REG_ECX, OWNER)
    events, stopped = [], []
    def step(engine, address, size, _):
        if address == STOP:
            stopped.append(True)
            engine.emu_stop()
            return
        if address not in (0x4204e0, TEXTURE):
            return
        esp = engine.reg_read(reg.UC_X86_REG_ESP)
        ret, receiver = get(esp), engine.reg_read(reg.UC_X86_REG_ECX)
        if address == 0x4204e0:
            input_pointer, count, page = [get(esp + 4 * i) for i in range(1, 4)]
            events.append(('bind', receiver - OWNER, input_pointer == INPUT, count, page))
            # Controlled mock of the separately exact horizontal cursor binder.
            put(receiver, count)
            put(receiver + 4, page)
            put(receiver + 8, input_pointer + 0x38 if input_pointer else 0)
            put(receiver + 12, 0)
            put(receiver + 16, 0)
            argument_bytes = 12
        else:
            args = tuple(get(esp + 4 * i) for i in range(1, 6))
            events.append(('texture', receiver - OWNER, args))
            argument_bytes = 20
        engine.reg_write(reg.UC_X86_REG_ESP, esp + 4 + argument_bytes)
        engine.reg_write(reg.UC_X86_REG_EIP, ret)
    engine.hook_add(uc.UC_HOOK_CODE, step)
    engine.emu_start(ADDRESS, STOP + 1, count=2000)
    if not stopped:
        raise ValueError('menu-config secondary update did not return')
    return events, bytes(engine.mem_read(OWNER + 0x278, 20)), engine.reg_read(reg.UC_X86_REG_ESP) - STACK


def expected_selection(primary, value):
    if primary == 0:
        return max(0, min(3, value))
    if primary in (1, 2):
        # Values in this fixture are small; int division truncates toward zero.
        return max(0, min(20, int(value / 5)))
    if primary == 3:
        return int((value & 255) == 0)
    if primary == 4:
        return int(((value + 1) & 255) == 0)
    return 0xdeadbeef


def audit():
    native, candidate = code_bodies()
    count = 0
    for primary in PRIMARIES:
        for value in VALUES:
            expected = execute(native, primary, value)
            observed = execute(candidate, primary, value)
            if expected != observed or observed[-1] != 8:
                raise ValueError(f'native/source trace differs for {primary=}, {value=}')
            events, cursor, _ = observed
            selection = struct.unpack_from('<I', cursor, 12)[0]
            if selection != expected_selection(primary, value):
                raise ValueError(f'unexpected selection for {primary=}, {value=}')
            if primary in (0, 1, 2, 3, 4):
                count_expected = 4 if primary == 0 else (21 if primary in (1, 2) else 2)
                if not events or events[0] != ('bind', 0x278, True, count_expected, 0):
                    raise ValueError('unexpected bounded cursor binding')
            if primary in (1, 2):
                width = ((320 * (value & 0xffffffff)) & 0xffffffff) // 100
                texture = ('texture', 0xb8 if primary == 1 else 0x14c,
                           (0x1234, 0, 0, width, 48))
                if len(events) != 2 or events[1] != texture:
                    raise ValueError('unexpected bounded texture call')
            elif len(events) != (1 if primary in (0, 3, 4) else 0):
                raise ValueError('unexpected bounded UI calls')
            count += 1
    return {'cases': count, 'result': 'bounded_traces_agree',
            'limitations': 'mock cursor binding and sprite texture; fixed dimensions and finite inputs, no full game or OS execution'}

if __name__ == '__main__':
    print(json.dumps(audit(), indent=2))
