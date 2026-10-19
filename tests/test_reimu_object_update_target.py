import importlib.util
from pathlib import Path
import unittest


ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location(
    "reimu_object_update_target_test",
    ROOT / "scripts/audit-reimu-object-update-target.py",
)
facts = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(facts)


class ReimuObjectTargetTests(unittest.TestCase):
    def test_e8_inside_fld1_is_not_a_call(self):
        # FLD1; three NOPs; CALL back to FLD1; RET.
        rows = facts.decode(bytes.fromhex("d9 e8 90 90 90 e8 f6 ff ff ff c3"), 0x1000)
        self.assertEqual(facts.direct_calls(rows), {0x1000: [0x1005]})

    def test_unreviewed_indirect_jump_fails_closed(self):
        rows = facts.decode(bytes.fromhex("ff e0"), 0x1000)
        with self.assertRaisesRegex(ValueError, "unreviewed indirect jump"):
            facts.graph(rows, {})

    def test_branch_into_instruction_operand_fails_closed(self):
        rows = facts.decode(bytes.fromhex("eb ff"), 0x1000)
        with self.assertRaisesRegex(ValueError, "owned instruction"):
            facts.graph(rows, {})

    def test_table_target_must_be_an_instruction_start(self):
        rows = facts.decode(bytes.fromhex("ff 24 85 00 20 00 00 c3"), 0x1000)
        with self.assertRaisesRegex(ValueError, "owned instruction"):
            facts.graph(rows, {0x1000: [0x1001]})

    def test_reachability_does_not_absorb_skipped_alignment(self):
        rows = facts.decode(bytes.fromhex("eb 01 90 c3"), 0x1000)
        self.assertEqual(
            facts.reachable(facts.graph(rows, {}), 0x1000), {0x1000, 0x1003}
        )

    @unittest.skipUnless(
        (ROOT / "resources/th105.exe").is_file(), "requires canonical target"
    )
    def test_complete_current_root_and_remote_calls(self):
        packet = facts.audit()
        self.assertEqual(packet["owned_bytes"], 46128)
        self.assertEqual(packet["reachable_instructions"], 10670)
        self.assertEqual(len(packet["switches"]), 22)
        self.assertEqual(packet["direct_call_sites"], 404)
        calls = {row["target"]: row["sites"] for row in packet["calls"]}
        self.assertNotIn("0x4c611d", calls)
        self.assertIn("0x4a1612", calls["0x53cbc0"])
        self.assertEqual(packet["returns"], 68)


if __name__ == "__main__":
    unittest.main()
