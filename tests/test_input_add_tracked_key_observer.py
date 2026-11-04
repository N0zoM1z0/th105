"""Bounded duplicate and append checks for tracked input keys."""
import importlib.util
from pathlib import Path
import sys
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))
spec = importlib.util.spec_from_file_location('key_observer', ROOT / 'scripts/audit-input-add-tracked-key-observer.py')
observer = importlib.util.module_from_spec(spec)
spec.loader.exec_module(observer)

class InputAddTrackedKeyObserverTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.native, cls.candidate = observer.code_bodies()

    def test_bounded_key_traces(self):
        for values, key in observer.CASES:
            with self.subTest(values=values, key=key):
                target = observer.execute(self.native, values, key)
                expected = bytes(values if key in values else (*values, key))
                self.assertEqual(target, observer.execute(self.candidate, values, key))
                self.assertEqual(target, (expected, 8))

    def test_duplicate_gate_mutation_is_detected(self):
        body = bytearray(self.candidate)
        self.assertEqual(body[0x59:0x61], bytes.fromhex('8a073a442418745d'))
        body[0x5f] = 0x75
        self.assertNotEqual(observer.execute(self.native, (5,), 5),
                            observer.execute(bytes(body), (5,), 5))

if __name__ == '__main__':
    unittest.main()
