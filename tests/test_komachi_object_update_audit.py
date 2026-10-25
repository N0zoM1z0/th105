"""Synthetic controls for complete Komachi Object switch metadata ownership."""
from __future__ import annotations

import importlib.util
from pathlib import Path
import struct
import sys
import unittest

ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/"scripts"))
spec=importlib.util.spec_from_file_location("komachi_update_audit",ROOT/"scripts/audit-komachi-object-update.py")
audit=importlib.util.module_from_spec(spec)
spec.loader.exec_module(audit)


class KomachiUpdateMetadataTests(unittest.TestCase):
    def fixture(self):
        # Synthetic code/metadata, no game target bytes.
        code=bytearray(b"\x0f\xb6\x80"+bytes(4))
        fixups=[]
        for index in range(15):
            code+=b"\xff\x24"+(b"\x8d" if index==14 else b"\x85")
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

    def test_all_fifteen_tables_and_primary_remap_are_retained(self):
        code,_,_=self.fixture()
        _,tables,report=audit.inventory(code)
        self.assertEqual(tuple(map(len,tables.values())),audit.TABLE_WORDS)
        self.assertEqual(report["remap_bytes"],200)
        self.assertEqual(set(report["cases"]),set(map(str,range(800,1000))))

    def test_last_primary_index_cannot_escape_table(self):
        code,_,remap=self.fixture()
        code[remap+199]=28
        with self.assertRaisesRegex(ValueError,"remap index"):
            audit.inventory(code)

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


class KomachiHeightCaptureTests(unittest.TestCase):
    def decode(self,code):
        decoder=audit.capstone.Cs(audit.capstone.CS_ARCH_X86,audit.capstone.CS_MODE_32)
        decoder.detail=True
        return list(decoder.disasm(code,audit.START))

    def rows(self,store=b"\xdd\x5c\x24\x10",compare=b"\xdc\x5c\x24\x10",callee=0x435D60):
        # Synthetic x87 stack accesses plus a relocated CALL; no target bytes.
        code=store+b"\xe8"+struct.pack("<i",callee-audit.START-len(store)-5)+compare
        return self.decode(code)

    def test_qword_is_captured_before_the_height_call(self):
        facts=audit.height_call_captures(self.rows())
        self.assertEqual(len(facts),1)
        self.assertEqual(facts[0]["width"],8)
        self.assertEqual(facts[0]["esp_displacement"],16)
        self.assertEqual(int(facts[0]["store"],16),audit.START)

    def test_float_store_cannot_prove_a_qword_capture(self):
        self.assertEqual(audit.height_call_captures(self.rows(store=b"\xd9\x5c\x24\x10")),[])

    def test_a_different_stack_slot_is_not_the_captured_value(self):
        self.assertEqual(audit.height_call_captures(self.rows(compare=b"\xdc\x5c\x24\x14")),[])

    def test_another_callee_is_not_a_height_capture(self):
        self.assertEqual(audit.height_call_captures(self.rows(callee=0x4351C0)),[])

    def test_post_call_store_does_not_prove_a_pre_call_capture(self):
        code=b"\xe8"+struct.pack("<i",0x435D60-audit.START-5)+b"\xdd\x5c\x24\x10\xdc\x5c\x24\x10"
        self.assertEqual(audit.height_call_captures(self.decode(code)),[])


if __name__=="__main__":
    unittest.main()
