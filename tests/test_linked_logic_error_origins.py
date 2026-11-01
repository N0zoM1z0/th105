import copy
from pathlib import Path
import struct
import sys
import tomllib
from types import SimpleNamespace
import unittest
from unittest.mock import patch
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
import linked_logic_error_origins as linked

class LinkedLogicErrorTests(unittest.TestCase):
    def spec(self):
        spec=tomllib.loads(linked.ANCHORS.read_text())
        return spec,[dict(address=a['address'],size=str(a['size']))for a in spec['anchors']]
    def test_both_typed_roots_required(self):
        s,rows=self.spec();self.assertEqual(len(linked.validate_spec(s,rows,s['target_sha256'])),2)
        with self.assertRaises(ValueError):linked.validate_spec(s,rows[:1],s['target_sha256'])
    def test_runtime_error_shape_not_accepted(self):
        s,rows=self.spec();s['anchors'][0]['symbol']=s['anchors'][0]['symbol'].replace('logic_error','runtime_error')
        with self.assertRaises(ValueError):linked.validate_spec(s,rows,s['target_sha256'])
    def test_partial_extent_or_mask_not_accepted(self):
        for change in ('size','mask'):
            s,rows=self.spec()
            if change=='size':s['anchors'][0]['size']-=1
            else:s['anchors'][0]['mask']=[3]
            with self.assertRaises(ValueError):linked.validate_spec(s,rows,s['target_sha256'])
    def test_hash_or_target_mismatch_rejected(self):
        s,rows=self.spec()
        with self.assertRaises(ValueError):linked.validate_spec(s,rows,'wrong')
        s['anchors'][0]['handler_sha256']='not-a-digest'
        with self.assertRaises(ValueError):linked.validate_spec(s,rows,s['target_sha256'])
    def metadata(self):
        info=lambda p:struct.pack('<9I',0x19930522,1,p,0,0,0,0,0,1)
        unwind=lambda p:struct.pack('<2I',0xffffffff,p)
        return [info(0x10003000),info(0x6e3fb0),unwind(0x10004000),unwind(0x6bd950)]
    def test_all_eh_metadata_bytes_are_compared(self):
        args=self.metadata();out=linked.canonical_metadata(*args);self.assertEqual(out['metadata_bytes'],44)
        for idx in (0,1):
            for field in (0,1,3,4,5,6,7,8):
                bad=args.copy();v=bytearray(bad[idx]);v[field*4]^=1;bad[idx]=bytes(v)
                with self.assertRaises(ValueError):linked.canonical_metadata(*bad)
    def test_bad_unwind_state_is_rejected(self):
        args=self.metadata()
        for idx in (2,3):
            bad=args.copy();v=bytearray(bad[idx]);v[0]^=1;bad[idx]=bytes(v)
            with self.assertRaises(ValueError):linked.canonical_metadata(*bad)
    def test_only_named_original_owner_is_accepted(self):
        n='some-function';self.assertEqual(linked.named({n:[(123,'f   libcmt:stdexcpt.obj')]},n,'libcmt:stdexcpt.obj'),123)
        for rows in ([],[(123,'fake.obj')],[(123,'libcmt:stdexcpt.obj'),(124,'libcmt:stdexcpt.obj')]):
            with self.assertRaises(ValueError):linked.named({n:rows},n,'libcmt:stdexcpt.obj')
    def context(self):
        pe=SimpleNamespace(FILE_HEADER=SimpleNamespace(Machine=0x14c),
            OPTIONAL_HEADER=SimpleNamespace(ImageBase=0x10000000,SizeOfImage=0x30000),
            DIRECTORY_ENTRY_EXPORT=SimpleNamespace(symbols=[SimpleNamespace(name=linked.original.PUBLIC_ROOT.encode())]),
            get_data=lambda a,n:b'c'*n)
        symbols={n:[(0x10001000+i*32,'f '+owner)]for i,(n,(_,owner,_))in enumerate(linked.CALLEES.items())}
        symbols.update({'??_7logic_error@std@@6B@':[(0x10002000,'libcpmt:string.obj')],
                        '___security_cookie':[(0x10020040,'libcmt:gs_cookie.obj')]})
        origins={f'0x{a:08X}':dict(evidence_id=e,disposition='exclude')for a,o,e in linked.CALLEES.values()}
        return pe,symbols,origins
    def test_context_needs_independent_callee_proofs(self):
        pe,symbols,origins=self.context();origins['0x004020D0']['disposition']='review'
        with self.assertRaisesRegex(ValueError,'independent'):linked.source_context(pe,symbols,origins,lambda a,n:b'c'*n)
    def test_actual_class_rtti_is_not_optional(self):
        args=self.context()
        with patch.object(linked,'rtti',return_value=(0,0,0,b'.?AVruntime_error@std@@')):
            with self.assertRaisesRegex(ValueError,'actual class'):linked.source_context(*args,lambda a,n:b'c'*n)
    def test_unreviewed_export_is_rejected(self):
        pe,symbols,origins=self.context();pe.DIRECTORY_ENTRY_EXPORT.symbols.append(SimpleNamespace(name=b'fake'))
        with self.assertRaisesRegex(ValueError,'export'):linked.source_context(pe,symbols,origins,lambda a,n:b'c'*n)
    def test_actual_cookie_initialization_is_checked(self):
        args=self.context()
        with patch.object(linked,'rtti',return_value=(0,0,0,b'.?AVlogic_error@std@@')):
            with self.assertRaisesRegex(ValueError,'cookie'):linked.source_context(*args,lambda a,n:b'x'*n)
    def test_original_source_context(self):
        args=self.context()
        with patch.object(linked,'rtti',return_value=(0,0,0,b'.?AVlogic_error@std@@')):
            calls,vt,cookie=linked.source_context(*args,lambda a,n:b'c'*n)
            self.assertEqual(len(calls),6);self.assertEqual(cookie,0x10020040)

if __name__=='__main__':unittest.main()
