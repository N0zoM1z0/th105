#!/usr/bin/env python3
"""Compare Suika's complete emitted action-state root, including switch metadata."""
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
UNIT = "exact-first-suika-action-state"
ADDRESS = 0x00598990
CALLABLE_SIZE = 79435
PAYLOAD_SIZE = 81136


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
        if hashlib.sha256(target).hexdigest() != "11eb3a1f3f5eef32dee111878375b1b0270c7a38b1be49161220adb548a49e45":
            raise ValueError("reviewed complete target payload changed")
        # Three sparse action tables and seventeen nested sequence/difficulty tables.
        tables = {}
        for address, count in (
            (0x005ABFDC, 33),
            (0x005AC144, 50),
            (0x005AC304, 31),
            (0x005AC470, 7),
            (0x005AC48C, 18),
            (0x005AC4D4, 17),
            (0x005AC518, 6),
            (0x005AC540, 6),
            (0x005AC558, 6),
            (0x005AC570, 7),
            (0x005AC58C, 4),
            (0x005AC59C, 4),
            (0x005AC5AC, 4),
            (0x005AC5BC, 15),
            (0x005AC5F8, 4),
            (0x005AC608, 4),
            (0x005AC618, 11),
            (0x005AC644, 4),
            (0x005AC654, 4),
            (0x005AC664, 4),
        ):
            name = f"table_{address:08X}"
            values = list(struct.unpack("<" + "I" * count,
                comparator.target_bytes(address, count * 4)))
            tables[address] = (name, values)
        boundary = reachable_boundary_audit(target[:CALLABLE_SIZE], ADDRESS, tables)
        if (boundary["decoded_instructions"] != 20324
                or boundary["reachable_instructions"] != 20321
                or boundary["unreached_ranges"] != [[0x5A09FD, 0x5A0A00],
                    [0x5A5A5D, 0x5A5A60], [0x5A97CD, 0x5A97D0]]
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
