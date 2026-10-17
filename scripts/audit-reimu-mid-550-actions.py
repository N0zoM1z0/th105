#!/usr/bin/env python3
"""Compare shared550/551 and direct560 inside the integrated Reimu source."""
from __future__ import annotations

import argparse
import importlib.util
import itertools
import json
from pathlib import Path
import struct
import sys

import unicorn

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location("reimu_550_previous", ROOT / "scripts/audit-reimu-mid-540-actions.py")
previous = importlib.util.module_from_spec(spec)
sys.modules[spec.name] = previous
spec.loader.exec_module(previous)
low, SYMBOL = previous.low, previous.SYMBOL
ACTIONS = (550, 551, 560)
KEYS = (*previous.KEYS, *ACTIONS)
HELPERS = previous.HELPERS
CALL_TARGETS = {**previous.CALL_TARGETS, "selector_random_roll": 0x4067D0}
SUPPORT_PATHS = (Path(previous.__file__), *previous.SUPPORT_PATHS)
LITERAL_BINDINGS = {
    **previous.LITERAL_BINDINGS,
    "c0000000": 0x6C344C, "4046800000000000": 0x6C3D48,
    "4056800000000000": 0x6C25C8, "4052000000000000": 0x6C3D40,
    "4064400000000000": 0x6C3D38, "4032000000000000": 0x6C1F48,
    "4020000000000000": 0x6C09A8, "406f400000000000": 0x6C3D30,
    "c3480000": 0x6CD1B8, "40900000": 0x6C3EA8,
    "41600000": 0x6C3C64, "3f400000": 0x6C3C54,
}
SCHEMA = "th105-reimu-mid-550-native-v1"
SCOPE = ("integrated entry/low/all middle/direct560 source; actual native helpers "
         "and RET ABI, first822/825 request/payload; supplied read-only animation/"
         "flat/zero-handle context; no returning world request, later rings/grid, "
         "high source, full-root or canonical-exact claim")


def cases(smoke=False):
    base = next(previous.cases(True))
    if smoke:
        for action, change in itertools.product(ACTIONS, (
                {}, {"sequence": 0, "state": 3},
                {"sequence": 0, "frame": 3, "timer": -1},
                {"sequence": 1, "timer": -3, "y": 100.0},
                {"sequence": 1, "timer": 0, "y": 100.0},
                {"sequence": 1, "timer": 9, "y": 100.0},
                {"sequence": 1, "timer": 12},
                {"sequence": 2, "counter": -1, "timer": -1, "y": 100.0},
                {"sequence": 2, "vy": 0xC0400000},
                {"sequence": 3, "vy": 0xC0400000},
                {"sequence": 1, "counter": -1, "timer": -1},
                {"single_sequence": True, "transition": "terminal"})):
            yield {**base, "cohort": "smoke", "action": action, **change}
        return
    for action, sequence, change, cw in itertools.product(ACTIONS, range(9), (
            {}, {"counter": -1, "timer": -1}, {"y": 100.0},
            {"vy": 0xC0400000}, {"vy": 0x7FC12345},
            {"single_sequence": True, "transition": "terminal"}), (0x27F, 0x37F)):
        yield {**base, "cohort": "motion", "action": action, "sequence": sequence,
               "control_word": cw, **change}
    for action, timer, facing, seed, cw in itertools.product(
            (550, 551), (-32766, -12, -3, 0, 3, 6, 9, 12), (-128, -1, 0, 1, 127),
            (0, 5489, 0xFFFFFFFF), (0x27F, 0x37F)):
        yield {**base, "cohort": "ring", "action": action, "sequence": 1,
               "timer": timer, "facing": facing, "seed": seed, "control_word": cw,
               "y": 100.0}
    for action, timer, frame, counter, cw in itertools.product(
            ACTIONS, (-4, -3, -1, 0, 1, 2, 3, 8, 9, 10, 11, 12),
            (0, 2, 3), (-1, 0, 1), (0x27F, 0x37F)):
        yield {**base, "cohort": "gates", "action": action, "sequence": 1,
               "timer": timer, "frame": frame, "counter": counter, "control_word": cw}
    for action, sequence, alpha, change, cw in itertools.product(
            (550, 551), (2, 3), (0, 1, 234, 235, 244, 245, 246, 254, 255),
            ({"y": 100.0}, {"vy": 0xC0400000}), (0x27F, 0x37F)):
        yield {**base, "cohort": "alpha", "action": action, "sequence": sequence,
               "alpha": alpha, "control_word": cw, **change}
    for action, sequence, timer, frame, counter, state in itertools.product(
            ACTIONS, range(4), (-1, 0), (0, 3), (-1, 0, 1), (0, 1, 3)):
        yield {**base, "cohort": "nodes", "action": action, "sequence": sequence,
               "timer": timer, "frame": frame, "counter": counter, "state": state,
               "y": 100.0}
    for facing, counter, phase, cw in itertools.product(
            (-128, -1, 0, 1, 127), (-1, 0, 7), (0, 3, 4), (0x27F, 0x37F)):
        yield {**base, "cohort": "request825", "action": 560, "sequence": 0,
               "frame": 3, "timer": -1, "counter": counter, "facing": facing,
               "phase55a": phase, "control_word": cw}
    branches = (
        (550, 0x487518, {"state": 3}), (551, 0x487518, {"state": 3}),
        (550, 0x4874CA, {"sequence": 2, "counter": 0, "timer": 0}),
        (551, 0x487818, {"sequence": 2, "counter": -1, "timer": -1, "y": 100.0}),
        (550, 0x487887, {"frame": 3, "timer": -1}),
        (551, 0x479486, {"sequence": 1, "counter": -1, "timer": -1}),
        (550, 0x4878BA, {"sequence": 2, "vy": 0xC0400000}),
        (551, 0x4878BA, {"sequence": 3, "vy": 0xC0400000}),
        (560, 0x47FA23, {"sequence": 1, "vy": 0xC0400000}),
        (560, 0x487A3D, {"sequence": 1, "counter": -1, "timer": -1}),
        (560, 0x4879F0, {"frame": 3, "timer": -1}),
    )
    for (action, site, change), cw in itertools.product(branches, (0x27F, 0x37F)):
        yield {**base, "cohort": "branches", "action": action, "required_site": site,
               "control_word": cw, **change}
    for case in previous.cases(True):
        yield {**case, "cohort": "integration"}
    for case in previous.cases():
        if case["cohort"] == "integration":
            yield case
    for action in (547, 548, 549, 552, 559):
        yield {**base, "cohort": "default", "action": action}
    for action in (561, 600, 616, 700, 798, 799, 32767):
        yield {**base, "cohort": "handoff", "action": action}


class Probe(previous.Probe):
    resource_keys = KEYS
    handled_action_max = 560

    def step(self, uc, address, size):
        super().step(uc, address, size)
        if address == 0x465190 and self.spawn_request[1] in (822, 825):
            request = self.spawn_request
            pointer, count = request[6:8]
            expected_count = 4 if request[1] == 822 else 3
            sp = uc.reg_read(low.r.UC_X86_REG_ESP)
            if count != expected_count or pointer & 3 or not sp <= pointer <= pointer+count*4 <= low.STACK+0x10000:
                raise ValueError("550-family parameters escaped the active supplied stack")
            self.spawn_request = (*request[:6], struct.unpack("<"+"I"*count, uc.mem_read(pointer, count*4)), count)


def check_target_case(case, result, sites):
    previous.check_target_case(case, result, sites)
    if case["cohort"] == "ring":
        request = result["spawn_request"]
        if case["timer"] <= 9:
            if request is None or request[:2] != (0x465190, 822):
                raise ValueError("ring fixture bypassed the first822 request")
            if result["actor"][0x17C] != 10:
                raise ValueError("822 request bypassed17C=10")
        elif request is not None:
            raise ValueError("late timer unexpectedly emits a ring request")
    if case["cohort"] == "request825":
        if result["spawn_request"] is None or result["spawn_request"][:2] != (0x465190, 825):
            raise ValueError("560 fixture bypassed the actual825 request")


COHORT_COUNTS = {"motion": 324, "ring": 480, "gates": 648, "alpha": 144,
                 "nodes": 432, "request825": 90, "branches": 22,
                 "integration": 513, "default": 5, "handoff": 7}
SMOKE_COUNT = 36


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
        parser.exit(2, f"Reimu mid-550 audit failed: {error}\n")
    print(json.dumps(result, indent=2))
    raise SystemExit(1 if result["mismatch_count"] else 0)
