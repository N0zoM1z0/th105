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
        self.assertEqual(len(functions), 4002)
        matching = [row for row in functions if row["status"] == "matching"]
        self.assertEqual(len(matching), 196)
        self.assertTrue(all(row["match_percent"] == "100.00" for row in matching))
        with (ROOT / "config" / "implemented.csv").open(
            newline="", encoding="utf-8"
        ) as stream:
            implemented = [row[0] for row in csv.reader(stream) if row]
        self.assertEqual(len(implemented), 196)
        self.assertEqual(
            len(self.validator.rows(ROOT / "config" / "matches.csv")), 196
        )

    def test_match_unit_graph_covers_current_exact_baseline(self) -> None:
        manifest = self.manifest.load_manifest()
        self.assertEqual(len(manifest["units"]), 112)
        self.assertEqual(
            sum(len(unit["functions"]) for unit in manifest["units"].values()),
            196,
        )

    def test_progress_reports_current_exact_baseline(self) -> None:
        markdown = self.progress.render()
        self.assertIn("Tracked 1.06a function candidates | 4,002", markdown)
        self.assertIn("Confirmed authored functions | 196", markdown)
        self.assertIn("Classified exclusions | 673", markdown)
        self.assertIn("Origin/boundary review pending | 3,133", markdown)
        self.assertIn("Canonical exact functions | 196", markdown)
        self.assertIn("Canonical exact authored bytes | 27,594", markdown)
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
