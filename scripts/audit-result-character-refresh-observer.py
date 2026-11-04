#!/usr/bin/env python3
"""Bounded result portrait/list refresh with mocked providers."""
import sys,struct,hashlib,importlib.util,subprocess
sys.path.insert(0,'scripts')
import unicorn as uc, pefile
from unicorn import x86_const as reg
from workflow_manifest import ROOT,load_manifest
A=0x447080; O=0x1000000; S=0x200f000; STOP=0x710000
subprocess.run([sys.executable, str(ROOT / 'scripts/build.py'), '--unit', 'exact-first-result-character-refresh', '--json'], cwd=ROOT, check=True, stdout=subprocess.DEVNULL)
unit=load_manifest()['units']['exact-first-result-character-refresh'];f=unit['functions'][0]
spec=importlib.util.spec_from_file_location('cmp',ROOT/'scripts/compare-function.py');c=importlib.util.module_from_spec(spec);spec.loader.exec_module(c);c.verify_target();targets=c.known_targets()
for mapping in f['rel32_targets']:
 symbol,address=mapping.rsplit('=',1);targets[symbol]=int(address,0)
cand=c.coff_symbol_bytes(ROOT/unit['object'],f['symbol_base'],A,0xffffffff,targets,c.known_data_targets(),{})
native=c.target_bytes(A,342);image=pefile.PE(str(c.TARGET)).get_memory_mapped_image()
if (len(native) != 342 or len(cand) != 342
    or hashlib.sha256(native).hexdigest() != '3e393e363d311dc2cc8f81649b9224c8f4ec66a61dd69f4f3f52170e9eebf532'
    or hashlib.sha256(cand).hexdigest() != 'f8217a94cf5856bd9fc3bee48ee8f464ed006d0ce9df852686c269ec73418d10'):
 raise ValueError('body changed: review fixture')
def run(code,char,old,handle,init,count,input_present):
 e=uc.Uc(uc.UC_ARCH_X86,uc.UC_MODE_32);e.mem_map(0x400000,0x400000);e.mem_write(0x400000,image);e.mem_map(O,0x10000);e.mem_map(0x2000000,0x10000);e.mem_write(A,code)
 def put(a,v):e.mem_write(a,struct.pack('<I',v&0xffffffff))
 def get(a):return struct.unpack('<I',e.mem_read(a,4))[0]
 def readstr(a):
  b=bytes(e.mem_read(a,200));return b.split(b'\0',1)[0].decode('ascii')
 sprite=0x710100;color=0x710110;populate=0x710120;ws=0x710130
 put(0x6c01d8,ws);put(O+8,O+0x2000);put(O+0x2000+0x14,sprite);put(O+0x2000+4,color)
 listp=O+0xc8+char*0x108;put(listp,O+0x2100);put(O+0x2104,populate)
 put(O+4,old);put(O+0xc4,char);e.mem_write(O+0x1040+char,bytes([init]));put(0x6fd030,O+0x3000 if input_present else 0)
 for off in (0x108c,0x1090,0x1094,0x1098,0x109c):put(O+off,0xcccccccc)
 put(S,STOP);e.reg_write(reg.UC_X86_REG_ESP,S);e.reg_write(reg.UC_X86_REG_ECX,O)
 events=[];stopped=[]
 def hook(e,a,size,data):
  if a==STOP:stopped.append(1);e.emu_stop();return
  if a not in (0x404d70,0x43bf80,ws,0x404c90,sprite,color,populate,0x4395e0,0x689d25):return
  sp=e.reg_read(reg.UC_X86_REG_ESP);ret=get(sp);receiver=e.reg_read(reg.UC_X86_REG_ECX);args=lambda n:tuple(get(sp+4+4*i) for i in range(n));pop=0
  if a==0x404d70: events.append(('release',*args(1)));pop=4
  elif a==0x43bf80:events.append(('name',*args(1)));e.reg_write(reg.UC_X86_REG_EAX,0x710200);e.mem_write(0x710200,b'test\0')
  elif a==ws:
   ptr,fmt,name=args(3);events.append(('format',readstr(name)));e.mem_write(ptr,b'data/stand/test.bmp\0')
  elif a==0x404c90:
   out,path,w,h=args(4);events.append(('load',readstr(path),w,h));put(out,handle);e.reg_write(reg.UC_X86_REG_EAX,out);pop=16
  elif a==sprite:events.append(('sprite',receiver-O,*args(5)));pop=20
  elif a==color:events.append(('color',receiver-O,*args(1)));pop=4
  elif a==populate:events.append(('populate',receiver-O,get(receiver+0xb4)))
  elif a==0x4395e0:events.append(('count',receiver-O));e.reg_write(reg.UC_X86_REG_EAX,count)
  e.reg_write(reg.UC_X86_REG_ESP,sp+4+pop);e.reg_write(reg.UC_X86_REG_EIP,ret)
 e.hook_add(uc.UC_HOOK_CODE,hook);e.emu_start(A,STOP+1,count=10000)
 if not stopped:raise Exception('no return')
 return events,get(O+4),bytes(e.mem_read(O+0x1040+char,1))[0],tuple(get(O+x) for x in (0x108c,0x1090,0x1094,0x1098,0x109c)),e.reg_read(reg.UC_X86_REG_ESP)-S
CASES = [(0,9,4,0,3,1),(1,7,0,1,0,0),(14,0,5,1,2,0),
         (4,4,0,0,0,1),(7,2,8,0,1,0),(3,2,0,1,5,1)]

def expected(char, old, handle, init, count, input_present):
 events=[('release',old),('name',char),('format','test'),('load','data/stand/test.bmp',0,0)]
 if handle:
  events += [('sprite',8,handle,0,0,512,480),('color',8,0xff808080)]
 list_offset=0xc8+char*0x108
 if not init: events.append(('populate',list_offset,char))
 events.append(('count',list_offset))
 cursor=(0xcccccccc,)*5
 if count:
  events.append(('count',list_offset))
  cursor=(count,16,O+0x303c if input_present else 0,0,0)
 return events,handle,1,cursor,4

if __name__ == '__main__':
 for args in CASES:
  assert run(native,*args) == run(cand,*args) == expected(*args), args
 print('6 bounded native/source/model traces agree; mocked providers, valid characters 0-14 only')
