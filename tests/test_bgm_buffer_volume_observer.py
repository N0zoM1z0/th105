"""Bounded null/resource and mutation checks for BGM buffer volume."""
import importlib.util
from pathlib import Path
import sys
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))
spec = importlib.util.spec_from_file_location('volume_observer', ROOT / 'scripts/audit-bgm-buffer-volume-observer.py')
observer = importlib.util.module_from_spec(spec)
spec.loader.exec_module(observer)

class BgmBufferVolumeObserverTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.native, cls.candidate = observer.code_bodies()

    def test_six_mock_com_traces(self):
        for present in (False, True):
            for value in (-10000, -1, 0):
                with self.subTest(present=present, value=value):
                    native, native_stack = observer.execute(self.native, True, present, value)
                    source, source_stack = observer.execute(self.candidate, False, present, value)
                    self.assertEqual(native, source)
                    self.assertEqual((native_stack, source_stack), (4, 8))

    def test_wrong_receiver_offset_changes_trace(self):
        body = bytearray(self.candidate)
        original = bytes.fromhex('83790400')
        self.assertEqual(body.count(original), 1)
        body[body.index(original) + 2] = 8
        native, _ = observer.execute(self.native, True, True, -1)
        source, _ = observer.execute(bytes(body), False, True, -1)
        self.assertNotEqual(native, source)

if __name__ == '__main__':
    unittest.main()
