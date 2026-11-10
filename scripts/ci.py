#!/usr/bin/env python3
"""Run basic syntax and whitespace checks using only the standard library."""
from pathlib import Path
import argparse
import ast
import json
import os
import subprocess
import tomllib

ROOT = Path(__file__).resolve().parents[1]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--all", action="store_true", help="check all tracked files (used by GitHub Actions)")
    args = parser.parse_args()
    names = set()
    commands = [["git", "ls-files", "--others", "--exclude-standard", "-z"]]
    if args.all:
        commands.append(["git", "ls-files", "-z"])
    else:
        commands.append(["git", "diff", "HEAD", "--name-only", "-z"])
    for command in commands:
        names.update(n for n in subprocess.check_output(command, cwd=ROOT).decode().split("\0") if n)
    checked = 0
    for name in sorted(names):
        path = ROOT / name
        if not path.is_file() or path.is_symlink():
            continue
        if path.suffix == ".py":
            ast.parse(path.read_bytes(), filename=name)
        elif path.suffix == ".json":
            json.loads(path.read_text(encoding="utf-8"))
        elif path.suffix == ".toml":
            tomllib.loads(path.read_text(encoding="utf-8"))
        elif path.suffix == ".sh" or name == "scripts/repo-python":
            subprocess.run(["bash", "-n", str(path)], check=True)
        else:
            continue
        checked += 1
    subprocess.run(["git", "diff", "--check"], cwd=ROOT, check=True)
    subprocess.run(["git", "diff", "--cached", "--check"], cwd=ROOT, check=True)
    if os.environ.get("CI"):
        subprocess.run(["git", "show", "--format=", "--first-parent", "--check", "HEAD"], cwd=ROOT, check=True)
    print(f"Basic checks passed ({checked} syntax files).")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
