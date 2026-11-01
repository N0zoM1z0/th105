import copy
from pathlib import Path
import struct
import sys
import tomllib
import unittest
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
import linked_gamepad_allocator_origins as linked

class LinkedGamepadAllocatorTests(unittest.TestCase):
    def spec(self):
        s=tomllib.loads(linked.ANCHORS.read_text())
        return s,[dict(address='0x0040E000',size='84')],linked.load_manifest()['units']
    def test_actual_source_and_unmodified_ordinary_unit(self):
        s,r,u=self.spec();unit,a=linked.validate_spec(s,r,u,s['target_sha256'])
        context=linked.build_context(unit)
        self.assertEqual(unit['kind'],'probe');self.assertEqual(context['source'],unit['source'])
        self.assertEqual(context['link_runtime'],'import')
        self.assertNotIn('preserve_public_members',context)
        self.assertTrue(all(f['symbol_base']!=linked.SYMBOL for f in context['functions']))
    def test_wrong_source_or_profile_rejected(self):
        for k,v in [('source','scripts/probes/Other.cpp'),('enable_gs',False),('profile','vc8-sp1-ltcg-o2')]:
            s,r,u=self.spec();u=copy.deepcopy(u);u[linked.UNIT][k]=v
            with self.assertRaises(ValueError):linked.validate_spec(s,r,u,s['target_sha256'])
    def test_wrong_family_extent_or_mask_rejected(self):
        for k,v in [('symbol','?allocate@Other'),('size',83),('mask',[17])]:
            s,r,u=self.spec();s['anchors'][0][k]=v
            with self.assertRaises(ValueError):linked.validate_spec(s,r,u,s['target_sha256'])
    def test_source_closure_cannot_be_omitted(self):
        s,r,u=self.spec();s['source_pins'].pop(next(iter(s['source_pins'])))
        with self.assertRaises(ValueError):linked.validate_spec(s,r,u,s['target_sha256'])
    def fixture(self):
        start=0x10001000;targets=[0x10002000,0x10003000,0x10004000];info=0x10005000;vt=0x10006000
        b=bytearray(b'\x90'*84);b[:2]=b'\x75\x36';b[55]=0xc3
        calls={targets[0]:('??2@YAPAXI@Z',0x689dcb),targets[1]:('??0exception@std@@QAE@ABQBD@Z',0x689f1c),targets[2]:(linked.bad.THROW,0x68a153)}
        for off,target in zip((17,57,80),targets):
            b[off-1]=0xe8;struct.pack_into('<i',b,off,target-start-off-4)
        b[61]=0x68;struct.pack_into('<I',b,62,info)
        b[66:71]=bytes.fromhex('8d4c240851');b[71:75]=bytes.fromhex('c744240c');struct.pack_into('<I',b,75,vt)
        return bytes(b),start,calls,info,vt
    def test_complete_cfg_and_only_five_relocations(self):
        b,start,calls,info,vt=self.fixture();result,records=linked.canonical_allocator(b,start,0x40e000,calls,info,vt)
        allowed={i for off in (17,57,62,75,80)for i in range(off,off+4)}
        self.assertTrue(all(a==v for i,(a,v)in enumerate(zip(b,result))if i not in allowed));self.assertEqual(len(records),3)
    def test_default85_and_unreviewed_size_still_rejected(self):
        b,start,calls,info,vt=self.fixture()
        with self.assertRaises(ValueError):linked.bad.allocator_cfg(b,start,0x10004000,[17,57,80])
        with self.assertRaises(ValueError):linked.bad.allocator_cfg(b,start,0x10004000,[17,57,80],body_size=83)
    def test_wrong_throw_info_object_or_callee_rejected(self):
        b,start,calls,info,vt=self.fixture()
        for off in (17,57,62,68,74,75,80):
            bad=bytearray(b);bad[off]^=1
            with self.assertRaises(ValueError):linked.canonical_allocator(bytes(bad),start,0x40e000,calls,info,vt)
    def test_unreachable_or_interior_branch_rejected(self):
        b,start,calls,info,vt=self.fixture()
        for off,val in ((1,60),(3,0xc3)):
            bad=bytearray(b);bad[off]=val
            with self.assertRaises(ValueError):linked.canonical_allocator(bytes(bad),start,0x40e000,calls,info,vt)

if __name__=='__main__':unittest.main()
