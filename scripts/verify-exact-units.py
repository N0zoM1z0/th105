#!/usr/bin/env python3
"""Cold-build and compare every configured TH105 match unit.

The manifest also contains intentional nonexact probe units, so ``--all`` is a
complete-graph fail-fast diagnostic rather than an accepted-exact-only replay.
"""

from __future__ import annotations

import argparse
import subprocess
import sys

from workflow_manifest import ROOT, load_manifest


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--all", action="store_true", help="verify the complete unit graph")
    args = parser.parse_args()
    if not args.all:
        parser.error("aggregate verification requires --all")
    try:
        manifest = load_manifest()
        units = manifest["units"]
        for name, unit in units.items():
            output = ROOT / str(unit["object"])
            if output.exists():
                output.unlink()
            provenance = output.with_suffix(output.suffix + ".provenance.json")
            if provenance.exists():
                provenance.unlink()
            subprocess.run(
                [sys.executable, "scripts/build.py", "--unit", name, "--compare"],
                cwd=ROOT,
                check=True,
            )
    except (OSError, RuntimeError, ValueError, subprocess.CalledProcessError) as exc:
        print(f"error: exact-unit replay failed: {exc}")
        return 1
    print(f"exact-unit replay OK: {len(units)} cold unit(s)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
