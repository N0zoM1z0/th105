#!/usr/bin/env python3
"""Execute Reimu actions0..10 against a staged VC8 source object.

Uses original helper bodies through native RET, including real action setters
and Reimu/CharacterEx finalizers. Supplied animation data is read-only, texture
and original event handles are zero; no helper result is substituted.
"""
from __future__ import annotations

import argparse
from collections import Counter
import hashlib
import importlib.util
import itertools
import json
from pathlib import Path
import struct
import sys

import capstone
import pefile
import unicorn
from unicorn import unicorn as unicorn_api
from unicorn import x86_const as r

import linked_pe
from reimu_animation_fixture import RESOURCE, TREE, HEAD, VECTOR, SLOT, resource_graph

ROOT = Path(__file__).resolve().parents[1]
ADDRESS, SIZE = 0x478FA0, 81550
BODY_SHA = "dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6"
SYMBOL = "?try_run_checked_low_action@ReimuActionStatePreludeView@th105@@QAE_NXZ"
OWNER, STACK, RETURN = 0x2000000, 0x2100000, 0x710000
VTABLE = 0x6C412C


def load_script(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / "scripts" / filename)
    module = importlib.util.module_from_spec(spec)
    sys.modules[name] = module
    spec.loader.exec_module(module)
    return module


animation = load_script("reimu_low_animation_contract", "audit-common-fighter-animation-paths.py")
HELPERS = dict(animation.HELPERS)
HELPERS.update({
    0x473DD0: (442, "landing"), 0x435DC0: (42, "at_surface"),
    0x45AF40: (27, "zero_motion"), 0x45BFE0: (26, "set_action"),
    0x435200: (22, "base_set_action"), 0x45C460: (154, "reset_sequence"),
    0x491C40: (3785, "reimu_finalize"), 0x477830: (4849, "common_finalize"),
    0x4359F0: (14, "event_member"), 0x43B1A0: (28, "event_dispatch"),
    0x401D50: (106, "sound_handle"),
})
CALL_TARGETS = {
    "resolve_stage_surface_landing_transition": 0x473DD0,
    "advance_frame_and_dispatch": 0x4351C0,
    "zero_velocity_acceleration": 0x45AF40,
    "has_crossed_stage_surface_while_descending": 0x5F9310,
    "reimu_stage_surface_height_at_x": 0x435D60,
}
ARGUMENT_HELPERS = {0x45BFE0, 0x435200, 0x45C390, 0x45C180, 0x407160,
                    0x4359F0, 0x43B1A0, 0x401D50}
VX_BITS = (0, 0x80000000, 1, 0x80000001, 0x007FFFFF, 0x807FFFFF, 0x00800000,
           0x80800000, 0x3EFFFFFF, 0x3F000000, 0x3F000001, 0xBEFFFFFF,
           0xBF000000, 0xBF000001, 0x3F800000, 0xBF800000, 0x40400000,
           0xC0400000, 0x41200000, 0xC1200000, 0x4B800000, 0xCB800000,
           0x7F7FFFFF, 0xFF7FFFFF, 0x7F800000, 0xFF800000, 0x7FC12345,
           0xFFC12345, 0x7F812345, 0xFF812345, 0x3E800000, 0xBE800000)


def cases(smoke=False):
    base = dict(action=0, vx=0x40400000, vy=0x40400000, ay=0x3F000000,
                flag=1, y=0.0, sequence=0, transition="unexpired", duration=3,
                counter=7, timer=None, frame=0, limit=None, field=0, facing=1,
                control_word=0x27F, cohort="smoke")
    if smoke:
        for action, change in itertools.product(range(11), (
                {}, {"vx": 0}, {"vx": 0x3F000000}, {"sequence": -1},
                {"transition": "block"}, {"transition": "terminal"},
                {"y": 100.0, "transition": "terminal", "duration": 1},
                {"sequence": 1, "counter": -1, "timer": -1, "limit": 32767})):
            yield {**base, "action": action, **change}
        return
    for action, vx, flag, y, cw in itertools.product(
            range(4), VX_BITS, (0, 1, 128), (0.0, 5.0, 6.0, 100.0), (0x27F, 0x37F)):
        yield {**base, "cohort": "slide", "action": action, "vx": vx,
               "flag": flag, "y": y, "control_word": cw}
    for action, vx, y, facing, transition, cw in itertools.product(
            (4, 5), (0, 0x40400000, 0xC0400000, 0x7F800000, 0xFF800000, 0x7FC12345),
            (0.0, 100.0), (-1, 1), ("unexpired", "frame", "block", "terminal"), (0x27F, 0x37F)):
        yield {**base, "cohort": "fixed", "action": action, "vx": vx,
               "y": y, "facing": facing, "transition": transition, "control_word": cw}
    pairs = ((0, 0), (0x80000000, 0x80000000), (0x3F800000, 0), (0xBF800000, 0),
             (0x3F800000, 0x3F000000), (0xBF800000, 0x3F000000),
             (0x3F000000, 0x3F000000), (0x3F000001, 0x3F000000), (0x3EFFFFFF, 0x3F000000),
             (1, 0), (0x80000001, 0), (0x7F800000, 0x3F000000), (0xFF800000, 0x3F000000),
             (0x7F800000, 0x7F800000), (0xFF800000, 0xFF800000),
             (0x7FC12345, 0), (0x7F812345, 0), (0, 0x7FC12345), (0, 0x7F812345),
             (0x7FC12345, 0xFFC12345), (0xFFC12345, 0x7FC12345),
             (0x7F812345, 0xFF812345), (0xFF812345, 0x7F812345), (0x7F7FFFFF, 0xFF7FFFFF))
    for action, (vy, ay), sequence, y, flag, cw in itertools.product(
            range(6, 10), pairs, (-1, 0, 1, 2), (0.0, 5.0, 6.0, 100.0), (0, 1), (0x27F, 0x37F)):
        yield {**base, "cohort": "air", "action": action, "vy": vy, "ay": ay,
               "sequence": sequence, "y": y, "flag": flag, "control_word": cw}
    for action in range(11):
        for transition, flag, vx, field, cw in itertools.product(
                ("unexpired", "frame", "block", "terminal"), (0, 1),
                (0, 0x80000000, 0x40400000, 0xC0400000),
                (0, 1, 65536, -1) if action == 10 else (0,), (0x27F, 0x37F)):
            yield {**base, "cohort": "animation", "action": action, "transition": transition,
                   "flag": flag, "vx": vx, "field": field, "control_word": cw}
    for action, sequence, counters, flag, cw in itertools.product(
            (6, 7, 8), (-1, 0, 1, 2), ((-1, -1, 0), (-1, 0, 0), (0, -1, 0), (-1, -1, 1)),
            (0, 1), (0x27F, 0x37F)):
        counter, timer, frame = counters
        yield {**base, "cohort": "wrap", "action": action, "sequence": sequence,
               "counter": counter, "timer": timer, "frame": frame, "limit": 32767,
               "flag": flag, "control_word": cw}
    for flag, vx, cw in itertools.product((0, 1), (0, 0x40400000, 0xBF800000), (0x27F, 0x37F)):
        yield {**base, "cohort": "capture", "action": 1, "y": 100.0, "duration": 1,
               "transition": "terminal", "flag": flag, "vx": vx, "control_word": cw}




class Probe:
    def __init__(self, image, code, candidate):
        self.engine = unicorn.Uc(unicorn.UC_ARCH_X86, unicorn.UC_MODE_32)
        self.engine.mem_map(0x400000, 0x311000)
        self.engine.mem_write(0x400000, image)
        self.engine.mem_write(ADDRESS, code)
        for address in (OWNER, STACK):
            self.engine.mem_map(address, 0x10000)
        self.engine.mem_map(RESOURCE, 0x10000, unicorn.UC_PROT_READ)
        self.initial = self.engine.context_save()
        self.reg = r
        self.decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
        self.decoder.detail = True
        self.end, self.candidate = ADDRESS+len(code), candidate
        self.visited, self.helper_counts, self.launch_sites = set(), Counter(), Counter()
        self.engine.hook_add(unicorn.UC_HOOK_CODE, self.instruction)
        self.engine.hook_add(unicorn.UC_HOOK_MEM_WRITE, self.write)

    def write(self, uc, access, address, size, value, unused):
        if not (OWNER <= address <= address+size <= OWNER+0x1000
                or STACK <= address <= address+size <= STACK+0x10000):
            self.failure = f"write outside actor/stack at {address:#x}"
            uc.emu_stop()

    def instruction(self, uc, address, size, unused):
        try:
            self.step(uc, address, size)
        except Exception as error:
            self.failure = str(error)
            uc.emu_stop()

    def step(self, uc, address, size):
        if ADDRESS <= address < self.end:
            self.visited.add(address)
        elif not any(start <= address < start+length for start, (length, _) in HELPERS.items()):
            raise ValueError(f"unreviewed execution at {address:#x}")
        if not self.candidate and address in (0x479570, 0x479632, 0x4796D0):
            self.launch_sites[address] += 1
        raw = bytes(uc.mem_read(address, size))
        if raw[0] == 0xE8:
            destination = address+5+int.from_bytes(raw[1:5], "little", signed=True)
            if size != 5 or destination not in HELPERS:
                raise ValueError(f"unreviewed direct call at {address:#x}")
        elif raw[0] == 0xFF and (raw[1] >> 3) & 7 in (2, 3):
            destination = animation.AnimationProbe.indirect_destination(self, raw, address)
            if destination not in HELPERS:
                raise ValueError(f"unreviewed virtual call {destination:#x}")
        if address in HELPERS:
            self.helper_counts[address] += 1
            receiver = (VECTOR if address == 0x40C100 else TREE if address == 0x45C320
                        else OWNER+4 if address in (0x407160, 0x4073A0, 0x4073C0)
                        else 0x702288 if address == 0x401D50
                        else None if address in (0x68A1A0, 0x407230, 0x43B1A0) else OWNER)
            if receiver is not None and uc.reg_read(r.UC_X86_REG_ECX) != receiver:
                raise ValueError(f"unreviewed receiver at {address:#x}")
            argument = None
            if address in ARGUMENT_HELPERS:
                argument = struct.unpack("<I", uc.mem_read(uc.reg_read(r.UC_X86_REG_ESP)+4, 4))[0]
            if address in (0x407160, 0x401D50) and argument != 0:
                raise ValueError("textured/audio-backend context is outside this fixture")
            self.calls.append((address, receiver, argument))
        if address == 0x68A1A0:
            top = (uc.reg_read(r.UC_X86_REG_FPSW) >> 11) & 7
            self.calls.append(("ftol2", uc.reg_read(r.UC_X86_REG_FP0+top)))
        if raw[0] in (0xC3, 0xC2):
            sp = uc.reg_read(r.UC_X86_REG_ESP)
            if struct.unpack("<I", uc.mem_read(sp, 4))[0] == RETURN:
                self.saw_ret = True

    def evaluate(self, case):
        uc = self.engine
        uc.context_restore(self.initial)
        uc.mem_write(OWNER, bytes(0x10000))
        uc.mem_write(STACK+0xC000, bytes(0x4000))
        graph, blocks, frames, frame_count = resource_graph(case)
        uc.mem_write(RESOURCE, graph)
        action, sequence = case["action"], case["sequence"]
        index = sequence if 0 <= sequence < 4 else 0
        block, frame = blocks[action]+index*0x20, frames[action]+index*0x200
        timer = case["timer"] if case["timer"] is not None else 0 if case["transition"] == "unexpired" else case["duration"]-1
        fields = ((0, "I", VTABLE), (0xEC, "f", 640.0), (0xF0, "f", case["y"]),
                  (0xF4, "I", case["vx"]), (0xF8, "I", case["vy"]), (0xFC, "f", 0.2),
                  (0x100, "I", case["ay"]), (0x104, "b", case["facing"]), (0x130, "I", VECTOR),
                  (0x13C, "h", action), (0x13E, "h", sequence), (0x140, "h", case["frame"]),
                  (0x142, "h", timer), (0x144, "i", case["counter"]), (0x148, "h", frame_count),
                  (0x14C, "h", case["limit"] if case["limit"] is not None else case["duration"]),
                  (0x150, "I", frame), (0x158, "I", frame+case["frame"]*0x88),
                  (0x15C, "I", block), (0x160, "I", TREE), (0x170, "I", OWNER+0x2000),
                  (0x174, "h", 1), (0x47E, "B", case["flag"]), (0x6B8, "i", case["field"]),
                  (0x7A2, "h", 85))
        for offset, fmt, value in fields:
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
        self.failure, self.calls, self.saw_ret = None, [], False
        uc.emu_start(ADDRESS, RETURN, count=100000)
        if self.failure:
            raise ValueError(f"{case}: {self.failure}")
        if (not self.saw_ret or uc.reg_read(r.UC_X86_REG_EIP) != RETURN
                or uc.reg_read(r.UC_X86_REG_ESP) != sp+4
                or any(uc.reg_read(register) != value for register, value in saved.items())):
            raise ValueError("low action did not restore its native RET ABI")
        if self.candidate and uc.reg_read(r.UC_X86_REG_EAX) & 0xFF != 1:
            raise ValueError("staged dispatcher did not report a handled low action")
        if (uc.reg_read(r.UC_X86_REG_FPSW) >> 11) & 7:
            raise ValueError("low action leaves live x87 values")
        return {"actor": bytes(uc.mem_read(OWNER, 0x1000)), "calls": self.calls,
                "control_word": uc.reg_read(r.UC_X86_REG_FPCW)}


def check_target_case(case, result):
    calls = Counter(call[0] for call in result["calls"])
    actions = [call[2] for call in result["calls"] if call[0] == 0x45BFE0]
    if case["cohort"] == "animation":
        wanted = {"unexpired": (0, 0), "frame": (1, 0), "block": (1, 1), "terminal": (1, 1)}[case["transition"]]
        if (calls[0x45C1A0], calls[0x45C220]) != wanted:
            raise ValueError("target did not reach the requested frame/block transition")
        expected = ([2 if case["action"] == 1 else 0 if case["action"] == 3
                     else 0 if case["field"] == 0 else 2]
                    if case["transition"] == "terminal" and case["action"] in (1, 3, 10) else [])
        if actions != expected:
            raise ValueError("target completion did not reach its required action setter")
    if case["cohort"] == "capture" and actions != [9, 2]:
        raise ValueError("target did not preserve its selected action across landing/animation")


def audit(object_path, smoke=False):
    support_paths = [Path(__file__), ROOT / "scripts/reimu_animation_fixture.py",
                     ROOT / "scripts/audit-common-fighter-animation-paths.py"]
    support_hashes = {str(path.relative_to(ROOT)): linked_pe.sha(path) for path in support_paths}
    canonical = linked_pe.comparator()
    target_sha = canonical.verify_target()
    target = canonical.target_bytes(ADDRESS, SIZE)
    if hashlib.sha256(target).hexdigest() != BODY_SHA:
        raise ValueError("Reimu root boundary/hash changed")
    mapper = load_script("reimu_low_coff", "compare-giant-action-switches.py")
    obj = mapper.CoffObject(object_path, symbol_base=SYMBOL)
    rel32 = {symbol.name: address for symbol in obj.symbols.values()
             for name, address in CALL_TARGETS.items() if symbol.name.startswith("?"+name+"@")}
    known = dict(canonical.known_data_targets())
    for bits, address in (("40900000", 0x6C3EA8), ("c0900000", 0x6C3EA4),
                          ("41700000", 0x6C3EA0), ("3f0ccccd", 0x6C3E9C),
                          ("c0800000", 0x6C3E98), ("3f19999a", 0x6C3E94),
                          ("40800000", 0x6CD200), ("3fe0000000000000", 0x6CD138)):
        literal = bytes.fromhex(bits)[::-1]
        if canonical.target_bytes(address, len(literal)) != literal:
            raise ValueError("target numeric binding changed")
        known.setdefault("__real@"+bits, (address, literal, frozenset({0}), "literal"))
    object_sha = linked_pe.sha(object_path)
    candidate = canonical.coff_symbol_bytes(object_path, SYMBOL, ADDRESS, len(obj.text), rel32, known, {})
    if len(candidate) > SIZE or any(ADDRESS < start+length and start < ADDRESS+len(candidate)
                                  for start, (length, _) in HELPERS.items()):
        raise ValueError("candidate staging body overlaps a real helper")
    image = pefile.PE(str(ROOT / "resources/th105.exe")).get_memory_mapped_image()
    if (image[0x2FA898:0x2FBC98] != bytes(0x1400)
            or canonical.target_bytes(0x6FCA98, 0x200) != bytes(0x200)):
        raise ValueError("fixture needs original flat surface and zero event handles")
    probes = [Probe(image, target, False), Probe(image, candidate, True)]
    count = mismatches = 0
    digest, cohorts, examples = hashlib.sha256(), Counter(), []
    for case in cases(smoke):
        expected, actual = (probe.evaluate(case) for probe in probes)
        check_target_case(case, expected)
        count += 1
        cohorts[case["cohort"]] += 1
        digest.update(json.dumps(case, sort_keys=True).encode())
        if expected != actual:
            mismatches += 1
            if len(examples) < 6:
                examples.append({"case": case, "different_actor_offsets": [hex(i) for i, (a, b) in
                                 enumerate(zip(expected["actor"], actual["actor"])) if a != b],
                                 "target_calls": expected["calls"], "candidate_calls": actual["calls"]})
        if count % 1000 == 0:
            print(f"Reimu low actions: {count}, differences {mismatches}", file=sys.stderr)
    if (count != (88 if smoke else 10700) or linked_pe.sha(object_path) != object_sha
            or any(linked_pe.sha(ROOT / path) != digest for path, digest in support_hashes.items())):
        raise ValueError("input matrix incomplete or an input changed during execution")
    return {"schema": "th105-reimu-low-native-v1", "target_sha256": target_sha,
            "body_sha256": BODY_SHA, "object_sha256": object_sha,
            "cases": count, "mismatch_count": mismatches, "cohorts": dict(cohorts),
            "input_sha256": digest.hexdigest(), "examples": examples,
            "visited_root_instructions": [len(probe.visited) for probe in probes],
            "helper_counts": [{HELPERS[address][1]: probe.helper_counts[address]
                              for address in HELPERS} for probe in probes],
            "target_launch_sites": dict(probes[0].launch_sites),
            "helper_sha256": {hex(address): hashlib.sha256(canonical.target_bytes(address, length)).hexdigest()
                              for address, (length, _) in HELPERS.items()},
            "unicorn_version": unicorn.__version__, "python_version": sys.version.split()[0],
            "unicorn_library_sha256": linked_pe.sha(Path(unicorn_api._uc._name)),
            "audit_source_sha256": linked_pe.sha(Path(__file__)), "build_provenance_verified": False,
            "support_sha256": support_hashes,
            "scope": "actions0..10 through real helpers/native RET; supplied read-only animation graph, "
                     "flat original surface and zero texture/event handles; no result hooks, full-gameplay, "
                     "floating-exception, source-completeness or canonical-exact claim"}


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("object", type=Path)
    parser.add_argument("--smoke", action="store_true")
    args = parser.parse_args()
    try:
        result = audit(args.object, args.smoke)
    except (KeyError, OSError, ValueError, unicorn.UcError) as error:
        parser.exit(2, f"Reimu low-action audit failed: {error}\n")
    print(json.dumps(result, indent=2))
    raise SystemExit(1 if result["mismatch_count"] else 0)
