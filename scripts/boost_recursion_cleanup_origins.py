"""Origin-only proof for Boost's emitted recursion-info destructor callback."""
import importlib.util
import json
from pathlib import Path
import struct
import tomllib
import build
import linked_pe as core
from linked_logic_error_origins import require, digest
from workflow_manifest import load_manifest

ROOT = Path(__file__).resolve().parents[1]
ANCHORS = ROOT / 'config/boost-recursion-cleanup-origin-anchors.toml'
UNIT = 'boost-regex-iterator-search'
ADDRESS = '0x00443020'
HASH = 'e273e09ce595653c6564d58efcfb8e86e3ed0674babf41678a8999a971cf864a'

def validate_spec(spec, selected, target_sha):
    require(set(spec) == {'schema_version', 'target_sha256', 'unit', 'anchors'}
            and type(spec['schema_version']) is int and spec['schema_version'] == 1
            and spec['target_sha256'] == target_sha and spec['unit'] == UNIT,
            'recursion cleanup schema, target or unit differs')
    require(len(selected) == len(spec['anchors']) == 1, 'recursion cleanup selects one body')
    anchor = spec['anchors'][0]
    require(anchor == {'address': ADDRESS, 'size': 8, 'sha256': HASH}
            and type(anchor['size']) is int and selected[0]['address'] == ADDRESS
            and int(selected[0]['size'], 0) == 8, 'recursion cleanup body contract differs')
    return anchor

def validate(rule, selected, rows, read, target_sha):
    try:
        require(ROOT / str(rule['boost_recursion_cleanup_anchor_file']) == ANCHORS,
                'unreviewed recursion cleanup anchor path')
        anchor = validate_spec(tomllib.loads(ANCHORS.read_text()), selected, target_sha)
        unit = load_manifest()['units'][UNIT]
        require(unit.get('kind') == 'probe', 'original instantiation is not a probe')
        record = build.build_unit(UNIT, unit, True, target_sha)
        code, comparisons = build.compare_unit(unit, True)
        require(code == 0 and len(comparisons) == 5 and all(x['result'] == 'exact' for x in comparisons),
                'original matcher whole-body comparisons failed')
        spec = importlib.util.spec_from_file_location('recursion_lifetime_origin_audit', ROOT / 'scripts/audit-boost-matcher-lifetimes.py')
        audit = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(audit)
        proof = audit.audit(read)
        require(proof['target_sha256'] == target_sha and proof['result'] == 'exact',
                'complete original matcher lifetimes and array roles differ')
        require(digest(read(int(ADDRESS, 0), 8)) == anchor['sha256'], 'callback body hash differs')
        output = ROOT / 'build/origin-anchors/boost-recursion-cleanup'
        output.mkdir(parents=True, exist_ok=True)
        (output / 'proof.json').write_text(json.dumps(dict(build=record, comparisons=comparisons,
            lifetime_audit=proof, scope='Compiler-emitted Boost recursion-info destructor callback only; no authored or additional exact credit.'), indent=2) + '\n')
        return []
    except (OSError, ValueError, KeyError, TypeError, RuntimeError, struct.error) as exc:
        return [str(rule['id']) + ': ' + str(exc)]
