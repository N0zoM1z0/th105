#!/usr/bin/env python3
"""Compile/link one pinned VC8 LTCG comparison unit without executing it."""
import argparse
import json
from linked_pe import build_linked
from workflow_manifest import load_manifest


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("unit")
    args = parser.parse_args()
    try:
        unit = load_manifest()["units"][args.unit]
        if unit["kind"] != "linked_candidate":
            raise ValueError("unit is not a linked candidate")
        metadata = build_linked(args.unit, unit)
        print(json.dumps({"ok": True, "unit": args.unit, "image_sha256": metadata["image_sha256"]}))
        return 0
    except (OSError, ValueError, KeyError, RuntimeError) as error:
        parser.exit(1, str(error) + "\n")


if __name__ == "__main__":
    raise SystemExit(main())
