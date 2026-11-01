import copy
import struct
import sys
from pathlib import Path
import tomllib
import unittest
from types import SimpleNamespace
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
import vc8_atan2_entry_origins as g
class Atan2EntryTests(unittest.TestCase):
    def fixture(self):
        s=tomllib.loads(g.ANCHORS.read_text());return s,[dict(address=e[0],size='10')for e in g.ENTRIES],g.load_manifest()['units']
    def test_two_whole_distinct_entries(self):
        s,r,u=self.fixture();aa,_=g.validate_spec(s,r,u,s['target_sha256']);self.assertEqual(len(aa),2)
    def test_no_prefix_or_mask(self):
        for k,v in [('size',9),('mask',[1])]:
            s,r,u=self.fixture();s['anchors'][0][k]=v
            with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_no_duplicate_entry(self):
        s,r,u=self.fixture();r[1]=r[0]
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_original_member_and_archive(self):
        for k,v in [('toolchain_object','atan2_sse2.obj'),('toolchain_archive_sha256','0'*64)]:
            s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT][k]=v
            with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_exact_tail_destination_required(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT]['functions'][0]['rel32_targets']=['__ctrandisp2=0x00400000']
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_full_table_binding_required(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT]['functions'][0]['dir32_targets']=[]
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def body(self):return b'\xba'+struct.pack('<I',0x6f8990)+b'\xe9'+struct.pack('<i',0x6965ab-(0x68bb70+10))
    def test_real_register_and_named_tail(self):self.assertEqual(len(g.entry_shape(self.body(),0x68bb70,0x6f8990,0x6965ab)),2)
    def test_wrong_table_or_target(self):
        for off in [1,6]:
            b=bytearray(self.body());b[off]^=1
            with self.assertRaises(ValueError):g.entry_shape(bytes(b),0x68bb70,0x6f8990,0x6965ab)
    def test_no_call_or_register_substitution(self):
        for off,val in [(0,0xb9),(5,0xe8)]:
            b=bytearray(self.body());b[off]=val
            with self.assertRaises(ValueError):g.entry_shape(bytes(b),0x68bb70,0x6f8990,0x6965ab)
    def test_no_padding_or_short_root(self):
        for b in [self.body()[:-1],self.body()+b'\x90']:
            with self.assertRaises(ValueError):g.entry_shape(b,0x68bb70,0x6f8990,0x6965ab)
    def reader(self,kind=6,add=0,name='ptr'):
        return SimpleNamespace(section=lambda s:SimpleNamespace(raw_size=4),symbol=lambda s:SimpleNamespace(value=0),raw=lambda s,n:struct.pack('<I',add),refs=lambda s,n:[(0,kind,name)])
    def test_whole_storage_relocation_checked(self):self.assertEqual(g.replay(self.reader(),'s',0x1000,4,{'ptr':0x2000},lambda a,n:struct.pack('<I',0x2000)),struct.pack('<I',0x2000))
    def test_unsupported_relocation_or_addend_rejected(self):
        for r in [self.reader(kind=7),self.reader(add=1),self.reader(name='unknown')]:
            with self.assertRaises(ValueError):g.replay(r,'s',0x1000,4,{'ptr':0x2000},lambda a,n:struct.pack('<I',0x2000))
    def test_whole_native_storage_mutation_rejected(self):
        with self.assertRaises(ValueError):g.replay(self.reader(),'s',0x1000,4,{'ptr':0x2000},lambda a,n:bytes(4))
if __name__=='__main__':unittest.main()
