#!/usr/bin/env python3
"""Observe Aya853/861 scale additions against original root execution."""
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
spec = importlib.util.spec_from_file_location('aya_scale_math', ROOT / 'scripts/audit-aya-object-903-native.py')
math = importlib.util.module_from_spec(spec)
sys.modules[spec.name] = math
spec.loader.exec_module(math)
base = math.base


def x87(uc):
    tag = uc.reg_read(base.r.UC_X86_REG_FPTAG)
    return dict(status=uc.reg_read(base.r.UC_X86_REG_FPSW), tag=tag,
                live=[None if (tag >> (2*i)) & 3 == 3
                      else uc.reg_read(getattr(base.r, 'UC_X86_REG_FP'+str(i))) for i in range(8)])


class Probe(math.Probe):
    def prepare(self, case):
        action, seq, scale, growth, alpha, phase, cw = self.settings
        assert self.action_id == action
        for off, fmt, value in ((0x11C, 'I', scale), (0x120, 'I', 0x3F800001),
                               (0x370, 'I', growth), (0x113, 'B', alpha),
                               (0x144, 'i', 1)):
            self.uc.mem_write(base.OWNER+off,struct.pack('<'+fmt,value))
        # Owner position usesEC/F0, outside the actor's own388-byte extent.
        self.uc.mem_write(base.OWNER+0x10EC,struct.pack('<ff',640.0,100.0))
        self.scale_stores = []

    def write(self, uc, access, address, size, value, data):
        if address in (base.OWNER+0x11C,base.OWNER+0x120) and size == 4:
            self.scale_stores.append(dict(offset=hex(address-base.OWNER),value=value & 0xFFFFFFFF,**x87(uc)))
        super().write(uc,access,address,size,value,data)

    def read(self, uc, access, address, size, value, data):
        # This audit scopes scale-store snapshots, not the already-known alpha-read epochs.
        pass

    def evaluate(self, case):
        self.settings = case
        action, seq, scale, growth, alpha, phase, cw = case
        out = base.Probe.run(self,(seq,phase,100,cw,20.0))
        assert out['stop'] == 'ret' and len(self.scale_stores) == 2
        out['scale_stores'] = self.scale_stores
        return out


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--object',type=Path,default=ROOT/base.unit['object'])
    parser.add_argument('--control-object',type=Path)
    parser.add_argument('--diagnostic',action='store_true',help='Report all differences; do not claim target agreement')
    parser.add_argument('--output',type=Path,default=ROOT/'build/aya-scale-adds.json')
    args=parser.parse_args()
    table,receipt=math.lookup_fixture(base.c)
    cws=(0x27F,0x67F,0xA7F,0xE7F,0x37F,0x77F,0xB7F,0xF7F)
    bits=(0,0x80000000,1,0x80000001,0x3F800000,0x3F800001,0xBF800000,0xBF800001,
          0x7F7FFFFF,0xFF7FFFFF,0x7F800000,0xFF800000,0x7FC00123,0xFFC00456,0x7F800001,0xFF800002)
    cases=[(action,seq,scale,growth,20,0,cw)
           for (action,seq),scale,growth,cw in itertools.product(((853,2),(853,3),(861,1)),bits,bits,cws)]
    cases += [(action,seq,scale,growth,alpha,phase,cw)
              for (action,seq),scale,growth,alpha,phase,cw in itertools.product(
                  ((853,2),(853,3),(861,1)),(0x3F800001,),(0x3DCCCCCD,),
                  (0,15,16,255),(0,1,6),(0x27F,0x37F))]
    objects=[args.object]+([args.control_object] if args.control_object else [])
    probes={action:[Probe(table)]+[Probe(table,obj) for obj in objects] for action in (853,861)}
    for action,items in probes.items():
        for p in items:p.action_id=action
    diffs={action:[Counter() for _ in objects] for action in probes}
    counts,calls,examples=Counter(),Counter(),[]
    for case in cases:
        action=case[0]; values=[p.evaluate(case) for p in probes[action]]
        counts.update([str(action)]);calls.update(hex(a) for a in values[0]['calls'])
        for i,val in enumerate(values[1:]):
            fields=[k for k in values[0] if val[k]!=values[0][k]]
            diffs[action][i].update(fields)
            if fields and len(examples)<3:
                examples.append(dict(case=case,object=i,fields=fields,
                                     actor_difference_offsets=[hex(j) for j,(a,b) in enumerate(zip(bytes.fromhex(values[0]['actor']),bytes.fromhex(val['actor']))) if a!=b],
                                     target=values[0]['scale_stores'],candidate=val['scale_stores']))
    report=dict(target_sha256=base.c.verify_target(),actual_returns=len(cases),counts=dict(counts),
                objects=[dict(path=str(obj),sha256=base.lp.sha(obj),
                              differences={str(action):dict(diffs[action][i]) for action in diffs}) for i,obj in enumerate(objects)],
                examples=examples,target_calls=dict(calls),
                lookup={k:v for k,v in receipt.items() if k!='trace'},
                input_sha256=hashlib.sha256(json.dumps(cases).encode()).hexdigest(),
                scope='853 sequence2/3 and861 sequence1 original root/frame returns; store snapshots and complete effects; finite owner positions and masked x87; no spawn, arbitrary resources, unmasked exceptions or full-root proof')
    args.output.parent.mkdir(parents=True,exist_ok=True)
    args.output.write_text(json.dumps(report,indent=2)+'\n');print(json.dumps(report,indent=2))
    if not args.diagnostic and any(d for items in diffs.values() for d in items):raise SystemExit(1)


if __name__=='__main__':main()
