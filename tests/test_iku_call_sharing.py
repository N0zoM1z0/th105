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
