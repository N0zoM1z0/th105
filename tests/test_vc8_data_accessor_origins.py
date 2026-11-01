import copy
from pathlib import Path
import sys
import tomllib
from types import SimpleNamespace
import unittest
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
import vc8_data_accessor_origins as g
class DataAccessorTests(unittest.TestCase):
    def fixture(self):
        s=tomllib.loads(g.ANCHORS.read_text());return s,[dict(address=a['address'],size=str(a['size']))for a in s['anchors']],g.load_manifest()['units']
    def pe(self):return SimpleNamespace(OPTIONAL_HEADER=SimpleNamespace(ImageBase=0x400000),sections=[SimpleNamespace(VirtualAddress=0x2e6000,SizeOfRawData=0x15000,Misc_VirtualSize=0x1ea08,Characteristics=0xc0000040)])
    def test_all_original_accessors(self):
        s,r,u=self.fixture();self.assertEqual({a['address']for a in g.validate_spec(s,r,u,s['target_sha256'])},set(g.CONTRACT))
    def test_no_short_or_masked_member(self):
        for k,v in [('size',5),('mask',[1]),('symbol','wrong')]:
            s,r,u=self.fixture();s['anchors'][0][k]=v
            with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_actual_member_required(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.IOB_UNIT]['toolchain_object']='timeset.obj'
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_actual_data_role_required(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.TIME_UNIT]['functions'][0]['dir32_targets']=['__daylight=vc8_timezone_cell']
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_missing_member_rejected(self):
        s,r,u=self.fixture();s['anchors'].pop()
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_target_pin_required(self):
        s,r,u=self.fixture();s['target_sha256']='0'*64
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,'1'*64)
    def test_actual_whole_buffer(self):self.assertEqual(g.zero_fill_buffer(self.pe(),0x703a00,4096)['size'],4096)
    def test_partial_buffer_rejected(self):
        with self.assertRaises(ValueError):g.zero_fill_buffer(self.pe(),0x703a00,4095)
    def test_raw_backed_buffer_rejected(self):
        p=self.pe();p.sections[0].SizeOfRawData=0x1da01
        with self.assertRaises(ValueError):g.zero_fill_buffer(p,0x703a00,4096)
    def test_buffer_cannot_cross_virtual_end(self):
        p=self.pe();p.sections[0].Misc_VirtualSize=0x1e9ff
        with self.assertRaises(ValueError):g.zero_fill_buffer(p,0x703a00,4096)
    def test_buffer_must_be_writable(self):
        p=self.pe();p.sections[0].Characteristics=0x40000040
        with self.assertRaises(ValueError):g.zero_fill_buffer(p,0x703a00,4096)
    def test_buffer_cannot_be_executable(self):
        p=self.pe();p.sections[0].Characteristics|=0x20000000
        with self.assertRaises(ValueError):g.zero_fill_buffer(p,0x703a00,4096)
if __name__=='__main__':unittest.main()
