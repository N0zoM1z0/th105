#!/usr/bin/env python3
"""Merge Ghidra's function inventory with durable reconstruction metadata."""

from __future__ import annotations

import csv
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
GHIDRA = ROOT / ".analysis" / "ghidra-functions.csv"
OUTPUT = ROOT / "config" / "functions.csv"
KNOWN = ROOT / "config" / "known-symbols.csv"
RECCMP = ROOT / "config" / "reccmp-functions.csv"

FIELDS = [
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
MANUAL_FIELDS = {
    "proposed_name",
    "module",
    "status",
    "match_percent",
    "calling_convention",
    "signature",
    "source_file",
    "evidence",
    "owner",
    "notes",
}


def canonical(value: str) -> str:
    return f"0x{int(value, 16):08X}"


def read_index(path: Path) -> dict[str, dict[str, str]]:
    if not path.exists():
        return {}
    with path.open(newline="", encoding="utf-8") as stream:
        return {canonical(row["address"]): row for row in csv.DictReader(stream)}


def main() -> int:
    if not GHIDRA.exists():
        raise SystemExit(f"missing {GHIDRA}; run scripts/export-function-inventory.sh")

    existing = read_index(OUTPUT)
    known = read_index(KNOWN)
    rows: list[dict[str, str]] = []

    with GHIDRA.open(newline="", encoding="utf-8") as stream:
        for raw in csv.DictReader(stream):
            address = canonical(raw["address"])
            row = {field: "" for field in FIELDS}
            row.update({field: raw.get(field, "") for field in FIELDS})
            row["address"] = address
            row["span_end"] = canonical(raw["span_end"])
            row["status"] = "unclassified"
            row["match_percent"] = "0.00"

            old = existing.get(address)
            if old:
                for field in MANUAL_FIELDS:
                    row[field] = old.get(field, row[field])

            seed = known.get(address)
            if seed:
                row["proposed_name"] = row["proposed_name"] or seed["name"]
                row["module"] = row["module"] or seed["module"]
                row["evidence"] = row["evidence"] or seed["evidence"]
                if row["status"] == "unclassified":
                    row["status"] = "identified"

            rows.append(row)

    rows.sort(key=lambda row: int(row["address"], 16))
    with OUTPUT.open("w", newline="", encoding="utf-8") as stream:
        writer = csv.DictWriter(stream, fieldnames=FIELDS, lineterminator="\n")
        writer.writeheader()
        writer.writerows(rows)

    with RECCMP.open("w", newline="", encoding="utf-8") as stream:
        writer = csv.writer(stream, lineterminator="\n")
        writer.writerow(["name", "address", "type"])
        for row in rows:
            if row["proposed_name"]:
                writer.writerow([row["proposed_name"], row["address"], "function"])

    print(f"wrote {len(rows)} functions to {OUTPUT.relative_to(ROOT)}")
    print(f"wrote supported names to {RECCMP.relative_to(ROOT)}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
