"""Guard complete EH relocation replay and unmasked region comparisons."""
from __future__ import annotations

import importlib.util
from pathlib import Path
import struct
import sys
from types import SimpleNamespace
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
spec = importlib.util.spec_from_file_location("select_ctor_audit", ROOT / "scripts/audit-select-constructor.py")
audit = importlib.util.module_from_spec(spec)
spec.loader.exec_module(audit)


class SelectConstructorEHTests(unittest.TestCase):
    def fixture(self, code, relocations, kind=".text$x"):
        raw = code + b"".join(struct.pack("<IIH", *r) for r in relocations)

        def read(offset, size):
            value = raw[offset:offset + size]
            if len(value) != size:
                raise ValueError("short COFF read")
            return value

        obj = SimpleNamespace(_read_raw=read, symbols={0: SimpleNamespace(name="destination")})
        section = SimpleNamespace(name=kind, characteristics=0, raw_offset=0,
                                  raw_size=len(code), reloc_offset=len(code),
                                  reloc_count=len(relocations))
        return obj, section

    def test_replays_late_code_relocation_and_preserves_entire_tail(self):
        code = bytes(64) + b"\xe8" + bytes(4) + b"\xc3"
        obj, section = self.fixture(code, [(65, 0, 20)])
        actual = audit.replay_section(obj, section, 0x1000, {"destination": 0x2000}, {}, None)
        self.assertEqual(len(actual), 70)
        self.assertEqual(struct.unpack_from("<i", actual, 65)[0], 0x2000 - 0x1045)
        self.assertEqual(actual[-1], 0xC3)

    def test_metadata_uses_verified_absolute_address_and_rejects_wrong_pin(self):
        obj, section = self.fixture(bytes(8), [(4, 0, 6)], ".xdata$x")
        data = {"destination": (0x2000, b"\xc3", frozenset([0]), "address")}
        actual = audit.replay_section(obj, section, 0x3000, {}, data, lambda a, n: b"\xc3")
        self.assertEqual(actual, bytes(4) + struct.pack("<I", 0x2000))
        with self.assertRaisesRegex(ValueError, "pin changed"):
            audit.replay_section(obj, section, 0x3000, {}, data, lambda a, n: b"\xcc")

    def test_unsupported_late_relocations_and_overlaps_are_rejected(self):
        for relocs, message in [([(12, 0, 7)], "unsupported EH relocation"),
                                ([(4, 0, 6), (6, 0, 6)], "overlapping"),
                                ([(14, 0, 6)], "escapes"),
                                ([(4, 9, 6)], "missing symbol")]:
            with self.subTest(relocations=relocs):
                obj, section = self.fixture(bytes(16), relocs)
                data = {"destination": (0x2000, b"\xc3", frozenset([0]), "address")}
                with self.assertRaisesRegex(ValueError, message):
                    audit.replay_section(obj, section, 0x1000, {}, data, lambda a, n: b"\xc3")

    def test_unreviewed_addend_and_data_rel32_are_rejected(self):
        obj, section = self.fixture(struct.pack("<I", 1), [(0, 0, 6)], ".xdata$x")
        data = {"destination": (0x2000, b"\xc3", frozenset([0, 1]), "address")}
        with self.assertRaisesRegex(ValueError, "role/addend"):
            audit.replay_section(obj, section, 0x3000, {}, data, lambda a, n: b"\xc3")
        obj, section = self.fixture(b"\xe8" + bytes(4), [(1, 0, 20)], ".xdata$x")
        with self.assertRaisesRegex(ValueError, "not a code"):
            audit.replay_section(obj, section, 0x3000, {"destination": 0x2000}, {}, None)

    def test_changed_or_extra_tail_byte_prevents_exactness(self):
        for candidate in (b"\x90\xcc", b"\x90\xc3\xcc"):
            result = audit.region_result(candidate, b"\x90\xc3", 0x1000)
            self.assertFalse(result["exact"])
            self.assertEqual(result["unmasked_differing_bytes"], 1)


if __name__ == "__main__":
    unittest.main()
