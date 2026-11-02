import copy
from pathlib import Path
import struct
import sys
import tomllib
from types import SimpleNamespace
import unittest
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
import replay_member_cleanup_origins as g
class ReplayCleanupTests(unittest.TestCase):
    def fixture(self):
        s=tomllib.loads(g.ANCHORS.read_text());return s,[dict(address=a,size=str(v[0]))for a,v in g.CONTRACT.items()],g.load_manifest()['units']
    def test_two_complete_emitted_roots(self):
        s,r,u=self.fixture();a,_=g.validate_spec(s,r,u,s['target_sha256']);self.assertEqual(sum(x['size']for x in a),32)
    def test_no_mask_or_prefix(self):
        for k,v in [('size',26),('mask',[17])]:
            s,r,u=self.fixture();s['anchors'][0][k]=v
            with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_no_duplicate_callback(self):
        s,r,u=self.fixture();s['anchors'].append(copy.deepcopy(s['anchors'][-1]))
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_actual_owner_source_required(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT]['source']='fake.cpp'
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_paired_constructor_required(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT]['functions']=[f for f in u[g.UNIT]['functions']if f['address']!='0x0042C930']
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_base_cleanup_target_required(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);next(f for f in u[g.UNIT]['functions']if f['address']=='0x0042C950')['rel32_targets']=[g.INPUT_BASE+'=0x00400000']
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_original_range_target_required(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);next(f for f in u[g.UNIT]['functions']if f['address']=='0x0042B8E0')['rel32_targets']=[g.RANGE+'=0x00400000']
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def array(self):
        raw=bytearray.fromhex('680000000068000000006a026a688d7e0857e800000000');fields=[(1,6,g.INPUT_DTOR,0x42c950),(6,6,g.INPUT_CTOR,0x42c930),(19,20,g.ARRAY_CTOR,0x68a30c)];native=bytearray(raw)
        for off,k,s,to in fields:struct.pack_into('<I',native,off,(to-(0x43f1d9+off+4)if k==20 else to)&0xffffffff)
        reader=SimpleNamespace(raw=lambda n,s,o:bytes(raw),refs=lambda n,s,o:[(o,k,n)for o,k,n,to in fields]);return reader,raw,fields,bytes(native)
    def call(self,r,fields,native):return g.array_site(r,g.CTOR,41,23,0x43f1d9,fields,(10,bytes.fromhex('6a026a688d7e0857')),lambda a,n:native)
    def test_real_count_stride_member_pair(self):
        r,b,f,n=self.array();self.assertEqual(self.call(r,f,n)['stride'],104)
    def test_source_callback_addend_rejected(self):
        r,b,f,n=self.array();b[1]=1
        with self.assertRaises(ValueError):self.call(r,f,n)
    def test_native_wrong_callback_rejected(self):
        r,b,f,n=self.array();n=bytearray(n);n[1]^=1
        with self.assertRaises(ValueError):self.call(r,f,bytes(n))
    def test_native_count_and_member_mutations_rejected(self):
        for off in [11,16]:
            r,b,f,n=self.array();n=bytearray(n);n[off]^=1
            with self.assertRaises(ValueError):self.call(r,f,bytes(n))
    def test_wrong_source_role_rejected(self):
        r,b,f,n=self.array();r.refs=lambda n,s,o:[(1,6,'wrong'),(6,6,g.INPUT_CTOR),(19,20,g.ARRAY_CTOR)]
        with self.assertRaises(ValueError):self.call(r,f,n)
if __name__=='__main__':unittest.main()
