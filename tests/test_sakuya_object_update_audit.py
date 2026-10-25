"""Synthetic controls for complete Sakuya Object switch metadata ownership."""
from __future__ import annotations

import importlib.util
from pathlib import Path
import struct
import sys
import unittest

ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/"scripts"))
spec=importlib.util.spec_from_file_location("sakuya_update_audit",ROOT/"scripts/audit-sakuya-object-update.py")
audit=importlib.util.module_from_spec(spec)
spec.loader.exec_module(audit)


class SakuyaUpdateMetadataTests(unittest.TestCase):
    def fixture(self):
        # Synthetic code/metadata, no game target bytes.
        code=bytearray(b"\x0f\xb6\x80"+bytes(4))
        fixups=[]
        for index in range(7):
            code+=b"\xff\x24"+(b"\x8d" if index==6 else b"\x85")
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

    def test_all_seven_tables_and_primary_remap_are_retained(self):
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

    def test_destination_cannot_point_into_metadata(self):
        code,offsets,_=self.fixture()
        struct.pack_into("<I",code,offsets[-1],audit.START+offsets[0])
        with self.assertRaisesRegex(ValueError,"destination count"):
            audit.inventory(code)

    def test_last_table_byte_cannot_be_truncated(self):
        code,_,_=self.fixture()
        with self.assertRaisesRegex(ValueError,"destination count"):
            audit.inventory(code[:-1])

    def test_external_cfg_tail_is_rejected(self):
        decoder=audit.capstone.Cs(audit.capstone.CS_ARCH_X86,audit.capstone.CS_MODE_32)
        decoder.detail=True
        code=b"\xe9"+struct.pack("<i",0x477830-audit.START-5)
        with self.assertRaisesRegex(ValueError,"CFG edge escapes"):
            audit.closed_cfg(list(decoder.disasm(code,audit.START)),{})


if __name__=="__main__":
    unittest.main()
