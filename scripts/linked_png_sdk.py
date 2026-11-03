"""Build pinned PNG/zlib comparison providers; runtime equivalence is not claimed."""
import hashlib
import json
import os
from pathlib import Path
import re
import subprocess

SOURCE_LOCK_SHA256 = "e15ee4be7778db9c26ede6be8d55a8231ea4b3ef1dabdc16de4e6fb9cc72b4e4"
ZLIB_HEADER_LOCK_SHA256 = "545cdad1f307bd6b15fced5a12d5c1d6fbe2b0b03fc80c680c492b378ee03210"

FAMILIES = {
    'libpng': ('libpng-1.5.2', 'https://github.com/pnggroup/libpng',
               'dcc3505c7bd0660876fc80110f8e3581900a186a', 'v1.5.2'),
    'zlib': ('zlib-1.2.3', 'https://github.com/madler/zlib',
             'abf180a067223611620dd97dd5681df7c7fa7c9b', 'v1.2.3'),
}


def validate(unit):
    flag = unit.get('link_png_sdk', False)
    if type(flag) is not bool or flag and unit.get('link_runtime') != 'static':
        raise ValueError('PNG providers require an explicit boolean and static CRT')
    callback = unit.get('link_png_read_callback', False)
    if type(callback) is not bool or callback and flag is not True:
        raise ValueError('PNG callback proof requires the pinned PNG provider graph')


def verified_sources(root, manifest):
    if set(manifest) != set(FAMILIES):
        raise ValueError('PNG source families differ from the original version contract')
    result = []
    for name, (folder, repository, commit, tag) in FAMILIES.items():
        family = manifest[name]
        if any(family.get(k) != v for k, v in [('repository', repository), ('commit', commit), ('tag', tag)]):
            raise ValueError('PNG source repository/version identity differs')
        records = family.get('files')
        if not isinstance(records, list) or not records:
            raise ValueError('PNG source file manifest is missing')
        seen = set()
        for record in records:
            path = record.get('path', '')
            if (not (re.fullmatch(r'[A-Za-z0-9_]+(?:\.[ch])?', path) or name == 'libpng' and path == 'scripts/pnglibconf.h.prebuilt')
                    or path in seen or type(record.get('size')) is not int
                    or not re.fullmatch('[0-9a-f]{40}', record.get('git_blob_sha1', ''))
                    or not re.fullmatch('[0-9a-f]{64}', record.get('sha256', ''))):
                raise ValueError('invalid or duplicate PNG source record')
            seen.add(path)
            source = root / '.tools/upstream' / folder / path
            data = source.read_bytes()
            blob = b'blob ' + str(len(data)).encode() + b'\0' + data
            if (len(data) != record['size'] or hashlib.sha1(blob).hexdigest() != record['git_blob_sha1']
                    or hashlib.sha256(data).hexdigest() != record['sha256']):
                raise ValueError('upstream PNG source bytes differ: ' + str(source))
            result.append((name, source, record))
    return result


def verified_zlib_headers(root, manifest):
    expected = {'repository': 'https://github.com/madler/zlib',
                'commit': '9712272c78b9d9c93746d9c8e156a3728c65ca72', 'tag': 'v1.2.5'}
    if set(manifest) != {'repository', 'commit', 'tag', 'files'} or any(
            manifest.get(key) != value for key, value in expected.items()):
        raise ValueError('PNG zlib header identity differs')
    files = manifest['files']
    if not isinstance(files, list) or len(files) != 2 or {x.get('path') for x in files} != {'zlib.h', 'zconf.h'}:
        raise ValueError('PNG zlib header list differs')
    for record in files:
        path = root / '.tools/upstream/zlib-1.2.5-headers' / record['path']
        data = path.read_bytes()
        blob = b'blob ' + str(len(data)).encode() + b'\0' + data
        if (len(data) != record.get('size') or hashlib.sha1(blob).hexdigest() != record.get('git_blob_sha1')
                or hashlib.sha256(data).hexdigest() != record.get('sha256')):
            raise ValueError('PNG zlib header bytes differ: ' + str(path))
    return files


def materialize_png_config(png_root, *, generate=False):
    """Use only the byte-pinned official prebuilt configuration."""
    generated = png_root / 'pnglibconf.h'
    prebuilt = png_root / 'scripts/pnglibconf.h.prebuilt'
    if generate:
        generated.write_bytes(prebuilt.read_bytes())
    if not generated.is_file() or generated.read_bytes() != prebuilt.read_bytes():
        raise ValueError('PNG prebuilt configuration differs')


def inputs(unit, image, *, generate=False):
    import linked_pe as core
    validate(unit)
    if not unit.get('link_png_sdk'):
        return []
    root = core.ROOT
    lock = root / 'config/png-source-lock.json'
    if core.sha(lock) != SOURCE_LOCK_SHA256:
        raise ValueError("PNG source lock differs from the pinned upstream manifest")
    manifest = json.loads(lock.read_text())
    sources = verified_sources(root, manifest)
    header_lock = root / 'config/png-zlib-header-lock.json'
    if core.sha(header_lock) != ZLIB_HEADER_LOCK_SHA256:
        raise ValueError('PNG zlib header lock differs')
    zlib_headers = verified_zlib_headers(root, json.loads(header_lock.read_text()))
    materialize_png_config(root / '.tools/upstream/libpng-1.5.2', generate=generate)
    target = core.comparator()
    target.verify_target()
    data = target.TARGET.read_bytes()
    for marker in (b'1.5.2\0', b'1.2.5\0', b'deflate 1.2.3 Copyright 1995-2005 Jean-loup Gailly',
                   b'inflate 1.2.3 Copyright 1995-2005 Mark Adler'):
        if marker not in data:
            raise ValueError('canonical target PNG/zlib version evidence is absent')
    tools, _ = core.pinned_tools(True)
    librarian = tools / 'bin/lib.exe'
    import tomllib
    pin = tomllib.loads((root / 'config/tools.lock.toml').read_text())['msvc8_named_imports']['bin/lib.exe']
    if core.sha(librarian) != pin:
        raise ValueError('PNG archive librarian differs from the pinned VC8 tool')
    folder = Path(image).with_suffix('.png-sdk')
    env = os.environ.copy()
    env.update(WINEPREFIX=env.get('TH105_WINEPREFIX', str(root / '.tools/wine-msvc8')),
               WINEARCH='win32', WINEDEBUG='-all')
    for key in ('CL', '_CL_', 'LINK', '_LINK_', 'INCLUDE', 'LIB', 'LIBPATH'):
        env[key] = ''
    def win(path):
        return 'Z:' + str(Path(path).resolve()).replace('/', '\\')
    results = []
    for name, (version, _, _, _) in FAMILIES.items():
        dest = folder / name
        objects, commands, records = [], [], []
        if generate:
            dest.mkdir(parents=True, exist_ok=True)
        for family, source, record in sources:
            if family != name:
                continue
            records.append(record)
            if source.suffix != '.c':
                continue
            obj = dest / (source.stem + '.obj')
            objects.append(obj)
            command = ['wine', str(tools / 'bin/cl.exe'), '/nologo', '/c', '/TC', '/O2', '/MT', '/GS-',
                       '/I' + win(tools / 'include'), '/I' + win(tools / 'PlatformSDK/Include'),
                       '/I' + win(source.parent), '/I' + win(root / ('.tools/upstream/zlib-1.2.5-headers' if name == 'libpng' else '.tools/upstream/zlib-1.2.3')),
                       '/Fo' + win(obj), win(source)]
            commands.append(command)
            if generate:
                log = dest / (source.stem + '.log')
                with log.open('w') as stream:
                    done = subprocess.run(command, cwd=root, env=env, stdout=stream, stderr=subprocess.STDOUT)
                core.check_build_phase('PNG source ' + source.name, done.returncode, log)
        archive = folder / (name + '.lib')
        command = ['wine', str(librarian), '/nologo', '/OUT:' + win(archive)] + [win(p) for p in objects]
        commands.append(command)
        if generate:
            log = dest / 'archive.log'
            with log.open('w') as stream:
                done = subprocess.run(command, cwd=root, env=env, stdout=stream, stderr=subprocess.STDOUT)
            core.check_build_phase('PNG archive', done.returncode, log)
        if not archive.read_bytes().startswith(b'!<arch>\n'):
            raise ValueError('PNG provider is not a compiler-generated archive')
        result = {'family': name, 'path': str(archive.relative_to(root)), 'sha256': core.sha(archive),
                  'source_manifest_sha256': core.sha(lock), 'sources': records,
                  'objects': [{'path': str(p.relative_to(root)), 'sha256': core.sha(p)} for p in objects],
                  'commands': commands, 'librarian_sha256': pin}
        if name == 'libpng':
            result['zlib_header_lock_sha256'] = core.sha(header_lock)
            result['zlib_headers'] = zlib_headers
        results.append(result)
    return results


def callback_witness(unit, pe, functions, symbols, cil_owner, imports, known, read_target):
    """The actual game PNG read callback, with full code equality before pointer replay."""
    import linked_pe as core
    validate(unit)
    if not unit.get('link_png_read_callback'):
        return []
    symbol = '?CBitmapData_png_read@th105@@YAXPAUPngStruct@1@PAEK@Z'
    target, size = 0x0041A8E0, 33
    entries = symbols.get(symbol, [])
    if (len(entries) != 1 or entries[0][1].split()[-1:] != [cil_owner]
            or functions.get(entries[0][0]) != [(symbol, cil_owner)]):
        raise ValueError('PNG callback lacks unique source CIL code ownership')
    start = entries[0][0]
    anchor = known.get(symbol)
    if (anchor is None or anchor[0] != target or anchor[2] != frozenset({0})
            or anchor[3] != 'address' or read_target(target, len(anchor[1])) != anchor[1]):
        raise ValueError('PNG callback target anchor differs')
    section = pe.get_section_by_rva(start - core.IMAGE_BASE)
    if section is None or not section.Characteristics & 0x20000000:
        raise ValueError('PNG callback source is not executable code')
    raw = core.linked_body(pe, functions, start)
    def resolve(address):
        return core.resolve_linked_call(address, pe, functions, imports, {'_png_get_io_ptr': 0x0066BEF0})
    code, calls, refs = core.canonicalize(raw, start, target, [], resolve,
        (core.IMAGE_BASE, core.IMAGE_BASE + pe.OPTIONAL_HEADER.SizeOfImage), (0x400000, 0x710000))
    core.validate_body_relocations(pe, start, len(raw), refs)
    expected = read_target(target, size)
    if len(raw) != size or code != expected:
        raise ValueError('complete PNG read callback code is not canonical exact')
    digest = hashlib.sha256(code).hexdigest()
    return [{'kind': 'png_read_callback', 'source_address': start, 'address': target,
             'symbol': symbol, 'size': size, 'callback_exact': True,
             'canonical_sha256': digest, 'target_sha256': hashlib.sha256(expected).hexdigest(),
             'source_sha256': hashlib.sha256(raw).hexdigest(), 'calls': calls}]
