#!/usr/bin/env python3
"""Compare Tenshi's complete emitted action-state root, including switch metadata."""
from __future__ import annotations

import argparse
import hashlib
import importlib.util
import json
import struct

from giant_owner_audit import reachable_boundary_audit
from pathlib import Path

from workflow_manifest import load_manifest

ROOT = Path(__file__).resolve().parents[1]
UNIT = "exact-first-tenshi-action-state"
ADDRESS = 0x0063D3E0
CALLABLE_SIZE = 47784
PAYLOAD_SIZE = 48968


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
        if hashlib.sha256(target).hexdigest() != "a7e25e318b6ffcc43edbca3e9e3e34f311e5343c82c1a0b91d6a6d45a52d6d47":
            raise ValueError("reviewed complete target payload changed")
        # Resolve all three action tables and all three nested difficulty tables.
        tables = {}
        for name, address, count in (
            ("low", 0x648E88, 35), ("mid", 0x648FF8, 36),
            ("high", 0x64916C, 37), ("difficulty720", 0x6492F8, 4),
            ("difficulty740", 0x649308, 4), ("difficulty741", 0x649318, 4),
        ):
            values = list(struct.unpack("<" + "I" * count,
                comparator.target_bytes(address, count * 4)))
            tables[address] = (name, values)
        boundary = reachable_boundary_audit(target[:CALLABLE_SIZE], ADDRESS, tables)
        if (boundary["decoded_instructions"] != 12490
                or boundary["reachable_instructions"] != 12489
                or boundary["unreached_ranges"] != [[0x647C49, 0x647C50]]
                or boundary["unresolved_indirect_exits"]):
            raise ValueError("reviewed native callable boundary changed")
        mismatch = comparator.first_mismatch(target, candidate, ADDRESS)
        exact = len(candidate) == PAYLOAD_SIZE and candidate == target
        print(json.dumps({
            "result": "exact" if exact else "mismatch",
            "unit": UNIT,
            "native_boundary": boundary,
            "target_sha256": target_sha256,
            "callable_size": CALLABLE_SIZE,
            "complete_payload_size": PAYLOAD_SIZE,
            "object_section_tail_size": len(candidate),
            "first_mismatch": mismatch,
            "unmasked_differing_bytes": sum(a != b for a, b in zip(target, candidate)) + abs(len(target) - len(candidate)),
            "canonical_payload_sha256": hashlib.sha256(candidate).hexdigest(),
        }, indent=2))
        return 0 if exact else 1
    except (OSError, ValueError, RuntimeError) as error:
        print(json.dumps({"result": "blocked", "error": str(error)}, indent=2))
        return 1


if __name__ == "__main__":
    raise SystemExit(main())
