#!/usr/bin/env python3
"""Audit action804's real sequence2 velocity and x87 lifetimes.

The finite matrix uses the original animation helper and full RET ABI.
It neither supplies opaque returns nor establishes whole-root exactness.
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

import capstone
from capstone import x86_const as x
import pefile

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
SPEC = importlib.util.spec_from_file_location(
    "action804_world", ROOT / "scripts/audit-reimu-object-world-sharing.py"
)
world = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(world)
native = world.native
ANIMATION = 0x4351C0


def source_packet(path, symbol):
    unit = tomllib.loads((ROOT / "config/match-units.toml").read_text())["units"][
        "gpt-web-reimu-object-action-state"
    ]
    function = unit["functions"][0]
    targets, data = native.c.known_targets(), native.c.known_data_targets()
    for pair in function["rel32_targets"]:
        name, address = pair.split("=", 1)
        targets[name] = int(address, 16)
    for pair in function["dir32_targets"]:
        name, key = pair.split("=", 1)
        data[name] = data[key]
    targets.update({
        "?has_crossed_stage_surface_while_descending@ReimuObject@@QAEHXZ": 0x5F9310,
        "?publish_battle_layout_scalar@ReimuObject@@QAEXM@Z": 0x4359D0,
    })
    obj = native.m.CoffObject(path, symbol_base=symbol)
    code = native.c.coff_symbol_bytes(
        path, symbol, native.S, len(obj.text), targets, data
    )
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    decoder.detail = True
    head = list(decoder.disasm(code[:100], native.S))
    jump = next(row for row in head if row.mnemonic == "jmp"
                and row.operands[0].type == x.X86_OP_MEM)
    indices = [row.operands[1].mem.disp for row in head
               if row.address < jump.address and row.mnemonic == "movzx"
               and row.operands[1].type == x.X86_OP_MEM
               and row.operands[1].mem.disp > native.S]
    if len(indices) != 1:
        raise ValueError("unreviewed primary dispatch index")
    metadata = min(indices[0], jump.operands[0].mem.disp) - native.S
    rows = native.facts.decode(code[:metadata], native.S)
    switches = world.reviewed_source_switches(rows, code, metadata)
    primary = switches[jump.address]
    if len(switches) != 22 or primary["checked_maximum"] != 199:
        raise ValueError("source switch inventory differs")
    index = code[primary["index_table"] - native.S + 4]
    start = primary["destinations"][index]
    end = min(pc for pc in primary["destinations"] if pc > start)
    return code, [row for row in rows if start <= row.address < end], metadata


def velocity_window(rows):
    candidates = []
    for index, row in enumerate(rows):
        if row.mnemonic != "fsub" or len(row.operands) != 1:
            continue
        operand = row.operands[0]
        if (operand.type == x.X86_OP_MEM and not operand.mem.base
                and not operand.mem.index and operand.size == 8
                and native.c.target_bytes(operand.mem.disp, 8)
                == struct.pack("<d", 0.25)):
            candidates.append(index)
    if len(candidates) != 1:
        raise ValueError("804 gravity operation is not unique")
    start = candidates[0] - 1
    if (rows[start].mnemonic != "fld"
            or rows[start].op_str != "dword ptr [esi + 0xf8]"):
        raise ValueError("gravity does not load the actual velocity")
    end = next(index for index in range(start, len(rows))
               if rows[index].mnemonic == "fstp"
               and rows[index].op_str == "dword ptr [esi + 0x12c]")
    return rows[start:end + 1]


def logical_float_state(engine):
    tags = engine.reg_read(native.r.UC_X86_REG_FPTAG)
    top = (engine.reg_read(native.r.UC_X86_REG_FPSW) >> 11) & 7
    values = []
    for index in range(8):
        physical = (top + index) & 7
        tag = (tags >> (physical * 2)) & 3
        if tag != 3:
            mantissa, exponent = engine.reg_read(
                getattr(native.r, "UC_X86_REG_FP" + str(physical))
            )
            values.append(dict(index=index, tag=tag,
                               words=[f"{mantissa:016x}", f"{exponent:04x}"]))
    return dict(depth=len(values), values=values)


class LifetimeProbe(native.Probe):
    def configure(self, window):
        compare = next(row for row in window if row.mnemonic == "fcomp")
        self.stages = {compare.address: "predicate",
                       compare.address + compare.size: "after_predicate",
                       ANIMATION: "animation"}

    def evaluate(self, case):
        self.case, self.events, self.snapshots = case, [], []
        self.stage_counts = Counter()
        result = super().evaluate(case)
        return dict(output=result, writes=self.events, snapshots=self.snapshots,
                    final_status=self.uc.reg_read(native.r.UC_X86_REG_FPSW))

    def instruction(self, engine, pc, size, unused):
        if pc == self.start:
            for offset, name in ((0xF0, "y_bits"), (0xF8, "vy_bits")):
                engine.mem_write(native.OWNER + offset,
                                 struct.pack("<I", self.case[name]))
        if pc in self.stages:
            stage = self.stages[pc]
            self.stage_counts[stage] += 1
            self.snapshots.append(dict(stage=stage, **logical_float_state(engine)))
        super().instruction(engine, pc, size, unused)

    def write(self, engine, access, address, size, value, unused):
        if native.OWNER <= address < address + size <= native.OWNER + 0x388:
            offset, value = address - native.OWNER, value & ((1 << (size * 8)) - 1)
            self.events.append([offset, size, value])
            if offset in (0xF8, 0x12C, 0x330):
                self.snapshots.append(dict(stage=f"store_{offset:x}", size=size,
                                           value=value, **logical_float_state(engine)))
        super().write(engine, access, address, size, value, unused)


def cases():
    ys = (0, 0x80000000, 0x3E800000, 0xBE800000, 0x3F800000,
          0xBF800000, 0x7FC00011, 0xFFC00021, 0x7F800000, 0xFF800000)
    velocities = (0, 0x80000000, 0x3E7FFFFF, 0x3E800000, 0x3E800001,
                  0xBE800000, 0x3F800000, 0xBF800000, 1, 0x80000001,
                  0x7FC00011, 0xFFC00021, 0x7F800001, 0xFF800001,
                  0x7F800000, 0xFF800000)
    words = [precision + rounding for precision in (0x27F, 0x37F)
             for rounding in (0, 0x400, 0x800, 0xC00)]
    for y, vy, word, alpha in itertools.product(ys, velocities, words, (0, 4, 5, 200)):
        yield dict(action=804, seq=2, phase=0, counter=1, timer=0,
                   alpha=alpha, y_bits=y, vy_bits=vy, cw=word)


def audit(obj, symbol, contrast=None, contrast_symbol=None):
    native.facts.audit()
    target_rows = native.facts.decode(native.c.target_bytes(0x496C1E, 0x468), 0x496C1E)
    target_window = velocity_window(target_rows)
    paths = [obj, Path(__file__), ROOT / "resources/th105.exe",
             ROOT / "config/match-units.toml",
             *[ROOT / "config" / name for name in (
                 "target.toml", "function-byte-ownership.toml",
                 "giant-action-switches.toml", "known-symbols.csv", "known-globals.csv",
                 "reccmp-relocations.csv")],
             ROOT / "src/characters/ReimuObjectActionStateStaging.cpp",
             ROOT / "src/characters/ReimuObjectActionStateStaging.hpp",
             *[ROOT / "scripts" / name for name in (
                 "audit-reimu-object-scalar-actions.py",
                 "audit-reimu-object-world-sharing.py",
                 "audit-reimu-object-selector-families.py",
                 "audit-reimu-object-update-target.py",
                 "audit-reimu-object-entry-calls.py",
                 "audit-common-fighter-animation-paths.py",
                 "audit-common-fighter-motion-paths.py",
                 "compare-function.py", "compare-giant-action-switches.py",
                 "match_literals.py", "workflow_manifest.py", "requirements-ci.txt")]]
    if contrast:
        paths.append(contrast)
    pins = lambda: {str(path): hashlib.sha256(path.read_bytes()).hexdigest()
                    for path in paths}
    before = pins()
    image = pefile.PE(str(ROOT / "resources/th105.exe")).get_memory_mapped_image()
    probes = [LifetimeProbe(image)]
    probes[0].configure(target_window)
    packets = []
    for label, path, name in [("source", obj, symbol)] + (
            [("contrast", contrast, contrast_symbol)] if contrast else []):
        code, rows, metadata = source_packet(path, name)
        window = velocity_window(rows)
        probe = LifetimeProbe(image, code)
        probe.configure(window)
        probes.append(probe)
        packets.append(dict(label=label, object=str(path), symbol=name,
                            runtime_sha256=hashlib.sha256(code).hexdigest(),
                            source_bytes=len(code), metadata_offset=metadata,
                            window_bytes=sum(row.size for row in window),
                            window_byte_equal=(b"".join(row.bytes for row in window)
                                               == b"".join(row.bytes for row in target_window)),
                            window=[dict(address=row.address, bytes=row.bytes.hex(),
                                         text=row.mnemonic + " " + row.op_str)
                                    for row in window]))
    differences = {packet["label"]: Counter() for packet in packets}
    examples = {label: [] for label in differences}
    counts, inputs = Counter(), hashlib.sha256()
    for case in cases():
        inputs.update(json.dumps(case, sort_keys=True).encode())
        answers = [probe.evaluate(case) for probe in probes]
        if (probes[0].stage_counts["predicate"] != 1
                or probes[0].stage_counts["after_predicate"] != 1):
            raise ValueError("fixture does not reach the bounded predicate exactly once")
        counts["cases"] += 1
        counts["animation"] += probes[0].stage_counts["animation"]
        counts["bounced"] += sum(row[0] == 0xF8 for row in answers[0]["writes"]) == 2
        for packet, answer in zip(packets, answers[1:]):
            label = packet["label"]
            changed = [key for key in answers[0] if answers[0][key] != answer[key]]
            differences[label].update(changed)
            if changed and len(examples[label]) < 3:
                examples[label].append(dict(case=case, fields=changed,
                                            target_snapshots=answers[0]["snapshots"],
                                            source_snapshots=answer["snapshots"]))
    if counts["cases"] != 5120 or before != pins():
        raise ValueError("incomplete matrix or changed audit inputs")
    return dict(
        schema="th105-reimu-object-804-lifetimes-v1",
        result="equal_scoped_804_lifetimes" if not differences["source"] else "mismatch",
        target_sha256=native.c.verify_target(), counts=dict(counts),
        engine_versions=dict(unicorn=native.unicorn.__version__,
                             capstone=capstone.__version__, pefile=pefile.__version__),
        differences={key: dict(value) for key, value in differences.items()},
        examples=examples, packets=packets, input_sha256=inputs.hexdigest(),
        input_pins=before, build_provenance_verified=False,
        target_window=[dict(address=row.address, bytes=row.bytes.hex(),
                            text=row.mnemonic + " " + row.op_str) for row in target_window],
        animation_sha256=hashlib.sha256(native.c.target_bytes(ANIMATION, 62)).hexdigest(),
        scope="804 sequence2 x86 emulation only; original real helper, full RET ABI, outputs, ordered "
              "stores, logical x87 at predicate/store/helper and final status; masked "
              "exceptions with explicit PC/RC; excludes unmasked exceptions, arbitrary "
              "aliases/vtables/resources, original types/TU and whole-root exactness",
    )


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("object", type=Path)
    parser.add_argument("--symbol", default=native.SYMBOL)
    parser.add_argument("--contrast-object", type=Path)
    parser.add_argument("--contrast-symbol", default="?dispatch_action_state@ReimuObject@@UAEXXZ")
    args = parser.parse_args()
    report = audit(args.object, args.symbol, args.contrast_object, args.contrast_symbol)
    print(json.dumps(report, indent=2))
    raise SystemExit(0 if report["result"] == "equal_scoped_804_lifetimes" else 1)
