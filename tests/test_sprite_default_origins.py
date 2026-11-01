import copy
from pathlib import Path
import sys
import tomllib
import unittest
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
import sprite_default_origins as g
class SpriteDefaultTests(unittest.TestCase):
    def fixture(self):
        s=tomllib.loads(g.ANCHORS.read_text());return s,[dict(address='0x0041F6E0',size='16')],g.load_manifest()['units']
    def test_actual_implicit_member(self):
        s,r,u=self.fixture();a,_=g.validate_spec(s,r,u,s['target_sha256']);self.assertEqual(a['size'],16)
    def test_no_short_or_masked_proof(self):
        for k,v in [('size',15),('mask',[11]),('symbol',g.DTOR)]:
            s,r,u=self.fixture();s['anchors'][0][k]=v
            with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_reviewed_declaration_hash_required(self):
        s,r,u=self.fixture();s['sources'][0]['normalized_sha256']='0'*64
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_all_relevant_source_views_required(self):
        s,r,u=self.fixture();s['sources'].pop()
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_actual_owner_required(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT]['source']='src/battle/SpriteRenderFinalizer.cpp'
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_correct_constructor_selector_required(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);next(x for x in u[g.UNIT]['functions']if x['address']=='0x0041F6E0')['symbol_base']=g.DTOR
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_parent_array_owner_cannot_disappear(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT]['functions']=[x for x in u[g.UNIT]['functions']if x['address']!='0x004231A0']
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_compiler_contract_required(self):
        s,r,u=self.fixture();s['compiler_sha256']='0'*64
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
if __name__=='__main__':unittest.main()
