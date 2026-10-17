"""A register-bounded switch must retain unknown and conflicting paths."""
import importlib.util
from pathlib import Path
import sys
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
spec = importlib.util.spec_from_file_location(
    "reimu_action_root_test", ROOT / "scripts/audit-reimu-action-root.py")
audit = importlib.util.module_from_spec(spec)
spec.loader.exec_module(audit)


class ReimuRegisterBoundTests(unittest.TestCase):
    def definitions(self, code):
        rows = audit.decode(bytes.fromhex(code), 0x1000)
        return audit.reaching_ebp_definitions(rows, {}, rows[-2].address)[0]

    def test_preserved_ebp_reaches_bound_across_an_ordinary_call(self):
        self.assertEqual(self.definitions("bd03000000 e800000001 39e8 c3"), {0x1000})

    def test_both_conflicting_definitions_survive_the_join(self):
        self.assertEqual(self.definitions("85c0 7407 bd03000000 eb05 bd04000000 39e8 c3"),
                         {0x1004, 0x100B})

    def test_a_path_without_any_definition_remains_unknown(self):
        self.assertEqual(self.definitions("85c0 7405 bd03000000 39e8 c3"), {None, 0x1004})

    def test_partial_register_write_invalidates_the_prior_whole_value(self):
        self.assertEqual(self.definitions("bd03000000 66bd0400 39e8 c3"), {0x1005})


if __name__ == "__main__":
    unittest.main()
