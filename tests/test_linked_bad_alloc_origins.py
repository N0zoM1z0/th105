from pathlib import Path
import struct
import sys
import tomllib
import unittest
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
import linked_bad_alloc_origins as linked

class LinkedBadAllocTests(unittest.TestCase):
    def spec(self):
        s=tomllib.loads(linked.ANCHORS.read_text())
        return s,[dict(address=a['address'],size=str(a['size']))for a in s['anchors']]
    def fixture(self,word=False):
        # Synthetic machine-code fixture, not game bytes or reconstructed C++.
        start=0x10001000;throw=0x10003000;info=0x10004000;vt=0x10005000
        offsets=[18,58,81]if word else[15,58,81]
        b=bytearray(b'\x90'*85);b[0:2]=b'\x75\x37'
        # Return is at56; the branch owns the separately reachable throw path57.
        b[56]=0xc3
        calls={start+0x100:('??2@YAPAXI@Z',0x689dcb),
               start+0x200:('??0exception@std@@QAE@ABQBD@Z',0x689f1c),
               throw:(linked.THROW,0x68a153)}
        for off,to in zip(offsets,calls):
            b[off-1]=0xe8;struct.pack_into('<i',b,off,to-(start+off+4))
        b[62]=0x68;struct.pack_into('<I',b,63,info)
        b[67:72]=bytes.fromhex('8d4c240851'if word else'8d4c240451')
        b[72:76]=bytes.fromhex('c744240c'if word else'c7442408');struct.pack_into('<I',b,76,vt)
        return b,start,throw,offsets,calls,info,vt
    def test_five_typed_complete_anchors(self):
        s,rows=self.spec();self.assertEqual(len(linked.validate_spec(s,rows,s['target_sha256'])),5)
        with self.assertRaises(ValueError):linked.validate_spec(s,rows[:-1],s['target_sha256'])
    def test_wrong_copy_address_or_partial_body_rejected(self):
        for field,value in [('address','0x00401780'),('size',24),('symbol','fake')]:
            s,rows=self.spec();s['anchors'][2][field]=value
            with self.assertRaises(ValueError):linked.validate_spec(s,rows,s['target_sha256'])
    def test_cfg_closes_both_return_and_noreturn_paths(self):
        for word in (False,True):
            b,start,throw,offsets,*_=self.fixture(word)
            self.assertTrue(linked.allocator_cfg(bytes(b),start,throw,offsets))
    def test_ordinary_core_still_rejects_terminal_call(self):
        b,start,*_=self.fixture()
        with self.assertRaises(ValueError):linked.core.decode_closed_body(bytes(b),start)
    def test_wrong_throw_target_rejected(self):
        b,start,throw,offsets,*_=self.fixture()
        with self.assertRaisesRegex(ValueError,'terminal'):linked.allocator_cfg(bytes(b),start,throw+1,offsets)
    def test_branch_into_instruction_rejected(self):
        b,start,throw,offsets,*_=self.fixture();b[1]=61
        with self.assertRaisesRegex(ValueError,'CFG'):linked.allocator_cfg(bytes(b),start,throw,offsets)
    def test_unreachable_bytes_rejected(self):
        b,start,throw,offsets,*_=self.fixture();b[3]=0xc3
        with self.assertRaises(ValueError):linked.allocator_cfg(bytes(b),start,throw,offsets)
    def test_extra_call_rejected(self):
        b,start,throw,offsets,*_=self.fixture();b[3:8]=b'\xe8\0\0\0\0'
        with self.assertRaisesRegex(ValueError,'inventory'):linked.allocator_cfg(bytes(b),start,throw,offsets)
    def test_canonicalizer_changes_only_five_pointer_fields(self):
        for word in (False,True):
            b,start,throw,offsets,calls,info,vt=self.fixture(word);symbol=linked.WORD if word else linked.BYTE
            canonical,report,refs=linked.allocator_canonical(bytes(b),start,0x410130 if word else 0x402590,symbol,calls,info,vt)
            allowed={i for off in offsets+[63,76]for i in range(off,off+4)}
            self.assertTrue(all(a==v for i,(a,v)in enumerate(zip(b,canonical))if i not in allowed))
            self.assertEqual(len(report),3);self.assertEqual(len(refs),2)
    def test_wrong_type_or_object_argument_rejected(self):
        b,start,throw,offsets,calls,info,vt=self.fixture()
        for at in (63,69,74,76):
            bad=bytearray(b);bad[at]^=1
            with self.assertRaises(ValueError):linked.allocator_canonical(bytes(bad),start,0x402590,linked.BYTE,calls,info,vt)
    def test_wrong_call_semantics_rejected(self):
        b,start,throw,offsets,calls,info,vt=self.fixture();key=next(iter(calls));calls[key]=('wrong',calls[key][1])
        with self.assertRaisesRegex(ValueError,'semantic'):linked.allocator_canonical(bytes(b),start,0x402590,linked.BYTE,calls,info,vt)

if __name__=='__main__':unittest.main()
