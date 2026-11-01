"""Whole original SDK table getters and complete initialized data sections."""
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
from coff_exception_rtti import Reader
from workflow_manifest import load_manifest
from linked_logic_error_origins import require,digest

ROOT=Path(__file__).resolve().parents[1]
ANCHORS=ROOT/'config/xiph-table-getter-origin-anchors.toml'
ARCHIVE_SHA='fead50bbdf6a17e695b8b628f4ebe2c64a8f589ca6b983909484f4f361afbfcc'
CONTRACT={
 '0x00684CF0':dict(unit='xiph-original-window-get',member='window.obj',symbol='__vorbis_window_get',table='_vwin',
    object_sha='b1906845039a193d3d0c7d1190e10aae87e159adf9bdbcf0eb60c98d1f2b6bab',base=0x6ef17c,size=32672,offset=32640,addend=0,
    labels={'_vwin64':0,'_vwin128':128,'_vwin256':384,'_vwin512':896,'_vwin1024':1920,'_vwin2048':3968,'_vwin4096':8064,'_vwin8192':16256,'_vwin':32640}),
 '0x00689820':dict(unit='xiph-original-invsq2exp-lookup',member='lsp.obj',symbol='_vorbis_invsq2explook',table='_INVSQ2EXP_LOOKUP',
    object_sha='c89a27b23e2ea6e4fb3128912ba8e3cc4005207eef90342da07fa784dc2069ec',base=0x6f75d4,size=1176,offset=648,addend=128,
    labels={'_COS_LOOKUP':0,'_INVSQ_LOOKUP':516,'_INVSQ2EXP_LOOKUP':648,'_FROMdB_LOOKUP':908,'_FROMdB2_LOOKUP':1048}),
}

def validate_spec(spec,selected,units,target_sha):
    require(set(spec)=={'schema_version','target_sha256','anchors'}and type(spec['schema_version'])is int and spec['schema_version']==1
        and spec['target_sha256']==target_sha,'SDK getters schema/target differs')
    aa=spec['anchors'];by={x['address']:x for x in selected}
    require(len(aa)==len(selected)==2 and set(by)==set(CONTRACT)and {a['address']for a in aa}==set(CONTRACT),'SDK getters selection differs')
    for a in aa:
        k=CONTRACT[a['address']]
        require(set(a)=={'address','size','symbol','unit','sha256'}and type(a['size'])is int and a['size']==12 and int(by[a['address']]['size'],0)==12
            and a['symbol']==k['symbol']and a['unit']==k['unit']and isinstance(a['sha256'],str)and len(a['sha256'])==64
            and all(c in '0123456789abcdef'for c in a['sha256']),'SDK getter typed complete anchor differs')
        u=units[k['unit']]
        require(u.get('kind')=='upstream_prebuilt'and u.get('source')=='scripts/fetch-xiph-sdk-object.py'
            and u.get('profile')=='xiph-win32sdk-1.0.1'and u.get('enable_gs')is False and u.get('sdk_component')=='vorbis'
            and u.get('sdk_object')==k['member']and u.get('sdk_archive_sha256')==ARCHIVE_SHA,'SDK getter original member/profile differs')
        require(u['functions']==[dict(address=a['address'],symbol_base=k['symbol'],dir32_targets=[k['table']+'='+k['table']])],
            'SDK getter formal whole-body/table contract differs')
    return aa

def initialized_data(pe,address,size):
    rva=address-pe.OPTIONAL_HEADER.ImageBase
    sections=[s for s in pe.sections if s.VirtualAddress<=rva and rva+size<=s.VirtualAddress+s.SizeOfRawData]
    require(len(sections)==1 and sections[0].Name.rstrip(b'\0')==b'.data'and sections[0].Characteristics&0x40000000
        and sections[0].Characteristics&0x80000000 and not sections[0].Characteristics&0x20000000,
        'SDK getter data must be whole initialized writable non-executable storage')
    return pe.get_data(rva,size)

def qualify(unit,anchor,rows,read,c,game):
    k=CONTRACT[anchor['address']];obj=ROOT/unit['object'];require(digest(obj.read_bytes())==k['object_sha'],'SDK getter original object differs')
    r=Reader(obj);symbol=r.symbol(k['table']);sec=r.section(k['table'])
    require(sec.name=='.data'and sec.raw_size==k['size']and symbol.value==k['offset']and sec.raw_offset>0
        and sec.characteristics&0x40000000 and sec.characteristics&0x80000000 and not sec.characteristics&0x20000000,
        'SDK getter complete source data section differs')
    for name,off in k['labels'].items():
        s=r.symbol(name);require(s.section_number==symbol.section_number and s.value==off,'SDK getter actual data-label role differs')
    raw_data=r.cf._read_raw(sec.raw_offset,sec.raw_size);canonical_data=bytearray(raw_data);pointer_roles=[]
    expected=[(32640+4*i,n)for i,n in enumerate(list(k['labels'])[:-1])]if k['table']=='_vwin'else[]
    require(sec.reloc_count==len(expected),'SDK getter full data relocation inventory differs')
    for i,(expected_offset,expected_name)in enumerate(expected):
        off,idx,kind=struct.unpack('<IIH',r.cf._read_raw(sec.reloc_offset+10*i,10));s=r.cf.symbols[idx]
        require(off==expected_offset and kind==6 and s.name==expected_name and s.section_number==symbol.section_number
            and s.value==k['labels'][expected_name]and struct.unpack_from('<I',raw_data,off)[0]==0,
            'SDK getter pointer table must reference its actual complete window arrays')
        to=k['base']+s.value;struct.pack_into('<I',canonical_data,off,to);pointer_roles.append(dict(field=off,symbol=s.name,address=hex(to)))
    native=read(k['base'],k['size'])
    require(bytes(canonical_data)==native and initialized_data(game,k['base'],k['size'])==native,'SDK getter complete data section differs')
    name,raw,_,refs=rank.read_coff_function(obj,k['symbol'],None)
    require(name==k['symbol']and len(raw)==16 and raw[12:]==b'\x90'*4 and refs==[(7,6,k['table'])]
        and struct.unpack_from('<I',raw,7)[0]==k['addend'],'SDK getter complete code section/real table addend differs')
    data=c.known_data_targets();target_base=k['base']+k['offset']
    require(data[k['table']]==(target_base,native[k['offset']+k['addend']:k['offset']+k['addend']+4],frozenset({k['addend']}),'address'),
        'SDK getter isolated table mapping/addend differs')
    to=int(anchor['address'],0);body=c.coff_symbol_bytes(obj,k['symbol'],to,0xffffffff,{},data)
    require(len(body)==16 and body==read(to,16)and digest(body[:12])==anchor['sha256'],'SDK getter whole callable and padding differ')
    allowed=set(range(7,11));require(all(x==y for i,(x,y)in enumerate(zip(raw,body))if i not in allowed),'SDK getter changed nonrelocation byte')
    ins=core.decode_closed_body(body[:12],to)
    hits=[x['address']for x in rows if int(x['size'],0)==12 and c.coff_symbol_bytes(obj,k['symbol'],int(x['address'],0),0xffffffff,{},data)[:12]==read(int(x['address'],0),12)]
    require(hits==[anchor['address']],'SDK getter complete callable is not inventory-unique')
    return dict(anchor=dict(address=anchor['address'],size=12,section_size=16,symbol=k['symbol'],sha256=digest(body[:12]),section_sha256=digest(body),
        inventory_hits=hits,instructions=len(ins),masked_bytes=0,unequal_bytes=0),
        data=dict(address=hex(k['base']),size=k['size'],sha256=digest(native),table_offset=k['offset'],code_addend=k['addend'],pointer_roles=pointer_roles,
            storage='Complete initialized writable data section; no data or padding bytes count as authored/function credit'))

def validate(rule,selected,rows,read,target_sha):
    try:
        require(ROOT/str(rule['xiph_table_getter_anchor_file'])==ANCHORS,'unreviewed SDK getter anchor path')
        units=load_manifest()['units'];aa=validate_spec(tomllib.loads(ANCHORS.read_text()),selected,units,target_sha)
        sdk=(ROOT/'.tools/upstream/OggVorbis-win32sdk-1.0.1.zip').read_bytes();require(digest(sdk)==ARCHIVE_SHA,'SDK getter archive differs')
        sp=importlib.util.spec_from_file_location('table_sdk',ROOT/'scripts/fetch-xiph-sdk-object.py');m=importlib.util.module_from_spec(sp);sp.loader.exec_module(m)
        c=core.comparator();c.verify_target();game=pefile.PE(str(c.TARGET));facts=[];builds=[];comparisons=[]
        for a in aa:
            k=CONTRACT[a['address']];require(digest(m.extract_object(sdk,'vorbis',k['member']))==digest(m.extract_object(sdk,'vorbisfile',k['member']))==k['object_sha'],
                'SDK getter duplicate archive members must be identical, not extra credit')
            u=units[k['unit']];builds.append(build.build_unit(k['unit'],u,True,target_sha));facts.append(qualify(u,a,rows,read,c,game))
            code,results=build.compare_unit(u,True);require(code==0 and len(results)==1 and results[0]['result']=='exact','SDK getter formal comparison failed');comparisons.extend(results)
        proof=dict(anchors=facts,builds=builds,comparisons=comparisons,archive_sha256=ARCHIVE_SHA,validator_sha256=core.sha(Path(__file__)),anchor_sha256=core.sha(ANCHORS))
        (ROOT/'build/origin-anchors/xiph-table-getters.json').write_text(json.dumps(proof,indent=2)+'\n');return []
    except (OSError,ValueError,KeyError,TypeError,RuntimeError,struct.error,pefile.PEFormatError)as exc:return [str(rule['id'])+': '+str(exc)]

def main():
    c=core.comparator();sha=c.verify_target();rows=list(csv.DictReader((ROOT/'config/functions.csv').open()))
    result=validate(dict(id='xiph-original-table-getters-106a',xiph_table_getter_anchor_file=str(ANCHORS.relative_to(ROOT))),[r for r in rows if r['address']in CONTRACT],rows,c.target_bytes,sha)
    print(json.dumps(dict(errors=result)));return bool(result)
if __name__=='__main__':raise SystemExit(main())
