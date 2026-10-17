#!/usr/bin/env python3
"""Check Reimu510..513 request expansion in the current integrated root."""
from __future__ import annotations

import argparse
import importlib.util
import json
from pathlib import Path
import sys

import unicorn

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location("reimu_510_shape_previous", ROOT / "scripts/audit-reimu-high-final-actions.py")
previous = importlib.util.module_from_spec(spec)
sys.modules[spec.name] = previous
spec.loader.exec_module(previous)
family = previous
while Path(family.__file__).name != "audit-reimu-mid-510-actions.py":
    family = family.previous
low, SYMBOL, Probe = previous.low, previous.SYMBOL, previous.Probe
HELPERS, CALL_TARGETS = previous.HELPERS, previous.CALL_TARGETS
LITERAL_BINDINGS = previous.LITERAL_BINDINGS
SUPPORT_PATHS = (Path(previous.__file__), *previous.SUPPORT_PATHS)
SCHEMA = "th105-reimu-510-request-shape-native-v1"
SCOPE = ("510..513 explicit request-source expansion; native helpers/RET and first812 request; "
         "current-root integration; returning world calls/later rays, original void ABI and "
         "full-function canonical equality remain unproved")
COHORT_COUNTS = {"motion": 336, "volley": 600, "charge": 864, "tail": 288,
                 "branches": 24, "integration": 948, "default": 1}
SMOKE_COUNT = 36


def cases(smoke=False):
    base = next(previous.cases(True))
    for case in family.cases(smoke):
        if smoke or case["cohort"] in ("motion", "volley", "charge", "tail", "branches", "default"):
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
        parser.exit(2, f"Reimu510 request-shape audit failed: {error}\n")
    print(json.dumps(result, indent=2))
    raise SystemExit(1 if result["mismatch_count"] else 0)
