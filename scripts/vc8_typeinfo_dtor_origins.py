"""Original type_info destructor with whole CRT cleanup, SEH scope and BSS root."""
import csv
import importlib.util
import json
from pathlib import Path
import struct
import tomllib
import pefile
import build
import linked_pe as core
import rank_retained_exact as rank
from coff_exception_rtti import Reader,RttiGraph
from workflow_manifest import load_manifest
from linked_logic_error_origins import require,digest
from xiph_owned_switch_origins import zero_initialized_counter

ROOT=Path(__file__).resolve().parents[1]
ANCHORS=ROOT/'config/vc8-typeinfo-dtor-origin-anchors.toml'
UNIT='vc8-original-typeinfo-destructor'
SYMBOL='??1type_info@@UAE@XZ'
VTABLE='??_7type_info@@6B@'
PROVIDER='?_Type_info_dtor@type_info@@CAXPAV1@@Z'
TABLE='__sehtable$'+PROVIDER
NODE='___type_info_root_node'
ARCHIVE_SHA='3bc6c5b90f8507964839fd0264d8565c3b766d01f9efcad336532a11e8f06ac3'
OBJECT_SHA='40061415f0967ee72c14ec7f7cb895551033c98ade9973dee139f8e4258622ae'
PROVIDER_SHA='86a3632d27658fd13f9f40c2db6014c0a29d85c275bb8bb729b385e89fdad656'
PROVIDER_PATH=ROOT/'build/origin-anchors/vc8-typeinfo-dtor/typname.obj'
CALLS={'__SEH_prolog4':0x6909a4,'__lock':0x698f68,'_free':0x68c686,'__SEH_epilog4':0x6909e9,'__unlock':0x698e90}
PROVIDER_REFS=[(3,6,TABLE),(8,20,'__SEH_prolog4'),(15,20,'__lock'),(35,6,NODE),(40,6,NODE),
    (63,20,'_free'),(72,20,'_free'),(94,20,'__SEH_epilog4'),(106,20,'__unlock')]

def validate_spec(spec,selected,units,target_sha):
    require(set(spec)=={'schema_version','target_sha256','unit','anchors'}and type(spec['schema_version'])is int
        and spec['schema_version']==1 and spec['target_sha256']==target_sha and spec['unit']==UNIT,'typeinfo schema/target/unit differs')
    require(len(spec['anchors'])==len(selected)==1,'typeinfo requires one whole root');a=spec['anchors'][0]
    require(set(a)=={'address','size','symbol','sha256'}and a['address']=='0x006898EF'and type(a['size'])is int and a['size']==14
        and a['symbol']==SYMBOL and selected[0]['address']==a['address']and int(selected[0]['size'],0)==14
        and isinstance(a['sha256'],str)and len(a['sha256'])==64 and all(c in '0123456789abcdef'for c in a['sha256']),
        'typeinfo whole typed anchor differs')
    u=units[UNIT]
    require(u.get('kind')=='msvc_prebuilt'and u.get('source')=='scripts/extract-msvc-library-object.py'
        and u.get('profile')=='vc8-sp1-libcmt'and u.get('enable_gs')is False and u.get('toolchain_library')=='libcmt'
        and u.get('toolchain_object')=='typinfo.obj'and u.get('toolchain_archive_sha256')==ARCHIVE_SHA,'typeinfo original archive unit differs')
    require([f for f in u['functions']if f['address']=='0x006898EF']==[dict(address='0x006898EF',symbol_base=SYMBOL,rel32_targets=[PROVIDER+'=0x0068E5D6'],dir32_targets=[VTABLE+'='+VTABLE])],
        'typeinfo formal whole body/provider/table differs')
    return a,u

def cleanup(provider_path,rows,origins,read,c,game):
    require(digest(provider_path.read_bytes())==PROVIDER_SHA,'typeinfo cleanup original member differs')
    r=Reader(provider_path);raw=r.raw(PROVIDER,112)
    require(r.section(PROVIDER).raw_size==112 and r.symbol(PROVIDER).value==0 and r.refs(PROVIDER,112)==PROVIDER_REFS,
        'typeinfo complete cleanup extent/relocations differ')
    by={x['address']:x for x in rows}
    for name,to in {**CALLS,PROVIDER:0x68e5d6}.items():
        key=f'0x{to:08X}';require(by[key]['current_name']==name and origins[key]['disposition']=='exclude','typeinfo named CRT provider ownership missing')
    sec=r.section(TABLE);require(sec.name=='.xdata$x'and sec.raw_size==28 and r.symbol(TABLE).value==0 and sec.reloc_count==1,
        'typeinfo complete SEH scope extent differs')
    offset,index,kind=struct.unpack('<IIH',r.cf._read_raw(sec.reloc_offset,10));action=r.cf.symbols[index]
    require((offset,kind)==(24,6)and action.name=='$LN10'and action.section_number==r.symbol(PROVIDER).section_number and action.value==103,
        'typeinfo SEH must bind actual scoped local finally symbol')
    metadata=bytearray(r.raw(TABLE,28));require(list(struct.unpack('<7I',metadata))==[0xfffffffe,0,0xffffffd4,0,0xfffffffe,0,0],
        'typeinfo original complete EH4 scope fields differ')
    struct.pack_into('<I',metadata,24,0x68e63d);require(bytes(metadata)==read(0x6e2290,28),'typeinfo full native scope table differs')
    core.readonly_data(game,0x6e2290,28)
    node=r.symbol(NODE);ns=r.section(NODE)
    require(node.value==0 and ns.name=='.bss'and ns.raw_size==8 and ns.raw_offset==0 and ns.reloc_count==0
        and ns.characteristics&0x80 and ns.characteristics&0x80000000 and not ns.characteristics&0x20000000,
        'typeinfo original root must be an eight-byte zero-initialized node')
    initial=zero_initialized_counter(game,0x6fd41c,4)+zero_initialized_counter(game,0x6fd420,4)
    require(initial==bytes(8)and struct.unpack_from('<I',raw,35)[0]==4 and struct.unpack_from('<I',raw,40)[0]==0,
        'typeinfo root initialization/typed field addends differ')
    data={TABLE:(0x6e2290,bytes(metadata),frozenset({0}),'address'),NODE:(0x6fd41c,initial,frozenset({0,4}),'address')}
    body=c.coff_symbol_bytes(provider_path,PROVIDER,0x68e5d6,0xffffffff,CALLS,data)
    require(len(body)==112 and body==read(0x68e5d6,112),'typeinfo whole native cleanup differs')
    allowed={i for off,k,n in PROVIDER_REFS for i in range(off,off+4)}
    require(all(x==y for i,(x,y)in enumerate(zip(raw,body))if i not in allowed),'typeinfo cleanup changed nonrelocation bytes')
    main=core.decode_closed_body(body[:103],0x68e5d6);finally_code=core.decode_closed_body(body[103:],0x68e63d)
    require(body[88]==0xe8 and 0x68e5d6+93+struct.unpack_from('<i',body,89)[0]==0x68e63d,
        'typeinfo normal cleanup must call the same scoped finally')
    return dict(address='0x0068E5D6',size=112,sha256=digest(body),main_bytes=103,finally_address='0x0068E63D',finally_bytes=9,
        instructions=len(main)+len(finally_code),scope_address='0x006E2290',scope_size=28,scope_sha256=digest(metadata),
        root_address='0x006FD41C',root_size=8,relocations=PROVIDER_REFS,masked_bytes=0,unequal_bytes=0)

def qualify(unit,anchor,rows,read,c,game):
    obj=ROOT/unit['object'];require(digest(obj.read_bytes())==OBJECT_SHA,'typeinfo original root member differs')
    r=Reader(obj);graph=RttiGraph(r,game,read,{'.?AVtype_info@@'});graph.table(VTABLE,0x6cd238,0,'.?AVtype_info@@')
    origins={x['address']:x for x in csv.DictReader((ROOT/'config/function-origins.csv').open())}
    support=cleanup(PROVIDER_PATH,rows,origins,read,c,game)
    name,raw,_,refs=rank.read_coff_function(obj,SYMBOL,None)
    require(name==SYMBOL and len(raw)==14 and refs==[(3,6,VTABLE),(8,20,PROVIDER)],'typeinfo root complete extent/relocations differ')
    data=c.known_data_targets();require(data[VTABLE][0]==0x6cd238 and data[VTABLE][3]=='address','typeinfo formal vtable differs')
    body=c.coff_symbol_bytes(obj,SYMBOL,0x6898ef,0xffffffff,{PROVIDER:0x68e5d6},data)
    require(body==read(0x6898ef,14)and digest(body)==anchor['sha256'],'typeinfo full canonical destructor differs')
    core.decode_closed_body(body,0x6898ef)
    allowed=set(range(3,7))|set(range(8,12));require(all(x==y for i,(x,y)in enumerate(zip(raw,body))if i not in allowed),'typeinfo root changed nonrelocation bytes')
    hits=[x['address']for x in rows if int(x['size'],0)==14 and c.coff_symbol_bytes(obj,SYMBOL,int(x['address'],0),0xffffffff,{PROVIDER:0x68e5d6},data)==read(int(x['address'],0),14)]
    require(hits==['0x006898EF'],'typeinfo destructor is not inventory-unique')
    return dict(anchor=dict(address=anchor['address'],size=14,symbol=SYMBOL,sha256=digest(body),relocations=refs,inventory_hits=hits,masked_bytes=0,unequal_bytes=0),rtti=graph.records,support=support)

def validate(rule,selected,rows,read,target_sha):
    try:
        require(ROOT/str(rule['vc8_typeinfo_dtor_anchor_file'])==ANCHORS,'unreviewed typeinfo anchor path')
        a,u=validate_spec(tomllib.loads(ANCHORS.read_text()),selected,load_manifest()['units'],target_sha)
        archive=(ROOT/'.tools/msvc80-sp1/lib/libcmt.lib').read_bytes();require(digest(archive)==ARCHIVE_SHA,'typeinfo original archive differs')
        sp=importlib.util.spec_from_file_location('typeinfo_extract',ROOT/'scripts/extract-msvc-library-object.py');m=importlib.util.module_from_spec(sp);sp.loader.exec_module(m)
        objects=[b for name,b in m.archive_members(archive)if Path(name).name=='typname.obj'];require(len(objects)==1 and digest(objects[0])==PROVIDER_SHA,'typeinfo provider archive identity differs')
        PROVIDER_PATH.parent.mkdir(parents=True,exist_ok=True);PROVIDER_PATH.write_bytes(objects[0])
        record=build.build_unit(UNIT,u,True,target_sha);c=core.comparator();c.verify_target();game=pefile.PE(str(c.TARGET));proof=qualify(u,a,rows,read,c,game)
        code,results=build.compare_unit(u,True);require(code==0 and results and all(x['result']=='exact'for x in results),'typeinfo formal root failed')
        proof.update(build=record,comparisons=results,archive_sha256=ARCHIVE_SHA,object_sha256=OBJECT_SHA,provider_object_sha256=PROVIDER_SHA,
            validator_sha256=core.sha(Path(__file__)),anchor_sha256=core.sha(ANCHORS))
        (PROVIDER_PATH.parent/'proof.json').write_text(json.dumps(proof,indent=2)+'\n');return []
    except (OSError,ValueError,KeyError,TypeError,RuntimeError,struct.error,pefile.PEFormatError)as exc:return [str(rule['id'])+': '+str(exc)]

def main():
    c=core.comparator();sha=c.verify_target();rows=list(csv.DictReader((ROOT/'config/functions.csv').open()))
    result=validate(dict(id='vc8-original-typeinfo-destructor-106a',vc8_typeinfo_dtor_anchor_file=str(ANCHORS.relative_to(ROOT))),[r for r in rows if r['address']=='0x006898EF'],rows,c.target_bytes,sha)
    print(json.dumps(dict(errors=result)));return bool(result)
if __name__=='__main__':raise SystemExit(main())
