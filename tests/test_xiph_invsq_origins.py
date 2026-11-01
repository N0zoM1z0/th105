import copy
from pathlib import Path
import sys
import tomllib
import unittest
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
import xiph_invsq_origins as g
class InvsqTests(unittest.TestCase):
    def fixture(self):
        s=tomllib.loads(g.ANCHORS.read_text());return s,[dict(address='0x006897D0',size='77')],g.tables.load_manifest()['units']
    def test_whole_original_interpolator(self):
        s,r,u=self.fixture();a,unit=g.validate_spec(s,r,u,s['target_sha256']);self.assertEqual(a['size'],77)
    def test_shortened_masked_or_other_symbol_rejected(self):
        for k,v in [('size',76),('mask',[11]),('symbol','_vorbis_coslook')]:
            s,r,u=self.fixture();s['anchors'][0][k]=v
            with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_original_sdk_member_required(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT]['sdk_object']='window.obj'
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_addend_specific_element_mapping_required(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);f=next(f for f in u[g.UNIT]['functions']if f['address']=='0x006897D0');f['dir32_targets'][-1]='_INVSQ_LOOKUP+0x4=_INVSQ_LOOKUP'
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_all_real_constants_required(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);f=next(f for f in u[g.UNIT]['functions']if f['address']=='0x006897D0');f['dir32_targets'].pop(0)
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_formal_prefix_not_allowed(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);f=next(f for f in u[g.UNIT]['functions']if f['address']=='0x006897D0');f['size']=76
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_previous_getter_contract_preserved(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT]['functions']=[f for f in u[g.UNIT]['functions']if f['address']!='0x00689820']
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
if __name__=='__main__':unittest.main()
