import importlib.util
from pathlib import Path
import struct
import sys
import unittest
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'scripts'))
spec = importlib.util.spec_from_file_location('design_color_tests', Path(__file__).resolve().parents[1] / 'scripts/audit-design-color-owner.py')
g = importlib.util.module_from_spec(spec)
spec.loader.exec_module(g)


class DesignColorTests(unittest.TestCase):
    def args(self):
        return [44, 4, [(4*i, 6, n) for i, (n, _) in enumerate(g.SLOTS)], bytes(40), struct.pack('<10I', *(a for _, a in g.SLOTS))]

    def test_complete_ten_slot_roles(self):
        g.check_table(*self.args())

    def test_wrong_load_role_rejected(self):
        args = self.args()
        args[2][4] = (16, 6, '?wrong_load')
        with self.assertRaises(ValueError):
            g.check_table(*args)

    def test_partial_table_or_hidden_addend_rejected(self):
        for index, value in [(0, 40), (1, 0), (3, b'\1' + bytes(39))]:
            args = self.args()
            args[index] = value
            with self.assertRaises(ValueError):
                g.check_table(*args)

    def test_every_native_slot_byte_checked(self):
        for i in range(40):
            args = self.args()
            data = bytearray(args[4])
            data[i] ^= 1
            args[4] = bytes(data)
            with self.assertRaises(ValueError):
                g.check_table(*args)


if __name__ == '__main__':
    unittest.main()
