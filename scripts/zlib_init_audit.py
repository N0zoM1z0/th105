"""Replay the native zlib inflate-init body with explicit target-role bindings."""
import hashlib
import json
from pathlib import Path
import sys

import linked_pe as core
import linked_png_sdk as sdk
from coff_exception_rtti import Reader

SYMBOL = '_inflateInit2_'
ADDRESS, SIZE = 0x6678F0, 203
BODY_HASH = '3ec7df001cc27cd27f2221da9508f3052ad4b3b90783ed3ae7ec090d43c54333'
EXPECTED_REFS = [(59, 6, '_zcalloc'), (74, 6, '_zcfree'), (162, 20, '_inflateReset')]


def validate_references(refs):
    if refs != EXPECTED_REFS:
        raise ValueError('zlib inflate-init relocation roles differ')


def audit(path):
    root = core.ROOT
    lock = root / 'config/png-source-lock.json'
    if core.sha(lock) != sdk.SOURCE_LOCK_SHA256:
        raise ValueError('zlib source lock differs')
    sdk.verified_sources(root, json.loads(lock.read_text()))
    core.pinned_tools(False)
    c = core.comparator()
    sha = c.verify_target()
    r = Reader(path)
    if r.section(SYMBOL).raw_size != SIZE or r.symbol(SYMBOL).value != 0:
        raise ValueError('zlib inflate-init extent differs')
    validate_references(r.refs(SYMBOL, SIZE))
    data = c.known_data_targets()
    for name, address in [('_zcalloc', 0x66AE40), ('_zcfree', 0x66AE60)]:
        data[name] = (address, c.target_bytes(address, 1), frozenset({0}), 'address')
    body = c.coff_symbol_bytes(path, SYMBOL, ADDRESS, SIZE, {'_inflateReset': 0x667890}, data, {})
    if body != c.target_bytes(ADDRESS, SIZE) or hashlib.sha256(body).hexdigest() != BODY_HASH:
        raise ValueError('zlib inflate-init body differs')
    return {'result': 'exact', 'target_sha256': sha, 'body_size': SIZE, 'body_sha256': BODY_HASH,
            'scope': 'body with explicit target-role bindings; no callee or whole-library equivalence claim'}


if __name__ == '__main__':
    try:
        print(json.dumps(audit(Path(sys.argv[1])), indent=2))
    except (OSError, ValueError, KeyError, RuntimeError, IndexError) as exc:
        raise SystemExit(str(exc))
