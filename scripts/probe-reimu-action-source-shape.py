#!/usr/bin/env python3
"""Build a diagnostic Reimu case-expansion probe below build/, without exact credit."""
from __future__ import annotations

import argparse
import hashlib
import importlib.util
import json
import os
from pathlib import Path
import re
import shutil
import subprocess
import sys
import tomllib

ROOT = Path(__file__).resolve().parents[1]
SOURCE = ROOT / "src/characters/ReimuActionStateDispatch.cpp"
HEADER = "ReimuActionStateStaging.hpp"
SYMBOL = "?run_checked_action_dispatch@ReimuActionStatePreludeView@th105@@QAE_NXZ"
TOKEN = re.compile(r'//[^\n]*|/\*[\s\S]*?\*/|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|'
                   r'\bcase\s+(\d+)\s*:|\bdefault\s*:|[{}]')
INCLUDE = re.compile(r'^#include "([^"]+)"\s*$', re.M)


def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def load(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / "scripts" / filename)
    module = importlib.util.module_from_spec(spec)
    sys.modules[name] = module
    spec.loader.exec_module(module)
    return module


def generate(output):
    canonical = load("reimu_shape_canonical", "compare-function.py")
    target_sha = canonical.verify_target()
    mapper = load("reimu_shape_mapper", "compare-giant-action-switches.py")
    target_mapper = mapper.load_target_mapper()
    manifest = tomllib.loads((ROOT / "config/giant-action-switches.toml").read_text())
    root = target_mapper.select_root(manifest, "reimu-vslot28")
    target = target_mapper.map_root(target_mapper.PeImage(ROOT / "resources/th105.exe"),
                                    target_mapper.load_function_rows(ROOT / "config/functions.csv"), root)
    owners = {key: group["destination"] for region in target["regions"]
              for group in region["groups"] if group["destination"] != 0x48CE1F
              for key in group["cases"]}
    # These direct equality arms sit outside the three byte-index tables.
    owners.update({300: 0x47CBBD, 560: 0x48790B})
    inputs = {SOURCE, SOURCE.parent / HEADER}

    def inline(match):
        name = match.group(1)
        if name == HEADER:
            return match.group(0)
        path = SOURCE.parent / name
        if not name.startswith("ReimuActionState") or path.parent != SOURCE.parent or not path.is_file():
            raise ValueError(f"unexpected fragment include: {name}")
        inputs.add(path)
        return INCLUDE.sub(inline, path.read_text())

    text = INCLUDE.sub(inline, SOURCE.read_text())
    depth, labels = 0, []
    for token in TOKEN.finditer(text):
        raw = token.group(0)
        if raw == "{":
            depth += 1
        elif raw == "}":
            depth -= 1
        elif depth == 3 and (token.group(1) is not None or raw.startswith("default")):
            labels.append((token.start(), token.end(), int(token.group(1)) if token.group(1) else None))
    if depth or not labels or labels[-1][2] is not None or len(labels) != len(owners)+1:
        raise ValueError("outer action switch/label boundary changed")
    bodies, index = {}, 0
    while index < len(labels)-1:
        keys, last = [labels[index][2]], index
        while last+1 < len(labels)-1 and not text[labels[last][1]:labels[last+1][0]].strip():
            last += 1
            keys.append(labels[last][2])
        body = text[labels[last][1]:labels[last+1][0]]
        for key in keys:
            if key in bodies:
                raise ValueError("duplicate source action")
            bodies[key] = body
        index = last+1
    if bodies.keys() != owners.keys():
        raise ValueError("source keys differ from canonical nondefault actions")

    marker = "    switch (selected_action) {"
    if text.count(marker) != 1:
        raise ValueError("staged action-switch spelling changed")
    pieces = [text[:text.index(marker)]]
    groups = []
    for region, predicate in (("low", lambda key: key <= 300),
                              ("mid", lambda key: 300 < key <= 560),
                              ("high", lambda key: key > 560)):
        if region != "high":
            pieces.append(f"    if (selected_action <= {300 if region == 'low' else 560}) {{\n")
        pieces.append("    switch (selected_action) {\n")
        pending = [key for key in bodies if predicate(key)]
        while pending:
            key = pending[0]
            shared = [other for other in pending if owners[other] == owners[key]]
            if any(bodies[other] != bodies[key] for other in shared):
                raise ValueError("shared target owner has different source bodies")
            body = bodies[key]
            if len(shared) == 1:
                body = re.sub(r"\bselected_action\b", str(key), body)
            pieces.append("    "+" ".join(f"case {other}:" for other in shared)+body)
            groups.append({"region": region, "keys": shared, "target_entry": hex(owners[key])})
            pending = [other for other in pending if other not in shared]
        pieces.append("    default:\n        update_common_action_state();\n        return true;\n    }\n")
        if region != "high":
            pieces.append("    }\n")
    pieces.append("}\n\n} // namespace th105\n")
    output.mkdir(parents=True, exist_ok=True)
    generated = output / SOURCE.name
    generated.write_bytes("".join(pieces).replace("\n", "\r\n").encode())
    shutil.copyfile(SOURCE.parent / HEADER, output / HEADER)
    return mapper, root, target, {
        "schema": "th105-reimu-action-source-shape-v1", "target_sha256": target_sha,
        "source_sha256": {str(path.relative_to(ROOT)): sha(path) for path in sorted(inputs)},
        "generated_source_sha256": sha(generated), "groups": groups,
        "scope": "ordinary C++ case/region expansion only; bool staging and unresolved740 remain; no implementation/exact credit"}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--output-dir", type=Path, default=ROOT / "build/reimu-action-source-shape")
    parser.add_argument("--emit-only", action="store_true")
    args = parser.parse_args()
    output = args.output_dir.resolve()
    if not output.is_relative_to(ROOT / "build") or output == ROOT / "build":
        parser.error("generated probe files must occupy a subdirectory of build/")
    mapper, root, target, report = generate(output)
    if not args.emit_only:
        obj = output / "ReimuActionStateDispatch.obj"
        with (output / "compile.log").open("w") as log:
            subprocess.run([str(ROOT / "scripts/compile-unit.sh"), str(output / SOURCE.name), str(obj)],
                           cwd=ROOT, stdout=log, stderr=subprocess.STDOUT, check=True)
        if any(sha(ROOT / path) != digest for path, digest in report["source_sha256"].items()):
            raise ValueError("source inputs changed during compilation")
        candidate = mapper.build_candidate_map(mapper.CoffObject(obj, symbol_base=SYMBOL), root)
        comparison = mapper.compare_maps(target, candidate)
        (output / "mapping.json").write_text(json.dumps(comparison, indent=2)+"\n")
        report.update(object_sha256=sha(obj), text_bytes=candidate["text_size"],
                      metadata_start=candidate["metadata_start"],
                      candidate_unique_destinations=candidate["unique_destination_count"],
                      split_target_groups=comparison["split_target_group_count"],
                      default_compiler_sha256=sha(ROOT / ".tools/msvc80-sp1/bin/cl.exe"),
                      compiler_environment={key: os.environ.get(key) for key in
                          ("CL", "_CL_", "INCLUDE", "TH105_MSVC8_ROOT", "TH105_WINEPREFIX",
                           "TH105_ENABLE_GS", "TH105_FP_MODE", "TH105_EXTRA_INCLUDE_DIRS")},
                      compile_script_sha256=sha(ROOT / "scripts/compile-unit.sh"))
    (output / "receipt.json").write_text(json.dumps(report, indent=2)+"\n")
    print(json.dumps({key: value for key, value in report.items() if key not in ("source_sha256", "groups")}, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
