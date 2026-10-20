#!/usr/bin/env python3
"""Audit physical World sharing across42 action entries and903 selector loops.

Reachability and call projections assume normal ABI returns. Actual prefixes
stop at original opaque entries. These checks do not prove branch predicates,
loop bounds, indirect callee identity, returning World effects or exact bytes.
"""

from __future__ import annotations

import argparse
from collections import Counter
import hashlib
import importlib.util
import json
from pathlib import Path
import struct
import tomllib

import pefile
from unicorn import x86_const as u

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location(
    "world_sharing_graphs", ROOT / "scripts/audit-reimu-object-selector-families.py"
)
graphs = importlib.util.module_from_spec(spec)
spec.loader.exec_module(graphs)
native, x = graphs.native, graphs.x
WORLD = 0x64CCB0
SHARED_ACTIONS = ["822", "869", "900", "901", "902", "903", "908"]


def index_clobbered(row, register):
    names = {
        x.X86_REG_EAX: ("EAX", "AX", "AL", "AH"),
        x.X86_REG_EBX: ("EBX", "BX", "BL", "BH"),
        x.X86_REG_ECX: ("ECX", "CX", "CL", "CH"),
        x.X86_REG_EDX: ("EDX", "DX", "DL", "DH"),
        x.X86_REG_ESI: ("ESI", "SI"),
        x.X86_REG_EDI: ("EDI", "DI"),
        x.X86_REG_EBP: ("EBP", "BP"),
        x.X86_REG_ESP: ("ESP", "SP"),
    }
    if register not in names:
        raise ValueError("unreviewed source switch index register")
    aliases = {getattr(x, "X86_REG_" + name) for name in names[register]}
    return bool(aliases.intersection(row.regs_access()[1]))


def reviewed_source_switches(rows, code, metadata):
    """Accept bounded unsigned guards and metadata-owned destination/index tables."""

    def read(address, size):
        if not native.S + metadata <= address <= address + size <= native.S + len(code):
            raise ValueError("source switch table leaves reviewed metadata")
        return code[address - native.S : address - native.S + size]

    result = {}
    for position, jump in enumerate(rows):
        if jump.mnemonic != "jmp" or jump.operands[0].type == x.X86_OP_IMM:
            continue
        op = jump.operands[0]
        if not (
            op.type == x.X86_OP_MEM
            and not op.mem.base
            and op.mem.index
            and op.mem.scale == 4
        ):
            raise ValueError("unreviewed source indirect jump")
        guards = [
            index
            for index in range(max(0, position - 8), position)
            if rows[index].mnemonic == "ja"
        ]
        if not guards:
            raise ValueError("missing source unsigned switch guard")
        guard_position = guards[-1]
        compares = [
            index
            for index in range(max(0, guard_position - 4), guard_position)
            if rows[index].mnemonic == "cmp"
        ]
        if not compares:
            raise ValueError("missing source switch bound")
        bound_position = compares[-1]
        bound = rows[bound_position]
        if (
            bound.operands[0].type != x.X86_OP_REG
            or bound.operands[1].type != x.X86_OP_IMM
        ):
            raise ValueError("unreviewed source switch bound operands")
        register, maximum = bound.operands[0].reg, bound.operands[1].imm
        if not 0 <= maximum <= 255:
            raise ValueError("source switch bound exceeds reviewed range")
        for row in rows[bound_position + 1 : guard_position]:
            writes = row.regs_access()[1]
            if (
                row.group(graphs.capstone.CS_GRP_JUMP)
                or row.group(graphs.capstone.CS_GRP_CALL)
                or index_clobbered(row, register)
                or x.X86_REG_EFLAGS in writes
            ):
                raise ValueError("source bound/flags clobbered before guard")
        sparse = [
            row
            for row in rows[guard_position + 1 : position]
            if row.mnemonic == "movzx"
            and row.operands[0].type == x.X86_OP_REG
            and row.operands[0].reg == op.mem.index
            and row.operands[1].type == x.X86_OP_MEM
            and row.operands[1].size == 1
        ]
        if any(
            row.group(graphs.capstone.CS_GRP_CALL)
            or row.group(graphs.capstone.CS_GRP_JUMP)
            for row in rows[guard_position + 1 : position]
        ):
            raise ValueError("unreviewed control transfer after source switch guard")
        if sparse:
            if len(sparse) != 1:
                raise ValueError("ambiguous source sparse index")
            load = sparse[0]
            if load.operands[1].mem.base != register or load.operands[1].mem.index:
                raise ValueError("sparse index does not use bounded register")
            index_table = load.operands[1].mem.disp
            indices = read(index_table, maximum + 1)
            count = max(indices) + 1
            if set(indices) != set(range(count)):
                raise ValueError("source sparse index coverage differs")
            middle = rows[guard_position + 1 : position]
            before, after = (
                middle[: middle.index(load)],
                middle[middle.index(load) + 1 :],
            )
            if any(index_clobbered(row, register) for row in before) or any(
                index_clobbered(row, op.mem.index) for row in after
            ):
                raise ValueError("source sparse index register clobbered")
        else:
            index_table, count = None, maximum + 1
            if op.mem.index != register or any(
                index_clobbered(row, register)
                for row in rows[guard_position + 1 : position]
            ):
                raise ValueError("source checked index does not feed destination table")
        destinations = list(
            struct.unpack("<" + "I" * count, read(op.mem.disp, count * 4))
        )
        if any(
            not native.S <= address < native.S + metadata for address in destinations
        ):
            raise ValueError("source switch destination leaves code")
        result[jump.address] = dict(
            instruction=jump.address,
            table=op.mem.disp,
            guard=rows[guard_position].address,
            count=count,
            checked_maximum=maximum,
            index_table=index_table,
            destinations=destinations,
        )
    return result


def census(rows, switches, entries, side, start):
    by = {row.address: row for row in rows}
    root = graphs.closure(by, start, switches)
    members = {}
    for entry in entries:
        for address in graphs.closure(by, entry[side], switches):
            members.setdefault(address, []).append(entry["name"])
    calls, returns = {}, {}
    for address in root:
        row = by[address]
        if row.mnemonic == "call":
            if address not in members:
                raise ValueError("call before classified action destinations")
            direct = row.operands[0].type == x.X86_OP_IMM
            calls[address] = dict(
                kind="direct" if direct else "indirect",
                target=row.operands[0].imm if direct else None,
                operand=row.op_str,
                entries=members[address],
            )
        elif row.group(graphs.capstone.CS_GRP_RET):
            if address not in members:
                raise ValueError("RET before classified action destinations")
            returns[address] = members[address]
    return dict(reachable_instructions=len(root), calls=calls, returns=returns)


def counts(view, callee):
    return Counter(
        tuple(row["entries"])
        for row in view["calls"].values()
        if row["target"] == callee
    )


class PrefixProbe(native.Probe):
    def evaluate(self, case):
        self.frontier = None
        return super().evaluate(case)

    def instruction(self, engine, address, size, unused):
        if address == WORLD:
            stack = engine.reg_read(u.UC_X86_REG_ESP)
            caller = struct.unpack("<I", engine.mem_read(stack, 4))[0] - 5
            row = self.root_instructions.get(caller)
            if (
                row is None
                or row.mnemonic != "call"
                or row.size != 5
                or row.operands[0].type != x.X86_OP_IMM
                or row.operands[0].imm != WORLD
            ):
                raise ValueError("unreviewed903 World caller")
            self.frontier = caller
        super().instruction(engine, address, size, unused)


def selector_903(rows, code):
    image = bytearray(
        pefile.PE(str(ROOT / "resources/th105.exe")).get_memory_mapped_image()
    )
    math = native.load("world_sharing_math", "scripts/iku_native_math.py")
    table, lookup = math.lookup_fixture(native.c)
    image[0x2FE8B0 : 0x2FE8B0 + len(table)] = table
    seeds = native.seed_fixtures(bytes(image))
    probes = [
        PrefixProbe(bytes(image), seeds=seeds),
        PrefixProbe(bytes(image), code, seeds=seeds),
    ]
    for probe, instructions in zip(probes, rows):
        probe.root_instructions = {row.address: row for row in instructions}
    selected = [
        dict(case, facing=facing)
        for case in native.actions_903_905_cases()
        if case["cohort"] == "high-903-owner"
        and case["owner_action"] == 740
        and case["owner_seq"] == 6
        for facing in (-128, -1, 0, 1, 127)
    ]
    differences, callers = [], [{mode: set() for mode in range(4)} for _ in probes]
    for index, case in enumerate(selected):
        outputs = [probe.evaluate(case) for probe in probes]
        if outputs[0] != outputs[1]:
            differences.append(dict(case_index=index, case=case))
        expected_action = 904 if case["match_identifier"] in (1, 2, 3) else 903
        if (
            outputs[0]["endpoint"]["kind"] != "spawn"
            or outputs[0]["endpoint"]["arguments"][0] != expected_action
        ):
            raise ValueError("unexpected target903 first request")
        if case["match_identifier"] in range(4):
            for probe, observed in zip(probes, callers):
                observed[case["match_identifier"]].add(probe.frontier)
    if any(len(sites) != 1 for observed in callers for sites in observed.values()):
        raise ValueError("nonunique903 first World caller for selector")
    destinations = [
        [next(iter(observed[mode])) for mode in range(4)] for observed in callers
    ]
    if destinations[0] != [0x499DF8, 0x49E76C, 0x49E6CC, 0x49E642]:
        raise ValueError("target903 first request sites differ")
    families = []
    for instructions, starts in zip(rows, destinations):
        part = graphs.partition(instructions, dict(destinations=starts))
        families.append(
            [graphs.call_graph(instructions, part, mode, None) for mode in range(4)]
        )
    combined = [graphs.combine_call_graphs(family) for family in families]
    return dict(
        case_count=len(selected),
        input_sha256=hashlib.sha256(
            json.dumps(selected, sort_keys=True).encode()
        ).hexdigest(),
        differences=differences,
        first_world_sites=destinations,
        per_mode_call_graph_equal=[
            graphs.same_call_graph(a, b) for a, b in zip(*families)
        ],
        joint_call_graph_equal=graphs.same_call_graph(*combined),
        joint_call_counts=[len(graph) - 5 for graph in combined],
        joint_graphs=dict(target=combined[0], source=combined[1]),
        lookup_initialization=lookup,
        scope="actual first-entry prefixes and conditional normal-return call loops; no loop-bound/predicate or returning-World proof",
    )


def retirement_prefixes(rows, code, source_shared_site):
    """Check preparations before the first opaque World on each selected route."""
    base = dict(
        seq=0,
        phase=0,
        state=1,
        counter=1,
        timer=1,
        index=1,
        owner_health=100,
        owner_value174=8000,
        mode=1000.0,
        speed_word=0,
    )
    examples = [
        dict(
            base,
            action=822,
            owner_health=-1,
            scenario="822-health",
            tail_first=False,
            words=4,
        ),
        dict(
            base,
            action=822,
            frame=1,
            frame_count=3,
            phase=1,
            scenario="822-phase",
            tail_first=False,
            words=4,
        ),
        dict(
            base,
            action=869,
            owner_action=669,
            owner_seq=2,
            scenario="869-sequence",
            tail_first=True,
            words=3,
        ),
        dict(
            base,
            action=869,
            owner_action=668,
            owner_word_7c8=0,
            scenario="869-owner",
            tail_first=True,
            words=3,
        ),
        dict(
            base,
            action=900,
            owner_value174=-1,
            scenario="900-health",
            tail_first=True,
            words=3,
        ),
        dict(
            base,
            action=900,
            seq=1,
            phase=1,
            scenario="900-phase",
            tail_first=True,
            words=3,
        ),
        *[
            dict(
                base,
                action=900,
                counter=40,
                match_identifier=mode,
                scenario=f"900-selector-{mode}",
                tail_first=True,
                words=4,
            )
            for mode in range(4)
        ],
        dict(
            base,
            action=901,
            seq=1,
            owner_value174=-1,
            scenario="901-health",
            tail_first=False,
            words=3,
        ),
        dict(
            base,
            action=901,
            seq=1,
            mode=0.0,
            y=70.0,
            vy=-1.0,
            scenario="901-exhaustion",
            tail_first=False,
            words=3,
        ),
        dict(
            base,
            action=902,
            seq=2,
            phase=1,
            scenario="902-phase",
            tail_first=True,
            words=3,
        ),
        *[
            dict(
                base,
                action=903,
                seq=mode,
                owner_value174=-1,
                scenario=f"903-health-{mode}",
                tail_first=True,
                words=3,
            )
            for mode in range(3)
        ],
        *[
            dict(
                base,
                action=908,
                seq=mode,
                scenario=f"908-sequence-{mode}",
                tail_first=True,
                words=3,
            )
            for mode in (6, 7)
        ],
    ]
    inputs = [
        dict(case, facing=facing, cw=cw)
        for case in examples
        for facing in (-128, -1, 0, 1, 127)
        for cw in (0x27F, 0x37F)
    ]
    image = bytearray(
        pefile.PE(str(ROOT / "resources/th105.exe")).get_memory_mapped_image()
    )
    math = native.load("world_retirement_math", "scripts/iku_native_math.py")
    table, lookup = math.lookup_fixture(native.c)
    image[0x2FE8B0 : 0x2FE8B0 + len(table)] = table
    seeds = native.seed_fixtures(bytes(image))
    surfaces, surface_receipt = native.surface_fixtures(bytes(image))
    probes = [
        PrefixProbe(bytes(image), seeds=seeds, surfaces=surfaces),
        PrefixProbe(bytes(image), code, seeds=seeds, surfaces=surfaces),
    ]
    for probe, instructions in zip(probes, rows):
        probe.root_instructions = {row.address: row for row in instructions}
    differences, role_differences, observations = [], [], []
    for index, case in enumerate(inputs):
        expected, actual = [probe.evaluate(case) for probe in probes]
        if (
            expected["endpoint"]["kind"] != "spawn"
            or expected["endpoint"]["arguments"][0] != case["action"]
        ):
            raise ValueError(
                f"retirement fixture did not reach expected target request: {case['scenario']}"
            )
        if expected["endpoint"]["arguments"][6] != case["words"] or (
            (probes[0].frontier == 0x499DF8) != case["tail_first"]
        ):
            raise ValueError(
                f"retirement fixture target role/count differs: {case['scenario']}"
            )
        if expected != actual:
            differences.append(dict(case_index=index, scenario=case["scenario"]))
        if (probes[1].frontier == source_shared_site) != case["tail_first"]:
            role_differences.append(dict(case_index=index, scenario=case["scenario"]))
        observations.append(
            dict(
                case_index=index,
                scenario=case["scenario"],
                target_site=probes[0].frontier,
                source_site=probes[1].frontier,
                target_arguments=expected["endpoint"]["arguments"],
                source_arguments=actual["endpoint"]["arguments"],
            )
        )
    return dict(
        case_count=len(inputs),
        input_sha256=hashlib.sha256(
            json.dumps(inputs, sort_keys=True).encode()
        ).hexdigest(),
        inputs=inputs,
        differences=differences,
        frontier_role_differences=role_differences,
        observations=observations,
        lookup_initialization=lookup,
        surface_initialization=surface_receipt,
        scope="first original World entries only;822/901 burst finals stay static normal-return evidence, with no fabricated World returns",
    )


def audit(path):
    facts = native.facts.audit()
    mapper = native.m
    obj = mapper.CoffObject(path, symbol_base=native.SYMBOL)
    target_mapper = mapper.load_target_mapper()
    root = target_mapper.select_root(
        tomllib.loads((ROOT / "config/giant-action-switches.toml").read_text()),
        "reimu-object-vslot28",
    )
    target_map = target_mapper.map_root(
        target_mapper.PeImage(ROOT / "resources/th105.exe"),
        target_mapper.load_function_rows(ROOT / "config/functions.csv"),
        root,
    )
    source_map = mapper.build_candidate_map(obj, root)
    code = native.export(path)
    target_rows = [
        row
        for lo, hi in native.facts.RANGES
        for row in native.facts.decode(native.c.target_bytes(lo, hi - lo), lo)
    ]
    source_rows = graphs.decode(code[: source_map["metadata_start"]], native.S)
    target_switches = {
        int(row["instruction"], 0): dict(
            destinations=[int(address, 0) for address in row["destinations"]]
        )
        for row in facts["switches"]
    }
    source_switches = reviewed_source_switches(
        source_rows, code, source_map["metadata_start"]
    )
    entries = []
    for group in target_map["regions"][0]["groups"]:
        cases = group["cases"]
        sources = {source_map["regions"][0]["mapping"][case] for case in cases}
        if len(sources) != 1:
            raise ValueError("source outer action aliases differ")
        entries.append(
            dict(
                name="default" if len(cases) > 20 else "/".join(map(str, cases)),
                cases=cases,
                target=group["destination"],
                source=native.S + sources.pop(),
            )
        )
    if len(entries) != 42:
        raise ValueError("outer action destination count differs")
    views = [
        census(target_rows, target_switches, entries, "target", native.A),
        census(source_rows, source_switches, entries, "source", native.S),
    ]
    world_counts = [counts(view, WORLD) for view in views]
    partitions_equal = world_counts[0] == world_counts[1]
    tail_receipts = []
    for rows, switches, view in zip(
        (target_rows, source_rows), (target_switches, source_switches), views
    ):
        by = {row.address: row for row in rows}
        shared = [
            site
            for site, row in view["calls"].items()
            if row["target"] == WORLD and row["entries"] == SHARED_ACTIONS
        ]
        if len(shared) != 1:
            tail_receipts.append(dict(qualified=False, sites=shared))
            continue
        site = shared[0]
        after = graphs.closure(by, site + by[site].size, switches)
        rets = [address for address in after if address in view["returns"]]
        qualified = (
            len(rets) == 1
            and view["returns"][rets[0]] == SHARED_ACTIONS
            and not any(address in view["calls"] for address in after)
        )
        tail_receipts.append(
            dict(
                qualified=qualified,
                site=site,
                returns=rets,
                encoded="".join(by[address].bytes.hex() for address in sorted(after)),
                instructions=[
                    dict(
                        site=address,
                        text=by[address].mnemonic + " " + by[address].op_str,
                    )
                    for address in sorted(after)
                ],
            )
        )
    if not tail_receipts[0]["qualified"] or tail_receipts[0]["site"] != 0x499DF8:
        raise ValueError("target shared World/RET tail differs")
    post_tail_equal = tail_receipts[1]["qualified"] and tail_receipts[0][
        "encoded"
    ] == tail_receipts[1].get("encoded")
    selector = selector_903((target_rows, source_rows), code)
    retiring = retirement_prefixes(
        (target_rows, source_rows), code, tail_receipts[1].get("site")
    )
    accepted = (
        partitions_equal
        and tail_receipts[1]["qualified"]
        and post_tail_equal
        and not selector["differences"]
        and all(selector["per_mode_call_graph_equal"])
        and selector["joint_call_graph_equal"]
        and not retiring["differences"]
        and not retiring["frontier_role_differences"]
    )
    return dict(
        schema="th105-reimu-object-world-sharing-v1",
        result="equal_scoped_world_sharing" if accepted else "rejected",
        target_sha256=facts["target_sha256"],
        object_sha256=hashlib.sha256(path.read_bytes()).hexdigest(),
        candidate_sha256=hashlib.sha256(code).hexdigest(),
        build_provenance_verified=False,
        action_entry_count=len(entries),
        entries=entries,
        source_switches=list(source_switches.values()),
        world_partition_equal=partitions_equal,
        world_site_counts=[sum(c.values()) for c in world_counts],
        world_partitions=[
            [dict(entries=list(k), count=v) for k, v in sorted(c.items())]
            for c in world_counts
        ],
        shared_world_tails=tail_receipts,
        post_world_tail_bytes_equal=post_tail_equal,
        selector_903=selector,
        retirement_prefixes=retiring,
        direct_callee_partition_equal={
            hex(callee): counts(views[0], callee) == counts(views[1], callee)
            for callee in sorted(
                {
                    row["target"]
                    for row in views[0]["calls"].values()
                    if row["target"] is not None
                }
            )
        },
        censuses=dict(target=views[0], source=views[1]),
        support_sha256={
            name: hashlib.sha256((ROOT / name).read_bytes()).hexdigest()
            for name in (
                "scripts/audit-reimu-object-world-sharing.py",
                "scripts/audit-reimu-object-selector-families.py",
                "scripts/audit-reimu-object-scalar-actions.py",
                "scripts/audit-reimu-object-update-target.py",
                "scripts/compare-giant-action-switches.py",
                "scripts/map-giant-action-switches.py",
                "scripts/compare-function.py",
                "scripts/iku_native_math.py",
                "config/giant-action-switches.toml",
                "src/characters/ReimuObjectActionStateStaging.cpp",
                "src/characters/ReimuObjectActionStateStaging.hpp",
            )
        },
        scope="physical World call memberships over42 action destinations, shared seven-action normal-return tail, and903 prefix/call-loop scope; no full semantics, indirect callee identity, loop-bound/predicate or canonical claim",
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
                    "entries",
                    "source_switches",
                    "world_partitions",
                    "censuses",
                    "support_sha256",
                    "selector_903",
                    "retirement_prefixes",
                )
            },
            indent=2,
        )
    )
    if "selector_903" in report:
        print(
            json.dumps(
                {
                    k: v
                    for k, v in report["selector_903"].items()
                    if k not in ("joint_graphs", "lookup_initialization", "differences")
                },
                indent=2,
            )
        )
        print("903 prefix differences", len(report["selector_903"]["differences"]))
    if "retirement_prefixes" in report:
        receipt = report["retirement_prefixes"]
        print(
            json.dumps(
                {
                    key: receipt[key]
                    for key in (
                        "case_count",
                        "input_sha256",
                        "differences",
                        "frontier_role_differences",
                        "scope",
                    )
                },
                indent=2,
            )
        )
    return int(report["result"] != "equal_scoped_world_sharing")


if __name__ == "__main__":
    raise SystemExit(main())
