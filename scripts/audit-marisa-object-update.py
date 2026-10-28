#!/usr/bin/env python3
"""Audit complete JP1.06a MarisaObject update bytes, CFG, and switch metadata.

No normalized comparison, masking, or partial-function credit is supported.
"""
from __future__ import annotations
import argparse
from collections import Counter
import hashlib
import importlib.util
import json
from pathlib import Path
import struct
import capstone
from capstone import x86
from workflow_manifest import load_manifest
ROOT=Path(__file__).resolve().parents[1]
START,MAIN,FULL=0x4BBE00,48771,49744
UNIT='exact-first-marisa-object-update'
SYMBOL='?update_action_state@MarisaObjectUpdateView@th105@@UAEXXZ'
MAIN_SHA='ee841171c5399bb81bbfd2514da95cfc572a90bf85d8a3f077e6064006b18b36'
FULL_SHA='ed64218fba02fe174150885db55f58797fbcb3ff7e47f79a54c4c26b9cb64e4d'
WORDS=(42,9,8,5,6,7,11,14,8,7,5,4,7,12,7,8,12,4)
REMAPS=((0x4c7d2c,200),(0x4c7f60,22),(0x4c7fc4,19),(0x4c7ff8,22))
PADDING=((0x4bdee5,0x4bdef0),(0x4bdf28,0x4bdf30),(0x4be528,0x4be530),(0x4c003d,0x4c0040),(0x4c0075,0x4c0080),(0x4c1938,0x4c1940))

def load_compare():
    spec=importlib.util.spec_from_file_location('marisa_canonical',ROOT/'scripts/compare-function.py')
    module=importlib.util.module_from_spec(spec);spec.loader.exec_module(module)
    return module

def inventory(raw):
    md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);md.detail=True
    prefix=list(md.disasm(raw[:128],START))
    primary=next(i.operands[0].mem.disp for i in prefix if i.mnemonic=='jmp' and i.operands[0].type==x86.X86_OP_MEM)
    if not START<primary<START+len(raw):raise ValueError('primary table outside payload')
    rows=list(md.disasm(raw[:primary-START],START));addresses={i.address for i in rows}
    if sum(i.size for i in rows)!=primary-START:raise ValueError('incomplete callable/alignment decode')
    starts=sorted({i.operands[0].mem.disp for i in rows if i.mnemonic=='jmp' and i.operands[0].type==x86.X86_OP_MEM})
    remaps=sorted({i.operands[1].mem.disp for i in rows if i.mnemonic=='movzx' and len(i.operands)>1 and i.operands[1].type==x86.X86_OP_MEM and primary<=i.operands[1].mem.disp<START+len(raw)})
    if len(remaps)!=4:raise ValueError('expected four bounded remap arrays')
    spans=[];tables={}
    for a in starts:
        end=min([v for v in starts+remaps if v>a]+[START+len(raw)])
        if a<primary or (end-a)%4:raise ValueError('invalid destination table extent')
        ds=struct.unpack_from('<%dI'%((end-a)//4),raw,a-START)
        if not ds or not all(v in addresses for v in ds):raise ValueError('table edge is not an instruction')
        tables[a]=ds;spans.append((a,end))
    remap_info=[]
    for a,n in zip(remaps,(200,22,19,22)):
        data=raw[a-START:a-START+n]
        if len(data)!=n:raise ValueError('truncated remap')
        prior=max(t for t in tables if t<a)
        if max(data)>=len(tables[prior]):raise ValueError('remap index outside destination table')
        end=(a+n+3)&~3
        padding=raw[a+n-START:end-START]
        if padding not in (b'',b'\x90',b'\x8b\xff',b'\x66\x90',b'\x90\x90',b'\x90\x90\x90'):raise ValueError('unreviewed metadata alignment')
        spans.append((a,end));remap_info.append(dict(address=hex(a),size=n,sha256=hashlib.sha256(data).hexdigest()))
    spans.sort()
    if spans[0][0]!=primary or spans[-1][1]!=START+len(raw) or any(a[1]!=b[0] for a,b in zip(spans,spans[1:])):raise ValueError('metadata gap/overlap')
    calls=Counter(i.operands[0].imm for i in rows if i.mnemonic=='call' and i.operands[0].type==x86.X86_OP_IMM)
    return rows,tables,dict(main_and_alignment=primary-START,tables=[dict(address=hex(a),dwords=len(ds))for a,ds in tables.items()],remaps=remap_info,returns=sum(i.mnemonic=='ret'for i in rows),virtual_calls=sum(i.mnemonic=='call'and i.operands[0].type!=x86.X86_OP_IMM for i in rows),direct_calls={hex(a):n for a,n in sorted(calls.items())},stack_allocation=[i.operands[1].imm for i in prefix[:12]if i.mnemonic=='sub'and i.operands[0].reg==x86.X86_REG_ESP])

def target_cfg(rows,tables):
    by={i.address:i for i in rows if i.address<START+MAIN};seen=set();pending=[START]
    while pending:
        a=pending.pop()
        if a in seen:continue
        if a not in by:raise ValueError('CFG edge escapes callable')
        i=by[a];seen.add(a)
        if i.mnemonic=='ret':
            if i.op_str:raise ValueError('unexpected callee pop')
        elif i.mnemonic=='jmp':pending.extend(tables[i.operands[0].mem.disp]if i.operands[0].type==x86.X86_OP_MEM else [i.operands[0].imm])
        elif i.group(capstone.CS_GRP_JUMP):pending.extend([i.operands[0].imm,a+i.size])
        else:pending.append(a+i.size)
    omitted={a+j for a,i in by.items()if a not in seen for j in range(i.size)}
    expected={a for lo,hi in PADDING for a in range(lo,hi)}
    if omitted!=expected or len(seen)!=11310:raise ValueError('unreviewed reachable/padding change')
    return dict(reachable_instructions=len(seen),reachable_bytes=sum(by[a].size for a in seen),padding=[dict(start=hex(a),end=hex(b))for a,b in PADDING])

def main():
    ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('--target-only',action='store_true');ap.add_argument('--object',type=Path);args=ap.parse_args()
    try:
        c=load_compare();identity=c.verify_target();target=c.target_bytes(START,FULL)
        if hashlib.sha256(target).hexdigest()!=FULL_SHA or hashlib.sha256(target[:MAIN]).hexdigest()!=MAIN_SHA:raise ValueError('canonical payload changed')
        if struct.unpack('<I',c.target_bytes(0x6c4524,4))[0]!=START:raise ValueError('MarisaObject slot28 changed')
        rows,tables,facts=inventory(target)
        if tuple(map(len,tables.values()))!=WORDS or tuple((int(v['address'],16),v['size'])for v in facts['remaps'])!=REMAPS:raise ValueError('target switch metadata changed')
        if facts['returns']!=71 or facts['stack_allocation']!=[0x340]:raise ValueError('target return/frame inventory changed')
        result=dict(target_sha256=identity,callable_size=MAIN,complete_payload_size=FULL,target_payload_sha256=FULL_SHA,target_inventory=facts,target_cfg=target_cfg(rows,tables),canonical_acceptance=False)
        if args.target_only:result['result']='observed_target_bytes'
        else:
            unit=load_manifest()['units'][UNIT];f=unit['functions'][0];targets=c.known_targets()
            for binding in f['rel32_targets']:
                n,a=binding.rsplit('=',1);targets[n]=int(a,0)
            overrides=dict(v.split('=',1)for v in f['dir32_targets'])
            candidate=c.coff_symbol_bytes(args.object or ROOT/unit['object'],SYMBOL,START,0xffffffff,targets,c.known_data_targets(),overrides)
            result.update(result='exact'if candidate==target else 'mismatch',object_section_tail_size=len(candidate),all_section_relocations_replayed=True,canonical_payload_sha256=hashlib.sha256(candidate).hexdigest(),first_mismatch=c.first_mismatch(target,candidate,START),unmasked_differing_bytes=sum(a!=b for a,b in zip(target,candidate))+abs(len(target)-len(candidate)),candidate_inventory=inventory(candidate)[2],canonical_acceptance=candidate==target)
    except (OSError,ValueError,RuntimeError,KeyError,StopIteration,struct.error)as e:
        print(json.dumps(dict(result='blocked',error=str(e)),indent=2));return 1
    print(json.dumps(result,indent=2));return 0 if args.target_only or result['canonical_acceptance'] else 1
if __name__=='__main__':raise SystemExit(main())
