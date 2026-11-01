"""Synthetic proof fixtures; no original game/compiler instruction bytes."""
import hashlib
from pathlib import Path
import struct
import sys
from types import SimpleNamespace
import unittest
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
import linked_pe as core
import linked_string_range_origins as gen
from test_linked_pe import VTablePe


class StringRangeOriginTests(unittest.TestCase):
    def fixture(self):
        pe=VTablePe();pe.OPTIONAL_HEADER.SizeOfImage=0x4000
        start=core.IMAGE_BASE+0x1100;delete=core.IMAGE_BASE+0x1200;free=core.IMAGE_BASE+0x1300
        target=0x402000
        raw=bytearray(b'\x90'*26+b'\xe8'+b'\0'*4+b'\x90'*25+b'\xc3')
        struct.pack_into('<i',raw,27,delete-start-31)
        native=bytearray(raw);struct.pack_into('<i',native,27,gen.DELETE-target-31)
        helper=b'\xe9'+struct.pack('<i',free-delete-5)
        native_helper=b'\xe9'+struct.pack('<i',gen.FREE-gen.DELETE-5)
        pe.data[0x1100:0x1139]=raw;pe.data[0x1200:0x1205]=helper;pe.data[0x1300]=0xc3
        symbol='??$_Destroy_range@V?$basic_string@DSynthetic@std@@'
        functions={start:[(symbol,'i root.ltcg.obj')],start+57:[('_after','root.ltcg.obj')],
                   delete:[('??3@YAXPAX@Z','libcmt:delete.obj')],
                   delete+5:[('_after_delete','libcmt:delete.obj')],
                   free:[('_free','libcmt:free.obj')]}
        anchor=dict(address='0x00402000',size=57,symbol=symbol,sha256=hashlib.sha256(native).hexdigest())
        rows=[dict(address='0x00401000',size='1',status='matching'),
              dict(address='0x00402000',size='57',status='unclassified')]
        data={target:bytes(native),gen.DELETE:native_helper}
        args=dict(pe=pe,functions=functions,cil_owner='root.ltcg.obj',anchor=anchor,rows=rows,
                  read_pe=lambda a,n:data[a][:n])
        spec=dict(schema_version=1,target_sha256='a'*64,unit='u',proof_roots=['0x00401000'],anchors=[anchor])
        units={'u':dict(kind='linked_candidate',profile=core.PROFILE,functions=[dict(address='0x00401000')])}
        return args,data,spec,units

    def test_full_body_and_complete_crt_tail(self):
        a,d,s,u=self.fixture();gen.validate_spec(s,[a['rows'][1]],u,a['rows'],'a'*64)
        proof=gen.qualify(**a)
        self.assertEqual([x['offset']for x in proof['calls']],[27])
        self.assertEqual(proof['masked_bytes'],0)
        self.assertEqual(proof['data_references'],[])

    def test_no_forced_export(self):
        a,_,_,_=self.fixture()
        a['pe'].DIRECTORY_ENTRY_EXPORT=SimpleNamespace(symbols=[SimpleNamespace(address=0x1100)])
        with self.assertRaisesRegex(ValueError,'export'):gen.qualify(**a)

    def test_real_cil_owner_required(self):
        a,_,_,_=self.fixture();a['functions'][core.IMAGE_BASE+0x1100]=[(a['anchor']['symbol'],'stub.obj')]
        with self.assertRaisesRegex(ValueError,'CIL'):gen.qualify(**a)

    def test_delete_and_free_original_owners(self):
        for address,name in [(0x1200,'??3@YAXPAX@Z'),(0x1300,'_free')]:
            a,_,_,_=self.fixture();a['functions'][core.IMAGE_BASE+address]=[(name,'fake.obj')]
            with self.assertRaisesRegex(ValueError,'CRT ownership'):gen.qualify(**a)

    def test_delete_wrapper_must_reach_free(self):
        a,_,_,_=self.fixture();a['pe'].data[0x1201]^=1
        with self.assertRaises(ValueError):gen.qualify(**a)

    def test_whole_delete_target_checked(self):
        a,d,_,_=self.fixture();d[gen.DELETE]=b'\x90'+d[gen.DELETE][1:]
        with self.assertRaisesRegex(ValueError,'wrapper is not canonical'):gen.qualify(**a)

    def test_changed_range_target_fails(self):
        a,d,_,_=self.fixture();b=bytearray(d[0x402000]);b[40]=0x91;d[0x402000]=bytes(b)
        with self.assertRaises(ValueError):gen.qualify(**a)

    def test_extra_call_fails(self):
        a,_,_,_=self.fixture();start=core.IMAGE_BASE+0x1100;dest=core.IMAGE_BASE+0x1200
        a['pe'].data[0x1105:0x110a]=b'\xe8'+struct.pack('<i',dest-start-10)
        with self.assertRaises(ValueError):gen.qualify(**a)

    def test_unproved_callee_fails(self):
        a,_,_,_=self.fixture();a['pe'].data[0x111b]^=1
        with self.assertRaises(ValueError):gen.qualify(**a)

    def test_data_relocations_fail(self):
        a,_,_,_=self.fixture()
        a['pe'].DIRECTORY_ENTRY_BASERELOC=[SimpleNamespace(entries=[SimpleNamespace(type=3,rva=0x1102)])]
        with self.assertRaises(ValueError):gen.qualify(**a)

    def test_full_inventory_uniqueness(self):
        a,d,_,_=self.fixture();b=bytearray(d[0x402000])
        struct.pack_into('<i',b,27,gen.DELETE-0x403000-31)
        d[0x403000]=bytes(b);a['rows'].append(dict(address='0x00403000',size='57',status='matching'))
        with self.assertRaisesRegex(ValueError,'unique'):gen.qualify(**a)

    def test_no_family_extent_or_mask_waiver(self):
        for change in [lambda s:s.update(mask_offsets=[27]),
                       lambda s:s['anchors'][0].update(size=56),
                       lambda s:s['anchors'][0].update(symbol='?_Inc@const_iterator@?$_Tree@X@std@@'),
                       lambda s:s.update(proof_roots=['0x00402000'])]:
            a,_,s,u=self.fixture();change(s)
            with self.assertRaises(ValueError):gen.validate_spec(s,[a['rows'][1]],u,a['rows'],'a'*64)


if __name__=='__main__':unittest.main()
