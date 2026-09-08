#!/usr/bin/env python3
"""Rank direct targets reached from canonical-exact authored functions.

This is candidate/origin discovery, never exact-match acceptance.  It decodes
only the current SHA-pinned PE bytes owned by functions whose ledger status is
`matching`, records direct CALL/JMP edges leaving each exact span, and then
joins the landing address against the candidate and origin ledgers.

A landing exactly at a candidate start is reported separately from a landing in
the interior of a candidate.  Interior targets are evidence to inspect (for
remote chunks/private entries), not automatic new function boundaries.
"""
from __future__ import annotations

import argparse
import csv
import importlib.util
import json
from pathlib import Path
import sys
from typing import Any

from capstone import Cs, CS_ARCH_X86, CS_MODE_32, CS_GRP_CALL, CS_GRP_JUMP
from capstone.x86_const import X86_OP_IMM

ROOT = Path(__file__).resolve().parents[1]
TARGET = ROOT / "resources" / "th105.exe"
FUNCTIONS = ROOT / "config" / "functions.csv"
ORIGINS = ROOT / "config" / "function-origins.csv"


def load_compare() -> Any:
    path = ROOT / "scripts" / "compare-function.py"
    spec = importlib.util.spec_from_file_location("th105_exact_owner_callee_compare", path)
    if spec is None or spec.loader is None:
        raise RuntimeError(f"cannot load {path}")
    module = importlib.util.module_from_spec(spec)
    sys.modules[spec.name] = module
    spec.loader.exec_module(module)
    return module


def load_rows(path: Path) -> list[dict[str, str]]:
    with path.open(newline="", encoding="utf-8") as handle:
        return list(csv.DictReader(handle))


def direct_external_edges(code: bytes, address: int) -> list[tuple[int, int, str]]:
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    decoder.detail = True
    instructions = list(decoder.disasm(code, address))
    if sum(insn.size for insn in instructions) != len(code):
        consumed = sum(insn.size for insn in instructions)
        raise ValueError(f"incomplete decode at {address + consumed:#x}")
    end = address + len(code)
    edges: list[tuple[int, int, str]] = []
    for insn in instructions:
        if not (insn.group(CS_GRP_CALL) or insn.group(CS_GRP_JUMP)) or not insn.operands:
            continue
        operand = insn.operands[0]
        if operand.type != X86_OP_IMM:
            continue
        target = operand.imm & 0xFFFFFFFF
        if address <= target < end:
            continue
        kind = "call" if insn.group(CS_GRP_CALL) else "jump"
        edges.append((insn.address, target, kind))
    return edges


def candidate_owner(
    spans: list[tuple[int, int, dict[str, str]]], address: int
) -> dict[str, str] | None:
    lo, hi = 0, len(spans)
    while lo < hi:
        mid = (lo + hi) // 2
        if spans[mid][0] <= address:
            lo = mid + 1
        else:
            hi = mid
    if lo:
        start, end, row = spans[lo - 1]
        if start <= address < end:
            return row
    return None


def census(include_nonreview: bool, include_jumps: bool) -> dict[str, Any]:
    compare = load_compare()
    target_sha = compare.verify_target()
    rows = load_rows(FUNCTIONS)
    origins = {int(row["address"], 0): row for row in load_rows(ORIGINS)}
    by_start = {int(row["address"], 0): row for row in rows}
    spans = sorted(
        (int(row["address"], 0), int(row["span_end"], 0) + 1, row)
        for row in rows
    )
    exact = [row for row in rows if row["status"] == "matching"]
    usage: dict[int, dict[str, Any]] = {}
    for owner in exact:
        address = int(owner["address"], 0)
        size = int(owner["size"])
        code = compare.target_bytes(address, size)
        for site, target, kind in direct_external_edges(code, address):
            if kind == "jump" and not include_jumps:
                continue
            record = usage.setdefault(target, {"sites": [], "owners": {}})
            record["sites"].append((site, kind))
            record["owners"].setdefault(address, []).append((site, kind))

    output = []
    for target, use in usage.items():
        start_row = by_start.get(target)
        owner_row = candidate_owner(spans, target)
        if start_row is not None:
            landing = "candidate_start"
            function = start_row
        elif owner_row is not None:
            landing = "candidate_interior"
            function = owner_row
        else:
            landing = "unledgered"
            function = None
        origin = None if function is None else origins.get(int(function["address"], 0))
        if not include_nonreview and landing == "candidate_start":
            if origin is not None and origin["disposition"] != "review":
                continue
        elif not include_nonreview and landing == "candidate_interior":
            # Keep interior targets regardless of current owner classification: they
            # are precisely where missed private entries/remote chunks can hide.
            pass
        elif not include_nonreview and landing == "unledgered":
            pass
        owner_entries = []
        for owner_address, sites in sorted(use["owners"].items()):
            owner = by_start[owner_address]
            owner_entries.append({
                "address": f"0x{owner_address:08X}",
                "name": owner["proposed_name"] or owner["current_name"],
                "sites": [
                    {"address": f"0x{site:08X}", "kind": kind}
                    for site, kind in sites
                ],
            })
        output.append({
            "target": f"0x{target:08X}",
            "landing": landing,
            "candidate_address": None if function is None else function["address"],
            "candidate_size": None if function is None else int(function["size"]),
            "name": None if function is None else (function["proposed_name"] or function["current_name"]),
            "status": None if function is None else function["status"],
            "origin": None if origin is None else origin["origin"],
            "disposition": None if origin is None else origin["disposition"],
            "owner_count": len(owner_entries),
            "edge_count": len(use["sites"]),
            "call_count": sum(1 for _, kind in use["sites"] if kind == "call"),
            "jump_count": sum(1 for _, kind in use["sites"] if kind == "jump"),
            "owners": owner_entries,
        })
    priority = {"unledgered": 0, "candidate_interior": 1, "candidate_start": 2}
    output.sort(
        key=lambda row: (
            priority[row["landing"]],
            -row["owner_count"],
            -row["edge_count"],
            row["candidate_size"] if row["candidate_size"] is not None else 0,
            row["target"],
        )
    )
    landing_counts = {name: 0 for name in ("unledgered", "candidate_interior", "candidate_start")}
    for row in output:
        landing_counts[row["landing"]] += 1
    return {
        "schema": "th105-exact-owner-direct-target-census-v1",
        "target_sha256": target_sha,
        "exact_owner_count": len(exact),
        "include_nonreview": include_nonreview,
        "include_jumps": include_jumps,
        "landing_counts": landing_counts,
        "rows": output,
        "scope": "direct relative edges leaving canonical-exact provisional main spans; remote byte ownership and indirect calls require separate review",
    }


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--include-nonreview", action="store_true")
    parser.add_argument("--no-jumps", action="store_true")
    parser.add_argument("--json", action="store_true")
    args = parser.parse_args()
    try:
        result = census(args.include_nonreview, not args.no_jumps)
    except (OSError, RuntimeError, TypeError, ValueError) as exc:
        print(f"exact-owner callee census failed: {exc}", file=sys.stderr)
        return 2
    if args.json:
        print(json.dumps(result, indent=2))
    else:
        counts = result["landing_counts"]
        print(
            f"Exact-owner direct targets: {len(result['rows'])} row(s); "
            f"owners={result['exact_owner_count']} "
            f"starts={counts['candidate_start']} interiors={counts['candidate_interior']} "
            f"unledgered={counts['unledgered']} target={result['target_sha256']}"
        )
        for row in result["rows"]:
            name = row["name"] or "<not in functions.csv>"
            disposition = row["disposition"] or "untracked"
            size = "?" if row["candidate_size"] is None else str(row["candidate_size"])
            print(
                f"{row['target']} {row['landing']:18s} owners={row['owner_count']:3d} "
                f"edges={row['edge_count']:3d} size={size:>6s} {disposition:9s} {name}"
            )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
