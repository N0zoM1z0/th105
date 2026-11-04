import copy
import sys
from pathlib import Path
import unittest
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'scripts'))
import boost_recursion_cleanup_origins as m

class RecursionCleanupOriginTests(unittest.TestCase):
    def setUp(self):
        self.sha = '56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e'
        self.spec = dict(schema_version=1, target_sha256=self.sha, unit=m.UNIT,
                         anchors=[dict(address=m.ADDRESS, size=8, sha256=m.HASH)])
        self.rows = [dict(address=m.ADDRESS, size='8')]
    def test_contract(self):
        self.assertEqual(m.validate_spec(self.spec, self.rows, self.sha)['address'], m.ADDRESS)
    def test_target_rejected(self):
        with self.assertRaises(ValueError): m.validate_spec(self.spec, self.rows, '0' * 64)
    def test_size_address_and_hash_rejected(self):
        for key, value in [('size', 7), ('address', '0x00443021'), ('sha256', '0' * 64)]:
            spec = copy.deepcopy(self.spec); spec['anchors'][0][key] = value
            with self.assertRaises(ValueError): m.validate_spec(spec, self.rows, self.sha)
    def test_extra_anchor_and_schema_rejected(self):
        spec = copy.deepcopy(self.spec); spec['anchors'].append(spec['anchors'][0])
        with self.assertRaises(ValueError): m.validate_spec(spec, self.rows, self.sha)
        spec = copy.deepcopy(self.spec); spec['extra'] = True
        with self.assertRaises(ValueError): m.validate_spec(spec, self.rows, self.sha)
    def test_youmu_deque_origin_count_and_extent(self):
        import csv
        import tomllib
        root = Path(__file__).resolve().parents[1]
        rules = tomllib.loads((root / 'config/function-origin-rules.toml').read_text())['rules']
        rule = next(x for x in rules if x['id'] == 'vc8-generated-youmu-record-deque-comdats-106a')
        anchors = tomllib.loads((root / rule['vc8_generated_anchor_file']).read_text())['anchors']
        with (root / 'config/functions.csv').open(newline='') as stream:
            rows = {x['address']: x for x in csv.DictReader(stream)}
        self.assertEqual(len(anchors), rule['expected_count'])
        self.assertEqual(sum(int(rows[x['address']]['size'], 0) for x in anchors), rule['expected_bytes'])
    def test_selection_rejected(self):
        with self.assertRaises(ValueError): m.validate_spec(self.spec, [], self.sha)
        with self.assertRaises(ValueError): m.validate_spec(self.spec, [dict(address=m.ADDRESS, size='9')], self.sha)
if __name__ == '__main__': unittest.main()
