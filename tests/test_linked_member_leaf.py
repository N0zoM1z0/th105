"""A private member is not accepted from a cached shape or caller-byte waiver."""
import copy
from pathlib import Path
import struct
import sys
from types import SimpleNamespace
import unittest
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'scripts'))
import linked_pe as core
import linked_member_leaf as leaf
from test_linked_pe import VTablePe


class MemberLeafTests(unittest.TestCase):
    def fixture(self, body=bytes.fromhex('51837e040074058b460459c333c059c3')):
        parent, child = 0x10001000, 0x10001100
        tp, tc = 0x401000, 0x402000
        owner, symbol = '?update@Owner@@QAE_NXZ', '?stop@Buffer@@QAEJXZ'
        def caller(a, b):
            return bytes.fromhex('8d7724e8') + struct.pack('<i', b-a-8) + b'\xc3'
        pe = VTablePe()
        pe.data[0x1000:0x1009] = caller(parent, child)
        pe.data[0x1100:0x1100+len(body)] = body
        target = {tp: caller(tp, tc), tc: body}
        cf = dict(address='0x00401000', symbol_base=owner,
                  rel32_targets=[symbol+'=0x00402000'])
        f = dict(address='0x00402000', symbol_base=symbol,
                 private_from=dict(caller='0x00401000', site='0x00401003',
                                   relocation_free_member=True))
        unit = dict(kind='linked_candidate', source='src/fixture.cpp',
                    object='build/root.dll', profile=core.PROFILE,
                    link_data_targets=[], functions=[cf, f])
        args = dict(function=f, unit=unit, pe=pe,
                    functions={parent: [(owner, 'root.ltcg.obj')],
                               parent+9: [('_after_parent', 'root.ltcg.obj')],
                               child: [(symbol, 'root.ltcg.obj')],
                               child+len(body): [('_after_child', 'root.ltcg.obj')]},
                    exports={owner: parent}, cil_owner='root.ltcg.obj',
                    ledger={cf['address']: dict(status='implemented', source_file=unit['source'], size='9'),
                            f['address']: dict(status='unclassified', size=str(len(body)))},
                    read_target=lambda a, n: target[a][:n])
        return args, target

    def test_complete_raw_member_and_actual_subobject_are_required(self):
        args, _ = self.fixture()
        core.validate_contract(args['unit'], set())
        r = core.private_caller_witness(**args)['relocation_free_member']
        self.assertEqual(r['size'], 16)
        self.assertEqual(r['receiver_register'], 'esi')
        self.assertEqual(r['owner_register'], 'edi')
        self.assertEqual(r['offset'], 36)
        self.assertEqual(r['absolute_relocations'], 0)
        self.assertEqual(r['source_sha256'], r['target_sha256'])

    def test_canonicalizer_cannot_add_even_attested_address_references(self):
        leaf.validate_canonical_identity(b'abc',b'abc',[],[])
        for raw,canonical,calls,refs in [(b'abc',b'abd',[],[]),
                (b'abc',b'abc',[{'target':0x401000}],[]),
                (b'abc',b'abc',[],[{'kind':'binding','address':0x703864}])]:
            with self.assertRaises(ValueError):
                leaf.validate_canonical_identity(raw,canonical,calls,refs)

    def test_old_source_only_rule_is_not_relaxed(self):
        args, _ = self.fixture()
        edge = args['function']['private_from']
        del edge['relocation_free_member']
        edge['source_only_caller'] = True
        with self.assertRaisesRegex(ValueError, 'source-only caller requires'):
            core.validate_contract(args['unit'], set())

    def test_contract_rejects_loose_abi_and_extra_paths(self):
        changes = [lambda f: f['private_from'].update(relocation_free_member=1),
                   lambda f: f['private_from'].update(source_only_caller=True),
                   lambda f: f.update(symbol_base='?stop@Buffer@@QAEJH@Z'),
                   lambda f: f.update(symbol_base='_stop@4'),
                   lambda f: f.update(symbol_base='?stop@Buffer@@QAEIXZ'),
                   lambda f: f.update(eh_cleanup={}),
                   lambda f: f.update(alignment_sites=[]),
                   lambda f: f.update(export_name='export_stop')]
        for change in changes:
            args, _ = self.fixture();change(args['function'])
            with self.assertRaises(ValueError):core.validate_contract(args['unit'], set())

    def test_parent_must_be_a_distinct_exported_source_owner(self):
        for change in (lambda p: p.update(private_from=dict(caller='0x00405000',site='0x00405010')),
                       lambda p: p.update(private_global={})):
            args, _ = self.fixture();change(args['unit']['functions'][0])
            with self.assertRaises(ValueError):core.validate_contract(args['unit'], set())
        args, _ = self.fixture();args['ledger']['0x00401000']['source_file']='src/other.cpp'
        with self.assertRaises(ValueError):core.private_caller_witness(**args)

    def test_whole_body_not_matching_prefix(self):
        for mutate in (lambda b: b[:-1]+b'\x90', lambda b: b[:-1]):
            args, target = self.fixture();target[0x402000]=mutate(target[0x402000])
            with self.assertRaisesRegex(ValueError,'whole unmasked'):core.private_caller_witness(**args)

    def test_leaf_pe_relocations_are_not_masked(self):
        args, _ = self.fixture()
        args['pe'].DIRECTORY_ENTRY_BASERELOC=[SimpleNamespace(entries=[SimpleNamespace(type=3,rva=0x1108)])]
        with self.assertRaises(ValueError):core.private_caller_witness(**args)

    def test_both_call_sites_must_supply_same_adjacent_subobject(self):
        for value in (0x28, 0, 0x25):
            args, target = self.fixture();b=bytearray(target[0x401000]);b[2]=value;target[0x401000]=bytes(b)
            with self.assertRaises(ValueError):core.private_caller_witness(**args)
        args,target=self.fixture();target[0x401000]=b'\x90\x90\x90'+target[0x401000][3:]
        with self.assertRaises(ValueError):core.private_caller_witness(**args)

    def test_rejects_absolute_access_and_direct_call_even_when_bytes_equal(self):
        bodies=[bytes.fromhex('a100204000')+b'\x90'*10+b'\xc3',
                bytes.fromhex('e800100000')+b'\x90'*10+b'\xc3']
        for body in bodies:
            args,_=self.fixture(body)
            with self.assertRaises(ValueError):core.private_caller_witness(**args)

    def test_receiver_must_be_accessed_and_not_rewritten(self):
        for body in (b'\x90'*15+b'\xc3',bytes.fromhex('8bf78b4604')+b'\x90'*10+b'\xc3'):
            args,_=self.fixture(body)
            with self.assertRaises(ValueError):core.private_caller_witness(**args)

    def test_partial_receiver_register_write_is_rejected(self):
        body=bytes.fromhex('668bf78b4604')+b'\x90'*9+b'\xc3'
        args,_=self.fixture(body)
        with self.assertRaisesRegex(ValueError,'instance register'):
            core.private_caller_witness(**args)

    def test_branch_cannot_bypass_adjacent_subobject_lea(self):
        body=bytes.fromhex('85c075038d7724e800010000c3')
        rows=core.decode_closed_body(body,0x401000)
        with self.assertRaisesRegex(ValueError,'bypasses'):
            leaf.subobject_lea(rows,0x401007)

    def test_nonzero_return_cleanup_and_external_tails_rejected(self):
        for body in (bytes.fromhex('8b4604')+b'\x90'*10+bytes.fromhex('c20400'),
                     bytes.fromhex('8b4604')+b'\x90'*11+bytes.fromhex('ffe0')):
            args,_=self.fixture(body)
            with self.assertRaises(ValueError):core.private_caller_witness(**args)

    def test_aliased_or_exported_private_leaf_rejected(self):
        args,_=self.fixture();args['functions'][0x10001100].append(('?alias@Buffer@@QAEJXZ','root.ltcg.obj'))
        with self.assertRaises(ValueError):core.private_caller_witness(**args)
        args,_=self.fixture();args['exports'][args['function']['symbol_base']]=0x10001100
        with self.assertRaises(ValueError):core.private_caller_witness(**args)

    def test_missing_real_caller_mapping_rejected(self):
        args,_=self.fixture();args['unit']['functions'][0]['rel32_targets']=[]
        with self.assertRaises(ValueError):core.private_caller_witness(**args)


if __name__ == '__main__':unittest.main()
