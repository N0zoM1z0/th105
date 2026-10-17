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
