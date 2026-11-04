"""Bounded result-menu refresh observations and a mutation control."""
import importlib.util
from pathlib import Path
import sys
import unittest
ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))
spec = importlib.util.spec_from_file_location('result_refresh_observer', ROOT / 'scripts/audit-result-character-refresh-observer.py')
observer = importlib.util.module_from_spec(spec)
spec.loader.exec_module(observer)

class ResultCharacterRefreshTests(unittest.TestCase):
    def test_native_source_and_model(self):
        for args in observer.CASES:
            with self.subTest(args=args):
                self.assertEqual(observer.run(observer.native, *args), observer.expected(*args))
                self.assertEqual(observer.run(observer.cand, *args), observer.expected(*args))

    def test_tint_mutation_is_detected(self):
        body = bytearray(observer.cand)
        color = bytes.fromhex('808080ff')
        self.assertEqual(body.count(color), 1)
        body[body.index(color)] = 0x81
        args = observer.CASES[0]
        self.assertNotEqual(observer.run(bytes(body), *args), observer.expected(*args))

if __name__ == '__main__':
    unittest.main()
