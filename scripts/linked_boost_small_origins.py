"""Complete typed original Boost control-block/base/import leaf bodies."""
import csv
import json
from pathlib import Path
import struct
import tomllib
import pefile
import linked_pe as core
import original_boost_link as original
from linked_logic_error_origins import require,named,digest
from linked_bad_alloc_origins import import_at

ROOT=Path(__file__).resolve().parents[1]
ANCHORS=ROOT/'config/linked-boost-small-origin-anchors.toml'
OUTPUT=ROOT/'build/origin-anchors/linked-boost-small'
DESTROY='?destroy@sp_counted_base@detail@boost@@UAEXXZ'
COPY='??0clone_base@exception_detail@boost@@QAE@ABV012@@Z'
FREE='?free_module@re_detail@boost@@YAXPAX@Z'
DISPOSE='?dispose@?$sp_counted_impl_pd@PAUHINSTANCE__@@P6AXPAX@Z@detail@boost@@UAEXXZ'
BASE='sp_counted_base@detail@boost@@'
CLONE='clone_base@exception_detail@boost@@'
IMPL='?$sp_counted_impl_pd@PAUHINSTANCE__@@P6AXPAX@Z@detail@boost@@'
CONTRACT={
 '0x006A08B0':(13,DESTROY,'i original-0.obj',BASE,0x6d5de0,8),
 '0x006A4D30':(11,COPY,'i original-0.obj',CLONE,0x6d5dd0,None),
 '0x006B55D0':(12,FREE,'original-1.obj',None,None,None),
 '0x006B55E0':(11,DISPOSE,'i original-1.obj',IMPL,0x6d690c,4),
}

def validate_spec(spec,selected,target_sha):
    require(set(spec)=={'schema_version','target_sha256','anchors'}and type(spec['schema_version'])is int
            and spec['schema_version']==1 and spec['target_sha256']==target_sha,'Boost small schema/target differs')
    anchors=spec['anchors']
    require(len(anchors)==len(selected)==4 and {a['address']for a in anchors}==set(CONTRACT)
            and {r['address']for r in selected}==set(CONTRACT),'Boost small selection differs')
    by={r['address']:r for r in selected}
    for a in anchors:
        size,symbol,*_=CONTRACT[a['address']]
        require(set(a)=={'address','size','symbol','sha256'}and type(a['size'])is int and a['size']==size
                and a['symbol']==symbol and int(by[a['address']]['size'],0)==size
                and isinstance(a['sha256'],str)and len(a['sha256'])==64
                and all(c in '0123456789abcdef'for c in a['sha256']),'Boost small typed extent/hash differs')
    return anchors

def table_identity(pe,game,symbols,klass,target):
    symbol='??_7'+klass+'6B@';owner='original-1.obj'if klass==IMPL else'original-0.obj'
    source=named(symbols,symbol,owner);expected='.?AV'+klass
    require(core.primary_type_name(pe,source)==core.primary_type_name(game,target)==expected,
            'Boost small actual RTTI differs')
    return dict(source_address=source,target_address=target,symbol=symbol,target_key='native-'+klass)

def qualify(pe,game,functions,symbols,anchor,rows,read):
    size,symbol,owner,klass,table,slot=CONTRACT[anchor['address']]
    target=int(anchor['address'],0);start=named(symbols,symbol,owner)
    require(functions.get(start)==[(symbol,owner)],'Boost small source alias differs')
    raw=core.linked_body(pe,functions,start);require(len(raw)==size,'Boost small complete extent differs')
    vtables=[];refs=[];identity={}
    if klass:
        vt=table_identity(pe,game,symbols,klass,table);vtables=[vt]
        identity=dict(type_name='.?AV'+klass,source_vtable=hex(vt['source_address']),native_vtable=hex(table))
        if slot is not None:
            require(struct.unpack('<I',core.readonly_data(pe,vt['source_address']+slot,4))[0]==start
                    and struct.unpack('<I',read(table+slot,4))[0]==target,'Boost small virtual slot identity differs')
            core.validate_body_relocations(pe,vt['source_address']+slot,4,[dict(field_offset=0)])
            identity['vslot']=slot
        if klass==IMPL:
            destroy=named(symbols,DESTROY,'i original-0.obj')
            require(struct.unpack('<I',core.readonly_data(pe,vt['source_address']+8,4))[0]==destroy
                    and struct.unpack('<I',read(table+8,4))[0]==0x6a08b0,
                    'Boost small derived destroy identity differs')
    else:
        require(raw[5:7]==b'\xff\x15','Boost free_module is not an indirect import CALL')
        source_iat=struct.unpack_from('<I',raw,7)[0]
        require(import_at(pe,source_iat)==import_at(game,0x6c00bc)==[('kernel32.dll','FreeLibrary')],
                'Boost free_module requires the actual FreeLibrary import')
        refs=[dict(kind='runtime',source_address=source_iat,address=0x6c00bc,size=4,symbol='kernel32!FreeLibrary')]
        identity=dict(import_name='kernel32.dll!FreeLibrary',source_iat=hex(source_iat),native_iat='0x006C00BC')
    def no_call(a):raise ValueError('Boost small unproved direct call')
    def rebound(a):
        return core.canonicalize(raw,start,a,[],no_call,(core.IMAGE_BASE,core.IMAGE_BASE+pe.OPTIONAL_HEADER.SizeOfImage),
                                (0x400000,0x706000),vtables=vtables,internal_refs=refs)
    canonical,calls,datarefs=rebound(target)
    fields=[4]if symbol==COPY else[7]if symbol==FREE else[]
    require(canonical==read(target,size)and digest(canonical)==anchor['sha256']and not calls
            and [r['field_offset']for r in datarefs]==fields,'Boost small full canonical body differs')
    core.validate_body_relocations(pe,start,size,datarefs)
    allowed={i for off in fields for i in range(off,off+4)}
    require(all(a==b for i,(a,b)in enumerate(zip(raw,canonical))if i not in allowed),'Boost small nonrelocation byte changed')
    hits=[r['address']for r in rows if int(r['size'],0)==size and rebound(int(r['address'],0))[0]==read(int(r['address'],0),size)]
    require(hits==[anchor['address']],'Boost small complete body is not inventory-unique')
    return dict(address=anchor['address'],size=size,symbol=symbol,sha256=digest(canonical),source_va=hex(start),
                identity=identity,data_refs=datarefs,inventory_hits=hits,source_instructions=len(core.decode_closed_body(raw,start)),
                target_instructions=len(core.decode_closed_body(canonical,target)),masked_bytes=0,unequal_bytes=0)

def validate(rule,selected,rows,read,target_sha):
    try:
        require(ROOT/str(rule['linked_boost_small_anchor_file'])==ANCHORS,'Boost small unreviewed anchor path')
        anchors=validate_spec(tomllib.loads(ANCHORS.read_text()),selected,target_sha)
        image,build=original.build(output=OUTPUT);pe=pefile.PE(str(image));game=pefile.PE(str(core.comparator().TARGET))
        maps=image.with_suffix('.map').read_text();functions=core.parse_map(maps);symbols=core.parse_map_symbols(maps)
        exports=getattr(getattr(pe,'DIRECTORY_ENTRY_EXPORT',None),'symbols',[])
        require(pe.FILE_HEADER.Machine==0x14c and pe.OPTIONAL_HEADER.ImageBase==core.IMAGE_BASE
                and len(exports)==1 and exports[0].name.decode()==original.PUBLIC_ROOT,'Boost small image/export identity differs')
        facts=[qualify(pe,game,functions,symbols,a,rows,read)for a in anchors]
        proof=dict(rule=rule['id'],target_sha256=target_sha,anchors=facts,build=build,
                   validator_sha256=core.sha(Path(__file__)),anchor_sha256=core.sha(ANCHORS),
                   dependencies={p:core.sha(ROOT/'scripts'/p)for p in ('linked_logic_error_origins.py','linked_bad_alloc_origins.py')},
                   scope='whole original typed Boost leaves; no game-authored or partial credit')
        (OUTPUT/'proof.json').write_text(json.dumps(proof,indent=2)+'\n')
        return []
    except (OSError,ValueError,KeyError,TypeError,RuntimeError,struct.error,pefile.PEFormatError)as exc:
        return [str(rule['id'])+': '+str(exc)]

def main():
    c=core.comparator();sha=c.verify_target();rows=list(csv.DictReader((ROOT/'config/functions.csv').open()))
    errors=validate(dict(id='linked-original-boost-small-106a',linked_boost_small_anchor_file=str(ANCHORS.relative_to(ROOT))),
                    [r for r in rows if r['address']in CONTRACT],rows,c.target_bytes,sha)
    print(json.dumps(dict(errors=errors)));return bool(errors)

if __name__=='__main__':raise SystemExit(main())
