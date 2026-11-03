import importlib.util
from pathlib import Path
import sys
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))
spec = importlib.util.spec_from_file_location('network_packet_vtables', ROOT / 'scripts/audit-network-packet-vtables.py')
audit = importlib.util.module_from_spec(spec)
spec.loader.exec_module(audit)

class FakeReader:
    def __init__(self, refs): self.slots = refs
    def section(self, symbol): return type('Section', (), {'name': '.rdata', 'raw_size': 12})()
    def symbol(self, symbol): return type('Symbol', (), {'value': 4})()
    def raw(self, symbol, size, offset=0):
        if symbol == 'hierarchy': return __import__('struct').pack('<4I', 0, 0, 2, 0)
        if symbol == 'base': return __import__('struct').pack('<7I', 0, 0, 0, 0xffffffff, 0, 0x40, 0)
        return bytes(size)
    def refs(self, symbol, size): return self.slots
    def pointer(self, symbol, offset): return {('table', -4): 'col', ('col', 16): 'hierarchy', ('hierarchy', 12): 'array', ('array', 4): 'base', ('base', 0): 'base_type'}[(symbol, offset)]
    def typename(self, symbol): return b'.?AUNetworkPacketBase8@th105@@\0'

class NetworkPacketVtableTests(unittest.TestCase):
    def test_two_concrete_slots_required_in_order(self):
        audit.check_source_table(FakeReader([(0, 6, 'serialize'), (4, 6, 'parse')]), 'table', 'serialize', 'parse')
        with self.assertRaisesRegex(ValueError, 'slots differ'):
            audit.check_source_table(FakeReader([(0, 6, 'parse'), (4, 6, 'serialize')]), 'table', 'serialize', 'parse')
        with self.assertRaisesRegex(ValueError, 'slots differ'):
            audit.check_source_table(FakeReader([(0, 6, 'serialize')]), 'table', 'serialize', 'parse')

if __name__ == '__main__': unittest.main()
