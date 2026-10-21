from __future__ import annotations

import importlib.util
from pathlib import Path
import sys
import unittest
from unittest import mock
import xml.etree.ElementTree as ET


ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
SPEC = importlib.util.spec_from_file_location("th105_progress_svg", ROOT / "scripts/progress.py")
assert SPEC is not None and SPEC.loader is not None
progress = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(progress)


class ProgressSvgTests(unittest.TestCase):
    def render_fixture(self, pending: bool, *, remote_exact: bool = True) -> ET.Element:
        functions = [
            {"address": "0x1000", "size": "60"},
            {"address": "0x2000", "size": "10"},
            {"address": "0x3000", "size": "1000"},
            {"address": "0x4000", "size": "500"},
        ]
        rows = {
            "functions.csv": functions,
            "function-origins.csv": [
                {"address": row["address"], "disposition": disposition}
                for row, disposition in zip(
                    functions, ("authored", "authored", "review" if pending else "exclude", "exclude")
                )
            ],
            "matches.csv": [{"address": "0x1000", "size": "60"}],
        }
        ownership = {0x1000: {
            "owned_bytes": 90, "main_excluded_bytes": 0,
            "remote_bytes": 30, "remote_exact": remote_exact,
        }}
        with mock.patch.object(progress, "csv_rows", side_effect=rows.__getitem__), mock.patch.object(
            progress, "load_byte_ownership", return_value=ownership
        ):
            return ET.fromstring(progress.render_svg())

    def assert_fill(self, svg: ET.Element, name: str, fraction: float) -> None:
        fill = svg.find(f".//*[@id='{name}-fill']")
        track = svg.find(f".//*[@id='{name}-track']")
        self.assertIsNotNone(fill)
        self.assertIsNotNone(track)
        self.assertAlmostEqual(float(fill.attrib["width"]) / float(track.attrib["width"]), fraction, places=4)

    def test_pending_review_preserves_byte_weighted_exact_fill(self) -> None:
        svg = self.render_fixture(pending=True)
        # One of two authored functions is exact, but it owns 90 of 100 bytes.
        # Excluded and unclassified candidates must not enter this denominator.
        self.assert_fill(svg, "exact", 0.9)
        self.assert_fill(svg, "review", 0.75)
        text = " ".join(svg.itertext())
        self.assertIn("90.00%", text)
        self.assertIn("90 / 100 bytes", text)
        self.assertIn("Authored denominator provisional · pending review: 1", text)
        self.assertIn("confirmed authored bytes", svg.attrib["aria-label"])
        self.assertIn("denominator provisional", svg.attrib["aria-label"])

    def test_completed_review_keeps_same_exact_scope(self) -> None:
        svg = self.render_fixture(pending=False)
        self.assert_fill(svg, "exact", 0.9)
        self.assert_fill(svg, "review", 1.0)
        self.assertIn("completed origin/boundary review", " ".join(svg.itertext()))
        self.assertNotIn("provisional", svg.attrib["aria-label"])

    def test_unverified_remote_bytes_do_not_inflate_exact_fill(self) -> None:
        svg = self.render_fixture(pending=True, remote_exact=False)
        self.assert_fill(svg, "exact", 0.6)
        self.assertIn("60 / 100 bytes", " ".join(svg.itertext()))

    def test_empty_or_unclassified_inventory_has_zero_exact_fill(self) -> None:
        for disposition in (None, "review", "exclude"):
            with self.subTest(disposition=disposition):
                rows = {
                    "functions.csv": [] if disposition is None else [{"address": "0x1000", "size": "40"}],
                    "function-origins.csv": [] if disposition is None else [{"address": "0x1000", "disposition": disposition}],
                    "matches.csv": [],
                }
                with mock.patch.object(progress, "csv_rows", side_effect=rows.__getitem__), mock.patch.object(
                    progress, "load_byte_ownership", return_value={}
                ):
                    svg = ET.fromstring(progress.render_svg())
                self.assert_fill(svg, "exact", 0.0)
                self.assertIn("0.00%", " ".join(svg.itertext()))


if __name__ == "__main__":
    unittest.main()
