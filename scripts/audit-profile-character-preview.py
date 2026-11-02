#!/usr/bin/env python3
"""Complete preview policy and bounded call-boundary observations, not exact credit."""
from collections import Counter
import importlib.util
import json
from pathlib import Path
import struct
import capstone
from unicorn import Uc, UC_ARCH_X86, UC_MODE_32, UC_HOOK_CODE, UC_HOOK_MEM_WRITE
from unicorn.x86_const import *
import linked_pe as core
from linked_logic_error_origins import require, digest
from native_callbacks import guarded_callback
spec = importlib.util.spec_from_file_location('profile_preview_helpers', Path(__file__).with_name('audit-ctile-real-owner.py'))
h = importlib.util.module_from_spec(spec)
spec.loader.exec_module(h)
ADDRESS, SIZE = 0x4484f0, 178
UNIT = 'exact-first-profile-character-preview'
OWNER, NAME = 0x200000, 0x202000
STACK, SP, RETURN, FORMATTER = 0x300000, 0x30fe00, 0x500000, 0x500100
COOKIE, FORMAT, TABLE = 0x13572468, 0x6c0c00, 0x6c0668
FORMAT_BYTES = b'data/stand/%s.bmp\0'
NAME_BYTES = b'probe_character\0'
PATH_BYTES = b'data/stand/probe_character.bmp\0'
REGS = [UC_X86_REG_EBX, UC_X86_REG_EBP, UC_X86_REG_ESI, UC_X86_REG_EDI]
SAVED = [0x11223344, 0x22334455, 0x33445566, 0x44556677]
EXPECTED_CALLS = {0x404d70:1, 0x43bf80:1, 0x404c90:1, 0x689d25:1}
CASES = [dict(old_handle=a, character=b, loaded=c) for a,b,c in [
    (0,-1,0), (0x12345678,-1,0), (0,0,0), (0x76543210,7,0),
    (0x12345678,0,0x1234), (0xf1234567,15,0xf0000000)]]


def check_contract(calls, indirect, writes, returns):
    require(calls == EXPECTED_CALLS and indirect == 3, 'preview helper/virtual call inventory differs')
    require(writes == [(4,4),(4,4)] and returns == [0], 'preview handle width or RET0 differs')


def cfg(code):
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    instructions = list(md.disasm(code, ADDRESS))
    require(sum(i.size for i in instructions) == len(code), 'preview partial instruction')
    closed = core.decode_closed_body(code, ADDRESS)
    calls, indirect, writes, returns = Counter(), 0, [], []
    for i in instructions:
        if i.group(capstone.CS_GRP_CALL):
            if i.operands[0].type == capstone.x86.X86_OP_IMM:
                calls[i.operands[0].imm] += 1
            else:
                indirect += 1
        if i.group(capstone.CS_GRP_RET):
            returns.append(i.operands[0].imm if i.operands else 0)
        if i.id == capstone.x86.X86_INS_MOV and i.operands[0].type == capstone.x86.X86_OP_MEM:
            op = i.operands[0]
            if op.mem.base == capstone.x86.X86_REG_ESI and op.mem.index == 0 and op.mem.disp == 4:
                writes.append((op.mem.disp, op.size))
    check_contract(dict(calls), indirect, writes, returns)
    return dict(instructions=len(closed), direct_calls={hex(a):n for a,n in calls.items()}, indirect_calls=indirect, handle_writes=writes, returns=returns)


def check_result(case, result):
    expected = [('release',case['old_handle'])]
    writes = [(4,4,0)]
    handle = 0
    if case['character'] != -1:
        expected += [('name',case['character']),('format',PATH_BYTES[:-1].decode()),('load',PATH_BYTES[:-1].decode(),0,0)]
        handle = case['loaded']
        writes.append((4,4,handle))
        if handle:
            expected += [('texture',handle,0,0,512,480),('color',0xff808080)]
    require(result['calls'] == expected, 'preview branch policy or arguments differ')
    require(result['writes'] == writes and result['texture'] == handle and result['cookie_checks'] == 1, 'preview publication or cookie check differs')


def observe(code, case, table):
    uc = Uc(UC_ARCH_X86, UC_MODE_32)
    uc.mem_map(0x400000,0x400000)
    uc.mem_map(OWNER,0x10000)
    uc.mem_map(STACK,0x10000)
    uc.mem_write(ADDRESS,code)
    uc.mem_write(0x6f7a88,struct.pack('<I',COOKIE))
    uc.mem_write(FORMAT,FORMAT_BYTES)
    uc.mem_write(TABLE,table)
    uc.mem_write(0x6c01d8,struct.pack('<I',FORMATTER))
    uc.mem_write(NAME,NAME_BYTES)
    owner = bytearray([0xa5]*0x288)
    struct.pack_into('<I',owner,4,case['old_handle'])
    struct.pack_into('<I',owner,8,TABLE)
    struct.pack_into('<I',owner,0xa0,case['character'] & 0xffffffff)
    uc.mem_write(OWNER,bytes(owner))
    uc.mem_write(SP,struct.pack('<I',RETURN))
    uc.reg_write(UC_X86_REG_ESP,SP)
    uc.reg_write(UC_X86_REG_ECX,OWNER)
    for reg,value in zip(REGS,SAVED):
        uc.reg_write(reg,value)
    md = capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
    expected = {i.address:bytes(i.bytes) for i in md.disasm(code,ADDRESS)}
    errors, calls, writes = [], [], []
    state = dict(cookie_checks=0)

    def word(at):
        return struct.unpack('<I',uc.mem_read(at,4))[0]

    def string(at,limit=260):
        data = bytes(uc.mem_read(at,limit))
        require(b'\0' in data,'preview missing string terminator')
        return data[:data.index(0)]

    def finish(purge, value=0x5a5acafe):
        esp = uc.reg_read(UC_X86_REG_ESP)
        ret = word(esp)
        uc.reg_write(UC_X86_REG_ESP,esp+4+purge)
        uc.reg_write(UC_X86_REG_EIP,ret)
        for reg,x in [(UC_X86_REG_EAX,value),(UC_X86_REG_ECX,0xcccccccc),(UC_X86_REG_EDX,0xdddddddd),(UC_X86_REG_EFLAGS,0x246)]:
            uc.reg_write(reg,x)

    def instruction(engine,at,size,unused):
        esp = engine.reg_read(UC_X86_REG_ESP)
        ecx = engine.reg_read(UC_X86_REG_ECX)
        if at == 0x404d70:
            require(ecx == 0x702798 and word(OWNER+4) == case['old_handle'],'preview wrong release receiver/state')
            calls.append(('release',word(esp+4)))
            finish(4)
        elif at == 0x43bf80:
            require(word(OWNER+4) == 0,'preview handle not cleared before name helper')
            calls.append(('name',word(esp+4)))
            finish(0,NAME)
        elif at == FORMATTER:
            dest,fmt,name = [word(esp+x) for x in [4,8,12]]
            require(STACK <= dest and dest+260 <= STACK+0x10000 and fmt == FORMAT and name == NAME,'preview formatter arguments differ')
            require(string(fmt,32) == FORMAT_BYTES[:-1] and string(name,32) == NAME_BYTES[:-1],'preview fixture strings differ')
            engine.mem_write(dest,PATH_BYTES)
            calls.append(('format',PATH_BYTES[:-1].decode()))
            finish(0,len(PATH_BYTES)-1)
        elif at == 0x404c90:
            out,path,width,height = [word(esp+x) for x in [4,8,12,16]]
            require(ecx == 0x702798 and STACK <= out < STACK+0x10000-4 and word(OWNER+4) == 0,'preview loader receiver/output differs')
            calls.append(('load',string(path).decode(),width,height))
            engine.mem_write(out,struct.pack('<I',case['loaded']))
            finish(16,out)
        elif at == 0x406a60:
            require(ecx == OWNER+8,'preview wrong sprite receiver')
            calls.append(('texture',*[word(esp+x) for x in [4,8,12,16,20]]))
            finish(20)
        elif at == 0x40ac50:
            require(ecx == OWNER+8,'preview wrong color receiver')
            calls.append(('color',word(esp+4)))
            finish(4)
        elif at == 0x689d25:
            require(ecx == COOKIE,'preview GS cookie differs')
            state['cookie_checks'] += 1
            finish(0)
        else:
            require(at in expected and bytes(engine.mem_read(at,size)) == expected[at],'preview unknown instruction/helper')

    def write(engine,access,at,size,value,unused):
        if STACK <= at and at+size <= STACK+0x10000:
            return
        require(at == OWNER+4 and size == 4,'preview unexpected owner write')
        writes.append((at-OWNER,size,value & 0xffffffff))

    uc.hook_add(UC_HOOK_CODE,guarded_callback(instruction,errors))
    uc.hook_add(UC_HOOK_MEM_WRITE,guarded_callback(write,errors))
    uc.emu_start(ADDRESS,RETURN,count=300)
    require(not errors,'preview callback rejected: '+'; '.join(errors))
    require(uc.reg_read(UC_X86_REG_EIP) == RETURN and uc.reg_read(UC_X86_REG_ESP) == SP+4,'preview RET0 stack contract differs')
    require([uc.reg_read(r) for r in REGS] == SAVED,'preview nonvolatile contract differs')
    result = dict(calls=calls,writes=writes,texture=word(OWNER+4),cookie_checks=state['cookie_checks'])
    check_result(case,result)
    struct.pack_into('<I',owner,4,result['texture'])
    require(bytes(uc.mem_read(OWNER,0x288)) == bytes(owner),'preview other owner state changed')
    return result


def audit():
    c = core.comparator()
    sha = c.verify_target()
    native = c.target_bytes(ADDRESS,SIZE)
    require(digest(native) == '1afe0ad43b693c126df82a1725c72af49dd16db7f1a08ec8be9695bdf712a4a9','preview native whole body differs')
    u,p = h.fresh(UNIT)
    source = h.canonical(c,u,p,u['functions'][0])
    require(len(source) == SIZE,'preview full candidate extent differs')
    native_cfg,source_cfg = cfg(native),cfg(source)
    require(c.target_bytes(FORMAT,len(FORMAT_BYTES)) == FORMAT_BYTES,'preview pooled path format differs')
    table = c.target_bytes(TABLE,36)
    require(struct.unpack_from('<I',table,20)[0] == 0x406a60 and struct.unpack_from('<I',table,4)[0] == 0x40ac50,'preview actual sprite virtual roles differ')
    parents = []
    for name,at,site in [('gpt-web-profile-character-select-constructor',0x4487e0,0x4489fe),('gpt-web-profile-character-select-update',0x4485b0,0x4486eb)]:
        pu,pp = h.fresh(name)
        body = h.canonical(c,pu,pp,pu['functions'][0])
        require(body == c.target_bytes(at,len(body)),'preview parent whole body differs')
        call = body[site-at:site-at+5]
        require(call[0] == 0xe8 and site+5+struct.unpack_from('<i',call,1)[0] == ADDRESS,'preview direct owner edge differs')
        parents.append(dict(address=hex(at),size=len(body),call_site=hex(site),sha256=digest(body)))
    cases = []
    for case in CASES:
        expected,actual = observe(native,case,table),observe(source,case,table)
        require(actual == expected,'preview finite native/source observations differ')
        cases.append(dict(case=case,observation=actual))
    needle = bytes.fromhex('c7460400000000')
    require(source.count(needle) == 1,'preview clear-store encoding differs')
    bad = bytearray(source)
    bad[source.index(needle)+2] = 12
    try:
        observe(bytes(bad),CASES[1],table)
    except ValueError as error:
        require('unexpected owner write' in str(error),'unexpected preview negative-control failure')
    else:
        raise ValueError('preview wrong-field control accepted')
    return dict(diagnostic_only=True,exact=source == native,target_sha256=sha,native_sha256=digest(native),candidate_sha256=digest(source),source_size=len(source),unequal_bytes=sum(a!=b for a,b in zip(source,native)),first_mismatch=c.first_mismatch(native,source,ADDRESS),native_cfg=native_cfg,source_cfg=source_cfg,parents=parents,isolated_cases=cases,wrong_field_rejected=True,scope='six finite call-boundary fixtures with modeled helper returns and noisy volatile registers; no actual name lookup, resource loading, formatting, sprite helper, OS execution, concurrency or universal equivalence claim; differing whole body receives no exact credit')


if __name__ == '__main__':
    print(json.dumps(audit(),indent=2))
