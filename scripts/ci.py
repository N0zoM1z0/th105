#!/usr/bin/env python3
"""Check tracked syntax, ledgers, build configuration and private artifacts."""
from pathlib import Path
import argparse
import ast
import json
import os
import subprocess
import sys
import tomllib

ROOT = Path(__file__).resolve().parents[1]
PRIVATE_ROOTS = {".analysis", ".tools", ".venv", "build", "local"}
PRIVATE_SUFFIXES = {".exe", ".dll", ".obj", ".lib", ".pdb", ".gpr", ".pyc",
                    ".jar", ".class", ".zip", ".7z", ".rar", ".dat", ".pem", ".key"}


def check_private_artifact(name, path):
    parts = Path(name).parts
    if (parts[0] in PRIVATE_ROOTS or path.suffix.lower() in PRIVATE_SUFFIXES
            or any(part.endswith(".rep") for part in parts)
            or path.name in {".env", "id_rsa", "id_ed25519", "reccmp-user.yml"}):
        raise ValueError(f"private/generated artifact must stay untracked: {name}")
    if path.is_file():
        with path.open("rb") as stream:
            header = stream.read(64)
        if header.startswith((b"MZ", b"\x7fELF", b"PK\x03\x04")) or b"PRIVATE KEY-----" in header:
            raise ValueError(f"private binary/key must stay untracked: {name}")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--all", action="store_true", help="compatibility option; all tracked files are always checked")
    parser.add_argument("--base", help="also check whitespace in every commit after this PR/push base")
    args = parser.parse_args()
    names = set()
    commands = [["git", "ls-files", "--others", "--exclude-standard", "-z"],
                ["git", "ls-files", "-z"]]
    for command in commands:
        names.update(n for n in subprocess.check_output(command, cwd=ROOT).decode().split("\0") if n)
    checked = 0
    for name in sorted(names):
        path = ROOT / name
        check_private_artifact(name, path)
        if not path.exists() and not path.is_symlink():
            continue
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
    if args.base:
        base = subprocess.check_output(
            ["git", "rev-parse", "--verify", args.base + "^{commit}"], cwd=ROOT,
        ).decode().strip()
        subprocess.run(["git", "log", "--format=", "--check", base + "..HEAD"],
                       cwd=ROOT, check=True)
    elif os.environ.get("CI"):
        subprocess.run(["git", "show", "--format=", "--first-parent", "--check", "HEAD"], cwd=ROOT, check=True)
    subprocess.run([sys.executable, "-S", "-B", "scripts/validate-tracking.py", "--portable"],
                   cwd=ROOT, check=True)
    print(f"Basic checks passed ({checked} syntax files).")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
