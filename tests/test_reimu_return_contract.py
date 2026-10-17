from pathlib import Path
import sys
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'scripts'))
from reimu_return_contract import pending_from_return, validate_return_symbol


class ReimuReturnContractTests(unittest.TestCase):
    def test_bool_uses_only_the_result_byte(self):
        self.assertTrue(pending_from_return(0xABCD1200))
        self.assertFalse(pending_from_return(0xABCD1201))

    def test_non_bool_result_is_rejected(self):
        with self.assertRaises(ValueError):
            pending_from_return(0xABCD12FF)

    def test_void_ret_has_no_pending_result_byte(self):
        for eax in (0, 1, 2, 255, 0xFFFFFFFF):
            self.assertFalse(pending_from_return(eax, 'void'))

    def test_return_kind_must_match_the_compiler_symbol(self):
        boolean = '?run@View@th105@@QAE_NXZ'
        nothing = '?run@View@th105@@QAEXXZ'
        validate_return_symbol(boolean, 'bool')
        validate_return_symbol(nothing, 'void')
        for symbol, kind in ((boolean, 'void'), (nothing, 'bool'), ('?run@View@th105@@QAEXH@Z', 'void')):
            with self.assertRaises(ValueError):
                validate_return_symbol(symbol, kind)

    def test_unknown_kind_is_rejected(self):
        with self.assertRaises(ValueError):
            pending_from_return(0, 'unknown')


if __name__ == '__main__':
    unittest.main()
