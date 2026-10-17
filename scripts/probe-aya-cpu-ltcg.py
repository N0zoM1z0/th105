#!/usr/bin/env python3
"""Build an Aya CPU LTCG probe with real engine objects and static VC8 CRT.

This is a provenance experiment, not a canonical acceptance command. Generated
source/images stay under build/. No executable address bindings, fake callers,
stub helpers or unresolved-link overrides are supplied.
"""
from __future__ import annotations

import argparse
import hashlib
import importlib.util
import json
import os
from pathlib import Path
import re
import struct
import subprocess
import sys
import tomllib

import capstone
import pefile
import linked_pe
from giant_owner_audit import decode, reachable_boundary_audit
from workflow_manifest import load_manifest

ROOT = Path(__file__).resolve().parents[1]
SYMBOL = "?update_cpu_action_policy@AyaCpuActionPolicyView@th105@@QAEXXZ"
DEPENDENCIES = ("cross-v106a-mt19937-next", "cross-v106a-outcome-random", "gpt-web-angle-atan2-natural")
DEQUE_SYMBOL = "??A?$deque@UFighterSequenceSlot@th105@@V?$allocator@UFighterSequenceSlot@th105@@@std@@@std@@QAEAAUFighterSequenceSlot@th105@@I@Z"
DEQUE_INSTANCE = "template th105::FighterSequenceSlot & std::deque<th105::FighterSequenceSlot>::operator[](unsigned int);"
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


def checked_switch_indices(indices, destinations):
    """Reject incomplete destination sets instead of silently closing a CFG."""
    if not indices or not destinations or max(indices) >= len(destinations):
        raise ValueError("switch index escapes its relocated destination table")


def canonical_deque(code, start, functions, canonical):
    def resolve(address):
        names = [name for name, _ in functions.get(address, [])]
        if names != ["__invalid_parameter_noinfo"]:
            raise ValueError("unchecked deque runtime call identity")
        return names[0], 0x68A143

    replayed, calls, _ = linked_pe.canonicalize(
        code, start, 0x4399C0, [], resolve,
        (0x10000000, 0x20000000), (0x400000, 0x706000))
    return {"callable_bytes": len(code), "canonical_sha256": hashlib.sha256(replayed).hexdigest(),
            "target_standard_abi_exact": replayed == canonical.target_bytes(0x4399C0, 94),
            "replayed_calls": calls}


def normalize_map_aliases(functions, aliases):
    """Collapse only linker aliases backed by the same address and object."""
    result = {}
    for address, names in functions.items():
        normalized = set()
        for name, owner in names:
            actual = aliases.get(name, name)
            if actual != name and (actual, owner) not in names:
                raise ValueError("map alias has no same-address/object definition")
            normalized.add((actual, owner))
        result[address] = sorted(normalized)
    return result


def qualified_jump_alignment(code, start, instructions, first, last):
    """Recognize the observed short-JMP/three-byte-LEA/16-byte-header pattern."""
    previous = next((row for row in instructions if row.address + row.size == first), None)
    return (last % 16 == 0 and code[first - start:last - start] == b"\x8d\x49\x00"
            and previous is not None and bytes(previous.bytes) == b"\xeb\x03"
            and previous.operands[0].type == capstone.x86.X86_OP_IMM
            and previous.operands[0].imm == last)


def inspect_linked_root(image, map_path, canonical, *, symbol=SYMBOL,
                        root_name="aya-cpu-action-policy", switch_count=6, aliases=None,
                        allow_loop_alignment=False):
    """Inspect every reachable instruction, with bounds-checked switch indices.

    Map names alone never authorize remapping a privately specialized callee.
    This report does not canonicalize the root or award partial credit.
    """
    pe = pefile.PE(str(image))
    base = pe.OPTIONAL_HEADER.ImageBase
    if base != 0x10000000 or pe.FILE_HEADER.Machine != 0x14C:
        raise ValueError("unexpected probe PE architecture/base")
    functions = linked_pe.parse_map(map_path.read_text())
    functions = normalize_map_aliases(functions, aliases or {})
    exported, = (entry for entry in pe.DIRECTORY_ENTRY_EXPORT.symbols if entry.name == symbol.encode())
    start = base + exported.address
    end = min(address for address in functions if address > start)
    if not any(name == symbol for name, _ in functions.get(start, [])):
        raise ValueError("root export/map disagrees")

    class Envelope:
        path = image
        text = pe.get_data(start - base, end - start)
        relocations = {entry.rva + base - start: None
                       for block in pe.DIRECTORY_ENTRY_BASERELOC for entry in block.entries
                       if entry.type == 3 and start <= base + entry.rva < end}

        def relocated_text_value(self, offset):
            return struct.unpack_from("<I", self.text, offset)[0] - start

    obj = Envelope()
    if len(obj.text) != end - start:
        raise ValueError("truncated linked root envelope")
    spec = importlib.util.spec_from_file_location("aya_link_switch_map", ROOT / "scripts/compare-giant-action-switches.py")
    mapper = importlib.util.module_from_spec(spec)
    sys.modules[spec.name] = mapper
    spec.loader.exec_module(mapper)
    root = next(item for item in tomllib.loads((ROOT / "config/giant-action-switches.toml").read_text())["roots"]
                if item["name"] == root_name)
    candidate = mapper.build_candidate_map(obj, root)
    metadata = candidate["metadata_start"]
    code = obj.text[:metadata]
    instructions = decode(code, start)
    switches, facts = {}, []
    for number, instruction in enumerate(instructions):
        if instruction.mnemonic != "jmp" or instruction.operands[0].type != capstone.x86.X86_OP_MEM:
            continue
        operand = instruction.operands[0]
        if operand.mem.base or not operand.mem.index or operand.mem.scale != 4:
            raise ValueError("unsupported linked indirect jump")
        table = operand.mem.disp & 0xFFFFFFFF
        offset = table - start
        if (instruction.address - start + instruction.disp_offset not in obj.relocations
                or not metadata <= offset < len(obj.text)):
            raise ValueError("switch table outside root metadata")
        destinations = []
        while offset + 4 * len(destinations) in obj.relocations:
            destination = obj.relocated_text_value(offset + 4 * len(destinations))
            if not 0 <= destination < metadata:
                raise ValueError("switch destination outside root code")
            destinations.append(start + destination)
        # Current six dispatches use MOVZX byte indices after a CMP/JA bound.
        # Refuse another lowering instead of guessing a table extent.
        load_number = next((j for j in range(number - 1, max(-1, number - 4), -1)
                            if instructions[j].mnemonic == "movzx"
                            and instructions[j].operands[0].reg == operand.mem.index), None)
        if load_number is None:
            raise ValueError("unproved switch byte-index load")
        load = instructions[load_number]
        memory = load.operands[1]
        if (memory.type != capstone.x86.X86_OP_MEM or memory.size != 1
                or memory.mem.index or not memory.mem.base
                or load.address - start + load.disp_offset not in obj.relocations):
            raise ValueError("unsupported switch index addressing")
        bound = next((j for j in range(load_number - 1, max(-1, load_number - 10), -1)
                      if instructions[j].mnemonic == "cmp"
                      and instructions[j].operands[0].type == capstone.x86.X86_OP_REG
                      and instructions[j].operands[0].reg == memory.mem.base
                      and instructions[j].operands[1].type == capstone.x86.X86_OP_IMM), None)
        between = instructions[bound + 1:load_number] if bound is not None else []
        guards = [i for i in between if i.mnemonic == "ja"]
        if bound is None or len(guards) != 1:
            raise ValueError("unproved switch unsigned index bound")
        for item in between:
            written = item.regs_access()[1]
            if (memory.mem.base in written or capstone.x86.X86_REG_EFLAGS in written
                    or item.group(capstone.CS_GRP_CALL) or item.group(capstone.CS_GRP_RET)
                    or (item.group(capstone.CS_GRP_JUMP) and item is not guards[0])):
                raise ValueError("switch bound/index changed before table access")
        if any(operand.mem.index in item.regs_access()[1] or item.group(capstone.CS_GRP_JUMP)
               or item.group(capstone.CS_GRP_CALL) or item.group(capstone.CS_GRP_RET)
               for item in instructions[load_number + 1:number]):
            raise ValueError("switch destination index changed after byte load")
        count = instructions[bound].operands[1].imm + 1
        index_address = memory.mem.disp & 0xFFFFFFFF
        if not 0 < count <= 256 or not start + metadata <= index_address <= end - count:
            raise ValueError("switch indices outside root metadata")
        indices = pe.get_data(index_address - base, count)
        checked_switch_indices(indices, destinations)
        switches[table] = (f"switch-{len(facts)}", destinations)
        facts.append({"dispatch": f"0x{instruction.address:08X}", "table": f"0x{table:08X}",
                      "destination_count": len(destinations), "index_count": count,
                      "indices_sha256": hashlib.sha256(indices).hexdigest()})
    if len(switches) != switch_count:
        raise ValueError("unexpected linked root switch count")
    boundary = reachable_boundary_audit(code, start, switches)
    if boundary["unresolved_indirect_exits"] or boundary["internal_call_targets"]:
        raise ValueError("unclosed linked CPU transfers")
    for first, last in boundary["unreached_ranges"]:
        if allow_loop_alignment and qualified_jump_alignment(code, start, instructions, first, last):
            continue
        # Observed VC8 four-byte table alignment: MOV EDI,EDI or LEA ECX,[ECX].
        # Permit only this trailing gap after RET, never interior dead code.
        gap = code[first - start:last - start]
        previous = next((i for i in instructions if i.address + i.size == first), None)
        if (last != start + len(code) or last % 4 or previous is None or previous.mnemonic != "ret"
                or gap not in (b"\x90", b"\x8b\xff", b"\x8d\x49\x00")):
            raise ValueError("nonpadding unreachable linked CPU instructions")
    call_counts = {}
    for edge in boundary["direct_external_targets"]:
        names = functions.get(edge["address"], [])
        if len(names) != 1 or any(site["kind"] != "call" for site in edge["sites"]):
            raise ValueError("unidentified linked CPU external transfer")
        call_counts[names[0][0]] = len(edge["sites"])
    helper, = (address for address, names in functions.items() if any(name == DEQUE_SYMBOL for name, _ in names))
    helper_code = linked_pe.linked_body(pe, functions, helper)
    return {"root_callable_and_padding_bytes": len(code), "reachable_bytes": boundary["reachable_bytes"],
            "reachable_instructions": boundary["reachable_instructions"], "switches": facts,
            "unreached_padding_bytes": len(code) - boundary["reachable_bytes"], "direct_calls": call_counts,
            "unreached_alignment_ranges": boundary["unreached_ranges"],
            "deque": canonical_deque(helper_code, helper, functions, canonical),
            "scope": "full linked CFG and separate library witness; root is not canonically compared or executed"}


def probe(mode, deque_boundary="visible"):
    if deque_boundary not in ("visible", "coff"):
        raise ValueError("unknown deque source boundary")
    canonical = linked_pe.comparator()
    target_hash = canonical.verify_target()
    body_hash = hashlib.sha256(canonical.target_bytes(0x6126E0, 16032)).hexdigest()
    if body_hash != "7efa001552238230ac86c77f48f36a217cc486e847f85cb924527c64e2dc6e09":
        raise ValueError("Aya CPU target boundary/hash differs")
    tools, pins = linked_pe.pinned_tools()
    output = ROOT / "build/aya-cpu-ltcg-probes" / (mode if deque_boundary == "visible" else mode + "-coff-deque")
    output.mkdir(parents=True, exist_ok=True)
    (output / "receipt.json").unlink(missing_ok=True)
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
    prepared = prepare_source(original.read_text(), mode)
    if deque_boundary == "coff":
        prepared = prepared.replace("namespace th105 {", "extern " + DEQUE_INSTANCE + "\n\nnamespace th105 {", 1)
    generated.write_bytes(prepared.replace("\n", "\r\n").encode())

    def win(path):
        return "Z:" + str(path).replace("/", "\\")

    obj, image, map_path = output / "AyaCpu.ltcg.obj", output / "AyaCpu.dll", output / "AyaCpu.map"
    compile_command = ["wine", str(tools / "bin/cl.exe"), "/nologo", "/c", "/O2", "/GL",
                       "/GS-", "/GR", "/EHsc", "/MT"]
    compile_command.extend("/I" + win(path) for path in
                           (ROOT / "src", tools / "include", tools / "PlatformSDK/Include"))
    compile_command.extend(("/Fo" + win(obj), win(generated)))
    provider = None
    provider_commands = []
    if deque_boundary == "coff":
        provider_source, provider = output / "NativeDeque.cpp", output / "NativeDeque.obj"
        provider_source.write_text('#include "battle/SpellRuntime.hpp"\n#include <deque>\n' + DEQUE_INSTANCE + "\n")
        command = [part for part in compile_command[:-2] if part != "/GL"]
        command.extend(("/Fo" + win(provider), win(provider_source)))
        run(command, environment, output / "deque.compile.log")
        provider_commands.append(command)
        replayed = canonical.coff_symbol_bytes(provider, DEQUE_SYMBOL, 0x4399C0, 94,
                                               {"__invalid_parameter_noinfo": 0x68A143}, canonical.known_data_targets(), {})
        if replayed != canonical.target_bytes(0x4399C0, 94):
            raise ValueError("real SDK COFF deque provider is nonexact")
    libraries = [tools / "lib" / name for name in ("libcmt.lib", "libcpmt.lib", "oldnames.lib")]
    libraries.extend(tools / "PlatformSDK/Lib" / name for name in ("Kernel32.Lib", "User32.Lib", "AdvAPI32.Lib"))
    if any(not path.is_file() for path in libraries):
        raise ValueError("the real VC8 CRT/SDK link input is missing")
    # Use the actual static-CRT DLL startup. /NOENTRY pulls an incompatible
    # main-startup member for this closure; supplying a fake main is forbidden.
    link_command = ["wine", str(tools / "bin/link.exe"), "/nologo", "/DLL", "/LTCG", "/NODEFAULTLIB",
                    "/OPT:REF", "/OPT:NOICF", "/INCREMENTAL:NO", "/BASE:0x10000000",
                    "/EXPORT:" + SYMBOL, "/MAP:" + win(map_path), "/OUT:" + win(image)]
    link_inputs = ([provider] if provider else []) + [obj, *objects, *libraries]
    link_command.extend(win(path) for path in link_inputs)
    run(compile_command, environment, output / "compile.log")
    run(link_command, environment, output / "link.log")
    shape = inspect_linked_root(image, map_path, canonical)
    if deque_boundary == "coff" and not shape["deque"]["target_standard_abi_exact"]:
        raise ValueError("linked deque no longer matches the attested COFF provider")
    pe = pefile.PE(str(image))
    exported, = (entry for entry in pe.DIRECTORY_ENTRY_EXPORT.symbols if entry.name == SYMBOL.encode())
    code = pe.get_memory_mapped_image()[exported.address:exported.address + 64]
    address = pe.OPTIONAL_HEADER.ImageBase + exported.address
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    prologue = list(decoder.disasm(code, address))[:12]
    result = {"schema": "th105-aya-cpu-closed-ltcg-probe-v2", "evidence": "genuine source/dependency link; no authored exact credit",
              "mode": mode, "deque_boundary": deque_boundary, "target_sha256": target_hash, "target_body_sha256": body_hash,
              "source_sha256": linked_pe.sha(original), "generated_source_sha256": linked_pe.sha(generated),
              "image_sha256": linked_pe.sha(image), "map_sha256": linked_pe.sha(map_path),
              "tool_pins": pins, "dependency_receipts": receipts,
              "libraries": {str(path.relative_to(tools)): linked_pe.sha(path) for path in libraries},
              "compile_command": compile_command, "link_command": link_command,
              "provider_compile_commands": provider_commands,
              "provider": ({"source_sha256": linked_pe.sha(provider_source), "object_sha256": linked_pe.sha(provider),
                            "canonical_library_bytes": 94} if provider else None),
              "linked_shape": shape,
              "root_address": f"0x{address:08X}", "root_prologue": [f"{i.mnemonic} {i.op_str}" for i in prologue],
              "prologue_matches_target": code[:16] == canonical.target_bytes(0x6126E0, 16),
              "canonical_whole_comparison_performed": False,
              "scope": "exported ECX root with original source or explicit alias-type controls; actual checked VC8 deque, engine COFF dependencies and CRT startup; library ABI is checked separately and never inferred from its map name; no root matching claim"}
    (output / "receipt.json").write_text(json.dumps(result, indent=2) + "\n")
    return result


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--float-aliases", choices=("preserve", "constants", "fields", "all"), default="preserve")
    parser.add_argument("--deque-boundary", choices=("visible", "coff"), default="visible",
                        help="keep the real template visible to LTCG, or supply its actual exact SDK COFF instantiation")
    args = parser.parse_args()
    try:
        print(json.dumps(probe(args.float_aliases, args.deque_boundary), indent=2))
    except Exception as error:
        parser.exit(2, f"Aya CPU LTCG probe failed: {error}\n")
