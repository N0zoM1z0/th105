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


def read_rows(path: Path) -> list[dict[str, str]]:
    with path.open(newline="", encoding="utf-8") as stream:
        return list(csv.DictReader(stream))


def canonical(value: str) -> str:
    return f"0x{int(value, 16):08X}"


def main() -> int:
    errors: list[str] = []
    rows = read_rows(FUNCTIONS)
    addresses: set[str] = set()
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

        status = row["status"]
        if status not in STATUSES:
            errors.append(f"functions.csv:{line}: invalid status {status!r}")
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

    for path in (KNOWN, CLAIMS):
        for line, row in enumerate(read_rows(path), 2):
            address = canonical(row["address"])
            if address not in addresses:
                if path == KNOWN and row.get("confidence") == "internal":
                    continue
                errors.append(f"{path.name}:{line}: address {address} is absent from functions.csv")

    if errors:
        print("\n".join(errors))
        return 1
    print(f"tracking OK: {len(rows)} functions, {len(read_rows(CLAIMS))} active claims")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
