import copy
from pathlib import Path
import struct
import sys
import tempfile
import tomllib
import unittest
from unittest.mock import patch
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
import vc8_float_sine_origins as sine

class FloatSineOriginTests(unittest.TestCase):
    def fixture(self):
        s=tomllib.loads(sine.ANCHORS.read_text());units=sine.load_manifest()['units']
        return s,[dict(address='0x0063D3C0',size='18')],units
    def test_actual_caller_and_overload_contract(self):
        s,rows,u=self.fixture();self.assertEqual(sine.validate_spec(s,rows,u,s['target_sha256'])['source'],'src/characters/TenshiActionState.cpp')
    def test_old_double_facade_or_other_alias_rejected(self):
        for symbol in ('?tenshi_sine_radians@th105@@YANM@Z','_sinf'):
            s,rows,u=self.fixture();s['anchors'][0]['symbol']=symbol
            with self.assertRaises(ValueError):sine.validate_spec(s,rows,u,s['target_sha256'])
    def test_partial_body_or_mask_rejected(self):
        for key,value in [('size',17),('mask',[5])]:
            s,rows,u=self.fixture();s['anchors'][0][key]=value
            with self.assertRaises(ValueError):sine.validate_spec(s,rows,u,s['target_sha256'])
    def test_different_compiler_profile_rejected(self):
        s,rows,u=self.fixture();u=copy.deepcopy(u);u[sine.UNIT]['enable_gs']=True
        with self.assertRaises(ValueError):sine.validate_spec(s,rows,u,s['target_sha256'])
    def window(self):
        start=0x600000;offset=3
        return b'\xd9\x1c\x24\xe8'+struct.pack('<i',0x63d3c0-start-offset-5)+b'\xd8\x1d'+struct.pack('<I',0x6d6ea8)+b'\x83\xc4\x04',start,offset
    def test_float_argument_comparison_and_cleanup(self):
        code,start,offset=self.window();self.assertEqual(sine.caller_window(code,start,offset)['comparison'],'FCOMP dword [0x006D6EA8]')
    def test_double_compare_wrong_literal_or_cleanup_rejected(self):
        code,start,offset=self.window()
        for at in (0,offset+1,offset+5,offset+7,offset+13):
            bad=bytearray(code);bad[at]^=1
            with self.assertRaises(ValueError):sine.caller_window(bytes(bad),start,offset)
    def source_fixture(self,root):
        spec=dict(source_pins={})
        for name in sine.SOURCES:
            p=root/name;p.parent.mkdir(parents=True,exist_ok=True)
            raw=b'std::sin(p[0]);\n'if name.endswith('.cpp')else b'// fixture header\n'
            p.write_bytes(raw);spec['source_pins'][name]=sine.digest(raw)
        tools=root/'tools';pins={}
        for name in sine.HEADER_PINS:
            p=tools/name;p.parent.mkdir(parents=True,exist_ok=True);p.write_bytes(b'vendor-original\n');pins[name]=sine.digest(p.read_bytes())
        return spec,tools,pins
    def test_repo_crlf_normalized_but_vendor_bytes_raw(self):
        with tempfile.TemporaryDirectory()as tmp:
            root=Path(tmp);s,tools,pins=self.source_fixture(root)
            with patch.object(sine,'HEADER_PINS',pins):
                sine.verify_sources(s,tools,root)
                for name in sine.SOURCES:
                    p=root/name;p.write_bytes(p.read_bytes().replace(b'\n',b'\r\n'))
                sine.verify_sources(s,tools,root)
                p=tools/'include/math.h';p.write_bytes(p.read_bytes().replace(b'\n',b'\r\n'))
                with self.assertRaisesRegex(ValueError,'math header'):sine.verify_sources(s,tools,root)
    def test_changed_caller_source_rejected(self):
        with tempfile.TemporaryDirectory()as tmp:
            root=Path(tmp);s,tools,pins=self.source_fixture(root)
            (root/'src/characters/TenshiActionState.cpp').write_text('custom_sine();\n')
            with patch.object(sine,'HEADER_PINS',pins):
                with self.assertRaisesRegex(ValueError,'caller source'):sine.verify_sources(s,tools,root)

if __name__=='__main__':unittest.main()
