"""Alice action 214 executes original lookup functions on synthetic data."""
import importlib.util
from pathlib import Path
import sys
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))
spec = importlib.util.spec_from_file_location('alice_lookups', ROOT / 'scripts/audit-alice-fighter-action214-real-lookups.py')
lookup = importlib.util.module_from_spec(spec); spec.loader.exec_module(lookup)


class AliceAction214RealLookupTests(unittest.TestCase):
    def test_original_lookups_matrix(self):
        result = lookup.audit()
        self.assertEqual(result['result'], 'bounded_lookup_paths_agree')
        self.assertEqual(result['cases'], 432)

    def test_wrong_velocity_factor_is_detected(self):
        prefix = lookup.load_prefix(); observer, address, image, _, source, _ = prefix.setup()
        changed = bytearray(source); offset = 0x4eb700 - address
        self.assertEqual(changed[offset:offset+6], bytes.fromhex('d88e3c070000'))
        changed[offset+2] = 0x40
        case = dict(sequence=1, held=1, stop_at_adjust=True, vertical=1, horizontal=1,
                    facing=1, slow=0, angle=0.0, heading=30, speed=4.0)
        with self.assertRaises(ValueError):
            lookup.validate(prefix, observer.execute(image, bytes(changed), case, address), case)


if __name__ == '__main__': unittest.main()
