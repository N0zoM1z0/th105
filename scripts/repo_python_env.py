"""Check the interpreter and importable packages used by scripts/repo-python."""
from __future__ import annotations

import importlib
from importlib import metadata
from pathlib import Path
import platform
import re
import sys

ROOT = Path(__file__).resolve().parents[1]


def load_pins(path: Path) -> dict[str, str]:
    pins = {}
    for line in path.read_text(encoding="utf-8").splitlines():
        line = line.split("#", 1)[0].strip()
        if not line:
            continue
        match = re.fullmatch(r"([A-Za-z0-9_.-]+)==([0-9][A-Za-z0-9.+!-]*)", line)
        if match is None or match[1] in pins:
            raise ValueError(f"requirements must contain unique exact pins: {line}")
        pins[match[1]] = match[2]
    if not pins:
        raise ValueError("repository Python dependency pins are empty")
    return pins


def check_environment(root: Path = ROOT) -> None:
    expected_python = (root / ".python-version").read_text(encoding="utf-8").strip()
    if not re.fullmatch(r"[0-9]+\.[0-9]+\.[0-9]+", expected_python):
        raise ValueError(".python-version must pin a complete CPython version")
    actual_python = platform.python_version()
    if platform.python_implementation() != "CPython" or actual_python != expected_python:
        raise ValueError(f"need CPython {expected_python}; selected {platform.python_implementation()} {actual_python}")

    pins = load_pins(root / "scripts/requirements-ci.txt")
    for package, expected in pins.items():
        try:
            actual = metadata.version(package)
        except metadata.PackageNotFoundError as error:
            raise ValueError(f"missing locked dependency {package}=={expected}") from error
        if actual != expected:
            raise ValueError(f"need {package}=={expected}; selected {actual}")

    for package in ("capstone", "pefile", "unicorn"):
        module = importlib.import_module(package)
        if module.__version__ != pins[package]:
            raise ValueError(f"imported {package} does not match its installed locked distribution")
        if package in ("capstone", "unicorn"):
            native_version = module.cs_version if package == "capstone" else module.uc_version
            expected_api = tuple(int(part) for part in pins[package].split(".")[:2])
            if native_version()[:2] != expected_api:
                raise ValueError(f"{package} native library API does not match its locked wrapper")
    # Capstone4 imports this even on Python3.11; verify the declared dependency.
    importlib.import_module("pkg_resources")


def main() -> int:
    try:
        check_environment()
    except (OSError, ValueError, ImportError) as error:
        print(f"error: {error}\nUse the README.md repository Python setup commands.", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
