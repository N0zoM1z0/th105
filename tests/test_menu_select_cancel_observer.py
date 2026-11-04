"""Compare native and real source cancel paths, with UI providers mocked."""
import importlib.util
from pathlib import Path
import struct
import sys
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))
spec = importlib.util.spec_from_file_location('menu_cancel', ROOT / 'scripts/audit-menu-select-cancel-observer.py')
observer = importlib.util.module_from_spec(spec)
spec.loader.exec_module(observer)


class MenuSelectCancelObserverTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.bodies = observer.code_bodies()

    def test_native_and_source_cancel_paths(self):
        for case in ((7,1,0,0), (0,0,1,0), (0,0,0,1), (0,0,0,0)):
            for body in self.bodies:
                with self.subTest(case=case):
                    self.assertEqual(observer.execute(body, *case), observer.expected(*case[1:]))

    def test_case_seven_must_not_play_cancel_event(self):
        source = bytearray(self.bodies[1])
        self.assertEqual(struct.unpack('<I', source[-4:])[0], 0x447f91)
        source[-4:] = struct.pack('<I', 0x447f87)
        case = (7,1,0,0)
        self.assertNotEqual(observer.execute(bytes(source), *case), observer.expected(*case[1:]))


if __name__ == '__main__':
    unittest.main()
