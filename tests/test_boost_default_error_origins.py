import copy
from pathlib import Path
import sys
import tomllib
import unittest
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
import boost_default_error_origins as g
class DefaultErrorTests(unittest.TestCase):
    def fixture(self):
        s=tomllib.loads(g.ANCHORS.read_text());return s,[dict(address='0x006B4800',size='18')],g.load_manifest()['units']
    def test_original_complete_getter(self):
        s,r,u=self.fixture();a,unit=g.validate_spec(s,r,u,s['target_sha256']);self.assertEqual(a['size'],18)
    def test_wrong_extent_mask_and_symbol_rejected(self):
        for k,v in [('size',17),('mask',[4]),('symbol',g.SYMBOL.replace('YI','YA')),('sha256','z'*64)]:
            s,r,u=self.fixture();s['anchors'][0][k]=v
            with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_original_source_and_flags_required(self):
        for k,v in [('source','scripts/probes/Invented.cpp'),('profile','vc8-sp1-probe-o2-ob1'),('enable_gs',False),('boost_regex_headers',False),('boost_regex_source_tu','regex.cpp')]:
            s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT][k]=v
            with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_both_original_packages_required(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT]['include_dirs']=[g.upstream.FOLDER]
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_literal_binding_cannot_be_removed_or_changed(self):
        for value in [[],[g.UNKNOWN+'='+g.TABLE,g.TABLE+'='+g.TABLE]]:
            s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT]['functions'][0]['dir32_targets']=value
            with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_formal_prefix_comparison_rejected(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT]['functions'][0]['size']=17
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_other_candidate_not_selected(self):
        s,r,u=self.fixture();r[0]['address']='0x006A0AF0'
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
if __name__=='__main__':unittest.main()
