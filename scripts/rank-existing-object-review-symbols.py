#!/usr/bin/env python3
"""Rank review candidates already emitted by tracked VC8 probe objects.

This is discovery only, never exact acceptance.  It joins three independent
facts:
  * direct relative edges from canonical-exact target owners,
  * their configured decorated callee symbol names, and
  * symbols actually emitted by existing build/match-units/*.obj files.

Same-size output is a prioritization signal, not a match claim.  Every candidate
still needs canonical compare-function.py validation and origin review.
"""
from __future__ import annotations

import argparse
import importlib.util
import json
from pathlib import Path
import re
import subprocess
import sys
import tomllib
from typing import Any

ROOT = Path(__file__).resolve().parents[1]
UNITS = ROOT / "config" / "match-units.toml"
OBJECT_DIR = ROOT / "build" / "match-units"
CALLEE_CENSUS = ROOT / "scripts" / "rank-exact-owner-review-callees.py"

NM_LINE = re.compile(
    r"^(?P<object>.*?):(?P<address>[0-9A-Fa-f]+)\s+"
    r"(?P<size>[0-9A-Fa-f]+)\s+(?P<type>[A-Za-z])\s+(?P<name>.*)$"
)


def load_module(name: str, path: Path) -> Any:
    spec = importlib.util.spec_from_file_location(name, path)
    if spec is None or spec.loader is None:
        raise RuntimeError(f"cannot load {path}")
    module = importlib.util.module_from_spec(spec)
    sys.modules[name] = module
    spec.loader.exec_module(module)
    return module


def parse_nm_line(line: str) -> dict[str, Any] | None:
    match = NM_LINE.match(line)
    if match is None:
        return None
    if match.group("type").upper() != "T":
        return None
    return {
        "object": match.group("object"),
        "address": int(match.group("address"), 16),
        "size": int(match.group("size"), 16),
        "name": match.group("name"),
    }


def decorated_targets(units: dict[str, Any], review: set[int]) -> dict[str, set[int]]:
    output: dict[str, set[int]] = {}
    for unit in units.values():
        for function in unit.get("functions", []):
            for mapping in function.get("rel32_targets", []):
                name, separator, address_text = mapping.rpartition("=")
                if not separator:
                    continue
                try:
                    address = int(address_text, 0)
                except ValueError:
                    continue
                if address in review:
                    output.setdefault(name, set()).add(address)
    return output


def emitted_symbols(object_paths: list[Path]) -> dict[str, list[dict[str, Any]]]:
    if not object_paths:
        return {}
    completed = subprocess.run(
        ["nm", "-A", "-S", "--size-sort", *map(str, object_paths)],
        cwd=ROOT,
        capture_output=True,
        text=True,
        check=True,
    )
    output: dict[str, list[dict[str, Any]]] = {}
    for line in completed.stdout.splitlines():
        row = parse_nm_line(line)
        if row is not None:
            output.setdefault(row["name"], []).append(row)
    return output


def rank_rows(
    review_rows: dict[int, dict[str, Any]],
    names: dict[str, set[int]],
    emitted: dict[str, list[dict[str, Any]]],
) -> list[dict[str, Any]]:
    output = []
    for name, addresses in names.items():
        for symbol in emitted.get(name, []):
            for address in addresses:
                review = review_rows[address]
                target_size = int(review["candidate_size"])
                output.append(
                    {
                        "target": review["target"],
                        "target_size": target_size,
                        "owner_count": int(review["owner_count"]),
                        "edge_count": int(review["edge_count"]),
                        "symbol": name,
                        "object": symbol["object"],
                        "symbol_size": symbol["size"],
                        "size_delta": symbol["size"] - target_size,
                        "size_match": symbol["size"] == target_size,
                    }
                )
    output.sort(
        key=lambda row: (
            not row["size_match"],
            abs(row["size_delta"]),
            -row["owner_count"],
            row["target_size"],
            row["target"],
            row["object"],
        )
    )
    return output


def census() -> dict[str, Any]:
    callee = load_module("th105_existing_object_callee_census", CALLEE_CENSUS)
    direct = callee.census(include_nonreview=False, include_jumps=True)
    review_rows = {
        int(row["target"], 0): row
        for row in direct["rows"]
        if row["landing"] == "candidate_start" and row["disposition"] == "review"
    }
    units = tomllib.loads(UNITS.read_text(encoding="utf-8"))["units"]
    names = decorated_targets(units, set(review_rows))
    objects = sorted(OBJECT_DIR.glob("*.obj"))
    rows = rank_rows(review_rows, names, emitted_symbols(objects))
    return {
        "schema": "th105-existing-object-review-symbols-v1",
        "target_sha256": direct["target_sha256"],
        "exact_owner_count": direct["exact_owner_count"],
        "review_start_count": direct["landing_counts"]["candidate_start"],
        "object_count": len(objects),
        "emitted_candidate_rows": len(rows),
        "exact_size_rows": sum(row["size_match"] for row in rows),
        "rows": rows,
        "scope": "prioritization only; same-size emitted symbols require canonical byte comparison and independent origin review",
    }


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--json", action="store_true")
    parser.add_argument("--exact-size-only", action="store_true")
    args = parser.parse_args()
    try:
        result = census()
    except (OSError, RuntimeError, subprocess.CalledProcessError, TypeError, ValueError) as error:
        print(f"existing-object review ranking failed: {error}", file=sys.stderr)
        return 2
    rows = result["rows"]
    if args.exact_size_only:
        rows = [row for row in rows if row["size_match"]]
    if args.json:
        result = {**result, "rows": rows}
        print(json.dumps(result, indent=2))
        return 0
    print(
        f"Existing-object review symbols: objects={result['object_count']} "
        f"emitted={result['emitted_candidate_rows']} exact-size={result['exact_size_rows']} "
        f"review-starts={result['review_start_count']} exact-owners={result['exact_owner_count']}"
    )
    for row in rows:
        print(
            f"{row['target']} target={row['target_size']:4d} emitted={row['symbol_size']:4d} "
            f"delta={row['size_delta']:+4d} owners={row['owner_count']:3d} "
            f"{Path(row['object']).name} {row['symbol']}"
        )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
