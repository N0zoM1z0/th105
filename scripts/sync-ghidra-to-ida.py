#!/usr/bin/env python3
"""Plan or apply the evidence-backed part of a Ghidra bundle through IDA MCP."""

from __future__ import annotations

import argparse
import asyncio
import csv
import hashlib
import json
from pathlib import Path
import re
import tomllib
from typing import Any

from ida_mcp_client import IdaMcpError, call_json, open_session, parse_int, require_target


ROOT = Path(__file__).resolve().parents[1]
DEFAULT_BUNDLE = ROOT / '.analysis' / 'ghidra-analysis-bundle'
DEFAULT_REPORT = ROOT / '.analysis' / 'ida-import-report.json'
DEFAULT_NAME = re.compile(r'^(?:sub|nullsub|loc|unk|off|byte|word|dword|qword|flt|dbl)_[0-9A-Fa-f]+$')
ALLOWED_KINDS = {'names', 'prototypes', 'comments'}


def sha256(path: Path) -> str:
    value = hashlib.sha256()
    with path.open('rb') as stream:
        for block in iter(lambda: stream.read(1024 * 1024), b''):
            value.update(block)
    return value.hexdigest()


def load_csv(path: Path) -> list[dict[str, str]]:
    with path.open(encoding='utf-8', newline='') as stream:
        return list(csv.DictReader(stream))


def validate_bundle(bundle: Path) -> dict[str, Any]:
    manifest = json.loads((bundle / 'manifest.json').read_text(encoding='utf-8'))
    if manifest.get('schema') != 'th105-ghidra-analysis-bundle-v1':
        raise ValueError('unsupported analysis bundle schema')
    with (ROOT / 'config' / 'target.toml').open('rb') as stream:
        expected = tomllib.load(stream)
    target = manifest.get('target')
    if not isinstance(target, dict):
        raise ValueError('analysis bundle target metadata is missing')
    expected_identity = {
        'sha256': expected['target']['sha256'].lower(),
        'md5': expected['target']['md5'].lower(),
        'image_base': parse_int(expected['pe']['image_base']),
        'size': int(expected['target']['size']),
    }
    try:
        actual_identity = {
            'sha256': str(target['sha256']).lower(),
            'md5': str(target['md5']).lower(),
            'image_base': parse_int(target['image_base']),
            'size': parse_int(target['size']),
        }
    except (KeyError, TypeError, ValueError) as exc:
        raise ValueError('invalid analysis bundle target metadata') from exc
    if actual_identity != expected_identity:
        raise ValueError(
            f'analysis bundle target mismatch: got {actual_identity!r}, '
            f'expected {expected_identity!r}'
        )
    for name, record in manifest['files'].items():
        path = bundle / name
        if not path.is_file() or sha256(path) != record['sha256']:
            raise ValueError(f'analysis bundle digest mismatch: {name}')
    return manifest


def is_default_name(name: str) -> bool:
    return bool(DEFAULT_NAME.fullmatch(name))


def eligible_functions(bundle: Path) -> list[dict[str, str]]:
    ledger = {row['address'].lower(): row for row in load_csv(ROOT / 'config' / 'functions.csv')}
    selected = []
    for row in load_csv(bundle / 'functions.csv'):
        tracked = ledger.get(row['address'].lower())
        if tracked is None or tracked['status'] == 'unclassified':
            continue
        supported_names = {tracked['current_name'], tracked['proposed_name']}
        if row['name_source'] != 'USER_DEFINED' or row['name'] not in supported_names:
            continue
        if int(row['size']) != int(tracked['size']):
            raise ValueError(f"bundle/ledger size mismatch at {row['address']}")
        if parse_int(row['span_end']) != parse_int(tracked['span_end']):
            raise ValueError(f"bundle/ledger span mismatch at {row['address']}")
        row = dict(row)
        row['ledger_signature'] = tracked['signature']
        selected.append(row)
    return selected


async def run(args: argparse.Namespace) -> dict[str, Any]:
    bundle = args.bundle.resolve()
    manifest = validate_bundle(bundle)
    kinds = {value.strip() for value in args.kinds.split(',') if value.strip()}
    unknown = kinds - ALLOWED_KINDS
    if unknown:
        raise ValueError(f'unknown import kinds: {sorted(unknown)}')

    candidates = eligible_functions(bundle)
    report: dict[str, Any] = {
        'schema': 'th105-ida-import-report-v1',
        'mode': 'apply' if args.apply else 'dry-run',
        'bundle_manifest_sha256': sha256(bundle / 'manifest.json'),
        'source_archive_sha256': manifest['source']['archive_sha256'],
        'kinds': sorted(kinds),
        'summary': {},
        'functions': [],
    }

    async with open_session(args.server) as (session, _initialized):
        report['ida_target'] = await require_target(session)
        for source in candidates:
            address = source['address']
            item: dict[str, Any] = {
                'address': address,
                'ledger_size': int(source['size']),
                'wanted_name': source['name'],
                'wanted_prototype': source['signature'],
                'operations': [],
            }
            try:
                current = await call_json(
                    session, 'get_function_by_address', {'address': address}
                )
                item['ida_before'] = current
                current_size = parse_int(current.get('size')) if isinstance(current, dict) else -1
                current_name = str(current.get('name', '')) if isinstance(current, dict) else ''
                if current_size != int(source['size']):
                    item['decision'] = 'boundary_conflict'
                    report['functions'].append(item)
                    continue
                if current_name != source['name'] and not is_default_name(current_name):
                    item['decision'] = 'name_conflict'
                    report['functions'].append(item)
                    continue

                item['decision'] = 'eligible'
                operations: list[tuple[str, dict[str, str]]] = []
                if 'names' in kinds and current_name != source['name']:
                    operations.append(('rename_function', {
                        'function_address': address,
                        'new_name': source['name'],
                    }))
                if 'prototypes' in kinds and source['signature_source'] == 'USER_DEFINED':
                    operations.append(('set_function_prototype', {
                        'function_address': address,
                        'prototype': source['signature'],
                    }))
                if 'comments' in kinds and source['comment']:
                    operations.append(('set_comment', {
                        'address': address,
                        'comment': source['comment'],
                    }))

                for tool, arguments in operations:
                    operation: dict[str, Any] = {'tool': tool, 'arguments': arguments}
                    if args.apply:
                        try:
                            operation['result'] = await call_json(session, tool, arguments)
                            operation['status'] = 'applied'
                        except IdaMcpError as exc:
                            operation['status'] = 'failed'
                            operation['error'] = str(exc)
                    else:
                        operation['status'] = 'planned'
                    item['operations'].append(operation)

                if args.apply:
                    item['ida_after'] = await call_json(
                        session, 'get_function_by_address', {'address': address}
                    )
            except (IdaMcpError, TypeError, ValueError) as exc:
                item['decision'] = 'query_failed'
                item['error'] = str(exc)
            report['functions'].append(item)

    counts: dict[str, int] = {}
    for item in report['functions']:
        decision = str(item['decision'])
        counts[decision] = counts.get(decision, 0) + 1
        for operation in item['operations']:
            key = f"{operation['tool']}:{operation['status']}"
            counts[key] = counts.get(key, 0) + 1
    report['summary'] = counts
    return report


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument('--bundle', type=Path, default=DEFAULT_BUNDLE)
    parser.add_argument('--report', type=Path, default=DEFAULT_REPORT)
    parser.add_argument('--server', default='ida-pro-mcp')
    parser.add_argument('--kinds', default='names,prototypes,comments')
    parser.add_argument('--apply', action='store_true')
    args = parser.parse_args()
    try:
        report = asyncio.run(run(args))
    except (IdaMcpError, OSError, ValueError, json.JSONDecodeError) as exc:
        print(json.dumps({'ok': False, 'error': str(exc)}, indent=2))
        raise SystemExit(1) from exc
    args.report.parent.mkdir(parents=True, exist_ok=True)
    args.report.write_text(json.dumps(report, indent=2) + '\n', encoding='utf-8')
    print(json.dumps({
        'ok': True,
        'mode': report['mode'],
        'report': str(args.report),
        'summary': report['summary'],
    }, indent=2))


if __name__ == '__main__':
    main()
