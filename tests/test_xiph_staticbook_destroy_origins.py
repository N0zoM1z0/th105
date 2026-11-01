import copy
from pathlib import Path
import sys
import tomllib
import unittest
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
import xiph_staticbook_destroy_origins as g
class StaticbookTests(unittest.TestCase):
    def fixture(self):
        s=tomllib.loads(g.ANCHORS.read_text());return s,[dict(address='0x00681190',size='29')],g.load_manifest()['units']
    def test_original_whole_destroy_and_clear(self):
        s,r,u=self.fixture();a,unit=g.validate_spec(s,r,u,s['target_sha256']);self.assertEqual(a['size'],29);self.assertEqual(len(unit['functions']),2)
    def test_no_shortened_masked_or_wrong_symbol(self):
        for k,v in [('size',28),('mask',[14]),('symbol',g.CLEAR)]:
            s,r,u=self.fixture();s['anchors'][0][k]=v
            with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_original_member_and_archive_required(self):
        for k,v in [('sdk_object','codebook.obj'),('sdk_component','ogg'),('sdk_archive_sha256','0'*64),('kind','probe')]:
            s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT][k]=v
            with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_actual_clear_and_free_bindings_required(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT]['functions'][0]['rel32_targets']=['_free=0x0068C686']
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_whole_support_regression_cannot_be_removed(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT]['functions'].pop()
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_padding_not_code_credit(self):
        s,r,u=self.fixture();s['anchors'][0]['size']=32;r[0]['size']='32'
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_formal_prefix_rejected(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT]['functions'][0]['size']=28
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
if __name__=='__main__':unittest.main()
