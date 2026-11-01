import copy
from pathlib import Path
import sys
import tomllib
import unittest
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
import vc8_typeinfo_delete_origins as g
class TypeinfoDeleteTests(unittest.TestCase):
    def fixture(self):
        s=tomllib.loads(g.ANCHORS.read_text());return s,[dict(address='0x006898FD',size='28')],g.normal.load_manifest()['units']
    def test_one_original_deleting_body(self):
        s,r,u=self.fixture();a,unit=g.validate_spec(s,r,u,s['target_sha256']);self.assertEqual(a['size'],28)
    def test_no_shortened_masked_or_other_class(self):
        for k,v in [('size',27),('mask',[4]),('symbol',g.SCALAR.replace('type_info','exception@std'))]:
            s,r,u=self.fixture();s['anchors'][0][k]=v
            with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_original_member_required(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT]['toolchain_object']='stdexcpt.obj'
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_normal_support_contract_preserved(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT]['functions']=[f for f in u[g.UNIT]['functions']if f['address']!='0x006898EF']
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_actual_deallocation_target_required(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);f=next(f for f in u[g.UNIT]['functions']if f['address']=='0x006898FD');f['rel32_targets'][-1]=g.DELETE+'=0x0068C686'
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_alias_does_not_add_second_credit(self):
        s,r,u=self.fixture();s['anchors'].append(copy.deepcopy(s['anchors'][0]));r.append(copy.deepcopy(r[0]))
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_formal_prefix_rejected(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);f=next(f for f in u[g.UNIT]['functions']if f['address']=='0x006898FD');f['size']=27
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
if __name__=='__main__':unittest.main()
