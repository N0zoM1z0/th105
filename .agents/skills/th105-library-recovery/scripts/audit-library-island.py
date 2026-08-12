#!/usr/bin/env python3
"""Audit one TH105 external-code island without changing repository state."""

from __future__ import annotations

import argparse
import csv
import json
from pathlib import Path
from statistics import median


ROOT = Path(__file__).resolve().parents[4]
FUNCTIONS = ROOT / "config" / "functions.csv"
ORIGINS = ROOT / "config" / "function-origins.csv"


def read_csv(path: Path) -> list[dict[str, str]]:
    with path.open(newline="", encoding="utf-8") as handle:
        return list(csv.DictReader(handle))


def percentile_nearest_rank(values: list[int], percent: int) -> int:
    ordered = sorted(values)
    index = max(0, (len(ordered) * percent + 99) // 100 - 1)
    return ordered[index]


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Measure a verified library island from the TH105 ledgers."
    )
    selector = parser.add_mutually_exclusive_group(required=True)
    selector.add_argument("--evidence-id", help="exact function-origins evidence_id")
    selector.add_argument("--origin", help="origin value such as third_party")
    selector.add_argument("--subsystem", help="subsystem value such as audio")
    parser.add_argument("--top", type=int, default=10, help="largest rows to show")
    parser.add_argument("--json", action="store_true", help="emit JSON")
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    functions = read_csv(FUNCTIONS)
    origins = read_csv(ORIGINS)
    function_addresses = [row["address"] for row in functions]
    origin_addresses = [row["address"] for row in origins]
    if function_addresses != origin_addresses:
        raise SystemExit(
            "config/function-origins.csv is stale or out of ledger order; "
            "run python3 scripts/function-origins.py --check"
        )

    combined = [dict(function, **origin) for function, origin in zip(functions, origins)]
    key, value = next(
        (name, getattr(args, name))
        for name in ("evidence_id", "origin", "subsystem")
        if getattr(args, name) is not None
    )
    selected = [row for row in combined if row[key] == value]
    if not selected:
        raise SystemExit(f"no rows matched {key}={value!r}")

    sizes = [int(row["size"]) for row in selected]
    exact = [row for row in selected if row["match_percent"] == "100.00"]
    named = [row for row in selected if row["proposed_name"]]
    sourced = [row for row in selected if row["source_file"]]
    all_library_exact = [
        row
        for row in functions
        if row["status"] == "library" and row["match_percent"] == "100.00"
    ]
    all_function_bytes = sum(int(row["size"]) for row in functions)

    largest = sorted(selected, key=lambda row: int(row["size"]), reverse=True)[: args.top]
    result = {
        "selector": {key: value},
        "address_start": min(selected, key=lambda row: int(row["address"], 16))["address"],
        "address_end": max(selected, key=lambda row: int(row["address"], 16))["span_end"],
        "functions": len(selected),
        "bytes": sum(sizes),
        "status_counts": {
            status: sum(row["status"] == status for row in selected)
            for status in sorted({row["status"] for row in selected})
        },
        "named_functions": len(named),
        "sourced_functions": len(sourced),
        "exact_library_functions": len(exact),
        "exact_library_bytes": sum(int(row["size"]) for row in exact),
        "size_distribution": {
            "min": min(sizes),
            "median": median(sizes),
            "p75": percentile_nearest_rank(sizes, 75),
            "p90": percentile_nearest_rank(sizes, 90),
            "max": max(sizes),
        },
        "repository_library_exact": {
            "functions": len(all_library_exact),
            "bytes": sum(int(row["size"]) for row in all_library_exact),
            "all_function_bytes": all_function_bytes,
        },
        "largest": [
            {
                "address": row["address"],
                "size": int(row["size"]),
                "name": row["proposed_name"] or row["current_name"],
                "status": row["status"],
                "match_percent": row["match_percent"],
            }
            for row in largest
        ],
    }

    if args.json:
        print(json.dumps(result, indent=2, sort_keys=True))
        return 0

    print(f"selector: {key}={value}")
    print(f"range: {result['address_start']}..{result['address_end']}")
    print(f"island: {result['functions']} functions, {result['bytes']:,} bytes")
    print(f"status: {result['status_counts']}")
    print(f"named/source: {len(named)}/{len(sourced)}")
    print(
        "island exact-library: "
        f"{len(exact)} functions, {result['exact_library_bytes']:,} bytes"
    )
    print(
        "repository exact-library: "
        f"{len(all_library_exact)} functions, "
        f"{result['repository_library_exact']['bytes']:,} / "
        f"{all_function_bytes:,} all-function bytes"
    )
    dist = result["size_distribution"]
    print(
        "sizes: "
        f"min={dist['min']} median={dist['median']} p75={dist['p75']} "
        f"p90={dist['p90']} max={dist['max']}"
    )
    print("largest:")
    for row in result["largest"]:
        print(
            f"  {row['address']} {row['size']:5d} "
            f"{row['match_percent']:>6} {row['name']}"
        )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
