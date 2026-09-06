#!/usr/bin/env python3
"""Cold-build and replay every accepted exact TH105 function."""

from __future__ import annotations

import argparse
import csv
import sys
from typing import Any

from build import build_unit, compare_unit
from workflow_manifest import ROOT, canonical_address, load_manifest


MATCHES = ROOT / "config" / "matches.csv"


def accepted_functions(
    units: dict[str, dict[str, Any]],
) -> dict[str, set[str]]:
    """Return accepted addresses grouped by their configured build unit."""

    configured = {
        name: {
            canonical_address(str(function["address"]))
            for function in unit["functions"]
        }
        for name, unit in units.items()
    }
    accepted: dict[str, set[str]] = {}
    seen: set[str] = set()
    with MATCHES.open(newline="", encoding="utf-8") as stream:
        for row in csv.DictReader(stream):
            if row["status"] != "matching":
                continue
            address = canonical_address(row["address"])
            unit_name = row["unit"]
            if unit_name not in units:
                raise ValueError(
                    f"accepted function {address} names unknown unit {unit_name!r}"
                )
            if address not in configured[unit_name]:
                raise ValueError(
                    f"accepted function {address} is absent from unit {unit_name!r}"
                )
            if address in seen:
                raise ValueError(f"duplicate accepted function address: {address}")
            seen.add(address)
            accepted.setdefault(unit_name, set()).add(address)
    if not accepted:
        raise ValueError("matches.csv contains no accepted exact functions")
    return accepted


def comparison_view(
    unit: dict[str, Any], addresses: set[str]
) -> dict[str, Any]:
    """Select only accepted functions from a possibly mixed probe unit."""

    selected = dict(unit)
    selected["functions"] = [
        function
        for function in unit["functions"]
        if canonical_address(str(function["address"])) in addresses
    ]
    if len(selected["functions"]) != len(addresses):
        raise ValueError("accepted-function selection did not close over its unit")
    return selected


def failure_detail(report: object) -> str:
    if not isinstance(report, dict):
        return repr(report)
    failure = report.get("failure")
    if isinstance(failure, dict) and failure.get("message"):
        return str(failure["message"])
    mismatch = report.get("first_mismatch")
    if mismatch:
        return f"first mismatch {mismatch}"
    return str(report.get("result", "unknown comparison failure"))


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--all", action="store_true", help="verify every matches.csv exact function"
    )
    args = parser.parse_args()
    if not args.all:
        parser.error("aggregate verification requires --all")
    try:
        manifest = load_manifest()
        units = manifest["units"]
        accepted = accepted_functions(units)
        selected = [
            (name, unit, accepted[name])
            for name, unit in units.items()
            if name in accepted
        ]
        total_functions = sum(len(addresses) for _, _, addresses in selected)
        for index, (name, unit, addresses) in enumerate(selected, start=1):
            output = ROOT / str(unit["object"])
            if output.exists():
                output.unlink()
            provenance = output.with_suffix(output.suffix + ".provenance.json")
            if provenance.exists():
                provenance.unlink()
            build_unit(name, unit, True, manifest["target_sha256"])
            compare_code, reports = compare_unit(
                comparison_view(unit, addresses), True
            )
            failures = [
                report
                for report in reports
                if not isinstance(report, dict) or report.get("result") != "exact"
            ]
            if compare_code or failures or len(reports) != len(addresses):
                detail = (
                    failure_detail(failures[0])
                    if failures
                    else f"expected {len(addresses)} reports, got {len(reports)}"
                )
                raise RuntimeError(f"{name}: {detail}")
            print(
                f"[{index}/{len(selected)}] {name}: "
                f"{len(reports)}/{len(addresses)} exact",
                flush=True,
            )
    except (KeyError, OSError, RuntimeError, TypeError, ValueError) as exc:
        print(f"error: accepted exact-unit replay failed: {exc}", file=sys.stderr)
        return 1
    print(
        f"accepted exact-unit replay OK: {len(selected)} cold unit(s), "
        f"{total_functions} function(s)"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
