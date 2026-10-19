import importlib.util
from pathlib import Path
from types import SimpleNamespace
import unittest

path = Path(__file__).resolve().parents[1] / 'scripts/audit-reimu-call-sharing.py'
spec = importlib.util.spec_from_file_location('reimu_call_sharing_test', path)
sharing = importlib.util.module_from_spec(spec)
spec.loader.exec_module(sharing)


class CompleteCallSharingTests(unittest.TestCase):
    def virtual_graph(self, slots):
        row = SimpleNamespace(address=0x100, mnemonic='call',
                              operands=[SimpleNamespace(type=sharing.x.X86_OP_REG)])
        return SimpleNamespace(rows=[row], reachable={0x100}, virtual_definitions=slots)

    def test_mixed_slots_remain_one_physical_call_and_empty_sites_survive(self):
        graph = self.virtual_graph({0x100: {0x10: 8, 0x20: 12}})
        graph.rows.append(SimpleNamespace(address=0x200, mnemonic='call',
                                         operands=[SimpleNamespace(type=sharing.x.X86_OP_REG)]))
        graph.reachable.add(0x200)
        graph.virtual_definitions[0x200] = {0x30: 20}
        graph.reachable_from = lambda start: {0x100}
        _, _, slots = sharing.collect_sites(graph, {416: 0x100, 522: 0x100})
        self.assertEqual(slots, {(8, 12): {0x100: {416, 522}}, (20,): {0x200: set()}})

    def test_missing_indirect_definition_fails_closed(self):
        with self.assertRaisesRegex(ValueError, 'definitions disagree'):
            sharing.virtual_slot_candidates(self.virtual_graph({}))

    def test_spurious_definition_cannot_add_a_phantom_call(self):
        with self.assertRaisesRegex(ValueError, 'definitions disagree'):
            sharing.virtual_slot_candidates(self.virtual_graph({0x100: {0x10: 8}, 0x200: {0x20: 12}}))

    def test_unreviewed_slot_is_not_normalized_to_a_known_method(self):
        with self.assertRaisesRegex(ValueError, 'unreviewed indirect slot'):
            sharing.virtual_slot_candidates(self.virtual_graph({0x100: {0x10: 16}}))

    def test_slot_uncertainty_change_does_not_imply_an_extra_call(self):
        target = {(8, 12): {0x100: {416}}}
        source = {(12,): {0x200: {416}}}
        result = sharing.compare_sites(sharing.merge_slot_sites(target), sharing.merge_slot_sites(source))
        self.assertTrue(result['partition_equal'])
        self.assertEqual(result['per_action_count_deltas'], [])

    def test_one_physical_call_cannot_be_counted_under_two_identities(self):
        with self.assertRaisesRegex(ValueError, 'multiple slot identities'):
            sharing.merge_slot_sites({(8,): {0x100: {416}}, (12,): {0x100: {416}}})

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

    def census(self, target, source):
        return {
            'schema': 'th105-reimu-call-sharing-v1', 'target_sha256': 'attested-target',
            'object_sha256': 'test-object', 'nondefault_actions': 2,
            'entries': [{'action': 300}, {'action': 320}],
            'calls': [{'callee': '0x4351c0', **sharing.compare_sites(target, source)}],
            'slot_calls': [], 'returns': sharing.compare_sites({}, {}),
            'indirect_calls': sharing.compare_sites({}, {}),
        }

    def test_group_improvement_cannot_hide_a_new_action_count_regression(self):
        # Actual runtime-interface control shape: one merged site becomes
        # one300 site and two mutually exclusive320 sites, rather than one each.
        target = {0x100: {300}, 0x200: {320}}
        previous = self.census(target, {0x300: {300, 320}})
        candidate = self.census(target, {0x400: {300}, 0x500: {320}, 0x600: {320}})
        result = sharing.constraint_preservation(previous, candidate)
        self.assertEqual(result['lost_group_checks'], [])
        self.assertEqual(len(result['new_equal_group_checks']), 1)
        self.assertEqual(result['lost_count_checks'], [{
            'domain': 'callee:0x4351c0', 'kind': 'action_sites', 'action': 320,
            'target': 1, 'previous': 1, 'candidate': 2}])
        self.assertFalse(result['preserves_existing_checks'])

    def test_restoring_two_independent_sites_preserves_previous_action_counts(self):
        target = {0x100: {300}, 0x200: {320}}
        previous = self.census(target, {0x300: {300, 320}})
        candidate = self.census(target, {0x400: {300}, 0x500: {320}})
        result = sharing.constraint_preservation(previous, candidate)
        self.assertTrue(result['preserves_existing_checks'])
        self.assertEqual(len(result['new_equal_group_checks']), 2)
        self.assertEqual(result['new_equal_count_checks'], [{
            'domain': 'callee:0x4351c0', 'kind': 'physical_sites', 'action': None,
            'target': 2, 'previous': 1, 'candidate': 2}])

    def test_extra_unreached_site_regresses_total_even_when_every_action_count_agrees(self):
        target = {0x100: {300, 320}}
        previous = self.census(target, {0x200: {300, 320}})
        candidate = self.census(target, {0x200: {300, 320}, 0x300: set()})
        result = sharing.constraint_preservation(previous, candidate)
        self.assertEqual(result['lost_group_checks'], [])
        self.assertEqual(result['lost_count_checks'][0]['kind'], 'physical_sites')
        self.assertFalse(result['preserves_existing_checks'])

    def test_preservation_rejects_changed_target_identity_or_site_inventory(self):
        previous = self.census({0x100: {300}}, {0x200: {300}})
        changed = self.census({0x100: {300}}, {0x200: {300}})
        changed['target_sha256'] = 'another-target'
        with self.assertRaisesRegex(ValueError, 'target evidence changed'):
            sharing.constraint_preservation(previous, changed)
        with self.assertRaisesRegex(ValueError, 'target evidence changed'):
            sharing.constraint_preservation(previous, self.census({0x101: {300}}, {0x200: {300}}))


if __name__ == '__main__':
    unittest.main()
