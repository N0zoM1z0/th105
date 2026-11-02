import importlib.util
from pathlib import Path
import struct
import sys
from types import SimpleNamespace
import unittest
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
sp=importlib.util.spec_from_file_location('network_dtor_eh_tests',Path(__file__).resolve().parents[1]/'scripts/audit-network-base-destructor-eh.py');g=importlib.util.module_from_spec(sp);sp.loader.exec_module(g)
class NetworkDestructorEhTests(unittest.TestCase):
    def reader(self,code=169,handler=142,meta=100):
        return SimpleNamespace(section=lambda n:SimpleNamespace(name='.text$x'if n.startswith('__ehhandler')else'.xdata$x',raw_size=code if n.startswith('__ehhandler')else meta),symbol=lambda n:SimpleNamespace(value=handler if n.startswith('__ehhandler')else 36 if n.startswith('__unwindtable')else 0))
    def test_nested_lifetime_layout(self):self.assertEqual(g.check_eh_layout(self.reader())[0].raw_size,169)
    def test_flattened_array_cleanup_rejected(self):
        with self.assertRaises(ValueError):g.check_eh_layout(self.reader(code=179,handler=152))
    def test_no_partial_metadata(self):
        with self.assertRaises(ValueError):g.check_eh_layout(self.reader(meta=96))
    def test_wrong_handler_position_rejected(self):
        with self.assertRaises(ValueError):g.check_eh_layout(self.reader(handler=152))
    def fixture(self):
        actions=[('a'+str(i),0x6b8c60+off)for i,off in enumerate(g.OFFSETS)];meta=bytearray(struct.pack('<9I',0x19930522,8,0x6decbc,0,0,0,0,0,1)+b''.join(struct.pack('<iI',i-1,at)for i,(n,at)in enumerate(actions)));return meta,actions
    def test_whole_state_chain(self):
        m,a=self.fixture();g.check_unwind(bytes(m),a)
    def test_missing_state_or_changed_previous_state(self):
        m,a=self.fixture()
        with self.assertRaises(ValueError):g.check_unwind(bytes(m),a[:-1])
        struct.pack_into('<i',m,36+5*8,3)
        with self.assertRaises(ValueError):g.check_unwind(bytes(m),a)
    def test_action_cannot_skip_this_adjusting_funclet(self):
        m,a=self.fixture();struct.pack_into('<I',m,36+5*8+4,0x43c380)
        with self.assertRaises(ValueError):g.check_unwind(bytes(m),a)
    def test_magic_and_final_flags_checked(self):
        for off in [0,32]:
            m,a=self.fixture();m[off]^=1
            with self.assertRaises(ValueError):g.check_unwind(bytes(m),a)
if __name__=='__main__':unittest.main()
