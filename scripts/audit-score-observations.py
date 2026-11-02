#!/usr/bin/env python3
"""Bounded signed-maximum diagnostic, not a canonical exactness receipt."""
import hashlib
import json
import struct
import capstone
from unicorn import Uc, UC_ARCH_X86, UC_MODE_32, UC_HOOK_CODE, UC_HOOK_MEM_WRITE
from unicorn.x86_const import *
import linked_pe as core
from native_callbacks import guarded_callback
from workflow_manifest import ROOT, load_manifest, unit_input_digest, compiler_sha256
from linked_logic_error_origins import require

ADDRESS, SIZE = 0x42d010, 191
UNIT = 'gpt-web-score-observations'
OWNER, RECORDS, STACK, SP, RETURN = 0x200000, 0x208000, 0x300000, 0x30fe00, 0x400000
SAVED = [UC_X86_REG_EBX, UC_X86_REG_EBP, UC_X86_REG_ESI, UC_X86_REG_EDI]
VALUES = [0x11223344, 0x22334455, 0x33445566, 0x44556677]


def observe(code, getters, case):
    uc = Uc(UC_ARCH_X86, UC_MODE_32)
    uc.mem_map(0x400000, 0x300000)
    uc.mem_map(OWNER, 0x10000)
    uc.mem_map(STACK, 0x10000)
    uc.mem_write(ADDRESS, code)
    for at, data in getters.items():
        uc.mem_write(at, data)
    uc.mem_write(0x6fbd4c, struct.pack('<I', case.get('mode', 0)))
    uc.mem_write(0x6fbd44, struct.pack('<I', case.get('setup', 0)))
    before = b''.join(struct.pack('<6i', 11, 99, 22, 33, 7, case['stored']) for _ in range(2))
    uc.mem_write(RECORDS, before)
    count = case.get('count', 2)
    selector = case.get('selector', 0)
    uc.mem_write(OWNER + 0x198 + selector * 16, struct.pack('<4I', 0, RECORDS, RECORDS + count * 24, RECORDS + 48))
    key = case.get('key', 11)
    uc.mem_write(SP, struct.pack('<5I', RETURN, selector, key, 22, case['value'] & 0xffffffff))
    uc.reg_write(UC_X86_REG_ESP, SP)
    uc.reg_write(UC_X86_REG_ECX, OWNER)
    for reg, value in zip(SAVED, VALUES):
        uc.reg_write(reg, value)
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    expected = {i.address: bytes(i.bytes) for at, data in [(ADDRESS, code), *getters.items()] for i in md.disasm(data, at)}
    require(sum(len(v) for a, v in expected.items() if ADDRESS <= a < ADDRESS + len(code)) == len(code), 'partial source instruction')
    errors, calls = [], []

    def instruction(engine, at, size, unused):
        require(at in expected and bytes(engine.mem_read(at, size)) == expected[at], 'unknown instruction/helper')
        if at in getters:
            calls.append(hex(at))

    def write(engine, access, at, size, value, unused):
        require(STACK <= at and at + size <= STACK + 0x10000 or size == 4 and at in (RECORDS + 16, RECORDS + 20), 'unexpected record/owner write')

    uc.hook_add(UC_HOOK_CODE, guarded_callback(instruction, errors))
    uc.hook_add(UC_HOOK_MEM_WRITE, guarded_callback(write, errors))
    uc.emu_start(ADDRESS, RETURN, count=2000)
    require(not errors, 'callback rejected: ' + '; '.join(errors))
    require(uc.reg_read(UC_X86_REG_EIP) == RETURN and uc.reg_read(UC_X86_REG_ESP) == SP + 20, 'RET16 contract differs')
    require([uc.reg_read(r) for r in SAVED] == VALUES, 'callee-save contract differs')
    return dict(records=bytes(uc.mem_read(RECORDS, 48)).hex(), calls=calls)


def audit():
    c = core.comparator()
    sha = c.verify_target()
    native = c.target_bytes(ADDRESS, SIZE)
    require(native[0xa2:0xab] == bytes.fromhex('8b5c24203b5e147e0d'), 'native signed maximum comparison differs')
    require(native[0x4d:0x56] == bytes.fromhex('3bff7405e8') + struct.pack('<i', 0x68a143 - 0x42d066), 'native iterator self-compatibility sequence differs')
    u = load_manifest()['units'][UNIT]
    p = ROOT / u['object']
    provenance = json.loads(p.with_suffix(p.suffix + '.provenance.json').read_text())
    digest, _ = unit_input_digest(UNIT, u)
    require(provenance['input_digest'] == digest and provenance['object_sha256'] == core.sha(p) and provenance['compiler_sha256'] == compiler_sha256(), 'fresh source build required')
    f = u['functions'][0]
    calls = c.known_targets() | {n: int(a, 0) for n, a in (x.rsplit('=', 1) for x in f['rel32_targets'])}
    source = c.coff_symbol_bytes(p, f['symbol_base'], ADDRESS, 0xffffffff, calls, c.known_data_targets(), {})
    require(len(source) == 182, 'source whole extent differs')
    getters = {at: c.target_bytes(at, 6) for at in (0x43ac40, 0x43b070)}
    require(getters == {0x43ac40: bytes.fromhex('a14cbd6f00c3'), 0x43b070: bytes.fromhex('a144bd6f00c3')}, 'actual native getters differ')
    cases = [dict(stored=a, value=b) for a, b in [(10, 5), (10, 15), (10, 10), (-10, -15), (-10, -5), (0, -1), (0, 1), (2147483647, -2147483648)]]
    cases += [dict(stored=10, value=5, **extra) for extra in [dict(mode=1), dict(setup=2), dict(count=0), dict(key=99), dict(selector=14)]]
    reports = []
    for case in cases:
        target, actual = observe(native, getters, case), observe(source, getters, case)
        require(target == actual, 'source/native finite observation differs')
        active = case.get('mode', 0) == 0 and case.get('setup', 0) != 2 and case.get('count', 2) > 0 and case.get('key', 11) == 11
        record = struct.unpack('<12i', bytes.fromhex(target['records']))
        require(record[4] == 7 + int(active) and record[5] == (max(case['stored'], case['value']) if active else case['stored']), 'signed maximum/count differs')
        require(record[10:] == (7, case['stored']), 'duplicate record was changed')
        reports.append(dict(case=case, observation=actual))
    # The inverted JLE must observably disagree, not silently pass this diagnostic.
    old = bytearray(source)
    require(old[0xa0:0xa2] == bytes.fromhex('7d0d'), 'source maximum branch differs')
    old[0xa0] = 0x7e
    require(observe(bytes(old), getters, cases[0]) != observe(native, getters, cases[0]), 'inverted minimum logic escaped negative control')
    return dict(target_sha256=sha, native_sha256=hashlib.sha256(native).hexdigest(), source_sha256=hashlib.sha256(source).hexdigest(), native_size=SIZE, source_size=len(source), exact=False, cases=reports, inverted_minimum_rejected=True, scope='13 finite normal-path cases; actual native getters, RET16 and callee saves; no malformed-vector continuation, OS calls or universal equivalence claim; missing nine-byte iterator self-compatibility check remains')


if __name__ == '__main__':
    print(json.dumps(audit(), indent=2))
