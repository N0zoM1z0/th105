"""Fail-closed complete compact-switch envelopes, without native toolchains."""
import copy
import hashlib
import json
from pathlib import Path
import struct
import sys
import types
import unittest
from unittest import mock

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'scripts'))
import coff_switch_payload as payload
import build


def fixture(spill=False, compare=b'\x83\xf8\x01', default_code=b'\x31\xc0\xc3'):
    address = 0x401000
    middle = bytes.fromhex('885c2416') if spill else b''
    load = len(compare) + len(middle) + 2
    jump = load + 7
    case0, case1, default = jump + 7, jump + 10, jump + 16
    code_size = default + len(default_code)
    table, index = code_size + 1, code_size + 9
    body = (compare + middle + b'\x77' + bytes([default - load])
            + b'\x0f\xb6\x90' + struct.pack('<I', address + index)
            + b'\xff\x24\x95' + struct.pack('<I', address + table)
            + b'\x31\xc0\xc3' + b'\xb8\x01\x00\x00\x00\xc3'
            + default_code + b'\x90'
            + struct.pack('<II', address + case0, address + case1) + b'\x00\x01')
    contract = dict(size=len(body), sha256=hashlib.sha256(body).hexdigest(),
                    alignment_hex='90', table_offset=table, table_entries=2,
                    map_offset=index, map_size=2, load_offset=load, jump_offset=jump)
    relocations = [(load + 3, 6, '$MAP'), (jump + 3, 6, '$TABLE'),
                   (table, 6, '$CASE0'), (table + 4, 6, '$CASE1')]
    return body, address, code_size, contract, relocations


def changed(raw, contract, offset, value):
    raw = bytearray(raw)
    raw[offset:offset + len(value)] = value
    raw = bytes(raw)
    contract = dict(contract, sha256=hashlib.sha256(raw).hexdigest())
    return raw, contract


class CompactSwitchTests(unittest.TestCase):
    def test_entire_payload_and_optional_flags_preserving_spill(self):
        for spill in (False, True):
            b, a, n, c, r = fixture(spill)
            out = payload.inspect(b, b, a, n, c, r)
            self.assertEqual(out['reachable_code_bytes'], n)
            self.assertEqual(out['payload_size'], len(b))
            self.assertEqual(out['canonical_payload_sha256'], out['target_payload_sha256'])

    def test_contract_fields_types_and_partition_are_exact(self):
        b, a, n, c, r = fixture()
        for patch in ({'extra': 1}, {'size': True}, {'table_offset': c['table_offset'] + 1},
                      {'map_offset': c['map_offset'] - 1}, {'map_size': 0},
                      {'table_entries': 257}, {'sha256': 'x' * 64}, {'alignment_hex': '00'}):
            with self.subTest(patch=patch), self.assertRaises(ValueError):
                payload.validate_contract(dict(c, **patch), n)

    def test_hash_and_every_payload_byte_and_length_are_required(self):
        b, a, n, c, r = fixture()
        for source, target, contract in [(b[:-1], b, c), (b + b'\xcc', b, c),
                (b, b[:-1], c), (b[:-1] + b'\x00', b, c),
                (b, b, dict(c, sha256='0' * 64))]:
            with self.assertRaises(ValueError):
                payload.inspect(source, target, a, n, contract, r)

    def test_jump_words_and_indices_must_own_all_valid_cases(self):
        b, a, n, c, r = fixture()
        patches = [(c['map_offset'], b'\x02'), (c['map_offset'], b'\x01'),
                   (c['table_offset'], struct.pack('<I', a + n)),
                   (c['table_offset'], struct.pack('<I', a + c['jump_offset'])),
                   (c['table_offset'], struct.pack('<I', a + 1)),
                   (c['table_offset'] + 4, b[c['table_offset']:c['table_offset'] + 4])]
        for at, value in patches:
            raw, contract = changed(b, c, at, value)
            with self.subTest(offset=at), self.assertRaises(ValueError):
                payload.inspect(raw, raw, a, n, contract, r)

    def test_unsigned_guard_index_and_direct_metadata_operands_are_required(self):
        b, a, n, c, r = fixture()
        patches = [(2, b'\x02'), (3, b'\x75'),
                   (c['load_offset'] + 3, struct.pack('<I', a + c['map_offset'] + 1)),
                   (c['jump_offset'] + 2, b'\x85'),
                   (c['jump_offset'] + 3, struct.pack('<I', a + c['table_offset'] + 4))]
        for at, value in patches:
            raw, contract = changed(b, c, at, value)
            with self.subTest(offset=at), self.assertRaises(ValueError):
                payload.inspect(raw, raw, a, n, contract, r)

    def test_scheduled_integer_stack_spill_must_be_one_byte(self):
        b, a, n, c, r = fixture(True)
        for at, value in [(3, b'\x80'), (4, b'\x5d'), (3, b'\x89'), (6, b'\xff')]:
            raw, contract = changed(b, c, at, value)
            with self.subTest(offset=at), self.assertRaises(ValueError):
                payload.inspect(raw, raw, a, n, contract, r)

    def test_register_bound_must_be_constant_on_every_incoming_path(self):
        compare = b'\x90' * 8 + bytes.fromhex('bb01000000 90909090 3bc3')
        body, address, size, contract, relocs = fixture(compare=compare)
        payload.inspect(body, body, address, size, contract, relocs)
        patches = ((9, b'\x02', 'reaching constant'),
                   (13, b'\xb3\x00', 'reaching constant'),
                   (0, b'\x75\x0b', 'branch escapes code or bypasses'),
                   (0, b'\xe8\x08\x00\x00\x00', 'call bypasses'))
        for offset, value, message in patches:
            raw, updated_contract = changed(body, contract, offset, value)
            with self.subTest(value=value), self.assertRaisesRegex(ValueError, message):
                payload.inspect(raw, raw, address, size, updated_contract, relocs)

    def test_scheduled_fstp_requires_a_dword_stack_slot(self):
        body, address, size, contract, relocs = fixture(spill=True)
        raw, updated_contract = changed(body, contract, 3, bytes.fromhex('d95c2428'))
        payload.inspect(raw, raw, address, size, updated_contract, relocs)
        for spill in ('dd5c2428', 'd95c24fc'):
            raw, updated_contract = changed(body, contract, 3, bytes.fromhex(spill))
            with self.subTest(spill=spill), self.assertRaisesRegex(ValueError, 'unsupported instruction'):
                payload.inspect(raw, raw, address, size, updated_contract, relocs)

    def test_scheduled_edi_save_and_constant_keep_the_selector(self):
        compare = bytes.fromhex('9090 83f801 57 bf01000000')
        body, address, size, contract, relocs = fixture(compare=compare)
        payload.inspect(body, body, address, size, contract, relocs)

        for offset, replacement in ((5, b'\x50'), (6, b'\xb8'), (7, b'\x02')):
            raw, updated = changed(body, contract, offset, replacement)
            with self.subTest(offset=offset), self.assertRaisesRegex(ValueError, 'unsupported instruction'):
                payload.inspect(raw, raw, address, size, updated, relocs)

    def test_scheduled_edi_five_and_lea_ebp_preserve_flags(self):
        # cmp eax, 1; mov edi, 5; lea ebp, [edi + 0x73]
        compare = bytes.fromhex('83f801 bf05000000 8d6f73')
        body, address, size, contract, relocs = fixture(compare=compare)
        payload.inspect(body, body, address, size, contract, relocs)
        # Clobbering selector eax with lea eax, [edi + 0x73] must fail.
        bad, updated = changed(body, contract, 8, bytes.fromhex('8d4773'))
        with self.assertRaisesRegex(ValueError, 'unsupported instruction'):
            payload.inspect(bad, bad, address, size, updated, relocs)

    def test_cfg_register_bound_across_early_return_and_negative_clobber(self):
        # 3x nop; mov ebp, 1; test eax, eax; jne +1; ret; cmp eax, ebp; ja default; ...
        compare = bytes.fromhex('909090 bd01000000 85c0 7501 c3 3bc5')
        body, address, size, contract, relocs = fixture(compare=compare)
        payload.inspect(body, body, address, size, contract, relocs)
        # Wrong constant (mov ebp, 2) must fail.
        wrong, updated = changed(body, contract, 4, b'\x02')
        with self.assertRaisesRegex(ValueError, 'reaching constant'):
            payload.inspect(wrong, wrong, address, size, updated, relocs)
        # Path bypassing mov ebp, 1 must fail.
        bypass_compare = bytes.fromhex('90 85c0 7405 bd01000000 7501 c3 3bc5')
        b2, a2, s2, c2, r2 = fixture(compare=bypass_compare)
        with self.assertRaisesRegex(ValueError, 'reaching constant'):
            payload.inspect(b2, b2, a2, s2, c2, r2)

    def test_local_relocations_cannot_be_missing_duplicated_or_added_to_map(self):
        b, a, n, c, r = fixture()
        bad = [r[:-1], r + [r[-1]], r + [(c['map_offset'], 6, '$FAKE')],
               [(o, 20 if o == c['table_offset'] else k, s) for o, k, s in r],
               [(o, k, 'external' if o == c['table_offset'] else s) for o, k, s in r],
               r[1:], [(o, k, 'external' if o == c['load_offset'] + 3 else s) for o, k, s in r]]
        for relocs in bad:
            with self.assertRaises(ValueError):
                payload.inspect(b, b, a, n, c, relocs)

    def test_additional_indirect_branch_is_not_a_switch_waiver(self):
        b, a, n, c, r = fixture()
        case1 = c['jump_offset'] + 10
        raw, contract = changed(b, c, case1, b'\xff\xe0\x90\x90\x90\xc3')
        with self.assertRaises(ValueError):
            payload.inspect(raw, raw, a, n, contract, r)

    def test_virtual_tail_needs_a_slot_load_and_frame_restore(self):
        vtail = bytes.fromhex('8b068b50145f8bce5e5b83c404ffe2')
        body, address, size, contract, relocs = fixture(default_code=vtail)
        without_tail = contract
        contract = dict(contract, virtual_tail_jumps=[size - 2])
        self.assertEqual(payload.inspect(body, body, address, size, contract, relocs)
                         ['reachable_code_bytes'], size)
        with self.assertRaises(ValueError):
            payload.inspect(body, body, address, size, without_tail, relocs)

        start = size - len(vtail)
        for at, replacement in ((start + 3, b'\x51'), (start + 5, b'\x90'),
                                (size - 1, b'\xe0')):
            wrong, rebound = changed(body, contract, at, replacement)
            with self.subTest(offset=at), self.assertRaisesRegex(ValueError, 'virtual tail'):
                payload.inspect(wrong, wrong, address, size, rebound, relocs)
        wrong, rebound = changed(body, contract, 4, bytes([start + 2 - 5]))
        with self.assertRaisesRegex(ValueError, 'branch escapes code or bypasses'):
            payload.inspect(wrong, wrong, address, size, rebound, relocs)

    def test_two_tables_and_an_explicit_external_tail(self):
        address, external = 0x401000, 0x402000
        first = dict(alignment_hex='', table_offset=48, table_entries=2,
                     map_offset=56, map_size=2, load_offset=5, jump_offset=12)
        second = dict(alignment_hex='8bff', table_offset=60, table_entries=2,
                      map_offset=68, map_size=2, load_offset=24, jump_offset=31)
        code = (bytes.fromhex('83f801770e0fb690') + struct.pack('<I', address + 56)
                + bytes.fromhex('ff2495') + struct.pack('<I', address + 48)
                + bytes.fromhex('83f90177120fb681') + struct.pack('<I', address + 68)
                + bytes.fromhex('ff2485') + struct.pack('<I', address + 60)
                + bytes.fromhex('c333c0c3e9') + struct.pack('<i', external - address - 47)
                + b'\xc3')
        body = (code + struct.pack('<II', address + 38, address + 39) + b'\x00\x01'
                + bytes.fromhex('8bff') + struct.pack('<II', address + 42, address + 47)
                + b'\x00\x01')
        contract = dict(first, size=len(body), sha256=hashlib.sha256(body).hexdigest(),
                        additional_tables=[second], tail_jumps=[42])
        relocations = [(at, 6, '$SWITCH') for at in (8, 15, 27, 34, 48, 52, 60, 64)]
        relocations.append((43, 20, 'tail'))
        bindings = {'tail': external}
        report = payload.inspect(body, body, address, len(code), contract, relocations, bindings)
        self.assertEqual((report['switch_tables'], report['table_entries']), (2, 4))

        for at in (56, 68):
            modified, _ = changed(body, contract, at, b'\x01')
            with self.subTest(map_offset=at), self.assertRaisesRegex(ValueError, f'{address + at:#010x}'):
                payload.inspect(modified, body, address, len(code), contract, relocations, bindings)
        with self.assertRaisesRegex(ValueError, 'external REL32 binding'):
            payload.inspect(body, body, address, len(code), contract, relocations)
        missing = [r for r in relocations if r[0] != 60]
        with self.assertRaisesRegex(ValueError, 'local DIR32 jump word'):
            payload.inspect(body, body, address, len(code), contract, missing, bindings)

    def test_dense_table_requires_instruction_targets_and_reviewed_alignment(self):
        address = 0x401000
        code = (bytes.fromhex('83f801770bff2485') + struct.pack('<I', address + 20)
                + bytes.fromhex('c38d4900c3'))
        body = code + bytes.fromhex('8d4900') + struct.pack('<II', address + 12, address + 16)
        contract = dict(size=len(body), sha256=hashlib.sha256(body).hexdigest(),
                        alignment_hex='8d4900', table_offset=20, table_entries=2, jump_offset=5)
        relocations = [(at, 6, '$TABLE') for at in (8, 20, 24)]
        report = payload.inspect(body, body, address, len(code), contract, relocations)
        self.assertEqual(report['internal_alignment'], [(13, 16)])
        self.assertEqual(report['index_bytes'], 0)
        for offset, replacement in ((13, bytes.fromhex('939090')), (24, struct.pack('<I', address + 14))):
            modified, modified_contract = changed(body, contract, offset, replacement)
            with self.subTest(offset=offset), self.assertRaises(ValueError):
                payload.inspect(modified, modified, address, len(code), modified_contract, relocations)

    def test_build_comparison_fails_closed_on_payload_failure(self):
        unit = dict(kind='probe', object='build/fixture-switch.obj', functions=[
            dict(address='0x00401000', symbol_base='fixture', switch_payload={})])
        completed = types.SimpleNamespace(returncode=0, stdout=json.dumps({'result': 'exact'}), stderr='')
        with mock.patch.object(build.subprocess, 'run', return_value=completed), \
                mock.patch.object(payload, 'verify', side_effect=ValueError('bad complete payload')) as verify:
            code, reports = build.compare_unit(unit, True)
        verify.assert_called_once()
        self.assertEqual(code, 1)
        self.assertEqual(reports[0]['result'], 'blocked')
        self.assertEqual(reports[0]['failure']['category'], 'comparison.switch_payload')

    def test_text_mode_cannot_report_a_prefix_as_complete(self):
        unit = dict(kind='probe', object='build/fixture-switch.obj', functions=[
            dict(address='0x00401000', symbol_base='fixture', switch_payload={})])
        completed = types.SimpleNamespace(returncode=0, stdout=json.dumps({'result': 'exact'}), stderr='')
        with mock.patch.object(build.subprocess, 'run', return_value=completed), \
                mock.patch.object(payload, 'verify', side_effect=ValueError('metadata differs')), \
                mock.patch('builtins.print') as output:
            code, reports = build.compare_unit(unit, False)
        self.assertEqual((code, reports), (1, []))
        self.assertIn('blocked', output.call_args.args[0])

    def test_prefix_mismatch_is_not_overridden_by_metadata(self):
        unit = dict(kind='probe', object='build/fixture-switch.obj', functions=[
            dict(address='0x00401000', symbol_base='fixture', switch_payload={})])
        completed = types.SimpleNamespace(returncode=1, stdout=json.dumps({'result': 'mismatch'}), stderr='')
        with mock.patch.object(build.subprocess, 'run', return_value=completed), \
                mock.patch.object(payload, 'verify') as verify:
            code, reports = build.compare_unit(unit, True)
        verify.assert_not_called()
        self.assertEqual(code, 1)
        self.assertEqual(reports[0]['result'], 'mismatch')

    def test_build_comparison_retains_successful_full_payload_proof(self):
        unit = dict(kind='probe', object='build/fixture-switch.obj', functions=[
            dict(address='0x00401000', symbol_base='fixture', switch_payload={})])
        completed = types.SimpleNamespace(returncode=0, stdout=json.dumps({'result': 'exact'}), stderr='')
        proof = {'canonical_payload_sha256': 'a' * 64, 'payload_size': 42}
        with mock.patch.object(build.subprocess, 'run', return_value=completed), \
                mock.patch.object(payload, 'verify', return_value=proof):
            code, reports = build.compare_unit(unit, True)
        self.assertEqual(code, 0)
        self.assertEqual(reports[0]['validated_switch_payload'], proof)


if __name__ == '__main__':
    unittest.main()
