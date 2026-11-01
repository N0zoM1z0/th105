"""Whole original bad_alloc lifetimes and two allocator overflow paths.

This bounded noreturn contract leaves linked_pe.decode_closed_body unchanged.
The terminal call is justified by complete original CRT throw/record/IAT proof.
"""
import csv
import json
from pathlib import Path
import struct
import tomllib
import capstone
from capstone.x86 import X86_OP_IMM,X86_OP_MEM,X86_INS_JMP,X86_INS_MOV,X86_INS_PUSH,X86_REG_ESP
import pefile
import linked_pe as core
import original_boost_link as original
import linked_noreturn as noreturn
from linked_logic_error_origins import require,named,digest

ROOT=Path(__file__).resolve().parents[1]
ANCHORS=ROOT/'config/linked-bad-alloc-origin-anchors.toml'
OUTPUT=ROOT/'build/origin-anchors/linked-bad-alloc'
DTOR='??1bad_alloc@std@@UAE@XZ'
SCALAR='??_Gbad_alloc@std@@UAEPAXI@Z'
COPY='??0bad_alloc@std@@QAE@ABV01@@Z'
BYTE='?allocate@?$allocator@D@std@@QAEPADI@Z'
WORD='?allocate@?$allocator@J@std@@QAEPAJI@Z'
THROW='__CxxThrowException@8'
VTABLE='??_7bad_alloc@std@@6B@'
INFO='__TI2?AVbad_alloc@std@@'
CONTRACT={
 '0x00401630':(11,DTOR,[7],[2],True),
 '0x00401640':(36,SCALAR,[10,23],[5],False),
 '0x00402680':(25,COPY,[9],[15],False),
 '0x00402590':(85,BYTE,[15,58,81],[63,76],False),
 '0x00410130':(85,WORD,[18,58,81],[63,76],False),
}
CALLEES={
 '??1exception@std@@UAE@XZ':(0x689fda,'libcmt:stdexcpt.obj','vc8-kb971090-short-and-data-runtime-106a'),
 '??0exception@std@@QAE@ABV01@@Z':(0x689f82,'libcmt:stdexcpt.obj','vc8-pinned-archive-symbols-106a'),
 '??0exception@std@@QAE@ABQBD@Z':(0x689f1c,'libcmt:stdexcpt.obj','vc8-pinned-archive-symbols-106a'),
 '??2@YAPAXI@Z':(0x689dcb,'libcmt:new.obj','vc8-pinned-archive-symbols-106a'),
 '??3@YAXPAX@Z':(0x6898ea,'libcmt:delete.obj','vc8-runtime-tail-aliases-106a'),
 THROW:(0x68a153,'libcmt:throw.obj','vc8-pinned-archive-symbols-106a'),
}

def validate_spec(spec,selected,target_sha):
    require(set(spec)=={'schema_version','target_sha256','anchors'}and type(spec['schema_version'])is int
            and spec['schema_version']==1 and spec['target_sha256']==target_sha,'bad_alloc anchor schema differs')
    anchors=spec['anchors']
    require(len(anchors)==len(CONTRACT)==len(selected)
            and {a['address']for a in anchors}==set(CONTRACT)
            and {r['address']for r in selected}==set(CONTRACT),'bad_alloc selection differs')
    by={r['address']:r for r in selected}
    for a in anchors:
        size,symbol,*_=CONTRACT[a['address']]
        require(set(a)=={'address','size','symbol','sha256'}and type(a['size'])is int and a['size']==size
                and a['symbol']==symbol and int(by[a['address']]['size'],0)==size
                and isinstance(a['sha256'],str)and len(a['sha256'])==64
                and all(c in '0123456789abcdef'for c in a['sha256']),'bad_alloc typed whole anchor differs')
    return anchors

def import_at(pe,slot):
    return [(d.dll.decode().lower(),core.import_identity(e))for d in pe.DIRECTORY_ENTRY_IMPORT for e in d.imports if e.address==slot]

def throw_witness(pe,game,functions,symbols,read):
    start=named(symbols,THROW,'libcmt:throw.obj')
    raw=core.linked_body(pe,functions,start);target=read(noreturn.THROW,noreturn.THROW_SIZE)
    require(len(raw)==74 and digest(target)==noreturn.THROW_SHA,'bad_alloc complete CRT throw extent/hash differs')
    core.decode_closed_body(raw,start);core.decode_closed_body(target,noreturn.THROW)
    require(raw[14]==0xbe and raw[64:66]==b'\xff\x15','bad_alloc CRT throw pointer roles differ')
    record=struct.unpack_from('<I',raw,15)[0];slot=struct.unpack_from('<I',raw,66)[0]
    source_record=core.readonly_data(pe,record,32);native_record=read(noreturn.RECORD,32)
    require(source_record==native_record and digest(native_record)==noreturn.RECORD_SHA
            and struct.unpack_from('<I',native_record,4)[0]==1,'bad_alloc noncontinuable exception record differs')
    require(import_at(pe,slot)==import_at(game,0x6c015c)==[('kernel32.dll','RaiseException')],
            'bad_alloc RaiseException import identity differs')
    b=bytearray(raw);struct.pack_into('<I',b,15,noreturn.RECORD);struct.pack_into('<I',b,66,0x6c015c)
    require(b==target,'bad_alloc complete canonical CRT throw differs')
    core.validate_body_relocations(pe,start,74,[dict(field_offset=i)for i in (15,66)])
    return dict(source_va=hex(start),target='0x0068A153',size=74,sha256=digest(target),
                record_sha256=digest(native_record),record_size=32,noncontinuable=True,import_name='kernel32.dll!RaiseException')

def allocator_cfg(raw,start,throw,call_offsets,*,body_size=85):
    """Close all paths without treating an ordinary terminal CALL as a return."""
    require(type(body_size)is int and body_size in (78,84,85),'unreviewed allocator CFG contract')
    require(len(raw)==body_size,f'allocator must include the full{body_size}-byte body')
    d=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);d.detail=True
    instructions=list(d.disasm(raw,start));by={i.address:i for i in instructions}
    require(sum(i.size for i in instructions)==body_size,'allocator incomplete instruction decode')
    last=instructions[-1]
    require(last.address==start+body_size-5 and last.size==5 and last.bytes[0]==0xe8
            and last.operands[0].type==X86_OP_IMM and last.operands[0].imm==throw,
            'allocator terminal call is not the proved CRT throw')
    calls=[i for i in instructions if i.group(capstone.CS_GRP_CALL)]
    require([i.address-start+1 for i in calls]==call_offsets
            and all(i.size==5 and i.bytes[0]==0xe8 and i.operands[0].type==X86_OP_IMM for i in calls),
            'allocator call inventory differs')
    pending=[start];reached=set();returns=[]
    while pending:
        a=pending.pop()
        if a in reached:continue
        require(a in by,'allocator CFG escapes or enters an instruction')
        i=by[a];reached.add(a)
        if i.group(capstone.CS_GRP_RET):
            returns.append(a);continue
        if i is last:continue
        require(not i.group(capstone.CS_GRP_INT)and i.mnemonic not in {'hlt','ud2','int3','loop','loope','loopne','jcxz','jecxz'},
                'allocator unsupported control flow')
        if i.group(capstone.CS_GRP_JUMP):
            require(len(i.operands)==1 and i.operands[0].type==X86_OP_IMM,'allocator indirect jump')
            pending.append(i.operands[0].imm)
            if i.id==X86_INS_JMP:continue
        pending.append(a+i.size)
    require(reached==set(by)and len(returns)==1,'allocator unreachable bytes or unexpected return paths')
    return instructions

def allocator_canonical(raw,start,target,symbol,callmap,source_info,source_vtable):
    contract=CONTRACT['0x00402590'if symbol==BYTE else '0x00410130']
    offsets=contract[2];throw=next(a for a,(n,t)in callmap.items()if n==THROW)
    instructions=allocator_cfg(raw,start,throw,offsets);by={i.address-start:i for i in instructions}
    push=by.get(62);store=by.get(72)
    require(raw[67:72]==bytes.fromhex('8d4c240451'if symbol==BYTE else '8d4c240851'),
            'allocator throw object argument differs')
    require(push is not None and push.id==X86_INS_PUSH and push.size==5 and push.operands[0].type==X86_OP_IMM
            and push.operands[0].imm==source_info,'allocator ThrowInfo is not the actual pushed argument')
    require(store is not None and store.id==X86_INS_MOV and store.size==8
            and store.operands[0].type==X86_OP_MEM and store.operands[0].size==4
            and store.operands[0].mem.base==X86_REG_ESP and not store.operands[0].mem.index
            and store.operands[0].mem.disp==(8 if symbol==BYTE else 12)
            and store.operands[1].type==X86_OP_IMM and store.operands[1].imm==source_vtable,
            'allocator bad_alloc stack-object vptr role differs')
    # Only the proven ThrowInfo PUSH and typed stack vptr MOV have absolute data.
    for i in instructions:
        for op in i.operands:
            if op.type==X86_OP_MEM:
                require(not op.mem.segment and (op.mem.base or op.mem.index),'allocator unexpected absolute/segmented memory')
            if op.type==X86_OP_IMM and not i.group(capstone.CS_GRP_CALL)and not i.group(capstone.CS_GRP_JUMP):
                value=op.imm & 0xffffffff
                if 0x10000000<=value<0x11000000 or 0x400000<=value<0x706000:
                    require(i in (push,store),'allocator untyped absolute immediate')
    b=bytearray(raw);calls=[]
    for off in offsets:
        dest=start+off+4+struct.unpack_from('<i',raw,off)[0]
        require(dest in callmap,'allocator unnamed callee')
        n,to=callmap[dest];calls.append(dict(offset=off,symbol=n,target=to));struct.pack_into('<i',b,off,to-(target+off+4))
    require([r['symbol']for r in calls]==['??2@YAPAXI@Z','??0exception@std@@QAE@ABQBD@Z',THROW],
            'allocator call semantic roles differ')
    struct.pack_into('<I',b,63,0x6e3c18);struct.pack_into('<I',b,76,0x6c05a0)
    allocator_cfg(bytes(b),target,noreturn.THROW,offsets)
    return bytes(b),calls,[dict(field_offset=63,kind='throw_info'),dict(field_offset=76,kind='stack_vptr')]

def throw_metadata(pe,game,symbols,read,*,source_owner='original-0.obj',
                   exception_copy_owner='libcmt:stdexcpt.obj',type_info_owner='libcmt:typinfo.obj'):
    sr=lambda a,n:core.pe_data(pe,a,n)
    words=lambda rd,a,n:list(struct.unpack('<'+'I'*n,rd(a,4*n)))
    source=named(symbols,INFO,source_owner);target=0x6e3c18
    si=words(sr,source,4);ti=words(read,target,4)
    dtor=named(symbols,DTOR,'i '+source_owner);copy=named(symbols,COPY,'i '+source_owner)
    excopy=named(symbols,'??0exception@std@@QAE@ABV01@@Z',exception_copy_owner)
    require(si[:3]==[0,dtor,0]and ti[:3]==[0,0x401630,0],'bad_alloc ThrowInfo destructor/flags differs')
    sa=words(sr,si[3],3);ta=words(read,ti[3],3)
    require(sa[0]==ta[0]==2,'bad_alloc needs exactly two catchable types')
    typeinfo=named(symbols,'??_7type_info@@6B@',type_info_owner)
    types=[];metadata=[]
    for idx,(name,scopy,tcopy)in enumerate([('.?AVbad_alloc@std@@',copy,0x402680),('.?AVexception@std@@',excopy,0x689f82)]):
        at=sa[idx+1];bt=ta[idx+1];sw=words(sr,at,7);tw=words(read,bt,7)
        require([sw[i]for i in (0,2,3,4,5)]==[tw[i]for i in (0,2,3,4,5)]==[0,0,0xffffffff,0,12]
                and sw[6]==scopy and tw[6]==tcopy,'bad_alloc catchable layout/copy differs')
        literal=name.encode()+b'\0';sh=words(sr,sw[1],2);th=words(read,tw[1],2)
        require(sh==[typeinfo,0]and th[1]==0
                and core.primary_type_name(pe,typeinfo)==core.primary_type_name(game,th[0])=='.?AVtype_info@@'
                and sr(sw[1]+8,len(literal))==read(tw[1]+8,len(literal))==literal,
                'bad_alloc complete type descriptor differs')
        core.validate_body_relocations(pe,sw[1],8+len(literal),[dict(field_offset=0)])
        sw[1]=tw[1];sw[6]=tw[6]
        require(struct.pack('<7I',*sw)==read(bt,28),'bad_alloc canonical catchable type differs')
        core.validate_body_relocations(pe,at,28,[dict(field_offset=4),dict(field_offset=24)])
        types.append(dict(name=name,size=12,copy=hex(tcopy),descriptor_sha256=digest(read(tw[1],8+len(literal)))))
        metadata.append(dict(address=hex(bt),size=28,sha256=digest(read(bt,28))))
    si[1]=ti[1];si[3]=ti[3];sa[1:]=ta[1:]
    require(struct.pack('<4I',*si)==read(target,16)and struct.pack('<3I',*sa)==read(ti[3],12),
            'bad_alloc complete canonical ThrowInfo/array differs')
    core.validate_body_relocations(pe,source,16,[dict(field_offset=4),dict(field_offset=12)])
    source_array=words(sr,source,4)[3]
    core.validate_body_relocations(pe,source_array,12,[dict(field_offset=4),dict(field_offset=8)])
    return source,dict(throw_info=hex(target),throw_info_sha256=digest(read(target,16)),
                       array=hex(ti[3]),array_sha256=digest(read(ti[3],12)),catchable_types=types,
                       records=metadata,record_bytes=84)

def qualify(pe,functions,symbols,anchor,rows,read,callmap,sv,source_info):
    size,symbol,offs,fields,tail=CONTRACT[anchor['address']];target=int(anchor['address'],0)
    start=named(symbols,symbol,'i original-0.obj')
    expected=[(symbol,'i original-0.obj')]
    if symbol==SCALAR:expected += [('??_Ebad_alloc@std@@UAEPAXI@Z','i CIL library: CIL module')]
    require({(n,' '.join(o.split()))for n,o in functions[start]}==set(expected),'bad_alloc unexpected source aliases')
    raw=core.linked_body(pe,functions,start);require(len(raw)==size,'bad_alloc full source extent differs')
    def resolve(a):
        require(a in callmap,'bad_alloc unproved callee')
        return callmap[a]
    def rebound(a):
        if symbol in (BYTE,WORD):return allocator_canonical(raw,start,a,symbol,callmap,source_info,sv)
        return core.canonicalize(raw,start,a,[],resolve,(core.IMAGE_BASE,core.IMAGE_BASE+pe.OPTIONAL_HEADER.SizeOfImage),
            (0x400000,0x706000),vtables=[dict(source_address=sv,target_address=0x6c05a0,symbol=VTABLE,target_key='native-bad-alloc')],tail=tail)
    canonical,calls,refs=rebound(target)
    require(canonical==read(target,size)and digest(canonical)==anchor['sha256']
            and [c['offset']for c in calls]==offs and [r['field_offset']for r in refs]==fields,
            'bad_alloc complete canonical body differs')
    core.validate_body_relocations(pe,start,size,refs)
    allowed={i for off in offs+fields for i in range(off,off+4)}
    require(all(x==y for i,(x,y)in enumerate(zip(raw,canonical))if i not in allowed),'bad_alloc changed nonrelocation byte')
    hits=[r['address']for r in rows if int(r['size'],0)==size and rebound(int(r['address'],0))[0]==read(int(r['address'],0),size)]
    require(hits==[anchor['address']],'bad_alloc full canonical body not inventory-unique')
    return dict(address=anchor['address'],symbol=symbol,size=size,sha256=digest(canonical),source_va=hex(start),
                calls=calls,data_refs=refs,inventory_hits=hits,unequal_bytes=0,masked_bytes=0)

def validate(rule,selected,rows,read,target_sha):
    try:
        require(ROOT/str(rule['linked_bad_alloc_anchor_file'])==ANCHORS,'bad_alloc unreviewed anchor path')
        anchors=validate_spec(tomllib.loads(ANCHORS.read_text()),selected,target_sha)
        image,build=original.build(output=OUTPUT);pe=pefile.PE(str(image));game=pefile.PE(str(core.comparator().TARGET))
        text=image.with_suffix('.map').read_text();functions=core.parse_map(text);symbols=core.parse_map_symbols(text)
        exports=getattr(getattr(pe,'DIRECTORY_ENTRY_EXPORT',None),'symbols',[])
        require(pe.FILE_HEADER.Machine==0x14c and pe.OPTIONAL_HEADER.ImageBase==core.IMAGE_BASE
                and len(exports)==1 and exports[0].name.decode()==original.PUBLIC_ROOT,'bad_alloc image/export contract differs')
        origins={r['address']:r for r in csv.DictReader((ROOT/'config/function-origins.csv').open())};callmap={}
        for n,(target,owner,evidence)in CALLEES.items():
            at=named(symbols,n,owner);row=origins.get(f'0x{target:08X}',{})
            require(row.get('disposition')=='exclude'and row.get('evidence_id')==evidence,'bad_alloc missing independent callee proof')
            callmap[at]=(n,target)
        sv=named(symbols,VTABLE,'libcmt:new.obj')
        require(core.primary_type_name(pe,sv)==core.primary_type_name(game,0x6c05a0)=='.?AVbad_alloc@std@@',
                'bad_alloc actual nominal RTTI differs')
        throw=throw_witness(pe,game,functions,symbols,read)
        source_info,metadata=throw_metadata(pe,game,symbols,read)
        facts=[qualify(pe,functions,symbols,a,rows,read,callmap,sv,source_info)for a in anchors]
        proof=dict(rule=rule['id'],target_sha256=target_sha,anchors=facts,build=build,throw=throw,metadata=metadata,
            validator_sha256=core.sha(Path(__file__)),anchor_sha256=core.sha(ANCHORS),
            supporting_validators={p:core.sha(ROOT/'scripts'/p)for p in ('linked_logic_error_origins.py','linked_noreturn.py')},
            scope='whole original lifetimes plus one-/four-byte allocation family, no authored or partial credit')
        (OUTPUT/'proof.json').write_text(json.dumps(proof,indent=2)+'\n')
        return []
    except (OSError,ValueError,KeyError,TypeError,RuntimeError,struct.error,pefile.PEFormatError)as exc:
        return [str(rule['id'])+': '+str(exc)]

def main():
    c=core.comparator();sha=c.verify_target();rows=list(csv.DictReader((ROOT/'config/functions.csv').open()))
    errors=validate(dict(id='linked-original-bad-alloc-106a',linked_bad_alloc_anchor_file=str(ANCHORS.relative_to(ROOT))),
                    [r for r in rows if r['address']in CONTRACT],rows,c.target_bytes,sha)
    print(json.dumps(dict(errors=errors)));return bool(errors)

if __name__=='__main__':raise SystemExit(main())
