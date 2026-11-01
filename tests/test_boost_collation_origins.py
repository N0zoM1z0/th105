import copy
import hashlib
from pathlib import Path
import struct
import sys
from types import SimpleNamespace
import unittest
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
import boost_collation_origins as collation

class CollationOriginTests(unittest.TestCase):
    def fixture(self):
        data=bytearray(96);data[32:35]=b'A\0\0';struct.pack_into('<IIH',data,64,0,1,6);struct.pack_into('<IIH',data,74,4,2,6)
        syms={0:SimpleNamespace(name='table',section_number=1,value=0),1:SimpleNamespace(name='literal',section_number=2,value=0),2:SimpleNamespace(name='empty',section_number=2,value=2)}
        sections=[SimpleNamespace(name='.data',raw_size=8,raw_offset=0,reloc_offset=64,reloc_count=2,characteristics=0xc0000040),SimpleNamespace(name='.rdata',raw_size=3,raw_offset=32,reloc_offset=0,reloc_count=0,characteristics=0x40000040)]
        cf=SimpleNamespace(symbols=syms,sections=sections,_read_raw=lambda a,n:bytes(data[a:a+n]))
        raw=struct.pack('<2I',0x403000,0x403010);memory={0x402000:raw,0x403000:b'A\0',0x403010:b'\0'}
        target_data=SimpleNamespace(Name=b'.data\0\0\0',VirtualAddress=0x2000,SizeOfRawData=0x100,Characteristics=0xc0000040)
        target_rdata=SimpleNamespace(Name=b'.rdata\0\0',VirtualAddress=0x3000,SizeOfRawData=0x100,Characteristics=0x40000040)
        pe=SimpleNamespace(OPTIONAL_HEADER=SimpleNamespace(ImageBase=0x400000),get_section_by_rva=lambda r:target_data if 0x2000<=r<0x2100 else target_rdata if 0x3000<=r<0x3100 else None)
        table=dict(symbol='table',address='0x00402000',entries=2,sha256=hashlib.sha256(raw).hexdigest())
        return cf,table,[b'A\0',b'\0'],pe,lambda a,n:memory[a][:n],data,memory,target_rdata
    def test_complete_literal_table(self):
        cf,t,v,pe,read,*_=self.fixture();self.assertEqual(collation.verify_table(cf,t,v,pe,read)['entries'],2)
    def test_all_pointer_cells_required(self):
        cf,t,v,pe,read,data,*_=self.fixture();cf.sections[0].reloc_count=1
        with self.assertRaisesRegex(ValueError,'every pointer'):collation.verify_table(cf,t,v,pe,read)
    def test_source_and_native_literals_are_both_checked(self):
        for source in (True,False):
            cf,t,v,pe,read,data,memory,_=self.fixture()
            if source:data[32]=ord('B')
            else:memory[0x403000]=b'B\0'
            with self.assertRaisesRegex(ValueError,'string cell'):collation.verify_table(cf,t,v,pe,read)
    def test_readonly_string_storage_required(self):
        cf,t,v,pe,read,data,memory,section=self.fixture();section.Characteristics|=0x80000000
        with self.assertRaisesRegex(ValueError,'readonly'):collation.verify_table(cf,t,v,pe,read)
    def test_initializer_requires_one_final_sentinel(self):
        self.assertEqual(collation.source_literals('const char* names[] = {"A", "",};','names'),[b'A\0',b'\0'])
        for text in ['const char* names[]={"A"};','const char* names[]={"", "A", ""};','const char* names[]={arbitrary, ""};']:
            with self.assertRaises(ValueError):collation.source_literals(text,'names')
    def relocation_fixture(self):
        b=bytearray(16);b[0]=0xb8;struct.pack_into('<i',b,1,4);b[5]=0x90;b[6]=0xe8;b[11]=0xc3
        rels=[(1,6,'table'),(7,20,'callee')];expected=[dict(offset=1,kind=6,symbol='table',addend=4),dict(offset=7,kind=20,symbol='callee',addend=0)]
        return bytes(b),rels,expected
    def test_base_plus_four_and_call_are_resolved_not_masked(self):
        b,r,e=self.relocation_fixture();out=collation.canonicalize(b,r,0x4000,{'table':0x7000},{'callee':0x9000},e)
        self.assertEqual(struct.unpack_from('<I',out,1)[0],0x7004);self.assertEqual(struct.unpack_from('<i',out,7)[0],0x9000-(0x4000+11))
    def test_relocation_set_cannot_shrink_or_broaden(self):
        b,r,e=self.relocation_fixture()
        with self.assertRaises(ValueError):collation.canonicalize(b,r,0x4000,{'table':0x7000},{'callee':0x9000},e[:1])
        changed=bytearray(b);struct.pack_into('<i',changed,1,8);e[0]['addend']=8
        with self.assertRaises(ValueError):collation.canonicalize(bytes(changed),r,0x4000,{'table':0x7000},{'callee':0x9000},e)
    def test_cfg_must_be_closed_and_complete(self):
        self.assertEqual(collation.inspect_cfg(b'\xb8\x01\x00\x00\x00\xc3',0x4000,[])['instructions'],2)
        for code in [b'\xeb\x10',b'\xc3\x90',b'\xff\xd0\xc3',b'\x0f']:
            with self.assertRaises(ValueError):collation.inspect_cfg(code,0x4000,[])
