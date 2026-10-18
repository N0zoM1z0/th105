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


@unittest.skipUnless(importlib.util.find_spec("unicorn"), "Unicorn is unavailable")
class CpuX87InputTests(unittest.TestCase):
    def make_probe(self, leave_live=False):
        class EntryProbe(probe.CpuProbe):
            def step(self, uc, address):
                if address == self.address:
                    self.entry_state = tuple(uc.reg_read(register) for register in (
                        self.reg.UC_X86_REG_FPSW, self.reg.UC_X86_REG_FPTAG, self.reg.UC_X86_REG_FPCW))
                    if leave_live:
                        uc.reg_write(self.reg.UC_X86_REG_FPTAG, 0xFFFC)
                super().step(uc, address)

        # Diagnostic-only bytes: stop before the synthetic join executes.
        code = CpuBoundaryJoinTests.JOIN + b"\xc3"
        instance = EntryProbe(bytes(0x1000), code, len(code))
        instance.engine.reg_write(instance.reg.UC_X86_REG_FPSW, 3 << 11)
        instance.engine.reg_write(instance.reg.UC_X86_REG_FPTAG, 0x5555)
        instance.initial = instance.engine.context_save()
        return instance

    def test_case_entry_resets_both_top_and_occupied_tags(self):
        instance = self.make_probe()
        instance.run((201, 200, 0, 1, 3, 0, 0x27F))
        self.assertEqual(instance.entry_state, (0, 0xFFFF, 0x27F))

    def test_zero_top_with_an_occupied_slot_is_rejected(self):
        instance = self.make_probe(leave_live=True)
        with self.assertRaisesRegex(ValueError, "live x87"):
            instance.run((201, 200, 0, 1, 3, 0, 0x27F))


if __name__ == "__main__":
    unittest.main()
