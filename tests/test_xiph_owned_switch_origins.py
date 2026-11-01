import copy
from pathlib import Path
import struct
import sys
import unittest
from types import SimpleNamespace

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "scripts"))
import xiph_owned_switch_origins as x


class XiphOwnedSwitchTests(unittest.TestCase):
    def fixture(self):
        base, size = 0x1000, 24
        code = b"\x83\xf8\x07\x77\x12\xff\x24\x85" + struct.pack("<I", base+size)
        canonical = code + b"\x90"*11 + b"\xc3" + struct.pack("<8I", *([base+23]*8))
        raw = bytearray(canonical)
        struct.pack_into("<I", raw, 8, size)
        for a in range(size, len(raw), 4):
            struct.pack_into("<I", raw, a, 23)
        return dict(raw=bytes(raw), canonical=canonical, native=canonical,
                    base=base, code_size=size,
                    relocations=[(8,6)]+[(a,6) for a in range(size,len(raw),4)],
                    targets={})

    def mutate_code(self, args, offset, values):
        for key in ("raw", "canonical", "native"):
            b=bytearray(args[key]);b[offset:offset+len(values)]=values;args[key]=bytes(b)

    def test_full_code_and_owned_table(self):
        proof=x.qualify(**self.fixture())
        self.assertEqual(proof["payload_bytes"],56)
        self.assertEqual(proof["masked_bytes"],0)
        self.assertEqual(proof["unequal_bytes"],0)

    def test_wrong_native_byte(self):
        a=self.fixture();a["native"]=b"\x90"+a["native"][1:]
        with self.assertRaisesRegex(ValueError,"whole SDK"):x.qualify(**a)

    def test_missing_suffix(self):
        a=self.fixture()
        for k in ("raw","canonical","native"):a[k]=a[k][:-4]
        with self.assertRaisesRegex(ValueError,"eight owned"):x.qualify(**a)

    def test_wrong_bound_and_signed_guard(self):
        for offset, value in [(2,b"\x08"),(3,b"\x7f")]:
            a=self.fixture();self.mutate_code(a,offset,value)
            with self.assertRaisesRegex(ValueError,"unsigned"):x.qualify(**a)

    def test_table_pointer_outside_suffix(self):
        a=self.fixture();self.mutate_code(a,8,struct.pack("<I",0x101c))
        with self.assertRaisesRegex(ValueError,"unsigned"):x.qualify(**a)

    def test_table_entry_mid_instruction(self):
        a=self.fixture()
        for k in ("canonical","native"):
            b=bytearray(a[k]);struct.pack_into("<I",b,24,0x1001);a[k]=bytes(b)
        with self.assertRaisesRegex(ValueError,"switch entry"):x.qualify(**a)

    def test_guard_bypass(self):
        a=self.fixture();self.mutate_code(a,12,b"\xeb\xf5")
        with self.assertRaisesRegex(ValueError,"bypassed"):x.qualify(**a)

    def test_extra_or_missing_relocations(self):
        for alter in [lambda a:a["relocations"].append((0,6)),
                      lambda a:a["relocations"].pop(),
                      lambda a:a["relocations"].append((8,6)),
                      lambda a:a["relocations"].append((3,7))]:
            a=self.fixture();alter(a)
            with self.assertRaises(ValueError):x.qualify(**a)

    def test_unaccounted_call(self):
        a=self.fixture();self.mutate_code(a,12,b"\xe8\x00\x00\x00\x00")
        with self.assertRaisesRegex(ValueError,"external call"):x.qualify(**a)

    def test_unclaimed_rel32(self):
        a=self.fixture();a["relocations"].append((13,20))
        with self.assertRaisesRegex(ValueError,"call inventory"):x.qualify(**a)

    def test_changes_outside_link_fields(self):
        a=self.fixture();b=bytearray(a["raw"]);b[12]=0xcc;a["raw"]=bytes(b)
        with self.assertRaisesRegex(ValueError,"non-link"):x.qualify(**a)

    def test_no_schema_waivers(self):
        spec=dict(component="vorbis",object="codebook.obj",symbol=x.SYMBOL,
                  address="0x00681C70",size=880,payload_sha256="a"*64)
        for change in [lambda s:s.update(min_nonreloc_bytes=1),
                       lambda s:s.update(size=True),
                       lambda s:s.update(symbol="_unproved"),
                       lambda s:s.update(address="0x00401000")]:
            s=copy.deepcopy(spec);change(s)
            errors=x.validate(dict(id="test",xiph_owned_switch=s),
                              [dict(address="0x00681C70",size="880")],[],
                              None,SimpleNamespace())
            self.assertTrue(errors)
            self.assertIn("identity or extent",errors[0])

    def four_fixture(self):
        base,size,table=0x1000,26,28
        code=b"\x83\xf8\x03\x77\x14\xff\x24\x85"+struct.pack("<I",base+table)
        body=code+b"\x90"*13+b"\xc3"+b"\x8b\xff"
        body+=struct.pack("<4I",*([base+25]*4))+b"\x90"*12
        raw=bytearray(body);struct.pack_into("<I",raw,8,table)
        for at in range(table,table+16,4):struct.pack_into("<I",raw,at,25)
        return dict(raw=bytes(raw),canonical=body,native=body,base=base,code_size=size,
                    relocations=[(8,6)]+[(a,6)for a in range(table,table+16,4)],
                    targets={},layout=dict(table_offset=table,table_count=4,
                        prefix=b"\x8b\xff",suffix=b"\x90"*12,absolute_fields={}))

    def add_absolute(self,a,offset,opcode,target,kind):
        self.mutate_code(a,offset,opcode+struct.pack("<I",target))
        b=bytearray(a["raw"]);struct.pack_into("<I",b,offset+1,0);a["raw"]=bytes(b)
        a["relocations"].append((offset+1,6))
        a["layout"]["absolute_fields"][offset+1]=(target,kind)

    def test_four_entries_with_exact_alignment(self):
        p=x.qualify(**self.four_fixture())
        self.assertEqual(p["alignment_bytes"],14)
        self.assertEqual(len(p["table_entries"]),4)

    def test_alignment_not_masked(self):
        a=self.four_fixture();self.mutate_code(a,26,b"\x90")
        with self.assertRaisesRegex(ValueError,"exact alignment"):x.qualify(**a)

    def test_owned_callback_pointer(self):
        a=self.four_fixture();self.add_absolute(a,12,b"\x68",0x2000,"callback")
        self.assertEqual(x.qualify(**a)["unequal_bytes"],0)

    def test_callback_must_be_pointer_argument(self):
        a=self.four_fixture();self.add_absolute(a,12,b"\xb8",0x2000,"callback")
        with self.assertRaisesRegex(ValueError,"callback"):x.qualify(**a)

    def test_counter_load_store(self):
        a=self.four_fixture();self.add_absolute(a,12,b"\xa1",0x2000,"counter")
        self.add_absolute(a,17,b"\xa3",0x2000,"counter")
        self.assertEqual(x.qualify(**a)["unequal_bytes"],0)

    def test_counter_cannot_be_arbitrary_reference(self):
        a=self.four_fixture();self.add_absolute(a,12,b"\x68",0x2000,"counter")
        with self.assertRaisesRegex(ValueError,"counter"):x.qualify(**a)

    def test_absolute_target_must_match(self):
        a=self.four_fixture();self.add_absolute(a,12,b"\x68",0x2000,"callback")
        a["layout"]["absolute_fields"][13]=(0x3000,"callback")
        with self.assertRaisesRegex(ValueError,"declared target"):x.qualify(**a)

    def test_bss_counter_is_proved_zero_fill(self):
        sec=SimpleNamespace(VirtualAddress=0x1000,SizeOfRawData=0x100,
                            Misc_VirtualSize=0x200,Characteristics=0xC0000080)
        pe=SimpleNamespace(OPTIONAL_HEADER=SimpleNamespace(ImageBase=0x400000),sections=[sec])
        self.assertEqual(x.zero_initialized_counter(pe,0x401100,4),b"\0"*4)
        for address,size,flags in [(0x4010fc,4,0xC0000080),(0x4011ff,4,0xC0000080),
                                   (0x401100,8,0xC0000080),(0x401100,4,0x40000080),
                                   (0x401100,4,0xE0000080)]:
            sec.Characteristics=flags
            with self.assertRaises(ValueError):x.zero_initialized_counter(pe,address,size)


if __name__ == "__main__":
    unittest.main()
