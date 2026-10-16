#!/usr/bin/env python3
"""Compare common-Fighter sequence paths using original native animation code.

The fixture supplies a checked action tree, linked sequence blocks and valid
untextured frames. No helper result, vtable entry or instruction is replaced.
Sampled execution is diagnostic only, never canonical matching evidence.
"""
from __future__ import annotations

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

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location(
    "common_animation_motion", ROOT / "scripts/audit-common-fighter-motion-paths.py")
motion = importlib.util.module_from_spec(spec)
spec.loader.exec_module(motion)

RESOURCE = 0x3000000
TREE, HEAD, NODE = RESOURCE, RESOURCE + 0x100, RESOURCE + 0x200
VECTOR, SLOT = RESOURCE + 0x300, RESOURCE + 0x400
BLOCK, FRAME = RESOURCE + 0x1000, RESOURCE + 0x2000
VTABLE = 0x6C3F94
ACTIONS = (73, 75, 88)
TRANSITIONS = ("unexpired", "frame", "block")
# Exact-target callable extents; the target hash also attests their contents.
HELPERS = {
    0x4351C0: (62, "advance_frame"), 0x435910: (59, "x_boundary"),
    0x435D60: (89, "surface_height"), 0x68A1A0: (171, "ftol2_sse"),
    0x5F9310: (64, "crossed_surface"), 0x45C1A0: (67, "next_frame"),
    0x45C220: (138, "next_block"), 0x45C180: (20, "set_frame"),
    0x45C110: (111, "apply_frame"), 0x45C390: (202, "select_sequence"),
    0x45C320: (105, "tree_lookup"), 0x436760: (335, "apply_sprite_frame"),
    0x40C100: (95, "texture_vector_at"), 0x407160: (193, "set_texture"),
    0x407230: (261, "texture_rectangle"), 0x4073A0: (24, "reset_transform"),
    0x4073C0: (24, "commit_transform"),
}
VIRTUAL_SLOTS = {0x0C: 0x45C390, 0x14: 0x45C220,
                 0x1C: 0x45C180, 0x20: 0x45C1A0}


def cases(smoke=False):
    bits = ("00000000", "80000000", "00000001", "80000001", "c0400000", "40400000",
            "7f800000", "ff800000", "7fc00000", "ffc00000", "7f800001", "ff800001")
    for action in ACTIONS:
        xs = (640.0,) if smoke or action == 75 else (40.0, 640.0, 1240.0)
        for x, vx, vy, transition, cw in itertools.product(
                xs, ("00000000", "80000000", "c0400000", "7fc00000") if smoke else bits,
                ("00000000", "40400000") if smoke else bits, TRANSITIONS,
                (0x27F,) if smoke else (0x27F, 0x37F)):
            yield dict(action=action, x=x, vx_bits=vx, vy_bits=vy,
                       transition=transition, control_word=cw)


class AnimationProbe(motion.MotionProbe):
    def __init__(self, *args):
        import unicorn
        from capstone import Cs, CS_ARCH_X86, CS_MODE_32
        super().__init__(*args)
        self.engine.mem_map(RESOURCE, 0x10000, unicorn.UC_PROT_READ)
        self.decoder = Cs(CS_ARCH_X86, CS_MODE_32)
        self.decoder.detail = True
        self.sequence_choices = Counter()

    def indirect_destination(self, raw, address):
        from capstone.x86 import X86_OP_MEM, X86_OP_REG
        ins = next(self.decoder.disasm(raw, address))
        operand = ins.operands[0]

        def register(number):
            return self.engine.reg_read(getattr(
                self.reg, "UC_X86_REG_" + ins.reg_name(number).upper())) if number else 0

        if operand.type == X86_OP_REG:
            return register(operand.reg)
        if operand.type != X86_OP_MEM or operand.mem.segment:
            raise ValueError("unreviewed indirect-transfer operand")
        pointer = (register(operand.mem.base) + register(operand.mem.index)
                   * operand.mem.scale + operand.mem.disp)
        return struct.unpack("<I", self.engine.mem_read(pointer, 4))[0]

    def step(self, uc, address, size):
        r = self.reg
        if motion.ADDRESS <= address < self.end:
            self.visited.add(address)
        elif not any(start <= address < start + length for start, (length, _) in HELPERS.items()):
            raise ValueError(f"unreviewed executed dependency {address:#x}")
        raw = bytes(uc.mem_read(address, size))
        if raw[0] == 0xE8:
            if size != 5:
                raise ValueError("unreviewed direct-call encoding")
            destination = address + 5 + int.from_bytes(raw[1:], "little", signed=True)
            if destination not in HELPERS:
                raise ValueError(f"unreviewed call {destination:#x}")
        elif raw[0] == 0xFF and (raw[1] >> 3) & 7 in (2, 3, 4, 5):
            destination = self.indirect_destination(raw, address)
            if (raw[1] >> 3) & 7 in (2, 3) or not motion.ADDRESS <= destination < self.end:
                if destination not in VIRTUAL_SLOTS.values():
                    raise ValueError(f"unreviewed virtual transfer {destination:#x}")
                if (uc.reg_read(r.UC_X86_REG_ECX) != self.OWNER
                        or struct.unpack("<I", uc.mem_read(self.OWNER, 4))[0] != VTABLE):
                    raise ValueError("native virtual receiver/vptr differs from the fixture")
        if address in HELPERS:
            self.helper_counts[address] += 1
            receiver = uc.reg_read(r.UC_X86_REG_ECX)
            expected = (VECTOR if address == 0x40C100 else TREE if address == 0x45C320
                        else self.OWNER + 4 if address in (0x407160, 0x4073A0, 0x4073C0)
                        else None if address in (0x68A1A0, 0x407230) else self.OWNER)
            if expected is not None and receiver != expected:
                raise ValueError(f"helper {address:#x} has an unreviewed receiver {receiver:#x}")
            argument = None
            if address in (0x45C390, 0x45C180, 0x407160):
                esp = uc.reg_read(r.UC_X86_REG_ESP)
                argument = struct.unpack("<I", uc.mem_read(esp + 4, 4))[0]
                if address == 0x407160 and argument != 0:
                    raise ValueError("textured frames require unavailable graphics context")
            self.calls.append((address, expected, argument))
            if address == 0x45C390:
                self.sequence_choices[argument] += 1
        if address == 0x68A1A0:
            top = (uc.reg_read(r.UC_X86_REG_FPSW) >> 11) & 7
            value = uc.reg_read(r.UC_X86_REG_FP0 + top)
            if not isinstance(value, tuple) or len(value) != 2:
                raise ValueError("emulator does not expose the x87 conversion input")
            self.calls.append(("ftol2", value))
        if raw[0] in (0xC3, 0xC2):
            esp = uc.reg_read(r.UC_X86_REG_ESP)
            if struct.unpack("<I", uc.mem_read(esp, 4))[0] == motion.RETURN:
                self.saw_ret = True

    def evaluate(self, case):
        if (case["action"] not in ACTIONS or case["transition"] not in TRANSITIONS
                or case["control_word"] not in (0x27F, 0x37F)
                or case["x"] not in (40.0, 640.0, 1240.0)):
            raise ValueError("case is outside the reviewed animation domain")
        uc, r = self.engine, self.reg
        uc.context_restore(self.initial)
        uc.mem_write(self.OWNER, bytes(0x1000))
        uc.mem_write(self.STACK + 0xC000, bytes(0x4000))
        image = bytearray(0x10000)

        def put(address, fmt, *values):
            struct.pack_into(fmt, image, address - RESOURCE, *values)

        put(TREE + 4, "<I", HEAD)
        put(HEAD, "<III", NODE, NODE, NODE)
        put(HEAD + 0x15, "<B", 1)
        put(NODE, "<IIIiI", HEAD, HEAD, HEAD, case["action"], BLOCK)
        put(VECTOR + 4, "<III", SLOT, SLOT + 4, SLOT + 4)
        frame_count = 2 if case["transition"] == "frame" else 1
        for index in range(4):
            block, frame = BLOCK + index * 0x20, FRAME + index * 0x200
            put(block + 4, "<II", frame, frame + frame_count * 0x88)
            put(block + 0x14, "<B", 0 if index == 0 else 1)
            put(block + 0x18, "<II", block - 0x20 if index else 0,
                block + 0x20 if index < 3 else 0)
            for frame_index in range(frame_count):
                put(frame + frame_index * 0x88 + 8, "<hhhhhhb",
                    3, 0, index + 1, index + 2, 16 + frame_index, 24, -1)
        # The target reads this graph but cannot write it; inherited guards
        # admit writes only to the actor and stack.
        uc.mem_write(RESOURCE, bytes(image))
        fields = ((0, "<I", VTABLE), (0xEC, "<f", case["x"]), (0xF0, "<f", 100.0),
                  (0xF4, "<I", int(case["vx_bits"], 16)), (0xF8, "<I", int(case["vy_bits"], 16)),
                  (0x130, "<I", VECTOR), (0x13C, "<h", case["action"]),
                  (0x142, "<h", 0 if case["transition"] == "unexpired" else 2),
                  (0x144, "<i", 7), (0x148, "<h", frame_count), (0x14C, "<h", 3),
                  (0x150, "<I", FRAME), (0x158, "<I", FRAME), (0x15C, "<I", BLOCK),
                  (0x160, "<I", TREE), (0x730, "<h", 100))
        for offset, fmt, value in fields:
            uc.mem_write(self.OWNER + offset, struct.pack(fmt, value))
        uc.mem_write(self.STACK + 0xFF00, struct.pack("<I", motion.RETURN))
        uc.reg_write(r.UC_X86_REG_ESP, self.STACK + 0xFF00)
        uc.reg_write(r.UC_X86_REG_ECX, self.OWNER)
        uc.reg_write(r.UC_X86_REG_FPCW, case["control_word"])
        saved = {"EBX": 0xB0B01111, "ESI": 0x51512222,
                 "EDI": 0xD1D13333, "EBP": 0xBEBE4444}
        for register, value in saved.items():
            uc.reg_write(getattr(r, "UC_X86_REG_" + register), value)
        self.failure, self.calls, self.saw_ret = None, [], False
        try:
            uc.emu_start(motion.ADDRESS, motion.RETURN, count=100000)
        except Exception as error:
            raise ValueError(f"{case} at {uc.reg_read(r.UC_X86_REG_EIP):#x}: {error}") from error
        if self.failure:
            raise ValueError(f"{case}: {self.failure}")
        delta = uc.reg_read(r.UC_X86_REG_ESP) - (self.STACK + 0xFF00)
        if not self.saw_ret or uc.reg_read(r.UC_X86_REG_EIP) != motion.RETURN or delta != 4:
            raise ValueError("animation path failed its native RET/stack check")
        if (uc.reg_read(r.UC_X86_REG_FPSW) >> 11) & 7:
            raise ValueError("animation path leaves live x87 values")
        restored = {name: uc.reg_read(getattr(r, "UC_X86_REG_" + name)) for name in saved}
        if restored != saved:
            raise ValueError("animation path corrupts a callee-saved register")
        return {"actor": bytes(uc.mem_read(self.OWNER, 0x7A4)).hex(), "calls": self.calls,
                "stack_delta": delta, "control_word": uc.reg_read(r.UC_X86_REG_FPCW),
                "callee_saved": restored}


def check_target_transition(case, result):
    """Require each fixture label to reach the intended original native path."""
    counts = Counter(call[0] for call in result["calls"])
    expected = {"unexpired": (0, 0, 0), "frame": (1, 0, 1),
                "block": (1, 1, None)}[case["transition"]]
    actual = tuple(counts[address] for address in (0x45C1A0, 0x45C220, 0x45C110))
    if any(wanted is not None and wanted != observed for wanted, observed in zip(expected, actual)):
        raise ValueError(f"target did not reach the requested animation transition: {case}")


def audit(object_path, smoke=False, selected_cases=None):
    import unicorn
    from unicorn import unicorn as unicorn_api
    canonical = motion.load_script("common_animation_canonical", "compare-function.py")
    target_sha = canonical.verify_target()
    target = canonical.target_bytes(motion.ADDRESS, motion.SIZE)
    if hashlib.sha256(target).hexdigest() != motion.BODY_SHA256:
        raise ValueError("common Fighter callable boundary/hash changed")
    mapper = motion.load_script("common_animation_mapper", "compare-giant-action-switches.py")
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
    rel32.update({name: int(value, 0) for name, value in (
        item.split("=", 1) for item in function.get("rel32_targets", []))})
    candidate = canonical.coff_symbol_bytes(
        object_path, function["symbol_base"], motion.ADDRESS, len(obj.text), rel32,
        canonical.known_data_targets(), dict(item.split("=", 1) for item in function.get("dir32_targets", [])))
    mapped = pefile.PE(ROOT / "resources/th105.exe").get_memory_mapped_image()
    surface = canonical.known_data_targets()["?g_stage_surface_heights@th105@@3PAMA"][0] - 0x400000
    if mapped[surface:surface + 0x1400] != bytes(0x1400):
        raise ValueError("animation fixture requires the original flat stage")
    for slot, destination in VIRTUAL_SLOTS.items():
        if struct.unpack_from("<I", mapped, VTABLE - 0x400000 + slot)[0] != destination:
            raise ValueError("original CharacterEx animation vtable differs")
    probes = (AnimationProbe(mapped, target, motion.SIZE),
              AnimationProbe(mapped, candidate, candidate_map["metadata_start"]))
    count = differences = 0
    examples, digest, controls = [], hashlib.sha256(), Counter()
    for case in cases(smoke) if selected_cases is None else selected_cases:
        digest.update(json.dumps(case, sort_keys=True).encode())
        controls[(case["action"], case["transition"])] += 1
        expected, actual = (probe.evaluate(case) for probe in probes)
        check_target_transition(case, expected)
        count += 1
        if expected != actual:
            differences += 1
            if len(examples) < 10:
                examples.append({"case": case, "target": expected, "candidate": actual})
        if count % 500 == 0:
            print(f"Common Fighter animation paths: {count}, differences {differences}", file=sys.stderr)
    if not count or (selected_cases is None and count != (72 if smoke else 6048)):
        raise ValueError("animation input generator did not complete its controls")
    if selected_cases is None:
        if set(controls) != set(itertools.product(ACTIONS, TRANSITIONS)):
            raise ValueError("animation matrix omits an action/transition")
        if any(set(probe.sequence_choices) != {2, 3} for probe in probes):
            raise ValueError("animation matrix did not execute both native sequence selections")
    if object_sha != hashlib.sha256(object_path.read_bytes()).hexdigest():
        raise ValueError("object changed during native execution")
    library = Path(unicorn_api._uc._name)
    return {"schema": "th105-common-fighter-native-animation-v1", "evidence": "sampled native execution; no exact credit",
            "build_provenance_verified": False, "target_sha256": target_sha,
            "body_sha256": motion.BODY_SHA256, "object_sha256": object_sha,
            "unicorn_version": unicorn.__version__, "python_version": sys.version.split()[0],
            "unicorn_library_sha256": hashlib.sha256(library.read_bytes()).hexdigest(),
            "cases": count, "mismatch_count": differences, "examples": examples,
            "input_sha256": digest.hexdigest(),
            "input_source": "explicit cases" if selected_cases is not None else "smoke" if smoke else "animation matrix",
            "action_transition_cases": {f"{action}:{transition}": n for (action, transition), n in sorted(controls.items())},
            "helper_calls_target_candidate": [{name: probe.helper_counts[address]
                for address, (_, name) in HELPERS.items()} for probe in probes],
            "sequence_choices_target_candidate": [dict(probe.sequence_choices) for probe in probes],
            "target_root_instruction_count": len(motion.decode(target, motion.ADDRESS)),
            "visited_root_instructions_target_candidate": [len(probe.visited) for probe in probes],
            "scope": "actions73/75/88 with original virtuals/tree/frame/sprite code through native RET; actor7A4, native helper/argument/conversion trace, stack, callee-saved registers and CW; flat stage/y100, checked one-action tree, four linked blocks, untextured frames; PC53/64 masked exceptions; no event/graphics backend or complete gameplay/numerical/exception equivalence"}


def main():
    import argparse
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("object", type=Path)
    parser.add_argument("--smoke", action="store_true", help="72 transition/zero/NaN controls")
    args = parser.parse_args()
    try:
        result = audit(args.object, args.smoke)
    except Exception as error:
        parser.exit(2, f"Common Fighter animation execution failed: {error}\n")
    print(json.dumps(result, indent=2))
    return int(bool(result["mismatch_count"]))


if __name__ == "__main__":
    raise SystemExit(main())
