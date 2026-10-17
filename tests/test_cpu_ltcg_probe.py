"""A source-type control must refuse an unreviewed arithmetic temporary."""
import importlib.util
from pathlib import Path
import sys
from types import SimpleNamespace
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
spec = importlib.util.spec_from_file_location("cpu_ltcg_probe_test", ROOT / "scripts/probe-aya-cpu-ltcg.py")
probe = importlib.util.module_from_spec(spec)
spec.loader.exec_module(probe)


class CpuLtcgSourceControlTests(unittest.TestCase):
    def test_reviewed_source_with_logical_and_is_accepted(self):
        source = (ROOT / "src/characters/AyaCpuActionPolicy.cpp").read_text()
        self.assertIn("&& v95", source)
        prepared = probe.prepare_source(source, "all")
        self.assertIn("float v95;", prepared)

    def test_arithmetic_or_additional_assignment_blocks_narrowing(self):
        source = (ROOT / "src/characters/AyaCpuActionPolicy.cpp").read_text()
        for changed in (source.replace("v99 = v117;", "v99 = v117 + 0.1;"),
                        source.replace("v99 = v117;", "v99 = v117;\nv99 = v117 + 0.1;"),
                        source.replace("v99 = v117;", "v99 = v117;\nv99 += 0.1;"),
                        source.replace("v99 = v117;", "v99 = v117;\nconsume(&v99);")):
            with self.subTest(additional="v99 = v117;\n" in changed):
                with self.assertRaisesRegex(ValueError, "unreviewed value provenance for v99"):
                    probe.prepare_source(changed, "all")

    def test_preserve_mode_does_not_narrow_an_arithmetic_value(self):
        source = (ROOT / "src/characters/AyaCpuActionPolicy.cpp").read_text()
        changed = source.replace("v99 = v117;", "v99 = v117 + 0.1;")
        prepared = probe.prepare_source(changed, "preserve")
        self.assertIn("double v99;", prepared)
        self.assertIn("v99 = v117 + 0.1;", prepared)


class CpuLtcgDependencyTests(unittest.TestCase):
    def test_loop_alignment_requires_the_exact_jump_gap_and_aligned_destination(self):
        start = 0x1000100B
        code = bytes.fromhex("eb038d4900c3")
        rows = probe.decode(code, start)
        self.assertTrue(probe.qualified_jump_alignment(code, start, rows, start + 2, start + 5))
        for changed, base in ((bytes.fromhex("eb028d4900c3"), start),
                              (bytes.fromhex("eb038d4000c3"), start), (code, start + 1)):
            with self.subTest(code=changed.hex(), base=base):
                self.assertFalse(probe.qualified_jump_alignment(changed, base, probe.decode(changed, base), base + 2, base + 5))

    def test_a_missing_sixth_switch_destination_cannot_close_the_cfg(self):
        indices = bytes([0, 1, 2, 3, 4, 5, 0])
        destinations = list(range(6))
        probe.checked_switch_indices(indices, destinations)
        with self.assertRaisesRegex(ValueError, "index escapes"):
            probe.checked_switch_indices(indices, destinations[:-1])

    def test_same_template_name_cannot_authorize_a_private_receiver_or_ret(self):
        # Synthetic parser fixture, with no proprietary bytes. Both alternatives
        # retain a named thiscall-like entry; only full instruction replay proves ABI.
        body = b"\x8b\x01" + b"\x90" * 89 + b"\xc2\x04\x00"
        canonical = SimpleNamespace(target_bytes=lambda address, count: body)
        address = 0x10001000
        names = {address: [(probe.DEQUE_SYMBOL, "provider.obj")]}
        self.assertTrue(probe.canonical_deque(body, address, names, canonical)["target_standard_abi_exact"])
        for changed in (b"\x8b\x07" + body[2:], body[:-3] + b"\xc2\x00\x00"):
            with self.subTest(body=changed.hex()):
                self.assertFalse(probe.canonical_deque(changed, address, names, canonical)["target_standard_abi_exact"])

    def test_unattested_deque_runtime_identity_is_rejected(self):
        body = b"\xe8\xfb\x0f\x00\x00" + b"\x90" * 86 + b"\xc2\x04\x00"
        canonical = SimpleNamespace(target_bytes=lambda address, count: body)
        with self.assertRaisesRegex(ValueError, "runtime call identity"):
            probe.canonical_deque(body, 0x10001000, {0x10002000: [("_unknown", "crt.obj")]}, canonical)


if __name__ == "__main__":
    unittest.main()
