"""Whole original type_info deleting destructor and resolved source vtable alias."""
import csv
import json
from pathlib import Path
import struct
import tomllib
import pefile
import vc8_typeinfo_dtor_origins as normal
import original_boost_link as original
from linked_logic_error_origins import require,digest,named

ROOT=normal.ROOT
ANCHORS=ROOT/'config/vc8-typeinfo-delete-origin-anchors.toml'
UNIT=normal.UNIT
SCALAR='??_Gtype_info@@UAEPAXI@Z'
VECTOR='??_Etype_info@@UAEPAXI@Z'
DELETE='??3@YAXPAX@Z'
OUTPUT=ROOT/'build/origin-anchors/vc8-typeinfo-delete-link'

def validate_spec(spec,selected,units,target_sha):
    require(set(spec)=={'schema_version','target_sha256','unit','anchors'}and type(spec['schema_version'])is int
        and spec['schema_version']==1 and spec['target_sha256']==target_sha and spec['unit']==UNIT,'typeinfo delete schema/target/unit differs')
    require(len(spec['anchors'])==len(selected)==1,'typeinfo deleting aliases count one body');a=spec['anchors'][0]
    require(set(a)=={'address','size','symbol','sha256'}and a['address']=='0x006898FD'and type(a['size'])is int and a['size']==28
        and a['symbol']==SCALAR and selected[0]['address']==a['address']and int(selected[0]['size'],0)==28
        and isinstance(a['sha256'],str)and len(a['sha256'])==64 and all(c in '0123456789abcdef'for c in a['sha256']),
        'typeinfo delete whole typed anchor differs')
    old=tomllib.loads(normal.ANCHORS.read_text());normal.validate_spec(old,[dict(address='0x006898EF',size='14')],units,target_sha)
    u=units[UNIT]
    require([f for f in u['functions']if f['address']==a['address']]==[dict(address=a['address'],symbol_base=SCALAR,
        rel32_targets=[normal.SYMBOL+'=0x006898EF',DELETE+'=0x006898EA'])],'typeinfo deleting formal callees/extent differ')
    return a,u

def qualify(unit,anchor,rows,read,c,game,pe,functions,symbols):
    old=tomllib.loads(normal.ANCHORS.read_text());support=normal.qualify(unit,old['anchors'][0],rows,read,c,game)
    obj=ROOT/unit['object'];r=normal.Reader(obj);require(r.pointer(normal.VTABLE,0)==VECTOR,'typeinfo source slot must name its actual weak vector entry')
    data=obj.read_bytes();ptr,count=struct.unpack_from('<II',data,8)
    weak=[(idx,s)for idx,s in r.cf.symbols.items()if s.name==VECTOR];require(len(weak)==1,'typeinfo weak vector symbol differs')
    idx,s=weak[0];record=data[ptr+idx*18:ptr+(idx+1)*18]
    require(s.section_number==0 and record[16:18]==bytes([105,1]),'typeinfo vector entry is not the original weak external')
    fallback,characteristic=struct.unpack_from('<II',data,ptr+(idx+1)*18)
    require(characteristic==2 and r.cf.symbols[fallback].name==SCALAR,'typeinfo weak-library fallback identity differs')
    # Search-library weakness is not unconditional aliasing: verify actual fresh link resolution.
    gs=named(symbols,SCALAR,'i libcmt:typinfo.obj');es=named(symbols,VECTOR,'i libcmt:typinfo.obj')
    require(gs==es and set(functions[gs])=={(SCALAR,'i libcmt:typinfo.obj'),(VECTOR,'i libcmt:typinfo.obj')},'typeinfo actual linked deleting aliases differ')
    vt=named(symbols,normal.VTABLE,'libcmt:typinfo.obj')
    require(struct.unpack('<I',normal.core.readonly_data(pe,vt,4))[0]==gs and struct.unpack('<I',read(0x6cd238,4))[0]==0x6898fd,
        'typeinfo actual source/native deleting vtable slot differs')
    nd=named(symbols,normal.SYMBOL,'libcmt:typinfo.obj');de=named(symbols,DELETE,'libcmt:delete.obj');free=named(symbols,'_free','libcmt:free.obj')
    callmap={nd:(normal.SYMBOL,0x6898ef),de:(DELETE,0x6898ea),free:('_free',0x68c686)}
    def resolve(at):require(at in callmap,'typeinfo delete unproved linked callee');return callmap[at]
    def linked(at,to,size,tail=False):
        raw=normal.core.linked_body(pe,functions,at);require(len(raw)==size,'typeinfo linked complete extent differs')
        body,calls,refs=normal.core.canonicalize(raw,at,to,[],resolve,(normal.core.IMAGE_BASE,normal.core.IMAGE_BASE+pe.OPTIONAL_HEADER.SizeOfImage),(0x400000,0x706000),tail=tail)
        require(not refs and body==read(to,size),'typeinfo complete linked body differs');normal.core.validate_body_relocations(pe,at,size,[])
        return body,calls
    deleted,dcalls=linked(de,0x6898ea,5,True);require([x['symbol']for x in dcalls]==['_free'],'typeinfo delete/free tail differs')
    body,calls=linked(gs,0x6898fd,28);require([x['offset']for x in calls]==[4,17]and [x['symbol']for x in calls]==[normal.SYMBOL,DELETE],
        'typeinfo linked deleting calls differ')
    name,raw,_,refs=normal.rank.read_coff_function(obj,SCALAR,None)
    require(name==SCALAR and len(raw)==28 and refs==[(4,20,normal.SYMBOL),(17,20,DELETE)],'typeinfo original whole deleting COMDAT differs')
    canonical=c.coff_symbol_bytes(obj,SCALAR,0x6898fd,0xffffffff,{normal.SYMBOL:0x6898ef,DELETE:0x6898ea},{})
    require(canonical==body and digest(body)==anchor['sha256'],'typeinfo archive/linked/native destructor disagree')
    hits=[x['address']for x in rows if int(x['size'],0)==28 and c.coff_symbol_bytes(obj,SCALAR,int(x['address'],0),0xffffffff,{normal.SYMBOL:0x6898ef,DELETE:0x6898ea},{})==read(int(x['address'],0),28)]
    require(hits==['0x006898FD'],'typeinfo deleting body is not inventory-unique')
    return dict(anchor=dict(address=anchor['address'],size=28,symbol=SCALAR,sha256=digest(body),inventory_hits=hits,calls=calls,masked_bytes=0,unequal_bytes=0),
        source_aliases=[SCALAR,VECTOR],source_weak_library_fallback=SCALAR,source_vtable=hex(vt),normal_support=support,
        delete_support=dict(address='0x006898EA',size=5,sha256=digest(deleted),calls=dcalls))

def validate(rule,selected,rows,read,target_sha):
    try:
        require(ROOT/str(rule['vc8_typeinfo_delete_anchor_file'])==ANCHORS,'unreviewed typeinfo delete anchor path')
        a,u=validate_spec(tomllib.loads(ANCHORS.read_text()),selected,normal.load_manifest()['units'],target_sha)
        errors=normal.validate(dict(id='vc8-original-typeinfo-destructor-106a',vc8_typeinfo_dtor_anchor_file=str(normal.ANCHORS.relative_to(ROOT))),
            [x for x in rows if x['address']=='0x006898EF'],rows,read,target_sha)
        require(not errors,'typeinfo normal whole proof failed: '+'; '.join(errors))
        image,record=original.build(output=OUTPUT);pe=pefile.PE(str(image));maps=image.with_suffix('.map').read_text();functions=normal.core.parse_map(maps);symbols=normal.core.parse_map_symbols(maps)
        c=normal.core.comparator();c.verify_target();game=pefile.PE(str(c.TARGET));proof=qualify(u,a,rows,read,c,game,pe,functions,symbols)
        code,results=normal.build.compare_unit(u,True);require(code==0 and len(results)==2 and all(x['result']=='exact'for x in results),'typeinfo normal/deleting formal regression failed')
        proof.update(link_build=record,comparisons=results,validator_sha256=normal.core.sha(Path(__file__)),anchor_sha256=normal.core.sha(ANCHORS),normal_validator_sha256=normal.core.sha(Path(normal.__file__)))
        (OUTPUT/'proof.json').write_text(json.dumps(proof,indent=2)+'\n');return []
    except (OSError,ValueError,KeyError,TypeError,RuntimeError,struct.error,pefile.PEFormatError)as exc:return [str(rule['id'])+': '+str(exc)]

def main():
    c=normal.core.comparator();sha=c.verify_target();rows=list(csv.DictReader((ROOT/'config/functions.csv').open()))
    result=validate(dict(id='vc8-original-typeinfo-delete-106a',vc8_typeinfo_delete_anchor_file=str(ANCHORS.relative_to(ROOT))),[r for r in rows if r['address']=='0x006898FD'],rows,c.target_bytes,sha)
    print(json.dumps(dict(errors=result)));return bool(result)
if __name__=='__main__':raise SystemExit(main())
