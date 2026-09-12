import importlib.util
from pathlib import Path
import struct
import sys
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
SPEC = importlib.util.spec_from_file_location("x87_return_sites", ROOT / "scripts" / "audit-x87-return-sites.py")
audit = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(audit)


class X87ReturnSitesTests(unittest.TestCase):
    def test_singleton_and_array_caller_results(self):
        row = {"address": "0x5264df", "name": "sub_520890"}
        self.assertEqual(audit.caller_rows(row), [row])
        self.assertEqual(audit.caller_rows([row]), [row])
        self.assertEqual(audit.caller_rows([]), [])

    def test_malformed_caller_results_fail_closed(self):
        for value in (None, "error", {}, {"error": "unavailable"}, [None],
                      [{"address": None}], [{"address": 0x5264df}]):
            with self.assertRaises(ValueError):
                audit.caller_rows(value)

    def test_direct_call_uses_signed_displacement(self):
        self.assertEqual(audit.direct_call_target(b"\xe8" + struct.pack("<i", -0x105), 0x401100), 0x401000)

    def test_non_call_and_truncated_call_fail_closed(self):
        for code in (b"\xe9\0\0\0\0", b"\xe8\0", b"\xff\xd0"):
            with self.assertRaises(ValueError):
                audit.direct_call_target(code, 0x401000)

    def test_window_stops_before_following_jump_destination(self):
        result = audit.consumer_window(bytes.fromhex("d9e0eb00d91e"), 0x401000)
        self.assertEqual(result["first_x87"], "fchs")
        self.assertEqual(result["stop"], "control_transfer")
        self.assertEqual(len(result["instructions"]), 2)

    def test_window_has_instruction_budget(self):
        result = audit.consumer_window(b"\x90" * 96, 0x401000)
        self.assertEqual(result["stop"], "instruction_limit")
        self.assertEqual(len(result["instructions"]), 20)
        self.assertIsNone(result["first_x87"])


if __name__ == "__main__":
    unittest.main()
