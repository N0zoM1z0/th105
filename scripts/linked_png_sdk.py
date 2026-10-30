"""Build original PNG/zlib sources as real C providers, never replacement game code."""
import hashlib
import json
import os
from pathlib import Path
import re
import subprocess

SOURCE_LOCK_SHA256 = "e1bd10b901bf5a1669456a18f00a2b9d6f62d330f0361d32e42a5cf2a2e1e9c1"

FAMILIES = {
    'libpng': ('libpng-1.2.5', 'https://github.com/pnggroup/libpng',
               '0cc2f95a9d87ae903a9842f1121384e3b2e5bbdc', 'v1.2.5'),
    'zlib': ('zlib-1.2.3', 'https://github.com/madler/zlib',
             'abf180a067223611620dd97dd5681df7c7fa7c9b', 'v1.2.3'),
}


def validate(unit):
    flag = unit.get('link_png_sdk', False)
    if type(flag) is not bool or flag and unit.get('link_runtime') != 'static':
        raise ValueError('PNG providers require an explicit boolean and static CRT')


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
            if (not re.fullmatch(r'[A-Za-z0-9_]+(?:\.[ch])?', path)
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
    target = core.comparator()
    target.verify_target()
    data = target.TARGET.read_bytes()
    for marker in (b'1.2.5\0', b'deflate 1.2.3 Copyright 1995-2005 Jean-loup Gailly',
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
                       '/I' + win(source.parent), '/I' + win(root / '.tools/upstream/zlib-1.2.3'),
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
        results.append({'family': name, 'path': str(archive.relative_to(root)), 'sha256': core.sha(archive),
                        'source_manifest_sha256': core.sha(lock), 'sources': records,
                        'objects': [{'path': str(p.relative_to(root)), 'sha256': core.sha(p)} for p in objects],
                        'commands': commands, 'librarian_sha256': pin})
    return results
