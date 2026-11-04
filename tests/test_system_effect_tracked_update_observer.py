"""Bounded SystemEffect list update/prune fixture checks."""
import importlib.util
from pathlib import Path
import sys
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))
spec = importlib.util.spec_from_file_location('tracked_observer', ROOT / 'scripts/audit-system-effect-tracked-update-observer.py')
observer = importlib.util.module_from_spec(spec)
spec.loader.exec_module(observer)

class SystemEffectTrackedUpdateObserverTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.native, cls.candidate = observer.code_bodies()

    def test_five_bounded_list_traces(self):
        for states, flip in observer.CASES:
            with self.subTest(states=states, flip=flip):
                self.assertEqual(observer.execute(self.native, states, flip),
                                 observer.execute(self.candidate, states, flip))

    def test_changed_state_offset_is_detected(self):
        body = bytearray(self.candidate)
        # The target reads state at object +4; mutate the candidate's state test.
        pattern = bytes.fromhex('83790400')
        self.assertEqual(body.count(pattern), 1)
        body[body.index(pattern) + 2] = 12
        self.assertNotEqual(observer.execute(self.native, (1,), ()),
                            observer.execute(bytes(body), (1,), ()))

if __name__ == '__main__':
    unittest.main()
