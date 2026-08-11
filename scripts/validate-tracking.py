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
