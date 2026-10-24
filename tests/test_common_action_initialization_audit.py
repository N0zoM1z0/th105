"""Fail closed when either remapped or direct switch ownership is malformed."""
from __future__ import annotations

import importlib.util
from pathlib import Path
import struct
import sys
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
spec = importlib.util.spec_from_file_location("common_entry_audit", ROOT / "scripts/audit-common-action-initialization.py")
audit = importlib.util.module_from_spec(spec)
spec.loader.exec_module(audit)


class CommonEntryMetadataTests(unittest.TestCase):
    def fixture(self):
        # Synthetic input clusters, not bytes from the target executable.
        code = bytearray(b"\x3d" + struct.pack("<I", 226) + b"\x0f\xb6\x80")
        low_map = len(code)
        code += bytes(4) + b"\xff\x24\x85"
        low_table = len(code)
        code += bytes(4) + b"\x83\xc0\x9c\x83\xf8\x0f\xff\x24\x85"
        nested_table = len(code)
        code += bytes(4) + b"\x2d" + struct.pack("<I", 691) + b"\x83\xf8\x6c\x0f\xb6\x88"
        high_map = len(code)
        code += bytes(4) + b"\xff\x24\x8d"
        high_table = len(code)
        code += bytes(4)
        destination = audit.START + len(code)
        code += b"\xc3\x90"
        offsets = []
        for table_field, map_field, words, count in ((low_table, low_map, 50, 227),
                                                     (nested_table, None, 16, 0),
                                                     (high_table, high_map, 17, 109)):
            table = len(code)
            struct.pack_into("<I", code, table_field, audit.START + table)
            code += struct.pack("<" + "I" * words, *([destination] * words))
            remap = len(code)
            if map_field is not None:
                struct.pack_into("<I", code, map_field, audit.START + remap)
                code += bytes(i % words for i in range(count))
            offsets.append((table, remap))
        return code, offsets

    def test_both_remapped_clusters_and_direct_card_table_are_retained(self):
        code, _ = self.fixture()
        _, _, _, result = audit.inventory(code)
        self.assertEqual([(t["first_case"], t["dwords"], t["remap_bytes"])
                          for t in result["tables"]], [(0, 50, 227), (100, 16, 0), (691, 17, 109)])

    def test_invalid_final_remap_index_is_rejected(self):
        code, offsets = self.fixture()
        code[offsets[-1][1] + 108] = 17
        with self.assertRaisesRegex(ValueError, "table/index"):
            audit.inventory(code)

    def test_direct_table_cannot_point_into_metadata(self):
        code, offsets = self.fixture()
        struct.pack_into("<I", code, offsets[1][0], audit.START + offsets[0][0])
        with self.assertRaisesRegex(ValueError, "outside code"):
            audit.inventory(code)

    def test_truncated_last_remap_is_rejected(self):
        code, _ = self.fixture()
        with self.assertRaisesRegex(ValueError, "extent escapes"):
            audit.inventory(code[:-1])

    def test_unreviewed_external_tail_is_rejected(self):
        decoder = audit.capstone.Cs(audit.capstone.CS_ARCH_X86, audit.capstone.CS_MODE_32)
        decoder.detail = True
        code = b"\xe9" + struct.pack("<i", 0x478000 - audit.START - 5)
        # 478000 is in the reviewed main, so it misses this synthetic packet's
        # instruction inventory rather than silently becoming another function.
        with self.assertRaisesRegex(ValueError, "misses a main instruction"):
            audit.close_target_cfg(list(decoder.disasm(code, audit.START)), {})


if __name__ == "__main__":
    raise SystemExit(unittest.main())
