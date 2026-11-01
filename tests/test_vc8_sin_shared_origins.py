import copy
from pathlib import Path
import sys
import tomllib
import unittest
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
import vc8_sin_shared_origins as g
class SinSharedTests(unittest.TestCase):
    def fixture(self):
        s=tomllib.loads(g.ANCHORS.read_text());return s,[dict(address=a['address'],size=str(a['size']))for a in s['anchors']],g.sqrt.load_manifest()['units']
    def test_both_original_owners_required(self):
        s,r,u=self.fixture();aa=g.validate_spec(s,r,u,s['target_sha256']);self.assertEqual(sum(a['size']for a in aa),570)
    def test_no_shortened_masked_or_public_entry_substitute(self):
        for key,value in [('size',144),('mask',[0]),('symbol','_sin')]:
            s,r,u=self.fixture();s['anchors'][0][key]=value
            with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_wrong_original_member_rejected(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.P4_UNIT]['toolchain_object']='cos_pentium4.obj'
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_actual_x87_fallback_required(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.P4_UNIT]['functions'][0]['rel32_targets']=['__sin_default=0x0068B630']
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_all_coefficient_bindings_required(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.P4_UNIT]['functions'][0]['dir32_targets'].pop()
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_actual_name_and_control_word_roles_required(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.SIN_UNIT]['functions'][0]['dir32_targets'][0]='__DEFAULT_CW_in_mem=vc8_common_pi_by_2_to_61'
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_shared_common_provider_contract_stays_strict(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.sqrt.UNIT]['functions'][0]['dir32_targets']=[]
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_duplicate_or_missing_owner_rejected(self):
        s,r,u=self.fixture();s['anchors'].pop();r.pop()
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_p4_alignment_byte_is_not_extra_function_credit(self):
        s,r,u=self.fixture();a=next(a for a in s['anchors']if a['unit']==g.P4_UNIT);a['size']=426
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
if __name__=='__main__':unittest.main()
