from __future__ import annotations

import importlib.util
from pathlib import Path
import sys
import unittest

ROOT = Path(__file__).resolve().parents[1]
SCRIPT = ROOT / "scripts" / "rank-exact-owner-review-callees.py"

spec = importlib.util.spec_from_file_location("exact_owner_callee_census", SCRIPT)
assert spec is not None and spec.loader is not None
census = importlib.util.module_from_spec(spec)
sys.modules[spec.name] = census
spec.loader.exec_module(census)


class ExactOwnerCalleeCensusTests(unittest.TestCase):
    def test_direct_external_edges_decode_calls_and_jumps(self) -> None:
        # call 0x2000; jmp 0x1010.  Both leave this seven-byte synthetic span.
        code = bytes.fromhex("e8fb0f0000eb09")
        self.assertEqual(
            census.direct_external_edges(code, 0x1000),
            [(0x1000, 0x2000, "call"), (0x1005, 0x1010, "jump")],
        )

    def test_direct_external_edges_ignore_internal_calls(self) -> None:
        # call the following RET, so the direct target remains inside the span.
        code = bytes.fromhex("e800000000c3")
        self.assertEqual(census.direct_external_edges(code, 0x1000), [])

    def test_candidate_owner_distinguishes_interior_and_gap(self) -> None:
        first = {"address": "0x00001000"}
        second = {"address": "0x00001020"}
        spans = [(0x1000, 0x1010, first), (0x1020, 0x1030, second)]
        self.assertIs(census.candidate_owner(spans, 0x1000), first)
        self.assertIs(census.candidate_owner(spans, 0x100F), first)
        self.assertIsNone(census.candidate_owner(spans, 0x1010))
        self.assertIsNone(census.candidate_owner(spans, 0x101F))
        self.assertIs(census.candidate_owner(spans, 0x1025), second)


if __name__ == "__main__":
    unittest.main()
