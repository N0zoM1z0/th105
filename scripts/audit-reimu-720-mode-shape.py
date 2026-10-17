#!/usr/bin/env python3
"""Check the four Reimu720 random-angle modes with current native execution."""
from __future__ import annotations

import argparse
import importlib.util
import json
from pathlib import Path
import sys

import unicorn

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location("reimu720_previous", ROOT / "scripts/audit-reimu-aimed-mode-shape.py")
previous = importlib.util.module_from_spec(spec)
sys.modules[spec.name] = previous
spec.loader.exec_module(previous)
family = previous.previous
low, SYMBOL, Probe = previous.low, previous.SYMBOL, previous.Probe
HELPERS, CALL_TARGETS = previous.HELPERS, previous.CALL_TARGETS
LITERAL_BINDINGS = previous.LITERAL_BINDINGS
SUPPORT_PATHS = (Path(previous.__file__), *previous.SUPPORT_PATHS)
SCHEMA = "th105-reimu720-mode-shape-native-v1"
SCOPE = ("720 independent random-angle modes; actual native MT/helpers/RET and first901 request; "
         "current-root integration; returning requests, later rays, original void ABI and "
         "full-function canonical equality remain unproved")
COHORT_COUNTS = {"motion": 108, "nodes": 288, "visual720": 504, "random720": 216,
                 "branches": 8, "integration": 974}
SMOKE_COUNT = 12
ALLOW_SWITCH_METADATA = True


def cases(smoke=False):
    for case in family.cases(smoke):
        if case["action"] == 720:
            yield case
    if not smoke:
        for case in previous.cases(True):
            yield {**case, "cohort": "integration"}
        for case in previous.cases():
            if case["cohort"] == "integration":
                yield case


def check_target_case(case, result, sites):
    family.check_target_case(case, result, sites)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("object", type=Path)
    selection = parser.add_mutually_exclusive_group()
    selection.add_argument("--smoke", action="store_true")
    selection.add_argument("--cohort", action="append", choices=tuple(COHORT_COUNTS))
    args = parser.parse_args()
    try:
        result = low.audit(args.object, args.smoke, args.cohort, contract=sys.modules[__name__])
    except (KeyError, OSError, ValueError, unicorn.UcError) as error:
        parser.exit(2, f"Reimu720 mode audit failed: {error}\n")
    print(json.dumps(result, indent=2))
    raise SystemExit(1 if result["mismatch_count"] else 0)
