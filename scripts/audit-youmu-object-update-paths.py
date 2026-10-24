#!/usr/bin/env python3
"""Check fourteen native930/3 prefixes for distance precision and NaN continuation.

Actual square/trig instructions run with zero-initialized and axis lookup
fixtures (cos0=1, sin0=0). Stop at the first spawn/frame/RET; inject no helper returns or edges.
This diagnostic is not a full-function behavior or exact-match claim.
--point900 checks four prefixes through actual bounds/phase/math helpers instead.
"""
from pathlib import Path
import argparse
import json,importlib.util,struct,hashlib,pefile,unicorn
from unicorn import x86_const as R
ROOT=Path(__file__).resolve().parents[1]
START=0x53CEA0
OWNER,STACK,PARENT,PARAM,TARGET,RETURN=0x1000000,0x2000000,0x3000000,0x3001000,0x3002000,0x710000
HELPERS={0x406580,0x406360,0x4063D0}

def execute(image,code,dx,dy_bits,cw,axis_lookup=False,point_facing=None):
 u=unicorn.Uc(unicorn.UC_ARCH_X86,unicorn.UC_MODE_32)
 u.mem_map(0x400000,(len(image)+4095)//4096*4096);u.mem_write(0x400000,image);u.mem_write(START,code)
 for a in (OWNER,STACK,PARENT):u.mem_map(a,65536)
 u.mem_map(RETURN,4096)
 def put(a,fmt,*v):u.mem_write(a,struct.pack('<'+fmt,*v))
 for o,f,v in ((0,'I',0x6C50BC),(0x13C,'h',930),(0x13E,'h',3),
               (0x144,'i',1),(0x180,'i',0),(0x330,'i',3),(0x104,'B',255),
               (0xEC,'f',dx),(0xF0,'I',dy_bits),(0x340,'I',PARAM),(0x348,'I',PARENT),
               (0x170,'I',TARGET),(0x113,'B',180),(0x184,'B',1),
               (0x11C,'f',1.),(0x120,'f',1.),(0xF4,'f',1.75),(0xF8,'f',-2.5)):
  put(OWNER+o,f,v)
 put(PARENT+0x174,'h',100);put(PARENT+0x7FC,'B',1)
 put(PARAM,'5f',37.25,10.,1.,45.,0.)
 put(0x6FA894,'i',1)
 if axis_lookup:put(0x6FE8B0,'f',1.0)
 if point_facing is not None:
  put(OWNER+0x13C,'h',900);put(OWNER+0x13E,'h',0)
  put(OWNER+0x104,'B',point_facing);put(OWNER+0x364,'h',1)
  put(OWNER+0x194,'I',PARENT+0x3000);put(OWNER+0x11C,'f',3.3125)
  put(PARENT+0x13C,'h',710);put(PARENT+0x730,'h',1)
  put(PARAM,'f',0.);put(TARGET+0xEC,'f',760.);put(TARGET+0xF0,'f',100.)
 put(STACK+0xFF00,'I',RETURN);u.reg_write(R.UC_X86_REG_ESP,STACK+0xFF00);u.reg_write(R.UC_X86_REG_ECX,OWNER)
 u.reg_write(R.UC_X86_REG_FPCW,cw);u.reg_write(R.UC_X86_REG_FPSW,0);u.reg_write(R.UC_X86_REG_FPTAG,0xFFFF)
 calls=[];result={}
 helpers=HELPERS if point_facing is None else {
  0x406360,0x4063D0,0x406540,0x68A1A0,0x4FC710,0x4963A0,0x64CD00}
 def hook(uc,a,n,unused):
  if a in helpers:calls.append(hex(a))
  if a not in (0x64CCB0,0x4351C0,RETURN):return
  result.update(boundary=hex(a),owner=bytes(uc.mem_read(OWNER,0x388)).hex(),calls=calls)
  if point_facing is not None:
   result['bounds']=bytes(uc.mem_read(PARENT+0x3000,24)).hex()
  if a==0x64CCB0:
   esp=uc.reg_read(R.UC_X86_REG_ESP);args=struct.unpack('<7I',uc.mem_read(esp+4,28))
   result['arguments']=[*args[:5],args[6]];result['receiver']=uc.reg_read(R.UC_X86_REG_ECX)
   result['payload']=bytes(uc.mem_read(args[5],args[6]*4)).hex()
  uc.emu_stop()
 u.hook_add(unicorn.UC_HOOK_CODE,hook);u.emu_start(START,RETURN+1,count=20000)
 if not result:raise ValueError('native prefix did not reach first spawn/frame/RET')
 return result

def main():
 parser=argparse.ArgumentParser(description=__doc__)
 parser.add_argument('--object',type=Path,help='override the configured COFF object')
 parser.add_argument('--point900',action='store_true',help='check four900/0 prefixes through first spawn')
 args=parser.parse_args()
 try:
  spec=importlib.util.spec_from_file_location('youmu_update_payload',ROOT/'scripts/audit-youmu-object-update.py')
  if spec is None or spec.loader is None:raise ValueError('payload comparator unavailable')
  payload=importlib.util.module_from_spec(spec);spec.loader.exec_module(payload)
  _,identity,candidate,target=payload.load_candidate(args.object)
  image=pefile.PE(str(ROOT/'resources/th105.exe')).get_memory_mapped_image()
  cases=((0.,0x42480000,False,0x64CCB0),
         (0.01,0x42480000,False,0x4351C0),
         (0.01,struct.unpack('<I',struct.pack('<f',49.99))[0],False,0x64CCB0),
         (0.,0x7FC00000,False,0x4351C0),
         (1000.,0x42480000,True,0x64CCB0),
         (1000.,0x42480001,True,0x4351C0),
         (1000.,struct.unpack('<I',struct.pack('<f',49.99))[0],True,0x64CCB0))
  results=[]
  if args.point900:
   for cw in (0x27F,0x37F):
    for facing in (1,255):
     expected=execute(image,target,640.,0x42C80000,cw,True,facing)
     actual=execute(image,candidate,640.,0x42C80000,cw,True,facing)
     if expected['boundary']!='0x64ccb0':raise ValueError('reviewed900 target spawn boundary changed')
     if expected['calls']!=['0x68a1a0','0x68a1a0','0x4fc710','0x4963a0','0x64cd00','0x4063d0','0x68a1a0','0x406360','0x68a1a0','0x406540']:
      raise ValueError('reviewed900 native helper trace changed')
     results.append(dict(facing=facing,control=cw,boundary=expected['boundary'],
       actual_boundary=actual['boundary'],differences=sorted(
        k for k in set(expected)|set(actual) if expected.get(k)!=actual.get(k))))
  else:
   for cw in (0x27F,0x37F):
    for dx,dy_bits,axis,want in cases:
     expected=execute(image,target,dx,dy_bits,cw,axis);actual=execute(image,candidate,dx,dy_bits,cw,axis)
     if int(expected['boundary'],0)!=want:raise ValueError('reviewed native target boundary changed')
     if expected['calls']!=['0x406580','0x406580','0x406360','0x4063d0','0x406580']:
      raise ValueError('reviewed native target helper trace changed')
     results.append(dict(dx=dx,dy_bits=f'0x{dy_bits:08X}',axis_lookup=axis,control=cw,
       boundary=expected['boundary'],actual_boundary=actual['boundary'],
       differences=sorted(k for k in set(expected)|set(actual) if expected.get(k)!=actual.get(k))))
  report=dict(diagnostic_only=True,target_sha256=identity,
    candidate_sha256=hashlib.sha256(candidate).hexdigest(),count=len(results),
    mismatch_count=sum(bool(r['differences'])for r in results),results=results,
    scope=('900/0 prefixes through actual bounds/six/phase/trig/atan2 to first spawn, preallocated descriptor and axis fixtures' if args.point900 else
           '930 sequence3 prefixes to first spawn/frame, actual square and trig helpers, zero-initialized and axis target lookup fixtures')+', no injected instructions/returns/edges')
 except (OSError,ValueError,unicorn.UcError,struct.error) as error:
  print(json.dumps(dict(result='blocked',error=str(error)),indent=2));return 1
 print(json.dumps(report,indent=2));return bool(report['mismatch_count'])
if __name__=='__main__':raise SystemExit(main())
