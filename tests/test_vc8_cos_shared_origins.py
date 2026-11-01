import copy
from pathlib import Path
import sys
import tomllib
import unittest
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
import vc8_cos_shared_origins as g
class CosSharedTests(unittest.TestCase):
    def fixture(self):
        s=tomllib.loads(g.ANCHORS.read_text());return s,[dict(address='0x006967CE',size='395')],g.sin.sqrt.load_manifest()['units']
    def test_original_complete_shared_body(self):
        s,r,u=self.fixture();a,unit=g.validate_spec(s,r,u,s['target_sha256']);self.assertEqual(a['size'],395)
    def test_no_mask_or_public_entry_substitute(self):
        for k,v in [('size',394),('mask',[0]),('symbol','__CIcos_pentium4')]:
            s,r,u=self.fixture();s['anchors'][0][k]=v
            with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_correct_original_member_required(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT]['toolchain_object']='sin_pentium4.obj'
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_actual_x87_fallback_required(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT]['functions'][0]['rel32_targets']=['__cos_default=0x0068BB90']
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_all_coefficient_roles_required(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT]['functions'][0]['dir32_targets'].pop()
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_common_protocol_contract_preserved(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.sin.SIN_UNIT]['functions'][0]['dir32_targets']=[]
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_trailing_alignment_not_code_credit(self):
        s,r,u=self.fixture();s['anchors'][0]['size']=398;r[0]['size']='398'
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_actual_neutral_alignment(self):
        g.neutral_trailing_lea(bytes.fromhex('8d4900'),0x1000)
    def test_other_unreachable_instructions_not_waived(self):
        for b in [bytes.fromhex('8d4901'),bytes.fromhex('8b4900'),bytes.fromhex('909090'),bytes.fromhex('8d490090')]:
            with self.assertRaises(ValueError):g.neutral_trailing_lea(b,0x1000)
if __name__=='__main__':unittest.main()
