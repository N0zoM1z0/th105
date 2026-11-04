"""Native/source post-pipeline branch comparison with mocked transition."""
import importlib.util
import itertools
from pathlib import Path
import sys
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))
spec = importlib.util.spec_from_file_location('arcade_post', ROOT / 'scripts/audit-arcade-post-pipeline-observer.py')
observer = importlib.util.module_from_spec(spec)
spec.loader.exec_module(observer)


class ArcadePostPipelineObserverTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.bodies = observer.code_bodies()

    def test_flag_counter_and_wrap_matrix(self):
        cases = itertools.product((0, 1), (0, 1), (0, 1, 255), (0, 1, 255), (0, 255))
        for case in cases:
            for body in self.bodies:
                with self.subTest(case=case):
                    self.assertEqual(observer.execute(body, case), observer.expected(case))

    def test_inverted_pending_gate_is_detected(self):
        body = bytearray(self.bodies[1])
        self.assertEqual(body[0xb:0xd], bytes.fromhex('746d'))
        body[0xb] = 0x75
        case = (1, 0, 0, 0, 0)
        self.assertNotEqual(observer.execute(bytes(body), case), observer.expected(case))


if __name__ == '__main__':
    unittest.main()
