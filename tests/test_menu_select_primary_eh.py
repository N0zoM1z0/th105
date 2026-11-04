"""Menu selection's complete exception metadata contract."""
import importlib.util
from pathlib import Path
import sys
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))
spec = importlib.util.spec_from_file_location('menu_eh', ROOT / 'scripts/audit-menu-select-primary-eh.py')
eh = importlib.util.module_from_spec(spec); spec.loader.exec_module(eh)


class MenuSelectPrimaryEhTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.meta = eh.core.comparator().target_bytes(eh.META, 76)

    def test_complete_remote_eh(self):
        result = eh.audit()
        self.assertEqual(result['result'], 'exact')
        self.assertEqual((result['code_size'], result['metadata_size'], result['states']), (82, 76, 5))

    def test_each_metadata_byte_is_checked(self):
        eh.check_metadata(self.meta)
        for offset in range(len(self.meta)):
            changed = bytearray(self.meta); changed[offset] ^= 1
            with self.subTest(offset=offset), self.assertRaises(ValueError):
                eh.check_metadata(bytes(changed))


if __name__ == '__main__': unittest.main()
