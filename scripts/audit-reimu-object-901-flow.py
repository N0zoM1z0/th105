#!/usr/bin/env python3
"""Audit901 prefixes, its four-word caller buffer and cross-sequence call sharing.

Actual helper instructions run to original frontiers. Subsequent call graphs
are static projections conditional on normal ABI returns, with RETs collapsed.
They do not prove branch predicates, returning World behavior or exact bytes.
"""

from __future__ import annotations

import argparse
import hashlib
import importlib.util
import json
from pathlib import Path
import struct

from capstone import x86_const as x
import pefile
from unicorn import x86_const as u

ROOT = Path(__file__).resolve().parents[1]


def load(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / "scripts" / filename)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


graphs = load("flow901_graphs", "audit-reimu-object-selector-families.py")
owners = load("flow901_owners", "audit-giant-action-owners.py")
native = graphs.native


def sequence_switch(rows, start, end, read, maximum=6):
    local = [row for row in rows if start <= row.address < end]
    jumps = [
        (index, row)
        for index, row in enumerate(local)
        if row.mnemonic == "jmp"
        and row.operands[0].type == x.X86_OP_MEM
        and not row.operands[0].mem.base
        and row.operands[0].mem.index
        and row.operands[0].mem.scale == 4
    ]
    reviewed = []
    for index, jump in jumps:
        if index < 2:
            continue
        compare, guard = local[index - 2 : index]
        register = jump.operands[0].mem.index
        if (
            compare.mnemonic == "cmp"
            and compare.operands[0].type == x.X86_OP_REG
            and compare.operands[0].reg == register
            and compare.operands[1].type == x.X86_OP_IMM
            and compare.operands[1].imm == maximum
            and guard.mnemonic == "ja"
            and guard.operands[0].type == x.X86_OP_IMM
            and any(
                row.mnemonic == "movsx"
                and row.operands[0].type == x.X86_OP_REG
                and row.operands[0].reg == register
                and row.operands[1].type == x.X86_OP_MEM
                and row.operands[1].size == 2
                and row.operands[1].mem.base == x.X86_REG_ESI
                and not row.operands[1].mem.index
                and row.operands[1].mem.disp == 0x13E
                for row in local[: index - 2]
            )
        ):
            reviewed.append(jump)
    if len(reviewed) != 1:
        raise ValueError(f"missing unique signed-sequence/CMP{maximum}/JA protocol")
    jump = reviewed[0]
    table = jump.operands[0].mem.disp
    return dict(
        instruction=jump.address,
        table=table,
        destinations=list(
            struct.unpack(f"<{maximum + 1}I", read(table, 4 * (maximum + 1)))
        ),
    )


def cases():
    examples = list(native.upper_projectile_cases())
    selected = [
        next(
            case
            for case in examples
            if case["action"] == 901
            and case["cohort"] == "upper-state"
            and case["seq"] == mode
        )
        for mode in range(7)
    ]
    packet = dict(
        next(
            case
            for case in examples
            if case["cohort"] == "upper-901-orbit" and case["owner_word730"] == 1
        )
    )
    packet.update(stack_fill=0xA5, observe_four_word_buffer=True)
    return selected + [packet]


class ObservedProbe(native.Probe):
    def evaluate(self, case):
        self.input_case, self.switch_hits, self.buffer_words = case, [], None
        return super().evaluate(case)

    def instruction(self, engine, address, size, unused):
        if address == self.start and "stack_fill" in self.input_case:
            stack = engine.reg_read(u.UC_X86_REG_ESP)
            engine.mem_write(
                stack - 0x600, bytes([self.input_case["stack_fill"]]) * 0x600
            )
        if address == self.sequence_jump:
            self.switch_hits.append(address)
        if address == native.SPAWN and self.input_case.get("observe_four_word_buffer"):
            stack = engine.reg_read(u.UC_X86_REG_ESP)
            args = struct.unpack("<8I", engine.mem_read(stack, 32))
            if args[1] != 901 or args[7] != 3:
                raise ValueError("unexpected901 four-word caller-buffer frontier")
            self.buffer_words = bytes(engine.mem_read(args[6], 16)).hex()
        super().instruction(engine, address, size, unused)


def audit(path):
    facts = native.facts.audit()
    ownership = owners.audit(
        "reimu-object-vslot28", path, "gpt-web-reimu-object-action-state"
    )
    candidate = native.export(path)
    metadata = ownership["candidate_metadata_start"]
    source_rows = graphs.decode(candidate[:metadata], native.S)
    target_rows = [
        row
        for lo, hi in native.facts.RANGES
        for row in native.facts.decode(native.c.target_bytes(lo, hi - lo), lo)
    ]
    entry = next(row for row in ownership["owners"] if row["name"] == "actions:901")

    def read_source(address, size):
        if (
            not native.S + metadata
            <= address
            <= address + size
            <= native.S + len(candidate)
        ):
            raise ValueError("901 sequence table leaves reviewed source metadata")
        return candidate[address - native.S : address - native.S + size]

    target_switch = sequence_switch(
        target_rows, 0x49CEC2, 0x49D7D6, native.c.target_bytes
    )
    source_start = native.S + entry["candidate_offset"]
    source_switch = sequence_switch(
        source_rows, source_start, source_start + entry["candidate_span"], read_source
    )
    projections = []
    for rows, switch in ((target_rows, target_switch), (source_rows, source_switch)):
        part = graphs.partition(rows, switch)
        projections.append(
            [graphs.call_graph(rows, part, mode, None) for mode in range(7)]
        )
    combined = [graphs.combine_call_graphs(family) for family in projections]
    per_mode = [graphs.same_call_graph(a, b) for a, b in zip(*projections)]
    combined_equal = graphs.same_call_graph(*combined)

    image = bytearray(
        pefile.PE(str(ROOT / "resources/th105.exe")).get_memory_mapped_image()
    )
    math = native.load("flow901_math", "scripts/iku_native_math.py")
    table, lookup = math.lookup_fixture(native.c)
    image[0x2FE8B0 : 0x2FE8B0 + len(table)] = table
    seeds = native.seed_fixtures(bytes(image))
    surfaces, surface_receipt = native.surface_fixtures(bytes(image))
    target = ObservedProbe(bytes(image), seeds=seeds, surfaces=surfaces)
    source = ObservedProbe(bytes(image), candidate, seeds=seeds, surfaces=surfaces)
    target.sequence_jump, source.sequence_jump = (
        target_switch["instruction"],
        source_switch["instruction"],
    )
    inputs, differences, buffer_observations = cases(), [], []
    for index, case in enumerate(inputs):
        expected, actual = target.evaluate(case), source.evaluate(case)
        if expected != actual:
            differences.append(
                dict(case_index=index, reason="actual901 prefix differs")
            )
        if target.switch_hits != [target.sequence_jump] or source.switch_hits != [
            source.sequence_jump
        ]:
            differences.append(
                dict(case_index=index, reason="901 sequence dispatch differs")
            )
        if case.get("observe_four_word_buffer"):
            buffer_observations.append(
                dict(
                    case_index=index,
                    target=target.buffer_words,
                    source=source.buffer_words,
                )
            )
            if target.buffer_words != "000000000000403f0000404000000000":
                raise ValueError(
                    "target901 caller buffer differs from reviewed four-word object"
                )
            if target.buffer_words != source.buffer_words:
                differences.append(
                    dict(case_index=index, reason="four-word caller buffer differs")
                )
    return dict(
        schema="th105-reimu-901-flow-v1",
        result="equal_scoped_901_flow"
        if all(per_mode) and combined_equal and not differences
        else "rejected",
        target_sha256=facts["target_sha256"],
        object_sha256=hashlib.sha256(path.read_bytes()).hexdigest(),
        candidate_sha256=hashlib.sha256(candidate).hexdigest(),
        build_provenance_verified=False,
        case_count=len(inputs),
        input_sha256=hashlib.sha256(
            json.dumps(inputs, sort_keys=True).encode()
        ).hexdigest(),
        inputs=inputs,
        runtime_differences=differences,
        caller_buffer_observations=buffer_observations,
        per_mode_call_graph_equal=per_mode,
        combined_call_graph_equal=combined_equal,
        combined_call_counts=[len(graph) - 8 for graph in combined],
        target_switch=target_switch,
        source_switch=source_switch,
        combined_graphs=dict(target=combined[0], source=combined[1]),
        lookup_initialization=lookup,
        surface_initialization=surface_receipt,
        support_sha256={
            name: hashlib.sha256((ROOT / name).read_bytes()).hexdigest()
            for name in (
                "scripts/audit-reimu-object-901-flow.py",
                "scripts/audit-reimu-object-selector-families.py",
                "scripts/audit-reimu-object-scalar-actions.py",
                "scripts/audit-reimu-object-entry-calls.py",
                "scripts/audit-reimu-object-update-target.py",
                "scripts/audit-common-fighter-animation-paths.py",
                "scripts/audit-giant-action-owners.py",
                "scripts/compare-giant-action-switches.py",
                "scripts/map-giant-action-switches.py",
                "scripts/iku_native_math.py",
                "scripts/compare-function.py",
                "src/characters/ReimuObjectActionStateStaging.cpp",
                "src/characters/ReimuObjectActionStateStaging.hpp",
            )
        },
        scope="actual901 prefixes and caller-buffer initialization; static normal-return call/RET projections preserve partial sharing across seven sequences; no predicate, returning-World or canonical equivalence claim",
    )


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("object", type=Path)
    parser.add_argument("--output", type=Path)
    args = parser.parse_args()
    try:
        report = audit(args.object)
    except (ValueError, OSError) as error:
        report = dict(result="rejected", reason=str(error))
    if args.output:
        args.output.parent.mkdir(parents=True, exist_ok=True)
        args.output.write_text(json.dumps(report, indent=2) + "\n")
    print(
        json.dumps(
            {
                k: v
                for k, v in report.items()
                if k
                not in (
                    "inputs",
                    "combined_graphs",
                    "lookup_initialization",
                    "surface_initialization",
                    "support_sha256",
                )
            },
            indent=2,
        )
    )
    return int(report["result"] != "equal_scoped_901_flow")


if __name__ == "__main__":
    raise SystemExit(main())
