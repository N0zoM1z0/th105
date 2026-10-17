#!/usr/bin/env python3
"""Execute the integrated entry/low/301..322 source against the canonical root.

Native helpers and callbacks execute unchanged. Compare actual world requests,
including the pointed three-float payload, without supplying callback results.
"""
from __future__ import annotations

import argparse
import importlib.util
import itertools
import json
from pathlib import Path
import struct
import sys

import unicorn

import linked_pe

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
spec = importlib.util.spec_from_file_location("reimu_mid_low_contract", ROOT / "scripts/audit-reimu-low-dispatch.py")
low = importlib.util.module_from_spec(spec)
sys.modules[spec.name] = low
spec.loader.exec_module(low)

SYMBOL = "?run_checked_action_dispatch@ReimuActionStatePreludeView@th105@@QAE_NXZ"
ACTIONS = (*range(301, 311), 320, 321, 322)
KEYS = tuple(sorted(set(low.KEYS) | set(ACTIONS)))
HELPERS, CALL_TARGETS = low.HELPERS, low.CALL_TARGETS
LITERAL_BINDINGS = {"3fe3333340000000": 0x6C3B48,
                    "402c000000000000": 0x6C1B10,
                    "4050400000000000": 0x6C3E48,
                    "40c00000": 0x6CD1D8, "41900000": 0x6C3E50,
                    "41400000": 0x6C12B0, "3f400000": 0x6C3C54,
                    "4051800000000000": 0x6C0CE0, "3f666666": 0x6C3E40}
SCHEMA = "th105-reimu-mid-normal-native-v1"
SCOPE = ("integrated entry/low/301..322 staged source; native helpers and RET ABI; "
         "actual wrapper entries compare arguments and three-float pointed payload; "
         "pending later actions stop at original mid selector; supplied read-only "
         "animation and flat/zero-handle context; no returning world requests, "
         "whole-game, floating-exception, full-root or canonical-exact claim")


def cases(smoke=False):
    base = {**next(low.cases(True)), "action": 301, "y": 0.0,
            "held6bc": 1, "latch750": 1}
    if smoke:
        for action, change in itertools.product(ACTIONS, (
                {}, {"sequence": 1}, {"sequence": 2, "counter": 12},
                {"frame": 4, "timer": -1}, {"frame": 3, "timer": -1},
                {"y": 0.0, "vy": 0xC0400000},
                {"counter": -1, "timer": -1, "transition": "block"},
                {"single_sequence": True, "transition": "terminal"})):
            yield {**base, "cohort": "smoke", "action": action, **change}
        return
    for action, sequence, change, cw in itertools.product(ACTIONS, range(7), (
            {}, {"y": 0.0, "vy": 0xC0400000},
            {"y": 0.0, "vy": 0x3F800000}, {"vy": 0x7FC12345},
            {"counter": 12, "vx": 0x41900000},
            {"counter": 13, "vx": 0x80000000}, {"y": 100.0}), (0x27F, 0x37F)):
        yield {**base, "cohort": "motion", "action": action, "sequence": sequence,
               "control_word": cw, **change}
    for action, vx, flag, cw in itertools.product(
            (301, 302, 303, 304, 305, 310, 320, 321, 322),
            (0xC0400000, 0x80000000, 0, 0x3F000000, 0x3F19999A, 0x3F800000,
             0x3FC00000, 0x40000000, 0x40C00000, 0x41600000, 0x41600001, 0x7FC12345),
            (0, 1, 128, 255), (0x27F, 0x37F)):
        yield {**base, "cohort": "friction", "action": action, "frame": 5,
               "sequence": 6 if action == 304 else 2,
               "vx": vx, "flag": flag, "control_word": cw}
    for action, frame, latch, held, cw in itertools.product(
            ACTIONS, (0, 1, 2, 3, 4, 5, 7, 9, 11, 12),
            (0, 1), (0, 1), (0x27F, 0x37F)):
        yield {**base, "cohort": "frames", "action": action, "frame": frame,
               "timer": -1, "latch750": latch, "held6bc": held, "control_word": cw}
    for action, sequence, facing, latch in itertools.product(
            ACTIONS, range(7), (-128, -1, 0, 1, 127), (0, 1)):
        yield {**base, "cohort": "nodes", "action": action, "sequence": sequence,
               "facing": facing, "latch750": latch, "counter": -1, "timer": -1}
    for state, count, sequence, counter, cw in itertools.product(
            (0, 1, 7), (-32768, -1, 0, 4, 5, 6, 32767), (0, 1, 2),
            (-16, -15, -1, 0, 14, 15), (0x27F, 0x37F)):
        yield {**base, "cohort": "state", "action": 310, "state": state,
               "counter730": count, "sequence": sequence, "counter": counter,
               "control_word": cw}
    for action, horizontal, vertical, state, facing in itertools.product(
            (301, 302, 303, 305, 320, 321, 322), (-1, 0, 1), (-1, 0, 1),
            (0, 1), (-1, 1)):
        yield {**base, "cohort": "directional", "action": action,
               "input": horizontal, "field": vertical, "state": state,
               "facing": facing, "mode4b8": 10, "y": 0.0}
    for action, flag, cw in itertools.product(range(311, 320), (0, 1), (0x27F, 0x37F)):
        yield {**base, "cohort": "default", "action": action,
               "flag": flag, "control_word": cw}
    for action, gate, peer_gate in itertools.product(
            (323, 400, 551, 560, 561, 798, 799, 32767), (0, 1), (0, 1)):
        yield {**base, "cohort": "handoff", "action": action,
               "entry_gate": gate, "peer_gate": peer_gate}
    # These target PCs are observations, and assert actual branch execution.
    branches = (
        (301, 0x47CD50, {"frame": 4, "timer": -1}),
        (301, 0x47CCEE, {"frame": 5}),
        (302, 0x47CE5D, {"frame": 3, "timer": -1}),
        (302, 0x47CF55, {"frame": 4, "timer": -1}),
        (302, 0x47D01E, {"sequence": 1, "frame": 1, "timer": -1}),
        (303, 0x47D0D7, {"frame": 3, "timer": -1}),
        (303, 0x47D0F8, {"frame": 5, "timer": -1}),
        (303, 0x47D118, {"frame": 7, "timer": -1}),
        (303, 0x47D13D, {"frame": 9, "timer": -1}),
        (304, 0x47D1CE, {"sequence": 1, "vy": 0xC0400000}),
        (304, 0x47D254, {"sequence": 4, "vy": 0xC0400000}),
        (304, 0x4852F6, {"sequence": 5, "counter": 12}),
        (304, 0x47D334, {"sequence": 1, "counter": -1, "timer": -1}),
        (304, 0x47D393, {"sequence": 1, "counter": -1, "timer": -1, "latch750": 0}),
        (304, 0x479486, {"sequence": 3, "counter": -1, "timer": -1}),
        (304, 0x47D419, {"sequence": 4, "counter": -1, "timer": -1}),
        (305, 0x47D4F8, {"frame": 4, "timer": -1}),
        (306, 0x47D544, {"sequence": 1, "counter": 13}),
        (306, 0x47D602, {"frame": 1, "timer": -1}),
        (307, 0x47D6CB, {"frame": 2, "timer": -1}),
        (308, 0x47D79E, {"frame": 4, "timer": -1}),
        (308, 0x47D7C5, {"sequence": 1, "counter": 10}),
        (309, 0x47D826, {"frame": 2, "timer": -1}),
        (310, 0x47D873, {"state": 1, "counter730": 5}),
        (310, 0x47D8CF, {"sequence": 1, "counter": -15}),
        (310, 0x47D8FB, {"sequence": 1, "vy": 0xC0400000}),
        (320, 0x47CC4B, {"frame": 3, "timer": -1}),
        (321, 0x47CC4B, {"frame": 2, "timer": -1}),
        (322, 0x47DB57, {"frame": 5, "timer": -1}),
    )
    for (action, site, change), cw in itertools.product(branches, (0x27F, 0x37F)):
        yield {**base, "cohort": "branches", "action": action,
               "required_site": site, "control_word": cw, **change}
    coordinate_requests = (
        (302, {"frame": 3, "timer": -1}),
        (302, {"frame": 4, "timer": -1}),
        (302, {"sequence": 1, "frame": 1, "timer": -1}),
        (304, {"sequence": 1, "counter": -1, "timer": -1}),
        (306, {"frame": 1, "timer": -1}),
        (308, {"frame": 4, "timer": -1}),
    )
    for (action, change), x, facing, cw in itertools.product(
            coordinate_requests, (0, 0x80000000, 1, 0x3F000001, 0x43FFFFFF, 0x4B800000, 0x7FC12345),
            (-128, -1, 0, 1, 127), (0x27F, 0x37F)):
        yield {**base, "cohort": "coordinates", "action": action,
               "coordinate_bits": (x, 0), "facing": facing, "control_word": cw, **change}
    for case in low.cases(True):
        yield {**base, **case, "cohort": "integration"}
    for case in low.cases():
        if case["cohort"] == "common_return":
            yield {**base, **case, "cohort": "integration"}


class Probe(low.Probe):
    resource_keys = KEYS
    handled_action_max = 322
    frame_capacity = 14

    def extra_actor_fields(self, case):
        return (*super().extra_actor_fields(case),
                (0x6BC, "i", case["held6bc"]), (0x750, "B", case["latch750"]))

    def step(self, uc, address, size):
        super().step(uc, address, size)
        if address == 0x465190 and self.spawn_request[1] == 848:
            # Pointer identity belongs to each stack; compare its actual data.
            request = self.spawn_request
            pointer, count = request[6:8]
            sp = uc.reg_read(low.r.UC_X86_REG_ESP)
            if count != 3 or not sp <= pointer <= pointer+12 <= low.STACK+0x10000:
                raise ValueError("object848 parameters escaped the active supplied stack")
            self.spawn_request = (*request[:6], struct.unpack("<III", uc.mem_read(pointer, 12)), count)


def check_target_case(case, result, sites):
    low.check_target_case(case, result, sites)
    if case.get("required_site") is not None and case["required_site"] not in sites:
        raise ValueError(f"advertised middle branch not executed: {case}")
    if case["cohort"] == "integration" and case.get("execute_common"):
        low.check_target_case({**case, "cohort": "common_return"}, result, sites)


COHORT_COUNTS = {"motion": 1274, "friction": 864, "frames": 1040, "nodes": 910,
                 "state": 756, "directional": 252, "default": 36, "handoff": 32}
COHORT_COUNTS["branches"] = 58
COHORT_COUNTS.update(coordinates=420, integration=87)
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
        parser.exit(2, f"Reimu mid-normal audit failed: {error}\n")
    print(json.dumps(result, indent=2))
    raise SystemExit(1 if result["mismatch_count"] else 0)
