from pathlib import Path
import sys
import tomllib
import unittest
from unittest.mock import patch
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
import linked_boost_small_origins as linked

class LinkedBoostSmallTests(unittest.TestCase):
    def spec(self):
        s=tomllib.loads(linked.ANCHORS.read_text())
        return s,[dict(address=a['address'],size=str(a['size']))for a in s['anchors']]
    def test_complete_typed_selection(self):
        s,rows=self.spec();self.assertEqual(len(linked.validate_spec(s,rows,s['target_sha256'])),len(linked.CONTRACT))
        with self.assertRaises(ValueError):linked.validate_spec(s,rows[:-1],s['target_sha256'])
    def test_no_partial_or_masked_body_contract(self):
        for key,value in [('size',10),('mask',[4]),('symbol','fake')]:
            s,rows=self.spec();s['anchors'][0][key]=value
            with self.assertRaises(ValueError):linked.validate_spec(s,rows,s['target_sha256'])
    def test_target_and_digest_are_required(self):
        s,rows=self.spec()
        with self.assertRaises(ValueError):linked.validate_spec(s,rows,'wrong')
        s['anchors'][0]['sha256']='0'
        with self.assertRaises(ValueError):linked.validate_spec(s,rows,s['target_sha256'])
    def test_original_named_class_identity(self):
        for klass in (linked.BASE,linked.CLONE,linked.IMPL):
            symbol='??_7'+klass+'6B@';owner='original-1.obj'if klass==linked.IMPL else'original-0.obj'
            symbols={symbol:[(0x10002000,owner)]}
            with patch.object(linked.core,'primary_type_name',return_value='.?AV'+klass):
                fact=linked.table_identity(None,None,symbols,klass,0x6d5de0)
                self.assertEqual(fact['source_address'],0x10002000)
    def test_wrong_class_even_if_body_equal_rejected(self):
        klass=linked.BASE;symbols={'??_7'+klass+'6B@':[(0x10002000,'original-0.obj')]}
        with patch.object(linked.core,'primary_type_name',return_value='.?AVwrong@@'):
            with self.assertRaisesRegex(ValueError,'RTTI'):linked.table_identity(None,None,symbols,klass,0x6d5de0)
    def test_foreign_source_vtable_rejected(self):
        klass=linked.IMPL;symbols={'??_7'+klass+'6B@':[(0x10002000,'foreign.obj')]}
        with self.assertRaisesRegex(ValueError,'owner'):linked.table_identity(None,None,symbols,klass,0x6d690c)
    def test_ambiguous_source_vtable_rejected(self):
        klass=linked.CLONE;symbols={'??_7'+klass+'6B@':[(0x10002000,'original-0.obj'),(0x10003000,'original-0.obj')]}
        with self.assertRaises(ValueError):linked.table_identity(None,None,symbols,klass,0x6d5dd0)

    def test_destructor_uses_its_real_clone_base_identity(self):
        size,symbol,owner,klass,table,slot=linked.CONTRACT['0x006A0880']
        self.assertEqual((size,symbol,klass,table,slot),(7,linked.DTOR,linked.CLONE,0x6d5dd0,None))
        self.assertEqual(owner,'i original-0.obj')
    def test_copy_cannot_be_substituted_for_destructor(self):
        s,rows=self.spec();a=next(a for a in s['anchors']if a['address']=='0x006A0880');a['symbol']=linked.COPY
        with self.assertRaises(ValueError):linked.validate_spec(s,rows,s['target_sha256'])

if __name__=='__main__':unittest.main()
