"""Original unsigned-list growth in the actual BGM lifetime CIL graph."""
import csv
import hashlib
import json
from pathlib import Path
import struct
import tomllib
import capstone
import pefile
import linked_pe as core
import linked_logic_error_origins as logic
import linked_bad_alloc_origins as bad
from linked_logic_error_origins import require, named, digest
from workflow_manifest import load_manifest, source_dependencies

ROOT = Path(__file__).resolve().parents[1]
ANCHORS = ROOT/'config/linked-unsigned-list-growth-origin-anchors.toml'
UNIT = 'exact-first-bgm-service-lifetime'
SYMBOL = '?_Incsize@?$list@IV?$allocator@I@std@@@std@@IAEXI@Z'
PARENT = '?release@BgmAllocationManager50@th105@@QAEXI@Z'
STRING_ASSIGN = '?assign@?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@QAEAAV12@PBDI@Z'
STRING_DTOR = '??1?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@QAE@XZ'
LENGTH_DTOR = '??1length_error@std@@UAE@XZ'
LENGTH_COPY = '??0length_error@std@@QAE@ABV01@@Z'
LENGTH_VTABLE = '??_7length_error@std@@6B@'
THROW_INFO = '__TI3?AVlength_error@std@@'
LITERAL = '??_C@_0BB@MOGOBHAF@list?$DMT?$DO?5too?5long?$AA@'
TEXT = b'list<T> too long\0'
SHA = '0743f70aab2e36a82b3ee5df1e3a2cd5312c75b966f90846b4e1fd7ed7f7c79f'
HEADERS = {
    'include/list': '11cd2edd5f34036b95bcb8eb0323e466ce0c535227c7e2612fc8703976ab4a3b',
    'include/xstring': 'c1a068968165290d000d554340d9c4e7e123c47ea619ad05d1c8f4e719c05922',
    'include/stdexcept': '6d0f7027cb666813b92aaef26165fb493969c3dd0109ce3df8e04e7bffd4a2cc',
    'include/xmemory': '83a2121ebc455b25493a689a4fb299db0ca848ffc29668159bc9fb5faa95e50b',
}


def inputs(unit):
    paths = set(source_dependencies(unit))
    for s in unit.get('linked_coff_sources', []):
        paths.update(source_dependencies(dict(source=s)))
    return paths


def validate_spec(spec,selected,unit,target_sha):
    require(set(spec)=={'schema_version','target_sha256','unit','source_pins','anchors'}
        and type(spec['schema_version']) is int and spec['schema_version']==1
        and spec['target_sha256']==target_sha and spec['unit']==UNIT, 'list growth schema/target/unit differs')
    require(len(selected)==len(spec['anchors'])==1, 'list growth needs one whole candidate')
    anchor=spec['anchors'][0]
    require(anchor==dict(address='0x00402700',size=165,symbol=SYMBOL,sha256=SHA)
        and selected[0]['address']==anchor['address'] and int(selected[0]['size'],0)==165,
        'list growth whole target/type differs')
    require(unit.get('kind')=='linked_candidate' and unit.get('profile')==core.PROFILE
        and unit.get('source')=='src/audio/BgmServiceLifetime.cpp' and unit.get('enable_gs') is True
        and unit.get('link_runtime')=='static' and unit.get('link_xiph_sdk') is True
        and unit.get('linked_coff_sources')==['src/library/UnsignedIntList.cpp','src/library/UnsignedIntVector.cpp']
        and {f['address'] for f in unit['functions']}=={'0x004032F0','0x004033C0','0x00403ED0','0x004034F0'},
        'list growth actual BGM source graph differs')
    pins=spec['source_pins'];expected={str(p.relative_to(ROOT)) for p in inputs(unit)}
    require(isinstance(pins,dict) and set(pins)==expected and all(isinstance(v,str) and len(v)==64
        and all(c in '0123456789abcdef' for c in v) for v in pins.values()), 'list growth source closure differs')
    return anchor


def throw_metadata(pe,game,symbols,owner,read):
    sr=lambda a,n:core.pe_data(pe,a,n)
    words=lambda rd,a,n:list(struct.unpack('<'+'I'*n,rd(a,4*n)))
    source=named(symbols,THROW_INFO,owner);target=0x6e3be0
    dtor=named(symbols,LENGTH_DTOR,'i '+owner);si=words(sr,source,4);ti=words(read,target,4)
    require(si[:3]==[0,dtor,0]and ti[:3]==[0,0x401740,0],'tree length_error ThrowInfo differs')
    sa=words(sr,si[3],4);ta=words(read,ti[3],4)
    require(sa[0]==ta[0]==3,'tree length_error needs three catchable types')
    typeinfo=named(symbols,'??_7type_info@@6B@','libcmt:typinfo.obj');records=[]
    types=[('.?AVlength_error@std@@',40,LENGTH_COPY,0x402570,'i '+owner),
           ('.?AVlogic_error@std@@',40,logic.COPY,0x4017a0,'i '+owner),
           ('.?AVexception@std@@',12,'??0exception@std@@QAE@ABV01@@Z',0x689f82,'libcmt:stdexcpt.obj')]
    for idx,(name,size,copy,target_copy,copy_owner)in enumerate(types):
        at=sa[idx+1];bt=ta[idx+1];sw=words(sr,at,7);tw=words(read,bt,7)
        require([sw[i]for i in (0,2,3,4,5)]==[tw[i]for i in (0,2,3,4,5)]==[0,0,0xffffffff,0,size]
            and sw[6]==named(symbols,copy,copy_owner)and tw[6]==target_copy,'tree catchable layout/copy differs')
        literal=name.encode()+b'\0';sh=words(sr,sw[1],2);th=words(read,tw[1],2)
        require(sh==[typeinfo,0]and th[1]==0
            and core.primary_type_name(pe,typeinfo)==core.primary_type_name(game,th[0])=='.?AVtype_info@@'
            and sr(sw[1]+8,len(literal))==read(tw[1]+8,len(literal))==literal,'tree whole type descriptor differs')
        core.validate_body_relocations(pe,sw[1],8+len(literal),[dict(field_offset=0)])
        sw[1]=tw[1];sw[6]=tw[6]
        require(struct.pack('<7I',*sw)==read(bt,28),'tree canonical catchable record differs')
        core.validate_body_relocations(pe,at,28,[dict(field_offset=4),dict(field_offset=24)])
        records.append(dict(name=name,size=size,copy=hex(target_copy),descriptor_sha256=digest(read(tw[1],8+len(literal))),catchable_sha256=digest(read(bt,28))))
    si[1]=ti[1];si[3]=ti[3];sa[1:]=ta[1:]
    require(struct.pack('<4I',*si)==read(target,16)and struct.pack('<4I',*sa)==read(ti[3],16),'tree whole ThrowInfo/array differs')
    core.validate_body_relocations(pe,source,16,[dict(field_offset=4),dict(field_offset=12)])
    array=words(sr,source,4)[3];core.validate_body_relocations(pe,array,16,[dict(field_offset=4),dict(field_offset=8),dict(field_offset=12)])
    return source,dict(info_sha256=digest(read(target,16)),array_sha256=digest(read(ti[3],16)),types=records)


def qualify(pe,game,functions,symbols,owner,anchor,rows,origins,read):
    sr=lambda a,n:core.pe_data(pe,a,n)
    def loc(n,o=None):return named(symbols,n,o or 'i '+owner)
    call_map={}
    for n,(target,expected,evidence) in logic.CALLEES.items():
        source_owner='i '+owner if n==logic.ASSIGN else expected
        row=origins[f'0x{target:08X}']
        require(row['evidence_id']==evidence and row['disposition']=='exclude','list growth logic dependency origin differs')
        call_map[loc(n,source_owner)]=(n,target)
    for n,target,expected in [(STRING_ASSIGN,0x4021c0,'i '+owner),
        (STRING_DTOR,0x401e00,'i '+owner), ('??3@YAXPAX@Z',0x6898ea,'libcmt:delete.obj'),
        (bad.THROW,0x68a153,'libcmt:throw.obj')]:
        require(origins[f'0x{target:08X}']['disposition']=='exclude','list growth support origin differs')
        call_map[loc(n,expected)]=(n,target)
    def resolve(a):
        require(a in call_map,'list growth unproved named callee')
        return call_map[a]
    def canon(raw,at,to,**kw):
        return core.canonicalize(raw,at,to,[],resolve,(core.IMAGE_BASE,core.IMAGE_BASE+pe.OPTIONAL_HEADER.SizeOfImage),
            (0x400000,0x706000),**kw)
    logic_v=loc('??_7logic_error@std@@6B@',owner.replace('.ltcg.obj','.coff0.obj'))
    length_v=loc(LENGTH_VTABLE,owner.replace('.ltcg.obj','.coff0.obj'))
    cookie=loc('___security_cookie','libcmt:gs_cookie.obj')
    require(logic.rtti(sr,logic_v)==logic.rtti(read,0x6c05d0)==(0,0,0,b'.?AVlogic_error@std@@')
        and logic.rtti(sr,length_v)==logic.rtti(read,0x6c0888)==(0,0,0,b'.?AVlength_error@std@@')
        and sr(cookie,4)==read(0x6f7a88,4), 'list growth actual exception RTTI/cookie differs')
    logic_context=(call_map,logic_v,cookie)
    logic_proofs=[logic.qualify(pe,functions,symbols,a,rows,read,logic_context,owner=owner)
        for a in tomllib.loads(logic.ANCHORS.read_text())['anchors']]
    call_map[loc(logic.STRING)]=(logic.STRING,0x401670)
    call_map[loc(logic.COPY)]=(logic.COPY,0x4017a0)
    throw=bad.throw_witness(pe,game,functions,symbols,read)
    throw_info,throw_metadata_proof=throw_metadata(pe,game,symbols,owner,read)
    logic_table=dict(source_address=logic_v,target_address=0x6c05d0,symbol='logic_error',target_key='logic_error')
    length_table=dict(source_address=length_v,target_address=0x6c0888,symbol=LENGTH_VTABLE,target_key='length_error')
    support=[]
    for symbol,target,size,tail,tables in [(LENGTH_DTOR,0x401740,50,True,[logic_table]),
        (LENGTH_COPY,0x402570,25,False,[length_table]),(STRING_DTOR,0x401e00,38,False,[])]:
        a=loc(symbol);raw=core.linked_body(pe,functions,a)
        require(len(raw)==size,'list growth exception/string support extent differs')
        result,_,refs=canon(raw,a,target,vtables=tables,tail=tail)
        require(result==read(target,size),'list growth full exception/string support differs')
        core.validate_body_relocations(pe,a,size,refs)
        support.append(dict(symbol=symbol,address=hex(target),size=size,sha256=digest(result)))
    start=loc(SYMBOL);raw=core.linked_body(pe,functions,start)
    require(functions.get(start)==[(SYMBOL,'i '+owner)] and len(raw)==165, 'list growth whole source body/owner differs')
    require(all(core.IMAGE_BASE+e.address!=start for e in pe.DIRECTORY_ENTRY_EXPORT.symbols), 'list growth helper must not be forced export')
    parent=loc(PARENT,owner);parent_code=core.linked_body(pe,functions,parent)
    parent_calls=[i.address-parent for i in core.decode_closed_body(parent_code,parent) if i.group(capstone.CS_GRP_CALL)
        and i.operands[0].type==capstone.x86.X86_OP_IMM and i.operands[0].imm==start]
    require(digest(read(0x405200,167))=='f225dfcb190c5b55cba3f65a784ba7a244a15da3670549afac6573f6c4166421', 'list growth independent exact native owner changed')
    native_calls=[i.address for i in core.decode_closed_body(read(0x405200,167),0x405200) if i.group(capstone.CS_GRP_CALL)
        and i.operands[0].type==capstone.x86.X86_OP_IMM and i.operands[0].imm==0x402700]
    require(parent_calls==[0xe0] and native_calls==[0x405286],
        'list growth actual caller edges differ')
    handler=loc('__ehhandler$'+SYMBOL,'CIL library: CIL module');hb=core.linked_body(pe,functions,handler)
    require(len(hb)==27,'list growth whole handler extent differs')
    si=struct.unpack_from('<I',hb,18)[0];fi=sr(si,36);su=struct.unpack_from('<I',fi,8)[0];uw=sr(su,8);action=struct.unpack_from('<I',uw,4)[0]
    require(struct.unpack_from('<I',read(0x6e4644,36),8)[0]==0x6e463c
        and struct.unpack_from('<I',read(0x6e463c,8),4)[0]==0x6bdfa0,'list growth native EH pointer differs')
    metadata=logic.canonical_metadata(fi,read(0x6e4644,36),uw,read(0x6e463c,8))
    core.validate_body_relocations(pe,si,36,[dict(field_offset=8)]);core.validate_body_relocations(pe,su,8,[dict(field_offset=4)])
    require(functions.get(action)==[('__unwindfunclet$'+SYMBOL+'$0','CIL library: CIL module')], 'list growth actual unwind action differs')
    ab=core.linked_body(pe,functions,action);require(len(ab)==8,'list growth unwind extent differs')
    ac,_,ar=canon(ab,action,0x6bdfa0,tail=True);require(ac==read(0x6bdfa0,8),'list growth complete unwind differs');core.validate_body_relocations(pe,action,8,ar)
    hc,_,hr=canon(hb,handler,0x6bdfa8,tail=True,internal_refs=[dict(kind='eh_info',source_address=si,address=0x6e4644,size=36,symbol='FuncInfo')])
    require(hc==read(0x6bdfa8,27),'list growth complete handler differs');core.validate_body_relocations(pe,handler,27,hr)
    literal=loc(LITERAL,owner);require(core.readonly_data(pe,literal,len(TEXT))==core.readonly_data(game,0x6d6968,len(TEXT))==read(0x6d6968,len(TEXT))==TEXT,'list growth full literal differs')
    refs=[dict(kind='eh_handler',source_address=handler,address=0x6bdfa8,size=27,symbol='handler'),
        dict(kind='runtime',source_address=cookie,address=0x6f7a88,size=4,symbol='cookie'),
        dict(kind='literal',source_address=literal,address=0x6d6968,size=len(TEXT),literal_size=len(TEXT),read_offset=0,allow_pointer_push=True,symbol=LITERAL),
        dict(kind='object',source_address=throw_info,address=0x6e3be0,size=16,symbol=THROW_INFO)]
    def rebound(to):return canon(raw,start,to,vtables=[length_table],internal_refs=refs)
    canonical,cs,rs=rebound(0x402700)
    require(canonical==read(0x402700,165) and digest(canonical)==anchor['sha256']
        and [x['offset'] for x in cs]==[92,114,137] and [x['field_offset'] for x in rs]==[9,25,62,119,132],
        'list growth whole root/relocation roles differ')
    core.validate_body_relocations(pe,start,165,rs);core.decode_closed_body(canonical,0x402700)
    allowed={i for off in [92,114,137,9,25,62,119,132] for i in range(off,off+4)}
    require(all(x==y for i,(x,y) in enumerate(zip(raw,canonical)) if i not in allowed),'list growth changed non-relocation byte')
    hits=[r['address'] for r in rows if int(r['size'],0)==165 and rebound(int(r['address'],0))[0]==read(int(r['address'],0),165)]
    require(hits==['0x00402700'],'list growth full inventory uniqueness differs')
    return dict(address=anchor['address'],size=165,sha256=digest(canonical),source_va=hex(start),symbol=SYMBOL,
        native_owner='0x00405200',source_owner=hex(parent),source_owner_exact=False,owner_sites=[hex(a) for a in native_calls],calls=cs,references=rs,inventory_hits=hits,
        logic_support=logic_proofs,support=support,throw=throw,throw_metadata=throw_metadata_proof,
        eh=dict(handler_sha256=digest(hc),action_sha256=digest(ac),**metadata),masked_bytes=0,unequal_bytes=0)


def validate(rule,selected,rows,read,target_sha):
    try:
        require(ROOT/str(rule['linked_unsigned_list_growth_anchor_file'])==ANCHORS,'list growth anchor path differs')
        unit=load_manifest()['units'][UNIT];spec=tomllib.loads(ANCHORS.read_text());anchor=validate_spec(spec,selected,unit,target_sha)
        require(all(core.sha(ROOT/path)==sha for path,sha in spec['source_pins'].items()),'list growth source pin differs')
        require(next(r for r in rows if r['address']=='0x00405200')['status']=='matching','list growth parent not accepted')
        tools,_=core.pinned_tools(True)
        require(all(core.sha(tools/name)==sha for name,sha in HEADERS.items()),'list growth standard header pin differs')
        core.build_linked(UNIT,unit);roots=core.compare_linked(UNIT,unit,{'0x004032F0','0x004033C0','0x00403ED0','0x004034F0'})
        require(len(roots)==4 and all(r['result']=='exact' for r in roots),'list growth real BGM owner/roots differ')
        image=ROOT/unit['object'];pe=pefile.PE(str(image));game=pefile.PE(str(core.comparator().TARGET));maps=image.with_suffix('.map').read_text()
        origins={r['address']:r for r in csv.DictReader((ROOT/'config/function-origins.csv').open())}
        proof=qualify(pe,game,core.parse_map(maps),core.parse_map_symbols(maps),image.with_suffix('.ltcg.obj').name,anchor,rows,origins,read)
        output=ROOT/'build/origin-anchors/linked-unsigned-list-growth';output.mkdir(parents=True,exist_ok=True)
        (output/'proof.json').write_text(json.dumps(dict(target_sha256=target_sha,proof=proof,roots=roots),indent=2)+'\n')
        return []
    except (OSError,ValueError,KeyError,TypeError,RuntimeError,struct.error,pefile.PEFormatError) as exc:
        return [str(rule['id'])+': '+str(exc)]
