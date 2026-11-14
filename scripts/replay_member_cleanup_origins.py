"""Original replay vector forwarding and actual implicit input-array cleanup."""
import csv
import importlib.util
import json
from pathlib import Path
import struct
import tomllib
import pefile
import build
import linked_pe as core
import input_base_cleanup_origins as base
from coff_exception_rtti import Reader
from linked_logic_error_origins import require,digest
from workflow_manifest import load_manifest,compiler_sha256
ROOT=Path(__file__).resolve().parents[1]
UNIT='exact-first-replay-storage-constructor'
ANCHORS=ROOT/'config/replay-member-cleanup-origin-anchors.toml'
OUTPUT=ROOT/'build/origin-anchors/replay-member-cleanup'
COMPILER=base.COMPILER
CTOR='??0ReplayStorageLifetime@th105@@QAE@XZ'
DTOR='??1ReplayStorageLifetime@th105@@QAE@XZ'
INPUT_CTOR='??0ProfileInputManagerExLifetime@th105@@QAE@XZ'
INPUT_DTOR='??1ProfileInputManagerExLifetime@th105@@UAE@XZ'
INPUT_BASE='??1ProfileInputManagerLifetime@th105@@UAE@XZ'
DESTROY='?_Destroy@?$vector@UReplayStorageSlot@th105@@V?$allocator@UReplayStorageSlot@th105@@@std@@@std@@IAEXPAUReplayStorageSlot@th105@@0@Z'
RANGE='??$_Destroy_range@UReplayStorageSlot@th105@@V?$allocator@UReplayStorageSlot@th105@@@std@@@std@@YAXPAUReplayStorageSlot@th105@@0AAV?$allocator@UReplayStorageSlot@th105@@@0@U_Nonscalar_ptr_iterator_tag@0@@Z'
DEQUE='??1?$deque@FV?$allocator@F@std@@@std@@QAE@XZ'
TIDY='?_Tidy@?$deque@FV?$allocator@F@std@@@std@@IAEXXZ'
ARRAY_CTOR='??_L@YGXPAXIHP6EX0@Z1@Z'
ARRAY_DTOR='??_M@YGXPAXIHP6EX0@Z@Z'
CONTRACT={'0x0042B8E0':(27,DESTROY,[RANGE+'=0x0042B230']),'0x0042C950':(5,INPUT_DTOR,[INPUT_BASE+'=0x00409D50'])}
SOURCES={'src/input/ReplayStorageConstructor.cpp': '06e6e6c24fdb4af2ea31557f87a4799f71edddfab90d67a0bebf2ee7e8ade39a', 'src/ui/ProfileMenuBaseDataLifetime.hpp': '9aa94662d9ace0b77c983fd05219a50daf11b91dc8c694634126cc71ed48bae9', 'src/engine/CriticalSectionWrapper.hpp': '4d5b4b8731d7fe40d8827900b877c012d12f12b6bf349153c2c9995673fbb3c5', 'src/engine/Sprite.hpp': '3e2ca688bd65839f4b53f4a3b05ba86795f63503868e5c3ba8dd663b7991979b', 'src/engine/ColorInterface.hpp': '71db76e78b423b322a52fe5d0b64559238fdb1fc33170b1f2954d7efd051b093', 'src/engine/TextureHandleValue.hpp': 'c8ab0afa18da3d0b27d099345ad34e57849aa5a39d6ef757549304fb26f0be84'}
VENDOR={'vector':'883848802b49aa4160509b744f37d18a459d31c2c880ae3de3f113fed850c8e5','deque':'2970afda6fd33a55bb0f3860124a28e5c9e532dda18a240ac5749fb0a8cc0fc7','xmemory':'83a2121ebc455b25493a689a4fb299db0ca848ffc29668159bc9fb5faa95e50b','xutility':'104560e2ad5e433eb62c06d70882534306ba345f5f74e6907a6b270df3bd7cea'}
def validate_spec(spec,selected,units,target_sha):
    require(set(spec)=={'schema_version','target_sha256','compiler_sha256','unit','anchors'}and type(spec['schema_version'])is int and spec['schema_version']==1 and spec['target_sha256']==target_sha and spec['compiler_sha256']==COMPILER and spec['unit']==UNIT,'replay cleanup schema/compiler differs');aa=spec['anchors'];require(len(aa)==len(selected)==2 and {a['address']for a in aa}=={r['address']for r in selected}==set(CONTRACT),'replay cleanup complete selection differs');u=units[UNIT]
    require(u.get('kind')=='probe'and u.get('source')==next(iter(SOURCES))and u.get('profile')=='vc8-sp1-probe-o2'and u.get('enable_gs')is True,'replay cleanup actual owner differs')
    for a in aa:
        size,sym,calls=CONTRACT[a['address']];require(set(a)=={'address','size','symbol','sha256'}and type(a['size'])is int and a['size']==size and a['symbol']==sym and int(next(r['size']for r in selected if r['address']==a['address']),0)==size and isinstance(a['sha256'],str)and len(a['sha256'])==64 and all(x in '0123456789abcdef'for x in a['sha256']),'replay cleanup extent/symbol differs');require([f for f in u['functions']if f['address']==a['address']]==[dict(address=a['address'],symbol_base=sym,rel32_targets=calls)],'replay cleanup source call contract differs')
    for at,sym in [('0x0043F1B0',CTOR),('0x0042C930',INPUT_CTOR),('0x0043F260',DTOR)]:require(any(f['address']==at and f['symbol_base']==sym for f in u['functions']),'replay cleanup actual parent/pair missing')
    return aa,u

def array_site(reader,owner,offset,size,address,fields,shape,read):
    raw=bytearray(reader.raw(owner,size,offset));require(reader.refs(owner,size,offset)==[(o,k,s)for o,k,s,t in fields],'replay cleanup exact array source fields differ')
    for off,kind,symbol,to in fields:
        require(struct.unpack_from('<I',raw,off)[0]==0,'replay cleanup source callback addend differs');struct.pack_into('<I',raw,off,(to-(address+off+4)if kind==20 else to)&0xffffffff)
    start,expected=shape;require(bytes(raw[start:start+len(expected)])==expected,'replay cleanup actual count/stride/member differs');require(bytes(raw)==read(address,size),'replay cleanup whole array caller differs');return dict(address=hex(address),size=size,sha256=digest(raw),count=2,stride=104,member_offset=8)

def qualify(unit,anchors,rows,read,c):
    for p,sha in SOURCES.items():require(digest((ROOT/p).read_bytes())==sha,'replay cleanup reviewed source ownership differs')
    for n,sha in VENDOR.items():require(digest((ROOT/'.tools/msvc80-sp1/include'/n).read_bytes())==sha,'replay cleanup original vendor header differs')
    p=ROOT/unit['object'];r=Reader(p);known=c.known_data_targets();facts=[]
    for a in anchors:
        size,sym,calls=CONTRACT[a['address']];at=int(a['address'],0);refs=[(17,20,RANGE)]if size==27 else[(1,20,INPUT_BASE)]
        require(r.symbol(sym).value==0 and r.section(sym).name=='.text'and r.section(sym).raw_size==size and r.refs(sym,size)==refs,'replay cleanup complete emitted body differs');raw=r.raw(sym,size)
        require(all(struct.unpack_from('<I',raw,o)[0]==0 for o,k,n in refs),'replay cleanup root addend differs');targets={n:int(v,0)for n,v in (x.rsplit('=',1)for x in calls)};b=c.coff_symbol_bytes(p,sym,at,size,targets,known);require(len(b)==size and b==read(at,size)and digest(b)==a['sha256'],'replay cleanup whole canonical root differs');core.decode_closed_body(b,at,tail=size==5,external_exits={at:0x409d50}if size==5 else None)
        hits=[x['address']for x in rows if int(x['size'],0)==size and c.coff_symbol_bytes(p,sym,int(x['address'],0),size,targets,known)==read(int(x['address'],0),size)];facts.append(dict(address=a['address'],size=size,symbol=sym,sha256=digest(b),inventory_hits=hits,masked_bytes=0,unequal_bytes=0))
    require(all(f['inventory_hits']==[f['address']]for f in facts),'replay complete physical cleanup inventory differs')
    require(r.section(CTOR).raw_size==161 and r.section(DTOR).raw_size==208,'replay complete owner extents differ')
    sites=[array_site(r,CTOR,41,23,0x43f1d9,[(1,6,INPUT_DTOR,0x42c950),(6,6,INPUT_CTOR,0x42c930),(19,20,ARRAY_CTOR,0x68a30c)],(10,bytes.fromhex('6a026a688d7e0857')),read),array_site(r,DTOR,154,35,0x43f2fa,[(1,6,INPUT_DTOR,0x42c950),(31,20,ARRAY_DTOR,0x68a2a9)],(5,bytes.fromhex('6a026a6883c70857')),read)]
    require(r.symbol(DEQUE).value==0 and r.section(DEQUE).raw_size==5 and r.refs(DEQUE,5)==[(1,20,TIDY)],'replay original deque callback differs');db=c.coff_symbol_bytes(p,DEQUE,0x448de0,5,{TIDY:0x420a80},known);require(db==read(0x448de0,5),'replay whole deque callback differs');core.decode_closed_body(db,0x448de0,tail=True,external_exits={0x448de0:0x420a80})
    require(r.symbol(RANGE).value==0 and r.section(RANGE).raw_size==52 and r.refs(RANGE,52)==[(20,20,TIDY),(25,6,DEQUE),(38,20,ARRAY_DTOR)],'replay whole original range helper differs');rb=c.coff_symbol_bytes(p,RANGE,0x42b230,52,{TIDY:0x420a80,ARRAY_DTOR:0x68a2a9},known|{DEQUE:(0x448de0,db,frozenset({0}),'address')});require(len(rb)==52 and rb==read(0x42b230,52),'replay entire range helper differs');core.decode_closed_body(rb,0x42b230);require(rb[16:19]==bytes.fromhex('8d4e3c')and rb[29:38]==bytes.fromhex('6a026a148d460850e8')and rb[42:45]==bytes.fromhex('83c650'),'replay range actual private/member deque offsets/stride differ')
    origins={x['address']:x for x in csv.DictReader((ROOT/'config/function-origins.csv').open())}
    for at in ['0x0042B230','0x00448DE0','0x00420A80','0x00409D50']:require(origins[at]['disposition']=='exclude','replay cleanup dependency must have its own positive exclusion')
    return dict(anchors=facts,array_sites=sites,range_support=dict(address='0x0042B230',size=52,sha256=digest(rb)),deque_callback=dict(address='0x00448DE0',size=5,sha256=digest(db)),scope='32 compiler-library/implicit cleanup bytes only; input callback identity from actual constructor/destructor pairing, not exclusive alias/ICF; no parent/range/deque/EH/authored credit')

def validate(rule,selected,rows,read,target_sha):
    try:
        require(ROOT/str(rule['replay_member_cleanup_anchor_file'])==ANCHORS,'unreviewed replay cleanup anchors');require(compiler_sha256()==COMPILER,'replay cleanup compiler differs');units=load_manifest()['units'];aa,u=validate_spec(tomllib.loads(ANCHORS.read_text()),selected,units,target_sha)
        errors=base.validate(dict(id='input-base-vptr-cleanup-106a',input_base_cleanup_anchor_file=str(base.ANCHORS.relative_to(ROOT))),[r for r in rows if r['address']=='0x00409D50'],rows,read,target_sha);require(not errors,'replay input base cleanup proof failed')
        sp=importlib.util.spec_from_file_location('replay_cleanup_old_origins',ROOT/'scripts/function-origins.py');o=importlib.util.module_from_spec(sp);sp.loader.exec_module(o);old=next(x for x in tomllib.loads(o.RULES.read_text())['rules']if x.get('vc8_generated_anchor_file')=='config/vc8-generated-replay-storage-dtor-origin-anchors.toml');require(not o.validate_vc8_generated_anchor_evidence(old,[r for r in rows if r['address']=='0x0043F260'],rows,read),'replay implicit parent provenance failed')
        record=build.build_unit(UNIT,u,True,target_sha);c=core.comparator();c.verify_target();proof=qualify(u,aa,rows,read,c);code,results=build.compare_unit(u,True);require(code==0 and len(results)==5 and all(r['result']=='exact'for r in results),'replay complete owner comparisons failed');proof.update(build=record,comparisons=results,validator_sha256=core.sha(Path(__file__)),anchor_sha256=core.sha(ANCHORS));OUTPUT.mkdir(parents=True,exist_ok=True);(OUTPUT/'proof.json').write_text(json.dumps(proof,indent=2)+'\n');return []
    except (OSError,ValueError,KeyError,TypeError,RuntimeError,struct.error)as exc:return [str(rule['id'])+': '+str(exc)]
def main():
    c=core.comparator();sha=c.verify_target();rows=list(csv.DictReader((ROOT/'config/functions.csv').open()));errors=validate(dict(id='replay-member-cleanups-106a',replay_member_cleanup_anchor_file=str(ANCHORS.relative_to(ROOT))),[r for r in rows if r['address']in CONTRACT],rows,c.target_bytes,sha);print(json.dumps(dict(errors=errors)));return bool(errors)
if __name__=='__main__':raise SystemExit(main())
