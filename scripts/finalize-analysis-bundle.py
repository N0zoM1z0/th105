#!/usr/bin/env python3
"""Validate Ghidra bundle payloads and write a checksummed manifest."""

from __future__ import annotations

import argparse
import csv
import hashlib
import json
from pathlib import Path
import tomllib


ROOT = Path(__file__).resolve().parents[1]
PAYLOAD_FILES = (
    "functions.csv",
    "symbols.csv",
    "comments.csv",
    "defined-data.csv",
    "data-types.csv",
    "data-types.h",
)


def load_properties(path: Path) -> dict[str, str]:
    result: dict[str, str] = {}
    for raw in path.read_text(encoding="utf-8").splitlines():
        line = raw.strip()
        if not line or line.startswith(('#', '!')) or '=' not in line:
            continue
        key, value = line.split('=', 1)
        result[key.strip()] = value.strip()
    return result


def digest(path: Path) -> str:
    value = hashlib.sha256()
    with path.open('rb') as stream:
        for block in iter(lambda: stream.read(1024 * 1024), b''):
            value.update(block)
    return value.hexdigest()


def row_count(path: Path) -> int:
    with path.open(encoding='utf-8', newline='') as stream:
        return sum(1 for _ in csv.DictReader(stream))


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument('bundle', type=Path)
    parser.add_argument('--source-archive-sha256', required=True)
    parser.add_argument('--source-archive-name', required=True)
    args = parser.parse_args()

    bundle = args.bundle.resolve()
    metadata = load_properties(bundle / 'export-metadata.properties')
    with (ROOT / 'config' / 'target.toml').open('rb') as stream:
        expected = tomllib.load(stream)

    wanted_sha = expected['target']['sha256'].lower()
    wanted_md5 = expected['target']['md5'].lower()
    if metadata.get('sha256', '').lower() != wanted_sha:
        raise SystemExit('Ghidra bundle target SHA-256 mismatch')
    if metadata.get('md5', '').lower() != wanted_md5:
        raise SystemExit('Ghidra bundle target MD5 mismatch')
    if int(metadata.get('image_base', '0'), 0) != int(expected['pe']['image_base'], 0):
        raise SystemExit('Ghidra bundle image base mismatch')

    files = {}
    counts = {}
    for name in PAYLOAD_FILES:
        path = bundle / name
        if not path.is_file():
            raise SystemExit(f'missing bundle payload: {name}')
        files[name] = {'sha256': digest(path), 'size': path.stat().st_size}
        if name.endswith('.csv'):
            counts[name] = row_count(path)

    manifest = {
        'schema': 'th105-ghidra-analysis-bundle-v1',
        'target': {
            'sha256': wanted_sha,
            'md5': wanted_md5,
            'image_base': int(expected['pe']['image_base'], 0),
            'size': int(expected['target']['size']),
        },
        'source': {
            'archive_name': args.source_archive_name,
            'archive_sha256': args.source_archive_sha256.lower(),
            'ghidra_version': metadata.get('ghidra_version'),
            'language': metadata.get('language'),
            'compiler_spec': metadata.get('compiler_spec'),
        },
        'counts': counts,
        'files': files,
    }
    (bundle / 'manifest.json').write_text(
        json.dumps(manifest, indent=2, sort_keys=True) + '\n', encoding='utf-8'
    )
    print(json.dumps(manifest, indent=2, sort_keys=True))


if __name__ == '__main__':
    main()
