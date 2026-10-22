#!/usr/bin/env python3
"""Compare the isolated908 angle-add window under explicit entry preconditions.

This starts after the wave call and stops before the counter update. It does
not execute or synthesize spawn/wave returns, or establish a root RET ABI.
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

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location(
    "angle_lifetimes", ROOT / "scripts/audit-reimu-object-804-lifetimes.py"
)
lifetimes = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(lifetimes)
native = lifetimes.native


def angle_window(rows):
    matches = []
    for index, row in enumerate(rows):
        if (row.mnemonic != "call" or row.operands[0].type != lifetimes.x.X86_OP_IMM
                or row.operands[0].imm != 0x45C030):
            continue
        following = rows[index + 1:index + 12]
        if not any(item.mnemonic == "movsx"
                   and item.op_str.endswith("word ptr [esi + 0x366]") for item in following):
            continue
        stores = [offset for offset, item in enumerate(following)
                  if item.mnemonic == "fstp" and item.op_str == "dword ptr [esi + 0x374]"]
        if not stores:
            continue
        window = following[:stores[0] + 1]
        if (any(item.mnemonic not in ("fld", "movsx", "mov", "fild", "fadd", "faddp", "fstp")
                for item in window)
                or sum(item.mnemonic in ("fadd", "faddp") for item in window) != 1):
            raise ValueError("unreviewed908 arithmetic window")
        matches.append(window)
    if len(matches) != 1:
        raise ValueError("908 post-wave angle window is not unique")
    return matches[0]


class WindowProbe:
    def __init__(self, image, window, candidate=None):
        self.window = window
        self.uc = native.unicorn.Uc(native.unicorn.UC_ARCH_X86, native.unicorn.UC_MODE_32)
        readonly_code = native.unicorn.UC_PROT_READ | native.unicorn.UC_PROT_EXEC
        self.uc.mem_map(0x400000, 0x311000, readonly_code)
        self.uc.mem_write(0x400000, image)
        if candidate is not None:
            self.uc.mem_map(native.S, (len(candidate) + 0xFFF) & ~0xFFF, readonly_code)
            self.uc.mem_write(native.S, candidate)
        self.uc.mem_map(native.OWNER, 0x1000)
        self.uc.mem_map(native.STACK, 0x1000)
        self.sp = native.STACK + 0x800
        addition = next(row for row in window if row.mnemonic in ("fadd", "faddp"))
        self.before_add, self.after_add = addition.address, addition.address + addition.size
        self.pcs = {row.address for row in window}
        self.uc.hook_add(native.unicorn.UC_HOOK_CODE, self.instruction)
        self.uc.hook_add(native.unicorn.UC_HOOK_MEM_WRITE, self.write)
        self.initial = self.uc.context_save()

    def instruction(self, engine, pc, size, unused):
        if pc not in self.pcs:
            raise ValueError("execution escaped the arithmetic window")
        self.visited.append(pc)
        if pc in (self.before_add, self.after_add):
            self.snapshots.append(dict(stage="before_add" if pc == self.before_add else "after_add",
                                       **lifetimes.logical_float_state(engine)))

    def write(self, engine, access, address, size, value, unused):
        if (address, size) == (native.OWNER + 0x374, 4):
            region, offset = "owner", 0x374
        elif (address, size) == (self.sp + 0x20, 4):
            region, offset = "stack", 0x20
        else:
            raise ValueError(f"unreviewed window write {address:#x}/{size}")
        self.writes.append([region, offset, size, value & 0xFFFFFFFF])

    def evaluate(self, case):
        engine = self.uc
        engine.context_restore(self.initial)
        engine.mem_write(native.OWNER, bytes([0xA5]) * 0x388)
        engine.mem_write(native.STACK, bytes(0x1000))
        engine.mem_write(native.OWNER + 0x374, struct.pack("<I", case["angle_bits"]))
        engine.mem_write(native.OWNER + 0x366, struct.pack("<h", case["counter"]))
        fixtures = ((native.r.UC_X86_REG_EAX, 0x11111111),
                    (native.r.UC_X86_REG_EBX, 0x22222222),
                    (native.r.UC_X86_REG_ESI, native.OWNER),
                    (native.r.UC_X86_REG_EDI, 0x33333333),
                    (native.r.UC_X86_REG_EBP, 0x44444444),
                    (native.r.UC_X86_REG_ESP, self.sp),
                    (native.r.UC_X86_REG_EFLAGS, 0x202),
                    (native.r.UC_X86_REG_FPCW, case["cw"]),
                    (native.r.UC_X86_REG_FPSW, 0), (native.r.UC_X86_REG_FPTAG, 0xFFFF))
        for register, value in fixtures:
            engine.reg_write(register, value)
        self.snapshots, self.writes, self.visited = [], [], []
        end = self.window[-1].address + self.window[-1].size
        engine.emu_start(self.window[0].address, end, count=32)
        if (self.visited != [row.address for row in self.window]
                or engine.reg_read(native.r.UC_X86_REG_EIP) != end
                or engine.reg_read(native.r.UC_X86_REG_ESP) != self.sp
                or engine.reg_read(native.r.UC_X86_REG_FPCW) != case["cw"]
                or engine.reg_read(native.r.UC_X86_REG_FPTAG) != 0xFFFF
                or engine.reg_read(native.r.UC_X86_REG_FPSW) & 0x3800
                or bytes(engine.mem_read(native.OWNER + 0x366, 2)) != struct.pack("<h", case["counter"])):
            raise ValueError("arithmetic window endpoint/state differs from its preconditions")
        return dict(angle=bytes(engine.mem_read(native.OWNER + 0x374, 4)).hex(),
                    writes=self.writes, snapshots=self.snapshots,
                    final_status=engine.reg_read(native.r.UC_X86_REG_FPSW))


def cases():
    angles = (0, 0x80000000, 0x3F000000, 0xBF000000, 0x3F7FFFFF, 0x3F800000, 0x3F800001,
              0x4B7FFFFF, 0x4B800000, 0xCB800000, 0x7F7FFFFF, 0xFF7FFFFF, 1, 0x80000001,
              0x7F800000, 0xFF800000, 0x7FC00011, 0xFFC00021, 0x7F800001, 0xFF800001)
    counters = (-32768, -256, -1, 0, 1, 2, 3, 15, 59, 60, 127, 255, 256, 32767)
    words = [precision + rounding for precision in (0x27F, 0x37F)
             for rounding in (0, 0x400, 0x800, 0xC00)]
    for angle, counter, word in itertools.product(angles, counters, words):
        yield dict(angle_bits=angle, counter=counter, cw=word)


def audit(obj, symbol, contrast=None, contrast_symbol=None):
    native.facts.audit()
    target_rows = [row for lo, hi in native.facts.RANGES
                   for row in native.facts.decode(native.c.target_bytes(lo, hi - lo), lo)]
    target_window = angle_window(target_rows)
    paths = [obj, Path(__file__), ROOT / "resources/th105.exe",
             ROOT / "src/characters/ReimuObjectActionStateStaging.cpp",
             ROOT / "src/characters/ReimuObjectActionStateStaging.hpp",
             *[ROOT / "config" / name for name in (
                 "target.toml", "function-byte-ownership.toml", "match-units.toml",
                 "giant-action-switches.toml", "known-symbols.csv", "known-globals.csv",
                 "reccmp-relocations.csv")],
             *[ROOT / "scripts" / name for name in (
                 "audit-reimu-object-804-lifetimes.py", "audit-reimu-object-scalar-actions.py",
                 "audit-reimu-object-world-sharing.py", "audit-reimu-object-selector-families.py",
                 "audit-reimu-object-update-target.py", "audit-reimu-object-entry-calls.py",
                 "audit-common-fighter-animation-paths.py", "audit-common-fighter-motion-paths.py",
                 "compare-function.py", "compare-giant-action-switches.py",
                 "match_literals.py", "workflow_manifest.py", "requirements-ci.txt")]]
    if contrast:
        paths.append(contrast)
    pins = lambda: {str(path): hashlib.sha256(path.read_bytes()).hexdigest() for path in paths}
    before = pins()
    image = lifetimes.pefile.PE(str(ROOT / "resources/th105.exe")).get_memory_mapped_image()
    probes, packets = [WindowProbe(image, target_window)], []
    for label, path, name in [("source", obj, symbol)] + (
            [("contrast", contrast, contrast_symbol)] if contrast else []):
        code, _, metadata = lifetimes.source_packet(path, name)
        window = angle_window(native.facts.decode(code[:metadata], native.S))
        probes.append(WindowProbe(image, window, code))
        packets.append(dict(label=label, object=str(path), symbol=name, source_bytes=len(code),
                            runtime_sha256=hashlib.sha256(code).hexdigest(),
                            window_byte_equal=(b"".join(row.bytes for row in window)
                                               == b"".join(row.bytes for row in target_window)),
                            window=[dict(address=row.address, bytes=row.bytes.hex(),
                                         text=row.mnemonic + " " + row.op_str) for row in window]))
    differences = {packet["label"]: Counter() for packet in packets}
    examples = {label: [] for label in differences}
    count, inputs = 0, hashlib.sha256()
    for case in cases():
        inputs.update(json.dumps(case, sort_keys=True).encode())
        answers = [probe.evaluate(case) for probe in probes]
        count += 1
        for packet, answer in zip(packets, answers[1:]):
            label = packet["label"]
            changed = [key for key in answers[0] if answers[0][key] != answer[key]]
            differences[label].update(changed)
            if changed and len(examples[label]) < 2:
                examples[label].append(dict(case=case, fields=changed,
                                            target_snapshots=answers[0]["snapshots"],
                                            source_snapshots=answer["snapshots"]))
    if count != 2240 or before != pins():
        raise ValueError("incomplete matrix or changed window inputs")
    return dict(schema="th105-reimu-object-908-window-v1", cases=count,
                result="equal_scoped_908_window" if not differences["source"] else "mismatch",
                target_sha256=native.c.verify_target(), input_pins=before, input_sha256=inputs.hexdigest(),
                differences={label: dict(value) for label, value in differences.items()},
                examples=examples, packets=packets, build_provenance_verified=False,
                engine_versions=dict(unicorn=native.unicorn.__version__,
                                     capstone=lifetimes.capstone.__version__,
                                     pefile=lifetimes.pefile.__version__),
                target_window=[dict(address=row.address, bytes=row.bytes.hex(),
                                    text=row.mnemonic + " " + row.op_str) for row in target_window],
                preconditions="isolated arithmetic entry: ESI=owner; writable stack at ESP+20; "
                              "empty x87; masked exceptions, PC53/64 and four rounding modes",
                scope="starts after wave CALL and stops before counter update; no spawn/wave "
                      "execution, fabricated return, full-root/RET ABI, arbitrary incoming x87, "
                      "unmasked exceptions, original nominal declaration or canonical acceptance claim")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("object", type=Path)
    parser.add_argument("--symbol", default=native.SYMBOL)
    parser.add_argument("--contrast-object", type=Path)
    parser.add_argument("--contrast-symbol", default=native.SYMBOL)
    args = parser.parse_args()
    report = audit(args.object, args.symbol, args.contrast_object, args.contrast_symbol)
    print(json.dumps(report, indent=2))
    raise SystemExit(0 if report["result"] == "equal_scoped_908_window" else 1)
