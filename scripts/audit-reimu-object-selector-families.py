#!/usr/bin/env python3
"""Compare selector-owned call sites; never return an opaque world call.

Actual target/source execution identifies each selector table and first world
frontier. The subsequent static graph is explicitly conditional on normal ABI
returns. --action bounds the report; the default checks all four families.
Physical site partitions and payload prefixes do not prove exact bytes.
"""

from __future__ import annotations

import argparse
from collections import Counter
import hashlib
import importlib.util
import json
from pathlib import Path
import struct
import sys

import capstone
from capstone import x86_const as x
from unicorn import x86_const as u
import pefile

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
spec = importlib.util.spec_from_file_location(
    "selector_native", ROOT / "scripts/audit-reimu-object-scalar-actions.py"
)
native = importlib.util.module_from_spec(spec)
spec.loader.exec_module(native)

ACTIONS = {
    905: (0x49EB9C, 0x49F275),
    906: (0x49F275, 0x49FB74),
    907: (0x49FB74, 0x4A051D),
    908: (0x4A051D, 0x4A13EF),
}


def decode(data, address):
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    decoder.detail = True
    rows = list(decoder.disasm(data, address))
    if sum(row.size for row in rows) != len(data):
        raise ValueError("source instruction stream is not completely decoded")
    return rows


def selector_switches(rows, read):
    """Recognize MOV-global/CMP3/JA/JMP, including flag-preserving x87 stores."""
    result = {}
    for index, load in enumerate(rows[:-3]):
        if not (
            load.mnemonic == "mov"
            and len(load.operands) == 2
            and load.operands[0].type == x.X86_OP_REG
            and load.operands[0].size == 4
            and load.operands[1].type == x.X86_OP_MEM
            and not load.operands[1].mem.base
            and not load.operands[1].mem.index
            and load.operands[1].size == 4
            and load.operands[1].mem.disp == 0x6FA894
        ):
            continue
        register = load.operands[0].reg
        compare = rows[index + 1]
        cursor = index + 2
        while cursor < len(rows) and rows[cursor].mnemonic in (
            "fld",
            "fldz",
            "fld1",
            "fst",
            "fstp",
        ):
            cursor += 1
        if cursor + 1 >= len(rows):
            continue
        guard, jump = rows[cursor : cursor + 2]
        if not (
            compare.mnemonic == "cmp"
            and compare.operands[0].type == x.X86_OP_REG
            and compare.operands[0].reg == register
            and compare.operands[1].type == x.X86_OP_IMM
            and compare.operands[1].imm == 3
            and guard.mnemonic == "ja"
            and guard.operands[0].type == x.X86_OP_IMM
            and jump.mnemonic == "jmp"
            and jump.operands[0].type == x.X86_OP_MEM
            and not jump.operands[0].mem.base
            and jump.operands[0].mem.index == register
            and jump.operands[0].mem.scale == 4
        ):
            continue
        table = jump.operands[0].mem.disp
        destinations = struct.unpack("<4I", read(table, 16))
        result[jump.address] = dict(
            instruction=jump.address,
            load=load.address,
            guard=guard.address,
            table=table,
            destinations=list(destinations),
        )
    return result


def jump_destinations(row, switches):
    if row.operands[0].type == x.X86_OP_IMM:
        return [row.operands[0].imm]
    if row.address in switches:
        return switches[row.address]["destinations"]
    raise ValueError("unreviewed indirect jump after selector dispatch")


def closure(rows, start, switches=None):
    switches = switches or {}
    pending, visited = [start], set()
    while pending:
        address = pending.pop()
        if address in visited:
            continue
        if address not in rows:
            raise ValueError(f"selector edge leaves decoded code at {address:#x}")
        visited.add(address)
        row = rows[address]
        if row.group(capstone.CS_GRP_RET):
            continue
        if row.group(capstone.CS_GRP_JUMP):
            pending.extend(jump_destinations(row, switches))
            if row.mnemonic == "jmp":
                continue
        # A call edge models only the conditional normal-return continuation.
        pending.append(address + row.size)
    return visited


def partition(rows, switch, switches=None):
    by = {row.address: row for row in rows}
    families = [closure(by, address, switches) for address in switch["destinations"]]
    shared = set.intersection(*families)

    def calls(addresses):
        result = []
        for address in sorted(addresses):
            row = by[address]
            if row.group(capstone.CS_GRP_CALL):
                if row.operands[0].type != x.X86_OP_IMM:
                    raise ValueError("unreviewed indirect call after selector dispatch")
                result.append(dict(site=address, target=row.operands[0].imm))
        return result

    return dict(
        switch=switch,
        shared_calls=calls(shared),
        families=[
            dict(mode=mode, calls=calls(addresses - shared))
            for mode, addresses in enumerate(families)
        ],
    )


def signature(part):
    def counts(calls):
        return sorted(Counter(row["target"] for row in calls).items())

    return counts(part["shared_calls"]), [
        counts(row["calls"]) for row in part["families"]
    ]


def call_graph(rows, part, mode, first_world, switches=None):
    """Project conditional normal-return flow onto actual call sites and RET."""
    by = {row.address: row for row in rows}
    shared = {row["site"] for row in part["shared_calls"]}
    calls = part["shared_calls"] + part["families"][mode]["calls"]
    sites = {row["site"] for row in calls}

    def frontier(start):
        pending, seen, result = [start], set(), set()
        while pending:
            address = pending.pop()
            if address in seen:
                continue
            seen.add(address)
            if address in sites:
                result.add(str(address))
                continue
            row = by[address]
            if row.group(capstone.CS_GRP_RET):
                result.add("return")
                continue
            if row.group(capstone.CS_GRP_JUMP):
                pending.extend(jump_destinations(row, switches or {}))
                if row.mnemonic == "jmp":
                    continue
            pending.append(address + row.size)
        return sorted(result)

    graph = {
        "entry": dict(
            color="entry", successors=frontier(part["switch"]["destinations"][mode])
        ),
        "return": dict(color="return", successors=[]),
    }
    for row in calls:
        site = row["site"]
        color = ("shared" if site in shared else "private") + f":{row['target']:#x}"
        if site == first_world:
            color += ":first_world"
        graph[str(site)] = dict(color=color, successors=frontier(site + by[site].size))
    return graph


def combine_call_graphs(graphs):
    """Preserve physical sharing across an ordered family of call projections.

    A call shared by only some entries must stay one node. Independent graph
    bijections can otherwise accept both clones and a wrong sharing subset.
    """
    result = {"return": dict(color="return", successors=[])}
    membership = {}
    for mode, graph in enumerate(graphs):
        if graph.get("return") != dict(color="return", successors=[]):
            raise ValueError("unreviewed projected return node")
        if "entry" not in graph:
            raise ValueError("missing projected entry node")
        if any(
            next_node not in graph
            for row in graph.values()
            for next_node in row["successors"]
        ):
            raise ValueError("projected edge leaves its call graph")
        result[f"entry:{mode}"] = dict(
            color=f"entry:{mode}", successors=sorted(set(graph["entry"]["successors"]))
        )
        for key, row in graph.items():
            if key in ("entry", "return"):
                continue
            if key.startswith("entry:"):
                raise ValueError("call node conflicts with a family entry")
            normalized = dict(
                color=row["color"], successors=sorted(set(row["successors"]))
            )
            if key in result and result[key] != normalized:
                raise ValueError("inconsistent projection of a shared physical call")
            result[key] = normalized
            membership.setdefault(key, []).append(mode)
    for key, modes in membership.items():
        result[key]["color"] += ":modes=" + ",".join(map(str, modes))
    return result


def same_call_graph(target, source):
    """Small labeled-graph bijection; duplicate callees need not share PCs."""
    if len(target) != len(source):
        return False
    choices = {
        key: [
            other
            for other in source
            if target[key]["color"] == source[other]["color"]
            and len(target[key]["successors"]) == len(source[other]["successors"])
        ]
        for key in target
    }
    if any(not values for values in choices.values()):
        return False
    order = sorted(target, key=lambda key: len(choices[key]))

    def visit(index, assigned, used):
        if index == len(order):
            return True
        key = order[index]
        for other in choices[key]:
            if other in used:
                continue
            proposed = {**assigned, key: other}
            if any(
                (b in target[a]["successors"])
                != (proposed[b] in source[proposed[a]]["successors"])
                for a in proposed
                for b in proposed
            ):
                continue
            if visit(index + 1, proposed, used | {other}):
                return True
        return False

    return visit(0, {}, set())


class ObservedProbe(native.Probe):
    def evaluate(self, case):
        self.selector_events = []
        self.frontier = None
        return super().evaluate(case)

    def instruction(self, engine, address, size, unused):
        if address in self.selector_map:
            self.selector_events.append(address)
        if address == native.SPAWN:
            stack = engine.reg_read(u.UC_X86_REG_ESP)
            self.frontier = struct.unpack("<I", engine.mem_read(stack, 4))[0] - 5
        super().instruction(engine, address, size, unused)


def audit(path, selected_actions=None):
    selected_actions = (
        tuple(ACTIONS) if selected_actions is None else tuple(selected_actions)
    )
    if (
        not selected_actions
        or len(set(selected_actions)) != len(selected_actions)
        or any(action not in ACTIONS for action in selected_actions)
    ):
        raise ValueError("select distinct supported action families")
    facts = native.facts.audit()
    candidate = native.export(path)
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    decoder.detail = True
    complete = list(decoder.disasm(candidate, native.S))
    tables = [
        row.operands[0].mem.disp
        for row in complete
        if row.mnemonic == "jmp"
        and row.operands[0].type == x.X86_OP_MEM
        and not row.operands[0].mem.base
        and row.operands[0].mem.index
        and row.operands[0].mem.scale == 4
        and row.address < row.operands[0].mem.disp < native.S + len(candidate)
    ]
    if not tables:
        raise ValueError("missing source switch metadata boundary")
    metadata = min(tables)
    source_rows = decode(candidate[: metadata - native.S], native.S)

    def read_source(address, size):
        offset = address - native.S
        if not metadata <= address <= address + size <= native.S + len(candidate):
            raise ValueError("source selector table leaves reviewed metadata")
        return candidate[offset : offset + size]

    source_switches = selector_switches(source_rows, read_source)
    target_rows = [
        row
        for lo, hi in native.facts.RANGES
        for row in native.facts.decode(native.c.target_bytes(lo, hi - lo), lo)
    ]
    target_switches = selector_switches(target_rows, native.c.target_bytes)
    image = bytearray(
        pefile.PE(str(ROOT / "resources/th105.exe")).get_memory_mapped_image()
    )
    math = native.load("selector_math", "scripts/iku_native_math.py")
    table, receipt = math.lookup_fixture(native.c)
    image[0x2FE8B0 : 0x2FE8B0 + len(table)] = table
    seeds = native.seed_fixtures(bytes(image))
    target = ObservedProbe(bytes(image), seeds=seeds)
    source = ObservedProbe(bytes(image), candidate, seeds=seeds)
    target.selector_map, source.selector_map = target_switches, source_switches
    actions, inputs = [], []
    for action in selected_actions:
        lo, hi = ACTIONS[action]
        selected = [
            value for address, value in target_switches.items() if lo <= address < hi
        ]
        if len(selected) != 1:
            raise ValueError("target selector inventory differs")
        target_switch = selected[0]
        source_sites, first_calls = set(), []
        for mode in range(4):
            case = dict(
                action=action,
                seq=0,
                state=1,
                phase=0,
                counter=60 if action == 908 else 0,
                timer=1,
                owner_value174=8000,
                owner_word738=action - 905,
                speed_word=0,
                fade_word=0,
                match_identifier=mode,
                cw=0x27F,
            )
            inputs.append(case)
            expected, actual = target.evaluate(case), source.evaluate(case)
            if expected != actual or expected["endpoint"]["kind"] != "spawn":
                raise ValueError(
                    f"actual first-world prefix differs for {action}/{mode}"
                )
            if (
                target.selector_events != [target_switch["instruction"]]
                or len(source.selector_events) != 1
            ):
                raise ValueError(
                    f"missing unique reviewed source selector jump for {action}/{mode}"
                )
            source_sites.update(source.selector_events)
            first_calls.append(
                dict(mode=mode, target=target.frontier, source=source.frontier)
            )
        if len(source_sites) != 1:
            raise ValueError("source changes selector dispatch across modes")
        source_switch = source_switches[next(iter(source_sites))]
        a, b = (
            partition(target_rows, target_switch),
            partition(source_rows, source_switch),
        )
        if signature(a) != signature(b):
            raise ValueError(f"selector call-site partition differs for action{action}")
        if (
            len({row["target"] for row in first_calls}) != 4
            or len({row["source"] for row in first_calls}) != 4
        ):
            raise ValueError("selector first-world calls are physically merged")
        graphs = []
        for mode, frontier in enumerate(first_calls):
            target_graph = call_graph(target_rows, a, mode, frontier["target"])
            source_graph = call_graph(source_rows, b, mode, frontier["source"])
            if not same_call_graph(target_graph, source_graph):
                raise ValueError(
                    f"selector normal-return call graph differs for action{action}/mode{mode}"
                )
            graphs.append(dict(mode=mode, target=target_graph, source=source_graph))
        actions.append(
            dict(action=action, target=a, source=b, first_world_calls=first_calls)
        )
        actions[-1]["call_graphs"] = graphs
    return dict(
        schema="th105-reimu-selector-sites-v1",
        result="equal_scoped_partitions",
        target_sha256=facts["target_sha256"],
        object_sha256=hashlib.sha256(path.read_bytes()).hexdigest(),
        candidate_sha256=hashlib.sha256(candidate).hexdigest(),
        case_count=len(inputs),
        selected_actions=list(selected_actions),
        input_sha256=hashlib.sha256(
            json.dumps(inputs, sort_keys=True).encode()
        ).hexdigest(),
        source_metadata_start=metadata - native.S,
        build_provenance_verified=False,
        support_sha256={
            name: hashlib.sha256((ROOT / name).read_bytes()).hexdigest()
            for name in (
                "scripts/audit-reimu-object-selector-families.py",
                "scripts/audit-reimu-object-scalar-actions.py",
                "scripts/audit-reimu-object-update-target.py",
                "scripts/compare-function.py",
                "scripts/iku_native_math.py",
                "src/characters/ReimuObjectActionStateStaging.cpp",
                "src/characters/ReimuObjectActionStateStaging.hpp",
            )
        },
        actions=actions,
        lookup_initialization=receipt,
        scope="actual first-world prefixes plus selector-owned call sites/normal-return call graphs; no returning-world execution, predicate equivalence, full-root or exact claim",
    )


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("object", type=Path)
    parser.add_argument("--output", type=Path)
    parser.add_argument(
        "--action", type=int, choices=tuple(ACTIONS), action="append",
        help="Audit these action families; the default checks all four.",
    )
    args = parser.parse_args()
    try:
        report = audit(args.object, args.action)
    except (ValueError, OSError) as error:
        report = dict(
            result="rejected", reason=str(error),
            selected_actions=list(ACTIONS) if args.action is None else args.action,
        )
    if args.output:
        args.output.parent.mkdir(parents=True, exist_ok=True)
        args.output.write_text(json.dumps(report, indent=2) + "\n")
    print(
        json.dumps(
            {
                key: value
                for key, value in report.items()
                if key not in ("actions", "lookup_initialization")
            },
            indent=2,
        )
    )
    return int(report["result"] != "equal_scoped_partitions")


if __name__ == "__main__":
    raise SystemExit(main())
