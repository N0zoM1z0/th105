import copy
import hashlib
from pathlib import Path
import struct
import sys
import unittest
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'scripts'))
import linked_pe as core
import linked_cleanup_caller as cleanup
from test_linked_pe import VTablePe


class CleanupCallerTests(unittest.TestCase):
    def fixture(self):
        parent, child, action = 0x10001000, 0x10001100, 0x10001200
        target_parent, target_child, target_action = 0x401000, 0x402000, 0x403000
        owner = '?load@Owner@@QAEXXZ'
        symbol = '??1Buffer@@QAE@XZ'
        action_symbol = '__unwindfunclet$' + owner + '$0'
        def funclet(base, callee):
            return b'\x8d\x45\xf8\xe9' + struct.pack('<i', callee - base - 8)
        source, native = funclet(action, child), funclet(target_action, target_child)
        pe = VTablePe()
        pe.data[0x1000:0x1001] = b'\xc3'
        pe.data[0x1100:0x1101] = b'\xc3'
        pe.data[0x1200:0x1208] = source
        packet = dict(kind='cleanup funclet 0', size=8, source_address=action,
                      target_address=target_action,
                      canonical_sha256=hashlib.sha256(native).hexdigest(),
                      target_sha256=hashlib.sha256(native).hexdigest(),
                      replayed_rel32=[dict(offset=4, symbol=symbol, target=target_child)],
                      data_references=[])
        caller = dict(address='0x00401000', symbol_base=owner,
                      rel32_targets=[symbol + '=0x00402000'],
                      eh_cleanup=dict(handler='0x00404000', info='0x00405000'))
        function = dict(address='0x00402000', symbol_base=symbol,
                        private_from=dict(caller='0x00401000', site='0x00403003',
                                          cleanup=0, through_exact_caller=True))
        unit = dict(kind='linked_candidate', source='src/fixture.cpp',
                    object='build/root.dll', profile=core.PROFILE,
                    link_runtime='static', link_runtime_data=['___security_cookie'],
                    link_data_targets=[], functions=[caller, function])
        target = {target_parent: b'\xc3', target_action: native}
        report = dict(result='exact', address=caller['address'],
                      linked_function_va=f'0x{parent:08X}',
                      source_body_sha256=hashlib.sha256(b'\xc3').hexdigest(),
                      target_sha256=hashlib.sha256(b'\xc3').hexdigest(),
                      object_compared_sha256=hashlib.sha256(b'\xc3').hexdigest(),
                      validated_data_references=[], validated_cleanup_eh=[packet])
        args = dict(function=function, unit=unit, pe=pe,
                    functions={parent: [(owner, 'root.ltcg.obj')],
                               parent+1: [('_after_parent', 'root.ltcg.obj')],
                               child: [(symbol, 'root.ltcg.obj')],
                               child+1: [('_after_child', 'root.ltcg.obj')],
                               action: [(action_symbol, 'CIL library: CIL module')],
                               action+8: [('_after_action', 'root.ltcg.obj')]},
                    exports={owner: parent}, cil_owner='root.ltcg.obj',
                    ledger={caller['address']: dict(status='matching', source_file=unit['source'], size='1')},
                    read_target=lambda a, n: target[a][:n], exact_caller_replay=report)
        return args, target

    def test_actual_exact_cleanup_edge_is_accepted(self):
        args, _target = self.fixture()
        core.validate_contract(args['unit'], set())
        result = core.private_caller_witness(**args)
        self.assertEqual(result['target_site'], '0x00403003')
        self.assertEqual(result['source_site'], '0x10001203')
        self.assertEqual(result['branch'], 'tail')

    def test_cleanup_contract_rejects_loose_or_nonexact_scope(self):
        edits = [
            lambda f: f['private_from'].update(through_exact_caller=False),
            lambda f: f['private_from'].update(cleanup=True),
            lambda f: f['private_from'].update(cleanup=-1),
            lambda f: f['private_from'].update(extra='waive'),
            lambda f: f.update(symbol_base='_free@4'),
        ]
        for edit in edits:
            args, _ = self.fixture()
            edit(args['function'])
            with self.assertRaises(ValueError):
                core.validate_contract(args['unit'], set())

    def test_parent_requires_full_cleanup_and_configured_ancestry(self):
        for change in [lambda p: p.pop('eh_cleanup'),
                       lambda p: p.update(private_from=dict(caller='0x00400000', site='0x00400000'))]:
            args, _ = self.fixture()
            change(args['unit']['functions'][0])
            with self.assertRaises(ValueError):
                core.validate_contract(args['unit'], set())

    def test_missing_or_stale_exact_parent_replay_is_rejected(self):
        for key, value in [('result', 'mismatch'), ('source_body_sha256', 'bad'),
                           ('target_sha256', 'bad'), ('validated_cleanup_eh', [])]:
            args, _ = self.fixture()
            args['exact_caller_replay'][key] = value
            with self.assertRaises(ValueError):
                core.private_caller_witness(**args)

    def test_changed_source_receiver_or_jump_is_rejected(self):
        for offset in [0x1201, 0x1204]:
            args, _ = self.fixture()
            args['pe'].data[offset] ^= 1
            with self.assertRaises(ValueError):
                core.private_caller_witness(**args)

    def test_changed_native_funclet_or_wrong_site_is_rejected(self):
        args, target = self.fixture()
        target[0x403000] = b'\x90' + target[0x403000][1:]
        with self.assertRaises(ValueError):
            core.private_caller_witness(**args)
        args, _ = self.fixture()
        args['function']['private_from']['site'] = '0x00403004'
        with self.assertRaises(ValueError):
            core.private_caller_witness(**args)

    def test_missing_duplicate_or_wrong_callee_packet_is_rejected(self):
        for change in [
            lambda packets: packets.clear(),
            lambda packets: packets.append(copy.deepcopy(packets[0])),
            lambda packets: packets[0]['replayed_rel32'][0].update(target=0x402001),
            lambda packets: packets[0].update(size=7),
        ]:
            args, _ = self.fixture()
            change(args['exact_caller_replay']['validated_cleanup_eh'])
            with self.assertRaises(ValueError):
                core.private_caller_witness(**args)

    def test_exported_cleanup_or_unmapped_destructor_is_rejected(self):
        args, _ = self.fixture()
        name = '__unwindfunclet$?load@Owner@@QAEXXZ$0'
        args['exports'][name] = 0x10001200
        with self.assertRaises(ValueError):
            core.private_caller_witness(**args)
        args, _ = self.fixture()
        args['unit']['functions'][0]['rel32_targets'] = []
        with self.assertRaises(ValueError):
            core.private_caller_witness(**args)


    def offset_fixture(self, wrong_register=False):
        args, target = self.fixture()
        action, child, native_action, native_child = 0x10001200, 0x10001100, 0x403000, 0x402000
        prefix = b'\x8b\x45\x04\x83' + bytes([0xc1 if wrong_register else 0xc0]) + b'\x30\xe9'
        source = prefix + struct.pack('<i', child - action - 11)
        native = prefix + struct.pack('<i', native_child - native_action - 11)
        args['pe'].data[0x1200:0x120b] = source
        args['functions'][action + 11] = args['functions'].pop(action + 8)
        target[native_action] = native
        packet = args['exact_caller_replay']['validated_cleanup_eh'][0]
        packet.update(size=11, canonical_sha256=hashlib.sha256(native).hexdigest(),
                      target_sha256=hashlib.sha256(native).hexdigest())
        packet['replayed_rel32'][0]['offset'] = 7
        args['function']['private_from']['site'] = '0x00403006'
        return args, target

    def test_complete_member_offset_cleanup_is_accepted(self):
        args, _ = self.offset_fixture()
        result = core.private_caller_witness(**args)
        self.assertEqual(result['cleanup_size'], 11)
        self.assertEqual(result['target_site'], '0x00403006')

    def test_matching_but_wrong_offset_register_is_rejected(self):
        args, _ = self.offset_fixture(wrong_register=True)
        with self.assertRaises(ValueError):
            core.private_caller_witness(**args)

    def test_private_exact_parent_retains_its_independent_entry_proof(self):
        args, _ = self.fixture()
        parent = args['unit']['functions'][0]
        old = parent['symbol_base']
        name = '??1Owner@@QAE@XZ'
        parent['symbol_base'] = name
        parent['private_from'] = dict(caller='0x00400000', site='0x00400000')
        args['functions'][0x10001000] = [(name, 'root.ltcg.obj')]
        args['functions'][0x10001200] = [
            ('__unwindfunclet$' + name + '$0', 'CIL library: CIL module')]
        args['exports'].pop(old)
        # A real direct caller is configured; the fresh exact parent report
        # must retain its separately established source/native entry witness.
        root = dict(address='0x00400000', symbol_base='_release@4',
                    rel32_targets=[name + '=0x00401000'])
        args['unit']['functions'].insert(0, root)
        core.validate_contract(args['unit'], set())
        with self.assertRaises(ValueError):
            core.private_caller_witness(**args)
        witness = dict(caller=root['address'], target_site='0x00400000',
                       source_site='0x10001300')
        args['exact_caller_replay']['private_caller_witness'] = witness
        result = core.private_caller_witness(**args)
        self.assertEqual(result['exact_caller']['private_caller_witness'], witness)
        parent['private_from']['through_exact_caller'] = True
        with self.assertRaises(ValueError):
            cleanup.validate(args['function']['private_from'], args['function'], args['unit'])


if __name__ == '__main__':
    unittest.main()
