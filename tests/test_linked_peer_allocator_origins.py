import copy
from pathlib import Path
import struct
import sys
import tomllib
import unittest
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
import linked_peer_allocator_origins as linked

class LinkedPeerAllocatorTests(unittest.TestCase):
    def spec(self):
        s=tomllib.loads(linked.ANCHORS.read_text())
        return s,[dict(address='0x00413C60',size='81')],linked.load_manifest()['units']
    def test_actual_source_and_unmodified_ordinary_unit(self):
        s,r,u=self.spec();unit,a=linked.validate_spec(s,r,u,s['target_sha256'])
        self.assertEqual(unit['kind'],'probe')
        self.assertNotIn(linked.SYMBOL,linked.network.EXPORTS)
        self.assertEqual(len(linked.network.SOURCES),7)
    def test_wrong_source_or_profile_rejected(self):
        for k,v in [('source','scripts/probes/Other.cpp'),('enable_gs',False),('profile','vc8-sp1-ltcg-o2')]:
            s,r,u=self.spec();u=copy.deepcopy(u);u[linked.UNIT][k]=v
            with self.assertRaises(ValueError):linked.validate_spec(s,r,u,s['target_sha256'])
    def test_wrong_family_extent_or_mask_rejected(self):
        for k,v in [('symbol','?allocate@Other'),('size',83),('mask',[14])]:
            s,r,u=self.spec();s['anchors'][0][k]=v
            with self.assertRaises(ValueError):linked.validate_spec(s,r,u,s['target_sha256'])
    def test_source_closure_cannot_be_omitted(self):
        s,r,u=self.spec();s['source_pins'].pop(next(iter(s['source_pins'])))
        with self.assertRaises(ValueError):linked.validate_spec(s,r,u,s['target_sha256'])
    def fixture(self):
        start=0x10001000;targets=[0x10002000,0x10003000,0x10004000];info=0x10005000;vt=0x10006000
        b=bytearray(b'\x90'*81);b[:2]=b'\x75\x33';b[52]=0xc3
        calls={targets[0]:('??2@YAPAXI@Z',0x689dcb),targets[1]:('??0exception@std@@QAE@ABQBD@Z',0x689f1c),targets[2]:(linked.bad.THROW,0x68a153)}
        for off,target in zip((14,54,77),targets):
            b[off-1]=0xe8;struct.pack_into('<i',b,off,target-start-off-4)
        b[58]=0x68;struct.pack_into('<I',b,59,info)
        b[63:68]=bytes.fromhex('8d4c240851');b[68:72]=bytes.fromhex('c744240c');struct.pack_into('<I',b,72,vt)
        return bytes(b),start,calls,info,vt
    def test_complete_cfg_and_only_five_relocations(self):
        b,start,calls,info,vt=self.fixture();result,records=linked.canonical_allocator(b,start,0x413c60,calls,info,vt)
        allowed={i for off in (14,54,59,72,77)for i in range(off,off+4)}
        self.assertTrue(all(a==v for i,(a,v)in enumerate(zip(b,result))if i not in allowed));self.assertEqual(len(records),3)
    def test_default85_and_unreviewed_size_still_rejected(self):
        b,start,calls,info,vt=self.fixture()
        with self.assertRaises(ValueError):linked.bad.allocator_cfg(b,start,0x10004000,[14,54,77])
        with self.assertRaises(ValueError):linked.bad.allocator_cfg(b,start,0x10004000,[14,54,77],body_size=83)
    def test_wrong_throw_info_object_or_callee_rejected(self):
        b,start,calls,info,vt=self.fixture()
        for off in (14,54,59,65,71,72,77):
            bad=bytearray(b);bad[off]^=1
            with self.assertRaises(ValueError):linked.canonical_allocator(bytes(bad),start,0x413c60,calls,info,vt)
    def test_unreachable_or_interior_branch_rejected(self):
        b,start,calls,info,vt=self.fixture()
        for off,val in ((1,57),(3,0xc3)):
            bad=bytearray(b);bad[off]=val
            with self.assertRaises(ValueError):linked.canonical_allocator(bytes(bad),start,0x413c60,calls,info,vt)

class ReceiveContextTests(unittest.TestCase):
    def fixture(self):
        return dict(thread='#include "platform/BattleThreadHandle.hpp"\nnamespace th105 {\nBattleThreadHandle::BattleThreadHandle() {}\n}',
            peer='namespace th105 { extern "C" __declspec(dllimport) int __stdcall sendto(int);\nNetworkPeerMap::iterator NetworkWinsockPeerRemovalView::find_peer() {}\n}',
            main='namespace th105 { void actual() {\n                    remove_peer(it->second->slot_10);\nconnection_worker_13c.start(network_winsock_connection_thread, &handoff);\n} }')
    def test_only_actual_implementation_connections_are_changed(self):
        t=self.fixture();result=linked.network.materialize(t)
        self.assertIn('reinterpret_cast<NetworkWinsockPeerRemovalView *>(this)->remove_peer',result)
        self.assertIn('reinterpret_cast<BattleThreadHandle *>(&connection_worker_13c)->start',result)
        self.assertNotIn('int __stdcall sendto',result)
        self.assertNotIn('BattleThreadHandle::BattleThreadHandle() {}',result)
        self.assertNotIn('NetworkWinsockPeerRemovalView::find_peer() {}',result)
        self.assertEqual(result.count('void actual()'),1)
    def test_missing_or_duplicate_real_call_is_rejected(self):
        for suffix in ('', 'connection_worker_13c.start(network_winsock_connection_thread, &handoff);'):
            t=self.fixture()
            if suffix:t['main']+=suffix
            else:t['main']=t['main'].replace('remove_peer(it->second->slot_10);','other();')
            with self.assertRaises(ValueError):linked.network.materialize(t)
    def test_ambiguous_declaration_boundary_is_rejected(self):
        t=self.fixture();t['thread']+='BattleThreadHandle::BattleThreadHandle()'
        with self.assertRaises(ValueError):linked.network.materialize(t)

class InitializeContextTests(unittest.TestCase):
    fixture=ReceiveContextTests.fixture
    def extra_fixture(self):
        t=self.fixture();t['initialize']='namespace th105 { void start() {\n        wait_for_exit();\n} }'
        t['service']='namespace th105 { void service() { owner->remove_peer(slot); } }'
        return t
    def test_initializer_and_service_use_actual_implementations(self):
        out=linked.network.extra_contexts(self.extra_fixture())
        self.assertEqual(set(out),{'initialize','service'})
        self.assertTrue(out['initialize'].startswith('#include "platform/BattleThreadHandle.hpp"\n'))
        self.assertIn('reinterpret_cast<BattleThreadHandle *>(this)->wait_for_exit();',out['initialize'])
        self.assertIn('reinterpret_cast<NetworkWinsockPeerRemovalView *>(owner)->remove_peer(slot);',out['service'])
        self.assertNotIn('BattleThreadHandle::BattleThreadHandle() {}',out['initialize'])
    def test_missing_or_duplicate_initialize_wait_rejected(self):
        for suffix in ('', '        wait_for_exit();'):
            t=self.extra_fixture()
            if suffix:t['initialize']+=suffix
            else:t['initialize']=t['initialize'].replace('wait_for_exit();','other();')
            with self.assertRaises(ValueError):linked.network.extra_contexts(t)
    def test_changed_service_call_rejected(self):
        t=self.extra_fixture();t['service']=t['service'].replace('owner->remove_peer(slot);','other();')
        with self.assertRaises(ValueError):linked.network.extra_contexts(t)

if __name__=='__main__':unittest.main()
