"""Alice action 214 executes the real landing and stage-height helpers."""
import importlib.util
from pathlib import Path
import sys
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))
spec = importlib.util.spec_from_file_location('alice_landing', ROOT / 'scripts/audit-alice-fighter-action214-landing.py')
audit = importlib.util.module_from_spec(spec); spec.loader.exec_module(audit)


class AliceAction214LandingTests(unittest.TestCase):
    def test_original_landing_and_terrain_matrix(self):
        result = audit.audit()
        self.assertEqual(result['result'], 'bounded_landing_paths_agree')
        self.assertEqual(result['cases'], 648)
        self.assertGreater(result['crossed_cases'], 0)

    def test_inverted_landing_branch_is_detected(self):
        prefix = audit.load_prefix(); observer, address, image, _, source, _ = prefix.setup()
        changed = bytearray(source); offset = 0x4eba96 - address
        self.assertEqual(changed[offset:offset+2], bytes.fromhex('0f84'))
        changed[offset+1] = 0x85
        case = dict(sequence=1, held=1, stop_after_landing_check=True, vertical=-1, horizontal=0,
                    facing=1, slow=0, angle=0.0, heading=30, speed=4.0, table_kind='varying',
                    counter=30, x=50.0, y=-1.0, ground=0.0)
        with self.assertRaises(ValueError):
            audit.validate(prefix, observer.execute(image, bytes(changed), case, address), case)


if __name__ == '__main__': unittest.main()
