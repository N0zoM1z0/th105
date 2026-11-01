"""Whole endpoint allocator in the actual all-CIL network receive graph."""
import csv
import json
from pathlib import Path
import struct
import tomllib
import capstone
from capstone.x86 import X86_OP_IMM,X86_OP_MEM,X86_INS_PUSH,X86_INS_MOV,X86_REG_ESP
import pefile
import linked_pe as core
import linked_bad_alloc_origins as bad
import linked_noreturn as nr
import linked_byte_allocator_origins as byte
import network_receive_link as network
from linked_logic_error_origins import require,named,digest
from workflow_manifest import load_manifest

ROOT=Path(__file__).resolve().parents[1]
ANCHORS=ROOT/'config/linked-endpoint-allocator-origin-anchors.toml'
UNIT='cross-v106a-network-winsock-receive-thread'
SYMBOL='?allocate@?$allocator@UNetworkReceiveAddress16@th105@@@std@@QAEPAUNetworkReceiveAddress16@th105@@I@Z'
PARENT=network.EXPORTS[2]
HEADERS={
 'include/xmemory':'83a2121ebc455b25493a689a4fb299db0ca848ffc29668159bc9fb5faa95e50b',
 'include/new':'f780d7ea19c2a9666ae5ad3ad7cc9e42d2fc91b0a182d48dbc4d40489c5f4a61',
 'include/exception':'9a96028515808d3390dfe3ef14eb16fb881dd8ff133090d7bce6892466193ac6',
 'include/xstddef':'965b7cd738ab5786c5247be13c1f5399bf13ef9864e05598bb03476483bc5e91',
}
IMPORTS={
 '??2@YAPAXI@Z':('??2@YAPAXI@Z',0x689dcb),
 '??0exception@std@@QAE@ABQBD@Z':('??0exception@std@@QAE@ABQBD@Z',0x689f1c),
 '__CxxThrowException@8':('_CxxThrowException',0x68a153),
 '??1exception@std@@UAE@XZ':('??1exception@std@@UAE@XZ',0x689fda),
 '??0exception@std@@QAE@ABV01@@Z':('??0exception@std@@QAE@ABV01@@Z',0x689f82),
}

def validate_spec(spec,selected,units,target_sha):
    require(set(spec)=={'schema_version','target_sha256','unit','source_pins','anchors'}
            and type(spec['schema_version'])is int and spec['schema_version']==1
            and spec['target_sha256']==target_sha and spec['unit']==UNIT,'endpoint allocator schema/target/unit differs')
    require(len(spec['anchors'])==len(selected)==1,'endpoint allocator needs one whole root')
    a=spec['anchors'][0]
    require(set(a)=={'address','size','symbol','sha256'}and a['address']=='0x00413CC0'and type(a['size'])is int
            and a['size']==81 and a['symbol']==SYMBOL and selected[0]['address']==a['address']
            and int(selected[0]['size'],0)==81 and isinstance(a['sha256'],str)and len(a['sha256'])==64
            and all(c in '0123456789abcdef'for c in a['sha256']),
            'endpoint allocator typed selection differs')
    u=units[UNIT]
    require(u.get('kind')=='probe'and u.get('profile')=='vc8-sp1-probe-o2'
            and u.get('enable_gs')is True and u.get('source')==network.SOURCES['main'],
            'endpoint allocator needs the actual complete receive source')
    expected={str(p.relative_to(ROOT))for p in network.source_inputs()}
    require(isinstance(spec['source_pins'],dict)and set(spec['source_pins'])==expected
            and all(isinstance(v,str)and len(v)==64 and all(c in '0123456789abcdef'for c in v)for v in spec['source_pins'].values()),
            'endpoint allocator actual source closure differs')
    return u,a

def verify_sources(spec,tools):
    for name,sha in spec['source_pins'].items():
        p=(ROOT/name).resolve();p.relative_to(ROOT)
        require(digest(p.read_bytes().replace(b'\r\n',b'\n'))==sha,'endpoint allocator original caller source changed')
    for name,sha in HEADERS.items():require(core.sha(tools/name)==sha,'endpoint allocator original VC8 header changed')

def canonical_allocator(raw,start,target,callmap,source_info,source_vtable):
    throw=next(a for a,(n,t)in callmap.items()if n==bad.THROW)
    instructions=bad.allocator_cfg(raw,start,throw,[14,54,77],body_size=81)
    by={i.address-start:i for i in instructions};push=by.get(58);store=by.get(68)
    require(push is not None and push.id==X86_INS_PUSH and push.size==5
            and push.operands[0].type==X86_OP_IMM and push.operands[0].imm==source_info,
            'endpoint allocator actual ThrowInfo argument differs')
    require(raw[63:68]==bytes.fromhex('8d4c240851')and store is not None
            and store.id==X86_INS_MOV and store.size==8
            and store.operands[0].type==X86_OP_MEM and store.operands[0].size==4
            and store.operands[0].mem.base==X86_REG_ESP and not store.operands[0].mem.index
            and store.operands[0].mem.disp==12 and store.operands[1].type==X86_OP_IMM
            and store.operands[1].imm==source_vtable,'endpoint allocator actual bad_alloc object argument differs')
    b=bytearray(raw);calls=[]
    for off in (14,54,77):
        dest=start+off+4+struct.unpack_from('<i',raw,off)[0]
        require(dest in callmap,'endpoint allocator unproved callee')
        n,to=callmap[dest];struct.pack_into('<i',b,off,to-target-off-4);calls.append(dict(offset=off,symbol=n,target=to))
    require([r['symbol']for r in calls]==['??2@YAPAXI@Z','??0exception@std@@QAE@ABQBD@Z',bad.THROW],
            'endpoint allocator call roles differ')
    struct.pack_into('<I',b,59,0x6e3c18);struct.pack_into('<I',b,72,0x6c05a0)
    bad.allocator_cfg(bytes(b),target,nr.THROW,[14,54,77],body_size=81)
    return bytes(b),calls

def qualify(pe,game,functions,symbols,owner,anchor,rows,read):
    callmap={byte.import_callable(pe,functions,symbols,n,exp):(n,target)for n,(exp,target)in IMPORTS.items()}
    throw=byte.native_throw(game,read)
    sv=named(symbols,bad.VTABLE,'peer.obj')
    require(core.primary_type_name(pe,sv)==core.primary_type_name(game,0x6c05a0)=='.?AVbad_alloc@std@@',
            'endpoint allocator actual bad_alloc RTTI differs')
    source_info,metadata=bad.throw_metadata(pe,game,symbols,read,source_owner='peer.obj',
        exception_copy_owner='msvcrt:MSVCR80.dll',type_info_owner='msvcrt:ti_inst.obj')
    vt=[dict(source_address=sv,target_address=0x6c05a0,symbol=bad.VTABLE,target_key='native-bad-alloc')]
    def resolve(at):
        require(at in callmap,'endpoint allocator support has an unproved call')
        return callmap[at]
    support=[]
    for n,target,size,tail in [(bad.DTOR,0x401630,11,True),(bad.COPY,0x402680,25,False)]:
        at=named(symbols,n,'i peer.obj');raw=core.linked_body(pe,functions,at);require(len(raw)==size,'endpoint allocator support extent differs')
        b,calls,refs=core.canonicalize(raw,at,target,[],resolve,(core.IMAGE_BASE,core.IMAGE_BASE+pe.OPTIONAL_HEADER.SizeOfImage),
            (0x400000,0x706000),vtables=vt,tail=tail)
        require(b==read(target,size),'endpoint allocator complete support body differs')
        core.validate_body_relocations(pe,at,size,refs);support.append(dict(symbol=n,address=hex(target),size=size,sha256=digest(b)))
    start=named(symbols,SYMBOL,'i '+owner)
    require(functions.get(start)==[(SYMBOL,'i '+owner)],'endpoint allocator must have unique actual CIL ownership')
    require(all(core.IMAGE_BASE+e.address!=start for e in pe.DIRECTORY_ENTRY_EXPORT.symbols),
            'endpoint allocator may not be a forced export')
    raw=core.linked_body(pe,functions,start);require(len(raw)==81,'endpoint allocator complete extent differs')
    canonical,calls=canonical_allocator(raw,start,0x413cc0,callmap,source_info,sv)
    require(canonical==read(0x413cc0,81)and digest(canonical)==anchor['sha256'],'endpoint allocator whole canonical bytes differ')
    core.validate_body_relocations(pe,start,81,[dict(field_offset=59),dict(field_offset=72)])
    allowed={i for off in (14,54,59,72,77)for i in range(off,off+4)}
    require(all(a==b for i,(a,b)in enumerate(zip(raw,canonical))if i not in allowed),'endpoint allocator changed a nonrelocation byte')
    hits=[r['address']for r in rows if int(r['size'],0)==81
          and canonical_allocator(raw,start,int(r['address'],0),callmap,source_info,sv)[0]==read(int(r['address'],0),81)]
    require(hits==['0x00413CC0'],'endpoint allocator whole canonical body is not inventory-unique')
    exports={core.IMAGE_BASE+e.address for e in pe.DIRECTORY_ENTRY_EXPORT.symbols}
    require(exports=={named(symbols,n,owner)for n in network.EXPORTS},'network public exports changed')
    parent=named(symbols,PARENT,owner);parent_raw=core.linked_body(pe,functions,parent)
    native_parent=read(0x415340,542)
    require(digest(native_parent)=='5adc2f59eba3c9831a6813a1bf82cfe0e803ae2e9db354c558524d6f83089b3b',
            'endpoint whole native connection identity changed')
    core.decode_closed_body(parent_raw,parent);core.decode_closed_body(native_parent,0x415340)
    entry=named(symbols,network.EXPORTS[0],owner)
    loop=named(symbols,network.EXPORTS[1],owner)
    entry_raw=core.linked_body(pe,functions,entry)
    require(len(entry_raw)==14,'network actual receive entry extent differs')
    def entry_call(at):
        require(at==loop,'network actual receive entry callee differs')
        return network.EXPORTS[1],0x41d7c0
    entry_bytes,entry_calls,entry_refs=core.canonicalize(entry_raw,entry,0x41d7b0,[],entry_call,
        (core.IMAGE_BASE,core.IMAGE_BASE+pe.OPTIONAL_HEADER.SizeOfImage),(0x400000,0x706000))
    require(entry_bytes==read(0x41d7b0,14),'network existing receive entry is not whole canonical')
    core.validate_body_relocations(pe,entry,14,entry_refs)
    return dict(address='0x00413CC0',size=81,symbol=SYMBOL,sha256=digest(canonical),source_va=hex(start),
                unaccepted_parent=dict(symbol=PARENT,source_size=len(parent_raw),native_size=542),
                existing_entry=dict(address='0x0041D7B0',size=14,sha256=digest(entry_bytes)),
                calls=calls,inventory_hits=hits,throw=throw,metadata=metadata,support=support,masked_bytes=0,unequal_bytes=0)

def validate(rule,selected,rows,read,target_sha):
    try:
        require(ROOT/str(rule['linked_endpoint_allocator_anchor_file'])==ANCHORS,'unreviewed endpoint allocator anchor path')
        spec=tomllib.loads(ANCHORS.read_text());unit,anchor=validate_spec(spec,selected,load_manifest()['units'],target_sha)
        tools,pins=core.pinned_tools(False);verify_sources(spec,tools)
        image,build=network.build()
        pe=pefile.PE(str(image));game=pefile.PE(str(core.comparator().TARGET))
        maps=image.with_suffix('.map').read_text();functions=core.parse_map(maps);symbols=core.parse_map_symbols(maps)
        proof=qualify(pe,game,functions,symbols,'main.obj',anchor,rows,read)
        proof.update(unit=UNIT,build=build,source_pins=spec['source_pins'],headers=HEADERS,tool_pins=pins,
                     validator_sha256=core.sha(Path(__file__)),metadata_validator_sha256=core.sha(Path(bad.__file__)),
                     import_validator_sha256=core.sha(Path(byte.__file__)),
                     anchor_sha256=core.sha(ANCHORS),image_sha256=core.sha(image),map_sha256=core.sha(image.with_suffix('.map')),
                     scope='actual unexported source endpoint allocation family; only81 new library bytes, no parent or support credit')
        output=ROOT/'build/origin-anchors/linked-endpoint-allocator.json';output.parent.mkdir(parents=True,exist_ok=True)
        output.write_text(json.dumps(proof,indent=2)+'\n');return []
    except (OSError,ValueError,KeyError,TypeError,RuntimeError,struct.error,pefile.PEFormatError)as exc:
        return [str(rule['id'])+': '+str(exc)]

def main():
    c=core.comparator();sha=c.verify_target();rows=list(csv.DictReader((ROOT/'config/functions.csv').open()))
    errors=validate(dict(id='vc8-linked-endpoint-allocator-106a',linked_endpoint_allocator_anchor_file=str(ANCHORS.relative_to(ROOT))),
                    [r for r in rows if r['address']=='0x00413CC0'],rows,c.target_bytes,sha)
    print(json.dumps(dict(errors=errors)));return bool(errors)

if __name__=='__main__':raise SystemExit(main())
