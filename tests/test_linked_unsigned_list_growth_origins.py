import copy
from pathlib import Path
import sys
import tomllib
import unittest
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
import linked_unsigned_list_growth_origins as g
from workflow_manifest import load_manifest

class UnsignedListGrowthTests(unittest.TestCase):
    def setUp(self):
        self.spec=tomllib.loads(g.ANCHORS.read_text())
        self.unit=load_manifest()['units'][g.UNIT]
        self.selected=[dict(address='0x00402700',size='165')]
        self.sha=self.spec['target_sha256']
    def check(self,spec=None,unit=None,selected=None,sha=None):
        return g.validate_spec(spec or self.spec,selected or self.selected,unit or self.unit,sha or self.sha)
    def test_valid(self):
        self.assertEqual(self.check()['address'],'0x00402700')
    def test_target_and_extent_rejected(self):
        with self.assertRaises(ValueError):self.check(sha='0'*64)
        with self.assertRaises(ValueError):self.check(selected=[dict(address='0x00402700',size='164')])
    def test_wrong_symbol_and_hash_rejected(self):
        for k,v in [('symbol','wrong'),('sha256','0'*64),('size',164)]:
            s=copy.deepcopy(self.spec);s['anchors'][0][k]=v
            with self.assertRaises(ValueError):self.check(spec=s)
    def test_unit_settings_rejected(self):
        for k,v in [('source','src/ui/SceneRenderClusterRuntime.cpp'),('enable_gs',False),('link_runtime','import'),('link_xiph_sdk',False)]:
            u=copy.deepcopy(self.unit);u[k]=v
            with self.assertRaises(ValueError):self.check(unit=u)
    def test_source_closure_rejected(self):
        s=copy.deepcopy(self.spec);s['source_pins'].pop(next(iter(s['source_pins'])))
        with self.assertRaises(ValueError):self.check(spec=s)

if __name__=='__main__':unittest.main()
