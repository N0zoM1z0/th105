import copy
from pathlib import Path
import sys
import tomllib
import unittest
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
import sprite_callback_origins as g
class SpriteCallbackTests(unittest.TestCase):
    def fixture(self):
        s=tomllib.loads(g.ANCHORS.read_text());return s,[dict(address=g.ADDRESS,size='7')],g.owner.load_manifest()['units']
    def test_actual_array_callback(self):
        s,r,u=self.fixture();a,_=g.validate_spec(s,r,u,s['target_sha256']);self.assertEqual(a['symbol'],g.owner.DTOR)
    def test_identical_body_not_interchangeable(self):
        s,r,u=self.fixture();s['anchors'][0]['address']='0x0040AD50';r[0]['address']='0x0040AD50'
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_whole_cleanup_required(self):
        s,r,u=self.fixture();s['anchors'][0]['size']=6;r[0]['size']='6'
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_no_mask(self):
        s,r,u=self.fixture();s['anchors'][0]['mask']=[2]
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_correct_source_destructor_required(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);next(x for x in u[g.owner.UNIT]['functions']if x['address']==g.ADDRESS)['symbol_base']='??1IColor@@UAE@XZ'
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_paired_constructor_required(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.owner.UNIT]['functions']=[x for x in u[g.owner.UNIT]['functions']if x['address']!='0x0041F6E0']
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_actual_owner_source_required(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.owner.UNIT]['source']='src/battle/EffectSprite.cpp'
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
if __name__=='__main__':unittest.main()
