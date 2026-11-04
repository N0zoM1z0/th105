#!/usr/bin/env python3
"""Compare bounded no-reallocation key-registration traces."""
import hashlib
import importlib.util
import json
import struct
import subprocess
import sys

import unicorn as uc
from unicorn import x86_const as reg
from workflow_manifest import ROOT, load_manifest

UNIT, ADDRESS = 'gpt-web-input-add-tracked-key', 0x40a6c0
NATIVE_SHA = 'd216475e7dc02c57563922b36657dd6c8c3d58912cea295102f81b1b839f7839'
CANDIDATE_SHA = 'fa9003d09a87e2a094f18194f995e48242dcf7557bd77cd400aace4ca3da994d'
OWNER, BUFFER, STACK, STOP = 0x1000000, 0x1002000, 0x200f000, 0x710000
CASES = (((),0), ((5,),5), ((5,),6), ((0,127,255),0),
         ((0,127,255),255), ((0,127,255),9))


def code_bodies():
    subprocess.run([sys.executable, str(ROOT / 'scripts/build.py'), '--unit', UNIT, '--json'],
                   cwd=ROOT, check=True, stdout=subprocess.DEVNULL)
    spec = importlib.util.spec_from_file_location('key_compare', ROOT / 'scripts/compare-function.py')
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
    native = compare.target_bytes(ADDRESS, 202)
    if (len(candidate) != 199 or hashlib.sha256(candidate).hexdigest() != CANDIDATE_SHA
            or hashlib.sha256(native).hexdigest() != NATIVE_SHA):
        raise ValueError('tracked-key body or target changed; review the fixture')
    return native, candidate


def execute(code, values, key):
    if len(values) >= 16:
        raise ValueError('observer requires spare vector capacity')
    engine = uc.Uc(uc.UC_ARCH_X86, uc.UC_MODE_32)
    engine.mem_map(0x400000, 0x400000)
    engine.mem_map(OWNER, 0x10000)
    engine.mem_map(0x2000000, 0x10000)
    engine.mem_write(ADDRESS, code)
    def put(address, value):
        engine.mem_write(address, struct.pack('<I', value & 0xffffffff))
    def get(address):
        return struct.unpack('<I', engine.mem_read(address, 4))[0]
    put(OWNER + 0x404, BUFFER)
    put(OWNER + 0x408, BUFFER + len(values))
    put(OWNER + 0x40c, BUFFER + 16)
    engine.mem_write(BUFFER, bytes(values) + bytes(16 - len(values)))
    put(STACK, STOP)
    put(STACK + 4, key)
    engine.reg_write(reg.UC_X86_REG_ESP, STACK)
    engine.reg_write(reg.UC_X86_REG_ECX, OWNER)
    stopped = []
    def step(engine, address, size, _):
        if address == STOP:
            stopped.append(True)
            engine.emu_stop()
        elif address in (0x68a143, 0x40a8a0, 0x40a7f0):
            raise ValueError('fixture unexpectedly reached error or reallocation path')
    engine.hook_add(uc.UC_HOOK_CODE, step)
    engine.emu_start(ADDRESS, STOP + 1, count=2000)
    if not stopped:
        raise ValueError('tracked-key update did not return')
    end = get(OWNER + 0x408)
    if not BUFFER <= end <= BUFFER + 16:
        raise ValueError('tracked-key vector end left the fixture')
    return bytes(engine.mem_read(BUFFER, end - BUFFER)), engine.reg_read(reg.UC_X86_REG_ESP) - STACK


def audit():
    native, candidate = code_bodies()
    for values, key in CASES:
        target = execute(native, values, key)
        source = execute(candidate, values, key)
        expected = bytes(values if key in values else (*values, key))
        if target != source or source != (expected, 8):
            raise ValueError(f'native/source tracked-key trace differs for {values}, {key}')
    return {'cases': len(CASES), 'result': 'bounded_traces_agree',
            'limitations': 'valid vectors with spare capacity only; no allocation, error path or full-game execution'}

if __name__ == '__main__':
    print(json.dumps(audit(), indent=2))
