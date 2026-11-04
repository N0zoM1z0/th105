"""Bounded package index constructor traces and mutation control."""
import importlib.util
from pathlib import Path
import sys
import unittest
ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))
spec = importlib.util.spec_from_file_location('package_node_observer', ROOT / 'scripts/audit-package-index-node-constructor-observer.py')
observer = importlib.util.module_from_spec(spec)
spec.loader.exec_module(observer)

class PackageIndexNodeConstructorTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.native, cls.candidate = observer.code_bodies()

    def test_native_source_and_model(self):
        for case in observer.CASES:
            with self.subTest(case=case):
                self.assertEqual(observer.execute(self.native, True, *case), observer.expected(*case))
                self.assertEqual(observer.execute(self.candidate, False, *case), observer.expected(*case))

    def test_cleared_next_pointer_mutation_is_detected(self):
        body = bytearray(self.candidate)
        instruction = bytes.fromhex('c7461000000000')
        self.assertEqual(body.count(instruction), 1)
        body[body.index(instruction) + 3] = 1
        self.assertNotEqual(observer.execute(bytes(body), False, *observer.CASES[0]),
                            observer.expected(*observer.CASES[0]))

if __name__ == '__main__':
    unittest.main()
