#!/usr/bin/env python3
"""Rank direct callees shared by RTTI-owned roster Object giant roots.

This is target-backed candidate discovery, not exact-match acceptance. It decodes
canonical PE bytes for the fifteen Object primary-vtable +0x28 roots and counts
only direct relative calls leaving each root. The output is annotated from the
candidate/origin ledgers but does not trust either ledger for discovery: a
reachable target missing from functions.csv is reported explicitly.
"""
from __future__ import annotations

import argparse
import csv
import importlib.util
import json
from pathlib import Path
import sys
import tomllib
from typing import Any

from capstone import Cs, CS_ARCH_X86, CS_MODE_32, CS_GRP_CALL
from capstone.x86_const import X86_OP_IMM

ROOT = Path(__file__).resolve().parents[1]
TARGET = ROOT / "resources" / "th105.exe"
ANCHORS = ROOT / "config" / "roster-character-object-vtable-origin-anchors.toml"
FUNCTIONS = ROOT / "config" / "functions.csv"
ORIGINS = ROOT / "config" / "function-origins.csv"


def load_compare() -> Any:
    path = ROOT / "scripts" / "compare-function.py"
    spec = importlib.util.spec_from_file_location("th105_shared_callee_compare", path)
    if spec is None or spec.loader is None:
        raise RuntimeError(f"cannot load {path}")
    module = importlib.util.module_from_spec(spec)
    sys.modules[spec.name] = module
    spec.loader.exec_module(module)
    return module


def load_rows(path: Path) -> dict[int, dict[str, str]]:
    with path.open(newline="", encoding="utf-8") as handle:
        return {int(row["address"], 0): row for row in csv.DictReader(handle)}


def object_vslot28_roots() -> list[dict[str, Any]]:
    manifest = tomllib.loads(ANCHORS.read_text())
    roots = []
    for anchor in manifest["anchors"]:
        slots = [slot for slot in anchor.get("pointer_slots", []) if slot["slot_offset"] == "0x28"]
        if not slots:
            continue
        if len(slots) != 1:
            raise ValueError(f"{anchor['address']}: expected one +0x28 Object owner")
        roots.append({
            "owner": slots[0]["owner"],
            "address": int(anchor["address"], 0),
            "size": int(anchor["size"]),
        })
    if len(roots) != 15:
        raise ValueError(f"expected 15 roster Object +0x28 roots, got {len(roots)}")
    return roots


def direct_external_calls(code: bytes, address: int) -> dict[int, list[int]]:
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    decoder.detail = True
    instructions = list(decoder.disasm(code, address))
    if sum(insn.size for insn in instructions) != len(code):
        consumed = sum(insn.size for insn in instructions)
        raise ValueError(f"incomplete decode at {address + consumed:#x}")
    end = address + len(code)
    calls: dict[int, list[int]] = {}
    for insn in instructions:
        if not insn.group(CS_GRP_CALL) or not insn.operands:
            continue
        operand = insn.operands[0]
        if operand.type != X86_OP_IMM:
            continue
        target = operand.imm & 0xFFFFFFFF
        if address <= target < end:
            continue
        calls.setdefault(target, []).append(insn.address)
    return calls


def census(min_roots: int, include_matching: bool) -> dict[str, Any]:
    compare = load_compare()
    target_sha = compare.verify_target()
    functions = load_rows(FUNCTIONS)
    origins = load_rows(ORIGINS)
    usage: dict[int, dict[str, Any]] = {}
    roots = object_vslot28_roots()
    for root in roots:
        calls = direct_external_calls(compare.target_bytes(root["address"], root["size"]), root["address"])
        for target, sites in calls.items():
            record = usage.setdefault(target, {"root_sites": {}, "call_count": 0})
            record["root_sites"][root["owner"]] = sites
            record["call_count"] += len(sites)
    rows = []
    for address, use in usage.items():
        root_count = len(use["root_sites"])
        if root_count < min_roots:
            continue
        function = functions.get(address)
        if function is not None and function["status"] == "matching" and not include_matching:
            continue
        origin = origins.get(address)
        rows.append({
            "address": f"0x{address:08X}",
            "root_count": root_count,
            "call_count": use["call_count"],
            "roots": [
                {"owner": owner, "sites": [f"0x{site:08X}" for site in sites]}
                for owner, sites in sorted(use["root_sites"].items())
            ],
            "ledgered": function is not None,
            "name": None if function is None else (function["proposed_name"] or function["current_name"]),
            "status": None if function is None else function["status"],
            "origin": None if origin is None else origin["origin"],
            "disposition": None if origin is None else origin["disposition"],
        })
    rows.sort(key=lambda row: (-row["root_count"], -row["call_count"], row["address"]))
    return {
        "schema": "th105-roster-object-shared-callee-census-v1",
        "target_sha256": target_sha,
        "root_count": len(roots),
        "min_roots": min_roots,
        "include_matching": include_matching,
        "rows": rows,
        "unledgered_targets": [row["address"] for row in rows if not row["ledgered"]],
        "scope": "direct relative calls from canonical main spans of RTTI-owned Object +0x28 roots; indirect calls and remote chunks require separate review",
    }


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--min-roots", type=int, default=2)
    parser.add_argument("--include-matching", action="store_true")
    parser.add_argument("--json", action="store_true")
    args = parser.parse_args()
    if args.min_roots < 1:
        parser.error("--min-roots must be >= 1")
    try:
        result = census(args.min_roots, args.include_matching)
    except (OSError, RuntimeError, TypeError, ValueError) as exc:
        print(f"shared-callee census failed: {exc}", file=sys.stderr)
        return 2
    if args.json:
        print(json.dumps(result, indent=2))
    else:
        print(f"Object +0x28 shared direct callees: {len(result['rows'])} row(s); target {result['target_sha256']}")
        for row in result["rows"]:
            name = row["name"] or "<not in functions.csv>"
            status = row["status"] or "untracked"
            disposition = row["disposition"] or "untracked"
            print(f"{row['address']} roots={row['root_count']:2d} calls={row['call_count']:3d} {status:13s} {disposition:9s} {name}")
        if result["unledgered_targets"]:
            print("Unledgered direct targets: " + ", ".join(result["unledgered_targets"]))
    return 0

if __name__ == "__main__":
    raise SystemExit(main())
