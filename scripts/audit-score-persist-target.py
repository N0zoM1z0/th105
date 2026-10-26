#!/usr/bin/env python3
"""Pin score persistence and observe complete native serialization/write policy."""
import argparse
from collections import Counter
import hashlib
import importlib.util
import json
from pathlib import Path
import struct

import capstone
from capstone import x86
import pefile
from unicorn import Uc, UC_ARCH_X86, UC_MODE_32, UC_HOOK_CODE
from unicorn.x86_const import (UC_X86_REG_EAX, UC_X86_REG_EBX, UC_X86_REG_ECX,
    UC_X86_REG_EDX, UC_X86_REG_EBP, UC_X86_REG_ESI, UC_X86_REG_EDI,
    UC_X86_REG_ESP, UC_X86_REG_EIP)
from workflow_manifest import load_manifest

ROOT = Path(__file__).resolve().parents[1]
ADDRESS, SIZE = 0x42D3F0, 1155
SHA = '7c1f377790ad3439955063dfdfabfd872385eb123a26da7c073baaab491ceb48'
UNIT = 'exact-first-score-persist'


def require(condition, message):
    if not condition:
        raise ValueError(message)


def observe(image, code, case):
    m = Uc(UC_ARCH_X86, UC_MODE_32)
    m.mem_map(0x400000, (len(image) + 4095) & ~4095); m.mem_write(0x400000, image)
    m.mem_write(ADDRESS, code); m.mem_map(0, 0x10000)
    m.mem_map(0x800000, 0x400000); m.mem_map(0x1000000, 0x20000); m.mem_map(0xf00000, 0x1000)
    w = lambda a, v: m.mem_write(a, struct.pack('<I', v & 0xffffffff))
    r = lambda a: struct.unpack('<I', m.mem_read(a, 4))[0]
    pack = lambda values: struct.pack('<' + str(len(values)) + 'I', *(v & 0xffffffff for v in values))
    obj, stack = 0x802000, 0x1010004
    next_node, next_data = [0x806000], [0x900000]
    trees, events, serialized = {}, [], []
    header = pack([0x3456789a] + list(range(0x11, 0x11 + 15)))
    m.mem_write(obj, bytes([0 if case == 'inactive' else 1])); m.mem_write(obj + 4, header)
    common = [(-2, 9), (7, 5)]
    char_maps = {0: [(100, 3), (200, -2)], 14: [(-4, 5)], 15: [(1234, 88)]}
    records = {0: [[4, 1, 300, 2, 3, 4], [4, 3, 300, 99, 98, 97]],
               14: [[-5, 2, 255, -6, 7, 8]], 15: [[1234, 3, 999, 9, 9, 9]]}

    def tree(owner, values, mapped):
        head = next_node[0]; next_node[0] += 0x100
        order = []
        for key, value in values:
            node = next_node[0]; next_node[0] += 0x100
            w(node + 12, key)
            if mapped: w(node + 16, value)
            order.append(node)
        w(owner + 4, head); w(owner + 8, len(order))
        for off in (0, 4, 8): w(head + off, head)
        w(head, order[0] if order else head)
        trees[owner] = dict(head=head, order=order)

    tree(obj + 0x44, [(8, 0), (9, 0)], False)
    tree(obj + 0x50, [(10, 0), (11, 0)], False)
    tree(obj + 0x9c, common, True)
    for index in range(20):
        tree(obj + 0xa8 + 12 * index, char_maps.get(index, []), True)
        owner = obj + 0x198 + 16 * index; values = records.get(index, [])
        base = 0xb00000 + index * 0x1000 if values else 0
        for row, value in enumerate(values): m.mem_write(base + row * 24, pack(value))
        w(owner + 4, base); w(owner + 8, base + len(values) * 24 if base else 0); w(owner + 12, base + 0x1000 if base else 0)
    before = bytes(m.mem_read(obj, 0x2d8))
    words = [2, 8, 9, 2, 10, 11, len(common)]
    for key, value in common: words += [key, value]
    words += [15]
    for index in range(15):
        values = char_maps.get(index, []); words += [len(values)]
        for key, value in values: words += [key, value]
        values = records.get(index, []); words += [len(values)]
        for record in values: words += record
    expected = pack([0x6a]) + header + pack(words)
    require(len(expected) == 332, 'serialization fixture extent changed')
    encoded = b'' if case == 'encoder_zero' else b'\x13\x80\x00\xfd\x7a\x01'
    expected_wire = bytes(encoded[len(encoded)-i-1] ^ ((7*(len(encoded)-i-1))&255) for i in range(len(encoded)))
    apis = {0x800100: ('open', 28), 0x800110: ('close', 4), 0x800120: ('write', 20)}
    for iat, dest in [(0x6c0098, 0x800100), (0x6c00a0, 0x800110), (0x6c006c, 0x800120)]: w(iat, dest)
    w(stack, 0xf00000)
    saved = [(UC_X86_REG_EBP, 0x12345678), (UC_X86_REG_EBX, 0x22334455),
             (UC_X86_REG_ESI, 0x33445566), (UC_X86_REG_EDI, 0x44556677)]
    for reg, value in saved + [(UC_X86_REG_ESP, stack), (UC_X86_REG_ECX, obj)]: m.reg_write(reg, value)

    def hook(u, address, size, data):
        if address == 0xf00000: u.emu_stop(); return
        if address == 0x68a143: raise ValueError('native persist fixture reached invalid-parameter guard')
        if address == 0x43aa40:
            events.append('header_service'); return  # Execute the real independently exact6-byte provider.
        ss, receiver = u.reg_read(UC_X86_REG_ESP), u.reg_read(UC_X86_REG_ECX)
        pop, result = 0, 0
        if address in apis:
            name, pop = apis[address]
            if name == 'open':
                require(bytes(u.mem_read(r(ss+4), 10)) == b'score.dat\0', 'score path changed')
                require([r(ss+off) for off in (8,12,16,20,24,28)] == [0x40000000,0,0,2,0x80,0], 'writer flags changed')
                result = 0xffffffff if case == 'open_failure' else 0x5678
                events.append('open')
            elif name == 'write':
                require(r(ss+4) == (0 if case == 'open_failure' else 0x5678), 'write handle changed')
                require(r(ss+12) == len(encoded), 'write length changed')
                wire = bytes(u.mem_read(r(ss+8), r(ss+12)))
                require(wire == expected_wire, 'reverse/XOR wire bytes changed')
                require(bytes(wire[len(wire)-i-1] ^ ((7*i)&255) for i in range(len(wire))) == encoded, 'load transform no longer inverts persist transform')
                w(r(ss+16), len(wire)); result = int(case not in ('open_failure', 'encoder_zero'))
                events.append(dict(write_handle=hex(r(ss+4)), wire_hex=wire.hex(), count=len(wire)))
            else:
                require(r(ss+4) == 0x5678, 'close handle changed'); events.append('close'); result=1
        elif address == 0x665b8a:
            require(r(ss+4) == 0x80000, 'array capacity changed'); result=next_data[0]; next_data[0]+=0x80000; events.append('allocate:'+hex(result))
        elif address in (0x42cd00, 0x43b340):
            owner, node = r(receiver), r(receiver+4); state=trees[owner]
            require(node in state['order'], 'iterator increment past end')
            index=state['order'].index(node)+1; w(receiver+4,state['order'][index] if index<len(state['order']) else state['head'])
        elif address == 0x4067f0:
            require(r(ss+16) == 0x80000, 'encode capacity changed')
            content=bytes(u.mem_read(r(ss+4),r(ss+8))); require(content == expected, 'full serialized payload changed')
            serialized.append(content.hex()); u.mem_write(r(ss+12),encoded) if encoded else None
            result=len(encoded); events.append('encode')
        elif address == 0x68aa26:
            require(r(ss+4) in (0x900000,0x980000), 'array release changed'); events.append('release:'+hex(r(ss+4)))
        else: return
        u.reg_write(UC_X86_REG_EAX,result&0xffffffff); u.reg_write(UC_X86_REG_ECX,0xbad0c0de); u.reg_write(UC_X86_REG_EDX,0xbad0dada)
        u.reg_write(UC_X86_REG_ESP,ss+4+pop); u.reg_write(UC_X86_REG_EIP,r(ss))

    m.hook_add(UC_HOOK_CODE,hook); m.emu_start(ADDRESS,0,count=50000)
    require(m.reg_read(UC_X86_REG_EIP)==0xf00000,'persist did not return')
    require(m.reg_read(UC_X86_REG_ESP)==stack+4 and r(0)==0,'stack/FS0 not restored')
    for reg,value in saved: require(m.reg_read(reg)==value,'callee-saved register changed')
    require(bytes(m.mem_read(obj,0x2d8))==before,'persist changed the source score object')
    if case=='inactive': require(events==[] and serialized==[],'inactive gate performed work')
    else:
        require(len(serialized)==1,'encode call count changed')
        require(events[-2:] == ['release:0x980000','release:0x900000'] if case=='open_failure'
                else events[-3:] == ['release:0x980000','release:0x900000','close'], 'cleanup order changed')
    return dict(case=case,events=events,serialized_hex=serialized,serialized_bytes=332 if serialized else 0,
                source_unchanged=True,stack_callee_saves_fs0_preserved=True)


def audit(obj=None):
    spec=importlib.util.spec_from_file_location('score_persist_compare',ROOT/'scripts/compare-function.py')
    compare=importlib.util.module_from_spec(spec); spec.loader.exec_module(compare)
    identity=compare.verify_target(); code=compare.target_bytes(ADDRESS,SIZE)
    require(hashlib.sha256(code).hexdigest()==SHA,'complete body changed')
    decoder=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32); decoder.detail=True
    instructions=list(decoder.disasm(code,ADDRESS)); require(len(instructions)==360 and sum(i.size for i in instructions)==SIZE,'decode changed')
    by={i.address:i for i in instructions}; pending,reached,returns,calls=[ADDRESS],set(),[],Counter()
    while pending:
        address=pending.pop()
        if address in reached: continue
        require(address in by,'escaping/noninstruction edge'); reached.add(address); ins=by[address]
        if ins.mnemonic=='ret': require(bytes(ins.bytes)==b'\xc3','cleanup changed'); returns.append(address); continue
        if ins.mnemonic=='call': calls[hex(ins.operands[0].imm) if ins.operands[0].type==x86.X86_OP_IMM else ins.op_str]+=1
        if ins.group(capstone.CS_GRP_JUMP):
            require(ins.operands[0].type==x86.X86_OP_IMM,'unexpected indirect jump'); pending.append(ins.operands[0].imm)
            if ins.mnemonic=='jmp': continue
        pending.append(address+ins.size)
    require(len(reached)==359 and returns==[0x42d872],'whole CFG changed')
    alignment={hex(i.address):bytes(i.bytes).hex() for i in instructions if i.address not in reached}
    require(alignment=={'0x42d73d':'8d4900'},'internal alignment changed')
    require(compare.target_bytes(ADDRESS+SIZE,13)==b'\xcc'*13,'following separation changed')
    require(calls['0x68a143']==19 and calls['0x42cd00']==2 and calls['0x43b340']==2,'checked traversal census changed')
    require(compare.target_bytes(0x43aa40,6)==bytes.fromhex('b86a000000c3'),'real header provider changed')
    callers=[]
    for site in (0x42e7a5,0x43d68c,0x44067d):
        call=next(decoder.disasm(compare.target_bytes(site,5),site))
        require(call.mnemonic=='call' and call.operands[0].imm==ADDRESS,'persist caller changed')
        callers.append(hex(site))
    image=bytes(pefile.PE(str(ROOT/'resources/th105.exe')).get_memory_mapped_image())
    cases=['inactive','populated','open_failure','encoder_zero']; native=[observe(image,code,case) for case in cases]
    report=dict(result='target_cfg_closed',target_sha256=identity,address=hex(ADDRESS),size=SIZE,code_sha256=SHA,
                instructions=360,reached=359,ret0_sites=['0x42d872'],internal_alignment=alignment,calls=dict(calls),observed_caller_sites=callers,native_cases=native,
                limitations='API, allocator, encoder and iterator providers are observers; the real6-byte header service executes. Real I/O, compression and EH unwinding are not executed. Original nominal names/TU remain unknown.')
    if obj is not None:
        function=load_manifest()['units'][UNIT]['functions'][0]; targets=compare.known_targets()
        targets.update({n:int(a,0) for n,a in (s.split('=',1) for s in function['rel32_targets'])})
        candidate=compare.coff_symbol_bytes(obj,function['symbol_base'],ADDRESS,0xffffffff,targets,compare.known_data_targets(),{})
        require(candidate==code,'complete canonical candidate differs')
        require([observe(image,candidate,case) for case in cases]==native,'candidate observations differ')
        report['candidate']=dict(object=str(obj),section_size=len(candidate),full_canonical_sha256=hashlib.sha256(candidate).hexdigest(),
                                 all_relocations_replayed=True,unequal_positions=0,observer_cases_equal=4)
        report['result']='candidate_exact'
    return report


def main():
    parser=argparse.ArgumentParser(description=__doc__); parser.add_argument('--object',type=Path); args=parser.parse_args()
    try: report=audit(args.object)
    except (OSError,ValueError,KeyError,AssertionError) as error:
        print(json.dumps(dict(result='blocked',error=str(error)),indent=2)); return 1
    print(json.dumps(report,indent=2)); return 0


if __name__=='__main__': raise SystemExit(main())
