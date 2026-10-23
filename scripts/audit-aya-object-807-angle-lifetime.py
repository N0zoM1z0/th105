#!/usr/bin/env python3
"""Execute Aya807 and observe the live angle across its alpha write."""
from pathlib import Path
from collections import Counter
import argparse
import hashlib
import importlib.util
import itertools
import json
import struct
import sys

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location('aya807_gate', ROOT / 'scripts/audit-aya-object-804-sequence-read.py')
gate = importlib.util.module_from_spec(spec)
sys.modules[spec.name] = gate
spec.loader.exec_module(gate)
base, math = gate.base, gate.math


class Probe(gate.Probe):
    action_id = 807

    def prepare(self, case):
        seq,phase,owner_action,counter,time,alpha,angle,cw = self.settings
        for off,fmt,val in ((0x384,'h',counter),(0x144,'i',time),(0x113,'B',alpha),
                            (0x12C,'I',angle),(0x11C,'I',0x3F800001),(0x120,'I',0x3F800001)):
            self.uc.mem_write(base.OWNER+off,struct.pack('<'+fmt,val))
        self.uc.mem_write(base.OWNER+0x113C,struct.pack('<h',owner_action))
        self.sequence_reads,self.alpha_stores,self.effect,self.spawn = [],[],None,None

    def step(self, uc, pc, size, data):
        if pc == 0x435240:
            sp = uc.reg_read(base.r.UC_X86_REG_ESP)
            assert uc.reg_read(base.r.UC_X86_REG_ECX) == base.OWNER
            self.effect=list(struct.unpack('<5I',uc.mem_read(sp+4,20)))
            assert self.effect[0]==201 and self.effect[4]==1
            self.stop='original_effect_entry';uc.emu_stop();return
        if pc == 0x465190:
            sp = uc.reg_read(base.r.UC_X86_REG_ESP)
            assert uc.reg_read(base.r.UC_X86_REG_ECX) == base.OWNER+0x1000
            words=list(struct.unpack('<7I',uc.mem_read(sp+4,28)))
            assert words[0]==807 and words[4]==1 and words[6]==3
            payload=bytes(uc.mem_read(words[5],12)).hex(); words[5]='payload'
            self.spawn=dict(arguments=words,payload=payload)
            self.stop='original_owner_spawn_entry';uc.emu_stop();return
        super().step(uc,pc,size,data)

    def write(self, uc, access, address, size, value, data):
        if address == base.OWNER+0x113 and size == 1:
            tag=uc.reg_read(base.r.UC_X86_REG_FPTAG)
            self.alpha_stores.append(dict(value=value & 255,writes=len(self.writes),
                angle=bytes(uc.mem_read(base.OWNER+0x12C,4)).hex(),status=uc.reg_read(base.r.UC_X86_REG_FPSW),tag=tag,
                live=[None if (tag >> (2*i)) & 3 == 3
                      else uc.reg_read(getattr(base.r,'UC_X86_REG_FP'+str(i))) for i in range(8)]))
        super().write(uc,access,address,size,value,data)

    def evaluate(self, case):
        self.settings=case
        seq,phase,owner_action,counter,time,alpha,angle,cw=case
        out=base.Probe.run(self,(seq,phase,100,cw,20.0))
        assert out['stop'] in ('ret','original_effect_entry','original_owner_spawn_entry')
        out.update(sequence_reads=self.sequence_reads,alpha_stores=self.alpha_stores,
                   effect_entry_arguments=self.effect,spawn_entry=self.spawn)
        return out


def canonical(obj):
    co=base.mapper.CoffObject(obj,symbol_base=base.f['symbol_base'])
    return base.c.coff_symbol_bytes(obj,base.f['symbol_base'],base.A,len(co.text),
        {a:int(b,0) for a,b in (z.split('=',1) for z in base.f['rel32_targets'])},base.c.known_data_targets(),
        dict(z.split('=',1) for z in base.f.get('dir32_targets',[])))


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--object',type=Path,default=ROOT/base.unit['object'])
    parser.add_argument('--previous-object',type=Path)
    parser.add_argument('--allow-sequence-read-differences',action='store_true',
                        help='Check effects and alpha-store snapshots while reporting unresolved sequence reads')
    parser.add_argument('--output',type=Path,default=ROOT/'build/aya807-angle.json')
    args=parser.parse_args()
    table,receipt=math.lookup_fixture(base.c)
    cws=(0x27F,0x67F,0xA7F,0xE7F,0x37F,0x77F,0xB7F,0xF7F)
    angles=(0,0x80000000,1,0x80000001,0x3F800000,0x3F800001,0xBF800000,0xBF800001,
            0x7F7FFFFF,0xFF7FFFFF,0x7F800000,0xFF800000,0x7FC00123,0xFFC00456,0x7F800001,0xFF800002)
    cases=list(itertools.product((1,),(0,),(49,),(0,),(1,),(0,15,16,255),angles,cws))
    cases+=list(itertools.product((0,1,2,3),(0,1,5,6),(49,50,149,150),(3,4,32767),
                                  (0,1,5),(15,16,255),(0x3F800001,),(0x27F,0x37F)))
    objects=([args.previous_object] if args.previous_object else [])+[args.object]
    probes=[Probe(table)]+[Probe(table,obj) for obj in objects]
    diffs=[Counter() for _ in objects];stops,calls=Counter(),Counter();examples=[];stores=0
    for case in cases:
        values=[p.evaluate(case) for p in probes];target=values[0]
        stops.update([target['stop']]);calls.update(hex(a) for a in target['calls']);stores+=len(target['alpha_stores'])
        for i,val in enumerate(values[1:]):
            fields=[k for k in target if target[k]!=val[k]];diffs[i].update(fields)
            if 'alpha_stores' in fields and len(examples)<2:
                examples.append(dict(case=case,object=i,target=target['alpha_stores'],candidate=val['alpha_stores']))
        # Sequence snapshot recovery is separate; retain its differences without accepting other mismatches.
        allowed={'sequence_reads'} if args.allow_sequence_read_differences else set()
        assert not any(k not in allowed for k in target if target[k]!=values[-1][k])
    code=canonical(args.object);window=base.c.target_bytes(0x61A86D,26)
    assert code.count(window)==1,'unique original FLD/SUB/FADD/alpha-store/angle-store interval missing'
    delta=None
    if args.previous_object:
        old=canonical(args.previous_object)
        assert old.count(window)==0 and len(old)==len(code)
        changed=[dict(offset=hex(i),old=a,new=b) for i,(a,b) in enumerate(zip(old,code)) if a!=b]
        start=code.index(window)
        assert old[:start]==code[:start] and old[start+26:]==code[start+26:], 'other canonical bytes changed'
        delta=dict(previous_sha256=hashlib.sha256(old).hexdigest(),changed_bytes=changed,
                   scope='all complete-payload changes stay within the recovered26-byte interval')
    report=dict(target_sha256=base.c.verify_target(),cases=len(cases),target_stops=dict(stops),alpha_store_snapshots=stores,
                objects=[dict(path=str(obj),sha256=base.lp.sha(obj),differing_fields=dict(diff)) for obj,diff in zip(objects,diffs)],
                selected_canonical_sha256=hashlib.sha256(code).hexdigest(),full_size=len(code),
                sequence_reads_required=not args.allow_sequence_read_differences,
                matched_window=dict(target='0x61a86d',size=26,selected=hex(base.A+code.index(window)),sha256=hashlib.sha256(window).hexdigest()),
                canonical_delta=delta,examples=examples,target_calls=dict(calls),
                lookup={k:v for k,v in receipt.items() if k!='trace'},
                input_sha256=hashlib.sha256(json.dumps(cases).encode()).hexdigest(),
                scope='807 actual root/gate/animation RET and original effect/owner-spawn entry prefixes; live angle at alpha stores; unresolved sequence reads reported separately; masked x87 only, no fabricated return, full spawn/effect, arbitrary resources, unmasked exceptions or whole-root proof')
    args.output.parent.mkdir(parents=True,exist_ok=True)
    args.output.write_text(json.dumps(report,indent=2)+'\n');print(json.dumps(report,indent=2))


if __name__=='__main__':main()
