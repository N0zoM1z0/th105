from __future__ import annotations

import importlib.util
import json
from pathlib import Path
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
SPEC = importlib.util.spec_from_file_location(
    "iku_link_probe_tests", ROOT / "scripts/probe-iku-action-ltcg.py"
)
PROBE = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(PROBE)


class IkuLinkProbeTests(unittest.TestCase):
    def test_only_reviewed_free_getter_bodies_are_selected(self):
        for unit, filename in (
            ("cross-v106a-game-mode-getters", "src/battle/GameMode.cpp"),
            ("cross-v106a-input-selection-accessors", "src/input/InputSelection.cpp"),
        ):
            keep, remove = PROBE.FREE_SELECTIONS[unit]
            text = (ROOT / filename).read_text()
            selected = PROBE.select_free(text, keep, remove)
            for name in keep:
                self.assertIn(name + "(", selected)
            for name in remove:
                self.assertNotIn(name + "(", selected)
            self.assertIn("extern ", selected)

    def test_changed_or_unbalanced_provider_inventory_fails_closed(self):
        text = (ROOT / "src/battle/GameMode.cpp").read_text()
        keep, remove = PROBE.FREE_SELECTIONS["cross-v106a-game-mode-getters"]
        for changed in (
            text + "\nvoid unreviewed() {}\n",
            text.replace("get_game_mode", "different_mode"),
        ):
            with self.assertRaisesRegex(ValueError, "inventory changed"):
                PROBE.select_free(changed, keep, remove)
        with self.assertRaisesRegex(ValueError, "unbalanced"):
            PROBE.select_free("int get_game_mode() {", {"get_game_mode"}, set())

    def test_compile_cache_requires_inputs_and_current_object_hash(self):
        # Synthetic cache data only; no fixture object is compiled or executed.
        with tempfile.TemporaryDirectory() as directory:
            obj = Path(directory) / "provider.obj"
            cache = Path(directory) / "provider.compile.json"
            obj.write_bytes(b"ordinary object fixture")
            inputs = {
                "source_sha256": "source-A",
                "unit_input_digest": "headers-A",
                "command": ["cl", "/O2"],
                "tools": {"cl": "compiler-A"},
            }
            self.assertFalse(PROBE.reusable_compile(cache, obj, inputs))
            cache.write_text(
                json.dumps(
                    {"inputs": inputs, "object_sha256": PROBE.linked_pe.sha(obj)}
                )
            )
            self.assertTrue(PROBE.reusable_compile(cache, obj, inputs))
            for key, value in (
                ("source_sha256", "source-B"),
                ("unit_input_digest", "headers-B"),
                ("command", ["cl", "/Os"]),
                ("tools", {"cl": "compiler-B"}),
            ):
                self.assertFalse(
                    PROBE.reusable_compile(cache, obj, inputs | {key: value})
                )
            obj.write_bytes(b"different object fixture")
            self.assertFalse(PROBE.reusable_compile(cache, obj, inputs))
            cache.write_text("invalid cache JSON")
            self.assertFalse(PROBE.reusable_compile(cache, obj, inputs))
