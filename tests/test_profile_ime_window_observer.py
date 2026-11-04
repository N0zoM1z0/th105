"""Bounded IME window setup and mutation control."""
import importlib.util
from pathlib import Path
import sys
import unittest
ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))
spec = importlib.util.spec_from_file_location('ime_observer', ROOT / 'scripts/audit-profile-ime-window-observer.py')
observer = importlib.util.module_from_spec(spec)
spec.loader.exec_module(observer)

class ProfileImeWindowTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.native, cls.candidate = observer.code_bodies()

    def test_native_source_and_model(self):
        for case in observer.CASES:
            with self.subTest(case=case):
                self.assertEqual(observer.execute(self.native, *case), observer.expected(*case))
                self.assertEqual(observer.execute(self.candidate, *case), observer.expected(*case))

    def test_candidate_style_mutation_is_detected(self):
        body = bytearray(self.candidate)
        instruction = bytes.fromhex('80000000')
        self.assertEqual(body.count(instruction), 1)
        body[body.index(instruction)] = 0x81
        self.assertNotEqual(observer.execute(bytes(body), *observer.CASES[0]),
                            observer.expected(*observer.CASES[0]))

if __name__ == '__main__':
    unittest.main()
