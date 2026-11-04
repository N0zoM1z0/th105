import importlib.util
from pathlib import Path
import struct
import sys
import unittest
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'scripts'))
sp = importlib.util.spec_from_file_location('replay_header_eh', Path(__file__).resolve().parents[1] / 'scripts/audit-replay-header-read-eh.py')
m = importlib.util.module_from_spec(sp); sp.loader.exec_module(m)

class ReplayHeaderEhTests(unittest.TestCase):
    def fixture(self):
        return struct.pack('<iI9I', -1, m.CODE, 0x19930522, 1, m.META, 0, 0, 0, 0, 0, 1)
    def test_complete_metadata(self):
        m.check_metadata(self.fixture())
    def test_every_byte_is_checked(self):
        for index in range(44):
            mutated = bytearray(self.fixture()); mutated[index] ^= 1
            with self.assertRaises(ValueError): m.check_metadata(bytes(mutated))
    def test_truncation_rejected(self):
        with self.assertRaises(ValueError): m.check_metadata(self.fixture()[:-1])
if __name__ == '__main__': unittest.main()
