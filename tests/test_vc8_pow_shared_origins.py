import copy
from pathlib import Path
import sys
import tomllib
import unittest
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
import vc8_pow_shared_origins as g
class PowSharedTests(unittest.TestCase):
    def fixture(self):
        s=tomllib.loads(g.ANCHORS.read_text());return s,[dict(address='0x0068C28D',size='453')],g.sin.sqrt.load_manifest()['units']
    def test_whole_shared_extent(self):
        s,r,u=self.fixture();a,_=g.validate_spec(s,r,u,s['target_sha256']);self.assertEqual(a['size'],453)
    def test_no_mask_or_partial_body(self):
        for k,v in [('size',452),('mask',[0]),('symbol','_pow')]:
            s,r,u=self.fixture();s['anchors'][0][k]=v
            with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_integer_helper_not_new_credit(self):
        s,r,u=self.fixture();s['anchors'][0]['size']=493;r[0]['size']='493'
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_p4_not_substitute_for_x87_member(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT]['toolchain_object']='pow_pentium4.obj'
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_required_two_argument_error_role(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT]['functions'][0]['rel32_targets'].remove('__startTwoArgErrorHandling=0x00690D70')
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_external_extended_infinity_role_required(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT]['functions'][0]['dir32_targets'].remove('__infinity=vc8_pow_infinity')
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_actual_selector_protocol_required(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.sin.SIN_UNIT]['functions'][0]['rel32_targets']=[]
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_original_alignment(self):g.original_padding(g.TAIL)
    def test_generic_padding_not_accepted(self):
        for b in [b'\x90'*15,g.TAIL[:-1],g.TAIL+b'\x90',bytes.fromhex('8da424010000008da4240000000090')]:
            with self.assertRaises(ValueError):g.original_padding(b)
    def test_graph_does_not_waive_external_tail(self):
        with self.assertRaises(ValueError):g.sin.sqrt.closed_graph([(0x1000,bytes.fromhex('e900000000'),'root')],[0x1000],{0x1005})
if __name__=='__main__':unittest.main()
