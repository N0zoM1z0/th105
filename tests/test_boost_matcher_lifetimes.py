import importlib.util
from pathlib import Path
import struct
import sys
import unittest
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
sp=importlib.util.spec_from_file_location('boost_matcher_lifetime_tests',Path(__file__).resolve().parents[1]/'scripts/audit-boost-matcher-lifetimes.py')
g=importlib.util.module_from_spec(sp);sp.loader.exec_module(g)
class MatcherLifetimeTests(unittest.TestCase):
    def fixture(self,root):
        code,_,_,start,offsets=g.SCOPES[root];n=len(offsets)
        m=bytearray(b''.join(struct.pack('<iI',i-1,code+off)for i,off in enumerate(offsets))+struct.pack('<9I',0x19930522,n,start,0,0,0,0,0,1))
        return m,start,code,offsets
    def test_complete_four_scopes(self):
        for root in g.SCOPES:
            m,start,code,offsets=self.fixture(root);g.check_metadata(bytes(m),start,code,offsets)
    def test_truncated_metadata_rejected(self):
        m,s,c,o=self.fixture(0x443b30)
        with self.assertRaises(ValueError):g.check_metadata(m[:-1],s,c,o)
    def test_previous_state_rejected(self):
        m,s,c,o=self.fixture(0x443b30);struct.pack_into('<i',m,16,0)
        with self.assertRaises(ValueError):g.check_metadata(m,s,c,o)
    def test_action_cannot_skip_receiver_adjustment(self):
        m,s,c,o=self.fixture(0x443b30);struct.pack_into('<I',m,20,0x443020)
        with self.assertRaises(ValueError):g.check_metadata(m,s,c,o)
    def test_funcinfo_fields_all_checked(self):
        for field in range(9):
            m,s,c,o=self.fixture(0x442f40);m[8+field*4]^=1
            with self.assertRaises(ValueError):g.check_metadata(m,s,c,o)
    def arrays(self):
        return [(True,bytes.fromhex('682030440068003a44006a326a448d968800000052c644243001e818672400')),
                (False,bytes.fromhex('68203044006a326a448d868800000050c744242401000000e8c4672400'))]
    def test_actual_paired_arrays(self):
        for constructor,raw in self.arrays():g.check_array(raw,constructor)
    def test_every_array_byte_checked(self):
        for constructor,raw in self.arrays():
            for i in range(len(raw)):
                b=bytearray(raw);b[i]^=1
                with self.assertRaises(ValueError):g.check_array(b,constructor)
    def test_arrays_cannot_swap_roles(self):
        for constructor,raw in self.arrays():
            with self.assertRaises(ValueError):g.check_array(raw,not constructor)
if __name__=='__main__':unittest.main()
