import copy
from pathlib import Path
import sys
import tomllib
import unittest
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
import vc8_public_wrapper_origins as g
class PublicWrapperTests(unittest.TestCase):
    def fixture(self):
        s=tomllib.loads(g.ANCHORS.read_text());return s,[dict(address=a['address'],size=str(a['size']))for a in s['anchors']],g.load_manifest()['units']
    def test_all_complete_wrappers(self):
        s,r,u=self.fixture();self.assertEqual({a['address']for a in g.validate_spec(s,r,u,s['target_sha256'])},set(g.CONTRACT))
    def test_no_mask(self):
        s,r,u=self.fixture();s['anchors'][0]['mask']=[7]
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_complete_extent_required(self):
        s,r,u=self.fixture();s['anchors'][0]['size']-=1
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_no_missing_or_duplicate_body(self):
        for duplicate in [False,True]:
            s,r,u=self.fixture()
            if duplicate:s['anchors'].append(copy.deepcopy(s['anchors'][0]))
            else:s['anchors'].pop()
            with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_original_member_required(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u['vc8-original-atof-wrapper']['toolchain_object']='fread.obj'
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_exact_provider_required(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u['vc8-original-fread-wrapper']['functions'][0]['rel32_targets']=['_fread_s=0x0068CE5A']
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_correct_public_symbol_required(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u['vc8-original-fread-wrapper']['functions'][0]['symbol_base']='__fread_nolock'
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_original_archive_required(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u['vc8-original-flushall-wrapper']['toolchain_archive_sha256']='0'*64
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
if __name__=='__main__':unittest.main()
