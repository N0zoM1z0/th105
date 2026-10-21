import importlib.util
from pathlib import Path
import sys
import unittest


ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location(
    "giant_switch_mapper_test", ROOT / "scripts/map-giant-action-switches.py"
)
mapper = importlib.util.module_from_spec(SPEC)
sys.modules[SPEC.name] = mapper
SPEC.loader.exec_module(mapper)


class CodeImage:
    # FLD1; MOV EBP,669; CALL back to FLD1; RET. The E8 within FLD1
    # also passes the legacy raw scan's in-image target-range filter.
    code = bytes.fromhex("d9 e8 bd 9d 02 00 00 e8 f4 ff ff ff c3")
    address = 0x00400000

    def read(self, address, size):
        offset = address - self.address
        if not 0 <= offset <= offset + size <= len(self.code):
            raise ValueError("fixture read escapes code")
        return self.code[offset:offset + size]


class GiantSwitchMapperTests(unittest.TestCase):
    def root(self):
        return {
            "name": "fixture",
            "address": CodeImage.address,
            "callable_end": CodeImage.address + len(CodeImage.code),
            "metadata_end": CodeImage.address + len(CodeImage.code),
            "expected_direct_call_sites": 2,
            "expected_direct_call_targets": 2,
            "expected_ret_opcodes": 1,
            "regions": [],
        }

    def test_embedded_e8_is_separate_from_decoded_calls(self):
        result = mapper.map_root(CodeImage(), [], self.root())
        self.assertEqual(result["direct_call_sites"], 1)
        self.assertEqual(result["direct_call_target_count"], 1)
        self.assertEqual(result["direct_call_census_basis"], "linear_instruction_decode")
        self.assertEqual(result["raw_e8_sanity"]["sites"], 2)
        self.assertEqual(result["raw_e8_sanity"]["targets"], 2)
        text = mapper.format_text(result)
        self.assertIn("decoded direct calls: 1 sites / 1 targets", text)
        self.assertIn("raw E8 fingerprint: 2 sites / 2 targets", text)

    def test_raw_fingerprint_guard_still_uses_raw_count(self):
        root = self.root()
        root["expected_direct_call_sites"] = 1
        with self.assertRaisesRegex(ValueError, "site census 2 != expected 1"):
            mapper.map_root(CodeImage(), [], root)


if __name__ == "__main__":
    unittest.main()
