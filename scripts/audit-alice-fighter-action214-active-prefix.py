#!/usr/bin/env python3
"""Compare action 214 active steering up to the first real cosine call."""
import hashlib
import importlib.util
import itertools
import json
import struct
import pefile
from workflow_manifest import ROOT, load_manifest, unit_input_digest, compiler_sha256

SOURCE_SHA = '4d312925be3f754e27ef0f963632f8034ca587c6b09be35dc7a7ff8aefd5bd1d'


def load_observer():
    spec = importlib.util.spec_from_file_location('alice_214_paths', ROOT / 'scripts/audit-alice-fighter-action214-paths.py')
    module = importlib.util.module_from_spec(spec); spec.loader.exec_module(module); return module


def setup():
    observer = load_observer(); whole = observer.load_audit()
    unit = load_manifest()["units"][whole.UNIT]; obj = ROOT / unit["object"]
    record = json.loads(obj.with_suffix(obj.suffix + ".provenance.json").read_text())
    digest, _ = unit_input_digest(whole.UNIT, unit)
    if (record.get("unit") != whole.UNIT or record.get("input_digest") != digest or
        record.get("object_sha256") != hashlib.sha256(obj.read_bytes()).hexdigest() or
        record.get("compiler_sha256") != compiler_sha256()):
        raise ValueError("fresh Alice source/compiler provenance required")
    _, target_sha, source, native = whole.load_candidate()
    if len(source) != 44032 or hashlib.sha256(source).hexdigest() != SOURCE_SHA:
        raise ValueError('Alice source body changed; review active prefix fixture')
    image = pefile.PE(str(ROOT / 'resources/th105.exe')).get_memory_mapped_image()
    return observer, whole.ADDRESS, image, native, source, target_sha


def expected(case):
    v, h, facing = case['vertical'], case['horizontal'], case['facing']
    product = facing * h
    if v > 0: heading = -45 if product > 0 else (-135 if product < 0 else -90)
    elif v < 0: heading = 45 if product > 0 else (135 if product < 0 else 90)
    else: heading = 0 if product > 0 else (180 if product < 0 else case['heading'])
    delta = heading - int(case['angle'])
    if delta > 180: delta -= 360
    if delta < -180: delta += 360
    angle = case['angle'] + ((0.5 if case['slow'] else 1.5) * (1 if delta > 0 else -1 if delta < 0 else 0))
    return heading, delta, angle


def validate(result, case):
    if result['boundary'] != 'cosine' or result['receiver_offset'] is not None:
        raise ValueError('active path did not reach cdecl cosine boundary')
    actor = bytes.fromhex(result['observed_prefix']); heading, delta, angle = expected(case)
    values = (struct.unpack_from('<h', actor, 0x732)[0], struct.unpack_from('<h', actor, 0x734)[0],
              struct.unpack_from('<f', actor, 0x740)[0], struct.unpack_from('<h', actor, 0x736)[0],
              struct.unpack('<f', struct.pack('<I', result['argument_word']))[0])
    if values != (heading, delta, angle, 21, angle):
        raise ValueError('active steering differs from model: ' + repr((case, values)))


def audit():
    observer, address, image, native, source, identity = setup()
    cases = [dict(sequence=seq, held=1, stop_at_cosine=True, vertical=v, horizontal=h,
                  facing=f, slow=slow, angle=angle, heading=30, speed=4.0)
             for seq,v,h,f,slow,angle in itertools.product((1,2,3,4), (-1,0,1), (-1,0,1),
                                                           (-1,1), (0,1), (-180.0,0.0,180.0))]
    for case in cases:
        n = observer.execute(image, native, case, address); s = observer.execute(image, source, case, address)
        validate(n, case); validate(s, case)
        if n != s: raise ValueError('native/source active prefix differs: ' + repr(case))
    return {'target_sha256':identity, 'source_sha256':SOURCE_SHA, 'cases':len(cases),
            'result':'bounded_prefixes_agree', 'scope':'real frame helper; stop before first cosine body; no active velocity, later calls, real-game or exactness claim'}

if __name__ == '__main__': print(json.dumps(audit(), indent=2))
