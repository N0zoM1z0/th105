"""Reject source dispatches whose bound no longer protects the table index."""

from __future__ import annotations

import importlib.util
from pathlib import Path
import struct
import unittest

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location(
    "world_sharing", ROOT / "scripts/audit-reimu-object-world-sharing.py"
)
sharing = importlib.util.module_from_spec(spec)
spec.loader.exec_module(sharing)


def fixture(before=b"", after=b"", guard=0x77):
    start = sharing.native.S
    prefix = bytes.fromhex("0fbf863e01000083f801") + before
    length = len(prefix) + 2 + len(after) + 7 + 1
    code = prefix + bytes((guard, len(after) + 7)) + after
    code += bytes.fromhex("ff2485") + struct.pack("<I", start + length) + b"\xc3"
    return (
        sharing.graphs.decode(code, start),
        code + struct.pack("<II", start + length - 1, start + length - 1),
        length,
    )


class WorldSwitchGuardTests(unittest.TestCase):
    def test_bounded_dispatch_has_two_reviewed_destinations(self):
        rows, code, metadata = fixture()
        result = sharing.reviewed_source_switches(rows, code, metadata)
        self.assertEqual(len(result), 1)
        self.assertEqual(next(iter(result.values()))["count"], 2)

    def test_partial_index_write_before_guard_invalidates_bound(self):
        rows, code, metadata = fixture(before=bytes.fromhex("b0ff"))
        with self.assertRaisesRegex(ValueError, "clobbered before guard"):
            sharing.reviewed_source_switches(rows, code, metadata)

    def test_partial_index_write_after_guard_invalidates_dispatch(self):
        rows, code, metadata = fixture(after=bytes.fromhex("b0ff"))
        with self.assertRaisesRegex(ValueError, "checked index"):
            sharing.reviewed_source_switches(rows, code, metadata)

    def test_call_after_guard_cannot_silently_clobber_the_index(self):
        rows, code, metadata = fixture(after=bytes.fromhex("e800000000"))
        with self.assertRaisesRegex(ValueError, "control transfer"):
            sharing.reviewed_source_switches(rows, code, metadata)

    def test_lower_unsigned_guard_does_not_bound_the_upper_index(self):
        rows, code, metadata = fixture(guard=0x72)
        with self.assertRaisesRegex(ValueError, "unsigned switch guard"):
            sharing.reviewed_source_switches(rows, code, metadata)


if __name__ == "__main__":
    unittest.main()
