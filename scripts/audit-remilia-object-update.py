#!/usr/bin/env python3
"""Compare RemiliaObject's complete emitted update, including switch metadata."""
from __future__ import annotations

import argparse
import hashlib
import importlib.util
import json
from pathlib import Path
import struct

from workflow_manifest import load_manifest

ROOT = Path(__file__).resolve().parents[1]
UNIT = "exact-first-remilia-object-update"
ADDRESS = 0x00557690
CALLABLE_SIZE = 17793
PAYLOAD_SIZE = 18388


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
        if hashlib.sha256(target).hexdigest() != "793c1954983d385b07ead1e850f95b4c521448100500074eaa0b371e2f3b0cd6":
            raise ValueError("reviewed complete target payload changed")
        mismatch = comparator.first_mismatch(target, candidate, ADDRESS)
        exact = len(candidate) == PAYLOAD_SIZE and candidate == target
        # This diagnostic follows the actual byte-remap load in the reviewed
        # entry. It neither rebases destinations nor masks comparison bytes.
        candidate_remap = None
        if len(candidate) >= 0x2D and candidate[0x26:0x29] == bytes.fromhex("0fb680"):
            offset = struct.unpack_from("<I",candidate,0x29)[0]-ADDRESS
            if 0 <= offset and offset+199 <= len(candidate):
                candidate_remap = candidate[offset:offset+199]
        print(json.dumps({
            "result": "exact" if exact else "mismatch",
            "unit": UNIT,
            "target_sha256": target_sha256,
            "callable_size": CALLABLE_SIZE,
            "complete_payload_size": PAYLOAD_SIZE,
            "object_section_tail_size": len(candidate),
            "first_mismatch": mismatch,
            "unmasked_differing_bytes": sum(a != b for a, b in zip(target, candidate)) + abs(len(target) - len(candidate)),
            "canonical_payload_sha256": hashlib.sha256(candidate).hexdigest(),
            "diagnostic_remap_199_bytes_equal": candidate_remap == target[0x45F4:0x46BB],
        }, indent=2))
        return 0 if exact else 1
    except (OSError, ValueError, RuntimeError) as error:
        print(json.dumps({"result": "blocked", "error": str(error)}, indent=2))
        return 1


if __name__ == "__main__":
    raise SystemExit(main())
