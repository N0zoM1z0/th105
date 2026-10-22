"""Negative controls for optional normal-ABI carrier qualification."""
import importlib.util
from pathlib import Path
import struct
import unittest
import capstone

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location("aya_flow", ROOT / "scripts/audit-aya-object-normal-flow.py")
audit = importlib.util.module_from_spec(spec)
spec.loader.exec_module(audit)


def packet(raw):
    cs = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    cs.detail = True
    return {"by": {r.address: r for r in cs.disasm(raw, audit.S)},
            "switches": {}, "code": raw, "meta": len(raw)}


class CarrierLivenessTests(unittest.TestCase):
    def test_partial_write_does_not_kill_high_bytes(self):
        # mov al,0; test ax,ax; ret
        with self.assertRaisesRegex(AssertionError, "carrier remains live"):
            audit.dead_after(packet(bytes.fromhex("b0006685c0c3")), audit.S, "eax")

    def test_low_byte_overwrite_allows_low_byte_read(self):
        audit.dead_after(packet(bytes.fromhex("b00084c0c3")), audit.S, "eax")

    def test_full_overwrite_kills_carrier(self):
        audit.dead_after(packet(bytes.fromhex("b80000000085c0c3")), audit.S, "eax")

    def test_taken_branch_read_is_not_missed(self):
        # jz read; mov eax,0; ret; read: test eax,eax; ret
        with self.assertRaisesRegex(AssertionError, "carrier remains live"):
            audit.dead_after(packet(bytes.fromhex("7406b800000000c385c0c3")), audit.S, "eax")

    def test_unknown_call_fails_closed(self):
        raw = b"\xe8" + struct.pack("<i", 0x410000 - audit.S - 5) + b"\xc3"
        with self.assertRaisesRegex(AssertionError, "unqualified call"):
            audit.dead_after(packet(raw), audit.S, "edx")

    def test_call_clobber_is_not_a_defined_register_value(self):
        raw = b"\xe8" + struct.pack("<i", 0x435160 - audit.S - 5) + bytes.fromhex("85d2c3")
        with self.assertRaisesRegex(AssertionError, "carrier remains live"):
            audit.dead_after(packet(raw), audit.S, "edx")

    def test_this_argument_is_live_at_known_call(self):
        raw = b"\xe8" + struct.pack("<i", 0x435160 - audit.S - 5) + b"\xc3"
        with self.assertRaisesRegex(AssertionError, "this argument remains live"):
            audit.dead_after(packet(raw), audit.S, "ecx")
        audit.dead_after(packet(raw), audit.S, "edx")

    def test_changed_memory_address_is_not_register_renaming(self):
        # movsx ecx,[esi+104]; mov [esp+18],ecx; ret
        old = packet(bytes.fromhex("0fbe8e04010000894c2418c3"))
        new = packet(bytes.fromhex("0fbe860501000089442418c3"))
        with self.assertRaises(AssertionError):
            audit.carrier_window(old, new, audit.S, audit.S)

    def test_actual_spill_template_can_be_qualified(self):
        old = packet(bytes.fromhex("0fbe8e04010000894c2418c3"))
        new = packet(bytes.fromhex("0fbe860401000089442418c3"))
        _, _, pairs, report = audit.carrier_window(old, new, audit.S, audit.S)
        self.assertEqual(len(pairs), 2)
        self.assertEqual(report["registers"], ["ecx", "eax"])


if __name__ == "__main__":
    unittest.main()
