#!/usr/bin/env python3
"""Audit giant-root instruction/edge identity and raw reachable candidate boundaries.

This report is diagnostic only. It neither records matches nor awards partial
function/byte credit. Canonical acceptance remains compare-function.py.
"""
from __future__ import annotations

import argparse
import csv
import hashlib
import importlib.util
import json
from pathlib import Path
import sys
import tomllib
from typing import Any

from giant_owner_audit import compare_owner_instructions, paired_owners, reachable_boundary_audit

ROOT = Path(__file__).resolve().parents[1]


def load_script(name: str, filename: str) -> Any:
    spec = importlib.util.spec_from_file_location(name, ROOT / "scripts" / filename)
    if spec is None or spec.loader is None:
        raise RuntimeError(f"cannot load {filename}")
    module = importlib.util.module_from_spec(spec)
    sys.modules[name] = module
    spec.loader.exec_module(module)
    return module


def audit(root_name: str, object_path: Path, unit_name: str) -> dict[str, Any]:
    canonical = load_script("th105_owner_canonical", "compare-function.py")
    target_sha = canonical.verify_target()
    mapper = load_script("th105_owner_mapper", "compare-giant-action-switches.py")
    target_mapper = mapper.load_target_mapper()
    manifest = tomllib.loads((ROOT / "config/giant-action-switches.toml").read_text())
    root = target_mapper.select_root(manifest, root_name)
    target = target_mapper.map_root(target_mapper.PeImage(ROOT / "resources/th105.exe"),
                                    target_mapper.load_function_rows(ROOT / "config/functions.csv"), root)
    address = target["address"]
    units = tomllib.loads((ROOT / "config/match-units.toml").read_text())["units"]
    unit = units[unit_name]
    functions = [f for f in unit["functions"] if int(f["address"], 0) == address]
    if len(functions) != 1:
        raise ValueError("unit must supply exactly one matching root relocation contract")
    function = functions[0]
    obj = mapper.CoffObject(object_path)
    symbols = [s for s in obj.symbols.values() if s.name == function["symbol_base"]]
    if len(symbols) != 1 or symbols[0].value != 0 or symbols[0].section_number != obj.text_section_number:
        raise ValueError("audit requires the configured root at the selected COFF .text origin")
    candidate = mapper.build_candidate_map(obj, root)
    comparison = mapper.compare_maps(target, candidate)
    pairs = paired_owners(comparison["rows"])
    rel32 = canonical.known_targets()
    rel32.update({name: int(value, 0) for name, value in (item.split("=", 1) for item in function.get("rel32_targets", []))})
    dir32 = dict(item.split("=", 1) for item in function.get("dir32_targets", []))
    relocated = canonical.coff_symbol_bytes(object_path, function["symbol_base"], address, len(obj.text),
                                             rel32, canonical.known_data_targets(), dir32)
    target_code = canonical.target_bytes(address, target["callable_size"])
    candidate_code = relocated[:candidate["metadata_start"]]
    target_tables = []
    candidate_tables = []
    switches = {}
    for configured, actual, built in zip(root["regions"], target["regions"], candidate["regions"]):
        name = configured["name"]
        count = int(configured["destination_count"])
        cases = int(configured["case_max"]) - int(configured["case_min"]) + 1
        dt = target_mapper.parse_int(configured["destination_table"])
        it = target_mapper.parse_int(configured["index_table"])
        target_tables.extend([(dt, dt + 4 * count, name + ".destinations"), (it, it + cases, name + ".indices")])
        cd = address + built["destination_table_offset"]
        ci = address + built["index_table_offset"]
        candidate_tables.extend([(cd, cd + 4 * built["destination_count"], name + ".destinations"),
                                 (ci, ci + cases, name + ".indices")])
        switches[dt] = (name, [group["destination"] for group in actual["groups"]])
    owners = compare_owner_instructions(target_code, candidate_code, address, pairs, target_tables, candidate_tables)
    boundary = reachable_boundary_audit(target_code, address, switches)
    with (ROOT / "config/functions.csv").open(newline="") as handle:
        ledger = {int(row["address"], 0): row for row in csv.DictReader(handle)}
    with (ROOT / "config/function-origins.csv").open(newline="") as handle:
        origins = {int(row["address"], 0): row for row in csv.DictReader(handle)}
    pending = []
    for edge in boundary["direct_external_targets"]:
        entry = ledger.get(edge["address"])
        edge["ledger_name"] = (entry["proposed_name"] or entry["current_name"]) if entry else None
        edge["ledger_status"] = entry["status"] if entry else None
        edge["origin"] = origins.get(edge["address"])
        if entry is None:
            pending.append(edge["address"])
    boundary["unledgered_direct_targets"] = pending
    return {
        "schema": "th105-giant-owner-audit-v1", "evidence": "diagnostic_only_not_exact_acceptance",
        "target_sha256": target_sha, "object_sha256": hashlib.sha256(object_path.read_bytes()).hexdigest(),
        "root": root_name, "address": address, "unit": unit_name,
        "target_callable_size": len(target_code), "candidate_metadata_start": len(candidate_code),
        "owner_count_including_entry": len(owners),
        "instruction_edge_identical_owners": sum(owner["instruction_edge_identical"] for owner in owners),
        "target_boundary": boundary, "owners": owners,
    }


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("root")
    parser.add_argument("object", type=Path)
    parser.add_argument("--unit", required=True)
    parser.add_argument("--json", action="store_true")
    args = parser.parse_args()
    try:
        result = audit(args.root, args.object, args.unit)
    except (KeyError, OSError, RuntimeError, TypeError, ValueError) as error:
        print(f"owner audit failed: {error}", file=sys.stderr)
        return 2
    if args.json:
        print(json.dumps(result, indent=2))
    else:
        print(f"{result['root']}: DIAGNOSTIC ONLY; no exact-match credit")
        print(f"Instruction/edge-identical owners: {result['instruction_edge_identical_owners']}/{result['owner_count_including_entry']} (entry included)")
        boundary = result["target_boundary"]
        print(f"Raw target reachability: {boundary['reachable_bytes']}/{boundary['decoded_bytes']} bytes; {boundary['reachable_instructions']} instructions")
        print(f"Unledgered direct targets: {len(boundary['unledgered_direct_targets'])}; unresolved indirect exits: {len(boundary['unresolved_indirect_exits'])}")
        for owner in result["owners"]:
            if not owner["instruction_edge_identical"]:
                print(f"  {owner['name']}: {len(owner['differences'])} difference blocks, spans {owner['target_span']}/{owner['candidate_span']}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
