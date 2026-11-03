"""Pinned external-source provenance; no native toolchain needed."""
import copy
import hashlib
import json
from pathlib import Path
import sys
import tempfile
import unittest
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'scripts'))
import linked_png_sdk as png
import png_version_evidence as version

class PngProviderTests(unittest.TestCase):
    def test_flag_and_locked_upstream_identity(self):
        png.validate({})
        png.validate({'link_png_sdk': True, 'link_runtime': 'static'})
        for unit in ({'link_png_sdk': 1}, {'link_png_sdk': True},
                     {'link_png_sdk': True, 'link_runtime': 'import'}):
            with self.assertRaises(ValueError): png.validate(unit)
        path = Path(__file__).resolve().parents[1] / 'config/png-source-lock.json'
        self.assertEqual(hashlib.sha256(path.read_bytes()).hexdigest(), png.SOURCE_LOCK_SHA256)
        manifest = json.loads(path.read_text())
        with tempfile.TemporaryDirectory() as folder:
            root = Path(folder)
            bad = copy.deepcopy(manifest)
            bad['libpng']['commit'] = '0' * 40
            with self.assertRaises(ValueError): png.verified_sources(root, bad)
            bad = copy.deepcopy(manifest)
            bad['libpng']['files'][0]['path'] = '../outside.c'
            with self.assertRaises(ValueError): png.verified_sources(root, bad)
            first = manifest['libpng']['files'][0]
            f = root / '.tools/upstream/libpng-1.2.5' / first['path']
            f.parent.mkdir(parents=True)
            f.write_bytes(b'wrong upstream contents')
            with self.assertRaises(ValueError): png.verified_sources(root, manifest)

    def test_native_version_roles_fail_closed(self):
        values = {0x66BF00: bytes.fromhex('b8046e6d00c3'),
                  0x6D6E04: b'1.5.2\0',
                  0x41A97E: bytes.fromhex('68046e6d00'),
                  0x41A983: bytes.fromhex('e8d8532500'),
                  0x66CF02: bytes.fromhex('e8f9efffff'),
                  0x66CF10: bytes.fromhex('3a1430'),
                  0x66D037: bytes.fromhex('68f0b06c0050'),
                  0x6CB0F0: b'1.2.5\0',
                  0x66D03D: bytes.fromhex('e87ea9ffff')}
        def read(address, length):
            return values[address][:length]
        self.assertEqual(version.audit(read)['native_png_header'], '1.5.2')
        for address in values:
            original = values[address]
            values[address] = bytes([original[0] ^ 1]) + original[1:]
            with self.assertRaises(ValueError):
                version.audit(read)
            values[address] = original

    def test_disabled_provider_never_reads_or_builds(self):
        self.assertEqual(png.inputs({}, Path('missing.dll')), [])

if __name__ == '__main__': unittest.main()
