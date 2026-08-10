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
    if name.startswith("?"):
        return name[1:].split("@", 1)[0]
    if name.startswith("_"):
        name = name[1:]
    return name.split("@", 1)[0]


def known_targets() -> dict[str, int]:
    targets: dict[str, int] = {}
    with KNOWN_SYMBOLS.open(newline="", encoding="utf-8") as stream:
        for row in csv.DictReader(stream):
            name = row["name"]
            if name in targets:
                raise ValueError(f"duplicate known symbol name: {name}")
            targets[name] = int(row["address"], 16)
    return targets


def known_data_targets() -> dict[str, tuple[int, bytes, frozenset[int]]]:
    targets: dict[str, tuple[int, bytes, frozenset[int]]] = {}
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
            targets[name] = (int(row["address"], 16), data, addends)
    return targets


def coff_symbol_bytes(
    path: Path,
    symbol_base: str,
    function_address: int,
    function_size: int,
    targets: dict[str, int],
    data_targets: dict[str, tuple[int, bytes, frozenset[int]]],
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
            and (name == symbol_base or name.startswith(f"?{symbol_base}@"))
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
            if target_symbol_name not in data_targets:
                raise ValueError(
                    f"unknown absolute data relocation: {target_symbol_name}"
                )
            target_section_number = int(target_symbol["section_number"])
            if not 0 < target_section_number <= len(section_rows):
                raise ValueError("DIR32 target is not defined in this object")
            destination, literal, allowed_addends = data_targets[target_symbol_name]
            target_section = section_rows[target_section_number - 1]
            target_value = int(target_symbol["value"])
            addend = struct.unpack_from("<I", code, field_offset)[0]
            if addend not in allowed_addends:
                raise ValueError(
                    f"DIR32 relocation for {target_symbol_name} has unverified "
                    f"addend {addend:#x}"
                )
            if int(target_section["characteristics"]) & IMAGE_SCN_CNT_UNINITIALIZED_DATA:
                bss_size = int(target_section["raw_size"])
                bss_pointer = int(target_section["raw_pointer"])
                if (
                    bss_pointer != 0
                    or target_value + addend + len(literal) > bss_size
                    or any(literal)
                ):
                    raise ValueError(
                        f"unverified nonzero/unexpected BSS relocation for "
                        f"{target_symbol_name}"
                    )
                object_literal = bytes(len(literal))
            else:
                literal_offset = (
                    int(target_section["raw_pointer"]) + target_value + addend
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
            struct.pack_into("<I", code, field_offset, destination + addend)
            continue

        if relocation_type != IMAGE_REL_I386_REL32:
            raise ValueError(
                f"unsupported code relocation {relocation_type:#x} at +{field_offset:#x}"
            )
        if field_offset == 0 or code[field_offset - 1] not in (0xE8, 0xE9):
            raise ValueError(
                f"REL32 at +{field_offset:#x} is not an external CALL/JMP"
            )
        if int(target_symbol["section_number"]) != 0:
            raise ValueError("REL32 target is not an undefined external symbol")
        target_name = coff_short_name(target_symbol_name)
        if target_name not in targets:
            raise ValueError(f"unknown external call/jump target: {target_name}")
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
    symbol_base = row["proposed_name"] or (known and known["name"]) or row["current_name"]
    actual_section = coff_symbol_bytes(
        obj,
        symbol_base,
        int(address, 16),
        size,
        known_targets(),
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
