"""Actual native and CIL insertion paths with modeled low-level allocation."""
import importlib.util
from pathlib import Path
import sys
import unittest
ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))
spec = importlib.util.spec_from_file_location('real_growth', ROOT / 'scripts/audit-input-add-key-real-growth.py')
observer = importlib.util.module_from_spec(spec)
spec.loader.exec_module(observer)

class InputAddKeyRealGrowthTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.images = observer.prepare()

    def test_native_cil_and_model(self):
        for values, key in observer.CASES:
            with self.subTest(values=values, key=key):
                self.assertEqual(observer.run(self.images, True, values, key), observer.expected(values, key))
                self.assertEqual(observer.run(self.images, False, values, key), observer.expected(values, key))

    def test_repeated_growth_and_duplicates(self):
        keys = (2, 4, 2, 9, 0, 255, 8, 1)
        expected = observer.expected_series(keys)
        for native in (True, False):
            with self.subTest(native=native):
                self.assertEqual(observer.run(self.images, native, (), keys), expected)

    def test_many_growth_steps_and_duplicate_positions(self):
        keys = tuple(range(100)) + (0, 50, 99, 100)
        expected = observer.expected_series(keys)
        for native in (True, False):
            with self.subTest(native=native):
                self.assertEqual(observer.run(self.images, native, (), keys), expected)

    def test_duplicate_gate_mutation_is_detected(self):
        self.assertNotEqual(observer.run(self.images, False, (5,), 5, mutate=True),
                            observer.expected((5,), 5))

if __name__ == '__main__':
    unittest.main()
