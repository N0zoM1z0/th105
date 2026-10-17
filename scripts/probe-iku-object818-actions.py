#!/usr/bin/env python3
"""Compare staged Iku 565--568 C++ with native target action paths.

Original root prelude and dependency code run on both sides. Emission/effect/
action/sequence paths stop before their backend entry; other paths reach RET.
No helper result or executable instruction is supplied by a hook. This is a
semantic diagnostic, not a canonical comparison or a real linked image.
"""
import argparse
from collections import Counter
import csv
import hashlib
import importlib.util
import itertools
import json
import os
from pathlib import Path
import struct
import subprocess
import sys

import pefile
import unicorn
from unicorn import x86_const as r

from giant_owner_audit import decode
import linked_pe

ROOT = Path(__file__).resolve().parents[1]
SOURCE = ROOT / "src/characters/IkuObject818Actions.cpp"
HEADER = ROOT / "src/characters/AnimationSequenceVirtuals.hpp"
OWNER, PEER, WAVES, STACK, RETURN = 0x2000000, 0x2002000, 0x2004000, 0x1000000, 0xF000000
ENTRY_SP = STACK + 0xFF00
ENTRIES = {565: 0x6296BE, 566: 0x629E96, 567: 0x62A668, 568: 0x62AEF6}
BOUNDARIES = {0x465190: 7, 0x435240: 5, 0x45BFE0: 1, 0x45C390: 1}
HELPERS = {0x473DD0: 0, 0x435D60: 0, 0x435DC0: 0, 0x5F9310: 0,
           0x45AF40: 0, 0x4351C0: 0, 0x46BF30: 2, 0x478DF0: 1,
           0x45C030: 1, 0x401D50: 1, 0x68A1A0: 0}
# Same-target source-view aliases for native execution, not original C++ names
# or global comparator bindings. Their physical interfaces are already exact.
METHODS = {"spawn_owned_object_via_manager": 0x465190,
           "emit_fighter_effect_433cc0": 0x435240,
           "dispatch_character_wave_handle": 0x45C030,
           "add_phase_scaled_counter_558": 0x478DF0,
           "adjust_counter_482": 0x46BF30, "zero_velocity_acceleration": 0x45AF40,
           "has_crossed_stage_surface_while_descending": 0x5F9310,
           "advance_frame_and_dispatch": 0x4351C0,
           "resolve_stage_surface_landing_transition": 0x473DD0,
           "stage_surface_height_at_x": 0x435D60}


def build_source(source, output):
    if not output.resolve().is_relative_to(ROOT / "build"):
        raise ValueError("generated source objects must stay below build/")
    tool, pins = linked_pe.pinned_tools()
    output.parent.mkdir(parents=True, exist_ok=True)
    env = os.environ.copy()
    env.update(WINEPREFIX=str(ROOT / ".tools/wine-msvc8"), WINEARCH="win32", WINEDEBUG="-all")
    for name in ("CL", "_CL_", "LINK", "_LINK_", "INCLUDE", "LIB", "LIBPATH"):
        env[name] = ""
    win = lambda path: "Z:" + str(path.resolve()).replace("/", "\\")
    command = ["wine", str(tool / "bin/cl.exe"), "/nologo", "/c", "/O2", "/GS-", "/GR", "/EHsc", "/MT",
               *["/I" + win(p) for p in (ROOT / "src", ROOT / "src/characters", tool / "include", tool / "PlatformSDK/Include")],
               "/Fo" + win(output), win(source)]
    with output.with_suffix(".compile.log").open("w") as log:
        subprocess.run(command, cwd=ROOT, env=env, stdout=log, stderr=subprocess.STDOUT, check=True)
    receipt = {"command": command, "source": str(source), "source_sha256": linked_pe.sha(source),
               "header_sha256": linked_pe.sha(HEADER), "object_sha256": linked_pe.sha(output), "tools": pins}
    output.with_suffix(".build.json").write_text(json.dumps(receipt, indent=2) + "\n")
    return receipt


def control_source(name):
    source = SOURCE.read_text()
    if name == "unsigned-tick":
        needle = "short_at(0x732) % 6"
        if source.count(needle) != 1:
            raise ValueError("unsigned-tick control no longer has one source predicate")
        source = source.replace(needle, "static_cast<unsigned short>(short_at(0x732)) % 6")
    elif name == "publication-order":
        if source.count("if (second_variant)") != 1 or source.count("if (!second_variant)") != 1:
            raise ValueError("publication control no longer has the two source stores")
        source = source.replace("if (second_variant)", "if (control_variant)")
        source = source.replace("if (!second_variant)", "if (second_variant)")
        source = source.replace("if (control_variant)", "if (!second_variant)")
    else:
        raise ValueError("unknown diagnostic source control")
    path = ROOT / "build" / ("iku-object818-" + name + ".cpp")
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_bytes(source.replace("\n", "\r\n").encode())
    return path


def load_object(path, *, root_prefix="?try_dispatch_verified_object818_action@", methods=None, data_keys=()):
    methods = METHODS if methods is None else methods
    canonical = linked_pe.comparator()
    known_data = canonical.known_data_targets()
    spec = importlib.util.spec_from_file_location("iku818_coff", ROOT / "scripts/compare-giant-action-switches.py")
    module = importlib.util.module_from_spec(spec)
    sys.modules[spec.name] = module
    spec.loader.exec_module(module)
    obj = module.CoffObject(path)
    sections = {}
    for number, section in enumerate(obj.sections, 1):
        if section.name in (".text", ".rdata"):
            if section.raw_size > 0x10000:
                raise ValueError("unexpected large source section")
            sections[number] = (0x800000 + number * 0x10000, section,
                                bytearray(obj._read_raw(section.raw_offset, section.raw_size)))
    aliases = {}
    for base, section, data in sections.values():
        for index in range(section.reloc_count):
            field, symbol_index, kind = struct.unpack_from("<IIH", obj.data, section.reloc_offset + index * 10)
            if field + 4 > len(data):
                raise ValueError("source relocation outside section")
            symbol = obj.symbols[symbol_index]
            if symbol.section_number in sections:
                destination = sections[symbol.section_number][0] + symbol.value
            elif symbol.section_number == 0 and kind == 0x14:
                method = symbol.name.split("@", 1)[0].lstrip("?")
                if method not in methods:
                    raise ValueError("unreviewed source dependency: " + symbol.name)
                destination = methods[method]
                aliases[symbol.name] = destination
            elif symbol.section_number == 0 and kind == 6 and symbol.name in data_keys:
                destination, literal, _, _ = known_data[symbol.name]
                if (struct.unpack_from("<I", data, field)[0] != 0
                        or canonical.target_bytes(destination, len(literal)) != literal
                        or pefile.PE(str(ROOT / "resources/th105.exe")).get_section_by_rva(
                            destination - 0x400000).Characteristics & 0x20000000):
                    raise ValueError("external data binding is not attested non-executable data")
                aliases[symbol.name] = destination
            else:
                raise ValueError("unreviewed source section/symbol: " + symbol.name)
            addend = struct.unpack_from("<i", data, field)[0]
            if kind == 0x14:
                value = destination + addend - (base + field + 4)
            elif kind == 6:
                value = destination + addend
            else:
                raise ValueError("unreviewed source relocation type")
            struct.pack_into("<I", data, field, value & 0xFFFFFFFF)
    roots = [s for s in obj.symbols.values() if s.name.startswith(root_prefix)]
    if len(roots) != 1:
        raise ValueError("staged source entry is not unique")
    entry = sections[roots[0].section_number][0] + roots[0].value
    return entry, list(sections.values()), aliases


def input_cases(smoke):
    basic = dict(sequence=0, timer=0, time=7, frame=0, gate=1, tick=0, index=0,
                 facing=1, x=640.0, y=0.0, vy=3.0, acceleration=0.6,
                 field_6c0=1, field_6c4=1, flag=1, cw=0x27F, phase=0,
                 counter=1000, floor=0, state_4b8=0)
    result = []
    def add(action, **changes):
        result.append(dict(basic, action=action, **changes))
    for action in ENTRIES:
        for sequence, index, facing in itertools.product((0, 1), range(4), (-1, 1)):
            add(action, sequence=sequence, index=index, facing=facing)
        for sequence, gate, tick, index in itertools.product(
                (0, 1, 2, 3), (0, 1, 2), (-6, -1, 5, 6) if not smoke else (-6, 5),
                (-1, 0, 3, 4) if not smoke else (-1, 4)):
            add(action, sequence=sequence, gate=gate, tick=tick, index=index)
        for sequence, frame, timer in itertools.product((0, 1, 2), (0, 2, 5, 6, 10), (-1, 0)):
            add(action, sequence=sequence, frame=frame, timer=timer, gate=0,
                time=-1 if frame == 0 else 7)
        for first, second, flag in itertools.product((0, 1), repeat=3):
            add(action, field_6c0=first, field_6c4=second, flag=flag, frame=5, timer=-1, gate=0)
        if not smoke:
            for sequence, tick, index, cw in itertools.product(
                    (0, 1), (-32768, -12, -6, -1, 0, 5, 6, 32767),
                    (-32768, -1, 0, 1, 2, 3, 4, 32767), (0x27F, 0x37F)):
                add(action, sequence=sequence, tick=tick, index=index, cw=cw)
            for sequence, index, x, facing, cw in itertools.product(
                    (0, 1), range(4), (0.0, 0.1, 1279.0), (-1, 1), (0x27F, 0x37F)):
                add(action, sequence=sequence, index=index, x=x, facing=facing, cw=cw)
            for sequence, counter, state, phase in itertools.product(
                    (0, 1), (-32768, 0, 199, 200, 32767), (0, 5), (0, 3, 4)):
                add(action, sequence=sequence, frame=6 if sequence == 0 else 2,
                    timer=-1, gate=0, counter=counter, state_4b8=state, phase=phase)
        if action in (567, 568):
            for sequence, y, vy in itertools.product((0, 1, 2, 3), (0.0, 10.0), (-1.0, 0.0, 1.0)):
                add(action, sequence=sequence, y=y, vy=vy, gate=0)
    # Preserve deterministic order while avoiding repeated matrix intersections.
    return list({json.dumps(case, sort_keys=True): case for case in result}.values())


class Probe:
    def __init__(self, canonical, candidate, *, entries=None, helpers=None, boundaries=None,
                 no_receiver=(), extra_writes=()):
        self.canonical, self.candidate = canonical, candidate
        self.entries = ENTRIES if entries is None else entries
        self.helpers = HELPERS if helpers is None else helpers
        self.boundaries = BOUNDARIES if boundaries is None else boundaries
        self.no_receiver = {0x68A1A0, 0x401D50, *no_receiver}
        self.extra_writes = extra_writes
        self.engine = unicorn.Uc(unicorn.UC_ARCH_X86, unicorn.UC_MODE_32)
        uc = self.engine
        uc.mem_map(0x400000, 0x311000)
        uc.mem_write(0x400000, pefile.PE(str(ROOT / "resources/th105.exe")).get_memory_mapped_image())
        for base in (OWNER, STACK, RETURN):
            uc.mem_map(base, 0x10000)
        self.entry, self.sections, self.aliases = candidate
        for base, section, data in self.sections:
            uc.mem_map(base, 0x10000)
            uc.mem_write(base, bytes(data))
        ledger = {int(row["address"], 0): int(row["size"])
                  for row in csv.DictReader((ROOT / "config/functions.csv").open())}
        self.target_boundaries = {i.address for start in (0x620920, *self.helpers)
                                  for i in decode(canonical.target_bytes(start, ledger[start]), start)}
        self.initial = uc.context_save()
        self.visited, self.outcomes = set(), Counter()
        uc.hook_add(unicorn.UC_HOOK_CODE, self.instruction)
        uc.hook_add(unicorn.UC_HOOK_MEM_WRITE, self.write)

    def write(self, uc, access, address, size, value, unused):
        if not (OWNER <= address and address + size <= OWNER + 0x7B8
                or STACK <= address and address + size <= STACK + 0x10000
                or any(first <= address and address + size <= last for first, last in self.extra_writes)):
            self.failure = f"write outside actor/stack at {address:#x}"
            uc.emu_stop()

    def instruction(self, uc, address, size, unused):
        try:
            if self.prelude and address == self.entries[self.case["action"]]:
                self.prelude = False
                uc.emu_stop()
                return
            esp = uc.reg_read(r.UC_X86_REG_ESP)
            if address in self.boundaries or address in self.helpers:
                count = (self.boundaries | self.helpers)[address]
                args = list(struct.unpack("<" + "I" * count, uc.mem_read(esp + 4, count * 4)))
                call = {"entry": address, "arguments": args, "field_180": self.u32(OWNER + 0x180)}
                receiver = uc.reg_read(r.UC_X86_REG_ECX)
                if address not in self.no_receiver and receiver != OWNER:
                    raise ValueError("helper receiver differs")
                if address == 0x401D50 and (receiver != 0x702288 or args != [0]):
                    raise ValueError("audio path requires the real zero wave handle")
                if address == 0x465190:
                    pointer = args[5]
                    if args[6] == 0 and pointer == 0:
                        call["payload"] = None
                    elif args[6] != 3 or not STACK <= pointer <= STACK + 0x10000 - 12:
                        raise ValueError("spawn payload outside source stack")
                    else:
                        call["payload"] = bytes(uc.mem_read(pointer, 12)).hex()
                        args[5] = "stack_payload"
                if address == 0x68A1A0:
                    top = (uc.reg_read(r.UC_X86_REG_FPSW) >> 11) & 7
                    call["input_st0"] = uc.reg_read(r.UC_X86_REG_FP0 + top)
                self.calls.append(call)
                if address in self.boundaries:
                    self.outcome = hex(address)
                    uc.emu_stop()
                    return
            candidate_code = any(base <= address < base + len(data) and section.name == ".text"
                                 for base, section, data in self.sections)
            if address not in self.target_boundaries and not candidate_code:
                raise ValueError(f"unreviewed execution at {address:#x}")
            if 0x620920 <= address < 0x62EFBE:
                self.visited.add(address)
            raw = bytes(uc.mem_read(address, size))
            if raw[0] == 0xC3 and self.u32(esp) == RETURN:
                self.outcome = "ret"
        except Exception as error:
            self.failure = str(error)
            uc.emu_stop()

    def u32(self, address):
        return struct.unpack("<I", self.engine.mem_read(address, 4))[0]

    def actor_fields(self, case):
        return ((0, "I", 0x6C652C), (0xEC, "f", case["x"]), (0xF0, "f", case["y"]),
                  (0xF8, "f", case["vy"]), (0x100, "f", case["acceleration"]), (0x104, "b", case["facing"]),
                  (0x13C, "h", case["action"]), (0x13E, "h", case["sequence"]), (0x140, "h", case["frame"]),
                  (0x142, "h", case["timer"]), (0x144, "i", case["time"]), (0x14C, "h", 32767),
                  (0x164, "I", WAVES), (0x170, "I", PEER), (0x174, "h", 1000), (0x180, "i", 6),
                  (0x482, "h", case["counter"]), (0x486, "h", case["floor"]), (0x4B8, "h", case["state_4b8"]),
                  (0x4D0, "f", 1.0), (0x558, "h", 100), (0x55A, "b", case["phase"]),
                  (0x6C0, "i", case["field_6c0"]), (0x6C4, "i", case["field_6c4"]),
                  (0x730, "h", case["gate"]), (0x732, "h", case["tick"]), (0x734, "h", case["index"]),
                  (0x750, "B", case["flag"]))

    def prepare_case(self, case):
        pass

    def evaluate(self, case, source):
        uc = self.engine
        uc.context_restore(self.initial)
        uc.mem_write(OWNER, bytes(0x10000))
        uc.mem_write(STACK, bytes(0x10000))
        for offset, kind, value in self.actor_fields(case):
            uc.mem_write(OWNER + offset, struct.pack("<" + kind, value))
        self.prepare_case(case)
        uc.mem_write(ENTRY_SP, struct.pack("<I", RETURN))
        uc.reg_write(r.UC_X86_REG_ESP, ENTRY_SP)
        uc.reg_write(r.UC_X86_REG_ECX, OWNER)
        uc.reg_write(r.UC_X86_REG_FPCW, case["cw"])
        self.case, self.failure, self.prelude, self.outcome, self.calls = case, None, True, None, []
        preserved = (r.UC_X86_REG_EBX, r.UC_X86_REG_ESI, r.UC_X86_REG_EDI, r.UC_X86_REG_EBP)
        expected_preserved = [uc.reg_read(reg) for reg in preserved]
        uc.emu_start(0x620920, RETURN, count=100000)
        if self.failure or self.prelude or uc.reg_read(r.UC_X86_REG_EIP) != self.entries[case["action"]]:
            raise ValueError("original root prelude did not reach the selected action: " + str(self.failure))
        entry = self.entries[case["action"]]
        if source:
            entry = self.entry
            uc.reg_write(r.UC_X86_REG_ESP, ENTRY_SP)
            uc.reg_write(r.UC_X86_REG_ECX, OWNER)
            expected_preserved = [uc.reg_read(reg) for reg in preserved]
        uc.emu_start(entry, RETURN, count=100000)
        if self.failure or self.outcome is None:
            raise ValueError(f"{case} at {uc.reg_read(r.UC_X86_REG_EIP):#x}: {self.failure or 'no outcome'}")
        if self.outcome == "ret" and (uc.reg_read(r.UC_X86_REG_EIP) != RETURN
                                      or uc.reg_read(r.UC_X86_REG_ESP) != ENTRY_SP + 4):
            raise ValueError("native RET/stack contract differs")
        if self.outcome == "ret" and [uc.reg_read(reg) for reg in preserved] != expected_preserved:
            raise ValueError("native RET changes callee-saved registers")
        if ((uc.reg_read(r.UC_X86_REG_FPSW) >> 11) & 7 or uc.reg_read(r.UC_X86_REG_FPCW) != case["cw"]):
            raise ValueError("live x87 stack or changed control word at observed boundary")
        self.outcomes[("source" if source else "target", self.outcome)] += 1
        return {"outcome": self.outcome, "actor": bytes(uc.mem_read(OWNER, 0x7B8)).hex(), "calls": self.calls}


def audit(source=SOURCE, output=None, smoke=False):
    canonical = linked_pe.comparator()
    target_sha = canonical.verify_target()
    body = canonical.target_bytes(0x620920, 59038)
    if hashlib.sha256(body).hexdigest() != "abc831c6ccd95986bed811694f532ad8c8b92cb49702a7f6ce4de100b8a73dea":
        raise ValueError("Iku root bytes differ")
    output = output or ROOT / "build/IkuObject818Actions.obj"
    receipt = build_source(source, output)
    probe = Probe(canonical, load_object(output))
    cases = input_cases(smoke)
    count = 0
    differences, examples = 0, []
    inputs, outputs = hashlib.sha256(), hashlib.sha256()
    for case in cases:
        inputs.update(json.dumps(case, sort_keys=True).encode())
        expected, actual = probe.evaluate(case, False), probe.evaluate(case, True)
        outputs.update(json.dumps(expected, sort_keys=True).encode())
        count += 1
        if expected != actual:
            differences += 1
            if len(examples) < 2:
                examples.append({"case": case, "target": expected, "source": actual})
    if (linked_pe.sha(output) != receipt["object_sha256"] or linked_pe.sha(source) != receipt["source_sha256"]
            or linked_pe.sha(HEADER) != receipt["header_sha256"]):
        raise ValueError("source/header/object changed during native probe")
    return {"schema": "th105-iku-object818-source-native-v1", "target_sha256": target_sha,
            "build": receipt, "cases": count, "mismatch_count": differences, "examples": examples,
            "unicorn_version": unicorn.__version__, "python_version": sys.version.split()[0],
            "probe_script_sha256": linked_pe.sha(Path(__file__)),
            "input_sha256": inputs.hexdigest(), "target_output_sha256": outputs.hexdigest(),
            "outcomes": [{"side": side, "stop": stop, "cases": value}
                         for (side, stop), value in sorted(probe.outcomes.items())],
            "source_view_aliases": probe.aliases, "target_root_instructions_visited": len(probe.visited),
            "scope": "four complete staged action bodies; original prelude and native dependencies; "
                     "unexpired animation, flat stage, zero wave handle, PC53/64 nearest masked; "
                     "RET or first spawn/effect/action/sequence backend entry, no helper-result hooks; "
                     "second spawn and post-backend effects not executed; no whole-root source/exact claim"}


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--source", type=Path, default=SOURCE)
    parser.add_argument("--output", type=Path)
    parser.add_argument("--smoke", action="store_true")
    parser.add_argument("--control", choices=("unsigned-tick", "publication-order"),
                        help="compile an intentionally changed source to calibrate the native diagnostic")
    args = parser.parse_args()
    source = control_source(args.control) if args.control else args.source.resolve()
    output = args.output.resolve() if args.output else (ROOT / "build" / ("IkuObject818-" + args.control + ".obj")
                                                       if args.control else None)
    report = audit(source, output, args.smoke)
    report["diagnostic_control"] = args.control
    print(json.dumps(report, indent=2))
    raise SystemExit(bool(report["mismatch_count"]))
