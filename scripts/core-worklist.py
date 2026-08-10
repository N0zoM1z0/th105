#!/usr/bin/env python3
"""Validate and query the gameplay-first reconstruction framework."""

from __future__ import annotations

import argparse
import csv
import json
from pathlib import Path
import re
import sys


ROOT = Path(__file__).resolve().parents[1]
FUNCTIONS = ROOT / "config" / "functions.csv"
CLAIMS = ROOT / "config" / "claims.csv"
CORE_FUNCTIONS = ROOT / "config" / "core-functions.csv"
DEPENDENCIES = ROOT / "config" / "core-dependencies.csv"
CORE_TYPES = ROOT / "config" / "core-types.csv"

ADDRESS = re.compile(r"0x[0-9A-F]{8}$")
SIZE = re.compile(r"0x[0-9A-F]+$")
STATUS_RANK = {
    "blocked": -1,
    "unclassified": 0,
    "identified": 1,
    "decompiled": 2,
    "implemented": 3,
    "compiles": 3,
    "matching": 4,
    "library": 4,
}
REQUIRED_STATUSES = {"identified", "decompiled", "implemented", "matching", "library"}
COVERAGE = {"complete", "partial", "opaque"}
CONFIDENCE = {"observed", "inferred", "hypothesized"}


def read_rows(path: Path) -> list[dict[str, str]]:
    with path.open(newline="", encoding="utf-8") as stream:
        return list(csv.DictReader(stream))


def action_for(status: str) -> str:
    return {
        "unclassified": "contract",
        "identified": "decompile",
        "decompiled": "implement",
        "implemented": "shape",
        "compiles": "shape",
        "matching": "done",
        "library": "done",
        "blocked": "blocked",
    }[status]


def canonical_address(value: str) -> str:
    numeric = int(value.strip(), 16)
    return f"0x{numeric:08X}"


def validate() -> tuple[list[str], dict[str, dict[str, str]], list[dict[str, str]]]:
    errors: list[str] = []
    function_rows = read_rows(FUNCTIONS)
    functions = {row["address"]: row for row in function_rows}
    claims = {row["address"]: row for row in read_rows(CLAIMS)}
    scope = read_rows(CORE_FUNCTIONS)
    edges = read_rows(DEPENDENCIES)
    types = read_rows(CORE_TYPES)

    seen: set[str] = set()
    previous = -1
    for line, row in enumerate(scope, 2):
        address = row["address"]
        if not ADDRESS.fullmatch(address):
            errors.append(f"core-functions.csv:{line}: invalid address {address!r}")
            continue
        numeric = int(address, 16)
        if numeric <= previous:
            errors.append(f"core-functions.csv:{line}: addresses are duplicated or unsorted")
        previous = numeric
        if address not in functions:
            errors.append(f"core-functions.csv:{line}: {address} is absent from functions.csv")
        if address in seen:
            errors.append(f"core-functions.csv:{line}: duplicate {address}")
        seen.add(address)
        try:
            priority = int(row["priority"])
        except ValueError:
            priority = 0
        if priority not in (1, 2, 3):
            errors.append(f"core-functions.csv:{line}: priority must be 1, 2, or 3")
        if not row["lane"]:
            errors.append(f"core-functions.csv:{line}: lane is required")

    edge_keys: set[tuple[str, str]] = set()
    for line, row in enumerate(edges, 2):
        caller = row["caller"]
        callee = row["callee"]
        key = (caller, callee)
        if key in edge_keys:
            errors.append(f"core-dependencies.csv:{line}: duplicate edge {caller} -> {callee}")
        edge_keys.add(key)
        for role, address in (("caller", caller), ("callee", callee)):
            if not ADDRESS.fullmatch(address):
                errors.append(f"core-dependencies.csv:{line}: invalid {role} {address!r}")
            elif address not in functions:
                errors.append(f"core-dependencies.csv:{line}: {role} {address} is absent from functions.csv")
            elif address not in seen:
                errors.append(f"core-dependencies.csv:{line}: {role} {address} is outside core-functions.csv")
        required = row["required_status"]
        if required not in REQUIRED_STATUSES:
            errors.append(f"core-dependencies.csv:{line}: invalid required_status {required!r}")
        if not row["evidence"]:
            errors.append(f"core-dependencies.csv:{line}: evidence is required")

    type_names: set[str] = set()
    for line, row in enumerate(types, 2):
        name = row["type_name"]
        if not name or name in type_names:
            errors.append(f"core-types.csv:{line}: missing or duplicate type_name {name!r}")
        type_names.add(name)
        header = ROOT / row["header"]
        if not header.is_file():
            errors.append(f"core-types.csv:{line}: missing header {row['header']!r}")
        if row["coverage"] not in COVERAGE:
            errors.append(f"core-types.csv:{line}: invalid coverage {row['coverage']!r}")
        if row["observed_size"] and not SIZE.fullmatch(row["observed_size"]):
            errors.append(f"core-types.csv:{line}: invalid observed_size {row['observed_size']!r}")
        if row["confidence"] not in CONFIDENCE:
            errors.append(f"core-types.csv:{line}: invalid confidence {row['confidence']!r}")
        if not row["evidence"]:
            errors.append(f"core-types.csv:{line}: evidence is required")

    records: dict[str, dict[str, str]] = {}
    dependencies_by_caller: dict[str, list[dict[str, str]]] = {}
    for edge in edges:
        dependencies_by_caller.setdefault(edge["caller"], []).append(edge)

    for scoped in scope:
        address = scoped["address"]
        ledger = functions.get(address, {})
        blockers: list[str] = []
        for edge in dependencies_by_caller.get(address, []):
            callee = functions.get(edge["callee"], {})
            current = callee.get("status", "unclassified")
            required = edge["required_status"]
            if STATUS_RANK.get(current, -1) < STATUS_RANK[required]:
                blockers.append(f"{edge['callee']}:{current}<{required}")
        records[address] = {
            **scoped,
            "name": ledger.get("proposed_name") or ledger.get("current_name", ""),
            "current_name": ledger.get("current_name", ""),
            "proposed_name": ledger.get("proposed_name", ""),
            "size": ledger.get("size", ""),
            "span_end": ledger.get("span_end", ""),
            "status": ledger.get("status", ""),
            "action": action_for(ledger.get("status", "unclassified")),
            "match_percent": ledger.get("match_percent", ""),
            "calling_convention": ledger.get("calling_convention", ""),
            "signature": ledger.get("signature", ""),
            "source_file": ledger.get("source_file", ""),
            "ledger_evidence": ledger.get("evidence", ""),
            "ledger_owner": ledger.get("owner", ""),
            "ledger_notes": ledger.get("notes", ""),
            "scope_notes": scoped.get("notes", ""),
            "claim_owner": claims.get(address, {}).get("owner", ""),
            "claim_started_utc": claims.get(address, {}).get("started_utc", ""),
            "claim_branch": claims.get(address, {}).get("branch", ""),
            "claim_notes": claims.get(address, {}).get("notes", ""),
            "blockers": ";".join(blockers),
        }
    return errors, records, edges


def selected_records(
    records: dict[str, dict[str, str]], lane: str, ready: bool
) -> list[dict[str, str]]:
    items = [record for record in records.values() if not lane or record["lane"] == lane]
    items = [record for record in items if record["action"] not in {"done", "blocked"}]
    if ready:
        items = [record for record in items if not record["blockers"] and not record["claim_owner"]]
    return sorted(items, key=lambda row: (int(row["priority"]), int(row["address"], 16)))


def print_table(items: list[dict[str, str]], limit: int) -> None:
    if limit:
        items = items[:limit]
    print("address     lane             P status        action      claim      blockers  name")
    for row in items:
        blockers = str(len(row["blockers"].split(";"))) if row["blockers"] else "-"
        print(
            f"{row['address']}  {row['lane']:<16} {row['priority']} "
            f"{row['status']:<13} {row['action']:<11} "
            f"{(row['claim_owner'] or '-'):<10} {blockers:<8} {row['name']}"
        )


def blocker_records(
    records: dict[str, dict[str, str]], edges: list[dict[str, str]], lane: str
) -> list[dict[str, object]]:
    priorities = {1: 100, 2: 10, 3: 1}
    grouped: dict[str, dict[str, object]] = {}
    for edge in edges:
        caller = records[edge["caller"]]
        callee = records[edge["callee"]]
        if lane and caller["lane"] != lane and callee["lane"] != lane:
            continue
        current = callee["status"]
        required = edge["required_status"]
        if STATUS_RANK.get(current, -1) >= STATUS_RANK[required]:
            continue
        item = grouped.setdefault(
            edge["callee"],
            {
                "address": edge["callee"],
                "name": callee["name"],
                "lane": callee["lane"],
                "status": current,
                "claim_owner": callee["claim_owner"],
                "impact": 0,
                "blocked_callers": [],
            },
        )
        priority = int(caller["priority"])
        item["impact"] = int(item["impact"]) + priorities[priority]
        cast_callers = item["blocked_callers"]
        assert isinstance(cast_callers, list)
        cast_callers.append(
            {
                "address": edge["caller"],
                "name": caller["name"],
                "lane": caller["lane"],
                "priority": priority,
                "required_status": required,
                "evidence": edge["evidence"],
            }
        )
    return sorted(
        grouped.values(),
        key=lambda row: (-int(row["impact"]), int(str(row["address"]), 16)),
    )


def print_blockers(items: list[dict[str, object]], limit: int) -> None:
    if limit:
        items = items[:limit]
    print("address     lane             status        impact callers claim      name")
    for row in items:
        callers = row["blocked_callers"]
        assert isinstance(callers, list)
        print(
            f"{row['address']}  {str(row['lane']):<16} "
            f"{str(row['status']):<13} {int(row['impact']):<6} "
            f"{len(callers):<7} {str(row['claim_owner'] or '-'):<10} {row['name']}"
        )


def explain_record(
    address: str,
    records: dict[str, dict[str, str]],
    edges: list[dict[str, str]],
) -> dict[str, object]:
    if address not in records:
        raise ValueError(f"{address} is outside config/core-functions.csv")
    record = dict(records[address])
    dependencies: list[dict[str, object]] = []
    dependents: list[dict[str, object]] = []
    for edge in edges:
        if edge["caller"] == address:
            callee = records[edge["callee"]]
            dependencies.append(
                {
                    "address": edge["callee"],
                    "name": callee["name"],
                    "lane": callee["lane"],
                    "status": callee["status"],
                    "required_status": edge["required_status"],
                    "satisfied": STATUS_RANK[callee["status"]]
                    >= STATUS_RANK[edge["required_status"]],
                    "claim_owner": callee["claim_owner"],
                    "evidence": edge["evidence"],
                }
            )
        if edge["callee"] == address:
            caller = records[edge["caller"]]
            dependents.append(
                {
                    "address": edge["caller"],
                    "name": caller["name"],
                    "lane": caller["lane"],
                    "priority": int(caller["priority"]),
                    "status": caller["status"],
                    "required_status": edge["required_status"],
                    "blocked_by_this": STATUS_RANK[record["status"]]
                    < STATUS_RANK[edge["required_status"]],
                    "claim_owner": caller["claim_owner"],
                    "evidence": edge["evidence"],
                }
            )
    record["dependencies"] = dependencies
    record["dependents"] = dependents
    return record


def print_explanation(packet: dict[str, object]) -> None:
    scalar_fields = (
        "address", "name", "lane", "priority", "status", "action", "size",
        "span_end", "match_percent", "calling_convention", "signature",
        "source_file", "scope_notes", "ledger_evidence", "ledger_notes",
        "claim_owner", "claim_started_utc", "claim_branch", "claim_notes",
    )
    for field in scalar_fields:
        value = packet.get(field, "")
        print(f"{field}: {value or '-'}")
    for title in ("dependencies", "dependents"):
        print(f"{title}:")
        values = packet[title]
        assert isinstance(values, list)
        if not values:
            print("  -")
            continue
        for value in values:
            assert isinstance(value, dict)
            state_key = "satisfied" if title == "dependencies" else "blocked_by_this"
            print(
                f"  {value['address']} {value['name']} "
                f"status={value['status']} required={value['required_status']} "
                f"{state_key}={str(value[state_key]).lower()} "
                f"claim={value['claim_owner'] or '-'}"
            )
            print(f"    evidence: {value['evidence']}")


def print_dot(
    records: dict[str, dict[str, str]], edges: list[dict[str, str]], lane: str
) -> None:
    visible = {
        address: row for address, row in records.items() if not lane or row["lane"] == lane
    }
    colors = {
        "matching": "palegreen",
        "library": "lightgray",
        "implemented": "khaki",
        "compiles": "khaki",
        "decompiled": "lightskyblue",
        "identified": "lightcyan",
        "unclassified": "mistyrose",
        "blocked": "salmon",
    }
    print("digraph th105_core {")
    print('  rankdir="LR";')
    for address, row in visible.items():
        label = f"{address}\\n{row['name']}\\n{row['status']}"
        print(f'  "{address}" [label="{label}", style=filled, fillcolor={colors[row["status"]]}];')
    for edge in edges:
        if edge["caller"] in visible and edge["callee"] in visible:
            print(
                f'  "{edge["caller"]}" -> "{edge["callee"]}" '
                f'[label="{edge["required_status"]}"];'
            )
    print("}")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--check", action="store_true", help="validate manifests only")
    parser.add_argument("--ready", action="store_true", help="show unclaimed tasks with satisfied contract dependencies")
    parser.add_argument("--blockers", action="store_true", help="rank unmet dependency contracts by direct weighted impact")
    parser.add_argument("--explain", metavar="ADDRESS", help="emit one address-bounded agent handoff packet")
    parser.add_argument("--lane", default="", help="restrict output to one lane")
    parser.add_argument("--limit", type=int, default=0, help="limit table or JSON rows")
    parser.add_argument("--json", action="store_true", help="emit selected rows as JSON")
    parser.add_argument("--dot", action="store_true", help="emit a Graphviz dependency graph")
    args = parser.parse_args()

    errors, records, edges = validate()
    if errors:
        print("\n".join(errors), file=sys.stderr)
        return 1
    if args.check:
        lanes = len({row["lane"] for row in records.values()})
        print(
            f"core framework OK: {len(records)} functions, {len(edges)} dependencies, "
            f"{len(read_rows(CORE_TYPES))} types, {lanes} lanes"
        )
        return 0
    if args.dot:
        print_dot(records, edges, args.lane)
        return 0

    if args.explain:
        try:
            packet = explain_record(canonical_address(args.explain), records, edges)
        except (ValueError, KeyError) as error:
            print(str(error), file=sys.stderr)
            return 2
        if args.json:
            print(json.dumps(packet, indent=2, ensure_ascii=False))
        else:
            print_explanation(packet)
        return 0

    if args.blockers:
        items = blocker_records(records, edges, args.lane)
        if args.json:
            if args.limit:
                items = items[: args.limit]
            print(json.dumps(items, indent=2, ensure_ascii=False))
        else:
            print_blockers(items, args.limit)
        return 0

    items = selected_records(records, args.lane, args.ready)
    if args.limit:
        items = items[: args.limit]
    if args.json:
        print(json.dumps(items, indent=2, ensure_ascii=False))
    else:
        print_table(items, 0)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
