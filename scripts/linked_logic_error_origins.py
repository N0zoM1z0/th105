"""Original-library logic_error constructors with complete EH support.

A narrow typed contract, not a masked exception-shape classifier. The unchanged
seven-TU vendor graph is rebuilt; its public constructor remains unaccepted.
"""
import csv
import hashlib
import json
from pathlib import Path
import struct
import tomllib
import pefile
import linked_pe as core
import original_boost_link as original

ROOT=Path(__file__).resolve().parents[1]
ANCHORS=ROOT/'config/linked-logic-error-origin-anchors.toml'
OUTPUT=ROOT/'build/origin-anchors/linked-logic-error'
STRING='??0logic_error@std@@QAE@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@1@@Z'
COPY='??0logic_error@std@@QAE@ABV01@@Z'
ASSIGN='?assign@?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@QAEAAV12@ABV12@II@Z'
CONTRACT={
 '0x00401670':(107,STRING,0x6bd958,0x6e3fb8,0x6e3fb0,0x6bd950,[41,82],[3,17,56]),
 '0x004017A0':(113,COPY,0x6bd928,0x6e3f8c,0x6e3f84,0x6bd920,[47,87],[3,18,64]),
}
CALLEES={
 '@__security_check_cookie@4':(0x689d25,'libcmt:secchk.obj','vc8-short-security-cookie-check-106a'),
 '___CxxFrameHandler3':(0x6899e7,'libcmt:trnsctrl.obj','vc8-pinned-archive-symbols-106a'),
 '??1exception@std@@UAE@XZ':(0x689fda,'libcmt:stdexcpt.obj','vc8-kb971090-short-and-data-runtime-106a'),
 ASSIGN:(0x4020d0,'i original-0.obj','vc8-generated-fixed-slot-std-comdats-106a'),
 '??0exception@std@@QAE@XZ':(0x689f0b,'libcmt:stdexcpt.obj','vc8-kb971090-short-and-data-runtime-106a'),
 '??0exception@std@@QAE@ABV01@@Z':(0x689f82,'libcmt:stdexcpt.obj','vc8-pinned-archive-symbols-106a'),
}

def require(condition,message):
    if not condition:raise ValueError(message)

def digest(data):return hashlib.sha256(data).hexdigest()

def validate_spec(spec,selected,target_sha):
    require(set(spec)=={'schema_version','target_sha256','anchors'}
            and type(spec['schema_version'])is int and spec['schema_version']==1
            and spec['target_sha256']==target_sha,'logic_error anchor schema/target differs')
    anchors=spec['anchors']
    require(isinstance(anchors,list)and len(anchors)==2
            and {a['address']for a in anchors}==set(CONTRACT)
            and {r['address']for r in selected}==set(CONTRACT)and len(selected)==2,
            'logic_error selection differs')
    by={r['address']:r for r in selected}
    for a in anchors:
        size,symbol,*_=CONTRACT[a['address']]
        require(set(a)=={'address','size','symbol','sha256','handler_sha256','action_sha256'}
                and type(a['size'])is int and a['size']==size and a['symbol']==symbol
                and int(by[a['address']]['size'],0)==size,'logic_error typed anchor differs')
        require(all(isinstance(a[k],str)and len(a[k])==64 and all(c in '0123456789abcdef'for c in a[k])
                    for k in ('sha256','handler_sha256','action_sha256')),'logic_error invalid digest')
    return anchors

def named(symbols,name,owner):
    found=symbols.get(name,[])
    require(len(found)==1 and ' '.join(found[0][1].removeprefix('f ').split())==owner,'logic_error named original owner differs: '+name)
    return found[0][0]

def rtti(read,table):
    col=struct.unpack('<I',read(table-4,4))[0]
    sig,offset,cd,td,hierarchy=struct.unpack('<5I',read(col,20))
    return sig,offset,cd,read(td+8,128).split(b'\0')[0]

def canonical_metadata(source_info,target_info,source_unwind,target_unwind):
    si=list(struct.unpack('<9I',source_info));ti=list(struct.unpack('<9I',target_info))
    su=list(struct.unpack('<2I',source_unwind));tu=list(struct.unpack('<2I',target_unwind))
    require(si[:2]==ti[:2]==[0x19930522,1]and si[3:]==ti[3:]==[0,0,0,0,0,1]
            and su[0]==tu[0]==0xffffffff,'logic_error complete FuncInfo/unwind state differs')
    si[2]=ti[2];su[1]=tu[1]
    require(struct.pack('<9I',*si)==target_info and struct.pack('<2I',*su)==target_unwind,
            'logic_error canonical EH metadata differs')
    return dict(funcinfo_sha256=digest(target_info),unwind_map_sha256=digest(target_unwind),metadata_bytes=44)

def source_context(pe,symbols,origins,read):
    require(pe.FILE_HEADER.Machine==0x14c and pe.OPTIONAL_HEADER.ImageBase==core.IMAGE_BASE,
            'logic_error architecture/base differs')
    exports=getattr(getattr(pe,'DIRECTORY_ENTRY_EXPORT',None),'symbols',[])
    require(len(exports)==1 and exports[0].name.decode()==original.PUBLIC_ROOT,
            'logic_error needs only the original public export')
    calls={}
    for n,(target,owner,evidence)in CALLEES.items():
        at=named(symbols,n,owner);row=origins.get(f'0x{target:08X}',{})
        require(row.get('evidence_id')==evidence and row.get('disposition')=='exclude',
                'logic_error callee lacks its independent accepted ownership: '+n)
        calls[at]=(n,target)
    sv=named(symbols,'??_7logic_error@std@@6B@','libcpmt:string.obj')
    cookie=named(symbols,'___security_cookie','libcmt:gs_cookie.obj')
    sr=lambda a,n:pe.get_data(a-core.IMAGE_BASE,n)
    require(rtti(sr,sv)==rtti(read,0x6c05d0)==(0,0,0,b'.?AVlogic_error@std@@'),
            'logic_error RTTI is not the actual class')
    require(sr(cookie,4)==read(0x6f7a88,4),'logic_error initial security cookie differs')
    return calls,sv,cookie

def qualify(pe,functions,symbols,anchor,rows,read,context):
    calls_map,sv,cookie=context
    size,symbol,nh,ni,nu,na,call_offsets,data_offsets=CONTRACT[anchor['address']]
    start=named(symbols,symbol,'i original-0.obj')
    require(functions.get(start)==[(symbol,'i original-0.obj')],'logic_error root alias differs')
    handler=named(symbols,'__ehhandler$'+symbol,'CIL library: CIL module')
    sr=lambda a,n:pe.get_data(a-core.IMAGE_BASE,n)
    source_range=(core.IMAGE_BASE,core.IMAGE_BASE+pe.OPTIONAL_HEADER.SizeOfImage)
    def resolve(a):
        require(a in calls_map,'logic_error unproved callee')
        return calls_map[a]
    def canon(raw,at,to,**kw):
        return core.canonicalize(raw,at,to,[],resolve,source_range,(0x400000,0x706000),**kw)
    hb=core.linked_body(pe,functions,handler)
    require(len(hb)==27,'logic_error complete handler extent differs')
    native_handler=read(nh,27)
    source_info=struct.unpack_from('<I',hb,18)[0]
    require(struct.unpack_from('<I',native_handler,18)[0]==ni,'logic_error native FuncInfo address differs')
    si=sr(source_info,36);ti=read(ni,36)
    source_unwind=struct.unpack_from('<I',si,8)[0]
    require(struct.unpack_from('<I',ti,8)[0]==nu,'logic_error native unwind address differs')
    su=sr(source_unwind,8);tu=read(nu,8)
    require(struct.unpack_from('<I',tu,4)[0]==na,'logic_error native action address differs')
    metadata=canonical_metadata(si,ti,su,tu)
    core.validate_body_relocations(pe,source_info,36,[dict(field_offset=8)])
    core.validate_body_relocations(pe,source_unwind,8,[dict(field_offset=4)])
    action=struct.unpack_from('<I',su,4)[0]
    require(functions.get(action)==[('__unwindfunclet$'+symbol+'$0','CIL library: CIL module')],
            'logic_error unwind action is not original CIL')
    ab=core.linked_body(pe,functions,action)
    require(len(ab)==8,'logic_error action extent differs')
    ac,ca,ra=canon(ab,action,na,tail=True)
    require(ac==read(na,8)and not ra and len(ca)==1 and ca[0]['symbol']=='??1exception@std@@UAE@XZ'
            and digest(ac)==anchor['action_sha256'],'logic_error complete unwind action differs')
    core.validate_body_relocations(pe,action,8,[])
    refs=[dict(kind='eh_info',source_address=source_info,address=ni,size=36,symbol='actual-FuncInfo')]
    hc,ch,rh=canon(hb,handler,nh,internal_refs=refs,tail=True)
    require(hc==native_handler and digest(hc)==anchor['handler_sha256']
            and [v['symbol']for v in ch]==['@__security_check_cookie@4','___CxxFrameHandler3'],
            'logic_error complete handler differs')
    core.validate_body_relocations(pe,handler,27,rh)
    refs=[dict(kind='eh_handler',source_address=handler,address=nh,size=27,symbol='__ehhandler$'+symbol),
          dict(kind='runtime',source_address=cookie,address=0x6f7a88,size=4,symbol='___security_cookie')]
    vt=[dict(source_address=sv,target_address=0x6c05d0,symbol='??_7logic_error@std@@6B@',target_key='native-logic-error')]
    raw=core.linked_body(pe,functions,start);target=int(anchor['address'],0)
    require(len(raw)==size,'logic_error complete constructor extent differs')
    def rebound(to):return canon(raw,start,to,vtables=vt,internal_refs=refs)
    canonical,calls,datarefs=rebound(target)
    require(canonical==read(target,size)and digest(canonical)==anchor['sha256']
            and [c['offset']for c in calls]==call_offsets
            and [r['field_offset']for r in datarefs]==data_offsets,'logic_error whole canonical constructor differs')
    core.validate_body_relocations(pe,start,size,datarefs)
    allowed={i for off in call_offsets+data_offsets for i in range(off,off+4)}
    require(all(x==y for i,(x,y)in enumerate(zip(raw,canonical))if i not in allowed),
            'logic_error changed nonrelocation byte')
    hits=[r['address']for r in rows if int(r['size'],0)==size
          and rebound(int(r['address'],0))[0]==read(int(r['address'],0),size)]
    require(hits==[anchor['address']],'logic_error complete body is not inventory-unique')
    return dict(address=anchor['address'],size=size,symbol=symbol,sha256=digest(canonical),
                source_va=hex(start),source_instructions=len(core.decode_closed_body(raw,start)),
                target_instructions=len(core.decode_closed_body(canonical,target)),calls=calls,data_refs=datarefs,
                inventory_hits=hits,unequal_bytes=0,masked_bytes=0,
                eh=dict(handler=hex(nh),handler_size=27,handler_sha256=digest(hc),handler_calls=ch,
                        action=hex(na),action_size=8,action_sha256=digest(ac),action_calls=ca,
                        funcinfo=hex(ni),unwind_map=hex(nu),**metadata))

def validate(rule,selected,rows,read,target_sha):
    try:
        require(ROOT/str(rule['linked_logic_error_anchor_file'])==ANCHORS,'unreviewed logic_error anchor path')
        anchors=validate_spec(tomllib.loads(ANCHORS.read_text()),selected,target_sha)
        image,provenance=original.build(output=OUTPUT);pe=pefile.PE(str(image))
        maps=image.with_suffix('.map').read_text();functions=core.parse_map(maps);symbols=core.parse_map_symbols(maps)
        origins={r['address']:r for r in csv.DictReader((ROOT/'config/function-origins.csv').open())}
        context=source_context(pe,symbols,origins,read)
        facts=[qualify(pe,functions,symbols,a,rows,read,context)for a in anchors]
        proof=dict(rule=rule['id'],target_sha256=target_sha,anchors=facts,build=provenance,
                   validator_sha256=core.sha(Path(__file__)),anchor_sha256=core.sha(ANCHORS),
                   support_scope='complete handler27/action8/FuncInfo36/unwind8 for each root, no separate credit',
                   unaccepted_context_root=dict(symbol=original.PUBLIC_ROOT,source_size=len(core.linked_body(pe,functions,named(symbols,original.PUBLIC_ROOT,'i original-0.obj'))),native_size=111))
        (OUTPUT/'proof.json').write_text(json.dumps(proof,indent=2)+'\n')
        return []
    except (OSError,ValueError,KeyError,TypeError,RuntimeError,struct.error,pefile.PEFormatError)as exc:
        return [str(rule['id'])+': '+str(exc)]

def main():
    c=core.comparator();sha=c.verify_target();rows=list(csv.DictReader((ROOT/'config/functions.csv').open()))
    selected=[r for r in rows if r['address']in CONTRACT]
    errors=validate(dict(id='linked-original-logic-error-106a',linked_logic_error_anchor_file=str(ANCHORS.relative_to(ROOT))),
                    selected,rows,c.target_bytes,sha)
    print(json.dumps(dict(errors=errors)));return bool(errors)

if __name__=='__main__':raise SystemExit(main())
