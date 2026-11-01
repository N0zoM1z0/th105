import copy
from pathlib import Path
import struct
import sys
import tempfile
import tomllib
from types import SimpleNamespace
import unittest
from unittest.mock import patch
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
import boost_public_exception_copies as g
from coff_exception_rtti import RttiGraph

class PublicExceptionTests(unittest.TestCase):
    def fixture(self):
        s=tomllib.loads(g.ANCHORS.read_text());r=[dict(address=a['address'],size='46')for a in s['anchors']]
        return s,r,g.load_manifest()['units'][g.UNIT]
    def test_original_public_template_unit(self):
        s,r,u=self.fixture();self.assertEqual(len(g.validate_spec(s,r,u,s['target_sha256'])),2)
    def test_wrong_type_mask_or_partial_extent_rejected(self):
        for k,v in [('size',45),('mask',[9]),('symbol','wrong')]:
            s,r,u=self.fixture();s['anchors'][0][k]=v
            with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_different_profile_or_unverified_headers_rejected(self):
        for k,v in [('profile','vc8-sp1-probe-o2-ob1'),('enable_gs',False),('boost_regex_headers',False)]:
            s,r,u=self.fixture();u=copy.deepcopy(u);u[k]=v
            with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_forged_formal_binding_rejected(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u['functions'][0]['rel32_targets']=[]
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_probe_requires_original_headers_flag(self):
        with self.assertRaises(ValueError):g.upstream.validate(dict(source=g.upstream.EXCEPTION_PROBE,boost_regex_headers=False))
    def probe_root(self,raw):
        td=tempfile.TemporaryDirectory();root=Path(td.name);p=root/g.upstream.EXCEPTION_PROBE;p.parent.mkdir(parents=True);p.write_bytes(raw);return td,root
    def test_original_declaration_accepts_git_newline_forms(self):
        raw=(g.ROOT/g.upstream.EXCEPTION_PROBE).read_bytes().replace(b'\r\n',b'\n')
        for data in [raw,raw.replace(b'\n',b'\r\n')]:
            td,root=self.probe_root(data)
            with td:self.assertEqual(g.upstream.verified_exception_instantiations(root),root/g.upstream.EXCEPTION_PROBE)
    def test_missing_original_noreturn_or_added_wrapper_rejected(self):
        raw=(g.ROOT/g.upstream.EXCEPTION_PROBE).read_bytes()
        for data in [raw.replace(b'BOOST_ATTRIBUTE_NORETURN ',b''),raw+b'\nvoid invented() {}\n']:
            td,root=self.probe_root(data)
            with td:
                with self.assertRaises(ValueError):g.upstream.verified_exception_instantiations(root)

class GraphTests(unittest.TestCase):
    def fixture(self):
        pack=lambda x:struct.pack('<'+'I'*len(x),*x);typename='.?AVexception@std@@'
        source={'V':(-4,b'\0'*4),'C':(0,pack([0,0,0,0,0])),'H':(0,pack([0,0,1,0])),'A':(0,b'\0'*4),
                'D':(0,pack([0,0,0,0xffffffff,0,0x40,0])),'T':(0,b'\0'*8+typename.encode()+b'\0')}
        refs={'V':[(-4,'C')],'C':[(12,'T'),(16,'H')],'H':[(12,'A')],'A':[(0,'D')],'D':[(0,'T'),(24,'H')],'T':[(0,'??_7type_info@@6B@')]}
        sections={n:SimpleNamespace(name='.data'if n=='T'else'.rdata$r'if n!='V'else'.rdata',characteristics=0x40000040)for n in source}
        class Fake:
            def raw(self,n,size,offset=0):
                at,b=source[n];return b[offset-at:offset-at+size]
            def refs(self,n,size,offset=0):return [(at-offset,6,to)for at,to in refs[n]if offset<=at<offset+size]
            def pointer(self,n,offset):return next(to for at,to in refs[n]if at==offset)
            def typename(self,n):return source[n][1][8:]
            def section(self,n):return sections[n]
        target={0x500000:pack([0x500100]),0x500100:pack([0,0,0,0x500500,0x500200]),0x500200:pack([0,0,1,0x500300]),
                0x500300:pack([0x500400]),0x500400:pack([0x500500,0,0,0xffffffff,0,0x40,0x500200]),0x500500:pack([0x600000,0])+typename.encode()+b'\0'}
        def read(a,n):
            for at,b in target.items():
                if at<=a and a+n<=at+len(b):return b[a-at:a-at+n]
            raise ValueError('missing whole metadata')
        return Fake(),read,typename,source,target,refs,sections
    def run_fixture(self,f):
        reader,read,name,*_=f;graph=RttiGraph(reader,None,read,{name})
        with patch.object(g.core,'readonly_data',side_effect=lambda pe,a,n:read(a,n)),patch.object(g.core,'primary_type_name',return_value='.?AVtype_info@@'):
            graph.table('V',0x500004,0,name)
        return graph
    def test_whole_hierarchy_and_symbol_identity(self):
        graph=self.run_fixture(self.fixture());self.assertEqual(graph.bindings['H'],0x500200);self.assertEqual(graph.tables[0]['offset'],0)
    def test_wrong_subobject_or_base_adjustment_rejected(self):
        for address,off in [(0x500100,4),(0x500400,8)]:
            f=self.fixture();b=bytearray(f[4][address]);b[off]^=1;f[4][address]=bytes(b)
            with self.assertRaises(ValueError):self.run_fixture(f)
    def test_writable_rtti_is_not_readonly(self):
        f=self.fixture();f[6]['H'].characteristics|=0x80000000
        with self.assertRaises(ValueError):self.run_fixture(f)
    def test_entire_name_is_checked(self):
        f=self.fixture();b=bytearray(f[4][0x500500]);b[-2]^=1;f[4][0x500500]=bytes(b)
        with self.assertRaises(ValueError):self.run_fixture(f)
    def test_own_class_cycle_cannot_change_hierarchy(self):
        f=self.fixture();f[5]['D'][1]=(24,'wrong')
        with self.assertRaises(ValueError):self.run_fixture(f)
    def test_source_symbol_cannot_map_to_two_targets(self):
        f=self.fixture();reader,read,name,*_=f;graph=RttiGraph(reader,None,read,{name});graph.bind('T',0x500500)
        with self.assertRaises(ValueError):graph.bind('T',0x500600)

if __name__=='__main__':unittest.main()
