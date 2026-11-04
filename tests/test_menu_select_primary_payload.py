"""The menu payload census never waives missing bytes or changed tables."""
import importlib.util
from pathlib import Path
import sys
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))
def load(name, path):
    spec = importlib.util.spec_from_file_location(name, ROOT / path)
    module = importlib.util.module_from_spec(spec); spec.loader.exec_module(module)
    return module
observer = load('menu_observer', 'scripts/audit-menu-select-cancel-observer.py')
payload = load('menu_payload', 'scripts/audit-menu-select-primary-payload.py')


class MenuSelectPayloadTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.native, cls.source = observer.code_bodies()

    def test_current_payload_retains_all_differences(self):
        result = payload.compare_payload(self.native, self.source)
        self.assertEqual(result['result'], 'nonexact')
        self.assertEqual(result['missing_source_bytes'], 24)
        self.assertEqual(result['masked_bytes'], 0)
        self.assertGreaterEqual(result['unequal_positions_including_missing'], 24)

    def test_equal_fixture_and_changed_table(self):
        self.assertEqual(payload.compare_payload(self.native, self.native)['result'], 'payload_equal')
        changed = bytearray(self.native); changed[-1] ^= 1
        with self.assertRaises(ValueError): payload.compare_payload(bytes(changed), self.source)


if __name__ == '__main__': unittest.main()
