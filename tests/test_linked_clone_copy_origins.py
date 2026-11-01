from pathlib import Path
import sys
import tomllib
import unittest
from unittest.mock import patch
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
import linked_clone_copy_origins as linked

class LinkedCloneCopyTests(unittest.TestCase):
    def spec(self):
        s=tomllib.loads(linked.ANCHORS.read_text())
        return s,[dict(address='0x006A8370',size='46')]
    def test_only_runtime_error_clone_root_selected(self):
        s,rows=self.spec();self.assertEqual(linked.validate_spec(s,rows,s['target_sha256'])['size'],46)
        s['anchors'][0]['symbol']=s['anchors'][0]['symbol'].replace('runtime_error','invalid_argument')
        with self.assertRaises(ValueError):linked.validate_spec(s,rows,s['target_sha256'])
    def test_support_does_not_gain_new_credit(self):
        s,rows=self.spec();rows.append(dict(address='0x006A5E40',size='147'))
        with self.assertRaises(ValueError):linked.validate_spec(s,rows,s['target_sha256'])
    def test_whole_extent_and_fixed_digest_required(self):
        for key,value in [('size',45),('sha256','0'*64),('mask',[9])]:
            s,rows=self.spec();s['anchors'][0][key]=value
            with self.assertRaises(ValueError):linked.validate_spec(s,rows,s['target_sha256'])
    def fixture(self):
        symbols={n:[(0x10002000+i*32,'original-0.obj')]for i,(n,a,o,t)in enumerate(linked.VTABLES)}
        facts={}
        for i,(n,a,o,t)in enumerate(linked.VTABLES):facts[0x10002000+i*32]=facts[a]=(0,o,0,t)
        return symbols,facts
    def test_all_primary_and_secondary_rtti_roles(self):
        symbols,facts=self.fixture()
        with patch.object(linked,'rtti',side_effect=lambda pe,a:facts[a]):
            result=linked.bind_vtables(None,None,symbols)
            self.assertEqual(len(result),8)
            self.assertEqual({facts[r['target_address']][1]for r in result},{0,40,60})
    def test_wrong_secondary_offset_rejected(self):
        symbols,facts=self.fixture();facts[0x6d5ea0]=(0,40,0,linked.CLONE_TYPE)
        with patch.object(linked,'rtti',side_effect=lambda pe,a:facts[a]):
            with self.assertRaisesRegex(ValueError,'subobject'):linked.bind_vtables(None,None,symbols)
    def test_nominal_shape_substitution_rejected(self):
        symbols,facts=self.fixture();facts[0x6d5eb8]=(0,0,0,linked.CLONE_TYPE.replace('runtime_error','invalid_argument'))
        with patch.object(linked,'rtti',side_effect=lambda pe,a:facts[a]):
            with self.assertRaisesRegex(ValueError,'class'):linked.bind_vtables(None,None,symbols)
    def test_wrong_original_vtable_owner_rejected(self):
        symbols,facts=self.fixture();key=next(iter(symbols));symbols[key]=[(0x10002000,'fake.obj')]
        with self.assertRaises(ValueError):linked.bind_vtables(None,None,symbols)
    def test_complete_one_state_eh_contract_not_prefix(self):
        import struct
        info=struct.pack('<9I',0x19930522,1,0x10002000,0,0,0,0,0,1)
        unwind=struct.pack('<2I',0xffffffff,0x10003000)
        self.assertEqual(linked.logic.canonical_metadata(info,info,unwind,unwind)['metadata_bytes'],44)
        bad=bytearray(info);bad[32]^=1
        with self.assertRaises(ValueError):linked.logic.canonical_metadata(bytes(bad),info,unwind,unwind)

if __name__=='__main__':unittest.main()
