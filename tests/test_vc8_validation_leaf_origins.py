import copy
from pathlib import Path
import struct
import sys
import tomllib
from types import SimpleNamespace
import unittest
from unittest.mock import patch
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
import vc8_validation_leaf_origins as g
class ScopeFixture:
    def __init__(self):
        self.data=struct.pack('<7I',0xfffffffe,0,0xffffffd4,0,0xfffffffe,0,0)
        self.cf=SimpleNamespace(symbols={1:SimpleNamespace(name='$LN',value=363,section_number=84),2:SimpleNamespace(name='$LN',value=367,section_number=84)},_read_raw=lambda at,n:struct.pack('<IIH',20 if at==0 else 24,1 if at==0 else 2,6))
    def section(self,name):return SimpleNamespace(name='.xdata$x',raw_size=28,reloc_count=2,reloc_offset=0,characteristics=0x40401040)
    def symbol(self,name):
        if name not in [g.SCOPE,g.CATCH]:raise ValueError('ambiguous local name')
        return SimpleNamespace(value=0,section_number=84)
    def raw(self,name,size):return self.data
class ValidationLeafTests(unittest.TestCase):
    def fixture(self):
        s=tomllib.loads(g.ANCHORS.read_text());return s,[dict(address='0x0069C4BF',size='13')],g.load_manifest()['units']
    def test_one_physical_alias_representative(self):
        s,r,u=self.fixture();a,_=g.validate_spec(s,r,u,s['target_sha256']);self.assertEqual(a['symbol'],g.ALIASES[0])
    def test_no_mask_or_short_body(self):
        for k,v in [('size',12),('mask',[0])]:
            s,r,u=self.fixture();s['anchors'][0][k]=v
            with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_no_alias_double_count(self):
        s,r,u=self.fixture();s['anchors'].append(copy.deepcopy(s['anchors'][0]))
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_original_member_required(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT]['toolchain_object']='frame.obj'
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_representative_must_match_anchor(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT]['functions'][0]['symbol_base']=g.ALIASES[1]
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_archive_required(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT]['toolchain_archive_sha256']='0'*64
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def scope(self,r):
        native=struct.pack('<7I',0xfffffffe,0,0xffffffd4,0,0xfffffffe,0x68f452+363,0x68f452+367)
        with patch.object(g.core,'readonly_data',return_value=native):return g.scope_record(r,lambda at,n:native,None)
    def test_duplicate_local_names_resolve_by_index(self):
        _,refs=self.scope(ScopeFixture());self.assertEqual([x['symbol_index']for x in refs],[1,2])
    def test_local_label_must_belong_to_actual_owner(self):
        r=ScopeFixture();r.cf.symbols[2].section_number=85
        with self.assertRaises(ValueError):self.scope(r)
    def test_local_label_must_have_actual_offset(self):
        r=ScopeFixture();r.cf.symbols[2].value=368
        with self.assertRaises(ValueError):self.scope(r)
    def graph_fixture(self):
        b=bytearray(b'\x90'*383);b[361:363]=b'\xeb\x0c';b[363:367]=bytes.fromhex('33c040c3');b[367:370]=bytes.fromhex('8b65e8');b[370]=0xe9;struct.pack_into('<i',b,371,0x68fc12-(0x68f452+375));b[382]=0xc3;return b
    def test_structural_eh_roots_and_named_tail(self):self.assertEqual(g.catch_graph(bytes(self.graph_fixture()),0x68f452)['unaccounted_bytes'],0)
    def test_actual_handler_restore_required(self):
        b=self.graph_fixture();b[369]=0xe4
        with self.assertRaises(ValueError):g.catch_graph(bytes(b),0x68f452)
    def test_tail_is_not_generic_call_permission(self):
        b=self.graph_fixture();b[370]=0xe8
        with self.assertRaises(ValueError):g.catch_graph(bytes(b),0x68f452)
    def test_tail_target_cannot_change(self):
        b=self.graph_fixture();b[371]^=1
        with self.assertRaises(ValueError):g.catch_graph(bytes(b),0x68f452)
    def test_external_conditional_exit_rejected(self):
        b=self.graph_fixture();b[:2]=bytes.fromhex('0f85');struct.pack_into('<i',b,2,0x400000-(0x68f452+6))
        with self.assertRaises(ValueError):g.catch_graph(bytes(b),0x68f452)
    def test_unaccounted_unreachable_byte_rejected(self):
        b=self.graph_fixture();b[:2]=b'\xeb\x01'
        with self.assertRaises(ValueError):g.catch_graph(bytes(b),0x68f452)
if __name__=='__main__':unittest.main()
