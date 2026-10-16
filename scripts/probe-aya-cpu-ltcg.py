#!/usr/bin/env python3
"""Build an Aya CPU LTCG probe with real engine objects and static VC8 CRT.

This is a provenance experiment, not a canonical acceptance command. Generated
source/images stay under build/. No executable address bindings, fake callers,
stub helpers or unresolved-link overrides are supplied.
"""
from __future__ import annotations

import argparse
import hashlib
import json
import os
from pathlib import Path
import re
import subprocess
import sys

import capstone
import pefile
import linked_pe
from workflow_manifest import load_manifest

ROOT = Path(__file__).resolve().parents[1]
SYMBOL = "?update_cpu_action_policy@AyaCpuActionPolicyView@th105@@QAEXXZ"
DEPENDENCIES = ("cross-v106a-mt19937-next", "cross-v106a-outcome-random", "gpt-web-angle-atan2-natural")
CONSTANTS = {15: {"860.0"}, 16: {"960.0"}, 17: {"v16", "960.0"}}
FLOAT_VALUES = {19: {"*(float *)CPU_FIELD(236)"}, 68: {"*(float *)CPU_FIELD(236)"},
                95: {"v118"}, 96: {"v118"}, 97: {"v96"}, 99: {"v117"}, 100: {"v117"}}


def prepare_source(source, mode):
    if mode not in ("preserve", "constants", "fields", "all"):
        raise ValueError("unknown alias-type control")
    aliases = ({} if mode == "preserve" else CONSTANTS if mode == "constants"
               else FLOAT_VALUES if mode == "fields" else CONSTANTS | FLOAT_VALUES)
    # These aliases contain only exact constants or already-float values. Do
    # not silently extend this probe to an arithmetic/unknown-width temporary.
    for number, allowed in aliases.items():
        assignments = set(re.findall(rf"^v{number} = (.+);", source, re.MULTILINE))
        declaration = f"double v{number};"
        mutation = any(re.search(pattern, source) for pattern in (
            rf"\bv{number}\s*(?:\+\+|--|(?:<<|>>|[+*/%&|^\-])=)",
            rf"(?:\+\+|--)\s*v{number}\b", rf"(?<!&)&(?!&)\s*v{number}\b"))
        if mutation or not assignments or not assignments <= allowed or source.count(declaration) != 1:
            raise ValueError(f"unreviewed value provenance for v{number}")
        source = source.replace(declaration, f"float v{number};")
    return (source.replace('#include "CpuActionPolicies.hpp"', '#include "characters/CpuActionPolicies.hpp"')
            .replace('#include "../battle/Collision.hpp"', '#include "battle/Collision.hpp"')
            .replace('#include "../battle/SpellRuntime.hpp"', '#include "battle/SpellRuntime.hpp"'))


def run(command, environment, log):
    with log.open("w") as stream:
        result = subprocess.run(command, cwd=ROOT, env=environment, stdout=stream, stderr=subprocess.STDOUT)
    output = log.read_text(errors="replace")
    if result.returncode or re.search(r"\b(?:warning LNK|error LNK|fatal error)\b", output):
        raise ValueError(f"probe phase failed: {log}\n{output[-4000:]}")


def probe(mode):
    canonical = linked_pe.comparator()
    target_hash = canonical.verify_target()
    body_hash = hashlib.sha256(canonical.target_bytes(0x6126E0, 16032)).hexdigest()
    if body_hash != "7efa001552238230ac86c77f48f36a217cc486e847f85cb924527c64e2dc6e09":
        raise ValueError("Aya CPU target boundary/hash differs")
    tools, pins = linked_pe.pinned_tools()
    output = ROOT / "build/aya-cpu-ltcg-probes" / mode
    output.mkdir(parents=True, exist_ok=True)
    environment = os.environ.copy()
    environment.update(WINEPREFIX=str(ROOT / ".tools/wine-msvc8"), WINEARCH="win32", WINEDEBUG="-all")
    for variable in ("CL", "_CL_", "LINK", "_LINK_", "INCLUDE", "LIB", "LIBPATH"):
        environment[variable] = ""
    units = load_manifest()["units"]
    objects, receipts = [], {}
    # Rebuild only the three real dependency units, with their own accepted
    # profiles (including the angle helper's strict FP profile).
    for name in DEPENDENCIES:
        log = output / (name + ".build.json")
        run([sys.executable, "scripts/build.py", "--unit", name, "--compare", "--json"], environment, log)
        receipt = json.loads(log.read_text())
        obj = ROOT / units[name]["object"]
        if receipt["build"]["object_sha256"] != linked_pe.sha(obj):
            raise ValueError("dependency object/receipt differs")
        objects.append(obj)
        receipts[name] = receipt
    original = ROOT / units["gpt-web-aya-cpu-action-policy"]["source"]
    generated = output / "AyaCpu.cpp"
    generated.write_bytes(prepare_source(original.read_text(), mode).replace("\n", "\r\n").encode())

    def win(path):
        return "Z:" + str(path).replace("/", "\\")

    obj, image, map_path = output / "AyaCpu.ltcg.obj", output / "AyaCpu.dll", output / "AyaCpu.map"
    compile_command = ["wine", str(tools / "bin/cl.exe"), "/nologo", "/c", "/O2", "/GL",
                       "/GS-", "/GR", "/EHsc", "/MT"]
    compile_command.extend("/I" + win(path) for path in
                           (ROOT / "src", tools / "include", tools / "PlatformSDK/Include"))
    compile_command.extend(("/Fo" + win(obj), win(generated)))
    libraries = [tools / "lib" / name for name in ("libcmt.lib", "libcpmt.lib", "oldnames.lib")]
    libraries.extend(tools / "PlatformSDK/Lib" / name for name in ("Kernel32.Lib", "User32.Lib", "AdvAPI32.Lib"))
    if any(not path.is_file() for path in libraries):
        raise ValueError("the real VC8 CRT/SDK link input is missing")
    # Use the actual static-CRT DLL startup. /NOENTRY pulls an incompatible
    # main-startup member for this closure; supplying a fake main is forbidden.
    link_command = ["wine", str(tools / "bin/link.exe"), "/nologo", "/DLL", "/LTCG", "/NODEFAULTLIB",
                    "/OPT:REF", "/OPT:NOICF", "/INCREMENTAL:NO", "/BASE:0x10000000",
                    "/EXPORT:" + SYMBOL, "/MAP:" + win(map_path), "/OUT:" + win(image)]
    link_command.extend(win(path) for path in (obj, *objects, *libraries))
    run(compile_command, environment, output / "compile.log")
    run(link_command, environment, output / "link.log")
    pe = pefile.PE(str(image))
    exported, = (entry for entry in pe.DIRECTORY_ENTRY_EXPORT.symbols if entry.name == SYMBOL.encode())
    code = pe.get_memory_mapped_image()[exported.address:exported.address + 64]
    address = pe.OPTIONAL_HEADER.ImageBase + exported.address
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    prologue = list(decoder.disasm(code, address))[:12]
    result = {"schema": "th105-aya-cpu-closed-ltcg-probe-v1", "evidence": "genuine source/dependency link; no exact credit",
              "mode": mode, "target_sha256": target_hash, "target_body_sha256": body_hash,
              "source_sha256": linked_pe.sha(original), "generated_source_sha256": linked_pe.sha(generated),
              "image_sha256": linked_pe.sha(image), "map_sha256": linked_pe.sha(map_path),
              "tool_pins": pins, "dependency_receipts": receipts,
              "libraries": {str(path.relative_to(tools)): linked_pe.sha(path) for path in libraries},
              "compile_command": compile_command, "link_command": link_command,
              "root_address": f"0x{address:08X}", "root_prologue": [f"{i.mnemonic} {i.op_str}" for i in prologue],
              "prologue_matches_target": code[:16] == canonical.target_bytes(0x6126E0, 16),
              "canonical_whole_comparison_performed": False,
              "scope": "exported ECX root with original source or explicit alias-type controls; actual checked VC8 deque, engine COFF dependencies and CRT startup; linked image is not executed or a matching claim"}
    (output / "receipt.json").write_text(json.dumps(result, indent=2) + "\n")
    return result


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--float-aliases", choices=("preserve", "constants", "fields", "all"), default="preserve")
    args = parser.parse_args()
    try:
        print(json.dumps(probe(args.float_aliases), indent=2))
    except Exception as error:
        parser.exit(2, f"Aya CPU LTCG probe failed: {error}\n")
