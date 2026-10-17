#!/usr/bin/env python3
"""Compare four540-family bodies inside the integrated Reimu source."""
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
spec = importlib.util.spec_from_file_location("reimu_540_previous", ROOT / "scripts/audit-reimu-mid-520-actions.py")
previous = importlib.util.module_from_spec(spec)
sys.modules[spec.name] = previous
spec.loader.exec_module(previous)
low, SYMBOL = previous.low, previous.SYMBOL
ACTIONS = (540, 541, 545, 546)
KEYS = (*previous.KEYS, *ACTIONS)
HELPERS, CALL_TARGETS = previous.HELPERS, previous.CALL_TARGETS
SUPPORT_PATHS = (Path(previous.__file__), *previous.SUPPORT_PATHS)
LITERAL_BINDINGS = {
    **previous.LITERAL_BINDINGS,
    "42c80000": 0x6D6EE4, "3fb99999a0000000": 0x6CD1E0,
    "3fc99999a0000000": 0x6C0E80, "3fe6666660000000": 0x6C2A78,
    "43480000": 0x6C1A8C, "40c00000": 0x6CD1D8,
    "41000000": 0x6C2874, "40f00000": 0x6C3E54,
    "c1c00000": 0x6C3D78, "3ff0000000000000": 0x6CD160,
    "3fe99999a0000000": 0x6C2A68, "42480000": 0x6C3D74,
    "41700000": 0x6C3EA0, "4059000000000000": 0x6CD190,
    "43af0000": 0x6C3D70, "40a00000": 0x6C3B70,
    "c0a00000": 0x6C3B58, "3f000000": 0x6CD140,
    "40400000": 0x6D6ED8, "4022000000000000": 0x6C3D68,
    "4041400000000000": 0x6C3D60, "41b00000": 0x6C3D58,
    "403e000000000000": 0x6C0F00, "4041c00000000000": 0x6C3D50,
    "4044000000000000": 0x6C13D0,
}
SCHEMA = "th105-reimu-mid-540-native-v1"
SCOPE = ("integrated entry/low/middle through546; actual native helpers and RET ABI; "
         "first821 request/payload and native trig; supplied read-only animation/"
         "flat/zero-handle context; no returning world request, later fan iterations, "
         "full-root or canonical-exact claim")


def cases(smoke=False):
    base = {**next(previous.cases(True)), "skill60a": 3, "visual_x": 0x3F000000,
            "visual_y": 0x3FC00000, "alpha": 100, "byte184": 73}
    if smoke:
        for action, change in itertools.product(ACTIONS, (
                {}, {"sequence": 0, "frame": 4, "timer": 0},
                {"sequence": 0, "frame": 5, "alpha": 26},
                {"sequence": 2, "counter": -1, "timer": -1, "y": 100.0},
                {"sequence": 3, "counter": -1, "timer": -1, "y": 100.0},
                {"sequence": 3, "counter": 8, "y": 100.0},
                {"sequence": 4}, {"sequence": 5, "counter": -1, "timer": -1},
                {"sequence": 2, "vy": 0xC0400000},
                {"single_sequence": True, "transition": "terminal"})):
            yield {**base, "cohort": "smoke", "action": action, **change}
        return
    for action, sequence, change, cw in itertools.product(ACTIONS, range(9), (
            {}, {"counter": -1, "timer": -1}, {"y": 100.0},
            {"vy": 0xC0400000}, {"vy": 0x7FC12345},
            {"single_sequence": True, "transition": "terminal"}), (0x27F, 0x37F)):
        yield {**base, "cohort": "motion", "action": action, "sequence": sequence,
               "control_word": cw, **change}
    for action, sequence, frame, scale, alpha, cw in itertools.product(
            ACTIONS, (0, 2), (3, 4, 5, 7),
            (0, 0x80000000, 0x3D4CCCCD, 0x3F733333, 0x3F800000, 0x3F866666, 0x7F800000, 0x7FC12345),
            (0, 24, 25, 26, 230, 231, 255), (0x27F, 0x37F)):
        yield {**base, "cohort": "visual", "action": action, "sequence": sequence,
               "frame": frame, "visual_x": scale, "alpha": alpha, "control_word": cw}
    for action, sequence, counter, timer, frame in itertools.product(
            ACTIONS, range(7), (-1, 0, 1), (-1, 0, 1), (0, 7)):
        yield {**base, "cohort": "nodes", "action": action, "sequence": sequence,
               "counter": counter, "timer": timer, "frame": frame, "y": 100.0}
    for (action, sequence), facing, y, cw in itertools.product(
            ((540, 2), (541, 1), (545, 2), (546, 2)), (-128, -1, 0, 1, 127),
            (0.0, 100.0, 250.0, 251.0, 1000.0), (0x27F, 0x37F)):
        yield {**base, "cohort": "launch", "action": action, "sequence": sequence,
               "facing": facing, "y": y, "counter": -1, "timer": -1, "control_word": cw}
    for action, skill, facing, phase, cw in itertools.product(
            (545, 546), (-128, -1, 0, 3, 4, 127), (-128, -1, 0, 1, 127),
            (0, 3, 4), (0x27F, 0x37F)):
        yield {**base, "cohort": "fan", "action": action, "sequence": 3,
               "skill60a": skill, "facing": facing, "phase55a": phase,
               "counter": -1, "timer": -1, "y": 100.0, "control_word": cw}
    for sequence, counter, state, word, cw in itertools.product(
            (3, 4), (14, 15, 16), (0, 1, -1), (-32768, -1, 4, 5, 6, 32767), (0x27F, 0x37F)):
        yield {**base, "cohort": "state", "action": 541, "sequence": sequence,
               "counter": counter, "state": state, "counter734": word, "control_word": cw}
    branches = (
        (540, 0x486509, {"frame": 4, "timer": 0}),
        (540, 0x4865F7, {"sequence": 3, "vy": 0xC0400000}),
        (540, 0x486669, {"sequence": 2, "counter": -1, "timer": -1}),
        (540, 0x486707, {"sequence": 2, "frame": 7, "timer": -1}),
        (541, 0x48686F, {"sequence": 2, "vy": 0xC0400000}),
        (541, 0x4868EB, {"sequence": 3, "counter": 16}),
        (541, 0x4869B2, {"sequence": 1, "counter": -1, "timer": -1}),
        (545, 0x486B80, {"sequence": 2, "vy": 0xC0400000}),
        (546, 0x486B80, {"sequence": 2, "vy": 0xC0400000}),
        (545, 0x47D7BE, {"sequence": 3, "counter": 8, "y": 100.0}),
        (546, 0x47D7BE, {"sequence": 3, "counter": 8, "y": 100.0}),
        (545, 0x47EDAB, {"sequence": 5, "counter": -1, "timer": -1, "y": 100.0}),
        (546, 0x48748C, {"sequence": 5, "counter": -1, "timer": -1, "y": 100.0}),
    )
    for (action, site, change), cw in itertools.product(branches, (0x27F, 0x37F)):
        yield {**base, "cohort": "branches", "action": action, "required_site": site,
               "control_word": cw, **change}
    for case in previous.cases(True):
        yield {**case, "cohort": "integration"}
    for case in previous.cases():
        if case["cohort"] == "integration":
            yield case
    for action in (532, 539, 542, 543, 544):
        yield {**base, "cohort": "default", "action": action}
    for action in (547, 550, 551, 560, 561, 798, 32767):
        yield {**base, "cohort": "handoff", "action": action}


class Probe(previous.Probe):
    resource_keys = KEYS
    handled_action_max = 546

    def extra_actor_fields(self, case):
        return (*super().extra_actor_fields(case),
                (0x110, "B", 13), (0x111, "B", 29), (0x112, "B", 47),
                (0x113, "B", case.get("alpha", 100)),
                (0x11C, "I", case.get("visual_x", 0x3F000000)),
                (0x120, "I", case.get("visual_y", 0x3FC00000)),
                (0x184, "B", case.get("byte184", 73)),
                (0x60A, "b", case.get("skill60a", 3)))

    def step(self, uc, address, size):
        super().step(uc, address, size)
        if address == 0x465190 and self.spawn_request[1] == 821:
            request = self.spawn_request
            pointer, count = request[6:8]
            sp = uc.reg_read(low.r.UC_X86_REG_ESP)
            if count != 3 or pointer & 3 or not sp <= pointer <= pointer+12 <= low.STACK+0x10000:
                raise ValueError("821 parameters escaped the active supplied stack")
            self.spawn_request = (*request[:6], struct.unpack("<III", uc.mem_read(pointer, 12)), count)


def check_target_case(case, result, sites):
    previous.previous.charge.shot.check_target_case(case, result, sites)
    if case["cohort"] == "fan" or case["cohort"] == "launch" and case["action"] in (545, 546):
        if result["spawn_request"] is None or result["spawn_request"][:2] != (0x465190, 821):
            raise ValueError("fan fixture bypassed the actual first821 request")
        if result["actor"][0x17C] != 6:
            raise ValueError("821 request bypassed the observed17C=6 store")


COHORT_COUNTS = {"motion": 432, "visual": 3584, "nodes": 504, "launch": 200,
                 "fan": 360, "state": 216, "branches": 26, "integration": 473,
                 "default": 5, "handoff": 7}
SMOKE_COUNT = 40


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
        parser.exit(2, f"Reimu mid-540 audit failed: {error}\n")
    print(json.dumps(result, indent=2))
    raise SystemExit(1 if result["mismatch_count"] else 0)
