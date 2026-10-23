#!/usr/bin/env python3
"""Describe Aya852 signed-byte promotion and x87 conversion placement; diagnostic only."""
from pathlib import Path
import argparse
import hashlib
import importlib.util
import json
import sys
import tomllib
import capstone
from capstone import x86_const as x

ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
import linked_pe as lp
from workflow_manifest import load_manifest


def load_mapper():
    spec=importlib.util.spec_from_file_location('aya852_facing_coff',ROOT/'scripts/compare-giant-action-switches.py')
    module=importlib.util.module_from_spec(spec);sys.modules[spec.name]=module;spec.loader.exec_module(module)
    return module


def window(code,address):
    cs=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);cs.detail=True
    rows=list(cs.disasm(code,address));assert sum(r.size for r in rows)==len(code)
    stores=[i for i,r in enumerate(rows) if r.mnemonic=='fstp' and r.operands[0].type==x.X86_OP_MEM
            and r.operands[0].mem.base==x.X86_REG_EAX and r.operands[0].mem.disp==0x6AC and r.operands[0].size==4]
    assert len(stores)==1,'owner+6AC product store is not unique'
    end=stores[0]
    starts=[i for i in range(max(0,end-24),end) if rows[i].mnemonic=='cmp' and len(rows[i].operands)==2
            and rows[i].operands[0].type==x.X86_OP_MEM and rows[i].operands[0].mem.base==x.X86_REG_ESI
            and rows[i].operands[0].mem.disp==0x104 and rows[i].operands[0].size==1
            and rows[i].operands[1].type==x.X86_OP_IMM and rows[i].operands[1].imm & 255==255]
    assert len(starts)==1,'facing=-1 guard not uniquely bounded'
    seq=rows[starts[0]:end+1]
    branches=[r for r in seq if r.mnemonic=='jne'];assert len(branches)==1
    branch=branches[0]
    assert branch.operands[0].type==x.X86_OP_IMM
    positive=branch.operands[0].imm
    decoded={r.address for r in seq}
    assert branch.address<positive<seq[-1].address and positive in decoded
    jumps=[r for r in seq if r.mnemonic=='jmp']
    assert len(jumps)==1 and jumps[0].operands[0].type==x.X86_OP_IMM
    assert jumps[0].operands[0].imm in decoded and jumps[0].operands[0].imm>positive
    assert all(not r.group(capstone.CS_GRP_JUMP) or r.address in (branch.address,jumps[0].address) for r in seq)
    assert all(not r.group(capstone.CS_GRP_CALL) and not r.group(capstone.CS_GRP_RET) for r in seq)
    captures=[r for r in seq if r.mnemonic in ('mov','movsx') and len(r.operands)==2
              and r.operands[1].type==x.X86_OP_MEM and r.operands[1].size==1
              and r.operands[1].mem.base==x.X86_REG_ECX and r.operands[1].mem.disp==0x104]
    assert len(captures)==1 and captures[0].address<branch.address
    raw=code[seq[0].address-address:seq[-1].address+seq[-1].size-address]
    return dict(start=hex(seq[0].address),size=len(raw),instructions=len(seq),sha256=hashlib.sha256(raw).hexdigest(),
                nested_byte_capture=dict(address=hex(captures[0].address),operation=captures[0].mnemonic,
                                         operands=captures[0].op_str,destination_bits=captures[0].operands[0].size*8),
                signed_extension_sites=[hex(r.address) for r in seq if r.mnemonic=='movsx'],
                fild_regions=[('before_direction_branch' if r.address<branch.address else
                               'negative_arm' if r.address<positive else 'positive_arm') for r in seq if r.mnemonic=='fild'],
                integer_multiplication=any(r.mnemonic=='fimul' for r in seq),
                rows=[dict(address=hex(r.address),bytes=r.bytes.hex(),operation=r.mnemonic,operands=r.op_str) for r in seq])


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--object',type=Path,action='append',help='Repeat for selected/frozen controls; default is configured object')
    parser.add_argument('--output',type=Path,default=ROOT/'build/aya852-facing-lifetimes.json')
    args=parser.parse_args()
    c=lp.comparator();target_sha=c.verify_target()
    mapper=load_mapper();unit=load_manifest()['units']['gpt-web-aya-object-vslot28-full-root'];f=unit['functions'][0]
    root=mapper.load_target_mapper().select_root(tomllib.loads((ROOT/'config/giant-action-switches.toml').read_text()),'aya-object-vslot28')
    address=0x61A290;target=window(c.target_bytes(address,19522),address)
    assert target['start']=='0x61c98c' and target['size']==62 and target['instructions']==14
    assert target['nested_byte_capture']['operation']=='movsx' and target['nested_byte_capture']['destination_bits']==32
    assert target['fild_regions']==['negative_arm','positive_arm'] and not target['integer_multiplication']
    candidates=[]
    for obj in args.object or [ROOT/unit['object']]:
        co=mapper.CoffObject(obj,symbol_base=f['symbol_base']);meta=mapper.build_candidate_map(co,root)['metadata_start']
        code=c.coff_symbol_bytes(obj,f['symbol_base'],address,len(co.text),
            {a:int(b,0) for a,b in (s.split('=',1) for s in f['rel32_targets'])},c.known_data_targets(),
            dict(s.split('=',1) for s in f.get('dir32_targets',[])))
        facts=window(code[:meta],address)
        candidates.append(dict(path=str(obj),object_sha256=lp.sha(obj),full_size=len(code),metadata_start=meta,
                               canonical_sha256=hashlib.sha256(code).hexdigest(),facing_window=facts))
    report=dict(evidence='raw_instruction_diagnostic_not_exact_acceptance',target_sha256=target_sha,target=target,
                objects=candidates,scope='complete facing=-1 compare to unique owner+6AC store; local branch edges closed, exact instruction observations only; no inferred original C++ type, equivalence or root acceptance')
    args.output.parent.mkdir(parents=True,exist_ok=True);args.output.write_text(json.dumps(report,indent=2)+'\n')
    print(json.dumps(report,indent=2))


if __name__=='__main__':main()
