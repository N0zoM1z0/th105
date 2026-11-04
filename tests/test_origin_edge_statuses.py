"""Keep provenance edge status assertions aligned with the function ledger."""
import csv
from pathlib import Path
import tomllib
import unittest

ROOT = Path(__file__).resolve().parents[1]

def mismatches(rules, rows):
    errors = []
    for rule in rules:
        for edge in rule.get('required_direct_edges', []):
            if 'caller_status' not in edge:
                continue
            address = edge['caller'].upper()
            actual = rows.get(address, {}).get('status')
            if actual != edge['caller_status']:
                errors.append((rule['id'], address, edge['caller_status'], actual))
        for edge in rule.get('required_selected_body_calls', []):
            address = edge['target'].upper()
            expected = edge.get('target_status', 'matching')
            actual = rows.get(address, {}).get('status')
            if actual != expected:
                errors.append((rule['id'], address, expected, actual))
    return errors

class OriginEdgeStatusTests(unittest.TestCase):
    def test_current_edge_statuses(self):
        rules = tomllib.loads((ROOT / 'config/function-origin-rules.toml').read_text())['rules']
        with (ROOT / 'config/functions.csv').open(newline='') as stream:
            rows = {row['address'].upper(): row for row in csv.DictReader(stream)}
        self.assertEqual(mismatches(rules, rows), [])
    def test_source_present_names_have_implemented_status(self):
        with (ROOT / 'config/implemented.csv').open(newline='') as stream:
            implemented = {row[0] for row in csv.reader(stream) if row}
        with (ROOT / 'config/functions.csv').open(newline='') as stream:
            rows = list(csv.DictReader(stream))
        stale = [(row['address'], row['proposed_name'], row['status']) for row in rows
                 if row['proposed_name'] in implemented
                 and row['status'] not in ('implemented', 'matching')]
        self.assertEqual(stale, [])
    def test_mismatched_caller_is_rejected(self):
        rules = [dict(id='caller', required_direct_edges=[dict(caller='0x10', caller_status='matching')])]
        self.assertEqual(len(mismatches(rules, {'0X10': dict(status='identified')})), 1)
    def test_missing_or_stale_body_target_is_rejected(self):
        rules = [dict(id='target', required_selected_body_calls=[dict(target='0x20')])]
        self.assertEqual(len(mismatches(rules, {})), 1)
        self.assertEqual(len(mismatches(rules, {'0X20': dict(status='implemented')})), 1)
        self.assertEqual(mismatches(rules, {'0X20': dict(status='matching')}), [])
if __name__ == '__main__': unittest.main()
