import importlib.util
from pathlib import Path
import struct
import unittest


ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location(
    "object812_loop_test", ROOT / "scripts/audit-reimu-object-812-loop.py"
)
loop = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(loop)


class MissingLoopTests(unittest.TestCase):
    def test_no_reviewed_loop_fails_closed(self):
        with self.assertRaisesRegex(ValueError, "one812"):
            loop.loop_contract([], lambda address, size: bytes(size))


@unittest.skipUnless(
    (ROOT / "resources/th105.exe").is_file(), "requires canonical target"
)
class Object812LoopTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        loop.native.facts.audit()
        cls.rows = loop.native.facts.decode(
            loop.native.c.target_bytes(0x497FEC, 0x101), 0x497FEC
        )

    def test_target_four_words_and_eight_conditional_iterations(self):
        packet = loop.loop_contract(self.rows, loop.native.c.target_bytes)
        self.assertEqual(packet["conditional_iteration_count"], 8)
        self.assertEqual(packet["counter_offset"], 0x18)
        self.assertEqual(packet["payload_offset"], 0x90)
        self.assertEqual(
            packet["payload"],
            [
                "current_parameter0",
                0.0,
                2.0,
                ("+", ("*", "sector", 45.0), "current_parameter0"),
            ],
        )

    def incorrect_literal_fixture(self, changed_address, value):
        # Deliberately inconsistent numeric evidence, not a target-byte edit.
        def read(address, size):
            if address == changed_address:
                return struct.pack("<f" if size == 4 else "<d", value)
            return loop.native.c.target_bytes(address, size)

        return read

    def test_seven_does_not_establish_eight_iterations(self):
        with self.assertRaisesRegex(ValueError, "bound"):
            loop.loop_contract(self.rows, self.incorrect_literal_fixture(0x6C2874, 7.0))

    def test_step_two_does_not_establish_eight_iterations(self):
        with self.assertRaisesRegex(ValueError, "increment"):
            loop.loop_contract(self.rows, self.incorrect_literal_fixture(0x6CD160, 2.0))

    def test_wrong_angle_step_changes_the_payload_contract(self):
        with self.assertRaisesRegex(ValueError, "request expressions"):
            loop.loop_contract(
                self.rows, self.incorrect_literal_fixture(0x6C3D48, 90.0)
            )


if __name__ == "__main__":
    unittest.main()
