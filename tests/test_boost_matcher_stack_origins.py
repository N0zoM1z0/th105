import copy
from pathlib import Path
import sys
import tomllib
import unittest
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
import boost_matcher_stack_origins as g
class MatcherStackTests(unittest.TestCase):
    def fixture(self):
        s=tomllib.loads(g.ANCHORS.read_text());return s,[dict(address=a['address'],size=str(a['size']))for a in s['anchors']],g.leaf.load_manifest()['units']
    def test_actual_original_typed_pair(self):
        s,r,u=self.fixture();a,unit=g.validate_spec(s,r,u,s['target_sha256']);self.assertEqual(sum(x['size']for x in a),24)
        self.assertEqual(g.NAMES[2],'recursion_stopper');self.assertEqual(len(g.NAMES),16)
    def test_wrong_extent_symbol_and_mask_rejected(self):
        for k,v in [('size',18),('symbol',g.unwind('end')),('mask',[1]),('sha256','0')]:
            s,r,u=self.fixture();s['anchors'][0][k]=v
            with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_tail_provider_cannot_change(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);f=next(f for f in u[g.UNIT]['functions']if f['address']=='0x006B25B0');f['rel32_targets']=[g.FAST+'=0x006AF2D0']
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_original_probe_required(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT]['source']='scripts/probes/Replacement.cpp'
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_checked_context_required(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.leaf.CONTEXT]['boost_regex_headers']=False
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_unrelated_tiny_stub_rejected(self):
        s,r,u=self.fixture();s['anchors'][1]['address']='0x006A0D70';r[1]['address']='0x006A0D70'
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_formal_prefix_size_rejected(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);f=next(f for f in u[g.UNIT]['functions']if f['address']=='0x006A2830');f['size']=18
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_old_leaf_contract_is_preserved(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);f=next(f for f in u[g.UNIT]['functions']if f['address']=='0x006A0AA0');f['symbol_base']=g.STOP
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
if __name__=='__main__':unittest.main()
