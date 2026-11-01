import copy
from pathlib import Path
import struct
import sys
import tomllib
from types import SimpleNamespace
import unittest
from unittest.mock import patch
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
import vc8_pointer_policy_origins as g
class PointerPolicyTests(unittest.TestCase):
    def fixture(self):
        s=tomllib.loads(g.ANCHORS.read_text());return s,[dict(address=a,size=str(r['size']))for a,r in g.CONTRACT.items()],g.load_manifest()['units']
    def test_complete_three_roots(self):
        s,r,u=self.fixture();self.assertEqual(len(g.validate_spec(s,r,u,s['target_sha256'])),3)
    def test_no_mask_or_partial_root(self):
        for k,v in [('size',12),('mask',[2])]:
            s,r,u=self.fixture();s['anchors'][0][k]=v
            with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_no_duplicate_ret_credit(self):
        s,r,u=self.fixture();s['anchors'].append(copy.deepcopy(s['anchors'][-1]))
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_ret_not_unhandld_object(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u['vc8-original-winxfltr-initializer']['toolchain_object']='unhandld.obj'
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_pinned_archive_required(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[s['anchors'][0]['unit']]['toolchain_archive_sha256']='0'*64
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_sigabrt_not_other_encoded_handler(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u['vc8-original-sigabrt-getter']['functions'][0]['dir32_targets']=['_abort_action=wrong_handler']
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_no_invented_call(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u['vc8-original-winxfltr-initializer']['functions'][0]['rel32_targets']=['wrong=0x00400000']
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def reader(self,add=0):return SimpleNamespace(symbol=lambda n:SimpleNamespace(value=0),section=lambda n:SimpleNamespace(name='.text',raw_size=5),raw=lambda n,s:b'\xa3'+struct.pack('<I',add),refs=lambda n,s:[(1,6,'cell')])
    def region(self):return dict(symbol='setter',size=5,address=0x1000,refs=[[1,6,'cell',0x2000]])
    def test_complete_storage_replay(self):self.assertEqual(g.whole(self.reader(),self.region(),lambda a,n:b'\xa3'+struct.pack('<I',0x2000)),b'\xa3'+struct.pack('<I',0x2000))
    def test_actual_source_addend_required(self):
        with self.assertRaises(ValueError):g.whole(self.reader(1),self.region(),lambda a,n:b'\xa3'+struct.pack('<I',0x2000))
    def test_named_relocation_roles_required(self):
        r=self.region();r['refs'][0][2]='other'
        with self.assertRaises(ValueError):g.whole(self.reader(),r,lambda a,n:bytes(5))
    def test_nonrelocation_byte_checked(self):
        with self.assertRaises(ValueError):g.whole(self.reader(),self.region(),lambda a,n:b'\xa1'+struct.pack('<I',0x2000))
    def bss_reader(self,offset=8,raw_offset=0):return SimpleNamespace(symbol=lambda n:SimpleNamespace(value=0 if n=='base'else offset,section_number=3),section=lambda n:SimpleNamespace(name='.bss',raw_size=20,raw_offset=raw_offset,reloc_count=0,characteristics=0x80))
    def test_full_bss_no_raw_read(self):
        with patch.object(g,'zero_initialized_counter',return_value=bytes(4))as z:
            result=g.bss(self.bss_reader(),'base',20,0x2000,[('base',0),('abort',8)],None);self.assertFalse(result['raw_bss_read']);self.assertEqual(z.call_count,5)
    def test_wrong_bss_field_or_raw_offset_rejected(self):
        for r in [self.bss_reader(offset=4),self.bss_reader(raw_offset=1)]:
            with self.assertRaises(ValueError):g.bss(r,'base',20,0x2000,[('base',0),('abort',8)],None)
    def test_native_bss_must_be_zero_fill(self):
        with patch.object(g,'zero_initialized_counter',return_value=b'\x01\x00\x00\x00'):
            with self.assertRaises(ValueError):g.bss(self.bss_reader(),'base',20,0x2000,[('base',0),('abort',8)],None)
if __name__=='__main__':unittest.main()
