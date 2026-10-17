"""Reject signed, overwritten, or bypassed unsigned-conversion certificates."""
import importlib.util
from pathlib import Path
import struct
import sys
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
spec = importlib.util.spec_from_file_location("iku_float_proof_test", ROOT / "scripts/audit-iku-random-float-tails.py")
proof = importlib.util.module_from_spec(spec)
spec.loader.exec_module(proof)
BASE = 0x620000
CORRECTION = b"\xd8\x05" + struct.pack("<I", proof.CORRECTION)


def call(target, offset):
    return b"\xe8" + struct.pack("<i", target - BASE - offset - 5)


def remainder(divide=b"\xf7\xf1", load=b"\xdb\x44\x24\x20"):
    # MT(); EDX=0; ECX=200; unsigned DIV; TEST/store/FILD; JGE over FADD.
    code = (call(0x4066B0, 0) + b"\x31\xd2\xb9\xc8\0\0\0" + divide
            + b"\x85\xd2\x89\x54\x24\x20" + load + b"\x7d\x06" + CORRECTION)
    return proof.decode(code, BASE)


def selector(subtract=0, overwrite=False):
    code = b"\x68" + struct.pack("<I", 400 if subtract else 30)
    if overwrite:
        code += b"\xd9\x1c\x24"  # FSTP [ESP] destroys the pushed argument.
    code += call(0x4067D0, len(code))
    if subtract:
        code += b"\x2d" + struct.pack("<I", subtract)
    code += b"\x85\xc0\x89\x44\x24\x14\xdb\x44\x24\x14\x7d\x06" + CORRECTION
    return proof.decode(code, BASE)


def certify(rows, incoming=None, literal=2.0 ** 32):
    return proof.prove_fixup(rows, len(rows) - 1, incoming or {},
                             lambda address, size: struct.pack("<f", literal))


class IkuUnsignedFloatProofTests(unittest.TestCase):
    def test_unsigned_remainder_guarantees_nonnegative_signed_conversion_input(self):
        fact = certify(remainder())
        self.assertEqual(fact["converted_unsigned_intervals"], [[0, 199]])
        self.assertIs(fact["guard_always_taken"], True)

    def test_unsigned_subtraction_keeps_the_feasible_high_interval(self):
        fact = certify(selector(subtract=200))
        self.assertEqual(fact["converted_unsigned_intervals"], [[0, 200], [4294967096, 4294967295]])
        self.assertIsNone(fact["guard_always_taken"])

    def test_signed_division_and_different_stack_load_cannot_inherit_the_proof(self):
        for rows in (remainder(divide=b"\xf7\xf9"), remainder(load=b"\xdb\x44\x24\x24")):
            with self.subTest(rows=rows), self.assertRaises(ValueError):
                certify(rows)

    def test_alternate_entry_cannot_bypass_the_range_definition(self):
        rows = remainder()
        for target in (rows[1].address, rows[-2].address, rows[-1].address):
            with self.subTest(target=target), self.assertRaises(ValueError):
                certify(rows, {target: {BASE - 100}})

    def test_overwritten_selector_argument_is_rejected(self):
        with self.assertRaisesRegex(ValueError, "overwritten"):
            certify(selector(overwrite=True))

    def test_changed_correction_and_truncated_producer_are_rejected(self):
        with self.assertRaisesRegex(ValueError, "literal"):
            certify(remainder(), literal=1.0)
        with self.assertRaisesRegex(ValueError, "truncated"):
            certify(remainder()[-3:])

    def test_selector_endpoint_is_inclusive_and_large_limits_do_not_prove_sign(self):
        self.assertEqual(proof.selector_bound(400), 400)
        self.assertEqual(proof.selector_bound(30), 30)
        for limit in (0, -1, 2**32, 0x80000000):
            with self.subTest(limit=limit), self.assertRaises(ValueError):
                proof.selector_bound(limit)


if __name__ == "__main__":
    unittest.main()
