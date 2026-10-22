#!/usr/bin/env python3
"""Execute action800 through its real effect gate, stopping at orientation entry."""
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
    "action800_lifetimes", ROOT / "scripts/audit-reimu-object-804-lifetimes.py"
)
lifetimes = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(lifetimes)
native = lifetimes.native
ORIENTATION = 0x435160


def parameter_window(rows):
    call = next(index for index, row in enumerate(rows)
                if row.mnemonic == "call" and row.operands[0].type == lifetimes.x.X86_OP_IMM
                and row.operands[0].imm == ORIENTATION)
    stores = [index for index, row in enumerate(rows[:call])
              if row.mnemonic == "fstp" and row.op_str == "dword ptr [esi + 0x12c]"]
    if not stores:
        raise ValueError("missing800 heading store before orientation")
    window = rows[stores[-1] + 1:call]
    if (not window or window[0].mnemonic != "movsx"
            or window[0].op_str != "ecx, word ptr [esi + 0x364]"
            or sum(row.mnemonic == "fmul" for row in window) != 1
            or sum(row.mnemonic in ("fadd", "faddp") for row in window) != 1
            or any(row.mnemonic not in ("movsx", "mov", "lea", "fld", "fild", "fmul",
                                        "fadd", "faddp", "fstp") for row in window)):
        raise ValueError("unreviewed800 parameter window")
    return window


class PrefixProbe(native.Probe):
    def configure(self, window):
        product = next(row for row in window if row.mnemonic == "fmul")
        addition = next(row for row in window if row.mnemonic in ("fadd", "faddp"))
        self.stages = {product.address: "before_product", addition.address: "before_add",
                       addition.address + addition.size: "after_add"}

    def instruction(self, engine, pc, size, unused):
        if pc == self.start:
            engine.mem_write(native.entry.PARAMETERS,
                             struct.pack("<fI", 37.25, self.case["parameter_bits"]))
        if pc in self.stages:
            self.snapshots.append(dict(stage=self.stages[pc],
                                       **lifetimes.logical_float_state(engine)))
        if pc == ORIENTATION:
            sp = engine.reg_read(native.r.UC_X86_REG_ESP)
            self.endpoint = dict(kind="first_orientation_entry",
                                 receiver=engine.reg_read(native.r.UC_X86_REG_ECX),
                                 arguments=bytes(engine.mem_read(sp + 4, 8)).hex())
            self.snapshots.append(dict(stage="orientation_entry",
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
        if (result["endpoint"]["kind"] != "first_orientation_entry"
                or result["endpoint"]["receiver"] != native.OWNER + 4
                or result["trace"] != [0x5575C0]
                or [row["stage"] for row in self.snapshots] != [
                    "before_product", "before_add", "after_add", "orientation_entry"]
                or bytes(self.uc.mem_read(native.OWNER + 0x364, 2))
                != struct.pack("<H", (case["state"] + 1) & 0xFFFF)):
            raise ValueError("fixture did not execute the reviewed800 prefix")
        return dict(output=result, writes=self.writes, snapshots=self.snapshots,
                    final_status=self.uc.reg_read(native.r.UC_X86_REG_FPSW))


def cases():
    parameters = (0, 0x80000000, 0x3F000000, 0xBF000000, 0x3F7FFFFF, 0x3F800000,
                  0x3F800001, 0x4B7FFFFF, 0x4B800000, 0xCB800000, 0x7F7FFFFF,
                  0xFF7FFFFF, 1, 0x80000001, 0x7F800000, 0xFF800000,
                  0x7FC00011, 0xFFC00021, 0x7F800001, 0xFF800001)
    states = (-32768, -256, -1, 0, 1, 2, 3, 15, 59, 60, 127, 255, 256, 32767)
    words = [precision + rounding for precision in (0x27F, 0x37F)
             for rounding in (0, 0x400, 0x800, 0xC00)]
    for parameter, state, word in itertools.product(parameters, states, words):
        yield dict(action=800, seq=0, phase=0, counter=1, timer=1, frame=0,
                   owner_action=150, state=state, parameter_bits=parameter, cw=word)


def audit(obj, symbol, contrast=None, contrast_symbol=None):
    native.facts.audit()
    lo, hi = native.facts.RANGES[0]
    target_window = parameter_window(native.facts.decode(native.c.target_bytes(lo, hi - lo), lo))
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
    target = PrefixProbe(image)
    target.configure(target_window)
    probes, packets = [target], []
    for label, path, name in [("source", obj, symbol)] + (
            [("contrast", contrast, contrast_symbol)] if contrast else []):
        code, _, metadata = lifetimes.source_packet(path, name)
        window = parameter_window(native.facts.decode(code[:metadata], native.S))
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
        raise ValueError("incomplete matrix or changed800 inputs")
    return dict(schema="th105-reimu-object-800-prefix-v1", cases=count,
                result="equal_scoped_800_prefix" if not differences["source"] else "mismatch",
                target_sha256=native.c.verify_target(), input_pins=before, input_sha256=inputs.hexdigest(),
                differences={label: dict(value) for label, value in differences.items()},
                examples=examples, packets=packets, build_provenance_verified=False,
                engine_versions=dict(unicorn=native.unicorn.__version__,
                                     capstone=lifetimes.capstone.__version__,
                                     pefile=lifetimes.pefile.__version__),
                target_window=[dict(address=row.address, bytes=row.bytes.hex(),
                                    text=row.mnemonic + " " + row.op_str) for row in target_window],
                scope="800 sequence0, phase0, timer/counter1, owner action150; execute the original "
                      "5575C0 gate and stop at first real435160 entry; external parameters, empty "
                      "incoming x87, masked PC53/64 with four rounding modes; no orientation return, "
                      "spawn/RET ABI, original member grouping or canonical acceptance claim")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("object", type=Path)
    parser.add_argument("--symbol", default=native.SYMBOL)
    parser.add_argument("--contrast-object", type=Path)
    parser.add_argument("--contrast-symbol", default=native.SYMBOL)
    args = parser.parse_args()
    report = audit(args.object, args.symbol, args.contrast_object, args.contrast_symbol)
    print(json.dumps(report, indent=2))
    raise SystemExit(0 if report["result"] == "equal_scoped_800_prefix" else 1)
