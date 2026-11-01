"""Coupled original x87/SSE sin owners, real fallback entries and full data."""
import csv
import importlib.util
import json
from pathlib import Path
import struct
import tomllib
import pefile
import build
import vc8_sqrt_shared_origins as sqrt
from linked_logic_error_origins import require,digest

ROOT=sqrt.ROOT
ANCHORS=ROOT/'config/vc8-sin-shared-origin-anchors.toml'
OUTPUT=ROOT/'build/origin-anchors/vc8-sin-shared'
HASHES={'sin.obj':'07cd973fdf1401cd07e48cac07c0753c6b846b1f29dab9941bf5acb2cb3ee5ac',
 'sin_pentium4.obj':'e353c0e9d913ecbf5b2c892a9d77437227d1c1894d8b7be489d30d98ec665c97',
 'mathfcns.obj':'db496994490b75ddda60c9068d30a546f984f0467acc150bebc8fa7c5eaf3289'}
SIN_UNIT='vc8-original-sin-shared-body'
P4_UNIT='vc8-original-sin-p4-shared-body'
CONTRACT={'0x0068B6C8':(145,SIN_UNIT,'sin.obj',0x68b630,152,297),'0x00694E3E':(425,P4_UNIT,'sin_pentium4.obj',0x694e20,30,456)}
CALLS=sqrt.CALLS|{'__sin_pentium4':0x694e38,'__CIsin_pentium4':0x694e20,'__sin_default':0x68b6bf}
SIN_BINDINGS=['__DEFAULT_CW_in_mem=vc8_common_default_cw','___fastflag=vc8_sqrt_fastflag','_NAME_=vc8_sin_operation_name',
 '__pi_by_2_to_61=vc8_common_pi_by_2_to_61','__indefinite=vc8_sqrt_indefinite']
P4_REFS=[(57,6,'PI32INV'),(69,6,'SHIFTER'),(85,6,'P_1'),(97,6,'P_2'),(126,6,'SC_4'),(132,6,'Ctable'),(153,6,'P_3'),
 (190,6,'SC_2'),(259,6,'SC_3'),(271,6,'SC_1'),(394,6,'ALL_ONES'),(416,6,'TWO_POW_55'),(432,6,'TWO_POW_M55'),(451,20,'__sin_default')]
P4_LABELS={'Ctable':0,'SC_1':2048,'SC_2':2064,'SC_3':2080,'SC_4':2096,'PI32INV':2112,'SHIFTER':2120,'P_2':2128,
 'P_1':2144,'P_3':2152,'TWO_POW_55':2160,'TWO_POW_M55':2168,'ALL_ONES':2176,'NEG_ZERO':2184,'ONE':2192}
P4_BINDINGS=[n+'=vc8_sin_p4_'+n for off,k,n in P4_REFS if k==6]
SIN_REFS=[(2,6,'___use_sse2_mathfcns'),(59,20,'__sin_pentium4'),(66,6,'___use_sse2_mathfcns'),(119,20,'__CIsin_pentium4'),
 (130,20,'__checkTOS_withFB'),(148,20,'__fload_withFB'),(169,6,'__DEFAULT_CW_in_mem'),(183,6,'___fastflag'),
 (190,20,'__fast_exit'),(201,6,'_NAME_'),(206,20,'__math_exit'),(212,6,'__pi_by_2_to_61'),(233,20,'__convertTOStoQNaN'),
 (257,6,'__indefinite'),(268,6,'___fastflag'),(275,20,'__fast_exit'),(286,6,'_NAME_'),(291,20,'__startOneArgErrorHandling')]
SIN_RANGES=[(0,63,'_sin'),(64,123,'__CIsin'),(123,143,'__CIsin_default'),(143,152,'__sin_default'),(152,297,'start')]
P4_RANGES=[(0,24,'__CIsin_pentium4'),(24,30,'__sin_pentium4'),(30,455,'start')]

def validate_spec(spec,selected,units,target_sha):
    require(set(spec)=={'schema_version','target_sha256','anchors'}and type(spec['schema_version'])is int
        and spec['schema_version']==1 and spec['target_sha256']==target_sha,'sin schema/target differs')
    aa=spec['anchors'];by={x['address']:x for x in selected}
    require(len(aa)==len(selected)==2 and set(by)==set(CONTRACT)and {a['address']for a in aa}==set(CONTRACT),'sin shared selection differs')
    for a in aa:
        size,key,member,base,off,extent=CONTRACT[a['address']]
        require(set(a)=={'address','size','symbol','unit','sha256'}and type(a['size'])is int and a['size']==size and int(by[a['address']]['size'],0)==size
            and a['symbol']=='start'and a['unit']==key and isinstance(a['sha256'],str)and len(a['sha256'])==64
            and all(c in '0123456789abcdef'for c in a['sha256']),'sin complete shared extent differs')
        u=units[key]
        require(u.get('kind')=='msvc_prebuilt'and u.get('source')=='scripts/extract-msvc-library-object.py'
            and u.get('profile')=='vc8-sp1-libcmt'and u.get('enable_gs')is False and u.get('toolchain_library')=='libcmt'
            and u.get('toolchain_object')==member and u.get('toolchain_archive_sha256')==sqrt.ARCHIVE_SHA,'sin original member differs')
        calls=[n+'='+f'0x{CALLS[n]:08X}'for n in ['__fast_exit','__math_exit','__convertTOStoQNaN','__startOneArgErrorHandling']]if key==SIN_UNIT else['__sin_default=0x0068B6BF']
        require(u['functions']==[dict(address=a['address'],symbol_base='start',rel32_targets=calls,dir32_targets=SIN_BINDINGS if key==SIN_UNIT else P4_BINDINGS)],
            'sin formal shared/data/call contract differs')
    old=tomllib.loads(sqrt.ANCHORS.read_text());sqrt.validate_spec(old,[dict(address='0x0068A39D',size='157')],units,target_sha)
    return aa

def qualify(units,anchors,rows,read,c,game):
    old=tomllib.loads(sqrt.ANCHORS.read_text());common_proof=sqrt.qualify(units[sqrt.UNIT],old['anchors'][0],rows,read,c,game)
    paths={'sin.obj':ROOT/units[SIN_UNIT]['object'],'sin_pentium4.obj':ROOT/units[P4_UNIT]['object'],'mathfcns.obj':OUTPUT/'mathfcns.obj'}
    for name,p in paths.items():require(digest(p.read_bytes())==HASHES[name],'sin actual archive member differs: '+name)
    r=sqrt.Reader(paths['sin.obj']);p=sqrt.Reader(paths['sin_pentium4.obj']);controller=sqrt.Reader(paths['mathfcns.obj']);known=c.known_data_targets()
    ns=r.section('_NAME_');name_data=r.raw('_NAME_',7)
    require(r.symbol('_NAME_').value==0 and ns.name=='.data'and ns.raw_size==7 and ns.reloc_count==0 and name_data==b'sin\0\0\0\0'
        and name_data==read(0x6f7ab0,7)and sqrt.initialized(game,0x6f7ab0,7,False)==name_data,'sin complete operation-name data differs')
    common=sqrt.Reader(sqrt.OUTPUT/'common.obj');require(common.symbol('__pi_by_2_to_61').value==10
        and common.symbol('__pi_by_2_to_61').section_number==common.symbol('One').section_number,'sin actual extended constant role differs')
    sec=p.section('Ctable');require(p.symbol('Ctable').value==0 and sec.name=='.rdata'and sec.raw_size==2208 and sec.reloc_count==0
        and sec.characteristics&0x40000000 and not sec.characteristics&0xa0000000,'sin complete coefficient source storage differs')
    coeff=p.raw('Ctable',2208);require(coeff==read(0x6cdc70,2208)and sqrt.core.readonly_data(game,0x6cdc70,2208)==coeff,'sin whole coefficient section differs')
    for name,offset in P4_LABELS.items():require(p.symbol(name).section_number==p.symbol('Ctable').section_number and p.symbol(name).value==offset,'sin coefficient source label differs')
    ends=sorted(P4_LABELS.values())+[2208]
    for off,kind,name in P4_REFS:
        if kind!=6:continue
        pos=P4_LABELS[name];end=next(x for x in ends if x>pos)
        require(known.get('vc8_sin_p4_'+name)==(0x6cdc70+pos,coeff[pos:end],frozenset({0}),'literal'),'sin complete coefficient literal binding differs')
    expected={'vc8_sin_use_sse2':(0x7039c4,bytes(4),frozenset({0}),'address'),
        'vc8_sin_operation_name':(0x6f7ab0,name_data,frozenset({0}),'literal'),
        'vc8_common_default_cw':(0x6cda28,read(0x6cda28,2),frozenset({0}),'address'),
        'vc8_common_pi_by_2_to_61':(0x6cda2a,read(0x6cda2a,10),frozenset({0}),'address')}
    require(all(known.get(k)==v for k,v in expected.items()),'sin typed common-data bindings differ')
    # The real controller declares a COFF common block, not an initialized/BSS section symbol.
    obj=paths['mathfcns.obj'].read_bytes();ptr,count=struct.unpack_from('<II',obj,8)
    flags=[(i,s)for i,s in controller.cf.symbols.items()if s.name=='___use_sse2_mathfcns'];require(len(flags)==1,'sin SSE selector source is ambiguous')
    i,flag=flags[0];rec=obj[ptr+18*i:ptr+18*(i+1)]
    require(flag.section_number==0 and flag.value==4 and rec[14:18]==bytes([0,0,2,0]),'sin SSE selector must be the actual four-byte external common block')
    require(sqrt.zero_initialized_counter(game,0x7039c4,4)==bytes(4),'sin SSE selector must occupy native PE zero-fill')
    init='__sse2_mathfcns_init';require(controller.symbol(init).value==0 and controller.section(init).raw_size==20
        and controller.refs(init,20)==[(2,6,'___use_sse2_mathfcns'),(8,20,'__get_sse2_info'),(13,6,'___use_sse2_mathfcns')],
        'sin complete SSE initializer source differs')
    by={x['address']:x for x in rows};origins={x['address']:x for x in csv.DictReader((ROOT/'config/function-origins.csv').open())}
    for at,name in [(0x69098f,init),(0x69c978,'__get_sse2_info'),(0x68b630,'_sin'),(0x68b670,'__CIsin'),(0x694e20,'__CIsin_pentium4')]:
        key=f'0x{at:08X}';require(by[key]['current_name']==name and origins[key]['disposition']=='exclude','sin actual named existing runtime ownership differs')
    init_body=c.coff_symbol_bytes(paths['mathfcns.obj'],init,0x69098f,0xffffffff,{'__get_sse2_info':0x69c978},{'___use_sse2_mathfcns':expected['vc8_sin_use_sse2']})
    require(len(init_body)==20 and init_body==read(0x69098f,20),'sin whole native SSE initializer differs');sqrt.core.decode_closed_body(init_body,0x69098f)
    owners=[];regions=[];bodies={}
    for reader,entry,key,member,base,extent,refs,ranges,bindings in [(r,'_sin',SIN_UNIT,'sin.obj',0x68b630,297,SIN_REFS,SIN_RANGES,SIN_BINDINGS+['___use_sse2_mathfcns=vc8_sin_use_sse2']),
            (p,'__CIsin_pentium4',P4_UNIT,'sin_pentium4.obj',0x694e20,456,P4_REFS,P4_RANGES,P4_BINDINGS)]:
        require(reader.symbol(entry).value==0 and reader.section(entry).name=='.text'and reader.section(entry).raw_size==extent and reader.refs(entry,extent)==refs,
            'sin full original owner extent/relocation inventory differs')
        raw=reader.raw(entry,extent);body=c.coff_symbol_bytes(paths[member],entry,base,0xffffffff,CALLS,known,dict(x.split('=',1)for x in bindings))
        require(len(body)==extent and body==read(base,extent),'sin complete coupled owner differs')
        allowed={i for off,k,n in refs for i in range(off,off+4)};require(all(x==y for i,(x,y)in enumerate(zip(raw,body))if i not in allowed),'sin changed nonrelocation bytes')
        pad=63 if key==SIN_UNIT else 455;require(raw[pad:pad+1]==body[pad:pad+1]==b'\x90','sin exact original alignment byte differs')
        for begin,end,name in ranges:
            require(reader.symbol(name).section_number==reader.symbol(entry).section_number and reader.symbol(name).value==begin,'sin actual public/shared entry position differs')
            regions.append((base+begin,body[begin:end],member+':'+name))
        bodies[key]=body;owners.append(dict(address=hex(base),size=extent,sha256=digest(body),alignment_byte_offset=pad,entries={name:begin for begin,end,name in ranges}))
    for name,to,size,off,nxt in sqrt.HELPERS:
        if name!='__load_CW':regions.append((to,read(to,size),name))
    graph=sqrt.closed_graph(regions,[0x68b630,0x68b670],{0x690d87})
    facts=[]
    for a in anchors:
        size,key,member,base,offset,extent=CONTRACT[a['address']];u=units[key];binding=SIN_BINDINGS if key==SIN_UNIT else P4_BINDINGS
        raw=c.coff_symbol_bytes(paths[member],'start',int(a['address'],0),0xffffffff,CALLS,known,dict(x.split('=',1)for x in binding))
        require(raw==bodies[key][offset:]and raw[:size]==read(int(a['address'],0),size)and digest(raw[:size])==a['sha256'],'sin complete shared body differs')
        hits=[x['address']for x in rows if int(x['size'],0)==size and c.coff_symbol_bytes(paths[member],'start',int(x['address'],0),0xffffffff,CALLS,known,dict(y.split('=',1)for y in binding))[:size]==read(int(x['address'],0),size)]
        require(hits==[a['address']],'sin shared body is not inventory-unique');facts.append(dict(address=a['address'],size=size,sha256=digest(raw[:size]),inventory_hits=hits,masked_bytes=0,unequal_bytes=0))
    return dict(anchors=facts,owners=owners,graph=graph,coefficient_section=dict(address='0x006CDC70',size=2208,sha256=digest(coeff)),
        selector=dict(address='0x007039C4',size=4,allocation='Original COFF external common symbol plus native zero-fill',initializer_address='0x0069098F',initializer_size=20,initializer_sha256=digest(init_body)),
        common_support=common_proof,scope='570 new shared runtime bytes only; no public-prefix/helper/data/alignment or authored credit')

def validate(rule,selected,rows,read,target_sha):
    try:
        require(ROOT/str(rule['vc8_sin_shared_anchor_file'])==ANCHORS,'unreviewed sin anchor path')
        units=sqrt.load_manifest()['units'];aa=validate_spec(tomllib.loads(ANCHORS.read_text()),selected,units,target_sha)
        errors=sqrt.validate(dict(id='vc8-original-sqrt-shared-owner-106a',vc8_sqrt_shared_anchor_file=str(sqrt.ANCHORS.relative_to(ROOT))),[x for x in rows if x['address']=='0x0068A39D'],rows,read,target_sha)
        require(not errors,'sin common exact dependency failed: '+'; '.join(errors))
        archive=(ROOT/'.tools/msvc80-sp1/lib/libcmt.lib').read_bytes();require(digest(archive)==sqrt.ARCHIVE_SHA,'sin original archive differs')
        sp=importlib.util.spec_from_file_location('sin_extract',ROOT/'scripts/extract-msvc-library-object.py');m=importlib.util.module_from_spec(sp);sp.loader.exec_module(m)
        found=[b for n,b in m.archive_members(archive)if Path(n).name=='mathfcns.obj'];require(len(found)==1 and digest(found[0])==HASHES['mathfcns.obj'],'sin controller archive identity differs');OUTPUT.mkdir(parents=True,exist_ok=True);(OUTPUT/'mathfcns.obj').write_bytes(found[0])
        records=[build.build_unit(key,units[key],True,target_sha)for key in (SIN_UNIT,P4_UNIT)];c=sqrt.core.comparator();c.verify_target();game=pefile.PE(str(c.TARGET));proof=qualify(units,aa,rows,read,c,game);comparisons=[]
        for key in (SIN_UNIT,P4_UNIT):
            code,results=build.compare_unit(units[key],True);require(code==0 and len(results)==1 and results[0]['result']=='exact','sin formal shared-body comparison failed');comparisons.extend(results)
        proof.update(builds=records,comparisons=comparisons,member_sha256=HASHES,validator_sha256=sqrt.core.sha(Path(__file__)),anchor_sha256=sqrt.core.sha(ANCHORS),common_validator_sha256=sqrt.core.sha(Path(sqrt.__file__)))
        (OUTPUT/'proof.json').write_text(json.dumps(proof,indent=2)+'\n');return []
    except (OSError,ValueError,KeyError,TypeError,RuntimeError,struct.error,pefile.PEFormatError)as exc:return [str(rule['id'])+': '+str(exc)]

def main():
    c=sqrt.core.comparator();sha=c.verify_target();rows=list(csv.DictReader((ROOT/'config/functions.csv').open()))
    result=validate(dict(id='vc8-original-sin-shared-owners-106a',vc8_sin_shared_anchor_file=str(ANCHORS.relative_to(ROOT))),[r for r in rows if r['address']in CONTRACT],rows,c.target_bytes,sha)
    print(json.dumps(dict(errors=result)));return bool(result)
if __name__=='__main__':raise SystemExit(main())
