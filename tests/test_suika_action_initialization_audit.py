"""Reject malformed metadata in both remapped Suika action regions."""
from __future__ import annotations

import importlib.util
from pathlib import Path
import struct
import sys
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
spec = importlib.util.spec_from_file_location(
    "suika_initialization_audit", ROOT / "scripts/audit-suika-action-initialization.py")
audit = importlib.util.module_from_spec(spec)
spec.loader.exec_module(audit)


class SuikaInitializationMetadataTests(unittest.TestCase):
    def fixture(self):
        # Synthetic instructions/tables; no executable target bytes.
        code, fixups = bytearray(), []
        for index, (lower, words, count) in enumerate(((300, 24, 119), (505, 32, 247))):
            code += b"\x2d" + struct.pack("<I", lower) + b"\x3d" + struct.pack("<I", count - 1)
            code += b"\x0f\xb6" + (b"\x80" if index == 0 else b"\x88")
            remap_field = len(code)
            code += bytes(4) + b"\xff\x24" + (b"\x85" if index == 0 else b"\x8d")
            table_field = len(code)
            code += bytes(4)
            fixups.append((remap_field, table_field, words, count))
        destination = audit.START + len(code)
        code += b"\xc3\x90"
        offsets = []
        for remap_field, table_field, words, count in fixups:
            table = len(code)
            struct.pack_into("<I", code, table_field, audit.START + table)
            code += struct.pack("<" + "I" * words, *([destination] * words))
            remap = len(code)
            struct.pack_into("<I", code, remap_field, audit.START + remap)
            code += bytes(i % words for i in range(count))
            offsets.append((table, remap))
        return code, offsets

    def test_both_ranges_and_ecx_remap_are_retained(self):
        code, _ = self.fixture()
        _, edges, result = audit.decode_inventory(code)
        self.assertEqual(len(edges), 2)
        self.assertEqual([(t["first_case"], t["dwords"], t["remap_bytes"])
                          for t in result["tables"]], [(300, 24, 119), (505, 32, 247)])

    def test_final_high_remap_index_is_checked(self):
        code, offsets = self.fixture()
        code[offsets[1][1] + 246] = 32
        with self.assertRaisesRegex(ValueError, "destination/index"):
            audit.decode_inventory(code)

    def test_destination_cannot_point_into_metadata(self):
        code, offsets = self.fixture()
        struct.pack_into("<I", code, offsets[1][0], audit.START + offsets[0][0])
        with self.assertRaisesRegex(ValueError, "destination/index"):
            audit.decode_inventory(code)

    def test_last_remap_byte_cannot_be_truncated(self):
        code, _ = self.fixture()
        with self.assertRaisesRegex(ValueError, "extent escapes"):
            audit.decode_inventory(code[:-1])

    def test_unreviewed_cfg_tail_is_rejected(self):
        decoder = audit.capstone.Cs(audit.capstone.CS_ARCH_X86, audit.capstone.CS_MODE_32)
        decoder.detail = True
        code = b"\xe9" + struct.pack("<i", 0x478000 - audit.START - 5)
        with self.assertRaisesRegex(ValueError, "external target CFG tail"):
            audit.target_cfg(list(decoder.disasm(code, audit.START)), {})


if __name__ == "__main__":
    unittest.main()
