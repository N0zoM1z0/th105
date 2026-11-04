#!/usr/bin/env python3
"""Compare six bounded DirectSound-volume wrapper traces with a mock COM call."""
import hashlib
import importlib.util
import json
from pathlib import Path
import struct
import subprocess
import sys

import unicorn as uc
from unicorn import x86_const as reg
from workflow_manifest import ROOT, load_manifest

UNIT, ADDRESS = 'gpt-web-bgm-buffer-set-volume', 0x401830
NATIVE_SHA = '3a36996783e794ec7971e821df5362286f4d769105569e1e7ccfaeb64f177669'
CANDIDATE_SHA = 'a4a0681fda29eccba8403a2a9b0e399ea705a599f3038542f992e05f51cff81f'
OWNER, RESOURCE, VTABLE, STACK, STOP, COM = 0x1000000, 0x1001000, 0x1002000, 0x200f000, 0x710000, 0x710100


def code_bodies():
    subprocess.run([sys.executable, str(ROOT / 'scripts/build.py'), '--unit', UNIT, '--json'],
                   cwd=ROOT, check=True, stdout=subprocess.DEVNULL)
    spec = importlib.util.spec_from_file_location('volume_compare', ROOT / 'scripts/compare-function.py')
    compare = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(compare)
    compare.verify_target()
    unit = load_manifest()['units'][UNIT]
    function = unit['functions'][0]
    candidate = compare.coff_symbol_bytes(ROOT / unit['object'], function['symbol_base'],
        ADDRESS, 0xffffffff, compare.known_targets(), compare.known_data_targets(), {})
    native = compare.target_bytes(ADDRESS, 19)
    if (len(candidate) != 25 or hashlib.sha256(candidate).hexdigest() != CANDIDATE_SHA
            or hashlib.sha256(native).hexdigest() != NATIVE_SHA):
        raise ValueError('volume body or target changed; review the fixture')
    return native, candidate


def execute(code, native_abi, present, value):
    engine = uc.Uc(uc.UC_ARCH_X86, uc.UC_MODE_32)
    engine.mem_map(0x400000, 0x400000)
    engine.mem_map(OWNER, 0x10000)
    engine.mem_map(0x2000000, 0x10000)
    engine.mem_write(ADDRESS, code)
    def put(address, word):
        engine.mem_write(address, struct.pack('<I', word & 0xffffffff))
    def get(address):
        return struct.unpack('<I', engine.mem_read(address, 4))[0]
    put(OWNER + 4, RESOURCE if present else 0)
    put(RESOURCE, VTABLE)
    put(VTABLE + 0x3c, COM)
    put(STACK, STOP)
    put(STACK + 4, value)
    engine.reg_write(reg.UC_X86_REG_ESP, STACK)
    engine.reg_write(reg.UC_X86_REG_EAX if native_abi else reg.UC_X86_REG_ECX, OWNER)
    if native_abi:
        engine.reg_write(reg.UC_X86_REG_EDX, value & 0xffffffff)
    calls, stopped = [], []
    def step(engine, address, size, _):
        if address == STOP:
            stopped.append(True)
            engine.emu_stop()
        elif address == COM:
            esp = engine.reg_read(reg.UC_X86_REG_ESP)
            calls.append((get(esp + 4), get(esp + 8)))
            engine.reg_write(reg.UC_X86_REG_EIP, get(esp))
            engine.reg_write(reg.UC_X86_REG_ESP, esp + 12)
    engine.hook_add(uc.UC_HOOK_CODE, step)
    engine.emu_start(ADDRESS, STOP + 1, count=100)
    if not stopped:
        raise ValueError('volume wrapper did not return')
    return calls, engine.reg_read(reg.UC_X86_REG_ESP) - STACK


def audit():
    native, candidate = code_bodies()
    count = 0
    for present in (False, True):
        for value in (-10000, -1, 0):
            native_calls, native_stack = execute(native, True, present, value)
            source_calls, source_stack = execute(candidate, False, present, value)
            expected = [(RESOURCE, value & 0xffffffff)] if present else []
            if native_calls != expected or source_calls != expected:
                raise ValueError('native/source mock COM trace differs from expected')
            # Distinct ABI boundaries are intentional; compare their own cleanup.
            if native_stack != 4 or source_stack != 8:
                raise ValueError('native/source return cleanup changed')
            count += 1
    return {'cases': count, 'result': 'bounded_calls_agree',
            'limitations': 'mock DirectSound method; native private ABI and ordinary source ABI differ'}

if __name__ == '__main__':
    print(json.dumps(audit(), indent=2))
