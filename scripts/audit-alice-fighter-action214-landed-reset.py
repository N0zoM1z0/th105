#!/usr/bin/env python3
"""Execute Alice 214's original scratch reset after crossing the synthetic stage."""
import importlib.util
import itertools
import json
import struct
from workflow_manifest import ROOT


def load_landing():
    spec = importlib.util.spec_from_file_location('alice_landing', ROOT / 'scripts/audit-alice-fighter-action214-landing.py')
    module = importlib.util.module_from_spec(spec); spec.loader.exec_module(module); return module


def validate(result):
    trace = ['0x4351c0', '0x4063d0', '0x406360', '0x46bf30', '0x5f9310',
             '0x435d60', '0x435d60', '0x435110', '0x45bfe0']
    if (result['boundary'], result['receiver_offset'], result.get('arguments'), result['helper_trace']) != ('action', 0, [215], trace):
        raise ValueError('landed reset/action boundary differs')
    actor = bytes.fromhex(result['observed_prefix'])
    offsets = (0x108, 0x10c, 0x110, 0x114, 0x11c, 0x120, 0x124, 0x128, 0x12c)
    values = tuple(struct.unpack_from('<I', actor, o)[0] for o in offsets)
    if values != (0, 0, 0xffffffff, 0, 0x3f800000, 0x3f800000, 0, 0, 0):
        raise ValueError('actual scratch reset fields differ')


def audit():
    landing = load_landing(); prefix = landing.load_prefix()
    observer, address, image, native, source, identity = prefix.setup(); cases = []
    for v,h,f,slow,table,y,x in itertools.product((-1,0,1), (-1,0,1), (-1,1), (0,1),
                                                   ('constant','varying'), (-1.0,0.0,1.0), (-1.0,50.0,1300.0)):
        case = dict(sequence=1, held=1, stop_after_scratch=True, vertical=v, horizontal=h,
                    facing=f, slow=slow, angle=0.0, heading=30, speed=4.0, table_kind=table,
                    counter=30, x=x, y=y, ground=0.0)
        vx, vy = landing.velocity(prefix, case); case['sequence'] = 1 if vx >= 0 else 3
        if y <= 0.0 and vy < 0.0: cases.append(case)
    for case in cases:
        n = observer.execute(image, native, case, address); s = observer.execute(image, source, case, address)
        validate(n); validate(s)
        if n != s: raise ValueError('native/source landed reset differs: ' + repr(case))
    return {'target_sha256':identity, 'cases':len(cases), 'result':'bounded_reset_paths_agree',
            'scope':'native frame, lookups, adjustment, terrain, landing and scratch bodies; synthetic tables; stop before action-215 body; no full-game claim'}

if __name__ == '__main__': print(json.dumps(audit(), indent=2))
