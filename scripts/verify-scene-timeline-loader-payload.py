#!/usr/bin/env python3
"""Verify the timeline loader's complete code, dispatch tables and provenance."""
from __future__ import annotations

import hashlib
import importlib.util
import json

from workflow_manifest import ROOT, compiler_sha256, load_manifest, unit_input_digest

UNIT = "exact-first-scene-timeline-loader"
ADDRESS = 0x004540F0
CALLABLE_SIZE = 1584
PAYLOAD_SIZE = 1676
PAYLOAD_SHA256 = "b6bb1b77c0258c4c24bf3ff0eeec71ea11409e7f1af88d4d91e0dc13fe1af973"


def verify() -> dict:
    unit = load_manifest()["units"][UNIT]
    function = unit["functions"][0]
    if int(function["address"], 0) != ADDRESS:
        raise ValueError("timeline unit entry changed")
    obj = ROOT / unit["object"]
    provenance = json.loads(obj.with_suffix(obj.suffix + ".provenance.json").read_text())
    digest, _ = unit_input_digest(UNIT, unit)
    if (provenance.get("unit") != UNIT or provenance.get("input_digest") != digest
            or provenance.get("compiler_sha256") != compiler_sha256()
            or provenance.get("profile") != unit["profile"]
            or provenance.get("enable_gs") != unit["enable_gs"]
            or provenance.get("object_sha256") != hashlib.sha256(obj.read_bytes()).hexdigest()):
        raise ValueError("fresh focused build provenance is required")
    spec = importlib.util.spec_from_file_location("canonical_compare", ROOT / "scripts/compare-function.py")
    compare = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(compare)
    target_sha = compare.verify_target()
    targets = compare.known_targets()
    for mapping in function.get("rel32_targets", []):
        symbol, address = mapping.rsplit("=", 1)
        targets[symbol] = int(address, 0)
    overrides = dict(mapping.rsplit("=", 1) for mapping in function.get("dir32_targets", []))
    expected = compare.target_bytes(ADDRESS, PAYLOAD_SIZE)
    if hashlib.sha256(expected).hexdigest() != PAYLOAD_SHA256:
        raise ValueError("reviewed native payload changed")
    actual = compare.coff_symbol_bytes(obj, function["symbol_base"], ADDRESS,
                                      PAYLOAD_SIZE, targets, compare.known_data_targets(), overrides)
    if len(actual) != PAYLOAD_SIZE or actual != expected:
        raise ValueError("complete timeline payload mismatch: " + str(
            compare.first_mismatch(expected, actual, ADDRESS)))
    return {"result": "exact", "unit": UNIT, "address": f"0x{ADDRESS:08X}",
            "callable_bytes": CALLABLE_SIZE, "payload_bytes": PAYLOAD_SIZE,
            "payload_sha256": PAYLOAD_SHA256, "target_sha256": target_sha,
            "build_provenance_verified": True}


if __name__ == "__main__":
    try:
        print(json.dumps(verify(), indent=2))
    except (OSError, ValueError, KeyError, RuntimeError) as exc:
        raise SystemExit(str(exc))
