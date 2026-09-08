from __future__ import annotations

import importlib.util
from pathlib import Path
import sys
import unittest

ROOT = Path(__file__).resolve().parents[1]
SCRIPT = ROOT / "scripts" / "rank-existing-object-review-symbols.py"
spec = importlib.util.spec_from_file_location("existing_object_review_symbols", SCRIPT)
assert spec is not None and spec.loader is not None
ranking = importlib.util.module_from_spec(spec)
sys.modules[spec.name] = ranking
spec.loader.exec_module(ranking)


class ExistingObjectReviewSymbolTests(unittest.TestCase):
    def test_parse_nm_text_symbol(self) -> None:
        row = ranking.parse_nm_line("build/foo.obj:00000000 0000014c T ?function@@YAXXZ")
        self.assertEqual(row["object"], "build/foo.obj")
        self.assertEqual(row["size"], 0x14C)
        self.assertEqual(row["name"], "?function@@YAXXZ")
        self.assertIsNone(ranking.parse_nm_line("build/foo.obj:00000000 00000004 r .rdata"))

    def test_rank_prefers_exact_size_then_small_delta(self) -> None:
        review = {
            0x1000: {"target": "0x00001000", "candidate_size": 10, "owner_count": 2, "edge_count": 3},
            0x2000: {"target": "0x00002000", "candidate_size": 20, "owner_count": 4, "edge_count": 5},
        }
        names = {"A": {0x1000}, "B": {0x2000}}
        emitted = {
            "A": [{"object": "a.obj", "size": 10, "name": "A"}],
            "B": [{"object": "b.obj", "size": 21, "name": "B"}],
        }
        rows = ranking.rank_rows(review, names, emitted)
        self.assertTrue(rows[0]["size_match"])
        self.assertEqual(rows[0]["target"], "0x00001000")
        self.assertEqual(rows[1]["size_delta"], 1)


if __name__ == "__main__":
    unittest.main()
