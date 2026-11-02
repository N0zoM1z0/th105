#!/usr/bin/env python3
"""Complete ACK-tail source/target comparison and finite lock-boundary observations."""
import importlib.util
import json
from pathlib import Path
import struct
import capstone
import pefile
from unicorn import Uc, UC_ARCH_X86, UC_MODE_32, UC_HOOK_CODE, UC_HOOK_MEM_WRITE
from unicorn.x86_const import *
import linked_pe as core
from linked_logic_error_origins import require, digest
from native_callbacks import guarded_callback
spec = importlib.util.spec_from_file_location('ack_owner_helpers', Path(__file__).with_name('audit-ctile-real-owner.py'))
h = importlib.util.module_from_spec(spec)
spec.loader.exec_module(h)
ADDRESS, SIZE = 0x44e6d0, 78
UNIT = 'gpt-web-network-primary-packet-continuation'
OWNER, SNAPSHOT, LOCAL, REMOTE = 0x200000, 0x201000, 0x202000, 0x203000
STACK, SP, RETURN = 0x300000, 0x30fe00, 0x500000
REGS = [UC_X86_REG_EBX, UC_X86_REG_EBP, UC_X86_REG_ESI, UC_X86_REG_EDI]
SAVED = [0x11223344, 0x22334455, 0x33445566, 0x44556677]
CASES = [dict(peer=a, side0=b, side1=d, alias=alias) for a,b,d,alias in [(0,0,0,False),(1,2,3,False),(255,128,127,False),(128,255,0,False),(85,170,255,True),(255,255,255,True)]]


def check_snapshot_owners(server_type, client_type, server_slots, client_slots):
    require(server_type == '.?AVCNetworkServer@@' and client_type == '.?AVCNetworkClient@@', 'snapshot primary RTTI owners differ')
    require(server_slots == (0x44fd80,0x44ffe0) and client_slots == (0x44e6d0,0x44f390), 'snapshot import/export virtual roles differ')


def check_result(case, result):
    require(result['calls'] == ['enter', 'leave'], 'ACK lock order differs')
    require(result['values'] == [case['peer'], case['side0'], case['side1'], 1], 'ACK byte publication differs')
    require(result['snapshot_unchanged'] and result['local_unchanged'], 'ACK source changed')


def observe(code, case):
    uc = Uc(UC_ARCH_X86, UC_MODE_32)
    uc.mem_map(0x400000, 0x100000)
    uc.mem_map(RETURN, 0x1000)
    uc.mem_map(OWNER, 0x10000)
    uc.mem_map(STACK, 0x10000)
    uc.mem_write(ADDRESS, code)
    uc.mem_write(OWNER, bytes([0xa5]) * 0x700)
    remote = LOCAL if case['alias'] else REMOTE
    uc.mem_write(OWNER+0x200, struct.pack('<I', LOCAL))
    uc.mem_write(OWNER+0x250, struct.pack('<I', remote))
    uc.mem_write(OWNER+0x3a6, b'\0')
    snapshot = bytearray([0x66] * 0x4c)
    # Model both unused native deque headers as empty, not serialized bytes.
    snapshot[0x10:0x24] = bytes(20)
    snapshot[0x30:0x44] = bytes(20)
    snapshot[0x0e], snapshot[0x2e] = case['side0'], case['side1']
    uc.mem_write(SNAPSHOT, bytes(snapshot))
    uc.mem_write(LOCAL, bytes([0x55])*8)
    uc.mem_write(LOCAL+4, bytes([case['peer']]))
    if not case['alias']:
        uc.mem_write(REMOTE, bytes([0x77])*8)
    local_before = bytes(uc.mem_read(LOCAL, 8))
    uc.mem_write(SP, struct.pack('<II', RETURN, SNAPSHOT))
    uc.reg_write(UC_X86_REG_ESP, SP)
    uc.reg_write(UC_X86_REG_ECX, OWNER)
    for reg, value in zip(REGS, SAVED):
        uc.reg_write(reg, value)
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    instructions = list(md.disasm(code, ADDRESS))
    require(sum(i.size for i in instructions) == len(code), 'ACK partial instruction')
    expected = {i.address:bytes(i.bytes) for i in instructions}
    errors, calls = [], []
    state = dict(locked=False)
    allowed = {remote+4, OWNER+0x21a, OWNER+0x23a, OWNER+0x3a6}

    def instruction(engine, at, size, unused):
        if at in [0x40ac30, 0x40ac40]:
            require(engine.reg_read(UC_X86_REG_ECX) == OWNER+0x25c, 'ACK wrong critical receiver')
            entering = at == 0x40ac30
            require(state['locked'] != entering, 'ACK repeated or unmatched lock call')
            state['locked'] = entering
            calls.append('enter' if entering else 'leave')
            esp = engine.reg_read(UC_X86_REG_ESP)
            ret = struct.unpack('<I', engine.mem_read(esp, 4))[0]
            engine.reg_write(UC_X86_REG_ESP, esp+4)
            engine.reg_write(UC_X86_REG_EIP, ret)
            for reg, value in [(UC_X86_REG_EAX,0x5a5acafe),(UC_X86_REG_ECX,0xcccccccc),(UC_X86_REG_EDX,0xdddddddd),(UC_X86_REG_EFLAGS,0x202)]:
                engine.reg_write(reg, value)
            return
        require(at in expected and bytes(engine.mem_read(at,size)) == expected[at], 'ACK unknown instruction/helper')

    def write(engine, access, at, size, value, unused):
        if STACK <= at and at+size <= STACK+0x10000:
            return
        require(state['locked'] and size == 1 and at in allowed, 'ACK unexpected or unlocked write')

    uc.hook_add(UC_HOOK_CODE, guarded_callback(instruction, errors))
    uc.hook_add(UC_HOOK_MEM_WRITE, guarded_callback(write, errors))
    uc.emu_start(ADDRESS, RETURN, count=200)
    require(not errors, 'ACK callback rejected: ' + '; '.join(errors))
    require(uc.reg_read(UC_X86_REG_EIP) == RETURN and uc.reg_read(UC_X86_REG_ESP) == SP+8, 'ACK RET4 contract differs')
    require([uc.reg_read(r) for r in REGS] == SAVED and not state['locked'], 'ACK nonvolatile or unlock contract differs')
    result = dict(calls=calls, values=[uc.mem_read(a,1)[0] for a in [remote+4,OWNER+0x21a,OWNER+0x23a,OWNER+0x3a6]], snapshot_unchanged=bytes(uc.mem_read(SNAPSHOT,0x4c)) == bytes(snapshot), local_unchanged=bytes(uc.mem_read(LOCAL,8)) == local_before, owner_sha256=digest(uc.mem_read(OWNER,0x700)), peer_sha256=digest(uc.mem_read(remote,8)))
    check_result(case, result)
    return result


def audit():
    c = core.comparator()
    sha = c.verify_target()
    native = c.target_bytes(ADDRESS, SIZE)
    game = pefile.PE(str(c.TARGET))
    server_slots = struct.unpack('<2I', core.readonly_data(game,0x6c16f4,8))
    client_slots = struct.unpack('<2I', core.readonly_data(game,0x6c175c,8))
    check_snapshot_owners(core.primary_type_name(game,0x6c16ec),core.primary_type_name(game,0x6c1754),server_slots,client_slots)
    require(digest(native) == 'd0c302e135a6cab0a56a6b33b09a5f53b6d0544dd69d77e4db6697a17aee9cc0', 'ACK complete native body differs')
    u,p = h.fresh(UNIT)
    f = next(f for f in u['functions'] if int(f['address'],0) == ADDRESS)
    source = h.canonical(c,u,p,f)
    require(len(source) == SIZE, 'ACK source full extent differs')
    for body in [native,source]:
        instructions = core.decode_closed_body(body,ADDRESS)
        require(len(instructions) == 21 and body[-3:] == b'\xc2\x04\x00', 'ACK whole CFG/RET4 differs')
    support = []
    cu,cp = h.fresh('cross-v106a-critical-section-wrapper')
    for at in [0x40ac30,0x40ac40]:
        cf = next(f for f in cu['functions'] if int(f['address'],0) == at)
        cb = h.canonical(c,cu,cp,cf)
        require(len(cb) == 11 and cb == c.target_bytes(at,11), 'ACK actual critical helper differs')
        support.append(dict(address=hex(at),size=11,sha256=digest(cb)))
    cases = []
    for case in CASES:
        target, actual = observe(native,case), observe(source,case)
        require(target == actual, 'ACK finite native/source observation differs')
        cases.append(dict(case=case,observation=actual))
    bad = bytearray(source)
    needle = bytes.fromhex('888e1a020000')
    require(source.count(needle) == 1, 'ACK side0 publication encoding differs')
    bad[source.index(needle)+2] ^= 1
    rejected = False
    try:
        observe(bytes(bad),CASES[0])
    except ValueError as error:
        rejected = 'unexpected or unlocked write' in str(error)
    require(rejected, 'ACK wrong-field negative escaped')
    return dict(target_sha256=sha, source_size=SIZE, candidate_sha256=digest(source), native_sha256=digest(native), unequal_bytes=sum(a!=b for a,b in zip(source,native)), first_mismatch=c.first_mismatch(native,source,ADDRESS), exact=source==native, support=support, snapshot_owners=dict(server_slots=server_slots,client_slots=client_slots), cases=cases, wrong_field_rejected=True, scope='six finite lock-boundary cases including equal peer pointers; full RET4/nonvolatile and write footprint; helper calls intercepted, no OS locks/network/gameplay execution or universal equivalence claim')


if __name__ == '__main__':
    print(json.dumps(audit(),indent=2))
