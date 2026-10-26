#!/usr/bin/env python3
"""Pin the whole score loader and observe native file/decode/container policy."""
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
ADDRESS, SIZE = 0x42F6F0, 1672
SHA = '603c5bbb9b498dd93944cab66f78b15ad41887b5fa3ec77b890ba47dd1e54ccf'
UNIT = 'exact-first-score-load'


def require(condition, message):
    if not condition:
        raise ValueError(message)


def payload(characters):
    words = [0x12345678, 0x3456789a] + list(range(0x11, 0x11 + 15))
    words += [3, 8, 8, 9, 2, 10, 11, 3, 7, 5, 7, 99, 8, 6, characters]
    if characters:
        words += [3, 100, 3, 100, 9, 200, 0xfffffffe, 3]
        words += [4, 1, 50, 2, 3, 4, 4, 3, 50, 99, 98, 97, 5, 2, 300, 6, 7, 8]
        words += [0, 0]
    return struct.pack('<' + str(len(words)) + 'I', *words)


def observe(image, code, case):
    m = Uc(UC_ARCH_X86, UC_MODE_32)
    m.mem_map(0x400000, (len(image) + 4095) & ~4095); m.mem_write(0x400000, image)
    m.mem_write(ADDRESS, code); m.mem_map(0, 0x10000)
    m.mem_map(0x800000, 0x400000); m.mem_map(0x1000000, 0x20000); m.mem_map(0xf00000, 0x1000)
    w = lambda a, v: m.mem_write(a, struct.pack('<I', v & 0xffffffff))
    r = lambda a: struct.unpack('<I', m.mem_read(a, 4))[0]
    obj, stack = 0x802000, 0x1010004
    next_node, next_data = [0x806000], [0x900000]
    trees, nodes, vectors, events = {}, {}, {}, []
    raw = b'\x00\x19\x72\xa0\xff\x21\x06'
    decoded = payload(0 if case == 'zero_characters' else 2)

    def tree(owner, kind, initial):
        head = next_node[0]; next_node[0] += 0x100
        nil = 0x11 if kind == 'set' else 0x15
        w(owner + 4, head); w(owner + 8, len(initial))
        for off in (0, 4, 8): w(head + off, head)
        m.mem_write(head + nil, b'\x01')
        entries, previous = {}, head
        for key, value in reversed(initial):
            node = next_node[0]; next_node[0] += 0x100
            w(node, previous); w(node + 4, head); w(node + 8, head); w(node + 12, key)
            if kind == 'map': w(node + 16, value)
            entries[key] = (node, value); nodes[node] = (owner, key); previous = node
        w(head + 4, previous)
        trees[owner] = dict(kind=kind, head=head, entries=entries)

    for off in (0x44, 0x50): tree(obj + off, 'set', [(77, 0)])
    tree(obj + 0x9c, 'map', [(77, 77)])
    for index in range(20):
        tree(obj + 0xa8 + 12 * index, 'map', [(77, 77)] if index < 2 else [])
        owner = obj + 0x198 + 16 * index; base = 0xb00000 + index * 0x1000
        old = [77, 2, 88, 1, 2, 3]
        m.mem_write(base, struct.pack('<6i', *old)); w(owner + 4, base); w(owner + 8, base + 24); w(owner + 12, base + 0x1000)
        vectors[owner] = base
    m.mem_write(obj + 4, b'\x55' * 64)
    apis = {0x800100: ('open', 28), 0x800110: ('close', 4), 0x800120: ('size', 8), 0x800130: ('read', 20)}
    for iat, dest in [(0x6c0098,0x800100),(0x6c00a0,0x800110),(0x6c0070,0x800120),(0x6c0094,0x800130)]: w(iat, dest)
    w(stack, 0xf00000)
    saved = [(UC_X86_REG_EBP,0x12345678),(UC_X86_REG_EBX,0x22334455),(UC_X86_REG_ESI,0x33445566),(UC_X86_REG_EDI,0x44556677)]
    for reg, value in saved + [(UC_X86_REG_ESP,stack),(UC_X86_REG_ECX,obj)]: m.reg_write(reg,value)

    def remove(node):
        if node in nodes:
            owner, key = nodes.pop(node); trees[owner]['entries'].pop(key, None)

    def erase(owner, node):
        head = trees[owner]['head']
        if node == head: return
        left, right = r(node), r(node + 8)
        erase(owner, right); erase(owner, left); remove(node)

    def capture():
        maps = {}
        for owner, state in trees.items():
            if owner in (obj+0x44,obj+0x50,obj+0x9c,obj+0xa8,obj+0xb4):
                maps[hex(owner-obj)] = sorted((key, struct.unpack('<i',struct.pack('<I',value&0xffffffff))[0]) for key,(_,value) in state['entries'].items())
        records = []
        for index in range(2):
            owner = obj + 0x198 + 16*index; base = r(owner+4); end = r(owner+8)
            records.append([list(struct.unpack('<6i',m.mem_read(a,24))) for a in range(base,end,24)])
        return dict(header=m.mem_read(obj+4,64).hex(), initialized=m.mem_read(obj,1)[0], maps=maps, records=records)

    def hook(u, address, size, data):
        if address == 0xf00000: u.emu_stop(); return
        if address == 0x68a143: raise ValueError('native loader fixture reached invalid-parameter guard')
        ss, receiver = u.reg_read(UC_X86_REG_ESP), u.reg_read(UC_X86_REG_ECX)
        pop, result = 0, 0
        if address in apis:
            name, pop = apis[address]
            if name == 'open':
                require(bytes(u.mem_read(r(ss+4),10)) == b'score.dat\0', 'score path changed')
                require([r(ss+off) for off in (8,12,16,20,24,28)] == [1,1,0,3,0x80,0], 'open flags changed')
                result = 0xffffffff if case == 'missing' else 0x5678
            elif name == 'size': result = len(raw)
            elif name == 'read':
                require(r(ss+12) == len(raw), 'read count changed'); u.mem_write(r(ss+8),raw); w(r(ss+16),len(raw)); result=1
            events.append(name)
        elif address == 0x665b8a:
            require(r(ss+4) == 0x80000, 'array capacity changed'); result=next_data[0]; next_data[0]+=0x80000; events.append('allocate')
        elif address == 0x406890:
            transformed=bytes(u.mem_read(r(ss+4),r(ss+8)))
            require(transformed == bytes(raw[len(raw)-i-1] ^ ((7*i)&255) for i in range(len(raw))), 'reverse/XOR transform changed')
            require(r(ss+16) == 0x80000, 'decode limit changed')
            u.mem_write(r(ss+12),decoded); result=0 if case=='decode_failure' else len(decoded); events.append('decode')
        elif address in (0x42ce20,0x43bc40): erase(receiver,r(ss+4)); pop=4
        elif address == 0x6898ea: remove(r(ss+4))
        elif address in (0x42db20,0x4606e0):
            state=trees[receiver]; key=r(r(ss+8)); value=r(r(ss+8)+4) if address==0x4606e0 else 0
            if key not in state['entries']:
                node=next_node[0]; next_node[0]+=0x100; state['entries'][key]=(node,value); nodes[node]=(receiver,key)
            node,_=state['entries'][key]; result=r(ss+4); w(result,receiver); w(result+4,node); w(result+8,1); w(receiver+8,len(state['entries'])); pop=8
        elif address == 0x42dfc0:
            require(receiver in vectors,'append receiver changed'); end=r(receiver+8); u.mem_write(end,bytes(u.mem_read(r(ss+4),24))); w(receiver+8,end+24); pop=4
        elif address == 0x42ed70:
            require(receiver==obj,'default receiver changed'); events.append('defaults'); w(obj+4,0x77777777)
        elif address == 0x42e3f0:
            require(receiver==obj,'refresh receiver changed'); events.append('refresh')
        elif address == 0x68aa26:
            require(r(ss+4) in (0x900000,0x980000),'array release changed'); events.append('release:'+hex(r(ss+4)))
        else: return
        u.reg_write(UC_X86_REG_EAX,result&0xffffffff); u.reg_write(UC_X86_REG_ECX,0xbad0c0de); u.reg_write(UC_X86_REG_EDX,0xbad0dada)
        u.reg_write(UC_X86_REG_ESP,ss+4+pop); u.reg_write(UC_X86_REG_EIP,r(ss))

    m.hook_add(UC_HOOK_CODE,hook); m.emu_start(ADDRESS,0,count=50000)
    require(m.reg_read(UC_X86_REG_EIP)==0xf00000,'loader did not return')
    require(m.reg_read(UC_X86_REG_ESP)==stack+4 and r(0)==0,'stack/FS0 not restored')
    for reg,value in saved: require(m.reg_read(reg)==value,'callee-saved register changed')
    success=case in ('populated','zero_characters'); require(m.reg_read(UC_X86_REG_EAX)&255==int(success),'boolean result changed')
    state=capture()
    if success:
        require(state['header']==decoded[4:68].hex() and state['initialized']==1,'loaded scalar state changed')
        require(state['maps']['0x44']==[(8,0),(9,0)] and state['maps']['0x50']==[(10,0),(11,0)],'set policy changed')
        require(state['maps']['0x9c']==[(7,5),(8,6)],'common map first-insert policy changed')
        if case=='populated':
            require(state['maps']['0xa8']==[(100,3),(200,-2)] and state['maps']['0xb4']==[],'character maps changed')
            require(state['records']==[[[4,1,50,2,3,4],[5,2,300,6,7,8]],[]],'record dedup/full-field policy changed')
        else: require(state['records']==[[[77,2,88,1,2,3]],[[77,2,88,1,2,3]]],'zero character count cleared untouched slots')
        require(events[-4:]==['refresh','release:0x980000','release:0x900000','close'],'successful cleanup order changed')
    elif case=='missing': require(events==['open','defaults'],'missing-file fallback changed')
    else: require(events[-4:]==['defaults','release:0x980000','release:0x900000','close'],'failed-decode cleanup order changed')
    return dict(case=case,events=events,state=state,result=success,stack_callee_saves_fs0_preserved=True)


def audit(obj=None):
    spec=importlib.util.spec_from_file_location('score_load_compare',ROOT/'scripts/compare-function.py')
    compare=importlib.util.module_from_spec(spec); spec.loader.exec_module(compare)
    identity=compare.verify_target(); code=compare.target_bytes(ADDRESS,SIZE)
    require(hashlib.sha256(code).hexdigest()==SHA,'complete body changed')
    decoder=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32); decoder.detail=True
    instructions=list(decoder.disasm(code,ADDRESS)); require(len(instructions)==521 and sum(i.size for i in instructions)==SIZE,'decode changed')
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
    require(len(reached)==521 and sorted(returns)==[0x42f795,0x42f876,0x42fd77],'full CFG changed')
    require(compare.target_bytes(ADDRESS+SIZE,8)==b'\xcc'*8,'following separation changed')
    require(calls['0x68a143']==5 and calls['0x42ed70']==2 and calls['0x406890']==1,'guard/fallback/decode census changed')
    ctor=compare.target_bytes(0x43e1a0,306)
    require(hashlib.sha256(ctor).hexdigest()=='991bc3a6dde8fab75eeea8f3d07879689361f418cc7e241cc8ff31a513ec690c','layout constructor changed')
    require(compare.target_bytes(0x43e287,4)==bytes.fromhex('6a146a0c') and compare.target_bytes(0x43e2a6,4)==bytes.fromhex('6a146a10'),'20-slot map/vector constructor arguments changed')
    image=bytes(pefile.PE(str(ROOT/'resources/th105.exe')).get_memory_mapped_image())
    cases=['missing','decode_failure','populated','zero_characters']; native=[observe(image,code,case) for case in cases]
    report=dict(result='target_cfg_closed',target_sha256=identity,address=hex(ADDRESS),size=SIZE,code_sha256=SHA,
                instructions=521,reached=521,ret0_sites=[hex(a) for a in sorted(returns)],calls=dict(calls),
                layout_constructor=dict(address='0x0043E1A0',size=306,sha256=hashlib.sha256(ctor).hexdigest(),map_slots=20,record_vector_slots=20,new_credit=False),
                native_cases=native,limitations='Services, decode, allocations and STL providers are observers; real file I/O, compressed-data behavior and EH unwinding are unexecuted. Original names/TU remain unknown.')
    if obj is not None:
        function=load_manifest()['units'][UNIT]['functions'][0]; targets=compare.known_targets()
        targets.update({n:int(a,0) for n,a in (s.split('=',1) for s in function['rel32_targets'])})
        overrides=dict(s.split('=',1) for s in function.get('dir32_targets',[]))
        candidate=compare.coff_symbol_bytes(obj,function['symbol_base'],ADDRESS,0xffffffff,targets,compare.known_data_targets(),overrides)
        require([observe(image,candidate,case) for case in cases]==native,'candidate service/container observations differ')
        differences=[dict(offset=i,address=hex(ADDRESS+i),target=f'{a:02x}',candidate=f'{b:02x}') for i,(a,b) in enumerate(zip(code,candidate)) if a!=b]
        report['candidate']=dict(object=str(obj),section_size=len(candidate),size_difference=len(candidate)-SIZE,
                                 full_canonical_sha256=hashlib.sha256(candidate).hexdigest(),all_relocations_replayed=True,
                                 unequal_positions=len(differences),differences=differences,observer_cases_equal=4)
        report['result']='candidate_exact' if candidate==code else 'candidate_nonexact'
    return report


def main():
    parser=argparse.ArgumentParser(description=__doc__); parser.add_argument('--object',type=Path); args=parser.parse_args()
    try: report=audit(args.object)
    except (OSError,ValueError,KeyError,AssertionError) as error:
        print(json.dumps(dict(result='blocked',error=str(error)),indent=2)); return 2
    print(json.dumps(report,indent=2)); return int(report['result']=='candidate_nonexact')


if __name__=='__main__': raise SystemExit(main())
