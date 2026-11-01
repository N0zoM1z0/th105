import copy
import inspect
from pathlib import Path
import struct
import sys
import tomllib
import unittest
from unittest.mock import patch
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
import linked_network_tree_erase_origins as g

class TreeEraseScopeTests(unittest.TestCase):
    def fixture(self):
        s=tomllib.loads(g.ANCHORS.read_text());return s,[dict(address='0x00414110',size='714')],g.load_manifest()['units'][g.UNIT]
    def test_actual_existing_owner_scope(self):
        s,r,u=self.fixture();self.assertEqual(g.validate_spec(s,r,u,s['target_sha256'])['size'],714)
    def test_partial_mask_or_wrong_payload_rejected(self):
        for k,v in [('size',713),('mask',[3]),('symbol','?erase@Other')]:
            s,r,u=self.fixture();s['anchors'][0][k]=v
            with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_self_consistent_unreviewed_symbol_rejected(self):
        s,r,u=self.fixture();s['anchors'][0]['symbol']+='x';s['anchors'][0]['symbol_sha256']=g.digest(s['anchors'][0]['symbol'].encode())
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_import_runtime_or_extra_library_barrier_rejected(self):
        for k,v in [('link_runtime','import'),('linked_coff_sources',['src/library/UnsignedIntList.cpp']),('enable_gs',False),('preserve_public_members',[])]:
            s,r,u=self.fixture();u=copy.deepcopy(u);u[k]=v
            with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_source_pins_cover_original_library_tus(self):
        s,r,u=self.fixture();self.assertIn('src/library/UnsignedIntList.cpp',s['source_pins']);self.assertIn('src/library/UnsignedIntVector.cpp',s['source_pins'])
        s['source_pins'].pop('src/library/UnsignedIntList.cpp')
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_logic_qualifier_default_owner_is_preserved(self):
        self.assertEqual(inspect.signature(g.logic.qualify).parameters['owner'].default,'original-0.obj')

class TreeThrowMetadataTests(unittest.TestCase):
    def fixture(self):
        source={};target={};symbols={};owner='owner.obj';pack=lambda xs:struct.pack('<'+'I'*len(xs),*xs)
        si=0x10001000;sa=0x10001040;ta=0x6e6000;dtor=0x10002000;tv=0x10003000
        symbols[g.THROW_INFO]=[(si,owner)];symbols[g.OUT_DTOR]=[(dtor,'f i '+owner)];symbols['??_7type_info@@6B@']=[(tv,'libcmt:typinfo.obj')]
        source[si]=pack([0,dtor,0,sa]);target[0x6e3ba4]=pack([0,0x401740,0,ta])
        sc=[0x10001100+i*0x40 for i in range(3)];tc=[0x6e6100+i*0x40 for i in range(3)]
        source[sa]=pack([3]+sc);target[ta]=pack([3]+tc)
        defs=[('.?AVout_of_range@std@@',40,g.OUT_COPY,0x401780,'i '+owner),('.?AVlogic_error@std@@',40,g.logic.COPY,0x4017a0,'i '+owner),('.?AVexception@std@@',12,'??0exception@std@@QAE@ABV01@@Z',0x689f82,'libcmt:stdexcpt.obj')]
        for i,(name,size,n,cp,ow)in enumerate(defs):
            sd=0x10004000+i*0x80;td=0x6e7000+i*0x80;sp=0x10005000+i*0x100
            symbols[n]=[(sp,'f '+ow)];lit=name.encode()+b'\0'
            source[sc[i]]=pack([0,sd,0,0xffffffff,0,size,sp]);target[tc[i]]=pack([0,td,0,0xffffffff,0,size,cp])
            source[sd]=pack([tv,0])+lit;target[td]=pack([0x6c3333,0])+lit
        return source,target,symbols,owner
    def reader(self,segments):
        def read(a,n):
            for at,b in segments.items():
                if at<=a and a+n<=at+len(b):return b[a-at:a-at+n]
            raise ValueError('missing whole fixture region')
        return read
    def run_fixture(self,s,t,sy,o):
        with patch.object(g.core,'pe_data',side_effect=lambda pe,a,n:self.reader(s)(a,n)),patch.object(g.core,'primary_type_name',return_value='.?AVtype_info@@'),patch.object(g.core,'validate_body_relocations'):
            return g.throw_metadata(None,None,sy,o,self.reader(t))
    def mutate(self,segments,at,offset,value):
        b=bytearray(segments[at]);struct.pack_into('<I',b,offset,value);segments[at]=bytes(b)
    def test_complete_three_type_metadata(self):
        s,t,sy,o=self.fixture();at,result=self.run_fixture(s,t,sy,o);self.assertEqual(at,0x10001000);self.assertEqual([x['size']for x in result['types']],[40,40,12])
    def test_wrong_flags_size_or_copy_is_rejected(self):
        for offset,value in [(0,1),(8,4),(12,0),(20,12),(24,0x4017a0)]:
            s,t,sy,o=self.fixture();self.mutate(t,0x6e6100,offset,value)
            with self.assertRaises(ValueError):self.run_fixture(s,t,sy,o)
    def test_incomplete_catchable_set_is_rejected(self):
        s,t,sy,o=self.fixture();self.mutate(t,0x6e6000,0,2)
        with self.assertRaises(ValueError):self.run_fixture(s,t,sy,o)
    def test_wrong_throw_destructor_is_rejected(self):
        s,t,sy,o=self.fixture();self.mutate(t,0x6e3ba4,4,0x401630)
        with self.assertRaises(ValueError):self.run_fixture(s,t,sy,o)
    def test_entire_type_name_is_checked(self):
        s,t,sy,o=self.fixture();b=bytearray(t[0x6e7000]);b[-2]^=1;t[0x6e7000]=bytes(b)
        with self.assertRaises(ValueError):self.run_fixture(s,t,sy,o)
    def test_copy_must_have_actual_cil_owner(self):
        s,t,sy,o=self.fixture();sy[g.OUT_COPY]=[(sy[g.OUT_COPY][0][0],'f other.obj')]
        with self.assertRaises(ValueError):self.run_fixture(s,t,sy,o)

if __name__=='__main__':unittest.main()
