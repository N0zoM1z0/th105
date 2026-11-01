"""Whole original tree single-position erase in the existing UDP lifetime unit."""
import csv
import json
from pathlib import Path
import struct
import tomllib
import capstone
import pefile
import linked_pe as core
import linked_logic_error_origins as logic
import linked_bad_alloc_origins as bad
import linked_generated_origins as pure
import linked_checked_iterator_origins as iterator
from linked_logic_error_origins import require,named,digest
from workflow_manifest import load_manifest,source_dependencies

ROOT=Path(__file__).resolve().parents[1]
ANCHORS=ROOT/'config/linked-network-tree-erase-origin-anchors.toml'
UNIT='exact-first-network-udp-lifetime'
PURE=ROOT/'config/vc8-linked-pure-network-tree-106a-anchors.toml'
ITERATOR=ROOT/'config/vc8-linked-checked-network-iterator-origin-anchors.toml'
SYMBOL_SHA='e82db1e72dc787d84182b4906d7ea81d40fa3b4b6ac009f925a11d34ba9f4c9d'
SYMBOL_PREFIX='?erase@?$_Tree@V?$_Tmap_traits@IPAUNetworkPeerRecord20@th105@@'
ASSIGN='?assign@?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@QAEAAV12@PBDI@Z'
STRING_DTOR='??1?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@QAE@XZ'
OUT_DTOR='??1out_of_range@std@@UAE@XZ'
OUT_COPY='??0out_of_range@std@@QAE@ABV01@@Z'
OUT_VTABLE='??_7out_of_range@std@@6B@'
LOGIC_VTABLE='??_7logic_error@std@@6B@'
THROW_INFO='__TI3?AVout_of_range@std@@'
LITERAL='??_C@_0BM@PAPJHAGI@invalid?5map?1set?$DMT?$DO?5iterator?$AA@'
TEXT=b'invalid map/set<T> iterator\0'
OFFSETS=[84,102,125,140,453,500,526,549,618,642,655]
FIELDS=[3,22,58,107,120]
HEADERS={
 'include/xtree':'f9c1671c4378a731f32ce8f4c388daad46c4e13fc3980112fdf24f8bd06d3209',
 'include/stdexcept':'6d0f7027cb666813b92aaef26165fb493969c3dd0109ce3df8e04e7bffd4a2cc',
 'include/xstring':'c1a068968165290d000d554340d9c4e7e123c47ea619ad05d1c8f4e719c05922',
}

def inputs(unit):
    files=set(source_dependencies(unit))
    for source in unit['linked_coff_sources']:files.update(source_dependencies(dict(source=source)))
    return files

def validate_spec(spec,selected,unit,target_sha):
    require(set(spec)=={'schema_version','target_sha256','unit','source_pins','anchors'}
        and type(spec['schema_version'])is int and spec['schema_version']==1
        and spec['target_sha256']==target_sha and spec['unit']==UNIT,'tree erase schema/target/unit differs')
    require(len(spec['anchors'])==len(selected)==1,'tree erase needs one whole candidate')
    a=spec['anchors'][0]
    require(set(a)=={'address','size','symbol','sha256','symbol_sha256'}and a['address']=='0x00414110'
        and type(a['size'])is int and a['size']==714 and selected[0]['address']==a['address']and int(selected[0]['size'],0)==714
        and a['symbol'].startswith(SYMBOL_PREFIX)and digest(a['symbol'].encode())==a['symbol_sha256']==SYMBOL_SHA
        and all(isinstance(a[k],str)and len(a[k])==64 and all(c in '0123456789abcdef'for c in a[k])for k in ('sha256','symbol_sha256')),
        'tree erase whole typed selection differs')
    require(unit.get('kind')=='linked_candidate'and unit.get('profile')==core.PROFILE
        and unit.get('link_runtime')=='static'and unit.get('enable_gs')is True
        and unit.get('source')=='src/network/NetworkWinsockConstructorRuntime.cpp'
        and unit.get('linked_coff_sources')==['src/library/UnsignedIntList.cpp','src/library/UnsignedIntVector.cpp']
        and unit.get('preserve_public_members')==['?wait_for_exit@NetworkThreadHandleCtorView@th105@@QAEXXZ']
        and {f['address']for f in unit['functions']}=={'0x00413820','0x004138B0','0x00412B10','0x00412CC0','0x00413780'},
        'tree erase actual existing owner context differs')
    expected={str(p.relative_to(ROOT))for p in inputs(unit)}
    require(isinstance(spec['source_pins'],dict)and set(spec['source_pins'])==expected
        and all(isinstance(v,str)and len(v)==64 and all(c in '0123456789abcdef'for c in v)for v in spec['source_pins'].values()),'tree erase source closure differs')
    return a

def throw_metadata(pe,game,symbols,owner,read):
    sr=lambda a,n:core.pe_data(pe,a,n)
    words=lambda rd,a,n:list(struct.unpack('<'+'I'*n,rd(a,4*n)))
    source=named(symbols,THROW_INFO,owner);target=0x6e3ba4
    dtor=named(symbols,OUT_DTOR,'i '+owner);si=words(sr,source,4);ti=words(read,target,4)
    require(si[:3]==[0,dtor,0]and ti[:3]==[0,0x401740,0],'tree out_of_range ThrowInfo differs')
    sa=words(sr,si[3],4);ta=words(read,ti[3],4)
    require(sa[0]==ta[0]==3,'tree out_of_range needs three catchable types')
    typeinfo=named(symbols,'??_7type_info@@6B@','libcmt:typinfo.obj');records=[]
    types=[('.?AVout_of_range@std@@',40,OUT_COPY,0x401780,'i '+owner),
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
    def loc(n,o=None):return named(symbols,n,o or 'i '+owner)
    calls={}
    for n,(target,expected,evidence)in logic.CALLEES.items():
        source_owner='i '+owner if n==logic.ASSIGN else expected
        require(origins[f'0x{target:08X}']['evidence_id']==evidence,'tree logic support callee ownership changed')
        calls[loc(n,source_owner)]=(n,target)
    cookie=loc('___security_cookie','libcmt:gs_cookie.obj')
    require(core.pe_data(pe,cookie,4)==read(0x6f7a88,4),'tree initial security cookie differs')
    tables=[]
    for n,target,name in [(LOGIC_VTABLE,0x6c05d0,'.?AVlogic_error@std@@'),(OUT_VTABLE,0x6c05dc,'.?AVout_of_range@std@@')]:
        va=loc(n,owner.replace('.ltcg.obj','.coff0.obj'))
        require(core.primary_type_name(pe,va)==core.primary_type_name(game,target)==name,'tree actual exception RTTI differs')
        tables.append(dict(source_address=va,target_address=target,symbol=n,target_key=name))
    logic_spec=tomllib.loads(logic.ANCHORS.read_text())
    logic_support=[logic.qualify(pe,functions,symbols,a,rows,read,(calls,tables[0]['source_address'],cookie),owner=owner)for a in logic_spec['anchors']]
    throw=bad.throw_witness(pe,game,functions,symbols,read)
    for n,target,expected in [(ASSIGN,0x4021c0,'i '+owner),(bad.THROW,0x68a153,'libcmt:throw.obj'),
        ('??3@YAXPAX@Z',0x6898ea,'libcmt:delete.obj'),(logic.STRING,0x401670,'i '+owner),
        (logic.COPY,0x4017a0,'i '+owner),(STRING_DTOR,0x401e00,'i '+owner)]:
        require(origins[f'0x{target:08X}']['disposition']=='exclude','tree named library callee is not independently owned')
        calls[loc(n,expected)]=(n,target)
    children=[]
    for a in tomllib.loads(PURE.read_text())['anchors']:
        children.append(pure.qualify(pe,functions,owner,a,rows,read));calls[loc(a['symbol'])]=(a['symbol'],int(a['address'],0))
    ia=tomllib.loads(ITERATOR.read_text())['anchors'][0]
    children.append(iterator.qualify(pe,functions,owner,ia,rows,read));calls[loc(ia['symbol'])]=(ia['symbol'],int(ia['address'],0))
    def resolve(at):
        require(at in calls,'tree erase has an unproved named callee');return calls[at]
    def canon(raw,at,target,**kwargs):
        return core.canonicalize(raw,at,target,[],resolve,(core.IMAGE_BASE,core.IMAGE_BASE+pe.OPTIONAL_HEADER.SizeOfImage),(0x400000,0x706000),**kwargs)
    support=[]
    for n,target,size,tail in [(OUT_DTOR,0x401740,50,True),(OUT_COPY,0x401780,25,False),(STRING_DTOR,0x401e00,38,False)]:
        at=loc(n);raw=core.linked_body(pe,functions,at);require(len(raw)==size,'tree exception/string support extent differs')
        b,cs,refs=canon(raw,at,target,vtables=tables,tail=tail)
        require(b==read(target,size),'tree whole exception/string support differs');core.validate_body_relocations(pe,at,size,refs)
        support.append(dict(symbol=n,address=hex(target),size=size,sha256=digest(b)))
    info,metadata=throw_metadata(pe,game,symbols,owner,read)
    symbol=anchor['symbol'];start=loc(symbol);raw=core.linked_body(pe,functions,start)
    require(functions.get(start)==[(symbol,'i '+owner)]and len(raw)==714,'tree erase actual whole CIL ownership differs')
    require(all(core.IMAGE_BASE+e.address!=start for e in pe.DIRECTORY_ENTRY_EXPORT.symbols),'tree erase may not be a forced export')
    handler=loc('__ehhandler$'+symbol,'CIL library: CIL module');hb=core.linked_body(pe,functions,handler)
    require(len(hb)==27,'tree complete handler extent differs');si=struct.unpack_from('<I',hb,18)[0]
    fi=core.pe_data(pe,si,36);su=struct.unpack_from('<I',fi,8)[0];uw=core.pe_data(pe,su,8);action=struct.unpack_from('<I',uw,4)[0]
    eh=logic.canonical_metadata(fi,read(0x6e129c,36),uw,read(0x6e1294,8))
    require(struct.unpack_from('<I',read(0x6e129c,36),8)[0]==0x6e1294 and struct.unpack_from('<I',read(0x6e1294,8),4)[0]==0x6bb670,'tree native EH pointers differ')
    core.validate_body_relocations(pe,si,36,[dict(field_offset=8)]);core.validate_body_relocations(pe,su,8,[dict(field_offset=4)])
    require(functions.get(action)==[('__unwindfunclet$'+symbol+'$0','CIL library: CIL module')],'tree unwind owner differs')
    ab=core.linked_body(pe,functions,action);require(len(ab)==8,'tree whole unwind extent differs')
    ac,_,ar=canon(ab,action,0x6bb670,tail=True);require(ac==read(0x6bb670,8),'tree complete unwind action differs');core.validate_body_relocations(pe,action,8,ar)
    hc,_,hr=canon(hb,handler,0x6bb678,tail=True,internal_refs=[dict(kind='eh_info',source_address=si,address=0x6e129c,size=36,symbol='actual-FuncInfo')])
    require(hc==read(0x6bb678,27),'tree whole EH handler differs');core.validate_body_relocations(pe,handler,27,hr)
    literal=loc(LITERAL,owner)
    require(core.readonly_data(pe,literal,len(TEXT))==core.readonly_data(game,0x6d69b4,len(TEXT))==TEXT,'tree complete original readonly message differs')
    ins=core.decode_closed_body(raw,start);by={i.address-start:i for i in ins}
    require(by[106].mnemonic=='push'and by[106].operands[0].type==capstone.x86.X86_OP_IMM and by[106].operands[0].imm==info,'tree actual ThrowInfo argument differs')
    refs=[dict(kind='eh_handler',source_address=handler,address=0x6bb678,size=27,symbol='actual-handler'),
          dict(kind='runtime',source_address=cookie,address=0x6f7a88,size=4,symbol='___security_cookie'),
          dict(kind='literal',source_address=literal,address=0x6d69b4,size=len(TEXT),literal_size=len(TEXT),read_offset=0,allow_pointer_push=True,symbol=LITERAL),
          dict(kind='object',source_address=info,address=0x6e3ba4,size=16,symbol=THROW_INFO)]
    def rebound(to):return canon(raw,start,to,vtables=tables,internal_refs=refs)
    canonical,cs,rs=rebound(0x414110)
    require(canonical==read(0x414110,714)and digest(canonical)==anchor['sha256']and [r['offset']for r in cs]==OFFSETS
        and [r['field_offset']for r in rs]==FIELDS,'tree whole canonical bytes or relocation roles differ')
    core.validate_body_relocations(pe,start,714,rs)
    core.decode_closed_body(canonical,0x414110)
    allowed={i for off in OFFSETS+FIELDS for i in range(off,off+4)}
    require(all(x==y for i,(x,y)in enumerate(zip(raw,canonical))if i not in allowed),'tree changed nonrelocation bytes')
    hits=[r['address']for r in rows if int(r['size'],0)==714 and rebound(int(r['address'],0))[0]==read(int(r['address'],0),714)]
    require(hits==['0x00414110'],'tree whole body is not inventory-unique')
    return dict(address='0x00414110',size=714,symbol=symbol,sha256=digest(canonical),source_va=hex(start),instructions=len(ins),
        calls=cs,references=rs,inventory_hits=hits,children=children,logic_support=logic_support,support=support,
        throw=throw,throw_metadata=metadata,eh=dict(handler_sha256=digest(hc),action_sha256=digest(ac),**eh),masked_bytes=0,unequal_bytes=0)

def validate(rule,selected,rows,read,target_sha):
    try:
        require(ROOT/str(rule['linked_network_tree_erase_anchor_file'])==ANCHORS,'unreviewed tree erase anchor path')
        spec=tomllib.loads(ANCHORS.read_text());unit=load_manifest()['units'][UNIT];anchor=validate_spec(spec,selected,unit,target_sha)
        tools,pins=core.pinned_tools(True)
        for name,sha in spec['source_pins'].items():require(digest((ROOT/name).read_bytes().replace(b'\r\n',b'\n'))==sha,'tree original source changed')
        for name,sha in HEADERS.items():require(core.sha(tools/name)==sha,'tree original standard header changed')
        core.build_linked(UNIT,unit);roots=core.compare_linked(UNIT,unit,{'0x00413820','0x00413780'})
        require(len(roots)==2 and all(r['result']=='exact'and r['target_sha256']==r['object_compared_sha256']for r in roots),'tree real owner proof failed')
        image=ROOT/unit['object'];pe=pefile.PE(str(image));game=pefile.PE(str(core.comparator().TARGET));maps=image.with_suffix('.map').read_text()
        origins={r['address']:r for r in csv.DictReader((ROOT/'config/function-origins.csv').open())}
        proof=qualify(pe,game,core.parse_map(maps),core.parse_map_symbols(maps),image.with_suffix('.ltcg.obj').name,anchor,rows,origins,read)
        proof.update(unit=UNIT,roots=roots,source_pins=spec['source_pins'],headers=HEADERS,tool_pins=pins,
            validator_sha256=core.sha(Path(__file__)),dependency_hashes={str(p.relative_to(ROOT)):core.sha(p)for p in [Path(logic.__file__),Path(bad.__file__),Path(pure.__file__),Path(iterator.__file__),PURE,ITERATOR,logic.ANCHORS]},anchor_sha256=core.sha(ANCHORS),image_sha256=core.sha(image),map_sha256=core.sha(image.with_suffix('.map')),
            build_receipt_sha256=core.sha(image.with_suffix('.link.json')),scope='single-position tree erase only; no range/owner/authored credit')
        output=ROOT/'build/origin-anchors/linked-network-tree-erase.json';output.write_text(json.dumps(proof,indent=2)+'\n');return []
    except (OSError,ValueError,KeyError,TypeError,RuntimeError,struct.error,pefile.PEFormatError)as exc:return [str(rule['id'])+': '+str(exc)]

def main():
    c=core.comparator();sha=c.verify_target();rows=list(csv.DictReader((ROOT/'config/functions.csv').open()))
    errors=validate(dict(id='vc8-linked-network-tree-erase-106a',linked_network_tree_erase_anchor_file=str(ANCHORS.relative_to(ROOT))),[r for r in rows if r['address']=='0x00414110'],rows,c.target_bytes,sha)
    print(json.dumps(dict(errors=errors)));return bool(errors)

if __name__=='__main__':raise SystemExit(main())
