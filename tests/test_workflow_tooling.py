from __future__ import annotations

import importlib.util
from pathlib import Path
import struct
import sys
import tempfile
import unittest


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
        cls.clones = load_script("clone-families.py")
        cls.packet = load_script("work-packet.py")
        cls.synthetic = load_script("generate-synthetic-coff.py")

    def test_ledger_reader_rejects_extra_physical_column(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "functions.csv"
            path.write_text("a,b\n1,2,3\n", encoding="utf-8")
            errors: list[str] = []
            rows = self.validator.read_rows(path, errors, ["a", "b"])
        self.assertEqual(rows, [])
        self.assertIn("expected 2 columns, got 3", errors[0])

    def test_first_mismatch_is_structured(self) -> None:
        mismatch = self.comparator.first_mismatch(b"\x90\x90\xc3", b"\x90\xcc\xc3", 0x401000)
        self.assertEqual(mismatch["offset"], 1)
        self.assertEqual(mismatch["address"], "0x00401001")
        self.assertEqual(mismatch["target_byte"], "90")
        self.assertEqual(mismatch["object_byte"], "cc")

    def test_unknown_dir32_is_a_blocker(self) -> None:
        result, failure = self.comparator.failure_record(
            ValueError("unknown absolute data relocation: __ehhandler$probe")
        )
        self.assertEqual(result, "blocked")
        self.assertEqual(failure["category"], "relocation.dir32.unknown_symbol")

    def test_target_identity_failure_is_not_a_match_blocker(self) -> None:
        result, failure = self.comparator.failure_record(
            ValueError("target SHA-256 mismatch: got wrong, expected exact")
        )
        self.assertEqual(result, "error")
        self.assertEqual(failure["category"], "target.identity_mismatch")

    def test_match_unit_graph_validates(self) -> None:
        manifest = self.manifest.load_manifest()
        self.assertGreaterEqual(len(manifest["units"]), 2)

    def test_known_clone_families_match_target(self) -> None:
        reports = self.clones.load_and_check()
        self.assertEqual(len(reports), 3)
        self.assertEqual(sum(report["member_count"] for report in reports), 45)

    def test_ghidra_body_span_boundary_is_advisory(self) -> None:
        entry, size, basis = self.packet.canonical_backend_boundary(
            {
                "address": "0053caa0",
                "body_start": "0053caa0",
                "body_end": "0053cb4e",
            }
        )
        self.assertEqual(entry, "0x0053CAA0")
        self.assertEqual(size, 175)
        self.assertEqual(basis, "backend_body_span")

    def test_synthetic_coff_replays_to_exact_target(self) -> None:
        manifest = self.synthetic.load_manifest()
        island = self.synthetic.validate_island(
            "youmu-owner-record", manifest["islands"]["youmu-owner-record"]
        )
        coff = self.synthetic.build_coff(island)
        self.assertEqual(struct.unpack_from("<H", coff, 0)[0], 0x014C)
        self.assertEqual(struct.unpack_from("<H", coff, 2)[0], 1)
        self.assertEqual(struct.unpack_from("<H", coff, 52)[0], 2)
        self.assertEqual(self.synthetic.replay_link(island, coff), island["body"])


if __name__ == "__main__":
    unittest.main()
