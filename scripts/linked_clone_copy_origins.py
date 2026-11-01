"""Whole runtime_error Boost clone copy with full injector/cleanup support.

Only the clone46 is newly classified. The runtime_error copy113 remains
nonexact in this CIL context; it is an independently typed named callee.
"""
import csv
import json
from pathlib import Path
import struct
import tomllib
import pefile
import linked_pe as core
import original_boost_link as original
import linked_logic_error_origins as logic
from linked_logic_error_origins import require,named,digest

ROOT=Path(__file__).resolve().parents[1]
ANCHORS=ROOT/'config/linked-clone-copy-origin-anchors.toml'
OUTPUT=ROOT/'build/origin-anchors/linked-clone-copy'
RUNTIME='??0runtime_error@std@@QAE@ABV01@@Z'
DTOR='??1runtime_error@std@@UAE@XZ'
INJECT='??0?$error_info_injector@Vruntime_error@std@@@exception_detail@boost@@QAE@ABU012@@Z'
CLONE='??0?$clone_impl@U?$error_info_injector@Vruntime_error@std@@@exception_detail@boost@@@exception_detail@boost@@QAE@ABV012@@Z'
INJECT_TYPE='.?AU?$error_info_injector@Vruntime_error@std@@@exception_detail@boost@@'
CLONE_TYPE='.?AV?$clone_impl@U?$error_info_injector@Vruntime_error@std@@@exception_detail@boost@@@exception_detail@boost@@'
BODIES={
 DTOR:(0x6a4b30,50,'6a6bbdb7903fd2a855dcc3cd9c743ed97475204db0f6c237e15b0f93841b1571'),
 INJECT:(0x6a5e40,147,'4d40a0405a1332bf60fd5d41d5a1aaa3dc487fd5e8b23fe4d0b0636c55e13c9a'),
 CLONE:(0x6a8370,46,'f467d41117e8c58e4d0e8ac830fc40022e49a3d7d5ab74eacc5f245c4a7283dc'),
}
VTABLES=[
 ('??_7runtime_error@std@@6B@',0x6d5e48,0,'.?AVruntime_error@std@@'),
 ('??_7exception@boost@@6B@',0x6d5e40,0,'.?AVexception@boost@@'),
 ('??_7clone_base@exception_detail@boost@@6B@',0x6d5dd0,0,'.?AVclone_base@exception_detail@boost@@'),
 ('??_7?$error_info_injector@Vruntime_error@std@@@exception_detail@boost@@6Bruntime_error@std@@@',0x6d5e94,0,INJECT_TYPE),
 ('??_7?$error_info_injector@Vruntime_error@std@@@exception_detail@boost@@6Bexception@2@@',0x6d5e8c,40,INJECT_TYPE),
 ('??_7?$clone_impl@U?$error_info_injector@Vruntime_error@std@@@exception_detail@boost@@@exception_detail@boost@@6Bruntime_error@std@@@',0x6d5eb8,0,CLONE_TYPE),
 ('??_7?$clone_impl@U?$error_info_injector@Vruntime_error@std@@@exception_detail@boost@@@exception_detail@boost@@6Bexception@2@@',0x6d5eb0,40,CLONE_TYPE),
 ('??_7?$clone_impl@U?$error_info_injector@Vruntime_error@std@@@exception_detail@boost@@@exception_detail@boost@@6B@',0x6d5ea0,60,CLONE_TYPE),
]
EXTERNAL={
 '??1exception@std@@UAE@XZ':(0x689fda,'libcmt:stdexcpt.obj','vc8-kb971090-short-and-data-runtime-106a'),
 '??3@YAXPAX@Z':(0x6898ea,'libcmt:delete.obj','vc8-runtime-tail-aliases-106a'),
 '@__security_check_cookie@4':(0x689d25,'libcmt:secchk.obj','vc8-short-security-cookie-check-106a'),
 '___CxxFrameHandler3':(0x6899e7,'libcmt:trnsctrl.obj','vc8-pinned-archive-symbols-106a'),
 '??0exception@std@@QAE@ABV01@@Z':(0x689f82,'libcmt:stdexcpt.obj','vc8-pinned-archive-symbols-106a'),
 logic.ASSIGN:(0x4020d0,'i original-0.obj','vc8-generated-fixed-slot-std-comdats-106a'),
 RUNTIME:(0x6a59a0,'i original-0.obj','vc8-generated-battle-input-slot-config-std-comdats-106a'),
}

def validate_spec(spec,selected,target_sha):
    require(set(spec)=={'schema_version','target_sha256','anchors'}and type(spec['schema_version'])is int
            and spec['schema_version']==1 and spec['target_sha256']==target_sha,'clone copy schema/target differs')
    require(len(spec['anchors'])==len(selected)==1,'clone copy needs exactly one new root')
    a=spec['anchors'][0];r=selected[0];address,size,sha=BODIES[CLONE]
    require(a==dict(address=f'0x{address:08X}',size=size,symbol=CLONE,sha256=sha)
            and r['address']==a['address']and int(r['size'],0)==size,'clone copy typed anchor differs')
    return a

def rtti(pe,table):
    col=struct.unpack('<I',core.readonly_data(pe,table-4,4))[0]
    sig,offset,cd,td,hierarchy=struct.unpack('<5I',core.readonly_data(pe,col,20))
    require(hierarchy!=0,'clone RTTI hierarchy is missing')
    raw=core.pe_data(pe,td+8,256);require(b'\0'in raw,'clone RTTI type name is unterminated')
    return sig,offset,cd,raw.split(b'\0')[0].decode('ascii')

def bind_vtables(pe,game,symbols):
    out=[]
    for symbol,target,offset,typename in VTABLES:
        source=named(symbols,symbol,'original-0.obj');expected=(0,offset,0,typename)
        require(rtti(pe,source)==rtti(game,target)==expected,'clone actual class/subobject RTTI differs')
        out.append(dict(source_address=source,target_address=target,symbol=symbol,target_key=typename+':'+str(offset)))
    return out

def complete_eh(pe,functions,symbols,read,canon):
    source=named(symbols,'__ehhandler$'+INJECT,'CIL library: CIL module');target=0x6bd458
    raw=core.linked_body(pe,functions,source);require(len(raw)==27,'clone injector full handler extent differs')
    native=read(target,27);si=struct.unpack_from('<I',raw,18)[0];ti=0x6e3834
    require(struct.unpack_from('<I',native,18)[0]==ti,'clone native FuncInfo identity differs')
    sr=lambda a,n:core.pe_data(pe,a,n);sw=sr(si,36);tw=read(ti,36)
    su=struct.unpack_from('<I',sw,8)[0];tu=0x6e382c
    require(struct.unpack_from('<I',tw,8)[0]==tu,'clone native unwind identity differs')
    sa=sr(su,8);ta=read(tu,8);metadata=logic.canonical_metadata(sw,tw,sa,ta)
    action=struct.unpack_from('<I',sa,4)[0];native_action=0x6bd450
    require(struct.unpack_from('<I',ta,4)[0]==native_action
            and functions.get(action)==[('__unwindfunclet$'+INJECT+'$0','CIL library: CIL module')],
            'clone original/native cleanup ownership differs')
    ab=core.linked_body(pe,functions,action);require(len(ab)==8,'clone full action extent differs')
    ac,calls,refs=canon(ab,action,native_action,tail=True)
    require(ac==read(native_action,8)and not refs and len(calls)==1 and calls[0]['symbol']==DTOR,
            'clone full cleanup action differs')
    core.validate_body_relocations(pe,action,8,[])
    hc,hcalls,hrefs=canon(raw,source,target,tail=True,
        internal_refs=[dict(kind='eh_info',source_address=si,address=ti,size=36,symbol='actual-FuncInfo')])
    require(hc==native and [r['symbol']for r in hcalls]==['@__security_check_cookie@4','___CxxFrameHandler3'],
            'clone full EH handler differs')
    core.validate_body_relocations(pe,source,27,hrefs)
    core.validate_body_relocations(pe,si,36,[dict(field_offset=8)])
    core.validate_body_relocations(pe,su,8,[dict(field_offset=4)])
    return dict(kind='eh_handler',source_address=source,address=target,size=27,symbol='__ehhandler$'+INJECT),dict(
        handler=hex(target),handler_size=27,handler_sha256=digest(hc),action=hex(native_action),
        action_size=8,action_sha256=digest(ac),funcinfo=hex(ti),unwind_map=hex(tu),**metadata)

def qualify(pe,game,functions,symbols,rows,origins,read):
    vtables=bind_vtables(pe,game,symbols);callmap={}
    for n,(target,owner,evidence)in EXTERNAL.items():
        row=origins.get(f'0x{target:08X}',{})
        require(row.get('disposition')=='exclude'and row.get('evidence_id')==evidence,'clone missing independent named callee proof')
        callmap[named(symbols,n,owner)]=(n,target)
    for n,(target,size,sha)in BODIES.items():callmap[named(symbols,n,'i original-0.obj')]=(n,target)
    def resolve(a):
        require(a in callmap,'clone unproved external callee')
        return callmap[a]
    def canon(raw,start,target,**kw):
        return core.canonicalize(raw,start,target,[],resolve,(core.IMAGE_BASE,core.IMAGE_BASE+pe.OPTIONAL_HEADER.SizeOfImage),
                                 (0x400000,0x706000),**kw)
    eh_ref,eh=complete_eh(pe,functions,symbols,read,canon)
    cookie=named(symbols,'___security_cookie','libcmt:gs_cookie.obj')
    require(core.pe_data(pe,cookie,4)==read(0x6f7a88,4),'clone security cookie differs')
    refs=[eh_ref,dict(kind='runtime',source_address=cookie,address=0x6f7a88,size=4,symbol='___security_cookie')]
    facts=[]
    for symbol,(target,size,sha)in BODIES.items():
        start=named(symbols,symbol,'i original-0.obj')
        require(functions.get(start)==[(symbol,'i original-0.obj')],'clone unexpected source alias')
        raw=core.linked_body(pe,functions,start);require(len(raw)==size,'clone complete body extent differs')
        def rebound(at):
            return canon(raw,start,at,vtables=vtables,internal_refs=refs if symbol==INJECT else[],tail=symbol==DTOR)
        canonical,calls,datarefs=rebound(target)
        require(canonical==read(target,size)and digest(canonical)==sha,'clone complete canonical body differs: '+symbol)
        core.validate_body_relocations(pe,start,size,datarefs)
        expected_calls={DTOR:[20,46],INJECT:[47],CLONE:[9]}[symbol]
        expected_data={DTOR:[5],INJECT:[3,18,73,114,121],CLONE:[16,22,29,36]}[symbol]
        require([r['offset']for r in calls]==expected_calls and [r['field_offset']for r in datarefs]==expected_data,
                'clone exact call/data field inventory differs')
        allowed={i for off in expected_calls+expected_data for i in range(off,off+4)}
        require(all(a==b for i,(a,b)in enumerate(zip(raw,canonical))if i not in allowed),'clone changed nonrelocation byte')
        hits=[r['address']for r in rows if int(r['size'],0)==size and rebound(int(r['address'],0))[0]==read(int(r['address'],0),size)]
        require(hits==[f'0x{target:08X}'],'clone complete source body is not inventory-unique')
        facts.append(dict(address=f'0x{target:08X}',symbol=symbol,size=size,sha256=sha,source_va=hex(start),
                          calls=calls,data_refs=datarefs,inventory_hits=hits,masked_bytes=0,unequal_bytes=0))
    runtime_start=named(symbols,RUNTIME,'i original-0.obj')
    runtime_raw=core.linked_body(pe,functions,runtime_start);runtime_target=read(0x6a59a0,113)
    runtime_handler=named(symbols,'__ehhandler$'+RUNTIME,'CIL library: CIL module')
    runtime_refs=[dict(kind='eh_handler',source_address=runtime_handler,address=0x6bd928,size=27,symbol='__ehhandler$'+RUNTIME),refs[1]]
    runtime_canonical,_,runtime_data=canon(runtime_raw,runtime_start,0x6a59a0,vtables=vtables,internal_refs=runtime_refs)
    core.validate_body_relocations(pe,runtime_start,len(runtime_raw),runtime_data)
    require(len(runtime_raw)==113 and runtime_canonical!=runtime_target,'clone runtime-copy diagnostic context changed')
    differences=[i for i,(a,b)in enumerate(zip(runtime_canonical,runtime_target))if a!=b]
    return dict(bodies=facts,eh=eh,vtables=vtables,
                nonexact_callee=dict(symbol=RUNTIME,address='0x006A59A0',source_size=len(runtime_raw),native_size=113,
                    canonical_sha256=digest(runtime_canonical),native_sha256=digest(runtime_target),
                    unequal_bytes=len(differences),first_difference=differences[0],
                    note='Current CIL reorders the EH state store; named typed callee only, not a whole exact support claim.'))

def validate(rule,selected,rows,read,target_sha):
    try:
        require(ROOT/str(rule['linked_clone_copy_anchor_file'])==ANCHORS,'clone unreviewed anchor path')
        validate_spec(tomllib.loads(ANCHORS.read_text()),selected,target_sha)
        image,build=original.build(output=OUTPUT);pe=pefile.PE(str(image));game=pefile.PE(str(core.comparator().TARGET))
        maps=image.with_suffix('.map').read_text();functions=core.parse_map(maps);symbols=core.parse_map_symbols(maps)
        exports=getattr(getattr(pe,'DIRECTORY_ENTRY_EXPORT',None),'symbols',[])
        require(pe.FILE_HEADER.Machine==0x14c and pe.OPTIONAL_HEADER.ImageBase==core.IMAGE_BASE
                and len(exports)==1 and exports[0].name.decode()==original.PUBLIC_ROOT,'clone image/export contract differs')
        origins={r['address']:r for r in csv.DictReader((ROOT/'config/function-origins.csv').open())}
        facts=qualify(pe,game,functions,symbols,rows,origins,read)
        proof=dict(rule=rule['id'],target_sha256=target_sha,build=build,proof=facts,
                   validator_sha256=core.sha(Path(__file__)),anchor_sha256=core.sha(ANCHORS),
                   supporting_validator_sha256=core.sha(Path(logic.__file__)))
        (OUTPUT/'proof.json').write_text(json.dumps(proof,indent=2)+'\n');return []
    except (OSError,ValueError,KeyError,TypeError,RuntimeError,struct.error,pefile.PEFormatError)as exc:
        return [str(rule['id'])+': '+str(exc)]

def main():
    c=core.comparator();sha=c.verify_target();rows=list(csv.DictReader((ROOT/'config/functions.csv').open()))
    errors=validate(dict(id='linked-original-runtime-clone-copy-106a',linked_clone_copy_anchor_file=str(ANCHORS.relative_to(ROOT))),
                    [r for r in rows if r['address']=='0x006A8370'],rows,c.target_bytes,sha)
    print(json.dumps(dict(errors=errors)));return bool(errors)

if __name__=='__main__':raise SystemExit(main())
