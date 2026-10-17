#!/usr/bin/env python3
"""Compare eight520-family bodies inside the integrated Reimu source."""
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
spec = importlib.util.spec_from_file_location("reimu_520_previous", ROOT / "scripts/audit-reimu-mid-510-actions.py")
previous = importlib.util.module_from_spec(spec)
sys.modules[spec.name] = previous
spec.loader.exec_module(previous)
low, SYMBOL = previous.low, previous.SYMBOL
ACTIONS = (520, 521, 522, 523, 525, 526, 530, 531)
KEYS = (*previous.KEYS, *ACTIONS)
HELPERS = {**previous.HELPERS, 0x478DD0: (18, "sqrt_float")}
CALL_TARGETS = {**previous.CALL_TARGETS, "sqrt_float_value": 0x478DD0}
SUPPORT_PATHS = (Path(previous.__file__), *previous.SUPPORT_PATHS)
LITERAL_BINDINGS = {
    **previous.LITERAL_BINDINGS,
    "43070000": 0x6C3DC4, "4713c100": 0x6C3DC0,
    "402e000000000000": 0x6C3DB8, "c3070000": 0x6C3DB0,
    "43610000": 0x6C3DAC, "c2e60000": 0x6C3DA8,
    "477e0100": 0x6C3DA4, "42e60000": 0x6C3DA0,
    "43a50000": 0x6C3D9C, "47fafa00": 0x6C3D98,
    "43d20000": 0x6C3D94, "483a5400": 0x6C3D90,
    "405ac00000000000": 0x6C0ED0, "405f400000000000": 0x6C1898,
    "42b40000": 0x6C3D8C, "c2b40000": 0x6C3D88,
    "4062c00000000000": 0x6C3D80, "4024000000000000": 0x6D6EC0,
}
SCHEMA = "th105-reimu-mid-520-native-v1"
SCOPE = ("integrated entry/low/middle through531; actual native helpers and RET ABI; "
         "first815/816/817 request and payload; supplied read-only animation/flat/"
         "zero-handle context; no returning world request, later trajectory math, "
         "complete volleys, full-root or canonical-exact claim")


def firing_profiles(action):
    if action <= 523:
        for timer, frame in itertools.product((-1, 0, 1), (0, 2, 7)):
            yield {"sequence": 3, "counter": 0, "timer": timer, "frame": frame}
    elif action <= 526:
        for counter in (-1, 0, 7):
            yield {"sequence": 0, "counter": counter, "timer": -1, "frame": 7}
    else:
        yield {"sequence": 1, "counter": -1, "timer": -1, "frame": 0}


def cases(smoke=False):
    base = {**next(previous.cases(True)), "skill609": 3}
    if smoke:
        for action in ACTIONS:
            for change in ({}, {"sequence": 1, "counter": 18},
                           {"sequence": 1, "counter": 11},
                           {"sequence": 2, "counter": 51},
                           {"sequence": 4, "vy": 0xC0400000},
                           {"sequence": 5, "counter": -1, "timer": -1},
                           {"single_sequence": True, "transition": "terminal"},
                           next(firing_profiles(action))):
                yield {**base, "cohort": "smoke", "action": action, **change}
        return
    for action, sequence, change, cw in itertools.product(ACTIONS, range(7), (
            {}, {"counter": -1, "timer": -1}, {"y": 100.0},
            {"vy": 0xC0400000}, {"vy": 0x7FC12345},
            {"single_sequence": True, "transition": "terminal"}), (0x27F, 0x37F)):
        yield {**base, "cohort": "motion", "action": action, "sequence": sequence,
               "control_word": cw, **change}
    for action in ACTIONS:
        for change, facing, phase, cw in itertools.product(
                firing_profiles(action), (-128, -1, 0, 1, 127), (0, 3, 4), (0x27F, 0x37F)):
            yield {**base, "cohort": "firing", "action": action, "facing": facing,
                   "phase55a": phase, "scale": 1.25, "control_word": cw, **change}
    for action in ACTIONS:
        pairs = ([(1, count) for count in (-1, 0, 1)] if action <= 523 else
                 [(1, count) for count in (9, 10, 11)] + [(2, count) for count in (49, 50, 51)]
                 if action <= 526 else [(1, count) for count in (17, 18, 19)])
        for (sequence, count), cw in itertools.product(pairs, (0x27F, 0x37F)):
            yield {**base, "cohort": "cutoff", "action": action, "sequence": sequence,
                   "counter": count, "control_word": cw}
    for action, sequence, counter, timer, frame in itertools.product(
            ACTIONS, (0, 1, 3, 5), (-1, 0, 1), (-1, 0, 1), (0, 1, 7)):
        yield {**base, "cohort": "gating", "action": action, "sequence": sequence,
               "counter": counter, "timer": timer, "frame": frame}
    branches = (
        (520, 0x4852C7, {}), (521, 0x4852C7, {}),
        (522, 0x48599F, {"sequence": 5}), (523, 0x485D75, {"sequence": 5}),
        (522, 0x47FFA2, {"vy": 0xC0400000}), (523, 0x47FFA2, {"vy": 0xC0400000}),
        (522, 0x48748C, {"sequence": 5, "counter": -1, "timer": -1}),
        (523, 0x485DBE, {"sequence": 5, "counter": -1, "timer": -1}),
        (525, 0x4852F6, {"sequence": 1, "counter": 11}),
        (526, 0x4852F6, {"sequence": 2, "counter": 51}),
        (530, 0x47D7BE, {"sequence": 1, "counter": 18}),
        (531, 0x4852F6, {"sequence": 1, "counter": 18}),
    )
    for (action, site, change), cw in itertools.product(branches, (0x27F, 0x37F)):
        yield {**base, "cohort": "branches", "action": action, "required_site": site,
               "control_word": cw, **change}
    for case in previous.cases(True):
        yield {**case, "cohort": "integration"}
    for case in previous.cases():
        if case["cohort"] == "integration":
            yield case
    for action in (514, 519, 524, 527, 528, 529):
        yield {**base, "cohort": "default", "action": action}
    for action in (532, 540, 551, 560, 561, 798, 32767):
        yield {**base, "cohort": "handoff", "action": action}


class Probe(previous.Probe):
    helpers = HELPERS
    resource_keys = KEYS
    handled_action_max = 531

    def extra_actor_fields(self, case):
        return (*super().extra_actor_fields(case), (0x609, "b", case.get("skill609", 3)))

    def helper_receiver(self, address):
        if address == 0x478DD0:
            return None
        return super().helper_receiver(address)

    def step(self, uc, address, size):
        super().step(uc, address, size)
        if address == 0x465190 and self.spawn_request[1] in (815, 816, 817):
            request = self.spawn_request
            pointer, count = request[6:8]
            sp = uc.reg_read(low.r.UC_X86_REG_ESP)
            if count != 3 or pointer & 3 or not sp <= pointer <= pointer+12 <= low.STACK+0x10000:
                raise ValueError("520-family parameters escaped the active supplied stack")
            self.spawn_request = (*request[:6], struct.unpack("<III", uc.mem_read(pointer, 12)), count)


def check_target_case(case, result, sites):
    previous.charge.shot.check_target_case(case, result, sites)
    if case["cohort"] == "firing":
        expected_id = 815 if case["action"] <= 523 else 816 if case["action"] <= 526 else 817
        if result["spawn_request"] is None or result["spawn_request"][:2] != (0x465190, expected_id):
            raise ValueError("firing fixture bypassed the observed first object request")
        expected_flag = {815: 1, 816: 5, 817: 9}[expected_id]
        if result["actor"][0x17C] != expected_flag:
            raise ValueError("first request bypassed the observed17C store")


COHORT_COUNTS = {"motion": 672, "firing": 1320, "cutoff": 60, "gating": 864,
                 "branches": 24, "integration": 409, "default": 6, "handoff": 7}
SMOKE_COUNT = 64


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
        parser.exit(2, f"Reimu mid-520 audit failed: {error}\n")
    print(json.dumps(result, indent=2))
    raise SystemExit(1 if result["mismatch_count"] else 0)
