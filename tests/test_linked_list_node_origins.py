from pathlib import Path
import struct
import sys
import tomllib
import unittest
import capstone
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
import linked_list_node_origins as linked

class LinkedListNodeTests(unittest.TestCase):
    def spec(self):
        s=tomllib.loads(linked.ANCHORS.read_text())
        return s,[dict(address='0x006A3BD0',size='26')]
    def rows(self,tail='894604c7460800000000c3'):
        base=0x10001000;callee=0x10002000
        raw=b'\xe8'+struct.pack('<i',callee-base-5)+bytes.fromhex(tail)
        d=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);d.detail=True
        return list(d.disasm(raw,base)),callee,base
    def test_original_whole_specialization(self):
        s,rows=self.spec();self.assertEqual(linked.validate_spec(s,rows,s['target_sha256'])['size'],26)
    def test_wrong_payload_specialization_rejected(self):
        s,rows=self.spec();s['anchors'][0]['symbol']=s['anchors'][0]['symbol'].replace('PBK','PBD')
        with self.assertRaises(ValueError):linked.validate_spec(s,rows,s['target_sha256'])
    def test_partial_mask_or_extra_root_rejected(self):
        for mode in ('partial','mask','extra'):
            s,rows=self.spec()
            if mode=='partial':s['anchors'][0]['size']=25
            elif mode=='mask':s['anchors'][0]['mask']=[3]
            else:rows.append(dict(address='0x006B0310',size='125'))
            with self.assertRaises(ValueError):linked.validate_spec(s,rows,s['target_sha256'])
    def test_actual_owner_publishes_returned_head_and_zero_count(self):
        rows,callee,site=self.rows();fact=linked.header_use(rows,callee,site)
        self.assertEqual((fact['header_offset'],fact['size_offset'],fact['receiver']),(4,8,'esi'))
    def test_wrong_call_site_rejected(self):
        rows,callee,site=self.rows()
        with self.assertRaises(ValueError):linked.header_use(rows,callee,site+1)
    def test_wrong_callee_rejected(self):
        rows,callee,site=self.rows()
        with self.assertRaises(ValueError):linked.header_use(rows,callee+1,site)
    def test_wrong_header_offset_or_value_rejected(self):
        for tail in ('894608c7460800000000c3','895604c7460800000000c3','894604c7460801000000c3'):
            rows,callee,site=self.rows(tail)
            with self.assertRaises(ValueError):linked.header_use(rows,callee,site)
    def test_different_owner_for_count_rejected(self):
        rows,callee,site=self.rows('894604c7470800000000c3')
        with self.assertRaises(ValueError):linked.header_use(rows,callee,site)

if __name__=='__main__':unittest.main()
