import importlib.util
from pathlib import Path
import sys
import unittest
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
spec=importlib.util.spec_from_file_location('server_input_tests',Path(__file__).resolve().parents[1]/'scripts/audit-server-input-publish.py')
g=importlib.util.module_from_spec(spec)
spec.loader.exec_module(g)


class ServerInputContractTests(unittest.TestCase):
    def args(self):
        return [dict(g.EXPECTED_CALLS),3,[0x40ac40,0x40ac40],[(0x7c,2),(0x98,4)],[0x3ff],[]]

    def test_complete_call_field_and_exit_contract(self):
        g.check_contract(*self.args())

    def test_both_outer_unlock_tail_exits_required(self):
        for i,value in [(2,[0x40ac40]),(2,[0x40ac30,0x40ac40]),(5,[0x44fb34])]:
            args=self.args();args[i]=value
            with self.assertRaises(ValueError):g.check_contract(*args)

    def test_missing_or_extra_calls_rejected(self):
        args=self.args();args[0][0x42a4b0]=1
        with self.assertRaises(ValueError):g.check_contract(*args)
        args=self.args();args[1]=2
        with self.assertRaises(ValueError):g.check_contract(*args)

    def test_input_width_mask_and_sequence_store_required(self):
        for i,value in [(3,[(0x7c,4),(0x98,4)]),(3,[(0x7c,2)]),(4,[0xffff])]:
            args=self.args();args[i]=value
            with self.assertRaises(ValueError):g.check_contract(*args)


if __name__=='__main__':unittest.main()
