#!/usr/bin/env python3
"""Generate and validate the current TH105 1.06a function-origin census.

Rules are deliberately fail-closed: each current-target rule fixes its selected
candidate count and byte total, may attest target strings/opcodes/names, and is
applied only after the target SHA-256 matches config/target.toml.
"""
from __future__ import annotations

import argparse
from collections import Counter
import csv
import hashlib
import importlib.util
from pathlib import Path
import struct
import tomllib

ROOT = Path(__file__).resolve().parents[1]
FUNCTIONS = ROOT / "config/functions.csv"
RULES = ROOT / "config/function-origin-rules.toml"
OUTPUT = ROOT / "config/function-origins.csv"
TARGET = ROOT / "resources/th105.exe"
FIELDS = ["address", "origin", "subsystem", "disposition", "confidence", "evidence_id"]
ORIGINS = {"authored_game", "compiler_generated", "vc8_runtime", "third_party", "import_thunk", "unknown"}
DISPOSITIONS = {"authored", "exclude", "review"}
CONFIDENCES = {"observed", "inferred", "hypothesized", "unknown"}
AUTHORED_MODULES = {"assets", "audio", "battle", "characters", "config", "engine", "input", "network", "platform", "render", "script", "ui"}


def read_csv(path: Path) -> list[dict[str, str]]:
    with path.open(newline="", encoding="utf-8") as stream:
        return list(csv.DictReader(stream))


def target_manifest() -> dict[str, object]:
    with (ROOT / "config/target.toml").open("rb") as stream:
        return tomllib.load(stream)


def attest_target(rules_doc: dict[str, object]) -> bytes:
    data = TARGET.read_bytes()
    configured = str(target_manifest()["target"]["sha256"])
    rules_hash = str(rules_doc["target_sha256"])
    actual = hashlib.sha256(data).hexdigest()
    if actual != configured or rules_hash != configured:
        raise ValueError(f"target identity mismatch: actual={actual} config={configured} rules={rules_hash}")
    return data


def pe_reader(data: bytes):
    pe = struct.unpack_from("<I", data, 0x3C)[0]
    count = struct.unpack_from("<H", data, pe + 6)[0]
    opt_size = struct.unpack_from("<H", data, pe + 20)[0]
    image_base = struct.unpack_from("<I", data, pe + 52)[0]
    section_base = pe + 24 + opt_size
    sections = []
    for index in range(count):
        off = section_base + index * 40
        virtual_size, rva, raw_size, raw_ptr = struct.unpack_from("<IIII", data, off + 8)
        sections.append((rva, virtual_size, raw_size, raw_ptr))

    def read(address: int, size: int) -> bytes:
        rva = address - image_base
        for section_rva, _virtual_size, raw_size, raw_ptr in sections:
            if section_rva <= rva and rva + size <= section_rva + raw_size:
                offset = raw_ptr + rva - section_rva
                return data[offset : offset + size]
        raise ValueError(f"0x{address:08X}: requested bytes are not initialized PE raw data")

    return read




def load_msvc_archive_symbols() -> set[str]:
    """Return all defined COFF symbols from the SHA-pinned VC8 SP1 archives."""
    extractor_path = ROOT / "scripts/extract-msvc-library-object.py"
    spec = importlib.util.spec_from_file_location("th105_msvc_extract", extractor_path)
    if spec is None or spec.loader is None:
        raise ValueError("cannot load pinned MSVC archive extractor")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    symbols: set[str] = set()
    for _key, (filename, expected_hash) in module.LIBRARIES.items():
        archive_path = ROOT / ".tools/msvc80-sp1/lib" / filename
        archive = archive_path.read_bytes()
        actual_hash = hashlib.sha256(archive).hexdigest()
        if actual_hash != expected_hash:
            raise ValueError(f"{filename} SHA-256 mismatch: {actual_hash} != {expected_hash}")
        for _member_name, obj in module.archive_members(archive):
            if len(obj) < 20 or struct.unpack_from("<H", obj, 0)[0] != 0x014C:
                continue
            symbol_ptr, symbol_count = struct.unpack_from("<II", obj, 8)
            string_table = symbol_ptr + symbol_count * 18
            if not symbol_ptr or string_table + 4 > len(obj):
                continue

            def symbol_name(offset: int) -> str:
                raw = obj[offset : offset + 8]
                if raw[:4] == b"\0\0\0\0":
                    name_offset = struct.unpack_from("<I", raw, 4)[0]
                    start = string_table + name_offset
                    if not string_table + 4 <= start < len(obj):
                        return ""
                    end = obj.find(b"\0", start)
                    if end < 0:
                        end = len(obj)
                    return obj[start:end].decode("ascii", errors="replace")
                return raw.rstrip(b"\0").decode("ascii", errors="replace")

            index = 0
            while index < symbol_count:
                offset = symbol_ptr + index * 18
                if offset + 18 > len(obj):
                    break
                name = symbol_name(offset)
                section = struct.unpack_from("<h", obj, offset + 12)[0]
                aux_count = obj[offset + 17]
                if section > 0 and name and not name.startswith("."):
                    symbols.add(name)
                index += 1 + aux_count
    return symbols


def msvc_symbol_aliases(name: str) -> set[str]:
    # GNU/COFF tooling and IDA differ by one C-name leading underscore.
    return {name, name[1:] if name.startswith("_") else "_" + name}

def baseline(row: dict[str, str]) -> dict[str, str]:
    if row["status"] == "matching":
        if row["module"] not in AUTHORED_MODULES:
            raise ValueError(f"{row['address']}: matching function lacks authored module")
        return {"address": row["address"], "origin": "authored_game", "subsystem": row["module"], "disposition": "authored", "confidence": "observed", "evidence_id": "canonical-exact-authored"}
    return {"address": row["address"], "origin": "unknown", "subsystem": row["module"], "disposition": "review", "confidence": "unknown", "evidence_id": "ida-1.06a-initial-inventory"}


def select(rule: dict[str, object], rows: list[dict[str, str]], msvc_symbols: set[str] | None = None) -> list[dict[str, str]]:
    explicit = {str(value).upper() for value in rule.get("addresses", [])}
    start = int(str(rule["start"]), 0) if "start" in rule else None
    end = int(str(rule["end"]), 0) if "end" in rule else None
    selected = []
    for row in rows:
        address = int(row["address"], 0)
        if explicit and row["address"].upper() not in explicit:
            continue
        if start is not None and not (start <= address <= end):
            continue
        if rule.get("msvc_archive_defined_symbol"):
            if msvc_symbols is None:
                raise ValueError(f"{rule['id']}: MSVC archive symbols were not loaded")
            prefixes = tuple(str(value) for value in rule.get("exclude_name_prefixes", []))
            name = row["current_name"]
            if not name or (prefixes and name.startswith(prefixes)):
                continue
            if not any(alias in msvc_symbols for alias in msvc_symbol_aliases(name)):
                continue
        selected.append(row)
    return selected


def validate_rule_evidence(rule: dict[str, object], selected: list[dict[str, str]], data: bytes, read_pe) -> list[str]:
    errors: list[str] = []
    rule_id = str(rule["id"])
    expected_names = [str(value) for value in rule.get("expected_names", [])]
    if expected_names:
        actual = [row["current_name"] for row in selected]
        if actual != expected_names:
            errors.append(f"{rule_id}: current names differ: got {actual!r}")
    prefix = bytes.fromhex(str(rule.get("opcode_prefix_hex", "")))
    if prefix:
        for row in selected:
            try:
                actual = read_pe(int(row["address"], 0), len(prefix))
            except ValueError as exc:
                errors.append(f"{rule_id}: {exc}")
                continue
            if actual != prefix:
                errors.append(f"{rule_id}: {row['address']} opcode {actual.hex()} != {prefix.hex()}")
    for text in rule.get("required_target_strings", []):
        encoded = str(text).encode("ascii")
        if encoded not in data:
            errors.append(f"{rule_id}: target string missing: {text!r}")
    return errors


def materialize() -> tuple[list[dict[str, str]], list[str]]:
    rows = read_csv(FUNCTIONS)
    rules_doc = tomllib.loads(RULES.read_text(encoding="utf-8"))
    data = attest_target(rules_doc)
    read_pe = pe_reader(data)
    census = {row["address"]: baseline(row) for row in rows}
    errors: list[str] = []
    claimed: dict[str, str] = {}
    rules = rules_doc.get("rules", [])
    need_msvc = any(bool(rule.get("msvc_archive_defined_symbol")) for rule in rules)
    msvc_symbols = load_msvc_archive_symbols() if need_msvc else None
    for rule in rules:
        rule_id = str(rule["id"])
        selected = select(rule, rows, msvc_symbols)
        count = len(selected)
        byte_count = sum(int(row["size"], 0) for row in selected)
        if count != int(rule["expected_count"]):
            errors.append(f"{rule_id}: selected {count} rows, expected {rule['expected_count']}")
        if byte_count != int(rule["expected_bytes"]):
            errors.append(f"{rule_id}: selected {byte_count} bytes, expected {rule['expected_bytes']}")
        errors.extend(validate_rule_evidence(rule, selected, data, read_pe))
        for row in selected:
            if row["status"] == "matching":
                errors.append(f"{rule_id}: overlaps canonical authored function {row['address']}")
                continue
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
    return [census[row["address"]] for row in rows], errors


def validate_rows(rows: list[dict[str, str]]) -> list[str]:
    errors: list[str] = []
    ledger = read_csv(FUNCTIONS)
    if not rows or list(rows[0]) != FIELDS:
        return ["function-origins.csv: invalid or missing header"]
    if [row["address"] for row in rows] != [row["address"] for row in ledger]:
        errors.append("function-origins.csv: addresses do not exactly match functions.csv")
    for line, row in enumerate(rows, 2):
        if row["origin"] not in ORIGINS: errors.append(f"function-origins.csv:{line}: invalid origin")
        if row["disposition"] not in DISPOSITIONS: errors.append(f"function-origins.csv:{line}: invalid disposition")
        if row["confidence"] not in CONFIDENCES: errors.append(f"function-origins.csv:{line}: invalid confidence")
        if row["origin"] == "unknown" and row["disposition"] != "review": errors.append(f"function-origins.csv:{line}: unknown origin must remain review")
    return errors


def write(rows: list[dict[str, str]]) -> None:
    with OUTPUT.open("w", newline="", encoding="utf-8") as stream:
        writer = csv.DictWriter(stream, fieldnames=FIELDS, lineterminator="\n")
        writer.writeheader(); writer.writerows(rows)


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--write", action="store_true")
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    try:
        expected, errors = materialize()
    except (OSError, KeyError, TypeError, ValueError, tomllib.TOMLDecodeError) as exc:
        print(f"error: origin census failed: {exc}"); return 1
    if errors:
        print("\n".join(errors)); return 1
    if args.write: write(expected)
    if args.check:
        if not OUTPUT.exists(): print("missing config/function-origins.csv"); return 1
        actual = read_csv(OUTPUT); errors.extend(validate_rows(actual))
        if actual != expected: errors.append("config/function-origins.csv is stale; run scripts/function-origins.py --write")
        if errors: print("\n".join(errors)); return 1
    counts = Counter(row["origin"] for row in expected)
    excluded = sum(row["disposition"] == "exclude" for row in expected)
    authored = sum(row["disposition"] == "authored" for row in expected)
    print(f"origin census OK: {len(expected)} rows, authored={authored}, excluded={excluded}, review={len(expected)-authored-excluded}; " + ", ".join(f"{k}={counts[k]}" for k in sorted(counts)))
    return 0

if __name__ == "__main__": raise SystemExit(main())
