#!/usr/bin/env python3
"""Run exact-acceptance tooling checks; optional diagnostics use --all-tests."""

from __future__ import annotations

import argparse
import os
from pathlib import Path
import subprocess
import sys


ROOT = Path(__file__).resolve().parents[1]

# Reconstruction experiments are optional. The routine gate protects strict
# comparison, relocation/extent ownership, the environment and exact accounting.
EXACT_TEST_MODULES = (
    "test_workflow_tooling",
    "test_compare_unit_object",
    "test_owned_extent_comparison",
    "test_linked_pe",
    "test_linked_lifecycle",
    "test_linked_noreturn",
    "test_linked_switch_replay",
    "test_select_constructor_audit",
    "test_repo_python",
    "test_progress_svg",
)


def tracked(pattern: str) -> list[str]:
    output = subprocess.run(
        ["git", "ls-files", "--cached", "--others", "--exclude-standard", "-z", pattern],
        cwd=ROOT,
        check=True,
        stdout=subprocess.PIPE,
    ).stdout
    return [
        entry
        for raw in output.split(b"\0")
        if raw
        for entry in [raw.decode()]
        if (ROOT / entry).is_file()
    ]


def run(label: str, command: list[str], *, cwd: Path = ROOT) -> None:
    print(f"\n==> {label}", flush=True)
    environment = os.environ.copy()
    environment["PYTHONPYCACHEPREFIX"] = str(ROOT / "build" / "pycache")
    subprocess.run(command, cwd=cwd, env=environment, check=True)


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--all-tests", action="store_true",
        help="also run optional analysis/probe tests (no native corpus rebuild)",
    )
    args = parser.parse_args()
    try:
        run("Check repository Python environment", [sys.executable, "scripts/repo_python_env.py"])
        python_files = sorted(
            set(
                tracked("scripts/*.py")
                + tracked("scripts/ida/*.py")
                + tracked("tests/*.py")
            )
        )
        run("Compile tracked Python", [sys.executable, "-m", "py_compile", *python_files])
        shell_files = tracked("scripts/*.sh") + tracked("scripts/repo-python")
        if shell_files:
            run("Check shell syntax", ["bash", "-n", *shell_files])
        run(
            "Audit floating relocation mappings",
            [sys.executable, "scripts/check-match-literals.py", "--skip-target-bytes"],
        )
        run(
            "Validate reconstruction ledgers",
            [sys.executable, "scripts/validate-tracking.py", "--skip-target-bytes"],
        )
        run("Validate match-unit graph", [sys.executable, "scripts/build.py", "--check"])
        if args.all_tests:
            run(
                "Run all tooling and analysis tests",
                [sys.executable, "-m", "unittest", "discover", "-s", "tests", "-v"],
            )
        else:
            run(
                "Run exact-acceptance tooling tests",
                [sys.executable, "-m", "unittest", "-v", *EXACT_TEST_MODULES],
                cwd=ROOT / "tests",
            )
        run("Check generated progress", [sys.executable, "scripts/progress.py", "--check"])
        if os.environ.get("CI"):
            run(
                "Check generated progress is committed",
                [
                    "git",
                    "diff",
                    "--exit-code",
                    "--",
                    "docs/PROGRESS.md",
                    "resources/progress.svg",
                ],
            )
        run(
            "Smoke-test status report",
            [sys.executable, "scripts/report-reconstruction-status.py", "--summary"],
        )
        run("Check whitespace", ["git", "diff", "--check"])
    except (OSError, subprocess.CalledProcessError) as exc:
        print(f"error: CI validation failed: {exc}")
        return 1
    print("\nTH105 target-independent CI checks passed")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
