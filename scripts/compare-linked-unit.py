#!/usr/bin/env python3
"""Compare complete symbol/CFG-bounded linked functions with the canonical PE."""
import argparse
import json
import struct
import pefile
from linked_pe import compare_linked
from workflow_manifest import canonical_address, load_manifest, repository_path


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("unit")
    parser.add_argument("--image")
    parser.add_argument("--address", action="append", default=[])
    parser.add_argument("--json", action="store_true")
    args = parser.parse_args()
    reports = []
    try:
        unit = load_manifest()["units"][args.unit]
        if unit["kind"] != "linked_candidate":
            raise ValueError("unit is not a linked candidate")
        addresses = {canonical_address(a) for a in args.address}
        if addresses - {f["address"] for f in unit["functions"]}:
            raise ValueError("selected address is absent from linked unit")
        reports = compare_linked(args.unit, unit, addresses,
                                 repository_path(args.image, output=True) if args.image else None)
        code = int(any(r["result"] != "exact" for r in reports))
    except (OSError, ValueError, KeyError, RuntimeError, struct.error, pefile.PEFormatError) as error:
        reports = [{"result": "blocked", "failure": {"category": "linked.contract", "message": str(error)}}]
        code = 1
    if args.json:
        print(json.dumps({"unit": args.unit, "comparisons": reports}, indent=2))
    else:
        for report in reports:
            print(json.dumps(report))
    return code


if __name__ == "__main__":
    raise SystemExit(main())
