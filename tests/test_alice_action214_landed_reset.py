"""Alice 214 executes the original landed scratch reset on synthetic terrain."""
import importlib.util
from pathlib import Path
import sys
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))
spec = importlib.util.spec_from_file_location('alice_landed_reset', ROOT / 'scripts/audit-alice-fighter-action214-landed-reset.py')
audit = importlib.util.module_from_spec(spec); spec.loader.exec_module(audit)


class AliceAction214LandedResetTests(unittest.TestCase):
    def test_real_scratch_reset_matrix(self):
        result = audit.audit()
        self.assertEqual(result['result'], 'bounded_reset_paths_agree')
        self.assertEqual(result['cases'], 96)

    def test_wrong_action_is_detected(self):
        landing = audit.load_landing(); prefix = landing.load_prefix()
        observer, address, image, _, source, _ = prefix.setup()
        changed = bytearray(source); offset = 0x4ebae7 - address
        self.assertEqual(changed[offset:offset+5], bytes.fromhex('68d7000000'))
        changed[offset+1] = 0xd6
        case = dict(sequence=1, held=1, stop_after_scratch=True, vertical=-1, horizontal=0,
                    facing=1, slow=0, angle=0.0, heading=30, speed=4.0, table_kind='varying',
                    counter=30, x=50.0, y=-1.0, ground=0.0)
        with self.assertRaises(ValueError):
            audit.validate(observer.execute(image, bytes(changed), case, address))


if __name__ == '__main__': unittest.main()
