#!/usr/bin/env python3
"""Compare final Reimu high families, preserving unresolved740 stack paths."""
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
spec = importlib.util.spec_from_file_location("reimu_high_final_previous", ROOT / "scripts/audit-reimu-high-late-actions.py")
previous = importlib.util.module_from_spec(spec)
sys.modules[spec.name] = previous
spec.loader.exec_module(previous)
low, SYMBOL = previous.low, previous.SYMBOL
ACTIONS = (720, 730, 740, 760, 770, 795, 797, 798)
KEYS = previous.KEYS
HELPERS = {**previous.HELPERS, 0x45D110: (154, "finalize_sequence_entry"),
           0x45B250: (15, "copy_action_word")}
CALL_TARGETS = {**previous.CALL_TARGETS, "finalize_sequence_entry": 0x45D110,
                "copy_action_word_176_to_174": 0x45B250}
SUPPORT_PATHS = (Path(previous.__file__), *previous.SUPPORT_PATHS)
LITERAL_BINDINGS = {**previous.LITERAL_BINDINGS,
                    "406e000000000000": 0x6C3CB0, "3fb99999a0000000": 0x6CD1E0,
                    "3fc99999a0000000": 0x6C0E80, "4084000000000000": 0x6C0EA0,
                    "44200000": 0x6C0574, "43f00000": 0x6C0578, "44480000": 0x6C3B38,
                    "bfc00000": 0x6C3CAC, "c0200000": 0x6C3CA8,
                    "418c0000": 0x6C3E60, "3ee66666": 0x6C3E80,
                    "3e800000": 0x6C3440, "402e000000000000": 0x6C3DB8,
                    "4024000000000000": 0x6D6EC0}
SCHEMA = "th105-reimu-high-final-native-v1"
SCOPE = ("integrated source through798; native helper/RET ABI, first901/902/903/905 request; "
         "740 out-of-range uninitialized-stack arms remain pending; inactive sequence finalize, "
         "bounded animation/texture context and real MT; no returning world requests, complete "
         "volleys, active score/backend, full void-root or canonical-exact claim")


def cases(smoke=False):
    base = next(previous.cases(True))
    if smoke:
        for action, change in itertools.product(ACTIONS, (
                {}, {"sequence": 1, "counter": -1, "timer": -1},
                {"sequence": 2, "counter": -1, "timer": -1},
                {"sequence": 3, "counter": -1, "timer": -1},
                {"sequence": 3, "counter": 90}, {"sequence": 3, "counter": 120},
                {"sequence": 4, "counter": 59, "y": 100.0},
                {"sequence": 5, "counter": -1},
                {"sequence": 6, "counter": 60}, {"frame": 7, "timer": -1},
                {"vy": 0xC0400000},
                {"single_sequence": True, "transition": "terminal"})):
            yield {**base, "cohort": "smoke", "action": action, **change}
        return
    for action, sequence, change, cw in itertools.product(ACTIONS, range(9), (
            {}, {"counter": -1, "timer": -1}, {"y": 100.0},
            {"vy": 0xC0400000}, {"vy": 0x7FC12345},
            {"single_sequence": True, "transition": "terminal"}), (0x27F, 0x37F)):
        yield {**base, "cohort": "motion", "action": action, "sequence": sequence,
               "control_word": cw, **change}
    for action, sequence, count, timer, frame in itertools.product(
            ACTIONS, range(9), (-1, 0), (-1, 0), (0, 1, 2, 3, 4, 6, 7, 10)):
        yield {**base, "cohort": "nodes", "action": action, "sequence": sequence,
               "counter": count, "timer": timer, "frame": frame}
    for sequence, frame, scale, alpha, cw in itertools.product(
            (0, 1, 2), (0, 3, 4), (0, 0x3F800000, 0xBF800000, 0x7FC12345),
            (0, 24, 25, 26, 235, 236, 255), (0x27F, 0x37F)):
        yield {**base, "cohort": "visual720", "action": 720, "sequence": sequence,
               "frame": frame, "visual_x": scale, "alpha": alpha, "control_word": cw}
    for sequence, mode, seed, facing, cw in itertools.product(
            (2, 3), (0, 1, 2, 3, 4, 0xFFFFFFFF), (0, 5489, 0xFFFFFFFF), (-128, -1, 127), (0x27F, 0x37F)):
        yield {**base, "cohort": "random720", "action": 720, "sequence": sequence,
               "counter": -1, "timer": -1, "match_selector": mode, "seed": seed,
               "facing": facing, "control_word": cw}
    for mode, count, phase, facing, cw in itertools.product(
            (0, 1, 2, 3, 4, 0xFFFFFFFF), (-17, -8, -6, -5, -4, -1, 0, 1, 4, 5, 6, 8, 16, 59, 60),
            (0.0, 5.0, 45.0, 90.0), (-128, -1, 127), (0x27F, 0x37F)):
        yield {**base, "cohort": "cadence730", "action": 730, "sequence": 5,
               "counter": count-1, "post_counter": count, "match_selector": mode,
               "speed": phase, "facing": facing, "control_word": cw}
    for mode, count, word, seed, cw in itertools.product(
            range(4), (-10, -8, -6, -5, -1, 0, 1, 5, 6, 8, 10, 79, 80, 81),
            (-32768, -1, 0, 5, 6, 7, 8, 10, 11, 13, 14, 32767),
            (0, 5489, 0xFFFFFFFF), (0x27F, 0x37F)):
        yield {**base, "cohort": "shots740", "action": 740, "sequence": 1,
               "counter": count, "counter730": word, "seed": seed,
               "match_selector": mode, "control_word": cw}
    for mode, count, cw in itertools.product(range(4), (29, 30, 49, 50, 59, 60, 61), (0x27F, 0x37F)):
        yield {**base, "cohort": "cutoff740", "action": 740, "sequence": 6,
               "counter": count, "match_selector": mode, "control_word": cw}
    for phase, hp, timer, cw in itertools.product(
            (-1, 0, 1, 2, 3), (-32768, 0, 2499, 2500, 2501, 4999, 5000, 5001, 7499, 7500, 7501, 32767),
            (-32768, -1, 0, 1, 120, 32767), (0x27F, 0x37F)):
        yield {**base, "cohort": "phase760", "action": 760, "sequence": 5,
               "counter738": phase, "self_word": hp, "level736": timer, "control_word": cw}
    for word, player, duration, cw in itertools.product(
            (-32768, -1, 0, 1, 32767), (0, 1), (-1, 0, 2), (0x27F, 0x37F)):
        yield {**base, "cohort": "finalize770", "action": 770, "frame": 7,
               "timer": -1, "word176": word, "player": player,
               "texture_duration": duration, "control_word": cw}
    branches = (
        (720, 0x48BD39, {"sequence": 3, "counter": 90}),
        (720, 0x48BD4E, {"sequence": 3, "counter": 120}),
        (720, 0x48BD96, {"sequence": 4, "vy": 0xC0400000}),
        (720, 0x48BE03, {"sequence": 2, "counter": -1, "timer": -1}),
        (730, 0x48C238, {"sequence": 1, "counter": -1, "timer": -1}),
        (730, 0x48C341, {"sequence": 3, "counter": -1, "timer": -1}),
        (730, 0x47D7BE, {"sequence": 4, "counter": 59}),
        (740, 0x47D7BE, {"sequence": 1, "counter": 81, "counter730": 32767}),
        (740, 0x48C92A, {"sequence": 6, "counter": -1, "timer": -1}),
        (760, 0x48C977, {"sequence": 1, "counter": -1, "timer": -1}),
        (760, 0x48CA89, {"sequence": 3, "counter": -1, "timer": -1}),
        (760, 0x48CBC2, {"sequence": 4, "counter": 59, "level736": 77}),
        (760, 0x48CC63, {"sequence": 5, "counter738": 0, "self_word": 2500}),
        (770, 0x48CCD4, {"frame": 7, "timer": -1}),
        (795, 0x47B835, {"vy": 0xC0400000}),
        (797, 0x48CDC1, {"vy": 0xC0400000}),
        (798, 0x48CE14, {"vy": 0xC0400000}),
    )
    for (action, site, change), cw in itertools.product(branches, (0x27F, 0x37F)):
        yield {**base, "cohort": "branches", "action": action, "required_site": site,
               "control_word": cw, **change}
    for sequence, mode, cw in itertools.product((1, 6), (4, 0xFFFFFFFF), (0x27F, 0x37F)):
        yield {**base, "cohort": "unresolved740", "action": 740, "sequence": sequence,
               "match_selector": mode, "control_word": cw}
    for case in previous.cases(True):
        yield {**case, "cohort": "integration"}
    for case in previous.cases():
        if case["cohort"] == "integration":
            yield case
    for action in (712, 719, 721, 739, 750, 796):
        yield {**base, "cohort": "default", "action": action}
    for action in (799, 800, 1000, 32767):
        yield {**base, "cohort": "handoff", "action": action}


class Probe(previous.Probe):
    helpers = HELPERS
    handled_action_max = 798
    argument_helpers = previous.Probe.argument_helpers | {0x45D110}

    def extra_actor_fields(self, case):
        return (*super().extra_actor_fields(case), (0x176, "h", case.get("word176", 1234)),
                (0x655, "B", 0xAA), *((offset, "h", -11-i) for i, offset in enumerate(range(0x764, 0x76E, 2))))

    def step(self, uc, address, size):
        super().step(uc, address, size)
        if not self.candidate and address in (0x48C772, 0x48C8C4):
            self.pending_handoff = True
            uc.emu_stop()
        if address == 0x45D110 and uc.mem_read(low.OWNER+0x55A, 1) != b"\0":
            raise ValueError("active score/event finalization is outside this fixture")
        if address == 0x465190 and self.spawn_request[1] in (901, 902, 903, 905, 906, 907, 908):
            request = self.spawn_request
            pointer, count = request[6:8]
            expected = 4 if request[1] == 901 else 3
            sp = uc.reg_read(low.r.UC_X86_REG_ESP)
            if count != expected or pointer & 3 or not sp <= pointer <= pointer+count*4 <= low.STACK+0x10000:
                raise ValueError("final-high parameters escaped the active supplied stack")
            self.spawn_request = (*request[:6], struct.unpack("<"+"I"*count, uc.mem_read(pointer, count*4)), count)


def check_target_case(case, result, sites):
    previous.check_target_case(case, result, sites)
    cohort = case["cohort"]
    if cohort == "unresolved740":
        site = 0x48C772 if case["sequence"] == 1 else 0x48C8C4
        if site not in sites or result["endpoint"] != "pending":
            raise ValueError("740 did not stop before its uninitialized stack read")
    if cohort == "random720":
        if case["sequence"] == 2:
            if 0x48BE03 not in sites or 0x48BE2B not in sites:
                raise ValueError("720 random-position fixture bypassed its real draws")
        elif case["match_selector"] <= 3:
            table_sites = (0x48C126, 0x48C050, 0x48BF7A, 0x48BEA4)
            if table_sites[case["match_selector"]] not in sites or result["spawn_request"] is None or result["spawn_request"][:2] != (0x465190, 901):
                raise ValueError("720 fixture bypassed the advertised901 table arm")
        elif result["spawn_request"] is not None:
            raise ValueError("720 out-of-range mode emitted an object")
    if cohort in ("cadence730", "shots740"):
        mode = case["match_selector"]
        if cohort == "cadence730":
            fire = mode <= 3 and case["post_counter"] % (8, 6, 5, 4)[mode] == 0
            object_id = 902
        else:
            fire = case["counter"] % (10, 8, 6, 5)[mode] == 0 and case["counter730"] < (6, 8, 11, 14)[mode]
            object_id = 903
        request = result["spawn_request"]
        if (request is not None) != fire or (fire and request[:2] != (0x465190, object_id)):
            raise ValueError("cadence fixture bypassed its signed gate/real request")
    if cohort == "finalize770" and not all(any(call[0] == address for call in result["calls"]) for address in (0x45D110, 0x45F560, 0x45B250)):
        raise ValueError("770 fixture bypassed its actual finalization helpers")


COHORT_COUNTS = {"motion": 864, "nodes": 2304, "visual720": 504, "random720": 216,
                 "cadence730": 2160, "shots740": 4032, "cutoff740": 56,
                 "phase760": 720, "finalize770": 60, "branches": 34,
                 "unresolved740": 8, "integration": 852, "default": 6, "handoff": 4}
SMOKE_COUNT = 96


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
        parser.exit(2, f"Reimu high-final audit failed: {error}\n")
    print(json.dumps(result, indent=2))
    raise SystemExit(1 if result["mismatch_count"] else 0)
