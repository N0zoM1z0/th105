import importlib.util
import json
from pathlib import Path
import sys
import tempfile
from types import SimpleNamespace
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
SPEC = importlib.util.spec_from_file_location("iku_mt_preservation_tests", ROOT / "scripts/probe-iku-mt-preservation.py")
PROBE = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(PROBE)


class IkuMtPreservationTests(unittest.TestCase):
    def test_map_symbol_requires_one_address_but_allows_duplicate_owner_rows(self):
        self.assertEqual(PROBE.unique_address({"mt": [(1, "CIL module"), (1, "mt.obj")]}, "mt"), 1)
        for symbols in ({}, {"mt": [(1, "mt.obj"), (2, "clone.obj")]}):
            with self.assertRaisesRegex(ValueError, "unique MAP address"):
                PROBE.unique_address(symbols, "mt")

    def test_context_rejects_wrong_target_source_and_visibility(self):
        canonical = SimpleNamespace(verify_target=lambda: "target-fixture")
        receipt = {
            "schema": "th105-iku-provider-visibility-entry-v1",
            "target_sha256": "target-fixture",
            "root_source_sha256": PROBE.linked_pe.sha(ROOT / "src/characters/IkuActionState.cpp"),
            "visible_provider_units": [PROBE.MT_UNIT],
        }
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory)
            for key, wrong in (("schema", "another-tool"), ("target_sha256", "another-target"),
                               ("root_source_sha256", "another-source"), ("visible_provider_units", ["another-unit"])):
                (path / "receipt.json").write_text(json.dumps(receipt | {key: wrong}))
                with self.assertRaises(ValueError):
                    PROBE.load_context(path, canonical)

    def test_context_rejects_replaced_image_before_emulation(self):
        canonical = SimpleNamespace(verify_target=lambda: "target-fixture")
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory)
            # Non-executable hash fixture; this must fail before a PE is parsed.
            (path / "IkuRoot.dll").write_bytes(b"replaced artifact fixture")
            (path / "receipt.json").write_text(json.dumps({
                "schema": "th105-iku-provider-visibility-entry-v1",
                "target_sha256": "target-fixture",
                "root_source_sha256": PROBE.linked_pe.sha(ROOT / "src/characters/IkuActionState.cpp"),
                "visible_provider_units": [PROBE.MT_UNIT], "image_sha256": "old-image",
            }))
            with self.assertRaisesRegex(ValueError, "stale linked MT artifact"):
                PROBE.load_context(path, canonical)
