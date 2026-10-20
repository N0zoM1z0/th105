"""Call counts alone cannot establish a selector's normal-return topology."""

from __future__ import annotations

import copy
import importlib.util
from pathlib import Path
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


if __name__ == "__main__":
    unittest.main()
