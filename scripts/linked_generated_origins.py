"""Fresh, unmasked VC8 LTCG provenance for a narrow pure-container family.

No target relocations, private ABI declarations, authored credit, cached-only
acceptance, masked bytes or adjustable evidence thresholds are supported.
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
PREFIXES = ('?_Ufill@?$vector@', '?_Lrotate@?$_Tree@', '?_Rrotate@?$_Tree@')


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
                or a['address'] not in by or type(a['size']) is not int or a['size'] < 24
                or int(by[a['address']]['size'],0) != a['size']
                or not isinstance(a['symbol'],str) or not a['symbol'].startswith(PREFIXES)
                or '@std@@' not in a['symbol'] or a['symbol'] in symbols
                or not isinstance(a['sha256'],str) or not re.fullmatch('[0-9a-f]{64}',a['sha256'])):
            raise ValueError('invalid complete pure-container source anchor')
        symbols.add(a['symbol'])
    return unit


def qualify(pe, functions, cil_owner, anchor, rows, read_pe):
    symbol, size = anchor['symbol'], anchor['size']
    found = [(a,aliases) for a,aliases in functions.items() if any(n==symbol for n,o in aliases)]
    if (len(found)!=1 or len(found[0][1])!=1
            or found[0][1][0][1].split()[-1:] != [cil_owner]):
        raise ValueError('generated symbol has no unique source-CIL MAP ownership')
    start = found[0][0]
    raw = core.linked_body(pe, functions, start)
    native = read_pe(int(anchor['address'],0),size)
    if (len(raw)!=size or len(native)!=size or raw!=native
            or hashlib.sha256(native).hexdigest()!=anchor['sha256']):
        raise ValueError('whole generated body differs; prefixes/masks are unsupported')
    source_rows = core.decode_closed_body(raw,start)
    target_rows = core.decode_closed_body(native,int(anchor['address'],0))
    core.validate_body_relocations(pe,start,size,[])
    for i in source_rows:
        if i.group(capstone.CS_GRP_CALL):
            raise ValueError('pure-container anchor contains a call')
        for op in i.operands:
            if op.type==X86_OP_MEM and ((not op.mem.base and not op.mem.index) or op.mem.segment):
                raise ValueError('pure-container anchor contains absolute or segmented access')
    def reject_call(_destination):
        raise ValueError('pure-container anchor cannot resolve a call')
    canonical,calls,refs=core.canonicalize(raw,start,int(anchor['address'],0),[],reject_call,
        (core.IMAGE_BASE,core.IMAGE_BASE+pe.OPTIONAL_HEADER.SizeOfImage),(0x400000,0x706000))
    if canonical!=raw or calls or refs:
        raise ValueError('pure-container anchor cannot canonicalize address references')
    matches=[]
    for r in rows:
        if int(r['size'],0)==size and read_pe(int(r['address'],0),size)==raw:matches.append(r['address'])
    if matches != [anchor['address']]:
        raise ValueError('pure-container body is not unique across the whole candidate inventory: '+repr(matches))
    return dict(address=anchor['address'],symbol=symbol,size=size,sha256=anchor['sha256'],
                source_va=f'0x{start:08X}',source_instructions=len(source_rows),
                target_instructions=len(target_rows),nonrelocation_bytes=size,
                masked_bytes=0,canonical_rewrites=0,inventory_matches=matches)


def validate(rule, selected, rows, read_pe, target_sha):
    from workflow_manifest import load_manifest, repository_path
    anchor_path=ROOT/str(rule['vc8_linked_generated_anchor_file'])
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
            scope='fresh source-generated pure compiler bodies; no authored or partial exact credit')
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
    parser.add_argument('rule',help='one configured vc8_linked_generated_anchor_file rule ID')
    args=parser.parse_args()
    spec=importlib.util.spec_from_file_location('linked_origin_census',ROOT/'scripts/function-origins.py')
    origins=importlib.util.module_from_spec(spec);spec.loader.exec_module(origins)
    try:
        doc=tomllib.loads(origins.RULES.read_text());rules=[r for r in doc['rules'] if r['id']==args.rule]
        if (len(rules)!=1 or 'vc8_linked_generated_anchor_file' not in rules[0]
                or rules[0].get('origin')!='compiler_generated' or rules[0].get('disposition')!='exclude'):
            raise ValueError('select one configured pure linked compiler-origin rule')
        rule=rules[0];rows=origins.read_csv(origins.FUNCTIONS);selected=origins.select(rule,rows)
        if (len(selected)!=rule['expected_count']
                or sum(int(r['size'],0) for r in selected)!=rule['expected_bytes']):
            raise ValueError('selected pure linked body count or bytes differ')
        data=origins.attest_target(doc)
        errors=validate(rule,selected,rows,origins.pe_reader(data),str(origins.target_manifest()['target']['sha256']))
        print(json.dumps(dict(rule=args.rule,result='blocked' if errors else 'verified',
            count=len(selected),bytes=rule['expected_bytes'],errors=errors)))
        return int(bool(errors))
    except (OSError,ValueError,KeyError,TypeError) as exc:
        print(json.dumps(dict(rule=args.rule,result='blocked',error=str(exc))))
        return 1


if __name__=='__main__':raise SystemExit(main())
