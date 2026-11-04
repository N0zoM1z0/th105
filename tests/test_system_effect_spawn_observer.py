"""Focused bounded tests for the scenario effect-spawn trace fixture."""
import importlib.util
from pathlib import Path
import sys
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))
spec = importlib.util.spec_from_file_location('spawn_observer', ROOT / 'scripts/audit-system-effect-spawn-observer.py')
observer = importlib.util.module_from_spec(spec)
spec.loader.exec_module(observer)

class SystemEffectSpawnObserverTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.native, cls.candidate = observer.code_bodies()

    def test_five_bounded_native_source_traces_agree(self):
        for case in observer.CASES:
            with self.subTest(case=case):
                self.assertEqual(observer.execute(self.native, *case), observer.execute(self.candidate, *case))

    def test_changed_mode_store_is_detected(self):
        body = bytearray(self.candidate)
        original = bytes.fromhex('89863c010000')
        self.assertEqual(body.count(original), 1)
        at = body.index(original)
        body[at + 2] = 0x40
        case = (1, 640.0, 480.0)
        self.assertNotEqual(observer.execute(self.native, *case), observer.execute(bytes(body), *case))

if __name__ == '__main__':
    unittest.main()
