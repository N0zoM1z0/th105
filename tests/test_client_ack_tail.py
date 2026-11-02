import copy
import importlib.util
from pathlib import Path
import sys
import unittest
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'scripts'))
spec = importlib.util.spec_from_file_location('ack_tail_tests', Path(__file__).resolve().parents[1] / 'scripts/audit-client-ack-tail.py')
g = importlib.util.module_from_spec(spec)
spec.loader.exec_module(g)


class AckTailTests(unittest.TestCase):
    def fixture(self):
        case = dict(peer=255, side0=128, side1=127, alias=False)
        result = dict(calls=['enter','leave'], values=[255,128,127,1], packet_unchanged=True, local_unchanged=True)
        return case, result

    def test_unsigned_byte_publications(self):
        g.check_result(*self.fixture())

    def test_lock_order_required(self):
        case, result = self.fixture()
        for calls in [[], ['leave','enter'], ['enter','enter','leave']]:
            result['calls'] = calls
            with self.assertRaises(ValueError):
                g.check_result(case,result)

    def test_wrong_field_or_pending_value_rejected(self):
        case, result = self.fixture()
        for i in range(4):
            bad = copy.deepcopy(result)
            bad['values'][i] ^= 1
            with self.assertRaises(ValueError):
                g.check_result(case,bad)

    def test_sources_remain_readonly(self):
        case, result = self.fixture()
        for key in ['packet_unchanged','local_unchanged']:
            bad = copy.deepcopy(result)
            bad[key] = False
            with self.assertRaises(ValueError):
                g.check_result(case,bad)


if __name__ == '__main__':
    unittest.main()
