#!/usr/bin/env python3
"""Compare selected functions in an existing COFF object without building.

This reuses a unit's relocation/boundary contract, not its build provenance.
It does not promote results, verify the compiler profile, or write ledgers.
"""
from __future__ import annotations

import argparse
import copy
import json
import sys

from build import compare_unit
from workflow_manifest import load_manifest


def select_functions(unit: dict, addresses: list[int]) -> dict:
    selected = copy.deepcopy(unit)
    if addresses:
        requested = set(addresses)
        available = {int(row["address"], 0) for row in unit["functions"]}
        missing = requested - available
        if missing:
            raise ValueError("addresses absent from unit: " + ", ".join(hex(x) for x in sorted(missing)))
        selected["functions"] = [row for row in selected["functions"]
                                 if int(row["address"], 0) in requested]
    return selected


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("unit")
    parser.add_argument("object", help="existing COFF path below build/")
    parser.add_argument("--address", action="append", type=lambda value: int(value, 0), default=[])
    parser.add_argument("--json", action="store_true")
    args = parser.parse_args()
    try:
        units = load_manifest()["units"]
        if args.unit not in units:
            raise ValueError("unknown match unit: " + args.unit)
        unit = select_functions(units[args.unit], args.address)
        unit["object"] = args.object
        if not args.json:
            print("Existing-object comparison only; compiler/build provenance is not verified.", flush=True)
        code, comparisons = compare_unit(unit, args.json)
        if args.json:
            print(json.dumps({"mode": "compare_existing_object_no_build", "unit": args.unit,
                              "build_provenance_verified": False, "comparisons": comparisons}, indent=2))
        return code
    except (OSError, RuntimeError, ValueError, KeyError) as exc:
        print(f"existing-object comparison failed: {exc}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    raise SystemExit(main())
