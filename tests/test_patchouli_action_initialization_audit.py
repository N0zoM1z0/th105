"""Keep the two remaps and LEA-based direct card table fail-closed."""
from __future__ import annotations

import importlib.util
from pathlib import Path
import struct
import sys
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
spec = importlib.util.spec_from_file_location(
    "patchouli_initialization_audit", ROOT / "scripts/audit-patchouli-action-initialization.py")
audit = importlib.util.module_from_spec(spec)
spec.loader.exec_module(audit)


class PatchouliInitializationMetadataTests(unittest.TestCase):
    def fixture(self):
        # Synthetic bytecode/data, independent of private target bytes.
        code, fixups = bytearray(), []
        for index, (lower, words, count) in enumerate(((198, 23, 221), (505, 33, 226), (100, 15, 0))):
            code += b"\x90"  # Zero-operand instructions may precede a switch.
            if count:
                code += b"\x2d" + struct.pack("<I", lower) + b"\x3d" + struct.pack("<I", count - 1)
                code += b"\x0f\xb6" + (b"\x80" if index == 0 else b"\x88")
                remap_field = len(code)
                code += bytes(4)
            else:
                code += b"\x8d\x41\x9c\x83\xf8\x0e"
                remap_field = None
            code += b"\xff\x24" + (b"\x8d" if index == 1 else b"\x85")
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
            if remap_field is not None:
                struct.pack_into("<I", code, remap_field, audit.START + remap)
                code += bytes(i % words for i in range(count))
            offsets.append((table, remap))
        return code, offsets

    def test_both_remaps_and_direct_lea_range_survive(self):
        code, _ = self.fixture()
        _, edges, _, result = audit.inventory(code)
        self.assertEqual(len(edges), 3)
        self.assertEqual([(t["first_case"], t["dwords"], t["remap_bytes"])
                          for t in result["tables"]], [(198, 23, 221), (505, 33, 226), (100, 15, 0)])

    def test_last_high_remap_index_is_checked(self):
        code, offsets = self.fixture()
        code[offsets[1][1] + 225] = 33
        with self.assertRaisesRegex(ValueError, "table/index"):
            audit.inventory(code)

    def test_direct_destination_cannot_point_at_metadata(self):
        code, offsets = self.fixture()
        struct.pack_into("<I", code, offsets[-1][0], audit.START + offsets[0][0])
        with self.assertRaisesRegex(ValueError, "outside code"):
            audit.inventory(code)

    def test_last_direct_word_cannot_be_truncated(self):
        code, _ = self.fixture()
        with self.assertRaisesRegex(ValueError, "table/index"):
            audit.inventory(code[:-1])

    def test_unreviewed_main_edge_is_rejected(self):
        decoder = audit.capstone.Cs(audit.capstone.CS_ARCH_X86, audit.capstone.CS_MODE_32)
        decoder.detail = True
        code = b"\xe9" + struct.pack("<i", 0x51D700 - audit.START - 5)
        with self.assertRaisesRegex(ValueError, "misses a main instruction"):
            audit.close_target_cfg(list(decoder.disasm(code, audit.START)), {})


if __name__ == "__main__":
    unittest.main()
