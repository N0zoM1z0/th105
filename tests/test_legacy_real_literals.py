import struct
from pathlib import Path
import sys
import unittest
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
import match_literals as g

class LegacyRealTests(unittest.TestCase):
    def decode(self,s,**kw):return g.real_literal_bytes(dict(type='DIR32',symbol=s,**kw))
    def legacy(self,width,sign,exponent,mantissa):return f'__real@{width}@{(sign<<15)|exponent:04x}{mantissa:016x}'
    def test_actual_sdk_finite_constants(self):
        for symbol,expected in [('__real@4@40058000000000000000','00008042'),('__real@4@40048000000000000000','00000042'),('__real@8@3ffe8000000000000000','000000000000e03f')]:
            self.assertEqual(self.decode(symbol),bytes.fromhex(expected))
    def test_signed_zero_preserved(self):
        for width in (4,8):
            for sign in (0,1):self.assertEqual(self.decode(self.legacy(width,sign,0,0)),(sign<<(width*8-1)).to_bytes(width,'little'))
    def test_negative_finite_value(self):
        self.assertEqual(self.decode('__real@4@c0028000000000000000'),struct.pack('<f',-8.0))
    def test_smallest_exact_subnormals(self):
        for width,bias,precision in [(4,127,24),(8,1023,53)]:
            exponent=16383+1-bias-(precision-1)
            self.assertEqual(self.decode(self.legacy(width,0,exponent,1<<63)),(1).to_bytes(width,'little'))
    def test_largest_finite_values(self):
        for width,bias,precision in [(4,127,24),(8,1023,53)]:
            mantissa=((1<<precision)-1)<<(64-precision)
            bits=((2*bias)<<(precision-1))|((1<<(precision-1))-1)
            self.assertEqual(self.decode(self.legacy(width,0,16383+bias,mantissa)),bits.to_bytes(width,'little'))
    def test_precision_loss_is_not_rounded(self):
        for width in (4,8):
            with self.assertRaisesRegex(ValueError,'exactly representable'):self.decode(self.legacy(width,0,16383,(1<<63)|1))
    def test_overflow_is_not_infinity(self):
        for width in (4,8):
            with self.assertRaisesRegex(ValueError,'overflows'):self.decode(self.legacy(width,0,0x7ffe,1<<63))
    def test_underflow_is_not_zero(self):
        for width in (4,8):
            with self.assertRaisesRegex(ValueError,'exactly representable'):self.decode(self.legacy(width,0,1,1<<63))
    def test_special_and_pseudo_extended_values_rejected(self):
        for exponent,mantissa in [(0x7fff,1<<63),(0x7fff,(1<<63)|1),(0,1),(16383,1)]:
            with self.assertRaises(ValueError):self.decode(self.legacy(8,0,exponent,mantissa))
    def test_bad_width_or_payload_rejected(self):
        for symbol in ['__real@16@3fff8000000000000000','__real@4@3fff800000000000000','__real@4@3fff80000000000000000','__real@4@zzff8000000000000000']:
            with self.assertRaises(ValueError):self.decode(symbol)
    def test_legacy_requires_dir32(self):
        with self.assertRaisesRegex(ValueError,'DIR32'):g.real_literal_bytes(dict(type='REL32',symbol='__real@4@3fff8000000000000000'))
    def test_legacy_requires_zero_addend(self):
        with self.assertRaisesRegex(ValueError,'zero addend'):self.decode('__real@4@3fff8000000000000000',addend=4)
        with self.assertRaisesRegex(ValueError,'zero addend'):g.real_literal_reference_bytes('__real@4@3fff8000000000000000+0x4')
    def test_wrong_declared_bits_rejected(self):
        with self.assertRaises(ValueError):self.decode('__real@4@3fff8000000000000000',data_hex='00000000')
    def test_existing_ieee_format_and_rejections_preserved(self):
        self.assertEqual(self.decode('__real@3f800000'),bytes.fromhex('0000803f'))
        with self.assertRaises(ValueError):self.decode('__real@3fff8000000000000000')
    def test_alias_cannot_hide_a_different_value(self):
        row=dict(data_hex='00000040',addends='0',validation='literal')
        with self.assertRaises(ValueError):g.validate_real_literal_mapping('__real@4@3fff8000000000000000','named',row)
    def test_legacy_ledger_still_requires_literal_validation(self):
        name='__real@4@3fff8000000000000000';row=dict(coff_symbol=name,address='0x00401000',data_hex='0000803f',addends='0',validation='literal')
        self.assertEqual(g.audit_real_literals([row],dict(units={}))['ledger_literals'],1)
        row['validation']='address'
        with self.assertRaises(ValueError):g.audit_real_literals([row],dict(units={}))
if __name__=='__main__':unittest.main()
