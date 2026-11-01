"""Actual-RTTI-bound original exception copy constructors and what() slots.

The two raw-identical what() bodies are explicitly disambiguated by their
original named class vtables; neither is called globally byte-unique.
"""
import csv
import json
from pathlib import Path
import struct
import tomllib
import pefile
import linked_pe as core
import original_boost_link as original
import linked_logic_error_origins as logic
from linked_logic_error_origins import require,named,digest

ROOT=Path(__file__).resolve().parents[1]
ANCHORS=ROOT/'config/linked-exception-members-origin-anchors.toml'
OUTPUT=ROOT/'build/origin-anchors/linked-exception-members'
CONTRACT={
 '0x004016E0':(14,'?what@logic_error@std@@UBEPBDXZ','logic_error',0x6c05d0,'what'),
 '0x006A4B70':(14,'?what@runtime_error@std@@UBEPBDXZ','runtime_error',0x6d5e48,'what'),
 '0x00401780':(25,'??0out_of_range@std@@QAE@ABV01@@Z','out_of_range',0x6c05dc,'copy'),
 '0x00402570':(25,'??0length_error@std@@QAE@ABV01@@Z','length_error',0x6c0888,'copy'),
}
WHAT_HITS=['0x004016E0','0x006A4B70']

def validate_spec(spec,selected,target_sha):
    require(set(spec)=={'schema_version','target_sha256','anchors'}and type(spec['schema_version'])is int
            and spec['schema_version']==1 and spec['target_sha256']==target_sha,'exception-member schema/target differs')
    anchors=spec['anchors']
    require(len(anchors)==len(selected)==len(CONTRACT)
            and {a['address']for a in anchors}==set(CONTRACT)
            and {r['address']for r in selected}==set(CONTRACT),'exception-member selection differs')
    by={r['address']:r for r in selected}
    for a in anchors:
        size,symbol,*_=CONTRACT[a['address']]
        require(set(a)=={'address','size','symbol','sha256'}and type(a['size'])is int and a['size']==size
                and a['symbol']==symbol and int(by[a['address']]['size'],0)==size
                and isinstance(a['sha256'],str)and len(a['sha256'])==64
                and all(c in '0123456789abcdef'for c in a['sha256']),'exception-member complete typed anchor differs')
    return anchors

def type_contract(pe,game,symbols,klass,table,read):
    symbol='??_7'+klass+'@std@@6B@';source=named(symbols,symbol,'original-0.obj'if klass=='runtime_error'else'libcpmt:string.obj')
    expected='.?AV'+klass+'@std@@'
    require(core.primary_type_name(pe,source)==core.primary_type_name(game,table)==expected,
            'exception-member actual nominal RTTI differs')
    # The exact name and slot, not a short opcode fingerprint, disambiguate what().
    what='?what@'+('runtime_error'if klass=='runtime_error'else'logic_error')+'@std@@UBEPBDXZ'
    source_what=named(symbols,what,'i original-0.obj');target_what=0x6a4b70 if klass=='runtime_error'else 0x4016e0
    require(struct.unpack('<I',core.readonly_data(pe,source+4,4))[0]==source_what
            and struct.unpack('<I',read(table+4,4))[0]==target_what,'exception-member named what slot differs')
    core.validate_body_relocations(pe,source+4,4,[dict(field_offset=0)])
    return source,symbol,dict(type_name=expected,source_vtable=hex(source),native_vtable=hex(table),
                             source_what=hex(source_what),native_what=hex(target_what))

def inventory_contract(kind,address,hits):
    expected=WHAT_HITS if kind=='what'else[address]
    require(hits==expected,'exception-member whole inventory identity differs')
    return dict(whole_byte_hits=hits,byte_unique=kind!='what',typed_identity='actual original named class/slot'if kind=='what'else'actual original named class/copy')

def qualify(pe,game,functions,symbols,anchor,rows,read):
    size,symbol,klass,table,kind=CONTRACT[anchor['address']];target=int(anchor['address'],0)
    start=named(symbols,symbol,'i original-0.obj')
    require(functions.get(start)==[(symbol,'i original-0.obj')],'exception-member source owner/alias differs')
    sv,vsymbol,identity=type_contract(pe,game,symbols,klass,table,read)
    raw=core.linked_body(pe,functions,start);require(len(raw)==size,'exception-member complete extent differs')
    base=named(symbols,logic.COPY,'i original-0.obj')
    def resolve(a):
        require(kind=='copy'and a==base,'exception-member unproved base call')
        return logic.COPY,0x4017a0
    def rebound(a):
        return core.canonicalize(raw,start,a,[],resolve,(core.IMAGE_BASE,core.IMAGE_BASE+pe.OPTIONAL_HEADER.SizeOfImage),
            (0x400000,0x706000),vtables=[dict(source_address=sv,target_address=table,symbol=vsymbol,target_key='native-'+klass)])
    canonical,calls,refs=rebound(target)
    require(canonical==read(target,size)and digest(canonical)==anchor['sha256'],'exception-member whole canonical bytes differ')
    expected_calls=[9]if kind=='copy'else[];expected_fields=[15]if kind=='copy'else[]
    require([c['offset']for c in calls]==expected_calls and [r['field_offset']for r in refs]==expected_fields,
            'exception-member call/data roles differ')
    core.validate_body_relocations(pe,start,size,refs)
    allowed={i for off in expected_calls+expected_fields for i in range(off,off+4)}
    require(all(a==b for i,(a,b)in enumerate(zip(raw,canonical))if i not in allowed),'exception-member changed nonrelocation byte')
    hits=[r['address']for r in rows if int(r['size'],0)==size and rebound(int(r['address'],0))[0]==read(int(r['address'],0),size)]
    inventory=inventory_contract(kind,anchor['address'],hits)
    return dict(address=anchor['address'],symbol=symbol,size=size,sha256=digest(canonical),source_va=hex(start),
                source_instructions=len(core.decode_closed_body(raw,start)),target_instructions=len(core.decode_closed_body(canonical,target)),
                calls=calls,data_refs=refs,identity=identity,inventory=inventory,unequal_bytes=0,masked_bytes=0)

def validate(rule,selected,rows,read,target_sha):
    try:
        require(ROOT/str(rule['linked_exception_members_anchor_file'])==ANCHORS,'exception-member unreviewed anchor path')
        anchors=validate_spec(tomllib.loads(ANCHORS.read_text()),selected,target_sha)
        image,build=original.build(output=OUTPUT);pe=pefile.PE(str(image));game=pefile.PE(str(core.comparator().TARGET))
        maps=image.with_suffix('.map').read_text();functions=core.parse_map(maps);symbols=core.parse_map_symbols(maps)
        origins={r['address']:r for r in csv.DictReader((ROOT/'config/function-origins.csv').open())}
        context=logic.source_context(pe,symbols,origins,read)
        # Fresh whole base constructors, including complete EH, precede derived copies.
        base_facts=[logic.qualify(pe,functions,symbols,a,rows,read,context)
                    for a in tomllib.loads(logic.ANCHORS.read_text())['anchors']]
        facts=[qualify(pe,game,functions,symbols,a,rows,read)for a in anchors]
        proof=dict(rule=rule['id'],target_sha256=target_sha,anchors=facts,base_constructors=base_facts,build=build,
                   validator_sha256=core.sha(Path(__file__)),anchor_sha256=core.sha(ANCHORS),
                   base_validator_sha256=core.sha(Path(logic.__file__)),base_anchor_sha256=core.sha(logic.ANCHORS),
                   scope='complete original typed members, explicit two-body what equality; no authored credit')
        (OUTPUT/'proof.json').write_text(json.dumps(proof,indent=2)+'\n')
        return []
    except (OSError,ValueError,KeyError,TypeError,RuntimeError,struct.error,pefile.PEFormatError)as exc:
        return [str(rule['id'])+': '+str(exc)]

def main():
    c=core.comparator();sha=c.verify_target();rows=list(csv.DictReader((ROOT/'config/functions.csv').open()))
    errors=validate(dict(id='linked-original-exception-members-106a',linked_exception_members_anchor_file=str(ANCHORS.relative_to(ROOT))),
                    [r for r in rows if r['address']in CONTRACT],rows,c.target_bytes,sha)
    print(json.dumps(dict(errors=errors)));return bool(errors)

if __name__=='__main__':raise SystemExit(main())
