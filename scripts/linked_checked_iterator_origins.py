"""Fresh full-canonical checked-tree iterator provenance in real CIL contexts.

Only the reviewed call/tail pair to the original invalid-parameter helper is
allowed. The separate relocation-free pure-container validator is unchanged.
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
PREFIXES = ('?_Inc@const_iterator@?$_Tree@',)
INVALID = 0x0068A143
INVALID_SHA = 'cd349dae43dbf63016fe6ea9339dab15c59041e3224e48cf8a53004224b45e77'


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
                or a['address'] not in by or type(a['size']) is not int or a['size'] != 97
                or int(by[a['address']]['size'],0) != a['size']
                or not isinstance(a['symbol'],str) or not a['symbol'].startswith(PREFIXES)
                or '@std@@' not in a['symbol'] or a['symbol'] in symbols
                or not isinstance(a['sha256'],str) or not re.fullmatch('[0-9a-f]{64}',a['sha256'])):
            raise ValueError('invalid complete checked-iterator source anchor')
        symbols.add(a['symbol'])
    return unit


def qualify(pe, functions, cil_owner, anchor, rows, read_pe):
    symbol, size = anchor['symbol'], anchor['size']
    found = [(a,aliases) for a,aliases in functions.items() if any(n==symbol for n,o in aliases)]
    if (len(found)!=1 or len(found[0][1])!=1
            or found[0][1][0][1].split()[-1:] != [cil_owner]):
        raise ValueError('iterator has no unique source-CIL ownership')
    start = found[0][0]
    exports = getattr(getattr(pe,'DIRECTORY_ENTRY_EXPORT',None),'symbols',[])
    if any(pe.OPTIONAL_HEADER.ImageBase + e.address == start for e in exports):
        raise ValueError('checked iterator may not be forced into the export set')
    helpers = [(a,aliases)for a,aliases in functions.items()
               if any(n=='__invalid_parameter_noinfo'for n,o in aliases)]
    if len(helpers)!=1 or helpers[0][1] != [('__invalid_parameter_noinfo','libcmt:invarg.obj')]:
        raise ValueError('checked iterator needs the original named CRT helper')
    helper=helpers[0][0]
    helper_body=core.linked_body(pe,functions,helper)
    native_helper=read_pe(INVALID,16)
    if (len(helper_body)!=16 or helper_body != native_helper
            or hashlib.sha256(native_helper).hexdigest()!=INVALID_SHA):
        raise ValueError('whole original invalid-parameter helper differs')
    # The complete fixed wrapper calls its original named CRT owner at -36.
    if functions.get(helper-36) != [('__invalid_parameter','libcmt:invarg.obj')]:
        raise ValueError('original CRT helper call owner differs')
    raw=core.linked_body(pe,functions,start)
    native=read_pe(int(anchor['address'],0),size)
    if size!=97 or len(raw)!=size or len(native)!=size:
        raise ValueError('complete checked iterator extent differs')
    # These are actual source E8/E9 fields, not masks or fabricated receiver ABI.
    if raw[5]!=0xe8 or raw[19]!=0xe9:
        raise ValueError('checked iterator call/tail sites differ')
    source_rows=core.decode_closed_body(raw,start,external_exits={start+19:helper})
    target=int(anchor['address'],0)
    target_rows=core.decode_closed_body(native,target,external_exits={target+19:INVALID})
    core.validate_body_relocations(pe,start,size,[])
    for i in source_rows:
        if i.group(capstone.CS_GRP_CALL) and i.address!=start+5:
            raise ValueError('checked iterator has an extra call')
        for op in i.operands:
            if op.type==X86_OP_MEM and ((not op.mem.base and not op.mem.index) or op.mem.segment):
                raise ValueError('checked iterator has absolute or segmented data')
    def resolve(address):
        if address!=helper:
            raise ValueError('checked iterator has an unproved callee')
        return '__invalid_parameter_noinfo',INVALID
    def rebound(address):
        return core.canonicalize(raw,start,address,[],resolve,
            (core.IMAGE_BASE,core.IMAGE_BASE+pe.OPTIONAL_HEADER.SizeOfImage),
            (0x400000,0x706000),external_exits={start+19:helper})
    canonical,calls,refs=rebound(target)
    if (canonical!=native or refs or [x['offset']for x in calls]!=[6,20]
            or hashlib.sha256(native).hexdigest()!=anchor['sha256']):
        raise ValueError('whole checked iterator canonical body differs')
    changed={j for off in (6,20)for j in range(off,off+4)}
    if any(a!=b for i,(a,b)in enumerate(zip(raw,canonical))if i not in changed):
        raise ValueError('checked iterator changed a non-call byte')
    matches=[]
    for row in rows:
        if int(row['size'],0)==size:
            other=int(row['address'],0)
            if rebound(other)[0]==read_pe(other,size):matches.append(row['address'])
    if matches!=[anchor['address']]:
        raise ValueError('checked iterator is not full-inventory unique: '+repr(matches))
    return dict(address=anchor['address'],symbol=symbol,size=size,sha256=anchor['sha256'],
                source_va=f'0x{start:08X}',source_instructions=len(source_rows),
                target_instructions=len(target_rows),calls=calls,data_references=refs,
                helper_sha256=INVALID_SHA,masked_bytes=0,unequal_bytes=0,
                inventory_matches=matches)


def validate(rule, selected, rows, read_pe, target_sha):
    from workflow_manifest import load_manifest, repository_path
    anchor_path=ROOT/str(rule['vc8_linked_checked_iterator_anchor_file'])
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
            scope='fresh source-generated checked iterator compiler bodies; no authored or partial exact credit')
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
    parser.add_argument('rule',help='one configured vc8_linked_checked_iterator_anchor_file rule ID')
    args=parser.parse_args()
    spec=importlib.util.spec_from_file_location('linked_origin_census',ROOT/'scripts/function-origins.py')
    origins=importlib.util.module_from_spec(spec);spec.loader.exec_module(origins)
    try:
        doc=tomllib.loads(origins.RULES.read_text());rules=[r for r in doc['rules'] if r['id']==args.rule]
        if (len(rules)!=1 or 'vc8_linked_checked_iterator_anchor_file' not in rules[0]
                or rules[0].get('origin')!='compiler_generated' or rules[0].get('disposition')!='exclude'):
            raise ValueError('select one configured checked iterator compiler-origin rule')
        rule=rules[0];rows=origins.read_csv(origins.FUNCTIONS);selected=origins.select(rule,rows)
        if (len(selected)!=rule['expected_count']
                or sum(int(r['size'],0) for r in selected)!=rule['expected_bytes']):
            raise ValueError('selected checked iterator body count or bytes differ')
        data=origins.attest_target(doc)
        errors=validate(rule,selected,rows,origins.pe_reader(data),str(origins.target_manifest()['target']['sha256']))
        print(json.dumps(dict(rule=args.rule,result='blocked' if errors else 'verified',
            count=len(selected),bytes=rule['expected_bytes'],errors=errors)))
        return int(bool(errors))
    except (OSError,ValueError,KeyError,TypeError) as exc:
        print(json.dumps(dict(rule=args.rule,result='blocked',error=str(exc))))
        return 1


if __name__=='__main__':raise SystemExit(main())
