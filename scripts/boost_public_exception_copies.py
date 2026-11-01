"""Original public Boost exception instantiations: full clone copies and RTTI/EH."""
import csv
import json
from pathlib import Path
import struct
import tomllib
import capstone
import pefile
import build
import linked_pe as core
import rank_retained_exact as rank
import upstream_boost as upstream
from coff_exception_rtti import Reader,RttiGraph
from linked_logic_error_origins import require,digest
from workflow_manifest import load_manifest

ROOT=Path(__file__).resolve().parents[1]
ANCHORS=ROOT/'config/boost-public-exception-copy-origin-anchors.toml'
UNIT='boost-public-exception-copies'
LOGIC_COPY='??0logic_error@std@@QAE@ABV01@@Z'
LOGIC_DTOR='??1logic_error@std@@UAE@XZ'
INVALID_DTOR='??1invalid_argument@std@@UAE@XZ'
ASSIGN='?assign@?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@QAEAAV12@ABV12@II@Z'
CLONE_BASE='??_7clone_base@exception_detail@boost@@6B@'
BOOST_BASE='??_7exception@boost@@6B@'
LOGIC_VT='??_7logic_error@std@@6B@'
INVALID_VT='??_7invalid_argument@std@@6B@'
CONTRACT={
 'logic_error':dict(copy=0x6b5060,inject=0x6b4e60,size=147,handler=0x6bd3f8,action=0x6bd3f0,info=0x6e37d4,unwind=0x6e37cc,
     inject_vtables=[0x6d687c,0x6d6874],clone_vtables=[0x6d68a0,0x6d6898,0x6d6888],dtor=0x401740),
 'invalid_argument':dict(copy=0x6a95d0,inject=0x6a7310,size=153,handler=0x6bc9d8,action=0x6bc9d0,info=0x6e2c70,unwind=0x6e2c68,
     inject_vtables=[0x6d5e5c,0x6d5e54],clone_vtables=[0x6d5e80,0x6d5e78,0x6d5e68],dtor=0x665ac7),
}

def names(klass):
    inject='?$error_info_injector@V'+klass+'@std@@@exception_detail@boost@@'
    clone='?$clone_impl@U'+inject+'@exception_detail@boost@@'
    return dict(inject='??0'+inject+'QAE@ABU012@@Z',copy='??0'+clone+'QAE@ABV012@@Z',
        inject_type='.?AU'+inject,clone_type='.?AV'+clone,
        inject_vtables=['??_7'+inject+'6B'+klass+'@std@@@','??_7'+inject+'6Bexception@2@@'],
        clone_vtables=['??_7'+clone+'6B'+klass+'@std@@@','??_7'+clone+'6Bexception@2@@','??_7'+clone+'6B@'],
        public='??$throw_exception@V'+klass+'@std@@@boost@@YAXABV'+klass+'@std@@@Z')

def validate_spec(spec,selected,unit,target_sha):
    require(set(spec)=={'schema_version','target_sha256','unit','anchors'}and type(spec['schema_version'])is int
        and spec['schema_version']==1 and spec['target_sha256']==target_sha and spec['unit']==UNIT,'public exception schema/target/unit differs')
    aa=spec['anchors'];by={r['address']:r for r in selected}
    require(len(aa)==len(selected)==2 and {a['klass']for a in aa}==set(CONTRACT),'public exception needs two typed whole roots')
    for a in aa:
        k=CONTRACT[a['klass']];n=names(a['klass']);address=f'0x{k["copy"]:08X}'
        require(set(a)=={'address','size','klass','symbol','sha256'}and a['address']==address and type(a['size'])is int and a['size']==46
            and a['symbol']==n['copy']and address in by and int(by[address]['size'],0)==46
            and isinstance(a['sha256'],str)and len(a['sha256'])==64 and all(c in '0123456789abcdef'for c in a['sha256']),
            'public exception typed root/extent differs')
    require(unit.get('kind')=='probe'and unit.get('source')==upstream.EXCEPTION_PROBE and unit.get('profile')=='vc8-sp1-probe-o2'
        and unit.get('enable_gs')is True and unit.get('boost_regex_headers')is True
        and unit.get('include_dirs')==[upstream.FOLDER]and len(unit['functions'])==2
        and {f['address']for f in unit['functions']}==set(by),'public exception original source/profile differs')
    for f in unit['functions']:
        klass=next(klass for klass,k in CONTRACT.items()if f['address']==f'0x{k["copy"]:08X}')
        k=CONTRACT[klass];n=names(klass)
        require(set(f)=={'address','symbol_base','rel32_targets','dir32_targets'}and f['symbol_base']==n['copy']
            and f['rel32_targets']==[n['inject']+'='+f'0x{k["inject"]:08X}']
            and f['dir32_targets']==[v+'='+v for v in [CLONE_BASE]+n['clone_vtables']],
            'public exception formal comparison contract differs')
    return aa

def rtti(reader,game,read):
    types={'.?AVclone_base@exception_detail@boost@@','.?AVexception@boost@@','.?AVlogic_error@std@@','.?AVinvalid_argument@std@@','.?AVexception@std@@'}
    for klass in CONTRACT:types.update([names(klass)['inject_type'],names(klass)['clone_type']])
    graph=RttiGraph(reader,game,read,types)
    for n,to,kind in [(CLONE_BASE,0x6d5dd0,'.?AVclone_base@exception_detail@boost@@'),(BOOST_BASE,0x6d5e40,'.?AVexception@boost@@'),
        (LOGIC_VT,0x6c05d0,'.?AVlogic_error@std@@'),(INVALID_VT,0x6c7548,'.?AVinvalid_argument@std@@')]:graph.table(n,to,0,kind)
    for klass,k in CONTRACT.items():
        n=names(klass)
        for symbol,to,offset in zip(n['inject_vtables'],k['inject_vtables'],[0,40]):graph.table(symbol,to,offset,n['inject_type'])
        for symbol,to,offset in zip(n['clone_vtables'],k['clone_vtables'],[0,40,60]):graph.table(symbol,to,offset,n['clone_type'])
    return graph

def replay_region(reader,name,size,target,targets,read,offset=0):
    raw=bytearray(reader.raw(name,size,offset));refs=reader.refs(name,size,offset);out=[]
    for off,kind,symbol in refs:
        require(symbol in targets and kind in (6,20),'public exception unresolved whole region relocation')
        add=struct.unpack_from('<i',raw,off)[0];require(add==0,'public exception unexpected relocation addend')
        to=targets[symbol]
        if kind==6:struct.pack_into('<I',raw,off,to)
        else:struct.pack_into('<i',raw,off,to-target-off-4)
        out.append(dict(offset=off,kind=kind,symbol=symbol,target=hex(to)))
    require(raw==read(target,size),'public exception complete region bytes differ')
    return dict(address=hex(target),size=size,sha256=digest(raw),relocations=out)

def complete_eh(reader,symbol,k,dtor,read):
    hn='__ehhandler$'+symbol;fn='__ehfuncinfo$'+symbol;un='__unwindtable$'+symbol;an='__unwindfunclet$'+symbol+'$0'
    hs=reader.symbol(hn);fs=reader.symbol(fn);us=reader.symbol(un);a=reader.symbol(an)
    code=reader.section(hn);data=reader.section(fn)
    require(code.name=='.text$x'and code.raw_size==35 and hs.value==8 and a.value==0 and a.section_number==hs.section_number,
        'public exception complete cleanup/handler ownership differs')
    require(data.name=='.xdata$x'and data.raw_size==44 and fs.value==8 and us.value==0 and fs.section_number==us.section_number,
        'public exception full FuncInfo/unwind ownership differs')
    require(reader.refs(an,35)==[(4,20,dtor),(21,20,'@__security_check_cookie@4'),(26,6,fn),(31,20,'___CxxFrameHandler3')]
        and reader.refs(un,44)==[(4,6,an),(16,6,un)],'public exception complete EH relocation roles differ')
    sw=list(struct.unpack('<9I',reader.raw(fn,36)));uw=list(struct.unpack('<2I',reader.raw(un,8)))
    require(sw==[0x19930522,1,0,0,0,0,0,0,1]and uw==[0xffffffff,0],'public exception exact EH scalar fields differ')
    targets={dtor:k['dtor'],'@__security_check_cookie@4':0x689d25,'___CxxFrameHandler3':0x6899e7,fn:k['info'],un:k['unwind'],an:k['action']}
    records=[replay_region(reader,an,35,k['action'],targets,read),replay_region(reader,un,44,k['unwind'],targets,read)]
    require(k['handler']==k['action']+8 and k['info']==k['unwind']+8,'public exception target owned spans differ')
    core.decode_closed_body(read(k['action'],8),k['action'],tail=True);core.decode_closed_body(read(k['handler'],27),k['handler'],tail=True)
    return records

def qualify(unit,anchors,rows,read,c,game,origins):
    obj=ROOT/unit['object'];reader=Reader(obj);graph=rtti(reader,game,read);data=c.known_data_targets();calls={
        LOGIC_COPY:0x4017a0,LOGIC_DTOR:0x401740,INVALID_DTOR:0x665ac7,
        '??0exception@std@@QAE@ABV01@@Z':0x689f82,'??1exception@std@@UAE@XZ':0x689fda,
        '??3@YAXPAX@Z':0x6898ea,'@__security_check_cookie@4':0x689d25,'___CxxFrameHandler3':0x6899e7,ASSIGN:0x4020d0}
    for address in [0x4017a0,0x401740,0x665ac7,0x689f82,0x689fda,0x6898ea,0x689d25,0x6899e7,0x4020d0]:
        require(origins[f'0x{address:08X}']['disposition']=='exclude','public exception needs independent named provider ownership')
    require(origins['0x004017A0']['confidence']=='observed','logic_error named base copy needs its independent observed proof')
    require(origins['0x00665AC7']['evidence_id']=='boost-invalid-argument-eh-cleanup-tail-106a','invalid_argument native cleanup identity changed')
    for name,to in graph.bindings.items():data[name]=(to,read(to,4),frozenset({0}),'address')
    data['___security_cookie']=(0x6f7a88,read(0x6f7a88,4),frozenset({0}),'address')
    def whole(symbol,target,size,expected,tail=False):
        actual,raw,_,rels=rank.read_coff_function(obj,symbol,None)
        require(actual==symbol and len(raw)==size and rels==expected,'public exception complete function or relocation inventory differs')
        b=c.coff_symbol_bytes(obj,symbol,target,0xffffffff,calls,data)
        require(b==read(target,size),'public exception whole function bytes differ: '+symbol)
        core.decode_closed_body(b,target,tail=tail)
        allowed={i for off,kind,n in rels for i in range(off,off+4)}
        require(all(x==y for i,(x,y)in enumerate(zip(raw,b))if i not in allowed),'public exception changed nonrelocation bytes')
        return dict(symbol=symbol,address=hex(target),size=size,sha256=digest(b),relocations=rels,masked_bytes=0,unequal_bytes=0)
    dtorefs=[(5,6,LOGIC_VT),(20,20,'??3@YAXPAX@Z'),(46,20,'??1exception@std@@UAE@XZ')]
    support=[whole(LOGIC_DTOR,0x401740,50,dtorefs,True)]
    invalid_base=whole(INVALID_DTOR,0x401740,50,dtorefs,True)
    invalid_base['scope']='Byte equivalence to the base destructor only; not an exact native invalid_argument provider.'
    # Its actual named destructor provider is nonexact in this COFF context:
    # native retains the derived vptr store before the base-destructor tail.
    thunk=read(0x665ac7,11);d=capstone.Cs(3,4);d.detail=True;ins=core.decode_closed_body(thunk,0x665ac7,tail=True)
    require(len(ins)==2 and ins[0].mnemonic=='mov'and ins[0].size==6
        and ins[0].operands[0].type==capstone.x86.X86_OP_MEM and ins[0].operands[0].mem.base==capstone.x86.X86_REG_ECX
        and ins[0].operands[0].size==4 and ins[0].operands[0].mem.disp==0 and not ins[0].operands[0].mem.index and not ins[0].operands[0].mem.segment
        and ins[0].operands[1].type==capstone.x86.X86_OP_IMM and ins[0].operands[1].imm==0x6c7548
        and ins[1].mnemonic=='jmp'and ins[1].operands[0].imm==0x401740,'invalid_argument whole native typed cleanup differs')
    facts=[];helper_facts=[];eh=[];public=[]
    by={a['klass']:a for a in anchors}
    for klass,k in CONTRACT.items():
        n=names(klass);calls[n['inject']]=k['inject'];hn='__ehhandler$'+n['inject'];data[hn]=(k['handler'],read(k['handler'],27),frozenset({0}),'address')
        expected=[(3,6,hn),(18,6,'___security_cookie'),(47,20,LOGIC_COPY)]
        if klass=='invalid_argument':expected += [(53,6,INVALID_VT)]
        delta=6 if klass=='invalid_argument'else 0
        expected += [(73+delta,6,BOOST_BASE),(114+delta,6,n['inject_vtables'][0]),(121+delta,6,n['inject_vtables'][1])]
        helper_facts.append(whole(n['inject'],k['inject'],k['size'],expected))
        dtor=LOGIC_DTOR if klass=='logic_error'else INVALID_DTOR;eh+=complete_eh(reader,n['inject'],k,dtor,read)
        expected=[(9,20,n['inject']),(16,6,CLONE_BASE),(22,6,n['clone_vtables'][0]),(29,6,n['clone_vtables'][1]),(36,6,n['clone_vtables'][2])]
        fact=whole(n['copy'],k['copy'],46,expected);require(fact['sha256']==by[klass]['sha256'],'public exception root digest differs')
        hits=[]
        for row in rows:
            if int(row['size'],0)==46:
                a=int(row['address'],0)
                if c.coff_symbol_bytes(obj,n['copy'],a,0xffffffff,calls,data)==read(a,46):hits.append(row['address'])
        require(hits==[by[klass]['address']],'public exception whole root is not inventory-unique');fact['inventory_hits']=hits;facts.append(fact)
        _,b,_,rr=rank.read_coff_function(obj,n['public'],None);require(len(b)==97,'original public throw specialization emission changed')
        public.append(dict(symbol=n['public'],source_size=len(b),native_body_accepted=False))
    # Current ordinary copy remains a typed provider, not an extra exact body.
    bh='__ehhandler$'+LOGIC_COPY;data[bh]=(0x6bd928,read(0x6bd928,27),frozenset({0}),'address')
    _,raw,_,rr=rank.read_coff_function(obj,LOGIC_COPY,None);bc=c.coff_symbol_bytes(obj,LOGIC_COPY,0x4017a0,0xffffffff,calls,data);native=read(0x4017a0,113)
    require(len(raw)==113 and bc!=native,'ordinary logic_error provider diagnostic changed')
    return dict(roots=facts,injectors=helper_facts,eh=eh,rtti=graph.records,vtables=graph.tables,support=support,public_instantiations=public,
        nonexact_providers=[dict(symbol=LOGIC_COPY,source_size=113,native_size=113,canonical_sha256=digest(bc),unequal_bytes=sum(x!=y for x,y in zip(bc,native))),
            dict(symbol=INVALID_DTOR,source_size=50,native_size=11,native_address='0x00665AC7',native_sha256=digest(thunk),source_matches_base_50_only=True,base_body_equivalence=invalid_base)])

def validate(rule,selected,rows,read,target_sha):
    try:
        require(ROOT/str(rule['boost_public_exception_copy_anchor_file'])==ANCHORS,'unreviewed public exception anchor path')
        spec=tomllib.loads(ANCHORS.read_text());unit=load_manifest()['units'][UNIT];aa=validate_spec(spec,selected,unit,target_sha)
        upstream.verified_exception_instantiations();tools,pins=core.pinned_tools(False)
        record=build.build_unit(UNIT,unit,True,target_sha);c=core.comparator();c.verify_target();game=pefile.PE(str(c.TARGET))
        origins={r['address']:r for r in csv.DictReader((ROOT/'config/function-origins.csv').open())}
        proof=qualify(unit,aa,rows,read,c,game,origins);code,comparisons=build.compare_unit(unit,True)
        require(code==0 and len(comparisons)==2 and all(r['result']=='exact'for r in comparisons),'public exception formal root comparison failed')
        proof.update(build=record,comparisons=comparisons,tool_pins=pins,validator_sha256=core.sha(Path(__file__)),anchor_sha256=core.sha(ANCHORS),
            rtti_validator_sha256=core.sha(ROOT/'scripts/coff_exception_rtti.py'),scope='two whole original clone copies only; no public wrapper, injector, EH, metadata or nonexact-provider byte credit')
        output=ROOT/'build/origin-anchors/boost-public-exception-copies.json';output.write_text(json.dumps(proof,indent=2)+'\n');return []
    except (OSError,ValueError,KeyError,TypeError,RuntimeError,struct.error,pefile.PEFormatError)as exc:return [str(rule['id'])+': '+str(exc)]

def main():
    c=core.comparator();sha=c.verify_target();rows=list(csv.DictReader((ROOT/'config/functions.csv').open()))
    errors=validate(dict(id='boost-original-public-exception-copies-106a',boost_public_exception_copy_anchor_file=str(ANCHORS.relative_to(ROOT))),[r for r in rows if r['address']in {'0x006A95D0','0x006B5060'}],rows,c.target_bytes,sha)
    print(json.dumps(dict(errors=errors)));return bool(errors)

if __name__=='__main__':raise SystemExit(main())
