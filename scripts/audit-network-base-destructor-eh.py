#!/usr/bin/env python3
"""Whole CNetworkBase destruction and remote EH; no additional byte credit."""
import importlib.util
import json
from pathlib import Path
import struct
import sys
import capstone
import linked_pe as core
from coff_exception_rtti import Reader
from linked_logic_error_origins import require,digest
from workflow_manifest import ROOT,load_manifest,unit_input_digest,compiler_sha256
UNIT='gpt-web-network-base-runtime'
SPRITE_UNIT='gpt-web-ui-sprite-lifetime'
OWNER='??1CNetworkBaseLifetimeView@th105@@UAE@XZ'
PACKET='??1InputPacket24@th105@@QAE@XZ'
GROUP='??1NetworkQueuePair48@th105@@QAE@XZ'
SLOT='??1NetworkQueueSlot20@th105@@QAE@XZ'
ARRAY='??_M@YGXPAXIHP6EX0@Z@Z'
OFFSETS=[0,11,25,49,63,87,101,115]
CALLS={'??1CriticalSectionWrapper@th105@@UAE@XZ':0x40ac10,PACKET:0x43be90,ARRAY:0x68a2a9,GROUP:0x43c380,'??1NetworkWinsockState314@th105@@UAE@XZ':0x412cc0,'??1?$deque@FV?$allocator@F@std@@@std@@QAE@XZ':0x448de0,'@__security_check_cookie@4':0x689d25,'___CxxFrameHandler3':0x6899e7}
REFS=[(7,20,'??1CriticalSectionWrapper@th105@@UAE@XZ'),(21,20,PACKET),(26,6,'??1?$deque@FV?$allocator@F@std@@@std@@QAE@XZ'),(44,20,ARRAY),(59,20,'??1CriticalSectionWrapper@th105@@UAE@XZ'),(64,6,'??1NetworkInputEndpoint7C@th105@@QAE@XZ'),(82,20,ARRAY),(97,20,GROUP),(111,20,'??1CriticalSectionWrapper@th105@@UAE@XZ'),(116,6,'??1CSprite@@UAE@XZ'),(137,20,ARRAY),(155,20,'@__security_check_cookie@4'),(160,6,'__ehfuncinfo$'+OWNER),(165,20,'___CxxFrameHandler3')]
def load(name,file):
    sp=importlib.util.spec_from_file_location(name,ROOT/'scripts'/file);m=importlib.util.module_from_spec(sp);sys.modules[name]=m;sp.loader.exec_module(m);return m
EH=load('network_dtor_eh_sections','audit-select-constructor.py')
def current(name):
    u=load_manifest()['units'][name];p=ROOT/u['object'];record=json.loads(p.with_suffix(p.suffix+'.provenance.json').read_text());actual,_=unit_input_digest(name,u)
    require(record.get('unit')==name and record.get('input_digest')==actual and record.get('compiler_sha256')==compiler_sha256()and record.get('profile')==u['profile']and record.get('enable_gs')==u['enable_gs']and record.get('object_sha256')==core.sha(p),'fresh network/sprite owner provenance required');return u,p

def check_eh_layout(r):
    info='__ehfuncinfo$'+OWNER;unwind='__unwindtable$'+OWNER;handler='__ehhandler$'+OWNER;first='__unwindfunclet$'+OWNER+'$0';code_sec=r.section(handler);meta_sec=r.section(info)
    require(code_sec.name=='.text$x'and code_sec.raw_size==169 and r.symbol(handler).value==142 and r.symbol(first).value==0 and meta_sec.name=='.xdata$x'and meta_sec.raw_size==100 and r.symbol(info).value==0 and r.symbol(unwind).value==36,'network whole EH ownership differs')
    return code_sec,meta_sec

def check_unwind(meta,actions):
    require(len(meta)==100 and len(actions)==8,'network full unwind storage differs')
    require(list(struct.unpack('<9I',meta[:36]))==[0x19930522,8,0x6decbc,0,0,0,0,0,1],'network complete FuncInfo fields differ')
    for i,(n,at)in enumerate(actions):require(struct.unpack_from('<iI',meta,36+8*i)==(i-1,at),'network actual unwind state chain differs')

def audit(read=None):
    c=core.comparator();sha=c.verify_target();read=read or c.target_bytes;u,p=current(UNIT);su,sp=current(SPRITE_UNIT);r=Reader(p);known=c.known_data_targets();f=u['functions'][0]
    require(f['address']=='0x0043C950'and f['symbol_base']==OWNER and r.section(OWNER).raw_size==259,'network actual complete destructor differs');targets=c.known_targets()|{n:int(v,0)for n,v in (x.rsplit('=',1)for x in f['rel32_targets'])};over=dict(x.rsplit('=',1)for x in f['dir32_targets']);main=c.coff_symbol_bytes(p,OWNER,0x43c950,259,targets,known,over)
    info='__ehfuncinfo$'+OWNER;unwind='__unwindtable$'+OWNER;handler='__ehhandler$'+OWNER;first='__unwindfunclet$'+OWNER+'$0';code_sec,meta_sec=check_eh_layout(r)
    require(over.get(handler)=='__ehhandler$??1CNetworkBaseFullLifetimeView@th105@@UAE@XZ' and known[over[handler]][0]==0x6b8cee and r.refs(first,169)==REFS,'network EH exact typed relocation roles differ')
    data={n:(at,read(at,size),frozenset({0}),'address')for n,at,size in [('??1?$deque@FV?$allocator@F@std@@@std@@QAE@XZ',0x448de0,5),('??1NetworkInputEndpoint7C@th105@@QAE@XZ',0x43bea0,19),('??1CSprite@@UAE@XZ',0x40ad50,7),(info,0x6dec98,36),(unwind,0x6decbc,64)]}
    actions=[]
    for i,off in enumerate(OFFSETS):
        n='__unwindfunclet$'+OWNER+'$'+str(i);s=r.symbol(n);require(s.value==off and s.section_number==r.symbol(handler).section_number,'network source unwind action offset/owner differs');at=0x6b8c60+off;data[n]=(at,read(at,1),frozenset({0}),'address');actions.append((n,at))
    require(r.refs(info,36)==[(8,6,unwind)]and r.refs(unwind,64)==[(4+8*i,6,n)for i,(n,at)in enumerate(actions)],'network FuncInfo/unwind roles differ')
    code=EH.replay_section(r.cf,code_sec,0x6b8c60,CALLS,data,read);meta=EH.replay_section(r.cf,meta_sec,0x6dec98,CALLS,data,read)
    check_unwind(meta,actions)
    decoded=[]
    for lo,hi in zip(OFFSETS+[142],OFFSETS[1:]+[142,169]):
        body=code[lo:hi];md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);ins=list(md.disasm(body,0x6b8c60+lo));tail=ins[-1]if ins else None;exits={}
        if tail and tail.mnemonic=='jmp':
            require(tail.size==5 and tail.bytes[0]==0xe9,'network EH exit is not original E9');to=tail.address+5+struct.unpack_from('<i',tail.bytes,1)[0];require(to in CALLS.values(),'network EH exit is not a named cleanup/runtime target');exits[tail.address]=to
        core.decode_closed_body(body,0x6b8c60+lo,tail=bool(exits),external_exits=exits);decoded.append(dict(address=hex(0x6b8c60+lo),size=hi-lo,instructions=len(ins)))
    # The previously flattened owner+20C object has a real 19-byte helper.
    require(r.symbol(GROUP).value==0 and r.section(GROUP).raw_size==19 and r.refs(GROUP,19)==[(1,6,SLOT),(14,20,ARRAY)],'network real queue-pair cleanup differs')
    slot=c.coff_symbol_bytes(p,SLOT,0x43bf50,8,{'?_Tidy@?$deque@FV?$allocator@F@std@@@std@@IAEXXZ':0x420a80},known);require(len(slot)==8 and slot==read(0x43bf50,8),'network actual queue-slot cleanup differs')
    group=c.coff_symbol_bytes(p,GROUP,0x43c380,19,{ARRAY:0x68a2a9},known|{SLOT:(0x43bf50,slot,frozenset({0}),'address')});require(group[5:14]==bytes.fromhex('6a026a2083c10851e8'),'network group count2/stride32/member8 differs');core.decode_closed_body(group,0x43c380)
    packet=c.coff_symbol_bytes(p,PACKET,0x43be90,8,{'?_Tidy@?$deque@FV?$allocator@F@std@@@std@@IAEXXZ':0x420a80},known);require(r.section(PACKET).raw_size==8 and len(packet)==8,'network entire implicit packet cleanup differs');core.decode_closed_body(packet,0x43be90,tail=True,external_exits={0x43be93:0x420a80})
    endpoint_name='??1NetworkInputEndpoint7C@th105@@QAE@XZ';tidy='?_Tidy@?$deque@FV?$allocator@F@std@@@std@@IAEXXZ';base='??1CInputManager@th105@@UAE@XZ'
    require(r.section(endpoint_name).raw_size==19 and r.refs(endpoint_name,19)==[(7,20,tidy),(15,20,base)],'network endpoint entire cleanup roles differ')
    endpoint=c.coff_symbol_bytes(p,endpoint_name,0x43bea0,19,{tidy:0x420a80,base:0x409d50},known);require(len(endpoint)==19 and endpoint==read(0x43bea0,19),'network endpoint cleanup differs');core.decode_closed_body(endpoint,0x43bea0,tail=True,external_exits={0x43beae:0x409d50})
    deque_name='??1?$deque@FV?$allocator@F@std@@@std@@QAE@XZ';require(r.section(deque_name).raw_size==5 and r.refs(deque_name,5)==[(1,20,tidy)],'network whole deque callback differs')
    deque=c.coff_symbol_bytes(p,deque_name,0x448de0,5,{tidy:0x420a80},known);require(len(deque)==5 and deque==read(0x448de0,5),'network deque callback differs');core.decode_closed_body(deque,0x448de0,tail=True,external_exits={0x448de0:0x420a80})
    sprite={}
    for sf in su['functions']:
        at=int(sf['address'],0);size=16 if at==0x40ada0 else 7;require(at in [0x40ada0,0x40ad50],'unexpected sprite lifetime selection');b=c.coff_symbol_bytes(sp,sf['symbol_base'],at,size,{},known,dict(x.rsplit('=',1)for x in sf.get('dir32_targets',[])));require(len(b)==size and b==read(at,size),'network natural sprite callback differs');sprite[sf['address']]=digest(b)
    regions={name:EH.region_result(b,read(at,size),at)for name,b,at,size in [('main',main,0x43c950,259),('eh_code',code,0x6b8c60,169),('eh_metadata',meta,0x6dec98,100),('queue_pair_support',group,0x43c380,19),('packet_cleanup',packet,0x43be90,8),('input_endpoint_support',endpoint,0x43bea0,19),('deque_support',deque,0x448de0,5)]}
    return dict(result='exact'if all(v['exact']for v in regions.values())else'mismatch',target_sha256=sha,regions=regions,source_unwind_actions=[dict(symbol=n,address=hex(at))for n,at in actions],decoded_eh_regions=decoded,natural_sprite_callbacks=sprite,source_provenance_verified=True,scope='existing destructor and complete remote EH plus bounded cleanup support; no new authored bytes or claim of executed OS exception behavior; queue-pair19 is not added to provisional inventory')
if __name__=='__main__':
    try:
        result=audit();print(json.dumps(result,indent=2));raise SystemExit(result['result']!='exact')
    except (OSError,ValueError,KeyError,RuntimeError,struct.error)as exc:raise SystemExit(str(exc))
