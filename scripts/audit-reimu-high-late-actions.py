#!/usr/bin/env python3
"""Compare Reimu650..711 using target-pinned native execution."""
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
spec = importlib.util.spec_from_file_location("reimu_high_late_previous", ROOT / "scripts/audit-reimu-high-middle-actions.py")
previous = importlib.util.module_from_spec(spec)
sys.modules[spec.name] = previous
spec.loader.exec_module(previous)
low, SYMBOL = previous.low, previous.SYMBOL
ACTIONS = (650, 651, 658, 669, 695, 696, 710, 711)
KEYS = (*previous.KEYS, 704)
HELPERS, CALL_TARGETS = previous.HELPERS, previous.CALL_TARGETS
SUPPORT_PATHS = (Path(previous.__file__), *previous.SUPPORT_PATHS)
LITERAL_BINDINGS = {**previous.LITERAL_BINDINGS,
                    "c046800000000000": 0x6C3CC8, "3e4ccccd": 0x6C3CC0,
                    "4010000000000000": 0x6C0CC8, "3ff8000000000000": 0x6C0EA8,
                    "4042000000000000": 0x6C3CB8}
SCHEMA = "th105-reimu-high-late-native-v1"
SCOPE = ("integrated source through711; native helpers/RET ABI and first world "
         "request; 869 counts3/4 both compared in full,900 count3; bounded animation/"
         "texture/manager context, original match selector as runtime input; no "
         "returning world requests, complete volleys, active event/backend context, "
         "full-root or canonical-exact claim")
MATCH_SELECTOR = 0x6FA894


def cases(smoke=False):
    base = {**next(previous.cases(True)), "match_selector": 0,
            "stored_motion": (0x40400000, 0x41000000, 0x3E99999A)}
    if smoke:
        for action, change in itertools.product(ACTIONS, (
                {}, {"sequence": 1, "counter": 0},
                {"sequence": 1, "counter": 180},
                {"sequence": 1, "counter": 240},
                {"sequence": 0, "frame": 2, "timer": -1},
                {"sequence": 0, "frame": 6, "timer": -1},
                {"sequence": 1, "counter": -1, "timer": -1, "y": 100.0},
                {"sequence": 2, "vy": 0xC0400000},
                {"sequence": 4, "frame": 1, "timer": -1},
                {"sequence": 4, "frame": 1, "timer": -1, "match_selector": 3},
                {"sequence": 3, "counter": 20, "y": 100.0},
                {"sequence": 6},
                {"single_sequence": True, "transition": "terminal"})):
            yield {**base, "cohort": "smoke", "action": action, **change}
        return
    for action, sequence, change, cw in itertools.product(ACTIONS, range(9), (
            {}, {"counter": -1, "timer": -1}, {"y": 100.0},
            {"vy": 0xC0400000}, {"vy": 0x7FC12345},
            {"single_sequence": True, "transition": "terminal"}), (0x27F, 0x37F)):
        yield {**base, "cohort": "motion", "action": action, "sequence": sequence,
               "control_word": cw, **change}
    for action, sequence, counter, timer, frame in itertools.product(
            ACTIONS, range(9), (-1, 0), (-1, 0), (0, 1, 2, 3, 4, 5, 6, 10)):
        yield {**base, "cohort": "nodes", "action": action, "sequence": sequence,
               "counter": counter, "timer": timer, "frame": frame}
    for action, count, word, facing, cw in itertools.product(
            (650, 651), (-5, -1, 0, 1, 5, 30, 31, 60, 61),
            (-32768, -1, 0, 4, 5, 9, 10, 32767), (-128, -1, 1, 127), (0x27F, 0x37F)):
        yield {**base, "cohort": "shots", "action": action, "sequence": 1,
               "counter": count, "counter730": word, "facing": facing, "control_word": cw}
    for count, phase, facing, cw in itertools.product(
            (-10, -8, -3, -2, -1, 0, 1, 2, 8, 10, 178, 179, 180, 181, 239, 240, 241),
            (0.0, 5.0, 45.0, 90.0), (-128, -1, 0, 1, 127), (0x27F, 0x37F)):
        yield {**base, "cohort": "burst669", "action": 669, "sequence": 1,
               "counter": count, "speed": phase, "facing": facing, "control_word": cw}
    peers = ((512.0, 100.0), (640.0, 100.0), (1000.0, -50.0), (100.0, 400.0), (700.0, -200.0))
    for action, mode, facing, (x, y), cw in itertools.product(
            (710, 711), (0, 1, 2, 3, 4, 0xFFFFFFFF), (-128, -1, 0, 1, 127), peers, (0x27F, 0x37F)):
        yield {**base, "cohort": "patterns", "action": action, "sequence": 4,
               "frame": 1, "timer": -1, "match_selector": mode, "facing": facing,
               "peer": struct.unpack("<I", struct.pack("<f", x))[0],
               "peer_y": y, "control_word": cw}
    for action, stored, cw in itertools.product((710, 711),
            ((0x40400000, 0x41000000, 0x3E99999A), (0xC1000000, 0x40800000, 0x3F000000),
             (0x80000000, 0x7FC12345, 0)), (0x27F, 0x37F)):
        yield {**base, "cohort": "snapshot", "action": action, "sequence": 1,
               "counter": -1, "timer": -1, "stored_motion": stored, "control_word": cw}
    for speed, frame, cw in itertools.product(
            (0, 0x80000000, 0x3F000000, 0x3FC00000, 0x40000000, 0xBF800000, 0x7FC12345),
            (0, 3, 4), (0x27F, 0x37F)):
        yield {**base, "cohort": "friction", "action": 696, "vx": speed,
               "frame": frame, "timer": -1, "control_word": cw}
    branches = (
        (650, 0x4852F6, {"sequence": 1, "counter": 31}),
        (650, 0x48A2B0, {"sequence": 2, "vy": 0xC0400000}),
        (650, 0x48A3AF, {"sequence": 1, "counter": 0, "counter730": 4}),
        (650, 0x4886BE, {"frame": 2, "timer": -1}),
        (651, 0x47D7BE, {"sequence": 1, "counter": 61}),
        (651, 0x48A2B0, {"sequence": 2, "vy": 0xC0400000}),
        (651, 0x48A55A, {"sequence": 1, "counter": 0, "counter730": 9}),
        (651, 0x4888FB, {"frame": 2, "timer": -1}),
        (658, 0x47D7BE, {"sequence": 1, "counter": 21}),
        (658, 0x48A6FF, {"sequence": 2, "vy": 0xC0400000}),
        (658, 0x48A768, {"frame": 4, "timer": -1}),
        (658, 0x48A7EC, {"frame": 5, "timer": -1}),
        (658, 0x48A824, {"frame": 10, "timer": -1}),
        (658, 0x48A85A, {"sequence": 3, "counter": -1, "timer": -1}),
        (658, 0x48A912, {"sequence": 4, "counter730": 1, "counter732": 1, "counter734": 0}),
        (669, 0x48A9AF, {"sequence": 1, "counter": 240}),
        (669, 0x48AA9F, {"sequence": 1, "counter": 180}),
        (669, 0x48AD0B, {"sequence": 2, "vy": 0xC0400000}),
        (669, 0x48AD7C, {"sequence": 1, "counter": -1, "timer": -1}),
        (669, 0x48ADF4, {"frame": 2, "timer": -1}),
        (695, 0x48AE9B, {"frame": 6, "timer": -1}),
        (696, 0x48AFFB, {"frame": 3, "timer": -1}),
        (696, 0x48B027, {"frame": 4, "timer": -1}),
        (710, 0x48B079, {"sequence": 2, "vy": 0xC0400000}),
        (711, 0x48B079, {"sequence": 2, "vy": 0xC0400000}),
        (710, 0x48B0E9, {"sequence": 1, "counter": -1, "timer": -1}),
        (711, 0x48B6E2, {"sequence": 1, "counter": -1, "timer": -1}),
        (710, 0x48B12A, {"sequence": 3, "counter": 19, "y": 100.0}),
        (711, 0x48B723, {"sequence": 3, "counter": 19, "y": 100.0}),
        (710, 0x48B645, {"sequence": 4, "frame": 3, "timer": -1}),
        (711, 0x48B645, {"sequence": 4, "frame": 3, "timer": -1}),
        (710, 0x48B040, {"sequence": 6, "y": 100.0}),
        (711, 0x48B665, {"sequence": 6, "y": 100.0}),
    )
    for (action, site, change), cw in itertools.product(branches, (0x27F, 0x37F)):
        yield {**base, "cohort": "branches", "action": action, "required_site": site,
               "control_word": cw, **change}
    for case in previous.cases(True):
        yield {**case, "cohort": "integration"}
    for case in previous.cases():
        if case["cohort"] == "integration":
            yield case
    for action in (620, 649, 652, 668, 670, 700):
        yield {**base, "cohort": "default", "action": action}
    for action in (712, 720, 730, 760, 798, 799, 32767):
        yield {**base, "cohort": "handoff", "action": action}


class Probe(previous.Probe):
    resource_keys = KEYS
    handled_action_max = 711
    #619 supplies4 floats;669 supplies3 to the same real object869 API.
    parameter_counts_869 = (3, 4)

    def prepare_extra_case(self, case):
        super().prepare_extra_case(case)
        self.engine.mem_write(MATCH_SELECTOR, struct.pack("<I", case.get("match_selector", 0)))

    def extra_actor_fields(self, case):
        stored = case.get("stored_motion", (0x40400000, 0x41000000, 0x3E99999A))
        return (*super().extra_actor_fields(case), *( (0x780+4*i, "I", value) for i, value in enumerate(stored)))

    def step(self, uc, address, size):
        super().step(uc, address, size)
        if address == 0x465190 and self.spawn_request[1] == 900:
            request = self.spawn_request
            pointer, count = request[6:8]
            sp = uc.reg_read(low.r.UC_X86_REG_ESP)
            if count != 3 or pointer & 3 or not sp <= pointer <= pointer+12 <= low.STACK+0x10000:
                raise ValueError("900 parameters escaped the active supplied stack")
            self.spawn_request = (*request[:6], struct.unpack("<III", uc.mem_read(pointer, 12)), count)


def check_target_case(case, result, sites):
    previous.check_target_case(case, result, sites)
    if case["cohort"] == "patterns":
        if case["match_selector"] <= 3:
            mode_sites = {710: (0x48B50D, 0x48B3EC, 0x48B2CB, 0x48B1A6),
                          711: (0x48BB21, 0x48B9F1, 0x48B8C2, 0x48B79B)}
            if mode_sites[case["action"]][case["match_selector"]] not in sites:
                raise ValueError("mode fixture bypassed its original table arm")
            if result["spawn_request"] is None or result["spawn_request"][:2] != (0x465190, 900):
                raise ValueError("mode fixture bypassed the advertised first900 request")
        elif result["spawn_request"] is not None:
            raise ValueError("out-of-range match selector unexpectedly emits an object")

    if case["cohort"] == "shots":
        cutoff, limit, object_id = (30, 5, 850) if case["action"] == 650 else (60, 10, 853)
        expected = case["counter"] <= cutoff and case["counter"] % 5 == 0 and case["counter730"] < limit
        request = result["spawn_request"]
        if (request is not None) != expected or (expected and request[:2] != (0x465190, object_id)):
            raise ValueError("shot fixture bypassed its advertised signed gate")
    if case["cohort"] == "burst669":
        expected = case["counter"] <= 180 and case["counter"] % 2 == 0
        request = result["spawn_request"]
        if (request is not None) != expected or (expected and (request[:2] != (0x465190, 869) or request[-1] != 3)):
            raise ValueError("669 fixture bypassed the advertised first three-float ray")
        required = 0x48AA9F if expected else 0x48A9AF if case["counter"] >= 240 else 0x48AD34
        if required not in sites:
            raise ValueError("669 fixture bypassed its original cutoff arm")
    if case["cohort"] == "snapshot":
        required = 0x48B0E9 if case["action"] == 710 else 0x48B6E2
        if required not in sites:
            raise ValueError("snapshot fixture bypassed the original saved-motion reads")


COHORT_COUNTS = {"motion": 864, "nodes": 2304, "shots": 1152, "burst669": 680,
                 "patterns": 600, "snapshot": 12, "friction": 42, "branches": 66,
                 "integration": 748, "default": 6, "handoff": 7}
SMOKE_COUNT = 104


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
        parser.exit(2, f"Reimu high-late audit failed: {error}\n")
    print(json.dumps(result, indent=2))
    raise SystemExit(1 if result["mismatch_count"] else 0)
