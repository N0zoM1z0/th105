#!/usr/bin/env python3
"""Compare action869's real parameter-add prefix, stopping at first sine entry."""
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
    "orbit_lifetimes", ROOT / "scripts/audit-reimu-object-804-lifetimes.py"
)
lifetimes = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(lifetimes)
native = lifetimes.native
SINE = 0x406360


def parameter_window(rows):
    matches = []
    for index, row in enumerate(rows):
        following = rows[index + 1:index + 5]
        if (row.mnemonic == "fstp" and row.op_str == "dword ptr [esi + 0x37c]"
                and len(following) == 4 and following[0].mnemonic == "mov"
                and following[0].op_str == "eax, dword ptr [esi + 0x340]"
                and following[1].mnemonic == "fld"
                and following[2].mnemonic == "fadd"
                and following[3].mnemonic == "fstp"
                and following[3].op_str == "dword ptr [eax]"):
            matches.append(rows[index:index + 6])
    if len(matches) != 1:
        raise ValueError("869 parameter-add window is not unique")
    return matches[0]


def source_packet(path, symbol):
    code, _, metadata = lifetimes.source_packet(path, symbol)
    rows = native.facts.decode(code[:metadata], native.S)
    jump = next(row for row in rows[:40] if row.mnemonic == "jmp"
                and row.operands[0].type == lifetimes.x.X86_OP_MEM)
    primary = lifetimes.world.reviewed_source_switches(rows, code, metadata)[jump.address]
    index = code[primary["index_table"] - native.S + 69]
    start = primary["destinations"][index]
    end = min(pc for pc in primary["destinations"] if pc > start)
    window = parameter_window([row for row in rows if start <= row.address < end])
    return code, window


class PrefixProbe(native.Probe):
    def configure(self, window):
        addition = window[3]
        self.before_add = addition.address
        self.after_add = addition.address + addition.size

    def instruction(self, engine, pc, size, unused):
        if pc == self.start:
            engine.mem_write(native.OWNER + 0x37C,
                             struct.pack("<I", self.case["angular_bits"]))
            parameter = (native.entry.PARAMETERS if self.case["alias"] == "external"
                         else native.OWNER + 0x370)
            engine.mem_write(native.OWNER + 0x340, struct.pack("<I", parameter))
            engine.mem_write(parameter, struct.pack("<I", self.case["parameter_bits"]))
        if pc in (self.before_add, self.after_add):
            stage = "before_add" if pc == self.before_add else "after_add"
            self.snapshots.append(dict(stage=stage, **lifetimes.logical_float_state(engine)))
        if pc == SINE:
            sp = engine.reg_read(native.r.UC_X86_REG_ESP)
            self.endpoint = dict(kind="first_sine_entry",
                                 argument=bytes(engine.mem_read(sp + 4, 4)).hex())
            self.snapshots.append(dict(stage="sine_entry",
                                       **lifetimes.logical_float_state(engine)))
            engine.emu_stop()
            return
        super().instruction(engine, pc, size, unused)

    def write(self, engine, access, address, size, value, unused):
        for region, base, extent in (("owner", native.OWNER, 0x388),
                                     ("parameters", native.entry.PARAMETERS, 16)):
            if base <= address < address + size <= base + extent:
                self.writes.append([region, address - base, size,
                                    value & ((1 << (size * 8)) - 1)])
                break
        super().write(engine, access, address, size, value, unused)

    def evaluate(self, case):
        self.case, self.snapshots, self.writes = case, [], []
        result = super().evaluate(case)
        if (result["endpoint"]["kind"] != "first_sine_entry"
                or [row["stage"] for row in self.snapshots]
                != ["before_add", "after_add", "sine_entry"]):
            raise ValueError("fixture did not cross the actual addition once")
        return dict(output=result, writes=self.writes, snapshots=self.snapshots,
                    final_status=self.uc.reg_read(native.r.UC_X86_REG_FPSW))


def cases():
    parameters = (0, 0x80000000, 0x3F800000, 0xBF800000, 1, 0x80000001,
                  0x7FC00011, 0xFFC00021, 0x7F800001, 0xFF800001,
                  0x7F800000, 0xFF800000)
    angular = (0, 0x80000000, 0x3EFFFFFF, 0x3F000000, 0x3F000001,
               0xC167FFFF, 0xC1680000, 0xC1680001, 1, 0x80000001,
               0x7FC00011, 0xFFC00021, 0x7F800001, 0xFF800001,
               0x7F800000, 0xFF800000)
    words = [precision + rounding for precision in (0x27F, 0x37F)
             for rounding in (0, 0x400, 0x800, 0xC00)]
    for parameter, velocity, word, alias in itertools.product(
            parameters, angular, words, ("external", "amplitude")):
        yield dict(action=869, seq=0, phase=0, owner_action=669, owner_seq=1,
                   counter=1, timer=0, state=1, amplitude=0.5,
                   parameter_bits=parameter, angular_bits=velocity, cw=word, alias=alias)


def audit(obj, symbol, contrast=None, contrast_symbol=None):
    native.facts.audit()
    destinations = struct.unpack("<42I", native.c.target_bytes(0x4A197C, 42 * 4))
    index = native.c.target_bytes(0x4A1A24 + 69, 1)[0]
    start = destinations[index]
    end = min(pc for pc in destinations if pc > start)
    target_window = parameter_window(native.facts.decode(
        native.c.target_bytes(start, end - start), start))
    paths = [obj, Path(__file__), ROOT / "resources/th105.exe",
             ROOT / "src/characters/ReimuObjectActionStateStaging.cpp",
             ROOT / "src/characters/ReimuObjectActionStateStaging.hpp",
             *[ROOT / "config" / name for name in (
                 "target.toml", "function-byte-ownership.toml", "match-units.toml",
                 "giant-action-switches.toml", "known-symbols.csv", "known-globals.csv",
                 "reccmp-relocations.csv")],
             *[ROOT / "scripts" / name for name in (
                 "audit-reimu-object-804-lifetimes.py",
                 "audit-reimu-object-scalar-actions.py", "audit-reimu-object-world-sharing.py",
                 "audit-reimu-object-selector-families.py", "audit-reimu-object-update-target.py",
                 "audit-reimu-object-entry-calls.py", "audit-common-fighter-animation-paths.py",
                 "audit-common-fighter-motion-paths.py", "compare-function.py",
                 "compare-giant-action-switches.py", "match_literals.py",
                 "workflow_manifest.py", "requirements-ci.txt")]]
    if contrast:
        paths.append(contrast)
    pins = lambda: {str(path): hashlib.sha256(path.read_bytes()).hexdigest() for path in paths}
    before = pins()
    image = lifetimes.pefile.PE(str(ROOT / "resources/th105.exe")).get_memory_mapped_image()
    target = PrefixProbe(image)
    target.configure(target_window)
    probes, packets = [target], []
    for label, path, name in [("source", obj, symbol)] + (
            [("contrast", contrast, contrast_symbol)] if contrast else []):
        code, window = source_packet(path, name)
        probe = PrefixProbe(image, code)
        probe.configure(window)
        probes.append(probe)
        packets.append(dict(label=label, object=str(path), symbol=name, source_bytes=len(code),
                            runtime_sha256=hashlib.sha256(code).hexdigest(),
                            window_byte_equal=(b"".join(row.bytes for row in window)
                                               == b"".join(row.bytes for row in target_window)),
                            window=[dict(address=row.address, bytes=row.bytes.hex(),
                                         text=row.mnemonic + " " + row.op_str) for row in window]))
    differences = {packet["label"]: Counter() for packet in packets}
    examples = {label: [] for label in differences}
    counts, inputs = Counter(), hashlib.sha256()
    for case in cases():
        inputs.update(json.dumps(case, sort_keys=True).encode())
        answers = [probe.evaluate(case) for probe in probes]
        counts[case["alias"]] += 1
        counts["cases"] += 1
        for packet, answer in zip(packets, answers[1:]):
            label = packet["label"]
            changed = [key for key in answers[0] if answers[0][key] != answer[key]]
            differences[label].update(changed)
            if changed and len(examples[label]) < 2:
                examples[label].append(dict(case=case, fields=changed,
                                            target_snapshots=answers[0]["snapshots"],
                                            source_snapshots=answer["snapshots"]))
    if counts["cases"] != 3072 or before != pins():
        raise ValueError("incomplete matrix or changed audit inputs")
    return dict(schema="th105-reimu-object-869-prefix-v1",
                result="equal_scoped_869_prefix" if not differences["source"] else "mismatch",
                target_sha256=native.c.verify_target(), counts=dict(counts),
                differences={label: dict(value) for label, value in differences.items()},
                examples=examples, packets=packets, input_sha256=inputs.hexdigest(), input_pins=before,
                engine_versions=dict(unicorn=native.unicorn.__version__,
                                     capstone=lifetimes.capstone.__version__,
                                     pefile=lifetimes.pefile.__version__),
                build_provenance_verified=False,
                target_window=[dict(address=row.address, bytes=row.bytes.hex(),
                                    text=row.mnemonic + " " + row.op_str) for row in target_window],
                scope="869 sequence0/owner669 x86 emulation prefix only, stopping before first real "
                      "sine entry executes; two explicit parameter aliases, masked exceptions, "
                      "PC53/64 and four rounding modes; no returning lookup, full RET ABI, "
                      "arbitrary aliases, original nominal types or whole-root exactness claim")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("object", type=Path)
    parser.add_argument("--symbol", default=native.SYMBOL)
    parser.add_argument("--contrast-object", type=Path)
    parser.add_argument("--contrast-symbol", default="?dispatch_action_state@ReimuObject@@UAEXXZ")
    args = parser.parse_args()
    report = audit(args.object, args.symbol, args.contrast_object, args.contrast_symbol)
    print(json.dumps(report, indent=2))
    raise SystemExit(0 if report["result"] == "equal_scoped_869_prefix" else 1)
