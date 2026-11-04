"""Exercise native and source timer branches to their mocked helper boundary."""
import importlib.util
import itertools
from pathlib import Path
import sys
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))
spec = importlib.util.spec_from_file_location('battle_timer', ROOT / 'scripts/audit-battle-event-timer-observer.py')
observer = importlib.util.module_from_spec(spec)
spec.loader.exec_module(observer)


class BattleEventTimerObserverTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.bodies = observer.code_bodies()

    def test_threshold_and_overflow_matrix(self):
        cases = itertools.product((1, 2), (0, 16), (3, 16),
            (-32768, -1, 0, 1, 498, 499, 998, 999, 32767), (0, 1))
        for case in cases:
            for body in self.bodies:
                with self.subTest(case=case):
                    self.assertEqual(observer.execute(body, case), observer.expected(case))

    def test_changed_phase_gate_is_detected(self):
        body = bytearray(self.bodies[1])
        self.assertEqual(body[3:10], bytes.fromhex('83be8800000002'))
        body[9] = 3
        case = (2, 0, 3, 1, 1)
        self.assertNotEqual(observer.execute(bytes(body), case), observer.expected(case))


if __name__ == '__main__':
    unittest.main()
