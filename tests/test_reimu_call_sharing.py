import importlib.util
from pathlib import Path
import unittest

path = Path(__file__).resolve().parents[1] / 'scripts/audit-reimu-call-sharing.py'
spec = importlib.util.spec_from_file_location('reimu_call_sharing_test', path)
sharing = importlib.util.module_from_spec(spec)
spec.loader.exec_module(sharing)


class CompleteCallSharingTests(unittest.TestCase):
    def test_equal_action_counts_do_not_prove_shared_site_ownership(self):
        result = sharing.compare_sites({0x100: {6, 7}, 0x200: {795, 797}},
                                       {0x300: {6, 7, 795, 797}})
        self.assertEqual(result['per_action_count_deltas'], [])
        self.assertFalse(result['partition_equal'])
        self.assertEqual(len(result['partitions']), 3)

    def test_placement_is_distinct_from_action_set_membership(self):
        result = sharing.compare_sites({0x100: {0, 2, 9}}, {0x900: {0, 2, 9}})
        self.assertTrue(result['partition_equal'])
        self.assertNotEqual(result['partitions'][0]['target_sites'],
                            result['partitions'][0]['source_sites'])

    def test_same_membership_at_two_physical_sites_keeps_multiplicity(self):
        result = sharing.compare_sites({0x100: {410, 414}, 0x200: {410, 414}},
                                       {0x300: {410, 414}})
        self.assertFalse(result['partition_equal'])
        self.assertEqual(result['per_action_count_deltas'], [
            {'action': 410, 'target': 2, 'source': 1},
            {'action': 414, 'target': 2, 'source': 1}])

    def test_sites_outside_nondefault_actions_are_not_silently_dropped(self):
        result = sharing.compare_sites({0x100: set(), 0x200: set()}, {0x300: set()})
        self.assertEqual(result['per_action_count_deltas'], [])
        self.assertFalse(result['partition_equal'])
        self.assertEqual(result['partitions'], [
            {'actions': [], 'target_sites': ['0x100', '0x200'], 'source_sites': ['0x300']}])


if __name__ == '__main__':
    unittest.main()
