import copy
from pathlib import Path
import struct
import sys
import tomllib
from types import SimpleNamespace
import unittest
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
import vc8_control_entry_origins as g
class RegistrationFixture:
    def __init__(self,section='.CRT$XIC',raw=bytes(4),flags=0x40300040):self.label=section;self.data=raw;self.flags=flags
    def section(self,name):return SimpleNamespace(name=self.label,raw_size=4,characteristics=self.flags)
    def symbol(self,name):return SimpleNamespace(value=0)
    def raw(self,name,size):return self.data
    def refs(self,name,size):return [(0,6,'init')]
class ControlEntryTests(unittest.TestCase):
    def fixture(self):
        s=tomllib.loads(g.ANCHORS.read_text());return s,[dict(address=a['address'],size=str(a['size']))for a in s['anchors']],g.load_manifest()['units']
    def test_all_original_entries(self):
        s,r,u=self.fixture();self.assertEqual({a['address']for a in g.validate_spec(s,r,u,s['target_sha256'])},set(g.CONTRACT))
    def test_no_mask(self):
        s,r,u=self.fixture();s['anchors'][0]['mask']=[2]
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_no_short_body(self):
        s,r,u=self.fixture();s['anchors'][0]['size']-=1
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_missing_entry_rejected(self):
        s,r,u=self.fixture();s['anchors'].pop()
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_heap_handler_is_not_debugger_hook(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u['vc8-original-debugger-hook']['toolchain_object']='handler.obj'
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_sse_query_target_required(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u['vc8-original-sse2-initializer']['functions'][0]['rel32_targets']=['__get_sse2_info=0x0069C928']
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_common_words_not_interchangeable(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u['vc8-original-debugger-hook']['functions'][0]['dir32_targets']=['__debugger_hook_dummy=vc8_sse2_available']
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_actual_exception_callback_required(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u['vc8-original-cxx-filter-registration']['functions'][0]['dir32_targets'].pop(0)
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_actual_c_registration(self):
        self.assertEqual(g.registration(RegistrationFixture(),'.CRT$XIC','init',0x4000,0x5000,lambda at,n:struct.pack('<I',0x4000))['native_target'],'0x4000')
    def test_cpp_registration_not_substituted(self):
        with self.assertRaises(ValueError):g.registration(RegistrationFixture('.CRT$XCU'),'.CRT$XIC','init',0x4000,0x5000,lambda at,n:struct.pack('<I',0x4000))
    def test_registration_addend_must_be_zero(self):
        with self.assertRaises(ValueError):g.registration(RegistrationFixture(raw=b'\1\0\0\0'),'.CRT$XIC','init',0x4000,0x5000,lambda at,n:struct.pack('<I',0x4000))
    def test_registration_native_role_must_match(self):
        with self.assertRaises(ValueError):g.registration(RegistrationFixture(),'.CRT$XIC','init',0x4000,0x5000,lambda at,n:struct.pack('<I',0x4001))
    def test_registration_source_must_be_readonly(self):
        with self.assertRaises(ValueError):g.registration(RegistrationFixture(flags=0xc0300040),'.CRT$XIC','init',0x4000,0x5000,lambda at,n:struct.pack('<I',0x4000))
if __name__=='__main__':unittest.main()
