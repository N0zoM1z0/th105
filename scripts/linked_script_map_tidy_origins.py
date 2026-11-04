"""Prove CScript's native map cleanup from its genuine linked VC8 owner."""
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
UNIT = 'exact-first-script-lifecycle-linked'
ANCHORS = ROOT / 'config/linked-script-map-tidy-origin-anchors.toml'
TARGET = 0x405cd0
ERASE = 0x405d50
FREE = 0x6898ea
BODY_SHA = 'ebd0b50c162abec11a631e2fcfa27ecc2374d18c98d2f274bd4925910cc2d196'
ERASE_SHA = 'f8917ef2d0056ba4a11be297c130cfe53fc4435e9d4dfea8b604e703501ffedd'
OWNER_SHA = '1ed5c1a7fe28f8796a191563a9d5b6abcc2bdf7a1f047e570dd1c516b7a90e58'
OWNER = '??1CScript@@QAE@XZ'
SYMBOL = '?_Tidy@?$_Tree@V?$_Tmap_traits@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PAVCCommandFactoryBase@CScript@@U?$less@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@V?$allocator@U?$pair@$$CBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PAVCCommandFactoryBase@CScript@@@std@@@2@$0A@@std@@@std@@IAEXXZ'


def inputs(unit):
    paths = set(source_dependencies(unit))
    for source in unit.get('linked_coff_sources', []):
        paths.update(source_dependencies(dict(source=source)))
    return paths


def one(functions, predicate, expected_owner, label):
    matches = [(a, n, o) for a, names in functions.items() for n, o in names if predicate(n)]
    require(len(matches) == 1, label + ' symbol must be unique')
    address, name, owner = matches[0]
    require(owner == expected_owner and functions[address] == [(name, owner)], label + ' ownership differs')
    return address, name


def calls(body, address):
    return [i for i in core.decode_closed_body(body, address)
            if i.group(capstone.CS_GRP_CALL) and i.operands[0].type == capstone.x86.X86_OP_IMM]


def qualify(pe, functions, image_stem, rows, origins, read, symbol):
    image_owner = 'i ' + image_stem + '.ltcg.obj'
    start, _ = one(functions, lambda n: n == symbol, image_owner, 'tree tidy')
    parent, _ = one(functions, lambda n: n == OWNER, image_stem + '.ltcg.obj', 'script destructor')
    raw = core.linked_body(pe, functions, start)
    require(len(raw) == 56 and len(calls(raw, start)) == 2, 'tree tidy extent or calls differ')
    erase = calls(raw, start)[0].operands[0].imm
    erase_names = functions.get(erase, [])
    require(len(erase_names) == 1 and erase_names[0][1] == image_owner
        and erase_names[0][0].startswith('?erase@?$_Tree@')
        and 'CCommandFactoryBase@CScript' in erase_names[0][0], 'source tree erase role differs')
    erase_symbol = erase_names[0][0]
    free, _ = one(functions, lambda n: n == '??3@YAXPAX@Z', 'libcmt:delete.obj', 'delete')
    require(origins.get('0x006898EA', {}).get('evidence_id') == 'vc8-runtime-tail-aliases-106a'
        and origins['0x006898EA']['disposition'] == 'exclude', 'delete ownership differs')
    require(hashlib.sha256(read(0x405660, 95)).hexdigest() == OWNER_SHA, 'native destructor differs')
    require(hashlib.sha256(read(ERASE, 199)).hexdigest() == ERASE_SHA, 'native erase body differs')
    parent_calls = [i.address - parent for i in calls(core.linked_body(pe, functions, parent), parent)
                    if i.operands[0].imm == start]
    native_owner_calls = [i.address for i in calls(read(0x405660, 95), 0x405660)
                          if i.operands[0].imm == TARGET]
    require(parent_calls == [0x48] and native_owner_calls == [0x4056a8], 'actual owner edges differ')
    require([i.operands[0].imm for i in calls(raw, start)] == [erase, free], 'source call roles differ')
    native = read(TARGET, 56)
    require(hashlib.sha256(native).hexdigest() == BODY_SHA, 'native tidy hash differs')
    require([(i.address, i.operands[0].imm) for i in calls(native, TARGET)]
            == [(0x405cea, ERASE), (0x405cf3, FREE)], 'native call roles differ')
    core.validate_body_relocations(pe, start, len(raw), [])
    def resolve(address):
        require(address in (erase, free), 'unproved source callee')
        return (erase_symbol, ERASE) if address == erase else ('??3@YAXPAX@Z', FREE)
    def rebound(target):
        return core.canonicalize(raw, start, target, [], resolve,
            (core.IMAGE_BASE, core.IMAGE_BASE + pe.OPTIONAL_HEADER.SizeOfImage), (0x400000, 0x706000))
    body, bound_calls, refs = rebound(TARGET)
    require(body == native and not refs and [x['offset'] for x in bound_calls] == [27, 36],
            'whole tree tidy body differs')
    changed = {i for off in (27, 36) for i in range(off, off + 4)}
    require(all(a == b for i, (a, b) in enumerate(zip(raw, body)) if i not in changed),
            'non-call bytes changed')
    hits = [row['address'] for row in rows if int(row['size'], 0) == 56
            and rebound(int(row['address'], 0))[0] == read(int(row['address'], 0), 56)]
    require(hits == ['0x00405CD0'], 'tree tidy body is not inventory-unique')
    return dict(address='0x00405CD0', size=56, sha256=BODY_SHA, source_address=hex(start),
        source_owner=hex(parent), native_owner='0x00405660', source_owner_call=hex(parent + 0x48),
        native_owner_call='0x004056A8', source_erase_symbol=erase_symbol, native_erase='0x00405D50',
        native_erase_sha256=ERASE_SHA, calls=bound_calls, inventory_hits=hits, masked_bytes=0,
        unequal_bytes=0, scope='generated map cleanup; erase role bound, erase implementation not matched')


def validate_spec(spec, selected, unit, target_sha):
    require(set(spec) == {'schema_version', 'target_sha256', 'unit', 'source_pins', 'anchors'}
        and spec['schema_version'] == 1 and spec['target_sha256'] == target_sha and spec['unit'] == UNIT,
        'anchor schema, target or unit differs')
    require(len(selected) == len(spec['anchors']) == 1 and selected[0]['address'] == '0x00405CD0'
        and int(selected[0]['size'], 0) == 56, 'selected target differs')
    a = spec['anchors'][0]
    require(a == dict(address='0x00405CD0', size=56, symbol=SYMBOL, sha256=BODY_SHA),
        'anchor body or symbol differs')
    require(unit.get('kind') == 'linked_candidate' and unit.get('profile') == core.PROFILE
        and unit.get('enable_gs') is True and unit.get('link_runtime') == 'static'
        and unit.get('source') == 'src/battle/ScriptLifecycle.cpp'
        and {f['address'] for f in unit['functions']} == {'0x00405660', '0x004056C0', '0x00405770'},
        'owner build context differs')
    pins = spec['source_pins']; expected = {str(p.relative_to(ROOT)) for p in inputs(unit)}
    require(set(pins) == expected and all(isinstance(h, str) and len(h) == 64 and all(x in '0123456789abcdef' for x in h) for h in pins.values()),
        'source dependency closure differs')
    return a


def validate(rule, selected, rows, read, target_sha):
    try:
        import build
        require(ROOT / str(rule['linked_script_map_tidy_anchor_file']) == ANCHORS, 'anchor path differs')
        unit = load_manifest()['units'][UNIT]
        spec = tomllib.loads(ANCHORS.read_text())
        a = validate_spec(spec, selected, unit, target_sha)
        require(all(core.sha(ROOT / p) == h for p, h in spec['source_pins'].items()), 'source pin differs')
        require(next(r for r in rows if r['address'] == '0x00405660')['status'] == 'matching',
            'native destructor not accepted')
        build.build_unit(UNIT, unit, False, target_sha)
        accepted = [f for f in unit['functions'] if f['address'] in ('0x00405660', '0x00405770')]
        require(len(accepted) == 2, 'accepted owner selection differs')
        rc, comparisons = build.compare_unit(dict(unit, functions=accepted), True)
        require(rc == 0 and all(x['result'] == 'exact' for x in comparisons), 'accepted roots differ')
        image = ROOT / unit['object']; pe = pefile.PE(str(image))
        functions = core.parse_map(image.with_suffix('.map').read_text())
        origins = {r['address']: r for r in csv.DictReader((ROOT / 'config/function-origins.csv').open())}
        proof = qualify(pe, functions, image.stem, rows, origins, read, a['symbol'])
        output = ROOT / 'build/origin-anchors/linked-script-map-tidy'; output.mkdir(parents=True, exist_ok=True)
        (output / 'proof.json').write_text(json.dumps(proof, indent=2) + '\n')
        return []
    except (OSError, ValueError, KeyError, TypeError, RuntimeError, struct.error, pefile.PEFormatError) as exc:
        return [str(rule['id']) + ': ' + str(exc)]
