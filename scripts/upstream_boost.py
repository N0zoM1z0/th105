"""Verify/fetch the original Boost 1.40 VC8 header closure, without editing it.

This is compatible reference source, not proof of an exclusive shipped release.
No network is used by builds or checks. Explicit --fetch downloads missing files
from their immutable official boostorg commits and verifies them before writing.
"""
from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path, PurePosixPath
import re
import urllib.request

ROOT = Path(__file__).resolve().parents[1]
FOLDER = '.tools/upstream/boost-1.40.0-vc8'
LOCK = 'config/boost-regex-source-lock.json'
LOCK_SHA256 = '847c4101e4d3e4b91a1130f2ffc8d49e1c904457bd5910e5045f05d4d29b881a'
SUPERPROJECT = '644e2135159e0b3ca535aab1a67938c27caf6ec9'
INSTANCE_PATH = '.tools/upstream/boost-regex-1.40.0-src/instances.cpp'
INSTANCE_PROBE = 'scripts/probes/BoostRegexInstancesOrigin.cpp'
INSTANCE = dict(path='instances.cpp', repository='https://github.com/boostorg/regex',
                commit='fa1ef1dfd4136803625e49853289ade7c2ddff0a', source_path='src/instances.cpp',
                git_blob_sha1='69d72ad6e15e823c1a6f1d434c69e8f437513f01', size=697,
                sha256='44e69a60e7643db548f2c7c1fdae2807d2b8409f206cd1fe80620ae6b42d5371')


def validate(unit: dict) -> None:
    flag = unit.get('boost_regex_headers', False)
    instance = unit.get('boost_regex_instances', False)
    if type(instance) is not bool or instance and (flag is not True or unit.get('source') != INSTANCE_PROBE):
        raise ValueError('Boost instance source requires its verified header package and original-source probe')
    if type(flag) is not bool:
        raise ValueError('Boost header selection must be an explicit boolean')
    if flag and (unit.get('kind') != 'probe'
                 or unit.get('include_dirs') != [FOLDER]):
        raise ValueError('Boost header selection requires its sole pinned include directory')


def load_lock(root: Path) -> dict:
    raw = (root / LOCK).read_bytes()
    if hashlib.sha256(raw).hexdigest() != LOCK_SHA256:
        raise ValueError('Boost source lock differs from its pinned original-source manifest')
    return json.loads(raw)


def records(manifest: dict) -> list[dict]:
    if (manifest.get('schema_version') != 1 or manifest.get('release') != 'boost-1.40.0'
            or manifest.get('superproject') != 'https://github.com/boostorg/boost'
            or manifest.get('superproject_commit') != SUPERPROJECT):
        raise ValueError('Boost source version/repository identity differs')
    entries = manifest.get('files')
    if not isinstance(entries, list) or not entries:
        raise ValueError('Boost source records are missing')
    seen = set()
    for entry in entries:
        name = entry.get('path', '')
        path = PurePosixPath(name)
        expected_source = name if name == 'LICENSE_1_0.txt' else 'include/' + name
        if (not re.fullmatch(r'[A-Za-z0-9_./-]+', name) or path.is_absolute()
                or '..' in path.parts or str(path) != name or name in seen
                or not (name.startswith('boost/') or name == 'LICENSE_1_0.txt')
                or entry.get('source_path') != expected_source
                or not re.fullmatch(r'https://github.com/boostorg/[A-Za-z0-9_]+', entry.get('repository', ''))
                or not re.fullmatch('[0-9a-f]{40}', entry.get('commit', ''))
                or not re.fullmatch('[0-9a-f]{40}', entry.get('git_blob_sha1', ''))
                or not re.fullmatch('[0-9a-f]{64}', entry.get('sha256', ''))
                or type(entry.get('size')) is not int or entry['size'] < 1):
            raise ValueError('Invalid/duplicate Boost source record: ' + name)
        seen.add(name)
    if 'LICENSE_1_0.txt' not in seen or 'boost/version.hpp' not in seen:
        raise ValueError('Boost license or version header is missing')
    return entries


def verify_bytes(data: bytes, entry: dict) -> None:
    blob = b'blob ' + str(len(data)).encode() + b'\0' + data
    if (len(data) != entry['size'] or hashlib.sha1(blob).hexdigest() != entry['git_blob_sha1']
            or hashlib.sha256(data).hexdigest() != entry['sha256']):
        raise ValueError('Original Boost source bytes differ: ' + entry['path'])


def source_path(root: Path, name: str) -> Path:
    folder = (root / FOLDER).resolve()
    folder.relative_to(root.resolve())
    path = (folder / name).resolve()
    path.relative_to(folder)
    return path


def verified_sources(root: Path, manifest: dict) -> list[Path]:
    entries = records(manifest)
    result = []
    for entry in entries:
        path = source_path(root, entry['path'])
        verify_bytes(path.read_bytes(), entry)
        result.append(path)
    folder = root / FOLDER
    actual = {p.relative_to(folder).as_posix() for p in folder.rglob('*') if p.is_file()}
    if actual != {entry['path'] for entry in entries}:
        raise ValueError('Boost header package contains unpinned extra files')
    return result


def instance_path(root: Path) -> Path:
    path = (root / INSTANCE_PATH).resolve()
    path.relative_to(root.resolve())
    return path


def verified_instance(root: Path) -> Path:
    path = instance_path(root)
    verify_bytes(path.read_bytes(), INSTANCE)
    return path


def inputs(unit: dict, root: Path = ROOT) -> list[Path]:
    validate(unit)
    if not unit.get('boost_regex_headers'):
        return []
    result = [root / LOCK, root / 'scripts/upstream_boost.py',
              *verified_sources(root, load_lock(root))]
    if unit.get('boost_regex_instances'):
        result.append(verified_instance(root))
    return result


def fetch_entry(path: Path, entry: dict) -> None:
    if path.exists():
        verify_bytes(path.read_bytes(), entry)
        return
    repository = entry['repository'].removeprefix('https://github.com/')
    url = f"https://raw.githubusercontent.com/{repository}/{entry['commit']}/{entry['source_path']}"
    with urllib.request.urlopen(url, timeout=60) as response:
        data = response.read(entry['size'] + 1)
    verify_bytes(data, entry)
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_bytes(data)


def fetch_missing(root: Path, manifest: dict) -> None:
    for entry in records(manifest):
        fetch_entry(source_path(root, entry['path']), entry)


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--fetch', action='store_true', help='fetch missing pinned official source files')
    parser.add_argument('--instances', action='store_true', help='also verify/fetch the original narrow instance source')
    args = parser.parse_args()
    try:
        manifest = load_lock(ROOT)
        if args.fetch:
            fetch_missing(ROOT, manifest)
            if args.instances:
                fetch_entry(instance_path(ROOT), INSTANCE)
        sources = verified_sources(ROOT, manifest)
        if args.instances:
            sources.append(verified_instance(ROOT))
        print(f'Original Boost 1.40 reference package verified: {len(sources)} files')
        return 0
    except (OSError, ValueError) as exc:
        parser.exit(1, str(exc) + '\n')


if __name__ == '__main__':
    raise SystemExit(main())
