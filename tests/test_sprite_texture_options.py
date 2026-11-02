import importlib.util
from pathlib import Path
import sys
import unittest
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'scripts'))
spec = importlib.util.spec_from_file_location('sprite_options_tests', Path(__file__).resolve().parents[1] / 'scripts/audit-sprite-texture-options.py')
g = importlib.util.module_from_spec(spec)
spec.loader.exec_module(g)

class SpriteTextureOptionsTests(unittest.TestCase):
    def result(self, case):
        return dict(state=g.expected(case).hex(), query_handles=[case['handle']], writes=list(g.FIELDS))

    def test_preserved_coordinate_is_checked(self):
        case = g.CASES[1]
        result = self.result(case)
        g.check_result(case, result)
        state = bytearray.fromhex(result['state'])
        state[8] ^= 1
        result['state'] = state.hex()
        with self.assertRaises(ValueError):
            g.check_result(case, result)

    def test_query_identity_and_count_are_checked(self):
        case = g.CASES[1]
        for handles in [[], [0], [case['handle']] * 2]:
            result = self.result(case)
            result['query_handles'] = handles
            with self.assertRaises(ValueError):
                g.check_result(case, result)

    def test_duplicate_or_missing_writes_are_rejected(self):
        case = g.CASES[0]
        for writes in [list(g.FIELDS)[:-1], list(g.FIELDS) + [4]]:
            result = self.result(case)
            result['writes'] = writes
            with self.assertRaises(ValueError):
                g.check_result(case, result)

    def test_uv_corner_and_unsigned_extent(self):
        case = dict(g.CASES[4])
        result = self.result(case)
        state = bytes.fromhex(result['state'])
        u, v = g.struct.unpack_from('<ff', state, 8 + 3 * 28 + 20)
        self.assertAlmostEqual(u, (case['x'] + case['width']) / case['texture_width'], places=14)
        self.assertAlmostEqual(v, (case['y'] + case['height']) / case['texture_height'], places=14)
        self.assertGreater(u, 0)
        self.assertLess(v, 0)

if __name__ == '__main__':
    unittest.main()
