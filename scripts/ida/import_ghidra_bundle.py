"""Conflict-safe IDAPython importer for a TH105 Ghidra analysis bundle.

Run from IDA with File -> Script file.  It defaults to a dry run.  Pass
``--apply`` through IDA's script arguments to write names, prototypes, and
repeatable function comments.  Function boundaries are never changed.
"""

from __future__ import annotations

import argparse
import csv
import hashlib
import json
from pathlib import Path
import re

import ida_funcs
import ida_name
import ida_nalt
import ida_typeinf
import idc


TARGET_SHA256 = '49c23d9467b9927ba687ed2b873c4bc2d2f39ddadc9f55051ccf10172c0b7c11'
TARGET_MD5 = 'c2e6515bc690ee3ad74c57045ff40d88'
TARGET_SIZE = 3039232
TARGET_BASE = 0x400000
DEFAULT_NAME = re.compile(r'^(?:sub|nullsub|loc|unk|off|byte|word|dword|qword|flt|dbl)_[0-9A-Fa-f]+$')


def digest(path: Path) -> str:
    value = hashlib.sha256()
    with path.open('rb') as stream:
        for block in iter(lambda: stream.read(1024 * 1024), b''):
            value.update(block)
    return value.hexdigest()


def rows(path: Path) -> list[dict[str, str]]:
    with path.open(encoding='utf-8', newline='') as stream:
        return list(csv.DictReader(stream))


def verify_ida_target() -> None:
    sha = ida_nalt.retrieve_input_file_sha256().hex().lower()
    md5 = ida_nalt.retrieve_input_file_md5().hex().lower()
    size = ida_nalt.retrieve_input_file_size()
    base = ida_nalt.get_imagebase()
    if (sha, md5, size, base) != (TARGET_SHA256, TARGET_MD5, TARGET_SIZE, TARGET_BASE):
        raise RuntimeError(
            f'wrong IDA target: sha256={sha} md5={md5} size={size} base={base:#x}'
        )


def verify_bundle(bundle: Path) -> dict:
    manifest = json.loads((bundle / 'manifest.json').read_text(encoding='utf-8'))
    if manifest.get('schema') != 'th105-ghidra-analysis-bundle-v1':
        raise RuntimeError('unsupported Ghidra analysis bundle schema')
    target = manifest['target']
    if (
        target['sha256'].lower() != TARGET_SHA256
        or target['md5'].lower() != TARGET_MD5
        or int(target['size']) != TARGET_SIZE
        or int(target['image_base']) != TARGET_BASE
    ):
        raise RuntimeError('analysis bundle target mismatch')
    for name, record in manifest['files'].items():
        if digest(bundle / name) != record['sha256']:
            raise RuntimeError(f'analysis bundle digest mismatch: {name}')
    return manifest


def load_supported(repo: Path) -> tuple[dict[int, dict[str, str]], dict[int, str]]:
    functions = {int(row['address'], 0): row for row in rows(repo / 'config/functions.csv')}
    globals_ = {int(row['address'], 0): row['name'] for row in rows(repo / 'config/known-globals.csv')}
    return functions, globals_


def parse_arguments() -> argparse.Namespace:
    parser = argparse.ArgumentParser()
    parser.add_argument('--repo', type=Path, default=Path(__file__).resolve().parents[2])
    parser.add_argument('--bundle', type=Path)
    parser.add_argument('--report', type=Path)
    parser.add_argument('--apply', action='store_true')
    parser.add_argument('--overwrite-user-types', action='store_true')
    return parser.parse_args(idc.ARGV[1:])


def main() -> None:
    args = parse_arguments()
    repo = args.repo.resolve()
    bundle = (args.bundle or repo / '.analysis/ghidra-analysis-bundle').resolve()
    report_path = (args.report or bundle / 'ida-python-import-report.json').resolve()
    verify_ida_target()
    manifest = verify_bundle(bundle)
    ledger, known_globals = load_supported(repo)

    report = {
        'schema': 'th105-ida-python-import-report-v1',
        'mode': 'apply' if args.apply else 'dry-run',
        'source_archive_sha256': manifest['source']['archive_sha256'],
        'functions': [],
        'globals': [],
    }

    for source in rows(bundle / 'functions.csv'):
        if source['name_source'] != 'USER_DEFINED':
            continue
        ea = int(source['address'], 0)
        tracked = ledger.get(ea)
        if tracked is None or tracked['status'] == 'unclassified':
            continue
        if source['name'] not in {tracked['current_name'], tracked['proposed_name']}:
            continue
        item = {'address': source['address'], 'wanted_name': source['name'], 'operations': []}
        function = ida_funcs.get_func(ea)
        if function is None or function.start_ea != ea or function.end_ea - function.start_ea != int(source['size']):
            item['decision'] = 'boundary_conflict'
            if function is not None:
                item['ida_range'] = [hex(function.start_ea), hex(function.end_ea)]
            report['functions'].append(item)
            continue

        current_name = ida_name.get_name(ea)
        item['ida_name_before'] = current_name
        if current_name != source['name'] and not DEFAULT_NAME.fullmatch(current_name or ''):
            item['decision'] = 'name_conflict'
            report['functions'].append(item)
            continue
        item['decision'] = 'eligible'

        if current_name != source['name']:
            op = {'kind': 'name', 'before': current_name, 'after': source['name']}
            if args.apply:
                op['applied'] = bool(ida_name.set_name(ea, source['name'], ida_name.SN_CHECK | ida_name.SN_NOWARN))
            item['operations'].append(op)

        if source['signature_source'] == 'USER_DEFINED':
            has_user_type = bool(ida_nalt.get_aflags(ea) & ida_nalt.AFL_USERTI)
            op = {'kind': 'prototype', 'after': source['signature']}
            if has_user_type and not args.overwrite_user_types:
                op['decision'] = 'user_type_conflict'
            elif args.apply:
                try:
                    tif = ida_typeinf.tinfo_t(source['signature'], None, ida_typeinf.PT_SIL)
                    op['applied'] = bool(tif.is_func() and ida_typeinf.apply_tinfo(ea, tif, ida_typeinf.PT_SIL))
                except Exception as exc:
                    op['applied'] = False
                    op['error'] = str(exc)
            item['operations'].append(op)

        if source['comment']:
            existing = ida_funcs.get_func_cmt(function, True) or ''
            op = {'kind': 'comment', 'before': existing, 'after': source['comment']}
            if existing and existing != source['comment']:
                op['decision'] = 'comment_conflict'
            elif args.apply and existing != source['comment']:
                op['applied'] = bool(ida_funcs.set_func_cmt(function, source['comment'], True))
            item['operations'].append(op)
        report['functions'].append(item)

    for source in rows(bundle / 'symbols.csv'):
        if source['source'] != 'USER_DEFINED' or source['symbol_type'] == 'Function':
            continue
        ea = int(source['address'], 0)
        wanted = known_globals.get(ea)
        if wanted != source['name']:
            continue
        current = ida_name.get_name(ea)
        item = {'address': source['address'], 'before': current, 'after': wanted}
        if current == wanted:
            item['decision'] = 'already_present'
        elif not DEFAULT_NAME.fullmatch(current or ''):
            item['decision'] = 'name_conflict'
        elif args.apply:
            item['decision'] = 'applied' if ida_name.set_name(
                ea, wanted, ida_name.SN_CHECK | ida_name.SN_NOWARN
            ) else 'failed'
        else:
            item['decision'] = 'planned'
        report['globals'].append(item)

    summary = {}
    for item in report['functions']:
        key = item['decision']
        summary[key] = summary.get(key, 0) + 1
        for operation in item['operations']:
            key = f"{operation['kind']}:{operation.get('decision', 'applied' if operation.get('applied') else 'planned')}"
            summary[key] = summary.get(key, 0) + 1
    for item in report['globals']:
        key = f"global:{item['decision']}"
        summary[key] = summary.get(key, 0) + 1
    report['summary'] = summary
    report_path.write_text(json.dumps(report, indent=2) + '\n', encoding='utf-8')
    print(json.dumps({'report': str(report_path), 'summary': summary}, indent=2))


if __name__ == '__main__':
    main()
