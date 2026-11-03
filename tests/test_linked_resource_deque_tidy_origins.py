import copy
import sys
from pathlib import Path
import tomllib
import unittest
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'scripts'))
import linked_resource_deque_tidy_origins as g
from workflow_manifest import load_manifest

class ResourceDequeTidyContractTests(unittest.TestCase):
    def setUp(self):
        self.spec = tomllib.loads(g.ANCHORS.read_text())
        self.unit = load_manifest()['units'][g.UNIT]
        self.rows = [dict(address='0x00413E10', size='102')]
        self.sha = self.spec['target_sha256']

    def test_valid_contract(self):
        self.assertEqual(g.validate_spec(self.spec,self.rows,self.unit,self.sha)['address'],'0x00413E10')

    def test_wrong_target_or_extra_body_rejected(self):
        with self.assertRaises(ValueError):
            g.validate_spec(self.spec,self.rows,self.unit,'0'*64)
        with self.assertRaises(ValueError):
            g.validate_spec(self.spec,self.rows*2,self.unit,self.sha)

    def test_wrong_extent_and_symbol_rejected(self):
        for key,value in [('size',101),('symbol','invented'),('sha256','0'*64)]:
            bad = copy.deepcopy(self.spec)
            bad['anchors'][0][key] = value
            with self.assertRaises(ValueError):
                g.validate_spec(bad,self.rows,self.unit,self.sha)

    def test_wrong_owner_context_rejected(self):
        for key,value in [('source','src/ui/SceneRenderClusterRuntime.cpp'),('enable_gs',False),('link_runtime','import')]:
            bad = copy.deepcopy(self.unit)
            bad[key] = value
            with self.assertRaises(ValueError):
                g.validate_spec(self.spec,self.rows,bad,self.sha)

    def test_incomplete_source_closure_rejected(self):
        bad = copy.deepcopy(self.spec)
        bad['source_pins'].pop(next(iter(bad['source_pins'])))
        with self.assertRaises(ValueError):
            g.validate_spec(bad,self.rows,self.unit,self.sha)

if __name__ == '__main__':
    unittest.main()
