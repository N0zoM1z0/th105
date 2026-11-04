#!/usr/bin/env python3
"""Compare bounded checked-list update/prune traces with controlled callbacks."""
import hashlib
import importlib.util
import json
import struct
import subprocess
import sys

import unicorn as uc
from unicorn import x86_const as reg
from workflow_manifest import ROOT, load_manifest

UNIT, ADDRESS = 'gpt-web-system-effect-tracked-update', 0x456d70
NATIVE_SHA = '3d388c3213b3e439b25969e50cbc0a28982fa4e44133e2d618c5db2e7846cba5'
CANDIDATE_SHA = '8a0b422d86622752dde63ee7ce1af9bc48a4876d94806d157e0a6fa4e6c764f4'
OWNER, HEAD, STACK, STOP, CALLBACK = 0x1000000, 0x1001000, 0x200f000, 0x710000, 0x710100
CASES = (((), ()), ((1,), ()), ((0,), ()), ((1,0,1,0), ()), ((1,1), (1,)))


def code_bodies():
    subprocess.run([sys.executable, str(ROOT / 'scripts/build.py'), '--unit', UNIT, '--json'],
                   cwd=ROOT, check=True, stdout=subprocess.DEVNULL)
    spec = importlib.util.spec_from_file_location('tracked_compare', ROOT / 'scripts/compare-function.py')
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
    native = compare.target_bytes(ADDRESS, 201)
    if (len(candidate) != 201 or hashlib.sha256(candidate).hexdigest() != CANDIDATE_SHA
            or hashlib.sha256(native).hexdigest() != NATIVE_SHA):
        raise ValueError('tracked update body or target changed; review the fixture')
    return native, candidate


def execute(code, states, flip):
    engine = uc.Uc(uc.UC_ARCH_X86, uc.UC_MODE_32)
    engine.mem_map(0x400000, 0x400000)
    engine.mem_map(OWNER, 0x10000)
    engine.mem_map(0x2000000, 0x10000)
    engine.mem_write(ADDRESS, code)
    def put(address, value):
        engine.mem_write(address, struct.pack('<I', value & 0xffffffff))
    def get(address):
        return struct.unpack('<I', engine.mem_read(address, 4))[0]
    nodes = [0x1002000 + i * 0x20 for i in range(len(states))]
    objects = [0x1004000 + i * 0x100 for i in range(len(states))]
    put(OWNER + 0x58, HEAD)
    put(OWNER + 0x5c, len(nodes))
    put(HEAD, nodes[0] if nodes else HEAD)
    put(HEAD + 4, nodes[-1] if nodes else HEAD)
    for i, node in enumerate(nodes):
        put(node, nodes[i + 1] if i + 1 < len(nodes) else HEAD)
        put(node + 4, nodes[i - 1] if i else HEAD)
        put(node + 8, objects[i])
        put(objects[i] + 4, states[i])
        put(objects[i] + 8, 0x100 + i)
    for index, value in enumerate((STOP, CALLBACK, 0)):
        put(STACK + 4 * index, value)
    engine.reg_write(reg.UC_X86_REG_ESP, STACK)
    engine.reg_write(reg.UC_X86_REG_ECX, OWNER)
    events, stopped = [], []
    def step(engine, address, size, _):
        if address == STOP:
            stopped.append(True)
            engine.emu_stop()
            return
        if address == 0x68a143:
            raise ValueError('fixture violates checked-list preconditions')
        if address not in (CALLBACK, 0x56d8f0, 0x6898ea):
            return
        esp = engine.reg_read(reg.UC_X86_REG_ESP)
        ret, receiver = get(esp), engine.reg_read(reg.UC_X86_REG_ECX)
        if address == CALLBACK:
            index = objects.index(receiver)
            events.append(('update', index))
            if index in flip:
                put(receiver + 4, 0)
            argument_bytes = 0
        elif address == 0x56d8f0:
            events.append(('release', receiver - OWNER, get(esp + 4)))
            argument_bytes = 4
        else:
            events.append(('delete', nodes.index(get(esp + 4))))
            argument_bytes = 0
        engine.reg_write(reg.UC_X86_REG_ESP, esp + 4 + argument_bytes)
        engine.reg_write(reg.UC_X86_REG_EIP, ret)
    engine.hook_add(uc.UC_HOOK_CODE, step)
    engine.emu_start(ADDRESS, STOP + 1, count=3000)
    if not stopped:
        raise ValueError('tracked update did not return')
    remaining, previous, node = [], HEAD, get(HEAD)
    while node != HEAD:
        if node not in nodes or len(remaining) >= len(nodes) or get(node + 4) != previous:
            raise ValueError('fixture list links are inconsistent')
        remaining.append(nodes.index(node))
        previous, node = node, get(node)
    if get(HEAD + 4) != previous:
        raise ValueError('fixture list tail is inconsistent')
    return events, remaining, get(OWNER + 0x5c), engine.reg_read(reg.UC_X86_REG_ESP) - STACK


def audit():
    native, candidate = code_bodies()
    for states, flip in CASES:
        expected = execute(native, states, flip)
        observed = execute(candidate, states, flip)
        retained = [i for i, state in enumerate(states) if state and i not in flip]
        expected_events = []
        for index, state in enumerate(states):
            expected_events.append(('update', index))
            if not state or index in flip:
                expected_events.extend((('release', 4, 0x100 + index), ('delete', index)))
        if (expected != observed or observed[0] != expected_events
                or observed[1:] != (retained, len(retained), 12)):
            raise ValueError(f'native/source tracked update differs for {states}, {flip}')
    return {'cases': len(CASES), 'result': 'bounded_traces_agree',
            'limitations': 'controlled member callback, handle release and node free; no real game objects or failure paths'}

if __name__ == '__main__':
    print(json.dumps(audit(), indent=2))
