from __future__ import annotations

import importlib.util
import json
from pathlib import Path
import sys
import tempfile
from types import SimpleNamespace
import unittest
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
SPEC = importlib.util.spec_from_file_location(
    "iku_link_probe_tests", ROOT / "scripts/probe-iku-action-ltcg.py"
)
PROBE = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(PROBE)


class IkuLinkProbeTests(unittest.TestCase):
    def test_visibility_preserves_default_and_selects_only_game_units(self):
        available = {"game-a", "game-b"}
        self.assertIsNone(PROBE.visibility_selection(None, available))
        self.assertEqual(PROBE.visibility_selection("none", available), set())
        self.assertEqual(PROBE.visibility_selection("all", available), available)
        self.assertEqual(PROBE.visibility_selection("game-b,game-a", available), available)
        for invalid in ("", "sdk-deque", "game-a,missing", "none,game-a"):
            with self.assertRaises(ValueError):
                PROBE.visibility_selection(invalid, available)

    def visibility_fixture(self, code=None, relocations=(), exports=None, functions=None):
        code = code if code is not None else b"\x90" * 128
        pe = SimpleNamespace(
            DIRECTORY_ENTRY_EXPORT=SimpleNamespace(symbols=exports if exports is not None else [
                SimpleNamespace(name=PROBE.SYMBOL.encode(), address=0x1000)]),
            DIRECTORY_ENTRY_BASERELOC=[SimpleNamespace(entries=relocations)],
            OPTIONAL_HEADER=SimpleNamespace(ImageBase=0x10000000),
            get_data=lambda address, size: code[:size],
        )
        canonical = SimpleNamespace(
            target_bytes=lambda address, size: b"\x90" * size,
            first_mismatch=lambda target, candidate, address: None,
        )
        map_path = SimpleNamespace(read_text=lambda: "synthetic MAP fixture")
        return pe, canonical, map_path, functions or {}

    def test_visibility_inventory_does_not_certify_missing_or_split_aliases(self):
        pe, canonical, map_path, functions = self.visibility_fixture(functions={
            0x10001000: [("same", "CIL library: CIL module"), ("actual", "provider.obj"),
                         ("split", "CIL library: CIL module")],
            0x10002000: [("other", "provider.obj")],
        })
        with patch.object(PROBE.pefile, "PE", return_value=pe), patch.object(
                PROBE.linked_pe, "parse_map", return_value=functions):
            result = PROBE.visibility_entry(Path("fixture.dll"), map_path, canonical,
                                            {"same": "actual", "split": "other", "missing": "actual"})
        self.assertTrue(result["map_alias_inventory"]["same"]["same_unique_address"])
        self.assertFalse(result["map_alias_inventory"]["split"]["same_unique_address"])
        self.assertFalse(result["map_alias_inventory"]["missing"]["same_unique_address"])
        self.assertIn("does not certify", result["scope"])

    def test_mt_noinline_is_isolated_from_other_visibility_contexts(self):
        available = {"cross-v106a-mt19937-next", "game-a"}
        self.assertEqual(PROBE.visibility_selection("cross-v106a-mt19937-next", available, True),
                         {"cross-v106a-mt19937-next"})
        for specification in (None, "none", "all", "game-a"):
            with self.assertRaisesRegex(ValueError, "requires only"):
                PROBE.visibility_selection(specification, available, True)

    def test_noinline_control_changes_only_two_reviewed_declarations(self):
        source = (ROOT / "src/engine/Mt19937.cpp").read_text()
        controlled = PROBE.mt_noinline_source(source)
        self.assertEqual(controlled.count("__declspec(noinline)"), 2)
        self.assertEqual(controlled.replace("__declspec(noinline) ", ""), source)
        for changed in (source.replace("mt19937_next_u32", "unknown_next"),
                        source + "\nunsigned __cdecl mt19937_next_u32();\n"):
            with self.assertRaisesRegex(ValueError, "reviewed seed/next"):
                PROBE.mt_noinline_source(changed)

    def test_visibility_rejects_call_crossing_end_of_prefix(self):
        # Only the first byte of this synthetic CALL lies in the101-byte window.
        pe, canonical, map_path, _ = self.visibility_fixture(
            code=b"\x90" * 100 + b"\xe8\0\0\0\0" + b"\x90" * 23)
        with patch.object(PROBE.pefile, "PE", return_value=pe):
            with self.assertRaisesRegex(ValueError, "call relocation"):
                PROBE.visibility_entry(Path("fixture.dll"), map_path, canonical, {})

    def test_visibility_rejects_highlow_inside_prefix(self):
        pe, canonical, map_path, _ = self.visibility_fixture(
            relocations=[SimpleNamespace(type=3, rva=0x1064)])
        with patch.object(PROBE.pefile, "PE", return_value=pe):
            with self.assertRaisesRegex(ValueError, "pointer relocation"):
                PROBE.visibility_entry(Path("fixture.dll"), map_path, canonical, {})

    def test_visibility_rejects_absent_or_duplicate_root_exports(self):
        entry = SimpleNamespace(name=PROBE.SYMBOL.encode(), address=0x1000)
        for exports in ([], [entry, entry]):
            pe, canonical, map_path, _ = self.visibility_fixture(exports=exports)
            with patch.object(PROBE.pefile, "PE", return_value=pe):
                with self.assertRaisesRegex(ValueError, "one real Iku export"):
                    PROBE.visibility_entry(Path("fixture.dll"), map_path, canonical, {})

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
