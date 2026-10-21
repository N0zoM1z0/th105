#!/usr/bin/env python3
"""Audit907's real bounce callbacks, ordered writes and logical x87 states.

This finite sequence4 fixture executes the original next-block helper and its
real continuations. It does not require identical physical callback sharing,
replace helper returns, or establish canonical equality of root496540.
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
import tomllib

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location(
    "bounce_retirement", ROOT / "scripts/audit-reimu-object-retirement-fpu.py"
)
retirement = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(retirement)
native = retirement.native
NEXT_BLOCK = 0x45C220


def logical_float_state(engine):
    state = retirement.tail.floating_state(engine)
    return {key: state[key] for key in ("depth", "values")}


class BounceProbe(retirement.stores.StoreProbe):
    def evaluate(self, case):
        self.snapshots, self.callbacks = [], []
        result, writes = super().evaluate(case)
        return dict(result=result, writes=[list(row[1:]) for row in writes],
                    snapshots=self.snapshots, callbacks=self.callbacks)

    def write(self, engine, access, address, size, value, unused):
        pc = engine.reg_read(native.r.UC_X86_REG_EIP)
        in_root = pc in self.root_instructions
        if in_root and address in (
            native.OWNER + 0xF4, native.OWNER + 0xF8,
            native.OWNER + 0x184, native.OWNER + 0x180,
        ):
            self.snapshots.append(dict(
                field=address - native.OWNER, size=size,
                value=value & ((1 << (size * 8)) - 1),
                **logical_float_state(engine),
            ))
        super().write(engine, access, address, size, value, unused)

    def instruction(self, engine, pc, size, unused):
        if pc == NEXT_BLOCK:
            sp = engine.reg_read(native.r.UC_X86_REG_ESP)
            continuation = struct.unpack("<I", engine.mem_read(sp, 4))[0]
            if continuation in self.root_calls:
                if engine.reg_read(native.r.UC_X86_REG_ECX) != native.OWNER:
                    raise ValueError("bounce next-block receiver differs")
                vtable = struct.unpack("<I", engine.mem_read(native.OWNER, 4))[0]
                slot = struct.unpack("<I", engine.mem_read(vtable + 0x14, 4))[0]
                if vtable != 0x6C40A4 or slot != NEXT_BLOCK:
                    raise ValueError("original ReimuObject slot14 differs")
                self.callback_sites[self.root_calls[continuation]] += 1
                self.callbacks.append(dict(receiver=native.OWNER,
                                           **logical_float_state(engine)))
        super().instruction(engine, pc, size, unused)


def cases():
    for x, y, vx, vy, facing, cw, phase in itertools.product(
        (-1.0, 0.0, 1280.0, 1281.0), (-1.0, 0.0, 900.0, 901.0),
        (-3.25, -0.0, 3.25, float("nan")),
        (-1.5, -0.0, 1.5, float("nan")), (-1, 1), (0x27F, 0x37F), (0, 6),
    ):
        # This fixture's later owner_value174 initialization is the actual
        # +174 value consumed by907. Keep it above2500 to admit state1 bounce.
        yield dict(action=907, seq=4, state=1, owner_value174=3000,
                   x=x, y=y, vx=vx, vy=vy, facing=facing, cw=cw, phase=phase)


def audit(obj):
    paths = [obj, Path(__file__), ROOT / "resources/th105.exe",
             ROOT / "config/match-units.toml",
             ROOT / "src/characters/ReimuObjectActionStateStaging.cpp",
             ROOT / "src/characters/ReimuObjectActionStateStaging.hpp",
             *[ROOT / "scripts" / name for name in (
                 "audit-reimu-object-retirement-fpu.py",
                 "audit-reimu-object-typed-stores.py",
                 "audit-reimu-object-999-tail.py",
                 "audit-reimu-object-scalar-actions.py",
                 "audit-reimu-object-update-target.py",
                 "audit-reimu-object-entry-calls.py",
                 "audit-common-fighter-animation-paths.py",
                 "compare-function.py", "compare-giant-action-switches.py",
             )]]

    def pins():
        return {str(p): hashlib.sha256(p.read_bytes()).hexdigest() for p in paths}

    before = pins()
    code = native.export(obj)  # Target audit plus complete typed relocation replay.
    image = native.pefile.PE(str(ROOT / "resources/th105.exe")).get_memory_mapped_image()
    target_rows = [row for lo, hi in native.facts.RANGES
                   for row in native.facts.decode(native.c.target_bytes(lo, hi - lo), lo)]
    root = native.m.load_target_mapper().select_root(
        tomllib.loads((ROOT / "config/giant-action-switches.toml").read_text()),
        "reimu-object-vslot28",
    )
    mapping = native.m.build_candidate_map(
        native.m.CoffObject(obj, symbol_base=native.SYMBOL), root,
    )
    source_rows = native.facts.decode(code[:mapping["metadata_start"]], native.S)
    probes = [BounceProbe(image), BounceProbe(image, code)]
    for probe, rows in zip(probes, (target_rows, source_rows)):
        probe.root_instructions = {row.address for row in rows}
        probe.root_calls = {row.address + row.size: row.address
                            for row in rows if row.mnemonic == "call"}
        probe.callback_sites = Counter()
    inputs, counts, mismatches, examples = hashlib.sha256(), Counter(), Counter(), []
    for case in cases():
        inputs.update(json.dumps(case, sort_keys=True).encode())
        expected, actual = [probe.evaluate(case) for probe in probes]
        xhit = ((case["facing"] * case["vx"] < 0 and case["x"] < 0)
                or (case["facing"] * case["vx"] > 0 and case["x"] > 1280))
        yhit = ((case["vy"] < 0 and case["y"] < 0)
                or (case["vy"] > 0 and case["y"] > 900))
        if len(expected["callbacks"]) != int(xhit or yhit):
            raise ValueError("actual target callbacks violate the admitted bounce gate")
        counts["x" if xhit else "y" if yhit else "none"] += 1
        different = [key for key in expected if expected[key] != actual[key]]
        mismatches.update(different)
        if different and len(examples) < 3:
            examples.append(dict(case=case, fields=different, target=expected, source=actual))
    if sum(counts.values()) != 2048 or before != pins():
        raise ValueError("incomplete bounce matrix or changed audit inputs")
    return dict(
        schema="th105-reimu-object-907-bounce-v1",
        result="equal_scoped_907_bounce" if not mismatches else "mismatch",
        target_sha256=native.c.verify_target(), object_sha256=before[str(obj)],
        native_sha256=hashlib.sha256(code).hexdigest(), cases=sum(counts.values()),
        axis_counts=dict(counts), input_sha256=inputs.hexdigest(),
        differences=dict(mismatches), examples=examples,
        root_callback_sites=[{hex(k): v for k, v in sorted(p.callback_sites.items())}
                             for p in probes],
        visited_root_instructions=[len(p.visited) for p in probes],
        next_block_sha256=hashlib.sha256(native.c.target_bytes(NEXT_BLOCK, 138)).hexdigest(),
        input_pins=before, build_provenance_verified=False,
        scope="907 sequence4 only; real callbacks and RETs, outputs, ordered writes, "
              "logical x87 at bounce stores and callback entry; excludes physical TOP/exception "
              "flags, arbitrary aliases/resources/vtables, unmasked exceptions, original TU "
              "and whole-root semantics/canonical equality",
    )


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("object", type=Path)
    parser.add_argument("--output", type=Path)
    args = parser.parse_args()
    report = audit(args.object)
    output = args.output or ROOT / "build/reimu-object-907-bounce.json"
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps({key: report[key] for key in (
        "result", "cases", "axis_counts", "differences", "root_callback_sites",
    )}))
    raise SystemExit(0 if report["result"] == "equal_scoped_907_bounce" else 1)
