"""Reject false native caller identities without a game image or emulator."""
import importlib.util
from pathlib import Path
import struct
import sys
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
spec = importlib.util.spec_from_file_location("cpu_selector_sites_test", ROOT / "scripts/audit-cpu-policy-paths.py")
probe = importlib.util.module_from_spec(spec)
spec.loader.exec_module(probe)


class SelectorCallerTests(unittest.TestCase):
    def test_only_decoded_selector_calls_authorize_a_return(self):
        address = 0x6126E0
        code = b"\xb8\xe8\xaa\xbb\xcc" + b"\xe8" + struct.pack("<i", 0x4067D0 - address - 10) + b"\xc3"
        sites = probe.selector_call_sites(code, address)
        self.assertEqual(sites, {address + 5})
        self.assertEqual(probe.selector_call_site(address + 10, sites), address + 5)
        # An E8 byte inside MOV's immediate is not a decoded call boundary.
        for returned in (address + 6, address + 11, address - 1):
            with self.subTest(returned=returned), self.assertRaisesRegex(ValueError, "decoded root call"):
                probe.selector_call_site(returned, sites)

    def test_a_call_to_another_dependency_cannot_authorize_a_selector_site(self):
        address = 0x6126E0
        code = b"\xe8" + struct.pack("<i", 0x4066B0 - address - 5) + b"\xc3"
        self.assertEqual(probe.selector_call_sites(code, address), set())

    def test_pairing_rejects_truncation_and_argument_changes(self):
        target = [(0x612000, 1000), (0x615000, 10)]
        candidate = [(0x612100, 1000), (0x615100, 10)]
        self.assertEqual(probe.pair_selector_sites(target, candidate),
                         [(0x612000, 0x612100, 1000), (0x615000, 0x615100, 10)])
        for changed in (candidate[:-1], candidate + [(0x615200, 10)], [(0x612100, 1000), (0x615100, 40)]):
            with self.subTest(changed=changed), self.assertRaises(ValueError):
                probe.pair_selector_sites(target, changed)


class ReimuJoinTests(unittest.TestCase):
    # Synthetic diagnostic instructions only; never reconstruction source.
    COUNTER = bytes.fromhex("66399e66070000")
    BRANCH_RETURN = bytes.fromhex("7500c3")

    def locate(self, code):
        instance = probe.NativeCpuProbe.__new__(probe.NativeCpuProbe)
        return instance.locate_join(code, 0x48D390)

    def test_target_and_candidate_flag_preserving_shapes(self):
        for middle in (b"", bytes.fromhex("bf06000000")):
            with self.subTest(middle=middle):
                self.assertEqual(self.locate(self.COUNTER + middle + self.BRANCH_RETURN), 0x48D390)

    def test_unreviewed_or_flag_changing_instructions_are_rejected(self):
        for middle in (bytes.fromhex("bf07000000"), bytes.fromhex("83c001")):
            with self.subTest(middle=middle), self.assertRaises(ValueError):
                self.locate(self.COUNTER + middle + self.BRANCH_RETURN)

    def test_ambiguous_or_wrong_counter_is_rejected(self):
        code = self.COUNTER + self.BRANCH_RETURN
        for changed in (code * 2, code.replace(bytes.fromhex("6607"), bytes.fromhex("6407"))):
            with self.subTest(changed=changed), self.assertRaises(ValueError):
                self.locate(changed)

    def test_incomplete_callable_is_rejected(self):
        with self.assertRaises(ValueError):
            self.locate(self.COUNTER + self.BRANCH_RETURN + b"\x0f")


if __name__ == "__main__":
    unittest.main()
