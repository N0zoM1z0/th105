import copy
from pathlib import Path
import sys
import tomllib
import unittest
from types import SimpleNamespace
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
import vc8_typeinfo_dtor_origins as g
class TypeinfoDtorTests(unittest.TestCase):
    def fixture(self):
        s=tomllib.loads(g.ANCHORS.read_text());return s,[dict(address='0x006898EF',size='14')],g.load_manifest()['units']
    def test_original_typeinfo_member(self):
        s,r,u=self.fixture();a,unit=g.validate_spec(s,r,u,s['target_sha256']);self.assertEqual(a['size'],14)
    def test_wrong_extent_mask_or_class_rejected(self):
        for k,v in [('size',13),('mask',[3]),('symbol','??1exception@std@@UAE@XZ')]:
            s,r,u=self.fixture();s['anchors'][0][k]=v
            with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_original_archive_identity_required(self):
        for k,v in [('toolchain_library','libcpmt'),('toolchain_object','typname.obj'),('toolchain_archive_sha256','0'*64),('source','scripts/fake.py'),('kind','probe')]:
            s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT][k]=v
            with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_actual_cleanup_target_required(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT]['functions'][0]['rel32_targets']=[g.PROVIDER+'=0x00689FDA']
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_actual_typeinfo_vtable_required(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT]['functions'][0]['dir32_targets']=[]
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_no_prefix_formal_comparison(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT]['functions'][0]['size']=13
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_unrelated_same_size_candidate_rejected(self):
        s,r,u=self.fixture();r[0]['address']='0x0068B420'
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_two_field_root_requires_actual_zero_fill(self):
        section=SimpleNamespace(VirtualAddress=0x1000,SizeOfRawData=0x100,Misc_VirtualSize=0x200,Characteristics=0xC0000040)
        pe=SimpleNamespace(OPTIONAL_HEADER=SimpleNamespace(ImageBase=0x400000),sections=[section])
        self.assertEqual(g.zero_initialized_counter(pe,0x401100,4)+g.zero_initialized_counter(pe,0x401104,4),bytes(8))
    def test_initialized_or_executable_region_is_not_bss(self):
        for address,flags in [(0x4010FC,0xC0000040),(0x401100,0xE0000040)]:
            section=SimpleNamespace(VirtualAddress=0x1000,SizeOfRawData=0x100,Misc_VirtualSize=0x200,Characteristics=flags)
            pe=SimpleNamespace(OPTIONAL_HEADER=SimpleNamespace(ImageBase=0x400000),sections=[section])
            with self.assertRaises(ValueError):g.zero_initialized_counter(pe,address,4)
if __name__=='__main__':unittest.main()
