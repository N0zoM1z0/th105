#!/usr/bin/env python3
"""Check that Aya861 skips phase/count advancement for every nonzero sequence."""
from pathlib import Path
from collections import Counter
import argparse
import hashlib
import importlib.util
import itertools
import json
import struct
import sys
import capstone

ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('aya861_math',ROOT/'scripts/audit-aya-object-903-native.py')
math=importlib.util.module_from_spec(spec)
sys.modules[spec.name]=math
spec.loader.exec_module(math)
base=math.base


class Probe(math.Probe):
    action_id=861

    def prepare(self,case):
        seq,phase,counter,alpha,cw= self.settings
        for off,fmt,val in ((0x364,'h',counter),(0x113,'B',alpha),(0x370,'f',0.1)):
            self.uc.mem_write(base.OWNER+off,struct.pack('<'+fmt,val))
        self.uc.mem_write(base.OWNER+0x10EC,struct.pack('<ff',640.0,100.0))

    def read(self,uc,access,address,size,value,data):
        pass  # This observer checks phase/count effects; alpha-read epochs are outside its scope.

    def evaluate(self,case):
        self.settings=case
        seq,phase,counter,alpha,cw=case
        out=base.Probe.run(self,(seq,phase,100,cw,20.0))
        assert out['stop']=='ret'
        return out


def canonical(obj):
    co=base.mapper.CoffObject(obj,symbol_base=base.f['symbol_base'])
    return base.c.coff_symbol_bytes(obj,base.f['symbol_base'],base.A,len(co.text),
        {a:int(b,0) for a,b in (z.split('=',1) for z in base.f['rel32_targets'])},
        base.c.known_data_targets(),dict(z.split('=',1) for z in base.f.get('dir32_targets',[])))


def branch_delta(previous,selected):
    old,new=canonical(previous),canonical(selected)
    assert len(old)==len(new)
    changed=[i for i,(a,b) in enumerate(zip(old,new)) if a!=b]
    assert len(changed)==1,'entire payload must differ only in the861 branch displacement byte'
    off=changed[0]-2
    assert old[off:off+2]==new[off:off+2]==b'\x0f\x85'
    assert new[off-14:off]==base.c.target_bytes(0x61D5E4,14), 'entry guard differs from target'
    def dest(code):return base.A+off+6+struct.unpack_from('<i',code,off+2)[0]
    before,after=dest(old),dest(new)
    assert after-before==41
    cs=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
    target=list(cs.disasm(base.c.target_bytes(0x61D5E4,20),0x61D5E4))
    assert target[-1].address==0x61D5F2 and target[-1].mnemonic=='jne' and target[-1].op_str=='0x61c2a7'
    suffix=list(cs.disasm(new[after-base.A:after-base.A+9],after))
    assert suffix[0].mnemonic=='cmp' and suffix[0].op_str=='word ptr [esi + 0x13e], bx'
    phase=list(cs.disasm(new[before-base.A:after-base.A],before))
    assert sum(r.size for r in phase)==41
    assert phase[0].mnemonic=='cmp' and phase[0].op_str=='dword ptr [esi + 0x180], edi'
    assert any(r.mnemonic=='add' and r.op_str=='word ptr [esi + 0x364], bx' for r in phase)
    return dict(full_size=len(new),previous_sha256=hashlib.sha256(old).hexdigest(),
                selected_sha256=hashlib.sha256(new).hexdigest(),changed_offsets=[hex(i) for i in changed],
                branch=hex(base.A+off),previous_destination=hex(before),selected_destination=hex(after),
                scope='one changed displacement byte skips the41-byte phase/count interval; complete other canonical bytes identical')


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--object',type=Path,default=ROOT/base.unit['object'])
    parser.add_argument('--previous-object',type=Path)
    parser.add_argument('--output',type=Path,default=ROOT/'build/aya861-phase-scope.json')
    args=parser.parse_args()
    table,receipt=math.lookup_fixture(base.c)
    cases=list(itertools.product((1,2,3,4),(0,1,5,6),(-32768,-1,0,4,5,6,32766,32767),
                                  (0,15,255),(0x27F,0x67F,0xA7F,0xE7F,0x37F,0x77F,0xB7F,0xF7F)))
    objects=([args.previous_object] if args.previous_object else [])+[args.object]
    probes=[Probe(table)]+[Probe(table,obj) for obj in objects]
    raw=[Counter() for _ in objects]; final=[0 for _ in objects]
    state_changes=[0 for _ in objects]; examples=[]; reordered=0
    for case in cases:
        values=[p.evaluate(case) for p in probes]
        target=values[0]
        assert not any(off in (0x180,0x364) for off,size,value in target['writes'])
        for i,val in enumerate(values[1:]):
            fields=[k for k in target if val[k]!=target[k]];raw[i].update(fields)
            final[i]+=int(any(k!='writes' for k in fields))
            state_changes[i]+=int(any(off in (0x180,0x364) for off,size,value in val['writes']))
        selected=values[-1]
        assert not any(k!='writes' for k in target if target[k]!=selected[k]),'selected final state differs'
        assert not any(off in (0x180,0x364) for off,size,value in selected['writes'])
        if selected['writes']!=target['writes']:
            # Retain the known scheduling difference explicitly; never normalize phase/count writes.
            a,b=target['writes'],selected['writes']
            assert case[0]==1 and [(off,size) for off,size,value in a[:2]]==[(0xEC,4),(0x113,1)]
            assert a[0]==b[1] and a[1]==b[0] and a[2:]==b[2:]
            reordered+=1
        if args.previous_object and values[1]['actor']!=target['actor'] and len(examples)<2:
            examples.append(dict(case=case,target_counter=bytes.fromhex(target['actor'])[0x364:0x366].hex(),
                                 previous_counter=bytes.fromhex(values[1]['actor'])[0x364:0x366].hex(),
                                 selected_counter=bytes.fromhex(selected['actor'])[0x364:0x366].hex()))
    delta=branch_delta(args.previous_object,args.object) if args.previous_object else None
    report=dict(target_sha256=base.c.verify_target(),actual_returns=len(cases),
                objects=[dict(path=str(obj),sha256=base.lp.sha(obj),raw_differing_fields=dict(diff),
                              final_state_differences=n,phase_count_write_cases=p)
                         for obj,diff,n,p in zip(objects,raw,final,state_changes)],
                selected_known_alpha_x_store_reorders=reordered,examples=examples,canonical_delta=delta,
                input_sha256=hashlib.sha256(json.dumps(cases).encode()).hexdigest(),
                lookup={k:v for k,v in receipt.items() if k!='trace'},
                scope='861 nonzero sequences1..4 through original animation/math RET; complete final effects and explicit phase/count-write exclusion; known two-disjoint-write alpha/X scheduling difference reported, not ordered equivalence; no seq0 random/spawn, arbitrary resources, unmasked exceptions or whole-root proof')
    args.output.parent.mkdir(parents=True,exist_ok=True)
    args.output.write_text(json.dumps(report,indent=2)+'\n');print(json.dumps(report,indent=2))


if __name__=='__main__':main()
