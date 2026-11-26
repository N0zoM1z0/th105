from __future__ import annotations

import importlib.util
from pathlib import Path
import struct
import sys
import tempfile
import unittest
from unittest import mock

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location("giant_coff_selection", ROOT / "scripts/compare-giant-action-switches.py")
COFF = importlib.util.module_from_spec(SPEC)
sys.modules[SPEC.name] = COFF
SPEC.loader.exec_module(COFF)


class GiantCoffSelectionTests(unittest.TestCase):
    def make_object(self, path, *, value=0, section_name=b".text", duplicate=False):
        # The larger COMDAT deliberately owns a different relocation table.
        header = struct.pack("<HHIIIHH", 0x14C, 2, 0, 160, 4, 0, 0)
        sections = b"".join(
            struct.pack("<8sIIIIIIHHI", name, 0, 0, size, raw, reloc, 0, 1, 0, 0x60001020)
            for name, size, raw, reloc in ((b".text", 32, 100, 140), (section_name, 8, 132, 150))
        )
        relocations = struct.pack("<IIH", 4, 3, 6) + struct.pack("<IIH", 0, 2, 6)
        symbols = b"".join(
            struct.pack("<8sIhHBB", name, offset, section, 0x20, 2, 0)
            for name, offset, section in ((b"_root" if duplicate else b"_helper", 0, 1),
                                          (b"_root", value, 2), (b"_dep", 0, 0), (b"_other", 0, 0))
        )
        path.write_bytes(header + sections + b"H" * 32 + b"R" * 8 + relocations + symbols + struct.pack("<I", 4))

    def test_explicit_root_selects_its_own_section_and_relocations(self):
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "two-roots.obj"
            self.make_object(path)
            inferred = COFF.CoffObject(path)
            self.assertEqual(inferred.text_section_number, 1)
            self.assertEqual(inferred.relocations[4][0].name, "_other")
            selected = COFF.CoffObject(path, symbol_base="_root")
            self.assertEqual(selected.text_section_number, 2)
            self.assertEqual(selected.text, b"R" * 8)
            self.assertEqual(set(selected.relocations), {0})
            self.assertEqual(selected.relocations[0][0].name, "_dep")

    def test_unsupported_or_ambiguous_root_fails_closed(self):
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "two-roots.obj"
            for fields, name in (({}, "_missing"), ({}, "_dep"), ({"duplicate": True}, "_root"),
                                 ({"value": 1}, "_root"), ({"section_name": b".rdata"}, "_root")):
                with self.subTest(fields=fields, symbol=name):
                    self.make_object(path, **fields)
                    with self.assertRaises(ValueError):
                        COFF.CoffObject(path, symbol_base=name)

    def prefix_fixture(self):
        obj = object.__new__(COFF.CoffObject)
        obj.path = Path("fixture.obj")
        obj.text_section_number = 1
        obj.text = b"\x90" * 12 + struct.pack("<4I", 4, 6, 8, 10) + b"\x00" * 12
        obj.relocations = {offset: (COFF.CoffSymbol("$case", 0, 1), 6)
                           for offset in range(12, 28, 4)}
        region = dict(name="low", case_min=0, case_max=0,
                      destination_table_offset=28, destination_count=1,
                      index_table_offset=32, mapping={0: 4}, groups={4: [0]})
        root = dict(regions=[dict(destination_table="0x1040")], auxiliary_switches=[
            dict(destination_table="0x1030", destinations=["0x1004"] * 4)])
        return obj, region, root

    def test_auxiliary_prefix_is_metadata_before_the_first_sparse_table(self):
        obj, region, root = self.prefix_fixture()
        with mock.patch.object(COFF, "candidate_region_tables", return_value=[region]):
            result = COFF.build_candidate_map(obj, root)
        self.assertEqual(result["metadata_start"], 12)
        self.assertEqual(result["regions"][0]["groups"][0]["span_to_next_destination"], 8)

    def test_auxiliary_prefix_requires_local_relocations_code_targets_and_no_gap(self):
        for problem in ("missing", "external", "metadata", "gap"):
            obj, region, root = self.prefix_fixture()
            if problem == "missing":
                del obj.relocations[12]
            elif problem == "external":
                obj.relocations[12] = (COFF.CoffSymbol("_external", 0, 0), 6)
            elif problem == "metadata":
                obj.text = obj.text[:12] + struct.pack("<I", 12) + obj.text[16:]
            else:
                root["auxiliary_switches"][0]["destination_table"] = "0x102C"
            with self.subTest(problem=problem), mock.patch.object(
                    COFF, "candidate_region_tables", return_value=[region]):
                with self.assertRaises(ValueError):
                    COFF.build_candidate_map(obj, root)
