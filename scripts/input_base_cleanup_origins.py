"""Compiler vptr-only input cleanup, actual named type and complete deleting owner."""
import csv
import json
from pathlib import Path
import struct
import tomllib
import pefile
import build
import linked_pe as core
import scalar_wrapper_origins as scalar
from coff_exception_rtti import Reader,RttiGraph
from linked_logic_error_origins import require,digest
from workflow_manifest import load_manifest,compiler_sha256
ROOT=Path(__file__).resolve().parents[1]
UNIT='gpt-web-input-manager-lifetime'
SOURCE='src/input/InputManagerLifetime.cpp'
SOURCE_SHA='12c40614ec80da7bbabeb74c3f60c3b86d763ea2a0804fb3b5718efd1f9a5fea'
COMPILER='71c93ca5bddc9b2816d0e053cac2b952f926f6b9321fab6b1ab6e8603621324c'
ANCHORS=ROOT/'config/input-base-cleanup-origin-anchors.toml'
OUTPUT=ROOT/'build/origin-anchors/input-base-cleanup'
DTOR='??1CInputManager@@UAE@XZ'
SCALAR='??_GCInputManager@@UAEPAXI@Z'
WEAK='??_ECInputManager@@UAEPAXI@Z'
TABLE='??_7CInputManager@@6B@'
UPDATE='?update_player_input_counters_from_raw@CInputManager@@UAEXXZ'
def validate_spec(spec,selected,units,target_sha):
    require(set(spec)=={'schema_version','target_sha256','compiler_sha256','unit','source_sha256','anchors'}and type(spec['schema_version'])is int and spec['schema_version']==1 and spec['target_sha256']==target_sha and spec['compiler_sha256']==COMPILER and spec['unit']==UNIT and spec['source_sha256']==SOURCE_SHA,'input cleanup schema/source/compiler differs');require(len(spec['anchors'])==len(selected)==1,'input cleanup selects one physical body');a=spec['anchors'][0]
    require(set(a)=={'address','size','symbol','sha256'}and a['address']=='0x00409D50'and type(a['size'])is int and a['size']==7 and a['symbol']==DTOR and selected[0]['address']==a['address']and int(selected[0]['size'],0)==7 and isinstance(a['sha256'],str)and len(a['sha256'])==64 and all(x in '0123456789abcdef'for x in a['sha256']),'input cleanup whole extent/identity differs');u=units[UNIT]
    require(u.get('kind')=='probe'and u.get('source')==SOURCE and u.get('profile')=='vc8-sp1-probe-o2'and u.get('enable_gs')is False and [f for f in u['functions']if f['address']==a['address']]==[dict(address=a['address'],symbol_base=DTOR,dir32_targets=[TABLE+'='+TABLE])],'input cleanup actual ordinary owner differs');require(any(f['address']=='0x00409D30'and f['symbol_base']==SCALAR for f in u['functions']),'input cleanup scalar owner absent');return a,u

def weak_fallback(reader,raw):
    ptr,count=struct.unpack_from('<II',raw,8);found=[(i,s)for i,s in reader.cf.symbols.items()if s.name==WEAK];require(len(found)==1,'input deleting-slot weak symbol ambiguous');i,s=found[0];rec=raw[ptr+18*i:ptr+18*(i+1)];aux=raw[ptr+18*(i+1):ptr+18*(i+2)]
    require(s.section_number==0 and s.value==0 and rec[14:18]==bytes([32,0,105,1])and len(aux)==18,'input deleting slot must be original weak external');index,kind=struct.unpack_from('<II',aux);require(kind==2 and aux[8:]==bytes(10)and index in reader.cf.symbols and reader.cf.symbols[index].name==SCALAR and reader.symbol(SCALAR).section_number>0,'input vector-deleting weak fallback must name actual defined scalar body');return dict(weak_symbol=WEAK,fallback=SCALAR,tag_index=index,search_characteristic=kind)

def qualify(unit,anchor,rows,read,c,game):
    require(digest((ROOT/SOURCE).read_bytes())==SOURCE_SHA,'input cleanup reviewed empty destructor source changed');p=ROOT/unit['object'];r=Reader(p);g=RttiGraph(r,game,read,{'.?AVCInputManager@@'});g.table(TABLE,0x6c1674,0,'.?AVCInputManager@@')
    require(r.symbol(TABLE).value==4 and r.section(TABLE).name=='.rdata'and r.section(TABLE).raw_size==12 and r.refs(TABLE,8)==[(0,6,WEAK),(4,6,UPDATE)]and r.raw(TABLE,8)==bytes(8),'input actual two-slot source table differs');fallback=weak_fallback(r,p.read_bytes());require(read(0x6c1674,8)==struct.pack('<2I',0x409d30,0x409da0)and core.readonly_data(game,0x6c1674,8)==read(0x6c1674,8),'input actual deleting/update slots differ')
    require(r.symbol(DTOR).value==0 and r.section(DTOR).name=='.text'and r.section(DTOR).raw_size==7 and r.refs(DTOR,7)==[(2,6,TABLE)],'input complete vptr-only source cleanup differs');known=c.known_data_targets();b=c.coff_symbol_bytes(p,DTOR,0x409d50,7,{},known);require(len(b)==7 and b==read(0x409d50,7)and digest(b)==anchor['sha256'],'input complete canonical cleanup differs');core.decode_closed_body(b,0x409d50)
    require(r.symbol(SCALAR).value==0 and r.section(SCALAR).raw_size==31,'input complete scalar support differs');sb=c.coff_symbol_bytes(p,SCALAR,0x409d30,31,{'??3@YAXPAX@Z':0x6898ea},known);require(len(sb)==31 and sb==read(0x409d30,31),'input entire scalar support differs');core.decode_closed_body(sb,0x409d30)
    callback=b'\xb9'+struct.pack('<I',0x6fbd60)+b'\xe9'+struct.pack('<i',0x409d50-(0x6befb0+10));require(callback==read(0x6befb0,10),'input actual static cleanup edge differs');core.decode_closed_body(callback,0x6befb0,tail=True,external_exits={0x6befb5:0x409d50})
    hits=[x['address']for x in rows if int(x['size'],0)==7 and c.coff_symbol_bytes(p,DTOR,int(x['address'],0),7,{},known)==read(int(x['address'],0),7)];require(hits==['0x00409D50'],'input vptr-only cleanup physical inventory differs')
    unique={(x['address'],x['size'])for x in g.records};require(len(g.records)==7 and sum(n for a,n in unique)==100,'input complete type graph extent differs')
    return dict(anchor=dict(address=anchor['address'],size=7,sha256=digest(b),inventory_hits=hits,masked_bytes=0,unequal_bytes=0),rtti=g.records,tables=g.tables,unique_rtti_bytes=100,vtable=dict(address='0x006C1674',size=8,weak_fallback=fallback),scalar_support=dict(address='0x00409D30',size=31,sha256=digest(sb)),callback=dict(address='0x006BEFB0',size=10,object='0x006FBD60',target='0x00409D50'),scope='7 compiler lifecycle bytes, withdrawn from authored totals; no scalar/RTTI/static credit or exclusive normal-versus-derived cleanup spelling; published base type does not identify dynamic global type')

def validate(rule,selected,rows,read,target_sha):
    try:
        require(ROOT/str(rule['input_base_cleanup_anchor_file'])==ANCHORS,'unreviewed input cleanup anchor path');require(compiler_sha256()==COMPILER,'input cleanup compiler differs');units=load_manifest()['units'];a,u=validate_spec(tomllib.loads(ANCHORS.read_text()),selected,units,target_sha);record=build.build_unit(UNIT,u,True,target_sha);c=core.comparator();c.verify_target();game=pefile.PE(str(c.TARGET));proof=qualify(u,a,rows,read,c,game);code,results=build.compare_unit(u,True);require(code==0 and len(results)==2 and all(r['result']=='exact'for r in results),'input whole lifetime comparisons failed')
        spec=tomllib.loads(scalar.ANCHORS.read_text());anchors=[a for a in spec['anchors']if a['unit']==UNIT];scalar.replay(UNIT,anchors,units,spec,read,game,True)
        proof.update(build=record,comparisons=results,validator_sha256=core.sha(Path(__file__)),anchor_sha256=core.sha(ANCHORS));OUTPUT.mkdir(parents=True,exist_ok=True);(OUTPUT/'proof.json').write_text(json.dumps(proof,indent=2)+'\n');return []
    except (OSError,ValueError,KeyError,TypeError,RuntimeError,struct.error,pefile.PEFormatError)as exc:return [str(rule['id'])+': '+str(exc)]
def main():
    c=core.comparator();sha=c.verify_target();rows=list(csv.DictReader((ROOT/'config/functions.csv').open()));errors=validate(dict(id='input-base-vptr-cleanup-106a',input_base_cleanup_anchor_file=str(ANCHORS.relative_to(ROOT))),[r for r in rows if r['address']=='0x00409D50'],rows,c.target_bytes,sha);print(json.dumps(dict(errors=errors)));return bool(errors)
if __name__=='__main__':raise SystemExit(main())
