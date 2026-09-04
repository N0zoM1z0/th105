#!/usr/bin/env python3
"""Report TH105 candidate classification, source presence, and exact coverage."""

from __future__ import annotations

import argparse
import csv
import json
from pathlib import Path
import tomllib

from function_byte_ownership import exact_extra_bytes, load as load_byte_ownership, owned_size


ROOT = Path(__file__).resolve().parents[1]
CONFIG = ROOT / "config"


def dict_rows(name: str) -> list[dict[str, str]]:
    with (CONFIG / name).open(newline="", encoding="utf-8") as stream:
        return list(csv.DictReader(stream))


def load() -> tuple[list[dict[str, object]], dict[str, object]]:
    functions = dict_rows("functions.csv")
    function_map = {int(row["address"], 0): row for row in functions}
    ownership = load_byte_ownership(function_map)
    origins = {row["address"]: row for row in dict_rows("function-origins.csv")}
    mapped = {row["address"]: row for row in dict_rows("reccmp-functions.csv")}
    exact = {row["address"]: row for row in dict_rows("matches.csv")}
    with (CONFIG / "implemented.csv").open(newline="", encoding="utf-8") as stream:
        implemented = {row[0] for row in csv.reader(stream) if row}
    with (CONFIG / "match-units.toml").open("rb") as stream:
        manifest = tomllib.load(stream)
    units: dict[str, list[str]] = {}
    for name, unit in manifest.get("units", {}).items():
        for function in unit.get("functions", []):
            units.setdefault(function["address"], []).append(name)

    rows: list[dict[str, object]] = []
    for function in functions:
        address = function["address"]
        origin = origins[address]
        mapping = mapped.get(address)
        name = mapping["name"] if mapping else function["current_name"]
        category = (
            "authored"
            if origin["disposition"] == "authored"
            else "excluded"
            if origin["disposition"] == "exclude"
            else "review"
        )
        main_size = int(function["size"], 0)
        numeric_address = int(address, 0)
        rows.append(
            {
                "address": address,
                "size": main_size,
                "owned_bytes": owned_size(numeric_address, main_size, ownership),
                "remote_bytes": int(ownership.get(numeric_address, {}).get("remote_bytes", 0)),
                "name": name,
                "status": function["status"],
                "category": category,
                "origin": origin["origin"],
                "mapped": mapping is not None,
                "source_present": bool(mapping and name in implemented),
                "exact": address in exact,
                "units": sorted(units.get(address, [])),
            }
        )

    summary: dict[str, object] = {
        "candidates": len(rows),
        "candidate_bytes": sum(int(row["size"]) for row in rows),
        "review": sum(row["category"] == "review" for row in rows),
        "authored": sum(row["category"] == "authored" for row in rows),
        "authored_bytes": sum(int(row["owned_bytes"]) for row in rows if row["category"] == "authored"),
        "remote_authored_bytes": sum(int(row["remote_bytes"]) for row in rows if row["category"] == "authored"),
        "excluded": sum(row["category"] == "excluded" for row in rows),
        "mapped": sum(bool(row["mapped"]) for row in rows),
        "source_present": sum(bool(row["source_present"]) for row in rows),
        "exact_functions": sum(bool(row["exact"]) for row in rows),
        "exact_bytes": sum(
            int(row["size"]) + exact_extra_bytes(int(str(row["address"]), 0), ownership)
            for row in rows
            if row["exact"]
        ),
        "configured_units": len(manifest.get("units", {})),
    }
    return rows, summary


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--summary", action="store_true")
    parser.add_argument("--json", action="store_true")
    parser.add_argument(
        "--category", choices=("all", "review", "authored", "excluded"), default="all"
    )
    parser.add_argument(
        "--state",
        choices=("all", "unmapped", "source-missing", "non-exact", "without-unit"),
        default="all",
    )
    parser.add_argument("--sort", choices=("address", "size"), default="address")
    args = parser.parse_args()
    try:
        rows, summary = load()
    except (OSError, KeyError, TypeError, ValueError, tomllib.TOMLDecodeError) as exc:
        print(f"error: status report failed: {exc}")
        return 1
    selected = [
        row for row in rows if args.category == "all" or row["category"] == args.category
    ]
    if args.state == "unmapped":
        selected = [row for row in selected if not row["mapped"]]
    elif args.state == "source-missing":
        selected = [row for row in selected if row["category"] == "authored" and not row["source_present"]]
    elif args.state == "non-exact":
        selected = [row for row in selected if not row["exact"]]
    elif args.state == "without-unit":
        selected = [row for row in selected if not row["units"]]
    selected.sort(
        key=(lambda row: int(str(row["address"]), 0))
        if args.sort == "address"
        else lambda row: (-int(row["size"]), int(str(row["address"]), 0))
    )
    if args.json:
        payload: dict[str, object] = {"summary": summary}
        if not args.summary:
            payload["rows"] = selected
        print(json.dumps(payload, indent=2))
    elif args.summary:
        print(
            f"Candidates: {summary['candidates']} provisional; "
            f"review {summary['review']}, authored {summary['authored']}, "
            f"excluded {summary['excluded']}"
        )
        print(
            f"Reconstruction: mapped {summary['mapped']}, source "
            f"{summary['source_present']}, exact {summary['exact_functions']} "
            f"({summary['exact_bytes']} bytes), units {summary['configured_units']}"
        )
    else:
        for row in selected:
            units = ",".join(row["units"]) or "-"
            print(
                f"{row['address']}\t{row['size']}\t{row['category']}\t"
                f"mapped={int(row['mapped'])}\tsource={int(row['source_present'])}\t"
                f"exact={int(row['exact'])}\tunit={units}\t{row['name']}"
            )
        print(f"rows={len(selected)}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
