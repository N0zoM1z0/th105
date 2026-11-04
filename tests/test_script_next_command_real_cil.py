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

    def test_repeated_reads_until_end(self):
        for offset, count in ((0, 4), (14, 3)):
            expected = [observer.expected(offset, count, cursor)
                        for cursor in range(offset, offset + count + 1)]
            for native in (True, False):
                with self.subTest(offset=offset, native=native):
                    self.assertEqual(observer.execute(self.images, native, offset, count,
                                                      offset, steps=count + 1), expected)

    def test_cursor_increment_mutation_is_detected(self):
        case = (0, 4, 2)
        self.assertNotEqual(observer.execute(self.images, False, *case, mutate=True),
                            observer.expected(*case))

if __name__ == '__main__':
    unittest.main()
