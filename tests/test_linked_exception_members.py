from pathlib import Path
import struct
import sys
import tomllib
import unittest
from unittest.mock import patch
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
import linked_exception_members as linked

class LinkedExceptionMemberTests(unittest.TestCase):
    def spec(self):
        s=tomllib.loads(linked.ANCHORS.read_text())
        return s,[dict(address=a['address'],size=str(a['size']))for a in s['anchors']]
    def test_all_four_typed_roots_required(self):
        s,rows=self.spec();self.assertEqual(len(linked.validate_spec(s,rows,s['target_sha256'])),4)
        with self.assertRaises(ValueError):linked.validate_spec(s,rows[:-1],s['target_sha256'])
    def test_bad_alloc_shape_cannot_replace_out_of_range(self):
        s,rows=self.spec();a=next(a for a in s['anchors']if a['address']=='0x00401780');a['symbol']=a['symbol'].replace('out_of_range','bad_alloc')
        with self.assertRaises(ValueError):linked.validate_spec(s,rows,s['target_sha256'])
    def test_partial_or_masked_contract_rejected(self):
        for partial in (False,True):
            s,rows=self.spec()
            if partial:s['anchors'][0]['size']-=1
            else:s['anchors'][0]['mask']=[3]
            with self.assertRaises(ValueError):linked.validate_spec(s,rows,s['target_sha256'])
    def test_identical_what_bodies_are_explicit_not_called_unique(self):
        r=linked.inventory_contract('what','0x004016E0',linked.WHAT_HITS)
        self.assertFalse(r['byte_unique'])
        for hits in (linked.WHAT_HITS[:1],linked.WHAT_HITS+['0x00401000']):
            with self.assertRaises(ValueError):linked.inventory_contract('what','0x004016E0',hits)
    def test_copy_must_be_globally_canonical_unique(self):
        r=linked.inventory_contract('copy','0x00401780',['0x00401780']);self.assertTrue(r['byte_unique'])
        with self.assertRaises(ValueError):linked.inventory_contract('copy','0x00401780',['0x00401780','0x00402570'])
    def fixture(self,klass='logic_error'):
        table=0x6c05d0 if klass=='logic_error'else 0x6d5e48
        native_what=0x4016e0 if klass=='logic_error'else 0x6a4b70
        vt='??_7'+klass+'@std@@6B@';what='?what@'+klass+'@std@@UBEPBDXZ'
        symbols={vt:[(0x10002000,'libcpmt:string.obj'if klass=='logic_error'else'original-0.obj')],what:[(0x10003000,'f i original-0.obj')]}
        return table,native_what,symbols
    def test_actual_named_type_and_slot(self):
        for klass in ('logic_error','runtime_error'):
            table,what,symbols=self.fixture(klass)
            with patch.object(linked.core,'primary_type_name',return_value='.?AV'+klass+'@std@@'),patch.object(linked.core,'readonly_data',return_value=struct.pack('<I',0x10003000)),patch.object(linked.core,'validate_body_relocations'):
                source,symbol,fact=linked.type_contract(None,None,symbols,klass,table,lambda a,n:struct.pack('<I',what))
                self.assertEqual(source,0x10002000);self.assertEqual(fact['native_what'],hex(what))
    def test_wrong_nominal_rtti_rejected(self):
        table,what,symbols=self.fixture()
        with patch.object(linked.core,'primary_type_name',return_value='.?AVruntime_error@std@@'):
            with self.assertRaisesRegex(ValueError,'nominal'):linked.type_contract(None,None,symbols,'logic_error',table,lambda a,n:b'\0'*n)
    def test_wrong_slot_rejected_even_when_opcode_body_identical(self):
        table,what,symbols=self.fixture()
        with patch.object(linked.core,'primary_type_name',return_value='.?AVlogic_error@std@@'),patch.object(linked.core,'readonly_data',return_value=struct.pack('<I',0x10003000)):
            with self.assertRaisesRegex(ValueError,'slot'):linked.type_contract(None,None,symbols,'logic_error',table,lambda a,n:struct.pack('<I',0x6a4b70))
    def test_wrong_original_vtable_owner_rejected(self):
        table,what,symbols=self.fixture();symbols['??_7logic_error@std@@6B@']=[(0x10002000,'unreviewed.obj')]
        with self.assertRaisesRegex(ValueError,'owner'):linked.type_contract(None,None,symbols,'logic_error',table,lambda a,n:b'\0'*n)

if __name__=='__main__':unittest.main()
