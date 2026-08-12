#!/usr/bin/env python3
"""Build reproducible focused VC8 match units; full executable linking is pending."""

from __future__ import annotations

import argparse
from datetime import datetime, timezone
import json
import os
from pathlib import Path
import subprocess
import sys

from workflow_manifest import (
    MANIFEST,
    ROOT,
    compiler_sha256,
    file_sha256,
    find_unit,
    load_manifest,
    repository_path,
    unit_input_digest,
)


def build_unit(
    name: str,
    unit: dict[str, object],
    json_mode: bool,
    target_sha256: str,
) -> dict[str, object]:
    source = repository_path(str(unit["source"]))
    output = repository_path(str(unit["object"]), output=True)
    output.parent.mkdir(parents=True, exist_ok=True)
    environment = os.environ.copy()
    environment["TH105_ENABLE_GS"] = "1" if unit["enable_gs"] else "0"
    include_dirs = [
        str(repository_path(str(path))) for path in unit.get("include_dirs", [])
    ]
    environment["TH105_EXTRA_INCLUDE_DIRS"] = os.pathsep.join(include_dirs)
    command = [
        str(ROOT / "scripts" / "compile-unit.sh"),
        str(source),
        str(output),
    ]
    completed = subprocess.run(
        command,
        cwd=ROOT,
        env=environment,
        capture_output=json_mode,
        text=json_mode,
    )
    if completed.returncode != 0:
        raise RuntimeError(
            completed.stderr.strip() if json_mode else f"compiler exited {completed.returncode}"
        )
    input_digest, inputs = unit_input_digest(name, unit)
    provenance = {
        "schema_version": 1,
        "target_sha256": target_sha256,
        "unit": name,
        "kind": unit["kind"],
        "profile": unit["profile"],
        "enable_gs": unit["enable_gs"],
        "include_dirs": [
            str(Path(path).relative_to(ROOT)) for path in include_dirs
        ],
        "source": str(source.relative_to(ROOT)),
        "object": str(output.relative_to(ROOT)),
        "source_sha256": file_sha256(source),
        "object_sha256": file_sha256(output),
        "compiler_sha256": compiler_sha256(),
        "manifest_sha256": file_sha256(MANIFEST),
        "input_digest": input_digest,
        "inputs": inputs,
        "command": command,
        "built_utc": datetime.now(timezone.utc).isoformat().replace("+00:00", "Z"),
    }
    provenance_path = output.with_suffix(output.suffix + ".provenance.json")
    provenance_path.write_text(json.dumps(provenance, indent=2) + "\n", encoding="utf-8")
    return provenance


def compare_unit(unit: dict[str, object], json_mode: bool) -> tuple[int, list[object]]:
    output = repository_path(str(unit["object"]), output=True)
    reports: list[object] = []
    return_code = 0
    for function in unit["functions"]:  # type: ignore[index]
        assert isinstance(function, dict)
        command = [
            sys.executable,
            str(ROOT / "scripts" / "compare-function.py"),
        ]
        if function.get("contiguous_span"):
            command.append("--contiguous-span")
        if function.get("symbol_base"):
            command.extend(["--symbol-base", str(function["symbol_base"])])
        for mapping in function.get("rel32_targets", []):
            command.extend(["--rel32-target", str(mapping)])
        for mapping in function.get("dir32_targets", []):
            command.extend(["--dir32-target", str(mapping)])
        if json_mode:
            command.append("--json")
        command.extend([str(function["address"]), str(output)])
        completed = subprocess.run(
            command,
            cwd=ROOT,
            capture_output=json_mode,
            text=json_mode,
        )
        return_code = max(return_code, completed.returncode)
        if json_mode:
            try:
                reports.append(json.loads(completed.stdout))
            except json.JSONDecodeError:
                reports.append(
                    {
                        "result": "error",
                        "failure": {
                            "category": "comparison.output_invalid",
                            "message": completed.stderr or completed.stdout,
                        },
                    }
                )
                return_code = 1
    return return_code, reports


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    selection = parser.add_mutually_exclusive_group()
    selection.add_argument("--unit", help="build a unit by manifest id")
    selection.add_argument(
        "--object-name",
        help="build the unit owning this object basename (objdiff compatibility)",
    )
    parser.add_argument("--list", action="store_true", help="list configured units")
    parser.add_argument("--check", action="store_true", help="validate the manifest only")
    parser.add_argument("--compare", action="store_true", help="run canonical strict comparisons")
    parser.add_argument("--json", action="store_true", help="emit one JSON result")
    args = parser.parse_args()

    try:
        manifest = load_manifest()
        if args.check:
            result = {
                "ok": True,
                "schema_version": manifest["schema_version"],
                "units": len(manifest["units"]),
                "functions": sum(
                    len(unit["functions"]) for unit in manifest["units"].values()
                ),
            }
            print(json.dumps(result, indent=2) if args.json else (
                f"match-unit graph OK: {result['units']} units, "
                f"{result['functions']} functions"
            ))
            return 0
        if args.list:
            rows = [
                {
                    "unit": name,
                    "kind": unit["kind"],
                    "source": unit["source"],
                    "object": unit["object"],
                    "addresses": [row["address"] for row in unit["functions"]],
                }
                for name, unit in manifest["units"].items()
            ]
            if args.json:
                print(json.dumps(rows, indent=2))
            else:
                for row in rows:
                    print(
                        f"{row['unit']}: {row['source']} -> {row['object']} "
                        f"({', '.join(row['addresses'])})"
                    )
            return 0
        selector = args.unit or args.object_name
        if not selector:
            parser.error("one of --unit, --object-name, --list, or --check is required")
        name, unit = find_unit(selector, manifest)
        provenance = build_unit(name, unit, args.json, manifest["target_sha256"])
        compare_code, comparisons = (0, [])
        if args.compare:
            compare_code, comparisons = compare_unit(unit, args.json)
        if args.json:
            print(json.dumps({
                "result": "ok" if compare_code == 0 else "comparison_failed",
                "build": provenance,
                "comparisons": comparisons,
            }, indent=2))
        return compare_code
    except (OSError, RuntimeError, ValueError) as error:
        if args.json:
            print(json.dumps({
                "result": "error",
                "failure": {"category": "build.error", "message": str(error)},
            }, indent=2))
        else:
            print(f"error: {error}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    raise SystemExit(main())
