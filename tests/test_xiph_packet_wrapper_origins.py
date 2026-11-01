import copy
from pathlib import Path
import sys
import tomllib
import unittest
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
import xiph_packet_wrapper_origins as g
class PacketWrapperTests(unittest.TestCase):
    def fixture(self):
        s=tomllib.loads(g.ANCHORS.read_text());return s,[dict(address=a['address'],size='21')for a in s['anchors']],g.load_manifest()['units']
    def test_original_pair_and_provider(self):
        s,r,u=self.fixture();a,unit=g.validate_spec(s,r,u,s['target_sha256']);self.assertEqual(len(a),2);self.assertEqual(len(unit['functions']),3)
    def test_source_archive_and_member_cannot_change(self):
        for key,value in [('source','scripts/fake.py'),('kind','probe'),('sdk_component','vorbis'),('sdk_object','bitwise.obj'),('sdk_archive_sha256','0'*64),('profile','vc8-sp1-probe-o2')]:
            s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT][key]=value
            with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_no_prefix_mask_or_swapped_symbol(self):
        for key,value in [('size',20),('mask',[13]),('symbol','_ogg_stream_packetpeek')]:
            s,r,u=self.fixture();s['anchors'][0][key]=value
            with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_named_provider_cannot_change(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT]['functions'][0]['rel32_targets']=['__packetout=0x006B6950']
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_provider_regression_cannot_be_removed(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT]['functions'].pop()
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_padding_cannot_be_claimed_as_code(self):
        s,r,u=self.fixture();s['anchors'][0]['size']=32;r[0]['size']='32'
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_formal_partial_body_rejected(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT]['functions'][0]['size']=20
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
if __name__=='__main__':unittest.main()
