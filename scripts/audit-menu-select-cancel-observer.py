#!/usr/bin/env python3
"""Observe the real menu-selection cancel paths with mocked UI providers."""
import hashlib
import importlib.util
import json
import struct
import subprocess
import sys
import unicorn as uc
from unicorn import x86_const as reg
from workflow_manifest import ROOT, load_manifest

UNIT, ADDRESS = 'exact-first-menu-select-primary', 0x447d20
OWNER, INPUT, OBJECT, VTABLE, STACK, STOP, COLOR = 0x1000000, 0x1002000, 0x1003000, 0x1004000, 0x200f000, 0x710000, 0x710100
NATIVE_SHA = '734fdf7846611548e8cbe17846298fb1190dcfeee014c6aae36e14c980eb268e'
SOURCE_SHA = 'e34ac53616d075aa906247e216098bdecbed6f9ad8b8e5bb7d6fb6788b78d7a7'


def code_bodies():
    subprocess.run([sys.executable, str(ROOT / 'scripts/build.py'), '--unit', UNIT, '--json'],
                   cwd=ROOT, check=True, stdout=subprocess.DEVNULL)
    spec = importlib.util.spec_from_file_location('menu_compare', ROOT / 'scripts/compare-function.py')
    compare = importlib.util.module_from_spec(spec); spec.loader.exec_module(compare); compare.verify_target()
    unit = load_manifest()['units'][UNIT]; f = unit['functions'][0]; targets = compare.known_targets()
    for mapping in f['rel32_targets']:
        name, address = mapping.rsplit('=', 1); targets[name] = int(address, 0)
    data = dict(mapping.split('=', 1) for mapping in f['dir32_targets'])
    source = compare.coff_symbol_bytes(ROOT / unit['object'], f['symbol_base'], ADDRESS,
        0xffffffff, targets, compare.known_data_targets(), data)
    native = compare.target_bytes(ADDRESS, 704)
    if (len(native) != 704 or hashlib.sha256(native).hexdigest() != NATIVE_SHA or
        len(source) != 680 or hashlib.sha256(source).hexdigest() != SOURCE_SHA):
        raise ValueError('menu code or switch payload changed; review fixture')
    return native, source


def execute(code, selection, primary, cancel, menu_cancel, game_mode=0, full=False):
    engine = uc.Uc(uc.UC_ARCH_X86, uc.UC_MODE_32)
    engine.mem_map(0, 0x1000); engine.mem_map(0x400000, 0x400000)
    engine.mem_map(OWNER, 0x10000); engine.mem_map(0x2000000, 0x10000)
    engine.mem_write(ADDRESS, code)
    def put(address, value): engine.mem_write(address, struct.pack('<I', value & 0xffffffff))
    def get(address): return struct.unpack('<I', engine.mem_read(address, 4))[0]
    put(0x6fd030, INPUT); put(OWNER + 0x68, selection); put(INPUT + 0x40, primary); put(INPUT + 0x44, cancel)
    engine.mem_write(OWNER + 4, bytes((0x55, 0x66))); engine.mem_write(OWNER + 0x70, b"\x44"); put(0x6e694c, 22)
    put(VTABLE + 4, COLOR)
    for index in range(8):
        obj = OBJECT + 0x20 * index; put(obj, VTABLE); put(OWNER + 0x3c + index * 4, obj)
    put(STACK, STOP); engine.reg_write(reg.UC_X86_REG_ESP, STACK); engine.reg_write(reg.UC_X86_REG_ECX, OWNER)
    events, stopped = [], []
    def hook(engine, address, size, _):
        if address == STOP:
            stopped.append(True); engine.emu_stop(); return
        if address not in (0x41fa20, 0x43b1a0, 0x43abd0, COLOR, 0x689dcb,
                           0x43afe0, 0x4487e0, 0x44ba90, 0x43b0f0, 0x43ac40): return
        sp = engine.reg_read(reg.UC_X86_REG_ESP); cleanup = 0
        if address == 0x41fa20:
            events.append(('cursor',)); engine.reg_write(reg.UC_X86_REG_EAX, 0)
        elif address == 0x43b1a0:
            events.append(('event', get(sp + 4)))
        elif address == 0x43abd0:
            events.append(('menu_cancel',)); engine.reg_write(reg.UC_X86_REG_EAX, menu_cancel)
        elif address == COLOR:
            events.append(('color', engine.reg_read(reg.UC_X86_REG_ECX), get(sp + 4))); cleanup = 4
        elif address == 0x689dcb:
            events.append(('new', get(sp + 4))); engine.reg_write(reg.UC_X86_REG_EAX, 0x1006000)
        elif address == 0x43afe0:
            slot = get(sp + 4); events.append(('player', slot)); engine.reg_write(reg.UC_X86_REG_EAX, 0x1007000 + 0x100 * slot)
        elif address in (0x4487e0, 0x44ba90):
            receiver = engine.reg_read(reg.UC_X86_REG_ECX); player = get(sp + 4)
            if address == 0x4487e0:
                events.append(('character', receiver, player)); cleanup = 4
            else:
                events.append(('keys', receiver, player, get(sp + 8))); cleanup = 8
            engine.reg_write(reg.UC_X86_REG_EAX, receiver)
        elif address == 0x43b0f0:
            events.append(('install', get(sp + 4)))
        else:
            events.append(('game_mode',)); engine.reg_write(reg.UC_X86_REG_EAX, game_mode)
        engine.reg_write(reg.UC_X86_REG_EIP, get(sp)); engine.reg_write(reg.UC_X86_REG_ESP, sp + 4 + cleanup)
    engine.hook_add(uc.UC_HOOK_CODE, hook)
    engine.emu_start(ADDRESS, STOP + 1, count=3000)
    if not stopped: raise ValueError('menu did not return')
    result = (engine.reg_read(reg.UC_X86_REG_EAX) & 255, events)
    if full:
        result += (bytes(engine.mem_read(OWNER + 4, 2)), bytes(engine.mem_read(OWNER + 0x70, 1))[0], get(0x6e694c))
    return result


def expected(primary, cancel, menu_cancel):
    events = [('cursor',)] + [('color', OBJECT + 0x20 * i, 0xffffffff) for i in range(8)]
    if primary == 1: return 0, events + [('event', 40)]
    if cancel == 1: return 0, events + [('event', 41)]
    events += [('menu_cancel',)]
    return (0, events + [('event', 41)]) if menu_cancel else (1, events)


def expected_selection(selection, game_mode):
    events = [('cursor',)] + [('color', OBJECT + 0x20 * i, 0xffffffff) for i in range(8)]
    events.append(('event', 40))
    state, active, scene = 0x55, 0x44, 22
    result = 1
    if selection in (0, 1):
        state, active = 1, selection
    elif selection in (2, 3):
        slot = selection - 2; active = slot
        events += [('new', 0x288), ('player', slot),
                   ('character', 0x1006000, 0x1007000 + 0x100 * slot), ('install', 0x1006000)]
    elif selection in (4, 5):
        slot = selection - 4
        if selection == 5: events.append(('game_mode',))
        binding = 0 if selection == 4 else (1 if game_mode == 3 else 0xffffffff)
        events += [('new', 0x330), ('player', slot),
                   ('keys', 0x1006000, 0x1007000 + 0x100 * slot, binding), ('install', 0x1006000)]
    elif selection == 6:
        scene = 2
    elif selection == 7:
        result = 0
    return result, events, bytes((state, 0)), active, scene


def audit():
    bodies = code_bodies(); cases = ((7,1,0,0), (0,0,1,0), (0,0,0,1), (0,0,0,0))
    for case in cases:
        for code in bodies:
            if execute(code, *case) != expected(*case[1:]):
                raise ValueError('menu cancel trace differs for ' + repr(case))
    return {'cases':len(cases), 'result':'bounded_traces_agree',
            'limitations':'UI helpers and menu input mocked; no allocation, exceptions or full-game execution'}

if __name__ == '__main__': print(json.dumps(audit(), indent=2))
