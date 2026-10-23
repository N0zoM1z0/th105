from pathlib import Path
import importlib.util
import sys
import unittest

import capstone


ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
SPEC = importlib.util.spec_from_file_location(
    "aya_normal_flow_successor_tests", ROOT / "scripts/audit-aya-object-normal-flow.py"
)
FLOW = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(FLOW)


class NormalFlowSuccessorTests(unittest.TestCase):
    def reachable(self, code, switches=None):
        start = 0x800000
        cs = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
        cs.detail = True
        packet = {"by": {row.address: row for row in cs.disasm(code, start)},
                  "switches": switches or {}}
        pending, seen = [start], set()
        while pending:
            pc = pending.pop()
            if pc in seen:
                continue
            seen.add(pc)
            pending.extend(FLOW.edges(packet, packet["by"][pc]))
        return seen

    def test_unconditional_jump_cannot_reach_skipped_register_updates(self):
        # JMP RET skips INC EAX and INC ECX. A fabricated fallthrough used to
        # make unrelated action bodies appear reachable in whole-root audits.
        self.assertEqual(self.reachable(bytes.fromhex("eb 02 40 41 c3")),
                         {0x800000, 0x800004})

    def test_conditional_jump_preserves_both_real_paths(self):
        self.assertEqual(self.reachable(bytes.fromhex("75 02 40 41 c3")),
                         {0x800000, 0x800002, 0x800003, 0x800004})

    def test_reviewed_indirect_jump_has_only_its_destinations(self):
        self.assertEqual(self.reachable(bytes.fromhex("ff e0 40 41 c3"),
                         {0x800000: {"destinations": [0x800004]}}),
                         {0x800000, 0x800004})

    def test_external_tail_jump_does_not_fall_through_inside_root(self):
        self.assertEqual(self.reachable(bytes.fromhex("eb 20 40 c3")), {0x800000})


if __name__ == "__main__":
    unittest.main()
