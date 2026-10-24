"""Reject malformed metadata for all three Yukari initializer switch regions."""
from __future__ import annotations

import importlib.util
from pathlib import Path
import struct
import sys
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
spec = importlib.util.spec_from_file_location(
    "yukari_initialization_audit", ROOT / "scripts/audit-yukari-action-initialization.py")
audit = importlib.util.module_from_spec(spec)
spec.loader.exec_module(audit)


class YukariInitializationMetadataTests(unittest.TestCase):
    def fixture(self):
        # Synthetic instructions/metadata; no target executable bytes.
        instructions, fixups = bytearray(), []
        regions = ((4, 14, 211), (301, 26, 248), (562, 17, 237))
        for index, (lower, words, count) in enumerate(regions):
            instructions += b"\x2d" + struct.pack("<I", lower) + b"\x3d" + struct.pack("<I", count - 1)
            # The actual third cluster uses ECX as its byte-table index.
            instructions += b"\x0f\xb6" + (b"\x88" if index == 2 else b"\x80")
            remap_field = len(instructions)
            instructions += bytes(4) + b"\xff\x24" + (b"\x8d" if index == 2 else b"\x85")
            table_field = len(instructions)
            instructions += bytes(4)
            fixups.append((remap_field, table_field, words, count))
        destination = audit.START + len(instructions)
        instructions += b"\xc3\x90"
        payload = instructions.copy()
        tables = []
        for remap_field, table_field, words, count in fixups:
            table = len(payload)
            payload += struct.pack("<" + "I" * words, *([destination] * words))
            remap = len(payload)
            payload += bytes(i % words for i in range(count))
            struct.pack_into("<I", payload, remap_field, audit.START + remap)
            struct.pack_into("<I", payload, table_field, audit.START + table)
            tables.append((table, remap))
        return payload, tables

    def test_all_regions_and_ecx_index_keep_complete_metadata(self):
        code, _ = self.fixture()
        _, edges, inventory = audit.decode_inventory(code)
        self.assertEqual(len(edges), 3)
        self.assertEqual([(t["first_case"], t["dwords"], t["remap_bytes"])
                          for t in inventory["tables"]], [(4, 14, 211), (301, 26, 248), (562, 17, 237)])

    def test_invalid_last_remap_index_is_rejected(self):
        code, tables = self.fixture()
        code[tables[-1][1] + 236] = 17
        with self.assertRaisesRegex(ValueError, "destination/index"):
            audit.decode_inventory(code)

    def test_destination_cannot_point_into_metadata(self):
        code, tables = self.fixture()
        struct.pack_into("<I", code, tables[-1][0], audit.START + tables[0][0])
        with self.assertRaisesRegex(ValueError, "destination/index"):
            audit.decode_inventory(code)

    def test_truncated_last_remap_is_rejected(self):
        code, _ = self.fixture()
        with self.assertRaisesRegex(ValueError, "extent escapes"):
            audit.decode_inventory(code[:-1])

    def test_unreviewed_external_tail_is_rejected(self):
        decoder = audit.capstone.Cs(audit.capstone.CS_ARCH_X86, audit.capstone.CS_MODE_32)
        decoder.detail = True
        code = b"\xe9" + struct.pack("<i", 0x478000 - audit.START - 5)
        with self.assertRaisesRegex(ValueError, "external target CFG tail"):
            audit.target_cfg(list(decoder.disasm(code, audit.START)), {})


if __name__ == "__main__":
    unittest.main()
