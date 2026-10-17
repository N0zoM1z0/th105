from __future__ import annotations

import importlib.util
from pathlib import Path
import struct
import sys
import tempfile
import unittest

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
