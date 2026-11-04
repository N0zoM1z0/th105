"""Bounded raw keyboard/gamepad counter checks."""
import importlib.util
from pathlib import Path
import sys
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))
spec = importlib.util.spec_from_file_location('input_observer', ROOT / 'scripts/audit-input-raw-counters-observer.py')
observer = importlib.util.module_from_spec(spec)
spec.loader.exec_module(observer)

class InputRawCountersObserverTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.native, cls.candidate = observer.code_bodies()

    def test_bounded_input_counters(self):
        for case in observer.cases():
            with self.subTest(case=case):
                native = observer.execute(self.native, *case)
                self.assertEqual(native, observer.execute(self.candidate, *case))
                self.assertEqual(native, observer.expected(case))

    def test_changed_axis_threshold_is_detected(self):
        body = bytearray(self.candidate)
        # Change one native-style -500 threshold to -499 in the source body.
        pattern = bytes.fromhex('0cfeffff')
        self.assertGreaterEqual(body.count(pattern), 1)
        body[body.index(pattern)] = 0x0d
        case = (0, -500, 0, (), True, False)
        self.assertNotEqual(observer.execute(self.native, *case),
                            observer.execute(bytes(body), *case))

if __name__ == '__main__':
    unittest.main()
