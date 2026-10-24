"""Reject invalid switch metadata before using its diagnostic ownership facts."""
from __future__ import annotations

import importlib.util
from pathlib import Path
import struct
import sys
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
spec = importlib.util.spec_from_file_location(
    "reimu_initialization_audit", ROOT / "scripts/audit-reimu-action-initialization.py")
audit = importlib.util.module_from_spec(spec)
spec.loader.exec_module(audit)


class ReimuInitializationMetadataTests(unittest.TestCase):
    def fixture(self):
        # Three synthetic switches, sharing a RET. No game bytes are used.
        instructions, fixups = bytearray(), []
        for lower in (10, 20, 30):
            instructions += b"\x2d" + struct.pack("<I", lower) + b"\x83\xf8\x02"
            instructions += b"\x0f\xb6\x80"
            remap_field = len(instructions)
            instructions += bytes(4) + b"\xff\x24\x85"
            table_field = len(instructions)
            instructions += bytes(4)
            fixups.append((remap_field, table_field))
        destination = audit.START + len(instructions)
        instructions += b"\xc3\x90"
        payload = instructions.copy()
        tables = []
        for remap_field, table_field in fixups:
            table = len(payload)
            payload += struct.pack("<III", destination, destination, destination)
            remap = len(payload)
            payload += bytes([0, 1, 2])
            struct.pack_into("<I", payload, remap_field, audit.START + remap)
            struct.pack_into("<I", payload, table_field, audit.START + table)
            tables.append((table, remap))
        return payload, tables

    def test_three_complete_tables_keep_their_ranges_and_counts(self):
        code, _ = self.fixture()
        _, edges, inventory = audit.decode_inventory(code)
        self.assertEqual(len(edges), 3)
        self.assertEqual([t["first_case"] for t in inventory["tables"]], [10, 20, 30])
        self.assertEqual([t["dwords"] for t in inventory["tables"]], [3, 3, 3])
        self.assertEqual([t["remap_bytes"] for t in inventory["tables"]], [3, 3, 3])

    def test_out_of_range_index_in_last_table_is_rejected(self):
        code, tables = self.fixture()
        code[tables[-1][1] + 2] = 3
        with self.assertRaisesRegex(ValueError, "destination/index"):
            audit.decode_inventory(code)

    def test_metadata_pointer_cannot_be_a_destination(self):
        code, tables = self.fixture()
        struct.pack_into("<I", code, tables[-1][0], audit.START + tables[0][0])
        with self.assertRaisesRegex(ValueError, "destination/index"):
            audit.decode_inventory(code)

    def test_truncated_last_remap_is_rejected(self):
        code, _ = self.fixture()
        with self.assertRaisesRegex(ValueError, "extent escapes"):
            audit.decode_inventory(code[:-1])

    def test_unreviewed_external_cfg_tail_is_rejected(self):
        decoder = audit.capstone.Cs(audit.capstone.CS_ARCH_X86, audit.capstone.CS_MODE_32)
        decoder.detail = True
        code = b"\xe9" + struct.pack("<i", 0x478000 - audit.START - 5)
        with self.assertRaisesRegex(ValueError, "external target CFG tail"):
            audit.target_cfg(list(decoder.disasm(code, audit.START)), {})


if __name__ == "__main__":
    unittest.main()
