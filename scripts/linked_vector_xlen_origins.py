"""Whole original vector<unsigned> length-error entry in real BGM CIL.

The body ends at a proven nonreturning CRT throw call. Its straight-line CFG,
all named call/data roles, full EH and exception support remain byte-checked.
"""
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
import linked_unsigned_list_growth_origins as length
from linked_logic_error_origins import require, named, digest
from workflow_manifest import load_manifest, source_dependencies

ROOT=Path(__file__).resolve().parents[1]
ANCHORS=ROOT/'config/linked-vector-xlen-origin-anchors.toml'
UNIT='exact-first-bgm-stream-lifetime'
SYMBOL='?_Xlen@?$vector@IV?$allocator@I@std@@@std@@KAXXZ'
INSERT_N='?_Insert_n@?$vector@IV?$allocator@I@std@@@std@@IAEXV?$_Vector_iterator@IV?$allocator@I@std@@@2@IABI@Z'
INSERT='?insert@?$vector@IV?$allocator@I@std@@@std@@QAE?AV?$_Vector_iterator@IV?$allocator@I@std@@@2@V32@ABI@Z'
PUSH='?push_back@?$vector@IV?$allocator@I@std@@@std@@QAEXABI@Z'
LITERAL='??_C@_0BD@OLBABOEK@vector?$DMT?$DO?5too?5long?$AA@'
SHA='567ff29dd208ccf9f58498146dd85054ec22273ddcfd1800aaaf4256b0ef4575'
HEADERS={'include/vector':'883848802b49aa4160509b744f37d18a459d31c2c880ae3de3f113fed850c8e5','include/xmemory':'83a2121ebc455b25493a689a4fb299db0ca848ffc29668159bc9fb5faa95e50b','include/stdexcept':'6d0f7027cb666813b92aaef26165fb493969c3dd0109ce3df8e04e7bffd4a2cc','include/xstring':'c1a068968165290d000d554340d9c4e7e123c47ea619ad05d1c8f4e719c05922'}

def inputs(unit):
    paths=set(source_dependencies(unit))
    for s in unit.get('linked_coff_sources',[]):paths.update(source_dependencies(dict(source=s)))
    return paths

def validate_spec(spec,selected,unit,target_sha):
    require(set(spec)=={'schema_version','target_sha256','unit','source_pins','anchors'} and type(spec['schema_version']) is int and spec['schema_version']==1 and spec['target_sha256']==target_sha and spec['unit']==UNIT,'vector xlen schema/target/unit differs')
    require(spec['anchors']==[dict(address='0x0040AAF0',size=123,symbol=SYMBOL,sha256=SHA)] and len(selected)==1 and selected[0]['address']=='0x0040AAF0' and int(selected[0]['size'],0)==123,'vector xlen target differs')
    require(unit.get('kind')=='linked_candidate' and unit.get('profile')==core.PROFILE and unit.get('source')=='src/audio/BgmStreamAllocation.cpp' and unit.get('enable_gs') is True and unit.get('link_runtime')=='static' and unit.get('link_xiph_sdk') is True and unit.get('linked_coff_sources')==['src/library/UnsignedIntList.cpp','src/library/UnsignedIntVector.cpp'] and {f['address'] for f in unit['functions']}=={'0x004036C0','0x00404330','0x00404270','0x00402880','0x004180F0','0x00418A00','0x00403F60','0x00404090'},'vector xlen actual CIL context differs')
    pins=spec['source_pins'];paths={str(p.relative_to(ROOT)) for p in inputs(unit)}
    require(isinstance(pins,dict) and set(pins)==paths and all(isinstance(v,str) and len(v)==64 and all(c in '0123456789abcdef' for c in v) for v in pins.values()),'vector xlen source closure differs')
    return spec['anchors'][0]

def qualify(pe,game,functions,symbols,owner,rows,origins,read):
    sr=lambda a,n:core.pe_data(pe,a,n)
    def loc(n,o=None):return named(symbols,n,o or 'i '+owner)
    callmap={}
    for n,(target,expected,evidence) in logic.CALLEES.items():
        source_owner='i '+owner if n==logic.ASSIGN else expected
        row=origins[f'0x{target:08X}'];require(row['evidence_id']==evidence and row['disposition']=='exclude','vector xlen logic dependency differs')
        callmap[loc(n,source_owner)]=(n,target)
    for n,target,expected in [(length.STRING_ASSIGN,0x4021c0,'i '+owner),(length.STRING_DTOR,0x401e00,'i '+owner),('??3@YAXPAX@Z',0x6898ea,'libcmt:delete.obj'),(bad.THROW,0x68a153,'libcmt:throw.obj')]:
        require(origins[f'0x{target:08X}']['disposition']=='exclude','vector xlen support origin differs');callmap[loc(n,expected)]=(n,target)
    def resolve(a):require(a in callmap,'vector xlen unproved callee');return callmap[a]
    def canon(raw,at,to,**kw):return core.canonicalize(raw,at,to,[],resolve,(core.IMAGE_BASE,core.IMAGE_BASE+pe.OPTIONAL_HEADER.SizeOfImage),(0x400000,0x706000),**kw)
    logic_v=loc('??_7logic_error@std@@6B@',owner.replace('.ltcg.obj','.coff0.obj'));length_v=loc(length.LENGTH_VTABLE,owner.replace('.ltcg.obj','.coff0.obj'));cookie=loc('___security_cookie','libcmt:gs_cookie.obj')
    require(logic.rtti(sr,logic_v)==logic.rtti(read,0x6c05d0)==(0,0,0,b'.?AVlogic_error@std@@') and logic.rtti(sr,length_v)==logic.rtti(read,0x6c0888)==(0,0,0,b'.?AVlength_error@std@@') and sr(cookie,4)==read(0x6f7a88,4),'vector xlen RTTI/cookie differs')
    context=(callmap,logic_v,cookie)
    logic_proofs=[logic.qualify(pe,functions,symbols,a,rows,read,context,owner=owner) for a in tomllib.loads(logic.ANCHORS.read_text())['anchors']]
    for address in ('0x00401670','0x004017A0'):
        require(origins.get(address,{}).get('evidence_id')=='linked-original-logic-error-106a' and origins[address]['disposition']=='exclude','vector xlen logic constructor origin differs')
    callmap[loc(logic.STRING)]=(logic.STRING,0x401670);callmap[loc(logic.COPY)]=(logic.COPY,0x4017a0)
    throw=bad.throw_witness(pe,game,functions,symbols,read);throw_info,throw_proof=length.throw_metadata(pe,game,symbols,owner,read)
    lt=dict(source_address=logic_v,target_address=0x6c05d0,symbol='logic_error',target_key='logic_error');et=dict(source_address=length_v,target_address=0x6c0888,symbol=length.LENGTH_VTABLE,target_key='length_error')
    support=[]
    for n,target,size,tail,tables in [(length.LENGTH_DTOR,0x401740,50,True,[lt]),(length.LENGTH_COPY,0x402570,25,False,[et]),(length.STRING_DTOR,0x401e00,38,False,[])]:
        a=loc(n);raw=core.linked_body(pe,functions,a);require(len(raw)==size,'vector xlen support extent differs');z,_,refs=canon(raw,a,target,vtables=tables,tail=tail);require(z==read(target,size),'vector xlen support body differs');core.validate_body_relocations(pe,a,size,refs);support.append(dict(symbol=n,address=hex(target),size=size,sha256=digest(z)))
    start=loc(SYMBOL);raw=core.linked_body(pe,functions,start)
    require(functions.get(start)==[(SYMBOL,'i '+owner)] and len(raw)==123,'vector xlen source owner/extent differs')
    exports=getattr(getattr(pe,'DIRECTORY_ENTRY_EXPORT',None),'symbols',[]);require(all(core.IMAGE_BASE+e.address!=start for e in exports),'vector xlen helper must not be forced export')
    handler=loc('__ehhandler$'+SYMBOL,'CIL library: CIL module');hb=core.linked_body(pe,functions,handler);require(len(hb)==27,'vector xlen handler extent differs')
    info=struct.unpack_from('<I',hb,18)[0];fi=sr(info,36);unwind=struct.unpack_from('<I',fi,8)[0];uw=sr(unwind,8);action=struct.unpack_from('<I',uw,4)[0]
    require(struct.unpack_from('<I',read(0x6e4644,36),8)[0]==0x6e463c and struct.unpack_from('<I',read(0x6e463c,8),4)[0]==0x6bdfa0,'vector xlen native EH pointer differs')
    metadata=logic.canonical_metadata(fi,read(0x6e4644,36),uw,read(0x6e463c,8));core.validate_body_relocations(pe,info,36,[dict(field_offset=8)]);core.validate_body_relocations(pe,unwind,8,[dict(field_offset=4)])
    require(functions.get(action)==[('__unwindfunclet$'+SYMBOL+'$0','CIL library: CIL module')],'vector xlen unwind owner differs')
    ab=core.linked_body(pe,functions,action);require(len(ab)==8,'vector xlen action extent differs');ac,_,ar=canon(ab,action,0x6bdfa0,tail=True);require(ac==read(0x6bdfa0,8),'vector xlen action body differs');core.validate_body_relocations(pe,action,8,ar)
    hc,_,hr=canon(hb,handler,0x6bdfa8,tail=True,internal_refs=[dict(kind='eh_info',source_address=info,address=0x6e4644,size=36,symbol='FuncInfo')]);require(hc==read(0x6bdfa8,27),'vector xlen handler differs');core.validate_body_relocations(pe,handler,27,hr)
    literal=loc(LITERAL,owner);text=b'vector<T> too long\0';require(core.readonly_data(pe,literal,len(text))==core.readonly_data(game,0x6d6938,len(text))==read(0x6d6938,len(text))==text,'vector xlen literal differs')
    d=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);d.detail=True;instructions=list(d.disasm(raw,start))
    require(sum(i.size for i in instructions)==123 and instructions[-1].address==start+118 and instructions[-1].size==5 and instructions[-1].bytes[0]==0xe8 and instructions[-1].operands[0].type==capstone.x86.X86_OP_IMM and instructions[-1].operands[0].imm==loc(bad.THROW,'libcmt:throw.obj') and all(not core.is_branch(i) and not i.group(capstone.CS_GRP_RET) and not i.group(capstone.CS_GRP_INT) for i in instructions),'vector xlen straight-line noreturn CFG differs')
    offsets=[74,96,119];call_ins=[i for i in instructions if i.group(capstone.CS_GRP_CALL)]
    require([i.address-start+1 for i in call_ins]==offsets and all(i.size==5 and i.bytes[0]==0xe8 and i.operands[0].type==capstone.x86.X86_OP_IMM for i in call_ins),'vector xlen call inventory differs')
    data={9:0x6bdfa8,24:0x6f7a88,44:0x6d6938,101:0x6e3be0,114:0x6c0888};source_data={9:handler,24:cookie,44:literal,101:throw_info,114:length_v}
    for off,value in source_data.items():require(struct.unpack_from('<I',raw,off)[0]==value,'vector xlen data role differs')
    calls=[]
    for off in offsets:
        src=start+off+4+struct.unpack_from('<i',raw,off)[0];name,to=resolve(src);calls.append(dict(offset=off,symbol=name,target=to))
    require([x['symbol'] for x in calls]==[length.STRING_ASSIGN,logic.STRING,bad.THROW],'vector xlen call semantic roles differ')
    def rebound(to):
        z=bytearray(raw)
        for entry in calls:struct.pack_into('<i',z,entry['offset'],entry['target']-(to+entry['offset']+4))
        for off,value in data.items():struct.pack_into('<I',z,off,value)
        return bytes(z)
    body=rebound(0x40aaf0);require(body==read(0x40aaf0,123) and digest(body)==SHA,'vector xlen full canonical body differs')
    core.validate_body_relocations(pe,start,123,[dict(field_offset=o) for o in data]);fields={i for off in list(data)+offsets for i in range(off,off+4)}
    require(all(a==b for i,(a,b) in enumerate(zip(raw,body)) if i not in fields),'vector xlen changed non-relocation byte')
    hits=[r['address'] for r in rows if int(r['size'],0)==123 and rebound(int(r['address'],0))==read(int(r['address'],0),123)];require(hits==['0x0040AAF0'],'vector xlen full inventory identity differs')
    def direct(code,at,to):return [i.address for i in core.decode_closed_body(code,at) if i.group(capstone.CS_GRP_CALL) and i.operands[0].type==capstone.x86.X86_OP_IMM and i.operands[0].imm==to]
    insert_n=loc(INSERT_N);insert=loc(INSERT);push=loc(PUSH)
    for a,n in [(insert_n,INSERT_N),(insert,INSERT),(push,PUSH)]:require(functions.get(a)==[(n,'i '+owner)],'vector xlen source parent alias differs')
    require(direct(core.linked_body(pe,functions,insert_n),insert_n,start)==[insert_n+0x4a] and direct(core.linked_body(pe,functions,insert),insert,insert_n)==[insert+0x56] and direct(core.linked_body(pe,functions,push),push,insert)==[push+0x61],'vector xlen source call graph differs')
    require(digest(read(0x40e060,475))=='991619dccf37d049faa442431a0098d2705788dfcfc19bbb9b733c3d3ae27742' and digest(read(0x40dee0,143))=='87fb25b43616db229aa94c107902eed7799753c7fe7e32d944ec91232c995f8a','vector xlen native parent differs')
    require(direct(read(0x40e060,475),0x40e060,0x40aaf0)==[0x40e0aa] and direct(read(0x40dee0,143),0x40dee0,0x40e060)==[0x40df36],'vector xlen native call graph differs')
    require(next(r for r in rows if r['address']=='0x0042E3F0')['status']=='matching' and digest(read(0x42e3f0,860))=='7244a3ee62bd835b17f9abdae49ae34aff70f21c350a99d40b0c4868874db9f2','vector xlen exact score caller differs')
    edge=read(0x42e5c5,5);require(edge[0]==0xe8 and 0x42e5ca+struct.unpack_from('<i',edge,1)[0]==0x40dee0,'vector xlen exact score call differs')
    return dict(address='0x0040AAF0',size=123,sha256=SHA,source_va=hex(start),calls=calls,inventory_hits=hits,source_parent_exact=False,native_parent_exact=False,native_score_caller='0x0042E3F0',eh=dict(handler_sha256=digest(hc),action_sha256=digest(ac),**metadata),logic_support=logic_proofs,support=support,throw=throw,throw_metadata=throw_proof,masked_bytes=0,unequal_bytes=0)

def validate(rule,selected,rows,read,target_sha):
    try:
        require(ROOT/str(rule['linked_vector_xlen_anchor_file'])==ANCHORS,'vector xlen anchor path differs')
        unit=load_manifest()['units'][UNIT];spec=tomllib.loads(ANCHORS.read_text());validate_spec(spec,selected,unit,target_sha)
        require(all(core.sha(ROOT/path)==sha for path,sha in spec['source_pins'].items()),'vector xlen source pin differs')
        tools,_=core.pinned_tools(True);require(all(core.sha(tools/n)==h for n,h in HEADERS.items()),'vector xlen standard header pin differs')
        core.build_linked(UNIT,unit);roots=core.compare_linked(UNIT,unit,{'0x00402880','0x004180F0','0x00418A00','0x00403F60'})
        require(len(roots)==4 and all(x['result']=='exact' for x in roots),'vector xlen existing BGM roots differ')
        image=ROOT/unit['object'];pe=pefile.PE(str(image));game=pefile.PE(str(core.comparator().TARGET));maps=image.with_suffix('.map').read_text();origins={r['address']:r for r in csv.DictReader((ROOT/'config/function-origins.csv').open())}
        proof=qualify(pe,game,core.parse_map(maps),core.parse_map_symbols(maps),image.with_suffix('.ltcg.obj').name,rows,origins,read)
        out=ROOT/'build/origin-anchors/linked-vector-xlen';out.mkdir(parents=True,exist_ok=True)
        (out/'proof.json').write_text(json.dumps(dict(target_sha256=target_sha,proof=proof,roots=roots),indent=2)+'\n');return []
    except (OSError,ValueError,KeyError,TypeError,RuntimeError,struct.error,pefile.PEFormatError) as exc:return [str(rule['id'])+': '+str(exc)]
