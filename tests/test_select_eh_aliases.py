import importlib.util
from pathlib import Path
import sys
import unittest
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
sp=importlib.util.spec_from_file_location('select_eh_alias_tests',Path(__file__).resolve().parents[1]/'scripts/audit-select-constructor.py');g=importlib.util.module_from_spec(sp);sp.loader.exec_module(g)
class SelectEhAliasTests(unittest.TestCase):
    def data(self):return {'verified_callback':(0x40ad50,b'body',frozenset({0}),'address')}
    def test_alias_uses_pre_attested_role(self):
        data=self.data();out=g.eh_named_aliases(data,{'actual_source_dtor':'verified_callback'});self.assertEqual(out['actual_source_dtor'],data['verified_callback'])
    def test_original_registry_not_modified(self):
        data=self.data();g.eh_named_aliases(data,{'actual_source_dtor':'verified_callback'});self.assertEqual(set(data),{'verified_callback'})
    def test_unknown_target_rejected(self):
        with self.assertRaises(ValueError):g.eh_named_aliases(self.data(),{'source':'unknown'})
    def test_raw_address_not_an_attested_name(self):
        with self.assertRaises(ValueError):g.eh_named_aliases(self.data(),{'source':'0x0040AD50'})
    def test_unreviewed_alias_chain_rejected(self):
        with self.assertRaises(ValueError):g.eh_named_aliases(self.data(),{'second':'verified_callback','first':'second'})
if __name__=='__main__':unittest.main()
