"""Original CRT data-address accessors with complete initialized/common owners."""
import csv
import json
from pathlib import Path
import struct
import tomllib
import pefile
import build
import linked_pe as core
from coff_exception_rtti import Reader
from workflow_manifest import load_manifest
from linked_logic_error_origins import require,digest
from vc8_sqrt_shared_origins import initialized
ROOT=Path(__file__).resolve().parents[1]
ANCHORS=ROOT/'config/vc8-data-accessor-origin-anchors.toml'
OUTPUT=ROOT/'build/origin-anchors/vc8-data-accessors'
ARCHIVE='3bc6c5b90f8507964839fd0264d8565c3b766d01f9efcad336532a11e8f06ac3'
IOB_UNIT='vc8-original-iob-accessor'
TIME_UNIT='vc8-original-time-data-accessors'
MEMBERS={IOB_UNIT:('_file.obj','935bb014351a6bdcb3a82106822af15ff2ebc9d51cec5b3aaeddf46c6d032e68'),TIME_UNIT:('timeset.obj','55559252e1be98ced21a48d4ee6ee7e97a45ccac131751ebc455c913bbab4781')}
CONTRACT={
 '0x0068D059':(IOB_UNIT,'___iob_func','__iob','vc8_iob_array',0x6f7b50),
 '0x00692481':(TIME_UNIT,'___daylight','__daylight','vc8_daylight_cell',0x6f86e4),
 '0x00692487':(TIME_UNIT,'___dstbias','__dstbias','vc8_dstbias_cell',0x6f86e8),
 '0x0069248D':(TIME_UNIT,'___timezone','__timezone','vc8_timezone_cell',0x6f86e0),
 '0x00692493':(TIME_UNIT,'___tzname','__tzname','vc8_tzname_array',0x6f8770)}

def validate_spec(spec,selected,units,target_sha):
    require(set(spec)=={'schema_version','target_sha256','anchors'}and type(spec['schema_version'])is int and spec['schema_version']==1 and spec['target_sha256']==target_sha,'CRT accessor schema/target differs')
    aa=spec['anchors'];by={r['address']:r for r in selected};require(len(aa)==len(selected)==len(CONTRACT)and set(by)==set(CONTRACT)and {a['address']for a in aa}==set(CONTRACT),'CRT accessor complete selection differs')
    for a in aa:
        key,sym,data,alias,to=CONTRACT[a['address']];require(set(a)=={'address','size','symbol','unit','sha256'}and type(a['size'])is int and a['size']==6 and int(by[a['address']]['size'],0)==6 and a['symbol']==sym and a['unit']==key and isinstance(a['sha256'],str)and len(a['sha256'])==64 and all(x in '0123456789abcdef'for x in a['sha256']),'CRT accessor whole member identity differs')
    for key,(member,sha)in MEMBERS.items():
        u=units[key];require(u.get('kind')=='msvc_prebuilt'and u.get('source')=='scripts/extract-msvc-library-object.py'and u.get('profile')=='vc8-sp1-libcmt'and u.get('enable_gs')is False and u.get('toolchain_library')=='libcmt'and u.get('toolchain_object')==member and u.get('toolchain_archive_sha256')==ARCHIVE,'CRT accessor original archive/member differs')
        expected=[dict(address=at,symbol_base=sym,dir32_targets=[data+'='+alias])for at,(k,sym,data,alias,to)in CONTRACT.items()if k==key];require(u['functions']==expected,'CRT accessor exact symbol/data roles differ')
    return aa

def zero_fill_buffer(pe,address,size):
    require(address==0x703a00 and size==4096,'CRT stdin buffer must retain its actual full common allocation')
    rva=address-pe.OPTIONAL_HEADER.ImageBase;ss=[s for s in pe.sections if s.VirtualAddress+s.SizeOfRawData<=rva and rva+size<=s.VirtualAddress+s.Misc_VirtualSize]
    require(len(ss)==1 and ss[0].Characteristics&0xc0000000==0xc0000000 and not ss[0].Characteristics&0x20000000,'CRT stdin buffer must be wholly writable non-executable PE zero-fill')
    return dict(address='0x00703A00',size=4096,allocation='original COFF common plus whole native PE virtual zero-fill; no raw-byte read')

def qualify(units,anchors,rows,read,c,game):
    paths={key:ROOT/units[key]['object']for key in MEMBERS};readers={}
    for key,p in paths.items():require(digest(p.read_bytes())==MEMBERS[key][1],'CRT accessor original object hash differs');readers[key]=Reader(p)
    io=readers[IOB_UNIT];tm=readers[TIME_UNIT];known=c.known_data_targets()
    rawobj=paths[IOB_UNIT].read_bytes();ptr,count=struct.unpack_from('<II',rawobj,8);common=[(i,s)for i,s in io.cf.symbols.items()if s.name=='__bufin'];require(len(common)==1,'CRT stdin common symbol is ambiguous');idx,sym=common[0];rec=rawobj[ptr+18*idx:ptr+18*(idx+1)]
    require(sym.section_number==0 and sym.value==4096 and rec[14:18]==bytes([0,0,2,0]),'CRT stdin buffer must be the real4096-byte external common definition')
    bss=zero_fill_buffer(game,0x703a00,4096)
    sec=io.section('__iob');require(io.symbol('__iob').value==0 and sec.name=='.data'and sec.raw_size==640 and io.refs('__iob',640)==[(0,6,'__bufin'),(8,6,'__bufin')],'CRT complete IOB source data differs')
    raw=bytearray(io.raw('__iob',640));require(list(struct.unpack_from('<8I',raw))==[0,0,0,257,0,0,4096,0],'CRT initial stdin record does not bind the full buffer capacity')
    for off in [0,8]:require(struct.unpack_from('<I',raw,off)[0]==0,'CRT IOB pointer addend differs');struct.pack_into('<I',raw,off,0x703a00)
    iob=bytes(raw);require(iob==read(0x6f7b50,640)and initialized(game,0x6f7b50,640,False)==iob,'CRT complete initialized IOB array differs')
    require(known.get('vc8_iob_array')==(0x6f7b50,iob[:4],frozenset({0}),'address'),'CRT IOB address binding differs')
    sec=tm.section('__timezone');require(tm.symbol('__timezone').value==0 and sec.name=='.data'and sec.raw_size==152 and tm.refs('__timezone',152)==[(144,6,'_tzstd'),(148,6,'_tzdst')],'CRT complete timezone source section differs')
    labels={'__timezone':0,'__daylight':4,'__dstbias':8,'_tzstd':16,'_tzdst':80,'__tzname':144}
    for n,pos in labels.items():require(tm.symbol(n).value==pos and tm.symbol(n).section_number==tm.symbol('__timezone').section_number,'CRT timezone actual source label differs')
    raw=bytearray(tm.raw('__timezone',152))
    for off,name in [(144,'_tzstd'),(148,'_tzdst')]:require(struct.unpack_from('<I',raw,off)[0]==0,'CRT timezone pointer addend differs');struct.pack_into('<I',raw,off,0x6f86e0+labels[name])
    time_data=bytes(raw);require(time_data==read(0x6f86e0,152)and initialized(game,0x6f86e0,152,False)==time_data,'CRT complete initial timezone data differs')
    for key,pos,size,mode in [('vc8_timezone_cell',0,4,'literal'),('vc8_daylight_cell',4,4,'literal'),('vc8_dstbias_cell',8,4,'literal'),('vc8_tzname_array',144,8,'address')]:require(known.get(key)==(0x6f86e0+pos,time_data[pos:pos+size],frozenset({0}),mode),'CRT exact typed timezone mapping differs')
    facts=[]
    for a in anchors:
        key,sym,data,alias,to=CONTRACT[a['address']];r=readers[key];p=paths[key];at=int(a['address'],0);require(r.symbol(sym).value==0 and r.section(sym).name=='.text'and r.section(sym).raw_size==6 and r.refs(sym,6)==[(1,6,data)]and r.raw(sym,6)[1:5]==bytes(4),'CRT accessor complete source extent/field differs')
        b=c.coff_symbol_bytes(p,sym,at,6,{},known,{data:alias});require(len(b)==6 and b==read(at,6)and digest(b)==a['sha256'],'CRT accessor whole canonical body differs');ins=core.decode_closed_body(b,at)
        hits=[x['address']for x in rows if int(x['size'],0)==6 and c.coff_symbol_bytes(p,sym,int(x['address'],0),6,{},known,{data:alias})==read(int(x['address'],0),6)];require(hits==[a['address']],'CRT accessor entire body is not inventory-unique')
        facts.append(dict(address=a['address'],size=6,symbol=sym,sha256=digest(b),data_symbol=data,data_address=hex(to),inventory_hits=hits,instructions=len(ins),masked_bytes=0,unequal_bytes=0))
    return dict(anchors=facts,iob=dict(address='0x006F7B50',size=640,sha256=digest(iob)),timezone=dict(address='0x006F86E0',size=152,sha256=digest(time_data)),stdin_buffer=bss,scope='30 runtime accessor bytes only; initialized-image/common allocation proof, not runtime immutability; no data/BSS/initializer/authored credit')

def validate(rule,selected,rows,read,target_sha):
    try:
        require(ROOT/str(rule['vc8_data_accessor_anchor_file'])==ANCHORS,'unreviewed CRT accessor anchor path');units=load_manifest()['units'];aa=validate_spec(tomllib.loads(ANCHORS.read_text()),selected,units,target_sha);builds=[build.build_unit(key,units[key],True,target_sha)for key in MEMBERS]
        c=core.comparator();c.verify_target();game=pefile.PE(str(c.TARGET));proof=qualify(units,aa,rows,read,c,game);reports=[]
        for key in MEMBERS:
            code,results=build.compare_unit(units[key],True);require(code==0 and len(results)==len(units[key]['functions'])and all(r['result']=='exact'for r in results),'CRT accessor formal comparisons failed');reports+=results
        proof.update(builds=builds,comparisons=reports,member_sha256={k:v[1]for k,v in MEMBERS.items()},validator_sha256=core.sha(Path(__file__)),anchor_sha256=core.sha(ANCHORS));OUTPUT.mkdir(parents=True,exist_ok=True);(OUTPUT/'proof.json').write_text(json.dumps(proof,indent=2)+'\n');return []
    except (OSError,ValueError,KeyError,TypeError,RuntimeError,struct.error,pefile.PEFormatError)as exc:return [str(rule['id'])+': '+str(exc)]

def main():
    c=core.comparator();sha=c.verify_target();rows=list(csv.DictReader((ROOT/'config/functions.csv').open()));result=validate(dict(id='vc8-original-data-accessors-106a',vc8_data_accessor_anchor_file=str(ANCHORS.relative_to(ROOT))),[r for r in rows if r['address']in CONTRACT],rows,c.target_bytes,sha);print(json.dumps(dict(errors=result)));return bool(result)
if __name__=='__main__':raise SystemExit(main())
