from pathlib import Path
import importlib.util
import sys
import unittest

SCRIPTS = Path(__file__).resolve().parents[1] / "scripts"
sys.path.insert(0, str(SCRIPTS))
from typed_indirect_tails import receiver_tail_facts

spec = importlib.util.spec_from_file_location("common_tail_test", SCRIPTS / "audit-common-fighter-indirect-tails.py")
audit = importlib.util.module_from_spec(spec)
spec.loader.exec_module(audit)


class TypedIndirectTailTests(unittest.TestCase):
    def facts(self, code, switches=None):
        return receiver_tail_facts(bytes.fromhex(code), 0x1000, switches or {})["register_tail_exits"]

    def test_entry_receiver_reaches_virtual_slot(self):
        tail = self.facts("8bf1 8b16 8b4214 ffe0")[0]
        self.assertEqual(tail["slot_offset"], 20)
        self.assertTrue(tail["ecx_is_entry_receiver"])

    def test_call_discards_volatile_receiver_provenance(self):
        tail = self.facts("8bf1 e800000001 8b16 8b4214 ffe0")[0]
        self.assertEqual(tail["slot_offset"], 20)
        self.assertFalse(tail["ecx_is_entry_receiver"])

    def test_reload_from_preserved_receiver_after_call(self):
        tail = self.facts("8bf1 e800000001 8bce 8b16 8b4214 ffe0")[0]
        self.assertTrue(tail["ecx_is_entry_receiver"])

    def test_disagreeing_control_flow_paths_do_not_qualify(self):
        tail = self.facts("8bf1 85c0 7402 31c9 8b16 8b4214 ffe0")[0]
        self.assertFalse(tail["ecx_is_entry_receiver"])

    def test_non_vptr_load_cannot_supply_virtual_identity(self):
        tail = self.facts("8bf1 8b5604 8b4214 ffe0")[0]
        self.assertIsNone(tail["slot_offset"])

    def test_partial_register_overwrite_invalidates_function_pointer(self):
        tail = self.facts("8bf1 8b16 8b4214 b001 ffe0")[0]
        self.assertIsNone(tail["slot_offset"])

    def test_validated_switch_visits_both_receiver_paths(self):
        code = "8bf1 ff248500200000 31c9 eb00 8b16 8b4214 ffe0"
        tail = self.facts(code, {0x2000: [0x1009, 0x100D]})[0]
        self.assertFalse(tail["ecx_is_entry_receiver"])
        self.assertEqual(self.facts(code), [])

    def test_loop_clobbers_receiver_on_both_successors(self):
        tail = self.facts("8bf1 e2fe 8b16 8b4214 ffe0")[0]
        self.assertFalse(tail["ecx_is_entry_receiver"])

    def test_domain_disagreement_and_empty_domain_never_qualify(self):
        tails = self.facts("8bf1 8b16 8b4214 ffe0")
        for tables in ({"a": 0x2000, "b": 0x3000}, {}):
            result = audit.qualify_domain(lambda address: address + 4, tables, tails)
            self.assertFalse(result[0]["qualified_for_reviewed_domain"])
            self.assertIsNone(result[0]["inferred_target"])

    def test_agreeing_domain_qualifies_only_its_observed_target(self):
        result = audit.qualify_domain(lambda address: 0x4000, {"a": 0x2000, "b": 0x3000},
                                     self.facts("8bf1 8b16 8b4214 ffe0"))
        self.assertTrue(result[0]["qualified_for_reviewed_domain"])
        self.assertEqual(result[0]["observed_domain_targets"], [0x4000])
        self.assertEqual(result[0]["inferred_target"], 0x4000)

    def test_only_proven_receiver_and_expected_slot_use_the_domain(self):
        for code in ("8bf1 8b16 8b4208 ffe0", "8bf1 31c9 8b16 8b4214 ffe0"):
            result = audit.qualify_domain(lambda address: self.fail("unproven slot was read"),
                                         {"a": 0x2000}, self.facts(code))
            self.assertFalse(result[0]["qualified_for_reviewed_domain"])

    def test_truncation_and_instruction_interior_edges_fail(self):
        for code in ("0f", "ebff"):
            with self.assertRaises(ValueError):
                self.facts(code)


if __name__ == "__main__":
    unittest.main()
