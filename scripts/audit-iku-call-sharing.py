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


def facts(path=None):
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
    return {
        "code_sha256": hashlib.sha256(code).hexdigest(),
        "entries": entries,
        "calls": calls,
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
    args = parser.parse_args()
    target_sha = homes.c.verify_target()
    target = facts()
    report = {
        "schema": "th105-iku-call-sharing-v1",
        "target_sha256": target_sha,
        "root_sha256": homes.ROOT_SHA,
        "script_sha256": hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
        "target": target,
        "scope": "Possible incoming action IDs through raw instruction edges; -1 is the default entry, "
        "and [] means no action/default entry reaches the call (for example a prelude call). "
        "Conditions are not evaluated. Calls retain their normal continuation. "
        "No original variable names, source-sharing proof, missing-behavior claim or exact byte credit.",
    }
    if args.object:
        report["candidate"] = facts(args.object.resolve())
        report["object_sha256"] = hashlib.sha256(args.object.read_bytes()).hexdigest()
        report["differences"] = differences(target, report["candidate"])
    print(json.dumps(report, indent=2))
