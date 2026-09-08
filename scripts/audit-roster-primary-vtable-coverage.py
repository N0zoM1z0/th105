#!/usr/bin/env python3
"""Audit raw roster primary-vtable slots against the provisional candidate ledger.

This is a boundary-coverage audit, not origin or exactness evidence by itself.
It reads the SHA-pinned target PE directly, reconstructs the fifteen Fighter and
fifteen Object primary-vtable bases from their RTTI-backed origin-anchor files,
and classifies every configured primary-vtable code pointer as a candidate
start, an interior pointer, or an unledgered pointer.
"""
from __future__ import annotations

import argparse
import bisect
import csv
import importlib.util
import json
from pathlib import Path
import struct
import sys
import tomllib
from typing import Any

ROOT = Path(__file__).resolve().parents[1]
FUNCTIONS = ROOT / "config" / "functions.csv"
SURFACES = (
    ("fighter", ROOT / "config" / "roster-fighter-vtable-origin-anchors.toml", 0x60),
    ("object", ROOT / "config" / "roster-character-object-vtable-origin-anchors.toml", 0x44),
)


def load_compare() -> Any:
    path = ROOT / "scripts" / "compare-function.py"
    spec = importlib.util.spec_from_file_location("th105_vtable_coverage_compare", path)
    if spec is None or spec.loader is None:
        raise RuntimeError(f"cannot load {path}")
    module = importlib.util.module_from_spec(spec)
    sys.modules[spec.name] = module
    spec.loader.exec_module(module)
    return module


def load_ledger() -> tuple[dict[int, dict[str, str]], list[tuple[int, int, dict[str, str]]]]:
    with FUNCTIONS.open(newline="", encoding="utf-8") as handle:
        rows = list(csv.DictReader(handle))
    starts = {int(row["address"], 0): row for row in rows}
    spans = sorted((int(row["address"], 0), int(row["span_end"], 0) + 1, row) for row in rows)
    return starts, spans


def containing_row(address: int, spans: list[tuple[int, int, dict[str, str]]]) -> dict[str, str] | None:
    starts = [span[0] for span in spans]
    index = bisect.bisect_right(starts, address) - 1
    if index >= 0 and spans[index][0] <= address < spans[index][1]:
        return spans[index][2]
    return None


def vtable_bases(path: Path) -> dict[str, int]:
    manifest = tomllib.loads(path.read_text())
    bases: dict[str, int] = {}
    for anchor in manifest["anchors"]:
        for slot in anchor.get("pointer_slots", []):
            owner = slot["owner"]
            base = int(slot["address"], 0) - int(slot["slot_offset"], 0)
            if owner in bases and bases[owner] != base:
                raise ValueError(f"{owner}: inconsistent primary-vtable base")
            bases[owner] = base
    if len(bases) != 15:
        raise ValueError(f"{path.name}: expected 15 primary vtables, got {len(bases)}")
    return bases


def audit_surface(compare: Any, name: str, path: Path, byte_length: int,
                  starts: dict[int, dict[str, str]],
                  spans: list[tuple[int, int, dict[str, str]]]) -> dict[str, Any]:
    usage: dict[int, list[dict[str, Any]]] = {}
    bases = vtable_bases(path)
    for owner, base in sorted(bases.items()):
        data = compare.target_bytes(base, byte_length)
        for offset in range(0, byte_length, 4):
            pointer = struct.unpack_from("<I", data, offset)[0]
            usage.setdefault(pointer, []).append({
                "owner": owner,
                "slot_offset": f"0x{offset:02X}",
                "slot_address": f"0x{base + offset:08X}",
            })

    rows = []
    for address, slots in sorted(usage.items()):
        row = starts.get(address)
        containing = None if row is not None else containing_row(address, spans)
        if row is not None:
            classification = "ledger_start"
            ledger_address = row["address"]
            ledger_name = row["proposed_name"] or row["current_name"]
        elif containing is not None:
            classification = "ledger_interior"
            ledger_address = containing["address"]
            ledger_name = containing["proposed_name"] or containing["current_name"]
        else:
            classification = "unledgered"
            ledger_address = None
            ledger_name = None
        rows.append({
            "address": f"0x{address:08X}",
            "classification": classification,
            "ledger_address": ledger_address,
            "ledger_name": ledger_name,
            "slots": slots,
        })
    return {
        "surface": name,
        "owner_count": len(bases),
        "slot_count": len(bases) * (byte_length // 4),
        "unique_pointer_count": len(rows),
        "ledger_start_count": sum(row["classification"] == "ledger_start" for row in rows),
        "ledger_interior": [row for row in rows if row["classification"] == "ledger_interior"],
        "unledgered": [row for row in rows if row["classification"] == "unledgered"],
        "rows": rows,
    }


def audit() -> dict[str, Any]:
    compare = load_compare()
    target_sha = compare.verify_target()
    starts, spans = load_ledger()
    surfaces = [audit_surface(compare, name, path, byte_length, starts, spans)
                for name, path, byte_length in SURFACES]
    return {
        "schema": "th105-roster-primary-vtable-coverage-v1",
        "target_sha256": target_sha,
        "surfaces": surfaces,
        "scope": "raw canonical primary-vtable dwords only; start/interior/unledgered boundary coverage, not origin or exactness acceptance",
    }


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--json", action="store_true")
    args = parser.parse_args()
    try:
        result = audit()
    except (KeyError, OSError, RuntimeError, TypeError, ValueError) as error:
        print(f"vtable coverage audit failed: {error}", file=sys.stderr)
        return 2
    if args.json:
        print(json.dumps(result, indent=2))
    else:
        print(f"target {result['target_sha256']}")
        for surface in result["surfaces"]:
            print(
                f"{surface['surface']}: {surface['slot_count']} slots, "
                f"{surface['unique_pointer_count']} unique pointers, "
                f"{surface['ledger_start_count']} ledger starts, "
                f"{len(surface['ledger_interior'])} interior, "
                f"{len(surface['unledgered'])} unledgered"
            )
            for row in surface["ledger_interior"] + surface["unledgered"]:
                print(f"  {row['address']} {row['classification']} {row['ledger_name'] or '<none>'}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
