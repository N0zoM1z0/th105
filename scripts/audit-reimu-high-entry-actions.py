#!/usr/bin/env python3
"""Compare the first nine high-table bodies in Reimu's integrated source."""
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
spec = importlib.util.spec_from_file_location("reimu_high_previous", ROOT / "scripts/audit-reimu-mid-550-actions.py")
previous = importlib.util.module_from_spec(spec)
sys.modules[spec.name] = previous
spec.loader.exec_module(previous)
low, SYMBOL = previous.low, previous.SYMBOL
ACTIONS = (561, 565, 566, 600, 601, 602, 604, 605, 606)
KEYS = (*previous.KEYS, *ACTIONS)
HELPERS = {**previous.HELPERS, 0x45F560: (170, "publish_texture"),
           0x42D1B0: (100, "texture_deque_at"), 0x4776C0: (15, "set_word48a"),
           0x45DEB0: (446, "sequence_window")}
CALL_TARGETS = {**previous.CALL_TARGETS, "publish_texture_state": 0x45F560,
                "set_word_48a": 0x4776C0,
                "dispatch_indexed_sequence_window_45c8b0": 0x45DEB0,
                "advance_secondary_event_effect_cycle": 0x473F90}
SUPPORT_PATHS = (Path(previous.__file__), *previous.SUPPORT_PATHS)
LITERAL_BINDINGS = {**previous.LITERAL_BINDINGS,
                    "41b40000": 0x6C3D28, "3fd0000000000000": 0x6C33A8,
                    "3fd99999a0000000": 0x6C3D20, "41480000": 0x6C3C48,
                    "3f666666": 0x6C3E40, "41200000": 0x6D6EEC,
                    "c2960000": 0x6C3D18, "c042000000000000": 0x6C3D10,
                    "4041800000000000": 0x6C3D08, "406c400000000000": 0x6C3D00,
                    "405e000000000000": 0x6C3E70}
SCHEMA = "th105-reimu-high-entry-native-v1"
SCOPE = ("integrated source through606; actual native helper/texture-deque/manager "
         "writes and RET ABI; first825/850/853/854/851/855/856 request/payload or "
         "effect entry; read-only animation/texture IDs, flat surface, zero wave/"
         "event handles, two texture-manager slots; no returning world requests, "
         "later high source, full-root or canonical-exact claim")
MANAGER = 0x2200000
MANAGER_POINTER = 0x6FBCA0


def cases(smoke=False):
    base = {**next(previous.cases(True)), "skill60b": 3, "player": 0,
            "texture_duration": 0, "peer_texture_duration": 0}
    if smoke:
        for action, change in itertools.product(ACTIONS, (
                {}, {"sequence": 1, "counter": 10, "y": 100.0},
                {"sequence": 1, "counter": 26, "held6c0": 0, "held6c4": 0},
                {"sequence": 0, "frame": 2, "timer": -1},
                {"sequence": 0, "frame": 6, "timer": 0},
                {"sequence": 0, "frame": 8, "timer": -1},
                {"sequence": 4, "counter": -1, "timer": -1, "y": 100.0},
                {"sequence": 4, "frame": 4, "timer": -1, "skill60b": 4, "y": 100.0},
                {"sequence": 7, "frame": 1, "timer": -1, "y": 100.0},
                {"sequence": 8, "counter": -1, "timer": -1},
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
    for action, count, held, latch, cw in itertools.product(
            (565, 566), (9, 10, 25, 26), ((0, 1), (1, 0), (65536, 65536)),
            (0, 1, 2), (0x27F, 0x37F)):
        yield {**base, "cohort": "hold", "action": action, "sequence": 1,
               "counter": count, "held6c0": held[0], "held6c4": held[1],
               "latch750": latch, "control_word": cw, "y": 0.0}
    for action, sequence, speed, cw in itertools.product((565, 566), (4, 5, 7, 8),
            (0, 0x80000000, 0x3DCCCCCD, 0x3E800000, 0x3ECCCCCD, 0x3F800000,
             0xBF800000, 0x7FC12345), (0x27F, 0x37F)):
        yield {**base, "cohort": "friction", "action": action, "sequence": sequence,
               "vx": speed, "y": 0.0 if sequence == 8 else 100.0, "control_word": cw}
    for action, skill, latch, held, cw in itertools.product((565, 566), (-128, 3, 4, 127),
            (0, 1), (0, 65536), (0x27F, 0x37F)):
        yield {**base, "cohort": "skill", "action": action, "sequence": 4, "frame": 4,
               "timer": -1, "skill60b": skill, "latch750": latch,
               "held6c0": held, "held6c4": held, "y": 100.0, "control_word": cw}
    for action, count, word, seed, cw in itertools.product((600, 601, 602),
            (-5, -1, 0, 1, 5, 30, 31, 45, 46, 60, 61),
            (-32768, -1, 0, 4, 5, 9, 10, 13, 14, 32767),
            (0, 5489, 0xFFFFFFFF), (0x27F, 0x37F)):
        yield {**base, "cohort": "cadence", "action": action, "sequence": 1,
               "counter": count, "counter730": word, "seed": seed, "control_word": cw,
               "y": 0.0}
    for action, player, own, peer, terminal in itertools.product(
            (600, 601, 602, 604, 605, 606), (0, 1), (0, 2), (0, 1), (False, True)):
        yield {**base, "cohort": "texture", "action": action, "player": player,
               "texture_duration": own, "peer_texture_duration": peer,
               "single_sequence": terminal, "transition": "terminal" if terminal else "unexpired"}
    for action, sequence, frame, facing, cw in itertools.product(
            ACTIONS, (0, 1, 4, 7), (0, 1, 2, 3, 6, 8), (-128, -1, 0, 1, 127), (0x27F, 0x37F)):
        yield {**base, "cohort": "nodes", "action": action, "sequence": sequence,
               "frame": frame, "timer": -1, "counter": -1,
               "facing": facing, "y": 100.0 if action in (565, 566) and sequence >= 4 else 0.0, "control_word": cw}
    branches = (
        (561, 0x47FA23, {"sequence": 1, "vy": 0xC0400000}),
        (561, 0x487BC7, {"sequence": 1, "counter": -1, "timer": -1}),
        (565, 0x487C7C, {"frame": 2, "vy": 0xC0400000}),
        (566, 0x48811A, {"frame": 2, "vy": 0xC0400000}),
        (565, 0x487CF0, {"sequence": 4, "vy": 0xC0400000}),
        (566, 0x48818E, {"sequence": 4, "vy": 0xC0400000}),
        (565, 0x487D3D, {"sequence": 1, "counter": 10, "y": 0.0}),
        (566, 0x4881EE, {"sequence": 1, "counter": 26, "held6c4": 0, "y": 0.0}),
        (565, 0x47BEB6, {"sequence": 8, "counter": -1, "timer": -1, "y": 0.0}),
        (566, 0x480CE4, {"sequence": 8, "counter": -1, "timer": -1, "y": 0.0}),
        (565, 0x487ECD, {"sequence": 4, "frame": 4, "timer": -1, "skill60b": 4, "y": 100.0}),
        (566, 0x487ECD, {"sequence": 4, "frame": 4, "timer": -1, "skill60b": 4, "y": 100.0}),
        (565, 0x48804B, {"sequence": 4, "counter": -1, "timer": -1, "y": 100.0}),
        (566, 0x4884C1, {"sequence": 4, "counter": -1, "timer": -1, "y": 100.0}),
        (565, 0x487F97, {"sequence": 7, "frame": 1, "timer": -1, "y": 100.0}),
        (566, 0x48840D, {"sequence": 7, "frame": 1, "timer": -1, "y": 100.0}),
        (600, 0x47D7BE, {"sequence": 1, "counter": 31, "y": 0.0}),
        (601, 0x47D7BE, {"sequence": 1, "counter": 61, "y": 0.0}),
        (602, 0x47D7BE, {"sequence": 1, "counter": 46, "y": 0.0}),
        (604, 0x47D7BE, {"sequence": 2, "counter": 31, "y": 0.0}),
        (605, 0x4852F6, {"sequence": 1, "counter": 31, "y": 0.0}),
        (606, 0x47D7BE, {"sequence": 2, "counter": 71, "y": 0.0}),
        (600, 0x488614, {"sequence": 1, "counter": 0, "y": 0.0}),
        (601, 0x4887E5, {"sequence": 1, "counter": 0, "y": 0.0}),
        (602, 0x488A30, {"sequence": 1, "counter": 0, "y": 0.0}),
        (604, 0x488C29, {"frame": 8, "timer": -1, "y": 0.0}),
        (605, 0x488D94, {"frame": 8, "timer": -1, "y": 0.0}),
        (606, 0x488F4C, {"frame": 8, "timer": -1, "y": 0.0}),
        (600, 0x4886C5, {"frame": 2, "timer": -1, "y": 0.0}),
        (604, 0x488B96, {"frame": 6, "timer": 0, "y": 0.0}),
    )
    for (action, site, change), cw in itertools.product(branches, (0x27F, 0x37F)):
        yield {**base, "cohort": "branches", "action": action, "required_site": site,
               "control_word": cw, **change}
    for case in previous.cases(True):
        yield {**case, "cohort": "integration"}
    for case in previous.cases():
        if case["cohort"] == "integration":
            yield case
    for action in (562, 564, 567, 599, 603):
        yield {**base, "cohort": "default", "action": action}
    for action in (607, 608, 616, 650, 798, 799, 32767):
        yield {**base, "cohort": "handoff", "action": action}


class Probe(previous.Probe):
    helpers = HELPERS
    resource_keys = KEYS
    # This larger key domain needs over1 MiB at nine sequences/fourteen frames.
    resource_size = 0x200000
    handled_action_max = 606
    argument_helpers = previous.Probe.argument_helpers | {0x45F560, 0x4776C0, 0x45DEB0, 0x42D1B0}

    def __init__(self, *args):
        super().__init__(*args)
        self.engine.mem_map(MANAGER, 0x1000)

    def prepare_extra_case(self, case):
        super().prepare_extra_case(case)
        self.engine.mem_write(MANAGER, bytes(0x1000))
        self.engine.mem_write(MANAGER+0xD8, struct.pack("<II", 0xABCD0001, 0xABCD0002))
        self.engine.mem_write(MANAGER_POINTER, struct.pack("<I", MANAGER))
        self.engine.mem_write(low.RESOURCE+0xE00, struct.pack("<8I", *(low.RESOURCE+0xE40+16*i for i in range(8))))
        self.engine.mem_write(low.RESOURCE+0xE40, struct.pack("<32I", *(0x1000+i for i in range(32))))

    def extra_actor_fields(self, case):
        return (*super().extra_actor_fields(case), (0x60B, "b", case.get("skill60b", 3)),
                (0x334, "b", case.get("player", 0)),
                (0x68C, "I", 0), (0x690, "I", low.RESOURCE+0xE00),
                (0x694, "I", 8), (0x698, "I", 0), (0x69C, "I", 8),
                (0x6A0, "h", case.get("texture_duration", 0)), (0x6A2, "b", -77),
                (0x26A0, "h", case.get("peer_texture_duration", 0)))

    def extra_result(self):
        return {**super().extra_result(), "texture_manager": bytes(self.engine.mem_read(MANAGER+0xD8, 8))}

    def helper_receiver(self, address):
        if address == 0x42D1B0:
            return low.OWNER+0x68C
        return super().helper_receiver(address)

    def write(self, uc, access, address, size, value, unused):
        if address in (MANAGER+0xD8, MANAGER+0xDC) and size == 4:
            return
        super().write(uc, access, address, size, value, unused)

    def step(self, uc, address, size):
        super().step(uc, address, size)
        if address == 0x45F560:
            self.calls.append(("native_args", address, bytes(uc.mem_read(uc.reg_read(low.r.UC_X86_REG_ESP)+4, 8)).hex()))
        if address == 0x465190 and self.spawn_request[1] in (850, 853, 854, 860, 851, 855, 856):
            request = self.spawn_request
            pointer, count = request[6:8]
            expected_count = 1 if request[1] in (851, 855, 856) else 3
            sp = uc.reg_read(low.r.UC_X86_REG_ESP)
            if count != expected_count or pointer & 3 or not sp <= pointer <= pointer+count*4 <= low.STACK+0x10000:
                raise ValueError("high parameters escaped the active supplied stack")
            self.spawn_request = (*request[:6], struct.unpack("<"+"I"*count, uc.mem_read(pointer, count*4)), count)


def check_target_case(case, result, sites):
    previous.check_target_case(case, result, sites)
    if case["cohort"] == "texture":
        if not any(call[0] == 0x45F560 for call in result["calls"]):
            raise ValueError("texture fixture bypassed the native publisher")
    if case["cohort"] == "hold":
        site = 0x487D20 if case["action"] == 565 else 0x4881BE
        if site not in sites:
            raise ValueError("hold fixture bypassed the actual full-width input/counter gates")
    if case["cohort"] == "cadence":
        limit = {600: 30, 601: 60, 602: 45}[case["action"]]
        cap = {600: 5, 601: 10, 602: 14}[case["action"]]
        fire = (case["counter"] <= limit and case["counter730"] < cap
                and (case["counter"] == 0 if case["action"] == 602 else case["counter"] % 5 == 0))
        if fire:
            expected = {600: 850, 601: 853, 602: 854}[case["action"]]
            if result["spawn_request"] is None or result["spawn_request"][:2] != (0x465190, expected):
                raise ValueError("cadence fixture bypassed the advertised actual projectile request")


COHORT_COUNTS = {"motion": 972, "hold": 144, "friction": 128, "skill": 64,
                 "cadence": 1980, "texture": 96, "nodes": 2160,
                 "branches": 60, "integration": 549, "default": 5, "handoff": 7}
SMOKE_COUNT = 108


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
        parser.exit(2, f"Reimu high-entry audit failed: {error}\n")
    print(json.dumps(result, indent=2))
    raise SystemExit(1 if result["mismatch_count"] else 0)
