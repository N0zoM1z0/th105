#!/usr/bin/env python3
"""Execute Alice 214 through original angle and counter-adjust helpers."""
import importlib.util
import itertools
import json
import struct
from workflow_manifest import ROOT


def load_prefix():
    spec = importlib.util.spec_from_file_location('alice_active_prefix', ROOT / 'scripts/audit-alice-fighter-action214-active-prefix.py')
    module = importlib.util.module_from_spec(spec); spec.loader.exec_module(module); return module


def validate(prefix, result, case):
    actor = bytes.fromhex(result['observed_prefix']); heading, delta, angle = prefix.expected(case)
    f32 = lambda v: struct.unpack('<f', struct.pack('<f', v))[0]
    if case['table_kind'] == 'varying':
        index = int(abs(f32(angle * 10.0)) + 0.5) % 3600
        vx = f32(((index % 17 - 8) / 16.0) * 4.0)
    else:
        vx = 1.0
    counter = max(0, case['counter'] - (10 if case['slow'] else 5))
    rotation = f32(180.0 - angle) if vx < 0 else f32(-angle)
    seq = case['sequence']; new_sequence = None
    if vx < 0 and seq in (1, 2): new_sequence = seq + 2
    elif vx >= 0 and seq in (3, 4): new_sequence = seq - 2
    boundary = 'sequence' if new_sequence is not None else ('scratch_reset' if counter == 0 else 'landing_check')
    expected_trace = ['0x4351c0', '0x4063d0', '0x406360', '0x46bf30',
                      {'sequence':'0x45c390', 'scratch_reset':'0x435110', 'landing_check':'0x5f9310'}[boundary]]
    values = (result['boundary'], result['receiver_offset'], result.get('arguments'),
              result['helper_trace'], struct.unpack_from('<h', actor, 0x482)[0],
              struct.unpack_from('<h', actor, 0x486)[0], struct.unpack_from('<f', actor, 0x12c)[0])
    expected = (boundary, 4 if boundary == 'scratch_reset' else 0,
                [new_sequence] if new_sequence is not None else None,
                expected_trace, counter, 1, rotation)
    if values != expected: raise ValueError('post-adjust path differs from model: ' + repr((case, values, expected)))


def audit():
    prefix = load_prefix(); observer, address, image, native, source, identity = prefix.setup()
    cases = [dict(sequence=seq, held=1, stop_after_adjust=True, vertical=v, horizontal=h,
                  facing=f, slow=slow, angle=angle, heading=30, speed=4.0, table_kind=table, counter=counter)
             for seq,v,h,f,slow,angle,table,counter in itertools.product((1,2,3,4), (-1,0,1), (-1,0,1),
                 (-1,1), (0,1), (-180.0,0.0,180.0), ('constant','varying'), (4,30))]
    for case in cases:
        n = observer.execute(image, native, case, address); s = observer.execute(image, source, case, address)
        validate(prefix, n, case); validate(prefix, s, case)
        if n != s: raise ValueError('native/source post-adjust state differs: ' + repr(case))
    return {'target_sha256':identity, 'cases':len(cases), 'result':'bounded_post_adjust_paths_agree',
            'scope':'real frame, native angle lookups, runtime helpers and counter adjust; synthetic tables; stops before next sequence/scratch/landing body; no full-game claim'}

if __name__ == '__main__': print(json.dumps(audit(), indent=2))
