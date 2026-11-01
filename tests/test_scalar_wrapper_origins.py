"""Structural synthetic metadata and proof tests; no original instruction fixtures."""
import copy
import hashlib
import importlib.util
from pathlib import Path
import struct
import sys
import tempfile
from types import SimpleNamespace
import unittest
from unittest.mock import patch
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/"scripts"))
import scalar_wrapper_origins as scalar
from test_linked_pe import VTablePe


class ScalarWrapperOriginTests(unittest.TestCase):
    def spec_fixture(self):
        a=dict(address="0x00401100",size=30,unit="owner",symbol_base="??_GFixture@@UAEPAXI@Z",sha256="a"*64,owners=[{}])
        spec=dict(schema_version=1,target_sha256="b"*64,
                  compiler_sha256="71c93ca5bddc9b2816d0e053cac2b952f926f6b9321fab6b1ab6e8603621324c",anchors=[a])
        rows=[dict(address=a["address"],size="30")]
        units={"owner":dict(kind="probe",profile="vc8-sp1-probe-o2",
                           functions=[dict(address=a["address"],symbol_base=a["symbol_base"])])}
        return spec,rows,units

    def rtti_fixture(self,second=False):
        pe=VTablePe(base=0x400000)
        for s in pe.sections:s.SizeOfRawData=0x1000
        def put(a,data):pe.data[a-0x400000:a-0x400000+len(data)]=data
        table=0x402300;slot=table+4 if second else table
        put(table-4,struct.pack("<I",0x402100))
        if second:put(table,struct.pack("<I",0x401200))
        put(slot,struct.pack("<I",0x401100))
        put(0x402100,struct.pack("<5I",0,0,0,0x403100,0x402200))
        put(0x403108,b".?AVFixture@@\0")
        put(0x402200,struct.pack("<4I",0,0,1,0x402220))
        put(0x402220,struct.pack("<I",0x402240));put(0x402240,struct.pack("<6I",0x403100,0,0,0xffffffff,0,0))
        owner=dict(vtable=hex(table),slot=hex(slot),col="0x402100",type_descriptor="0x403100",type_name=".?AVFixture@@")
        return pe,lambda a,n:pe.get_data(a-0x400000,n),owner,put

    def test_exact_reserved_selector_and_profile(self):
        s,r,u=self.spec_fixture()
        self.assertEqual(list(scalar.validate_spec(s,r,r,u,"b"*64)),["owner"])

    def test_numeric_address_spelling(self):
        s,r,u=self.spec_fixture()
        u["owner"]["functions"][0]["address"]="0x401100"
        self.assertTrue(scalar.validate_spec(s,r,r,u,"b"*64))

    def test_legacy_selector_alias(self):
        s,r,u=self.spec_fixture();s["anchors"][0]["symbol_base"]="Fixture_scalar_deleting_destructor"
        u["owner"]["functions"][0]["symbol_base"]=s["anchors"][0]["symbol_base"]
        self.assertTrue(scalar.validate_spec(s,r,r,u,"b"*64))

    def test_noncompiler_selector_rejected(self):
        s,r,u=self.spec_fixture();s["anchors"][0]["symbol_base"]="Fixture_dtor";u["owner"]["functions"][0]["symbol_base"]="Fixture_dtor"
        with self.assertRaises(ValueError):scalar.validate_spec(s,r,r,u,"b"*64)

    def test_pins_extent_and_owner_required(self):
        changes=[lambda s:s.update(target_sha256="c"*64),lambda s:s.update(compiler_sha256="c"*64),
                 lambda s:s["anchors"][0].update(size=29),lambda s:s["anchors"][0].update(owners=[]),
                 lambda s:s["anchors"].append(copy.deepcopy(s["anchors"][0]))]
        for change in changes:
            s,r,u=self.spec_fixture();change(s)
            with self.assertRaises(ValueError):scalar.validate_spec(s,r,r,u,"b"*64)

    def test_actual_probe_contract_required(self):
        for kind,profile in [("linked_candidate","vc8-sp1-probe-o2"),("probe","unproved")]:
            s,r,u=self.spec_fixture();u["owner"].update(kind=kind,profile=profile)
            with self.assertRaises(ValueError):scalar.validate_spec(s,r,r,u,"b"*64)

    def test_primary_and_second_slot_rtti(self):
        for second in (False,True):
            pe,read,owner,put=self.rtti_fixture(second)
            scalar.native_owner(pe,read,0x401100,owner)

    def test_wrong_owner_pointer_and_type(self):
        for at,value in [(0x402300,0x401101),(0x4022fc,0x402104),(0x40210c,0x403110),(0x402240,0x403110)]:
            pe,read,owner,put=self.rtti_fixture();put(at,struct.pack("<I",value))
            with self.assertRaises(ValueError):scalar.native_owner(pe,read,0x401100,owner)

    def test_secondary_col_is_not_primary_owner(self):
        pe,read,owner,put=self.rtti_fixture();put(0x402104,struct.pack("<I",4))
        with self.assertRaises(ValueError):scalar.native_owner(pe,read,0x401100,owner)

    def test_rtti_must_be_readonly(self):
        pe,read,owner,put=self.rtti_fixture();pe.sections[1].Characteristics|=0x80000000
        with self.assertRaises(ValueError):scalar.native_owner(pe,read,0x401100,owner)

    def test_preceding_virtual_entry_must_be_code(self):
        pe,read,owner,put=self.rtti_fixture(True);put(0x402300,struct.pack("<I",0x403200))
        with self.assertRaises(ValueError):scalar.native_owner(pe,read,0x401100,owner)

    def test_canonical_report_not_prefix(self):
        s,_,_=self.spec_fixture();a=s["anchors"]
        good=dict(address=a[0]["address"],result="exact",target_size=30,object_section_tail_size=30,target_sha256="a"*64,object_compared_sha256="a"*64)
        scalar.verify_comparisons(a,[good])
        for change in [dict(result="mismatch"),dict(object_section_tail_size=31),dict(object_compared_sha256="c"*64)]:
            bad=dict(good);bad.update(change)
            with self.assertRaises(ValueError):scalar.verify_comparisons(a,[bad])
        with self.assertRaises(ValueError):scalar.verify_comparisons(a,[good,good])

    def test_stale_input_digest_rejected(self):
        s,_,u=self.spec_fixture()
        with tempfile.TemporaryDirectory()as tmp:
            obj=Path(tmp)/"x.obj";obj.write_bytes(b"synthetic placeholder, not machine code")
            u["owner"].update(object="x.obj")
            prov=dict(input_digest="old",object_sha256=scalar.digest(obj),compiler_sha256=s["compiler_sha256"])
            with patch.object(scalar,"repository_path",return_value=obj),patch.object(scalar,"compiler_sha256",return_value=s["compiler_sha256"]),patch.object(scalar,"build_unit",return_value=prov),patch.object(scalar,"unit_input_digest",return_value=("current",[])):
                with self.assertRaisesRegex(ValueError,"current source provenance"):
                    scalar.replay("owner",s["anchors"],u,s,None,None,True)

    def test_authored_tracking_rejects_generated_selectors(self):
        path=Path(__file__).resolve().parents[1]/"scripts/validate-tracking.py"
        spec=importlib.util.spec_from_file_location("tracking_guard",path);module=importlib.util.module_from_spec(spec);spec.loader.exec_module(module)
        for name in ["??_GFixture@@UAEPAXI@Z","??_EFixture@@","Fixture_scalar_deleting_destructor"]:
            self.assertTrue(module.is_compiler_deallocation_selector(name))
        for name in ["??1Fixture@@QAE@XZ","set_runtime_scalar","render"]:
            self.assertFalse(module.is_compiler_deallocation_selector(name))


if __name__=="__main__":unittest.main()
