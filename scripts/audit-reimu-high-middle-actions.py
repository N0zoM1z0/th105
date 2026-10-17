#!/usr/bin/env python3
"""Compare Reimu608..619 with native helpers and a bounded animation domain."""
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
spec = importlib.util.spec_from_file_location("reimu_high_middle_previous", ROOT / "scripts/audit-reimu-high-entry-actions.py")
previous = importlib.util.module_from_spec(spec)
sys.modules[spec.name] = previous
spec.loader.exec_module(previous)
low, SYMBOL = previous.low, previous.SYMBOL
ACTIONS = (608, 609, 610, 612, 614, 616, 619)
# All staged set_action destinations plus directional-helper destinations.
# The fixture adds the current input action independently for every case.
KEYS = (0, 1, 2, 9, 10, 76, 78, 89, 97, 204, 208, 209, 210, 211, 212, 215, 669, 700)
HELPERS, CALL_TARGETS = previous.HELPERS, previous.CALL_TARGETS
SUPPORT_PATHS = (Path(previous.__file__), *previous.SUPPORT_PATHS)
LITERAL_BINDINGS = {**previous.LITERAL_BINDINGS,
                    "4062000000000000": 0x6C3CF8, "3e99999a": 0x6C3298,
                    "4054000000000000": 0x6C0850, "4057400000000000": 0x6C3CF0,
                    "43160000": 0x6C3CEC, "3fa00000": 0x6C3C00,
                    "41800000": 0x6C3CE8, "3dcccccd": 0x6C3450,
                    "3fe0000000000000": 0x6CD138, "4072c00000000000": 0x6C1B08,
                    "4071800000000000": 0x6C3CE0, "4000000000000000": 0x6C21C0,
                    "41a00000": 0x6C3E68, "c0800000": 0x6C3E98,
                    "3f333333": 0x6C3CD8, "4049b33340000000": 0x6C3CD0,
                    "00000000": 0x6D6EA8, "401c000000000000": 0x6C1B18}
SCHEMA = "th105-reimu-high-middle-native-v1"
SCOPE = ("integrated entry/low/middle/high source through619; actual native helper "
         "and RET ABI, first825/852/858/859/866/869 request/payload; read-only "
         "bounded animation/texture context, flat surface, inactive sequence-window/"
         "secondary event and zero sound handles; no returning world calls, later "
         "volleys/high source, full-root or canonical-exact claim")


def cases(smoke=False):
    base = next(previous.cases(True))
    if smoke:
        for action, change in itertools.product(ACTIONS, (
                {}, {"sequence": 1, "counter": 21},
                {"sequence": 0, "frame": 3, "timer": -1},
                {"sequence": 0, "frame": 4, "timer": -1},
                {"sequence": 0, "frame": 5, "timer": -1},
                {"sequence": 0, "frame": 7, "timer": -1},
                {"sequence": 2, "counter": -1, "timer": -1, "y": 400.0},
                {"sequence": 3, "vy": 0xC0400000},
                {"sequence": 4, "counter": -1, "timer": -1},
                {"sequence": 5, "frame": 5, "timer": -1, "y": 100.0},
                {"sequence": 6, "vy": 0xC0400000},
                {"sequence": 8},
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
            ACTIONS, range(9), (-1, 0), (-1, 0), (0, 1, 3, 4, 5, 7, 10)):
        yield {**base, "cohort": "nodes", "action": action, "sequence": sequence,
               "counter": counter, "timer": timer, "frame": frame}
    for count, timer, shot, facing, cw in itertools.product(
            (-32768, -1, 0, 1, 32767), (-32768, -1, 0, 1, 2, 6, 32767),
            (-32768, -1, 0, 2, 3, 32767), (-1, 1), (0x27F, 0x37F)):
        yield {**base, "cohort": "pair_timer", "action": 608, "sequence": 4,
               "counter730": count, "counter732": timer, "counter734": shot,
               "facing": facing, "control_word": cw}
    for sequence, frame, scale, alpha, cw in itertools.product(
            (0, 2), (0, 1, 2, 3), (0, 0x3D4CCCCD, 0x3F733333, 0x3F800000, 0x7FC12345),
            (0, 25, 26, 231, 255), (0x27F, 0x37F)):
        yield {**base, "cohort": "visual", "action": 612, "sequence": sequence,
               "frame": frame, "visual_x": scale, "alpha": alpha, "control_word": cw}
    for state, flag, cw in itertools.product((0, 1, -1), (0, 1, 127, 128, 255), (0x27F, 0x37F)):
        yield {**base, "cohort": "state", "action": 612, "sequence": 3,
               "state": state, "byte184": flag, "control_word": cw}
    for sequence, y, vy, count, cw in itertools.product(
            (1, 2, 3, 4, 5, 6, 7), (0.0, 279.0, 280.0, 299.0, 300.0, 301.0, 400.0),
            (0, 0xC0400000, 0x40A00000, 0x7FC12345), (119, 120, 121), (0x27F, 0x37F)):
        yield {**base, "cohort": "hover", "action": 616, "sequence": sequence,
               "y": y, "vy": vy, "counter": count, "control_word": cw}
    for bits, cw in itertools.product((0, 0x41900000, 0x41980000, 0x41A00000, 0x7FC12345), (0x27F, 0x37F)):
        yield {**base, "cohort": "hover_shape", "action": 616, "sequence": 3,
               "hover_bits": bits, "control_word": cw}
    for action, sequence, count, word, cw in itertools.product(
            (608, 609, 610, 619), (1, 2), (19, 20, 21, 24, 25, 40, 41, 60, 61),
            (-1, 0, 1, 2), (0x27F, 0x37F)):
        yield {**base, "cohort": "cutoff", "action": action, "sequence": sequence,
               "counter": count, "counter738": word, "control_word": cw}
    for action, player, own, peer, terminal in itertools.product(
            (608, 609, 610, 614, 616, 619), (0, 1), (0, 2), (0, 1), (False, True)):
        yield {**base, "cohort": "texture", "action": action, "player": player,
               "texture_duration": own, "peer_texture_duration": peer,
               "single_sequence": terminal, "transition": "terminal" if terminal else "unexpired"}
    branches = (
        (608, 0x4852F6, {"sequence": 1, "counter": 21}),
        (608, 0x488FD3, {"sequence": 2, "vy": 0xC0400000}),
        (608, 0x489047, {"frame": 4, "timer": -1}),
        (608, 0x4891F1, {"sequence": 4, "counter730": 1, "counter732": 1, "counter734": 0}),
        (608, 0x489139, {"sequence": 3, "counter": -1, "timer": -1}),
        (609, 0x4852F6, {"sequence": 1, "counter738": 1}),
        (609, 0x489387, {"frame": 5, "timer": -1}),
        (610, 0x489462, {"frame": 7, "timer": -1}),
        (612, 0x4894DE, {"frame": 1, "timer": 0}),
        (612, 0x489536, {"frame": 2, "alpha": 25}),
        (612, 0x4895E1, {"sequence": 3, "state": 1, "byte184": 127}),
        (612, 0x48961C, {"sequence": 3, "vy": 0xC0400000}),
        (612, 0x489712, {"sequence": 2, "counter": -1, "timer": -1}),
        (612, 0x48974B, {"sequence": 2, "frame": 3, "timer": -1}),
        (614, 0x47FFA2, {"sequence": 1, "vy": 0xC0400000}),
        (614, 0x4897CC, {"sequence": 5, "vy": 0xC0400000}),
        (614, 0x4899BB, {"sequence": 4, "counter": -1, "timer": -1, "counter730": 1}),
        (614, 0x489AE2, {"sequence": 5, "counter": -1, "timer": -1, "y": 100.0}),
        (614, 0x489BD6, {"sequence": 5, "frame": 6, "timer": -1, "y": 100.0}),
        (616, 0x489CB8, {"sequence": 1, "y": 300.0, "vy": 0xC0400000}),
        (616, 0x489FAD, {"sequence": 1, "y": 400.0, "counter": -1, "timer": -1}),
        (616, 0x489DBA, {"sequence": 3, "speed": 19.0}),
        (616, 0x489DF0, {"sequence": 4, "vx": 0x41000000}),
        (616, 0x489E58, {"sequence": 4, "y": 301.0, "vy": 0xC0400000}),
        (616, 0x489E8D, {"sequence": 5, "counter": 120, "y": 300.0}),
        (616, 0x489ED0, {"sequence": 6, "vy": 0xC0400000}),
        (619, 0x47D7BE, {"sequence": 1, "counter": 20}),
        (619, 0x48A0CA, {"frame": 3, "timer": -1}),
        (619, 0x48A203, {"frame": 5, "timer": -1}),
    )
    for (action, site, change), cw in itertools.product(branches, (0x27F, 0x37F)):
        yield {**base, "cohort": "branches", "action": action, "required_site": site,
               "control_word": cw, **change}
    for case in previous.cases(True):
        yield {**case, "cohort": "integration"}
    for case in previous.cases():
        if case["cohort"] == "integration":
            yield case
    for action in (607, 611, 613, 615, 617, 618):
        yield {**base, "cohort": "default", "action": action}
    for action in (620, 650, 669, 710, 798, 799, 32767):
        yield {**base, "cohort": "handoff", "action": action}


class Probe(previous.Probe):
    resource_keys = KEYS
    resource_size = 0x100000
    handled_action_max = 619
    parameter_counts_869 = (4,)

    def extra_actor_fields(self, case):
        hover = ((0x73C, "I", case["hover_bits"]),) if "hover_bits" in case else ()
        return (*super().extra_actor_fields(case), *hover)

    def step(self, uc, address, size):
        super().step(uc, address, size)
        if address == 0x45DEB0:
            self.calls.append(("native_args", address,
                               bytes(uc.mem_read(uc.reg_read(low.r.UC_X86_REG_ESP)+4, 12)).hex()))
        if address == 0x465190 and self.spawn_request[1] in (852, 858, 859, 866, 869):
            request = self.spawn_request
            pointer, count = request[6:8]
            if request[1] == 859:
                if (pointer, count) != (0, 0):
                    raise ValueError("859 unexpectedly carries a parameter array")
                return
            allowed_counts = self.parameter_counts_869 if request[1] == 869 else (3,)
            sp = uc.reg_read(low.r.UC_X86_REG_ESP)
            if count not in allowed_counts or pointer & 3 or not sp <= pointer <= pointer+count*4 <= low.STACK+0x10000:
                raise ValueError("high-middle parameters escaped the active supplied stack")
            self.spawn_request = (*request[:6], struct.unpack("<"+"I"*count, uc.mem_read(pointer, count*4)), count)


def check_target_case(case, result, sites):
    previous.check_target_case(case, result, sites)


COHORT_COUNTS = {"motion": 756, "nodes": 1764, "pair_timer": 840,
                 "visual": 400, "state": 30, "hover": 1176, "hover_shape": 10,
                 "cutoff": 576, "texture": 96, "branches": 58,
                 "integration": 657, "default": 6, "handoff": 7}
SMOKE_COUNT = 91


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
        parser.exit(2, f"Reimu high-middle audit failed: {error}\n")
    print(json.dumps(result, indent=2))
    raise SystemExit(1 if result["mismatch_count"] else 0)
