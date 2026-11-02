#!/usr/bin/env python3
"""Complete character-selection source/target comparison and bounded state observers."""
import json
from pathlib import Path
import struct
import capstone
import pefile
from unicorn import Uc, UC_ARCH_X86, UC_MODE_32, UC_HOOK_CODE
from unicorn.x86_const import *
import linked_pe as core
from native_callbacks import guarded_callback
from linked_logic_error_origins import require, digest
from workflow_manifest import ROOT, load_manifest, unit_input_digest, compiler_sha256
ADDRESS, SIZE = 0x41fc90, 619
SHA = 'a4bb43c20a44efc5f92ec5b027f9c52aa72fb633c1854f39090c8d62202d4e0c'
UNIT = 'exact-first-select-character-update'

def check_shape(size,count,unreachable,returns):
    require(size==619 and count==192,'character complete instruction extent differs')
    require(unreachable=={0x41fcba:bytes.fromhex('8d9b00000000')},'character exact compared alignment differs')
    require(returns=={a:b'\xc3'for a in [0x41fe2a,0x41feb1,0x41fed7,0x41fefa]},'character four RET0 paths differ')

def cfg(code):
    md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);md.detail=True;instructions=list(md.disasm(code,ADDRESS));require(sum(i.size for i in instructions)==len(code),'character partial instruction')
    by={i.address:i for i in instructions};pending=[ADDRESS];reached=set();returns={}
    while pending:
        at=pending.pop()
        if at in reached:continue
        require(at in by,'character escaping or mid-instruction edge');i=by[at];reached.add(at)
        if i.group(capstone.CS_GRP_RET):returns[at]=bytes(i.bytes);continue
        if i.group(capstone.CS_GRP_JUMP):
            require(i.operands[0].type==capstone.x86.X86_OP_IMM,'character unknown indirect jump');pending.append(i.operands[0].imm)
            if i.id==capstone.x86.X86_INS_JMP:continue
        require(not i.group(capstone.CS_GRP_INT),'character unexpected trap');pending.append(at+i.size)
    check_shape(len(code),len(instructions),{i.address:bytes(i.bytes)for i in instructions if i.address not in reached},returns)
    require(code[40:48]==bytes.fromhex('eb068d9b00000000'),'character alignment branch differs')
    return dict(instructions=len(instructions),reachable_instructions=len(reached),compared_alignment_bytes=6,returns=[hex(a)for a in returns])

CASES=[
 dict(name='idle',modes=[2],result=3),
 dict(name='move',modes=[2],inputs=[0,None],polls={'h0':[(1,2)],'v0':[(0,1)]},result=3),
 dict(name='locked_skip',modes=[2],inputs=[0,None],locked=True,polls={'h0':[(1,1),(1,3)],'v0':[(0,3),(0,3)]},result=3),
 dict(name='confirm_story',modes=[0],inputs=[0,None],buttons=[[1,0,0,-1],[0,0,0,0]],result=6),
 dict(name='random_locked',modes=[1],confirmed=[1,0],characters=[15,3],locked=True,result=6),
 dict(name='random_open',modes=[1],confirmed=[1,0],characters=[15,3],result=6),
 dict(name='confirmed_cancel',modes=[2],inputs=[0,None],confirmed=[1,0],buttons=[[0,1,0,0],[0,0,0,0]],result=3),
 dict(name='cancel_story',modes=[0],inputs=[0,None],buttons=[[0,1,0,0],[0,0,0,0]],result=2),
 dict(name='both_confirmed',modes=[2],confirmed=[1,1],result=3),
 dict(name='shared_second_cancel',modes=[2],inputs=[0,0],confirmed=[1,0],buttons=[[0,1,0,0],[0,0,0,0]],result=3),
 dict(name='independent_second_cancel',modes=[2],inputs=[0,1],confirmed=[1,0],buttons=[[0,0,0,0],[0,1,0,0]],result=2),
 dict(name='mode_changes',modes=[2,1],confirmed=[1,0],characters=[5,3],result=6),
]
def observe(image,code,case):
 m=Uc(UC_ARCH_X86,UC_MODE_32);m.mem_map(0x400000,(len(image)+4095)&~4095);m.mem_write(0x400000,image);m.mem_write(0x41fc90,code);m.mem_map(0x800000,0x40000);m.mem_map(0x1000000,0x20000);m.mem_map(0xf00000,0x1000);m.mem_write(0xf00000,b'\xc3'*0x1000)
 w=lambda a,v:m.mem_write(a,struct.pack('<I',v&0xffffffff));r=lambda a:struct.unpack('<I',m.mem_read(a,4))[0]
 obj=0x801000;setup=0x82a000;w(obj+0xc,setup);m.mem_write(obj+0x93,bytes([case.get('locked',False)]));m.mem_write(obj+0x7f8,bytes(case.get('confirmed',[0,0])));m.mem_write(setup+0x4c,b'\xaa\xaa')
 for i,v in enumerate(case.get('characters',[2,3])):w(setup+8+32*i,v)
 for i,v in enumerate(case.get('inputs',[None,None])):w(obj+0x10+4*i,0 if v is None else 0x810000+v*0x100)
 for i,buttons in enumerate(case.get('buttons',[[0,0,0,0],[0,0,0,0]])):
  for j,v in enumerate(buttons):w(0x810000+i*0x100+0x40+4*j,v)
 cursors={obj+0x100:'h0',obj+0x114:'v0',obj+0x128:'h1',obj+0x13c:'v1'};positions={n:0 for n in cursors.values()};mode_count=0;events=[]
 stubs={0x43b1a0:('event',1,0),0x41fa20:('cursor',0,0),0x41fb80:('refresh',2,8),0x43ac40:('mode',0,0),0x43ae90:('scenario',1,0),0x43b140:('fade',2,0),0x4067d0:('random',1,0),0x43ac60:('prepare',1,0)}
 stack=0x1010004;w(stack,0xf00000);saved={UC_X86_REG_EBP:0x12345678,UC_X86_REG_EBX:0x22334455,UC_X86_REG_ESI:0x33445566,UC_X86_REG_EDI:0x44556677}
 for rg,v in {**saved,UC_X86_REG_ESP:stack,UC_X86_REG_ECX:obj}.items():m.reg_write(rg,v)
 def hook(u,at,size,data):
  nonlocal mode_count
  if at==0xf00000:u.emu_stop();return
  if at not in stubs:
   if not 0x41fc90<=at<0x41fc90+619:raise ValueError('unobserved helper '+hex(at))
   return
  name,n,pop=stubs[at];ss=u.reg_read(UC_X86_REG_ESP);args=list(struct.unpack('<'+str(n)+'I',u.mem_read(ss+4,n*4)))if n else[];receiver=u.reg_read(UC_X86_REG_ECX)if name in ['cursor','refresh']else None;value=0
  if name=='cursor':
   if receiver not in cursors:raise ValueError('wrong cursor receiver '+hex(receiver))
   key=cursors[receiver];seq=case.get('polls',{}).get(key,[]);index=positions[key];positions[key]+=1;value,selection=seq[index]if index<len(seq)else(0,r(receiver+12));w(receiver+12,selection)
  elif name=='mode':
   seq=case['modes'];value=seq[min(mode_count,len(seq)-1)];mode_count+=1
  elif name=='random':
   require(args[0]in [13,15],'unreviewed random bound');value=args[0]-1
  abi_value=(0x5a000000|value)if name=='cursor'else value if name in ['mode','random']else 0x5a5acafe
  events.append(dict(kind=name,receiver=receiver,args=args,result=value if name in ['cursor','mode','random']else None,eax_bits=abi_value));u.reg_write(UC_X86_REG_EAX,abi_value);u.reg_write(UC_X86_REG_ECX,0xbad0c0de);u.reg_write(UC_X86_REG_EDX,0xbad0dada);u.reg_write(UC_X86_REG_EFLAGS,0x202);u.reg_write(UC_X86_REG_ESP,ss+4+pop);u.reg_write(UC_X86_REG_EIP,r(ss))
 hook_errors=[];m.hook_add(UC_HOOK_CODE,guarded_callback(hook,hook_errors));m.emu_start(0x41fc90,0,count=10000)
 if hook_errors:raise ValueError("observer hook failed: "+repr(hook_errors))
 require(m.reg_read(UC_X86_REG_EIP)==0xf00000,'character observer did not terminate');require(m.reg_read(UC_X86_REG_ESP)==stack+4,'character stack imbalance');require(all(m.reg_read(k)==v for k,v in saved.items()),'character callee-save corruption');result=m.reg_read(UC_X86_REG_EAX);require(result==case['result'],'character return differs: '+case['name'])
 return dict(result=result,state=r(obj+8),confirmed=list(m.mem_read(obj+0x7f8,2)),characters=[r(setup+8+32*i)for i in range(2)],options=[m.mem_read(setup+13+32*i,1)[0]for i in range(2)],random=list(m.mem_read(setup+0x4c,2)),cursors={n:r(a+12)for a,n in cursors.items()},events=events)

def check_observation(case,observation):
    name=case['name'];events=observation['events']
    counts=dict(idle=2,move=6,locked_skip=8,confirm_story=6,random_locked=5,random_open=5,confirmed_cancel=3,cancel_story=4,both_confirmed=2,shared_second_cancel=6,independent_second_cancel=5,mode_changes=4)
    require(len(events)==counts[name] and observation['result']==case['result'],'character bounded event/return contract differs')
    expected_chars=case.get('characters',[2,3])[:]
    if name in ['move','locked_skip','random_locked','random_open']:expected_chars[0]=dict(move=7,locked_skip=15,random_locked=12,random_open=14)[name]
    require(observation['characters']==expected_chars,'character selection publication differs')
    confirmed=case.get('confirmed',[0,0])[:]
    if name=='confirm_story':confirmed=[1,0]
    if name in ['confirmed_cancel','shared_second_cancel']:confirmed=[0,0]
    require(observation['confirmed']==confirmed and observation['state']==int(name=='both_confirmed'),'character confirmation/phase publication differs')
    require(observation['options']==([1,0]if name=='confirm_story'else[0,0]),'character unsigned button option differs')
    require(observation['random']==([1,170]if name.startswith('random_')else[0,170]if name=='mode_changes'else[170,170]),'character random flag differs')
    require([e['args']for e in events if e['kind']=='random']==([[13]]if name=='random_locked'else[[15]]if name=='random_open'else[]),'character actual random bound differs')
    modes=case['modes'];require([e['result']for e in events if e['kind']=='mode']==([0]if modes[0]==0 else[modes[0],modes[-1]]),'character independent mode queries differ')
    require([e['args']for e in events if e['kind']=='fade']==([[1000,0]]if case['result']==6 else[]),'character preparation/fade boundary differs')

def fresh(name,c):
    u=load_manifest()['units'][name];p=ROOT/u['object'];record=json.loads(p.with_suffix(p.suffix+'.provenance.json').read_text());actual,_=unit_input_digest(name,u)
    require(record.get('unit')==name and record.get('input_digest')==actual and record.get('compiler_sha256')==compiler_sha256() and record.get('object_sha256')==core.sha(p),'fresh character/caller/refresh source provenance required')
    return u,p

def canonical(c,u,p,f,size):
    calls=c.known_targets()|{n:int(at,0)for n,at in (v.rsplit('=',1)for v in f.get('rel32_targets',[]))};overrides=dict(v.rsplit('=',1)for v in f.get('dir32_targets',[]));body=c.coff_symbol_bytes(p,f['symbol_base'],int(f['address'],0),0xffffffff,calls,c.known_data_targets(),overrides);require(len(body)==size,'character whole source/callee extent differs');return body

def audit():
    c=core.comparator();sha=c.verify_target();native=c.target_bytes(ADDRESS,SIZE);require(digest(native)==SHA,'character full native body changed');shape=cfg(native)
    support=[]
    for name,at,size in [('exact-first-select-update-flow',0x4208e0,341),('exact-first-select-character-binding',0x41fb80,258)]:
        u,p=fresh(name,c);fs=[f for f in u['functions']if int(f['address'],0)==at];require(len(fs)==1,'character actual caller/refresh selection missing');body=canonical(c,u,p,fs[0],size);require(body==c.target_bytes(at,size),'character actual caller/refresh regression');support.append(dict(unit=name,address=hex(at),size=size,sha256=digest(body)))
    edge=c.target_bytes(0x420a30,5);require(edge[0]==0xe9 and 0x420a35+struct.unpack_from('<i',edge,1)[0]==ADDRESS,'character exact parent tail edge differs')
    edge=c.target_bytes(0x41fd7b,5);require(edge[0]==0xe8 and 0x41fd80+struct.unpack_from('<i',edge,1)[0]==0x41fb80,'character actual refresh edge differs')
    u,p=fresh(UNIT,c);f=u['functions'][0];require(f['address']=='0x0041FC90' and f['symbol_base']=='?update_characters_41fc90@CSelect@th105@@QAEHXZ','character actual ordinary source differs');candidate=canonical(c,u,p,f,SIZE);source_shape=cfg(candidate)
    image=pefile.PE(str(c.TARGET)).get_memory_mapped_image();cases=[]
    for case in CASES:
        target=observe(image,native,case);source=observe(image,candidate,case);check_observation(case,target);check_observation(case,source);require(target==source,'character bounded source/native state or call trace differs: '+case['name']);cases.append(dict(case=case,observation=target))
    bad=bytearray(candidate);require(struct.unpack_from('<I',bad,36)[0]==0x114,'character reviewed source induction base differs');struct.pack_into('<I',bad,36,0x100)
    try:
        observe(image,bytes(bad),CASES[1])
    except ValueError as error:
        require('wrong cursor receiver' in str(error),'unexpected character negative-control failure')
    else:
        raise ValueError('bad cursor-base control was accepted')
    return dict(result='exact'if candidate==native else'mismatch',diagnostic_only=True,target_sha256=sha,unit=UNIT,cfg=shape,source_cfg=source_shape,source_size=len(candidate),candidate_sha256=digest(candidate),native_sha256=digest(native),unequal_bytes=sum(a!=b for a,b in zip(candidate,native)),first_mismatch=c.first_mismatch(native,candidate,ADDRESS),support=support,isolated_cases=cases,bad_cursor_base_rejected=True,scope='complete619 bytes including alignment; finite state/call observations with noisy bool/void EAX and volatile registers/flags; no helper or OS execution, no universal equivalence or new exact credit')

if __name__=='__main__':
    try:
        result=audit();print(json.dumps(result,indent=2));raise SystemExit(result['result']!='exact')
    except (OSError,ValueError,KeyError,RuntimeError,struct.error)as error:raise SystemExit(str(error))
