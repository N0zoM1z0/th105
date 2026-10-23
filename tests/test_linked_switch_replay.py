from __future__ import annotations

import copy
import hashlib
from pathlib import Path
import struct
import sys
from types import SimpleNamespace
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "scripts"))
import linked_pe
import linked_switch_replay as replay


class LinkedSwitchReplayTests(unittest.TestCase):
    def setUp(self):
        # Synthetic parser fixture, not reconstructed game code or an exact unit.
        self.start, self.end, self.target = 0x10001000, 0x10001030, 0x620920
        self.literal = bytes.fromhex("000000000000f03f")
        raw = (b"\xe8" + struct.pack("<i", 0x10002000 - self.start - 5)
               + b"\xdd\x05" + struct.pack("<I", 0x10003000)
               + b"\xa1" + struct.pack("<I", 0x6FA894)
               + b"\x0f\xb6\x88" + struct.pack("<I", self.start + 36)
               + b"\xff\x24\x8d" + struct.pack("<I", self.start + 32)
               + b"\xc3\x90" + struct.pack("<I", self.start + 30)
               + b"\0\0" + b"\xcc" * 10)
        self.image = bytearray(0x4000)
        self.image[0x1000:0x1030] = raw
        self.image[0x3000:0x3008] = self.literal
        readonly = SimpleNamespace(VirtualAddress=0x3000, Misc_VirtualSize=0x100, SizeOfRawData=0x100,
                                   Characteristics=0x40000040)
        self.pe = SimpleNamespace(
            OPTIONAL_HEADER=SimpleNamespace(ImageBase=0x10000000, SizeOfImage=0x4000),
            DIRECTORY_ENTRY_BASERELOC=[SimpleNamespace(entries=[
                SimpleNamespace(rva=0x1000 + n, type=3) for n in (7, 19, 26, 32)])],
            get_data=lambda rva, size: bytes(self.image[rva:rva + size]),
            get_section_by_rva=lambda rva: readonly if 0x3000 <= rva < 0x3100 else None,
        )
        game_section = SimpleNamespace(VirtualAddress=0x2F0000, Misc_VirtualSize=0x10000,
                                       Characteristics=0xC0000040)
        self.game = SimpleNamespace(
            OPTIONAL_HEADER=SimpleNamespace(ImageBase=0x400000),
            get_section_by_rva=lambda rva: game_section,
        )
        self.map_text = (" 0001:00002000 _helper 10002000 f helper.obj\n"
                         " 0002:00003000 __real@3ff0000000000000 10003000 literal.obj\n")
        known = {
            "__real@3ff0000000000000": (0x6C0000, self.literal, frozenset({0}), "literal"),
            "game": (0x6FA894, b"\0" * 4, frozenset({0}), "literal"),
        }
        target_data = {0x6C0000: self.literal, 0x6FA894: b"\0" * 4}
        self.canonical = SimpleNamespace(
            known_data_targets=lambda: known,
            target_bytes=lambda address, size: target_data[address][:size],
            dir32_target_key=linked_pe.comparator().dir32_target_key,
            real_literal_bytes=linked_pe.comparator().real_literal_bytes,
        )
        self.inspection = {
            "root_callable_and_padding_bytes": 32,
            "switches": [{"dispatch": hex(self.start + 23), "table": hex(self.start + 32),
                          "destination_count": 1, "index_count": 2,
                          "indices_sha256": hashlib.sha256(b"\0\0").hexdigest()}],
        }
        self.bindings = [{"address": 0x6FA894, "key": "game", "data_hex": "00000000", "addends": [0]}]
        self.calls = {"_helper": 0x401000}

    def run_replay(self, **options):
        return replay.replay_root(
            self.pe, self.map_text, self.start, self.end, self.inspection,
            self.target, self.canonical, self.calls, self.bindings, {}, game_pe=self.game, **options,
        )

    def test_all_proved_fields_replay_and_every_other_byte_survives(self):
        result, report = self.run_replay()
        expected = bytearray(self.image[0x1000:0x1030])
        for offset, value in ((7, 0x6C0000), (19, self.target + 36),
                              (26, self.target + 32), (32, self.target + 30)):
            struct.pack_into("<I", expected, offset, value)
        struct.pack_into("<i", expected, 1, 0x401000 - self.target - 5)
        self.assertEqual(result, expected)
        self.assertEqual(report["highlow_fields"], 4)
        self.assertEqual(report["metadata_end_offset"], 38)
        self.assertEqual(report["trailing_link_alignment_hex"], "cc" * 10)
        # Ordinary instruction mutation remains visible; no opcode masking.
        self.image[0x100B] = 0xA3
        changed, _ = self.run_replay()
        self.assertEqual(changed[11], 0xA3)
        self.assertNotEqual(result, changed)

    def test_wrong_literal_bytes_map_contract_and_section_fail(self):
        self.image[0x3000] = 1
        with self.assertRaisesRegex(ValueError, "literal bytes"):
            self.run_replay()
        self.image[0x3000] = 0
        saved = self.map_text
        self.map_text = saved.replace("3ff0000000000000", "4000000000000000")
        with self.assertRaisesRegex(ValueError, "literal lacks canonical contract"):
            self.run_replay()
        self.map_text = saved
        self.image[0x1005:0x1007] = b"\xdb\x2d"  # FLD reads ten bytes from an eight-byte literal.
        with self.assertRaisesRegex(ValueError, "literal bytes, width"):
            self.run_replay()
        self.image[0x1005:0x1007] = b"\xdd\x05"
        section = self.pe.get_section_by_rva(0x3000)
        section.SizeOfRawData = 4
        with self.assertRaisesRegex(ValueError, "literal bytes"):
            self.run_replay()
        section.SizeOfRawData = 0x100
        for flag in (0x80000000, 0x80, 0x20000000):
            section.Characteristics = 0x40000040 | flag
            with self.subTest(flag=flag), self.assertRaisesRegex(ValueError, "literal bytes"):
                self.run_replay()

    def test_missing_duplicate_partial_and_unsupported_relocations_fail(self):
        original = copy.deepcopy(self.pe.DIRECTORY_ENTRY_BASERELOC)
        for entries in (
            original[0].entries[1:],
            original[0].entries + [original[0].entries[0]],
            original[0].entries + [SimpleNamespace(rva=0xFFF, type=3)],
            original[0].entries + [SimpleNamespace(rva=0x102E, type=3)],
            original[0].entries + [SimpleNamespace(rva=0x1001, type=1)],
        ):
            with self.subTest(entries=entries):
                self.pe.DIRECTORY_ENTRY_BASERELOC = [SimpleNamespace(entries=entries)]
                with self.assertRaises(ValueError):
                    self.run_replay()

    def test_switch_destinations_indices_and_tail_remain_attested(self):
        original = bytes(self.image)
        for offset, value in ((0x1020, self.start + 1), (0x1024, 1), (0x102F, 0x90)):
            self.image[:] = original
            if offset == 0x1020:
                struct.pack_into("<I", self.image, offset, value)
            else:
                self.image[offset] = value
            with self.subTest(offset=offset), self.assertRaises(ValueError):
                self.run_replay()

    def test_unknown_call_and_game_data_identity_fail(self):
        self.calls = {}
        with self.assertRaisesRegex(ValueError, "root call"):
            self.run_replay()
        self.calls = {"_helper": 0x401000}
        self.bindings[0]["data_hex"] = "01000000"
        with self.assertRaisesRegex(ValueError, "binding differs"):
            self.run_replay()
        self.bindings = []
        with self.assertRaisesRegex(ValueError, "memory address"):
            self.run_replay()

    def test_external_tail_needs_site_and_exact_unique_map_identity(self):
        self.image[0x1000] = 0xE9
        with self.assertRaisesRegex(ValueError, "unqualified"):
            self.run_replay()
        result, report = self.run_replay(qualified_direct_tails={self.start: 0x401000})
        self.assertEqual(result[0], 0xE9)
        self.assertEqual(struct.unpack_from("<i", result, 1)[0], 0x401000 - self.target - 5)
        self.assertEqual(report["replayed"]["qualified_direct_tails"], 1)
        for qualifications in ({self.start: 0x401001}, {self.start + 1: 0x401000}):
            with self.assertRaisesRegex(ValueError, "unqualified"):
                self.run_replay(qualified_direct_tails=qualifications)
        with self.assertRaisesRegex(ValueError, "unused"):
            self.run_replay(qualified_direct_tails={self.start: 0x401000, self.start + 5: 0x401000})
        self.map_text += " 0001:00002000 _alias 10002000 f helper.obj\n"
        with self.assertRaisesRegex(ValueError, "unqualified"):
            self.run_replay(qualified_direct_tails={self.start: 0x401000})

    def test_call_cannot_consume_a_tail_qualification(self):
        with self.assertRaisesRegex(ValueError, "unused"):
            self.run_replay(qualified_direct_tails={self.start: 0x401000})

    def dense_fixture(self):
        # Independent two-case CMP/JA dispatch, with no byte index table.
        self.image[0x1000:0x1030] = (
            b"\xe8" + struct.pack("<i", 0x10002000 - self.start - 5)
            + b"\xdd\x05" + struct.pack("<I", 0x10003000)
            + b"\xa1" + struct.pack("<I", 0x6FA894)
            + b"\x83\xf8\x01\x77\x09"
            + b"\xff\x24\x85" + struct.pack("<I", self.start + 32)
            + b"\xc3\xc3\xc3\x90"
            + struct.pack("<II", self.start + 28, self.start + 29)
            + b"\xcc" * 8
        )
        self.pe.DIRECTORY_ENTRY_BASERELOC[0].entries = [
            SimpleNamespace(rva=0x1000 + offset, type=3) for offset in (7, 24, 32, 36)
        ]
        self.inspection["switches"] = [{
            "dispatch": hex(self.start + 21), "table": hex(self.start + 32),
            "destination_count": 2, "index_count": 0,
        }]

    def test_dense_switch_replays_both_destinations_without_inventing_indices(self):
        self.dense_fixture()
        result, report = self.run_replay()
        expected = bytearray(self.image[0x1000:0x1030])
        struct.pack_into("<i", expected, 1, 0x401000 - self.target - 5)
        for offset, value in ((7, 0x6C0000), (24, self.target + 32),
                              (32, self.target + 28), (36, self.target + 29)):
            struct.pack_into("<I", expected, offset, value)
        self.assertEqual(result, expected)
        self.assertEqual(report["metadata_end_offset"], 40)
        self.assertEqual(report["highlow_fields"], 4)
        self.assertEqual(report["replayed"]["switch_addresses"], 1)
        self.assertEqual(report["replayed"]["switch_destinations"], 2)

    def test_dense_bound_width_register_guard_and_count_must_agree(self):
        self.dense_fixture()
        original = bytes(self.image)
        for offset, value in ((16, 0x80),  # CMP AL cannot bound EAX.
                              (18, 2),     # Three cases cannot qualify two entries.
                              (19, 0x76),  # JBE does not reject unsigned outliers.
                              (20, 0),     # Default cannot re-enter the dispatch.
                              (20, 11),    # Default cannot enter metadata.
                              (23, 0x8D)): # ECX table index differs from bounded EAX.
            self.image[:] = original
            self.image[0x1000 + offset] = value
            with self.subTest(offset=offset), self.assertRaisesRegex(ValueError, "dense switch"):
                self.run_replay()

    def test_dense_destination_and_address_fields_need_all_relocations(self):
        self.dense_fixture()
        original = copy.deepcopy(self.pe.DIRECTORY_ENTRY_BASERELOC)
        for missing in (7, 24, 32, 36):
            self.pe.DIRECTORY_ENTRY_BASERELOC = copy.deepcopy(original)
            self.pe.DIRECTORY_ENTRY_BASERELOC[0].entries = [
                entry for entry in original[0].entries if entry.rva != 0x1000 + missing
            ]
            with self.subTest(missing=missing), self.assertRaises(ValueError):
                self.run_replay()


if __name__ == "__main__":
    unittest.main()
