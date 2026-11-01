"""Whole original std::exception deleting destructor and complete class support."""
import csv
import json
from pathlib import Path
import struct
import tomllib
import pefile
import build
import linked_pe as core
import rank_retained_exact as rank
import original_boost_link as original
from coff_exception_rtti import Reader,RttiGraph
from workflow_manifest import load_manifest
from linked_logic_error_origins import require,digest,named

ROOT=Path(__file__).resolve().parents[1]
ANCHORS=ROOT/'config/vc8-exception-delete-origin-anchors.toml'
UNIT='vc8-original-exception-delete'
SCALAR='??_Gexception@std@@UAEPAXI@Z'
VECTOR='??_Eexception@std@@UAEPAXI@Z'
DTOR='??1exception@std@@UAE@XZ'
WHAT='?what@exception@std@@UBEPBDXZ'
VTABLE='??_7exception@std@@6B@'
LITERAL='??_C@_0BC@EOODALEL@Unknown?5exception?$AA@'
TEXT=b'Unknown exception\0'
DELETE='??3@YAXPAX@Z'
ARCHIVE_SHA='3bc6c5b90f8507964839fd0264d8565c3b766d01f9efcad336532a11e8f06ac3'
OBJECT_SHA='91330d0ffa2a3df9fd9b55ee7c687be79dfe2d4fe997a9a9ff83da26a98646f7'
OUTPUT=ROOT/'build/origin-anchors/vc8-exception-delete-link'

def validate_spec(spec,selected,units,target_sha):
    require(set(spec)=={'schema_version','target_sha256','unit','anchors'}and type(spec['schema_version'])is int
        and spec['schema_version']==1 and spec['target_sha256']==target_sha and spec['unit']==UNIT,'exception delete schema/target/unit differs')
    require(len(spec['anchors'])==len(selected)==1,'exception delete counts one physical root');a=spec['anchors'][0]
    require(set(a)=={'address','size','symbol','sha256'}and a['address']=='0x00689FFD'and type(a['size'])is int and a['size']==28
        and a['symbol']==SCALAR and selected[0]['address']==a['address']and int(selected[0]['size'],0)==28
        and isinstance(a['sha256'],str)and len(a['sha256'])==64 and all(c in '0123456789abcdef'for c in a['sha256']),
        'exception delete complete typed root differs')
    u=units[UNIT]
    require(u.get('kind')=='msvc_prebuilt'and u.get('source')=='scripts/extract-msvc-library-object.py'
        and u.get('profile')=='vc8-sp1-libcmt'and u.get('enable_gs')is False and u.get('toolchain_library')=='libcmt'
        and u.get('toolchain_object')=='stdexcpt.obj'and u.get('toolchain_archive_sha256')==ARCHIVE_SHA,'exception delete original member differs')
    require(u['functions']==[dict(address='0x00689FFD',symbol_base=SCALAR,rel32_targets=[DTOR+'=0x00689FDA',DELETE+'=0x006898EA']),
        dict(address='0x00689FDA',symbol_base=DTOR,rel32_targets=['_free=0x0068C686'],dir32_targets=[VTABLE+'='+VTABLE]),
        dict(address='0x00689FF0',symbol_base=WHAT,dir32_targets=[LITERAL+'='+LITERAL])],'exception delete formal roots/support differ')
    return a,u

def qualify(unit,anchor,rows,read,c,game,pe,functions,symbols):
    obj=ROOT/unit['object'];require(digest(obj.read_bytes())==OBJECT_SHA,'exception delete actual object differs')
    r=Reader(obj);graph=RttiGraph(r,game,read,{'.?AVexception@std@@'});graph.table(VTABLE,0x6cd24c,0,'.?AVexception@std@@')
    sec=r.section(LITERAL);require(sec.name=='.rdata'and sec.raw_size==18 and r.symbol(LITERAL).value==0 and not r.refs(LITERAL,18)
        and r.raw(LITERAL,18)==read(0x6cd254,18)==TEXT and core.readonly_data(game,0x6cd254,18)==TEXT,'exception whole original fallback literal differs')
    known=c.known_data_targets();require(known[VTABLE]==(0x6cd24c,read(0x6cd24c,4),frozenset({0}),'address')
        and known[LITERAL]==(0x6cd254,TEXT,frozenset({0}),'literal'),'exception exact vtable/literal bindings differ')
    origins={x['address']:x for x in csv.DictReader((ROOT/'config/function-origins.csv').open())};by={x['address']:x for x in rows}
    require(all(origins[a]['disposition']=='exclude'for a in ['0x00689FDA','0x00689FF0','0x006898EA','0x0068C686'])and by['0x0068C686']['current_name']=='_free',
        'exception named support ownership missing')
    calls={DTOR:0x689fda,DELETE:0x6898ea,'_free':0x68c686}
    def whole(name,to,size,refs):
        symbol,raw,_,rs=rank.read_coff_function(obj,name,None);require(symbol==name and len(raw)==size and rs==refs,'exception complete original extent/relocations differ')
        b=c.coff_symbol_bytes(obj,name,to,0xffffffff,calls,known);require(len(b)==size and b==read(to,size),'exception whole canonical member differs')
        allowed={i for off,k,n in rs for i in range(off,off+4)};require(all(x==y for i,(x,y)in enumerate(zip(raw,b))if i not in allowed),'exception changed nonrelocation bytes')
        core.decode_closed_body(b,to);return b,dict(address=f'0x{to:08X}',size=size,symbol=name,sha256=digest(b),relocations=rs,masked_bytes=0,unequal_bytes=0)
    _,dtor=whole(DTOR,0x689fda,22,[(6,6,VTABLE),(16,20,'_free')]);_,what=whole(WHAT,0x689ff0,13,[(8,6,LITERAL)])
    body,fact=whole(SCALAR,0x689ffd,28,[(4,20,DTOR),(17,20,DELETE)]);require(fact['sha256']==anchor['sha256'],'exception deleting digest differs')
    require(r.pointer(VTABLE,0)==VECTOR and r.pointer(VTABLE,4)==WHAT,'exception original two vtable roles differ')
    data=obj.read_bytes();ptr,count=struct.unpack_from('<II',data,8);weak=[(i,s)for i,s in r.cf.symbols.items()if s.name==VECTOR]
    require(len(weak)==1,'exception vector weak symbol differs');i,s=weak[0];record=data[ptr+18*i:ptr+18*(i+1)]
    require(s.section_number==0 and record[16:18]==bytes([105,1]),'exception vector symbol must be original weak external')
    fallback,flag=struct.unpack_from('<II',data,ptr+18*(i+1));require(flag==2 and r.cf.symbols[fallback].name==SCALAR,'exception weak-library fallback differs')
    gs=named(symbols,SCALAR,'i libcmt:stdexcpt.obj');es=named(symbols,VECTOR,'i libcmt:stdexcpt.obj');ws=named(symbols,WHAT,'libcmt:stdexcpt.obj')
    require(gs==es and set(functions[gs])=={(SCALAR,'i libcmt:stdexcpt.obj'),(VECTOR,'i libcmt:stdexcpt.obj')},'exception actual linked aliases differ')
    vt=named(symbols,VTABLE,'libcmt:stdexcpt.obj');require(struct.unpack('<2I',core.readonly_data(pe,vt,8))==(gs,ws)
        and struct.unpack('<2I',read(0x6cd24c,8))==(0x689ffd,0x689ff0),'exception actual source/native vtable slots differ')
    nd=named(symbols,DTOR,'libcmt:stdexcpt.obj');de=named(symbols,DELETE,'libcmt:delete.obj');fr=named(symbols,'_free','libcmt:free.obj')
    callmap={nd:(DTOR,0x689fda),de:(DELETE,0x6898ea),fr:('_free',0x68c686)}
    def resolve(at):require(at in callmap,'exception linked unproved callee');return callmap[at]
    linked=[]
    for at,to,size,tail in [(gs,0x689ffd,28,False),(de,0x6898ea,5,True)]:
        raw=core.linked_body(pe,functions,at);require(len(raw)==size,'exception linked extent differs')
        b,cs,refs=core.canonicalize(raw,at,to,[],resolve,(core.IMAGE_BASE,core.IMAGE_BASE+pe.OPTIONAL_HEADER.SizeOfImage),(0x400000,0x706000),tail=tail)
        require(not refs and b==read(to,size),'exception full linked body differs');core.validate_body_relocations(pe,at,size,[])
        require([x['symbol']for x in cs]==([DTOR,DELETE]if size==28 else['_free']),'exception linked call roles differ')
        linked.append(dict(address=hex(to),size=size,sha256=digest(b),calls=cs))
    hits=[x['address']for x in rows if int(x['size'],0)==28 and c.coff_symbol_bytes(obj,SCALAR,int(x['address'],0),0xffffffff,calls,known)==read(int(x['address'],0),28)]
    require(hits==['0x00689FFD'],'exception deleting body is not inventory-unique');fact['inventory_hits']=hits
    return dict(anchor=fact,support=[dtor,what],rtti=graph.records,linked=linked,source_aliases=[SCALAR,VECTOR],literal=dict(address='0x006CD254',size=18,sha256=digest(TEXT)))

def validate(rule,selected,rows,read,target_sha):
    try:
        require(ROOT/str(rule['vc8_exception_delete_anchor_file'])==ANCHORS,'unreviewed exception delete anchor path')
        a,u=validate_spec(tomllib.loads(ANCHORS.read_text()),selected,load_manifest()['units'],target_sha)
        require(core.sha(ROOT/'.tools/msvc80-sp1/lib/libcmt.lib')==ARCHIVE_SHA,'exception delete original archive differs')
        record=build.build_unit(UNIT,u,True,target_sha);image,link_record=original.build(output=OUTPUT);pe=pefile.PE(str(image));maps=image.with_suffix('.map').read_text()
        c=core.comparator();c.verify_target();game=pefile.PE(str(c.TARGET));proof=qualify(u,a,rows,read,c,game,pe,core.parse_map(maps),core.parse_map_symbols(maps))
        code,results=build.compare_unit(u,True);require(code==0 and len(results)==3 and all(x['result']=='exact'for x in results),'exception formal root/support failed')
        proof.update(build=record,link_build=link_record,comparisons=results,archive_sha256=ARCHIVE_SHA,object_sha256=OBJECT_SHA,validator_sha256=core.sha(Path(__file__)),anchor_sha256=core.sha(ANCHORS))
        (OUTPUT/'proof.json').write_text(json.dumps(proof,indent=2)+'\n');return []
    except (OSError,ValueError,KeyError,TypeError,RuntimeError,struct.error,pefile.PEFormatError)as exc:return [str(rule['id'])+': '+str(exc)]

def main():
    c=core.comparator();sha=c.verify_target();rows=list(csv.DictReader((ROOT/'config/functions.csv').open()))
    result=validate(dict(id='vc8-original-exception-delete-106a',vc8_exception_delete_anchor_file=str(ANCHORS.relative_to(ROOT))),[r for r in rows if r['address']=='0x00689FFD'],rows,c.target_bytes,sha)
    print(json.dumps(dict(errors=result)));return bool(result)
if __name__=='__main__':raise SystemExit(main())
