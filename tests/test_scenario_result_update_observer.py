"""Bounded checks of the Scenario result update fixture."""
import importlib.util
from pathlib import Path
import sys
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))
spec = importlib.util.spec_from_file_location('result_observer', ROOT / 'scripts/audit-scenario-result-update-observer.py')
observer = importlib.util.module_from_spec(spec)
spec.loader.exec_module(observer)

class ScenarioResultUpdateObserverTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.native, cls.candidate = observer.code_bodies()

    def test_bounded_phase_traces(self):
        for case in observer.CASES:
            for wave in (0.0, 0.5):
                with self.subTest(case=case, wave=wave):
                    self.assertEqual(observer.execute(self.native, *case, wave),
                                     observer.execute(self.candidate, *case, wave))

    def test_inverted_active_gate_is_detected(self):
        body = bytearray(self.candidate)
        self.assertEqual(bytes(body[5:10]), bytes.fromhex('f9803f0075'))
        body[9] = 0x74
        case = (0, 0, 0)
        self.assertNotEqual(observer.execute(self.native, *case, 0.0),
                            observer.execute(bytes(body), *case, 0.0))

if __name__ == '__main__':
    unittest.main()
