import copy
from pathlib import Path
import struct
import sys
import tomllib
import unittest
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
import vc8_sqrt_shared_origins as g
class SqrtSharedTests(unittest.TestCase):
    def fixture(self):
        s=tomllib.loads(g.ANCHORS.read_text());return s,[dict(address='0x0068A39D',size='157')],g.load_manifest()['units']
    def test_original_shared_body_contract(self):
        s,r,u=self.fixture();a,unit=g.validate_spec(s,r,u,s['target_sha256']);self.assertEqual(a['symbol'],'start')
    def test_not_a_short_prefix_or_public_entry_substitute(self):
        for key,value in [('size',156),('mask',[0]),('symbol','__CIsqrt')]:
            s,r,u=self.fixture();s['anchors'][0][key]=value
            with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_original_math_member_required(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT]['toolchain_object']='sin.obj'
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_actual_exit_roles_required(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT]['functions'][0]['rel32_targets'][1]='__fast_exit=0x00690E7B'
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_actual_operation_name_binding_required(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT]['functions'][0]['dir32_targets'][1]='_NAME_=vc8_sqrt_indefinite'
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_conditional_exit_to_complete_owned_helper(self):
        body=b'\x0f\x84'+struct.pack('<i',0x2000-0x1006)+b'\xc3'
        p=g.closed_graph([(0x1000,body,'owner'),(0x2000,b'\xc3','helper')],[0x1000],set());self.assertEqual(p['unreachable_bytes'],0)
    def test_external_call_is_only_explicit_named_call(self):
        body=b'\xe8'+struct.pack('<i',0x3000-0x1005)+b'\xc3'
        self.assertEqual(g.closed_graph([(0x1000,body,'owner')],[0x1000],{0x3000})['reached'],2)
        with self.assertRaises(ValueError):g.closed_graph([(0x1000,body,'owner')],[0x1000],set())
    def test_external_conditional_or_tail_jump_not_waived(self):
        for op,width in [(b'\xe9',5),(b'\x0f\x84',6)]:
            body=op+struct.pack('<i',0x3000-0x1000-width)+b'\xc3'
            with self.assertRaises(ValueError):g.closed_graph([(0x1000,body,'owner')],[0x1000],{0x3000})
    def test_cross_region_mid_helper_entry_rejected(self):
        body=b'\xe9'+struct.pack('<i',0x2001-0x1005)
        with self.assertRaises(ValueError):g.closed_graph([(0x1000,body,'owner'),(0x2000,b'\x90\xc3','helper')],[0x1000],set())
    def test_unreached_bytes_require_real_second_entry(self):
        regions=[(0x1000,b'\xc3\xc3','owner')]
        with self.assertRaises(ValueError):g.closed_graph(regions,[0x1000],set())
        self.assertEqual(g.closed_graph(regions,[0x1000,0x1001],set())['reached'],2)
    def test_overlap_or_duplicate_region_identity_rejected(self):
        for regions in [[(0x1000,b'\x90\xc3','one'),(0x1001,b'\xc3','two')],[(0x1000,b'\xc3','same'),(0x2000,b'\xc3','same')]]:
            with self.assertRaises(ValueError):g.closed_graph(regions,[0x1000],set())
    def test_indirect_trap_and_wrong_return_cleanup_rejected(self):
        for body in [b'\xff\xe0',b'\xcc\xc3',b'\xc2\x04\x00']:
            with self.assertRaises(ValueError):g.closed_graph([(0x1000,body,'owner')],[0x1000],set())
if __name__=='__main__':unittest.main()
