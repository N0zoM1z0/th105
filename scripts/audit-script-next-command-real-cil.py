#!/usr/bin/env python3
"""Compare actual native and genuine CIL script deque cursor execution."""
import copy
import hashlib
import importlib.util
import json
import struct

import pefile
import unicorn as uc
from unicorn import x86_const as reg
import linked_pe as core
from workflow_manifest import ROOT, load_manifest

SYMBOL = '?next_command@CScript@@QAEPAVCCommandBase@@XZ'
UNIT = copy.deepcopy(load_manifest()['units']['exact-first-script-next-command'])
UNIT.update(kind='linked_candidate', object='build/frontier-next-command-real-cil-20261104/Actual.dll',
            profile='vc8-sp1-ltcg-o2', enable_gs=False, link_runtime='static', link_data_targets=[])
OWNER, MAP, BLOCKS, STACK, STOP = 0x1000000, 0x1004000, 0x1005000, 0x200f000, 0x710000
CASES = ((0,0,0), (0,1,0), (0,4,2), (3,5,3), (14,3,14), (14,3,16), (14,3,17))


def prepare():
    spec = importlib.util.spec_from_file_location('script_compare', ROOT / 'scripts/compare-function.py')
    compare = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(compare)
    compare.verify_target()
    core.build_linked('private-next-command-real-cil', UNIT)
    pe = pefile.PE(str(ROOT / UNIT['object']))
    map_text = (ROOT / UNIT['object']).with_suffix('.map').read_text()
    functions, symbols = core.parse_map(map_text), core.parse_map_symbols(map_text)
    def address(name):
        entries = symbols.get(name, [])
        if len(entries) != 1:
            raise ValueError('linked symbol missing or ambiguous: ' + name)
        return entries[0][0]
    root = address(SYMBOL)
    body = core.linked_body(pe, functions, root)
    if len(body) != 156 or hashlib.sha256(body).hexdigest() != 'c28d661f48489cf8e01ebccc44857681bcb7f308e643b80898807d5159038ceb':
        raise ValueError('linked script cursor changed; review fixture')
    for va, size, digest in ((0x405ac0,104,'f055a70e7657ac54bc37a49178b9e70497c30886170bd2eea163e46b1f69f4c8'),
                             (0x405bb0,73,'633dfc35ddb6f2fdd5a59f8593b27e31ed41c31feb93cade0530c67db616f1cd')):
        if hashlib.sha256(compare.target_bytes(va,size)).hexdigest() != digest:
            raise ValueError('native script cursor changed; review fixture')
    return (pefile.PE(str(compare.TARGET)).get_memory_mapped_image(),
            pe.get_memory_mapped_image(), root, address('__invalid_parameter_noinfo'))


def execute(images, native, offset, count, cursor, mutate=False, steps=1,
            iterator_owner="valid", stop_at_invalid=False):
    if iterator_owner not in ("valid", "null"):
        raise ValueError("unsupported iterator owner fixture")
    native_image, source_image, root, invalid = images
    engine = uc.Uc(uc.UC_ARCH_X86, uc.UC_MODE_32)
    engine.mem_map(0x400000, 0x400000); engine.mem_write(0x400000, native_image)
    engine.mem_map(0x10000000, 0x10000); engine.mem_write(0x10000000, source_image)
    engine.mem_map(OWNER, 0x10000); engine.mem_map(0x2000000, 0x10000)
    if mutate:
        if native or bytes(engine.mem_read(root + 0x92, 4)) != bytes.fromhex('83463001'):
            raise ValueError('cursor increment changed')
        engine.mem_write(root + 0x95, b'\x02')
    def put(address, value):
        engine.mem_write(address, struct.pack('<I', value & 0xffffffff))
    def get(address):
        return struct.unpack('<I', engine.mem_read(address, 4))[0]
    deque = OWNER + 0x14
    put(deque + 4, MAP); put(deque + 8, 4); put(deque + 12, offset); put(deque + 16, count)
    put(OWNER + 0x2c, deque if iterator_owner == "valid" else 0); put(OWNER + 0x30, cursor)
    for block in range(4):
        put(MAP + 4 * block, BLOCKS + 0x100 * block)
        for index in range(4):
            put(BLOCKS + 0x100 * block + 4 * index, 0x2000 + 4 * (block * 4 + index))
    put(STACK, STOP)
    engine.reg_write(reg.UC_X86_REG_ESP, STACK); engine.reg_write(reg.UC_X86_REG_ECX, OWNER)
    stopped = []
    def step(engine, address, size, _):
        if address == STOP:
            stopped.append(True); engine.emu_stop()
        elif address in (0x68a143, invalid):
            if not stop_at_invalid:
                raise ValueError('fixture hit checked invalid-parameter path')
            stopped.append('invalid_parameter'); engine.emu_stop()
    engine.hook_add(uc.UC_HOOK_CODE, step)
    observations = []
    for _ in range(steps):
        stopped.clear()
        put(STACK, STOP)
        engine.reg_write(reg.UC_X86_REG_ESP, STACK)
        engine.reg_write(reg.UC_X86_REG_ECX, OWNER)
        engine.emu_start(0x405ac0 if native else root, STOP + 1, count=2000)
        if not stopped:
            raise ValueError('script cursor did not return')
        if stopped == ['invalid_parameter']:
            return ('invalid_parameter', get(OWNER + 0x30))
        observations.append((engine.reg_read(reg.UC_X86_REG_EAX), get(OWNER + 0x30),
                             engine.reg_read(reg.UC_X86_REG_ESP) - STACK))
    return observations[0] if steps == 1 else observations


def expected(offset, count, cursor):
    if cursor == offset + count:
        return 0, cursor, 4
    slot = ((cursor // 4) % 4) * 4 + cursor % 4
    return 0x2000 + 4 * slot, cursor + 1, 4


def audit():
    images = prepare()
    for case in CASES:
        if execute(images, True, *case) != expected(*case) or execute(images, False, *case) != expected(*case):
            raise ValueError('script cursor trace differs for ' + repr(case))
    return {'cases': len(CASES), 'result': 'bounded_traces_agree',
            'limitations': 'valid bounded deque layouts; no invalid iterator, allocation, actual script parsing or full game'}

if __name__ == '__main__':
    print(json.dumps(audit(), indent=2))
