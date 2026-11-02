import importlib.util
from pathlib import Path
import sys
import unittest
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
sp=importlib.util.spec_from_file_location('select_render_tests',Path(__file__).resolve().parents[1]/'scripts/audit-select-render.py');g=importlib.util.module_from_spec(sp);sp.loader.exec_module(g)
class SelectRenderTests(unittest.TestCase):
    def shape(self):return [1497,421,{0x420068:bytes.fromhex('8da42400000000'),0x42006f:b'\x90'},{0x41ff18:b'\xc3',0x4204d8:b'\xc3'}]
    def test_complete_boundary_and_padding(self):g.check_shape(*self.shape())
    def test_no_partial_extent(self):
        for index,value in [(0,1489),(1,419)]:
            args=self.shape();args[index]=value
            with self.assertRaises(ValueError):g.check_shape(*args)
    def test_padding_not_omitted(self):
        args=self.shape();args[2].pop(0x42006f)
        with self.assertRaises(ValueError):g.check_shape(*args)
    def test_padding_bytes_not_masked(self):
        args=self.shape();args[2][0x420068]=bytes.fromhex('8da42401000000')
        with self.assertRaises(ValueError):g.check_shape(*args)
    def test_unreviewed_unreachable_instruction(self):
        args=self.shape();args[2][0x420080]=b'\x90'
        with self.assertRaises(ValueError):g.check_shape(*args)
    def test_actual_ret0_required(self):
        args=self.shape();args[3][0x41ff18]=b'\xc2\x04\x00'
        with self.assertRaises(ValueError):g.check_shape(*args)
    def test_begin_failure_has_no_drawing(self):
        g.check_events([dict(kind='begin')],False,127,.25)
        with self.assertRaises(ValueError):g.check_events([dict(kind='begin'),dict(kind='sprite')],False,127,.25)
    def events(self):
        events=[dict(kind='other',args=[])for _ in range(79)];events[0]['kind']='begin';events[-1]['kind']='finish'
        for i,column in enumerate([10,15,0,1,17,3,4,5]):events[i+1]=dict(kind='tile',args=[0,0,0,column])
        for i in range(25):events[9+i]=dict(kind='color',args=[0x5fffffff if i>=22 else 0xffffff])
        return events
    def test_full_seven_row_argument_contract(self):g.check_events(self.events(),True,127,.25)
    def test_center_alternate_row_required(self):
        events=self.events();events[5]['args'][-1]=2
        with self.assertRaises(ValueError):g.check_events(events,True,127,.25)
    def test_byte_mix_not_boolean(self):
        events=self.events()
        for i in [31,32,33]:events[i]['args'][0]=0x00ffffff
        with self.assertRaises(ValueError):g.check_events(events,True,127,.25)
    def test_no_missing_color_call(self):
        events=self.events();events[9]['kind']='other'
        with self.assertRaises(ValueError):g.check_events(events,True,127,.25)
if __name__=='__main__':unittest.main()
