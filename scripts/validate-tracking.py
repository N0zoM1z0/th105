#!/usr/bin/env python3
"""Seconds-fast consistency checks for the shared function ledger."""

from __future__ import annotations

import csv
from pathlib import Path
import re


ROOT = Path(__file__).resolve().parents[1]
FUNCTIONS = ROOT / "config" / "functions.csv"
KNOWN = ROOT / "config" / "known-symbols.csv"
CLAIMS = ROOT / "config" / "claims.csv"
ACTION_CHANGES = ROOT / "config" / "character-action-change-cases.csv"
INPUT_DISPATCHES = ROOT / "config" / "character-input-dispatch-cases.csv"
CPU_POLICIES = ROOT / "config" / "character-cpu-policy-cases.csv"
LIFECYCLE_EVENTS = ROOT / "config" / "character-lifecycle-event-roots.csv"
FUNCTION_ORIGINS = ROOT / "config" / "function-origins.csv"
VSLOT28_ROOTS = ROOT / "config" / "character-vslot28-roots.csv"
VSLOT28_PILOTS = ROOT / "config" / "character-vslot28-pilot-slices.csv"
STATUSES = {
    "unclassified",
    "identified",
    "decompiled",
    "implemented",
    "compiles",
    "matching",
    "library",
    "blocked",
}
ADDRESS = re.compile(r"0x[0-9A-F]{8}$")
FUNCTION_COLUMNS = [
    "address",
    "size",
    "span_end",
    "current_name",
    "proposed_name",
    "module",
    "status",
    "match_percent",
    "calling_convention",
    "signature",
    "is_thunk",
    "source_file",
    "evidence",
    "owner",
    "notes",
]
ACTION_CHANGE_COLUMNS = [
    "character",
    "address",
    "ledger_size",
    "case_count",
    "under_300",
    "actions_300_399",
    "actions_400_499",
    "actions_500_599",
    "actions_600_699",
    "actions_700_plus",
    "case_labels",
    "direct_callees",
    "evidence",
]
INPUT_DISPATCH_COLUMNS = [
    "character",
    "address",
    "ledger_size",
    "decompiler_lines",
    "case_count",
    "actions_200_299",
    "actions_300_399",
    "case_labels",
    "direct_callees",
    "tail_target",
    "evidence",
]
CPU_POLICY_COLUMNS = [
    "owner_group",
    "address",
    "ledger_size",
    "decompiler_lines",
    "case_occurrences",
    "unique_case_count",
    "case_labels",
    "direct_callees",
    "vtable_owners",
    "evidence",
]
LIFECYCLE_EVENT_COLUMNS = [
    "character",
    "role",
    "address",
    "ledger_size",
    "decompiler_lines",
    "case_occurrences",
    "unique_case_count",
    "case_labels",
    "direct_callees",
    "evidence",
]
FUNCTION_ORIGIN_COLUMNS = [
    "address",
    "origin",
    "subsystem",
    "disposition",
    "confidence",
    "evidence_id",
]
VSLOT28_COLUMNS = [
    "fighter",
    "address",
    "vtable",
    "ledger_size",
    "span_end",
    "ida_reported_size",
    "boundary_state",
    "selector_field",
    "table_ranges",
    "dispatch_sites",
    "direct_callee_count",
    "shared_fingerprint",
    "distinctive_callees",
    "slice_status",
    "evidence",
]
VSLOT28_PILOT_COLUMNS = [
    "fighter",
    "address",
    "analysis_form",
    "analysis_lines",
    "case_occurrences",
    "unique_case_count",
    "case_labels",
    "slice_boundaries",
    "field_access_summary",
    "distinctive_contracts",
    "return_topology",
    "evidence",
]
VSLOT28_PILOT_SET = {
    ("Alice", "0x004E9A20"),
    ("Aya", "0x006018F0"),
    ("Iku", "0x0061FDE0"),
    ("Komachi", "0x005E5860"),
    ("Marisa", "0x004A2F40"),
    ("Patchouli", "0x0050EC80"),
    ("Reimu", "0x004787B0"),
    ("Remilia", "0x00544D40"),
    ("Sakuya", "0x004CA870"),
    ("Suika", "0x00598100"),
    ("Tenshi", "0x0063C900"),
    ("Udonge", "0x005BF460"),
    ("Youmu", "0x0052FDA0"),
    ("Yuyuko", "0x0055D4A0"),
    ("Yukari", "0x0057AA60"),
}
VSLOT28_ANALYSIS_FORMS = {
    "ida_hexrays",
    "exact_target_tables",
    "headless_ghidra",
}
ORIGINS = {
    "authored_game",
    "compiler_generated",
    "vc8_runtime",
    "third_party",
    "import_thunk",
    "unknown",
}
ORIGIN_DISPOSITIONS = {"include_authored", "exclude_authored", "review"}
ORIGIN_CONFIDENCES = {"observed", "inferred", "hypothesized", "unknown"}
VSLOT28_ROOT_SET = {
    ("Reimu", "0x004787B0", "0x006B013C"),
    ("Marisa", "0x004A2F40", "0x006B0594"),
    ("Sakuya", "0x004CA870", "0x006B0924"),
    ("Alice", "0x004E9A20", "0x006B0BEC"),
    ("Patchouli", "0x0050EC80", "0x006B0EBC"),
    ("Youmu", "0x0052FDA0", "0x006B1154"),
    ("Remilia", "0x00544D40", "0x006B13D4"),
    ("Yuyuko", "0x0055D4A0", "0x006B165C"),
    ("Yukari", "0x0057AA60", "0x006B18DC"),
    ("Suika", "0x00598100", "0x006B1B9C"),
    ("Udonge", "0x005BF460", "0x006B1E3C"),
    ("Komachi", "0x005E5860", "0x006B2074"),
    ("Aya", "0x006018F0", "0x006B22DC"),
    ("Iku", "0x0061FDE0", "0x006B2534"),
    ("Tenshi", "0x0063C900", "0x006B279C"),
}
LIFECYCLE_EVENT_ROOTS = {
    ("Reimu", "sequence-lifecycle", "0x00490C60"),
    ("Reimu", "event-bridge", "0x004A2A50"),
    ("Marisa", "sequence-lifecycle", "0x004B7AB0"),
    ("Marisa", "event-bridge", "0x004CA440"),
    ("Sakuya", "sequence-lifecycle", "0x004DD2A0"),
    ("Sakuya", "event-bridge", "0x004E9610"),
    ("Alice", "sequence-lifecycle", "0x004F88D0"),
    ("Alice", "constructor-boundary", "0x004FA530"),
    ("Alice", "event-bridge", "0x0050E780"),
    ("Patchouli", "sequence-lifecycle", "0x0051C5C0"),
    ("Patchouli", "event-bridge", "0x0052F950"),
    ("Youmu", "sequence-lifecycle", "0x005397E0"),
    ("Youmu", "event-bridge", "0x005448A0"),
    ("Remilia", "sequence-lifecycle", "0x005544A0"),
    ("Remilia", "event-bridge", "0x0055CFD0"),
    ("Yuyuko", "sequence-lifecycle", "0x0056BDC0"),
    ("Yuyuko", "event-bridge", "0x0057A5C0"),
    ("Yukari", "sequence-lifecycle", "0x00588DF0"),
    ("Yukari", "event-bridge", "0x00597B20"),
    ("Suika", "sequence-lifecycle", "0x005ABDF0"),
    ("Suika", "event-bridge", "0x005BEEE0"),
    ("Udonge", "sequence-lifecycle", "0x005D3EA0"),
    ("Udonge", "event-bridge", "0x005E53D0"),
    ("Komachi", "sequence-lifecycle", "0x005F5700"),
    ("Komachi", "event-bridge", "0x006013C0"),
    ("Aya", "sequence-lifecycle", "0x00615EA0"),
    ("Aya", "event-bridge", "0x0061F870"),
    ("Iku", "sequence-lifecycle", "0x0062E910"),
    ("Iku", "event-bridge", "0x0063C1D0"),
    ("Tenshi", "sequence-lifecycle", "0x00648850"),
    ("Tenshi", "event-bridge", "0x00658830"),
}
CPU_POLICY_GROUPS = {
    "Reimu",
    "Marisa",
    "Alice",
    "Default (11 fighters)",
    "Aya",
}
ROSTER = {
    "Reimu",
    "Marisa",
    "Sakuya",
    "Alice",
    "Patchouli",
    "Youmu",
    "Remilia",
    "Yuyuko",
    "Yukari",
    "Suika",
    "Udonge",
    "Komachi",
    "Aya",
    "Iku",
    "Tenshi",
}


def read_rows(
    path: Path,
    errors: list[str],
    expected_header: list[str] | None = None,
) -> list[dict[str, str]]:
    with path.open(newline="", encoding="utf-8") as stream:
        reader = csv.reader(stream)
        try:
            header = next(reader)
        except StopIteration:
            errors.append(f"{path.name}: missing CSV header")
            return []

        if expected_header is not None and header != expected_header:
            errors.append(
                f"{path.name}: invalid header; expected {','.join(expected_header)}"
            )
            return []
        if len(header) != len(set(header)):
            errors.append(f"{path.name}: duplicate CSV header field")
            return []

        rows: list[dict[str, str]] = []
        for line, values in enumerate(reader, 2):
            if len(values) != len(header):
                errors.append(
                    f"{path.name}:{line}: expected {len(header)} columns, "
                    f"got {len(values)}"
                )
                continue
            rows.append(dict(zip(header, values, strict=True)))
        return rows


def canonical(value: str) -> str:
    return f"0x{int(value, 16):08X}"


def main() -> int:
    errors: list[str] = []
    rows = read_rows(FUNCTIONS, errors, FUNCTION_COLUMNS)
    addresses: set[str] = set()
    ledger: dict[str, dict[str, str]] = {}
    previous = -1

    for line, row in enumerate(rows, 2):
        address = row["address"]
        if not ADDRESS.fullmatch(address):
            errors.append(f"functions.csv:{line}: invalid canonical address {address!r}")
            continue
        numeric = int(address, 16)
        if numeric <= previous:
            errors.append(f"functions.csv:{line}: addresses are duplicated or unsorted")
        previous = numeric
        addresses.add(address)
        ledger[address] = row

        status = row["status"]
        if status not in STATUSES:
            errors.append(f"functions.csv:{line}: invalid status {status!r}")
        if row["is_thunk"] not in {"true", "false"}:
            errors.append(
                f"functions.csv:{line}: invalid is_thunk {row['is_thunk']!r}"
            )
        try:
            percent = float(row["match_percent"])
        except ValueError:
            errors.append(f"functions.csv:{line}: invalid match_percent")
            continue
        if not 0.0 <= percent <= 100.0:
            errors.append(f"functions.csv:{line}: match_percent outside 0..100")
        if status == "matching" and percent != 100.0:
            errors.append(f"functions.csv:{line}: matching requires 100.00")
        if status == "matching" and (not row["source_file"] or not row["evidence"]):
            errors.append(f"functions.csv:{line}: matching requires source_file and evidence")
        if status in {"implemented", "compiles", "matching"} and not row["source_file"]:
            errors.append(f"functions.csv:{line}: {status} requires source_file")
        if status != "unclassified" and not row["evidence"]:
            errors.append(f"functions.csv:{line}: {status} requires evidence")

        source_file = row["source_file"]
        if source_file:
            source_path = Path(source_file)
            if source_path.is_absolute() or ".." in source_path.parts:
                errors.append(
                    f"functions.csv:{line}: source_file must be repository-relative: "
                    f"{source_file!r}"
                )
            elif status in {"implemented", "compiles", "matching"} and not (
                ROOT / source_path
            ).is_file():
                errors.append(
                    f"functions.csv:{line}: source_file does not exist: {source_file!r}"
                )

    action_rows = read_rows(ACTION_CHANGES, errors, ACTION_CHANGE_COLUMNS)
    action_characters: set[str] = set()
    action_addresses: set[str] = set()
    for line, row in enumerate(action_rows, 2):
        character = row["character"]
        if character in action_characters:
            errors.append(
                f"{ACTION_CHANGES.name}:{line}: duplicate character {character!r}"
            )
        action_characters.add(character)

        address = row["address"]
        if not ADDRESS.fullmatch(address):
            errors.append(
                f"{ACTION_CHANGES.name}:{line}: invalid canonical address {address!r}"
            )
            continue
        if address in action_addresses:
            errors.append(f"{ACTION_CHANGES.name}:{line}: duplicate address {address}")
        action_addresses.add(address)

        ledger_row = ledger.get(address)
        if ledger_row is None:
            errors.append(
                f"{ACTION_CHANGES.name}:{line}: address {address} is absent from functions.csv"
            )
            continue

        numeric_fields = [
            "ledger_size",
            "case_count",
            "under_300",
            "actions_300_399",
            "actions_400_499",
            "actions_500_599",
            "actions_600_699",
            "actions_700_plus",
        ]
        try:
            values = {name: int(row[name]) for name in numeric_fields}
        except ValueError:
            errors.append(f"{ACTION_CHANGES.name}:{line}: invalid numeric field")
            continue
        if any(value < 0 for value in values.values()):
            errors.append(f"{ACTION_CHANGES.name}:{line}: negative count")
        if values["ledger_size"] != int(ledger_row["size"]):
            errors.append(
                f"{ACTION_CHANGES.name}:{line}: ledger_size disagrees with functions.csv"
            )

        band_total = sum(values[name] for name in numeric_fields[2:])
        if band_total != values["case_count"]:
            errors.append(
                f"{ACTION_CHANGES.name}:{line}: action-band counts do not sum to case_count"
            )

        try:
            labels = [int(value, 16) for value in row["case_labels"].split(";")]
        except ValueError:
            errors.append(f"{ACTION_CHANGES.name}:{line}: invalid case label")
            labels = []
        if len(labels) != values["case_count"] or len(labels) != len(set(labels)):
            errors.append(
                f"{ACTION_CHANGES.name}:{line}: case labels are missing or duplicated"
            )

        for callee in row["direct_callees"].split(";"):
            if not ADDRESS.fullmatch(callee) or callee not in addresses:
                errors.append(
                    f"{ACTION_CHANGES.name}:{line}: invalid direct callee {callee!r}"
                )

        if ledger_row["status"] in {"unclassified", "identified"}:
            errors.append(
                f"{ACTION_CHANGES.name}:{line}: complete case manifest requires decompiled or later status"
            )

    if action_characters != ROSTER:
        missing = sorted(ROSTER - action_characters)
        extra = sorted(action_characters - ROSTER)
        errors.append(
            f"{ACTION_CHANGES.name}: roster mismatch; missing={missing}, extra={extra}"
        )

    input_rows = read_rows(INPUT_DISPATCHES, errors, INPUT_DISPATCH_COLUMNS)
    input_characters: set[str] = set()
    input_addresses: set[str] = set()
    for line, row in enumerate(input_rows, 2):
        character = row["character"]
        if character in input_characters:
            errors.append(
                f"{INPUT_DISPATCHES.name}:{line}: duplicate character {character!r}"
            )
        input_characters.add(character)

        address = row["address"]
        if not ADDRESS.fullmatch(address):
            errors.append(
                f"{INPUT_DISPATCHES.name}:{line}: invalid canonical address {address!r}"
            )
            continue
        if address in input_addresses:
            errors.append(f"{INPUT_DISPATCHES.name}:{line}: duplicate address {address}")
        input_addresses.add(address)

        ledger_row = ledger.get(address)
        if ledger_row is None:
            errors.append(
                f"{INPUT_DISPATCHES.name}:{line}: address {address} is absent from functions.csv"
            )
            continue

        numeric_fields = [
            "ledger_size",
            "decompiler_lines",
            "case_count",
            "actions_200_299",
            "actions_300_399",
        ]
        try:
            values = {name: int(row[name]) for name in numeric_fields}
        except ValueError:
            errors.append(f"{INPUT_DISPATCHES.name}:{line}: invalid numeric field")
            continue
        if any(value < 0 for value in values.values()):
            errors.append(f"{INPUT_DISPATCHES.name}:{line}: negative count")
        if values["ledger_size"] != int(ledger_row["size"]):
            errors.append(
                f"{INPUT_DISPATCHES.name}:{line}: ledger_size disagrees with functions.csv"
            )
        if values["actions_200_299"] + values["actions_300_399"] != values["case_count"]:
            errors.append(
                f"{INPUT_DISPATCHES.name}:{line}: action-band counts do not sum to case_count"
            )

        try:
            labels = [int(value, 16) for value in row["case_labels"].split(";")]
        except ValueError:
            errors.append(f"{INPUT_DISPATCHES.name}:{line}: invalid case label")
            labels = []
        if len(labels) != values["case_count"] or len(labels) != len(set(labels)):
            errors.append(
                f"{INPUT_DISPATCHES.name}:{line}: case labels are missing or duplicated"
            )

        for callee in row["direct_callees"].split(";"):
            if not ADDRESS.fullmatch(callee) or callee not in addresses:
                errors.append(
                    f"{INPUT_DISPATCHES.name}:{line}: invalid direct callee {callee!r}"
                )
        tail_target = row["tail_target"]
        if not ADDRESS.fullmatch(tail_target) or tail_target not in addresses:
            errors.append(
                f"{INPUT_DISPATCHES.name}:{line}: invalid tail target {tail_target!r}"
            )
        if ledger_row["status"] in {"unclassified", "identified"}:
            errors.append(
                f"{INPUT_DISPATCHES.name}:{line}: complete case manifest requires decompiled or later status"
            )

    if input_characters != ROSTER:
        missing = sorted(ROSTER - input_characters)
        extra = sorted(input_characters - ROSTER)
        errors.append(
            f"{INPUT_DISPATCHES.name}: roster mismatch; missing={missing}, extra={extra}"
        )

    cpu_rows = read_rows(CPU_POLICIES, errors, CPU_POLICY_COLUMNS)
    cpu_groups: set[str] = set()
    cpu_addresses: set[str] = set()
    cpu_vtable_owners: set[str] = set()
    expected_cpu_callees = {
        "0x0045B9E0",
        "0x0067B8E0",
        "0x00406710",
        "0x004069A0",
        "0x00406880",
    }
    for line, row in enumerate(cpu_rows, 2):
        group = row["owner_group"]
        if group in cpu_groups:
            errors.append(f"{CPU_POLICIES.name}:{line}: duplicate owner group {group!r}")
        cpu_groups.add(group)

        address = row["address"]
        if not ADDRESS.fullmatch(address):
            errors.append(f"{CPU_POLICIES.name}:{line}: invalid canonical address {address!r}")
            continue
        if address in cpu_addresses:
            errors.append(f"{CPU_POLICIES.name}:{line}: duplicate address {address}")
        cpu_addresses.add(address)
        ledger_row = ledger.get(address)
        if ledger_row is None:
            errors.append(f"{CPU_POLICIES.name}:{line}: address {address} is absent from functions.csv")
            continue

        try:
            ledger_size = int(row["ledger_size"])
            decompiler_lines = int(row["decompiler_lines"])
            occurrences = int(row["case_occurrences"])
            unique_count = int(row["unique_case_count"])
        except ValueError:
            errors.append(f"{CPU_POLICIES.name}:{line}: invalid numeric field")
            continue
        if min(ledger_size, decompiler_lines, occurrences, unique_count) < 0:
            errors.append(f"{CPU_POLICIES.name}:{line}: negative count")
        if ledger_size != int(ledger_row["size"]):
            errors.append(f"{CPU_POLICIES.name}:{line}: ledger_size disagrees with functions.csv")
        if occurrences < unique_count:
            errors.append(f"{CPU_POLICIES.name}:{line}: case occurrences below unique count")

        try:
            labels = [int(value, 0) for value in row["case_labels"].split(";")]
        except ValueError:
            errors.append(f"{CPU_POLICIES.name}:{line}: invalid case label")
            labels = []
        if len(labels) != unique_count or len(labels) != len(set(labels)):
            errors.append(f"{CPU_POLICIES.name}:{line}: case labels are missing or duplicated")

        callees = set(row["direct_callees"].split(";"))
        if callees != expected_cpu_callees:
            errors.append(f"{CPU_POLICIES.name}:{line}: shared direct-callee set disagrees")
        if any(not ADDRESS.fullmatch(callee) or callee not in addresses for callee in callees):
            errors.append(f"{CPU_POLICIES.name}:{line}: invalid direct callee")

        owners = row["vtable_owners"].split(";")
        if any(owner not in ROSTER for owner in owners):
            errors.append(f"{CPU_POLICIES.name}:{line}: invalid vtable owner")
        overlap = cpu_vtable_owners.intersection(owners)
        if overlap:
            errors.append(f"{CPU_POLICIES.name}:{line}: duplicate vtable owners {sorted(overlap)}")
        cpu_vtable_owners.update(owners)
        if ledger_row["status"] in {"unclassified", "identified"}:
            errors.append(f"{CPU_POLICIES.name}:{line}: complete manifest requires decompiled or later status")

    if cpu_groups != CPU_POLICY_GROUPS:
        errors.append(f"{CPU_POLICIES.name}: owner-group set mismatch")
    if cpu_vtable_owners != ROSTER:
        missing = sorted(ROSTER - cpu_vtable_owners)
        extra = sorted(cpu_vtable_owners - ROSTER)
        errors.append(f"{CPU_POLICIES.name}: vtable roster mismatch; missing={missing}, extra={extra}")

    lifecycle_rows = read_rows(
        LIFECYCLE_EVENTS, errors, LIFECYCLE_EVENT_COLUMNS
    )
    lifecycle_roots: set[tuple[str, str, str]] = set()
    lifecycle_addresses: set[str] = set()
    for line, row in enumerate(lifecycle_rows, 2):
        key = (row["character"], row["role"], row["address"])
        if key in lifecycle_roots:
            errors.append(f"{LIFECYCLE_EVENTS.name}:{line}: duplicate root {key!r}")
        lifecycle_roots.add(key)

        address = row["address"]
        if not ADDRESS.fullmatch(address):
            errors.append(
                f"{LIFECYCLE_EVENTS.name}:{line}: invalid canonical address {address!r}"
            )
            continue
        if address in lifecycle_addresses:
            errors.append(f"{LIFECYCLE_EVENTS.name}:{line}: duplicate address {address}")
        lifecycle_addresses.add(address)
        ledger_row = ledger.get(address)
        if ledger_row is None:
            errors.append(
                f"{LIFECYCLE_EVENTS.name}:{line}: address {address} is absent from functions.csv"
            )
            continue

        try:
            ledger_size = int(row["ledger_size"])
            decompiler_lines = int(row["decompiler_lines"])
            occurrences = int(row["case_occurrences"])
            unique_count = int(row["unique_case_count"])
        except ValueError:
            errors.append(f"{LIFECYCLE_EVENTS.name}:{line}: invalid numeric field")
            continue
        if min(ledger_size, decompiler_lines, occurrences, unique_count) < 0:
            errors.append(f"{LIFECYCLE_EVENTS.name}:{line}: negative count")
        if ledger_size != int(ledger_row["size"]):
            errors.append(
                f"{LIFECYCLE_EVENTS.name}:{line}: ledger_size disagrees with functions.csv"
            )
        if occurrences < unique_count:
            errors.append(
                f"{LIFECYCLE_EVENTS.name}:{line}: case occurrences below unique count"
            )

        labels: list[int] = []
        if row["case_labels"]:
            try:
                labels = [int(value, 0) for value in row["case_labels"].split(";")]
            except ValueError:
                errors.append(f"{LIFECYCLE_EVENTS.name}:{line}: invalid case label")
        if len(labels) != unique_count or len(labels) != len(set(labels)):
            errors.append(
                f"{LIFECYCLE_EVENTS.name}:{line}: case labels are missing or duplicated"
            )

        for callee in row["direct_callees"].split(";"):
            if not ADDRESS.fullmatch(callee) or callee not in addresses:
                errors.append(
                    f"{LIFECYCLE_EVENTS.name}:{line}: invalid direct callee {callee!r}"
                )
        if ledger_row["status"] in {"unclassified", "identified"}:
            errors.append(
                f"{LIFECYCLE_EVENTS.name}:{line}: complete manifest requires decompiled or later status"
            )

    if lifecycle_roots != LIFECYCLE_EVENT_ROOTS:
        missing = sorted(LIFECYCLE_EVENT_ROOTS - lifecycle_roots)
        extra = sorted(lifecycle_roots - LIFECYCLE_EVENT_ROOTS)
        errors.append(
            f"{LIFECYCLE_EVENTS.name}: root-set mismatch; missing={missing}, extra={extra}"
        )

    origin_rows = read_rows(FUNCTION_ORIGINS, errors, FUNCTION_ORIGIN_COLUMNS)
    origin_addresses: list[str] = []
    for line, row in enumerate(origin_rows, 2):
        address = row["address"]
        origin_addresses.append(address)
        if address not in ledger:
            errors.append(f"{FUNCTION_ORIGINS.name}:{line}: address absent from functions.csv")
        if row["origin"] not in ORIGINS:
            errors.append(f"{FUNCTION_ORIGINS.name}:{line}: invalid origin")
        if row["disposition"] not in ORIGIN_DISPOSITIONS:
            errors.append(f"{FUNCTION_ORIGINS.name}:{line}: invalid disposition")
        if row["confidence"] not in ORIGIN_CONFIDENCES:
            errors.append(f"{FUNCTION_ORIGINS.name}:{line}: invalid confidence")
        if row["origin"] == "unknown" and row["disposition"] != "review":
            errors.append(f"{FUNCTION_ORIGINS.name}:{line}: unknown must remain review")
        ledger_row = ledger.get(address)
        if ledger_row and row["disposition"] == "exclude_authored" and ledger_row["status"] != "library":
            errors.append(f"{FUNCTION_ORIGINS.name}:{line}: excluded row must be library")
    if origin_addresses != [row["address"] for row in rows]:
        errors.append(f"{FUNCTION_ORIGINS.name}: must contain every ledger address in order")

    vslot28_rows = read_rows(VSLOT28_ROOTS, errors, VSLOT28_COLUMNS)
    vslot28_seen: set[tuple[str, str, str]] = set()
    for line, row in enumerate(vslot28_rows, 2):
        key = (row["fighter"], row["address"], row["vtable"])
        vslot28_seen.add(key)
        ledger_row = ledger.get(row["address"])
        if ledger_row is None:
            errors.append(f"{VSLOT28_ROOTS.name}:{line}: address absent from functions.csv")
            continue
        try:
            ledger_size = int(row["ledger_size"])
            ida_size = int(row["ida_reported_size"])
            callee_count = int(row["direct_callee_count"])
        except ValueError:
            errors.append(f"{VSLOT28_ROOTS.name}:{line}: invalid numeric field")
            continue
        if ledger_size != int(ledger_row["size"]):
            errors.append(f"{VSLOT28_ROOTS.name}:{line}: ledger_size disagrees")
        if row["span_end"] != ledger_row["span_end"]:
            errors.append(f"{VSLOT28_ROOTS.name}:{line}: span_end disagrees")
        if min(ledger_size, ida_size, callee_count) < 0:
            errors.append(f"{VSLOT28_ROOTS.name}:{line}: negative numeric field")
        for value in row["dispatch_sites"].split(";"):
            if not ADDRESS.fullmatch(value):
                errors.append(f"{VSLOT28_ROOTS.name}:{line}: invalid dispatch site")
        for value in filter(None, row["distinctive_callees"].split(";")):
            if not ADDRESS.fullmatch(value) or value not in ledger:
                errors.append(f"{VSLOT28_ROOTS.name}:{line}: invalid distinctive callee")
    if vslot28_seen != VSLOT28_ROOT_SET:
        missing = sorted(VSLOT28_ROOT_SET - vslot28_seen)
        extra = sorted(vslot28_seen - VSLOT28_ROOT_SET)
        errors.append(f"{VSLOT28_ROOTS.name}: roster mismatch; missing={missing}, extra={extra}")

    vslot28_pilot_rows = read_rows(
        VSLOT28_PILOTS, errors, VSLOT28_PILOT_COLUMNS
    )
    vslot28_pilot_seen: set[tuple[str, str]] = set()
    for line, row in enumerate(vslot28_pilot_rows, 2):
        key = (row["fighter"], row["address"])
        vslot28_pilot_seen.add(key)
        ledger_row = ledger.get(row["address"])
        if ledger_row is None:
            errors.append(f"{VSLOT28_PILOTS.name}:{line}: address absent from functions.csv")
            continue
        try:
            analysis_lines = int(row["analysis_lines"])
            occurrences = int(row["case_occurrences"])
            unique_count = int(row["unique_case_count"])
            labels = [int(value, 0) for value in row["case_labels"].split(";")]
        except ValueError:
            errors.append(f"{VSLOT28_PILOTS.name}:{line}: invalid numeric field")
            continue
        if row["analysis_form"] not in VSLOT28_ANALYSIS_FORMS:
            errors.append(f"{VSLOT28_PILOTS.name}:{line}: invalid analysis form")
        if min(analysis_lines, occurrences, unique_count) <= 0:
            errors.append(f"{VSLOT28_PILOTS.name}:{line}: non-positive survey count")
        if occurrences < unique_count:
            errors.append(f"{VSLOT28_PILOTS.name}:{line}: occurrences below unique count")
        if len(labels) != unique_count or len(labels) != len(set(labels)):
            errors.append(f"{VSLOT28_PILOTS.name}:{line}: case labels disagree")
        if ledger_row["status"] not in {"decompiled", "implemented", "compiles", "matching"}:
            errors.append(f"{VSLOT28_PILOTS.name}:{line}: pilot requires decompiled or later")
        if not all(
            row[field]
            for field in (
                "slice_boundaries",
                "field_access_summary",
                "return_topology",
                "evidence",
            )
        ):
            errors.append(f"{VSLOT28_PILOTS.name}:{line}: incomplete structural evidence")
    if vslot28_pilot_seen != VSLOT28_PILOT_SET:
        missing = sorted(VSLOT28_PILOT_SET - vslot28_pilot_seen)
        extra = sorted(vslot28_pilot_seen - VSLOT28_PILOT_SET)
        errors.append(f"{VSLOT28_PILOTS.name}: pilot mismatch; missing={missing}, extra={extra}")

    for path in (KNOWN, CLAIMS):
        for line, row in enumerate(read_rows(path, errors), 2):
            try:
                address = canonical(row["address"])
            except (KeyError, ValueError):
                errors.append(
                    f"{path.name}:{line}: invalid address {row.get('address', '')!r}"
                )
                continue
            if address not in addresses:
                if path == KNOWN and row.get("confidence") == "internal":
                    continue
                errors.append(f"{path.name}:{line}: address {address} is absent from functions.csv")

    if errors:
        print("\n".join(errors))
        return 1
    claim_rows = read_rows(CLAIMS, [])
    print(f"tracking OK: {len(rows)} functions, {len(claim_rows)} active claims")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
