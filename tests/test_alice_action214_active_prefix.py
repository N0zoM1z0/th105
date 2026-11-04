"""Active Alice steering compared to native through the first cosine boundary."""
import importlib.util
from pathlib import Path
import sys
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))
spec = importlib.util.spec_from_file_location('alice_active', ROOT / 'scripts/audit-alice-fighter-action214-active-prefix.py')
audit = importlib.util.module_from_spec(spec); spec.loader.exec_module(audit)


class AliceAction214ActivePrefixTests(unittest.TestCase):
    def test_active_steering_matrix(self):
        result = audit.audit()
        self.assertEqual(result['result'], 'bounded_prefixes_agree')
        self.assertEqual(result['cases'], 432)

    def test_wrong_cosine_argument_is_detected(self):
        observer, address, image, _, source, _ = audit.setup()
        changed = bytearray(source); offset = 0x4eb6f1 - address
        self.assertEqual(changed[offset:offset+6], bytes.fromhex('d98640070000'))
        changed[offset+2] = 0x3c
        case = dict(sequence=1, held=1, stop_at_cosine=True, vertical=0, horizontal=0,
                    facing=1, slow=0, angle=0.0, heading=30, speed=4.0)
        with self.assertRaises(ValueError):
            audit.validate(observer.execute(image, bytes(changed), case, address), case)


if __name__ == '__main__': unittest.main()
