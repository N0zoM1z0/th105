#!/usr/bin/env python3
"""Validate evidence-bounded TH105 clone families against exact target bytes."""

from __future__ import annotations

import argparse
import csv
import hashlib
import json
from pathlib import Path
import struct
import tomllib


ROOT = Path(__file__).resolve().parents[1]
MANIFEST = ROOT / "config" / "clone-families.toml"
TARGET_CONFIG = ROOT / "config" / "target.toml"
TARGET = ROOT / "resources" / "th105.exe"
FUNCTIONS = ROOT / "config" / "functions.csv"


def target_bytes(address: int, size: int) -> bytes:
    data = TARGET.read_bytes()
    pe = struct.unpack_from("<I", data, 0x3C)[0]
    section_count = struct.unpack_from("<H", data, pe + 6)[0]
    optional_size = struct.unpack_from("<H", data, pe + 20)[0]
    sections = pe + 24 + optional_size
    image_base = struct.unpack_from("<I", data, pe + 52)[0]
    rva = address - image_base
    for index in range(section_count):
        offset = sections + 40 * index
        virtual_size, virtual_address, raw_size, raw_pointer = struct.unpack_from(
            "<IIII", data, offset + 8
        )
        if virtual_address <= rva < virtual_address + max(virtual_size, raw_size):
            within = rva - virtual_address
            if within + size > max(virtual_size, raw_size):
                raise ValueError(f"range 0x{address:08X}+{size:#x} crosses PE section")
            raw_available = max(0, min(size, raw_size - within))
            raw = data[raw_pointer + within : raw_pointer + within + raw_available]
            if len(raw) != raw_available:
                raise ValueError("PE section raw data is truncated")
            return raw + bytes(size - raw_available)
    raise ValueError(f"address 0x{address:08X} is outside the PE")


def load_and_check(selected: str | None = None) -> list[dict[str, object]]:
    with MANIFEST.open("rb") as stream:
        manifest = tomllib.load(stream)
    with TARGET_CONFIG.open("rb") as stream:
        target_config = tomllib.load(stream)["target"]
    actual_target = hashlib.sha256(TARGET.read_bytes()).hexdigest()
    expected_target = str(manifest.get("target_sha256", "")).lower()
    if manifest.get("schema_version") != 1:
        raise ValueError("clone-family manifest schema_version must be 1")
    if expected_target != target_config["sha256"].lower() or actual_target != expected_target:
        raise ValueError("clone-family target SHA-256 attestation failed")
    with FUNCTIONS.open(newline="", encoding="utf-8") as stream:
        ledger = {row["address"]: row for row in csv.DictReader(stream)}

    families = manifest.get("families")
    if not isinstance(families, dict) or not families:
        raise ValueError("clone-family manifest has no families")
    if selected and selected not in families:
        raise ValueError(f"unknown clone family: {selected}")

    reports: list[dict[str, object]] = []
    seen: set[int] = set()
    for family_name, family in families.items():
        if selected and family_name != selected:
            continue
        size = family.get("size")
        expected_hash = family.get("normalized_sha256")
        offsets = family.get("zero_dword_offsets")
        members = family.get("members")
        if not isinstance(size, int) or size <= 0:
            raise ValueError(f"family {family_name} has invalid size")
        if not isinstance(expected_hash, str) or len(expected_hash) != 64:
            raise ValueError(f"family {family_name} has invalid normalized hash")
        if not isinstance(offsets, list) or any(
            not isinstance(offset, int) or offset < 0 or offset + 4 > size
            for offset in offsets
        ):
            raise ValueError(f"family {family_name} has invalid dword offsets")
        if len(set(offsets)) != len(offsets):
            raise ValueError(f"family {family_name} repeats a dword offset")
        if not isinstance(members, list) or not members:
            raise ValueError(f"family {family_name} has no members")

        member_reports: list[dict[str, object]] = []
        for member in members:
            if not isinstance(member, dict) or not isinstance(member.get("name"), str):
                raise ValueError(f"family {family_name} has invalid member")
            address = int(str(member.get("address", "")), 0)
            canonical = f"0x{address:08X}"
            if address in seen:
                raise ValueError(f"address {canonical} occurs in multiple clone families")
            seen.add(address)
            row = ledger.get(canonical)
            if row is None or int(row["size"]) != size:
                raise ValueError(f"family {family_name} ledger size mismatch at {canonical}")
            body = bytearray(target_bytes(address, size))
            for replacement in member.get("replacements", []):
                if not isinstance(replacement, dict):
                    raise ValueError(f"family {family_name} has invalid replacement")
                offset = replacement.get("offset")
                before = bytes.fromhex(str(replacement.get("from_hex", "")))
                after = bytes.fromhex(str(replacement.get("to_hex", "")))
                if not isinstance(offset, int) or not before or len(before) != len(after):
                    raise ValueError(f"family {family_name} has invalid replacement")
                if body[offset : offset + len(before)] != before:
                    raise ValueError(
                        f"family {family_name} replacement evidence changed at {canonical}+{offset:#x}"
                    )
                body[offset : offset + len(before)] = after
            for offset in offsets:
                body[offset : offset + 4] = bytes(4)
            digest = hashlib.sha256(body).hexdigest()
            member_reports.append(
                {
                    "name": member["name"],
                    "address": canonical,
                    "ledger_status": row["status"],
                    "normalized_sha256": digest,
                    "exact_template": digest == expected_hash,
                }
            )
            if digest != expected_hash:
                raise ValueError(
                    f"family {family_name} normalized hash mismatch at {canonical}: {digest}"
                )
        reports.append(
            {
                "family": family_name,
                "size": size,
                "members": member_reports,
                "member_count": len(member_reports),
                "normalized_sha256": expected_hash,
                "notes": family.get("notes", ""),
            }
        )
    return reports


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--check", action="store_true")
    parser.add_argument("--show", metavar="FAMILY")
    parser.add_argument("--json", action="store_true")
    args = parser.parse_args()
    try:
        reports = load_and_check(args.show)
        if args.json:
            print(json.dumps({"ok": True, "families": reports}, indent=2))
        elif args.show:
            for member in reports[0]["members"]:
                print(
                    f"{member['address']} {member['name']}: "
                    f"{member['normalized_sha256']} ({member['ledger_status']})"
                )
        else:
            print(
                f"clone families OK: {len(reports)} families, "
                f"{sum(report['member_count'] for report in reports)} members"
            )
        return 0
    except (OSError, ValueError, tomllib.TOMLDecodeError) as error:
        if args.json:
            print(json.dumps({"ok": False, "error": str(error)}, indent=2))
        else:
            print(f"error: {error}")
        return 1


if __name__ == "__main__":
    raise SystemExit(main())
