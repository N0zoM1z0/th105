#!/usr/bin/env python3
"""Execute Alice active flight through native landing predicate and terrain lookup."""
import importlib.util
import itertools
import json
import struct
from workflow_manifest import ROOT


def load_prefix():
    spec = importlib.util.spec_from_file_location('alice_active_prefix', ROOT / 'scripts/audit-alice-fighter-action214-active-prefix.py')
    module = importlib.util.module_from_spec(spec); spec.loader.exec_module(module); return module


def velocity(prefix, case):
    _, _, angle = prefix.expected(case)
    if case['table_kind'] == 'constant': return 1.0, 1.0
    f32 = lambda v: struct.unpack('<f', struct.pack('<f', v))[0]
    ci = int(abs(f32(angle * 10.0)) + 0.5) % 3600
    si = int(abs(f32(angle * 10.0 - 900.0)) + 0.5) % 3600
    return f32((ci % 17 - 8) / 4.0), f32((si % 17 - 8) / 4.0)


def validate(prefix, result, case):
    vx, vy = velocity(prefix, case)
    crossed = case['y'] <= case['ground'] and vy < 0.0
    boundary = 'scratch_reset' if crossed else 'root_return'
    trace = ['0x4351c0', '0x4063d0', '0x406360', '0x46bf30', '0x5f9310', '0x435d60']
    trace += ['0x435d60', '0x435110'] if crossed else ['0x710000']
    actor = bytes.fromhex(result['observed_prefix'])
    values = (result['boundary'], result['receiver_offset'], result['helper_trace'],
              struct.unpack_from('<f', actor, 0xf0)[0], struct.unpack_from('<f', actor, 0xf4)[0],
              struct.unpack_from('<f', actor, 0xf8)[0], struct.unpack_from('<f', actor, 0x100)[0])
    expected = (boundary, 4 if crossed else None, trace, case['ground'] if crossed else case['y'],
                vx, 0.0 if crossed else vy, 0.0 if crossed else 0.5)
    if values != expected: raise ValueError('landing path differs from model: ' + repr((case, values, expected)))


def audit():
    prefix = load_prefix(); observer, address, image, native, source, identity = prefix.setup(); cases = []
    for v,h,f,slow,table,y,x in itertools.product((-1,0,1), (-1,0,1), (-1,1), (0,1),
                                                   ('constant','varying'), (-1.0,0.0,1.0), (-1.0,50.0,1300.0)):
        case = dict(sequence=1, held=1, stop_after_landing_check=True, vertical=v, horizontal=h,
                    facing=f, slow=slow, angle=0.0, heading=30, speed=4.0, table_kind=table,
                    counter=30, x=x, y=y, ground=0.0)
        vx, _ = velocity(prefix, case); case['sequence'] = 1 if vx >= 0 else 3
        cases.append(case)
    crossed = 0
    for case in cases:
        n = observer.execute(image, native, case, address); s = observer.execute(image, source, case, address)
        validate(prefix, n, case); validate(prefix, s, case)
        if n != s: raise ValueError('native/source landing state differs: ' + repr(case))
        crossed += n['boundary'] == 'scratch_reset'
    return {'target_sha256':identity, 'cases':len(cases), 'crossed_cases':crossed,
            'result':'bounded_landing_paths_agree',
            'scope':'actual native frame, angle, counter, landing and stage-height code; synthetic angle/stage tables; stops before scratch reset or at root return; no full-game claim'}

if __name__ == '__main__': print(json.dumps(audit(), indent=2))
