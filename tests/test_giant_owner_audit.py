from __future__ import annotations

from pathlib import Path
import struct
import sys
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "scripts"))
from giant_owner_audit import (
    compare_owner_instructions, decode, paired_owners,
    reachable_boundary_audit, signature,
)


class GiantOwnerAuditTests(unittest.TestCase):
    BASE = 0x1000

    def compare(self, target: bytes, candidate: bytes) -> dict:
        pairs = [dict(name="entry", aliases=["entry"], target_offset=0,
                      candidate_offset=0, target_span=len(target), candidate_span=len(candidate))]
        return compare_owner_instructions(target, candidate, self.BASE, pairs, [], [])[0]

    def jump_signature(self, displacement: int, owners: dict[int, str], near: bool = False):
        raw = b"\xe9" + struct.pack("<i", displacement) if near else bytes((0xEB, displacement))
        insn = decode(raw, self.BASE)[0]
        return signature(insn, self.BASE, 32, owners,
                         {self.BASE + offset for offset in range(32)}, [])

    def test_opcode_not_algebraically_normalized(self):
        result = self.compare(bytes.fromhex("83e832c3"), bytes.fromhex("83c0cec3"))
        self.assertFalse(result["instruction_edge_identical"])
        self.assertNotIn("exact", result)

    def test_return_consumer_width_is_not_masked(self):
        self.assertFalse(self.compare(bytes.fromhex("84c0c3"), bytes.fromhex("85c0c3"))["instruction_edge_identical"])

    def test_sign_and_zero_extension_are_not_masked(self):
        self.assertFalse(self.compare(bytes.fromhex("0fb64604c3"), bytes.fromhex("0fbe4604c3"))["instruction_edge_identical"])

    def test_conditional_predicate_is_not_masked(self):
        self.assertFalse(self.compare(bytes.fromhex("7700c3"), bytes.fromhex("7500c3"))["instruction_edge_identical"])

    def test_relocated_internal_edge_retains_owner_identity(self):
        target = self.jump_signature(6, {0: "entry", 8: "case50"})
        candidate = self.jump_signature(10, {0: "entry", 12: "case50"})
        self.assertEqual(target, candidate)
        wrong_owner = self.jump_signature(10, {0: "entry", 12: "case162"})
        self.assertNotEqual(target, wrong_owner)

    def test_intra_owner_offset_is_significant(self):
        self.assertNotEqual(self.jump_signature(6, {0: "entry", 8: "case50"}),
                            self.jump_signature(7, {0: "entry", 8: "case50"}))

    def test_short_and_near_branches_remain_distinct(self):
        self.assertNotEqual(self.jump_signature(6, {0: "entry", 8: "case50"}),
                            self.jump_signature(3, {0: "entry", 8: "case50"}, near=True))

    def test_external_call_target_is_significant_but_site_may_move(self):
        def call(site, destination):
            insn = decode(b"\xe8" + struct.pack("<i", destination-site-5), site)[0]
            return signature(insn, self.BASE, 32, {0: "entry"}, {site}, [])
        self.assertEqual(call(0x1000, 0x5000), call(0x1007, 0x5000))
        self.assertNotEqual(call(0x1000, 0x5000), call(0x1007, 0x5001))

    def test_switch_address_requires_proved_table_identity(self):
        def table(address, ranges):
            insn = decode(b"\xff\x24\x85" + struct.pack("<I", address), self.BASE)[0]
            return signature(insn, self.BASE, 7, {0: "entry"}, {self.BASE}, ranges)
        target = table(0x2000, [(0x2000, 0x2008, "low.destinations")])
        self.assertEqual(target, table(0x3000, [(0x3000, 0x3008, "low.destinations")]))
        self.assertNotEqual(target, table(0x3000, []))
        self.assertNotEqual(target, table(0x3000, [(0x3000, 0x3008, "high.destinations")]))
        self.assertNotEqual(target, table(0x3004, [(0x3000, 0x3008, "low.destinations")]))

    def test_table_ranges_cannot_overlap(self):
        insn = decode(bytes.fromhex("ff248500200000"), self.BASE)[0]
        with self.assertRaisesRegex(ValueError, "overlapping"):
            signature(insn, self.BASE, 7, {0: "entry"}, {self.BASE},
                      [(0x2000, 0x2010, "one"), (0x2000, 0x2020, "two")])

    def test_instruction_entry_validation(self):
        insn = decode(bytes.fromhex("eb01"), self.BASE)[0]
        with self.assertRaisesRegex(ValueError, "enters an instruction"):
            signature(insn, self.BASE, 8, {0: "entry"}, {self.BASE, self.BASE+2, self.BASE+7}, [])

    def test_truncated_instruction_fails_closed(self):
        with self.assertRaisesRegex(ValueError, "incomplete"):
            decode(b"\xe8\x00", self.BASE)

    @staticmethod
    def row(target, candidate, region="low"):
        return dict(region=region, cases=[50], target_offset=target, target_span=1,
                    candidate_offsets=[candidate], candidate_span=1, split=False)

    def test_cross_region_alias_is_not_double_counted(self):
        pairs = paired_owners([self.row(2, 3), self.row(2, 3, "high")])
        self.assertEqual(len(pairs), 2)  # one physical destination plus entry
        self.assertEqual(pairs[1]["aliases"], ["low:50", "high:50"])

    def test_distinct_target_owners_cannot_be_merged(self):
        with self.assertRaisesRegex(ValueError, "merges"):
            paired_owners([self.row(2, 3), self.row(3, 3)])

    def test_split_target_owner_is_rejected(self):
        row = self.row(2, 3)
        row["split"] = True
        with self.assertRaisesRegex(ValueError, "unsplit"):
            paired_owners([row])

    def test_raw_traversal_does_not_treat_immediate_e8_as_call(self):
        result = reachable_boundary_audit(bytes.fromhex("b8e8000000c3"), self.BASE, {})
        self.assertEqual(result["reachable_bytes"], 6)
        self.assertEqual(result["direct_external_targets"], [])

    def test_raw_traversal_records_external_call_and_fallthrough(self):
        code = b"\xe8" + struct.pack("<i", 0x5000-self.BASE-5) + b"\xc3"
        result = reachable_boundary_audit(code, self.BASE, {})
        self.assertEqual(result["reachable_bytes"], len(code))
        self.assertEqual(result["direct_external_targets"][0]["address"], 0x5000)

    def test_raw_traversal_expands_only_known_switch_tables(self):
        code = bytes.fromhex("ff248500200000c3c3")
        result = reachable_boundary_audit(code, self.BASE, {0x2000: ("low", [0x1007, 0x1008])})
        self.assertEqual(result["reachable_bytes"], len(code))
        self.assertEqual(result["unresolved_indirect_exits"], [])
        unresolved = reachable_boundary_audit(code, self.BASE, {})
        self.assertEqual(unresolved["reachable_bytes"], 7)
        self.assertEqual(unresolved["unreached_ranges"], [[0x1007, 0x1009]])

    def test_register_indirect_exit_is_not_invented_as_candidate(self):
        result = reachable_boundary_audit(bytes.fromhex("ffe0c3"), self.BASE, {})
        self.assertEqual(len(result["unresolved_indirect_exits"]), 1)
        self.assertEqual(result["direct_external_targets"], [])
        self.assertEqual(result["unreached_ranges"], [[0x1002, 0x1003]])

    def test_reachable_middle_of_instruction_rejected(self):
        with self.assertRaisesRegex(ValueError, "not a callable instruction"):
            reachable_boundary_audit(bytes.fromhex("eb01b801000000c3"), self.BASE, {})

    def test_unterminated_callable_rejected(self):
        with self.assertRaisesRegex(ValueError, "not a callable instruction"):
            reachable_boundary_audit(b"\x90", self.BASE, {})

    def test_owner_extent_cannot_cut_instruction(self):
        pairs = [dict(name="entry", aliases=["entry"], target_offset=0,
                      candidate_offset=0, target_span=1, candidate_span=1)]
        with self.assertRaisesRegex(ValueError, "cuts an instruction|partition"):
            compare_owner_instructions(bytes.fromhex("89c0c3"), bytes.fromhex("89c0c3"), self.BASE, pairs, [], [])


    def test_empty_callable_rejected(self):
        with self.assertRaisesRegex(ValueError, "empty callable"):
            reachable_boundary_audit(b"", self.BASE, {})

    def test_unrepresented_callable_bytes_rejected(self):
        pairs = [dict(name="entry", aliases=["entry"], target_offset=0,
                      candidate_offset=0, target_span=1, candidate_span=1)]
        with self.assertRaisesRegex(ValueError, "partition"):
            compare_owner_instructions(b"\x90\xc3", b"\x90\xc3", self.BASE, pairs, [], [])


if __name__ == "__main__":
    unittest.main()
