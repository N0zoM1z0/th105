#!/usr/bin/env python3
"""Check Reimu710/711 mode expansion with current-root native execution."""
from __future__ import annotations

import argparse
import importlib.util
import json
from pathlib import Path
import sys

import unicorn

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location("reimu_aimed_shape_previous", ROOT / "scripts/audit-reimu-high-final-actions.py")
previous = importlib.util.module_from_spec(spec)
sys.modules[spec.name] = previous
spec.loader.exec_module(previous)
family = previous
while Path(family.__file__).name != "audit-reimu-high-late-actions.py":
    family = family.previous
low, SYMBOL, Probe = previous.low, previous.SYMBOL, previous.Probe
HELPERS, CALL_TARGETS = previous.HELPERS, previous.CALL_TARGETS
LITERAL_BINDINGS = previous.LITERAL_BINDINGS
SUPPORT_PATHS = (Path(previous.__file__), *previous.SUPPORT_PATHS)
SCHEMA = "th105-reimu-aimed-mode-shape-native-v1"
SCOPE = ("710/711 independent mode loops; actual native helpers/RET and first900 request; "
         "current-root integration; later rays/returning world calls, original void ABI and "
         "full-function canonical equality remain unproved")
COHORT_COUNTS = {"motion": 216, "nodes": 576, "patterns": 600, "snapshot": 12,
                 "branches": 20, "integration": 948}
SMOKE_COUNT = 26
ALLOW_SWITCH_METADATA = True


def cases(smoke=False):
    base = next(previous.cases(True))
    for case in family.cases(smoke):
        if case["action"] in (710, 711) and (smoke or case["cohort"] in COHORT_COUNTS and case["cohort"] != "integration"):
            yield {**base, **case}
    if not smoke:
        for case in previous.cases(True):
            yield {**case, "cohort": "integration"}
        for case in previous.cases():
            if case["cohort"] == "integration":
                yield case


def check_target_case(case, result, sites):
    previous.check_target_case(case, result, sites)


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
        parser.exit(2, f"Reimu aimed-mode audit failed: {error}\n")
    print(json.dumps(result, indent=2))
    raise SystemExit(1 if result["mismatch_count"] else 0)
