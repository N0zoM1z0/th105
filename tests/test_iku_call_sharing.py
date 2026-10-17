from __future__ import annotations

import importlib.util
from pathlib import Path
import sys
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
SPEC = importlib.util.spec_from_file_location(
    "iku_call_sharing", ROOT / "scripts/audit-iku-call-sharing.py"
)
SHARING = importlib.util.module_from_spec(SPEC)
sys.modules[SPEC.name] = SHARING
SPEC.loader.exec_module(SHARING)


class IkuCallSharingTests(unittest.TestCase):
    def packet(self, calls, unknown=()):
        return {
            "calls": [
                {"site": site, "target": "0x465190", "actions": actions}
                for site, actions, _ in calls
            ],
            "payload_provenance": {
                "payload_sites": {hex(site): cells for site, _, cells in calls},
                "unknown_spawn_payload_sites": list(unknown),
                "distinct_payload_homes": len(
                    {cell for _, _, cells in calls for cell in cells}
                ),
            },
        }

    def test_shared_home_sets_use_independent_constraints_not_sorted_pairing(self):
        target = self.packet(
            [
                (0x1000, [416], [32]),
                (0x1010, [416, 417], [32, 44]),
                (0x1020, [417], [44]),
            ]
        )
        candidate = self.packet(
            [
                (0x2000, [416], [92]),
                (0x2010, [416, 417], [80, 92]),
                (0x2020, [417], [80]),
            ]
        )
        result = SHARING.correlate_homes(target, candidate)
        self.assertEqual(
            result["possible_target_to_candidate_homes"], {"32": [92], "44": [80]}
        )
        self.assertTrue(result["bijection_under_ordinal_pairing"])

    def test_shared_home_sets_without_independent_evidence_remain_ambiguous(self):
        target = self.packet([(0x1000, [416, 417], [32, 44])])
        candidate = self.packet([(0x2000, [416, 417], [80, 92])])
        result = SHARING.correlate_homes(target, candidate)
        self.assertEqual(
            result["possible_target_to_candidate_homes"],
            {"32": [80, 92], "44": [80, 92]},
        )
        self.assertFalse(result["bijection_under_ordinal_pairing"])

    def partition_packet(self, site, homes):
        packet = self.packet([(site, [416, 417], homes)])
        packet["payload_provenance"].update(
            partitioned_by_incoming_action=True,
            action_payload_sites=[
                {"action": action, "site": site, "homes": [home], "unknown": False, "can_be_null": False}
                for action, home in zip((416, 417), homes)
            ],
        )
        return packet

    def test_action_pointer_relation_resolves_a_reversed_shared_pair(self):
        target = self.partition_packet(0x1000, [32, 44])
        candidate = self.partition_packet(0x2000, [92, 80])
        result = SHARING.correlate_homes(target, candidate, action_partitioned=True)
        self.assertEqual(result["possible_target_to_candidate_homes"], {"32": [92], "44": [80]})
        self.assertTrue(result["bijection_under_ordinal_pairing"])
        self.assertEqual(result["issues"], [])

    def test_missing_unknown_and_null_partitions_keep_uncertainty(self):
        for condition in ("missing", "unknown", "null"):
            target = self.partition_packet(0x1000, [32, 44])
            candidate = self.partition_packet(0x2000, [92, 80])
            records = candidate["payload_provenance"]["action_payload_sites"]
            if condition == "missing":
                records.pop()
            elif condition == "unknown":
                records[1]["unknown"] = True
            else:
                records[1]["can_be_null"] = True
            result = SHARING.correlate_homes(target, candidate, action_partitioned=True)
            with self.subTest(condition=condition):
                self.assertEqual(result["possible_target_to_candidate_homes"], {"32": [92]})
                self.assertFalse(result["bijection_under_ordinal_pairing"])
                self.assertEqual(result["issues"][0]["action"], 417)

    def test_partition_mode_rejects_unpartitioned_or_duplicate_evidence(self):
        target = self.partition_packet(0x1000, [32, 44])
        candidate = self.partition_packet(0x2000, [92, 80])
        candidate["payload_provenance"]["partitioned_by_incoming_action"] = False
        with self.assertRaisesRegex(ValueError, "partitioned prologue"):
            SHARING.correlate_homes(target, candidate, action_partitioned=True)
        candidate["payload_provenance"]["partitioned_by_incoming_action"] = True
        records = candidate["payload_provenance"]["action_payload_sites"]
        records.append(records[0])
        with self.assertRaisesRegex(ValueError, "duplicate action/payload"):
            SHARING.correlate_homes(target, candidate, action_partitioned=True)

    def test_unknown_missing_and_inconsistent_home_evidence_cannot_form_a_bijection(
        self,
    ):
        target = self.packet([(0x1000, [416], [32])])
        candidate = self.packet([(0x2000, [416], [80])], unknown=(0x2000,))
        self.assertFalse(
            SHARING.correlate_homes(target, candidate)[
                "bijection_under_ordinal_pairing"
            ]
        )
        self.assertFalse(
            SHARING.correlate_homes(target, self.packet([]))[
                "bijection_under_ordinal_pairing"
            ]
        )
        target = self.packet([(0x1000, [416], [32]), (0x1010, [417], [32])])
        candidate = self.packet([(0x2000, [416], [80]), (0x2010, [417], [92])])
        result = SHARING.correlate_homes(target, candidate)
        self.assertEqual(result["possible_target_to_candidate_homes"], {"32": []})
        self.assertFalse(result["bijection_under_ordinal_pairing"])

    def rows(self, chunks):
        # Synthetic CFG input only; no fixture bytes are executed or accepted.
        return {
            row.address: row
            for address, code in chunks.items()
            for row in SHARING.decode(bytes.fromhex(code), address)
        }

    def test_shared_tail_keeps_both_origins_through_a_loop_and_call(self):
        rows = self.rows(
            {
                0x1000: "eb0e",
                0x1007: "eb07",
                0x1010: "e800000000",
                0x1015: "7505",
                0x1017: "ebf7",
                0x101C: "c3",
            }
        )
        origins = SHARING.propagate_origins(rows, {416: 0x1000, 565: 0x1007}, {})
        self.assertEqual(origins[0x1010], {416, 565})
        self.assertEqual(origins[0x101C], {416, 565})
        self.assertEqual(origins[0x1000], {416})

    def test_return_does_not_flow_into_the_next_action(self):
        rows = self.rows({0x1000: "c3c3"})
        origins = SHARING.propagate_origins(rows, {2: 0x1000, 4: 0x1001}, {})
        self.assertEqual(origins[0x1000], {2})
        self.assertEqual(origins[0x1001], {4})

    def test_compressed_table_edges_merge_and_unknown_edges_fail(self):
        rows = self.rows({0x1000: "ff248500200000", 0x1010: "c3", 0x1020: "c3"})
        origins = SHARING.propagate_origins(
            rows, {208: 0x1000}, {0x2000: [0x1010, 0x1020]}
        )
        self.assertEqual(origins[0x1010], {208})
        self.assertEqual(origins[0x1020], {208})
        with self.assertRaisesRegex(ValueError, "unreviewed indirect"):
            SHARING.propagate_origins(rows, {208: 0x1000}, {})
        with self.assertRaisesRegex(ValueError, "unknown instruction"):
            SHARING.propagate_origins(rows, {208: 0x1000}, {0x2000: [0x1001]})
