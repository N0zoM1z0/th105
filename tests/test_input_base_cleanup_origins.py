import copy
from pathlib import Path
import struct
import sys
import tomllib
from types import SimpleNamespace
import unittest
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
import input_base_cleanup_origins as g
class InputCleanupTests(unittest.TestCase):
    def fixture(self):
        s=tomllib.loads(g.ANCHORS.read_text());return s,[dict(address='0x00409D50',size='7')],g.load_manifest()['units']
    def test_whole_empty_lifecycle(self):
        s,r,u=self.fixture();a,_=g.validate_spec(s,r,u,s['target_sha256']);self.assertEqual(a['symbol'],g.DTOR)
    def test_no_mask_or_short_body(self):
        for k,v in [('size',6),('mask',[2])]:
            s,r,u=self.fixture();s['anchors'][0][k]=v
            with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_source_and_compiler_pin(self):
        for k in ['source_sha256','compiler_sha256']:
            s,r,u=self.fixture();s[k]='0'*64
            with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_published_type_not_old_view(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT]['functions'][0]['symbol_base']='??1CInputManagerLifetimeView@th105@@UAE@XZ'
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_scalar_owner_required(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT]['functions']=u[g.UNIT]['functions'][:1]
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def weak(self):
        symbols={0:SimpleNamespace(name=g.SCALAR,section_number=0,value=0),1:SimpleNamespace(name=g.WEAK,section_number=0,value=0),3:SimpleNamespace(name=g.SCALAR,section_number=11,value=0)}
        reader=SimpleNamespace(cf=SimpleNamespace(symbols=symbols),symbol=lambda n:symbols[3]);raw=bytearray(100);struct.pack_into('<II',raw,8,20,4);raw[52:56]=bytes([32,0,105,1]);struct.pack_into('<II',raw,56,0,2);return reader,raw
    def test_original_weak_fallback_to_defined_scalar(self):
        r,b=self.weak();self.assertEqual(g.weak_fallback(r,bytes(b))['fallback'],g.SCALAR)
    def test_wrong_weak_storage_or_aux_rejected(self):
        for off in [54,55]:
            r,b=self.weak();b[off]^=1
            with self.assertRaises(ValueError):g.weak_fallback(r,bytes(b))
    def test_wrong_weak_target_or_search_mode_rejected(self):
        for off in [56,60]:
            r,b=self.weak();b[off]^=1
            with self.assertRaises(ValueError):g.weak_fallback(r,bytes(b))
    def test_fallback_must_have_defined_body(self):
        r,b=self.weak();r.cf.symbols[3].section_number=0
        with self.assertRaises(ValueError):g.weak_fallback(r,bytes(b))
    def test_extra_weak_aux_payload_rejected(self):
        r,b=self.weak();b[64]=1
        with self.assertRaises(ValueError):g.weak_fallback(r,bytes(b))
if __name__=='__main__':unittest.main()
