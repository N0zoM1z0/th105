#!/usr/bin/env python3
"""Compare integrated Reimu400..408 source with actual target helper execution."""
from __future__ import annotations

import argparse
import itertools
import json
from pathlib import Path
import struct
import sys

import unicorn

import linked_pe

ROOT = Path(__file__).resolve().parents[1]
import importlib.util
spec = importlib.util.spec_from_file_location("reimu_projectile_mid", ROOT / "scripts/audit-reimu-mid-normal-actions.py")
mid = importlib.util.module_from_spec(spec)
sys.modules[spec.name] = mid
spec.loader.exec_module(mid)
low = mid.low
SUPPORT_PATHS = (Path(mid.__file__),)
SYMBOL = mid.SYMBOL
ACTIONS = (400, 401, 402, 404, 406, 408)
# Supply real transition destinations and each current input action. Unrelated
# action resources need not be duplicated in every supplied animation graph.
KEYS = (0, 1, 2, 9, 10, 97, 204, 208, 209, 210, *ACTIONS, 669, 700)
MATH = {0x68BB70: (10, "crt_atan2_entry"),
        0x6965AB: (0x196, "crt_atan2_stack_entry_and_postprocessing"),
        0x6965F3: (0x14E, "crt_math_postprocessing"),
        0x696774: (60, "crt_math_load_argument"),
        0x690C07: (0x163, "crt_math_binary_dispatch_and_special_values"),
        0x69649C: (0x8C, "crt_atan2_table_kernels"),
        0x6964EC: (9, "crt_half_pi_kernel"),
        0x690D59: (17, "crt_math_special_status")}
HELPERS = {**mid.HELPERS, 0x406540: (63, "atan2_degrees"),
           0x4351A0: (26, "random_range"), 0x4067D0: (27, "random_roll"),
           0x478DF0: (107, "scaled_counter"), 0x45C030: (35, "wave_handle"), **MATH}
CALL_TARGETS = {**mid.CALL_TARGETS, "atan2_degrees": 0x406540,
                "selector_random_range": 0x4351A0, "add_scaled_counter": 0x478DF0,
                "dispatch_character_wave_handle": 0x45C030}
LITERAL_BINDINGS = {**mid.LITERAL_BINDINGS,
                    "4058000000000000": 0x6C3E38,
                    "4063c00000000000": 0x6C3E28,
                    "405d400000000000": 0x6C3E20,
                    "4052c00000000000": 0x6C3E10,
                    "404b800000000000": 0x6C3E30,
                    "4060e00000000000": 0x6C3E18, "40600000": 0x6C3448}
SCHEMA = "th105-reimu-mid-projectile-native-v1"
SCOPE = ("integrated entry/low/middle through408; actual native helpers, CRT atan2, "
         "MT range draws and RET ABI; real request entry and three-float payload "
         "comparison; later source pending; supplied read-only nine-sequence "
         "animation/flat/zero-handle context; no returning world requests, "
         "whole-game, unmasked exceptions or canonical-exact claim")


def cases(smoke=False):
    base = {**next(mid.cases(True)), "action": 400, "counter730": 0,
            "counter732": 0, "counter734": 10, "counter738": 1,
            "held6c0": 1, "peer_y": 100.0, "scale": 1.0, "phase55a": 0,
            "counter558": 32760, "flag47f": 1}
    if smoke:
        for action, change in itertools.product(ACTIONS, (
                {}, {"sequence": 2, "counter": -1, "timer": -1},
                {"sequence": 6, "counter": -1, "timer": -1},
                {"counter730": 3, "latch750": 0},
                {"counter730": 3, "latch750": 1},
                {"sequence": 8, "counter": -1, "timer": -1},
                {"sequence": 1, "counter": -1, "timer": -1},
                {"sequence": 1, "y": 0.0, "vy": 0xC0400000},
                {"sequence": 2, "counter": 21},
                {"single_sequence": True, "transition": "terminal"})):
            yield {**base, "cohort": "smoke", "action": action, **change}
        return
    for action, sequence, change, cw in itertools.product(ACTIONS, range(9), (
            {}, {"counter": -1, "timer": -1}, {"y": 100.0},
            {"vy": 0xC0400000}, {"counter": 21}, {"counter": 29}), (0x27F, 0x37F)):
        yield {**base, "cohort": "motion", "action": action, "sequence": sequence,
               "control_word": cw, **change}
    for action, count, shot, latch, cw in itertools.product(
            (400, 401, 402, 404, 406), (-32768, -1, 0, 1, 2, 3, 4, 32767),
            (-1, 0, 4, 5), (0, 1, 2), (0x27F, 0x37F)):
        yield {**base, "cohort": "firing", "action": action, "counter730": count,
               "counter732": shot, "latch750": latch, "control_word": cw}
    for action, sequence, peer_x, peer_y, facing, cw in itertools.product(
            (400, 401, 404, 406), (2, 6), (0x43A00000, 0x44200000, 0x44800000),
            (-100.0, 0.0, 100.0), (-128, -1, 0, 1, 127), (0x27F, 0x37F)):
        if peer_x == 0x44200000 and peer_y == 0.0 or facing == 0 and peer_y == 0.0:
            continue  # Returning CRT domain-error handling is outside this fixture.
        yield {**base, "cohort": "aiming", "action": action, "sequence": sequence,
               "counter": -1, "timer": -1, "peer": peer_x, "peer_y": peer_y,
               "facing": facing, "control_word": cw}
    for action, phase, scale, latch, seed in itertools.product(
            (400, 401, 404, 406), (-128, 0, 3, 4, 127),
            (0.0, 0.6600000262260437, 1.0, 1.25), (0, 1), (0, 5489, 0xFFFFFFFF)):
        yield {**base, "cohort": "cost_random", "action": action, "counter730": 3,
               "phase55a": phase, "scale": scale, "latch750": latch, "seed": seed}
    branches = (
        (400, 0x47DC89, {"counter730": 3, "latch750": 0}),
        (400, 0x47DDBB, {"counter730": 3, "latch750": 1}),
        (401, 0x47E1CC, {"counter730": 3, "latch750": 0}),
        (401, 0x47E2FD, {"counter730": 3, "latch750": 1}),
        (402, 0x47E705, {"sequence": 2, "counter": -1, "timer": -1}),
        (402, 0x47D7BE, {"sequence": 2, "counter": 11}),
        (404, 0x47E802, {"vy": 0xC0400000}),
        (404, 0x47E94D, {"counter730": 3, "latch750": 0}),
        (404, 0x47EA83, {"counter730": 3, "latch750": 1}),
        (406, 0x47EE01, {"vy": 0xC0400000}),
        (406, 0x47EF4C, {"counter730": 3, "latch750": 0}),
        (406, 0x47F082, {"counter730": 3, "latch750": 1}),
        (408, 0x47F3B8, {"frame": 2, "vy": 0xC0400000}),
        (408, 0x47F44A, {"frame": 2, "timer": -1}),
        (404, 0x47EB41, {"sequence": 1, "counter": -1, "timer": -1}),
        (406, 0x47F135, {"sequence": 1, "counter": -1, "timer": -1}),
    )
    for (action, site, change), cw in itertools.product(branches, (0x27F, 0x37F)):
        yield {**base, "cohort": "branches", "action": action,
               "required_site": site, "control_word": cw, **change}
    for case in mid.cases(True):
        yield {**base, **case, "cohort": "integration"}
    for case in mid.cases():
        if case["cohort"] == "integration":
            yield {**base, **case}
    for action in (323, 399, 403, 405, 407):
        yield {**base, "cohort": "default", "action": action}
    for action in (409, 410, 500, 551, 560, 561, 798, 32767):
        yield {**base, "cohort": "handoff", "action": action}


class Probe(mid.Probe):
    helpers = HELPERS
    resource_keys = KEYS
    handled_action_max = 408
    sequence_capacity = 9
    argument_helpers = mid.Probe.argument_helpers | {0x478DF0, 0x45C030, 0x4351A0, 0x4067D0}

    def helper_receiver(self, address):
        if address in (0x406540, 0x4351A0, 0x4067D0, *MATH):
            return None
        return super().helper_receiver(address)

    def extra_actor_fields(self, case):
        return (*super().extra_actor_fields(case), (0x164, "I", low.RESOURCE+0xD00),
                (0x20F0, "f", case["peer_y"]), (0x47F, "B", case["flag47f"]),
                (0x4D0, "f", case["scale"]), (0x558, "h", case["counter558"]),
                (0x55A, "b", case["phase55a"]), (0x6C0, "i", case["held6c0"]),
                (0x734, "h", case["counter734"]), (0x738, "h", case["counter738"]))

    def step(self, uc, address, size):
        super().step(uc, address, size)
        if address in (0x406540, 0x4351A0):
            self.calls.append(("native_args", address,
                               bytes(uc.mem_read(uc.reg_read(low.r.UC_X86_REG_ESP)+4, 8)).hex()))
        if address == 0x465190 and self.spawn_request[1] in (800, 807):
            request = self.spawn_request
            pointer, count = request[6:8]
            sp = uc.reg_read(low.r.UC_X86_REG_ESP)
            if count != 3 or not sp <= pointer <= pointer+12 <= low.STACK+0x10000:
                raise ValueError("projectile parameters escaped the active supplied stack")
            self.spawn_request = (*request[:6], struct.unpack("<III", uc.mem_read(pointer, 12)), count)


def check_target_case(case, result, sites):
    mid.check_target_case(case, result, sites)


COHORT_COUNTS = {"motion": 648, "firing": 960, "aiming": 608,
                 "cost_random": 480, "branches": 32, "integration": 191,
                 "default": 5, "handoff": 8}
SMOKE_COUNT = 60


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
        parser.exit(2, f"Reimu mid-projectile audit failed: {error}\n")
    print(json.dumps(result, indent=2))
    raise SystemExit(1 if result["mismatch_count"] else 0)
