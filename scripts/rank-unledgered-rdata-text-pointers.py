#!/usr/bin/env python3
"""Rank aligned .rdata pointers into .text that are outside tracked code ownership.

The scanner reads the SHA-pinned PE directly and deliberately does not trust IDA
function discovery. Candidate main spans from functions.csv plus reviewed remote
chunks from function-byte-ownership.toml define current code ownership. Aligned
.rdata dwords that point into .text are classified as candidate starts, owned
interiors, or uncovered targets. Uncovered targets are discovery leads only:
compiler startup/EH tables, deleting destructors, jump-table data and authored
callbacks all occur on this surface and require provenance review.
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
BYTE_OWNERSHIP = ROOT / "config" / "function-byte-ownership.toml"


def load_compare() -> Any:
    path = ROOT / "scripts" / "compare-function.py"
    spec = importlib.util.spec_from_file_location("th105_rdata_pointer_compare", path)
    if spec is None or spec.loader is None:
        raise RuntimeError(f"cannot load {path}")
    module = importlib.util.module_from_spec(spec)
    sys.modules[spec.name] = module
    spec.loader.exec_module(module)
    return module


def pe_sections(data: bytes) -> dict[str, dict[str, int]]:
    pe = struct.unpack_from("<I", data, 0x3C)[0]
    count = struct.unpack_from("<H", data, pe + 6)[0]
    optional_size = struct.unpack_from("<H", data, pe + 20)[0]
    table = pe + 24 + optional_size
    image_base = struct.unpack_from("<I", data, pe + 52)[0]
    result: dict[str, dict[str, int]] = {}
    for index in range(count):
        offset = table + 40 * index
        name = data[offset : offset + 8].split(b"\0", 1)[0].decode("ascii")
        virtual_size, rva, raw_size, raw_pointer = struct.unpack_from("<IIII", data, offset + 8)
        result[name] = {
            "start": image_base + rva,
            "end": image_base + rva + max(virtual_size, raw_size),
            "raw_size": raw_size,
            "raw_pointer": raw_pointer,
        }
    return result


def load_ownership() -> tuple[dict[int, dict[str, str]], list[tuple[int, int, str, str]]]:
    with FUNCTIONS.open(newline="", encoding="utf-8") as handle:
        rows = list(csv.DictReader(handle))
    starts = {int(row["address"], 0): row for row in rows}
    spans: list[tuple[int, int, str, str]] = [
        (int(row["address"], 0), int(row["span_end"], 0) + 1, "main", row["address"])
        for row in rows
    ]
    ownership = tomllib.loads(BYTE_OWNERSHIP.read_text())
    for function in ownership.get("functions", []):
        owner = function["address"]
        for chunk in function.get("chunks", []):
            spans.append((int(chunk["start"], 0), int(chunk["end"], 0) + 1, "remote", owner))
    spans.sort()
    return starts, spans


def containing_span(address: int, spans: list[tuple[int, int, str, str]]) -> tuple[int, int, str, str] | None:
    span_starts = [span[0] for span in spans]
    index = bisect.bisect_right(span_starts, address) - 1
    if index >= 0 and spans[index][0] <= address < spans[index][1]:
        return spans[index]
    return None


def census() -> dict[str, Any]:
    compare = load_compare()
    target_sha = compare.verify_target()
    data = (ROOT / "resources" / "th105.exe").read_bytes()
    sections = pe_sections(data)
    if ".text" not in sections or ".rdata" not in sections:
        raise ValueError("target must contain .text and .rdata")
    text = sections[".text"]
    rdata = sections[".rdata"]
    starts, spans = load_ownership()
    blob = data[rdata["raw_pointer"] : rdata["raw_pointer"] + rdata["raw_size"]]
    if len(blob) != rdata["raw_size"]:
        raise ValueError("target .rdata raw data is truncated")

    targets: dict[int, list[int]] = {}
    for offset in range(0, len(blob) - 3, 4):
        pointer = struct.unpack_from("<I", blob, offset)[0]
        if text["start"] <= pointer < text["end"]:
            targets.setdefault(pointer, []).append(rdata["start"] + offset)

    rows = []
    for address, sites in sorted(targets.items()):
        row = starts.get(address)
        span = None if row is not None else containing_span(address, spans)
        if row is not None:
            classification = "ledger_start"
            owner = row["address"]
            name = row["proposed_name"] or row["current_name"]
            ownership_kind = "main"
        elif span is not None:
            classification = "owned_interior"
            owner = span[3]
            owner_row = starts.get(int(owner, 0))
            name = None if owner_row is None else (owner_row["proposed_name"] or owner_row["current_name"])
            ownership_kind = span[2]
        else:
            classification = "uncovered"
            owner = None
            name = None
            ownership_kind = None
        rows.append({
            "address": f"0x{address:08X}",
            "classification": classification,
            "reference_count": len(sites),
            "reference_sites": [f"0x{site:08X}" for site in sites],
            "owner": owner,
            "owner_name": name,
            "ownership_kind": ownership_kind,
        })
    uncovered = [row for row in rows if row["classification"] == "uncovered"]
    uncovered.sort(key=lambda row: (-row["reference_count"], row["address"]))
    return {
        "schema": "th105-rdata-text-pointer-census-v1",
        "target_sha256": target_sha,
        "text_range": [f"0x{text['start']:08X}", f"0x{text['end']:08X}"],
        "rdata_range": [f"0x{rdata['start']:08X}", f"0x{rdata['end']:08X}"],
        "unique_text_pointer_count": len(rows),
        "ledger_start_count": sum(row["classification"] == "ledger_start" for row in rows),
        "owned_interior_count": sum(row["classification"] == "owned_interior" for row in rows),
        "uncovered_count": len(uncovered),
        "uncovered": uncovered,
        "scope": "aligned canonical .rdata dwords only; uncovered pointers are discovery leads and receive no authored/exact credit without independent provenance",
    }


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--json", action="store_true")
    parser.add_argument("--limit", type=int, default=50)
    args = parser.parse_args()
    if args.limit < 0:
        parser.error("--limit must be >= 0")
    try:
        result = census()
    except (KeyError, OSError, RuntimeError, TypeError, ValueError, struct.error) as error:
        print(f"rdata pointer census failed: {error}", file=sys.stderr)
        return 2
    if args.json:
        print(json.dumps(result, indent=2))
    else:
        print(
            f"target {result['target_sha256']}: {result['unique_text_pointer_count']} unique .rdata->.text pointers; "
            f"{result['ledger_start_count']} starts, {result['owned_interior_count']} owned interiors, "
            f"{result['uncovered_count']} uncovered"
        )
        for row in result["uncovered"][:args.limit]:
            sites = ",".join(row["reference_sites"][:4])
            suffix = "..." if len(row["reference_sites"]) > 4 else ""
            print(f"{row['address']} refs={row['reference_count']:3d} sites={sites}{suffix}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
