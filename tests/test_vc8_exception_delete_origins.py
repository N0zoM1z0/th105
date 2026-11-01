import copy
from pathlib import Path
import sys
import tomllib
import unittest
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
import vc8_exception_delete_origins as g
class ExceptionDeleteTests(unittest.TestCase):
    def fixture(self):
        s=tomllib.loads(g.ANCHORS.read_text());return s,[dict(address='0x00689FFD',size='28')],g.load_manifest()['units']
    def test_original_class_family(self):
        s,r,u=self.fixture();a,unit=g.validate_spec(s,r,u,s['target_sha256']);self.assertEqual(a['size'],28);self.assertEqual(len(unit['functions']),3)
    def test_wrong_class_extent_or_mask_rejected(self):
        for k,v in [('symbol',g.SCALAR.replace('exception@std','type_info')),('size',27),('mask',[4])]:
            s,r,u=self.fixture();s['anchors'][0][k]=v
            with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_original_archive_member_required(self):
        for k,v in [('toolchain_object','typinfo.obj'),('toolchain_library','libcpmt'),('kind','probe')]:
            s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT][k]=v
            with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_support_functions_cannot_be_removed(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT]['functions'].pop()
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_actual_normal_destructor_required(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT]['functions'][0]['rel32_targets'][0]=g.DTOR+'=0x006898EF'
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_alias_not_second_body(self):
        s,r,u=self.fixture();s['anchors'].append(copy.deepcopy(s['anchors'][0]));r.append(copy.deepcopy(r[0]))
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_literal_binding_cannot_change(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT]['functions'][2]['dir32_targets']=[]
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
if __name__=='__main__':unittest.main()
