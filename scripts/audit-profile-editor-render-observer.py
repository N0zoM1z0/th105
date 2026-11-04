#!/usr/bin/env python3
"""Bounded profile-editor render trace comparison with controlled UI calls."""
import hashlib
import importlib.util
import json
import struct
import subprocess
import sys

import pefile
import unicorn as uc
from unicorn import x86_const as reg
from workflow_manifest import ROOT, load_manifest

UNIT, ADDRESS = 'gpt-web-profile-editor-render', 0x427db0
NATIVE_SHA = '300516c5b6bd3b326f40c6ca56f1b5f9b8c062351b4a98d80d53a8d011b4a6d0'
CANDIDATE_SHA = '6256d99a355e5c3130fa12be00af0d4e2e454b541c81f13136eabbde23dade1a'
OWNER, STACK, STOP, SETRECT = 0x1000000, 0x200f000, 0x710000, 0x710100
CASES = (
    (0,'abcd','xy',1,(0,1),16,0,(1,1),10.5,20.25),
    (1,'abcd','',2,(),16,0,(1,1),10.5,20.25),
    (1,'abcd','xy',1,(0,1),16,0,(1,1),10.5,20.25),
    *((1,'a','x',0,(attribute,),15,30,(1,1),-3.75,9.5)
      for attribute in (0,1,2,3,4,255)),
    (1,'ab','x',1,(3,),17,59,(0,1),0.0,0.0),
    (1,'ab','x',1,(1,),17,29,(1,0),0.0,0.0),
    (1,'','',0,(),16,0,(0,0),1.0,2.0),
)


def code_bodies():
    subprocess.run([sys.executable, str(ROOT / 'scripts/build.py'), '--unit', UNIT, '--json'],
                   cwd=ROOT, check=True, stdout=subprocess.DEVNULL)
    spec = importlib.util.spec_from_file_location('profile_render_compare', ROOT / 'scripts/compare-function.py')
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
    native = compare.target_bytes(ADDRESS, 584)
    if (len(candidate) != 596 or hashlib.sha256(candidate).hexdigest() != CANDIDATE_SHA
            or hashlib.sha256(native).hexdigest() != NATIVE_SHA):
        raise ValueError('profile render body/table or target changed; review the fixture')
    image = pefile.PE(str(compare.TARGET)).get_memory_mapped_image()
    return native, candidate, image


def bits(value):
    return struct.unpack('<I', struct.pack('<f', value))[0]


def execute(code, image, active, primary, composition, cursor, attributes,
            width, tick, handles, x, y):
    engine = uc.Uc(uc.UC_ARCH_X86, uc.UC_MODE_32)
    engine.mem_map(0x400000, 0x400000)
    engine.mem_write(0x400000, image)
    engine.mem_map(OWNER, 0x10000)
    engine.mem_map(0x2000000, 0x10000)
    engine.mem_write(ADDRESS, code)
    def put(address, value):
        engine.mem_write(address, struct.pack('<I', value & 0xffffffff))
    def get(address):
        return struct.unpack('<I', engine.mem_read(address, 4))[0]
    put(0x6c020c, SETRECT)
    # Exercise the actual pinned VC8 SSE conversion path for finite inputs.
    put(0x7039c8, 1)
    put(OWNER, handles[0])
    put(OWNER + 4, handles[1])
    put(OWNER + 0x154, width)
    put(OWNER + 0x160, tick)
    engine.mem_write(0x702b88, primary.encode('ascii') + b'\0')
    engine.mem_write(0x703388, composition.encode('ascii') + b'\0')
    engine.mem_write(0x703488, bytes(a & 255 for a in attributes))
    engine.mem_write(0x70358f, bytes((active,)))
    put(0x703590, cursor)
    for index, value in enumerate((STOP, bits(x), bits(y))):
        put(STACK + 4 * index, value)
    engine.reg_write(reg.UC_X86_REG_ESP, STACK)
    engine.reg_write(reg.UC_X86_REG_ECX, OWNER)
    events, stopped = [], []
    def step(engine, address, size, _):
        if address == STOP:
            stopped.append(True)
            engine.emu_stop()
            return
        if address not in (SETRECT, 0x401260, 0x4099f0):
            return
        esp = engine.reg_read(reg.UC_X86_REG_ESP)
        ret, receiver = get(esp), engine.reg_read(reg.UC_X86_REG_ECX)
        if address == SETRECT:
            pointer, left, top, right, bottom = [get(esp + 4 * i) for i in range(1, 6)]
            engine.mem_write(pointer, struct.pack('<4I', left, top, right, bottom))
            events.append(('rect', left, top, right, bottom))
            engine.reg_write(reg.UC_X86_REG_EAX, 1)
            argument_bytes = 20
        elif address == 0x401260:
            pointer, color, fill = [get(esp + 4 * i) for i in range(1, 4)]
            rect = tuple(struct.unpack('<4I', engine.mem_read(pointer, 16)))
            events.append(('draw', receiver, rect, color, fill))
            engine.reg_write(reg.UC_X86_REG_EAX, 1)
            argument_bytes = 12
        else:
            args = tuple(get(esp + 4 * i) for i in range(1, 5))
            events.append(('tile', receiver - OWNER, args))
            argument_bytes = 16
        engine.reg_write(reg.UC_X86_REG_ESP, esp + 4 + argument_bytes)
        engine.reg_write(reg.UC_X86_REG_EIP, ret)
    engine.hook_add(uc.UC_HOOK_CODE, step)
    engine.emu_start(ADDRESS, STOP + 1, count=10000)
    if not stopped:
        raise ValueError('profile editor render did not return')
    return events, engine.reg_read(reg.UC_X86_REG_ESP) - STACK


def expected(case):
    active, primary, composition, cursor, attributes, width, tick, handles, x, y = case
    events = []
    def rect(left, top, right, bottom):
        return tuple(v & 0xffffffff for v in (left, top, right, bottom))
    if not active:
        return events, 12
    end = cursor + len(composition)
    for index in range(max(len(primary), end)):
        left = int(x) + int(index * width / 2)
        if cursor <= index < end:
            top = int(y)
            full = rect(left, top, left + int(width / 2), top + width + 1)
            events.append(('rect', *full))
            attribute = attributes[index - cursor]
            colors = (0xffffffff, 0xff6060d0, 0xff808080, 0xff6060f0)
            if 0 <= attribute < 4:
                visible = full
                if attribute in (0, 3):
                    visible = rect(left, top + width, left + int(width / 2), top + width + 1)
                    events.append(('rect', *visible))
                events.append(('draw', 0x6fa21c, visible, colors[attribute], 1))
            if handles[1]:
                events.append(('tile', 0xb0, (bits(float(left)), bits(y), index - cursor, 0)))
        elif handles[0]:
            events.append(('tile', 0xc, (bits(float(left)), bits(y), index, 0)))
    if tick % 60 < 30:
        left, top = int(x) + int(cursor * width / 2), int(y)
        caret = rect(left, top, left + 1, top + width + 1)
        events.append(('rect', *caret))
        events.append(('draw', 0x6fa21c, caret, 0xffffffff, 1))
    return events, 12


def audit():
    native, candidate, image = code_bodies()
    for case in CASES:
        target_trace = execute(native, image, *case)
        source_trace = execute(candidate, image, *case)
        if target_trace != source_trace or source_trace != expected(case):
            raise ValueError(f'profile render trace differs for {case!r}')
    return {'cases': len(CASES), 'result': 'bounded_traces_agree',
            'limitations': 'mock SetRect/draw/tile, finite ASCII fixtures and selected x87 environment; no real rendering or full game'}

if __name__ == '__main__':
    print(json.dumps(audit(), indent=2))
