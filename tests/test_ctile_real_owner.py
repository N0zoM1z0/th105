import importlib.util
from pathlib import Path
import struct
import sys
import unittest
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'scripts'))
spec = importlib.util.spec_from_file_location('ctile_tests', Path(__file__).resolve().parents[1] / 'scripts/audit-ctile-real-owner.py')
g = importlib.util.module_from_spec(spec)
spec.loader.exec_module(g)


class CTileTableTests(unittest.TestCase):
    def args(self):
        return [20, 4, [(4*i, 6, name) for i, (name, _) in enumerate(g.SLOTS)], bytes(16), struct.pack('<4I', *(at for _, at in g.SLOTS))]

    def test_complete_table(self):
        g.check_table(*self.args())

    def test_no_fifth_virtual_slot(self):
        args = self.args()
        args[0] += 4
        with self.assertRaises(ValueError):
            g.check_table(*args)

    def test_wrong_inherited_role(self):
        args = self.args()
        args[2][1], args[2][2] = args[2][2], args[2][1]
        with self.assertRaises(ValueError):
            g.check_table(*args)

    def test_native_slot_mutations(self):
        for i in range(16):
            args = self.args()
            bad = bytearray(args[4])
            bad[i] ^= 1
            args[4] = bytes(bad)
            with self.assertRaises(ValueError):
                g.check_table(*args)

    def test_no_hidden_source_addend(self):
        args = self.args()
        args[3] = b'\1' + bytes(15)
        with self.assertRaises(ValueError):
            g.check_table(*args)


if __name__ == '__main__':
    unittest.main()
