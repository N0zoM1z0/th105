import copy
from pathlib import Path
import sys
import tomllib
import unittest
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
import boost_matcher_leaf_origins as g

class MatcherLeafTests(unittest.TestCase):
    def fixture(self):
        s=tomllib.loads(g.ANCHORS.read_text());r=[dict(address=a['address'],size=str(a['size']))for a in s['anchors']]
        return s,r,g.load_manifest()['units']
    def test_original_checked_specialization(self):
        s,r,u=self.fixture();a,unit,context=g.validate_spec(s,r,u,s['target_sha256']);self.assertEqual(sum(x['size']for x in a),30)
        self.assertEqual(g.NAMES[16],'jump');self.assertEqual(g.NAMES[28],'toggle_case')
    def test_no_shortened_or_masked_anchor(self):
        for key,value in [('size',11),('mask',[2]),('sha256','x'*64),('symbol',g.method('literal'))]:
            s,r,u=self.fixture();s['anchors'][0][key]=value
            with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_raw_pointer_specialization_rejected(self):
        s,r,u=self.fixture();s['anchors'][0]['symbol']=s['anchors'][0]['symbol'].replace(g.STEM,'?$perl_matcher@PBD@boost@@')
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_replacement_source_or_flags_rejected(self):
        for key,value in [('source','scripts/probes/Invented.cpp'),('enable_gs',False),('boost_regex_instances',False),('boost_regex_headers',False),('profile','vc8-sp1-probe-o2-ob1'),('include_dirs',[])]:
            s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT][key]=value
            with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_formal_mask_or_relocation_rejected(self):
        for key,value in [('dir32_targets',['fake=fake']),('size',11),('comparison',{'mask':[2]})]:
            s,r,u=self.fixture();u=copy.deepcopy(u);f=next(f for f in u[g.UNIT]['functions']if f['address']==s['anchors'][0]['address']);f[key]=value
            with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_context_cannot_change(self):
        for key,value in [('source','scripts/probes/Invented.cpp'),('enable_gs',False),('boost_regex_headers',False)]:
            s,r,u=self.fixture();u=copy.deepcopy(u);u[g.CONTEXT][key]=value
            with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_selection_must_remain_two_whole_bodies(self):
        s,r,u=self.fixture();r.pop()
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_unrelated_tiny_stubs_are_not_selected(self):
        s,r,u=self.fixture();s['anchors'][0]['address']='0x006A0B10';r[0]['address']='0x006A0B10'
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
if __name__=='__main__':unittest.main()
