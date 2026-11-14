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
            f = root / '.tools/upstream/libpng-1.5.2' / first['path']
            f.parent.mkdir(parents=True)
            f.write_bytes(b'wrong upstream contents')
            with self.assertRaises(ValueError): png.verified_sources(root, manifest)

    def test_png_zlib_header_lock_fails_closed(self):
        path = Path(__file__).resolve().parents[1] / 'config/png-zlib-header-lock.json'
        self.assertEqual(hashlib.sha256(path.read_bytes()).hexdigest(), png.ZLIB_HEADER_LOCK_SHA256)
        manifest = json.loads(path.read_text())
        with tempfile.TemporaryDirectory() as folder:
            root = Path(folder)
            header_dir = root / '.tools/upstream/zlib-1.2.5-headers'
            header_dir.mkdir(parents=True)
            fake = copy.deepcopy(manifest)
            for record in fake['files']:
                data = ('test ' + record['path']).encode()
                (header_dir / record['path']).write_bytes(data)
                record['size'] = len(data)
                record['sha256'] = hashlib.sha256(data).hexdigest()
                record['git_blob_sha1'] = hashlib.sha1(b'blob ' + str(len(data)).encode() + b'\0' + data).hexdigest()
            self.assertEqual(len(png.verified_zlib_headers(root, fake)), 2)
            (header_dir / 'zlib.h').write_bytes(b'tampered')
            with self.assertRaises(ValueError):
                png.verified_zlib_headers(root, fake)
            fake['files'][0]['path'] = '../outside.h'
            with self.assertRaises(ValueError):
                png.verified_zlib_headers(root, fake)

    def test_generated_configuration_must_match_prebuilt(self):
        with tempfile.TemporaryDirectory() as folder:
            root = Path(folder)
            (root / 'scripts').mkdir()
            (root / 'scripts/pnglibconf.h.prebuilt').write_bytes(b'official config')
            with self.assertRaises(ValueError):
                png.materialize_png_config(root)
            png.materialize_png_config(root, generate=True)
            png.materialize_png_config(root)
            (root / 'pnglibconf.h').write_bytes(b'changed config')
            with self.assertRaises(ValueError):
                png.materialize_png_config(root)

    def test_disabled_provider_never_reads_or_builds(self):
        self.assertEqual(png.inputs({}, Path('missing.dll')), [])

if __name__ == '__main__': unittest.main()
