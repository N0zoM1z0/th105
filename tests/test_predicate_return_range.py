import sys
from pathlib import Path
import struct
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'scripts'))
from predicate_return_range import prove_boolean_eax


class PredicateReturnRangeTests(unittest.TestCase):
    def test_both_full_width_boolean_returns(self):
        result = prove_boolean_eax(bytes.fromhex('7406b801000000c331c0c3'), 0x1000)
        self.assertEqual({value for values in result['returns'].values() for value in values}, {0, 1})

    def test_al_assignment_does_not_prove_high_bytes(self):
        with self.assertRaisesRegex(AssertionError, 'full-EAX'):
            prove_boolean_eax(bytes.fromhex('b001c3'), 0x1000)

    def test_non_boolean_full_width_value_is_rejected(self):
        with self.assertRaisesRegex(AssertionError, 'full-EAX'):
            prove_boolean_eax(bytes.fromhex('b800010000c3'), 0x1000)

    def test_one_bad_conditional_arm_is_rejected(self):
        with self.assertRaisesRegex(AssertionError, 'full-EAX'):
            prove_boolean_eax(bytes.fromhex('7406b800010000c331c0c3'), 0x1000)

    def test_normal_call_clobbers_the_proven_value(self):
        code = bytes.fromhex('b801000000e8') + struct.pack('<i', 0x2000 - 0x100A) + b'\xc3'
        with self.assertRaisesRegex(AssertionError, 'full-EAX'):
            prove_boolean_eax(code, 0x1000, (0x2000,))

    def test_external_jump_is_not_assumed_to_return_boolean(self):
        code = b'\xe9' + struct.pack('<i', 0x2000 - 0x1005)
        with self.assertRaisesRegex(AssertionError, 'control-flow exit'):
            prove_boolean_eax(code, 0x1000)


if __name__ == '__main__':
    unittest.main()
