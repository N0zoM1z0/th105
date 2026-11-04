"""Alice active flight through real counter adjustment, with synthetic tables."""
import importlib.util
from pathlib import Path
import sys
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))
spec = importlib.util.spec_from_file_location('alice_after_adjust', ROOT / 'scripts/audit-alice-fighter-action214-after-adjust.py')
audit = importlib.util.module_from_spec(spec); spec.loader.exec_module(audit)


class AliceAction214AfterAdjustTests(unittest.TestCase):
    def test_real_helpers_and_next_boundary_matrix(self):
        result = audit.audit()
        self.assertEqual(result['result'], 'bounded_post_adjust_paths_agree')
        self.assertEqual(result['cases'], 1728)

    def test_wrong_counter_amount_is_detected(self):
        prefix = audit.load_prefix(); observer, address, image, _, source, _ = prefix.setup()
        changed = bytearray(source); offset = 0x4eb79d - address
        self.assertEqual(changed[offset:offset+2], bytes.fromhex('6a0a'))
        changed[offset+1] = 9
        case = dict(sequence=1, held=1, stop_after_adjust=True, vertical=1, horizontal=1,
                    facing=1, slow=1, angle=0.0, heading=30, speed=4.0,
                    table_kind='constant', counter=30)
        with self.assertRaises(ValueError):
            audit.validate(prefix, observer.execute(image, bytes(changed), case, address), case)


if __name__ == '__main__': unittest.main()
