import importlib.util
from pathlib import Path
import struct
import sys
import unittest
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'scripts'))
spec = importlib.util.spec_from_file_location('select_owner_tests', Path(__file__).resolve().parents[1] / 'scripts/audit-select-owner-layout.py')
g = importlib.util.module_from_spec(spec)
spec.loader.exec_module(g)


class SelectOwnerTests(unittest.TestCase):
    def args(self):
        return [32, 4, [(i*4, 6, n) for i, (n, _) in enumerate(g.SLOTS)], bytes(28), struct.pack('<7I', *(a for _, a in g.SLOTS))]

    def test_seven_virtual_roles(self):
        g.check_table(*self.args())

    def test_six_slot_surrogate_rejected(self):
        args = self.args()
        args[0] = 28
        with self.assertRaises(ValueError):
            g.check_table(*args)

    def test_wrong_flow_declaration_rejected(self):
        args = self.args()
        args[2][-1] = (24, 6, '?wrong_flow')
        with self.assertRaises(ValueError):
            g.check_table(*args)

    def test_every_native_slot_byte_checked(self):
        for i in range(28):
            args = self.args()
            data = bytearray(args[4])
            data[i] ^= 1
            args[4] = bytes(data)
            with self.assertRaises(ValueError):
                g.check_table(*args)


if __name__ == '__main__':
    unittest.main()
