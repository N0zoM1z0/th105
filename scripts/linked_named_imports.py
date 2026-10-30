"""Generate and attest import metadata, never game code or replacement DLLs.

VC8 LIB's DEF stdcall spelling defaults to IMPORT_NAME_NOPREFIX. Select the
standard IMPORT_NAME_UNDECORATE policy for the actual undecorated DLL export.
Only that short-import header field changes; all other LIB output is retained.
"""
from pathlib import Path
import csv
import os
import struct
import subprocess
import tomllib

CONTRACTS = {
    '_D3DXCreateTexture@32': dict(dll='d3dx9_33.dll', name='D3DXCreateTexture',
                               target=0x68989C, target_iat=0x6C02B0),
    '_D3DXCreateEffect@36': dict(dll='d3dx9_33.dll', name='D3DXCreateEffect',
                              target=0x6898A2, target_iat=0x6C02B4),
}


def validate_contract(unit, occupied=()):
    mappings = unit.get('link_named_import_targets', [])
    if not isinstance(mappings, list):
        raise ValueError('named import mappings must be a list')
    seen = set(occupied)
    for mapping in mappings:
        symbol, sep, address = str(mapping).partition('=')
        if (not sep or symbol not in CONTRACTS or symbol in seen
                or address != '0x%08X' % CONTRACTS[symbol]['target']):
            raise ValueError('unknown, duplicate or incorrect named import contract')
        seen.add(symbol)


def converted_archive(raw, symbol, dll):
    """Validate metadata-only LIB output and change exactly one naming field."""
    if raw[:8] != b'!<arch>\n':
        raise ValueError('named import is not a COFF archive')
    offset, imports, descriptors = 8, [], []
    result = bytearray(raw)
    while offset < len(raw):
        header = raw[offset:offset + 60]
        if len(header) != 60 or header[58:] != b'`\n':
            raise ValueError('malformed import archive header')
        size = int(header[48:58].decode('ascii').strip())
        start, end = offset + 60, offset + 60 + size
        if end > len(raw):
            raise ValueError('truncated import archive')
        body = raw[start:end]
        member = header[:16].decode('ascii').strip()
        if member not in {'/', '//'}:
            if body[:4] == b'\0\0\xff\xff':
                expected = symbol.encode('ascii') + b'\0' + dll.encode('ascii') + b'\0'
                if len(body) < 20:
                    raise ValueError('short import header is truncated')
                h = struct.unpack_from('<HHHHIIHH', body)
                if (h[:4] != (0, 0xffff, 0, 0x14c)
                        or h[5:] != (len(expected), 0, 8) or body[20:] != expected):
                    raise ValueError('wrong import symbol, DLL, machine or naming policy')
                imports.append(start)
                struct.pack_into('<H', result, start + 18, 12)
            else:
                if len(body) < 20:
                    raise ValueError('truncated import descriptor')
                machine, count, _, pointer, symbols, optional, _ = struct.unpack_from('<HHIIIHH', body)
                if machine != 0x14c or optional or count not in (2, 3) or pointer + 18 * symbols > len(body):
                    raise ValueError('invalid import descriptor COFF')
                names = []
                for i in range(count):
                    if 20 + 40 * (i + 1) > len(body):
                        raise ValueError('truncated import descriptor sections')
                    s = struct.unpack_from('<8sIIIIIIHHI', body, 20 + 40 * i)
                    name = s[0].rstrip(b'\0')
                    if (name not in {b'.debug$S', b'.idata$2', b'.idata$3', b'.idata$4', b'.idata$5', b'.idata$6'}
                            or s[9] & 0x20000020 or s[4] + s[3] > len(body)
                            or (s[7] and s[5] + 10 * s[7] > len(body))):
                        raise ValueError('executable or invalid import descriptor section')
                    names.append(name)
                descriptors.append(names)
        offset = end + (size & 1)
    if (offset != len(raw) or len(imports) != 1 or descriptors != [
            [b'.debug$S', b'.idata$2', b'.idata$6'],
            [b'.debug$S', b'.idata$3'],
            [b'.debug$S', b'.idata$5', b'.idata$4']]):
        raise ValueError('unexpected import library member inventory')
    return bytes(result)


def contracts(unit, tools, *, generate=False):
    import linked_pe as linked
    from workflow_manifest import repository_path
    validate_contract(unit)
    if not unit.get('link_named_import_targets'):
        return []
    root = linked.ROOT
    tool = tools / 'bin/lib.exe'
    pin = tomllib.loads((root / 'config/tools.lock.toml').read_text())['msvc8_named_imports']['bin/lib.exe']
    if linked.sha(tool) != pin:
        raise ValueError('import librarian differs from pinned VC8 LIB')
    c = linked.comparator()
    c.verify_target()
    game = linked.pefile.PE(str(c.TARGET))
    identities = {e.address: (d.dll.decode('ascii').lower(), linked.import_identity(e))
                  for d in game.DIRECTORY_ENTRY_IMPORT for e in d.imports}
    with (root / 'config/functions.csv').open(newline='') as stream:
        ledger = {int(r['address'], 0): r for r in csv.DictReader(stream)}
    with (root / 'config/function-origins.csv').open(newline='') as stream:
        origins = {int(r['address'], 0): r for r in csv.DictReader(stream)}
    folder = repository_path(unit['object'], output=True).with_suffix('.imports')
    environment = os.environ.copy()
    environment.update(WINEPREFIX=environment.get('TH105_WINEPREFIX', str(root / '.tools/wine-msvc8')),
                       WINEARCH='win32', WINEDEBUG='-all')
    for key in ('CL', '_CL_', 'LINK', '_LINK_', 'INCLUDE', 'LIB', 'LIBPATH'):
        environment[key] = ''
    def win(path):
        return subprocess.run(['winepath', '-w', str(path)], cwd=root, env=environment,
                              check=True, capture_output=True, text=True).stdout.strip()
    results = []
    for mapping in unit['link_named_import_targets']:
        symbol = mapping.split('=')[0]
        contract = CONTRACTS[symbol]
        address, iat = contract['target'], contract['target_iat']
        section = game.get_section_by_rva(address - game.OPTIONAL_HEADER.ImageBase)
        data_section = game.get_section_by_rva(iat - game.OPTIONAL_HEADER.ImageBase)
        origin = origins.get(address, {})
        if (ledger.get(address, {}).get('size') != '6' or section is None
                or not section.Characteristics & 0x20000000 or data_section is None
                or data_section.Characteristics & 0x20000000
                or (origin.get('origin'), origin.get('disposition')) != ('import_thunk', 'exclude')
                or identities.get(iat) != (contract['dll'], contract['name'])
                or c.target_bytes(address, 6) != b'\xff\x25' + struct.pack('<I', iat)):
            raise ValueError('named target is not its canonical import thunk and IAT')
        stem = Path(contract['dll']).stem + '_' + contract['name']
        definition = folder / (stem + '.def')
        original = folder / (stem + '_lib.lib')
        output = folder / (stem + '_named.lib')
        text = 'LIBRARY ' + contract['dll'] + '\nEXPORTS\n ' + symbol[1:] + '\n'
        command = ['wine', str(tool), '/nologo', '/machine:x86',
                   '/def:' + win(definition), '/out:' + win(original)]
        if generate:
            folder.mkdir(parents=True, exist_ok=True)
            definition.write_text(text)
            log = folder / (stem + '.log')
            with log.open('w') as stream:
                done = subprocess.run(command, cwd=root, env=environment, stdout=stream, stderr=subprocess.STDOUT)
            linked.check_build_phase('import-library', done.returncode, log)
            output.write_bytes(converted_archive(original.read_bytes(), symbol, contract['dll']))
        if (definition.read_text() != text or output.read_bytes() !=
                converted_archive(original.read_bytes(), symbol, contract['dll'])):
            raise ValueError('generated named import metadata changed')
        results.append(dict(contract, symbol=symbol, library=str(output),
                            map_owner=output.stem + ':' + contract['dll'],
                            library_sha256=linked.sha(output), original_sha256=linked.sha(original),
                            definition_sha256=linked.sha(definition), librarian_sha256=pin,
                            generate_command=command, name_policy='IMPORT_NAME_UNDECORATE'))
    return results
