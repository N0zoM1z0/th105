from __future__ import annotations

import importlib.util
from pathlib import Path
import struct
import sys
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
SPEC = importlib.util.spec_from_file_location(
    "iku_payload_homes", ROOT / "scripts/audit-iku-payload-homes.py"
)
HOMES = importlib.util.module_from_spec(SPEC)
sys.modules[SPEC.name] = HOMES
SPEC.loader.exec_module(HOMES)


class IkuPayloadHomesTests(unittest.TestCase):
    def fixture(self, offsets, frame, *, unknown=False, gap=b""):
        # Synthetic caller input for provenance analysis; nothing is executed.
        code = bytearray.fromhex("558bec83e4f881ec")
        code.extend(struct.pack("<I", frame))
        code.extend(bytes.fromhex("535556578bf1"))
        code.extend(gap)
        for offset in offsets:
            code.extend(bytes((0x8B if unknown else 0x8D, 0x44, 0x24, offset)))
            code.extend(bytes.fromhex("6a03506a016a016a006a00682f0300008bce"))
            site = HOMES.START + len(code)
            code.extend(b"\xe8" + struct.pack("<i", 0x465190 - site - 5))
        code.extend(bytes.fromhex("5f5e5d5b8be55dc3"))
        return bytes(code)

    def test_distinct_buffers_have_distinct_frame_homes(self):
        result = HOMES.audit(self.fixture((32, 44), 40), {})
        self.assertEqual(result["distinct_payload_homes"], 2)
        self.assertEqual(set(result["home_sites"]), {"32", "44"})
        self.assertTrue(result["contiguous_12_byte_payload_cells"])
        self.assertEqual(result["unknown_spawn_payload_sites"], [])

    def test_reusing_one_buffer_retains_both_call_sites(self):
        result = HOMES.audit(self.fixture((32, 32), 28), {})
        self.assertEqual(result["distinct_payload_homes"], 1)
        self.assertEqual(len(result["home_sites"]["32"]), 2)
        self.assertTrue(result["contiguous_12_byte_payload_cells"])

    def test_unknown_pointer_does_not_become_a_stack_buffer(self):
        result = HOMES.audit(self.fixture((32,), 28, unknown=True), {})
        self.assertEqual(result["distinct_payload_homes"], 0)
        self.assertEqual(len(result["unknown_spawn_payload_sites"]), 1)
        self.assertFalse(result["contiguous_12_byte_payload_cells"])

    def test_wrong_callee_cleanup_fails_the_epilogue_check(self):
        cleanup = dict(HOMES.purge)
        cleanup[0x465190] = 0
        with self.assertRaisesRegex(ValueError, "epilogue stack differs"):
            HOMES.audit(self.fixture((32,), 28), {}, cleanup)

    def test_unreviewed_unreachable_bytes_fail_closed(self):
        with self.assertRaisesRegex(ValueError, "unreviewed unreachable"):
            HOMES.audit(self.fixture((32,), 28, gap=bytes.fromhex("eb0190")), {})

    def shared_fixture(self, second=bytes.fromhex("8d44242c")):
        original = self.fixture((32,), 40)
        first = bytes.fromhex("8d442420")
        code = bytearray(original[:18] + bytes((0x74, len(first) + 2))
                         + first + bytes((0xEB, len(second))) + second + original[22:])
        call = code.index(0xE8)
        struct.pack_into("<i", code, call + 1, 0x465190 - HOMES.START - call - 5)
        return bytes(code), {416: HOMES.START + 20, 565: HOMES.START + 26}

    def test_action_and_pointer_stay_coupled_at_the_shared_call(self):
        code, entries = self.shared_fixture()
        joined = HOMES.audit(code, {})
        self.assertEqual(list(joined["payload_sites"].values()), [[32, 44]])
        result = HOMES.audit(code, {}, action_entries=entries)
        self.assertEqual({row["action"]: row["homes"] for row in result["action_payload_sites"]},
                         {416: [32], 565: [44]})
        self.assertEqual(result["reachable_before_epilogue_restore"],
                         joined["reachable_before_epilogue_restore"])

    def test_crossing_another_entry_does_not_reset_an_existing_action(self):
        code, entries = self.shared_fixture()
        entries[565] = HOMES.START + 30  # Action416 also jumps into this shared tail.
        result = HOMES.audit(code, {}, action_entries=entries)
        self.assertEqual({row["action"]: row["homes"] for row in result["action_payload_sites"]},
                         {416: [32], 565: [44]})

    def test_two_pointer_paths_within_one_action_remain_a_set(self):
        code, entries = self.shared_fixture()
        result = HOMES.audit(code, {}, action_entries={416: HOMES.START + 18})
        self.assertEqual(len(result["action_payload_sites"]), 1)
        self.assertEqual(result["action_payload_sites"][0]["homes"], [32, 44])

    def test_two_actions_sharing_one_entry_receive_real_prologue_state(self):
        code = self.fixture((32,), 40)
        result = HOMES.audit(code, {}, action_entries={209: HOMES.START + 18, 221: HOMES.START + 18})
        self.assertEqual({row["action"]: row["homes"] for row in result["action_payload_sites"]},
                         {209: [32], 221: [32]})

    def test_unknown_and_null_stay_local_to_their_action(self):
        for second, is_unknown, is_null in ((bytes.fromhex("8b44242c"), True, False),
                                            (bytes.fromhex("31c09090"), False, True)):
            with self.subTest(second=second.hex()):
                code, entries = self.shared_fixture(second)
                result = HOMES.audit(code, {}, action_entries=entries)
                records = {row["action"]: row for row in result["action_payload_sites"]}
                self.assertEqual(records[416]["homes"], [32])
                self.assertFalse(records[416]["unknown"])
                self.assertEqual(records[565]["unknown"], is_unknown)
                self.assertEqual(records[565]["can_be_null"], is_null)

    def test_partitioning_cannot_hide_stack_disagreement_between_actions(self):
        code, entries = self.shared_fixture(bytes.fromhex("538d44242c"))
        with self.assertRaisesRegex(ValueError, "stack disagreement"):
            HOMES.audit(code, {}, action_entries=entries)
        with self.assertRaisesRegex(ValueError, "unqualified action entry"):
            HOMES.audit(self.fixture((32,), 40), {}, action_entries={416: HOMES.START + 2})
