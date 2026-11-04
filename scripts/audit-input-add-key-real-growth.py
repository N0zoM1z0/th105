#!/usr/bin/env python3
"""Execute native and real CIL key insertion, mocking only allocator/CRT calls."""
import copy
import hashlib
import importlib.util
import json
import struct

import pefile
import unicorn as uc
from unicorn import x86_const as r

import linked_pe as core
from workflow_manifest import ROOT, load_manifest

spec = importlib.util.spec_from_file_location('compare', ROOT / 'scripts/compare-function.py')
c = importlib.util.module_from_spec(spec)
spec.loader.exec_module(c)
UNIT = copy.deepcopy(load_manifest()['units']['exact-first-input-state-update'])
UNIT['object'] = 'build/frontier-input-add-key-cil-20261104/Actual.dll'
UNIT['preserve_public_members'] = []
ROOT_SYMBOL = '?add_tracked_key@InputStateTableStorage@th105@@QAEXE@Z'
INSERT_SYMBOL = '?_Insert_n@?$vector@EV?$allocator@E@std@@@std@@IAEXV?$_Vector_iterator@EV?$allocator@E@std@@@2@IABE@Z'
UNIT['functions'] = [{'address':'0x0040A6C0', 'symbol_base':ROOT_SYMBOL,
    'rel32_targets':['__invalid_parameter_noinfo=0x0068A143',
    '?_Xran@?$vector@EV?$allocator@E@std@@@std@@KAXXZ=0x0040A8A0',
    '?insert@?$vector@EV?$allocator@E@std@@@std@@QAE?AV?$_Vector_iterator@EV?$allocator@E@std@@@2@V32@ABE@Z=0x0040A7F0']}]
TARGET_PINS = ((0x40a6c0,202,'d216475e7dc02c57563922b36657dd6c8c3d58912cea295102f81b1b839f7839'),
               (0x40a7f0,126,'1ea2f5cd068bbdbd960ee4d3a4d20bec5561d00fe07a82463e68be92b150dae8'),
               (0x40a920,462,'852d8c80187e61675ed8712523a59a650105b5765cf216cbdcfaf33918da9383'),
               (0x40a870,37,'8bbbef0be2e23ce24bd7e6338853bb0bda4b5a5cf97b31259c0543bff0d145f8'),
               (0x40ab70,65,'4cf60ac8817bdd958602d933636a912d35906d3c717aa28ce2dbb5e050e6f882'))
CASES = (((),0), ((5,),6), ((0,127,255),9), ((1,2,3,4),5),
         ((1,2,3,4,5,6),7), ((5,),5))

def prepare():
    c.verify_target()
    core.build_linked('private-input-add-key-cil', UNIT)
    pe = pefile.PE(str(ROOT / UNIT['object']))
    map_text = (ROOT / UNIT['object']).with_suffix('.map').read_text()
    functions = core.parse_map(map_text)
    symbols = core.parse_map_symbols(map_text)
    def address(name):
     entries = symbols.get(name, [])
     if len(entries) != 1: raise ValueError('linked symbol missing or ambiguous: ' + name)
     return entries[0][0]
    root, insertion = address(ROOT_SYMBOL), address(INSERT_SYMBOL)
    for va, size, digest in TARGET_PINS:
     if hashlib.sha256(c.target_bytes(va,size)).hexdigest() != digest:
      raise ValueError('native insertion body changed')
    for va, size, digest in ((root,269,'e28dc0eb027db53dfcccec8c3c938fadd5babffaf17e3863d675f62070c0800c'),
                             (insertion,461,'4bb681972367ea120a1c034d06ae18b033079f3ddf6ba36bf44675ea76d1fde4')):
     body = core.linked_body(pe,functions,va)
     if len(body) != size or hashlib.sha256(body).hexdigest() != digest:
      raise ValueError('linked insertion body changed')
    providers = {key: address(name) for key,name in (
     ('new','??2@YAPAXI@Z'), ('delete','??3@YAXPAX@Z'),
     ('move','_memmove_s'), ('memset','_memset'), ('bad','__invalid_parameter_noinfo'))}
    native = pefile.PE(str(c.TARGET)).get_memory_mapped_image()
    return native, pe.get_memory_mapped_image(), root, providers

OWNER, BUF, NEW, STACK, STOP = 0x1000000, 0x1002000, 0x1008000, 0x200f000, 0x710000

def run(images, native, values, key, mutate=False):
    """Execute one or more registrations against a shared vector state."""
    native_image, source_image, root, providers = images
    engine = uc.Uc(uc.UC_ARCH_X86, uc.UC_MODE_32)
    engine.mem_map(0x400000, 0x400000)
    engine.mem_write(0x400000, native_image)
    engine.mem_map(0x10000000, 0x10000)
    engine.mem_write(0x10000000, source_image)
    engine.mem_map(OWNER, 0x10000)
    engine.mem_map(0x2000000, 0x10000)

    def put(address, value):
        engine.mem_write(address, struct.pack('<I', value & 0xffffffff))

    def get(address):
        return struct.unpack('<I', engine.mem_read(address, 4))[0]

    first = BUF if values else 0
    end = first + len(values) if values else 0
    put(OWNER + 0x404, first)
    put(OWNER + 0x408, end)
    put(OWNER + 0x40c, end)
    if values:
        engine.mem_write(BUF, bytes(values))
    if mutate:
        if native or bytes(engine.mem_read(root + 0x64, 2)) != bytes.fromhex('0f84'):
            raise ValueError('duplicate gate changed')
        engine.mem_write(root + 0x65, b'\x85')

    events, stopped, allocation_index = [], [], [0]
    new_addresses = (0x689dcb, providers['new'])
    delete_addresses = (0x6898ea, providers['delete'])
    move_addresses = (0x689eb0, providers['move'])
    memset_addresses = (0x68a440, providers['memset'])
    bad_addresses = (0x68a143, providers['bad'])

    def hook(engine, address, size, _):
        if address == STOP:
            stopped.append(True)
            engine.emu_stop()
            return
        if address in bad_addresses:
            raise ValueError('invalid parameter')
        if address not in new_addresses + delete_addresses + move_addresses + memset_addresses:
            return
        sp = engine.reg_read(r.UC_X86_REG_ESP)
        ret = get(sp)
        args = lambda n: tuple(get(sp + 4 * i) for i in range(1, n + 1))
        if address in new_addresses:
            length = args(1)[0]
            allocation = NEW + allocation_index[0] * 0x100
            allocation_index[0] += 1
            if length > 0x100 or allocation >= OWNER + 0x10000:
                raise ValueError('fixture allocator exhausted')
            events.append(('new', length))
            engine.reg_write(r.UC_X86_REG_EAX, allocation)
        elif address in delete_addresses:
            events.append(('delete', args(1)[0]))
        elif address in move_addresses:
            destination, capacity, source, length = args(4)
            if length > capacity:
                raise ValueError('invalid mock move bounds')
            events.append(('move', capacity, length))
            engine.mem_write(destination, bytes(engine.mem_read(source, length)))
            engine.reg_write(r.UC_X86_REG_EAX, 0)
        else:
            destination, value, length = args(3)
            events.append(('set', value, length))
            engine.mem_write(destination, bytes([value & 255]) * length)
            engine.reg_write(r.UC_X86_REG_EAX, destination)
        engine.reg_write(r.UC_X86_REG_ESP, sp + 4)
        engine.reg_write(r.UC_X86_REG_EIP, ret)

    engine.hook_add(uc.UC_HOOK_CODE, hook)
    keys = key if isinstance(key, tuple) else (key,)
    observations = []
    for current_key in keys:
        events.clear()
        stopped.clear()
        put(STACK, STOP)
        put(STACK + 4, current_key)
        engine.reg_write(r.UC_X86_REG_ESP, STACK)
        engine.reg_write(r.UC_X86_REG_ECX, OWNER)
        engine.emu_start(0x40a6c0 if native else root, STOP + 1, count=50000)
        if not stopped:
            raise ValueError('registration did not return')
        first, end, capacity_end = (get(OWNER + x) for x in (0x404, 0x408, 0x40c))
        contents = bytes(engine.mem_read(first, end - first)) if first else b''
        observations.append((contents, end - first if first else 0,
                             capacity_end - first if first else 0, list(events),
                             engine.reg_read(r.UC_X86_REG_ESP) - STACK))
    return observations if isinstance(key, tuple) else observations[0]


def expected_series(keys):
    values, capacity, backing, allocations = [], 0, 0, 0
    observations = []
    for key in keys:
        events = []
        if key not in values:
            if len(values) == capacity:
                new_capacity = max(len(values) + 1, capacity + capacity // 2)
                events.append(('new', new_capacity))
                if values:
                    events += [('move', len(values), len(values)), ('delete', backing)]
                backing = NEW + allocations * 0x100
                allocations += 1
                capacity = new_capacity
            values.append(key)
        observations.append((bytes(values), len(values), capacity, events, 8))
    return observations

def expected(values, key):
    duplicate = key in values
    if duplicate:
     return bytes(values), len(values), len(values), [], 8
    n = len(values)
    capacity = max(n + 1, n + n // 2)
    events = [('new', capacity)]
    if n: events += [('move', n, n), ('delete', BUF)]
    return bytes((*values, key)), n + 1, capacity, events, 8


def audit():
    images = prepare()
    for values, key in CASES:
     if run(images,True,values,key) != expected(values,key) or run(images,False,values,key) != expected(values,key):
      raise ValueError('real insertion trace differs for ' + repr((values,key)))
    return {'cases':len(CASES), 'result':'bounded_traces_agree',
            'limitations':'native and real CIL insertion execute; allocator and CRT memory operations mocked; no failure, OS or full game'}

if __name__ == '__main__':
    print(json.dumps(audit(), indent=2))
