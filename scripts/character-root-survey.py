#!/usr/bin/env python3
"""Survey all playable-character action roots in one attested IDA session."""

from __future__ import annotations

import argparse
import asyncio
import csv
import json
from pathlib import Path
import re
from typing import Any

from ida_mcp_client import (
    DEFAULT_SERVER,
    IdaMcpError,
    call_json,
    open_session,
    parse_int,
    require_target,
)


ROOT = Path(__file__).resolve().parents[1]
FUNCTIONS = ROOT / "config" / "functions.csv"

ROOTS = (
    ("Reimu", "0x00491480", "0x00494050"),
    ("Marisa", "0x004B81F0", "0x004B9A60"),
    ("Sakuya", "0x004DDB20", "0x004DEF70"),
    ("Alice", "0x004F9320", "0x004FA5C0"),
    ("Patchouli", "0x0051D140", "0x0051EA60"),
    ("Youmu", "0x00539D70", "0x0053B040"),
    ("Remilia", "0x00554A00", "0x00555D90"),
    ("Yuyuko", "0x0056C490", "0x0056D8E0"),
    ("Yukari", "0x00589F20", "0x0058BBA0"),
    ("Suika", "0x005ACC10", "0x005AE470"),
    ("Udonge", "0x005D4610", "0x005D63F0"),
    ("Komachi", "0x005F5DE0", "0x005F7190"),
    ("Aya", "0x006166A0", "0x00617B20"),
    ("Iku", "0x0062F4B0", "0x00630800"),
    ("Tenshi", "0x006495C0", "0x0064AB80"),
)

VSLOT28_ROOTS = (
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
)

CPU_POLICY_ROOTS = (
    ("Reimu", "0x0048CBA0"),
    ("Marisa", "0x004B38A0"),
    ("Alice", "0x004F4650"),
    ("Default (11 fighters)", "0x005CFE00"),
    ("Aya", "0x00611D80"),
)

# These are the remaining unclassified character-command roots in the core
# graph.  The apparent Alice constructor boundary is retained because it is the
# roster-owned bridge that occupies the otherwise lifecycle/event breadth set;
# the manifest records the neutral slot role instead of forcing it into a
# sequence callback family.
LIFECYCLE_EVENT_ROOTS = (
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
)

CASE_RE = re.compile(r"\bcase\s+(-?(?:0x[0-9a-fA-F]+|\d+))\s*:")


def ledger() -> dict[str, dict[str, str]]:
    with FUNCTIONS.open(newline="", encoding="utf-8") as stream:
        return {row["address"].upper(): row for row in csv.DictReader(stream)}


def integer(value: str) -> int:
    return int(value, 0)


def case_ranges(values: list[int]) -> list[str]:
    if not values:
        return []
    result: list[str] = []
    start = previous = values[0]
    for value in values[1:]:
        if value == previous + 1:
            previous = value
            continue
        result.append(str(start) if start == previous else f"{start}..{previous}")
        start = previous = value
    result.append(str(start) if start == previous else f"{start}..{previous}")
    return result


def flatten_callees(value: Any) -> list[dict[str, str]]:
    rows = value if isinstance(value, list) else [value]
    result: list[dict[str, str]] = []
    for row in rows:
        if not isinstance(row, dict):
            continue
        address = row.get("address")
        name = row.get("name")
        if address is None and isinstance(row.get("function"), dict):
            address = row["function"].get("address")
            name = row["function"].get("name")
        if address is not None:
            result.append({"address": str(address), "name": str(name or "")})
    return result


async def survey(
    server: str, kind: str, fighter_filter: set[str], decompile_timeout: float
) -> dict[str, object]:
    tracked = ledger()
    async with open_session(server) as (session, initialized):
        tools = {tool.name for tool in (await session.list_tools()).tools}
        required = {"get_function_by_address", "decompile_function", "get_callees"}
        missing = sorted(required - tools)
        if missing:
            raise IdaMcpError("missing_tool", f"IDA MCP missing required tools: {missing}")
        before = await require_target(session)
        entries: list[dict[str, object]] = []
        for fighter, action_address, input_address in ROOTS:
            if fighter_filter and fighter not in fighter_filter:
                continue
            selected = (("action-change", action_address), ("input-dispatch", input_address))
            for root_kind, address in selected:
                if kind not in {"both", "all"} and root_kind != kind:
                    continue
                row = tracked.get(address.upper())
                if row is None:
                    raise RuntimeError(f"missing ledger address: {address}")
                function = await call_json(
                    session, "get_function_by_address", {"address": address}
                )
                callees = await call_json(
                    session, "get_callees", {"function_address": address}
                )
                decompile_status = "complete"
                decompile_error = ""
                try:
                    async with asyncio.timeout(decompile_timeout):
                        decompile = await call_json(
                            session, "decompile_function", {"address": address}
                        )
                    text = (
                        decompile
                        if isinstance(decompile, str)
                        else json.dumps(decompile)
                    )
                except (IdaMcpError, RuntimeError, TimeoutError) as error:
                    # Preserve independently useful boundary/callee evidence and
                    # successful sibling roots when Hex-Rays rejects one giant
                    # dispatcher.  The explicit partial packet is then routed to
                    # exact instruction-table decoding or headless Ghidra.
                    decompile_status = "failed"
                    decompile_error = str(error)
                    text = ""
                case_occurrences = [integer(match) for match in CASE_RE.findall(text)]
                cases = sorted(set(case_occurrences))
                backend_size = (
                    parse_int(function.get("size")) if isinstance(function, dict) else -1
                )
                entries.append(
                    {
                        "fighter": fighter,
                        "kind": root_kind,
                        "address": address,
                        "ledger_size": int(row["size"]),
                        "backend_size": backend_size,
                        "boundary_agrees": backend_size == int(row["size"]),
                        "backend_name": function.get("name") if isinstance(function, dict) else None,
                        "decompile_status": decompile_status,
                        "decompile_error": decompile_error,
                        "decompiler_lines": text.count("\n") + 1 if text else 0,
                        "switch_case_occurrences": len(case_occurrences),
                        "switch_cases": cases,
                        "switch_case_ranges": case_ranges(cases),
                        "callees": flatten_callees(callees),
                    }
                )
        if kind in {"cpu-policy", "all"}:
            for fighter, address in CPU_POLICY_ROOTS:
                if fighter_filter and fighter not in fighter_filter:
                    continue
                row = tracked.get(address.upper())
                if row is None:
                    raise RuntimeError(f"missing ledger address: {address}")
                function = await call_json(
                    session, "get_function_by_address", {"address": address}
                )
                decompile = await call_json(
                    session, "decompile_function", {"address": address}
                )
                callees = await call_json(
                    session, "get_callees", {"function_address": address}
                )
                text = decompile if isinstance(decompile, str) else json.dumps(decompile)
                case_occurrences = [integer(match) for match in CASE_RE.findall(text)]
                cases = sorted(set(case_occurrences))
                backend_size = (
                    parse_int(function.get("size")) if isinstance(function, dict) else -1
                )
                entries.append(
                    {
                        "fighter": fighter,
                        "kind": "cpu-policy",
                        "address": address,
                        "ledger_size": int(row["size"]),
                        "backend_size": backend_size,
                        "boundary_agrees": backend_size == int(row["size"]),
                        "backend_name": function.get("name") if isinstance(function, dict) else None,
                        "decompiler_lines": text.count("\n") + 1,
                        "switch_case_occurrences": len(case_occurrences),
                        "switch_cases": cases,
                        "switch_case_ranges": case_ranges(cases),
                        "callees": flatten_callees(callees),
                    }
                )
        if kind in {"lifecycle-event", "all"}:
            for fighter, root_kind, address in LIFECYCLE_EVENT_ROOTS:
                if fighter_filter and fighter not in fighter_filter:
                    continue
                row = tracked.get(address.upper())
                if row is None:
                    raise RuntimeError(f"missing ledger address: {address}")
                function = await call_json(
                    session, "get_function_by_address", {"address": address}
                )
                decompile = await call_json(
                    session, "decompile_function", {"address": address}
                )
                callees = await call_json(
                    session, "get_callees", {"function_address": address}
                )
                text = decompile if isinstance(decompile, str) else json.dumps(decompile)
                case_occurrences = [integer(match) for match in CASE_RE.findall(text)]
                cases = sorted(set(case_occurrences))
                backend_size = (
                    parse_int(function.get("size")) if isinstance(function, dict) else -1
                )
                entries.append(
                    {
                        "fighter": fighter,
                        "kind": root_kind,
                        "address": address,
                        "ledger_size": int(row["size"]),
                        "backend_size": backend_size,
                        "boundary_agrees": backend_size == int(row["size"]),
                        "backend_name": function.get("name") if isinstance(function, dict) else None,
                        "decompiler_lines": text.count("\n") + 1,
                        "switch_case_occurrences": len(case_occurrences),
                        "switch_cases": cases,
                        "switch_case_ranges": case_ranges(cases),
                        "callees": flatten_callees(callees),
                    }
                )
        if kind in {"vslot28", "all"}:
            for fighter, address, vtable in VSLOT28_ROOTS:
                if fighter_filter and fighter not in fighter_filter:
                    continue
                row = tracked.get(address.upper())
                if row is None:
                    raise RuntimeError(f"missing ledger address: {address}")
                function = await call_json(
                    session, "get_function_by_address", {"address": address}
                )
                callees = await call_json(
                    session, "get_callees", {"function_address": address}
                )
                decompile_status = "complete"
                decompile_error = ""
                try:
                    async with asyncio.timeout(decompile_timeout):
                        decompile = await call_json(
                            session, "decompile_function", {"address": address}
                        )
                    text = (
                        decompile
                        if isinstance(decompile, str)
                        else json.dumps(decompile)
                    )
                except (IdaMcpError, RuntimeError, TimeoutError) as error:
                    # Giant dispatchers may exceed Hex-Rays' practical limits.
                    # Preserve the boundary/callee packet and continue siblings;
                    # exact table decoding or headless Ghidra supplies the rest.
                    decompile_status = "failed"
                    decompile_error = str(error)
                    text = ""
                case_occurrences = [integer(match) for match in CASE_RE.findall(text)]
                cases = sorted(set(case_occurrences))
                backend_size = (
                    parse_int(function.get("size")) if isinstance(function, dict) else -1
                )
                entries.append(
                    {
                        "fighter": fighter,
                        "kind": "vslot28",
                        "address": address,
                        "vtable": vtable,
                        "vtable_slot": "0x28",
                        "selector_field": "Fighter+0x13C:u16",
                        "ledger_size": int(row["size"]),
                        "ledger_span_end": row["span_end"],
                        "backend_size": backend_size,
                        "boundary_agrees": backend_size == int(row["size"]),
                        "backend_name": function.get("name") if isinstance(function, dict) else None,
                        "decompile_status": decompile_status,
                        "decompile_error": decompile_error,
                        "decompiler_lines": text.count("\n") + 1 if text else 0,
                        "switch_case_occurrences": len(case_occurrences),
                        "switch_cases": cases,
                        "switch_case_ranges": case_ranges(cases),
                        "callees": flatten_callees(callees),
                    }
                )
        after = await require_target(session)
        fields = ("sha256", "md5", "base", "filesize", "path", "module")
        if any(before.get(field) != after.get(field) for field in fields):
            raise IdaMcpError("target_mismatch", "IDA target changed during roster survey")
        return {
            "schema_version": 1,
            "backend": "ida",
            "protocol_version": initialized.protocolVersion,
            "target": before,
            "kind": kind,
            "entries": entries,
        }


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--server", default=DEFAULT_SERVER)
    parser.add_argument(
        "--kind",
        choices=(
            "action-change",
            "input-dispatch",
            "cpu-policy",
            "lifecycle-event",
            "vslot28",
            "both",
            "all",
        ),
        default="both",
    )
    parser.add_argument("--output", type=Path)
    parser.add_argument(
        "--decompile-timeout",
        type=float,
        default=60.0,
        help="per-root Hex-Rays timeout in seconds before emitting a partial row",
    )
    parser.add_argument(
        "--fighter",
        action="append",
        choices=tuple(row[0] for row in ROOTS),
        default=[],
        help="limit the survey to one or more fighter names",
    )
    args = parser.parse_args()
    try:
        result = asyncio.run(
            survey(
                args.server,
                args.kind,
                set(args.fighter),
                args.decompile_timeout,
            )
        )
    except (IdaMcpError, OSError, RuntimeError, ValueError) as error:
        print(json.dumps({"ok": False, "error": str(error)}, indent=2))
        return 1
    rendered = json.dumps(result, indent=2) + "\n"
    if args.output:
        args.output.parent.mkdir(parents=True, exist_ok=True)
        args.output.write_text(rendered, encoding="utf-8")
    else:
        print(rendered, end="")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
