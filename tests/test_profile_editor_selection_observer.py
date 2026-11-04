"""Bounded profile selection and mutation control."""
import importlib.util
from pathlib import Path
import sys
import unittest
ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))
spec = importlib.util.spec_from_file_location('selection_observer', ROOT / 'scripts/audit-profile-editor-selection-observer.py')
observer = importlib.util.module_from_spec(spec)
spec.loader.exec_module(observer)

class ProfileEditorSelectionTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.native, cls.candidate = observer.code_bodies()

    def test_native_source_and_model(self):
        for case in observer.CASES:
            with self.subTest(case=case):
                self.assertEqual(observer.execute(self.native, *case), observer.expected(*case))
                self.assertEqual(observer.execute(self.candidate, *case), observer.expected(*case))

    def test_text_width_mutation_is_detected(self):
        body = bytearray(self.candidate)
        instruction = bytes.fromhex('6800020000')
        self.assertEqual(body.count(instruction), 2)
        body[body.index(instruction) + 2] = 3
        self.assertNotEqual(observer.execute(bytes(body), *observer.CASES[5]),
                            observer.expected(*observer.CASES[5]))

if __name__ == '__main__':
    unittest.main()
