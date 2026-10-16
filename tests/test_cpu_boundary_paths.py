"""The execution probe must never stop at an unrelated or ambiguous join."""
import importlib.util
from pathlib import Path
import sys
import unittest

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location("cpu_boundary_paths", ROOT / "scripts/audit-cpu-boundary-paths.py")
probe = importlib.util.module_from_spec(spec)
sys.modules[spec.name] = probe
spec.loader.exec_module(probe)


class CpuBoundaryJoinTests(unittest.TestCase):
    # Synthetic test instructions, never linked into reconstruction code.
    JOIN = bytes.fromhex("66399e66070000bd07000000")

    def test_unique_instruction_pair(self):
        self.assertEqual(probe.policy_join(b"\x90" + self.JOIN + b"\xc3", 0x1000), 0x1001)

    def test_duplicate_join_is_rejected(self):
        with self.assertRaises(ValueError):
            probe.policy_join(self.JOIN * 2, 0x1000)

    def test_other_receiver_register_is_rejected(self):
        with self.assertRaises(ValueError):
            probe.policy_join(bytes.fromhex("66399f66070000bd07000000"), 0x1000)

    def test_other_counter_is_rejected(self):
        with self.assertRaises(ValueError):
            probe.policy_join(bytes.fromhex("66399e64070000bd07000000"), 0x1000)

    def test_other_policy_constant_is_rejected(self):
        with self.assertRaises(ValueError):
            probe.policy_join(bytes.fromhex("66399e66070000bd08000000"), 0x1000)

    def test_instruction_pair_must_be_adjacent(self):
        with self.assertRaises(ValueError):
            probe.policy_join(self.JOIN[:7] + b"\x90" + self.JOIN[7:], 0x1000)

    def test_incomplete_decode_is_rejected(self):
        with self.assertRaises(ValueError):
            probe.policy_join(self.JOIN + b"\x0f", 0x1000)


if __name__ == "__main__":
    unittest.main()
