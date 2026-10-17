#!/usr/bin/env python3
"""Check Reimu740 mode selectors and bounded unknown paths with current native execution."""
from __future__ import annotations

import argparse
import importlib.util
import json
from pathlib import Path
import sys
from types import SimpleNamespace

from reimu_740_mode_facts import ADDRESS, packet

import unicorn

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location("reimu740_previous", ROOT / "scripts/audit-reimu-730-mode-shape.py")
previous = importlib.util.module_from_spec(spec)
sys.modules[spec.name] = previous
spec.loader.exec_module(previous)
family = previous.family
low, SYMBOL, Probe = previous.low, previous.SYMBOL, previous.Probe
HELPERS, CALL_TARGETS = previous.HELPERS, previous.CALL_TARGETS
LITERAL_BINDINGS = previous.LITERAL_BINDINGS
SUPPORT_PATHS = (ROOT / "scripts/reimu_740_mode_facts.py", ROOT / "scripts/compare-function.py",
                 ROOT / "scripts/compare-giant-action-switches.py", Path(previous.__file__), *previous.SUPPORT_PATHS)
SCHEMA = "th105-reimu740-mode-shape-native-v1"
SCOPE = ("740 two explicit mode selectors; actual native MT/helpers/RET and first903 request; "
         "uninitialized out-of-range target reads remain pending; current-root integration; "
         "no returning request, original void ABI or canonical-exact claim")
COHORT_COUNTS = {"motion": 108, "nodes": 288, "shots740": 4032, "cutoff740": 56,
                 "branches": 4, "unresolved740": 8, "integration": 998}
SMOKE_COUNT = 12
ALLOW_SWITCH_METADATA = True


def cases(smoke=False):
    for case in family.cases(smoke):
        if case["action"] == 740:
            yield case
    if not smoke:
        for case in previous.cases(True):
            yield {**case, "cohort": "integration"}
        for case in previous.cases():
            if case["cohort"] == "integration":
                yield case


def check_target_case(case, result, sites):
    family.check_target_case(case, result, sites)


def boundary_probe(facts, *, base=Probe):
    boundaries = frozenset(ADDRESS+offset for offset in facts["source"]["pending_reads"])

    class BoundaryProbe(base):
        def step(self, uc, address, size):
            super().step(uc, address, size)
            if self.candidate and address in boundaries:
                actor = low.OWNER
                action = int.from_bytes(uc.mem_read(actor+0x13C, 2), "little")
                sequence = int.from_bytes(uc.mem_read(actor+0x13E, 2), "little")
                mode = int.from_bytes(uc.mem_read(0x6FA894, 4), "little")
                expected_sequence = 1 if address == ADDRESS+facts["source"]["pending_reads"][0] else 6
                if action != 740 or sequence != expected_sequence or mode <= 3:
                    raise ValueError("candidate indeterminate-read boundary has unexpected inputs")
                self.pending_handoff = True
                uc.emu_stop()

    return BoundaryProbe


def audit(path, smoke=False, cohorts=None):
    facts = packet(path)

    contract = SimpleNamespace(**vars(sys.modules[__name__]))
    contract.Probe = boundary_probe(facts)
    result = low.audit(path, smoke, cohorts, contract=contract)
    result["mode_structure"] = facts
    return result


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("object", type=Path)
    selection = parser.add_mutually_exclusive_group()
    selection.add_argument("--smoke", action="store_true")
    selection.add_argument("--cohort", action="append", choices=tuple(COHORT_COUNTS))
    args = parser.parse_args()
    try:
        result = audit(args.object, args.smoke, args.cohort)
    except (KeyError, OSError, ValueError, unicorn.UcError) as error:
        parser.exit(2, f"Reimu740 mode audit failed: {error}\n")
    print(json.dumps(result, indent=2))
    raise SystemExit(1 if result["mismatch_count"] else 0)
