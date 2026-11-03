"""Original VC8 deque teardown emitted by the real exact resource manager."""
import csv
import hashlib
import json
from pathlib import Path
import struct
import tomllib
import capstone
import pefile
import linked_pe as core
from linked_logic_error_origins import require
from workflow_manifest import load_manifest, source_dependencies

ROOT = Path(__file__).resolve().parents[1]
UNIT = 'exact-first-resource-manager-lifetime'
ANCHORS = ROOT / 'config/linked-resource-deque-tidy-origin-anchors.toml'
SYMBOL = '?_Tidy@?$deque@PAUWaveBufferResource@th105@@V?$allocator@PAUWaveBufferResource@th105@@@std@@@std@@IAEXXZ'
OWNER = '??1?$ResourceHandleManagerLifetime64@PAUWaveBufferResource@th105@@@th105@@UAE@XZ'
TARGET = 0x413e10
FREE = 0x6898ea
BODY_SHA = '4de2dcbf24ee43a38316c27c60d25deff6dc0e0bdedb8f30de7cbc94a7e3b21d'
OWNER_SHA = 'd4527fba2f164eaffcdfb24946a9cbbcae86331b850c7784e4e72d541d7e4d4a'


def inputs(unit):
    paths = set(source_dependencies(unit))
    for source in unit.get('linked_coff_sources', []):
        paths.update(source_dependencies(dict(source=source)))
    return paths


def validate_spec(spec, selected, unit, target_sha):
    require(set(spec) == {'schema_version', 'target_sha256', 'unit', 'source_pins', 'anchors'}
        and spec['schema_version'] == 1 and spec['target_sha256'] == target_sha
        and spec['unit'] == UNIT, 'resource deque anchor schema/target/unit differs')
    require(len(selected) == len(spec['anchors']) == 1, 'resource deque needs exactly one selected body')
    anchor = spec['anchors'][0]
    require(anchor == dict(address='0x00413E10', size=102, symbol=SYMBOL, sha256=BODY_SHA)
        and selected[0]['address'] == anchor['address'] and int(selected[0]['size'], 0) == 102,
        'resource deque exact target/symbol/extent differs')
    require(unit.get('kind') == 'linked_candidate' and unit.get('profile') == core.PROFILE
        and unit.get('enable_gs') is True and unit.get('link_runtime') == 'static'
        and unit.get('source') == 'src/assets/ResourceHandleManagerLifetime.cpp'
        and unit.get('linked_coff_sources') == ['src/library/UnsignedIntList.cpp', 'src/library/UnsignedIntVector.cpp']
        and {f['address'] for f in unit['functions']} == {'0x00401F10','0x00402090','0x00402020','0x004020B0'},
        'resource deque must use the real existing resource-manager owner unit')
    expected = {str(p.relative_to(ROOT)) for p in inputs(unit)}
    pins = spec['source_pins']
    require(isinstance(pins, dict) and set(pins) == expected
        and all(isinstance(v, str) and len(v) == 64 and all(x in '0123456789abcdef' for x in v) for v in pins.values()),
        'resource deque source closure differs')
    return anchor


def qualify(pe, functions, owner, anchor, rows, origins, read):
    image_owner = owner + '.ltcg.obj'
    def one(symbol, expected_owner):
        matches = [(a, names) for a, names in functions.items() if any(n == symbol for n, _ in names)]
        require(len(matches) == 1 and matches[0][1] == [(symbol, expected_owner)], 'resource deque symbol ownership differs')
        return matches[0][0]
    start = one(SYMBOL, 'i ' + image_owner)
    parent = one(OWNER, 'i ' + image_owner)
    free = one('??3@YAXPAX@Z', 'libcmt:delete.obj')
    require(origins.get('0x006898EA', {}).get('evidence_id') == 'vc8-runtime-tail-aliases-106a'
        and origins['0x006898EA']['disposition'] == 'exclude', 'resource deque delete ownership differs')
    require(hashlib.sha256(read(0x401f10, 98)).hexdigest() == OWNER_SHA, 'resource deque native owner changed')
    def direct_calls(code, address):
        return [i for i in core.decode_closed_body(code, address) if i.group(capstone.CS_GRP_CALL)
                and i.operands[0].type == capstone.x86.X86_OP_IMM]
    parent_code = core.linked_body(pe, functions, parent)
    source_sites = [i.address-parent for i in direct_calls(parent_code, parent) if i.operands[0].imm == start]
    native_sites = [i.address for i in direct_calls(read(0x401f10, 98), 0x401f10) if i.operands[0].imm == TARGET]
    require(source_sites == [0x5a] and native_sites == [0x401f6a], 'resource deque actual owner call edge differs')
    raw = core.linked_body(pe, functions, start)
    require(len(raw) == 102, 'resource deque complete emitted extent differs')
    source_instructions = core.decode_closed_body(raw, start)
    native = read(TARGET, 102)
    core.decode_closed_body(native, TARGET)
    core.validate_body_relocations(pe, start, len(raw), [])
    require(len([i for i in source_instructions if i.group(capstone.CS_GRP_CALL)]) == 2,
        'resource deque call inventory differs')
    def resolve(address):
        require(address == free, 'resource deque unproved callee')
        return ('??3@YAXPAX@Z', FREE)
    def rebound(target):
        return core.canonicalize(raw, start, target, [], resolve,
            (core.IMAGE_BASE, core.IMAGE_BASE + pe.OPTIONAL_HEADER.SizeOfImage), (0x400000,0x706000))
    body, calls, refs = rebound(TARGET)
    require(body == native and hashlib.sha256(body).hexdigest() == anchor['sha256']
        and not refs and [x['offset'] for x in calls] == [66,87], 'resource deque whole canonical body differs')
    changed = {i for off in (66,87) for i in range(off,off+4)}
    require(all(a == b for i, (a,b) in enumerate(zip(raw,body)) if i not in changed),
        'resource deque changed non-call bytes')
    hits = [row['address'] for row in rows if int(row['size'],0)==102
            and rebound(int(row['address'],0))[0] == read(int(row['address'],0),102)]
    require(hits == ['0x00413E10'], 'resource deque body is not inventory-unique')
    return dict(address=anchor['address'],size=102,sha256=anchor['sha256'],source_address=hex(start),
        symbol=SYMBOL,source_owner=hex(parent),native_owner='0x00401F10',source_owner_call=hex(parent+0x5a),
        native_owner_call='0x00401F6A',calls=calls,inventory_hits=hits,masked_bytes=0,unequal_bytes=0,
        scope='complete compiler-generated deque cleanup, no authored credit')


def validate(rule, selected, rows, read, target_sha):
    try:
        import build
        require(ROOT / str(rule['linked_resource_deque_tidy_anchor_file']) == ANCHORS, 'resource deque anchor path differs')
        unit = load_manifest()['units'][UNIT]
        spec = tomllib.loads(ANCHORS.read_text())
        anchor = validate_spec(spec, selected, unit, target_sha)
        require(all(core.sha(ROOT/path) == digest for path,digest in spec['source_pins'].items()), 'resource deque source pin differs')
        require(next(r for r in rows if r['address']=='0x00401F10')['status']=='matching', 'resource deque exact owner status differs')
        build.build_unit(UNIT, unit, False, target_sha)
        rc, comparisons = build.compare_unit(unit, True)
        require(rc == 0 and len(comparisons)==4 and all(x['result']=='exact' for x in comparisons), 'resource manager accepted roots differ')
        image=ROOT/unit['object'];pe=pefile.PE(str(image));functions=core.parse_map(image.with_suffix('.map').read_text())
        origins={r['address']:r for r in csv.DictReader((ROOT/'config/function-origins.csv').open())}
        proof=qualify(pe,functions,image.stem,anchor,rows,origins,read)
        output=ROOT/'build/origin-anchors/linked-resource-deque-tidy';output.mkdir(parents=True,exist_ok=True)
        (output/'proof.json').write_text(json.dumps(proof,indent=2)+'\n')
        return []
    except (OSError, ValueError, KeyError, TypeError, RuntimeError, struct.error, pefile.PEFormatError) as exc:
        return [str(rule['id'])+': '+str(exc)]
