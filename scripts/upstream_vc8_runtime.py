#!/usr/bin/env python3
"""Verify an isolated original VC8 KB971090 runtime reference; fetch only explicitly."""
from __future__ import annotations
import argparse
import hashlib
from pathlib import Path
import tempfile
import urllib.request

ROOT = Path(__file__).resolve().parents[1]
FOLDER = '.tools/upstream/vc8-kb971090'
URL = 'https://download.microsoft.com/download/D/2/3/D23F9F62-3DEE-4EC0-B3B9-D64E9F573D1F/VS80sp1-KB971090-X86-INTL.exe'
PACKAGE = ('VS80sp1-KB971090-X86-INTL.exe', 261194672, '38494dccecaa3fec1fd7b1cd9b93df5f77bee7305971513364e8fcf9339d3618')
PATCH = ('VS80sp1-KB971090-X86-INTL.msp', 296257024, '64826db38c375cca7c890a72bee993e01a69072e76146b947b5993f7cf6b3d65')
CABINET = ('patch.cab', 246055772, 'f9b898274082a2f907cb6382370c82b2d0442cdc2b4517436eed9d1c6a935991')
LIBRARIES = {
    'libcmt': ('libcmt.lib', 'cbc9a9f5f706aa63deda800a01386dd0b46c121f60bb7ea28bd74e5d9399c581'),
    'libcpmt': ('libcpmt.lib', 'fe8597decade589a232c45aed8c52d939d9a26f64069cfccb3a77caf9abe4138'),
}
LIBRARY_SIZES = {'libcmt': 7705590, 'libcpmt': 4983946}
MEMBERS = {
    'FL_libcmt_lib_____X86.3643236F_FC70_11D3_A536_0090278A1BB8': 'libcmt',
    'FL_libcpmt_lib_____X86.3643236F_FC70_11D3_A536_0090278A1BB8': 'libcpmt',
}


def within(root: Path, relative: str) -> Path:
    path = (root / relative).resolve()
    path.relative_to(root.resolve())
    return path


def verify(path: Path, size: int, sha256: str) -> None:
    if path.stat().st_size != size:
        raise ValueError(f'{path.name}: original file size differs')
    digest = hashlib.sha256()
    with path.open('rb') as stream:
        for block in iter(lambda: stream.read(1024 * 1024), b''):
            digest.update(block)
    if digest.hexdigest() != sha256:
        raise ValueError(f'{path.name}: original file SHA-256 differs')


def write_verified(path: Path, blocks, size: int, sha256: str) -> None:
    if path.exists():
        verify(path, size, sha256)
        return
    path.parent.mkdir(parents=True, exist_ok=True)
    temporary = None
    try:
        with tempfile.NamedTemporaryFile(dir=path.parent, delete=False) as stream:
            temporary = Path(stream.name)
            count = 0
            for block in blocks:
                count += len(block)
                if count > size:
                    raise ValueError(f'{path.name}: original file is too large')
                stream.write(block)
        verify(temporary, size, sha256)
        temporary.replace(path)
    finally:
        if temporary is not None and temporary.exists():
            temporary.unlink()


def verified_libraries(root: Path = ROOT) -> list[Path]:
    result = []
    for name, (filename, sha256) in LIBRARIES.items():
        path = within(root, FOLDER + '/' + filename)
        verify(path, LIBRARY_SIZES[name], sha256)
        result.append(path)
    return result


def fetch(root: Path = ROOT) -> None:
    # Optional extraction readers are not imported by offline/native validation.
    try:
        import libarchive
        import olefile
    except ImportError as exc:
        raise ValueError('Explicit extraction needs libarchive-c, olefile and system libarchive; no installer is executed') from exc
    reference = 'build/references/vc8/kb971090/'
    package = within(root, reference + PACKAGE[0])
    if package.exists():
        verify(package, *PACKAGE[1:])
    else:
        with urllib.request.urlopen(URL, timeout=120) as response:
            write_verified(package, iter(lambda: response.read(1024 * 1024), b''), *PACKAGE[1:])
    patch = within(root, reference + PATCH[0])
    if patch.exists():
        verify(patch, *PATCH[1:])
    else:
        with libarchive.file_reader(str(package)) as archive:
            for entry in archive:
                if entry.pathname == PATCH[0]:
                    write_verified(patch, entry.get_blocks(), *PATCH[1:])
                    break
            else:
                raise ValueError('Original patch member missing from official package')
    cabinet = within(root, reference + CABINET[0])
    if cabinet.exists():
        verify(cabinet, *CABINET[1:])
    else:
        with olefile.OleFileIO(str(patch)) as compound:
            candidates = [name for name in compound.listdir() if compound.get_size(name) == CABINET[1]]
            if len(candidates) != 1:
                raise ValueError('Original patch cabinet is not uniquely identified')
            with compound.openstream(candidates[0]) as stream:
                write_verified(cabinet, iter(lambda: stream.read(1024 * 1024), b''), *CABINET[1:])
    found = set()
    with libarchive.file_reader(str(cabinet)) as archive:
        for entry in archive:
            name = MEMBERS.get(entry.pathname)
            if name is None:
                continue
            if name in found:
                raise ValueError('Duplicate original library member')
            filename, sha256 = LIBRARIES[name]
            write_verified(within(root, FOLDER + '/' + filename), entry.get_blocks(), LIBRARY_SIZES[name], sha256)
            found.add(name)
            # Do not decompress unrelated later patch members.
            if found == set(LIBRARIES):
                break
    if found != set(LIBRARIES):
        raise ValueError('Original library members missing')
    verified_libraries(root)


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--fetch', action='store_true', help='download and extract official reference files without executing/installing the update')
    args = parser.parse_args()
    try:
        if args.fetch:
            fetch()
        paths = verified_libraries()
        print(f'Original KB971090 runtime references verified: {len(paths)} archives; active toolchain unchanged')
        return 0
    except (OSError, ValueError) as exc:
        parser.exit(1, str(exc) + '\n')


if __name__ == '__main__':
    raise SystemExit(main())
