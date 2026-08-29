from __future__ import annotations

import csv
import importlib.util
from pathlib import Path
import sys
import tomllib
import unittest
from unittest import mock


ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))


def load_script(name: str):
    path = ROOT / "scripts" / name
    spec = importlib.util.spec_from_file_location(name.removesuffix(".py"), path)
    if spec is None or spec.loader is None:
        raise RuntimeError(f"cannot import {path}")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


class WorkflowToolingTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls) -> None:
        cls.validator = load_script("validate-tracking.py")
        cls.comparator = load_script("compare-function.py")
        cls.manifest = load_script("workflow_manifest.py")
        cls.progress = load_script("progress.py")
        cls.ida_check = load_script("check-ida-mcp.py")
        cls.inventory = load_script("export-ida-inventory.py")
        cls.typed = load_script("typed-re.py")
        cls.mcp_runtime = load_script("mcp_runtime.py")
        cls.xiph_sdk = load_script("fetch-xiph-sdk-object.py")

    def test_corrected_target_identity(self) -> None:
        manifest = self.validator.validate_target(require_bytes=False)
        self.assertEqual(manifest["target"]["size"], 3_129_344)
        self.assertEqual(
            manifest["target"]["sha256"],
            "56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e",
        )
        self.assertEqual(manifest["pe"]["entry_point"], "0x0068B9D2")

    def test_corrected_inventory_tracks_only_current_target_progress(self) -> None:
        with (ROOT / "config" / "functions.csv").open(
            newline="", encoding="utf-8"
        ) as stream:
            functions = list(csv.DictReader(stream))
        self.assertEqual(len(functions), 4010)
        matching = [row for row in functions if row["status"] == "matching"]
        self.assertEqual(len(matching), 1094)
        self.assertTrue(all(row["match_percent"] == "100.00" for row in matching))
        with (ROOT / "config" / "implemented.csv").open(
            newline="", encoding="utf-8"
        ) as stream:
            implemented = [row[0] for row in csv.reader(stream) if row]
        self.assertEqual(len(implemented), 1094)
        self.assertEqual(
            len(self.validator.rows(ROOT / "config" / "matches.csv")), 1094
        )

    def test_match_unit_graph_covers_current_exact_baseline(self) -> None:
        manifest = self.manifest.load_manifest()
        self.assertEqual(len(manifest["units"]), 360)
        self.assertEqual(
            sum(len(unit["functions"]) for unit in manifest["units"].values()),
            1094,
        )

    def test_progress_reports_current_exact_baseline(self) -> None:
        markdown = self.progress.render()
        self.assertIn("Tracked 1.06a function candidates | 4,010", markdown)
        self.assertIn("Confirmed authored functions | 1,094", markdown)
        self.assertIn("Classified exclusions | 1,049", markdown)
        self.assertIn("Origin/boundary review pending | 1,867", markdown)
        self.assertIn("Canonical exact functions | 1,094", markdown)
        self.assertIn("Canonical exact authored bytes | 180,727", markdown)
        self.assertIn(
            "former 1.06 reconstruction state is intentionally excluded", markdown
        )

    def test_xiph_origin_anchor_manifest_is_pinned(self) -> None:
        with (ROOT / "config" / "xiph-origin-anchors.toml").open("rb") as stream:
            anchors = tomllib.load(stream)
        self.assertEqual(
            anchors["target_sha256"],
            "56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e",
        )
        self.assertEqual(anchors["sdk_sha256"], self.xiph_sdk.ARCHIVE_SHA256)
        rows = anchors["anchors"]
        self.assertEqual(len(rows), 39)
        self.assertEqual(len({row["address"] for row in rows}), 39)
        self.assertEqual(sum(row["size"] for row in rows), 2704)

    def test_xiph_relocated_origin_anchor_manifest_is_pinned(self) -> None:
        with (ROOT / "config" / "xiph-relocated-origin-anchors.toml").open("rb") as stream:
            anchors = tomllib.load(stream)
        self.assertEqual(
            anchors["target_sha256"],
            "56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e",
        )
        self.assertEqual(anchors["sdk_sha256"], self.xiph_sdk.ARCHIVE_SHA256)
        self.assertEqual(anchors["min_nonreloc_coverage"], 0.70)
        self.assertEqual(anchors["min_nonreloc_bytes"], 24)
        rows = anchors["anchors"]
        self.assertEqual(len(rows), 154)
        self.assertEqual(len({row["address"] for row in rows}), 154)
        self.assertEqual(sum(row["size"] for row in rows), 57489)


    def test_vc8_generated_origin_anchor_manifest_is_pinned(self) -> None:
        with (ROOT / "config" / "vc8-generated-origin-anchors.toml").open("rb") as stream:
            anchors = tomllib.load(stream)
        self.assertEqual(
            anchors["target_sha256"],
            "56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e",
        )
        self.assertEqual(
            anchors["compiler_sha256"],
            "71c93ca5bddc9b2816d0e053cac2b952f926f6b9321fab6b1ab6e8603621324c",
        )
        self.assertEqual(anchors["source"], "src/battle/PatGroup.cpp")
        self.assertTrue(anchors["enable_gs"])
        self.assertEqual(anchors["min_nonreloc_coverage"], 0.70)
        self.assertEqual(anchors["min_nonreloc_bytes"], 24)
        rows = anchors["anchors"]
        self.assertEqual(
            [(row["address"], row["size"]) for row in rows],
            [("0x0045FC30", 76), ("0x00461320", 129)],
        )
        with (ROOT / "config" / "vc8-generated-pat-copy-origin-anchors.toml").open("rb") as stream:
            copy_anchors = tomllib.load(stream)
        self.assertEqual(copy_anchors["target_sha256"], anchors["target_sha256"])
        self.assertEqual(copy_anchors["compiler_sha256"], anchors["compiler_sha256"])
        self.assertEqual(copy_anchors["source"], "scripts/probes/pat_vector_generated.cpp")
        self.assertTrue(copy_anchors["enable_gs"])
        self.assertEqual(copy_anchors["max_alignment_tail"], 1)
        self.assertEqual(copy_anchors["alignment_tail_hex"], "cc")
        self.assertEqual(
            [(row["address"], row["size"]) for row in copy_anchors["anchors"]],
            [("0x00461420", 249), ("0x00461940", 123)],
        )
        with (ROOT / "config" / "vc8-generated-pat-nested-origin-anchors.toml").open("rb") as stream:
            nested_anchors = tomllib.load(stream)
        self.assertEqual(nested_anchors["target_sha256"], anchors["target_sha256"])
        self.assertEqual(nested_anchors["compiler_sha256"], anchors["compiler_sha256"])
        self.assertEqual(nested_anchors["source"], "scripts/probes/pat_nested_vectors.cpp")
        self.assertTrue(nested_anchors["enable_gs"])
        self.assertEqual(
            [(row["address"], row["size"]) for row in nested_anchors["anchors"]],
            [
                ("0x0045FBD0", 88),
                ("0x00460AD0", 317),
                ("0x0040C240", 42),
                ("0x00435F90", 42),
                ("0x00464B40", 90),
                ("0x0040DF70", 90),
            ],
        )
        with (ROOT / "config" / "vc8-generated-pat-record-copy-origin-anchors.toml").open("rb") as stream:
            record_copy = tomllib.load(stream)
        self.assertEqual(record_copy["target_sha256"], anchors["target_sha256"])
        self.assertEqual(record_copy["compiler_sha256"], anchors["compiler_sha256"])
        self.assertEqual(record_copy["source"], "scripts/probes/pat_record_copy_generated.cpp")
        self.assertTrue(record_copy["enable_gs"])
        self.assertEqual(
            [(row["address"], row["size"]) for row in record_copy["anchors"]],
            [("0x00460C90", 311)],
        )
        with (ROOT / "config" / "vc8-generated-ui-map-origin-anchors.toml").open("rb") as stream:
            ui_map = tomllib.load(stream)
        self.assertEqual(ui_map["target_sha256"], anchors["target_sha256"])
        self.assertEqual(ui_map["compiler_sha256"], anchors["compiler_sha256"])
        self.assertEqual(ui_map["source"], "scripts/probes/ui_design_map_generated.cpp")
        self.assertFalse(ui_map["enable_gs"])
        self.assertEqual(
            [(row["address"], row["size"]) for row in ui_map["anchors"]],
            [("0x0046EA60", 105)],
        )
        with (ROOT / "config" / "vc8-generated-list-voidptr-origin-anchors.toml").open("rb") as stream:
            list_nodes = tomllib.load(stream)
        self.assertEqual(list_nodes["target_sha256"], anchors["target_sha256"])
        self.assertEqual(list_nodes["compiler_sha256"], anchors["compiler_sha256"])
        self.assertEqual(list_nodes["source"], "scripts/probes/list_voidptr_buynode_generated.cpp")
        self.assertFalse(list_nodes["enable_gs"])
        self.assertEqual(
            [(row["address"], row["size"], row["equivalence_group"]) for row in list_nodes["anchors"]],
            [
                ("0x004129E0", 51, "list-voidptr-buynode-clones"),
                ("0x00421F30", 51, "list-voidptr-buynode-clones"),
            ],
        )
        with (ROOT / "config" / "vc8-generated-list-voidptr-tidy-origin-anchors.toml").open("rb") as stream:
            list_tidy = tomllib.load(stream)
        self.assertEqual(list_tidy["target_sha256"], anchors["target_sha256"])
        self.assertEqual(list_tidy["compiler_sha256"], anchors["compiler_sha256"])
        self.assertEqual(list_tidy["source"], "scripts/probes/list_voidptr_tidy_generated.cpp")
        self.assertFalse(list_tidy["enable_gs"])
        self.assertEqual(
            [(row["address"], row["size"], row["equivalence_group"]) for row in list_tidy["anchors"]],
            [
                ("0x004023E0", 72, "list-voidptr-tidy-clones"),
                ("0x00435EB0", 72, "list-voidptr-tidy-clones"),
            ],
        )
        with (ROOT / "config" / "vc8-generated-scenario-event-map-find-origin-anchors.toml").open("rb") as stream:
            scenario_map_find = tomllib.load(stream)
        self.assertEqual(scenario_map_find["target_sha256"], anchors["target_sha256"])
        self.assertEqual(scenario_map_find["compiler_sha256"], anchors["compiler_sha256"])
        self.assertEqual(scenario_map_find["source"], "src/battle/ScenarioEventNameResolver.cpp")
        self.assertFalse(scenario_map_find["enable_gs"])
        self.assertEqual(
            [(row["address"], row["size"]) for row in scenario_map_find["anchors"]],
            [("0x006A4D60", 105)],
        )

    def test_exact_tu_std_origin_manifests_are_pinned(self) -> None:
        paths = sorted((ROOT / "config").glob("vc8-generated-*-std-origin-anchors.toml"))
        self.assertEqual(len(paths), 24)
        target_sha = "56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e"
        compiler_sha = "71c93ca5bddc9b2816d0e053cac2b952f926f6b9321fab6b1ab6e8603621324c"
        rows = []
        for path in paths:
            with path.open("rb") as stream:
                manifest = tomllib.load(stream)
            self.assertEqual(manifest["target_sha256"], target_sha)
            self.assertEqual(manifest["compiler_sha256"], compiler_sha)
            self.assertEqual(manifest["min_nonreloc_coverage"], 0.70)
            self.assertEqual(manifest["min_nonreloc_bytes"], 24)
            self.assertIn(manifest["max_alignment_tail"], (0, 1))
            if manifest["max_alignment_tail"]:
                self.assertEqual(manifest["alignment_tail_hex"], "cc")
            self.assertTrue(manifest["source"].startswith("src/"))
            rows.extend(manifest["anchors"])
        self.assertEqual(len(rows), 257)
        self.assertEqual(len({row["address"] for row in rows}), 257)
        self.assertEqual(sum(row["size"] for row in rows), 33_845)

    def test_new_layout_probe_origin_manifests_are_pinned(self) -> None:
        expected = {
            "vc8-generated-spriteex-vector-origin-anchors.toml": (
                "scripts/probes/spriteex_vector_generated.cpp", False, 12, 829
            ),
            "vc8-generated-map-int-value16-origin-anchors.toml": (
                "scripts/probes/map_int_value16_generated.cpp", False, 7, 506
            ),
            "vc8-generated-map-int-value244-origin-anchors.toml": (
                "scripts/probes/map_int_value244_generated.cpp", False, 7, 576
            ),
            "vc8-generated-fighter-sequence-deque-origin-anchors.toml": (
                "scripts/probes/fighter_sequence_deque_generated.cpp", False, 3, 713
            ),
            "vc8-generated-phase-render-list-origin-anchors.toml": (
                "src/battle/FighterPhaseRenderState.cpp", True, 5, 430
            ),
            "vc8-generated-battle-render-request-list-origin-anchors.toml": (
                "src/battle/BattleObjectStage.cpp", False, 1, 59
            ),
        }
        for filename, (source, enable_gs, count, byte_count) in expected.items():
            with (ROOT / "config" / filename).open("rb") as stream:
                manifest = tomllib.load(stream)
            self.assertEqual(manifest["target_sha256"], "56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e")
            self.assertEqual(manifest["compiler_sha256"], "71c93ca5bddc9b2816d0e053cac2b952f926f6b9321fab6b1ab6e8603621324c")
            self.assertEqual(manifest["source"], source)
            self.assertEqual(manifest["enable_gs"], enable_gs)
            self.assertEqual(len(manifest["anchors"]), count)
            self.assertEqual(sum(row["size"] for row in manifest["anchors"]), byte_count)

    def test_spell_tree_origin_manifest_is_expanded(self) -> None:
        path = ROOT / "config" / "vc8-generated-spell-tree-probe-origin-anchors.toml"
        with path.open("rb") as stream:
            manifest = tomllib.load(stream)
        self.assertEqual(manifest["source"], "scripts/probes/spell_tree.cpp")
        self.assertTrue(manifest["enable_gs"])
        self.assertEqual(len(manifest["anchors"]), 6)
        self.assertEqual(sum(row["size"] for row in manifest["anchors"]), 1_131)
        self.assertIn("0x0042CF20", {row["address"] for row in manifest["anchors"]})
        self.assertIn("0x0042E370", {row["address"] for row in manifest["anchors"]})

    def test_short_set_origin_manifest_is_pinned(self) -> None:
        path = ROOT / "config" / "vc8-generated-short-set-origin-anchors.toml"
        with path.open("rb") as stream:
            manifest = tomllib.load(stream)
        self.assertEqual(manifest["source"], "scripts/probes/short_set_generated.cpp")
        self.assertTrue(manifest["enable_gs"])
        self.assertEqual(
            [(row["address"], row["size"]) for row in manifest["anchors"]],
            [("0x00432F90", 509), ("0x00433190", 695), ("0x00433450", 189)],
        )

    def test_deque_short_erase_origin_manifest_is_pinned(self) -> None:
        path = ROOT / "config" / "vc8-generated-deque-short-erase-origin-anchors.toml"
        with path.open("rb") as stream:
            manifest = tomllib.load(stream)
        self.assertEqual(manifest["source"], "scripts/probes/DequeShortEraseOrigin.cpp")
        self.assertEqual([(row["address"], row["size"]) for row in manifest["anchors"]], [("0x004323B0", 108), ("0x00443A30", 108), ("0x0045DC20", 108), ("0x00617B50", 108)])
        self.assertTrue(all(row["equivalence_group"] == "deque-erase-108-clones" for row in manifest["anchors"]))

    def test_inventory_pagination_normalization(self) -> None:
        data, next_offset = self.inventory.normalize_page(
            {
                "data": [
                    {
                        "address": "0x401000",
                        "name": "sub_401000",
                        "size": "0x34",
                    }
                ],
                "next_offset": 1,
            }
        )
        self.assertEqual(len(data), 1)
        self.assertEqual(next_offset, 1)

    def test_attestation_byte_parser(self) -> None:
        self.assertEqual(
            self.ida_check.parse_ida_bytes("90 00 ff"), b"\x90\x00\xff"
        )

    def test_ida_mcp_runtime_is_pinned_and_project_independent(self) -> None:
        self.assertEqual(self.mcp_runtime.MCP_REQUIREMENT, "mcp==1.26.0")
        self.assertEqual(
            self.mcp_runtime.bootstrap_command(
                "/usr/bin/uv", ["scripts/check-ida-mcp.py"]
            ),
            [
                "/usr/bin/uv",
                "run",
                "--quiet",
                "--no-project",
                "--with",
                "mcp==1.26.0",
                "python3",
                "scripts/check-ida-mcp.py",
            ],
        )

    def test_ida_mcp_runtime_reports_missing_uv(self) -> None:
        with (
            mock.patch.object(
                self.mcp_runtime, "installed_mcp_version", return_value=None
            ),
            mock.patch.object(self.mcp_runtime.shutil, "which", return_value=None),
            mock.patch.dict(
                self.mcp_runtime.os.environ,
                {self.mcp_runtime.BOOTSTRAP_MARKER: ""},
            ),
        ):
            with self.assertRaisesRegex(RuntimeError, "install uv"):
                self.mcp_runtime.ensure_mcp_runtime()

    @unittest.skipUnless(
        (ROOT / "resources" / "th105.exe").is_file(), "private target is unavailable"
    )
    def test_typed_target_mapping_reads_exact_pe_bytes(self) -> None:
        data, _manifest = self.typed.verify_local_target()
        self.assertEqual(
            self.typed.target_bytes(data, 0x00401000, 8), data[0x1000:0x1008]
        )

    def test_first_mismatch_is_structured(self) -> None:
        mismatch = self.comparator.first_mismatch(
            b"\x90\x90\xc3", b"\x90\xcc\xc3", 0x401000
        )
        self.assertEqual(mismatch["offset"], 1)
        self.assertEqual(mismatch["address"], "0x00401001")

    def test_unknown_dir32_is_a_blocker(self) -> None:
        result, failure = self.comparator.failure_record(
            ValueError("unknown absolute data relocation: __ehhandler$probe")
        )
        self.assertEqual(result, "blocked")
        self.assertEqual(failure["category"], "relocation.dir32.unknown_symbol")

    def test_rel32_accepts_only_supported_instruction_forms(self) -> None:
        self.assertEqual(
            self.comparator.rel32_operand_kind(b"\xe8\0\0\0\0", 1), "call"
        )
        self.assertEqual(
            self.comparator.rel32_operand_kind(b"\xe9\0\0\0\0", 1), "jmp"
        )
        self.assertEqual(
            self.comparator.rel32_operand_kind(b"\x0f\x84\0\0\0\0", 2), "jcc"
        )
        self.assertIsNone(
            self.comparator.rel32_operand_kind(b"\x90\0\0\0\0", 1)
        )


if __name__ == "__main__":
    unittest.main()
