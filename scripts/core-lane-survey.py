#!/usr/bin/env python3
"""Survey selected core-framework lanes through one attested IDA MCP session."""

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
CORE_FUNCTIONS = ROOT / "config" / "core-functions.csv"
FUNCTIONS = ROOT / "config" / "functions.csv"

CASE_RE = re.compile(r"\bcase\s+(-?(?:0x[0-9a-fA-F]+|\d+))\s*:")
STRING_RE = re.compile(r'"((?:[^"\\]|\\.)*)"')
FIELD_RE = re.compile(r"(?:this|a1|v\d+)\s*\+\s*(0x[0-9a-fA-F]+|\d+)")


def read_rows(path: Path) -> list[dict[str, str]]:
    with path.open(newline="", encoding="utf-8") as stream:
        return list(csv.DictReader(stream))


def integer(value: str) -> int:
    return int(value, 0)


def flatten_functions(value: Any) -> list[dict[str, str]]:
    rows = value if isinstance(value, list) else [value]
    result: list[dict[str, str]] = []
    for row in rows:
        if not isinstance(row, dict):
            continue
        function = row.get("function")
        if isinstance(function, dict):
            row = function
        address = row.get("address") or row.get("start_ea")
        if address is None:
            continue
        result.append(
            {
                "address": str(address),
                "name": str(row.get("name") or row.get("function_name") or ""),
            }
        )
    return result


async def survey(server: str, lanes: set[str]) -> dict[str, object]:
    ledger = {row["address"].upper(): row for row in read_rows(FUNCTIONS)}
    selected = [row for row in read_rows(CORE_FUNCTIONS) if row["lane"] in lanes]
    async with open_session(server) as (session, initialized):
        tools = {tool.name for tool in (await session.list_tools()).tools}
        required = {
            "get_function_by_address",
            "decompile_function",
            "get_callees",
            "get_callers",
        }
        missing = sorted(required - tools)
        if missing:
            raise IdaMcpError("missing_tool", f"IDA MCP missing required tools: {missing}")
        before = await require_target(session)
        entries: list[dict[str, object]] = []
        for core in selected:
            address = core["address"]
            tracked = ledger.get(address.upper())
            if tracked is None:
                raise RuntimeError(f"missing ledger address: {address}")
            try:
                function = await call_json(
                    session, "get_function_by_address", {"address": address}
                )
                decompile = await call_json(
                    session, "decompile_function", {"address": address}
                )
                callees = await call_json(
                    session, "get_callees", {"function_address": address}
                )
                callers = await call_json(
                    session, "get_callers", {"function_address": address}
                )
            except IdaMcpError as error:
                entries.append(
                    {
                        "lane": core["lane"],
                        "priority": int(core["priority"]),
                        "address": address,
                        "ledger_name": tracked["proposed_name"] or tracked["current_name"],
                        "status": tracked["status"],
                        "ledger_size": int(tracked["size"]),
                        "query_error": str(error),
                        "core_notes": core["notes"],
                    }
                )
                continue
            text = decompile if isinstance(decompile, str) else json.dumps(decompile)
            backend_size = (
                parse_int(function.get("size")) if isinstance(function, dict) else -1
            )
            entries.append(
                {
                    "lane": core["lane"],
                    "priority": int(core["priority"]),
                    "address": address,
                    "ledger_name": tracked["proposed_name"] or tracked["current_name"],
                    "status": tracked["status"],
                    "ledger_size": int(tracked["size"]),
                    "backend_size": backend_size,
                    "boundary_agrees": backend_size == int(tracked["size"]),
                    "backend_name": (
                        function.get("name") if isinstance(function, dict) else None
                    ),
                    "decompiler_lines": text.count("\n") + 1,
                    "switch_cases": sorted({integer(value) for value in CASE_RE.findall(text)}),
                    "field_offsets": sorted({integer(value) for value in FIELD_RE.findall(text)}),
                    "string_literals": sorted(
                        {value for value in STRING_RE.findall(text) if value}
                    ),
                    "callees": flatten_functions(callees),
                    "callers": flatten_functions(callers),
                    "core_notes": core["notes"],
                }
            )
        after = await require_target(session)
        fields = ("sha256", "md5", "base", "filesize", "path", "module")
        if any(before.get(field) != after.get(field) for field in fields):
            raise IdaMcpError("target_mismatch", "IDA target changed during core-lane survey")
        return {
            "schema_version": 1,
            "backend": "ida",
            "protocol_version": initialized.protocolVersion,
            "target": before,
            "lanes": sorted(lanes),
            "entries": entries,
        }


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--server", default=DEFAULT_SERVER)
    parser.add_argument("--lane", action="append", required=True)
    parser.add_argument("--output", type=Path)
    args = parser.parse_args()
    try:
        result = asyncio.run(survey(args.server, set(args.lane)))
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
