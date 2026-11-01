from pathlib import Path
import struct
import sys
import tomllib
from types import SimpleNamespace
import unittest
from unittest.mock import patch
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
import linked_bad_exception_origins as g

class BadExceptionScopeTests(unittest.TestCase):
    def fixture(self):
        s=tomllib.loads(g.ANCHORS.read_text());return s,[dict(address=a,size=str(v[0]))for a,v in g.CONTRACT.items()]
    def test_three_whole_original_runtime_symbols(self):
        s,r=self.fixture();self.assertEqual(len(g.validate_spec(s,r,s['target_sha256'])),3)
    def test_bad_alloc_is_not_bad_exception(self):
        s,r=self.fixture();s['anchors'][0]['symbol']=s['anchors'][0]['symbol'].replace('bad_exception','bad_alloc')
        with self.assertRaises(ValueError):g.validate_spec(s,r,s['target_sha256'])
    def test_partial_extent_or_mask_rejected(self):
        for k,v in [('size',10),('mask',[2])]:
            s,r=self.fixture();s['anchors'][0][k]=v
            with self.assertRaises(ValueError):g.validate_spec(s,r,s['target_sha256'])
    def test_duplicate_or_missing_member_rejected(self):
        s,r=self.fixture();s['anchors'][1]=dict(s['anchors'][0])
        with self.assertRaises(ValueError):g.validate_spec(s,r,s['target_sha256'])
    def body_fixture(self):
        at=0x10001000;callee=0x10002000;vt=0x10003000;target=0x68fb16;b=bytearray(b'\x90'*24)
        b[7]=0xe8;struct.pack_into('<i',b,8,callee-at-12);b[12:14]=b'\xc7\x01';struct.pack_into('<I',b,14,vt);b[21:]=b'\xc2\x04\x00'
        native=bytearray(b);struct.pack_into('<i',native,8,0x689f82-target-12);struct.pack_into('<I',native,14,0x6cd9b8)
        pe=SimpleNamespace(OPTIONAL_HEADER=SimpleNamespace(SizeOfImage=0x10000),DIRECTORY_ENTRY_EXPORT=SimpleNamespace(symbols=[]))
        table=dict(source_address=vt,target_address=0x6cd9b8,symbol=g.VTABLE,target_key='bad-exception')
        anchor=dict(address='0x0068FB16',size=24,symbol=g.COPY,sha256=g.digest(native));rows=[dict(address=anchor['address'],size='24')]
        fs={at:[(g.COPY,g.OWNER)]};sy={g.COPY:[(at,'f '+g.OWNER)]};calls={callee:('??0exception@std@@QAE@ABV01@@Z',0x689f82)}
        return bytes(b),pe,fs,sy,anchor,rows,lambda a,n:bytes(native),table,calls
    def run_body(self,fixture):
        b,*args=fixture
        with patch.object(g.core,'linked_body',return_value=b),patch.object(g.core,'validate_body_relocations'):
            return g.qualify(*args)
    def test_all_copy_bytes_and_named_relocations(self):
        proof=self.run_body(self.body_fixture());self.assertEqual(proof['size'],24);self.assertEqual(proof['masked_bytes'],0)
    def test_unknown_callee_or_wrong_vtable_rejected(self):
        for at in (8,14):
            f=list(self.body_fixture());b=bytearray(f[0]);b[at]^=1;f[0]=bytes(b)
            with self.assertRaises(ValueError):self.run_body(f)
    def test_unexpected_function_alias_rejected(self):
        f=list(self.body_fixture());f[2][0x10001000].append(('other',g.OWNER))
        with self.assertRaises(ValueError):self.run_body(f)

class BadExceptionRttiTests(unittest.TestCase):
    def fixture(self):
        source={};target={};pack=lambda x:struct.pack('<'+'I'*len(x),*x)
        def populate(mem,v,col,h,bh,arr,barr,desc,bdesc,td,btd,ti,scalar,what):
            mem[v-4]=pack([col]);mem[v]=pack([scalar,what]);mem[col]=pack([0,0,0,td,h])
            mem[h]=pack([0,0,2,arr]);mem[bh]=pack([0,0,1,barr]);mem[arr]=pack([desc,bdesc]);mem[barr]=pack([bdesc])
            mem[desc]=pack([td,1,0,0xffffffff,0,0x40,h]);mem[bdesc]=pack([btd,0,0,0xffffffff,0,0x40,bh])
            mem[td]=pack([ti,0])+b'.?AVbad_exception@std@@\0';mem[btd]=pack([ti,0])+b'.?AVexception@std@@\0'
        populate(source,0x10008004,0x10008100,0x10008200,0x10008300,0x10008400,0x10008440,0x10008500,0x10008540,0x10008600,0x10008680,0x10003000,0x10001000,0x10002000)
        populate(target,0x6cd9b8,0x6db000,0x6db100,0x6db200,0x6db300,0x6db340,0x6db400,0x6db440,0x6db500,0x6db580,0x6c3333,0x68ef93,0x689ff0)
        sy={g.VTABLE:[(0x10008004,'libcmt:frame.obj')],g.SCALAR:[(0x10001000,'f '+g.OWNER)],g.WHAT:[(0x10002000,'f libcmt:stdexcpt.obj')],'??_7type_info@@6B@':[(0x10003000,'libcmt:typinfo.obj')]}
        return source,target,sy
    def reader(self,mem):
        def read(a,n):
            for at,b in mem.items():
                if at<=a and a+n<=at+len(b):return b[a-at:a-at+n]
            raise ValueError('missing whole RTTI region')
        return read
    def run_fixture(self,s,t,sy):
        with patch.object(g.core,'pe_data',side_effect=lambda pe,a,n:self.reader(s)(a,n)),patch.object(g.core,'primary_type_name',return_value='.?AVtype_info@@'),patch.object(g.core,'validate_body_relocations'):
            return g.rtti_graph(None,None,sy,self.reader(t))
    def change(self,mem,at,offset,value):
        b=bytearray(mem[at]);struct.pack_into('<I',b,offset,value);mem[at]=bytes(b)
    def test_complete_primary_and_base_cycles(self):
        table,records=self.run_fixture(*self.fixture());self.assertEqual(table['target_address'],0x6cd9b8);self.assertTrue(any(x['size']==28 for x in records))
    def test_nonprimary_or_wrong_base_layout_rejected(self):
        for at,off,value in [(0x6db000,4,4),(0x6db100,8,1),(0x6db400,8,4),(0x6db440,20,0)]:
            s,t,sy=self.fixture();self.change(t,at,off,value)
            with self.assertRaises(ValueError):self.run_fixture(s,t,sy)
    def test_wrong_whole_type_name_rejected(self):
        s,t,sy=self.fixture();b=bytearray(t[0x6db500]);b[10]^=1;t[0x6db500]=bytes(b)
        with self.assertRaises(ValueError):self.run_fixture(s,t,sy)
    def test_wrong_virtual_method_rejected(self):
        s,t,sy=self.fixture();self.change(t,0x6cd9b8,0,0x401640)
        with self.assertRaises(ValueError):self.run_fixture(s,t,sy)
    def test_wrong_hierarchy_cycle_rejected(self):
        s,t,sy=self.fixture();self.change(s,0x10008540,24,0x10008200)
        with self.assertRaises(ValueError):self.run_fixture(s,t,sy)

    def test_own_class_cannot_start_a_new_recursive_hierarchy(self):
        s,t,sy=self.fixture();self.change(s,0x10008500,24,0x10008300)
        with self.assertRaises(ValueError):self.run_fixture(s,t,sy)
    def test_same_source_descriptor_requires_consistent_target_identity(self):
        s,t,sy=self.fixture();t[0x6db600]=t[0x6db500];self.change(t,0x6db000,12,0x6db600)
        with self.assertRaises(ValueError):self.run_fixture(s,t,sy)

if __name__=='__main__':unittest.main()
