import copy
from pathlib import Path
import struct
import sys
import tomllib
from types import SimpleNamespace
import unittest
from unittest.mock import patch
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
import linked_byte_allocator_origins as linked

class LinkedByteAllocatorTests(unittest.TestCase):
    def spec(self):
        s=tomllib.loads(linked.ANCHORS.read_text())
        return s,[dict(address='0x0040AB70',size='78')],linked.load_manifest()['units']
    def test_only_existing_exact_source_context(self):
        s,rows,units=self.spec();u,a=linked.validate_spec(s,rows,units,s['target_sha256'])
        self.assertEqual(a['size'],78);self.assertEqual(u['source'],'src/input/InputStateTableUpdate.cpp')
    def test_different_root_profile_or_public_sibling_rejected(self):
        for k,v in [('link_runtime','static'),('preserve_public_members',[]),('enable_gs',True)]:
            s,rows,units=self.spec();units=copy.deepcopy(units);units[linked.UNIT][k]=v
            with self.assertRaises(ValueError):linked.validate_spec(s,rows,units,s['target_sha256'])
    def test_wrong_source_family_or_partial_extent_rejected(self):
        for k,v in [('symbol',linked.SYMBOL.replace('@E@','@D@')),('size',77),('mask',[11])]:
            s,rows,u=self.spec();s['anchors'][0][k]=v
            with self.assertRaises(ValueError):linked.validate_spec(s,rows,u,s['target_sha256'])
    def fixture(self):
        start=0x10001000;targets=[0x10002000,0x10003000,0x10004000];info=0x10005000;vt=0x10006000
        b=bytearray(b'\x90'*78);b[:2]=b'\x75\x30';b[49]=0xc3
        calls={targets[0]:('??2@YAPAXI@Z',0x689dcb),targets[1]:('??0exception@std@@QAE@ABQBD@Z',0x689f1c),targets[2]:(linked.bad.THROW,0x68a153)}
        for off,target in zip((11,51,74),targets):
            b[off-1]=0xe8;struct.pack_into('<i',b,off,target-start-off-4)
        b[55]=0x68;struct.pack_into('<I',b,56,info)
        b[60:65]=bytes.fromhex('8d4c240851');b[65:69]=bytes.fromhex('c744240c');struct.pack_into('<I',b,69,vt)
        return bytes(b),start,calls,info,vt
    def test_full78_cfg_and_exact_five_fields(self):
        b,start,calls,info,vt=self.fixture()
        result,records=linked.canonical_allocator(b,start,0x40ab70,calls,info,vt)
        allowed={i for off in (11,51,56,69,74)for i in range(off,off+4)}
        self.assertTrue(all(a==v for i,(a,v)in enumerate(zip(b,result))if i not in allowed));self.assertEqual(len(records),3)
    def test_old85_default_is_not_relaxed(self):
        b,start,calls,info,vt=self.fixture()
        with self.assertRaises(ValueError):linked.bad.allocator_cfg(b,start,0x10004000,[11,51,74])
        with self.assertRaises(ValueError):linked.bad.allocator_cfg(b,start,0x10004000,[11,51,74],body_size=79)
    def test_wrong_throw_info_object_or_terminal_target_rejected(self):
        b,start,calls,info,vt=self.fixture()
        for off in (56,62,68,69,74):
            bad=bytearray(b);bad[off]^=1
            with self.assertRaises(ValueError):linked.canonical_allocator(bytes(bad),start,0x40ab70,calls,info,vt)
    def test_unreachable_or_interior_branch_rejected(self):
        b,start,calls,info,vt=self.fixture()
        for off,val in ((1,54),(3,0xc3)):
            bad=bytearray(b);bad[off]=val
            with self.assertRaises(ValueError):linked.canonical_allocator(bytes(bad),start,0x40ab70,calls,info,vt)
    def import_fixture(self):
        name='??2@YAPAXI@Z';at=0x10001000;slot=0x10002000
        pe=SimpleNamespace(get_data=lambda r,n:b'\xff\x25'+struct.pack('<I',slot))
        return pe,{at:[(name,'msvcrt:MSVCR80.dll')]},{name:[(at,'f   msvcrt:MSVCR80.dll')]},name
    def test_genuine_named_import_identity(self):
        pe,fs,s,n=self.import_fixture()
        with patch.object(linked.bad,'import_at',return_value=[('msvcr80.dll',n)]):
            self.assertEqual(linked.import_callable(pe,fs,s,n,n),0x10001000)
    def test_same_thunk_bytes_wrong_dll_or_export_rejected(self):
        for result in ([('other.dll','??2@YAPAXI@Z')],[('msvcr80.dll','other')]):
            pe,fs,s,n=self.import_fixture()
            with patch.object(linked.bad,'import_at',return_value=result):
                with self.assertRaises(ValueError):linked.import_callable(pe,fs,s,n,n)

if __name__=='__main__':unittest.main()
