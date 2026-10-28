#!/usr/bin/env python3
"""Audit complete JP1.06a PatchouliObject update bytes, CFG, and switch metadata.

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
START,MAIN,FULL=0x520890,50649,51564
UNIT='exact-first-patchouli-object-update'
SYMBOL='?update_action_state@PatchouliObjectUpdateView@th105@@UAEXXZ'
MAIN_SHA='bf3a47cba713db2ffc1d72d9e3803aaa7b5b39e49da0ea11f34aed09ca8ab7ce'
FULL_SHA='6f0593093c471bd996eaa1f871a72f1339e80e5d0291a81224ba9b53608ac0cf'
WORDS=(31,4,11,7,10,6,4,14,7,4,8,10,4,6,12,6,6,4,11,4,4)
REMAPS=((0x52cee8,199),(0x52d114,20))
PADDING=((0x52271d,0x522720),(0x52334d,0x523350),(0x523fbd,0x523fc0),(0x528d2d,0x528d30),(0x529d29,0x529d30),(0x529f3d,0x529f40),(0x52b6f9,0x52b700),(0x52bda9,0x52bdb0),(0x52c579,0x52c580))

def load_compare():
    spec=importlib.util.spec_from_file_location('patchouli_canonical',ROOT/'scripts/compare-function.py')
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
    if len(remaps)!=2:raise ValueError('expected two bounded remap arrays')
    spans=[];tables={}
    for a in starts:
        end=min([v for v in starts+remaps if v>a]+[START+len(raw)])
        if a<primary or (end-a)%4:raise ValueError('invalid destination table extent')
        ds=struct.unpack_from('<%dI'%((end-a)//4),raw,a-START)
        if not ds or not all(v in addresses for v in ds):raise ValueError('table edge is not an instruction')
        tables[a]=ds;spans.append((a,end))
    remap_info=[]
    for a,n in zip(remaps,(199,20)):
        data=raw[a-START:a-START+n]
        if len(data)!=n:raise ValueError('truncated remap')
        prior=max(t for t in tables if t<a)
        if max(data)>=len(tables[prior]):raise ValueError('remap index outside destination table')
        end=a+n if a==remaps[-1] else (a+n+3)&~3
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
    if omitted!=expected or len(seen)!=12041:raise ValueError('unreviewed reachable/padding change')
    return dict(reachable_instructions=len(seen),reachable_bytes=sum(by[a].size for a in seen),padding=[dict(start=hex(a),end=hex(b))for a,b in PADDING])

def main():
    ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('--target-only',action='store_true');ap.add_argument('--object',type=Path);args=ap.parse_args()
    try:
        c=load_compare();identity=c.verify_target();target=c.target_bytes(START,FULL)
        if hashlib.sha256(target).hexdigest()!=FULL_SHA or hashlib.sha256(target[:MAIN]).hexdigest()!=MAIN_SHA:raise ValueError('canonical payload changed')
        if struct.unpack('<I',c.target_bytes(0x6c4e4c,4))[0]!=START:raise ValueError('PatchouliObject slot28 changed')
        if struct.unpack('<I',c.target_bytes(0x6c4e20,4))[0]!=0x6da55c:raise ValueError('PatchouliObject COL changed')
        if struct.unpack('<I',c.target_bytes(0x6da568,4))[0]!=0x6e8348 or not c.target_bytes(0x6e8350,32).startswith(b'.?AVPatchouliObject@@\0'):raise ValueError('PatchouliObject type descriptor changed')
        rows,tables,facts=inventory(target)
        if tuple(map(len,tables.values()))!=WORDS or tuple((int(v['address'],16),v['size'])for v in facts['remaps'])!=REMAPS:raise ValueError('target switch metadata changed')
        if facts['returns']!=82 or facts['stack_allocation']!=[0x3e0]:raise ValueError('target return/frame inventory changed')
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
