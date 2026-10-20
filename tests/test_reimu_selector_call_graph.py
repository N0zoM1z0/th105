"""Call counts alone cannot establish a selector's normal-return topology."""

from __future__ import annotations

import copy
import importlib.util
from pathlib import Path
import struct
import unittest

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location(
    "selector_sites", ROOT / "scripts/audit-reimu-object-selector-families.py"
)
sites = importlib.util.module_from_spec(spec)
spec.loader.exec_module(sites)


def ring_graph():
    return {
        "entry": dict(color="entry", successors=["loop"]),
        "loop": dict(color="private:spawn:first_world", successors=["loop", "final"]),
        "final": dict(color="private:spawn", successors=["wave"]),
        "wave": dict(color="private:wave", successors=["advance"]),
        "advance": dict(color="shared:advance", successors=["return"]),
        "return": dict(color="return", successors=[]),
    }


class SelectorCallGraphTests(unittest.TestCase):
    def test_packet_stores_preserve_the_guarded_selector(self):
        rows = sites.decode(
            bytes.fromhex("a194a86f0083f803d9eed95c24007707ff248500200000c3"), 0x1000
        )
        switches = sites.selector_switches(
            rows, lambda address, size: struct.pack("<4I", 1, 2, 3, 4)
        )
        self.assertEqual(switches[0x1010]["destinations"], [1, 2, 3, 4])

    def test_integer_clobber_between_compare_and_guard_is_not_reviewed(self):
        rows = sites.decode(
            bytes.fromhex("a194a86f0083f80340d9eed95c24007707ff248500200000c3"), 0x1000
        )
        self.assertEqual(sites.selector_switches(rows, lambda address, size: b""), {})

    def test_nested_dispatch_requires_review_and_preserves_all_call_edges(self):
        rows = sites.decode(bytes.fromhex("ff248500200000e800000000c3"), 0x1000)
        outer = dict(destinations=[0x1000, 0x100C])
        with self.assertRaisesRegex(ValueError, "unreviewed indirect jump"):
            sites.partition(rows, outer)
        nested = {0x1000: dict(destinations=[0x1007, 0x100C])}
        part = sites.partition(rows, outer, nested)
        graph = sites.call_graph(rows, part, 0, None, nested)
        self.assertEqual(graph["entry"]["successors"], [str(0x1007), "return"])
        self.assertEqual(graph[str(0x1007)]["successors"], ["return"])

    def test_renamed_duplicate_callees_and_loop_preserve_topology(self):
        target = ring_graph()
        target["loop"]["color"] = target["final"]["color"] = "private:spawn"
        names = dict(
            entry="start",
            loop="z",
            final="a",
            wave="q",
            advance="b",
            **{"return": "end"},
        )
        source = {
            names[key]: dict(
                color=row["color"], successors=[names[x] for x in row["successors"]]
            )
            for key, row in reversed(list(target.items()))
        }
        self.assertTrue(sites.same_call_graph(target, source))

    def test_same_callees_and_counts_cannot_hide_early_wave(self):
        target = ring_graph()
        source = copy.deepcopy(target)
        source["loop"]["successors"] = ["loop", "wave"]
        source["wave"]["successors"] = ["final"]
        source["final"]["successors"] = ["advance"]
        self.assertEqual(
            sorted(row["color"] for row in target.values()),
            sorted(row["color"] for row in source.values()),
        )
        self.assertFalse(sites.same_call_graph(target, source))

    def test_same_degree_cannot_hide_a_removed_iteration(self):
        target = ring_graph()
        source = copy.deepcopy(target)
        source["loop"]["successors"] = ["return", "final"]
        self.assertFalse(sites.same_call_graph(target, source))

    def test_shared_and_private_site_ownership_are_distinct(self):
        target = ring_graph()
        source = copy.deepcopy(target)
        source["advance"]["color"] = "private:advance"
        self.assertFalse(sites.same_call_graph(target, source))

    def family(self, names):
        return [
            {
                "entry": dict(color="entry", successors=[name]),
                name: dict(color="private:spawn", successors=["return"]),
                "return": dict(color="return", successors=[]),
            }
            for name in names
        ]

    def test_partial_sharing_survives_global_renaming(self):
        target = sites.combine_call_graphs(self.family(["100", "100", "200"]))
        source = sites.combine_call_graphs(self.family(["900", "900", "800"]))
        self.assertTrue(sites.same_call_graph(target, source))

    def test_individually_equal_entries_cannot_hide_cloned_shared_calls(self):
        target = self.family(["100", "100", "200"])
        source = self.family(["900", "901", "902"])
        self.assertTrue(
            all(sites.same_call_graph(a, b) for a, b in zip(target, source))
        )
        self.assertFalse(
            sites.same_call_graph(
                sites.combine_call_graphs(target), sites.combine_call_graphs(source)
            )
        )

    def test_equal_site_totals_cannot_hide_a_wrong_sharing_subset(self):
        target = sites.combine_call_graphs(self.family(["100", "100", "200"]))
        source = sites.combine_call_graphs(self.family(["900", "800", "800"]))
        self.assertEqual(len(target), len(source))
        self.assertFalse(sites.same_call_graph(target, source))


if __name__ == "__main__":
    unittest.main()
