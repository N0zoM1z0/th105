"""Pinned VC8 LTCG images with symbol-backed, fail-closed function comparison.

Images bind only existing game data/IAT cells. CRT code references are resolved
by the actual VC8 import libraries, never synthetic function implementations.
The result is a comparison artifact, not a standalone application.
"""
from __future__ import annotations

import csv
import hashlib
import importlib.util
import json
import os
from pathlib import Path
import re
import struct
import subprocess
import tomllib
from functools import lru_cache

import capstone
import pefile

ROOT = Path(__file__).resolve().parents[1]
PROFILE = "vc8-sp1-ltcg-o2"
IMAGE_BASE = 0x10000000
RUNTIME_DLLS = {"msvcr80.dll", "msvcp80.dll"}
SYMBOL = re.compile(r"^[A-Za-z_?@.$][A-Za-z0-9_?@.$]*$")
MAP_FUNCTION = re.compile(r"^\s+[0-9A-Fa-f]{4}:[0-9A-Fa-f]{8}\s+(\S+)\s+([0-9A-Fa-f]{8})\s+f(?:\s|$)(.*)$")
PIN_FILES = ("bin/cl.exe", "bin/c1xx.dll", "bin/c2.dll", "bin/link.exe", "lib/msvcrt.lib", "lib/msvcprt.lib")
PIN_DIRS = ("include", "PlatformSDK/Include")


def parser_versions() -> dict[str, str]:
    versions = {"capstone": capstone.__version__, "pefile": pefile.__version__}
    # Public CI uses4.0.2; the development image uses5.0.6. Both decoders are
    # exercised by the contract tests. A build/compare must use the same one.
    if versions["capstone"] not in {"4.0.2", "5.0.6"} or versions["pefile"] != "2024.8.26":
        raise ValueError("linked comparison needs the pinned requirements-ci.txt parsers")
    return versions


def sha(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def tree_sha(path: Path) -> str:
    digest = hashlib.sha256()
    for entry in sorted(p for p in path.rglob("*") if p.is_file()):
        digest.update(str(entry.relative_to(path)).encode("utf-8") + b"\0")
        digest.update(bytes.fromhex(sha(entry)))
    return digest.hexdigest()


@lru_cache(maxsize=1)
def comparator():
    spec = importlib.util.spec_from_file_location("linked_canonical", ROOT / "scripts/compare-function.py")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def validate_contract(unit: dict, data_keys: set[str]) -> None:
    if unit.get("profile") != PROFILE or not str(unit.get("object", "")).endswith(".dll"):
        raise ValueError("linked_candidate requires its LTCG profile and a .dll output")
    mappings = unit.get("link_data_targets")
    if not isinstance(mappings, list) or not mappings:
        raise ValueError("linked_candidate needs explicit link_data_targets")
    names = set()
    for mapping in mappings:
        name, separator, key = str(mapping).partition("=")
        if not separator or not SYMBOL.fullmatch(name) or key not in data_keys or name in names:
            raise ValueError("invalid/duplicate linked data binding: " + str(mapping))
        names.add(name)
    exports = set()
    functions = unit.get("functions")
    if not isinstance(functions, list) or not functions:
        raise ValueError("linked unit needs function contracts")
    for function in functions:
        if not isinstance(function, dict):
            raise ValueError("invalid linked function contract")
        export = function.get("export_name", function.get("symbol_base", ""))
        if not isinstance(export, str) or not SYMBOL.fullmatch(export) or export in exports:
            raise ValueError("invalid/duplicate linked export: " + str(export))
        symbol = function.get("symbol_base")
        if not isinstance(symbol, str) or not SYMBOL.fullmatch(symbol):
            raise ValueError("linked function needs its exact map symbol")
        if function.get("contiguous_span") or function.get("dir32_targets"):
            raise ValueError("linked profile does not support remote spans or DIR32 overrides")
        exports.add(export)


def pinned_tools() -> tuple[Path, dict[str, str]]:
    base = Path(os.environ.get("TH105_MSVC8_ROOT", ROOT / ".tools/msvc80-sp1")).resolve()
    pins = tomllib.loads((ROOT / "config/tools.lock.toml").read_text())["msvc8_sp1_ltcg"]
    actual = {name: sha(base / name) for name in PIN_FILES}
    actual.update({name: tree_sha(base / name) for name in PIN_DIRS})
    if actual != pins:
        raise ValueError("LTCG compiler/linker/import-library hashes differ from pinned tools")
    return base, actual


def target_bindings(unit: dict) -> list[dict]:
    c = comparator()
    c.verify_target()
    target = pefile.PE(str(c.TARGET))
    known = c.known_data_targets()
    imports = {}
    for dll in target.DIRECTORY_ENTRY_IMPORT:
        for entry in dll.imports:
            if entry.name:
                imports.setdefault(entry.name.decode("ascii"), []).append(entry.address)
    bindings = []
    for mapping in unit["link_data_targets"]:
        symbol, _, key = mapping.partition("=")
        base, raw, addends, validation = known[key]
        for addend in addends:
            if c.target_bytes(base + addend, len(raw)) != raw:
                raise ValueError(f"linked data bytes differ: {key}+{addend:#x}")
            section = target.get_section_by_rva(base + addend - target.OPTIONAL_HEADER.ImageBase)
            if section is None or section.Characteristics & 0x20000000:
                raise ValueError("absolute link bindings must be data, never code: " + symbol)
        if symbol.startswith("__imp__"):
            plain = symbol[len("__imp__"):].split("@", 1)[0]
            if imports.get(plain) != [base] or addends != frozenset({0}) or validation != "literal" or len(raw) != 4:
                raise ValueError("linked IAT name/slot/bytes are not attested: " + symbol)
        bindings.append({"symbol": symbol, "key": key, "address": base,
                         "data_hex": raw.hex(), "addends": sorted(addends), "validation": validation})
    return bindings


def absolute_data_object(bindings: list[dict]) -> bytes:
    """COFF symbol table only: zero sections and no copied code/data/stubs."""
    strings = bytearray(struct.pack("<I", 4))
    records = bytearray()
    for binding in bindings:
        symbol = binding["symbol"]
        if not SYMBOL.fullmatch(symbol):
            raise ValueError("invalid absolute data symbol")
        offset = len(strings)
        strings.extend(symbol.encode("ascii") + b"\0")
        records.extend(struct.pack("<IIIhHBB", 0, offset, binding["address"], -1, 0, 2, 0))
    struct.pack_into("<I", strings, 0, len(strings))
    return struct.pack("<HHIIIHH", 0x14C, 0, 0, 20, len(bindings), 0, 0) + records + strings


def build_linked(name: str, unit: dict) -> dict:
    from workflow_manifest import repository_path, unit_input_digest
    tools, hashes = pinned_tools()
    parsers = parser_versions()
    bindings = target_bindings(unit)
    source = repository_path(unit["source"])
    output = repository_path(unit["object"], output=True)
    output.parent.mkdir(parents=True, exist_ok=True)
    obj = output.with_suffix(".ltcg.obj")
    data_obj = output.with_suffix(".bindings.obj")
    map_path = output.with_suffix(".map")
    data_obj.write_bytes(absolute_data_object(bindings))
    environment = os.environ.copy()
    environment.update(WINEPREFIX=environment.get("TH105_WINEPREFIX", str(ROOT / ".tools/wine-msvc8")), WINEARCH="win32", WINEDEBUG="-all")
    # A unit's explicit command/header/library inputs define this profile.
    for variable in ("CL", "_CL_", "LINK", "_LINK_", "INCLUDE", "LIB", "LIBPATH"):
        environment[variable] = ""

    def win(path: Path) -> str:
        return subprocess.run(["winepath", "-w", str(path)], cwd=ROOT, env=environment,
                              check=True, capture_output=True, text=True).stdout.strip()

    compile_command = ["wine", str(tools / "bin/cl.exe"), "/nologo", "/c", "/O2", "/GL",
                       "/GS" if unit["enable_gs"] else "/GS-", "/GR", "/EHsc", "/MT"]
    for directory in [ROOT / "src", tools / "include", tools / "PlatformSDK/Include"] + [repository_path(p) for p in unit.get("include_dirs", [])]:
        compile_command.append("/I" + win(directory))
    compile_command.extend(["/Fo" + win(obj), win(source)])
    link_command = ["wine", str(tools / "bin/link.exe"), "/nologo", "/DLL", "/NOENTRY", "/LTCG",
                    "/NODEFAULTLIB", "/OPT:NOICF", f"/BASE:0x{IMAGE_BASE:X}",
                    "/MAP:" + win(map_path), "/OUT:" + win(output)]
    link_command.extend("/EXPORT:" + f.get("export_name", f["symbol_base"]) for f in unit["functions"])
    link_command.extend(win(p) for p in [obj, data_obj, tools / "lib/msvcrt.lib", tools / "lib/msvcprt.lib"])
    # Each invocation is serial. /FORCE and unresolved references are forbidden.
    for phase, command in [("compile", compile_command), ("link", link_command)]:
        log = output.with_suffix("." + phase + ".log")
        with log.open("w") as stream:
            completed = subprocess.run(command, cwd=ROOT, env=environment, stdout=stream, stderr=subprocess.STDOUT)
        if completed.returncode or re.search(r"\b(?:fatal error|error LNK|warning LNK)\b", log.read_text(errors="replace"), re.I):
            raise RuntimeError(f"LTCG {phase} failed; {log}:\n" + log.read_text(errors="replace")[-4000:])
    input_digest, inputs = unit_input_digest(name, unit)
    metadata = {"schema": "th105-linked-pe-v1", "unit": name, "profile": PROFILE,
                "target_sha256": comparator().verify_target(), "input_digest": input_digest, "inputs": inputs,
                "image_sha256": sha(output), "map_sha256": sha(map_path), "source_sha256": sha(source),
                "ltcg_object_sha256": sha(obj), "bindings_object_sha256": sha(data_obj),
                "tools": hashes, "parsers": parsers, "bindings": bindings, "compile_command": compile_command,
                "link_command": link_command}
    output.with_suffix(".link.json").write_text(json.dumps(metadata, indent=2) + "\n")
    return metadata


def parse_map(text: str) -> dict[int, list[tuple[str, str]]]:
    functions = {}
    for line in text.splitlines():
        match = MAP_FUNCTION.match(line)
        if match:
            functions.setdefault(int(match[2], 16), []).append((match[1], match[3].strip()))
    if not functions:
        raise ValueError("linker map has no function symbols")
    return functions


def is_branch(instruction) -> bool:
    # LOOP has only BRANCH_RELATIVE (not JUMP) in supported Capstone releases.
    return instruction.group(capstone.CS_GRP_JUMP) or instruction.mnemonic in {
        "loop", "loope", "loopne", "jcxz", "jecxz",
    }


def decode_closed_body(code: bytes, start: int) -> list:
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    decoder.detail = True
    instructions = list(decoder.disasm(code, start))
    if not instructions or sum(i.size for i in instructions) != len(code) or instructions[-1].mnemonic != "ret":
        raise ValueError("linked body does not close through a complete RET boundary")
    by_address = {i.address: i for i in instructions}
    pending, reached = [start], set()
    while pending:
        address = pending.pop()
        if address in reached:
            continue
        if address not in by_address:
            raise ValueError("linked CFG escapes or branches inside an instruction")
        instruction = by_address[address]
        reached.add(address)
        if instruction.group(capstone.CS_GRP_RET):
            continue
        if instruction.group(capstone.x86.X86_GRP_BRANCH_RELATIVE) and not (is_branch(instruction) or instruction.group(capstone.CS_GRP_CALL)):
            raise ValueError("unsupported linked relative control-flow instruction")
        if is_branch(instruction):
            if len(instruction.operands) != 1 or instruction.operands[0].type != capstone.x86.X86_OP_IMM:
                raise ValueError("linked indirect jumps are unsupported")
            pending.append(instruction.operands[0].imm)
            if instruction.id == capstone.x86.X86_INS_JMP:
                continue
        if instruction.group(capstone.CS_GRP_INT) or instruction.mnemonic in {"int3", "hlt", "ud2"}:
            raise ValueError("linked trap/noreturn boundaries are unsupported")
        pending.append(address + instruction.size)
    if len(reached) != len(instructions):
        raise ValueError("linked body has unaccounted unreachable bytes")
    return instructions


def canonicalize(code: bytes, start: int, target: int, bindings: list[dict], resolve_call,
                 image_range: tuple[int, int], game_range: tuple[int, int]) -> tuple[bytes, list, list]:
    instructions = decode_closed_body(code, start)
    permitted = {}
    widths = {}
    for binding in bindings:
        for addend in binding["addends"]:
            permitted.setdefault(binding["address"] + addend, []).append((binding["key"], addend))
            widths[binding["address"] + addend] = max(widths.get(binding["address"] + addend, 0), len(bytes.fromhex(binding["data_hex"])))
    replayed, references = [], []
    canonical = bytearray(code)
    for instruction in instructions:
        offset = instruction.address - start
        control_immediate = False
        if instruction.group(capstone.CS_GRP_CALL) and instruction.operands[0].type == capstone.x86.X86_OP_IMM:
            if instruction.size != 5 or instruction.bytes[0] != 0xE8:
                raise ValueError("linked external call must be ordinary E8 REL32")
            name, destination = resolve_call(instruction.operands[0].imm)
            displacement = destination - (target + offset + 5)
            if not -(2**31) <= displacement < 2**31:
                raise ValueError("linked REL32 displacement overflows")
            struct.pack_into("<i", canonical, offset + 1, displacement)
            replayed.append({"offset": offset + 1, "symbol": name, "target": destination})
            control_immediate = True
        if is_branch(instruction):
            control_immediate = True  # Internal CFG edges are preserved byte-for-byte.
        for operand in instruction.operands:
            value = None
            if operand.type == capstone.x86.X86_OP_MEM and operand.mem.base == 0 and operand.mem.index == 0:
                if operand.mem.segment in {capstone.x86.X86_REG_FS, capstone.x86.X86_REG_GS}:
                    continue
                value = operand.mem.disp & 0xffffffff
                if value not in permitted:
                    raise ValueError(f"unattested linked absolute memory reference {value:#x}")
                if operand.size > widths[value]:
                    raise ValueError("linked absolute read/write exceeds its attested bytes")
            elif operand.type == capstone.x86.X86_OP_IMM and not control_immediate:
                value = operand.imm & 0xffffffff
                if image_range[0] <= value < image_range[1]:
                    raise ValueError("unresolved internal linked address/literal")
                if game_range[0] <= value < game_range[1] and value not in permitted:
                    raise ValueError(f"unattested linked game address {value:#x}")
            if value in permitted:
                references.append({"offset": offset, "address": value, "bindings": permitted[value]})
    return bytes(canonical), replayed, references


def resolve_linked_call(destination: int, pe, functions: dict, imports: dict, targets: dict) -> tuple[str, int]:
    if not IMAGE_BASE <= destination < IMAGE_BASE + pe.OPTIONAL_HEADER.SizeOfImage:
        raise ValueError("linked call escapes its image without a named linker identity")
    thunk = pe.get_data(destination - IMAGE_BASE, 6) if IMAGE_BASE <= destination < IMAGE_BASE + pe.OPTIONAL_HEADER.SizeOfImage else b""
    if thunk[:2] == b"\xff\x25" and len(thunk) == 6:
        dll, imported = imports.get(struct.unpack_from("<I", thunk, 2)[0], (None, None))
        if dll not in RUNTIME_DLLS or not imported:
            raise ValueError("external linked call is not a named pinned VC8 runtime import")
        symbol = imported if imported.startswith("?") else "_" + imported
        if symbol not in targets:
            raise ValueError("unmapped linked runtime call: " + symbol)
        return symbol, targets[symbol]
    mapped = {(symbol, targets[symbol]) for symbol, _ in functions.get(destination, []) if symbol in targets}
    if len({address for _, address in mapped}) != 1:
        raise ValueError(f"unmapped/ambiguous linked function call {destination:#x}")
    return sorted(mapped)[0]


def compare_linked(name: str, unit: dict, addresses: set[str], image: Path | None = None) -> list[dict]:
    from workflow_manifest import repository_path, unit_input_digest
    c = comparator()
    target_hash = c.verify_target()
    image = image or repository_path(unit["object"], output=True)
    metadata = json.loads(image.with_suffix(".link.json").read_text())
    _, tools = pinned_tools()
    bindings = target_bindings(unit)
    expected = {"schema": "th105-linked-pe-v1", "unit": name, "profile": PROFILE,
                "target_sha256": target_hash, "input_digest": unit_input_digest(name, unit)[0],
                "source_sha256": sha(repository_path(unit["source"])), "image_sha256": sha(image),
                "map_sha256": sha(image.with_suffix(".map")), "tools": tools, "parsers": parser_versions(), "bindings": bindings,
                "ltcg_object_sha256": sha(image.with_suffix(".ltcg.obj")),
                "bindings_object_sha256": sha(image.with_suffix(".bindings.obj"))}
    if any(metadata.get(key) != value for key, value in expected.items()):
        raise ValueError("stale or modified linked build provenance; rebuild the configured unit")
    pe = pefile.PE(str(image))
    if (pe.FILE_HEADER.Machine != 0x14c or pe.OPTIONAL_HEADER.Magic != 0x10b
            or pe.OPTIONAL_HEADER.ImageBase != IMAGE_BASE
            or not pe.FILE_HEADER.Characteristics & 0x2000 or pe.OPTIONAL_HEADER.AddressOfEntryPoint != 0):
        raise ValueError("linked artifact is not the pinned x86 PE32 image")
    functions = parse_map(image.with_suffix(".map").read_text(errors="strict"))
    exports = {}
    if not hasattr(pe, "DIRECTORY_ENTRY_EXPORT"):
        raise ValueError("linked image has no export directory")
    for entry in pe.DIRECTORY_ENTRY_EXPORT.symbols:
        if entry.name:
            if entry.forwarder or entry.name.decode("ascii") in exports:
                raise ValueError("forwarded/duplicate linked exports are unsupported")
            exports[entry.name.decode("ascii")] = IMAGE_BASE + entry.address
    imports = {entry.address: (dll.dll.decode("ascii").lower(), entry.name.decode("ascii") if entry.name else None)
               for dll in getattr(pe, "DIRECTORY_ENTRY_IMPORT", []) for entry in dll.imports}
    with (ROOT / "config/functions.csv").open(newline="") as stream:
        ledger = {row["address"]: row for row in csv.DictReader(stream)}
    game = pefile.PE(str(c.TARGET), fast_load=True)
    game_range = (game.OPTIONAL_HEADER.ImageBase, game.OPTIONAL_HEADER.ImageBase + game.OPTIONAL_HEADER.SizeOfImage)
    reports = []
    for function in unit["functions"]:
        if addresses and function["address"] not in addresses:
            continue
        export = function.get("export_name", function["symbol_base"])
        if export not in exports:
            raise ValueError("linked export missing: " + export)
        start = exports[export]
        owner = [owner for symbol, owner in functions.get(start, []) if symbol == function["symbol_base"]]
        if len(owner) != 1 or image.with_suffix(".ltcg.obj").name not in owner[0]:
            raise ValueError("linked export is not owned by the configured source CIL object")
        section = pe.get_section_by_rva(start - IMAGE_BASE)
        if section is None or not section.Characteristics & 0x20000000 or section.Name.rstrip(b"\0") != b".text":
            raise ValueError("linked export is outside executable .text")
        section_end = IMAGE_BASE + section.VirtualAddress + section.Misc_VirtualSize
        end = min([address for address in functions if start < address < section_end] + [section_end])
        raw = pe.get_data(start - IMAGE_BASE, end - start)
        if len(raw) != end - start:
            raise ValueError("linked section is truncated")
        raw = raw.rstrip(b"\xcc")  # Only linker INT3 padding outside a closed RET is removed.
        for block in getattr(pe, "DIRECTORY_ENTRY_BASERELOC", []):
            for relocation in block.entries:
                if relocation.type and max(start, IMAGE_BASE + relocation.rva) < min(start + len(raw), IMAGE_BASE + relocation.rva + 4):
                    raise ValueError("linked internal base relocations need an explicit supported contract")
        targets = dict(mapping.split("=", 1) for mapping in function.get("rel32_targets", []))
        targets = {symbol: int(address, 0) for symbol, address in targets.items()}
        if any(f"0x{destination:08X}" not in ledger for destination in targets.values()):
            raise ValueError("linked callee mapping is outside the target candidate ledger")

        def resolve(destination: int) -> tuple[str, int]:
            return resolve_linked_call(destination, pe, functions, imports, targets)

        address = int(function["address"], 0)
        code, calls, data_refs = canonicalize(raw, start, address, bindings, resolve,
            (IMAGE_BASE, IMAGE_BASE + pe.OPTIONAL_HEADER.SizeOfImage), game_range)
        size = int(ledger[function["address"]]["size"], 0)
        target = c.target_bytes(address, size)
        mismatch = c.first_mismatch(target, code, address)
        reports.append({"schema_version": 1, "result": "mismatch" if mismatch else "exact",
            "address": function["address"], "object": str(image), "symbol_base": function["symbol_base"],
            "comparison": {"boundary": "linked_symbol_and_cfg", "size": size},
            "target_size": size, "object_section_tail_size": len(code), "object_size_kind": "linked_symbol_body",
            "linked_function_va": f"0x{start:08X}", "first_mismatch": mismatch, "failure": None,
            "target_executable_sha256": target_hash, "target_sha256": hashlib.sha256(target).hexdigest(),
            "object_compared_sha256": hashlib.sha256(code).hexdigest(), "replayed_rel32": calls,
            "validated_data_references": data_refs})
    return reports
