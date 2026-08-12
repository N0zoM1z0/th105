#!/usr/bin/env python3
"""Validate and query reproducible TH105 function-probe build units."""

from __future__ import annotations

import csv
import hashlib
import os
from pathlib import Path
import re
import tomllib
from typing import Any


ROOT = Path(__file__).resolve().parents[1]
MANIFEST = ROOT / "config" / "match-units.toml"
FUNCTIONS = ROOT / "config" / "functions.csv"
TARGET_CONFIG = ROOT / "config" / "target.toml"
RELOCATIONS = ROOT / "config" / "reccmp-relocations.csv"
ALLOWED_KINDS = {"probe", "synthetic_island", "linked_candidate"}
ALLOWED_PROFILES = {"vc8-sp1-probe-o2"}
ADDRESS = re.compile(r"0x[0-9A-F]{8}$")
REL32_TARGET = re.compile(r"[^=\s]+=0x[0-9A-Fa-f]{8}$")
DIR32_TARGET = re.compile(r"[^=\s]+=[^=\s]+$")


def repository_path(raw: str, *, output: bool = False) -> Path:
    relative = Path(raw)
    if relative.is_absolute() or ".." in relative.parts:
        raise ValueError(f"path must be repository-relative: {raw!r}")
    resolved = (ROOT / relative).resolve()
    resolved.relative_to(ROOT)
    if output and resolved != ROOT / "build" and (ROOT / "build") not in resolved.parents:
        raise ValueError(f"generated object must be below build/: {raw!r}")
    return resolved


def canonical_address(raw: str) -> str:
    address = f"0x{int(raw, 0):08X}"
    if not ADDRESS.fullmatch(address):
        raise ValueError(f"invalid function address: {raw!r}")
    return address


def load_manifest() -> dict[str, Any]:
    with MANIFEST.open("rb") as stream:
        manifest = tomllib.load(stream)
    if manifest.get("schema_version") != 1:
        raise ValueError("config/match-units.toml must use schema_version = 1")

    with TARGET_CONFIG.open("rb") as stream:
        target = tomllib.load(stream)["target"]
    if str(manifest.get("target_sha256", "")).lower() != target["sha256"].lower():
        raise ValueError("match-unit target_sha256 does not match config/target.toml")

    with FUNCTIONS.open(newline="", encoding="utf-8") as stream:
        ledger = {row["address"]: row for row in csv.DictReader(stream)}
    with RELOCATIONS.open(newline="", encoding="utf-8") as stream:
        dir32_allowlist = {
            row["coff_symbol"] for row in csv.DictReader(stream)
        }

    units = manifest.get("units")
    if not isinstance(units, dict) or not units:
        raise ValueError("config/match-units.toml must define at least one unit")
    object_names: set[str] = set()
    addresses: set[str] = set()
    for name, unit in units.items():
        if not isinstance(unit, dict):
            raise ValueError(f"match unit {name!r} must be a table")
        if unit.get("kind") not in ALLOWED_KINDS:
            raise ValueError(f"match unit {name!r} has invalid kind")
        if unit.get("profile") not in ALLOWED_PROFILES:
            raise ValueError(f"match unit {name!r} has invalid compiler profile")
        if not isinstance(unit.get("enable_gs"), bool):
            raise ValueError(f"match unit {name!r} enable_gs must be boolean")
        include_dirs = unit.get("include_dirs", [])
        if not isinstance(include_dirs, list) or not all(
            isinstance(path, str) and path for path in include_dirs
        ):
            raise ValueError(f"match unit {name!r} include_dirs must be a string list")
        for raw_include_dir in include_dirs:
            include_dir = repository_path(raw_include_dir)
            if not include_dir.is_dir():
                raise ValueError(
                    f"match unit {name!r} include directory does not exist: "
                    f"{raw_include_dir!r}"
                )
        source = repository_path(str(unit.get("source", "")))
        if not source.is_file():
            raise ValueError(f"match unit {name!r} source does not exist")
        output = repository_path(str(unit.get("object", "")), output=True)
        if output.name in object_names:
            raise ValueError(f"duplicate match-unit object basename: {output.name}")
        object_names.add(output.name)

        functions = unit.get("functions")
        if not isinstance(functions, list) or not functions:
            raise ValueError(f"match unit {name!r} must define functions")
        for function in functions:
            if not isinstance(function, dict):
                raise ValueError(f"match unit {name!r} has invalid function row")
            address = canonical_address(str(function.get("address", "")))
            if address not in ledger:
                raise ValueError(f"match unit {name!r} address {address} is absent from ledger")
            if address in addresses:
                raise ValueError(f"function {address} occurs in multiple match units")
            addresses.add(address)
            if "contiguous_span" in function and not isinstance(
                function["contiguous_span"], bool
            ):
                raise ValueError(
                    f"match unit {name!r} function {address} contiguous_span must be boolean"
                )
            for mapping in function.get("rel32_targets", []):
                if not isinstance(mapping, str) or not REL32_TARGET.fullmatch(mapping):
                    raise ValueError(
                        f"match unit {name!r} function {address} has invalid "
                        f"REL32 mapping {mapping!r}"
                    )
            for mapping in function.get("dir32_targets", []):
                if not isinstance(mapping, str) or not DIR32_TARGET.fullmatch(mapping):
                    raise ValueError(
                        f"match unit {name!r} function {address} has invalid "
                        f"DIR32 mapping {mapping!r}"
                    )
                allowlist_key = mapping.partition("=")[2]
                if allowlist_key not in dir32_allowlist:
                    raise ValueError(
                        f"match unit {name!r} function {address} references "
                        f"unknown DIR32 allowlist key {allowlist_key!r}"
                    )
    return manifest


def find_unit(name_or_object: str, manifest: dict[str, Any]) -> tuple[str, dict[str, Any]]:
    units = manifest["units"]
    if name_or_object in units:
        return name_or_object, units[name_or_object]
    wanted = Path(name_or_object).name
    matches = [
        (name, unit)
        for name, unit in units.items()
        if Path(str(unit["object"])).name == wanted
    ]
    if len(matches) != 1:
        raise ValueError(f"unknown or ambiguous match unit/object: {name_or_object!r}")
    return matches[0]


def unit_for_address(
    address: str, manifest: dict[str, Any]
) -> tuple[str, dict[str, Any], dict[str, Any]] | None:
    wanted = canonical_address(address)
    for name, unit in manifest["units"].items():
        for function in unit["functions"]:
            if canonical_address(function["address"]) == wanted:
                return name, unit, function
    return None


def file_sha256(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as stream:
        for block in iter(lambda: stream.read(1024 * 1024), b""):
            digest.update(block)
    return digest.hexdigest()


def compiler_sha256() -> str:
    compiler_root = Path(
        os.environ.get("TH105_MSVC8_ROOT", str(ROOT / ".tools" / "msvc80-sp1"))
    )
    compiler = compiler_root / "bin" / "cl.exe"
    if not compiler.is_file():
        raise ValueError("missing VC8 SP1 compiler; run scripts/bootstrap-tools.sh")
    return file_sha256(compiler)


def unit_input_digest(name: str, unit: dict[str, Any]) -> tuple[str, list[str]]:
    """Return a conservative digest for all tracked inputs that can shape a probe."""

    source = repository_path(str(unit["source"]))
    paths = {
        source,
        MANIFEST,
        ROOT / "scripts" / "build.py",
        ROOT / "scripts" / "compare-function.py",
        ROOT / "scripts" / "compile-unit.sh",
        ROOT / "scripts" / "workflow_manifest.py",
        ROOT / "config" / "known-symbols.csv",
        ROOT / "config" / "reccmp-relocations.csv",
        TARGET_CONFIG,
    }
    paths.update((ROOT / "src").rglob("*.h"))
    paths.update((ROOT / "src").rglob("*.hpp"))
    # Vendored library translation units include headers beside the source.
    # Hash them too, so an upstream-header change cannot reuse stale evidence.
    paths.update(source.parent.glob("*.h"))
    for raw_include_dir in unit.get("include_dirs", []):
        include_dir = repository_path(str(raw_include_dir))
        paths.update(include_dir.rglob("*.h"))
    digest = hashlib.sha256()
    digest.update(name.encode("utf-8"))
    digest.update(str(unit["profile"]).encode("utf-8"))
    digest.update(str(unit["enable_gs"]).encode("ascii"))
    relative_paths: list[str] = []
    for path in sorted(paths):
        relative = str(path.relative_to(ROOT))
        relative_paths.append(relative)
        digest.update(relative.encode("utf-8"))
        digest.update(bytes.fromhex(file_sha256(path)))

    digest.update(bytes.fromhex(compiler_sha256()))
    return digest.hexdigest(), relative_paths
