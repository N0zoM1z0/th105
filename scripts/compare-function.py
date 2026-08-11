#!/usr/bin/env python3
"""Compare one function's COFF COMDAT section with the original bytes."""

from __future__ import annotations

import csv
import argparse
from pathlib import Path
import struct
import sys


ROOT = Path(__file__).resolve().parents[1]
TARGET = ROOT / "resources" / "th105.exe"
FUNCTIONS = ROOT / "config" / "functions.csv"
KNOWN_SYMBOLS = ROOT / "config" / "known-symbols.csv"
KNOWN_RELOCATIONS = ROOT / "config" / "reccmp-relocations.csv"
IMAGE_REL_I386_DIR32 = 0x0006
IMAGE_REL_I386_REL32 = 0x0014
IMAGE_SCN_CNT_UNINITIALIZED_DATA = 0x00000080
IMAGE_SCN_LNK_NRELOC_OVFL = 0x01000000


def canonical(value: str) -> str:
    return f"0x{int(value, 16):08X}"


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
) -> bytes:
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
            if target_symbol_name not in data_targets:
                raise ValueError(
                    f"unknown absolute data relocation: {target_symbol_name}"
                )
            destination, literal, allowed_addends, validation = data_targets[
                target_symbol_name
            ]
            raw_addend = struct.unpack_from("<I", code, field_offset)[0]
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
        if field_offset == 0 or code[field_offset - 1] not in (0xE8, 0xE9):
            raise ValueError(
                f"REL32 at +{field_offset:#x} is not an external CALL/JMP"
            )
        target_name = coff_short_name(target_symbol_name)
        if target_name not in targets and target_symbol_name.startswith("?"):
            # Existing ledger aliases commonly use the unqualified source
            # member name, while newer rows may use Class_member. Prefer the
            # class-qualified spelling above, but retain the proven legacy
            # fallback for ordinary decorated member functions.
            unqualified_name = target_symbol_name[1:].split("@", 1)[0]
            if unqualified_name in targets:
                target_name = unqualified_name
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
            "Ghidra's non-contiguous function body"
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
    parser.add_argument("address")
    parser.add_argument("object")
    args = parser.parse_args()

    address = canonical(args.address)
    obj = Path(args.object).resolve()

    with FUNCTIONS.open(newline="", encoding="utf-8") as stream:
        row = next((item for item in csv.DictReader(stream) if item["address"] == address), None)
    if row is None:
        print(f"address is absent from function inventory: {address}", file=sys.stderr)
        return 1

    with KNOWN_SYMBOLS.open(newline="", encoding="utf-8") as stream:
        known = next((item for item in csv.DictReader(stream) if item["address"] == address), None)

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
    targets = known_targets()
    for mapping in args.rel32_target:
        name, separator, raw_address = mapping.partition("=")
        if not separator or not name or not raw_address:
            parser.error(f"invalid --rel32-target mapping: {mapping!r}")
        targets[name] = int(raw_address, 0)
    actual_section = coff_symbol_bytes(
        obj,
        symbol_base,
        int(address, 16),
        size,
        targets,
        known_data_targets(),
    )
    actual = actual_section[:size]
    print(f"function: {symbol_base} ({address}, {size} bytes)")
    print(f"expected: {expected.hex(' ')}")
    print(f"actual:   {actual.hex(' ')}")
    if len(actual_section) != size:
        print(f"note: object .text size is {len(actual_section)} bytes")
    if actual != expected or len(actual) != size:
        print("result: mismatch")
        return 1
    print("result: exact function-byte match")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
