import copy
from pathlib import Path
import struct
import sys
import tomllib
from types import SimpleNamespace
import unittest
from unittest.mock import patch
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
import deque_popback_origins as g
class DequePopTests(unittest.TestCase):
    def fixture(self):
        s=tomllib.loads(g.ANCHORS.read_text());return s,[dict(address='0x00428680',size='23')],g.load_manifest()['units']
    def test_one_complete_original_member(self):
        s,r,u=self.fixture();a,_=g.validate_spec(s,r,u,s['target_sha256']);self.assertEqual(a['size'],23)
    def test_no_mask_or_short_body(self):
        for k,v in [('size',22),('mask',[0])]:
            s,r,u=self.fixture();s['anchors'][0][k]=v
            with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_no_duplicate_body_credit(self):
        s,r,u=self.fixture();s['anchors'].append(copy.deepcopy(s['anchors'][0]))
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_unowned_identical_address_rejected(self):
        s,r,u=self.fixture();s['anchors'][0]['address']=r[0]['address']='0x00413DF0'
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_original_source_and_profile_required(self):
        for k,v in [('source','fake.cpp'),('profile','vc8-sp1-probe-os')]:
            s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT][k]=v
            with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_pinned_compiler_and_source_hash_required(self):
        for k in ['compiler_sha256','source_sha256']:
            s,r,u=self.fixture();s[k]='0'*64
            with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_original_std_member_required(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT]['functions'][0]['symbol_base']='custom_pop'
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def reader(self,name=None,add=0):return SimpleNamespace(symbol=lambda n:SimpleNamespace(value=0),section=lambda n:SimpleNamespace(name='.text',raw_size=1404),refs=lambda n,s,o:[(1,20,name or g.SYMBOL)],raw=lambda n,s,o:b'\xe8'+struct.pack('<I',add))
    def read(self,a,n):return b'\xe8'+struct.pack('<i',0x428680-(0x463d05+5))if n==5 else bytes(1404)
    def test_real_source_caller_role(self):
        with patch.object(g,'digest',return_value='d79e2baf0eb343544e0ed2bd7d6f2ef18cd20085623df4606805890367dac8c0'):self.assertEqual(len(g.caller_site(self.reader(),self.read)),5)
    def test_wrong_source_callee_or_addend_rejected(self):
        for r in [self.reader(name='other'),self.reader(add=1)]:
            with self.assertRaises(ValueError):g.caller_site(r,self.read)
    def test_actual_native_edge_cannot_select_identical_other_body(self):
        def read(a,n):return b'\xe8'+struct.pack('<i',0x413df0-(0x463d05+5))if n==5 else bytes(1404)
        with self.assertRaises(ValueError):g.caller_site(self.reader(),read)
if __name__=='__main__':unittest.main()
