"""Synthetic controls for complete Yukari Object switch metadata ownership."""
from __future__ import annotations

import importlib.util
from pathlib import Path
import struct
import sys
import unittest

ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/"scripts"))
spec=importlib.util.spec_from_file_location("yukari_update_audit",ROOT/"scripts/audit-yukari-object-update.py")
audit=importlib.util.module_from_spec(spec)
spec.loader.exec_module(audit)


class YukariUpdateMetadataTests(unittest.TestCase):
    def fixture(self):
        # Synthetic code/metadata, no game target bytes.
        code=bytearray(b"\x0f\xb6\x80"+bytes(4))
        fixups=[]
        for index in range(20):
            code+=b"\xff\x24"+(b"\x8d" if index==19 else b"\x85")
            fixups.append(len(code))
            code+=bytes(4)
        destination=audit.START+len(code)
        code+=b"\xc3"
        offsets=[]
        for index,(fixup,words) in enumerate(zip(fixups,audit.TABLE_WORDS)):
            start=len(code)
            struct.pack_into("<I",code,fixup,audit.START+start)
            code+=struct.pack("<"+str(words)+"I",*([destination]*words))
            offsets.append(start)
            if index==0:
                remap=len(code)
                struct.pack_into("<I",code,3,audit.START+remap)
                code+=bytes(n%words for n in range(200))
        return code,offsets,remap

    def test_all_twenty_tables_and_primary_remap_are_retained(self):
        code,_,_=self.fixture()
        _,tables,report=audit.inventory(code)
        self.assertEqual(tuple(map(len,tables.values())),audit.TABLE_WORDS)
        self.assertEqual(report["remap_bytes"],200)
        self.assertEqual(set(report["cases"]),set(map(str,range(800,1000))))

    def test_last_primary_index_cannot_escape_table(self):
        code,_,remap=self.fixture()
        code[remap+199]=33
        with self.assertRaisesRegex(ValueError,"remap index"):
            audit.inventory(code)

    def test_last_remap_byte_is_action999(self):
        code,_,remap=self.fixture()
        code[remap+199]=32
        report=audit.inventory(code)[2]
        self.assertEqual(len(report["cases"]),200)
        self.assertIn("999",report["cases"])
        self.assertNotIn("remap_alignment_hex",report)

    def test_destination_cannot_point_into_metadata(self):
        code,offsets,_=self.fixture()
        struct.pack_into("<I",code,offsets[-1],audit.START+offsets[0])
        with self.assertRaisesRegex(ValueError,"destination count"):
            audit.inventory(code)

    def test_last_table_byte_cannot_be_truncated(self):
        code,_,_=self.fixture()
        with self.assertRaisesRegex(ValueError,"destination count"):
            audit.inventory(code[:-1])

    def test_reviewed_padding_requires_exact_address_and_bytes(self):
        decoder=audit.capstone.Cs(audit.capstone.CS_ARCH_X86,audit.capstone.CS_MODE_32)
        rows=list(decoder.disasm(b"\xc3\x90",audit.START))
        by_address={row.address:row for row in rows}
        expected={audit.START+1:"90"}
        self.assertEqual(audit.check_unreachable(by_address,{audit.START},expected),
                         {hex(audit.START+1):"90"})
        with self.assertRaisesRegex(ValueError,"unreviewed unreachable"):
            audit.check_unreachable(by_address,{audit.START},{audit.START+1:"cc"})
        with self.assertRaisesRegex(ValueError,"unreviewed unreachable"):
            audit.check_unreachable(by_address,{audit.START},{audit.START+2:"90"})

    def test_reviewed_padding_cannot_hide_an_extra_instruction(self):
        decoder=audit.capstone.Cs(audit.capstone.CS_ARCH_X86,audit.capstone.CS_MODE_32)
        rows=list(decoder.disasm(b"\xc3\x90\x90",audit.START))
        with self.assertRaisesRegex(ValueError,"unreviewed unreachable"):
            audit.check_unreachable({row.address:row for row in rows},{audit.START},
                                    {audit.START+1:"90"})

    def test_external_cfg_tail_is_rejected(self):
        decoder=audit.capstone.Cs(audit.capstone.CS_ARCH_X86,audit.capstone.CS_MODE_32)
        decoder.detail=True
        code=b"\xe9"+struct.pack("<i",0x477830-audit.START-5)
        with self.assertRaisesRegex(ValueError,"CFG edge escapes"):
            audit.closed_cfg(list(decoder.disasm(code,audit.START)),{})

    def default_fixture(self,extra=b"",callee=0x4351C0):
        decoder=audit.capstone.Cs(audit.capstone.CS_ARCH_X86,audit.capstone.CS_MODE_32)
        decoder.detail=True
        code=b"\xe8"+struct.pack("<i",callee-audit.START-5)+extra
        code+=b"\x5f\x5e\x5d\x5b\x81\xc4\x60\x02\0\0\xc3"
        return list(decoder.disasm(code,audit.START))

    def test_default_ignores_frame_result(self):
        self.assertTrue(audit.check_default_exit(self.default_fixture(),audit.START)["ignores_frame_result"])
        with self.assertRaisesRegex(ValueError,"ignore frame result"):
            audit.check_default_exit(self.default_fixture(b"\x84\xc0"),audit.START)
        with self.assertRaisesRegex(ValueError,"frame callee"):
            audit.check_default_exit(self.default_fixture(callee=0x435160),audit.START)

    def test_default_must_not_decrement_lifetime(self):
        with self.assertRaisesRegex(ValueError,"ignore frame result"):
            audit.check_default_exit(self.default_fixture(b"\x83\x86\x30\x03\0\0\xff"),audit.START)


if __name__=="__main__":
    unittest.main()
