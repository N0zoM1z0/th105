#!/usr/bin/env python3
"""Compare staged Reimu88/89/145 and197..204 in an explicit native context.

Uses actual target helpers, including seeding/drawing MT19937. Stops before
real object/effect requests need a backend; never supplies callback results.
"""
from __future__ import annotations

import argparse
from collections import Counter
import hashlib
import itertools
import json
from pathlib import Path
import struct
import sys

import pefile
import unicorn
from unicorn import unicorn as unicorn_api
from unicorn import x86_const as r

import linked_pe

ROOT = Path(__file__).resolve().parents[1]


def load_script(name, filename):
    import importlib.util
    spec = importlib.util.spec_from_file_location(name, ROOT / "scripts" / filename)
    module = importlib.util.module_from_spec(spec)
    sys.modules[name] = module
    spec.loader.exec_module(module)
    return module


recovery = load_script("reimu_movement_recovery_contract", "audit-reimu-recovery-actions.py")
ADDRESS, SIZE, BODY_SHA = recovery.ADDRESS, recovery.SIZE, recovery.BODY_SHA
OWNER, STACK, RETURN = recovery.OWNER, recovery.STACK, recovery.RETURN
SYMBOL = "?try_run_checked_movement_attack_action@ReimuActionStatePreludeView@th105@@QAE_NXZ"
ACTIONS = (88, 89, 145, *range(197, 205))
KEYS = (0, 1, 2, 9, 10, 88, 89, 97, 145, *range(197, 205), 211, 212, 700)
HELPERS = {**recovery.HELPERS, 0x478E60: (116, "face_and_flip"),
           0x406670: (61, "mt_seed"), 0x4066B0: (279, "mt_next")}
MT_INDEX, MT_STATE, MT_BYTES = 0x6FA1FC, 0x6FDEF0, 624*4
CALL_TARGETS = {**recovery.CALL_TARGETS, "is_at_stage_surface": 0x435DC0,
                "face_opponent_and_flip_horizontal_velocity": 0x478E60,
                "emit_fighter_effect": 0x435240, "mt19937_next_u32": 0x4066B0}


def cases(smoke=False):
    base = dict(action=88, vx=0xC0400000, vy=0x40A00000, ay=0x3F000000,
                flag=1, y=100.0, x=640.0, sequence=0, transition="unexpired",
                duration=3, counter=7, timer=None, frame=0, limit=None, field=0,
                facing=1, control_word=0x27F, spawn=1, counter730=7,
                angle=0x41F00000, coupled=1, mode=0, input=0, peer=0x44000000,
                counter732=-77, seed=5489, cohort="smoke")
    if smoke:
        for action, change in itertools.product(ACTIONS, (
                {}, {"sequence": -1}, {"y": 0.0, "vy": 0xC0200000},
                {"sequence": 1, "counter": -1, "timer": -1, "spawn": 0},
                {"transition": "terminal", "sequence": 3, "counter": 9},
                {"sequence": 1, "counter": 4, "y": 0.0},
                {"sequence": 0, "frame": 3, "timer": -1},
                {"sequence": 2, "frame": 4, "timer": -1},
                {"sequence": 1, "counter": 0, "timer": 0, "spawn": 0})):
            yield {**base, "action": action, **change}
        return
    floats = (0, 0x80000000, 0x3F000000, 0xC0200000, 0x40A00000,
              0x7F800000, 0xFF800000, 0x7FC12345, 0x7F812345)
    for action, vy, sequence, y, cw in itertools.product(
            ACTIONS, floats, (-1, 0, 1, 2, 3), (0.0, 100.0), (0x27F, 0x37F)):
        yield {**base, "cohort": "motion", "action": action, "vy": vy,
               "sequence": sequence, "y": y, "control_word": cw}
    for action, facing, node, spawn, cw in itertools.product(
            ACTIONS, (-128, -1, 0, 1, 127),
            ((0, 3), (1, 0), (2, 0), (2, 2), (2, 4)), (0, 1), (0x27F, 0x37F)):
        sequence, frame = node
        yield {**base, "cohort": "animation", "action": action, "facing": facing,
               "sequence": sequence, "frame": frame, "counter": -1, "timer": -1,
               "spawn": spawn, "control_word": cw, "y": 0.0}
    for action, transition, cw in itertools.product(
            ACTIONS, ("unexpired", "frame", "block", "terminal"), (0x27F, 0x37F)):
        yield {**base, "cohort": "frame_transition", "action": action,
               "transition": transition, "sequence": 0, "control_word": cw,
               "single_sequence": transition == "terminal", "y": 0.0}
    for action, peer, facing, field, mode in itertools.product(
            (197, 198, 199), (0x43A00000, 0x44200000, 0x44480000, 0x7FC12345),
            (-1, 1), (-1, 0, 65536), (0, 2)):
        yield {**base, "cohort": "facing", "action": action, "peer": peer,
               "facing": facing, "field": field, "mode": mode,
               "sequence": 2, "frame": 2 if action == 199 else 4, "timer": -1, "y": 0.0}
        yield {**base, "cohort": "completion", "action": action, "peer": peer,
               "facing": facing, "field": field, "mode": mode,
               "sequence": 0, "transition": "terminal", "counter": 7, "y": 0.0, "single_sequence": True}
    for facing, axis, field, count in itertools.product(
            (-128, -1, 0, 1, 127), (-2147483648, -1, 0, 1, 2147483647),
            (-1, 0, 65536), (-32768, -1, 4, 5, 44, 45, 32767)):
        yield {**base, "cohort": "input", "action": 200, "sequence": 1,
               "counter": 7, "facing": facing, "input": axis,
               "field": field, "counter730": count, "y": 0.0}
    for action, seed, facing, count in itertools.product(
            range(200, 204), (0, 5489, 0xFFFFFFFF), (-128, -1, 0, 1, 127), (-5, 0, 4, 5)):
        yield {**base, "cohort": "random", "action": action, "seed": seed,
               "sequence": 1, "facing": facing, "counter": count, "y": 0.0 if action == 200 else 100.0}
    for action, facing, seed, cw, position in itertools.product(
            range(200, 204), (-128, -1, 0, 1, 127), (0, 5489),
            (0x27F, 0x37F), (640.0, 33554432.0)):
        yield {**base, "cohort": "movement_random_lifetimes", "action": action,
               "sequence": 1, "facing": facing, "seed": seed, "control_word": cw,
               "counter": 4 if action == 200 else 5, "x": position,
               "y": 0.0 if action == 200 else 100.0}

    pairs = ((0, 0x4B800000), (0x80000000, 0xCB800000),
             (0x43FFFFFF, 0x501502F9), (0x44200001, 0x7FC12345),
             (0x449FFFFF, 0x7F812345), (0x3F000001, 1), (0x3EAAAAAB, 0x80000001))
    for action, bits, cw, facing, seed in itertools.product(
            range(200, 204), pairs, (0x27F, 0x37F), (-1, 1), (0, 5489)):
        yield {**base, "cohort": "coordinates", "action": action, "sequence": 1,
               "coordinate_bits": (bits[0], 0) if action == 200 else bits, "counter": 4 if action == 200 else 5,
               "control_word": cw, "facing": facing, "seed": seed}


class Probe(recovery.Probe):
    helpers = HELPERS
    resource_keys = KEYS
    resource_size = 0x20000
    frame_capacity = 6
    argument_helpers = recovery.Probe.argument_helpers | {0x406670}

    def __init__(self, image, code, candidate):
        super().__init__(image, code, candidate)
        self.seed_packets = {}
        self.case_sites = set()
        uc, sp = self.engine, STACK+0xFF00
        for seed in (0, 5489, 0xFFFFFFFF):
            uc.context_restore(self.initial)
            uc.mem_write(sp, struct.pack("<II", RETURN, seed))
            uc.reg_write(r.UC_X86_REG_ESP, sp)
            self.failure, self.calls, self.saw_ret = None, [], False
            uc.emu_start(0x406670, RETURN, count=10000)
            if (self.failure or not self.saw_ret or uc.reg_read(r.UC_X86_REG_EIP) != RETURN
                    or uc.reg_read(r.UC_X86_REG_ESP) != sp+4
                    or struct.unpack("<I", uc.mem_read(MT_INDEX, 4))[0] != 624):
                raise ValueError("original MT seeding did not complete")
            self.seed_packets[seed] = bytes(uc.mem_read(MT_STATE, MT_BYTES))
        self.helper_counts.clear()

    def helper_receiver(self, address):
        return None if address in (0x406670, 0x4066B0) else super().helper_receiver(address)

    def write(self, uc, access, address, size, value, unused):
        pc = uc.reg_read(r.UC_X86_REG_EIP)
        if (size == 4 and address % 4 == 0
                and (address == MT_INDEX or MT_STATE <= address < MT_STATE+MT_BYTES)
                and (0x406670 <= pc < 0x4066AD or 0x4066B0 <= pc < 0x4067C7)):
            return
        super().write(uc, access, address, size, value, unused)

    def step(self, uc, address, size):
        super().step(uc, address, size)
        if not self.candidate and ADDRESS <= address < ADDRESS+SIZE:
            self.case_sites.add(address)

    def fixture_has_linked_terminal(self, case):
        return not case.get("single_sequence", False)

    def prepare_extra_case(self, case):
        self.case_sites = set()
        self.engine.mem_write(MT_INDEX, struct.pack("<I", 624))
        self.engine.mem_write(MT_STATE, self.seed_packets[case["seed"]])

    def extra_actor_fields(self, case):
        coordinates = ((0xEC, "I", case["coordinate_bits"][0]),
                       (0xF0, "I", case["coordinate_bits"][1])) if "coordinate_bits" in case else ()
        return (*coordinates, (0x2000+0xEC, "I", case["peer"]), (0x6B4, "i", case["input"]),
                (0x72C, "B", case["mode"]), (0x732, "h", case["counter732"]))

    def extra_result(self):
        return {"mt_index": bytes(self.engine.mem_read(MT_INDEX, 4)),
                "mt_state": bytes(self.engine.mem_read(MT_STATE, MT_BYTES))}


def check_target_case(case, result, sites):
    # These are instruction-derived coverage requirements, not candidate output.
    if case["cohort"] == "input" and 0x47AA7C not in sites:
        raise ValueError("input fixture bypassed action200's actual input gates")
    if case["cohort"] == "facing":
        site = {197: 0x47A6F5, 198: 0x47A83B, 199: 0x47A92B}[case["action"]]
        if site not in sites:
            raise ValueError("facing fixture bypassed the actual peer comparisons")
    if case["cohort"] == "frame_transition":
        calls = Counter(call[0] for call in result["calls"])
        wanted = {"unexpired": (0, 0), "frame": (1, 0), "block": (1, 1), "terminal": (1, 1)}[case["transition"]]
        if (calls[0x45C1A0], calls[0x45C220]) != wanted:
            raise ValueError(f"actual frame/block transitions not reached: {case}")
    if case["cohort"] == "completion":
        actions = [call[2] for call in result["calls"] if call[0] == 0x45BFE0]
        expected = [700] if case["mode"] == 2 else [0, 1] if case["field"] > 0 else [0]
        if actions != expected:
            raise ValueError(f"completion fixture bypassed its actual action setters: {case}; got {actions}")
    if case["cohort"] in ("random", "coordinates", "movement_random_lifetimes"):
        counter = case["counter"] + (case["action"] == 200)
        should_emit = counter % 5 == 0
        if case["action"] == 201 and "coordinate_bits" in case:
            y = struct.unpack("<f", struct.pack("<I", case["coordinate_bits"][1]))[0]
            should_emit = should_emit and not y <= 0.0
        calls = sum(call[0] == 0x4066B0 for call in result["calls"])
        if calls != (2 if should_emit else 0):
            raise ValueError(f"random fixture has {calls} draws; expected {2 if should_emit else 0}: {case}")
        if should_emit and result["spawn_request"][:2] != (0x435240, 124):
            raise ValueError("random fixture did not reach actual effect124 request")


COHORT_COUNTS = {"motion": 1980, "animation": 1100, "frame_transition": 88,
                 "facing": 144, "completion": 144, "input": 525, "random": 240, "coordinates": 224,
                 "movement_random_lifetimes": 160}


def audit(object_path, smoke=False, selected_cohorts=None):
    support_paths = [Path(__file__), ROOT / "scripts/audit-reimu-low-actions.py",
                     ROOT / "scripts/audit-reimu-recovery-actions.py",
                     ROOT / "scripts/reimu_animation_fixture.py",
                     ROOT / "scripts/audit-common-fighter-animation-paths.py"]
    support_hashes = {str(path.relative_to(ROOT)): linked_pe.sha(path) for path in support_paths}
    canonical = linked_pe.comparator()
    target_sha = canonical.verify_target()
    target = canonical.target_bytes(ADDRESS, SIZE)
    if hashlib.sha256(target).hexdigest() != BODY_SHA:
        raise ValueError("Reimu root boundary/hash changed")
    mapper = load_script("reimu_movement_coff", "compare-giant-action-switches.py")
    obj = mapper.CoffObject(object_path, symbol_base=SYMBOL)
    rel32 = {symbol.name: address for symbol in obj.symbols.values()
             for name, address in CALL_TARGETS.items() if symbol.name.startswith("?"+name+"@")}
    rel32["__ftol2_sse"] = 0x68A1A0
    known = dict(canonical.known_data_targets())
    bindings = {"3fe8000000000000": 0x6C12A0, "405b800000000000": 0x6C3E78,
                "41200000": 0x6D6EEC, "405e000000000000": 0x6C3E70,
                "3ee66666": 0x6C3E80, "c1200000": 0x6C3B20, "40800000": 0x6CD200,
                "c1600000": 0x6C3E84, "4008000000000000": 0x6C3B78,
                "4054000000000000": 0x6C0850, "41780000": 0x6C3E88,
                "4f800000": 0x6D6EF8, "4049000000000000": 0x6C3C08,
                "3fe0000000000000": 0x6CD138, "41000000": 0x6C2874,
                "3eb33333": 0x6C3E90, "c1480000": 0x6C3E8C, "41480000": 0x6C3C48,
                "40900000": 0x6C3EA8, "3ff0000000000000": 0x6CD160,
                "42aa0000": 0x6C4004, "3e800000": 0x6C3440, "3f647ae140000000": 0x6C3B50,
                "40000000": 0x6C13F0, "4044000000000000": 0x6C13D0,
                "c000000000000000": 0x6CD1F0, "4004000000000000": 0x6C33A0,
                "40a00000": 0x6C3B70}
    for bits, address in bindings.items():
        literal = bytes.fromhex(bits)[::-1]
        if canonical.target_bytes(address, len(literal)) != literal:
            raise ValueError(f"target numeric binding changed: {address:#x}")
        known.setdefault("__real@"+bits, (address, literal, frozenset({0}), "literal"))
    object_sha = linked_pe.sha(object_path)
    candidate = canonical.coff_symbol_bytes(object_path, SYMBOL, ADDRESS, len(obj.text), rel32, known, {})
    if len(candidate) > SIZE or any(ADDRESS < start+length and start < ADDRESS+len(candidate)
                                  for start, (length, _) in HELPERS.items()):
        raise ValueError("candidate staging body overlaps a real helper")
    image = pefile.PE(str(ROOT / "resources/th105.exe")).get_memory_mapped_image()
    if (image[0x2FA898:0x2FBC98] != bytes(0x1400)
            or canonical.target_bytes(0x6FCA98, 0x200) != bytes(0x200)
            or canonical.target_bytes(0x6FA880, 4) == struct.pack("<I", 16)):
        raise ValueError("fixture needs original flat surface/inactive event context")
    probes = [Probe(image, target, False), Probe(image, candidate, True)]
    count = mismatches = 0
    digest, cohorts, stops, examples = hashlib.sha256(), Counter(), Counter(), []
    for case in cases(smoke):
        if selected_cohorts and case["cohort"] not in selected_cohorts:
            continue
        expected, actual = (probe.evaluate(case) for probe in probes)
        check_target_case(case, expected, probes[0].case_sites)
        count += 1
        cohorts[case["cohort"]] += 1
        stops[hex(expected["spawn_request"][0]) if expected["spawn_request"] else "ret"] += 1
        digest.update(json.dumps(case, sort_keys=True).encode())
        if expected != actual:
            mismatches += 1
            if len(examples) < 6:
                examples.append({"case": case, "different_actor_offsets": [hex(i) for i, (a, b) in
                                 enumerate(zip(expected["actor"], actual["actor"])) if a != b],
                                 "target_calls": expected["calls"], "candidate_calls": actual["calls"],
                                 "target_request": expected["spawn_request"], "candidate_request": actual["spawn_request"],
                                 "rng_differs": (expected["mt_index"], expected["mt_state"]) !=
                                                (actual["mt_index"], actual["mt_state"])})
        if count % 1000 == 0:
            print(f"Reimu movement/attack: {count}, differences {mismatches}", file=sys.stderr)
    expected_count = sum(COHORT_COUNTS[name] for name in set(selected_cohorts)) if selected_cohorts else 99 if smoke else 4445
    if (count != expected_count or linked_pe.sha(object_path) != object_sha
            or any(linked_pe.sha(ROOT / path) != digest for path, digest in support_hashes.items())):
        raise ValueError("input matrix incomplete or an input changed during execution")
    return {"schema": "th105-reimu-movement-attack-native-v1", "target_sha256": target_sha,
            "body_sha256": BODY_SHA, "object_sha256": object_sha,
            "cases": count, "mismatch_count": mismatches, "cohorts": dict(cohorts),
            "selected_cohorts": selected_cohorts, "stops": dict(stops), "input_sha256": digest.hexdigest(), "examples": examples,
            "visited_root_instructions": [len(probe.visited) for probe in probes],
            "helper_counts": [{HELPERS[address][1]: probe.helper_counts[address]
                              for address in HELPERS} for probe in probes],
            "helper_sha256": {hex(address): hashlib.sha256(canonical.target_bytes(address, length)).hexdigest()
                              for address, (length, _) in HELPERS.items()},
            "native_seed_state_sha256": {str(seed): hashlib.sha256(packet).hexdigest()
                                         for seed, packet in probes[0].seed_packets.items()},
            "unicorn_version": unicorn.__version__, "python_version": sys.version.split()[0],
            "unicorn_library_sha256": linked_pe.sha(Path(unicorn_api._uc._name)),
            "build_provenance_verified": False, "support_sha256": support_hashes,
            "scope": "supplied flat/read-only resource/zero-handle context; real helpers/MT state; "
                     "RET or complete request at actual wrapper entry; no returning request, "
                     "full-gameplay, floating-exception or canonical-exact claim"}


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("object", type=Path)
    selection = parser.add_mutually_exclusive_group()
    selection.add_argument("--smoke", action="store_true")
    selection.add_argument("--cohort", action="append", choices=tuple(COHORT_COUNTS))
    args = parser.parse_args()
    try:
        result = audit(args.object, args.smoke, args.cohort)
    except (KeyError, OSError, ValueError, unicorn.UcError) as error:
        parser.exit(2, f"Reimu movement/attack audit failed: {error}\n")
    print(json.dumps(result, indent=2))
    raise SystemExit(1 if result["mismatch_count"] else 0)
