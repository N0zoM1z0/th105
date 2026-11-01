import copy
from pathlib import Path
import sys
import tomllib
import unittest
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
import vc8_invalid_copy_origins as g
class InvalidCopyTests(unittest.TestCase):
    def fixture(self):
        s=tomllib.loads(g.ANCHORS.read_text());return s,[dict(address='0x00665B72',size='24')],g.load_manifest()['units']
    def test_original_archive_copy(self):
        s,r,u=self.fixture();a,unit=g.validate_spec(s,r,u,s['target_sha256']);self.assertEqual(a['size'],24)
    def test_no_shortened_masked_or_other_class(self):
        for k,v in [('size',23),('mask',[8]),('symbol',g.SYMBOL.replace('invalid_argument','logic_error'))]:
            s,r,u=self.fixture();s['anchors'][0][k]=v
            with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_original_archive_member_required(self):
        for k,v in [('toolchain_library','libcmt'),('toolchain_object','frame.obj'),('toolchain_archive_sha256','0'*64),('kind','probe'),('source','scripts/fake.py')]:
            s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT][k]=v
            with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_named_base_copy_cannot_change(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT]['functions'][0]['rel32_targets']=[g.logic.COPY+'=0x006A59A0']
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_actual_vtable_binding_required(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT]['functions'][0]['dir32_targets']=[]
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_formal_prefix_rejected(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT]['functions'][0]['size']=23
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_native_anchor_cannot_be_replaced(self):
        s,r,u=self.fixture();r[0]['address']='0x0068FB16'
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
if __name__=='__main__':unittest.main()
