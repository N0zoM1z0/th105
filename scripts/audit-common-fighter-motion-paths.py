#!/usr/bin/env python3
"""Execute scoped common-Fighter motion paths with original native dependencies.

Sampled instruction execution is diagnostic only, never canonical acceptance.
Inputs keep animation frames unexpired and omit the wall-event path in action53;
no helper return or target instruction is replaced with a hook result.
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
import tomllib

import pefile
from giant_owner_audit import decode

ROOT = Path(__file__).resolve().parents[1]
ADDRESS, SIZE = 0x4740C0, 10219
BODY_SHA256 = "7def23cf4826d7511260e7d9ea8db18848c43a7b77939bb42724a29af117a0c6"
RETURN = 0x710000
HELPERS = {0x473DD0: "landing_transition", 0x435DC0: "at_or_below_surface",
           0x435D60: "surface_height", 0x435910: "x_boundary",
           0x4351C0: "advance_frame", 0x68A1A0: "ftol2_sse"}
ACTIONS = (50, 51, 52, 53, 54, 55, 56, 57, 58, 60, 61, 62, 63, 64, 66, 67,
           159, 160, 161, 162, 163, 164, 165, 166, 690)


def load_script(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / "scripts" / filename)
    module = importlib.util.module_from_spec(spec)
    sys.modules[name] = module
    spec.loader.exec_module(module)
    return module


def cases(smoke=False):
    patterns = {0, 0x80000000, 1, 0x80000001, 0x7F7FFFFF, 0xFF7FFFFF,
                0x7F800000, 0xFF800000, 0x7FC00000, 0xFFC00000, 0x7F800001, 0xFF800001}
    for value in (0.6, 1.0, 1.2, 1.5, 2.5, 3.0):
        bits = struct.unpack("<I", struct.pack("<f", value))[0]
        for adjacent in (bits - 1, bits, bits + 1):
            patterns.update((adjacent, adjacent | 0x80000000))
    for action in ACTIONS:
        xs = (640.0,) if smoke or action == 53 else (40.0, 640.0, 1240.0)
        variants = (0, 1) if action == 53 and not smoke else (0,)
        vectors = itertools.product((0, 0xC0400000, 0x40400000) if smoke else sorted(patterns),
                                    xs, (0,) if smoke else (0, 1),
                                    (0x27F,) if smoke else (0x27F, 0x37F), variants)
        for bits, x, peer, control_word, variant in vectors:
            yield dict(action=action, vx_bits=f"{bits:08x}", x=x, peer_enabled=peer,
                       control_word=control_word, word_732=variant)


class MotionProbe:
    OWNER, STACK = 0x2000000, 0x1000000

    def __init__(self, mapped, code, callable_size):
        import unicorn
        from unicorn import x86_const as registers
        self.reg = registers
        self.engine = unicorn.Uc(unicorn.UC_ARCH_X86, unicorn.UC_MODE_32)
        uc = self.engine
        uc.mem_map(0x400000, 0x311000)
        uc.mem_write(0x400000, mapped)
        uc.mem_write(ADDRESS, code)
        for base in (self.OWNER, self.STACK):
            uc.mem_map(base, 0x10000)
        self.initial = uc.context_save()
        self.end = ADDRESS + callable_size
        self.visited = set()
        self.helper_counts = Counter()
        uc.hook_add(unicorn.UC_HOOK_CODE, self.instruction)
        uc.hook_add(unicorn.UC_HOOK_MEM_WRITE, self.write)

    def write(self, uc, access, address, size, value, unused):
        actor = self.OWNER <= address and address + size <= self.OWNER + 0x7A4
        stack = self.STACK <= address and address + size <= self.STACK + 0x10000
        if not actor and not stack:
            self.failure = f"write outside actor/stack at {address:#x}"
            uc.emu_stop()

    def instruction(self, uc, address, size, unused):
        try:
            self.step(uc, address, size)
        except Exception as error:
            self.failure = str(error)
            uc.emu_stop()

    def step(self, uc, address, size):
        r = self.reg
        if ADDRESS <= address < self.end:
            self.visited.add(address)
        raw = bytes(uc.mem_read(address, size))
        if raw[0] == 0xE8:
            if size != 5:
                raise ValueError("unreviewed direct-call encoding")
            destination = address + 5 + int.from_bytes(raw[1:5], "little", signed=True)
            if destination not in HELPERS:
                raise ValueError(f"unreviewed dependency {destination:#x}")
            receiver = None if destination == 0x68A1A0 else uc.reg_read(r.UC_X86_REG_ECX) - self.OWNER
            if receiver not in (None, 0):
                raise ValueError("native helper receiver differs from the actor")
            self.calls.append((destination, receiver))
        elif raw[0] == 0xFF and ((raw[1] >> 3) & 7) in (2, 3):
            raise ValueError("animation/event indirect call is outside the motion fixture")
        if address in HELPERS:
            self.helper_counts[address] += 1
        if address == 0x68A1A0:
            top = (uc.reg_read(r.UC_X86_REG_FPSW) >> 11) & 7
            value = uc.reg_read(r.UC_X86_REG_FP0 + top)
            if not isinstance(value, tuple) or len(value) != 2:
                raise ValueError("emulator does not expose the x87 conversion input")
            self.calls.append(("ftol2", value))
        if raw[0] == 0xC3:
            esp = uc.reg_read(r.UC_X86_REG_ESP)
            if struct.unpack("<I", uc.mem_read(esp, 4))[0] == RETURN:
                self.saw_ret = True

    def evaluate(self, case):
        if case["action"] not in ACTIONS or case["control_word"] not in (0x27F, 0x37F):
            raise ValueError("case is outside the reviewed motion/CW domain")
        uc, r = self.engine, self.reg
        uc.context_restore(self.initial)
        uc.mem_write(self.OWNER, bytes(0x1000))
        uc.mem_write(self.STACK + 0xC000, bytes(0x4000))
        fields = ((0, "<I", 0x6C3F94), (0xEC, "<f", case["x"]), (0xF0, "<f", 0.0),
                  (0xF4, "<I", int(case["vx_bits"], 16)), (0x13C, "<h", case["action"]),
                  (0x142, "<h", 0), (0x144, "<i", 7), (0x14C, "<h", 32767),
                  (0x490, "<B", case["peer_enabled"]), (0x6AC, "<f", 7.0),
                  (0x730, "<h", 100), (0x732, "<h", case["word_732"]))
        for offset, fmt, value in fields:
            uc.mem_write(self.OWNER + offset, struct.pack(fmt, value))
        uc.mem_write(self.STACK + 0xFF00, struct.pack("<I", RETURN))
        uc.reg_write(r.UC_X86_REG_ESP, self.STACK + 0xFF00)
        uc.reg_write(r.UC_X86_REG_ECX, self.OWNER)
        uc.reg_write(r.UC_X86_REG_FPCW, case["control_word"])
        self.failure, self.calls, self.saw_ret = None, [], False
        try:
            uc.emu_start(ADDRESS, RETURN, count=100000)
        except Exception as error:
            raise ValueError(f"{case} at {uc.reg_read(r.UC_X86_REG_EIP):#x}: {error}") from error
        if self.failure:
            raise ValueError(f"{case}: {self.failure}")
        delta = uc.reg_read(r.UC_X86_REG_ESP) - (self.STACK + 0xFF00)
        if not self.saw_ret or uc.reg_read(r.UC_X86_REG_EIP) != RETURN or delta != 4:
            raise ValueError("motion path failed its native RET/stack check")
        if (uc.reg_read(r.UC_X86_REG_FPSW) >> 11) & 7:
            raise ValueError("motion path leaves live x87 values")
        return {"actor": bytes(uc.mem_read(self.OWNER, 0x7A4)).hex(), "calls": self.calls,
                "stack_delta": delta, "x87_control_word": uc.reg_read(r.UC_X86_REG_FPCW)}


def audit(object_path, smoke=False, selected_cases=None):
    import unicorn
    from unicorn import unicorn as unicorn_api
    canonical = load_script("common_motion_canonical", "compare-function.py")
    target_sha = canonical.verify_target()
    target = canonical.target_bytes(ADDRESS, SIZE)
    if hashlib.sha256(target).hexdigest() != BODY_SHA256:
        raise ValueError("common Fighter callable boundary/hash changed")
    mapper = load_script("common_motion_mapper", "compare-giant-action-switches.py")
    manifest = tomllib.loads((ROOT / "config/giant-action-switches.toml").read_text())
    root = mapper.load_target_mapper().select_root(manifest, "fighter-common-action")
    unit = tomllib.loads((ROOT / "config/match-units.toml").read_text())["units"]["gpt-web-fighter-common-action-state"]
    function, = unit["functions"]
    obj = mapper.CoffObject(object_path)
    object_sha = hashlib.sha256(object_path.read_bytes()).hexdigest()
    symbols = [symbol for symbol in obj.symbols.values() if symbol.name == function["symbol_base"]]
    if len(symbols) != 1 or symbols[0].value != 0 or symbols[0].section_number != obj.text_section_number:
        raise ValueError("common Fighter root must start the selected COFF section")
    candidate_map = mapper.build_candidate_map(obj, root)
    rel32 = canonical.known_targets()
    rel32.update({a: int(b, 0) for a, b in (s.split("=", 1) for s in function["rel32_targets"])})
    dir32 = dict(s.split("=", 1) for s in function["dir32_targets"])
    candidate = canonical.coff_symbol_bytes(object_path, function["symbol_base"], ADDRESS,
                                             len(obj.text), rel32, canonical.known_data_targets(), dir32)
    mapped = pefile.PE(str(ROOT / "resources/th105.exe")).get_memory_mapped_image()
    surface = canonical.known_data_targets()["?g_stage_surface_heights@th105@@3PAMA"][0] - 0x400000
    if mapped[surface:surface + 0x1400] != bytes(0x1400):
        raise ValueError("motion fixture requires the original zero-initialized stage surface")
    probes = (MotionProbe(mapped, target, SIZE), MotionProbe(mapped, candidate, candidate_map["metadata_start"]))
    count = differences = 0
    examples, digest = [], hashlib.sha256()
    for case in cases(smoke) if selected_cases is None else selected_cases:
        digest.update(json.dumps(case, sort_keys=True).encode())
        expected, actual = (probe.evaluate(case) for probe in probes)
        count += 1
        if expected != actual:
            differences += 1
            if len(examples) < 10:
                examples.append({"case": case, "target": expected, "candidate": actual})
        if count % 1000 == 0:
            print(f"Common Fighter motion paths: {count}, differences {differences}", file=sys.stderr)
    if not count or (selected_cases is None and count != (75 if smoke else 14208)):
        raise ValueError("motion input generator did not complete its controls")
    if object_sha != hashlib.sha256(object_path.read_bytes()).hexdigest():
        raise ValueError("object changed during native execution")
    library = Path(unicorn_api._uc._name)
    return {"schema": "th105-common-fighter-native-motion-v1", "evidence": "sampled native execution; no exact credit",
            "build_provenance_verified": False, "target_sha256": target_sha, "body_sha256": BODY_SHA256,
            "object_sha256": object_sha, "unicorn_version": unicorn.__version__,
            "unicorn_library_sha256": hashlib.sha256(library.read_bytes()).hexdigest(),
            "python_version": sys.version.split()[0], "cases": count, "mismatch_count": differences,
            "input_source": "explicit cases" if selected_cases is not None else "smoke" if smoke else "motion matrix",
            "input_sha256": digest.hexdigest(), "examples": examples,
            "helper_calls_target_candidate": [{HELPERS[a]: p.helper_counts[a] for a in HELPERS} for p in probes],
            "target_root_instruction_count": len(decode(target, ADDRESS)),
            "visited_root_instructions_target_candidate": [len(p.visited) for p in probes],
            "scope": "25 motion actions through native RET; actor7A4, helper calls and conversion inputs, stack and control word; flat stage/y0, unexpired frame, action53 interior only, PC53/64 masked exceptions; no animation/event context or helper-result hooks; complete gameplay/numerical/exception equivalence unproved"}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("object", type=Path)
    parser.add_argument("--smoke", action="store_true", help="75 finite interior controls")
    args = parser.parse_args()
    try:
        result = audit(args.object, args.smoke)
    except Exception as error:
        parser.exit(2, f"Common Fighter native execution failed: {error}\n")
    print(json.dumps(result, indent=2))
    return int(bool(result["mismatch_count"]))


if __name__ == "__main__":
    raise SystemExit(main())
