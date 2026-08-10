#!/usr/bin/env python3
"""Fast identity check for the one supported executable."""

from __future__ import annotations

import hashlib
from pathlib import Path
import sys


ROOT = Path(__file__).resolve().parents[1]
TARGET = ROOT / "resources" / "th105.exe"
EXPECTED_SIZE = 3_039_232
EXPECTED_SHA256 = "49c23d9467b9927ba687ed2b873c4bc2d2f39ddadc9f55051ccf10172c0b7c11"


def main() -> int:
    path = Path(sys.argv[1]).resolve() if len(sys.argv) > 1 else TARGET
    if not path.is_file():
        print(f"missing target: {path}", file=sys.stderr)
        print("copy the original Japanese 1.06a th105c.exe to resources/th105.exe", file=sys.stderr)
        return 1

    size = path.stat().st_size
    digest = hashlib.sha256(path.read_bytes()).hexdigest()
    if size != EXPECTED_SIZE or digest != EXPECTED_SHA256:
        print(f"unsupported executable: {path}", file=sys.stderr)
        print(f"  size:   {size} (expected {EXPECTED_SIZE})", file=sys.stderr)
        print(f"  sha256: {digest}", file=sys.stderr)
        return 1

    print(f"target OK: {path}")
    print(f"sha256: {digest}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
