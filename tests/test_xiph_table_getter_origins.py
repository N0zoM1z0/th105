import copy
from pathlib import Path
import sys
import tomllib
import unittest
from types import SimpleNamespace
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
import xiph_table_getter_origins as g
class TableGetterTests(unittest.TestCase):
    def fixture(self):
        s=tomllib.loads(g.ANCHORS.read_text());return s,[dict(address=a['address'],size='12')for a in s['anchors']],g.load_manifest()['units']
    def test_two_original_complete_getters(self):
        s,r,u=self.fixture();aa=g.validate_spec(s,r,u,s['target_sha256']);self.assertEqual(len(aa),2)
    def test_original_archive_or_member_cannot_change(self):
        for k,v in [('sdk_component','vorbisfile'),('sdk_object','framing.obj'),('sdk_archive_sha256','0'*64),('kind','probe')]:
            s,r,u=self.fixture();u=copy.deepcopy(u);u[s['anchors'][0]['unit']][k]=v
            with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_no_prefix_or_mask(self):
        for k,v in [('size',11),('mask',[7])]:
            s,r,u=self.fixture();s['anchors'][0][k]=v
            with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_code_padding_cannot_count_as_function(self):
        s,r,u=self.fixture();s['anchors'][0]['size']=16;r[0]['size']='16'
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_correct_table_symbol_required(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[s['anchors'][0]['unit']]['functions'][0]['dir32_targets']=['_vwin=_INVSQ2EXP_LOOKUP']
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_formal_prefix_extent_rejected(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[s['anchors'][0]['unit']]['functions'][0]['size']=11
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_duplicate_alias_not_extra_body(self):
        s,r,u=self.fixture();s['anchors'].append(copy.deepcopy(s['anchors'][0]));r.append(copy.deepcopy(r[0]))
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_symbol_cannot_switch_float_and_pointer_result(self):
        s,r,u=self.fixture();s['anchors'][0]['symbol']=s['anchors'][1]['symbol']
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_initialized_writable_data_is_allowed(self):
        sec=SimpleNamespace(VirtualAddress=0x1000,SizeOfRawData=16,Name=b'.data\0\0\0',Characteristics=0xC0000040)
        pe=SimpleNamespace(OPTIONAL_HEADER=SimpleNamespace(ImageBase=0x400000),sections=[sec],get_data=lambda rva,size:bytes(size))
        self.assertEqual(g.initialized_data(pe,0x401000,16),bytes(16))
    def test_zero_fill_executable_and_readonly_storage_rejected(self):
        for size,flags in [(17,0xC0000040),(16,0xE0000040),(16,0x40000040)]:
            sec=SimpleNamespace(VirtualAddress=0x1000,SizeOfRawData=16,Name=b'.data\0\0\0',Characteristics=flags)
            pe=SimpleNamespace(OPTIONAL_HEADER=SimpleNamespace(ImageBase=0x400000),sections=[sec])
            with self.assertRaises(ValueError):g.initialized_data(pe,0x401000,size)
if __name__=='__main__':unittest.main()
