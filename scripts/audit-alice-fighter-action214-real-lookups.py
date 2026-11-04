#!/usr/bin/env python3
"""Execute original lookup code in Alice 214 up to counter adjustment."""
import importlib.util
import itertools
import json
import struct
from workflow_manifest import ROOT


def load_prefix():
    spec = importlib.util.spec_from_file_location('alice_active_prefix', ROOT / 'scripts/audit-alice-fighter-action214-active-prefix.py')
    module = importlib.util.module_from_spec(spec); spec.loader.exec_module(module); return module


def validate(prefix, result, case):
    if result['boundary'] != 'adjust' or result['receiver_offset'] != 0:
        raise ValueError('did not reach owned counter-adjust boundary')
    expected_trace = ['0x4351c0', '0x4063d0', '0x406360', '0x46bf30']
    if result['helper_trace'] != expected_trace or result['arguments'] != [10 if case['slow'] else 5, 1]:
        raise ValueError('real lookup/adjust call order or arguments differ')
    actor = bytes.fromhex(result['observed_prefix']); heading, delta, angle = prefix.expected(case)
    f32 = lambda v: struct.unpack('<f', struct.pack('<f', v))[0]
    expected_speed = f32(4.0 + f32(0.3))
    if case.get("table_kind") == "varying":
        cosine_index = int(abs(f32(angle * 10.0)) + 0.5) % 3600
        sine_index = int(abs(f32(angle * 10.0 - 900.0)) + 0.5) % 3600
        vx = f32(((cosine_index % 17 - 8) / 16.0) * 4.0)
        vy = f32(((sine_index % 17 - 8) / 16.0) * 4.0)
    else:
        vx = vy = 1.0
    values = (struct.unpack_from('<h', actor, 0x732)[0], struct.unpack_from('<h', actor, 0x734)[0],
              struct.unpack_from('<f', actor, 0x740)[0], struct.unpack_from('<f', actor, 0xf4)[0],
              struct.unpack_from('<f', actor, 0xf8)[0], struct.unpack_from('<f', actor, 0x73c)[0],
              struct.unpack_from('<h', actor, 0x736)[0])
    if values != (heading, delta, angle, vx, vy, expected_speed, 21):
        raise ValueError('real lookup state differs from model: ' + repr((case, values)))


def audit():
    prefix = load_prefix(); observer, address, image, native, source, identity = prefix.setup()
    cases = [dict(sequence=seq, held=1, stop_at_adjust=True, vertical=v, horizontal=h,
                  facing=f, slow=slow, angle=angle, heading=30, speed=4.0, table_kind=table)
             for seq,v,h,f,slow,angle,table in itertools.product((1,2,3,4), (-1,0,1), (-1,0,1),
                                                           (-1,1), (0,1), (-180.0,0.0,180.0), ('constant','varying'))]
    for case in cases:
        n = observer.execute(image, native, case, address); s = observer.execute(image, source, case, address)
        validate(prefix, n, case); validate(prefix, s, case)
        if n != s: raise ValueError('native/source real-lookup state differs: ' + repr(case))
    return {'target_sha256':identity, 'cases':len(cases), 'result':'bounded_lookup_paths_agree',
            'scope':'actual native frame/cosine/sine and their called runtime helpers; synthetic constant and varying lookup tables; stop before counter-adjust body; no actual startup or full-game claim'}

if __name__ == '__main__': print(json.dumps(audit(), indent=2))
