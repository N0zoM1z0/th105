import importlib.util
from pathlib import Path
import struct
import sys
from types import SimpleNamespace
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))
spec = importlib.util.spec_from_file_location('reimu_linked_coff_tests', ROOT / 'scripts/audit-reimu-linked-coff.py')
audit = importlib.util.module_from_spec(spec)
spec.loader.exec_module(audit)


class LinkedCorrespondenceTests(unittest.TestCase):
    def setUp(self):
        self.start = 0x10001000
        self.destination = 0x10040000
        self.pool = 0x10030000
        self.bits = bytes.fromhex('0000803f')
        self.rows = [
            {'offset': 1, 'category': 'rel32_calls', 'kind': 20,
             'symbol': '_call', 'address': 0x401D50},
            {'offset': 8, 'category': 'numeric_literals', 'kind': 6,
             'symbol': '__real@3f800000', 'address': 0x6D0000},
            {'offset': 16, 'category': 'local_metadata_addresses', 'kind': 6,
             'symbol': '$table', 'address': audit.ADDRESS + 32},
            {'offset': 24, 'category': 'global_addresses', 'kind': 6,
             'symbol': '_global', 'address': 0x6FA894},
            {'offset': 32, 'category': 'local_code_pointers', 'kind': 6,
             'symbol': '$code', 'address': audit.ADDRESS + 6},
        ]
        self.reference = bytearray(b'\x90' * 48)
        self.reference[0] = 0xE8
        for row in self.rows:
            struct.pack_into('<I', self.reference, row['offset'], 0)
        self.payload = bytearray(self.reference)
        for offset, value in [(1, self.destination - (self.start + 5)), (8, self.pool),
                              (16, self.start + 32), (24, 0x6FA894), (32, self.start + 6)]:
            struct.pack_into('<I', self.payload, offset, value)
        self.highlow = {8, 16, 32}

    def replay(self, **changes):
        def read_literal(address, width):
            self.assertEqual((address, width), (self.pool, 4))
            return self.bits

        def target_bytes(address, width):
            self.assertEqual((address, width), (0x6D0000, 4))
            return self.bits

        args = dict(reference=self.reference, payload=self.payload, rows=self.rows,
                    highlow=self.highlow, start=self.start, metadata=32,
                    symbols={'_call': {self.destination}}, aliases={},
                    read_literal=read_literal, target_bytes=target_bytes)
        args.update(changes)
        return audit.replay_fields(**args)

    def test_all_field_roles_replay_and_full_payload_agrees(self):
        linked, reference, counts, callees = self.replay()
        self.assertEqual(linked, reference)
        self.assertEqual(len(linked), 48)
        self.assertEqual(set(counts), audit.CATEGORIES)
        self.assertEqual(sum(counts.values()), 5)
        self.assertEqual(callees, 1)
        self.assertEqual(struct.unpack_from('<I', linked, 32)[0], audit.ADDRESS + 6)
        self.assertEqual(struct.unpack_from('<I', linked, 8)[0], 0x6D0000)

    def test_wrong_call_provider_is_rejected(self):
        struct.pack_into('<I', self.payload, 1, self.destination + 16 - (self.start + 5))
        with self.assertRaisesRegex(ValueError, 'named provider'):
            self.replay()

    def test_wrong_literal_or_target_anchor_is_rejected(self):
        with self.assertRaisesRegex(ValueError, 'bits/width/target anchor'):
            self.replay(read_literal=lambda *_: bytes(4))
        with self.assertRaisesRegex(ValueError, 'bits/width/target anchor'):
            self.replay(target_bytes=lambda *_: bytes(4))

    def test_local_pointer_cannot_change_owner_offset(self):
        struct.pack_into('<I', self.payload, 32, self.start + 7)
        with self.assertRaisesRegex(ValueError, 'owner/offset'):
            self.replay()

    def test_highlow_missing_or_on_absolute_data_is_rejected(self):
        for relocations in (self.highlow - {8}, self.highlow | {24}):
            with self.subTest(relocations=relocations):
                with self.assertRaisesRegex(ValueError, 'HIGHLOW inventory'):
                    self.replay(highlow=relocations)

    def test_nonrelocation_bytes_remain_significant(self):
        self.payload[6] = 0x91
        with self.assertRaisesRegex(ValueError, 'outside relocation fields'):
            self.replay()

    def test_global_address_is_not_rebound(self):
        struct.pack_into('<I', self.payload, 24, 0x6FA898)
        with self.assertRaisesRegex(ValueError, 'game-data binding'):
            self.replay()

    def test_read_only_initialized_literal_storage_is_required(self):
        section = SimpleNamespace(Characteristics=0x40000040, VirtualAddress=0x30000,
                                  SizeOfRawData=4, contains_rva=lambda value: 0x30000 <= value < 0x30010)
        pe = SimpleNamespace(OPTIONAL_HEADER=SimpleNamespace(ImageBase=0x10000000),
                             get_section_by_rva=lambda _: section,
                             get_data=lambda *_: self.bits)
        self.assertEqual(audit.read_immutable(pe, self.pool, 4), self.bits)
        section.Characteristics |= 0x80000000
        with self.assertRaisesRegex(ValueError, 'immutable image data'):
            audit.read_immutable(pe, self.pool, 4)
        section.Characteristics = 0x40000040
        section.SizeOfRawData = 2
        with self.assertRaisesRegex(ValueError, 'immutable image data'):
            audit.read_immutable(pe, self.pool, 4)


if __name__ == '__main__':
    unittest.main()
