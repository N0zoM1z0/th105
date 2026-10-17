#!/usr/bin/env python3
"""Check Reimu730 mode-specific cadence and requests with current native execution."""
from __future__ import annotations

import argparse
import importlib.util
import itertools
import json
from pathlib import Path
import sys

import unicorn

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location("reimu730_previous", ROOT / "scripts/audit-reimu-720-mode-shape.py")
previous = importlib.util.module_from_spec(spec)
sys.modules[spec.name] = previous
spec.loader.exec_module(previous)
family = previous.family
low, SYMBOL, Probe = previous.low, previous.SYMBOL, previous.Probe
HELPERS, CALL_TARGETS = previous.HELPERS, previous.CALL_TARGETS
LITERAL_BINDINGS = previous.LITERAL_BINDINGS
SUPPORT_PATHS = (Path(previous.__file__), *previous.SUPPORT_PATHS)
SCHEMA = "th105-reimu730-mode-shape-native-v1"
SCOPE = ("730 independent cadence modes; actual native MT/math/helpers/RET and first902 request; "
         "current-root integration; post-request returning continuations, original void ABI and "
         "full-function canonical equality remain unproved")
COHORT_COUNTS = {"motion": 108, "nodes": 288, "cadence730": 2160,
                 "cadence730_extremes": 128, "branches": 6, "integration": 986}
SMOKE_COUNT = 12
ALLOW_SWITCH_METADATA = True


def cases(smoke=False):
    for case in family.cases(smoke):
        if case["action"] == 730:
            yield case
    if not smoke:
        base = next(family.cases(True))
        for mode, count, facing, cw in itertools.product(
                range(4), (-2147483648, -2147483647, -2147483646, -2147483645,
                           2147483640, 2147483645, 2147483646, 2147483647),
                (-1, 127), (0x27F, 0x37F)):
            yield {**base, "cohort": "cadence730_extremes", "action": 730, "sequence": 5,
                   "counter": (count-1+0x80000000) % 0x100000000-0x80000000,
                   "post_counter": count, "match_selector": mode, "speed": 5.0,
                   "facing": facing, "control_word": cw}
        for case in previous.cases(True):
            yield {**case, "cohort": "integration"}
        for case in previous.cases():
            if case["cohort"] == "integration":
                yield case


def check_target_case(case, result, sites):
    if case["cohort"] == "cadence730_extremes":
        case = {**case, "cohort": "cadence730"}
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
        parser.exit(2, f"Reimu730 mode audit failed: {error}\n")
    print(json.dumps(result, indent=2))
    raise SystemExit(1 if result["mismatch_count"] else 0)
