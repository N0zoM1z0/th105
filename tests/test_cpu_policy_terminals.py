"""Terminal witnesses must come from real writes and decoded root RETs."""
import importlib.util
from pathlib import Path
import struct
import sys
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
spec = importlib.util.spec_from_file_location("cpu_policy_terminal_tests", ROOT / "scripts/audit-cpu-policy-paths.py")
native = importlib.util.module_from_spec(spec)
sys.modules[spec.name] = native
spec.loader.exec_module(native)


@unittest.skipUnless(importlib.util.find_spec("unicorn"), "Unicorn is unavailable")
class CpuPolicyTerminalTests(unittest.TestCase):
    def make_probe(self, selected=True):
        class SyntheticProbe(native.NativeCpuProbe):
            def locate_join(self, code, address):
                return address

        # Diagnostic-only NOP / actual word store / RET. Never reconstruction code.
        code = bytes.fromhex("9066c786660700000300c3")
        instance = SyntheticProbe(bytes(0x1000), code, len(code),
                                  collect_selector_sites=True, collect_terminals=True)
        instance.phase, instance.selection_started = "root", selected
        instance.stopped, instance.failure = False, None
        uc, r = instance.engine, instance.reg
        uc.reg_write(r.UC_X86_REG_ESI, instance.OWNER)
        uc.reg_write(r.UC_X86_REG_ESP, instance.STACK + 0xFF00)
        uc.mem_write(instance.STACK + 0xFF00, struct.pack("<I", native.RETURN))
        return instance

    def test_records_executed_word_store_and_genuine_return(self):
        instance = self.make_probe()
        instance.engine.emu_start(instance.address + 1, native.RETURN)
        self.assertIsNone(instance.failure)
        self.assertEqual(instance.terminal_word_writes, [(instance.address + 1, 0x766, 3)])
        self.assertEqual(instance.root_return_site, instance.address + 10)
        self.assertEqual(instance.engine.reg_read(instance.reg.UC_X86_REG_ESP), instance.STACK + 0xFF04)

    def test_writes_before_selection_are_excluded(self):
        instance = self.make_probe(selected=False)
        instance.engine.emu_start(instance.address + 1, native.RETURN)
        self.assertIsNone(instance.failure)
        self.assertEqual(instance.terminal_word_writes, [])

    def test_return_outside_decoded_root_is_rejected(self):
        instance = self.make_probe()
        address = instance.address + 0x20
        instance.engine.mem_write(address, b"\xc3")
        instance.engine.emu_start(address, native.RETURN)
        self.assertIn("unreviewed or repeated root RET", instance.failure)
        self.assertIsNone(instance.root_return_site)


if __name__ == "__main__":
    unittest.main()
