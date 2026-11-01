"""Complete original std::string range destruction in an actual CIL context.

Only the real scalar-delete call is canonicalized, backed by its complete
original CRT tail wrapper. Other linked proof contracts remain unchanged.
"""
import hashlib
import json
from pathlib import Path
import re
import tomllib
import capstone
from capstone.x86 import X86_OP_IMM, X86_OP_MEM
import pefile
import linked_pe as core

ROOT = Path(__file__).resolve().parents[1]
PREFIXES = ('??$_Destroy_range@V?$basic_string@D',)
DELETE = 0x006898EA
FREE = 0x0068C686


def validate_spec(spec, selected, units, rows, target_sha):
    if (set(spec) != {'schema_version','target_sha256','unit','proof_roots','anchors'}
            or type(spec['schema_version']) is not int or spec['schema_version'] != 1 or spec['target_sha256'] != target_sha
            or not isinstance(spec['unit'], str) or spec['unit'] not in units):
        raise ValueError('linked generated anchor identity/schema differs')
    unit = units[spec['unit']]
    if unit.get('kind') != 'linked_candidate' or unit.get('profile') != core.PROFILE:
        raise ValueError('linked generated anchors need the pinned real CIL unit')
    by = {r['address']:r for r in rows}
    configured = {f['address'] for f in unit['functions']}
    roots = spec['proof_roots']
    if (not isinstance(roots,list) or not roots or any(not isinstance(a,str) for a in roots) or len(roots) != len(set(roots))
            or any(a not in configured or by.get(a,{}).get('status') != 'matching' for a in roots)):
        raise ValueError('linked generated anchors need distinct configured exact proof roots')
    anchors = spec['anchors']
    if (not isinstance(anchors,list) or not anchors or any(not isinstance(a,dict) for a in anchors)
            or {a.get('address') for a in anchors} != {r['address'] for r in selected}
            or len(anchors) != len(selected)):
        raise ValueError('linked generated anchor selection differs')
    symbols = set()
    for a in anchors:
        if (set(a) != {'address','size','symbol','sha256'}
                or a['address'] not in by or type(a['size']) is not int or a['size'] != 57
                or int(by[a['address']]['size'],0) != a['size']
                or not isinstance(a['symbol'],str) or not a['symbol'].startswith(PREFIXES)
                or '@std@@' not in a['symbol'] or a['symbol'] in symbols
                or not isinstance(a['sha256'],str) or not re.fullmatch('[0-9a-f]{64}',a['sha256'])):
            raise ValueError('invalid complete string-range source anchor')
        symbols.add(a['symbol'])
    return unit


def qualify(pe, functions, cil_owner, anchor, rows, read_pe):
    symbol,size=anchor['symbol'],anchor['size']
    found=[(a,aliases)for a,aliases in functions.items()if any(n==symbol for n,o in aliases)]
    if (len(found)!=1 or len(found[0][1])!=1
            or found[0][1][0][1].split()[-1:]!=[cil_owner]):
        raise ValueError('string range has no unique source-CIL ownership')
    start=found[0][0]
    exports=getattr(getattr(pe,'DIRECTORY_ENTRY_EXPORT',None),'symbols',[])
    if any(pe.OPTIONAL_HEADER.ImageBase+e.address==start for e in exports):
        raise ValueError('string range may not be forced into the export set')
    def named(name,owner):
        found=[(a,aliases)for a,aliases in functions.items()if any(n==name for n,o in aliases)]
        if len(found)!=1 or found[0][1]!=[(name,owner)]:
            raise ValueError('string range needs original named CRT ownership')
        return found[0][0]
    delete=named('??3@YAXPAX@Z','libcmt:delete.obj')
    free=named('_free','libcmt:free.obj')
    helper=core.linked_body(pe,functions,delete)
    if len(helper)!=5 or helper[0]!=0xe9:
        raise ValueError('complete original scalar-delete wrapper differs')
    core.validate_body_relocations(pe,delete,5,[])
    def resolve_free(address):
        if address!=free:raise ValueError('scalar delete does not reach original free')
        return '_free',FREE
    native_helper,hcalls,hrefs=core.canonicalize(helper,delete,DELETE,[],resolve_free,
        (core.IMAGE_BASE,core.IMAGE_BASE+pe.OPTIONAL_HEADER.SizeOfImage),
        (0x400000,0x706000),tail=True)
    if native_helper!=read_pe(DELETE,5) or hrefs or len(hcalls)!=1:
        raise ValueError('whole scalar-delete wrapper is not canonical')
    raw=core.linked_body(pe,functions,start)
    target=int(anchor['address'],0);native=read_pe(target,size)
    if size!=57 or len(raw)!=size or len(native)!=size:
        raise ValueError('complete string range extent differs')
    source_rows=core.decode_closed_body(raw,start)
    target_rows=core.decode_closed_body(native,target)
    core.validate_body_relocations(pe,start,size,[])
    calls_at=[]
    for i in source_rows:
        if i.group(capstone.CS_GRP_CALL):calls_at.append(i.address-start)
        for op in i.operands:
            if op.type==X86_OP_MEM and ((not op.mem.base and not op.mem.index)or op.mem.segment):
                raise ValueError('string range has absolute or segmented data')
    if calls_at!=[26]or raw[26]!=0xe8:
        raise ValueError('string range has an unproved call inventory')
    def resolve(address):
        if address!=delete:raise ValueError('string range has an unproved callee')
        return '??3@YAXPAX@Z',DELETE
    def rebound(address):
        return core.canonicalize(raw,start,address,[],resolve,
            (core.IMAGE_BASE,core.IMAGE_BASE+pe.OPTIONAL_HEADER.SizeOfImage),
            (0x400000,0x706000))
    canonical,calls,refs=rebound(target)
    if (canonical!=native or refs or [x['offset']for x in calls]!=[27]
            or hashlib.sha256(native).hexdigest()!=anchor['sha256']):
        raise ValueError('whole string range canonical body differs')
    if any(a!=b for i,(a,b)in enumerate(zip(raw,canonical))if not 27<=i<31):
        raise ValueError('string range changed a non-call byte')
    matches=[]
    for row in rows:
        if int(row['size'],0)==size:
            other=int(row['address'],0)
            if rebound(other)[0]==read_pe(other,size):matches.append(row['address'])
    if matches!=[anchor['address']]:
        raise ValueError('string range is not full-inventory unique: '+repr(matches))
    return dict(address=anchor['address'],symbol=symbol,size=size,sha256=anchor['sha256'],
                source_va=f'0x{start:08X}',source_instructions=len(source_rows),
                target_instructions=len(target_rows),calls=calls,data_references=refs,
                delete_wrapper_sha256=hashlib.sha256(native_helper).hexdigest(),
                masked_bytes=0,unequal_bytes=0,inventory_matches=matches)


def validate(rule, selected, rows, read_pe, target_sha):
    from workflow_manifest import load_manifest, repository_path
    anchor_path=ROOT/str(rule['vc8_linked_string_range_anchor_file'])
    try:
        spec=tomllib.loads(anchor_path.read_text())
        unit=validate_spec(spec,selected,load_manifest()['units'],rows,target_sha)
        core.comparator().verify_target()
        # A fresh normal build, followed by independent current-input provenance
        # and full exact replay of existing roots, precedes every new helper check.
        core.build_linked(spec['unit'],unit)
        roots=core.compare_linked(spec['unit'],unit,set(spec['proof_roots']))
        if (len(roots)!=len(spec['proof_roots']) or {r.get('address') for r in roots}!=set(spec['proof_roots'])
                or any(r.get('result')!='exact' or r.get('target_sha256')!=r.get('object_compared_sha256') for r in roots)):
            raise ValueError('generated provenance root failed fresh whole canonical replay')
        image=repository_path(unit['object'],output=True)
        pe=pefile.PE(str(image));functions=core.parse_map(image.with_suffix('.map').read_text())
        facts=[qualify(pe,functions,image.with_suffix('.ltcg.obj').name,a,rows,read_pe) for a in spec['anchors']]
        result=dict(rule=rule['id'],target_sha256=target_sha,unit=spec['unit'],
            source=unit['source'],validator_sha256=core.sha(Path(__file__)),anchor_sha256=core.sha(anchor_path),image_sha256=core.sha(image),map_sha256=core.sha(image.with_suffix('.map')),
            build_receipt_sha256=core.sha(image.with_suffix('.link.json')),roots=roots,anchors=facts,
            scope='fresh source-generated string range compiler bodies; no authored or partial exact credit')
        out=ROOT/'build/origin-anchors'/f'{anchor_path.stem}-linked.json';out.parent.mkdir(parents=True,exist_ok=True)
        out.write_text(json.dumps(result,indent=2)+'\n')
        return []
    except (OSError,ValueError,KeyError,RuntimeError,TypeError,pefile.PEFormatError) as exc:
        return [f"{rule['id']}: {exc}"]


def main():
    """Replay one configured proof without rewriting the global origin census."""
    import argparse
    import importlib.util
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('rule',help='one configured vc8_linked_string_range_anchor_file rule ID')
    args=parser.parse_args()
    spec=importlib.util.spec_from_file_location('linked_origin_census',ROOT/'scripts/function-origins.py')
    origins=importlib.util.module_from_spec(spec);spec.loader.exec_module(origins)
    try:
        doc=tomllib.loads(origins.RULES.read_text());rules=[r for r in doc['rules'] if r['id']==args.rule]
        if (len(rules)!=1 or 'vc8_linked_string_range_anchor_file' not in rules[0]
                or rules[0].get('origin')!='compiler_generated' or rules[0].get('disposition')!='exclude'):
            raise ValueError('select one configured string range compiler-origin rule')
        rule=rules[0];rows=origins.read_csv(origins.FUNCTIONS);selected=origins.select(rule,rows)
        if (len(selected)!=rule['expected_count']
                or sum(int(r['size'],0) for r in selected)!=rule['expected_bytes']):
            raise ValueError('selected string range body count or bytes differ')
        data=origins.attest_target(doc)
        errors=validate(rule,selected,rows,origins.pe_reader(data),str(origins.target_manifest()['target']['sha256']))
        print(json.dumps(dict(rule=args.rule,result='blocked' if errors else 'verified',
            count=len(selected),bytes=rule['expected_bytes'],errors=errors)))
        return int(bool(errors))
    except (OSError,ValueError,KeyError,TypeError) as exc:
        print(json.dumps(dict(rule=args.rule,result='blocked',error=str(exc))))
        return 1


if __name__=='__main__':raise SystemExit(main())
