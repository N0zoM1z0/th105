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


if __name__ == "__main__":
    unittest.main()
