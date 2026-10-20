#!/usr/bin/env python3
"""Audit812 prefixes and physical call sharing, without returning opaque calls.

Indirect identities are observed only with the admitted original-vtable inputs.
The static call projections are conditional on normal ABI returns and do not
prove predicates, loop bounds, arbitrary aliases or full-root byte equality.
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

import capstone
import pefile
from unicorn import x86_const as u

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location(
    "flow812_world", ROOT / "scripts/audit-reimu-object-world-sharing.py"
)
world = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(world)
graphs, native, x = world.graphs, world.native, world.x


def cases():
    yield from (case for case in native.sequence_cases() if case["action"] == 812)
    for seq, alpha, terminal, counter, facing, cw in itertools.product(
        (3, 4),
        (0, 14, 15, 16, 254, 255),
        (False, True),
        (0, 1),
        (-128, -1, 0, 1, 127),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=812,
            seq=seq,
            alpha=alpha,
            terminal=terminal,
            counter=counter,
            facing=facing,
            cw=cw,
            cohort="812-fade-finish",
        )
    # Exercise both812 transitions and the810 side of the shared sequence1 site.
    for action, seq, facing, cw in itertools.product(
        (810, 812),
        (1, 2),
        (-128, -1, 0, 1, 127),
        (0x27F, 0x37F),
    ):
        if action == 810 and seq == 2:
            continue
        yield dict(
            action=action,
            seq=seq,
            phase=1,
            counter=1,
            speed=3.0,
            facing=facing,
            cw=cw,
            cohort="812-transition-sharing",
        )


class SiteProbe(native.Probe):
    def evaluate(self, case):
        self.call_sites, self.indirect_events = set(), []
        return super().evaluate(case)

    def instruction(self, engine, address, size, unused):
        row = self.root_calls.get(address)
        if row is not None:
            self.call_sites.add(address)
            if row.operands[0].type != x.X86_OP_IMM:
                operand = row.operands[0]
                if operand.type != x.X86_OP_REG:
                    raise ValueError("unreviewed indirect812 CALL operand")
                register = getattr(u, "UC_X86_REG_" + row.reg_name(operand.reg).upper())
                callee = engine.reg_read(register)
                receiver = engine.reg_read(u.UC_X86_REG_ECX)
                if receiver != native.OWNER:
                    raise ValueError("indirect812 receiver is not the admitted actor")
                vtable = struct.unpack("<I", engine.mem_read(receiver, 4))[0]
                if vtable != 0x6C40A4:
                    raise ValueError("original812 vtable differs")
                slots = [
                    slot
                    for slot in (0x0C, 0x14)
                    if struct.unpack("<I", engine.mem_read(vtable + slot, 4))[0]
                    == callee
                ]
                if len(slots) != 1:
                    raise ValueError(
                        "indirect812 callee is not a reviewed original slot"
                    )
                slot = slots[0]
                stack = engine.reg_read(u.UC_X86_REG_ESP)
                words = (
                    []
                    if slot == 0x14
                    else list(struct.unpack("<I", engine.mem_read(stack, 4)))
                )
                if slot == 0x0C and words != [3]:
                    raise ValueError("812 select-sequence argument differs")
                identity = (callee, slot)
                if (
                    address in self.indirect_ids
                    and self.indirect_ids[address] != identity
                ):
                    raise ValueError(
                        "812 indirect site has multiple admitted identities"
                    )
                self.indirect_ids[address] = identity
                self.indirect_events.append([callee, slot, receiver, words])
        super().instruction(engine, address, size, unused)


def call_partition(rows, switch, switches, identities):
    """Resolve indirect labels from actual admitted prefixes, never CALL operands."""
    by = {row.address: row for row in rows}
    families = [
        graphs.closure(by, address, switches) for address in switch["destinations"]
    ]
    shared = set.intersection(*families)

    def calls(addresses):
        result = []
        for address in sorted(addresses):
            row = by[address]
            if row.group(capstone.CS_GRP_CALL):
                target = (
                    row.operands[0].imm
                    if row.operands[0].type == x.X86_OP_IMM
                    else identities[address][0]
                )
                result.append(dict(site=address, target=target))
        return result

    return dict(
        switch=switch,
        shared_calls=calls(shared),
        families=[
            dict(mode=mode, calls=calls(addresses - shared))
            for mode, addresses in enumerate(families)
        ],
    )


def audit(path):
    facts = native.facts.audit()
    mapper = native.m
    root = mapper.load_target_mapper().select_root(
        tomllib.loads((ROOT / "config/giant-action-switches.toml").read_text()),
        "reimu-object-vslot28",
    )
    tm = mapper.load_target_mapper()
    target_map = tm.map_root(
        tm.PeImage(ROOT / "resources/th105.exe"),
        tm.load_function_rows(ROOT / "config/functions.csv"),
        root,
    )
    obj = mapper.CoffObject(path, symbol_base=native.SYMBOL)
    source_map = mapper.build_candidate_map(obj, root)
    code = native.export(path)
    rows = [
        [
            row
            for lo, hi in native.facts.RANGES
            for row in native.facts.decode(native.c.target_bytes(lo, hi - lo), lo)
        ],
        graphs.decode(code[: source_map["metadata_start"]], native.S),
    ]
    switches = [
        {
            int(row["instruction"], 0): dict(
                destinations=[int(address, 0) for address in row["destinations"]]
            )
            for row in facts["switches"]
        },
        world.reviewed_source_switches(rows[1], code, source_map["metadata_start"]),
    ]
    entries = []
    for group in target_map["regions"][0]["groups"]:
        ids = group["cases"]
        offsets = {source_map["regions"][0]["mapping"][case] for case in ids}
        if len(offsets) != 1:
            raise ValueError("outer action aliases differ")
        entries.append(
            dict(
                name="default" if len(ids) > 20 else "/".join(map(str, ids)),
                cases=ids,
                target=group["destination"],
                source=native.S + offsets.pop(),
            )
        )
    if len(entries) != 42:
        raise ValueError("outer entry inventory differs")
    views = [
        world.census(side_rows, side_switches, entries, side, base)
        for side_rows, side_switches, side, base in zip(
            rows, switches, ("target", "source"), (native.A, native.S)
        )
    ]
    action = next(entry for entry in entries if entry["name"] == "812")
    closures = [
        graphs.closure({r.address: r for r in side_rows}, action[side], side_switches)
        for side_rows, side_switches, side in zip(rows, switches, ("target", "source"))
    ]
    sequence_switches = []
    for addresses, side_switches in zip(closures, switches):
        matches = [
            (pc, switch) for pc, switch in side_switches.items() if pc in addresses
        ]
        if len(matches) != 1 or len(matches[0][1]["destinations"]) != 5:
            raise ValueError("expected one five-entry812 sequence switch")
        sequence_switches.append(dict(matches[0][1], instruction=matches[0][0]))
    if sequence_switches[0]["instruction"] != 0x497E9A:
        raise ValueError("target812 sequence switch differs")
    image = bytearray(
        pefile.PE(str(ROOT / "resources/th105.exe")).get_memory_mapped_image()
    )
    math = native.load("flow812_math", "scripts/iku_native_math.py")
    table, lookup = math.lookup_fixture(native.c)
    image[0x2FE8B0 : 0x2FE8B0 + len(table)] = table
    probes = [SiteProbe(bytes(image)), SiteProbe(bytes(image), code)]
    for probe, side_rows in zip(probes, rows):
        probe.root_calls = {
            r.address: r for r in side_rows if r.group(capstone.CS_GRP_CALL)
        }
        probe.indirect_ids = {}
    inputs = list(cases())
    differences, indirect_differences, endpoints = [], [], Counter()
    observed = [set(), set()]
    for index, case in enumerate(inputs):
        outputs = [probe.evaluate(case) for probe in probes]
        if outputs[0] != outputs[1]:
            differences.append(
                dict(index=index, input=case, target=outputs[0], source=outputs[1])
            )
        if probes[0].indirect_events != probes[1].indirect_events:
            indirect_differences.append(dict(index=index, input=case))
        endpoints[outputs[0]["endpoint"]["kind"]] += 1
        if case["action"] == 812:
            for sites, probe in zip(observed, probes):
                sites.update(probe.call_sites)
    indirect_memberships, animation_memberships = [], []
    observed_identities = []
    for view, addresses, probe, sites in zip(views, closures, probes, observed):
        indirect = {
            pc: row
            for pc, row in view["calls"].items()
            if pc in addresses and row["target"] is None
        }
        if (
            not indirect.keys() <= sites
            or not indirect.keys() <= probe.indirect_ids.keys()
        ):
            raise ValueError("input matrix does not execute every812 indirect site")
        indirect_memberships.append(
            Counter(
                (probe.indirect_ids[pc][1], tuple(row["entries"]))
                for pc, row in indirect.items()
            )
        )
        animation_memberships.append(
            Counter(
                tuple(row["entries"])
                for pc, row in view["calls"].items()
                if pc in addresses and row["target"] == 0x4351C0
            )
        )
        observed_identities.append(
            [
                dict(
                    site=pc,
                    callee=probe.indirect_ids[pc][0],
                    slot=probe.indirect_ids[pc][1],
                    entries=row["entries"],
                )
                for pc, row in sorted(indirect.items())
            ]
        )
    if set(row["site"] for row in observed_identities[0]) != {
        0x4976E3,
        0x497F06,
        0x49826B,
    }:
        raise ValueError("target812 indirect inventory differs")
    expected_indirect = Counter(
        {(0x14, ("812",)): 1, (0x0C, ("812",)): 1, (0x0C, ("810", "812")): 1}
    )
    if indirect_memberships[0] != expected_indirect or animation_memberships[
        0
    ] != Counter({("812",): 1}):
        raise ValueError("target812 physical memberships differ")
    parts = [
        call_partition(side_rows, switch, side_switches, probe.indirect_ids)
        for side_rows, switch, side_switches, probe in zip(
            rows, sequence_switches, switches, probes
        )
    ]
    projected = [
        [
            graphs.call_graph(side_rows, part, mode, None, side_switches)
            for mode in range(5)
        ]
        for side_rows, part, side_switches in zip(rows, parts, switches)
    ]
    per_mode = [
        graphs.same_call_graph(projected[0][mode], projected[1][mode])
        for mode in range(5)
    ]
    joint = graphs.same_call_graph(
        *(graphs.combine_call_graphs(side) for side in projected)
    )
    indirect_equal = indirect_memberships[0] == indirect_memberships[1]
    animation_equal = animation_memberships[0] == animation_memberships[1]
    accepted = (
        not differences
        and not indirect_differences
        and indirect_equal
        and animation_equal
        and all(per_mode)
        and joint
    )
    return dict(
        schema="th105-reimu-object-812-flow-v1",
        result="equal_scoped_812_flow" if accepted else "rejected",
        target_sha256=facts["target_sha256"],
        object_sha256=hashlib.sha256(path.read_bytes()).hexdigest(),
        candidate_sha256=hashlib.sha256(code).hexdigest(),
        build_provenance_verified=False,
        case_count=len(inputs),
        input_sha256=hashlib.sha256(
            json.dumps(inputs, sort_keys=True).encode()
        ).hexdigest(),
        differences=differences,
        indirect_event_differences=indirect_differences,
        endpoints=dict(endpoints),
        indirect_partition_equal=indirect_equal,
        animation_partition_equal=animation_equal,
        indirect_sites=observed_identities,
        per_sequence_call_graph_equal=per_mode,
        joint_call_graph_equal=joint,
        joint_graph_call_counts=[
            len(graphs.combine_call_graphs(side)) - 6 for side in projected
        ],
        sequence_switches=sequence_switches,
        call_partitions=parts,
        lookup_initialization=lookup,
        root_census=[
            dict(
                reachable=view["reachable_instructions"],
                direct=sum(row["target"] is not None for row in view["calls"].values()),
                indirect=sum(row["target"] is None for row in view["calls"].values()),
                returns=len(view["returns"]),
            )
            for view in views
        ],
        support_sha256={
            name: hashlib.sha256((ROOT / name).read_bytes()).hexdigest()
            for name in (
                "scripts/audit-reimu-object-812-flow.py",
                "scripts/audit-reimu-object-world-sharing.py",
                "scripts/audit-reimu-object-selector-families.py",
                "scripts/audit-reimu-object-scalar-actions.py",
                "scripts/audit-reimu-object-update-target.py",
                "scripts/iku_native_math.py",
                "src/characters/ReimuObjectActionStateStaging.cpp",
                "src/characters/ReimuObjectActionStateStaging.hpp",
            )
        },
        scope="admitted actual812 prefixes and original-vtable call identities, physical812 memberships, five sequence/joint call projections conditional on normal ABI returns; no opaque returning execution, predicate/loop-bound, arbitrary-vtable or canonical claim",
    )


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("object", type=Path)
    parser.add_argument("--output", type=Path)
    args = parser.parse_args()
    try:
        result = audit(args.object)
    except (ValueError, KeyError) as exc:
        result = dict(result="rejected", reason=str(exc))
    if args.output:
        args.output.parent.mkdir(parents=True, exist_ok=True)
        args.output.write_text(json.dumps(result, indent=2) + "\n")
        print(
            json.dumps(
                {
                    key: value
                    for key, value in result.items()
                    if key
                    in (
                        "result",
                        "reason",
                        "case_count",
                        "indirect_partition_equal",
                        "animation_partition_equal",
                        "joint_call_graph_equal",
                    )
                }
            )
        )
    else:
        print(json.dumps(result, indent=2))
    return 0 if result["result"] == "equal_scoped_812_flow" else 1


if __name__ == "__main__":
    raise SystemExit(main())
