#!/usr/bin/env python3
"""Export a fresh, provisional TH105 function inventory from attested IDA.

IDA function boundaries and auto-names are discovery evidence, not accepted
compiler/object boundaries.  This command intentionally does not merge any
previous ledger state: use it only when establishing or deliberately replacing
the baseline for the exact target in config/target.toml.
"""

from __future__ import annotations

import argparse
import asyncio
import csv
import json
from pathlib import Path
from typing import Any

from ida_mcp_client import IdaMcpError, call_json, open_session, parse_int, require_target


ROOT = Path(__file__).resolve().parents[1]
ANALYSIS = ROOT / ".analysis" / "ida-functions.json"
FUNCTIONS = ROOT / "config" / "functions.csv"
ORIGINS = ROOT / "config" / "function-origins.csv"
RECCMP = ROOT / "config" / "reccmp-functions.csv"

FUNCTION_FIELDS = [
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
ORIGIN_FIELDS = [
    "address",
    "origin",
    "subsystem",
    "disposition",
    "confidence",
    "evidence_id",
]


def canonical(value: int) -> str:
    return f"0x{value:08X}"


def normalize_page(payload: Any) -> tuple[list[dict[str, Any]], int | None]:
    if isinstance(payload, list):
        return payload, None
    if not isinstance(payload, dict) or not isinstance(payload.get("data"), list):
        raise IdaMcpError("tool_error", f"unexpected list_functions result: {payload!r}")
    next_offset = payload.get("next_offset")
    return payload["data"], None if next_offset is None else parse_int(next_offset)


async def read_inventory(server: str) -> tuple[dict[str, Any], list[dict[str, Any]]]:
    async with open_session(server) as (session, _initialized):
        metadata = await require_target(session)
        rows: list[dict[str, Any]] = []
        offset = 0
        while True:
            payload = await call_json(
                session, "list_functions", {"offset": offset, "count": 1000}
            )
            page, next_offset = normalize_page(payload)
            rows.extend(page)
            if next_offset is None:
                break
            if next_offset <= offset:
                raise IdaMcpError(
                    "tool_error", f"list_functions did not advance: {next_offset}"
                )
            offset = next_offset
        return metadata, rows


def validate_rows(raw_rows: list[dict[str, Any]]) -> list[dict[str, Any]]:
    rows: list[dict[str, Any]] = []
    seen: set[int] = set()
    for raw in raw_rows:
        address = parse_int(raw.get("address"))
        size = parse_int(raw.get("size"))
        name = str(raw.get("name", ""))
        if address in seen or size <= 0 or not name:
            raise ValueError(f"invalid or duplicate IDA function row: {raw!r}")
        seen.add(address)
        rows.append({"address": address, "size": size, "name": name})
    rows.sort(key=lambda row: row["address"])
    return rows


def write_inventory(metadata: dict[str, Any], rows: list[dict[str, Any]]) -> None:
    ANALYSIS.parent.mkdir(parents=True, exist_ok=True)
    ANALYSIS.write_text(
        json.dumps({"target": metadata, "functions": rows}, indent=2) + "\n",
        encoding="utf-8",
    )

    with FUNCTIONS.open("w", newline="", encoding="utf-8") as stream:
        writer = csv.DictWriter(stream, fieldnames=FUNCTION_FIELDS, lineterminator="\n")
        writer.writeheader()
        for raw in rows:
            address = raw["address"]
            size = raw["size"]
            writer.writerow(
                {
                    "address": canonical(address),
                    "size": size,
                    "span_end": canonical(address + size - 1),
                    "current_name": raw["name"],
                    "status": "unclassified",
                    "match_percent": "0.00",
                    "is_thunk": "false",
                    "evidence": "IDA 1.06a auto-analysis candidate; boundary unreviewed",
                }
            )

    with ORIGINS.open("w", newline="", encoding="utf-8") as stream:
        writer = csv.DictWriter(stream, fieldnames=ORIGIN_FIELDS, lineterminator="\n")
        writer.writeheader()
        for raw in rows:
            writer.writerow(
                {
                    "address": canonical(raw["address"]),
                    "origin": "unknown",
                    "subsystem": "",
                    "disposition": "review",
                    "confidence": "unknown",
                    "evidence_id": "ida-1.06a-initial-inventory",
                }
            )

    # Auto-generated sub_* labels are not durable semantic mappings.
    RECCMP.write_text("name,address,type\n", encoding="utf-8")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--server", default="ida-pro-mcp")
    parser.add_argument(
        "--write",
        action="store_true",
        help="replace the current target-dependent inventory ledgers",
    )
    args = parser.parse_args()
    if not args.write:
        parser.error("refusing to replace inventory without --write")
    try:
        metadata, raw_rows = asyncio.run(read_inventory(args.server))
        rows = validate_rows(raw_rows)
        write_inventory(metadata, rows)
    except (IdaMcpError, OSError, TypeError, ValueError) as exc:
        print(f"error: IDA inventory export failed: {exc}")
        return 1
    print(f"wrote {len(rows)} provisional IDA functions")
    print(f"scratch: {ANALYSIS.relative_to(ROOT)}")
    print(f"ledger: {FUNCTIONS.relative_to(ROOT)}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
