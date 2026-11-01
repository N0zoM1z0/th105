"""Whole regex_error clone from the original public exception API and regex.cpp."""
import csv
import json
from pathlib import Path
import tomllib
import struct
import pefile
import build
import linked_pe as core
import rank_retained_exact as rank
import upstream_boost as upstream
from workflow_manifest import load_manifest
from coff_exception_rtti import Reader,RttiGraph
from boost_public_exception_copies import complete_eh
from linked_logic_error_origins import require,digest

ROOT=Path(__file__).resolve().parents[1]
ANCHORS=ROOT/'config/boost-public-regex-exception-origin-anchors.toml'
UNIT='boost-public-regex-exception-copy'
PROVIDER='boost-regex-source-core'
STEM='?$error_info_injector@Vregex_error@boost@@@exception_detail@boost@@'
CLONE_STEM='?$clone_impl@U'+STEM+'@exception_detail@boost@@'
COPY='??0'+CLONE_STEM+'QAE@ABV012@@Z'
INJECT='??0'+STEM+'QAE@ABU012@@Z'
RUNTIME_COPY='??0runtime_error@std@@QAE@ABV01@@Z'
REGEX_DTOR='??1regex_error@boost@@UAE@XZ'
RUNTIME_DTOR='??1runtime_error@std@@UAE@XZ'
RUNTIME_VT='??_7runtime_error@std@@6B@'
REGEX_VT='??_7regex_error@boost@@6B@'
CLONE_BASE='??_7clone_base@exception_detail@boost@@6B@'
BOOST_BASE='??_7exception@boost@@6B@'
INJECT_VT=['??_7'+STEM+'6Bregex_error@2@@','??_7'+STEM+'6Bexception@2@@']
CLONE_VT=['??_7'+CLONE_STEM+'6Bregex_error@2@@','??_7'+CLONE_STEM+'6Bexception@2@@','??_7'+CLONE_STEM+'6B@']
ASSIGN='?assign@?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@QAEAAV12@ABV12@II@Z'
INJECT_EH=dict(handler=0x6bd458,action=0x6bd450,unwind=0x6e382c,info=0x6e3834,dtor=0x6a4b30)
RUNTIME_EH=dict(handler=0x6bd928,action=0x6bd920,unwind=0x6e3f84,info=0x6e3f8c,dtor=0x689fda)

def validate_spec(spec,selected,units,target_sha):
    require(set(spec)=={'schema_version','target_sha256','unit','anchors'}and type(spec['schema_version'])is int
        and spec['schema_version']==1 and spec['target_sha256']==target_sha and spec['unit']==UNIT,'regex exception schema/target/unit differs')
    require(len(spec['anchors'])==len(selected)==1,'regex exception requires one whole root');a=spec['anchors'][0]
    require(set(a)=={'address','size','symbol','sha256'}and a['address']=='0x006B5350'and type(a['size'])is int and a['size']==46
        and a['symbol']==COPY and selected[0]['address']==a['address']and int(selected[0]['size'],0)==46
        and isinstance(a['sha256'],str)and len(a['sha256'])==64 and all(c in '0123456789abcdef'for c in a['sha256']),
        'regex exception whole typed anchor differs')
    u=units[UNIT];p=units[PROVIDER]
    require(u.get('kind')=='probe'and u.get('profile')=='vc8-sp1-probe-o2'and u.get('enable_gs')is True
        and u.get('source')==upstream.REGEX_EXCEPTION_PROBE and u.get('boost_regex_headers')is True
        and u.get('include_dirs')==[upstream.FOLDER]and len(u['functions'])==1,'regex exception public source/profile differs')
    f=u['functions'][0]
    require(f==dict(address='0x006B5350',symbol_base=COPY,rel32_targets=[INJECT+'=0x006B4FC0'],
        dir32_targets=[n+'='+n for n in [CLONE_BASE]+CLONE_VT]),'regex exception formal contract differs')
    require(p.get('kind')=='probe'and p.get('profile')=='vc8-sp1-probe-o2'and p.get('enable_gs')is True
        and p.get('source')=='scripts/probes/BoostRegexSourceRegex.cpp'and p.get('boost_regex_source_tu')=='regex.cpp'
        and p.get('boost_regex_headers')is True,'regex destructor must come from the actual original source TU')
    return a,u,p

def qualify(unit,provider,anchor,rows,read,c,game,origins):
    obj=ROOT/unit['object'];pobj=ROOT/provider['object'];reader=Reader(obj)
    allowed={'.?AVclone_base@exception_detail@boost@@','.?AVexception@boost@@','.?AVexception@std@@',
        '.?AVruntime_error@std@@','.?AVregex_error@boost@@','.?AU'+STEM,'.?AV'+CLONE_STEM}
    graph=RttiGraph(reader,game,read,allowed)
    tables=[(CLONE_BASE,0x6d5dd0,0,'.?AVclone_base@exception_detail@boost@@'),(BOOST_BASE,0x6d5e40,0,'.?AVexception@boost@@'),
            (RUNTIME_VT,0x6d5e48,0,'.?AVruntime_error@std@@'),(REGEX_VT,0x6d68ac,0,'.?AVregex_error@boost@@')]
    tables += [(n,to,off,'.?AU'+STEM)for n,to,off in zip(INJECT_VT,[0x6d6844,0x6d683c],[0,48])]
    tables += [(n,to,off,'.?AV'+CLONE_STEM)for n,to,off in zip(CLONE_VT,[0x6d6868,0x6d6860,0x6d6850],[0,48,68])]
    for args in tables:graph.table(*args)
    data=c.known_data_targets()
    for name,to in graph.bindings.items():data[name]=(to,read(to,4),frozenset({0}),'address')
    data['___security_cookie']=(0x6f7a88,read(0x6f7a88,4),frozenset({0}),'address')
    for name,k in [(INJECT,INJECT_EH),(RUNTIME_COPY,RUNTIME_EH)]:data['__ehhandler$'+name]=(k['handler'],read(k['handler'],27),frozenset({0}),'address')
    calls={INJECT:0x6b4fc0,RUNTIME_COPY:0x6a59a0,REGEX_DTOR:0x6a4b30,RUNTIME_DTOR:0x6a4b30,
        '??0exception@std@@QAE@ABV01@@Z':0x689f82,'??1exception@std@@UAE@XZ':0x689fda,'??3@YAXPAX@Z':0x6898ea,
        ASSIGN:0x4020d0,'@__security_check_cookie@4':0x689d25,'___CxxFrameHandler3':0x6899e7}
    for at in [0x6b4fc0,0x6a59a0,0x6a4b30,0x689f82,0x689fda,0x6898ea,0x4020d0,0x689d25,0x6899e7]:
        require(origins[f'0x{at:08X}']['disposition']=='exclude','regex exception named provider ownership missing')
    def whole(object_path,name,target,size,refs,tail=False):
        actual,raw,_,rs=rank.read_coff_function(object_path,name,None)
        require(actual==name and len(raw)==size and rs==refs,'regex exception whole source/relocation inventory differs')
        b=c.coff_symbol_bytes(object_path,name,target,0xffffffff,calls,data)
        require(b==read(target,size),'regex exception complete body differs: '+name)
        core.decode_closed_body(b,target,tail=tail);allowed={i for off,kind,n in rs for i in range(off,off+4)}
        require(all(x==y for i,(x,y)in enumerate(zip(raw,b))if i not in allowed),'regex exception changed nonrelocation byte')
        return dict(symbol=name,address=hex(target),size=size,sha256=digest(b),relocations=rs,masked_bytes=0,unequal_bytes=0)
    drefs=[(5,6,RUNTIME_VT),(20,20,'??3@YAXPAX@Z'),(46,20,'??1exception@std@@UAE@XZ')]
    support=[whole(pobj,REGEX_DTOR,0x6a4b30,50,drefs,True)]
    support.append(whole(obj,RUNTIME_COPY,0x6a59a0,113,[(3,6,'__ehhandler$'+RUNTIME_COPY),(18,6,'___security_cookie'),
        (47,20,'??0exception@std@@QAE@ABV01@@Z'),(60,6,RUNTIME_VT),(87,20,ASSIGN)]))
    support.append(whole(obj,INJECT,0x6b4fc0,154,[(3,6,'__ehhandler$'+INJECT),(18,6,'___security_cookie'),(47,20,RUNTIME_COPY),
        (53,6,REGEX_VT),(72,6,BOOST_BASE),(121,6,INJECT_VT[0]),(128,6,INJECT_VT[1])]))
    eh=complete_eh(reader,INJECT,INJECT_EH,REGEX_DTOR,read)+complete_eh(reader,RUNTIME_COPY,RUNTIME_EH,'??1exception@std@@UAE@XZ',read)
    refs=[(9,20,INJECT),(16,6,CLONE_BASE),(22,6,CLONE_VT[0]),(29,6,CLONE_VT[1]),(36,6,CLONE_VT[2])]
    fact=whole(obj,COPY,0x6b5350,46,refs);require(fact['sha256']==anchor['sha256'],'regex exception root digest differs')
    hits=[r['address']for r in rows if int(r['size'],0)==46 and c.coff_symbol_bytes(obj,COPY,int(r['address'],0),0xffffffff,calls,data)==read(int(r['address'],0),46)]
    require(hits==['0x006B5350'],'regex exception full root is not inventory-unique');fact['inventory_hits']=hits
    return dict(root=fact,support=support,eh=eh,rtti=graph.records,vtables=graph.tables,
        scope='only clone46 newly classified; complete154/113/50 and EH support are already excluded, no extra credit')

def validate(rule,selected,rows,read,target_sha):
    try:
        require(ROOT/str(rule['boost_public_regex_exception_anchor_file'])==ANCHORS,'unreviewed regex exception anchor path')
        spec=tomllib.loads(ANCHORS.read_text());a,u,p=validate_spec(spec,selected,load_manifest()['units'],target_sha)
        upstream.verified_regex_exception_instantiation();tools,pins=core.pinned_tools(False)
        record=build.build_unit(UNIT,u,True,target_sha);provider=build.build_unit(PROVIDER,p,True,target_sha)
        code,provider_roots=build.compare_unit(p,True);require(code==0 and all(r['result']=='exact'for r in provider_roots),'original regex.cpp selected-body regression failed')
        c=core.comparator();c.verify_target();game=pefile.PE(str(c.TARGET));origins={r['address']:r for r in csv.DictReader((ROOT/'config/function-origins.csv').open())}
        proof=qualify(u,p,a,rows,read,c,game,origins);code,roots=build.compare_unit(u,True)
        require(code==0 and len(roots)==1 and roots[0]['result']=='exact','public regex exception formal root failed')
        proof.update(build=record,provider_build=provider,formal=roots,provider_regression=provider_roots,tool_pins=pins,
            validator_sha256=core.sha(Path(__file__)),anchor_sha256=core.sha(ANCHORS),
            dependencies={name:core.sha(ROOT/'scripts'/name)for name in ['coff_exception_rtti.py','boost_public_exception_copies.py']})
        (ROOT/'build/origin-anchors/boost-public-regex-exception.json').write_text(json.dumps(proof,indent=2)+'\n');return []
    except (OSError,ValueError,KeyError,TypeError,RuntimeError,struct.error,pefile.PEFormatError)as exc:return [str(rule['id'])+': '+str(exc)]

def main():
    c=core.comparator();sha=c.verify_target();rows=list(csv.DictReader((ROOT/'config/functions.csv').open()))
    errors=validate(dict(id='boost-original-public-regex-exception-copy-106a',boost_public_regex_exception_anchor_file=str(ANCHORS.relative_to(ROOT))),[r for r in rows if r['address']=='0x006B5350'],rows,c.target_bytes,sha)
    print(json.dumps(dict(errors=errors)));return bool(errors)

if __name__=='__main__':raise SystemExit(main())
