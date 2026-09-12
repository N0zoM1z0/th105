import importlib.util
from pathlib import Path
import sys
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
SPEC = importlib.util.spec_from_file_location("compare_unit_object", ROOT / "scripts/compare-unit-object.py")
compare = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(compare)


class ExistingObjectSelectionTests(unittest.TestCase):
    def setUp(self):
        self.unit = {"functions": [{"address": "0x00401000"}, {"address": "0x00402000"}]}

    def test_only_requested_function_is_selected(self):
        result = compare.select_functions(self.unit, [0x402000])
        self.assertEqual(result["functions"], [{"address": "0x00402000"}])
        self.assertEqual(len(self.unit["functions"]), 2)

    def test_unknown_function_is_not_silently_skipped(self):
        with self.assertRaises(ValueError):
            compare.select_functions(self.unit, [0x403000])

    def test_empty_filter_copies_whole_unit(self):
        result = compare.select_functions(self.unit, [])
        result["functions"][0]["address"] = "changed"
        self.assertEqual(self.unit["functions"][0]["address"], "0x00401000")


if __name__ == "__main__":
    unittest.main()
