"""Script cursor execution through native helper and real linked CIL."""
import importlib.util
from pathlib import Path
import sys
import unittest
ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))
spec = importlib.util.spec_from_file_location('script_cursor_cil', ROOT / 'scripts/audit-script-next-command-real-cil.py')
observer = importlib.util.module_from_spec(spec)
spec.loader.exec_module(observer)

class ScriptNextCommandRealCilTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.images = observer.prepare()

    def test_native_cil_and_model(self):
        for case in observer.CASES:
            with self.subTest(case=case):
                self.assertEqual(observer.execute(self.images, True, *case), observer.expected(*case))
                self.assertEqual(observer.execute(self.images, False, *case), observer.expected(*case))

    def test_cursor_increment_mutation_is_detected(self):
        case = (0, 4, 2)
        self.assertNotEqual(observer.execute(self.images, False, *case, mutate=True),
                            observer.expected(*case))

if __name__ == '__main__':
    unittest.main()
