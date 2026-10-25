"""Synthetic controls for complete Yuyuko Object switch metadata ownership."""
from __future__ import annotations

import importlib.util
from pathlib import Path
import struct
import sys
import unittest

ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/"scripts"))
spec=importlib.util.spec_from_file_location("yuyuko_update_audit",ROOT/"scripts/audit-yuyuko-object-update.py")
audit=importlib.util.module_from_spec(spec)
spec.loader.exec_module(audit)


class YuyukoUpdateMetadataTests(unittest.TestCase):
    def fixture(self):
        # Guarded synthetic x86 switches and metadata, no proprietary bytes.
        code=bytearray()
        jumps=[]
        remap_fixups=[]
        guard_fixups=[]
        edges=[]
        for index in range(16):
            if index<len(audit.REMAP_LENGTHS):
                code+=b"\x3d"
                guard_fixups.append(len(code))
                code+=struct.pack("<I",audit.REMAP_LENGTHS[index]-1)
                code+=b"\x0f\x87"
                edges.append(len(code))
                code+=bytes(4)
                code+=b"\x0f\xb6\x80"
                remap_fixups.append(len(code))
                code+=bytes(4)
            code+=b"\xff\x24\x85"
            jumps.append(len(code))
            code+=bytes(4)
        destination=audit.START+len(code)
        code+=b"\xc3"
        for edge in edges:
            struct.pack_into("<i",code,edge,destination-(audit.START+edge+4))
        offsets=[]
        for fixup,words in zip(jumps,audit.TABLE_WORDS):
            offsets.append(len(code))
            struct.pack_into("<I",code,fixup,audit.START+len(code))
            code+=struct.pack("<"+str(words)+"I",*([destination]*words))
        remaps=[]
        for index,(fixup,size) in enumerate(zip(remap_fixups,audit.REMAP_LENGTHS)):
            remaps.append(len(code))
            struct.pack_into("<I",code,fixup,audit.START+len(code))
            code+=bytes(n%audit.TABLE_WORDS[index] for n in range(size))
        return code,offsets,remaps,guard_fixups

    def test_all_sixteen_tables_and_seven_remaps_are_retained(self):
        code,_,_,_=self.fixture()
        _,tables,report=audit.inventory(code)
        self.assertEqual(tuple(map(len,tables.values())),audit.TABLE_WORDS)
        self.assertEqual(report["total_remap_bytes"],291)
        self.assertEqual(tuple(r["size"]for r in report["remaps"]),audit.REMAP_LENGTHS)
        self.assertEqual(set(report["cases"]),set(map(str,range(800,999))))

    def test_last_primary_index_cannot_escape_table(self):
        code,_,remaps,_=self.fixture()
        code[remaps[0]+198]=29
        with self.assertRaisesRegex(ValueError,"remap index"):
            audit.inventory(code)

    def test_last_remap_byte_is_action998_not999(self):
        code,_,remaps,_=self.fixture()
        code[remaps[0]+198]=28
        report=audit.inventory(code)[2]
        self.assertEqual(len(report["cases"]),199)
        self.assertIn("998",report["cases"])
        self.assertNotIn("999",report["cases"])

    def test_nested_remap_index_cannot_escape_its_own_table(self):
        code,_,remaps,_=self.fixture()
        code[remaps[3]+16]=audit.TABLE_WORDS[3]
        with self.assertRaisesRegex(ValueError,"remap index"):
            audit.inventory(code)

    def test_nested_guard_bounds_are_not_silently_inherited(self):
        code,_,_,guards=self.fixture()
        struct.pack_into("<I",code,guards[2],13)
        with self.assertRaisesRegex(ValueError,"remap bounds"):
            audit.inventory(code)

    def test_destination_cannot_point_into_metadata(self):
        code,offsets,_,_=self.fixture()
        struct.pack_into("<I",code,offsets[-1],audit.START+offsets[0])
        with self.assertRaisesRegex(ValueError,"destination count"):
            audit.inventory(code)

    def test_last_remap_byte_cannot_be_truncated(self):
        code,_,_,_=self.fixture()
        with self.assertRaisesRegex(ValueError,"remap extent"):
            audit.inventory(code[:-1])

    def test_table_cut_is_rejected(self):
        code,offsets,_,_=self.fixture()
        struct.pack_into("<I",code,offsets[-1]+4,audit.START+offsets[0])
        with self.assertRaisesRegex(ValueError,"destination count"):
            audit.inventory(code)

    def test_unowned_metadata_tail_is_rejected(self):
        code,_,_,_=self.fixture()
        with self.assertRaisesRegex(ValueError,"unowned tail"):
            audit.inventory(code+b"\x90")

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
        code+=b"\x5f\x5e\x5d\x5b\x81\xc4\x38\x02\0\0\xc3"
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
