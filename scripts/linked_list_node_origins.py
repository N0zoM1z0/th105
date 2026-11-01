"""Complete original cache-list sentinel allocation, with actual owner use."""
import csv
import json
from pathlib import Path
import struct
import tomllib
import capstone
from capstone.x86 import X86_OP_IMM,X86_OP_MEM,X86_OP_REG,X86_REG_EAX
import pefile
import linked_pe as core
import original_boost_link as original
from linked_logic_error_origins import require,named,digest

ROOT=Path(__file__).resolve().parents[1]
ANCHORS=ROOT/'config/linked-list-node-origin-anchors.toml'
OUTPUT=ROOT/'build/origin-anchors/linked-list-node'
CTOR='??0data@?$object_cache@KV?$w32_regex_traits_implementation@D@re_detail@boost@@@boost@@QAE@XZ'
CALLER_SHA='8e3a82d4c3043bf5880656096dfa66e029b2e734571c3539ed09f64e3ebeb606'
# Exact original mangled specialization, not a caller-provided family prefix.
SYMBOL_SHA='7b009d0d5971a1dd4f3e9c83d19654088907b4ca83899957c3274b6fb1608557'

def validate_spec(spec,selected,target_sha):
    require(set(spec)=={'schema_version','target_sha256','anchors'}and type(spec['schema_version'])is int
            and spec['schema_version']==1 and spec['target_sha256']==target_sha,'list-node schema/target differs')
    require(len(spec['anchors'])==len(selected)==1,'list-node needs one whole root')
    a=spec['anchors'][0];r=selected[0]
    require(set(a)=={'address','size','symbol','sha256'}and a['address']=='0x006A3BD0'and a['size']==26
            and type(a['size'])is int and r['address']==a['address']and int(r['size'],0)==26
            and isinstance(a['symbol'],str)and digest(a['symbol'].encode())==SYMBOL_SHA
            and isinstance(a['sha256'],str)and len(a['sha256'])==64
            and all(c in '0123456789abcdef'for c in a['sha256']),'list-node original typed anchor differs')
    return a

def header_use(rows,callee,site=None):
    calls=[(j,i)for j,i in enumerate(rows)if i.group(capstone.CS_GRP_CALL)
           and i.operands[0].type==X86_OP_IMM and i.operands[0].imm==callee]
    require(len(calls)==1,'cache owner needs its sole sentinel allocation call')
    index,call=calls[0]
    require(site is None or call.address==site,'cache owner sentinel site differs')
    following=rows[index+1:index+3];require(len(following)==2,'cache sentinel header publication missing')
    first,second=following
    for i,offset in [(first,4),(second,8)]:
        require(i.mnemonic=='mov'and len(i.operands)==2 and i.operands[0].type==X86_OP_MEM
                and i.operands[0].size==4 and i.operands[0].mem.base and not i.operands[0].mem.index
                and not i.operands[0].mem.segment and i.operands[0].mem.disp==offset,
                'cache sentinel/size field publication differs')
    require(first.operands[1].type==X86_OP_REG and first.operands[1].reg==X86_REG_EAX
            and second.operands[1].type==X86_OP_IMM and second.operands[1].imm==0
            and first.operands[0].mem.base==second.operands[0].mem.base,
            'cache owner does not publish returned sentinel and zero size')
    return dict(site=hex(call.address),header_offset=4,size_offset=8,receiver=first.reg_name(first.operands[0].mem.base))

def qualify(pe,functions,symbols,anchor,rows,origins,read):
    symbol=anchor['symbol'];start=named(symbols,symbol,'i original-0.obj')
    require(functions.get(start)==[(symbol,'i original-0.obj')],'list-node source alias differs')
    alloc=named(symbols,'??2@YAPAXI@Z','libcmt:new.obj')
    for address,evidence in [('0x00689DCB','vc8-pinned-archive-symbols-106a'),('0x006B0310','boost-narrow-library-106a')]:
        row=origins.get(address,{})
        require(row.get('disposition')=='exclude'and row.get('evidence_id')==evidence,'list-node independent callee/owner proof missing')
    owner=named(symbols,CTOR,'i original-0.obj');owner_raw=core.linked_body(pe,functions,owner)
    native_owner=read(0x6b0310,125)
    require(digest(native_owner)==CALLER_SHA,'list-node native whole owner hash differs')
    source_use=header_use(core.decode_closed_body(owner_raw,owner),start)
    native_use=header_use(core.decode_closed_body(native_owner,0x6b0310),0x6a3bd0,0x6b0339)
    raw=core.linked_body(pe,functions,start)
    require(len(raw)==26 and raw[:2]==b'\x6a\x14','list-node must allocate the original20-byte node')
    def resolve(a):
        require(a==alloc,'list-node unknown callee')
        return '??2@YAPAXI@Z',0x689dcb
    def rebound(target):
        return core.canonicalize(raw,start,target,[],resolve,(core.IMAGE_BASE,core.IMAGE_BASE+pe.OPTIONAL_HEADER.SizeOfImage),(0x400000,0x706000))
    canonical,calls,refs=rebound(0x6a3bd0)
    require(canonical==read(0x6a3bd0,26)and digest(canonical)==anchor['sha256']
            and not refs and [r['offset']for r in calls]==[3],'list-node complete canonical body differs')
    core.validate_body_relocations(pe,start,26,[])
    require(all(a==b for i,(a,b)in enumerate(zip(raw,canonical))if not 3<=i<7),'list-node changed non-call byte')
    hits=[r['address']for r in rows if int(r['size'],0)==26 and rebound(int(r['address'],0))[0]==read(int(r['address'],0),26)]
    require(hits==['0x006A3BD0'],'list-node complete body is not inventory-unique')
    return dict(address=anchor['address'],symbol=symbol,size=26,sha256=digest(canonical),source_va=hex(start),
        calls=calls,inventory_hits=hits,source_owner=source_use,native_owner=native_use,
        owner_source_size=len(owner_raw),owner_native_size=125,owner_exact=False,
        source_instructions=len(core.decode_closed_body(raw,start)),target_instructions=len(core.decode_closed_body(canonical,0x6a3bd0)),
        masked_bytes=0,unequal_bytes=0,scope='20-byte list-node allocation/link prefix, no payload or parent exactness claim')

def validate(rule,selected,rows,read,target_sha):
    try:
        require(ROOT/str(rule['linked_list_node_anchor_file'])==ANCHORS,'list-node unreviewed anchor path')
        anchor=validate_spec(tomllib.loads(ANCHORS.read_text()),selected,target_sha)
        image,build=original.build(output=OUTPUT);pe=pefile.PE(str(image))
        maps=image.with_suffix('.map').read_text();functions=core.parse_map(maps);symbols=core.parse_map_symbols(maps)
        exports=getattr(getattr(pe,'DIRECTORY_ENTRY_EXPORT',None),'symbols',[])
        require(pe.FILE_HEADER.Machine==0x14c and pe.OPTIONAL_HEADER.ImageBase==core.IMAGE_BASE
                and len(exports)==1 and exports[0].name.decode()==original.PUBLIC_ROOT,'list-node image/export contract differs')
        origins={r['address']:r for r in csv.DictReader((ROOT/'config/function-origins.csv').open())}
        proof=qualify(pe,functions,symbols,anchor,rows,origins,read)
        proof.update(rule=rule['id'],target_sha256=target_sha,build=build,validator_sha256=core.sha(Path(__file__)),
                     anchor_sha256=core.sha(ANCHORS),helper_validator_sha256=core.sha(ROOT/'scripts/linked_logic_error_origins.py'))
        (OUTPUT/'proof.json').write_text(json.dumps(proof,indent=2)+'\n');return []
    except (OSError,ValueError,KeyError,TypeError,RuntimeError,struct.error,pefile.PEFormatError)as exc:
        return [str(rule['id'])+': '+str(exc)]

def main():
    c=core.comparator();sha=c.verify_target();rows=list(csv.DictReader((ROOT/'config/functions.csv').open()))
    errors=validate(dict(id='linked-original-cache-list-node-106a',linked_list_node_anchor_file=str(ANCHORS.relative_to(ROOT))),
                    [r for r in rows if r['address']=='0x006A3BD0'],rows,c.target_bytes,sha)
    print(json.dumps(dict(errors=errors)));return bool(errors)

if __name__=='__main__':raise SystemExit(main())
