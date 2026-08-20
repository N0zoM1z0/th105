#!/usr/bin/env python3
"""Compare one function's COFF COMDAT section with the original bytes."""

from __future__ import annotations

import csv
import argparse
import hashlib
import json
from pathlib import Path
import re
import struct
import sys
import tomllib


ROOT = Path(__file__).resolve().parents[1]
TARGET = ROOT / "resources" / "th105.exe"
FUNCTIONS = ROOT / "config" / "functions.csv"
KNOWN_SYMBOLS = ROOT / "config" / "known-symbols.csv"
KNOWN_RELOCATIONS = ROOT / "config" / "reccmp-relocations.csv"
TARGET_CONFIG = ROOT / "config" / "target.toml"
IMAGE_REL_I386_DIR32 = 0x0006
IMAGE_REL_I386_REL32 = 0x0014
IMAGE_SCN_CNT_UNINITIALIZED_DATA = 0x00000080
IMAGE_SCN_LNK_NRELOC_OVFL = 0x01000000


def first_mismatch(expected: bytes, actual: bytes, address: int) -> dict[str, object] | None:
    shared = min(len(expected), len(actual))
    offset = next(
        (index for index in range(shared) if expected[index] != actual[index]),
        shared if len(expected) != len(actual) else None,
    )
    if offset is None:
        return None
    return {
        "offset": offset,
        "address": f"0x{address + offset:08X}",
        "target_byte": f"{expected[offset]:02x}" if offset < len(expected) else None,
        "object_byte": f"{actual[offset]:02x}" if offset < len(actual) else None,
        "target_context": expected[offset : offset + 8].hex(" "),
        "object_context": actual[offset : offset + 8].hex(" "),
    }


def rel32_operand_kind(code: bytes | bytearray, field_offset: int) -> str | None:
    """Return the narrowly supported x86 instruction owning a REL32 field."""
    if field_offset >= 1 and code[field_offset - 1] in (0xE8, 0xE9):
        return "call" if code[field_offset - 1] == 0xE8 else "jmp"
    if (
        field_offset >= 2
        and code[field_offset - 2] == 0x0F
        and 0x80 <= code[field_offset - 1] <= 0x8F
    ):
        return "jcc"
    return None


def failure_record(error: Exception) -> tuple[str, dict[str, object]]:
    message = str(error)
    category = "comparison.error"
    details: dict[str, object] = {}

    patterns: list[tuple[str, str]] = [
        ("unknown absolute data relocation", "relocation.dir32.unknown_symbol"),
        ("has unverified addend", "relocation.dir32.addend_unverified"),
        ("DIR32 target has an invalid object section", "relocation.dir32.target_section_invalid"),
        ("is not an allowlisted four-byte import", "relocation.dir32.import_unverified"),
        ("unverified nonzero/unexpected BSS relocation", "relocation.dir32.bss_unverified"),
        ("do not match known literal", "relocation.dir32.object_literal_mismatch"),
        ("no longer match mapping", "relocation.dir32.target_literal_mismatch"),
        ("is not an external CALL/JMP/Jcc", "relocation.rel32.unsupported_operand"),
        ("unknown local call/jump target", "relocation.rel32.unknown_target"),
        ("unknown external call/jump target", "relocation.rel32.unknown_target"),
        ("unsupported code relocation", "relocation.unsupported_type"),
        ("relocation references invalid symbol index", "relocation.symbol_index_invalid"),
        ("COFF relocation extends beyond function section", "relocation.field_outside_section"),
        ("COFF relocation-overflow sections are unsupported", "coff.relocation_overflow"),
        ("REL32 displacement overflow", "relocation.rel32.displacement_overflow"),
        ("is not an i386 COFF object", "coff.machine_unsupported"),
        ("has no function symbol", "coff.symbol_missing"),
        ("has multiple function symbols", "coff.symbol_ambiguous"),
        ("not .text", "coff.symbol_not_text"),
        ("crosses a PE section boundary", "target.range_crosses_section"),
        ("PE section raw data is truncated", "target.raw_truncated"),
        ("is not in a PE section", "target.address_unmapped"),
        ("target SHA-256 mismatch", "target.identity_mismatch"),
        ("target size mismatch", "target.identity_mismatch"),
    ]
    for text, candidate in patterns:
        if text in message:
            category = candidate
            break
    if isinstance(error, FileNotFoundError):
        category = "coff.file_not_found"
    elif category == "comparison.error" and isinstance(error, (ValueError, struct.error)):
        category = "coff.malformed"

    symbol_match = re.search(r"(?:relocation|target):\s*([^\s]+)$", message)
    if symbol_match:
        details["symbol"] = symbol_match.group(1)
    if "unknown local call/jump target" in message:
        details["scope"] = "local"
    elif "unknown external call/jump target" in message:
        details["scope"] = "external"

    failure = {"category": category, "message": message, **details}
    result = "blocked" if category.startswith("relocation.") else "error"
    return result, failure


def canonical(value: str) -> str:
    return f"0x{int(value, 16):08X}"


def verify_target() -> str:
    with TARGET_CONFIG.open("rb") as stream:
        expected = tomllib.load(stream)["target"]
    actual_size = TARGET.stat().st_size
    if actual_size != expected["size"]:
        raise ValueError(
            f"target size mismatch: got {actual_size}, expected {expected['size']}"
        )
    actual_sha256 = hashlib.sha256(TARGET.read_bytes()).hexdigest()
    if actual_sha256 != expected["sha256"]:
        raise ValueError(
            "target SHA-256 mismatch: "
            f"got {actual_sha256}, expected {expected['sha256']}"
        )
    return actual_sha256


def target_bytes(address: int, size: int) -> bytes:
    data = TARGET.read_bytes()
    pe = struct.unpack_from("<I", data, 0x3C)[0]
    section_count = struct.unpack_from("<H", data, pe + 6)[0]
    optional_size = struct.unpack_from("<H", data, pe + 20)[0]
    sections = pe + 24 + optional_size
    image_base = struct.unpack_from("<I", data, pe + 52)[0]
    rva = address - image_base
    for index in range(section_count):
        offset = sections + 40 * index
        virtual_size, virtual_address, raw_size, raw_pointer = struct.unpack_from(
            "<IIII", data, offset + 8
        )
        if virtual_address <= rva < virtual_address + max(virtual_size, raw_size):
            section_offset = rva - virtual_address
            if section_offset + size > max(virtual_size, raw_size):
                raise ValueError(
                    f"range {address:#x}+{size:#x} crosses a PE section boundary"
                )
            raw_available = max(0, min(size, raw_size - section_offset))
            file_offset = raw_pointer + section_offset
            raw = data[file_offset : file_offset + raw_available]
            if len(raw) != raw_available:
                raise ValueError("PE section raw data is truncated")
            return raw + bytes(size - raw_available)
    raise ValueError(f"address {address:#x} is not in a PE section")


def coff_short_name(name: str) -> str:
    if name.startswith("@"):
        return name[1:].split("@", 1)[0]
    if name.startswith("??2@"):
        return "operator_new"
    if name.startswith("??3@"):
        return "operator_delete"
    if name.startswith("??_L@"):
        return "eh_vector_constructor_iterator"
    if name.startswith("??_M@"):
        return "eh_vector_destructor_iterator"
    if name.startswith("??0"):
        return f"{name[3:].split('@', 1)[0]}_ctor"
    if name.startswith("??1"):
        return f"{name[3:].split('@', 1)[0]}_dtor"
    if name.startswith("?"):
        scoped_name, separator, decoration = name[1:].partition("@@")
        parts = scoped_name.split("@")
        if separator and decoration.startswith(("A", "I", "Q", "U")) and len(parts) >= 2:
            return f"{parts[1]}_{parts[0]}"
        return parts[0]
    if name.startswith("_"):
        name = name[1:]
    return name.split("@", 1)[0]


def relocation_target_key(name: str, targets: dict[str, int]) -> str:
    """Resolve a COFF REL32 symbol without collapsing an explicit mapping.

    Different template specializations commonly share the same human-readable
    short name (for example, ``std::vector<T>::push_back``).  An exact decorated
    mapping must therefore take precedence over the compatibility aliases used
    by older match units.
    """
    if name in targets:
        return name

    short_name = coff_short_name(name)
    if short_name in targets:
        return short_name

    if name.startswith("?"):
        unqualified_name = name[1:].split("@", 1)[0]
        if unqualified_name in targets:
            return unqualified_name
    return short_name


def dir32_target_key(
    name: str, overrides: dict[str, str], addend: int = 0
) -> str:
    """Resolve a function-local DIR32 symbol/addend to a verified key."""
    addend_key = f"{name}+0x{addend:X}"
    if addend_key in overrides:
        return overrides[addend_key]
    return overrides.get(name, name)


def is_function_symbol(name: str, symbol_base: str) -> bool:
    if name == symbol_base or name.startswith(f"?{symbol_base}@"):
        return True
    if name.startswith("?") and not name.startswith("??"):
        parts = name[1:].split("@", 2)
        if len(parts) >= 2 and symbol_base == f"{parts[1]}_{parts[0]}":
            return True
    if symbol_base.endswith("_ctor"):
        class_name = symbol_base.removesuffix("_ctor")
        return name.startswith(f"??0{class_name}@")
    if symbol_base.endswith("_dtor"):
        class_name = symbol_base.removesuffix("_dtor")
        return name.startswith(f"??1{class_name}@")
    if symbol_base.endswith("_scalar_deleting_destructor"):
        class_name = symbol_base.removesuffix("_scalar_deleting_destructor")
        return name.startswith(f"??_G{class_name}@")
    return False


def known_targets() -> dict[str, int]:
    targets: dict[str, int] = {}
    with KNOWN_SYMBOLS.open(newline="", encoding="utf-8") as stream:
        for row in csv.DictReader(stream):
            name = row["name"]
            if name in targets:
                raise ValueError(f"duplicate known symbol name: {name}")
            targets[name] = int(row["address"], 16)
    return targets


def known_data_targets() -> dict[str, tuple[int, bytes, frozenset[int], str]]:
    targets: dict[str, tuple[int, bytes, frozenset[int], str]] = {}
    with KNOWN_RELOCATIONS.open(newline="", encoding="utf-8") as stream:
        for row in csv.DictReader(stream):
            name = row["coff_symbol"]
            if name in targets:
                raise ValueError(f"duplicate known relocation symbol: {name}")
            data = bytes.fromhex(row["data_hex"])
            if not data:
                raise ValueError(f"known relocation {name} has no data bytes")
            addends = frozenset(
                int(value, 0)
                for value in row["addends"].split(";")
                if value.strip()
            )
            if not addends or any(value < 0 for value in addends):
                raise ValueError(f"known relocation {name} has invalid addends")
            validation = row.get("validation") or "literal"
            if validation not in {"literal", "address"}:
                raise ValueError(
                    f"known relocation {name} has invalid validation {validation!r}"
                )
            targets[name] = (int(row["address"], 16), data, addends, validation)
    return targets


def coff_symbol_bytes(
    path: Path,
    symbol_base: str,
    function_address: int,
    function_size: int,
    targets: dict[str, int],
    data_targets: dict[str, tuple[int, bytes, frozenset[int], str]],
    data_target_overrides: dict[str, str] | None = None,
) -> bytes:
    if data_target_overrides is None:
        data_target_overrides = {}
    data = path.read_bytes()
    machine = struct.unpack_from("<H", data, 0)[0]
    if machine != 0x014C:
        raise ValueError(f"{path} is not an i386 COFF object")
    section_count = struct.unpack_from("<H", data, 2)[0]
    symbol_pointer, symbol_count = struct.unpack_from("<II", data, 8)
    optional_size = struct.unpack_from("<H", data, 16)[0]
    sections = 20 + optional_size
    string_table = symbol_pointer + symbol_count * 18
    section_rows: list[dict[str, int | bytes]] = []
    for index in range(section_count):
        offset = sections + 40 * index
        name = data[offset : offset + 8].rstrip(b"\0")
        raw_size, raw_pointer = struct.unpack_from("<II", data, offset + 16)
        reloc_pointer = struct.unpack_from("<I", data, offset + 24)[0]
        reloc_count = struct.unpack_from("<H", data, offset + 32)[0]
        characteristics = struct.unpack_from("<I", data, offset + 36)[0]
        section_rows.append(
            {
                "name": name,
                "raw_pointer": raw_pointer,
                "raw_size": raw_size,
                "reloc_pointer": reloc_pointer,
                "reloc_count": reloc_count,
                "characteristics": characteristics,
            }
        )

    def read_symbol_name(offset: int) -> str:
        raw_name = data[offset : offset + 8]
        if raw_name[:4] == b"\0\0\0\0":
            name_offset = struct.unpack_from("<I", raw_name, 4)[0]
            start = string_table + name_offset
            end = data.find(b"\0", start)
            if end < 0:
                raise ValueError("unterminated COFF symbol name")
            return data[start:end].decode("ascii", errors="replace")
        return raw_name.rstrip(b"\0").decode("ascii", errors="replace")

    symbols: dict[int, dict[str, int | str]] = {}
    function_symbol: dict[str, int | str] | None = None
    index = 0
    while index < symbol_count:
        offset = symbol_pointer + index * 18
        name = read_symbol_name(offset)
        value = struct.unpack_from("<I", data, offset + 8)[0]
        section_number = struct.unpack_from("<h", data, offset + 12)[0]
        auxiliary = data[offset + 17]
        symbol = {
            "name": name,
            "value": value,
            "section_number": section_number,
        }
        symbols[index] = symbol
        if (
            0 < section_number <= len(section_rows)
            and is_function_symbol(name, symbol_base)
        ):
            if function_symbol is not None:
                raise ValueError(f"{path} has multiple function symbols for {symbol_base}")
            function_symbol = symbol
        index += 1 + auxiliary

    if function_symbol is None:
        raise ValueError(f"{path} has no function symbol for {symbol_base}")
    section_number = int(function_symbol["section_number"])
    section = section_rows[section_number - 1]
    if section["name"] != b".text":
        raise ValueError(
            f"symbol {function_symbol['name']} is in {section['name']!r}, not .text"
        )
    if int(section["characteristics"]) & IMAGE_SCN_LNK_NRELOC_OVFL:
        raise ValueError("COFF relocation-overflow sections are unsupported")

    value = int(function_symbol["value"])
    raw_pointer = int(section["raw_pointer"])
    raw_size = int(section["raw_size"])
    code = bytearray(data[raw_pointer + value : raw_pointer + raw_size])
    reloc_pointer = int(section["reloc_pointer"])
    for reloc_index in range(int(section["reloc_count"])):
        offset = reloc_pointer + reloc_index * 10
        virtual_address, symbol_index, relocation_type = struct.unpack_from(
            "<IIH", data, offset
        )
        field_offset = virtual_address - value
        if not 0 <= field_offset < function_size:
            continue
        if field_offset > len(code) - 4:
            raise ValueError("COFF relocation extends beyond function section")
        target_symbol = symbols.get(symbol_index)
        if target_symbol is None:
            raise ValueError(f"relocation references invalid symbol index {symbol_index}")
        target_symbol_name = str(target_symbol["name"])

        if relocation_type == IMAGE_REL_I386_DIR32:
            target_section_number = int(target_symbol["section_number"])
            if target_section_number == section_number:
                # VC8 emits switch jump tables into the function's COMDAT and
                # references both the table and its local labels through DIR32
                # relocations.  These are code addresses, not allowlisted data
                # literals.  Model the image linker by preserving the local
                # symbol's offset from the function entry.
                raw_addend = struct.unpack_from("<I", code, field_offset)[0]
                addend = (
                    raw_addend
                    if raw_addend < (1 << 31)
                    else raw_addend - (1 << 32)
                )
                destination = (
                    function_address
                    + int(target_symbol["value"])
                    - value
                    + addend
                )
                struct.pack_into("<I", code, field_offset, destination & 0xFFFFFFFF)
                continue
            raw_addend = struct.unpack_from("<I", code, field_offset)[0]
            data_target_key = dir32_target_key(
                target_symbol_name, data_target_overrides, raw_addend
            )
            if data_target_key not in data_targets:
                raise ValueError(
                    f"unknown absolute data relocation: {target_symbol_name}"
                )
            destination, literal, allowed_addends, validation = data_targets[
                data_target_key
            ]
            if raw_addend not in allowed_addends:
                raise ValueError(
                    f"DIR32 relocation for {target_symbol_name} has unverified "
                    f"addend {raw_addend:#x}"
                )
            addend = (
                raw_addend
                if raw_addend < (1 << 31)
                else raw_addend - (1 << 32)
            )

            if validation == "address":
                if target_section_number != 0 and not (
                    0 < target_section_number <= len(section_rows)
                ):
                    raise ValueError("DIR32 target has an invalid object section")
            elif target_section_number == 0:
                if not target_symbol_name.startswith("__imp__") or len(literal) != 4:
                    raise ValueError(
                        f"undefined DIR32 target {target_symbol_name} is not an "
                        "allowlisted four-byte import"
                    )
            else:
                if not 0 < target_section_number <= len(section_rows):
                    raise ValueError("DIR32 target has an invalid object section")
                target_section = section_rows[target_section_number - 1]
                target_value = int(target_symbol["value"])
                object_value = target_value + addend
                if int(target_section["characteristics"]) & IMAGE_SCN_CNT_UNINITIALIZED_DATA:
                    # VC8 may encode an explicitly allowlisted negative
                    # displacement from a BSS array symbol. BSS has no object
                    # bytes; the resolved target literal is still checked below.
                    bss_size = int(target_section["raw_size"])
                    bss_pointer = int(target_section["raw_pointer"])
                    if (
                        bss_pointer != 0
                        or object_value + len(literal) > bss_size
                        or any(literal)
                    ):
                        raise ValueError(
                            f"unverified nonzero/unexpected BSS relocation for "
                            f"{target_symbol_name}"
                        )
                    object_literal = bytes(len(literal))
                else:
                    if object_value < 0 or object_value + len(literal) > int(
                        target_section["raw_size"]
                    ):
                        raise ValueError(
                            f"DIR32 relocation for {target_symbol_name} selects "
                            f"bytes outside its initialized COFF section"
                        )
                    literal_offset = (
                        int(target_section["raw_pointer"]) + object_value
                    )
                    object_literal = data[
                        literal_offset : literal_offset + len(literal)
                    ]
                if object_literal != literal:
                    raise ValueError(
                        f"object bytes for {target_symbol_name}+{addend:#x} do not "
                        "match known literal"
                    )
            if target_bytes(destination + addend, len(literal)) != literal:
                raise ValueError(
                    f"target bytes for {target_symbol_name}+{addend:#x} no longer "
                    "match mapping"
                )
            struct.pack_into(
                "<I", code, field_offset, (destination + addend) & 0xFFFFFFFF
            )
            continue

        if relocation_type != IMAGE_REL_I386_REL32:
            raise ValueError(
                f"unsupported code relocation {relocation_type:#x} at +{field_offset:#x}"
            )
        if rel32_operand_kind(code, field_offset) is None:
            raise ValueError(
                f"REL32 at +{field_offset:#x} is not an external CALL/JMP/Jcc"
            )
        target_name = relocation_target_key(target_symbol_name, targets)
        if target_name not in targets:
            locality = (
                "local" if int(target_symbol["section_number"]) != 0 else "external"
            )
            raise ValueError(
                f"unknown {locality} call/jump target: {target_name}"
            )
        addend = struct.unpack_from("<i", code, field_offset)[0]
        displacement = (
            targets[target_name]
            + addend
            - (function_address + field_offset + 4)
        )
        if not -(1 << 31) <= displacement < (1 << 31):
            raise ValueError("REL32 displacement overflow")
        struct.pack_into("<i", code, field_offset, displacement)
    return bytes(code)


def main() -> int:
    parser = argparse.ArgumentParser(
        description="Compare one VC8 COFF function with target executable bytes."
    )
    parser.add_argument(
        "--contiguous-span",
        action="store_true",
        help=(
            "compare entry through span_end, including bytes omitted from "
            "a provisional analysis function body"
        ),
    )
    parser.add_argument(
        "--symbol-base",
        help="override the ledger name used to select a COFF function symbol",
    )
    parser.add_argument(
        "--rel32-target",
        action="append",
        default=[],
        metavar="NAME=ADDRESS",
        help="add a probe-only REL32 symbol mapping without changing the ledger",
    )
    parser.add_argument(
        "--dir32-target",
        action="append",
        default=[],
        metavar="COFF_SYMBOL=ALLOWLIST_KEY",
        help=(
            "map one function-local DIR32 symbol or symbol+0xADDEND to a "
            "separately verified "
            "config/reccmp-relocations.csv key"
        ),
    )
    parser.add_argument(
        "--json",
        action="store_true",
        help="emit one machine-readable comparison result",
    )
    parser.add_argument("address")
    parser.add_argument("object")
    args = parser.parse_args()

    try:
        address = canonical(args.address)
    except ValueError as error:
        if args.json:
            print(json.dumps({
                "schema_version": 1,
                "result": "error",
                "address": args.address,
                "failure": {"category": "inventory.address_invalid", "message": str(error)},
            }, indent=2))
            return 1
        raise

    obj = Path(args.object).resolve()
    report: dict[str, object] = {
        "schema_version": 1,
        "result": "error",
        "address": address,
        "object": str(obj),
        "comparison": {
            "boundary": "contiguous_span" if args.contiguous_span else "ledger_size",
            "size": None,
        },
        "target_size": None,
        "object_section_tail_size": None,
        "object_size_kind": "section_tail",
        "first_mismatch": None,
        "failure": None,
    }

    try:
        report["target_executable_sha256"] = verify_target()
        with FUNCTIONS.open(newline="", encoding="utf-8") as stream:
            row = next(
                (item for item in csv.DictReader(stream) if item["address"] == address),
                None,
            )
        if row is None:
            report["result"] = "error"
            report["failure"] = {
                "category": "inventory.address_absent",
                "message": f"address is absent from function inventory: {address}",
            }
            if args.json:
                print(json.dumps(report, indent=2))
            else:
                print(report["failure"]["message"], file=sys.stderr)  # type: ignore[index]
            return 1

        with KNOWN_SYMBOLS.open(newline="", encoding="utf-8") as stream:
            known = next(
                (item for item in csv.DictReader(stream) if item["address"] == address),
                None,
            )

        size = int(row["size"])
        if args.contiguous_span:
            size = int(row["span_end"], 16) - int(address, 16) + 1
        expected = target_bytes(int(address, 16), size)
        symbol_base = (
            args.symbol_base
            or row["proposed_name"]
            or (known and known["name"])
            or row["current_name"]
        )
        report["symbol_base"] = symbol_base
        comparison = report["comparison"]
        assert isinstance(comparison, dict)
        comparison["size"] = size
        report["target_size"] = size

        targets = known_targets()
        for mapping in args.rel32_target:
            name, separator, raw_address = mapping.partition("=")
            if not separator or not name or not raw_address:
                parser.error(f"invalid --rel32-target mapping: {mapping!r}")
            targets[name] = int(raw_address, 0)
        data_target_overrides: dict[str, str] = {}
        for mapping in args.dir32_target:
            name, separator, allowlist_key = mapping.partition("=")
            if not separator or not name or not allowlist_key:
                parser.error(f"invalid --dir32-target mapping: {mapping!r}")
            data_target_overrides[name] = allowlist_key
        actual_section = coff_symbol_bytes(
            obj,
            symbol_base,
            int(address, 16),
            size,
            targets,
            known_data_targets(),
            data_target_overrides,
        )
        actual = actual_section[:size]
        mismatch = first_mismatch(expected, actual, int(address, 16))
        exact = actual == expected and len(actual) == size
        report.update(
            {
                "result": "exact" if exact else "mismatch",
                "object_section_tail_size": len(actual_section),
                "first_mismatch": mismatch,
                "target_sha256": hashlib.sha256(expected).hexdigest(),
                "object_compared_sha256": hashlib.sha256(actual).hexdigest(),
            }
        )
        if args.json:
            print(json.dumps(report, indent=2))
        else:
            print(f"function: {symbol_base} ({address}, {size} bytes)")
            print(f"expected: {expected.hex(' ')}")
            print(f"actual:   {actual.hex(' ')}")
            if len(actual_section) != size:
                print(
                    "note: object .text section tail size is "
                    f"{len(actual_section)} bytes"
                )
            print("result: exact function-byte match" if exact else "result: mismatch")
        return 0 if exact else 1
    except (OSError, ValueError, struct.error) as error:
        result, failure = failure_record(error)
        report["result"] = result
        report["failure"] = failure
        if args.json:
            print(json.dumps(report, indent=2))
        else:
            print(f"error: {failure['category']}: {failure['message']}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    raise SystemExit(main())
