#!/usr/bin/env python3
"""Validate TH105 1.06a inventory, source-presence, and exact-match ledgers."""

from __future__ import annotations

import argparse
import csv
import hashlib
from pathlib import Path
import re
import tomllib

from workflow_manifest import load_manifest


ROOT = Path(__file__).resolve().parents[1]
CONFIG = ROOT / "config"
TARGET = ROOT / "resources" / "th105.exe"
FUNCTION_FIELDS = [
    "address", "size", "span_end", "current_name", "proposed_name", "module",
    "status", "match_percent", "calling_convention", "signature", "is_thunk",
    "source_file", "evidence", "owner", "notes",
]
ORIGIN_FIELDS = [
    "address", "origin", "subsystem", "disposition", "confidence", "evidence_id"
]
MATCH_FIELDS = [
    "address", "name", "size", "status", "match_percent", "unit", "evidence"
]
CLAIM_FIELDS = ["address", "owner", "started_utc", "branch", "notes"]
STATUS = {
    "unclassified", "identified", "decompiled", "implemented", "compiles",
    "matching", "library", "blocked",
}
ADDRESS = re.compile(r"^0x[0-9A-F]{8}$")


def rows(path: Path) -> list[dict[str, str]]:
    with path.open(newline="", encoding="utf-8") as stream:
        return list(csv.DictReader(stream))


def require_header(path: Path, expected: list[str]) -> list[dict[str, str]]:
    with path.open(newline="", encoding="utf-8") as stream:
        reader = csv.DictReader(stream)
        if reader.fieldnames != expected:
            raise ValueError(f"{path.name}: unexpected columns: {reader.fieldnames}")
        entries = list(reader)
        for line, row in enumerate(entries, start=2):
            if None in row:
                raise ValueError(f"{path.name}:{line}: too many CSV fields")
            if any(row[field] is None for field in expected):
                raise ValueError(f"{path.name}:{line}: too few CSV fields")
        return entries


def parse_address(raw: str, context: str) -> int:
    if not ADDRESS.fullmatch(raw):
        raise ValueError(f"{context}: noncanonical address {raw!r}")
    return int(raw, 16)


def validate_target(require_bytes: bool) -> dict[str, object]:
    with (CONFIG / "target.toml").open("rb") as stream:
        manifest = tomllib.load(stream)
    target = manifest["target"]
    digest = str(target["sha256"])
    if not re.fullmatch(r"[0-9a-f]{64}", digest):
        raise ValueError("target.toml: invalid SHA-256")
    project = (ROOT / "reccmp-project.yml").read_text(encoding="utf-8")
    if project.count(digest) != 1:
        raise ValueError("reccmp-project.yml: target SHA-256 is missing or duplicated")
    if require_bytes:
        data = TARGET.read_bytes()
        if len(data) != int(target["size"]):
            raise ValueError("resources/th105.exe: target size mismatch")
        if hashlib.sha256(data).hexdigest() != digest:
            raise ValueError("resources/th105.exe: target SHA-256 mismatch")
    return manifest


def validate_functions(manifest: dict[str, object]) -> dict[int, dict[str, str]]:
    entries = require_header(CONFIG / "functions.csv", FUNCTION_FIELDS)
    pe = manifest["pe"]
    text_start = int(str(pe["text_start"]), 0)
    text_end = int(str(pe["text_end"]), 0)
    result: dict[int, dict[str, str]] = {}
    previous = -1
    for line, row in enumerate(entries, start=2):
        address = parse_address(row["address"], f"functions.csv:{line}")
        size = int(row["size"], 0)
        span_end = parse_address(row["span_end"], f"functions.csv:{line}")
        if address <= previous or address in result:
            raise ValueError(f"functions.csv:{line}: addresses are not strictly sorted")
        if size <= 0 or span_end != address + size - 1:
            raise ValueError(f"functions.csv:{line}: inconsistent provisional extent")
        if not (text_start <= address <= span_end <= text_end):
            raise ValueError(f"functions.csv:{line}: candidate lies outside .text")
        if row["status"] not in STATUS:
            raise ValueError(f"functions.csv:{line}: invalid status {row['status']!r}")
        percent = float(row["match_percent"])
        if not 0.0 <= percent <= 100.0:
            raise ValueError(f"functions.csv:{line}: invalid match percent")
        if row["status"] == "matching" and percent != 100.0:
            raise ValueError(f"functions.csv:{line}: matching requires 100.00")
        result[address] = row
        previous = address
    if not result:
        raise ValueError("functions.csv: inventory is empty")
    return result


def validate_origins(functions: dict[int, dict[str, str]]) -> None:
    entries = require_header(CONFIG / "function-origins.csv", ORIGIN_FIELDS)
    addresses: set[int] = set()
    for line, row in enumerate(entries, start=2):
        address = parse_address(row["address"], f"function-origins.csv:{line}")
        if address in addresses:
            raise ValueError(f"function-origins.csv:{line}: duplicate address")
        if row["disposition"] not in {"review", "authored", "exclude"}:
            raise ValueError(f"function-origins.csv:{line}: invalid disposition")
        addresses.add(address)
    if addresses != set(functions):
        raise ValueError("function-origins.csv: addresses differ from functions.csv")


def validate_claims() -> None:
    entries = require_header(CONFIG / "claims.csv", CLAIM_FIELDS)
    if entries:
        raise ValueError("claims.csv must remain header-only in single-agent workflow")


def validate_named_ledger(path: Path, fields: list[str]) -> list[dict[str, str]]:
    entries = require_header(path, fields)
    addresses: set[int] = set()
    names: set[str] = set()
    for line, row in enumerate(entries, start=2):
        address = parse_address(row["address"], f"{path.name}:{line}")
        name = row["name"]
        if address in addresses or not name or name in names:
            raise ValueError(f"{path.name}:{line}: duplicate or empty mapping")
        addresses.add(address)
        names.add(name)
    return entries


def validate_reccmp_ledgers() -> dict[int, dict[str, str]]:
    functions = validate_named_ledger(
        CONFIG / "reccmp-functions.csv", ["name", "address", "type"]
    )
    for name in ("reccmp-globals.csv", "reccmp-floats.csv", "reccmp-strings.csv"):
        validate_named_ledger(CONFIG / name, ["name", "address", "type"])
    require_header(
        CONFIG / "reccmp-relocations.csv",
        ["coff_symbol", "address", "data_hex", "addends", "evidence", "validation"],
    )
    return {int(row["address"], 0): row for row in functions}


def read_implemented(reccmp: dict[int, dict[str, str]]) -> set[str]:
    known_names = {row["name"] for row in reccmp.values() if row["type"] == "function"}
    values: set[str] = set()
    with (CONFIG / "implemented.csv").open(newline="", encoding="utf-8") as stream:
        for line, raw in enumerate(csv.reader(stream), start=1):
            if len(raw) != 1 or not raw[0] or raw[0] in values:
                raise ValueError(f"implemented.csv:{line}: expected one unique name")
            if raw[0] not in known_names:
                raise ValueError(f"implemented.csv:{line}: name lacks authored mapping")
            values.add(raw[0])
    return values


def validate_matches(
    functions: dict[int, dict[str, str]], reccmp: dict[int, dict[str, str]], units: dict[str, object]
) -> int:
    entries = require_header(CONFIG / "matches.csv", MATCH_FIELDS)
    matched: set[int] = set()
    for line, row in enumerate(entries, start=2):
        address = parse_address(row["address"], f"matches.csv:{line}")
        if address in matched or address not in functions:
            raise ValueError(f"matches.csv:{line}: duplicate or unmapped address")
        if row["status"] != "matching" or float(row["match_percent"]) != 100.0:
            raise ValueError(f"matches.csv:{line}: only canonical 100% matches are accepted")
        if int(row["size"], 0) != int(functions[address]["size"], 0):
            raise ValueError(f"matches.csv:{line}: size differs from inventory")
        if row["unit"] not in units or not row["evidence"]:
            raise ValueError(f"matches.csv:{line}: unit and evidence are required")
        mapped = reccmp.get(address)
        if mapped is None or mapped["name"] != row["name"] or mapped["type"] != "function":
            raise ValueError(f"matches.csv:{line}: exact row lacks matching authored mapping")
        matched.add(address)
    ledger_matching = {
        address for address, row in functions.items() if row["status"] == "matching"
    }
    if matched != ledger_matching:
        raise ValueError("matches.csv and functions.csv matching statuses differ")
    return len(matched)


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    target = parser.add_mutually_exclusive_group()
    target.add_argument("--require-target", action="store_true")
    target.add_argument("--skip-target-bytes", action="store_true")
    args = parser.parse_args()
    try:
        manifest = validate_target(args.require_target and not args.skip_target_bytes)
        functions = validate_functions(manifest)
        validate_origins(functions)
        validate_claims()
        validate_named_ledger(
            CONFIG / "known-symbols.csv",
            ["address", "name", "module", "confidence", "evidence"],
        )
        validate_named_ledger(
            CONFIG / "known-globals.csv",
            ["address", "name", "module", "confidence", "evidence"],
        )
        reccmp = validate_reccmp_ledgers()
        implemented = read_implemented(reccmp)
        match_manifest = load_manifest()
        matching = validate_matches(functions, reccmp, match_manifest["units"])
    except (OSError, KeyError, TypeError, ValueError, tomllib.TOMLDecodeError) as exc:
        print(f"error: tracking validation failed: {exc}")
        return 1
    print(
        f"tracking OK: {len(functions)} provisional candidates, "
        f"{len(implemented)} source-present, {matching} exact"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
