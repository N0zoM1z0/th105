#!/usr/bin/env python3
"""Native comparison of staged Reimu actions71..78; no exact/root credit.

Returning cases execute unchanged original helpers. Request cases stop at an
actual object/effect wrapper entry and compare its request, without supplying
a result. Returning continuations beyond these requests remain outside proof.
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
from reimu_animation_fixture import RESOURCE, TREE, VECTOR, resource_graph

ROOT = Path(__file__).resolve().parents[1]


def load_script(name, filename):
    import importlib.util
    spec = importlib.util.spec_from_file_location(name, ROOT / "scripts" / filename)
    module = importlib.util.module_from_spec(spec)
    sys.modules[name] = module
    spec.loader.exec_module(module)
    return module


low = load_script("reimu_recovery_low_contract", "audit-reimu-low-actions.py")
ADDRESS, SIZE, BODY_SHA = low.ADDRESS, low.SIZE, low.BODY_SHA
OWNER, STACK, RETURN, VTABLE = low.OWNER, low.STACK, low.RETURN, low.VTABLE
SYMBOL = "?try_run_checked_recovery_action@ReimuActionStatePreludeView@th105@@QAE_NXZ"
KEYS = tuple(range(11)) + tuple(range(71, 79)) + (97,)
WORLD = 0x6FBD00
HELPERS = {**low.HELPERS, 0x4359D0: (21, "publish_layout"),
           0x427280: (10, "layout_setter"), 0x435110: (67, "reset_scratch"),
           0x465190: (66, "spawn_request"),
           0x473F90: (244, "secondary_event_cycle"),
           0x435240: (52, "effect_request")}
CALL_TARGETS = {**low.CALL_TARGETS, "classify_fighter_x_boundary": 0x435910,
                "publish_battle_layout_scalar": 0x4359D0,
                "dispatch_indexed_event_member": 0x4359F0,
                "reset_fighter_action_scratch": 0x435110,
                "spawn_owned_object_via_manager": 0x465190}


def cases(smoke=False):
    base = dict(action=71, vx=0xC0400000, vy=0x40A00000, ay=0x3F000000,
                flag=1, y=100.0, x=640.0, sequence=0, transition="unexpired",
                duration=3, counter=7, timer=None, frame=0, limit=None, field=0,
                facing=1, control_word=0x27F, spawn=1, counter730=7,
                angle=0x41F00000, coupled=1, cohort="smoke")
    changes = ({}, {"sequence": 1, "vy": 0x3F800000},
               {"y": 0.0, "vy": 0xC0200000}, {"x": -10.0},
               {"transition": "block", "sequence": 0},
               {"sequence": 1, "counter": -1, "timer": -1},
               {"sequence": 1, "counter": 0, "timer": 0, "spawn": 0},
               {"sequence": 1, "counter": -1, "timer": -1, "spawn": 0})
    if smoke:
        for action, change in itertools.product(range(71, 79), changes):
            yield {**base, "action": action, **change}
        return
    pairs = ((0, 0), (0x80000000, 0), (0x3F800000, 0x3F000000),
             (0x40000000, 0x3F000000), (0x40000001, 0x3F000000),
             (0x3FFFFFFF, 0x3F000000), (0xC0200000, 0x3F000000),
             (1, 0), (0x80000001, 0), (0x7F800000, 0x3F000000),
             (0xFF800000, 0x3F000000), (0x7FC12345, 0), (0x7F812345, 0),
             (0x7FC12345, 0xFFC12345), (0xFFC12345, 0x7FC12345))
    for action, (vy, ay), sequence, y, cw in itertools.product(
            range(71, 79), pairs, (-1, 0, 1, 2), (0.0, 100.0), (0x27F, 0x37F)):
        yield {**base, "cohort": "gravity", "action": action, "vy": vy,
               "ay": ay, "sequence": sequence, "y": y, "control_word": cw}
    velocities = (0, 0x80000000, 0xBF000000, 0xBF800000, 0xC0200000,
                  0xC1700000, 0xC16FFFFF, 0xC1700001, 0xC1C80000,
                  0xC1C7FFFF, 0xC1C80001, 0x7FC12345, 0x7F800000, 0xFF800000)
    for action, vx, x, counter, coupled in itertools.product(
            (71, 72, 73, 74, 75), velocities, (-10.0, 640.0, 1290.0),
            (-32768, -1, 0, 1, 32767), (0, 1)):
        yield {**base, "cohort": "boundary", "action": action, "vx": vx,
               "x": x, "counter730": counter, "coupled": coupled}
    for action, transition, facing, spawn in itertools.product(
            range(71, 79), ("unexpired", "frame", "block", "terminal"),
            (-128, -1, 0, 1, 127), (0, 1)):
        for sequence in ((3,) if transition == "terminal" else (0, 1)):
            yield {**base, "cohort": "animation", "action": action,
                   "transition": transition, "sequence": sequence, "facing": facing,
                   "spawn": spawn, "counter": -1, "timer": -1}
    for action, facing in itertools.product((71, 74, 77), (-128, -1, 0, 1, 127)):
        yield {**base, "cohort": "spawn_entry", "action": action, "sequence": 1,
               "counter": 0, "timer": 0, "spawn": 0, "facing": facing}


class Probe(low.Probe):
    helpers = HELPERS
    resource_keys = KEYS
    frame_capacity = 2

    def fixture_has_linked_terminal(self, case):
        return True

    def prepare_extra_case(self, case):
        pass

    def extra_actor_fields(self, case):
        return ()

    def extra_result(self):
        return {}
    argument_helpers = low.ARGUMENT_HELPERS | {0x4359D0, 0x427280}

    def helper_receiver(self, address):
        if address == 0x427280:
            return 0x6FBCC0
        if address == 0x435110:
            return OWNER+4
        return super().helper_receiver(address)

    def write(self, uc, access, address, size, value, unused):
        if address == WORLD and size == 4 and uc.reg_read(r.UC_X86_REG_EIP) == 0x427284:
            return
        super().write(uc, access, address, size, value, unused)

    def step(self, uc, address, size):
        super().step(uc, address, size)
        if address in (0x465190, 0x435240):
            count = 7 if address == 0x465190 else 5
            self.spawn_request = (address, *struct.unpack("<"+"I"*count,
                uc.mem_read(uc.reg_read(r.UC_X86_REG_ESP)+4, count*4)))
            uc.emu_stop()

    def evaluate(self, case):
        uc = self.engine
        uc.context_restore(self.initial)
        uc.mem_write(OWNER, bytes(0x10000))
        uc.mem_write(STACK+0xC000, bytes(0x4000))
        uc.mem_write(WORLD, bytes.fromhex("0000803f"))
        graph, blocks, frames, frame_count = resource_graph(case, self.resource_keys, linked_terminal=self.fixture_has_linked_terminal(case), frame_capacity=self.frame_capacity)
        uc.mem_write(RESOURCE, graph)
        self.prepare_extra_case(case)
        action, sequence = case["action"], case["sequence"]
        index = sequence if 0 <= sequence < 4 else 0
        block, frame = blocks[action]+index*0x20, frames[action]+index*(0x400 if self.frame_capacity > 2 else 0x200)
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


def audit(object_path, smoke=False):
    support_paths = [Path(__file__), ROOT / "scripts/audit-reimu-low-actions.py",
                     ROOT / "scripts/reimu_animation_fixture.py",
                     ROOT / "scripts/audit-common-fighter-animation-paths.py"]
    support_hashes = {str(path.relative_to(ROOT)): linked_pe.sha(path) for path in support_paths}
    canonical = linked_pe.comparator()
    target_sha = canonical.verify_target()
    target = canonical.target_bytes(ADDRESS, SIZE)
    if hashlib.sha256(target).hexdigest() != BODY_SHA:
        raise ValueError("Reimu root boundary/hash changed")
    mapper = load_script("reimu_recovery_coff", "compare-giant-action-switches.py")
    obj = mapper.CoffObject(object_path, symbol_base=SYMBOL)
    rel32 = {symbol.name: address for symbol in obj.symbols.values()
             for name, address in CALL_TARGETS.items() if symbol.name.startswith("?"+name+"@")}
    rel32["__ftol2_sse"] = 0x68A1A0
    known = dict(canonical.known_data_targets())
    for bits, address in (("3f000000", 0x6CD140), ("40400000", 0x6D6ED8),
                          ("41200000", 0x6D6EEC), ("c0a00000", 0x6C3B58),
                          ("c0400000", 0x6C3B5C), ("c000000000000000", 0x6CD1F0),
                          ("3ff0000000000000", 0x6CD160), ("4004000000000000", 0x6C33A0),
                          ("40a00000", 0x6C3B70), ("40800000", 0x6CD200),
                          ("403e000000000000", 0x6C0F00), ("c02e000000000000", 0x6C3B60),
                          ("c039000000000000", 0x6C3B68), ("40000000", 0x6C13F0)):
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
        raise ValueError("fixture needs original flat surface and zero event handles")
    probes = [Probe(image, target, False), Probe(image, candidate, True)]
    count = mismatches = 0
    digest, cohorts, stops, examples = hashlib.sha256(), Counter(), Counter(), []
    for case in cases(smoke):
        expected, actual = (probe.evaluate(case) for probe in probes)
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
                                 "target_spawn": expected["spawn_request"], "candidate_spawn": actual["spawn_request"]})
        if count % 1000 == 0:
            print(f"Reimu recovery actions: {count}, differences {mismatches}", file=sys.stderr)
    if (count != (64 if smoke else 4595) or linked_pe.sha(object_path) != object_sha
            or any(linked_pe.sha(ROOT / path) != digest for path, digest in support_hashes.items())):
        raise ValueError("input matrix incomplete or an input changed during execution")
    return {"schema": "th105-reimu-recovery-native-v1", "target_sha256": target_sha,
            "body_sha256": BODY_SHA, "object_sha256": object_sha,
            "cases": count, "mismatch_count": mismatches, "cohorts": dict(cohorts),
            "stops": dict(stops), "input_sha256": digest.hexdigest(), "examples": examples,
            "visited_root_instructions": [len(probe.visited) for probe in probes],
            "helper_counts": [{HELPERS[address][1]: probe.helper_counts[address]
                              for address in HELPERS} for probe in probes],
            "helper_sha256": {hex(address): hashlib.sha256(canonical.target_bytes(address, length)).hexdigest()
                              for address, (length, _) in HELPERS.items()},
            "unicorn_version": unicorn.__version__, "python_version": sys.version.split()[0],
            "unicorn_library_sha256": linked_pe.sha(Path(unicorn_api._uc._name)),
            "build_provenance_verified": False, "support_sha256": support_hashes,
            "scope": "actions71..78 in supplied flat/read-only resource context; real helpers/RET or "
                     "stop at actual object/effect wrapper with full request; no callback-returning requests, "
                     "full-gameplay, floating-exception, source-completeness or canonical-exact claim"}


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("object", type=Path)
    parser.add_argument("--smoke", action="store_true")
    args = parser.parse_args()
    try:
        result = audit(args.object, args.smoke)
    except (KeyError, OSError, ValueError, unicorn.UcError) as error:
        parser.exit(2, f"Reimu recovery-action audit failed: {error}\n")
    print(json.dumps(result, indent=2))
    raise SystemExit(1 if result["mismatch_count"] else 0)
