#!/usr/bin/env python3
"""Compare the integrated Reimu500..508 family with native target execution."""
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
spec = importlib.util.spec_from_file_location("reimu_500_shots", ROOT / "scripts/audit-reimu-mid-shot-actions.py")
shot = importlib.util.module_from_spec(spec)
sys.modules[spec.name] = shot
spec.loader.exec_module(shot)
low = shot.low
SYMBOL = shot.SYMBOL
ACTIONS = (500, 501, 502, 503, 505, 506, 507, 508)
KEYS = (*shot.KEYS, *ACTIONS)
HELPERS, CALL_TARGETS = shot.HELPERS, shot.CALL_TARGETS
SUPPORT_PATHS = (Path(shot.__file__), *shot.SUPPORT_PATHS)
LITERAL_BINDINGS = {**shot.LITERAL_BINDINGS, "41b80000": 0x6C3DE4,
                    "41c80000": 0x6C3B3C, "41d80000": 0x6C3DE0,
                    "41d00000": 0x6C3DDC, "41e80000": 0x6C3DD8}
SCHEMA = "th105-reimu-mid-500-native-v1"
SCOPE = ("integrated entry/low/middle through508; actual native helpers and RET ABI; "
         "first real request entry/payload per volley; later source pending; "
         "supplied read-only animation/flat/zero-handle context; no returning "
         "world request, full-volley execution, full-root or canonical-exact claim")


def cases(smoke=False):
    base = {**next(shot.cases(True)), "action": 500, "byte17c": 73}
    if smoke:
        for action, change in itertools.product(ACTIONS, (
                {}, {"sequence": 1, "counter": 20},
                {"sequence": 1, "counter": 60, "level736": 1},
                {"sequence": 2, "frame": 2, "timer": 0, "level736": 0},
                {"sequence": 2, "frame": 1, "timer": 0, "level736": 2},
                {"sequence": 3, "counter": 29, "level736": 2},
                {"sequence": 4, "vy": 0xC0400000},
                {"sequence": 5, "counter": -1, "timer": -1},
                {"single_sequence": True, "transition": "terminal"})):
            yield {**base, "cohort": "smoke", "action": action, **change}
        return
    for action, sequence, change, cw in itertools.product(ACTIONS, range(7), (
            {}, {"counter": -1, "timer": -1}, {"y": 100.0},
            {"vy": 0xC0400000}, {"vy": 0x7FC12345},
            {"single_sequence": True, "transition": "terminal"}), (0x27F, 0x37F)):
        yield {**base, "cohort": "motion", "action": action, "sequence": sequence,
               "control_word": cw, **change}
    for action, level, facing, phase, cw in itertools.product(
            ACTIONS, (-1, 0, 1, 2, 3), (-128, -1, 0, 1, 127), (0, 3, 4), (0x27F, 0x37F)):
        yield {**base, "cohort": "volley", "action": action, "sequence": 2,
               "frame": 1 if action in (502, 503, 507, 508) else 2,
               "timer": 0, "level736": level, "facing": facing,
               "phase55a": phase, "scale": 1.25, "control_word": cw}
    for action, count, level, latch, held, cw in itertools.product(
            ACTIONS, (19, 20, 59, 60), (0, 1, 2),
            (0, 1, 2), ((0, 1), (1, 0), (65536, 65536)), (0x27F, 0x37F)):
        yield {**base, "cohort": "charge", "action": action, "sequence": 1,
               "counter": count, "level736": level, "latch750": latch,
               "held6c0": held[0], "held6c4": held[1], "control_word": cw}
    for action, level, count, cw in itertools.product(
            ACTIONS, (-32768, -1, 0, 1, 2, 32767), (9, 10, 19, 20, 29, 30),
            (0x27F, 0x37F)):
        yield {**base, "cohort": "tail", "action": action, "sequence": 3,
               "level736": level, "counter": count, "control_word": cw}
    branches = (
        (500, 0x4803EC, {"sequence": 2, "frame": 2, "timer": 0}),
        (501, 0x4808D1, {"sequence": 2, "frame": 2, "timer": 0}),
        (502, 0x480DD1, {"sequence": 2, "frame": 1, "timer": 0}),
        (503, 0x4812D0, {"sequence": 2, "frame": 1, "timer": 0}),
        (505, 0x481784, {"sequence": 2, "frame": 2, "timer": 0}),
        (506, 0x481ECC, {"sequence": 2, "frame": 2, "timer": 0}),
        (507, 0x4825F8, {"sequence": 2, "frame": 1, "timer": 0}),
        (508, 0x482D5F, {"sequence": 2, "frame": 1, "timer": 0}),
        (500, 0x480778, {"sequence": 1, "counter": 20}),
        (502, 0x480CD0, {"vy": 0xC0400000}),
        (503, 0x480CD0, {"vy": 0xC0400000}),
        (507, 0x4824FA, {"vy": 0xC0400000}),
        (508, 0x4824FA, {"vy": 0xC0400000}),
        (500, 0x48079F, {"sequence": 1, "counter": 60, "level736": 1}),
        (505, 0x481D98, {"sequence": 1, "counter": 60, "level736": 1}),
        (502, 0x48748C, {"sequence": 5, "counter": -1, "timer": -1}),
        (507, 0x48748C, {"sequence": 5, "counter": -1, "timer": -1}),
    )
    for (action, site, change), cw in itertools.product(branches, (0x27F, 0x37F)):
        yield {**base, "cohort": "branches", "action": action,
               "required_site": site, "control_word": cw, **change}
    for case in shot.cases(True):
        yield {**base, **case, "cohort": "integration"}
    for case in shot.cases():
        if case["cohort"] == "integration":
            yield {**base, **case}
    for action in (419, 450, 499, 504):
        yield {**base, "cohort": "default", "action": action}
    for action in (509, 510, 551, 560, 561, 798, 32767):
        yield {**base, "cohort": "handoff", "action": action}


class Probe(shot.Probe):
    resource_keys = KEYS
    handled_action_max = 508

    def extra_actor_fields(self, case):
        return (*super().extra_actor_fields(case), (0x17C, "B", case["byte17c"]),
                (0x736, "h", case.get("level736", case["turn_count"])))

    def step(self, uc, address, size):
        super().step(uc, address, size)
        if address == 0x465190 and self.spawn_request[1] in (810, 811):
            request = self.spawn_request
            pointer, count = request[6:8]
            sp = uc.reg_read(low.r.UC_X86_REG_ESP)
            if count != 3 or pointer & 3 or not sp <= pointer <= pointer+12 <= low.STACK+0x10000:
                raise ValueError("volley parameters escaped the active supplied stack")
            self.spawn_request = (*request[:6], struct.unpack("<III", uc.mem_read(pointer, 12)), count)


def check_target_case(case, result, sites):
    shot.check_target_case(case, result, sites)
    if case["cohort"] == "volley" and case["level736"] in (0, 1, 2):
        expected_id = 811 if case["action"] >= 505 else 810
        if result["spawn_request"] is None or result["spawn_request"][:2] != (0x465190, expected_id):
            raise ValueError("volley fixture bypassed the actual first object request")


COHORT_COUNTS = {"motion": 672, "volley": 1200, "charge": 1728, "tail": 576,
                 "branches": 34, "integration": 301, "default": 4, "handoff": 7}
SMOKE_COUNT = 72


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
        parser.exit(2, f"Reimu mid-500 audit failed: {error}\n")
    print(json.dumps(result, indent=2))
    raise SystemExit(1 if result["mismatch_count"] else 0)
