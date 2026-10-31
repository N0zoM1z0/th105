import hashlib
import importlib.util
from pathlib import Path
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))
import upstream_vc8_runtime as runtime
spec = importlib.util.spec_from_file_location('runtime_extract', ROOT / 'scripts/extract-msvc-library-object.py')
extract = importlib.util.module_from_spec(spec)
spec.loader.exec_module(extract)


class UpstreamRuntimeTests(unittest.TestCase):
    def test_archive_selection_is_explicit_and_preserves_default(self):
        root = Path('/tmp/reference-fixture')
        path, libraries = extract.archive_configuration(root=root)
        self.assertEqual(path, root / '.tools/msvc80-sp1/lib')
        self.assertEqual(libraries, extract.LIBRARIES)
        path, libraries = extract.archive_configuration('vc8-kb971090', root)
        self.assertEqual(path, root / runtime.FOLDER)
        self.assertEqual(libraries, runtime.LIBRARIES)
        with self.assertRaises(ValueError):
            extract.archive_configuration('arbitrary-location', root)

    def test_original_bytes_are_checked_before_publication(self):
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / 'original.lib'
            data = b'original archive fixture'
            sha = hashlib.sha256(data).hexdigest()
            runtime.write_verified(path, [data[:5], data[5:]], len(data), sha)
            self.assertEqual(path.read_bytes(), data)
            runtime.verify(path, len(data), sha)

    def test_altered_existing_archive_is_never_replaced(self):
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / 'original.lib'
            path.write_bytes(b'altered!')
            with self.assertRaises(ValueError):
                runtime.write_verified(path, [b'original'], 8, hashlib.sha256(b'original').hexdigest())
            self.assertEqual(path.read_bytes(), b'altered!')

    def test_partial_or_excess_download_is_not_published(self):
        for blocks in ([b'tiny'], [b'too much data']):
            with tempfile.TemporaryDirectory() as tmp:
                path = Path(tmp) / 'original.lib'
                with self.assertRaises(ValueError):
                    runtime.write_verified(path, blocks, 8, hashlib.sha256(b'original').hexdigest())
                self.assertFalse(path.exists())
                self.assertEqual(list(Path(tmp).iterdir()), [])

    def test_reference_paths_cannot_escape_root(self):
        with tempfile.TemporaryDirectory() as tmp:
            with self.assertRaises(ValueError):
                runtime.within(Path(tmp), '../outside')


if __name__ == '__main__':
    unittest.main()
