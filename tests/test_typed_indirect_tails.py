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

    def test_indirect_call_records_pre_call_state_and_then_clobbers_volatile_registers(self):
        code = bytes.fromhex("8bf1 8b06 8b5008 8bce ffd2 8bce ffd2 c3")
        calls = receiver_tail_facts(code, 0x1000, {}, include_calls=True,
                                   allow_slot_unions=True)["register_indirect_calls"]
        self.assertEqual(calls[0]["possible_vtable_slots"], [8])
        self.assertTrue(calls[0]["ecx_is_entry_receiver"])
        self.assertEqual(calls[1]["possible_vtable_slots"], [])

    def test_finite_method_join_keeps_both_targets_without_choosing_one(self):
        code = bytes.fromhex("8bf1 8b06 85db 7405 8b5008 eb03 8b500c 8bce ffd2 c3")
        for unions, expected in ((False, []), (True, [8, 12])):
            call = receiver_tail_facts(code, 0x1000, {}, include_calls=True,
                                       allow_slot_unions=unions)["register_indirect_calls"][0]
            self.assertEqual(call["possible_vtable_slots"], expected)
            self.assertIsNone(call["slot_offset"])

    def test_unknown_join_path_cannot_become_a_finite_method_set(self):
        code = bytes.fromhex("8bf1 8b06 85db 7405 8b5008 eb02 31d2 8bce ffd2 c3")
        call = receiver_tail_facts(code, 0x1000, {}, include_calls=True,
                                   allow_slot_unions=True)["register_indirect_calls"][0]
        self.assertEqual(call["possible_vtable_slots"], [])

    def test_nonvolatile_method_pointer_does_not_preserve_the_volatile_this_argument(self):
        code = bytes.fromhex("8bf1 8b06 8b5808 ffd3 ffd3 c3")
        calls = receiver_tail_facts(code, 0x1000, {}, include_calls=True,
                                   allow_slot_unions=True)["register_indirect_calls"]
        self.assertEqual(calls[1]["possible_vtable_slots"], [8])
        self.assertFalse(calls[1]["ecx_is_entry_receiver"])

    def test_direct_tail_keeps_only_proved_receiver_adjustment(self):
        for code, expected in (("8bf1 8bce", 0), ("8bf1 8d4e04", 4),
                               ("8bf1 8d4efc", -4), ("31c9", None),
                               ("8bf1 e800000001", None)):
            flow = receiver_tail_facts(bytes.fromhex(code + " e900000001"), 0x1000, {},
                                       include_direct_tails=True)
            self.assertEqual(flow["direct_tail_exits"][0]["ecx_entry_receiver_offset"], expected)

    def test_adjusted_or_conflicting_receiver_does_not_acquire_primary_vtable_identity(self):
        # One path uses the entry receiver, the other a +4 subobject.
        code = bytes.fromhex("8bf1 85c0 7403 8d4e04 e900000001")
        fact = receiver_tail_facts(code, 0x1000, {}, include_direct_tails=True)
        self.assertIsNone(fact["direct_tail_exits"][0]["ecx_entry_receiver_offset"])
        code = bytes.fromhex("8d4904 8b01 8b4014 ffe0")
        tail = receiver_tail_facts(code, 0x1000, {}, include_direct_tails=True)["register_tail_exits"][0]
        self.assertIsNone(tail["slot_offset"])
        self.assertFalse(tail["ecx_is_entry_receiver"])

    def test_direct_tail_mode_is_opt_in_and_ignores_internal_jumps(self):
        self.assertNotIn("direct_tail_exits", receiver_tail_facts(bytes.fromhex("e900000001"), 0x1000, {}))
        self.assertEqual(receiver_tail_facts(bytes.fromhex("eb00 c3"), 0x1000, {},
                                           include_direct_tails=True)["direct_tail_exits"], [])

    def test_common_tail_epilogue_preserves_restores_around_final_store(self):
        for code in ("5f 5e 5b 83c404", "5f 8d4e04 5e 5b 83c404",
                     "5f d99ef4000000 8bce 5e 5b 83c404"):
            rows = audit.decode(bytes.fromhex(code + " ffe0"), 0x1000)
            self.assertEqual(audit.qualify_frame_epilogue(rows, rows[-1].address), 0x1000)

    def test_common_tail_cannot_hide_stack_writes_calls_or_missing_restores(self):
        for code in ("5f 5e 5b 83c408", "5f 5e 83c404", "5e 5b 83c404",
                     "5f 890424 5e 5b 83c404", "5f e800000001 5e 5b 83c404",
                     "5f 31c9 5e 5b 83c404"):
            rows = audit.decode(bytes.fromhex(code + " ffe0"), 0x1000)
            with self.subTest(code=code), self.assertRaises(ValueError):
                audit.qualify_frame_epilogue(rows, rows[-1].address)


if __name__ == "__main__":
    unittest.main()
