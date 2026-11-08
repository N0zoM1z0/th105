"""Natural CSprite lifetimes and actual network-array ownership; no vptr recipes."""
import csv
import importlib.util
import json
from pathlib import Path
import struct
import sys
import tomllib
import pefile
import build
import linked_pe as core
from coff_exception_rtti import Reader,RttiGraph
from linked_logic_error_origins import require,digest
from workflow_manifest import load_manifest,compiler_sha256
ROOT=Path(__file__).resolve().parents[1]
UNIT='gpt-web-ui-sprite-lifetime'
PARENT='gpt-web-network-base-constructor-runtime'
ANCHORS=ROOT/'config/csprite-lifetime-origin-anchors.toml'
OUTPUT=ROOT/'build/origin-anchors/csprite-lifetime'
COMPILER='71c93ca5bddc9b2816d0e053cac2b952f926f6b9321fab6b1ab6e8603621324c'
CTOR='??0CSprite@@QAE@XZ'
DTOR='??1CSprite@@UAE@XZ'
SCALAR='??_GCSprite@@UAEPAXI@Z'
WEAK='??_ECSprite@@UAEPAXI@Z'
OWNER='??0CNetworkBaseConstructorView@th105@@QAE@XZ'
ARRAY='??_L@YGXPAXIHP6EX0@Z1@Z'
SOURCES={'src/network/NetworkInputPacket.hpp': '7c5ef194da1e8bded84b2608ebfa272245ed6364b8618fe81ba271de7550aca9', 'src/network/NetworkPacketBase.hpp': 'a7df6d6cb5694058e5813f8f777bba55714672acfdd383ac3b208ce9bb91d983', 'src/network/NetworkBaseMembers.hpp': '70f67e50a0094a38825da369f60f2a9bcdd78233f4a9b70238679bc9e38f3cb1', 'src/battle/EffectSprite.hpp': 'd5ae37906f406ecd3960aeb870715e78ba900449b84b778fb107b1436099775d', 'src/network/NetworkBaseConstructorRuntime.cpp': 'ac5d3ea4c7c09b6c42c446f83120a8da7ca23d6047901ead074febd861bde29e', 'src/input/InputManager.hpp': '8ef1625a4716361f2c50f6e3a0413501817a6ca55e4dd0af3f9b8587e57c714b', 'src/battle/Collision.hpp': 'a2cee65748e1301e4ff8def4a5a9bd94e0aded383fc183a002adddf03aa35581', 'src/engine/CriticalSectionWrapper.hpp': '4d5b4b8731d7fe40d8827900b877c012d12f12b6bf349153c2c9995673fbb3c5', 'src/engine/ColorInterface.hpp': '71db76e78b423b322a52fe5d0b64559238fdb1fc33170b1f2954d7efd051b093', 'src/engine/TextureHandleValue.hpp': 'c8ab0afa18da3d0b27d099345ad34e57849aa5a39d6ef757549304fb26f0be84', 'src/engine/Sprite.hpp': '8dc8c7c6f5baae0f3dd537c3b2c52c808a4a89e389bb1b4f6800650663b3694d'}
CONTRACT={'0x0040ADA0':(16,CTOR),'0x0040AD50':(7,DTOR)}
def validate_spec(spec,selected,units,target_sha):
    require(set(spec)=={'schema_version','target_sha256','compiler_sha256','unit','parent','source_sha256','anchors'}and type(spec['schema_version'])is int and spec['schema_version']==1 and spec['target_sha256']==target_sha and spec['compiler_sha256']==COMPILER and spec['unit']==UNIT and spec['parent']==PARENT and spec['source_sha256']==SOURCES,'CSprite source/schema/compiler contract differs');aa=spec['anchors'];require(len(aa)==len(selected)==2 and {a['address']for a in aa}=={r['address']for r in selected}==set(CONTRACT),'CSprite selects two whole physical lifetimes');u=units[UNIT];p=units[PARENT]
    require(u.get('source')=='src/network/NetworkBaseConstructorRuntime.cpp'and u.get('kind')=='probe'and u.get('profile')=='vc8-sp1-probe-o2'and u.get('enable_gs')is True and p.get('source')=='src/network/NetworkBaseConstructorRuntime.cpp'and p.get('kind')=='probe'and p.get('profile')=='vc8-sp1-probe-o2'and p.get('enable_gs')is True,'CSprite needs actual ordinary source owners')
    require(u['functions']==[dict(address='0x0040ADA0',symbol_base=CTOR,dir32_targets=['??_7CSprite@@6B@=_select_sprite_vtable_anchor']),dict(address='0x0040AD50',symbol_base=DTOR)],'CSprite must use natural class members, not raw-vptr probes')
    require(p['functions'][0]['address']=='0x0044DB10'and p['functions'][0]['symbol_base']==OWNER,'CSprite actual parent missing')
    for a in aa:
        size,sym=CONTRACT[a['address']];require(set(a)=={'address','size','symbol','sha256'}and type(a['size'])is int and a['size']==size and a['symbol']==sym and int(next(r['size']for r in selected if r['address']==a['address']),0)==size and isinstance(a['sha256'],str)and len(a['sha256'])==64 and all(x in '0123456789abcdef'for x in a['sha256']),'CSprite whole extent/hash differs')
    return aa,u,p

def weak_fallback(reader,raw):
    ptr,count=struct.unpack_from('<II',raw,8);found=[(i,s)for i,s in reader.cf.symbols.items()if s.name==WEAK];require(len(found)==1,'CSprite deleting weak symbol ambiguous');i,s=found[0];rec=raw[ptr+18*i:ptr+18*(i+1)];aux=raw[ptr+18*(i+1):ptr+18*(i+2)]
    require(s.section_number==0 and s.value==0 and rec[14:18]==bytes([32,0,105,1])and len(aux)==18,'CSprite deleting slot must be original weak external');index,kind=struct.unpack_from('<II',aux);require(kind==2 and aux[8:]==bytes(10)and index in reader.cf.symbols and reader.cf.symbols[index].name==SCALAR and reader.symbol(SCALAR).section_number>0,'CSprite weak fallback must name actual defined scalar body');return dict(symbol=WEAK,fallback=SCALAR,tag_index=index,search_characteristic=kind)

def array_site(reader,read):
    require(reader.symbol(OWNER).value==0 and reader.section(OWNER).raw_size==411,'CSprite complete parent extent differs');raw=bytearray(reader.raw(OWNER,40,243));require(reader.refs(OWNER,40,243)==[(1,6,DTOR),(6,6,CTOR),(36,20,ARRAY)],'CSprite actual paired-array roles differ')
    for off in [1,6,36]:require(struct.unpack_from('<I',raw,off)[0]==0,'CSprite actual array addend differs')
    struct.pack_into('<I',raw,1,0x40ad50);struct.pack_into('<I',raw,6,0x40ada0);struct.pack_into('<i',raw,36,0x68a30c-(0x44dc03+40));require(raw[10:24]==bytes.fromhex('6a0268940000008d867c02000050'),'CSprite actual count2/stride94/member27C differs');require(bytes(raw)==read(0x44dc03,40),'CSprite whole array caller differs');return dict(address='0x0044DC03',size=40,constructor='0x0040ADA0',destructor='0x0040AD50',count=2,stride=148,member_offset=636,sha256=digest(raw))

TABLE_SLOTS=[
 (WEAK,0x40ae80),('?set_color@CSpriteBase@@UAEXI@Z',0x40ac50),
 ('?set_vertex_colors@CSpriteBase@@UAEXPBI@Z',0x40ac70),('?multiply_color@CSpriteBase@@UAEXI@Z',0x40ac90),
 ('?set_texture_options@CSprite@@UAEXIHHHHHH@Z',0x406a90),('?set_texture@CSprite@@UAEXIHHHH@Z',0x406a60),
 ('?render_rectangle@CSprite@@UAEXMMMM@Z',0x4070c0),('?render@CSprite@@UAEXMM@Z',0x406be0),
 ('?render_fvf4142@CSprite@@UAEXMM@Z',0x406e50)]
def virtual_table(reader,read):
    symbol='??_7CSprite@@6B@';section=reader.section(symbol)
    require(section.name=='.rdata' and section.raw_size==40 and reader.symbol(symbol).value==4,'CSprite complete table storage/COL prefix differs')
    require(reader.refs(symbol,36)==[(i*4,6,name)for i,(name,at)in enumerate(TABLE_SLOTS)] and reader.raw(symbol,36)==bytes(36),'CSprite nine actual virtual member roles differ')
    expected=struct.pack('<9I',*(at for name,at in TABLE_SLOTS));require(read(0x6c0668,36)==expected,'CSprite entire native virtual table differs')
    return dict(address='0x006C0668',size=36,sha256=digest(expected),slots=[dict(offset=i*4,symbol=n,address=hex(at))for i,(n,at)in enumerate(TABLE_SLOTS)],scope='complete slot identity only; rendering/texture body exactness is separate')

def qualify(unit,parent,anchors,rows,read,c,game):
    for path,sha in SOURCES.items():require(digest((ROOT/path).read_bytes())==sha,'CSprite reviewed ordinary source changed: '+path)
    p=ROOT/unit['object'];r=Reader(p);pr=Reader(ROOT/parent['object']);g=RttiGraph(r,game,read,{'.?AVCSprite@@','.?AVCSpriteBase@@','.?AUIColor@@'});g.table('??_7CSprite@@6B@',0x6c0668,0,'.?AVCSprite@@');g.table('??_7IColor@@6B@',0x6c0624,0,'.?AUIColor@@');known=c.known_data_targets();facts=[]
    for a in anchors:
        size,sym=CONTRACT[a['address']];at=int(a['address'],0);refs=[(11,6,'??_7CSprite@@6B@')]if size==16 else[(2,6,'??_7IColor@@6B@')];require(r.symbol(sym).value==0 and r.section(sym).name=='.text'and r.section(sym).raw_size==size and r.refs(sym,size)==refs,'CSprite entire emitted lifetime differs');over={'??_7CSprite@@6B@':'_select_sprite_vtable_anchor'}if size==16 else{};b=c.coff_symbol_bytes(p,sym,at,size,{},known,over);require(len(b)==size and b==read(at,size)and digest(b)==a['sha256'],'CSprite whole canonical lifetime differs');core.decode_closed_body(b,at);hits=[x['address']for x in rows if int(x['size'],0)==size and c.coff_symbol_bytes(p,sym,int(x['address'],0),size,{},known,over)==read(int(x['address'],0),size)];expected=['0x0040ADA0']if size==16 else['0x0040AD50','0x00421D30'];require(hits==expected,'CSprite physical lifetime inventory differs');facts.append(dict(address=a['address'],size=size,sha256=digest(b),inventory_hits=hits,masked_bytes=0,unequal_bytes=0))
    table=virtual_table(r,read);weak=weak_fallback(r,p.read_bytes());sb=c.coff_symbol_bytes(p,SCALAR,0x40ae80,31,{'??3@YAXPAX@Z':0x6898ea},known);require(r.section(SCALAR).raw_size==31 and len(sb)==31 and sb==read(0x40ae80,31),'CSprite complete scalar support differs');core.decode_closed_body(sb,0x40ae80)
    unique={(x['address'],x['size'])for x in g.records};require(len(g.records)==24 and sum(n for a,n in unique)==273,'CSprite complete RTTI graph extent differs');site=array_site(pr,read)
    return dict(anchors=facts,virtual_table=table,rtti=g.records,tables=g.tables,unique_rtti_bytes=273,array_site=site,scalar_support=dict(address='0x0040AE80',size=31,sha256=digest(sb),weak_fallback=weak),scope='23 pure inherited/compiler lifetime bytes withdrawn from authored credit; no exclusive normal/derived/ICF spelling, rendering/texture implementation equality or scalar/RTTI/array/parent credit')

def validate(rule,selected,rows,read,target_sha):
    try:
        require(ROOT/str(rule['csprite_lifetime_anchor_file'])==ANCHORS,'unreviewed CSprite anchors');require(compiler_sha256()==COMPILER,'CSprite compiler differs');units=load_manifest()['units'];aa,u,p=validate_spec(tomllib.loads(ANCHORS.read_text()),selected,units,target_sha);records=[build.build_unit(n,units[n],True,target_sha)for n in [UNIT,PARENT]];c=core.comparator();c.verify_target();proof=qualify(u,p,aa,rows,read,c,pefile.PE(str(c.TARGET)));reports=[]
        for x in [u,p]:
            code,rs=build.compare_unit(x,True);require(code==0 and len(rs)==len(x['functions'])and all(r['result']=='exact'for r in rs),'CSprite actual owner formal comparison failed');reports+=rs
        sp=importlib.util.spec_from_file_location('csprite_network_full_eh',ROOT/'scripts/audit-network-base-constructor-eh.py');m=importlib.util.module_from_spec(sp);sys.modules[sp.name]=m;sp.loader.exec_module(m);audit=m.audit(read);require(audit['result']=='exact','CSprite parent full EH replay failed');proof.update(builds=records,comparisons=reports,parent_audit=audit,validator_sha256=core.sha(Path(__file__)),anchor_sha256=core.sha(ANCHORS));OUTPUT.mkdir(parents=True,exist_ok=True);(OUTPUT/'proof.json').write_text(json.dumps(proof,indent=2)+'\n');return []
    except (OSError,ValueError,KeyError,TypeError,RuntimeError,struct.error,pefile.PEFormatError)as exc:return [str(rule['id'])+': '+str(exc)]
def main():
    c=core.comparator();sha=c.verify_target();rows=list(csv.DictReader((ROOT/'config/functions.csv').open()));errors=validate(dict(id='csprite-real-lifetimes-106a',csprite_lifetime_anchor_file=str(ANCHORS.relative_to(ROOT))),[r for r in rows if r['address']in CONTRACT],rows,c.target_bytes,sha);print(json.dumps(dict(errors=errors)));return bool(errors)
if __name__=='__main__':raise SystemExit(main())
