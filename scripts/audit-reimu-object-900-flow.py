#!/usr/bin/env python3
"""Audit900 request prefixes, selected-word stores and physical call sharing.

Helpers execute original instructions and stop at real opaque entries. Static
call/RET projections assume normal ABI returns and do not prove predicates or
returning World effects. Invalid selectors are observed only in the target:
the fourth request word is unwritten, outside the defined source input domain.
"""

from __future__ import annotations

import argparse
import hashlib
import importlib.util
import json
from pathlib import Path
import struct

import pefile
from unicorn import x86_const as u

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location(
    "flow900_common", ROOT / "scripts/audit-reimu-object-901-flow.py"
)
common = importlib.util.module_from_spec(spec)
spec.loader.exec_module(common)
graphs, owners, native = common.graphs, common.owners, common.native


def cases():
    examples = list(native.upper_projectile_cases())
    selected = [
        dict(
            next(
                case
                for case in examples
                if case["action"] == 900
                and case["cohort"] == "upper-state"
                and case["seq"] == mode
            )
        )
        for mode in range(4)
    ]
    packet = dict(
        next(
            case
            for case in examples
            if case["cohort"] == "upper-900-gates"
            and case["seq"] == 0
            and case["counter"] == 40
        )
    )
    selected += [
        dict(
            packet,
            match_identifier=mode,
            stack_fill=0xA5,
            packet_selector=mode,
            target_only=mode not in range(4),
        )
        for mode in (0, 1, 2, 3, -1, 4)
    ]
    emission = dict(packet, seq=3, counter=6, owner_value174=1)
    selected += [
        dict(emission, amplitude=amplitude, emission_prefix=True)
        for amplitude in (0.0, 0.25)
    ]
    return selected


class ObservedProbe(common.ObservedProbe):
    def evaluate(self, case):
        self.packet, self.stack_writes, self.fourth_word_writes = None, [], []
        self.floating_events = []
        return super().evaluate(case)

    def write(self, engine, access, address, size, value, unused):
        if native.STACK <= address < native.STACK + 0x10000:
            self.stack_writes.append(
                dict(
                    site=engine.reg_read(u.UC_X86_REG_EIP),
                    address=address,
                    size=size,
                    value=value,
                    producer=self.floating_events[-2]
                    if len(self.floating_events) > 1
                    and self.floating_events[-1] == engine.reg_read(u.UC_X86_REG_EIP)
                    else None,
                )
            )
        super().write(engine, access, address, size, value, unused)

    def instruction(self, engine, address, size, unused):
        row = self.root_instructions.get(address)
        if row is not None and (
            row.mnemonic.startswith("f") or row.group(graphs.capstone.CS_GRP_CALL)
        ):
            self.floating_events.append(address)
        if address == native.SPAWN:
            stack = engine.reg_read(u.UC_X86_REG_ESP)
            args = struct.unpack("<8I", engine.mem_read(stack, 32))
            if args[1] != 900 or args[7] not in (3, 4):
                raise ValueError("unexpected900 request frontier")
            self.packet = dict(
                count=args[7], words=bytes(engine.mem_read(args[6], args[7] * 4)).hex()
            )
            if args[7] == 4:
                self.fourth_word_writes = [
                    row
                    for row in self.stack_writes
                    if row["address"] == args[6] + 12 and row["size"] == 4
                ]
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
    entry = next(row for row in ownership["owners"] if row["name"] == "actions:900")

    def read_source(address, size):
        if (
            not native.S + metadata
            <= address
            <= address + size
            <= native.S + len(candidate)
        ):
            raise ValueError("900 table leaves reviewed source metadata")
        return candidate[address - native.S : address - native.S + size]

    target_switch = common.sequence_switch(
        target_rows, 0x49C9F5, 0x49CEC2, native.c.target_bytes, maximum=3
    )
    source_start = native.S + entry["candidate_offset"]
    source_switch = common.sequence_switch(
        source_rows,
        source_start,
        source_start + entry["candidate_span"],
        read_source,
        maximum=3,
    )
    projections, nested = [], []
    for rows, switch, read in (
        (target_rows, target_switch, native.c.target_bytes),
        (source_rows, source_switch, read_source),
    ):
        reviewed = graphs.selector_switches(rows, read)
        nested.append(reviewed)
        part = graphs.partition(rows, switch, reviewed)
        projections.append(
            [graphs.call_graph(rows, part, mode, None, reviewed) for mode in range(4)]
        )
    combined = [graphs.combine_call_graphs(family) for family in projections]
    per_mode = [graphs.same_call_graph(a, b) for a, b in zip(*projections)]
    combined_equal = graphs.same_call_graph(*combined)

    image = bytearray(
        pefile.PE(str(ROOT / "resources/th105.exe")).get_memory_mapped_image()
    )
    math = native.load("flow900_math", "scripts/iku_native_math.py")
    table, lookup = math.lookup_fixture(native.c)
    image[0x2FE8B0 : 0x2FE8B0 + len(table)] = table
    seeds = native.seed_fixtures(bytes(image))
    target = ObservedProbe(bytes(image), seeds=seeds)
    source = ObservedProbe(bytes(image), candidate, seeds=seeds)
    target.root_instructions = {row.address: row for row in target_rows}
    source.root_instructions = {row.address: row for row in source_rows}
    target.sequence_jump, source.sequence_jump = (
        target_switch["instruction"],
        source_switch["instruction"],
    )
    inputs, differences, observations, store_observations = cases(), [], [], []
    for index, case in enumerate(inputs):
        expected = target.evaluate(case)
        if target.switch_hits != [target.sequence_jump]:
            raise ValueError("target900 sequence dispatch differs")
        if case.get("target_only"):
            actual = None
        else:
            actual = source.evaluate(case)
            if expected != actual or source.switch_hits != [source.sequence_jump]:
                differences.append(
                    dict(case_index=index, reason="actual900 prefix differs")
                )
            if target.packet != source.packet:
                differences.append(dict(case_index=index, reason="900 packet differs"))
        if "packet_selector" in case:
            selector = case["packet_selector"]
            fourth = (
                struct.pack("<f", {0: 8.0, 1: 15.0, 2: 25.0, 3: 50.0}[selector]).hex()
                if selector in range(4)
                else "a5a5a5a5"
            )
            if (
                target.packet is None
                or target.packet["count"] != 4
                or target.packet["words"][24:] != fourth
            ):
                raise ValueError(
                    "target900 selector packet differs from reviewed stores"
                )
            if case.get("target_only"):
                if target.fourth_word_writes:
                    raise ValueError("invalid target selector wrote the fourth word")
            else:
                store_observations.append(
                    dict(
                        selector=selector,
                        target=target.fourth_word_writes,
                        source=source.fourth_word_writes,
                    )
                )
        if case.get("emission_prefix"):
            math_trace = [
                address
                for address in expected["trace"]
                if address in (0x406360, 0x4063D0)
            ]
            if math_trace != ([] if case["amplitude"] == 0.0 else [0x406360, 0x4063D0]):
                raise ValueError("target900 emission math order differs")
        observations.append(
            dict(
                case_index=index,
                target=target.packet,
                source=None if actual is None else source.packet,
                target_trace=expected["trace"],
                source_trace=None if actual is None else actual["trace"],
            )
        )
    store_sites = [
        sorted({write["site"] for row in store_observations for write in row[side]})
        for side in ("target", "source")
    ]
    if store_sites[0] != [0x49CB04] or any(
        len(row["target"]) != 1 for row in store_observations
    ):
        raise ValueError("target fourth-word store differs from reviewed49CB04 join")
    source_by = {row.address: row for row in source_rows}
    store_equal = (
        len(store_sites[1]) == 1
        and all(len(row["source"]) == 1 for row in store_observations)
        and all(
            site in source_by
            and source_by[site].mnemonic == "fstp"
            and source_by[site].operands[0].size == 4
            for site in store_sites[1]
        )
    )

    def literal_producer(instructions, writes):
        if len(writes) != 1:
            return None
        row = instructions.get(writes[0]["producer"])
        if row is None or row.mnemonic != "fld":
            return None
        operand = row.operands[0]
        if (
            operand.type != graphs.x.X86_OP_MEM
            or operand.size != 4
            or operand.mem.base
            or operand.mem.index
        ):
            return None
        return operand.mem.disp

    producer_addresses = [
        [
            literal_producer(probe.root_instructions, row[side])
            for row in store_observations
        ]
        for side, probe in (("target", target), ("source", source))
    ]
    if producer_addresses[0] != [0x6C2874, 0x6C3EA0, 0x6C3B3C, 0x6C3D74]:
        raise ValueError(
            "target fourth-word producers differ from reviewed float literals"
        )
    producers_equal = producer_addresses[0] == producer_addresses[1]
    return dict(
        schema="th105-reimu-900-flow-v2",
        result="equal_scoped_900_flow"
        if all(per_mode)
        and combined_equal
        and store_equal
        and producers_equal
        and not differences
        else "rejected",
        target_sha256=facts["target_sha256"],
        object_sha256=hashlib.sha256(path.read_bytes()).hexdigest(),
        candidate_sha256=hashlib.sha256(candidate).hexdigest(),
        build_provenance_verified=False,
        case_count=len(inputs),
        compared_prefixes=sum(not case.get("target_only", False) for case in inputs),
        input_sha256=hashlib.sha256(
            json.dumps(inputs, sort_keys=True).encode()
        ).hexdigest(),
        inputs=inputs,
        runtime_differences=differences,
        packet_observations=observations,
        fourth_word_store_observations=store_observations,
        fourth_word_store_sites=store_sites,
        shared_fourth_word_fstp_equal=store_equal,
        direct_float_literal_producers_equal=producers_equal,
        fourth_word_literal_producers=producer_addresses,
        per_mode_call_graph_equal=per_mode,
        combined_call_graph_equal=combined_equal,
        combined_call_counts=[len(graph) - 5 for graph in combined],
        target_switch=target_switch,
        source_switch=source_switch,
        reviewed_selector_switches=nested,
        combined_graphs=dict(target=combined[0], source=combined[1]),
        lookup_initialization=lookup,
        support_sha256={
            name: hashlib.sha256((ROOT / name).read_bytes()).hexdigest()
            for name in (
                "scripts/audit-reimu-object-900-flow.py",
                "scripts/audit-reimu-object-901-flow.py",
                "scripts/audit-reimu-object-selector-families.py",
                "scripts/audit-reimu-object-scalar-actions.py",
                "scripts/audit-reimu-object-entry-calls.py",
                "scripts/audit-reimu-object-update-target.py",
                "scripts/audit-giant-action-owners.py",
                "scripts/compare-giant-action-switches.py",
                "scripts/map-giant-action-switches.py",
                "scripts/iku_native_math.py",
                "scripts/compare-function.py",
                "src/characters/ReimuObjectActionStateStaging.cpp",
                "src/characters/ReimuObjectActionStateStaging.hpp",
            )
        },
        scope="ten actual900 prefixes including four valid-selector stores and their preceding root floating operations, two target-only unwritten-word observations and four/joint conditional normal-return call/RET projections; observed shared FSTP/direct float producers do not prove predicates, other inputs, returning-World effects or exact bytes",
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
                    "support_sha256",
                    "reviewed_selector_switches",
                    "packet_observations",
                    "fourth_word_store_observations",
                )
            },
            indent=2,
        )
    )
    return int(report["result"] != "equal_scoped_900_flow")


if __name__ == "__main__":
    raise SystemExit(main())
