import importlib.util
from pathlib import Path
import unittest


ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location(
    "object808_buffer_test", ROOT / "scripts/audit-reimu-object-808-buffer.py"
)
buffer = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(buffer)


class Object808BufferTests(unittest.TestCase):
    def test_wrong_callee_cleanup_fails_closed(self):
        with self.assertRaisesRegex(ValueError, "seven words"):
            buffer.caller_buffer([], 24)

    def test_wider_store_cannot_establish_float_words(self):
        # Synthetic FLDZ; FSTP qword ptr [ESP+10h].
        rows = buffer.native.facts.decode(bytes.fromhex("d9ee dd5c2410"), 0x1000)
        with self.assertRaisesRegex(ValueError, "non-dword store"):
            buffer.caller_buffer(rows, 28)

    def test_unknown_instruction_fails_closed(self):
        rows = buffer.native.facts.decode(bytes.fromhex("90"), 0x1000)
        with self.assertRaisesRegex(ValueError, "unreviewed instruction"):
            buffer.caller_buffer(rows, 28)

    def test_word_push_cannot_use_dword_stack_effect(self):
        rows = buffer.native.facts.decode(bytes.fromhex("66 6a 03"), 0x1000)
        with self.assertRaisesRegex(ValueError, "non-dword push"):
            buffer.caller_buffer(rows, 28)

    def test_lea_cannot_change_the_stack_pointer_unobserved(self):
        rows = buffer.native.facts.decode(bytes.fromhex("8d 64 24 04"), 0x1000)
        with self.assertRaisesRegex(ValueError, "pointer register"):
            buffer.caller_buffer(rows, 28)

    def test_unreachable_constant_clobber_is_not_a_case_path(self):
        # NOP; JMP past MOV EBP,2; window NOP.
        rows = buffer.native.facts.decode(
            bytes.fromhex("90 eb05 bd02000000 90"), 0x1000
        )
        self.assertEqual(
            buffer.preserved_to_window(rows, 0x1000, 0x1008, buffer.x.X86_REG_EBP), 3
        )

    def test_partial_register_clobber_invalidates_the_constant(self):
        rows = buffer.native.facts.decode(bytes.fromhex("66bd0200 90"), 0x1000)
        with self.assertRaisesRegex(ValueError, "overwritten"):
            buffer.preserved_to_window(rows, 0x1000, 0x1004, buffer.x.X86_REG_EBP)

    def test_one_conditional_clobber_path_invalidates_the_constant(self):
        rows = buffer.native.facts.decode(
            bytes.fromhex("85c0 7405 bd02000000 90"), 0x1000
        )
        with self.assertRaisesRegex(ValueError, "overwritten"):
            buffer.preserved_to_window(rows, 0x1000, 0x1009, buffer.x.X86_REG_EBP)

    def test_return_only_epilogue_does_not_reach_the_window(self):
        rows = buffer.native.facts.decode(
            bytes.fromhex("85c0 7406 bd02000000 c3 90"), 0x1000
        )
        self.assertEqual(
            buffer.preserved_to_window(rows, 0x1000, 0x100A, buffer.x.X86_REG_EBP), 3
        )

    @unittest.skipUnless(
        (ROOT / "resources/th105.exe").is_file(), "requires canonical target"
    )
    def test_target_reuses_buffer_but_does_not_prove_preserved_contents(self):
        buffer.native.facts.audit()
        rows = buffer.native.facts.decode(
            buffer.native.c.target_bytes(0x497225, 0xA8), 0x497225
        )
        packet = buffer.caller_buffer(rows, 28)
        first, second = packet["requests"]
        self.assertTrue(packet["same_pointer"])
        self.assertEqual(first["pointer_offset"], 0x128)
        self.assertEqual(first["payload"], [0, 0, 0])
        self.assertEqual(
            second["payload"], [buffer.AFTER_CALL, buffer.AFTER_CALL, 0x3F800000]
        )
        self.assertEqual(first["call"], "0x49727b")
        self.assertEqual(second["call"], "0x4972c8")


if __name__ == "__main__":
    unittest.main()
