#!/usr/bin/env python3
"""Compare Alice's complete emitted CPU policy, including switch metadata."""
from __future__ import annotations

import argparse
import hashlib
import importlib.util
import json
from pathlib import Path

from workflow_manifest import load_manifest

ROOT = Path(__file__).resolve().parents[1]
UNIT = "exact-first-alice-cpu-policy"
ADDRESS = 0x004F4B80
CALLABLE_SIZE = 16354
PAYLOAD_SIZE = 17009


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--object", type=Path, help="override the configured COFF object")
    args = parser.parse_args()
    try:
        spec = importlib.util.spec_from_file_location(
            "th105_payload_comparator", ROOT / "scripts" / "compare-function.py"
        )
        if spec is None or spec.loader is None:
            raise RuntimeError("canonical comparator is unavailable")
        comparator = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(comparator)
        target_sha256 = comparator.verify_target()
        unit = load_manifest()["units"][UNIT]
        function = unit["functions"][0]
        if int(function["address"], 0) != ADDRESS:
            raise ValueError("configured function address changed")
        object_path = args.object or ROOT / unit["object"]
        targets = comparator.known_targets()
        for binding in function.get("rel32_targets", []):
            name, address = binding.rsplit("=", 1)
            targets[name] = int(address, 0)
        candidate = comparator.coff_symbol_bytes(
            object_path,
            function["symbol_base"],
            ADDRESS,
            0xFFFFFFFF,  # Replay every relocation in the returned section tail.
            targets,
            comparator.known_data_targets(),
        )
        target = comparator.target_bytes(ADDRESS, PAYLOAD_SIZE)
        if hashlib.sha256(target).hexdigest() != "44c74a61697409bc3628dbd5c2e48788f4c0e5ce02a439bcce5331d19812431d":
            raise ValueError("reviewed complete target payload changed")
        mismatch = comparator.first_mismatch(target, candidate, ADDRESS)
        exact = len(candidate) == PAYLOAD_SIZE and candidate == target
        print(json.dumps({
            "result": "exact" if exact else "mismatch",
            "unit": UNIT,
            "target_sha256": target_sha256,
            "callable_size": CALLABLE_SIZE,
            "complete_payload_size": PAYLOAD_SIZE,
            "object_section_tail_size": len(candidate),
            "first_mismatch": mismatch,
            "canonical_payload_sha256": hashlib.sha256(candidate).hexdigest(),
        }, indent=2))
        return 0 if exact else 1
    except (OSError, ValueError, RuntimeError) as error:
        print(json.dumps({"result": "blocked", "error": str(error)}, indent=2))
        return 1


if __name__ == "__main__":
    raise SystemExit(main())
