"""Bounded DirectInput error message forwarding."""
import importlib.util
from pathlib import Path
import sys
import unittest
ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))
spec = importlib.util.spec_from_file_location('dinput_error_observer', ROOT / 'scripts/audit-directinput-error-report-observer.py')
observer = importlib.util.module_from_spec(spec)
spec.loader.exec_module(observer)

class DirectInputErrorReportTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.native, cls.candidate = observer.code_bodies()

    def test_native_source_and_model(self):
        for window, message, result in observer.CASES:
            with self.subTest(window=window, message=message, result=result):
                expected = ([(window, message, 0x6d6b34, 0)], result, 4)
                self.assertEqual(observer.execute(self.native, True, window, message, result), expected)
                self.assertEqual(observer.execute(self.candidate, False, window, message, result), expected)

    def test_message_box_type_mutation_is_detected(self):
        body = bytearray(self.candidate)
        self.assertEqual(body.count(bytes.fromhex('6a00')), 1)
        body[body.index(bytes.fromhex('6a00')) + 1] = 1
        self.assertNotEqual(observer.execute(bytes(body), False, *observer.CASES[0]),
                            observer.execute(self.native, True, *observer.CASES[0]))

if __name__ == '__main__':
    unittest.main()
