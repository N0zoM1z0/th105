import copy
from pathlib import Path
import sys
import tomllib
import unittest
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
import vc8_log10_shared_origins as g
class Log10SharedTests(unittest.TestCase):
    def fixture(self):
        s=tomllib.loads(g.ANCHORS.read_text());return s,[dict(address='0x00697C6E',size='614')],g.core.load_manifest()['units']
    def test_whole_actual_shared_extent(self):
        s,r,u=self.fixture();a,_=g.validate_spec(s,r,u,s['target_sha256']);self.assertEqual(a['size'],614)
    def test_wrong_log_family_rejected(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT]['toolchain_object']='log_pentium4.obj'
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_no_short_body_or_mask(self):
        for k,v in [('size',613),('mask',[0]),('symbol','__CIlog10_pentium4')]:
            s,r,u=self.fixture();s['anchors'][0][k]=v
            with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_no_padding_credit(self):
        s,r,u=self.fixture();s['anchors'][0]['size']=626;r[0]['size']='626'
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_provider_target_exact(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT]['functions'][0]['rel32_targets']=['___libm_error_support=0x00694A93']
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_nonzero_addend_role_required(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT]['functions'][0]['dir32_targets'].remove('coeff+0x10=vc8_log10_p4_coeff_16')
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_actual_trailing_storage(self):g.original_tail(g.TAIL,0x1000)
    def test_no_generic_neutral_padding_waiver(self):
        for b in [b'\x90'*12,bytes.fromhex('8da424000000000501000000'),g.TAIL+b'\x90',g.TAIL[:-1]]:
            with self.assertRaises(ValueError):g.original_tail(b,0x1000)
    def test_closed_graph_rejects_unreachable_tail(self):
        with self.assertRaises(ValueError):g.core.closed_graph([(0x1000,b'\xc3'+g.TAIL,'root')],[0x1000],set())
    def test_closed_graph_rejects_external_conditional_exit(self):
        with self.assertRaises(ValueError):g.core.closed_graph([(0x1000,bytes.fromhex('7501c3'),'root')],[0x1000],{0x1003})
if __name__=='__main__':unittest.main()
