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

    def test_each_block_and_slot_across_map_wrap(self):
        # Four slots per block, four blocks: test every physical slot as a start
        # and cross each map boundary with a three-element live deque.
        for offset in range(16):
            for cursor in range(offset, offset + 4):
                case = (offset, 3, cursor)
                for native in (True, False):
                    with self.subTest(case=case, native=native):
                        self.assertEqual(observer.execute(self.images, native, *case),
                                         observer.expected(*case))

    def test_checked_invalid_parameter_boundary(self):
        # Stop before the CRT handler; do not assume it returns or emulate OS termination.
        for case, owner in (((3, 5, 9), "valid"), ((0, 0, 1), "valid"),
                            ((0, 4, 0), "null")):
            for native in (True, False):
                with self.subTest(case=case, owner=owner, native=native):
                    self.assertEqual(observer.execute(self.images, native, *case,
                        iterator_owner=owner, stop_at_invalid=True),
                        ("invalid_parameter", case[2]))

    def test_cursor_before_deque_offset_is_not_rejected_on_these_paths(self):
        # Observation only: a cursor before the live range is not a valid iterator.
        for native in (True, False):
            self.assertEqual(observer.execute(self.images, native, 3, 5, 2,
                                              stop_at_invalid=True), (0x2008, 3, 4))

    def test_cursor_increment_mutation_is_detected(self):
        case = (0, 4, 2)
        self.assertNotEqual(observer.execute(self.images, False, *case, mutate=True),
                            observer.expected(*case))

if __name__ == '__main__':
    unittest.main()
