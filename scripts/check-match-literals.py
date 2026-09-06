#!/usr/bin/env python3
"""Audit VC8 floating-literal relocations and manifest overrides."""

from __future__ import annotations

import argparse
import csv
import hashlib
from pathlib import Path
import tomllib

from match_literals import audit_real_literals


ROOT = Path(__file__).resolve().parents[1]
RELOCATIONS = ROOT / "config" / "reccmp-relocations.csv"
MANIFEST = ROOT / "config" / "match-units.toml"
TARGET_CONFIG = ROOT / "config" / "target.toml"
TARGET = ROOT / "resources" / "th105.exe"


def verified_target_bytes() -> bytes:
    with TARGET_CONFIG.open("rb") as stream:
        expected = tomllib.load(stream)["target"]
    data = TARGET.read_bytes()
    if len(data) != int(expected["size"]):
        raise ValueError("resources/th105.exe: target size mismatch")
    digest = hashlib.sha256(data).hexdigest()
    if digest != expected["sha256"]:
        raise ValueError(
            f"resources/th105.exe: target SHA-256 mismatch: got {digest}"
        )
    return data


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    target = parser.add_mutually_exclusive_group()
    target.add_argument("--require-target", action="store_true")
    target.add_argument("--skip-target-bytes", action="store_true")
    args = parser.parse_args()
    try:
        with RELOCATIONS.open(newline="", encoding="utf-8") as stream:
            relocation_rows = list(csv.DictReader(stream))
        with MANIFEST.open("rb") as stream:
            manifest = tomllib.load(stream)
        target_data = None if args.skip_target_bytes else verified_target_bytes()
        counts = audit_real_literals(
            relocation_rows, manifest, target_data=target_data
        )
    except (OSError, KeyError, TypeError, ValueError, tomllib.TOMLDecodeError) as exc:
        print(f"error: floating relocation audit failed: {exc}")
        return 1
    target_status = (
        f"{counts['target_checks']} target references checked"
        if target_data is not None
        else "target bytes skipped"
    )
    print(
        "floating relocation audit OK: "
        f"{counts['ledger_literals']} ledger literals, "
        f"{counts['explicit_mappings']} explicit mappings; {target_status}"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
