#!/usr/bin/env python3
"""Whole server input policy CFG/ABI diagnostic, not behavioral or exact credit."""
from collections import Counter
import importlib.util
import json
from pathlib import Path
import struct
import capstone
import linked_pe as core
from linked_logic_error_origins import require, digest
spec = importlib.util.spec_from_file_location('server_input_helpers', Path(__file__).with_name('audit-ctile-real-owner.py'))
h = importlib.util.module_from_spec(spec)
spec.loader.exec_module(h)
ADDRESS, SIZE = 0x44f9a0, 409
UNIT = 'gpt-web-network-primary-packet-continuation'
EXPECTED_CALLS = {0x40ac30:2, 0x416b60:2, 0x42a4b0:2, 0x42aa90:2, 0x40ac40:1}


def check_contract(calls, indirect, tails, writes, masks, returns):
    require(calls == EXPECTED_CALLS and indirect == 3, 'server direct/virtual call inventory differs')
    require(tails == [0x40ac40,0x40ac40] and returns == [], 'server both exits must tail-leave the outer critical section')
    require(writes == [(0x7c,2),(0x98,4)] and masks == [0x3ff], 'server input width/mask or sequence publication differs')


def cfg(code):
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    instructions = list(md.disasm(code,ADDRESS))
    require(sum(i.size for i in instructions) == len(code), 'server partial instruction')
    tails = {i.address:i.operands[0].imm for i in instructions if i.id == capstone.x86.X86_INS_JMP and i.operands[0].type == capstone.x86.X86_OP_IMM and not ADDRESS <= i.operands[0].imm < ADDRESS+len(code)}
    closed = core.decode_closed_body(code,ADDRESS,tail=True,external_exits=tails)
    calls, indirect, writes, masks, returns = Counter(),0,[],[],[]
    for i in instructions:
        if i.group(capstone.CS_GRP_CALL):
            if i.operands[0].type == capstone.x86.X86_OP_IMM:
                calls[i.operands[0].imm] += 1
            else:
                indirect += 1
        if i.group(capstone.CS_GRP_RET):
            returns.append(i.address)
        if i.id == capstone.x86.X86_INS_MOV and i.operands[0].type == capstone.x86.X86_OP_MEM:
            op = i.operands[0]
            if op.mem.base == capstone.x86.X86_REG_ESI and op.mem.index == 0 and op.mem.disp in (0x7c,0x98):
                writes.append((op.mem.disp,op.size))
        if i.id == capstone.x86.X86_INS_AND and i.operands[0].size == 2 and i.operands[1].type == capstone.x86.X86_OP_IMM:
            masks.append(i.operands[1].imm)
    check_contract(dict(calls),indirect,list(tails.values()),sorted(writes),masks,returns)
    return dict(instructions=len(closed),direct_calls={hex(a):n for a,n in calls.items()},indirect_calls=indirect,tail_exits={hex(a):hex(b) for a,b in tails.items()},published_fields=sorted(writes),input_masks=masks)


def audit():
    c = core.comparator()
    sha = c.verify_target()
    native = c.target_bytes(ADDRESS,SIZE)
    u,p = h.fresh(UNIT)
    f = next(f for f in u['functions'] if int(f['address'],0) == ADDRESS)
    source = h.canonical(c,u,p,f)
    target_cfg, source_cfg = cfg(native),cfg(source)
    require(struct.unpack('<I',c.target_bytes(0x6c1708,4))[0] == ADDRESS and struct.unpack('<I',c.target_bytes(0x6c1720,4))[0] == 0x44f550, 'server publication/adaptive virtual identities differ')
    af = next(f for f in u['functions'] if int(f['address'],0) == 0x44f550)
    adaptive = h.canonical(c,u,p,af)
    require(len(adaptive) == 162 and adaptive == c.target_bytes(0x44f550,162), 'server actual adaptive helper differs')
    md = capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
    md.detail = True
    helpers = []
    for at,size,purge in [(0x416b60,548,20),(0x42a4b0,122,4),(0x42aa90,119,4)]:
        body = c.target_bytes(at,size)
        ins = list(md.disasm(body,at))
        require(sum(i.size for i in ins) == size, 'server helper partial instruction')
        rets = [i for i in ins if i.group(capstone.CS_GRP_RET)]
        require(rets and all(len(i.operands) == 1 and i.operands[0].imm == purge for i in rets), 'server helper stack cleanup differs')
        helpers.append(dict(address=hex(at),size=size,ret_cleanup=purge,sha256=digest(body),source_exactness_claimed=False))
    return dict(target_sha256=sha,native_size=SIZE,source_size=len(source),native_sha256=digest(native),candidate_sha256=digest(source),first_mismatch=c.first_mismatch(native,source,ADDRESS),exact=False,native_cfg=target_cfg,source_cfg=source_cfg,adaptive_exact=dict(address='0x0044F550',size=162,sha256=digest(adaptive)),helper_abi=helpers,scope='complete CFG/call/tail/field-width evidence only; no helper execution, packet/network/lock runtime, behavioral equivalence, normalized-byte or new exactness claim')


if __name__ == '__main__':
    print(json.dumps(audit(),indent=2))
