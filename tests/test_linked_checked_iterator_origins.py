"""Synthetic x86 fixtures only; no target/compiler bytes."""
import copy
import hashlib
from pathlib import Path
import struct
import sys
from types import SimpleNamespace
import unittest
from unittest.mock import patch
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
import linked_pe as core
import linked_checked_iterator_origins as gen
from test_linked_pe import VTablePe


class CheckedIteratorOriginTests(unittest.TestCase):
    def fixture(self):
        pe=VTablePe();pe.OPTIONAL_HEADER.SizeOfImage=0x4000
        source=core.IMAGE_BASE+0x1100;helper=core.IMAGE_BASE+0x1200;target=0x402000
        raw=bytearray(b'\x75\x16'+b'\x90'*3+b'\xe8'+b'\0'*4+b'\x90'*9+b'\xe9'+b'\0'*4+b'\x90'*72+b'\xc3')
        for off in (6,20):struct.pack_into('<i',raw,off,helper-source-off-4)
        native=bytearray(raw)
        for off in (6,20):struct.pack_into('<i',native,off,gen.INVALID-target-off-4)
        helper_body=b'\x90'*15+b'\xc3'
        pe.data[0x1100:0x1161]=raw;pe.data[0x1200:0x1210]=helper_body
        symbol='?_Inc@const_iterator@?$_Tree@Synthetic@std@@QAEXXZ'
        functions={source:[(symbol,'i root.ltcg.obj')],source+97:[('_after','root.ltcg.obj')],
                   helper-36:[('__invalid_parameter','libcmt:invarg.obj')],
                   helper:[('__invalid_parameter_noinfo','libcmt:invarg.obj')],
                   helper+16:[('_after_crt','libcmt:invarg.obj')]}
        anchor=dict(address='0x00402000',size=97,symbol=symbol,sha256=hashlib.sha256(native).hexdigest())
        rows=[dict(address='0x00401000',size='1',status='matching'),dict(address='0x00402000',size='97',status='unclassified')]
        data={target:bytes(native),gen.INVALID:helper_body}
        args=dict(pe=pe,functions=functions,cil_owner='root.ltcg.obj',anchor=anchor,rows=rows,
                  read_pe=lambda a,n:data[a][:n])
        spec=dict(schema_version=1,target_sha256='a'*64,unit='u',proof_roots=['0x00401000'],anchors=[anchor])
        units={'u':dict(kind='linked_candidate',profile=core.PROFILE,functions=[dict(address='0x00401000')])}
        return args,data,spec,units

    def run_proof(self,args):
        with patch.object(gen,'INVALID_SHA',hashlib.sha256(b'\x90'*15+b'\xc3').hexdigest()):
            return gen.qualify(**args)

    def test_whole_body_and_both_error_edges(self):
        a,d,s,u=self.fixture();gen.validate_spec(s,[a['rows'][1]],u,a['rows'],'a'*64)
        r=self.run_proof(a)
        self.assertEqual([x['offset']for x in r['calls']],[6,20])
        self.assertEqual(r['masked_bytes'],0)
        self.assertEqual(r['data_references'],[])

    def test_no_forced_export(self):
        a,_,_,_=self.fixture()
        a['pe'].DIRECTORY_ENTRY_EXPORT=SimpleNamespace(symbols=[SimpleNamespace(address=0x1100)])
        with self.assertRaisesRegex(ValueError,'export'):self.run_proof(a)

    def test_unique_source_cil_owner(self):
        for owner in ['invented.obj','libcmt:tree.obj']:
            a,_,_,_=self.fixture();start=core.IMAGE_BASE+0x1100
            a['functions'][start]=[(a['anchor']['symbol'],owner)]
            with self.assertRaises(ValueError):self.run_proof(a)

    def test_original_crt_identity_required(self):
        a,_,_,_=self.fixture();h=core.IMAGE_BASE+0x1200
        a['functions'][h]=[('__invalid_parameter_noinfo','root.ltcg.obj')]
        with self.assertRaisesRegex(ValueError,'original named CRT'):self.run_proof(a)

    def test_complete_crt_wrapper_not_prefix(self):
        a,d,_,_=self.fixture();d[gen.INVALID]=b'\xcc'+d[gen.INVALID][1:]
        with self.assertRaisesRegex(ValueError,'helper differs'):self.run_proof(a)

    def test_original_crt_inner_owner_required(self):
        a,_,_,_=self.fixture();a['functions'][core.IMAGE_BASE+0x1200-36]=[('_wrong','libcmt:invarg.obj')]
        with self.assertRaisesRegex(ValueError,'call owner'):self.run_proof(a)

    def test_changed_native_byte_fails(self):
        a,d,_,_=self.fixture();b=bytearray(d[0x402000]);b[30]=0x91;d[0x402000]=bytes(b)
        with self.assertRaises(ValueError):self.run_proof(a)

    def test_unbound_tail_fails(self):
        a,_,_,_=self.fixture();a['pe'].data[0x1114]^=1
        with self.assertRaises(ValueError):self.run_proof(a)

    def test_extra_call_fails(self):
        a,_,_,_=self.fixture();start=core.IMAGE_BASE+0x1100;helper=core.IMAGE_BASE+0x1200
        a['pe'].data[0x111e:0x1123]=b'\xe8'+struct.pack('<i',helper-start-35)
        with self.assertRaises(ValueError):self.run_proof(a)

    def test_highlow_relocation_fails(self):
        a,_,_,_=self.fixture()
        a['pe'].DIRECTORY_ENTRY_BASERELOC=[SimpleNamespace(entries=[SimpleNamespace(type=3,rva=0x1102)])]
        with self.assertRaises(ValueError):self.run_proof(a)

    def test_full_inventory_uniqueness(self):
        a,d,_,_=self.fixture();b=bytearray(d[0x402000])
        for off in (6,20):struct.pack_into('<i',b,off,gen.INVALID-0x403000-off-4)
        d[0x403000]=bytes(b);a['rows'].append(dict(address='0x00403000',size='97',status='matching'))
        with self.assertRaisesRegex(ValueError,'unique'):self.run_proof(a)

    def test_no_size_family_or_threshold_waiver(self):
        for change in [lambda s:s.update(min_nonreloc_bytes=1),
                       lambda s:s['anchors'][0].update(size=96),
                       lambda s:s['anchors'][0].update(symbol='?_Lrotate@?$_Tree@X@std@@'),
                       lambda s:s.update(proof_roots=['0x00402000'])]:
            a,_,s,u=self.fixture();change(s)
            with self.assertRaises(ValueError):gen.validate_spec(s,[a['rows'][1]],u,a['rows'],'a'*64)


if __name__=='__main__':unittest.main()
