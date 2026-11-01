import copy
from pathlib import Path
import sys
import tomllib
import unittest
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
import boost_default_syntax_origins as g
class DefaultSyntaxTests(unittest.TestCase):
    def fixture(self):
        s=tomllib.loads(g.ANCHORS.read_text());return s,[dict(address='0x006B45D0',size='548')],g.errors.load_manifest()['units']
    def test_whole_original_source_and_all_literals(self):
        s,r,u=self.fixture();a,l,unit=g.validate_spec(s,r,u,s['target_sha256']);self.assertEqual(a['size'],548);self.assertEqual(len(l),50)
    def test_shortened_or_masked_body_rejected(self):
        for k,v in [('size',547),('mask',[10]),('symbol',g.SYMBOL.replace('YI','YA'))]:
            s,r,u=self.fixture();s['anchors'][0][k]=v
            with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_original_source_required(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT]['source']='scripts/probes/Replacement.cpp'
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_all_literal_roles_required(self):
        s,r,u=self.fixture();s['literals'].pop()
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_duplicate_field_or_symbol_rejected(self):
        for key in ['field','symbol']:
            s,r,u=self.fixture();s['literals'][1][key]=s['literals'][0][key]
            with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_isolated_literal_keys_required(self):
        s,r,u=self.fixture();s['literals'][0]['key']=s['literals'][0]['symbol']
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_reordered_literal_roles_rejected(self):
        s,r,u=self.fixture();s['literals'].reverse()
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_formal_prefix_or_missing_bindings_rejected(self):
        for key,value in [('size',547),('dir32_targets',[])]:
            s,r,u=self.fixture();u=copy.deepcopy(u);f=next(f for f in u[g.UNIT]['functions']if f['address']=='0x006B45D0');f[key]=value
            with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_error_getter_contract_cannot_be_removed(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT]['functions']=[f for f in u[g.UNIT]['functions']if f['address']!='0x006B4800']
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
if __name__=='__main__':unittest.main()
