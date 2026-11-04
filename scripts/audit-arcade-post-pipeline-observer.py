#!/usr/bin/env python3
"""Bounded actual native/source Arcade post-pipeline execution."""
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

UNIT, ADDRESS = 'exact-first-arcade-post-pipeline', 0x472f80
NATIVE_SHA = '7bd9a3677d422ac3ea268666d008962cbe98e547bdb4a781dac8c5d4395143fe'
SOURCE_SHA = 'a194fd236d33d3094f29894db9af4efd7177b239619b37927799ab0b1514221d'
OWNER, FIRST, SECOND, VTABLE, STACK, STOP, TRANSITION = 0x1000000, 0x1001000, 0x1002000, 0x1003000, 0x200f000, 0x710000, 0x710100


def code_bodies():
    subprocess.run([sys.executable, str(ROOT / 'scripts/build.py'), '--unit', UNIT, '--json'],
                   cwd=ROOT, check=True, stdout=subprocess.DEVNULL)
    spec = importlib.util.spec_from_file_location('arcade_post_compare', ROOT / 'scripts/compare-function.py')
    compare = importlib.util.module_from_spec(spec); spec.loader.exec_module(compare); compare.verify_target()
    unit = load_manifest()['units'][UNIT]; function = unit['functions'][0]
    source = compare.coff_symbol_bytes(ROOT / unit['object'], function['symbol_base'], ADDRESS,
        0xffffffff, compare.known_targets(), compare.known_data_targets(), {})
    native = compare.target_bytes(ADDRESS, 198)
    if (len(native) != 198 or hashlib.sha256(native).hexdigest() != NATIVE_SHA or
        len(source) != 198 or hashlib.sha256(source).hexdigest() != SOURCE_SHA):
        raise ValueError('Arcade post-pipeline body changed; review fixture')
    return native, source


def execute(code, case):
    pending_a, pending_b, delay_a, delay_b, state = case
    engine = uc.Uc(uc.UC_ARCH_X86, uc.UC_MODE_32)
    engine.mem_map(0x400000, 0x400000); engine.mem_map(OWNER, 0x10000); engine.mem_map(0x2000000, 0x10000)
    engine.mem_write(ADDRESS, code)
    def put(address, value): engine.mem_write(address, struct.pack('<I', value & 0xffffffff))
    def get(address): return struct.unpack('<I', engine.mem_read(address, 4))[0]
    put(OWNER, VTABLE); put(VTABLE + 0x34, TRANSITION); put(OWNER + 0xc, FIRST); put(OWNER + 0x10, SECOND)
    engine.mem_write(FIRST + 0x4e8, bytes((delay_a, pending_a, 0, 0x33)))
    engine.mem_write(SECOND + 0x4e8, bytes((delay_b, pending_b, 0, 0x44)))
    engine.mem_write(OWNER + 0x5b0, bytes((state,))); put(STACK, STOP)
    engine.reg_write(reg.UC_X86_REG_ESP, STACK); engine.reg_write(reg.UC_X86_REG_ECX, OWNER)
    events, stopped = [], []
    def hook(engine, address, size, _):
        if address == STOP: stopped.append(True); engine.emu_stop(); return
        if address == TRANSITION:
            sp = engine.reg_read(reg.UC_X86_REG_ESP)
            events.append((engine.reg_read(reg.UC_X86_REG_ECX), get(sp + 4)))
            engine.reg_write(reg.UC_X86_REG_EIP, get(sp)); engine.reg_write(reg.UC_X86_REG_ESP, sp + 8)
    engine.hook_add(uc.UC_HOOK_CODE, hook); engine.emu_start(ADDRESS, STOP + 1, count=500)
    if not stopped: raise ValueError('Arcade post-pipeline did not return')
    def byte(address): return bytes(engine.mem_read(address, 1))[0]
    return (byte(FIRST + 0x4e8), byte(SECOND + 0x4e8), byte(FIRST + 0x4eb),
            byte(SECOND + 0x4eb), byte(OWNER + 0x5b0), events)


def expected(case):
    a, b, da, db, state = case
    fa, fb, events = 0x33, 0x44, []
    if a and b:
        da = db = 1; state = 2; events.append((OWNER, 3))
    elif a:
        db = (db + 1) & 255
        if db == 2: fa = 1; state = 2; events.append((OWNER, 4))
        else: state = (state + 1) & 255; events.append((OWNER, 3))
    elif b:
        da = (da + 1) & 255
        if da == 2: fb = 1; state = 2; events.append((OWNER, 4))
        else: state = (state + 1) & 255; events.append((OWNER, 3))
    return da, db, fa, fb, state, events


def audit():
    bodies = code_bodies(); cases = list(itertools.product((0, 1), (0, 1), (0, 1, 255), (0, 1, 255), (0, 255)))
    for case in cases:
        for body in bodies:
            if execute(body, case) != expected(case): raise ValueError('Arcade trace differs for ' + repr(case))
    return {'cases':len(cases), 'result':'bounded_traces_agree',
            'limitations':'transition virtual is mocked; no concurrent updates or full-game execution'}

if __name__ == '__main__': print(json.dumps(audit(), indent=2))
