import copy
from pathlib import Path
import sys
import tomllib
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'scripts'))
import linked_package_map_tidy_origins as g
from workflow_manifest import load_manifest


class PackageMapTidyContractTests(unittest.TestCase):
    def setUp(self):
        self.spec = tomllib.loads(g.ANCHORS.read_text())
        self.unit = load_manifest()['units'][g.UNIT]
        self.rows = [dict(address='0x0041C8D0', size='56')]
        self.sha = self.spec['target_sha256']

    def test_valid_contract(self):
        self.assertEqual(g.validate_spec(self.spec, self.rows, self.unit, self.sha)['address'], '0x0041C8D0')

    def test_wrong_target_or_selected_extent_rejected(self):
        for rows, sha in [(self.rows, '0' * 64), (self.rows * 2, self.sha),
                          ([dict(address='0x0041C8D0', size='55')], self.sha)]:
            with self.assertRaises(ValueError):
                g.validate_spec(self.spec, rows, self.unit, sha)

    def test_anchor_corruption_rejected(self):
        for key, value in [('size', 55), ('symbol', 'invented'), ('sha256', '0' * 64)]:
            spec = copy.deepcopy(self.spec)
            spec['anchors'][0][key] = value
            with self.assertRaises(ValueError):
                g.validate_spec(spec, self.rows, self.unit, self.sha)

    def test_wrong_build_context_rejected(self):
        for key, value in [('source', 'src/ui/MenuResult.cpp'), ('enable_gs', False), ('link_runtime', 'import')]:
            unit = copy.deepcopy(self.unit)
            unit[key] = value
            with self.assertRaises(ValueError):
                g.validate_spec(self.spec, self.rows, unit, self.sha)

    def test_source_closure_and_symbol_ownership_rejected(self):
        spec = copy.deepcopy(self.spec)
        spec['source_pins'].pop(next(iter(spec['source_pins'])))
        with self.assertRaises(ValueError):
            g.validate_spec(spec, self.rows, self.unit, self.sha)
        with self.assertRaises(ValueError):
            g.one({1: [('tree', 'other')]}, lambda n: n == 'tree', 'expected', 'test')
        with self.assertRaises(ValueError):
            g.one({1: [('tree', 'expected')], 2: [('tree', 'expected')]}, lambda n: n == 'tree', 'expected', 'test')


if __name__ == '__main__':
    unittest.main()
