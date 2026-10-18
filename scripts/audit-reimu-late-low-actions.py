#!/usr/bin/env python3
"""Native comparison of remaining Reimu low-table actions and direct300.

The phase is not an original function boundary. Executes original helpers,
original angle-table initialization and MT19937; stops at real world requests.
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
from reimu_late_low_fixture import resource_graph, native_orientation_table

ROOT = Path(__file__).resolve().parents[1]


def load_script(name, filename):
    import importlib.util
    spec = importlib.util.spec_from_file_location(name, ROOT / "scripts" / filename)
    module = importlib.util.module_from_spec(spec)
    sys.modules[name] = module
    spec.loader.exec_module(module)
    return module


movement = load_script("reimu_late_movement_contract", "audit-reimu-movement-attack-actions.py")
ADDRESS, SIZE, BODY_SHA = movement.ADDRESS, movement.SIZE, movement.BODY_SHA
OWNER, STACK, RETURN = movement.OWNER, movement.STACK, movement.RETURN
VTABLE = movement.recovery.VTABLE
RESOURCE, TREE, VECTOR = movement.recovery.RESOURCE, movement.recovery.TREE, movement.recovery.VECTOR
WORLD = movement.recovery.WORLD
SYMBOL = "?try_run_checked_late_low_action@ReimuActionStatePreludeView@th105@@QAE_NXZ"
ACTIONS = (208, 209, 210, 211, 212, 214, 215, 220, 221, 222, 223, 224, 225, 226, 300)
KEYS = (0, 1, 2, 9, 10, 204, *ACTIONS)
HELPERS = {**movement.HELPERS, 0x406360: (100, "sine_lookup"),
           0x4063D0: (94, "cosine_lookup"), 0x68BAAE: (182, "fabs"),
           0x696387: (39, "control_word"), 0x46BF30: (74, "adjust_counter"),
           0x478EE0: (184, "directional_action_gate")}
CALL_TARGETS = {**movement.CALL_TARGETS, "adjust_counter_482": 0x46BF30,
                "try_dispatch_directional_action_208_210": 0x478EE0,
                "lookup_orientation_sine_quantized_abs": 0x406360,
                "lookup_orientation_cosine_quantized_abs": 0x4063D0}


def cases(smoke=False):
    base = {**next(movement.cases(True)), "action": 214, "y": 100.0,
            "sequence": 1, "counter730": 0, "mode4b8": 0, "held": 1,
            "gauge": 100, "turn_count": 0, "phase": 0.0, "speed": 5.0,
            "gate4b2": 0, "state": 0, "cohort": "smoke"}
    if smoke:
        for action, change in itertools.product(ACTIONS, (
                {}, {"sequence": 0, "y": 0.0}, {"sequence": 5},
                {"y": 0.0, "vy": 0xC0400000},
                {"counter": -1, "timer": -1},
                {"held": 0, "turn_count": 10},
                {"field": 1, "input": -1, "phase": 179.0},
                {"counter": 5, "sequence": 2},
                {"counter": 0, "sequence": 0, "timer": 0},
                {"single_sequence": True, "sequence": 0, "transition": "terminal"})):
            yield {**base, "action": action, **change}
        return
    for action, sequence, vy, y, cw in itertools.product(
            ACTIONS, (-1, 0, 1, 2, 5, 6),
            (0, 0xC1A00000, 0xC1A00001, 0x407FFFFF, 0x40800000, 0x7FC12345),
            (0.0, 100.0), (0x27F, 0x37F)):
        yield {**base, "cohort": "motion", "action": action, "sequence": sequence,
               "vy": vy, "y": y, "control_word": cw}
    for phase, axis, vertical, sequence, mode, cw in itertools.product(
            (-180.0, -90.0, -0.0, 89.75, 179.75, 359.75), (-1, 0, 1), (-1, 0, 1),
            (1, 3), (0, 1), (0x27F, 0x37F)):
        yield {**base, "cohort": "steering", "phase": phase, "input": axis,
               "field": vertical, "sequence": sequence, "mode4b8": mode,
               "control_word": cw}
    for sequence, held, count, gauge, facing, peer in itertools.product(
            (1, 2, 3, 4), (0, 1), (9, 10, 32767), (0, 4, 100),
            (-1, 1), (0x43A00000, 0x44480000)):
        yield {**base, "cohort": "flight_exit", "sequence": sequence, "held": held,
               "turn_count": count, "gauge": gauge, "facing": facing, "peer": peer,
               "phase": 0.0 if sequence in (1, 2) else 180.0}
    for action, sequence, facing, spawn in itertools.product(
            ACTIONS, (0, 1, 2, 3, 6), (-128, -1, 1), (0, 1)):
        yield {**base, "cohort": "nodes", "action": action, "sequence": sequence,
               "facing": facing, "spawn": spawn, "counter": -1, "timer": -1,
               "y": 0.0}
    for action, facing, seed in itertools.product(
            (208, 211, 220, 221, 222, 223, 224, 225, 226), (-1, 1), (0, 5489)):
        yield {**base, "cohort": "random", "action": action, "facing": facing,
               "seed": seed, "counter": 4 if action == 223 else 5,
               "sequence": 2 if action in (225, 226) else 1,
               "y": 0.0 if action == 223 else 100.0}
    for action, facing, seed, cw, position in itertools.product(
            (208, 211, 220, 221, 222), (-128, -1, 0, 1, 127), (0, 5489),
            (0x27F, 0x37F), (-0.0, 640.0, 1048576.0, 33554432.0)):
        # At2**25 the m64 x+50 snapshot carries bits that an m32 local loses.
        yield {**base, "cohort": "random_lifetimes", "action": action,
               "facing": facing, "seed": seed, "counter": 5, "sequence": 1,
               "x": position, "y": 100.0, "control_word": cw}
    for action, facing, seed, cw, position in itertools.product(
            (223, 224, 225, 226), (-128, -1, 0, 1, 127), (0, 5489),
            (0x27F, 0x37F), (-0.0, 640.0, 1048576.0, 33554432.0)):
        yield {**base, "cohort": "random124_lifetimes", "action": action,
               "facing": facing, "seed": seed, "counter": 4 if action == 223 else 5,
               "sequence": 2 if action in (225, 226) else 1,
               "x": position, "y": 0.0 if action == 223 else 100.0, "control_word": cw}
    for phase, facing, mode, cw, height in itertools.product(
            (-180.0, -90.0, -0.0, 89.75, 179.75, 359.75), (-128, -1, 0, 1, 127),
            (0, 1), (0x27F, 0x37F), (100.0, 681.0)):
        # Keep the sequence consistent with post-steering VX so no sequence
        # callback resets the frame counter before the advertised effect.
        yield {**base, "cohort": "flight_effect_lifetimes", "action": 214,
               "phase": phase, "facing": facing, "mode4b8": mode,
               "sequence": 3 if phase in (-180.0, 179.75) else 1,
               "counter": 0, "control_word": cw, "y": height}
    for facing, horizontal, vertical, state, gate in itertools.product(
            (-1, 1), (-1, 0, 1), (-1, 0), (0, 1), (0, 1)):
        yield {**base, "cohort": "directional", "action": 300, "mode4b8": 10,
               "input": horizontal, "field": vertical, "state": state,
               "gate4b2": gate, "facing": facing, "y": 0.0}


class Probe(movement.Probe):
    helpers = HELPERS
    resource_keys = KEYS
    resource_size = 0x40000
    argument_helpers = movement.Probe.argument_helpers | {
        0x406360, 0x4063D0, 0x68BAAE, 0x696387, 0x46BF30, 0x478EE0}

    def __init__(self, image, code, candidate, tables):
        self.tables = tables
        super().__init__(image, code, candidate)

    def helper_receiver(self, address):
        if address in (0x406360, 0x4063D0, 0x68BAAE, 0x696387):
            return None
        return super().helper_receiver(address)

    def step(self, uc, address, size):
        super().step(uc, address, size)
        if address in (0x68BAAE, 0x696387, 0x46BF30):
            self.calls.append(("native_args", address,
                bytes(uc.mem_read(uc.reg_read(r.UC_X86_REG_ESP)+4, 8)).hex()))

    def prepare_extra_case(self, case):
        super().prepare_extra_case(case)
        self.engine.mem_write(0x6FE8B0, self.tables[case["control_word"]][0])

    def extra_actor_fields(self, case):
        return (*super().extra_actor_fields(case),
                (0x482, "h", case["gauge"]), (0x486, "h", -1),
                (0x4B2, "h", case["gate4b2"]), (0x4B8, "i", case["mode4b8"]),
                (0x6C8, "i", case["held"]), (0x736, "h", case["turn_count"]),
                (0x73C, "f", case["speed"]), (0x740, "f", case["phase"]),
                (0x180, "i", case["state"]))

    def evaluate(self, case):
        uc = self.engine
        uc.context_restore(self.initial)
        uc.mem_write(OWNER, bytes(0x10000))
        uc.mem_write(STACK+0xC000, bytes(0x4000))
        uc.mem_write(WORLD, bytes.fromhex("0000803f"))
        graph, blocks, frames, frame_count = resource_graph(case, self.resource_keys)
        uc.mem_write(RESOURCE, graph)
        self.prepare_extra_case(case)
        action, sequence = case["action"], case["sequence"]
        index = sequence if 0 <= sequence < 7 else 0
        block, frame = blocks[action]+index*0x20, frames[action]+index*0x400
        timer = case["timer"] if case["timer"] is not None else 0 if case["transition"] == "unexpired" else case["duration"]-1
        fields = ((0, "I", VTABLE), (0xEC, "f", case["x"]), (0xF0, "f", case["y"]),
                  (0xF4, "I", case["vx"]), (0xF8, "I", case["vy"]), (0xFC, "f", 0.2),
                  (0x100, "I", case["ay"]), (0x104, "b", case["facing"]),
                  (0x12C, "I", case["angle"]), (0x130, "I", VECTOR),
                  (0x13C, "h", action), (0x13E, "h", sequence), (0x140, "h", case["frame"]),
                  (0x142, "h", timer), (0x144, "i", case["counter"]), (0x148, "h", frame_count),
                  (0x14C, "h", case["limit"] if case["limit"] is not None else case["duration"]),
                  (0x150, "I", frame), (0x158, "I", frame+case["frame"]*0x88),
                  (0x15C, "I", block), (0x160, "I", TREE), (0x170, "I", OWNER+0x2000),
                  (0x174, "h", 1), (0x47E, "B", case["flag"]), (0x490, "B", case["coupled"]),
                  (0x6AC, "I", 0x42C60000), (0x6B8, "i", case["field"]),
                  (0x730, "h", case["counter730"]), (0x732, "h", -77),
                  (0x7A2, "h", 85), (0x7A4, "h", case["spawn"]))
        for offset, fmt, value in (*fields, *self.extra_actor_fields(case)):
            uc.mem_write(OWNER+offset, struct.pack("<"+fmt, value))
        saved = {r.UC_X86_REG_EBX: 0x11111111, r.UC_X86_REG_ESI: 0x22222222,
                 r.UC_X86_REG_EDI: 0x33333333, r.UC_X86_REG_EBP: 0x44444444}
        for register, value in saved.items():
            uc.reg_write(register, value)
        sp = STACK+0xFF00
        uc.mem_write(sp, struct.pack("<I", RETURN))
        uc.reg_write(r.UC_X86_REG_ESP, sp)
        uc.reg_write(r.UC_X86_REG_ECX, OWNER)
        uc.reg_write(r.UC_X86_REG_FPCW, case["control_word"])
        self.failure, self.calls, self.saw_ret, self.spawn_request = None, [], False, None
        try:
            uc.emu_start(ADDRESS, RETURN, count=100000)
        except unicorn.UcError as error:
            raise ValueError(f"{case}: {error} at {uc.reg_read(r.UC_X86_REG_EIP):#x}") from error
        if self.failure:
            raise ValueError(f"{case}: {self.failure}")
        if self.spawn_request is None:
            if (not self.saw_ret or uc.reg_read(r.UC_X86_REG_EIP) != RETURN
                    or uc.reg_read(r.UC_X86_REG_ESP) != sp+4
                    or any(uc.reg_read(reg) != value for reg, value in saved.items())):
                raise ValueError(f"recovery action did not restore RET ABI: {case}")
            if self.candidate and uc.reg_read(r.UC_X86_REG_EAX) & 0xFF != 1:
                raise ValueError("staged dispatcher did not report a handled action")
        if (uc.reg_read(r.UC_X86_REG_FPSW) >> 11) & 7:
            raise ValueError("recovery action leaves live x87 values")
        return {"actor": bytes(uc.mem_read(OWNER, 0x1000)), "calls": self.calls,
                "control_word": uc.reg_read(r.UC_X86_REG_FPCW),
                "world": bytes(uc.mem_read(WORLD, 4)), "spawn_request": self.spawn_request, **self.extra_result()}


def check_target_case(case, result, sites):
    if case["cohort"] == "steering" and not {0x47BA76, 0x47BBDB} <= sites:
        raise ValueError("flight fixture bypassed steering or resource consumption")
    if case["cohort"] == "directional" and 0x47CBC8 not in sites:
        raise ValueError("directional fixture bypassed action300's actual gate")
    if case["cohort"] == "flight_effect_lifetimes":
        if (not {0x47BBDB, 0x47BCC6, 0x47BCF2, 0x47BD23} <= sites
                or result["spawn_request"][:2] != (0x435240, 125)
                or any(sum(call[0] == address for call in result["calls"]) != 2
                       for address in (0x406360, 0x4063D0))):
            raise ValueError("flight fixture bypassed its real steering/cost/effect lookups")
    if case["cohort"] in ("random", "random_lifetimes", "random124_lifetimes"):
        calls = sum(call[0] == 0x4066B0 for call in result["calls"])
        code = 123 if case["action"] in (208, 211, 220, 221, 222) else 124
        if calls != 2 or result["spawn_request"][:2] != (0x435240, code):
            raise ValueError(f"random fixture bypassed its advertised two draws/request: {case}")


def audit(object_path, smoke=False, selected_cohorts=None):
    support_paths = [Path(__file__), ROOT / "scripts/reimu_late_low_fixture.py",
                     ROOT / "scripts/audit-reimu-movement-attack-actions.py",
                     ROOT / "scripts/audit-reimu-recovery-actions.py",
                     ROOT / "scripts/audit-reimu-low-actions.py",
                     ROOT / "scripts/reimu_animation_fixture.py",
                     ROOT / "scripts/audit-common-fighter-animation-paths.py"]
    support_hashes = {str(path.relative_to(ROOT)): linked_pe.sha(path) for path in support_paths}
    canonical = linked_pe.comparator()
    target_sha = canonical.verify_target()
    target = canonical.target_bytes(ADDRESS, SIZE)
    if hashlib.sha256(target).hexdigest() != BODY_SHA:
        raise ValueError("Reimu root boundary/hash changed")
    mapper = load_script("reimu_late_coff", "compare-giant-action-switches.py")
    obj = mapper.CoffObject(object_path, symbol_base=SYMBOL)
    rel32 = {symbol.name: address for symbol in obj.symbols.values()
             for name, address in CALL_TARGETS.items() if symbol.name.startswith("?"+name+"@")}
    rel32["__ftol2_sse"] = 0x68A1A0
    known = dict(canonical.known_data_targets())
    bindings = {'405e000000000000': 7093872, '405b800000000000': 7093880, '3ee66666': 7093888, 'c1200000': 7093024, 'c1600000': 7093892, '4000000000000000': 7086528, '3fe0000000000000': 7131448, '4054000000000000': 7080016, '40f00000': 7093844, '3fe8000000000000': 7082656, '4059000000000000': 7131536, '4066800000000000': 7171760, '41200000': 7171820, '3fd3333340000000': 7088752, '442a0000': 7093848, '3ff0000000000000': 7131488, '4008000000000000': 7093112, '3f266666': 7093860, '41a00000': 7093864, '41700000': 7093920, '418c0000': 7093856, '41000000': 7088244, 'c1000000': 7131696, '41100000': 7093852, '40400000': 7171800, '40800000': 7131648, '4f800000': 7171832, '4049000000000000': 7093256, 'c1a00000': 7093368}
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
    tables = {cw: native_orientation_table(image, cw) for cw in (0x27F, 0x37F)}
    probes = [Probe(image, target, False, tables), Probe(image, candidate, True, tables)]
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
                                 "target_request": expected["spawn_request"], "candidate_request": actual["spawn_request"]})
        if count % 1000 == 0:
            print(f"Reimu late low: {count}, differences {mismatches}", file=sys.stderr)
    expected_count = sum(COHORT_COUNTS[name] for name in set(selected_cohorts)) if selected_cohorts else 150 if smoke else sum(COHORT_COUNTS.values())
    if (count != expected_count or linked_pe.sha(object_path) != object_sha
            or any(linked_pe.sha(ROOT / path) != digest for path, digest in support_hashes.items())):
        raise ValueError("input matrix incomplete or an input changed during execution")
    return {"schema": "th105-reimu-late-low-native-v1", "target_sha256": target_sha,
            "body_sha256": BODY_SHA, "object_sha256": object_sha, "cases": count,
            "mismatch_count": mismatches, "cohorts": dict(cohorts), "stops": dict(stops),
            "selected_cohorts": selected_cohorts, "input_sha256": digest.hexdigest(), "examples": examples,
            "visited_root_instructions": [len(probe.visited) for probe in probes],
            "helper_counts": [{HELPERS[address][1]: probe.helper_counts[address]
                              for address in HELPERS} for probe in probes],
            "helper_sha256": {hex(address): hashlib.sha256(canonical.target_bytes(address, length)).hexdigest()
                              for address, (length, _) in HELPERS.items()},
            "orientation_initialization": [tables[cw][1] for cw in sorted(tables)],
            "unicorn_version": unicorn.__version__, "python_version": sys.version.split()[0],
            "unicorn_library_sha256": linked_pe.sha(Path(unicorn_api._uc._name)),
            "build_provenance_verified": False, "support_sha256": support_hashes,
            "scope": "supplied seven-sequence/flat/zero-handle context; original orientation initialization, "
                     "MT and helpers; RET or complete real world request; no returning request, "
                     "whole-game, floating-exception, full-root source or canonical-exact claim"}


COHORT_COUNTS = {"motion": 2160, "steering": 432, "flight_exit": 288,
                 "nodes": 450, "random": 36, "random_lifetimes": 400,
                 "random124_lifetimes": 320,
                 "flight_effect_lifetimes": 240,
                 "directional": 48}


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
        parser.exit(2, f"Reimu late-low audit failed: {error}\n")
    print(json.dumps(result, indent=2))
    raise SystemExit(1 if result["mismatch_count"] else 0)
