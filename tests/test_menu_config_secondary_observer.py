"""Bounded tests for menu-config secondary selection and gauge fixture."""
import importlib.util
from pathlib import Path
import sys
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))
spec = importlib.util.spec_from_file_location('config_observer', ROOT / 'scripts/audit-menu-config-secondary-observer.py')
observer = importlib.util.module_from_spec(spec)
spec.loader.exec_module(observer)

class MenuConfigSecondaryObserverTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.native, cls.candidate = observer.code_bodies()

    def test_bounded_config_traces(self):
        for primary in observer.PRIMARIES:
            for value in observer.VALUES:
                with self.subTest(primary=primary, value=value):
                    self.assertEqual(observer.execute(self.native, primary, value),
                                     observer.execute(self.candidate, primary, value))

    def test_changed_upper_clamp_is_detected(self):
        body = bytearray(self.candidate)
        self.assertEqual(body[0x8d:0x92], bytes.fromhex('b814000000'))
        body[0x8e] = 19
        self.assertNotEqual(observer.execute(self.native, 1, 105),
                            observer.execute(bytes(body), 1, 105))

if __name__ == '__main__':
    unittest.main()
