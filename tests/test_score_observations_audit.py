import importlib.util
from pathlib import Path
import struct
import sys
import unittest
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'scripts'))
spec = importlib.util.spec_from_file_location('score_observations_tests', Path(__file__).resolve().parents[1] / 'scripts/audit-score-observations.py')
g = importlib.util.module_from_spec(spec)
spec.loader.exec_module(g)


class ScoreObservationTests(unittest.TestCase):
    def run_code(self, code):
        return g.observe(code, {}, dict(stored=10, value=5))

    def test_ret16_and_record_preservation(self):
        result = self.run_code(bytes.fromhex('c21000'))
        self.assertEqual(struct.unpack('<12i', bytes.fromhex(result['records'])), (11, 99, 22, 33, 7, 10) * 2)

    def test_wrong_cleanup_rejected(self):
        with self.assertRaisesRegex(ValueError, 'RET16'):
            self.run_code(bytes.fromhex('c20c00'))

    def test_callee_save_damage_rejected(self):
        with self.assertRaisesRegex(ValueError, 'callee-save'):
            self.run_code(bytes.fromhex('31dbc21000'))

    def test_unknown_helper_callback_fails_closed(self):
        code = b'\xe8' + struct.pack('<i', 0x500000 - g.ADDRESS - 5) + bytes.fromhex('c21000')
        with self.assertRaisesRegex(ValueError, 'callback rejected.*unknown instruction'):
            self.run_code(code)

    def test_unexpected_write_callback_fails_closed(self):
        code = b'\xc7\x05' + struct.pack('<II', g.OWNER, 1) + bytes.fromhex('c21000')
        with self.assertRaisesRegex(ValueError, 'callback rejected.*unexpected record'):
            self.run_code(code)

    def test_partial_instruction_rejected(self):
        with self.assertRaisesRegex(ValueError, 'partial source instruction'):
            self.run_code(b'\xe8')


if __name__ == '__main__':
    unittest.main()
