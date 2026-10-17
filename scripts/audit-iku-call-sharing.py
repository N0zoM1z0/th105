#!/usr/bin/env python3
"""Compare Iku call-site sharing by possible incoming action IDs.

This is a static CFG diagnostic. Conditions are not evaluated, and calls keep
their ordinary continuation. It does not prove a runtime path or byte equality.
"""

from collections import Counter, defaultdict, deque
from pathlib import Path
import argparse
import hashlib
import importlib.util
import json
import sys
import tomllib

import capstone
from capstone.x86 import X86_OP_IMM, X86_OP_MEM, X86_OP_REG

from giant_owner_audit import decode
from iku_middle_actions import MIDDLE_ENTRIES
from iku_opening_actions import OPENING_ENTRIES
from iku_upper_actions import ENTRIES
from typed_indirect_tails import receiver_tail_facts

ROOT = Path(__file__).resolve().parents[1]

SPEC = importlib.util.spec_from_file_location(
    "iku_sharing_homes", ROOT / "scripts/audit-iku-payload-homes.py"
)
homes = importlib.util.module_from_spec(SPEC)
sys.modules[SPEC.name] = homes
SPEC.loader.exec_module(homes)


def propagate_origins(rows, entries, switches):
    """Union entry labels through normal CFG edges, including cycles."""
    origins = defaultdict(set)
    queue = deque()
    for action, address in entries.items():
        origins[address].add(action)
        queue.append(address)
    while queue:
        pc = queue.popleft()
        if pc not in rows:
            raise ValueError(f"action edge enters an unknown instruction at {pc:#x}")
        row = rows[pc]
        if row.group(capstone.CS_GRP_RET):
            continue
        edges = [pc + row.size]
        if row.group(capstone.CS_GRP_JUMP):
            operand = row.operands[0]
            if operand.type == X86_OP_IMM:
                edges = [operand.imm] + ([] if row.mnemonic == "jmp" else edges)
            elif operand.type == X86_OP_MEM and operand.mem.disp in switches:
                edges = switches[operand.mem.disp]
            else:
                raise ValueError(f"unreviewed indirect action jump at {pc:#x}")
        for edge in edges:
            if edge not in rows:
                raise ValueError(
                    f"action edge enters an unknown instruction at {edge:#x}"
                )
            new = origins[pc] - origins[edge]
            if new:
                origins[edge].update(new)
                queue.append(edge)
    return origins


def candidate_entries(path, rows):
    obj = homes.coff.CoffObject(
        path,
        symbol_base="?dispatch_action_state_vslot28@IkuActionStateView@th105@@QAEXXZ",
    )
    config = homes.load(
        "iku_sharing_mapper", "scripts/map-giant-action-switches.py"
    ).select_root(
        tomllib.loads((ROOT / "config/giant-action-switches.toml").read_text()),
        "iku-vslot28",
    )
    regions = homes.coff.candidate_region_tables(obj, config)
    mapping = {
        action: homes.START + destination
        for region in regions
        for action, destination in region["mapping"].items()
    }
    labels = OPENING_ENTRIES | MIDDLE_ENTRIES | ENTRIES
    entries = {a: mapping[a] for a in labels if a not in (300, 560)}
    # Action11 is a checked hole in the first compressed table.
    entries[-1] = mapping[11]
    ordered = sorted(rows.values(), key=lambda row: row.address)
    for action in (300, 560):
        choices = []
        for index, row in enumerate(ordered[:-3]):
            if (
                row.mnemonic == "cmp"
                and len(row.operands) == 2
                and row.operands[0].type == X86_OP_REG
                and row.reg_name(row.operands[0].reg) == "eax"
                and row.operands[1].type == X86_OP_IMM
                and row.operands[1].imm == action
            ):
                branches = [
                    branch.operands[0].imm
                    for branch in ordered[index + 1 : index + 4]
                    if branch.mnemonic == "je" and branch.operands[0].type == X86_OP_IMM
                ]
                if len(branches) == 1:
                    choices.extend(branches)
        if len(choices) != 1:
            raise ValueError(f"ambiguous direct action{action} route: {choices}")
        entries[action] = choices[0]
    return entries


def facts(path=None, payload_homes=False, action_payloads=False):
    code, switches = homes.get_code(path)
    rows = {row.address: row for row in decode(code, homes.START)}
    entries = (
        OPENING_ENTRIES | MIDDLE_ENTRIES | ENTRIES | {-1: 0x62EFA5}
        if path is None
        else candidate_entries(path, rows)
    )
    origins = propagate_origins(rows, entries, switches)
    flow = receiver_tail_facts(
        code, homes.START, switches, include_calls=True, allow_slot_unions=True
    )
    virtual = {}
    for row in flow["register_indirect_calls"]:
        slots = row["possible_vtable_slots"]
        if (
            not row["ecx_is_entry_receiver"]
            or not slots
            or not set(slots) <= {8, 12, 20, 28}
        ):
            raise ValueError("unqualified Iku virtual call")
        virtual[row["address"]] = slots
    calls = []
    for pc, row in sorted(rows.items()):
        if row.mnemonic != "call":
            continue
        operand = row.operands[0]
        target = (
            hex(operand.imm)
            if operand.type == X86_OP_IMM
            else "vslots:" + ",".join(hex(slot) for slot in virtual[pc])
        )
        calls.append({"site": pc, "target": target, "actions": sorted(origins[pc])})
    report = {
        "code_sha256": hashlib.sha256(code).hexdigest(),
        "entries": entries,
        "calls": calls,
    }
    if payload_homes:
        provenance = homes.audit(code, switches, action_entries=entries if action_payloads else None)
        report["payload_provenance"] = {
            key: provenance[key]
            for key in (
                "frame",
                "distinct_payload_homes",
                "payload_sites",
                "unknown_spawn_payload_sites",
                "action_payload_sites",
                "partitioned_by_incoming_action",
                "dataflow_states",
                "reachable_before_epilogue_restore",
            )
        }
        if action_payloads:
            partition_origins = defaultdict(set)
            for item in provenance["action_payload_sites"]:
                partition_origins[item["site"]].add(item["action"])
            expected = {item["site"]: set(item["actions"]) or {None}
                        for item in calls if item["target"] == "0x465190"}
            if dict(partition_origins) != expected:
                raise ValueError("payload partitions disagree with independent CFG action origins")
    return report


def correlate_homes(target, candidate, *, action_partitioned=False):
    """Intersect home sets under action-origin/physical-call-ordinal pairing.

    This pairing is a conditional structural correlation, not argument identity.
    A multi-origin call supplies a set constraint, never a sorted zip of homes.
    """
    groups, partitions = [], []
    for packet in (target, candidate):
        by_origin = defaultdict(list)
        for call in sorted(packet["calls"], key=lambda row: row["site"]):
            if call["target"] == "0x465190":
                by_origin[tuple(call["actions"])].append(call["site"])
        groups.append(by_origin)
        if action_partitioned:
            provenance = packet["payload_provenance"]
            if not provenance.get("partitioned_by_incoming_action"):
                raise ValueError("action correlation requires partitioned prologue dataflow")
            index = {}
            for item in provenance["action_payload_sites"]:
                key = item["action"], item["site"]
                if key in index:
                    raise ValueError("duplicate action/payload site evidence")
                index[key] = item
            partitions.append(index)
    constraints, issues = {}, []
    for actions in sorted(groups[0].keys() | groups[1].keys()):
        sites = [group.get(actions, []) for group in groups]
        if len(sites[0]) != len(sites[1]):
            issues.append(
                {
                    "actions": actions,
                    "sites": sites,
                    "reason": "different group lengths",
                }
            )
            continue
        for pair in zip(*sites):
            for action in (actions or (None,)) if action_partitioned else (None,):
                context = {"actions": actions, "sites": pair}
                if action_partitioned:
                    context["action"] = action
                    evidence = [index.get((action, site)) for index, site in zip(partitions, pair)]
                    if any(item is None for item in evidence):
                        issues.append(context | {"reason": "missing action/payload evidence"})
                        continue
                    unknown = any(item["unknown"] for item in evidence)
                    cells = [set(item["homes"]) for item in evidence]
                    if evidence[0]["can_be_null"] != evidence[1]["can_be_null"]:
                        issues.append(context | {"reason": "different null-payload possibilities"})
                        continue
                else:
                    origins = [packet["payload_provenance"] for packet in (target, candidate)]
                    unknown = any(site in info["unknown_spawn_payload_sites"]
                                  for site, info in zip(pair, origins))
                    cells = [set(info["payload_sites"].get(hex(site), []))
                             for site, info in zip(pair, origins)]
                if unknown:
                    issues.append(context | {"reason": "unknown payload origin"})
                    continue
                if len(cells[0]) != len(cells[1]):
                    issues.append(context | {"reason": "different home-set cardinality"})
                    continue
                for home in cells[0]:
                    if home in constraints:
                        constraints[home].intersection_update(cells[1])
                    else:
                        constraints[home] = set(cells[1])
    unique = all(len(values) == 1 for values in constraints.values())
    image = {value for values in constraints.values() for value in values}
    candidate_homes = {
        value
        for values in candidate["payload_provenance"]["payload_sites"].values()
        for value in values
    }
    bijection = (
        not issues
        and bool(constraints)
        and unique
        and len(constraints) == target["payload_provenance"]["distinct_payload_homes"]
        and len(image) == len(constraints)
        and image == candidate_homes
        and len(image) == candidate["payload_provenance"]["distinct_payload_homes"]
    )
    return {
        "possible_target_to_candidate_homes": {
            str(home): sorted(values) for home, values in sorted(constraints.items())
        },
        "identity_correlations": sorted(
            home for home, values in constraints.items() if values == {home}
        ),
        "bijection_under_ordinal_pairing": bijection,
        "issues": issues,
        "incoming_action_partitioned": action_partitioned,
        "scope": (
            "Equal incoming-action groups paired by physical call ordinal; home-set constraints intersected. "
            + ("Action/pointer relation retained from the real prologue through shared tails. " if action_partitioned else "")
            + "Not a proof of payload values, feasible paths, original variable names or exact byte equality."
        ),
    }


def differences(target, candidate):
    counters = [
        Counter((row["target"], tuple(row["actions"])) for row in facts["calls"])
        for facts in (target, candidate)
    ]
    result = []
    for callee, actions in counters[0].keys() | counters[1].keys():
        left, right = (counts[callee, actions] for counts in counters)
        if left != right:
            result.append(
                {
                    "callee": callee,
                    "actions": actions,
                    "target_sites": left,
                    "candidate_sites": right,
                }
            )
    return sorted(
        result, key=lambda row: (-len(row["actions"]), row["callee"], row["actions"])
    )


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--object", type=Path)
    parser.add_argument(
        "--payload-homes",
        action="store_true",
        help="include stack provenance and conditional ordinal home correlation",
    )
    parser.add_argument(
        "--partition-payloads", action="store_true",
        help="retain incoming action and stack origin together through shared calls (implies --payload-homes)",
    )
    args = parser.parse_args()
    args.payload_homes = args.payload_homes or args.partition_payloads
    target_sha = homes.c.verify_target()
    target = facts(payload_homes=args.payload_homes, action_payloads=args.partition_payloads)
    report = {
        "schema": "th105-iku-call-sharing-v2" if args.partition_payloads else "th105-iku-call-sharing-v1",
        "target_sha256": target_sha,
        "root_sha256": homes.ROOT_SHA,
        "script_sha256": hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
        "support_sha256": {
            name: hashlib.sha256((ROOT / "scripts" / name).read_bytes()).hexdigest()
            for name in ("audit-iku-payload-homes.py", "typed_indirect_tails.py", "giant_owner_audit.py")
        },
        "target": target,
        "scope": "Possible incoming action IDs through raw instruction edges; -1 is the default entry, "
        "and [] means no action/default entry reaches the call (for example a prelude call). "
        "Conditions are not evaluated. Calls retain their normal continuation. "
        "No original variable names, source-sharing proof, missing-behavior claim or exact byte credit.",
    }
    if args.object:
        report["candidate"] = facts(
            args.object.resolve(), payload_homes=args.payload_homes, action_payloads=args.partition_payloads
        )
        report["object_sha256"] = hashlib.sha256(args.object.read_bytes()).hexdigest()
        report["differences"] = differences(target, report["candidate"])
        if args.payload_homes:
            report["home_correlation"] = correlate_homes(
                target, report["candidate"], action_partitioned=args.partition_payloads
            )
    print(json.dumps(report, indent=2))
