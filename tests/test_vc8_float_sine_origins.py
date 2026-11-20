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
    def test_original_vendor_header_bytes_required(self):
        with tempfile.TemporaryDirectory() as tmp:
            tools = Path(tmp)
            pins = {}
            for name in sine.HEADER_PINS:
                path = tools / name
                path.parent.mkdir(parents=True, exist_ok=True)
                path.write_bytes(b'vendor-original\n')
                pins[name] = sine.digest(path.read_bytes())
            with patch.object(sine, 'HEADER_PINS', pins):
                sine.verify_vendor_headers(tools)
                (tools / 'include/math.h').write_bytes(b'vendor-altered\n')
                with self.assertRaisesRegex(ValueError, 'math header'):
                    sine.verify_vendor_headers(tools)

if __name__=='__main__':unittest.main()
