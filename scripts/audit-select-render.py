#!/usr/bin/env python3
"""Complete CSelect renderer source/target diagnostic with isolated call observers."""
import importlib.util
import json
from pathlib import Path
import struct
import sys
import capstone
import pefile
from unicorn import Uc, UC_ARCH_X86, UC_MODE_32, UC_HOOK_CODE
from unicorn.x86_const import *
import linked_pe as core
from linked_logic_error_origins import require, digest
from native_callbacks import guarded_callback
from workflow_manifest import ROOT, load_manifest, unit_input_digest, compiler_sha256
ADDRESS, SIZE = 0x41ff00, 1497
SHA = 'd1bb636ab500206ab3ddf487b45ebd2a9dec4a1b8f3e16f479df1966ee8279ae'
UNIT = 'exact-first-select-render'

def check_shape(size,count,unreachable,returns):
    require(size==1497 and count==421,'select complete instruction extent differs')
    require(unreachable=={0x420068:bytes.fromhex('8da42400000000'),0x42006f:b'\x90'},'select exact compared alignment differs')
    require(returns=={0x41ff18:b'\xc3',0x4204d8:b'\xc3'},'select complete RET0 paths differ')

def cfg(code):
    md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);md.detail=True;instructions=list(md.disasm(code,ADDRESS))
    require(sum(i.size for i in instructions)==len(code),'select partial instruction')
    by={i.address:i for i in instructions};pending=[ADDRESS];reached=set();returns={}
    while pending:
        at=pending.pop()
        if at in reached:continue
        require(at in by,'select escaping or mid-instruction edge');i=by[at];reached.add(at)
        if i.group(capstone.CS_GRP_RET):returns[at]=bytes(i.bytes);continue
        if i.group(capstone.CS_GRP_JUMP):
            require(i.operands[0].type==capstone.x86.X86_OP_IMM,'select unknown indirect jump');pending.append(i.operands[0].imm)
            if i.id==capstone.x86.X86_INS_JMP:continue
        require(not i.group(capstone.CS_GRP_INT),'select unexpected trap')
        pending.append(at+i.size)
    unreachable={i.address:bytes(i.bytes)for i in instructions if i.address not in reached}
    check_shape(len(code),len(instructions),unreachable,returns)
    require(code[0x166:0x170]==bytes.fromhex('eb088da4240000000090'),'select skipped alignment branch differs')
    return dict(instructions=len(instructions),reachable_instructions=len(reached),compared_alignment_bytes=8,returns=[hex(a)for a in returns])

def check_events(events,begin,mix,transition):
    require(len(events)==(1 if not begin else 30 if not mix else 79),'select bounded call census differs')
    require(events[0]['kind']=='begin','select frame must begin first')
    if not begin:return
    require(events[-1]['kind']=='finish','select frame must finish last')
    tiles=[e['args'][2:]for e in events if e['kind']=='tile']
    require(tiles==([[0,10]] if not mix else [[0,i]for i in [10,15,0,1,17,3,4,5]]),'select character/random/music row arguments differ')
    if mix:
        colors=[e['args'][0]for e in events if e['kind']=='color'];require(len(colors)==25,'select full color publication count differs')
        expected=0x5fffffff if (mix,transition)==(127,.25) else 0x7fffffff
        require(colors[-3:]==[expected]*3,'select byte-valued alpha differs')

def observe(image,code,begin=True,mix=127,transition=.25,mutate_table=False):
 m=Uc(UC_ARCH_X86,UC_MODE_32);m.mem_map(0x400000,(len(image)+4095)&~4095);m.mem_write(0x400000,image);m.mem_write(0x41ff00,code)
 m.mem_map(0,0x10000);m.mem_map(0x800000,0x40000);m.mem_map(0x1000000,0x20000);m.mem_map(0xf00000,0x1000);m.mem_write(0xf00000,b'\xc3'*0x1000)
 w=lambda a,v:m.mem_write(a,struct.pack('<I',v&0xffffffff));r=lambda a:struct.unpack('<I',m.mem_read(a,4))[0];wf=lambda a,v:m.mem_write(a,struct.pack('<f',v))
 obj=0x801000;spritevt=0x830000;designvt=0x830100;effectvt=0x830200
 stubs={0x401000:('begin',0,begin),0x404750:('mode',4,0),0x4012a0:('rect',24,0),0x4099f0:('tile',16,0),0x43f900:('overlay',0,0),0x43f4c0:('guide',0,0),0x401040:('finish',0,0),0xf00100:('color',4,0),0xf00110:('sprite',8,0),0xf00120:('design-through',4,0),0xf00130:('design',0,0),0xf00140:('effect',4,0)}
 w(spritevt+4,0xf00100);w(spritevt+0x1c,0xf00110);w(designvt+4,0xf00100);w(designvt+0x20,0xf00120);w(designvt+0x24,0xf00130);w(effectvt+0x18,0xf00140)
 for off in [0x18c,0x220,0x2b8,0x3f8,0x494,0x528,0x2cd0]+[base+0x94*i for base in [0x1a38,0x2378]for i in range(16)]:w(obj+off,spritevt)
 for off in [0x150,0x1984]:w(obj+off,designvt)
 for i in range(16):
  node=0x808000+i*0x100;w(obj+0x5bc+i*4,node);w(node,spritevt);wf(node+0xc,20.+i*8);wf(node+0x10,30.+i*4);m.mem_write(node+0x14,bytes([i%3!=0]))
 for off in [0x5fc,0x604,0x610,0x2cb8,0x2cbc,0x2cc0,0x2cc4,0x2cc8,0x2d74]:
  count=2 if off in [0x5fc,0x604,0x610]else 1
  for i in range(count):
   node=0x810000+off*8+i*0x100;w(obj+off+i*4,node);w(node,spritevt);wf(node+0xc,100.+i*30);wf(node+0x10,200.+i*20);m.mem_write(node+0x14,b'\x01')
 for i in range(2):w(obj+0x1954+i*4,0x82d000+i*0x100);w(0x82d000+i*0x100,effectvt);w(obj+0x48c+i*4,100+i)
 m.mem_write(obj+0x90,b'\x01\x01');m.mem_write(obj+0x2d78,bytes([mix]));wf(obj+0x2d80,transition);w(obj+0x94,16);w(obj+0x195c+12,2);w(obj+0x1970+12,1)
 for off,v in [(0x10c,1),(0x120,2),(0x134,3),(0x148,3)]:w(obj+off,v)
 if mutate_table:w(0x6e61c8+60,0)
 stack=0x1010004;w(stack,0xf00000);saved={UC_X86_REG_EBP:0x12345678,UC_X86_REG_EBX:0x22334455,UC_X86_REG_ESI:0x33445566,UC_X86_REG_EDI:0x44556677}
 for rg,v in {**saved,UC_X86_REG_ESP:stack,UC_X86_REG_ECX:obj,UC_X86_REG_FPCW:0x37f,UC_X86_REG_FPTAG:0xffff}.items():m.reg_write(rg,v)
 events=[]
 def hook(u,at,size,data):
  if at==0xf00000:u.emu_stop();return
  if at not in stubs:
   require(ADDRESS<=at<ADDRESS+SIZE,'unobserved helper execution');return
  name,pop,value=stubs[at];ss=u.reg_read(UC_X86_REG_ESP);argbytes=4 if name=='overlay'else pop;args=list(struct.unpack('<'+str(argbytes//4)+'I',u.mem_read(ss+4,argbytes)))if argbytes else[];receiver=u.reg_read(UC_X86_REG_ECX)if name!='overlay'else None;events.append(dict(kind=name,receiver=receiver,args=args));u.reg_write(UC_X86_REG_EAX,int(value));u.reg_write(UC_X86_REG_ECX,0xbad0c0de);u.reg_write(UC_X86_REG_EDX,0xbad0dada);u.reg_write(UC_X86_REG_ESP,ss+4+pop);u.reg_write(UC_X86_REG_EIP,r(ss))
 hook_errors=[];m.hook_add(UC_HOOK_CODE,guarded_callback(hook,hook_errors))
 try:m.emu_start(0x41ff00,0,count=20000)
 except Exception as e:raise RuntimeError((str(e),hex(m.reg_read(UC_X86_REG_EIP)),events[-4:]))
 if hook_errors:raise ValueError("observer hook failed: "+repr(hook_errors))
 assert m.reg_read(UC_X86_REG_EIP)==0xf00000;assert m.reg_read(UC_X86_REG_ESP)==stack+4
 assert all(m.reg_read(rg)==v for rg,v in saved.items());assert m.reg_read(UC_X86_REG_EAX)&255==int(begin)
 return events

def audit():
    c=core.comparator();sha=c.verify_target();native=c.target_bytes(ADDRESS,SIZE);require(digest(native)==SHA,'select complete native body changed');shape=cfg(native)
    require(struct.unpack('<I',c.target_bytes(0x6c0bcc,4))[0]==ADDRESS and struct.unpack('<I',c.target_bytes(0x6c0bc0,4))[0]==0x6d78d0 and struct.unpack('<5I',c.target_bytes(0x6d78d0,20))[:4]==(0,0,0,0x6e6050) and c.target_bytes(0x6e6058,14)==b'.?AVCSelect@@\0','select native primary RTTI owner differs')
    ids=[0,2,5,1,3,6,7,4,8,10,11,9,12,13,14,15];require(c.target_bytes(0x6e61c8,64)==struct.pack('<16i',*ids),'select complete character/random table differs')
    u=load_manifest()['units'][UNIT];p=ROOT/u['object'];record=json.loads(p.with_suffix(p.suffix+'.provenance.json').read_text());expected,_=unit_input_digest(UNIT,u)
    require(record.get('unit')==UNIT and record.get('input_digest')==expected and record.get('compiler_sha256')==compiler_sha256() and record.get('object_sha256')==core.sha(p),'select fresh source/object provenance required')
    f=u['functions'][0];require(f['address']=='0x0041FF00' and f['symbol_base']=='?render@CSelect@th105@@UAE_NXZ','select actual virtual source owner differs');calls=c.known_targets()|{n:int(at,0)for n,at in (s.rsplit('=',1)for s in f['rel32_targets'])}
    candidate=c.coff_symbol_bytes(p,f['symbol_base'],ADDRESS,0xffffffff,calls,c.known_data_targets(),{})
    require(len(candidate)==SIZE,'select complete source body extent differs');source_shape=cfg(candidate)
    image=pefile.PE(str(c.TARGET)).get_memory_mapped_image();cases=[]
    for begin,mix,transition in [(False,127,.25),(True,0,.25),(True,127,.25),(True,255,-.5)]:
        target=observe(image,native,begin,mix,transition);source=observe(image,candidate,begin,mix,transition);check_events(target,begin,mix,transition);check_events(source,begin,mix,transition);require(target==source,'select bounded source/native observations differ');cases.append(dict(begin=begin,mix=mix,transition=transition,event_count=len(target),events=target))
    require(observe(image,candidate,True,127,.25,True)!=observe(image,native,True,127,.25),'select random-entry negative control was not detected')
    bad=bytearray(candidate);require(bad[11]==0xe8,'select first call role differs');struct.pack_into('<i',bad,12,0x40ac50-(ADDRESS+16))
    try:
        observe(image,bytes(bad),False,127,.25)
    except ValueError as error:
        require('unobserved helper execution' in str(error),'unexpected observer failure in guard control')
    else:
        raise ValueError('unknown-helper negative control was accepted')

    return dict(result='exact'if candidate==native else'mismatch',diagnostic_only=True,target_sha256=sha,unit=UNIT,cfg=shape,source_cfg=source_shape,source_size=len(candidate),candidate_sha256=digest(candidate),native_sha256=digest(native),unequal_bytes=sum(a!=b for a,b in zip(candidate,native)),first_mismatch=c.first_mismatch(native,candidate,ADDRESS),isolated_observer_cases=cases,random_entry_negative_rejected=True,unknown_helper_negative_rejected=True,scope='complete1497-byte comparison including alignment; bounded argument/control-flow observers, no rendering/helper/OS execution or universal semantic-equivalence claim; no exact credit for differing bytes')

if __name__=='__main__':
    try:
        result=audit();print(json.dumps(result,indent=2));raise SystemExit(result['result']!='exact')
    except (OSError,ValueError,KeyError,RuntimeError,struct.error)as exc:raise SystemExit(str(exc))
