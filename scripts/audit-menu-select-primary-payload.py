#!/usr/bin/env python3
"""Unmasked native/source menu payload comparison, including switch tables."""
import hashlib
import importlib.util
import itertools
import json
import struct
from workflow_manifest import ROOT


def compare_payload(native, source):
    if len(native) != 704 or len(source) < 32:
        raise ValueError('menu payload extent changed; review fixture')
    native_destinations = struct.unpack('<8I', native[-32:])
    source_destinations = struct.unpack('<8I', source[-32:])
    if native_destinations != (0x447db5, 0x447dd2, 0x447df0, 0x447e4a,
                               0x447ea5, 0x447f01, 0x447f50, 0x447fa7):
        raise ValueError('native switch destinations changed')
    unequal = [i for i, (a, b) in enumerate(itertools.zip_longest(native, source)) if a != b]
    return {'native_payload_bytes':len(native), 'source_payload_bytes':len(source),
            'native_sha256':hashlib.sha256(native).hexdigest(),
            'source_sha256':hashlib.sha256(source).hexdigest(),
            'native_table_offset':len(native)-32, 'source_table_offset':len(source)-32,
            'native_destinations':[hex(a) for a in native_destinations],
            'source_destinations':[hex(a) for a in source_destinations],
            'unequal_positions_including_missing':len(unequal),
            'first_unequal_offset':unequal[0] if unequal else None,
            'missing_source_bytes':max(0, len(native)-len(source)), 'masked_bytes':0,
            'result':'payload_equal' if not unequal else 'nonexact',
            'limitations':'payload excludes remote exception handler and metadata; offset differences are not independent semantic differences'}


def audit():
    spec = importlib.util.spec_from_file_location('menu_observer', ROOT / 'scripts/audit-menu-select-cancel-observer.py')
    observer = importlib.util.module_from_spec(spec); spec.loader.exec_module(observer)
    return compare_payload(*observer.code_bodies())

if __name__ == '__main__': print(json.dumps(audit(), indent=2))
