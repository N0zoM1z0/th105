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


def fixture(spill=False):
    address = 0x401000
    middle = bytes.fromhex('885c2416') if spill else b''
    load = 5 + len(middle)
    jump = load + 7
    case0, case1, default = jump + 7, jump + 10, jump + 16
    code_size = default + 3
    table, index = code_size + 1, code_size + 9
    body = (b'\x83\xf8\x01' + middle + b'\x77' + bytes([default - load])
            + b'\x0f\xb6\x90' + struct.pack('<I', address + index)
            + b'\xff\x24\x95' + struct.pack('<I', address + table)
            + b'\x31\xc0\xc3' + b'\xb8\x01\x00\x00\x00\xc3'
            + b'\x31\xc0\xc3' + b'\x90'
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

    def test_only_one_byte_stack_store_may_intervene_without_changing_flags(self):
        b, a, n, c, r = fixture(True)
        for at, value in [(3, b'\x80'), (4, b'\x5d'), (3, b'\x89'), (6, b'\xff')]:
            raw, contract = changed(b, c, at, value)
            with self.subTest(offset=at), self.assertRaises(ValueError):
                payload.inspect(raw, raw, a, n, contract, r)

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
