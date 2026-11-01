"""Implicit CSpriteEx construction: complete owner metadata and array callback."""
import csv
import json
from pathlib import Path
import struct
import tomllib
import pefile
import build
import linked_pe as core
from coff_exception_rtti import Reader,RttiGraph
from workflow_manifest import load_manifest,compiler_sha256
from linked_logic_error_origins import require,digest
ROOT=Path(__file__).resolve().parents[1]
UNIT='exact-first-select-constructor'
ANCHORS=ROOT/'config/sprite-default-origin-anchors.toml'
OUTPUT=ROOT/'build/origin-anchors/sprite-default'
CTOR='??0CSpriteEx@@QAE@XZ'
DTOR='??1CSpriteEx@@UAE@XZ'
OWNER='??0CSelect@th105@@QAE@XZ'
ARRAY='??_L@YGXPAXIHP6EX0@Z1@Z'
SOURCES=['src/battle/EffectSprite.hpp','src/ui/SelectConstructor.hpp','src/ui/SelectConstructor.cpp']
COMPILER='71c93ca5bddc9b2816d0e053cac2b952f926f6b9321fab6b1ab6e8603621324c'
def source_digest(path):return digest(path.read_text().encode('utf-8'))
def validate_spec(spec,selected,units,target_sha):
    require(set(spec)=={'schema_version','target_sha256','compiler_sha256','unit','sources','anchors'}and type(spec['schema_version'])is int and spec['schema_version']==1 and spec['target_sha256']==target_sha and spec['compiler_sha256']==COMPILER and spec['unit']==UNIT,'sprite default schema/target/compiler/unit differs')
    require([x.get('path')for x in spec['sources']]==SOURCES and all(set(x)=={'path','normalized_sha256'}and x['normalized_sha256']==source_digest(ROOT/x['path'])for x in spec['sources']),'sprite implicit declaration/owner changed; renew ownership review')
    require(len(spec['anchors'])==len(selected)==1,'sprite default selects one complete constructor');a=spec['anchors'][0]
    require(set(a)=={'address','size','symbol','sha256'}and a['address']=='0x0041F6E0'and type(a['size'])is int and a['size']==16 and a['symbol']==CTOR and selected[0]['address']==a['address']and int(selected[0]['size'],0)==16 and isinstance(a['sha256'],str)and len(a['sha256'])==64 and all(c in '0123456789abcdef'for c in a['sha256']),'sprite default complete extent/hash differs')
    u=units[UNIT];require(u.get('source')=='src/ui/SelectConstructor.cpp'and u.get('kind')=='probe'and u.get('profile')=='vc8-sp1-probe-o2'and u.get('enable_gs')is True,'sprite default actual source owner/profile differs')
    fs=[f for f in u['functions']if f['address']==a['address']];require(fs==[dict(address=a['address'],symbol_base=CTOR)],'sprite default must select actual implicit member')
    require(any(f['address']=='0x004231A0'and f['symbol_base']==OWNER for f in u['functions']),'sprite default actual CSelect owner missing');return a,u

def array_site(reader,read):
    require(reader.section(OWNER).name=='.text'and reader.section(OWNER).raw_size==4247,'sprite actual owner extent differs')
    raw=bytearray(reader.raw(OWNER,29,424));require(reader.refs(OWNER,29,424)==[(1,6,DTOR),(6,6,CTOR),(25,20,ARRAY)],'sprite actual array construction relocation roles differ')
    for off in [1,6,25]:require(struct.unpack_from('<I',raw,off)[0]==0,'sprite array callback source addend differs')
    struct.pack_into('<I',raw,1,0x421d30);struct.pack_into('<I',raw,6,0x41f6e0);struct.pack_into('<i',raw,25,0x68a30c-(0x4231a0+424+29))
    require(raw[10:25]==bytes.fromhex('6a028d862406000068e800000050e8'),'sprite actual count2/offset624/strideE8/call shape differs')
    require(bytes(raw)==read(0x423348,29),'sprite whole real array-construction site differs')
    return dict(address='0x00423348',size=29,constructor='0x0041F6E0',destructor='0x00421D30',array_helper='0x0068A30C',count=2,stride=232,member_offset=1572,sha256=digest(raw))

def qualify(unit,anchor,rows,read,c,game):
    r=Reader(ROOT/unit['object']);g=RttiGraph(r,game,read,{'.?AVCSpriteEx@@','.?AVCSpriteBase@@','.?AUIColor@@'})
    g.table('??_7CSpriteEx@@6B@',0x6c06e8,0,'.?AVCSpriteEx@@');g.table('??_7IColor@@6B@',0x6c0624,0,'.?AUIColor@@')
    require(r.symbol(CTOR).value==0 and r.section(CTOR).name=='.text'and r.section(CTOR).raw_size==16 and r.refs(CTOR,16)==[(11,6,'??_7CSpriteEx@@6B@')],'sprite complete implicit constructor differs')
    b=c.coff_symbol_bytes(ROOT/unit['object'],CTOR,0x41f6e0,16,{},c.known_data_targets());require(len(b)==16 and b==read(0x41f6e0,16)and digest(b)==anchor['sha256'],'sprite complete canonical constructor differs');core.decode_closed_body(b,0x41f6e0)
    require(r.symbol(DTOR).value==0 and r.section(DTOR).name=='.text'and r.section(DTOR).raw_size==7 and r.refs(DTOR,7)==[(2,6,'??_7IColor@@6B@')],'sprite actual callback destructor extent differs')
    d=c.coff_symbol_bytes(ROOT/unit['object'],DTOR,0x421d30,7,{},c.known_data_targets());require(len(d)==7 and d==read(0x421d30,7),'sprite complete array-destructor callback differs');core.decode_closed_body(d,0x421d30)
    site=array_site(r,read)
    hits=[x['address']for x in rows if int(x['size'],0)==16 and c.coff_symbol_bytes(ROOT/unit['object'],CTOR,int(x['address'],0),16,{},c.known_data_targets())==read(int(x['address'],0),16)];require(hits==['0x0041F6E0'],'sprite constructor is not inventory-unique')
    return dict(anchor=dict(address=anchor['address'],size=16,sha256=digest(b),inventory_hits=hits,masked_bytes=0,unequal_bytes=0),rtti=g.records,tables=g.tables,array_site=site,destructor_support=dict(address='0x00421D30',size=7,sha256=digest(d)),scope='16 compiler-generated bytes only; no authored/parent/destructor/array-site/RTTI credit')

def validate(rule,selected,rows,read,target_sha):
    try:
        require(ROOT/str(rule['sprite_default_anchor_file'])==ANCHORS,'unreviewed sprite default anchor path');require(compiler_sha256()==COMPILER,'sprite default compiler differs')
        a,u=validate_spec(tomllib.loads(ANCHORS.read_text()),selected,load_manifest()['units'],target_sha);record=build.build_unit(UNIT,u,True,target_sha);c=core.comparator();c.verify_target();game=pefile.PE(str(c.TARGET));proof=qualify(u,a,rows,read,c,game)
        view=dict(u,functions=[f for f in u['functions']if f['address']==a['address']]);code,results=build.compare_unit(view,True);require(code==0 and len(results)==1 and results[0]['result']=='exact','sprite formal constructor comparison failed')
        proof.update(build=record,comparisons=results,validator_sha256=core.sha(Path(__file__)),anchor_sha256=core.sha(ANCHORS));OUTPUT.mkdir(parents=True,exist_ok=True);(OUTPUT/'proof.json').write_text(json.dumps(proof,indent=2)+'\n');return []
    except (OSError,ValueError,KeyError,TypeError,RuntimeError,struct.error,pefile.PEFormatError)as exc:return [str(rule['id'])+': '+str(exc)]

def main():
    c=core.comparator();sha=c.verify_target();rows=list(csv.DictReader((ROOT/'config/functions.csv').open()));result=validate(dict(id='implicit-sprite-default-constructor-106a',sprite_default_anchor_file=str(ANCHORS.relative_to(ROOT))),[r for r in rows if r['address']=='0x0041F6E0'],rows,c.target_bytes,sha);print(json.dumps(dict(errors=result)));return bool(result)
if __name__=='__main__':raise SystemExit(main())
