import copy
import importlib.util
from pathlib import Path
import unittest

path = Path(__file__).resolve().parents[1] / 'scripts/audit-reimu-root-relocations.py'
spec = importlib.util.spec_from_file_location('reimu_root_bindings', path)
audit = importlib.util.module_from_spec(spec)
spec.loader.exec_module(audit)


class RootProbeBindingsTests(unittest.TestCase):
    def setUp(self):
        self.bindings = audit.load_bindings(audit.DEFAULT_BINDINGS)

    def test_manifest_separates_root_values_and_external_pool_anchor(self):
        self.assertEqual(len(self.bindings['root_literals']), 160)
        self.assertNotIn('41f0000000000000', self.bindings['root_literals'])
        self.assertEqual(self.bindings['pool_literals']['41f0000000000000'], '0x006D6ED0')
        self.assertEqual(len(self.bindings['rel32']), 36)

    def test_bounded_receiver_and_argument_views_use_existing_entries(self):
        calls = self.bindings['rel32']
        self.assertEqual(calls['?selector_random_range@th105@@YGHHH@Z'], '0x004351A0')
        self.assertEqual(calls['?selector_random_range@ReimuRandomReceiverView@th105@@QAEHHH@Z'],
                         '0x004351A0')
        prefix = '?spawn_owned_object_via_manager@ReimuActionStatePreludeView@th105@@'
        for suffix in ('QAEHHMMHHHH@Z', 'QAEHHMMHHPBMH@Z',
                       'QAEHHMMEHHH@Z', 'QAEHHMMEHPBMH@Z'):
            self.assertEqual(calls[prefix+suffix], '0x00465190')
        self.assertEqual(len({int(address, 0) for address in calls.values()}), 32)

    def test_acceptance_scope_cannot_be_enabled(self):
        changed = copy.deepcopy(self.bindings)
        changed['purpose'] = 'accepted'
        with self.assertRaises(ValueError):
            audit.validate_bindings(changed)

    def test_one_value_cannot_have_conflicting_ownership(self):
        changed = copy.deepcopy(self.bindings)
        changed['pool_literals']['00000000'] = changed['root_literals']['00000000']
        with self.assertRaises(ValueError):
            audit.validate_bindings(changed)

    def test_numeric_width_is_not_guessed(self):
        changed = copy.deepcopy(self.bindings)
        changed['pool_literals']['000000'] = '0x006D6ED0'
        with self.assertRaises(ValueError):
            audit.validate_bindings(changed)


if __name__ == '__main__':
    unittest.main()
