"""Pinned VC8 LTCG images with symbol-backed, fail-closed function comparison.

Images bind only existing game data/IAT cells. External code references are resolved
by the actual pinned VC8/SDK import libraries, never synthetic function implementations.
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
import sys
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
MAP_SYMBOL = re.compile(r"^\s+[0-9A-Fa-f]{4}:[0-9A-Fa-f]{8}\s+(\S+)\s+([0-9A-Fa-f]{8})\s+(.*)$")
PIN_FILES = ("bin/cl.exe", "bin/c1xx.dll", "bin/c2.dll", "bin/link.exe", "lib/msvcrt.lib", "lib/msvcprt.lib",
             "PlatformSDK/Lib/WS2_32.Lib")
PIN_DIRS = ("include", "PlatformSDK/Include")
STATIC_LIBS = ("lib/libcmt.lib", "lib/libcpmt.lib", "lib/oldnames.lib", "PlatformSDK/Lib/Kernel32.Lib")
SDK_IMPORTS = {
    "_sendto@24": {"library": "PlatformSDK/Lib/WS2_32.Lib", "dll": "ws2_32.dll", "ordinal": 20,
                   "iat": "__imp__sendto@24",
                   "member_sha256": "677c886dace564fc7dd6ca26b7eec488a4b65d67c46847ba0da1b9396d261168"},
}


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
    from linked_lifecycle import validate_contract as validate_lifecycle
    from linked_noreturn import validate_contract as validate_error_tails
    validate_lifecycle(unit, data_keys)
    if unit.get("profile") != PROFILE or not str(unit.get("object", "")).endswith(".dll"):
        raise ValueError("linked_candidate requires its LTCG profile and a .dll output")
    mappings = unit.get("link_data_targets")
    if not isinstance(mappings, list):
        raise ValueError("linked_candidate needs explicit link_data_targets")
    names = set()
    for mapping in mappings:
        name, separator, key = str(mapping).partition("=")
        if not separator or not SYMBOL.fullmatch(name) or key not in data_keys or name in names:
            raise ValueError("invalid/duplicate linked data binding: " + str(mapping))
        if name.startswith("??_7") or key.startswith("??_7"):
            raise ValueError("native vtables require the typed RTTI/entry contract")
        names.add(name)
    imports = unit.get("link_import_targets", [])
    if not isinstance(imports, list):
        raise ValueError("linked SDK imports must be an explicit list")
    import_names = set()
    for mapping in imports:
        symbol, separator, address = str(mapping).partition("=")
        if (not separator or symbol not in SDK_IMPORTS or symbol in names or symbol in import_names
                or not re.fullmatch(r"0x[0-9A-Fa-f]{8}", address)):
            raise ValueError("invalid/duplicate pinned SDK import mapping")
        import_names.add(symbol)
    coff_sources = unit.get("linked_coff_sources", [])
    if (not isinstance(coff_sources, list)
            or any(not isinstance(p, str) or not p.startswith("src/library/")
                   or not p.endswith(".cpp") or ".." in Path(p).parts for p in coff_sources)
            or len(set(coff_sources)) != len(coff_sources)
            or unit.get("source") in coff_sources):
        raise ValueError("linked COFF inputs must be distinct compiler-library C++ sources")
    if coff_sources:
        from workflow_manifest import repository_path
        if any(not repository_path(path).is_file() for path in coff_sources):
            raise ValueError("linked compiler-library source is missing")
    vtables = unit.get("link_vtables", [])
    if not isinstance(vtables, list):
        raise ValueError("linked vtable contracts must be a list")
    for table in vtables:
        if not isinstance(table, dict) or set(table) != {"symbol", "target", "entry", "target_type_name"}:
            raise ValueError("linked vtable requires exact symbol/target/entry/RTTI fields")
        symbol, key, entry = table["symbol"], table["target"], table["entry"]
        if (not isinstance(symbol, str) or not re.fullmatch(r"\?\?_7[A-Za-z_]\w*(?:@[A-Za-z_]\w*)*@@6B@", symbol)
                or symbol in names or not isinstance(key, str) or key not in data_keys or not isinstance(entry, str)):
            raise ValueError("invalid/duplicate linked single-destructor vtable")
        owner = symbol[4:-5]
        entry_name, separator, address = entry.partition("=")
        if (not separator or entry_name != "??_G" + owner + "@@UAEPAXI@Z"
                or not re.fullmatch(r"0x[0-9A-Fa-f]{8}", address)
                or not isinstance(table["target_type_name"], str)
                or not table["target_type_name"].startswith(".?AV")
                or not table["target_type_name"].endswith("@@")):
            raise ValueError("linked vtable must identify its own scalar deleting destructor and RTTI")
        names.add(symbol)
    exports, symbols = set(), set()
    functions = unit.get("functions")
    if not isinstance(functions, list) or not functions or any(not isinstance(f, dict) for f in functions):
        raise ValueError("linked unit needs function contracts")
    for function in functions:
        validate_error_tails(function)
        if not isinstance(function, dict):
            raise ValueError("invalid linked function contract")
        symbol = function.get("symbol_base")
        if not isinstance(symbol, str) or not SYMBOL.fullmatch(symbol) or symbol in symbols:
            raise ValueError("linked function needs its exact map symbol")
        symbols.add(symbol)
        if (function.get("contiguous_span") or function.get("owned_extent")
                or function.get("dir32_targets")):
            raise ValueError("linked profile does not support remote spans or DIR32 overrides")
        if "vtable_entry" in function:
            tables = [table for table in vtables
                      if table["symbol"] == function["vtable_entry"]
                      and table["entry"] == symbol + "=" + str(function.get("address"))]
            if (len(tables) != 1 or any(key in function
                    for key in ("export_name", "private_from", "private_global"))):
                raise ValueError("linked vtable entry needs its exact destructor contract without an export")
        if "private_global" in function:
            continue  # Validated as a paired, startup-reachable lifecycle above.
        if "private_from" in function:
            witness = function["private_from"]
            path = isinstance(witness, dict) and "via" in witness
            if path:
                validate_private_path_contract(witness, function)
                if unit.get("link_runtime", "import") != "import" or unit.get("link_objects"):
                    raise ValueError("private static paths require one import-runtime CIL input")
            if ("export_name" in function or not isinstance(witness, dict)
                    or (not path and (set(witness) != {"caller", "site"}
                        or any(not isinstance(value, str) or not re.fullmatch(r"0x[0-9A-Fa-f]{8}", value)
                               for value in witness.values())))):
                raise ValueError("private linked function needs only an explicit caller/site witness")
            callers = [f for f in functions if f.get("address") == witness["caller"]]
            if (len(callers) != 1 or callers[0] is function
                    or "private_from" in callers[0] or "private_global" in callers[0]
                    or "vtable_entry" in callers[0]):
                raise ValueError("private linked function needs a distinct configured exported caller")
        elif "vtable_entry" in function:
            continue
        else:
            export = function.get("export_name", symbol)
            if not isinstance(export, str) or not SYMBOL.fullmatch(export) or export in exports:
                raise ValueError("invalid/duplicate linked export: " + str(export))
            exports.add(export)
    preserved = unit.get("preserve_public_members", [])
    if (not isinstance(preserved, list)
            or any(not isinstance(symbol, str) or not SYMBOL.fullmatch(symbol)
                   or not re.fullmatch(r"\?[A-Za-z_]\w*@[^?]+@@Q[AB]E.+", symbol)
                   for symbol in preserved)):
        raise ValueError("preserved exports must be normal public thiscall members")
    if len(preserved) != len(set(preserved)) or set(preserved) & (symbols | exports):
        raise ValueError("preserved public exports duplicate a configured entry")
    if not exports and not unit.get("link_objects"):
        raise ValueError("linked unit needs an exported source root")


def pinned_tools(static: bool = False) -> tuple[Path, dict[str, str]]:
    base = Path(os.environ.get("TH105_MSVC8_ROOT", ROOT / ".tools/msvc80-sp1")).resolve()
    pins = tomllib.loads((ROOT / "config/tools.lock.toml").read_text())["msvc8_sp1_ltcg"]
    actual = {name: sha(base / name) for name in PIN_FILES}
    actual.update({name: tree_sha(base / name) for name in PIN_DIRS})
    if actual != pins:
        raise ValueError("LTCG compiler/linker/import-library hashes differ from pinned tools")
    if static:
        pins = tomllib.loads((ROOT / "config/tools.lock.toml").read_text())["msvc8_sp1_ltcg_static"]
        extra = {name: sha(base / name) for name in STATIC_LIBS}
        if extra != pins:
            raise ValueError("static CRT/SDK libraries differ from pinned tools")
        actual.update(extra)
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


def import_identity(entry):
    # pefile supplies convenient names for known ordinal imports. Those names
    # are annotations; preserve the actual PE import lookup identity here.
    return entry.ordinal if entry.import_by_ordinal else entry.name.decode("ascii")


def target_imports(unit: dict, tools: Path) -> list[dict]:
    mappings = unit.get("link_import_targets", [])
    if not mappings:
        return []
    c = comparator()
    c.verify_target()
    game = pefile.PE(str(c.TARGET))
    imports = {entry.address: (dll.dll.decode("ascii").lower(), import_identity(entry))
               for dll in game.DIRECTORY_ENTRY_IMPORT for entry in dll.imports}
    with (ROOT / "config/functions.csv").open(newline="") as stream:
        ledger = {int(row["address"], 0): row for row in csv.DictReader(stream)}
    with (ROOT / "config/function-origins.csv").open(newline="") as stream:
        origins = {int(row["address"], 0): row for row in csv.DictReader(stream)}
    spec = importlib.util.spec_from_file_location("linked_archive", ROOT / "scripts/extract-msvc-library-object.py")
    archive = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(archive)
    known, result = c.known_data_targets(), []
    for mapping in mappings:
        symbol, address = mapping.split("=", 1)
        contract, address = SDK_IMPORTS[symbol], int(address, 0)
        members = [body for _, body in archive.archive_members((tools / contract["library"]).read_bytes())
                   if hashlib.sha256(body).hexdigest() == contract["member_sha256"]]
        if len(members) != 1:
            raise ValueError("pinned SDK short import member is missing or ambiguous")
        member = members[0]
        expected_strings = symbol.encode("ascii") + b"\0" + contract["dll"].encode("ascii") + b"\0"
        header = struct.unpack_from("<HHHHIIHH", member)
        if (header[:4] != (0, 0xffff, 0, 0x14c) or header[5:] != (len(member) - 20, contract["ordinal"], 0)
                or member[20:].lower() != expected_strings):
            raise ValueError("pinned SDK member has the wrong symbol/DLL/ordinal/code type")
        iat, raw, addends, validation = known[contract["iat"]]
        section = game.get_section_by_rva(address - game.OPTIONAL_HEADER.ImageBase)
        iat_section = game.get_section_by_rva(iat - game.OPTIONAL_HEADER.ImageBase)
        origin = origins.get(address, {})
        if (ledger.get(address, {}).get("size") != "6" or section is None
                or not section.Characteristics & 0x20000000 or iat_section is None
                or iat_section.Characteristics & 0x20000000
                or (origin.get("origin"), origin.get("disposition")) != ("import_thunk", "exclude")
                or addends != frozenset({0}) or validation != "literal" or len(raw) != 4
                or c.target_bytes(iat, 4) != raw
                or imports.get(iat) != (contract["dll"], contract["ordinal"])
                or c.target_bytes(address, 6) != b"\xff\x25" + struct.pack("<I", iat)):
            raise ValueError("SDK target is not its attested six-byte import thunk and IAT")
        result.append({"symbol": symbol, "target": address, "target_iat": iat, **contract})
    return result


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


def coff_inputs(unit: dict, image: Path) -> list[dict]:
    from workflow_manifest import repository_path
    result = []
    for index, source in enumerate(unit.get("linked_coff_sources", [])):
        obj = image.with_suffix(f".coff{index}.obj")
        result.append({"source": source, "source_sha256": sha(repository_path(source)),
                       "object": obj.name, "object_sha256": sha(obj)})
    return result


def pe_data(pe, address: int, size: int) -> bytes:
    rva = address - pe.OPTIONAL_HEADER.ImageBase
    section = pe.get_section_by_rva(rva)
    if (size < 0 or section is None or section.Characteristics & 0x20000000
            or not section.VirtualAddress <= rva <= rva + size <= section.VirtualAddress + section.Misc_VirtualSize):
        raise ValueError("RTTI/vtable data escapes a nonexecutable PE section")
    data = pe.get_data(rva, size)
    if len(data) != size:
        raise ValueError("RTTI/vtable data is truncated")
    return data


def readonly_data(pe, address: int, size: int) -> bytes:
    data = pe_data(pe, address, size)
    if pe.get_section_by_rva(address - pe.OPTIONAL_HEADER.ImageBase).Characteristics & 0x80000000:
        raise ValueError("native vtable/COL must be read-only data")
    return data


def primary_type_name(pe, vtable: int) -> str:
    col, = struct.unpack("<I", readonly_data(pe, vtable - 4, 4))
    signature, offset, cd_offset, descriptor, hierarchy = struct.unpack("<5I", readonly_data(pe, col, 20))
    if signature or offset or cd_offset or not hierarchy:
        raise ValueError("native vtable needs a primary VC8 RTTI COL")
    section = pe.get_section_by_rva(descriptor + 8 - pe.OPTIONAL_HEADER.ImageBase)
    if section is None:
        raise ValueError("native RTTI type descriptor is unmapped")
    available = pe.OPTIONAL_HEADER.ImageBase + section.VirtualAddress + section.Misc_VirtualSize - descriptor - 8
    raw = pe_data(pe, descriptor + 8, min(256, available))
    if b"\0" not in raw:
        raise ValueError("native RTTI type name is unterminated")
    return raw.split(b"\0", 1)[0].decode("ascii")


def target_vtables(unit: dict) -> list[dict]:
    contracts = unit.get("link_vtables", [])
    if not contracts:
        return []
    c = comparator()
    c.verify_target()
    known = c.known_data_targets()
    pe = pefile.PE(str(c.TARGET))
    with (ROOT / "config/functions.csv").open(newline="") as stream:
        candidates = {int(row["address"], 0) for row in csv.DictReader(stream)}
    result = []
    for table in contracts:
        address, raw, addends, validation = known[table["target"]]
        entry_symbol, entry = table["entry"].split("=")
        entry = int(entry, 0)
        entry_section = pe.get_section_by_rva(entry - pe.OPTIONAL_HEADER.ImageBase)
        if (len(raw) != 4 or addends != frozenset({0}) or validation != "address"
                or readonly_data(pe, address, 4) != raw or entry not in candidates
                or entry_section is None or not entry_section.Characteristics & 0x20000000
                or struct.unpack("<I", raw)[0] != entry
                or primary_type_name(pe, address) != table["target_type_name"]):
            raise ValueError("target single-destructor vtable/entry/RTTI is not attested")
        result.append({"symbol": table["symbol"], "target_key": table["target"],
                       "target_address": address, "target_type_name": table["target_type_name"],
                       "entry_symbol": entry_symbol, "entry_target": entry})
    return result


def parse_map_symbols(text: str) -> dict[str, list[tuple[int, str]]]:
    result = {}
    for line in text.splitlines():
        match = MAP_SYMBOL.match(line)
        if match:
            result.setdefault(match[1], []).append((int(match[2], 16), match[3].strip()))
    return result


def source_vtables(pe, symbols: dict, functions: dict, contracts: list[dict], cil_owner: str) -> list[dict]:
    result = []
    for table in contracts:
        found = symbols.get(table["symbol"], [])
        if len(found) != 1 or found[0][1].split()[-1:] != [cil_owner]:
            raise ValueError("native vtable is not uniquely owned by the source CIL object")
        address = found[0][0]
        if address % 4:
            raise ValueError("native vtable is not dword-aligned")
        entry, = struct.unpack("<I", readonly_data(pe, address, 4))
        expected_types = {prefix + table["symbol"][4:-5] + "@@" for prefix in (".?AV", ".?AU")}
        owners = [owner for symbol, owner in functions.get(entry, []) if symbol == table["entry_symbol"]]
        if (len(owners) != 1 or owners[0].split()[-1:] != [cil_owner]
                or primary_type_name(pe, address) not in expected_types):
            raise ValueError("native vtable entry/RTTI disagrees with its source class")
        entry_section = pe.get_section_by_rva(entry - pe.OPTIONAL_HEADER.ImageBase)
        if entry_section is None or not entry_section.Characteristics & 0x20000000:
            raise ValueError("native deleting destructor is outside executable code")
        section = pe.get_section_by_rva(address - pe.OPTIONAL_HEADER.ImageBase)
        if address + 8 <= pe.OPTIONAL_HEADER.ImageBase + section.VirtualAddress + section.Misc_VirtualSize:
            following, = struct.unpack("<I", pe_data(pe, address + 4, 4))
            next_section = pe.get_section_by_rva(following - pe.OPTIONAL_HEADER.ImageBase)
            if next_section is not None and next_section.Characteristics & 0x20000000:
                raise ValueError("native vtable has an unsupported extra function slot")
        result.append({**table, "source_address": address, "source_entry": entry})
    if len({table["source_address"] for table in result}) != len(result):
        raise ValueError("native vtable mappings alias one source address")
    return result


def validate_body_relocations(pe, start: int, size: int, data_refs: list[dict]) -> None:
    expected = {start + ref["field_offset"] for ref in data_refs if "field_offset" in ref}
    found = set()
    for block in getattr(pe, "DIRECTORY_ENTRY_BASERELOC", []):
        for relocation in block.entries:
            address = pe.OPTIONAL_HEADER.ImageBase + relocation.rva
            if not relocation.type or max(start, address) >= min(start + size, address + 4):
                continue
            if relocation.type != 3 or address not in expected or address in found:
                raise ValueError("unsupported/duplicate linked base relocation")
            found.add(address)
    if found != expected:
        raise ValueError("typed internal fields need exact HIGHLOW relocation coverage")


def check_build_phase(phase: str, returncode: int, log: Path) -> None:
    output = log.read_text(errors="replace")
    # LNK's numeric suffix is part of the diagnostic token: a word boundary
    # immediately after "LNK" would miss ordinary warnings such as LNK4210.
    if returncode or re.search(r"\b(?:fatal\s+error|(?:error|warning)\s+LNK[0-9]*)\b", output, re.I):
        raise RuntimeError(f"LTCG {phase} failed; {log}:\n" + output[-4000:])


def build_linked(name: str, unit: dict) -> dict:
    from linked_lifecycle import layout_inputs
    from workflow_manifest import repository_path, unit_input_digest
    static = unit.get("link_runtime", "import") == "static"
    tools, hashes = pinned_tools(static)
    parsers = parser_versions()
    bindings = target_bindings(unit)
    sdk_imports = target_imports(unit, tools)
    vtables = target_vtables(unit)
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
    compile_flags = list(compile_command)
    compile_command.extend(["/Fo" + win(obj), win(source)])
    coff_objects, coff_commands = [], []
    for index, path in enumerate(unit.get("linked_coff_sources", [])):
        native_obj = output.with_suffix(f".coff{index}.obj")
        coff_objects.append(native_obj)
        coff_commands.append([p for p in compile_flags if p != "/GL"]
                             + ["/Fo" + win(native_obj), win(repository_path(path))])
    layout_commands = [[p for p in compile_flags if p != "/GL"]
                       + ["/Fo" + win(output.with_suffix(f".layout{i}.obj")), win(repository_path(o["layout_source"]))]
                       for i, o in enumerate(unit.get("link_objects", []))]
    link_command = ["wine", str(tools / "bin/link.exe"), "/nologo", "/DLL", "/LTCG",
                    "/NODEFAULTLIB", "/OPT:NOICF", f"/BASE:0x{IMAGE_BASE:X}",
                    "/MAP:" + win(map_path), "/OUT:" + win(output)]
    link_command.append("/OPT:REF" if static else "/NOENTRY")
    link_command.extend("/EXPORT:" + f.get("export_name", f["symbol_base"])
                        for f in unit["functions"] if "private_from" not in f
                        and "private_global" not in f and "vtable_entry" not in f)
    link_command.extend("/EXPORT:" + symbol for symbol in unit.get("preserve_public_members", []))
    libraries = sorted({contract["library"] for contract in sdk_imports})
    libraries.extend(STATIC_LIBS if static else ("lib/msvcrt.lib", "lib/msvcprt.lib"))
    link_command.extend(win(p) for p in [*coff_objects, obj, data_obj, *(tools / p for p in libraries),
                                        ])
    # Each invocation is serial. /FORCE and unresolved references are forbidden.
    phases = [(f"coff{index}.compile", command) for index, command in enumerate(coff_commands)]
    phases += [(f"layout{index}.compile", command) for index, command in enumerate(layout_commands)]
    for phase, command in phases + [("compile", compile_command), ("link", link_command)]:
        log = output.with_suffix("." + phase + ".log")
        with log.open("w") as stream:
            completed = subprocess.run(command, cwd=ROOT, env=environment, stdout=stream, stderr=subprocess.STDOUT)
        check_build_phase(phase, completed.returncode, log)
    input_digest, inputs = unit_input_digest(name, unit)
    metadata = {"schema": "th105-linked-pe-v1", "unit": name, "profile": PROFILE,
                "target_sha256": comparator().verify_target(), "input_digest": input_digest, "inputs": inputs,
                "image_sha256": sha(output), "map_sha256": sha(map_path), "source_sha256": sha(source),
                "ltcg_object_sha256": sha(obj), "bindings_object_sha256": sha(data_obj),
                "coff_inputs": coff_inputs(unit, output), "coff_compile_commands": coff_commands,
                "layout_inputs": layout_inputs(unit, output), "layout_compile_commands": layout_commands,
                "vtable_contracts": vtables,
                "sdk_imports": sdk_imports,
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


def decode_closed_body(code: bytes, start: int, *, tail: bool = False,
                       external_exits: dict[int, int] | None = None) -> list:
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    decoder.detail = True
    instructions = list(decoder.disasm(code, start))
    terminal = instructions[-1] if instructions else None
    tail_end = (tail and terminal is not None and terminal.size == 5 and terminal.bytes[0] == 0xe9
                and terminal.operands[0].type == capstone.x86.X86_OP_IMM
                and not start <= terminal.operands[0].imm < start + len(code))
    if not instructions or sum(i.size for i in instructions) != len(code) or (terminal.mnemonic != "ret" and not tail_end):
        raise ValueError("linked body does not close through a complete RET boundary")
    by_address = {i.address: i for i in instructions}
    external_exits = external_exits or {}
    for site, destination in external_exits.items():
        instruction = by_address.get(site)
        if (instruction is None or instruction.size != 5 or instruction.bytes[0] != 0xE9
                or instruction.operands[0].type != capstone.x86.X86_OP_IMM
                or instruction.operands[0].imm != destination
                or start <= destination < start + len(code)):
            raise ValueError("qualified linked error exit disagrees with its exact E9 edge")
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
            if instruction.address in external_exits or (tail_end and instruction.address == terminal.address):
                continue  # Its named destination must subsequently pass REL32 resolution.
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
                 image_range: tuple[int, int], game_range: tuple[int, int],
                 vtables: list[dict] = (), *, internal_refs: list[dict] = (), tail: bool = False,
                 external_exits: dict[int, int] | None = None) -> tuple[bytes, list, list]:
    instructions = decode_closed_body(code, start, tail=tail, external_exits=external_exits)
    native_vtables = {table["source_address"]: table for table in vtables}
    typed = {ref["source_address"]: ref for ref in internal_refs}
    if len(typed) != len(internal_refs) or set(typed) & set(native_vtables):
        raise ValueError("typed internal address roles overlap")
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
        external_tail = ((tail and instruction is instructions[-1] and instruction.bytes[0] == 0xe9)
                         or instruction.address in (external_exits or {}))
        if ((instruction.group(capstone.CS_GRP_CALL) or external_tail)
                and instruction.operands[0].type == capstone.x86.X86_OP_IMM):
            if instruction.size != 5 or instruction.bytes[0] not in (0xE8, 0xE9):
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
                if value not in permitted and value not in typed:
                    raise ValueError(f"unattested linked absolute memory reference {value:#x}")
                if value in permitted and operand.size > widths[value]:
                    raise ValueError("linked absolute read/write exceeds its attested bytes")
            elif operand.type == capstone.x86.X86_OP_IMM and not control_immediate:
                value = operand.imm & 0xffffffff
                if value in native_vtables:
                    destination = instruction.operands[0]
                    if (instruction.id != capstone.x86.X86_INS_MOV or len(instruction.operands) != 2
                            or destination.type != capstone.x86.X86_OP_MEM or destination.size != 4
                            or (not destination.mem.base and (destination.mem.disp & 0xffffffff) not in typed)
                            or (not destination.mem.base and typed[destination.mem.disp & 0xffffffff]["kind"] != "object")
                            or destination.mem.index
                            or destination.mem.segment in {capstone.x86.X86_REG_FS, capstone.x86.X86_REG_GS}
                            or instruction.imm_size != 4
                            or not 0 < instruction.imm_offset <= instruction.size - 4):
                        raise ValueError("native vtable address is not a supported dword member vptr store")
                    table = native_vtables[value]
                    field = offset + instruction.imm_offset
                    struct.pack_into("<I", canonical, field, table["target_address"])
                    references.append({"kind": "vptr", "offset": offset, "field_offset": field,
                        "source_address": value, "address": table["target_address"],
                        "symbol": table["symbol"], "target_key": table["target_key"]})
                    continue
                if image_range[0] <= value < image_range[1] and value not in typed:
                    raise ValueError("unresolved internal linked address/literal")
                if game_range[0] <= value < game_range[1] and value not in permitted:
                    raise ValueError(f"unattested linked game address {value:#x}")
            if value in typed:
                ref = typed[value]
                memory = operand.type == capstone.x86.X86_OP_MEM
                if memory:
                    allowed = ref["kind"] in {"object", "runtime"} and operand.size <= ref["size"]
                    field, width = instruction.disp_offset, instruction.disp_size
                else:
                    allowed = ((ref["kind"] == "object" and instruction.mnemonic in {"mov", "push"})
                               or (ref["kind"] == "eh_handler" and instruction.mnemonic == "push")
                               or (ref["kind"] == "eh_info" and instruction.mnemonic == "mov"
                                   and instruction.operands[0].type == capstone.x86.X86_OP_REG
                                   and instruction.operands[0].reg == capstone.x86.X86_REG_EAX))
                    field, width = instruction.imm_offset, instruction.imm_size
                if not allowed or width != 4 or not 0 < field <= instruction.size - 4:
                    raise ValueError("internal address is used outside its typed operand role")
                field += offset
                struct.pack_into("<I", canonical, field, ref["address"])
                references.append({**ref, "offset": offset, "field_offset": field})
                continue
            if value in permitted:
                references.append({"offset": offset, "address": value, "bindings": permitted[value]})
    return bytes(canonical), replayed, references


def resolve_linked_call(destination: int, pe, functions: dict, imports: dict, targets: dict,
                        sdk_imports: list[dict] | None = None) -> tuple[str, int]:
    if not IMAGE_BASE <= destination < IMAGE_BASE + pe.OPTIONAL_HEADER.SizeOfImage:
        raise ValueError("linked call escapes its image without a named linker identity")
    thunk = pe.get_data(destination - IMAGE_BASE, 6) if IMAGE_BASE <= destination < IMAGE_BASE + pe.OPTIONAL_HEADER.SizeOfImage else b""
    if thunk[:2] == b"\xff\x25" and len(thunk) == 6:
        dll, imported = imports.get(struct.unpack_from("<I", thunk, 2)[0], (None, None))
        if dll not in RUNTIME_DLLS:
            contracts = [contract for contract in sdk_imports or []
                         if (dll, imported) == (contract["dll"], contract["ordinal"])
                         and targets.get(contract["symbol"]) == contract["target"]]
            if len(contracts) != 1:
                raise ValueError("external linked call has no attested pinned SDK import contract")
            contract = contracts[0]
            if functions.get(destination) != [(contract["symbol"], "WS2_32:WS2_32.dll")]:
                raise ValueError("SDK thunk map symbol/library identity disagrees")
            return contract["symbol"], contract["target"]
        if not isinstance(imported, str) or not imported:
            raise ValueError("external linked call is not a named pinned VC8 runtime import")
        symbol = imported if imported.startswith("?") else "_" + imported
        if symbol not in targets:
            raise ValueError("unmapped linked runtime call: " + symbol)
        return symbol, targets[symbol]
    mapped = {(symbol, targets[symbol]) for symbol, _ in functions.get(destination, []) if symbol in targets}
    if len({address for _, address in mapped}) != 1:
        raise ValueError(f"unmapped/ambiguous linked function call {destination:#x}")
    return sorted(mapped)[0]


def source_function_start(function: dict, functions: dict, exports: dict, cil_owner: str,
                          vtables: list[dict] = ()) -> int:
    symbol = function["symbol_base"]
    found = [(address, owner) for address, aliases in functions.items()
             for name, owner in aliases if name == symbol]
    if len(found) != 1 or found[0][1].split()[-1:] != [cil_owner]:
        raise ValueError("linked function is not uniquely owned by the configured source CIL object")
    start = found[0][0]
    if "vtable_entry" in function:
        witnesses = [table for table in vtables
                     if table.get("symbol") == function["vtable_entry"]
                     and table.get("entry_symbol") == symbol
                     and table.get("entry_target") == int(function["address"], 0)]
        if (len(witnesses) != 1 or witnesses[0].get("source_entry") != start
                or start in exports.values() or any(key in function
                    for key in ("export_name", "private_from", "private_global"))):
            raise ValueError("linked destructor has no unique unexported native vtable entry")
        # VC8 can give its scalar/vector deleting wrappers the same code.
        # This admits only that compiler alias for this exact class, never
        # unrelated entry aliases or a new calling convention.
        allowed = {symbol, symbol.replace("??_G", "??_E", 1)}
        names = [name for name, _ in functions[start]]
        if len(names) != len(set(names)) or not set(names) <= allowed:
            raise ValueError("linked vtable destructor has unrelated/duplicate aliases")
        for _, owner in functions[start]:
            if (owner.split()[-1:] != [cil_owner]
                    and owner.split()[-4:] != ["CIL", "library:", "CIL", "module"]):
                raise ValueError("linked vtable destructor alias is outside its CIL context")
    elif "private_from" in function or "private_global" in function:
        if len(functions[start]) != 1 or start in exports.values():
            raise ValueError("private linked function has an aliased or exported entry")
    elif exports.get(function.get("export_name", symbol)) != start:
        raise ValueError("linked export/map identity disagrees")
    return start


def linked_body(pe, functions: dict, start: int) -> bytes:
    section = pe.get_section_by_rva(start - IMAGE_BASE)
    if section is None or not section.Characteristics & 0x20000000 or section.Name.rstrip(b"\0") != b".text":
        raise ValueError("linked function is outside executable .text")
    section_end = IMAGE_BASE + section.VirtualAddress + section.Misc_VirtualSize
    end = min([address for address in functions if start < address < section_end] + [section_end])
    raw = pe.get_data(start - IMAGE_BASE, end - start)
    if len(raw) != end - start:
        raise ValueError("linked section is truncated")
    return raw.rstrip(b"\xcc")  # Padding is outside the independently decoded RET boundary.


def validate_private_path_contract(contract: dict, function: dict) -> None:
    """An explicit static call path augments, rather than replaces, its export root."""
    address = lambda value: isinstance(value, str) and re.fullmatch(r"0x[0-9A-Fa-f]{8}", value)
    source = contract.get("source_file")
    via = contract.get("via")
    if (set(contract) != {"caller", "site", "source_file", "via"}
            or not address(contract.get("caller")) or not address(contract.get("site"))
            or not isinstance(source, str) or not source.startswith("src/")
            or not source.endswith(".cpp") or ".." in Path(source).parts
            or not isinstance(via, list) or not 1 <= len(via) <= 4):
        raise ValueError("private path needs an explicit source file and one to four static callers")
    addresses, symbols = {int(contract["caller"], 0), int(function["address"], 0)}, {function["symbol_base"]}
    if len(addresses) != 2:
        raise ValueError("private path cannot witness itself")
    for node in via:
        if (not isinstance(node, dict) or set(node) != {"address", "symbol_base", "site"}
                or not address(node.get("address")) or not address(node.get("site"))
                or not isinstance(node.get("symbol_base"), str)
                or not SYMBOL.fullmatch(node["symbol_base"])
                or int(node["address"], 0) in addresses or node["symbol_base"] in symbols):
            raise ValueError("private path has a malformed, duplicate or cyclic static caller")
        addresses.add(int(node["address"], 0)); symbols.add(node["symbol_base"])


def caller_data_witness(pe, instructions: list, functions: dict, bindings: list[dict],
                        game_range: tuple[int, int]) -> list[dict]:
    """Observe source caller address fields without canonicalizing or accepting that caller."""
    permitted = {}
    for binding in bindings:
        for addend in binding["addends"]:
            address = binding["address"] + addend
            permitted[address] = max(permitted.get(address, 0), len(bytes.fromhex(binding["data_hex"])))
    start = instructions[0].address
    refs = []
    for instruction in instructions:
        control = instruction.group(capstone.CS_GRP_CALL) or is_branch(instruction)
        for operand in instruction.operands:
            memory = operand.type == capstone.x86.X86_OP_MEM
            if memory:
                if operand.mem.base or operand.mem.index or operand.mem.segment in {
                        capstone.x86.X86_REG_FS, capstone.x86.X86_REG_GS}:
                    continue
                value, field, width = operand.mem.disp & 0xffffffff, instruction.disp_offset, instruction.disp_size
            elif operand.type == capstone.x86.X86_OP_IMM and not control:
                value, field, width = operand.imm & 0xffffffff, instruction.imm_offset, instruction.imm_size
            else:
                continue
            if value in permitted:
                if memory and operand.size > permitted[value]:
                    raise ValueError("caller access exceeds its attested binding")
                refs.append({"offset": instruction.address - start, "address": value, "kind": "binding"})
                continue
            section = pe.get_section_by_rva(value - IMAGE_BASE)
            if section is None:
                if memory or game_range[0] <= value < game_range[1]:
                    raise ValueError("caller has an unattested external address operand")
                continue
            extent = operand.size if memory else 1
            if (width != 4 or not 0 < field <= instruction.size - 4
                    or value + extent > IMAGE_BASE + section.VirtualAddress + section.Misc_VirtualSize
                    or not section.Characteristics & 0x40000000
                    or (memory and section.Characteristics & 0x20000000)
                    or (not memory and section.Characteristics & 0x20000000 and value not in functions)):
                raise ValueError("caller address operand has no complete mapped data/function role")
            refs.append({"offset": instruction.address - start,
                "field_offset": instruction.address - start + field, "source_address": value,
                "kind": "source_only", "section": section.Name.rstrip(b"\0").decode("ascii")})
    validate_body_relocations(pe, start, sum(i.size for i in instructions), refs)
    return refs


def private_path_witness(function: dict, unit: dict, pe, functions: dict, exports: dict,
                         cil_owner: str, ledger: dict, read_target, map_text: str,
                         bindings: list[dict], game_range: tuple[int, int]) -> dict:
    from workflow_manifest import source_dependencies, repository_path
    contract = function["private_from"]
    validate_private_path_contract(contract, function)
    source_file = repository_path(contract["source_file"])
    if source_file not in source_dependencies(unit):
        raise ValueError("private path source is not an actual quoted-include dependency")
    roots = [f for f in unit["functions"] if f["address"] == contract["caller"]]
    if len(roots) != 1 or any(key in roots[0] for key in ("private_from", "private_global", "vtable_entry")):
        raise ValueError("private path has no distinct configured exported root")
    nodes = [dict(roots[0], site=contract["site"]), *contract["via"], function]
    marker = re.search(r"^\s*Static symbols\s*$", map_text, re.M)
    if marker is None:
        raise ValueError("private path needs the actual linker static-symbol table")
    statics = parse_map(map_text[marker.end():])
    starts = [source_function_start(roots[0], functions, exports, cil_owner)]
    for node in contract["via"]:
        hits = [(a, aliases) for a, aliases in functions.items()
                if any(name == node["symbol_base"] for name, _ in aliases)]
        expected = [(node["symbol_base"], "CIL library: CIL module")]
        if (len(hits) != 1 or hits[0][1] != expected
                or statics.get(hits[0][0]) != expected or hits[0][0] in exports.values()):
            raise ValueError("private path intermediate is not a unique unexported CIL static symbol")
        starts.append(hits[0][0])
    starts.append(source_function_start(function, functions, exports, cil_owner))
    edges = []
    for index, node in enumerate(nodes[:-1]):
        row = ledger.get(node["address"], {})
        if row.get("status") not in {"implemented", "matching"} or row.get("source_file") != contract["source_file"]:
            raise ValueError("private path caller has no reviewed source in its included TU")
        source = linked_body(pe, functions, starts[index])
        source_rows = decode_closed_body(source, starts[index])
        data = caller_data_witness(pe, source_rows, functions, bindings, game_range)
        target = read_target(int(node["address"], 0), int(row["size"], 0))
        target_rows = decode_closed_body(target, int(node["address"], 0))
        def calls(rows, destination):
            return [i.address for i in rows if i.size == 5 and i.bytes[0] == 0xe8
                    and i.operands[0].imm == destination]
        source_calls = calls(source_rows, starts[index + 1])
        if len(source_calls) != 1 or calls(target_rows, int(nodes[index + 1]["address"], 0)) != [int(node["site"], 0)]:
            raise ValueError("private path needs one reachable E8 per complete source/target caller")
        if index == 0:
            mapping = nodes[1]["symbol_base"] + "=" + nodes[1]["address"]
            if node.get("rel32_targets", []).count(mapping) != 1:
                raise ValueError("private path exported root does not map its actual static callee")
        edges.append({"caller": node["address"], "callee": nodes[index + 1]["address"],
            "target_site": node["site"], "source_caller_symbol": node["symbol_base"],
            "source_caller_va": f"0x{starts[index]:08X}", "source_site": f"0x{source_calls[0]:08X}",
            "source_caller_sha256": hashlib.sha256(source).hexdigest(),
            "target_caller_sha256": hashlib.sha256(target).hexdigest(),
            "source_only_address_fields": data})
    return {"source_file": contract["source_file"], "edges": edges,
            "scope": "complete normal caller CFG and source address-role/relocation witnesses only; no caller byte or EH equality"}


def private_caller_witness(function: dict, unit: dict, pe, functions: dict, exports: dict,
                           cil_owner: str, ledger: dict, read_target, *, map_text: str = "",
                           bindings: list[dict] = (), game_range: tuple[int, int] = (0, 0)) -> dict:
    contract = function["private_from"]
    if "via" in contract:
        return private_path_witness(function, unit, pe, functions, exports, cil_owner,
                                    ledger, read_target, map_text, bindings, game_range)
    callers = [f for f in unit["functions"] if f["address"] == contract["caller"]]
    if len(callers) != 1 or "private_from" in callers[0]:
        raise ValueError("private linked witness has no configured exported caller")
    caller = callers[0]
    caller_row = ledger[contract["caller"]]
    if caller_row["status"] not in {"implemented", "matching"} or caller_row["source_file"] != unit["source"]:
        raise ValueError("private linked witness caller must have reviewed source in this TU")
    start = source_function_start(function, functions, exports, cil_owner)
    parent = source_function_start(caller, functions, exports, cil_owner)
    source = linked_body(pe, functions, parent)
    source_instructions = decode_closed_body(source, parent)
    validate_body_relocations(pe, parent, len(source), [])
    source_calls = [i.address for i in source_instructions
                    if i.size == 5 and i.bytes[0] == 0xe8 and i.operands[0].imm == start]
    target_parent, target_start = int(caller["address"], 0), int(function["address"], 0)
    target = read_target(target_parent, int(caller_row["size"], 0))
    target_calls = [i.address for i in decode_closed_body(target, target_parent)
                    if i.size == 5 and i.bytes[0] == 0xe8 and i.operands[0].imm == target_start]
    if len(source_calls) != 1 or target_calls != [int(contract["site"], 0)]:
        raise ValueError("private linked function needs one exact direct call in both closed caller bodies")
    mappings = [mapping for mapping in caller.get("rel32_targets", [])
                if mapping.split("=", 1)[0] == function["symbol_base"]]
    if len(mappings) != 1 or int(mappings[0].split("=", 1)[1], 0) != target_start:
        raise ValueError("private linked caller must map its actual source callee to the target entry")
    return {"caller": caller["address"], "target_site": contract["site"],
            "source_caller_symbol": caller["symbol_base"], "source_caller_va": f"0x{parent:08X}",
            "source_site": f"0x{source_calls[0]:08X}",
            "source_caller_sha256": hashlib.sha256(source).hexdigest(),
            "target_caller_sha256": hashlib.sha256(target).hexdigest()}


def preserved_member_witnesses(unit: dict, pe, functions: dict, exports: dict, cil_owner: str) -> list[dict]:
    result = []
    for symbol in unit.get("preserve_public_members", []):
        member = source_function_start({"symbol_base": symbol}, functions, exports, cil_owner)
        if len(functions[member]) != 1:
            raise ValueError("preserved public member has an aliased source entry")
        body = linked_body(pe, functions, member)
        if not body:
            raise ValueError("preserved public member has no native implementation")
        result.append({"symbol": symbol, "source_address": member,
                       "source_sha256": hashlib.sha256(body).hexdigest()})
    return result


def compare_linked(name: str, unit: dict, addresses: set[str], image: Path | None = None) -> list[dict]:
    from linked_lifecycle import layout_inputs, validate_static_entry, object_witnesses, cleanup_eh
    from linked_noreturn import witness as error_tail_witness
    from workflow_manifest import repository_path, unit_input_digest
    c = comparator()
    target_hash = c.verify_target()
    image = image or repository_path(unit["object"], output=True)
    metadata = json.loads(image.with_suffix(".link.json").read_text())
    static = unit.get("link_runtime", "import") == "static"
    tool_root, tools = pinned_tools(static)
    bindings = target_bindings(unit)
    sdk_imports = target_imports(unit, tool_root)
    vtable_contracts = target_vtables(unit)
    expected = {"schema": "th105-linked-pe-v1", "unit": name, "profile": PROFILE,
                "target_sha256": target_hash, "input_digest": unit_input_digest(name, unit)[0],
                "source_sha256": sha(repository_path(unit["source"])), "image_sha256": sha(image),
                "map_sha256": sha(image.with_suffix(".map")), "tools": tools, "parsers": parser_versions(), "bindings": bindings,
                "ltcg_object_sha256": sha(image.with_suffix(".ltcg.obj")),
                "bindings_object_sha256": sha(image.with_suffix(".bindings.obj")),
                "coff_inputs": coff_inputs(unit, image), "vtable_contracts": vtable_contracts,
                "layout_inputs": layout_inputs(unit, image),
                "sdk_imports": sdk_imports}
    if any(metadata.get(key) != value for key, value in expected.items()):
        raise ValueError("stale or modified linked build provenance; rebuild the configured unit")
    pe = pefile.PE(str(image))
    if (pe.FILE_HEADER.Machine != 0x14c or pe.OPTIONAL_HEADER.Magic != 0x10b
            or pe.OPTIONAL_HEADER.ImageBase != IMAGE_BASE
            or not pe.FILE_HEADER.Characteristics & 0x2000
            or (pe.OPTIONAL_HEADER.AddressOfEntryPoint == 0 if static else pe.OPTIONAL_HEADER.AddressOfEntryPoint != 0)):
        raise ValueError("linked artifact is not the pinned x86 PE32 image")
    map_text = image.with_suffix(".map").read_text(errors="strict")
    functions = parse_map(map_text)
    if static:
        validate_static_entry(pe, functions)
    vtables = source_vtables(pe, parse_map_symbols(map_text), functions,
                             vtable_contracts, image.with_suffix(".ltcg.obj").name)
    exports = {}
    if not hasattr(pe, "DIRECTORY_ENTRY_EXPORT") and not unit.get("link_objects"):
        raise ValueError("linked image has no export directory")
    for entry in getattr(getattr(pe, "DIRECTORY_ENTRY_EXPORT", None), "symbols", []):
        export = entry.name.decode("ascii") if entry.name else f"#{entry.ordinal}"
        if entry.forwarder or export in exports:
            raise ValueError("forwarded/duplicate linked exports are unsupported")
        exports[export] = IMAGE_BASE + entry.address
    imports = {entry.address: (dll.dll.decode("ascii").lower(), import_identity(entry))
               for dll in getattr(pe, "DIRECTORY_ENTRY_IMPORT", []) for entry in dll.imports}
    preserved_members = preserved_member_witnesses(unit, pe, functions, exports, image.with_suffix(".ltcg.obj").name)
    with (ROOT / "config/functions.csv").open(newline="") as stream:
        ledger = {row["address"]: row for row in csv.DictReader(stream)}
    game = pefile.PE(str(c.TARGET), fast_load=True)
    game_range = (game.OPTIONAL_HEADER.ImageBase, game.OPTIONAL_HEADER.ImageBase + game.OPTIONAL_HEADER.SizeOfImage)
    internal_refs, globals_witnesses = object_witnesses(unit, pe, game, functions, parse_map_symbols(map_text), exports,
        image.with_suffix(".ltcg.obj").name, c.known_data_targets(), c.target_bytes) if static else ([], {})
    reports = []
    for function in unit["functions"]:
        if addresses and function["address"] not in addresses:
            continue
        cil_owner = image.with_suffix(".ltcg.obj").name
        start = source_function_start(function, functions, exports, cil_owner, vtables)
        raw = linked_body(pe, functions, start)
        witness = (private_caller_witness(function, unit, pe, functions, exports,
                                        cil_owner, ledger, c.target_bytes, map_text=map_text,
                                        bindings=bindings, game_range=game_range)
                   if "private_from" in function else None)
        targets = dict(mapping.split("=", 1) for mapping in function.get("rel32_targets", []))
        targets = {symbol: int(address, 0) for symbol, address in targets.items()}
        if any(f"0x{destination:08X}" not in ledger for destination in targets.values()):
            raise ValueError("linked callee mapping is outside the target candidate ledger")

        def resolve(destination: int) -> tuple[str, int]:
            return resolve_linked_call(destination, pe, functions, imports, targets, sdk_imports)

        address = int(function["address"], 0)
        size = int(ledger[function["address"]]["size"], 0)
        target = c.target_bytes(address, size)
        error_exits, _, error_reports = error_tail_witness(
            sys.modules[__name__], function, pe, game, functions, exports,
            cil_owner, start, raw, target, c.target_bytes)
        refs, eh_reports = internal_refs, []
        if "eh_cleanup" in function:
            refs, eh_reports = cleanup_eh(function, pe, game, functions, exports, cil_owner,
                start, raw, target, internal_refs, bindings, vtables, resolve, game_range, c.target_bytes)
        code, calls, data_refs = canonicalize(raw, start, address, bindings, resolve,
            (IMAGE_BASE, IMAGE_BASE + pe.OPTIONAL_HEADER.SizeOfImage), game_range, vtables,
            internal_refs=refs, external_exits=error_exits)
        validate_body_relocations(pe, start, len(raw), data_refs)
        mismatch = c.first_mismatch(target, code, address)
        reports.append({"schema_version": 1, "result": "mismatch" if mismatch else "exact",
            "address": function["address"], "object": str(image), "symbol_base": function["symbol_base"],
            "comparison": {"boundary": "linked_symbol_and_cfg", "size": size},
            "target_size": size, "object_section_tail_size": len(code), "object_size_kind": "linked_symbol_body",
            "linked_function_va": f"0x{start:08X}", "first_mismatch": mismatch, "failure": None,
            "target_executable_sha256": target_hash, "target_sha256": hashlib.sha256(target).hexdigest(),
            "object_compared_sha256": hashlib.sha256(code).hexdigest(), "replayed_rel32": calls,
            "validated_data_references": data_refs, "validated_vtables": vtables,
            "global_lifecycle_witness": globals_witnesses.get(function.get("private_global", {}).get("object")),
            "validated_cleanup_eh": eh_reports,
            "validated_error_tails": error_reports,
            "preserved_public_members": preserved_members,
            "private_caller_witness": witness})
    return reports
