"""Original VC8 vector default constructor in the actual ScoreData array owner."""
import csv
import json
from pathlib import Path
import struct
import tomllib
import build
import linked_pe as core
from coff_exception_rtti import Reader
from workflow_manifest import load_manifest,compiler_sha256
from linked_logic_error_origins import require,digest
ROOT=Path(__file__).resolve().parents[1]
UNIT='exact-first-score-data-lifetime'
ANCHORS=ROOT/'config/score-vector-default-origin-anchors.toml'
OUTPUT=ROOT/'build/origin-anchors/score-vector-default'
CTOR='??0?$vector@UScoreDefaultRecord24@th105@@V?$allocator@UScoreDefaultRecord24@th105@@@std@@@std@@QAE@XZ'
DTOR=CTOR.replace('??0','??1',1)
OWNER='??0ScoreDataLifetimeView@th105@@QAE@XZ'
ARRAY='??_L@YGXPAXIHP6EX0@Z1@Z'
COMPILER='71c93ca5bddc9b2816d0e053cac2b952f926f6b9321fab6b1ab6e8603621324c'
SOURCES=['src/config/ScoreDataLifetime.cpp','src/config/ScoreDataDefaults.hpp']
VENDOR={'vector':'883848802b49aa4160509b744f37d18a459d31c2c880ae3de3f113fed850c8e5','xmemory':'83a2121ebc455b25493a689a4fb299db0ca848ffc29668159bc9fb5faa95e50b','xutility':'104560e2ad5e433eb62c06d70882534306ba345f5f74e6907a6b270df3bd7cea'}
def source_digest(p):return digest(p.read_text().encode('utf-8'))
def validate_spec(spec,selected,units,target_sha):
    require(set(spec)=={'schema_version','target_sha256','compiler_sha256','unit','sources','anchors'}and type(spec['schema_version'])is int and spec['schema_version']==1 and spec['target_sha256']==target_sha and spec['compiler_sha256']==COMPILER and spec['unit']==UNIT,'score vector schema/target/compiler/unit differs')
    require([x.get('path')for x in spec['sources']]==SOURCES and all(set(x)=={'path','normalized_sha256'}and x['normalized_sha256']==source_digest(ROOT/x['path'])for x in spec['sources']),'score vector actual source/record ownership changed')
    require(len(spec['anchors'])==len(selected)==1,'score vector selects one complete constructor');a=spec['anchors'][0]
    require(set(a)=={'address','size','symbol','sha256'}and a['address']=='0x004460D0'and type(a['size'])is int and a['size']==14 and a['symbol']==CTOR and selected[0]['address']==a['address']and int(selected[0]['size'],0)==14 and isinstance(a['sha256'],str)and len(a['sha256'])==64 and all(c in '0123456789abcdef'for c in a['sha256']),'score vector complete member extent/hash differs')
    u=units[UNIT];require(u.get('source')==SOURCES[0]and u.get('kind')=='probe'and u.get('profile')=='vc8-sp1-probe-o2'and u.get('enable_gs')is True,'score vector actual owner/profile differs')
    require([f for f in u['functions']if f['address']==a['address']]==[dict(address=a['address'],symbol_base=CTOR)],'score vector actual emitted member selector differs')
    for at,symbol in [('0x0043E1A0',OWNER),('0x00435F90',DTOR)]:require(any(f['address']==at and f['symbol_base']==symbol for f in u['functions']),'score vector paired owner/destructor missing')
    return a,u

def qualify(unit,anchor,rows,read,c):
    for name,sha in VENDOR.items():require(digest((ROOT/'.tools/msvc80-sp1/include'/name).read_bytes())==sha,'score vector original VC8 header differs: '+name)
    r=Reader(ROOT/unit['object']);require(r.symbol(CTOR).value==0 and r.section(CTOR).name=='.text'and r.section(CTOR).raw_size==14 and r.section(CTOR).reloc_count==0 and not r.refs(CTOR,14),'score vector complete relocation-free source member differs')
    raw=r.raw(CTOR,14);require(raw==read(0x4460d0,14)and digest(raw)==anchor['sha256'],'score vector whole native constructor differs');core.decode_closed_body(raw,0x4460d0)
    require(r.section(OWNER).name=='.text'and r.section(OWNER).raw_size==306,'score vector original parent extent differs');site=bytearray(r.raw(OWNER,31,252));require(r.refs(OWNER,31,252)==[(1,6,DTOR),(6,6,CTOR),(27,20,ARRAY)],'score vector exact array-callback roles differ')
    for off in [1,6,27]:require(struct.unpack_from('<I',site,off)[0]==0,'score vector source callback addend differs')
    struct.pack_into('<I',site,1,0x435f90);struct.pack_into('<I',site,6,0x4460d0);struct.pack_into('<i',site,27,0x68a30c-(0x43e29c+31))
    require(site[10:27]==bytes.fromhex('6a146a108d8e9801000051c644243007e8'),'score vector actual count20/stride16/member198/EH-state7 differs')
    require(bytes(site)==read(0x43e29c,31),'score vector complete original caller site differs')
    hits=[x['address']for x in rows if int(x['size'],0)==14 and raw==read(int(x['address'],0),14)];require(hits==['0x004460D0'],'score vector entire body is not inventory-unique')
    return dict(anchor=dict(address=anchor['address'],size=14,sha256=digest(raw),inventory_hits=hits,masked_bytes=0,unequal_bytes=0),array_site=dict(address='0x0043E29C',size=31,sha256=digest(site),count=20,stride=16,member_offset=408,constructor='0x004460D0',destructor='0x00435F90',eh_state=7),vendor_headers=VENDOR,scope='14 compiler-library bytes only; no parent/destructor/static/EH or authored credit; original template specialization spelling not claimed exclusive')

def validate(rule,selected,rows,read,target_sha):
    try:
        require(ROOT/str(rule['score_vector_default_anchor_file'])==ANCHORS,'unreviewed score vector anchor path');require(compiler_sha256()==COMPILER,'score vector compiler differs');a,u=validate_spec(tomllib.loads(ANCHORS.read_text()),selected,load_manifest()['units'],target_sha)
        record=build.build_unit(UNIT,u,True,target_sha);c=core.comparator();c.verify_target();proof=qualify(u,a,rows,read,c);code,results=build.compare_unit(u,True);require(code==0 and len(results)==len(u['functions'])and all(x['result']=='exact'for x in results),'score vector complete owner comparisons failed')
        proof.update(build=record,comparisons=results,validator_sha256=core.sha(Path(__file__)),anchor_sha256=core.sha(ANCHORS));OUTPUT.mkdir(parents=True,exist_ok=True);(OUTPUT/'proof.json').write_text(json.dumps(proof,indent=2)+'\n');return []
    except (OSError,ValueError,KeyError,TypeError,RuntimeError,struct.error)as exc:return [str(rule['id'])+': '+str(exc)]

def main():
    c=core.comparator();sha=c.verify_target();rows=list(csv.DictReader((ROOT/'config/functions.csv').open()));result=validate(dict(id='score-vector-default-constructor-106a',score_vector_default_anchor_file=str(ANCHORS.relative_to(ROOT))),[r for r in rows if r['address']=='0x004460D0'],rows,c.target_bytes,sha);print(json.dumps(dict(errors=result)));return bool(result)
if __name__=='__main__':raise SystemExit(main())
