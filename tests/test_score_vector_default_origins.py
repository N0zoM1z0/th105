import copy
from pathlib import Path
import sys
import tomllib
import unittest
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
import score_vector_default_origins as g
class ScoreVectorDefaultTests(unittest.TestCase):
    def fixture(self):
        s=tomllib.loads(g.ANCHORS.read_text());return s,[dict(address='0x004460D0',size='14')],g.load_manifest()['units']
    def test_actual_original_member(self):
        s,r,u=self.fixture();a,_=g.validate_spec(s,r,u,s['target_sha256']);self.assertEqual(a['symbol'],g.CTOR)
    def test_no_partial_or_masked_body(self):
        for k,v in [('size',13),('mask',[0]),('symbol',g.DTOR)]:
            s,r,u=self.fixture();s['anchors'][0][k]=v
            with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_source_owner_hash_required(self):
        s,r,u=self.fixture();s['sources'][0]['normalized_sha256']='0'*64
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_record_type_header_required(self):
        s,r,u=self.fixture();s['sources'].pop()
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_actual_parent_array_owner_required(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT]['functions']=[f for f in u[g.UNIT]['functions']if f['address']!='0x0043E1A0']
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_paired_destructor_required(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT]['functions']=[f for f in u[g.UNIT]['functions']if f['address']!='0x00435F90']
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_no_alternate_source_facade(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT]['source']='src/config/GameConfig.cpp'
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_compiler_pin_required(self):
        s,r,u=self.fixture();s['compiler_sha256']='0'*64
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
if __name__=='__main__':unittest.main()
