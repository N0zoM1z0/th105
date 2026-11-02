#!/usr/bin/env python3
"""Bounded CSprite query-return observations; differing bodies receive no exact credit."""
import sys, json, struct, collections
from pathlib import Path
sys.path.insert(0, 'scripts')
import capstone, pefile
from unicorn import Uc, UC_ARCH_X86, UC_MODE_32, UC_HOOK_CODE, UC_HOOK_MEM_WRITE
from unicorn.x86_const import *
import linked_pe as core
from linked_logic_error_origins import require, digest
from native_callbacks import guarded_callback
ADDRESS, SIZE, OWNER, STACK, SP, RETURN = (4221584, 334, 2097152, 3145728, 3210752, 5242880)
REGS = [UC_X86_REG_EBX, UC_X86_REG_EBP, UC_X86_REG_ESI, UC_X86_REG_EDI]
SAVED = [287454020, 573785173, 860116326, 1146447479]
CASES = [dict(zip(['handle', 'x', 'y', 'width', 'height', 'pivot_x', 'pivot_y', 'texture_width', 'texture_height'], x)) for x in [(0, 0, 0, 640, 480, 0, 0, 256, 256), (4045620583, 7, 11, 83, 37, -12, 9, 512, 256), (4660, -17, 23, 120, -8, 60, -4, 257, 129), (1, 0, 1024, 16, 16, 8, 8, 1024, 4096), (22136, 19, -31, -9, 22, -3, 17, 2147483649, 4026531841), (4294967295, -300, -120, 512, 480, 256, 240, 320, 240)]]
FIELDS = {4, 120, 124, 128, 132, 136, 140, 144} | {8 + i * 28 + j for i in range(4) for j in [8, 12, 16, 20, 24]}

def initial():
    b = bytearray([165] * 148)
    struct.pack_into('<I', b, 0, 7079528)
    return b

def expected(case):
    b = initial()
    struct.pack_into('<I', b, 4, case['handle'])
    uv = [(case['x'] / case['texture_width'], case['y'] / case['texture_height']), ((case['x'] + case['width']) / case['texture_width'], case['y'] / case['texture_height']), (case['x'] / case['texture_width'], (case['y'] + case['height']) / case['texture_height']), ((case['x'] + case['width']) / case['texture_width'], (case['y'] + case['height']) / case['texture_height'])]
    for i, (u, v) in enumerate(uv):
        struct.pack_into('<ffIff', b, 8 + i * 28 + 8, 0.5, 1.0, 4294967295, u, v)
    struct.pack_into('<7f', b, 120, case['width'], case['height'], case['pivot_x'], case['pivot_y'], 1.0, 1.0, 0.0)
    return bytes(b)

def check_result(case, result):
    require(bytes.fromhex(result['state']) == expected(case), 'sprite output or preserved fields differ')
    require(result['query_handles'] == [case['handle']], 'size-query arguments/count differ')
    require(sorted(result['writes']) == sorted(FIELDS) and len(result['writes']) == 28, 'sprite write footprint differs')

def cfg(code):
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    xs = list(md.disasm(code, ADDRESS))
    require(sum((x.size for x in xs)) == len(code), 'partial instruction')
    closed = core.decode_closed_body(code, ADDRESS)
    calls = collections.Counter()
    indirect = 0
    returns = []
    for x in xs:
        if x.group(capstone.CS_GRP_CALL):
            if x.operands[0].type == capstone.x86.X86_OP_IMM:
                calls[x.operands[0].imm] += 1
            else:
                indirect += 1
        if x.group(capstone.CS_GRP_RET):
            returns.append(x.operands[0].imm if x.operands else 0)
    require(calls == {4214368: 1} and indirect == 0 and (returns == [28]), 'query/RET contract differs')
    return dict(instructions=len(closed), calls={hex(k): v for k, v in calls.items()}, returns=returns)

def observe(c, code, case):
    uc = Uc(UC_ARCH_X86, UC_MODE_32)
    uc.mem_map(4194304, 4194304)
    uc.mem_map(OWNER, 65536)
    uc.mem_map(STACK, 65536)
    game = pefile.PE(str(c.TARGET))
    for s in game.sections:
        if s.SizeOfRawData:
            uc.mem_write(game.OPTIONAL_HEADER.ImageBase + s.VirtualAddress, s.get_data())
    uc.mem_write(ADDRESS, code)
    uc.mem_write(OWNER, bytes(initial()))
    uc.mem_write(SP, struct.pack('<8I', RETURN, *[case[k] & 4294967295 for k in ['handle', 'x', 'y', 'width', 'height', 'pivot_x', 'pivot_y']]))
    uc.reg_write(UC_X86_REG_ESP, SP)
    uc.reg_write(UC_X86_REG_ECX, OWNER)
    uc.reg_write(UC_X86_REG_FPCW, 895)
    for reg, val in zip(REGS, SAVED):
        uc.reg_write(reg, val)
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    ins = {x.address: bytes(x.bytes) for x in md.disasm(code, ADDRESS)}
    errors = []
    queries = []
    writes = []

    def word(at):
        return struct.unpack('<I', uc.mem_read(at, 4))[0]

    def instruction(engine, at, size, user):
        if at == 4214368:
            esp = engine.reg_read(UC_X86_REG_ESP)
            require(engine.reg_read(UC_X86_REG_ECX) == 7350168, 'wrong query receiver')
            handle, w, h = [word(esp + i) for i in [4, 8, 12]]
            require(handle == case['handle'] and word(OWNER + 4) == handle, 'handle publication/query differs')
            require(bytes(engine.mem_read(OWNER + 120, 16)) == struct.pack('<4f', *[case[k] for k in ['width', 'height', 'pivot_x', 'pivot_y']]), 'dimensions/pivots not published before query')
            require(w != h and all((STACK <= a <= STACK + 65536 - 4 for a in [w, h])), 'query outputs outside real stack storage')
            queries.append(handle)
            engine.mem_write(w, struct.pack('<I', case['texture_width']))
            engine.mem_write(h, struct.pack('<I', case['texture_height']))
            ret = word(esp)
            engine.reg_write(UC_X86_REG_ESP, esp + 16)
            engine.reg_write(UC_X86_REG_EIP, ret)
            for reg, val in [(UC_X86_REG_EAX, 2863311530), (UC_X86_REG_ECX, 3435973836), (UC_X86_REG_EDX, 3722304989), (UC_X86_REG_EFLAGS, 582)]:
                engine.reg_write(reg, val)
        else:
            require(at in ins and bytes(engine.mem_read(at, size)) == ins[at], 'unknown instruction/helper')

    def write(engine, access, at, size, value, user):
        if STACK <= at and at + size <= STACK + 65536:
            return
        require(size == 4 and at - OWNER in FIELDS, 'unexpected object write')
        writes.append(at - OWNER)
    uc.hook_add(UC_HOOK_CODE, guarded_callback(instruction, errors))
    uc.hook_add(UC_HOOK_MEM_WRITE, guarded_callback(write, errors))
    uc.emu_start(ADDRESS, RETURN, count=1000)
    require(not errors, 'callback rejected: ' + str(errors))
    require(uc.reg_read(UC_X86_REG_EIP) == RETURN and uc.reg_read(UC_X86_REG_ESP) == SP + 32, 'RET28 stack contract differs')
    require([uc.reg_read(r) for r in REGS] == SAVED, 'nonvolatile registers differ')
    result = dict(state=bytes(uc.mem_read(OWNER, 148)).hex(), query_handles=queries, writes=writes)
    check_result(case, result)
    return result
if __name__ == '__main__':
    import importlib.util
    spec = importlib.util.spec_from_file_location('sprite_options_helpers', Path(__file__).with_name('audit-ctile-real-owner.py'))
    h = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(h)
    c = core.comparator()
    sha = c.verify_target()
    h.fresh('exact-first-sprite-texture-options')
    u = __import__('tomllib').loads(Path('config/match-units.toml').read_text())['units']['exact-first-sprite-texture-options']
    f = u['functions'][0]
    calls = c.known_targets() | {n: int(a, 0) for n, a in (v.rsplit('=', 1) for v in f['rel32_targets'])}
    source = c.coff_symbol_bytes(Path(u['object']), f['symbol_base'], ADDRESS, 4294967295, calls, c.known_data_targets(), {})
    native = c.target_bytes(ADDRESS, SIZE)
    require(digest(native) == 'cef4fe718e7b4a273a2644a8a1a781a6412fdb70a7e0f8bdd31c27471990e3af', 'target body changed')
    results = []
    for case in CASES:
        a = observe(c, native, case)
        b = observe(c, source, case)
        require(a['state'] == b['state'] and a['query_handles'] == b['query_handles'], 'bounded parity differs')
        results.append(dict(case=case, state_sha256=digest(bytes.fromhex(a['state']))))
    bad = bytearray(source)
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    stores = [i for i in md.disasm(source, ADDRESS) if i.id == capstone.x86.X86_INS_MOV and i.operands[0].type == capstone.x86.X86_OP_MEM and i.operands[0].mem.base == capstone.x86.X86_REG_ESI and i.operands[0].mem.disp == 4]
    require(len(stores) == 1 and stores[0].disp_size == 1, 'handle store encoding differs')
    bad[stores[0].address - ADDRESS + stores[0].disp_offset] = 0
    try:
        observe(c, bytes(bad), CASES[1])
    except ValueError as error:
        require('unexpected object write' in str(error), 'wrong-field negative failed for another reason')
    else:
        raise AssertionError('wrong-field source accepted')
    negative = dict(b, state=bytes(initial()).hex())
    try:
        check_result(CASES[-1], negative)
    except ValueError:
        pass
    else:
        raise AssertionError('wrong output accepted')
    print(json.dumps(dict(target_sha256=sha, native_cfg=cfg(native), source_cfg=cfg(source), source_size=len(source), source_sha256=digest(source), cases=results, negative_rejected=True, scope='six finite texture-query return fixtures; helper/COM/OS not executed, no universal floating-point or alias claim'), indent=2))
