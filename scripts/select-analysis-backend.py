#!/usr/bin/env python3
"""Select verified IDA first and fall back to the independent Ghidra MCP."""

from __future__ import annotations

import json
from pathlib import Path
import subprocess
import sys
from typing import Any


ROOT = Path(__file__).resolve().parents[1]


def run_check(script: str) -> tuple[int, Any, str]:
    completed = subprocess.run(
        [sys.executable, str(ROOT / "scripts" / script)],
        cwd=ROOT,
        capture_output=True,
        text=True,
    )
    stdout = completed.stdout.strip()
    try:
        parsed = json.loads(stdout)
    except json.JSONDecodeError:
        parsed = stdout
    return completed.returncode, parsed, completed.stderr.strip()


def main() -> None:
    ida_code, ida_result, ida_stderr = run_check("check-ida-mcp.py")
    if ida_code == 0:
        print(json.dumps({"ok": True, "backend": "ida", "preflight": ida_result}, indent=2))
        return

    reason = ida_result.get("reason") if isinstance(ida_result, dict) else None
    if reason in {"target_mismatch", "boundary_conflict"}:
        print(
            json.dumps(
                {
                    "ok": False,
                    "backend": None,
                    "reason": reason,
                    "ida": ida_result,
                    "stderr": ida_stderr,
                },
                indent=2,
            )
        )
        raise SystemExit(1)

    ghidra_code, ghidra_result, ghidra_stderr = run_check("check-mcp.py")
    if ghidra_code == 0:
        print(
            json.dumps(
                {
                    "ok": True,
                    "backend": "ghidra",
                    "ida_unavailable": ida_result,
                    "preflight": ghidra_result,
                },
                indent=2,
            )
        )
        return

    print(
        json.dumps(
            {
                "ok": False,
                "backend": None,
                "reason": "no_verified_backend",
                "ida": ida_result,
                "ida_stderr": ida_stderr,
                "ghidra": ghidra_result,
                "ghidra_stderr": ghidra_stderr,
            },
            indent=2,
        )
    )
    raise SystemExit(1)


if __name__ == "__main__":
    main()
