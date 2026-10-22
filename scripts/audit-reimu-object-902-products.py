#!/usr/bin/env python3
"""Execute action902's five directional products and inspect real x87 values."""
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
    "direction_lifetimes", ROOT / "scripts/audit-reimu-object-804-lifetimes.py"
)
lifetimes = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(lifetimes)
native = lifetimes.native
ATAN2 = 0x406540


def multiplication_windows(rows):
    windows = []
    for index, row in enumerate(rows):
        if (row.mnemonic != "movsx"
                or not row.op_str.endswith("byte ptr [esi + 0x104]")):
            continue
        part = rows[max(0, index - 1):index + 8]
        conversions = [offset for offset, item in enumerate(part) if item.mnemonic == "fild"]
        if len(conversions) != 1:
            continue
        if not any(item.mnemonic in ("fld", "fmul")
                   and item.op_str == "dword ptr [esi + 0xf4]" for item in part):
            continue
        end = conversions[0] + 2
        if part[end - 1].mnemonic not in ("fmul", "fmulp"):
            raise ValueError("unreviewed directional multiplication")
        windows.append(part[:end])
    return windows


def source_packet(path, symbol):
    code, _, metadata = lifetimes.source_packet(path, symbol)
    rows = native.facts.decode(code[:metadata], native.S)
    jump = next(row for row in rows[:40] if row.mnemonic == "jmp"
                and row.operands[0].type == lifetimes.x.X86_OP_MEM)
    primary = lifetimes.world.reviewed_source_switches(rows, code, metadata)[jump.address]
    index = code[primary["index_table"] - native.S + 102]
    start = primary["destinations"][index]
    end = min(pc for pc in primary["destinations"] if pc > start)
    windows = multiplication_windows([row for row in rows if start <= row.address < end])
    if len(windows) != 6:
        raise ValueError("unreviewed902 source product inventory")
    # Five steering products precede the unchanged common movement product.
    return code, windows[:5]


class ProductProbe(native.Probe):
    def configure(self, windows):
        self.stages = {}
        for index, window in enumerate(windows):
            product = window[-1]
            self.stages[product.address] = "multiply_" + str(index)
            self.stages[product.address + product.size] = "after_" + str(index)

    def instruction(self, engine, pc, size, unused):
        if pc == self.start:
            engine.mem_write(native.OWNER + 0xF4, struct.pack("<I", self.case["vx_bits"]))
        if pc in self.stages:
            self.snapshots.append(dict(stage=self.stages[pc],
                                       **lifetimes.logical_float_state(engine)))
        if pc == self.atan_return_pc:
            self.atan_returned += 1
            self.atan_return_pc = None
        if pc == ATAN2:
            sp = engine.reg_read(native.r.UC_X86_REG_ESP)
            arguments = list(struct.unpack("<II", engine.mem_read(sp + 4, 8)))
            self.arguments.append(arguments)
            self.atan_return_pc = struct.unpack("<I", engine.mem_read(sp, 4))[0]
            if self.case["cohort"] == "prefix":
                self.endpoint = dict(kind="atan2_entry", arguments=arguments)
                engine.emu_stop()
                return
        super().instruction(engine, pc, size, unused)

    def write(self, engine, access, address, size, value, unused):
        if native.OWNER <= address < address + size <= native.OWNER + 0x388:
            self.writes.append([address - native.OWNER, size,
                                value & ((1 << (size * 8)) - 1)])
        super().write(engine, access, address, size, value, unused)

    def evaluate(self, case):
        self.case, self.snapshots, self.writes, self.arguments = case, [], [], []
        self.atan_return_pc, self.atan_returned = None, 0
        result = super().evaluate(case)
        if (sum(row["stage"] == "multiply_0" for row in self.snapshots) != 1
                or len(self.arguments) != 1
                or self.atan_returned != (case["cohort"] == "predicates")):
            raise ValueError("fixture did not cross the reviewed product/helper path")
        return dict(output=result, writes=self.writes, snapshots=self.snapshots,
                    atan2_arguments=self.arguments, atan2_returns=self.atan_returned,
                    final_status=self.uc.reg_read(native.r.UC_X86_REG_FPSW))


def cases():
    velocities = (0, 0x80000000, 0x3E7FFFFF, 0x3E800000, 0x3E800001,
                  0xBE800000, 0x3F800000, 0xBF800000, 1, 0x80000001,
                  0x7FC00011, 0xFFC00021, 0x7F800001, 0xFF800001,
                  0x7F800000, 0xFF800000)
    words = [precision + rounding for precision in (0x27F, 0x37F)
             for rounding in (0, 0x400, 0x800, 0xC00)]
    for velocity, facing, word in itertools.product(
            velocities, (-128, -2, -1, 0, 1, 2, 126, 127), words):
        yield dict(action=902, seq=2, phase=0, state=0, owner_value174=100,
                   counter=1, timer=1, vy=0.0, x=500.0, y=100.0, match_identifier=3,
                   vx_bits=velocity, facing=facing, cw=word, cohort="prefix")
    for state, velocity, facing, position, word in itertools.product(
            (0, 1), (-3.25, -1.0, 1.0, 3.25), (-128, -1, 1, 127),
            (100.0, 500.0, 900.0), words):
        yield dict(action=902, seq=2, phase=0, state=state, owner_value174=100,
                   counter=1, timer=1, vy=0.0, x=position, y=100.0, match_identifier=3,
                   vx_bits=struct.unpack("<I", struct.pack("<f", velocity))[0],
                   facing=facing, cw=word, cohort="predicates")


def audit(obj, symbol, contrast=None, contrast_symbol=None):
    native.facts.audit()
    destinations = struct.unpack("<42I", native.c.target_bytes(0x4A197C, 168))
    index = native.c.target_bytes(0x4A1A24 + 102, 1)[0]
    start = destinations[index]
    end = min(pc for pc in destinations if pc > start)
    target_windows = multiplication_windows(native.facts.decode(
        native.c.target_bytes(start, end - start), start))
    if len(target_windows) != 5:
        raise ValueError("target902 steering product inventory differs")
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
    target = ProductProbe(image)
    target.configure(target_windows)
    probes, packets = [target], []
    for label, path, name in [("source", obj, symbol)] + (
            [("contrast", contrast, contrast_symbol)] if contrast else []):
        code, windows = source_packet(path, name)
        probe = ProductProbe(image, code)
        probe.configure(windows)
        probes.append(probe)
        packets.append(dict(label=label, object=str(path), symbol=name, source_bytes=len(code),
                            runtime_sha256=hashlib.sha256(code).hexdigest(),
                            windows=[[dict(address=row.address, bytes=row.bytes.hex(),
                                           text=row.mnemonic + " " + row.op_str)
                                      for row in window] for window in windows]))
    differences = {packet["label"]: Counter() for packet in packets}
    examples = {label: [] for label in differences}
    counts, stages, inputs = Counter(), Counter(), hashlib.sha256()
    for case in cases():
        inputs.update(json.dumps(case, sort_keys=True).encode())
        answers = [probe.evaluate(case) for probe in probes]
        counts["cases"] += 1
        counts[case["cohort"]] += 1
        counts[answers[0]["output"]["endpoint"]["kind"]] += 1
        counts["atan2_returns"] += answers[0]["atan2_returns"]
        stages.update(row["stage"] for row in answers[0]["snapshots"])
        for packet, answer in zip(packets, answers[1:]):
            label = packet["label"]
            changed = [key for key in answers[0] if answers[0][key] != answer[key]]
            differences[label].update(changed)
            if changed and len(examples[label]) < 2:
                examples[label].append(dict(case=case, fields=changed,
                                            target_snapshots=answers[0]["snapshots"],
                                            source_snapshots=answer["snapshots"]))
    if counts["cases"] != 1792 or any(not stages["multiply_" + str(i)] for i in range(5)):
        raise ValueError("incomplete directional product matrix")
    if before != pins():
        raise ValueError("audit inputs changed during execution")
    return dict(schema="th105-reimu-object-902-products-v1",
                result="equal_scoped_902_products" if not differences["source"] else "mismatch",
                target_sha256=native.c.verify_target(), counts=dict(counts), target_stages=dict(stages),
                differences={label: dict(value) for label, value in differences.items()},
                examples=examples, packets=packets, input_sha256=inputs.hexdigest(), input_pins=before,
                engine_versions=dict(unicorn=native.unicorn.__version__,
                                     capstone=lifetimes.capstone.__version__,
                                     pefile=lifetimes.pefile.__version__),
                build_provenance_verified=False,
                target_windows=[[dict(address=row.address, bytes=row.bytes.hex(),
                                      text=row.mnemonic + " " + row.op_str) for row in window]
                                for window in target_windows],
                scope="902 sequence2 x86 emulation only;1024 raw-bit prefixes stop at real atan2 "
                      "entry,768 finite cases execute original helper to real return;512 full "
                      "RET ABI paths and256 first-spawn boundaries; masked exceptions with "
                      "PC53/64/four rounding modes; no returning spawn, arbitrary aliases, "
                      "unmasked exceptions, original nominal types or whole-root exactness claim")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("object", type=Path)
    parser.add_argument("--symbol", default=native.SYMBOL)
    parser.add_argument("--contrast-object", type=Path)
    parser.add_argument("--contrast-symbol", default=native.SYMBOL)
    args = parser.parse_args()
    report = audit(args.object, args.symbol, args.contrast_object, args.contrast_symbol)
    print(json.dumps(report, indent=2))
    raise SystemExit(0 if report["result"] == "equal_scoped_902_products" else 1)
