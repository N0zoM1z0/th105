#!/usr/bin/env python3
"""Generate and validate the whole-executable function-origin census."""

from __future__ import annotations

import argparse
from collections import Counter
import csv
from pathlib import Path
import tomllib


ROOT = Path(__file__).resolve().parents[1]
FUNCTIONS = ROOT / "config" / "functions.csv"
RULES = ROOT / "config" / "function-origin-rules.toml"
OUTPUT = ROOT / "config" / "function-origins.csv"
FIELDS = [
    "address",
    "origin",
    "subsystem",
    "disposition",
    "confidence",
    "evidence_id",
]
ORIGINS = {
    "authored_game",
    "compiler_generated",
    "vc8_runtime",
    "third_party",
    "import_thunk",
    "unknown",
}
DISPOSITIONS = {"include_authored", "exclude_authored", "review"}
CONFIDENCES = {"observed", "inferred", "hypothesized", "unknown"}
AUTHORED_MODULES = {
    "assets",
    "audio",
    "battle",
    "characters",
    "config",
    "engine",
    "input",
    "network",
    "platform",
    "render",
    "script",
    "ui",
}


def read_csv(path: Path) -> list[dict[str, str]]:
    with path.open(newline="", encoding="utf-8") as stream:
        return list(csv.DictReader(stream))


def baseline(row: dict[str, str]) -> dict[str, str]:
    status = row["status"]
    module = row["module"]
    name = row["proposed_name"] or row["current_name"]
    if status == "library":
        if name.startswith(("Unwind@", "Catch_All@")) or "EH unwind" in row["evidence"]:
            origin = "compiler_generated"
        elif module == "third_party":
            origin = "third_party"
        elif ".DLL::" in row["current_name"]:
            origin = "import_thunk"
        else:
            origin = "vc8_runtime"
        return {
            "address": row["address"],
            "origin": origin,
            "subsystem": module or "runtime",
            "disposition": "exclude_authored",
            "confidence": "observed",
            "evidence_id": "ledger-library",
        }
    if status != "unclassified" and module in AUTHORED_MODULES:
        return {
            "address": row["address"],
            "origin": "authored_game",
            "subsystem": module,
            "disposition": "include_authored",
            "confidence": "inferred",
            "evidence_id": "ledger-authored-module",
        }
    return {
        "address": row["address"],
        "origin": "unknown",
        "subsystem": module,
        "disposition": "review",
        "confidence": "unknown",
        "evidence_id": "",
    }


def select(rule: dict[str, object], rows: list[dict[str, str]]) -> list[dict[str, str]]:
    explicit = {str(value).upper() for value in rule.get("addresses", [])}
    start = int(str(rule["start"]), 16) if "start" in rule else None
    end = int(str(rule["end"]), 16) if "end" in rule else None
    prefix = str(rule.get("name_prefix", ""))
    selected: list[dict[str, str]] = []
    for row in rows:
        address = int(row["address"], 16)
        if explicit and row["address"].upper() not in explicit:
            continue
        if start is not None and not (start <= address <= end):
            continue
        if prefix and not row["current_name"].startswith(prefix):
            continue
        selected.append(row)
    return selected


def materialize() -> tuple[list[dict[str, str]], list[dict[str, object]], list[str]]:
    rows = read_csv(FUNCTIONS)
    rules = tomllib.loads(RULES.read_text(encoding="utf-8"))["rules"]
    census = {row["address"]: baseline(row) for row in rows}
    errors: list[str] = []
    claimed: dict[str, str] = {}
    for rule in rules:
        rule_id = str(rule["id"])
        selected = select(rule, rows)
        count = len(selected)
        byte_count = sum(int(row["size"]) for row in selected)
        if count != int(rule["expected_count"]):
            errors.append(
                f"{rule_id}: selected {count} rows, expected {rule['expected_count']}"
            )
        if byte_count != int(rule["expected_bytes"]):
            errors.append(
                f"{rule_id}: selected {byte_count} bytes, expected {rule['expected_bytes']}"
            )
        for row in selected:
            previous = claimed.get(row["address"])
            if previous:
                errors.append(f"{rule_id}: overlaps {previous} at {row['address']}")
                continue
            claimed[row["address"]] = rule_id
            census[row["address"]] = {
                "address": row["address"],
                "origin": str(rule["origin"]),
                "subsystem": str(rule["subsystem"]),
                "disposition": str(rule["disposition"]),
                "confidence": str(rule["confidence"]),
                "evidence_id": rule_id,
            }
    result = [census[row["address"]] for row in rows]
    return result, rules, errors


def validate_rows(rows: list[dict[str, str]]) -> list[str]:
    errors: list[str] = []
    ledger = read_csv(FUNCTIONS)
    if not rows or list(rows[0]) != FIELDS:
        errors.append("function-origins.csv: invalid or missing header")
        return errors
    ledger_addresses = [row["address"] for row in ledger]
    census_addresses = [row["address"] for row in rows]
    if census_addresses != ledger_addresses:
        errors.append("function-origins.csv: addresses do not exactly match functions.csv")
    for line, row in enumerate(rows, 2):
        if row["origin"] not in ORIGINS:
            errors.append(f"function-origins.csv:{line}: invalid origin")
        if row["disposition"] not in DISPOSITIONS:
            errors.append(f"function-origins.csv:{line}: invalid disposition")
        if row["confidence"] not in CONFIDENCES:
            errors.append(f"function-origins.csv:{line}: invalid confidence")
        if row["origin"] == "unknown" and row["disposition"] != "review":
            errors.append(f"function-origins.csv:{line}: unknown origin must remain review")
    return errors


def write_census(rows: list[dict[str, str]]) -> None:
    with OUTPUT.open("w", newline="", encoding="utf-8") as stream:
        writer = csv.DictWriter(stream, fieldnames=FIELDS, lineterminator="\n")
        writer.writeheader()
        writer.writerows(rows)


def apply_ledger(rules: list[dict[str, object]]) -> int:
    rows = read_csv(FUNCTIONS)
    changed = 0
    for rule in rules:
        status = str(rule.get("ledger_status", ""))
        if not status:
            continue
        evidence = f"[origin:{rule['id']}] docs/EXECUTABLE_INVENTORY.md"
        for row in select(rule, rows):
            before = (row["status"], row["module"], row["evidence"])
            row["status"] = status
            row["module"] = str(rule.get("ledger_module", row["module"]))
            if not row["evidence"]:
                row["evidence"] = evidence
            if status == "library" and row["match_percent"] != "100.00":
                row["match_percent"] = "0.00"
            after = (row["status"], row["module"], row["evidence"])
            changed += before != after
    if changed:
        with FUNCTIONS.open("w", newline="", encoding="utf-8") as stream:
            writer = csv.DictWriter(stream, fieldnames=rows[0], lineterminator="\n")
            writer.writeheader()
            writer.writerows(rows)
    return changed


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--write", action="store_true", help="regenerate the census")
    parser.add_argument(
        "--apply-ledger", action="store_true", help="apply audited ledger statuses"
    )
    parser.add_argument("--check", action="store_true", help="fail when stale or invalid")
    args = parser.parse_args()

    expected, rules, errors = materialize()
    if errors:
        print("\n".join(errors))
        return 1
    if args.apply_ledger:
        changed = apply_ledger(rules)
        expected, rules, errors = materialize()
        print(f"updated {changed} function ledger rows")
    if args.write or args.apply_ledger:
        write_census(expected)
    if args.check:
        if not OUTPUT.exists():
            print("missing config/function-origins.csv")
            return 1
        actual = read_csv(OUTPUT)
        errors.extend(validate_rows(actual))
        if actual != expected:
            errors.append("config/function-origins.csv is stale; run scripts/function-origins.py --write")
        if errors:
            print("\n".join(errors))
            return 1
    counts = Counter(row["origin"] for row in expected)
    excluded = sum(row["disposition"] == "exclude_authored" for row in expected)
    print(
        f"origin census OK: {len(expected)} rows, {excluded} excluded; "
        + ", ".join(f"{key}={counts[key]}" for key in sorted(counts))
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
