#!/usr/bin/env python3
"""Native comparison of integrated Reimu410/412/414/416/418 source."""
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
spec = importlib.util.spec_from_file_location("reimu_shot_projectiles", ROOT / "scripts/audit-reimu-mid-projectile-actions.py")
projectile = importlib.util.module_from_spec(spec)
sys.modules[spec.name] = projectile
spec.loader.exec_module(projectile)
low = projectile.low
SYMBOL = projectile.SYMBOL
ACTIONS = (410, 412, 414, 416, 418)
KEYS = (*projectile.KEYS, *ACTIONS)
HELPERS, CALL_TARGETS = projectile.HELPERS, projectile.CALL_TARGETS
SUPPORT_PATHS = (Path(projectile.__file__), *projectile.SUPPORT_PATHS)
LITERAL_BINDINGS = {**projectile.LITERAL_BINDINGS,
                    "404c800000000000": 0x6C3E08,
                    "405b000000000000": 0x6C3E00,
                    "4068a00000000000": 0x6C3DF8,
                    "40d00000": 0x6C3DF0, "42340000": 0x6C3DEC,
                    "3f59999a": 0x6C3DE8}
SCHEMA = "th105-reimu-mid-shot-native-v1"
SCOPE = ("integrated entry/low/middle through418; actual native helpers/math/MT/wave "
         "and RET ABI; real object/effect entries with three/four-float payloads; "
         "later source pending; supplied read-only animation/flat/zero-handle "
         "context; no returning world requests, full-root or canonical-exact claim")


def cases(smoke=False):
    base = {**next(projectile.cases(True)), "action": 410, "held6c4": 1, "field744": -123.0}
    if smoke:
        for action, change in itertools.product(ACTIONS, (
                {}, {"sequence": 1, "counter": -1, "timer": -1},
                {"sequence": 3, "counter": -1, "timer": -1},
                {"frame": 8, "timer": -1}, {"frame": 5, "timer": -1},
                {"sequence": 2, "frame": 2, "timer": -1},
                {"sequence": 2, "frame": 1, "timer": -1},
                {"frame": 4, "timer": -1}, {"sequence": 1, "counter": 24},
                {"single_sequence": True, "transition": "terminal"})):
            yield {**base, "cohort": "smoke", "action": action, **change}
        return
    for action, sequence, change, cw in itertools.product(ACTIONS, range(9), (
            {}, {"counter": -1, "timer": -1}, {"y": 100.0},
            {"vy": 0xC0400000}, {"vy": 0x7FC12345},
            {"single_sequence": True, "transition": "terminal"}), (0x27F, 0x37F)):
        yield {**base, "cohort": "motion", "action": action, "sequence": sequence,
               "control_word": cw, **change}
    frames = {410: (0, 2, 6, 8), 412: (0, 5), 414: (0, 1, 4, 5, 8),
              416: (0, 1, 3, 4), 418: (0, 2, 3)}
    for action in ACTIONS:
        for frame, sequence, latch, held, cw in itertools.product(
                frames[action], range(4), (0, 1, 2), (0, 1), (0x27F, 0x37F)):
            yield {**base, "cohort": "frames", "action": action, "frame": frame,
                   "sequence": sequence, "timer": -1, "latch750": latch,
                   "held6c4": held, "control_word": cw}
    for action, sequence, count, cw in itertools.product(
            ACTIONS, (0, 1, 2), (-1, 0, 19, 20, 21, 23, 24, 25), (0x27F, 0x37F)):
        yield {**base, "cohort": "counters", "action": action, "sequence": sequence,
               "counter": count, "control_word": cw}
    for action, node, x, y, facing, cw in itertools.product(
            (410, 414), (0, 1), (0x43A00000, 0x44800000), (-100.0, 100.0),
            (-128, -1, 0, 1, 127), (0x27F, 0x37F)):
        yield {**base, "cohort": "aiming", "action": action,
               "sequence": 0 if node == 0 else 2,
               "frame": (8 if action == 410 else 5) if node == 0 else (2 if action == 410 else 1),
               "timer": -1, "peer": x, "peer_y": y, "facing": facing,
               "control_word": cw}
    for action, node, phase, scale, cw in itertools.product(
            (410, 414, 416), (0, 1), (-128, 3, 4, 127),
            (0.6600000262260437, 1.25), (0x27F, 0x37F)):
        frame = (8 if action == 410 else 5 if action == 414 else 4) if node == 0 else (2 if action == 410 else 1)
        yield {**base, "cohort": "cost", "action": action,
               "sequence": 0 if node == 0 else 2, "frame": frame, "timer": -1,
               "phase55a": phase, "scale": scale, "control_word": cw}
    for vx, cw in itertools.product((0xC0400000, 0x80000000, 0, 0x3FFFFFFF,
                                     0x40000000, 0x40000001, 0x40A00000, 0x7FC12345),
                                    (0x27F, 0x37F)):
        yield {**base, "cohort": "friction", "action": 418, "sequence": 2,
               "vx": vx, "control_word": cw}
    branches = (
        (410, 0x47F595, {"frame": 6, "timer": -1, "latch750": 2}),
        (410, 0x47F6F5, {"frame": 8, "timer": -1}),
        (410, 0x47F86B, {"sequence": 2, "frame": 2, "timer": -1}),
        (410, 0x4852F6, {"sequence": 1, "counter": 24}),
        (412, 0x47F96B, {"frame": 5, "timer": -1}),
        (412, 0x47BFBF, {"sequence": 3, "counter": -1, "timer": -1}),
        (412, 0x47E5D7, {"sequence": 1, "counter": 20}),
        (414, 0x47AD16, {"frame": 8, "vy": 0xC0400000}),
        (414, 0x47FB24, {"frame": 4, "timer": -1, "latch750": 2}),
        (414, 0x47FC8B, {"frame": 5, "timer": -1}),
        (414, 0x47FE0A, {"sequence": 2, "frame": 1, "timer": -1}),
        (414, 0x47EDAB, {"sequence": 1, "counter": -1, "timer": -1}),
        (416, 0x47FFBE, {"frame": 4, "vy": 0xC0400000}),
        (416, 0x47FF5A, {"frame": 3, "timer": -1, "latch750": 2}),
        (416, 0x4800B3, {"frame": 4, "timer": -1}),
        (416, 0x4801C9, {"sequence": 2, "frame": 1, "timer": -1}),
        (416, 0x48748C, {"sequence": 1, "counter": -1, "timer": -1}),
        (418, 0x480245, {"vy": 0xC0400000}),
        (418, 0x4802DD, {"frame": 3, "timer": -1}),
    )
    for (action, site, change), cw in itertools.product(branches, (0x27F, 0x37F)):
        yield {**base, "cohort": "branches", "action": action,
               "required_site": site, "control_word": cw, **change}
    for case in projectile.cases(True):
        yield {**base, **case, "cohort": "integration"}
    for case in projectile.cases():
        if case["cohort"] == "integration":
            yield {**base, **case}
    for action in (409, 411, 413, 415, 417):
        yield {**base, "cohort": "default", "action": action}
    for action in (419, 500, 551, 560, 561, 798, 32767):
        yield {**base, "cohort": "handoff", "action": action}


class Probe(projectile.Probe):
    resource_keys = KEYS
    handled_action_max = 418

    def extra_actor_fields(self, case):
        return (*super().extra_actor_fields(case),
                (0x6C4, "i", case["held6c4"]), (0x744, "f", case["field744"]))

    def step(self, uc, address, size):
        super().step(uc, address, size)
        if address == 0x465190 and self.spawn_request[1] in (801, 808):
            request = self.spawn_request
            pointer, count = request[6:8]
            expected_count = 4 if request[1] == 801 else 3
            sp = uc.reg_read(low.r.UC_X86_REG_ESP)
            if (count != expected_count or pointer & 3
                    or not sp <= pointer <= pointer+count*4 <= low.STACK+0x10000):
                raise ValueError("shot parameters escaped the active supplied stack")
            self.spawn_request = (*request[:6], struct.unpack("<"+"I"*count, uc.mem_read(pointer, count*4)), count)


def check_target_case(case, result, sites):
    projectile.check_target_case(case, result, sites)


COHORT_COUNTS = {"motion": 540, "frames": 864, "counters": 240, "aiming": 160,
                 "cost": 96, "friction": 16, "branches": 38, "integration": 251,
                 "default": 5, "handoff": 7}
SMOKE_COUNT = 50


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
        parser.exit(2, f"Reimu mid-shot audit failed: {error}\n")
    print(json.dumps(result, indent=2))
    raise SystemExit(1 if result["mismatch_count"] else 0)
