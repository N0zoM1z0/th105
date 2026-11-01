import copy
import hashlib
from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import patch
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
import implicit_lifetime_origins as implicit

class ImplicitLifetimeTests(unittest.TestCase):
    def fixture(self):
        source=b'reviewed synthetic declaration, not native bytes'
        a=dict(address='0x00401100',size=55,sha256='a'*64,unit='owner',symbol_base='Alias_dtor',emitted_symbol='??1Fixture@@UAE@XZ',kind='destructor')
        spec=dict(schema_version=1,target_sha256='b'*64,compiler_sha256=implicit.COMPILER,sources=[dict(path='src/fixture.cpp',sha256=hashlib.sha256(source).hexdigest())],anchors=[a])
        rows=[dict(address=a['address'],size='55')]
        units={'owner':dict(kind='probe',profile='vc8-sp1-probe-o2',source='src/fixture.cpp',functions=[dict(address='0x401100',symbol_base='Alias_dtor')])}
        return spec,rows,units,source
    def check(self,s,r,u,source):
        with tempfile.TemporaryDirectory()as tmp:
            p=Path(tmp)/'source';p.write_bytes(source)
            with patch.object(implicit,'repository_path',return_value=p):return implicit.validate_spec(s,r,r,u,'b'*64)
    def test_complete_short_member_not_mask_threshold(self):
        s,r,u,b=self.fixture();self.assertEqual(list(self.check(s,r,u,b)),['owner'])
    def test_reviewed_source_cannot_change(self):
        s,r,u,b=self.fixture()
        with self.assertRaisesRegex(ValueError,'declaration changed'):self.check(s,r,u,b+b' changed')
    def test_wrong_member_kind(self):
        s,r,u,b=self.fixture();s['anchors'][0]['emitted_symbol']='??_GFixture@@UAEPAXI@Z'
        with self.assertRaises(ValueError):self.check(s,r,u,b)
    def test_copy_member_contract(self):
        s,r,u,b=self.fixture();s['anchors'][0].update(kind='copy_constructor',emitted_symbol='??0Fixture@@QAE@ABV0@@Z');self.assertTrue(self.check(s,r,u,b))
    def test_selection_and_extent(self):
        for change in [lambda s:s['anchors'].append(copy.deepcopy(s['anchors'][0])),lambda s:s['anchors'][0].update(size=54),lambda s:s.update(target_sha256='c'*64),lambda s:s.update(compiler_sha256='c'*64)]:
            s,r,u,b=self.fixture();change(s)
            with self.assertRaises(ValueError):self.check(s,r,u,b)
    def test_owner_source_and_selector(self):
        for change in [lambda u:u['owner'].update(kind='linked_candidate'),lambda u:u['owner'].update(source='src/other.cpp'),lambda u:u['owner']['functions'][0].update(symbol_base='wrong')]:
            s,r,u,b=self.fixture();change(u)
            with self.assertRaises(ValueError):self.check(s,r,u,b)
    def test_duplicate_review_sources(self):
        s,r,u,b=self.fixture();s['sources'].append(copy.deepcopy(s['sources'][0]))
        with self.assertRaises(ValueError):self.check(s,r,u,b)
