#!/usr/bin/env python3
"""Execute native and real CIL key insertion, mocking only allocator/CRT calls."""
import copy, hashlib, json, sys, pefile, struct, unicorn as uc, importlib.util
sys.path.insert(0,'scripts')
from unicorn import x86_const as r
from workflow_manifest import ROOT, load_manifest
import linked_pe as core
s=importlib.util.spec_from_file_location('c',ROOT/'scripts/compare-function.py');c=importlib.util.module_from_spec(s);s.loader.exec_module(c)
UNIT = copy.deepcopy(load_manifest()['units']['exact-first-input-state-update'])
UNIT['object'] = 'build/frontier-input-add-key-cil-20261104/Actual.dll'
UNIT['preserve_public_members'] = []
ROOT_SYMBOL = '?add_tracked_key@InputStateTableStorage@th105@@QAEXE@Z'
INSERT_SYMBOL = '?_Insert_n@?$vector@EV?$allocator@E@std@@@std@@IAEXV?$_Vector_iterator@EV?$allocator@E@std@@@2@IABE@Z'
UNIT['functions'] = [{'address':'0x0040A6C0', 'symbol_base':ROOT_SYMBOL,
    'rel32_targets':['__invalid_parameter_noinfo=0x0068A143',
    '?_Xran@?$vector@EV?$allocator@E@std@@@std@@KAXXZ=0x0040A8A0',
    '?insert@?$vector@EV?$allocator@E@std@@@std@@QAE?AV?$_Vector_iterator@EV?$allocator@E@std@@@2@V32@ABE@Z=0x0040A7F0']}]
TARGET_PINS = ((0x40a6c0,202,'d216475e7dc02c57563922b36657dd6c8c3d58912cea295102f81b1b839f7839'),
               (0x40a7f0,126,'1ea2f5cd068bbdbd960ee4d3a4d20bec5561d00fe07a82463e68be92b150dae8'),
               (0x40a920,462,'852d8c80187e61675ed8712523a59a650105b5765cf216cbdcfaf33918da9383'),
               (0x40a870,37,'8bbbef0be2e23ce24bd7e6338853bb0bda4b5a5cf97b31259c0543bff0d145f8'),
               (0x40ab70,65,'4cf60ac8817bdd958602d933636a912d35906d3c717aa28ce2dbb5e050e6f882'))
CASES = (((),0), ((5,),6), ((0,127,255),9), ((1,2,3,4),5),
         ((1,2,3,4,5,6),7), ((5,),5))

def prepare():
 c.verify_target()
 core.build_linked('private-input-add-key-cil', UNIT)
 pe = pefile.PE(str(ROOT / UNIT['object']))
 map_text = (ROOT / UNIT['object']).with_suffix('.map').read_text()
 functions = core.parse_map(map_text)
 symbols = core.parse_map_symbols(map_text)
 def address(name):
  entries = symbols.get(name, [])
  if len(entries) != 1: raise ValueError('linked symbol missing or ambiguous: ' + name)
  return entries[0][0]
 root, insertion = address(ROOT_SYMBOL), address(INSERT_SYMBOL)
 for va, size, digest in TARGET_PINS:
  if hashlib.sha256(c.target_bytes(va,size)).hexdigest() != digest:
   raise ValueError('native insertion body changed')
 for va, size, digest in ((root,269,'e28dc0eb027db53dfcccec8c3c938fadd5babffaf17e3863d675f62070c0800c'),
                          (insertion,461,'4bb681972367ea120a1c034d06ae18b033079f3ddf6ba36bf44675ea76d1fde4')):
  body = core.linked_body(pe,functions,va)
  if len(body) != size or hashlib.sha256(body).hexdigest() != digest:
   raise ValueError('linked insertion body changed')
 providers = {key: address(name) for key,name in (
  ('new','??2@YAPAXI@Z'), ('delete','??3@YAXPAX@Z'),
  ('move','_memmove_s'), ('memset','_memset'), ('bad','__invalid_parameter_noinfo'))}
 native = pefile.PE(str(c.TARGET)).get_memory_mapped_image()
 return native, pe.get_memory_mapped_image(), root, providers

OWNER=0x1000000; BUF=OWNER+0x2000; NEW=OWNER+0x8000; STACK=0x200f000; STOP=0x710000

def run(images,native,values,key,mutate=False):
 native_image, source_image, root, providers = images
 e=uc.Uc(uc.UC_ARCH_X86,uc.UC_MODE_32);e.mem_map(0x400000,0x400000);e.mem_write(0x400000,native_image);e.mem_map(0x10000000,0x10000);e.mem_write(0x10000000,source_image);e.mem_map(OWNER,0x10000);e.mem_map(0x2000000,0x10000)
 def put(a,v):e.mem_write(a,struct.pack('<I',v&0xffffffff))
 def get(a):return struct.unpack('<I',e.mem_read(a,4))[0]
 start=BUF if values else 0;end=start+len(values) if values else 0
 put(OWNER+0x404,start);put(OWNER+0x408,end);put(OWNER+0x40c,end)
 if values:e.mem_write(BUF,bytes(values))
 put(STACK,STOP);put(STACK+4,key);e.reg_write(r.UC_X86_REG_ESP,STACK);e.reg_write(r.UC_X86_REG_ECX,OWNER)
 if mutate:
  if native: raise ValueError('mutation applies only to source fixture')
  if bytes(e.mem_read(root + 0x64, 2)) != bytes.fromhex('0f84'): raise ValueError('duplicate gate changed')
  e.mem_write(root + 0x65, b'\x85')
 events=[];stop=[];new=(0x689dcb,providers['new']);delete=(0x6898ea,providers['delete']);move=(0x689eb0,providers['move']);memset=(0x68a440,providers['memset']);bad=(0x68a143,providers['bad'])
 def hook(e,a,size,_):
  if a==STOP:stop.append(1);e.emu_stop();return
  if a in bad:raise ValueError('invalid param')
  if a not in new+delete+move+memset:return
  sp=e.reg_read(r.UC_X86_REG_ESP);ret=get(sp);args=lambda n:tuple(get(sp+4*i) for i in range(1,n+1))
  if a in new:
   n=args(1)[0];events.append(('new',n));e.reg_write(r.UC_X86_REG_EAX,NEW)
  elif a in delete:events.append(('delete',args(1)[0]))
  elif a in move:
   dest,sz,src,count=args(4);events.append(('move',sz,count));assert count<=sz;e.mem_write(dest,bytes(e.mem_read(src,count)));e.reg_write(r.UC_X86_REG_EAX,0)
  else:
   dest,value,count=args(3);events.append(('set',value,count));e.mem_write(dest,bytes([value&255])*count);e.reg_write(r.UC_X86_REG_EAX,dest)
  e.reg_write(r.UC_X86_REG_ESP,sp+4);e.reg_write(r.UC_X86_REG_EIP,ret)
 e.hook_add(uc.UC_HOOK_CODE,hook)
 e.emu_start(0x40a6c0 if native else root,STOP+1,count=50000)
 if not stop:raise ValueError('no return')
 first,last,cap=(get(OWNER+x) for x in (0x404,0x408,0x40c))
 return bytes(e.mem_read(first,last-first)) if first else b'',last-first if first else 0,cap-first if first else 0,events,e.reg_read(r.UC_X86_REG_ESP)-STACK

def expected(values, key):
 duplicate = key in values
 if duplicate:
  return bytes(values), len(values), len(values), [], 8
 n = len(values)
 capacity = max(n + 1, n + n // 2)
 events = [('new', capacity)]
 if n: events += [('move', n, n), ('delete', BUF)]
 return bytes((*values, key)), n + 1, capacity, events, 8


def audit():
 images = prepare()
 for values, key in CASES:
  if run(images,True,values,key) != expected(values,key) or run(images,False,values,key) != expected(values,key):
   raise ValueError('real insertion trace differs for ' + repr((values,key)))
 return {'cases':len(CASES), 'result':'bounded_traces_agree',
         'limitations':'native and real CIL insertion execute; allocator and CRT memory operations mocked; no failure, OS or full game'}

if __name__ == '__main__':
 print(json.dumps(audit(), indent=2))
