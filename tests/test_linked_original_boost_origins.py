import copy
import hashlib
from pathlib import Path
import sys
import tempfile
from types import SimpleNamespace
import unittest
from unittest.mock import patch
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
import original_boost_link as original
import linked_original_boost_origins as linked
import upstream_boost as base

class OriginalBoostLinkTests(unittest.TestCase):
    def test_graph_contains_only_verified_vendor_units(self):
        units=original.source_units();self.assertEqual(len(units),len(original.extra.PROBES)+1)
        self.assertEqual(len({u['source']for u in units}),len(units))
        for u in units:base.validate(u)
    def test_only_real_public_constructor_is_exported(self):
        flags=original.link_flags();self.assertEqual([f for f in flags if f.startswith('/EXPORT:')],['/EXPORT:'+original.PUBLIC_ROOT])
        self.assertFalse(any(f.startswith(('/FORCE','/INCLUDE:'))for f in flags));self.assertIn('/NODEFAULTLIB',flags)
    def test_extra_instance_macro_is_rejected(self):
        with tempfile.TemporaryDirectory()as tmp:
            root=Path(tmp);p=root/base.RELEASE_INSTANCE_PROBE;p.parent.mkdir(parents=True);p.write_text('#define NDEBUG\n#include "../../'+base.INSTANCE_PATH+'"\n#define EXTRA_POLICY\n')
            with self.assertRaisesRegex(ValueError,'wrapper'):original.verified_inputs(root)
    def test_original_user32_pin_required(self):
        with patch.object(original.core,'sha',return_value='wrong'):
            with self.assertRaises(ValueError):original.library_paths(Path('/synthetic-tools'))
    def fixture(self):
        src=0x10002000;helper=0x10003000;root=0x10001000
        functions={src:[(linked.SYMBOL,'i original-0.obj')],helper:[('__invalid_parameter_noinfo','libcmt:invarg.obj')],helper-36:[('__invalid_parameter','libcmt:invarg.obj')],root:[(original.PUBLIC_ROOT,'i original-0.obj')]}
        pe=SimpleNamespace(FILE_HEADER=SimpleNamespace(Machine=0x14c),OPTIONAL_HEADER=SimpleNamespace(ImageBase=0x10000000,SizeOfImage=0x10000),DIRECTORY_ENTRY_EXPORT=SimpleNamespace(symbols=[SimpleNamespace(name=original.PUBLIC_ROOT.encode(),address=0x1000)]))
        raw=b's'*67;crt=b'c'*16;anchor=dict(address='0x0040DBF0',size=67,symbol=linked.SYMBOL,sha256=hashlib.sha256(raw).hexdigest());rows=[dict(address=anchor['address'],size='67')]
        return pe,functions,anchor,rows,raw,crt
    def run_qualify(self,pe,fs,a,rows,raw,crt,canonical=None,calls=None):
        if canonical is None:canonical=raw
        if calls is None:calls=[dict(offset=x)for x in (17,41,54)]
        ins=SimpleNamespace(operands=[])
        with patch.object(linked,'INVALID_SHA',hashlib.sha256(crt).hexdigest()),patch.object(linked.core,'linked_body',side_effect=lambda pe,fs,at:crt if at==0x10003000 else raw),patch.object(linked.core,'decode_closed_body',return_value=[ins]),patch.object(linked.core,'validate_body_relocations'),patch.object(linked.core,'canonicalize',return_value=(canonical,calls,[])):
            return linked.qualify(pe,fs,a,rows,lambda at,n:crt if at==linked.INVALID else b's'*n)
    def test_whole_body_contract_orchestration(self):
        args=self.fixture();r=self.run_qualify(*args);self.assertEqual(r['inventory_hits'],['0x0040DBF0'])
    def test_wrong_source_or_crt_owner_rejected(self):
        for source in (True,False):
            pe,fs,a,rows,raw,crt=self.fixture();key=0x10002000 if source else 0x10003000;fs[key]=[(fs[key][0][0],'unreviewed.obj')]
            with self.assertRaises(ValueError):self.run_qualify(pe,fs,a,rows,raw,crt)
    def test_helper_export_is_not_allowed(self):
        pe,fs,a,rows,raw,crt=self.fixture();pe.DIRECTORY_ENTRY_EXPORT.symbols.append(SimpleNamespace(name=linked.SYMBOL.encode(),address=0x2000))
        with self.assertRaisesRegex(ValueError,'exported'):self.run_qualify(pe,fs,a,rows,raw,crt)
    def test_extra_call_or_noncall_change_rejected(self):
        pe,fs,a,rows,raw,crt=self.fixture()
        with self.assertRaises(ValueError):self.run_qualify(pe,fs,a,rows,raw,crt,calls=[dict(offset=x)for x in (17,41,54,60)])
        with self.assertRaisesRegex(ValueError,'non-call'):self.run_qualify(pe,fs,a,rows,b't'+raw[1:],crt,canonical=raw)
    def test_inventory_alias_is_not_accepted_as_unique(self):
        pe,fs,a,rows,raw,crt=self.fixture();rows.append(dict(address='0x00401000',size='67'))
        with self.assertRaisesRegex(ValueError,'inventory-unique'):self.run_qualify(pe,fs,a,rows,raw,crt)
    def test_wrong_architecture_rejected(self):
        pe,fs,a,rows,raw,crt=self.fixture();pe.FILE_HEADER.Machine=0x8664
        with self.assertRaisesRegex(ValueError,'architecture'):self.run_qualify(pe,fs,a,rows,raw,crt)
