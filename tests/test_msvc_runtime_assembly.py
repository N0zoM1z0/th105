from pathlib import Path
import struct
import hashlib
import sys
import unittest
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'scripts'))
from msvc_runtime_assembly import verify_container, verify_readonly_sections, verify_internal_data_relocations


def fixture(label_offset=6, label_storage=6):
    body = bytes.fromhex('e8 01 00 00 00 c3 90 c3')
    header = struct.pack('<HHIIIHH', 0x14c, 1, 0, 68, 2, 0, 0)
    section = b'.text\0\0\0' + struct.pack('<IIIIIIHHI', 0, 0, 8, 60, 0, 0, 0, 0, 0x60000020)
    def symbol(name, offset, kind, storage):
        return name.ljust(8, b'\0') + struct.pack('<IhHBB', offset, 1, kind, storage, 0)
    return header + section + body + symbol(b'parent', 0, 0x20, 2) + symbol(b'start', label_offset, 0, label_storage) + struct.pack('<I', 4), body


class OriginalAssemblyEntryTests(unittest.TestCase):
    def test_named_called_entry_retains_complete_tail(self):
        obj, body = fixture()
        tail, relocations = verify_container(obj, 'parent', 'start', body, [], body, 6, 0)
        self.assertEqual(tail, b'\x90\xc3')
        self.assertEqual(relocations, [])

    def test_guessed_offset_or_wrong_symbol_kind_is_rejected(self):
        for obj, offset in [(fixture()[0], 7), (fixture(label_storage=2)[0], 6)]:
            body = fixture()[1]
            with self.assertRaises(ValueError):
                verify_container(obj, 'parent', 'start', body, [], body, offset, 0)

    def test_prefix_mismatch_is_not_hidden_by_tail_selection(self):
        obj, body = fixture()
        native = body[:5] + b'\x90' + body[6:]
        with self.assertRaises(ValueError):
            verify_container(obj, 'parent', 'start', body, [], native, 6, 0)

    def test_noncall_or_relocated_caller_is_rejected(self):
        obj, body = fixture()
        for call, relocations in [(1, []), (0, [(1, 20, 'external')])]:
            with self.assertRaises(ValueError):
                verify_container(obj, 'parent', 'start', body, relocations, body, 6, call)


class OriginalReadonlySectionTests(unittest.TestCase):
    def sample(self, flags=0x40000040):
        data = b'original'
        header = struct.pack('<HHIIIHH', 0x14c, 1, 0, 0, 0, 0, 0)
        section = b'.rdata\0\0' + struct.pack('<IIIIIIHHI', 0, 0, len(data), 60, 0, 0, 0, 0, flags)
        record = dict(section=1, address='0x401000', size=len(data), sha256=hashlib.sha256(data).hexdigest())
        return header + section + data, data, record

    def test_complete_original_data_matches_native(self):
        obj, data, record = self.sample()
        def read(address, size):
            self.assertEqual((address, size), (0x401000, len(data)))
            return data
        verify_readonly_sections(obj, [record], read)

    def test_writable_or_partial_sections_are_rejected(self):
        obj, data, record = self.sample(flags=0xc0000040)
        with self.assertRaises(ValueError):
            verify_readonly_sections(obj, [record], lambda a, n: data)
        obj, data, record = self.sample()
        record['size'] -= 1
        with self.assertRaises(ValueError):
            verify_readonly_sections(obj, [record], lambda a, n: data)

    def test_changed_native_data_and_repeated_sections_are_rejected(self):
        obj, data, record = self.sample()
        with self.assertRaises(ValueError):
            verify_readonly_sections(obj, [record], lambda a, n: b'changed!')
        with self.assertRaises(ValueError):
            verify_readonly_sections(obj, [record, record], lambda a, n: data)


class OriginalDataRelocationTests(unittest.TestCase):
    def test_actual_symbol_and_original_addend_locate_data(self):
        obj, _body = fixture()
        body = struct.pack('<I', 8)
        native = struct.pack('<I', 0x401000 + 6 + 8)
        specs = [dict(section=1, address='0x401000')]
        verify_internal_data_relocations(obj, body, [(0, 6, 'start')], native, specs)
        with self.assertRaises(ValueError):
            verify_internal_data_relocations(obj, body, [(0, 6, 'start')], struct.pack('<I', 0x401000), specs)

    def test_external_or_unproved_data_is_rejected(self):
        obj, _body = fixture()
        for name, specs in [('missing', [dict(section=1, address='0x401000')]), ('start', [])]:
            with self.assertRaises(ValueError):
                verify_internal_data_relocations(obj, b'\0' * 4, [(0, 6, name)], b'\0' * 4, specs)


if __name__ == '__main__':
    unittest.main()
