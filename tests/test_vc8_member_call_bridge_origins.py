import copy
from pathlib import Path
import sys
import tomllib
import unittest
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
import vc8_member_call_bridge_origins as g
class MemberBridgeTests(unittest.TestCase):
    def fixture(self):
        s=tomllib.loads(g.ANCHORS.read_text());return s,[dict(address='0x0068998E',size='7')],g.load_manifest()['units']
    def test_one_original_physical_body(self):
        s,r,u=self.fixture();a,unit=g.validate_spec(s,r,u,s['target_sha256']);self.assertEqual(a['size'],7)
    def test_alias_cannot_add_a_second_credit(self):
        s,r,u=self.fixture();s['anchors'].append(copy.deepcopy(s['anchors'][0]));r.append(copy.deepcopy(r[0]))
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_source_archive_and_member_required(self):
        for k,v in [('toolchain_library','libcpmt'),('toolchain_object','frame.obj'),('toolchain_archive_sha256','0'*64),('kind','probe')]:
            s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT][k]=v
            with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_shortened_or_masked_anchor_rejected(self):
        for k,v in [('size',6),('mask',[0])]:
            s,r,u=self.fixture();s['anchors'][0][k]=v
            with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_formal_relocation_or_prefix_rejected(self):
        for k,v in [('rel32_targets',['fake=0x00401000']),('size',6)]:
            s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT]['functions'][0][k]=v
            with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_different_native_candidate_rejected(self):
        s,r,u=self.fixture();r[0]['address']='0x0041DDB0'
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_bridge_linear_stack_transfer(self):
        self.assertEqual(len(g.bridge_cfg(bytes.fromhex('5859870424ffe0'),0x1000)),4)
    def test_wrong_return_this_or_tail_register_rejected(self):
        for body in ['5a59870424ffe0','585a870424ffe0','5859870424ffe1']:
            with self.assertRaises(ValueError):g.bridge_cfg(bytes.fromhex(body),0x1000)
    def test_wrong_stack_slot_or_direct_jump_rejected(self):
        for body in ['585987442404ffe0','5859870424eb00']:
            with self.assertRaises(ValueError):g.bridge_cfg(bytes.fromhex(body),0x1000)
    def test_extra_or_truncated_instruction_rejected(self):
        for body in ['5859870424ffe090','5859870424ff','5859870424c3']:
            with self.assertRaises(ValueError):g.bridge_cfg(bytes.fromhex(body),0x1000)
if __name__=='__main__':unittest.main()
