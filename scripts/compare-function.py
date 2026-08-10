#!/usr/bin/env python3
"""Compare one function's COFF COMDAT section with the original bytes."""

from __future__ import annotations

import csv
from pathlib import Path
import struct
import sys


ROOT = Path(__file__).resolve().parents[1]
TARGET = ROOT / "resources" / "th105.exe"
FUNCTIONS = ROOT / "config" / "functions.csv"
KNOWN_SYMBOLS = ROOT / "config" / "known-symbols.csv"


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
            file_offset = raw_pointer + (rva - virtual_address)
            return data[file_offset : file_offset + size]
    raise ValueError(f"address {address:#x} is not in a PE section")


def coff_symbol_bytes(path: Path, symbol_base: str) -> bytes:
    data = path.read_bytes()
    section_count = struct.unpack_from("<H", data, 2)[0]
    symbol_pointer, symbol_count = struct.unpack_from("<II", data, 8)
    optional_size = struct.unpack_from("<H", data, 16)[0]
    sections = 20 + optional_size
    string_table = symbol_pointer + symbol_count * 18
    section_rows: list[tuple[bytes, int, int]] = []
    for index in range(section_count):
        offset = sections + 40 * index
        name = data[offset : offset + 8].rstrip(b"\0")
        raw_size, raw_pointer = struct.unpack_from("<II", data, offset + 16)
        section_rows.append((name, raw_pointer, raw_size))

    index = 0
    while index < symbol_count:
        offset = symbol_pointer + index * 18
        raw_name = data[offset : offset + 8]
        if raw_name[:4] == b"\0\0\0\0":
            name_offset = struct.unpack_from("<I", raw_name, 4)[0]
            start = string_table + name_offset
            end = data.find(b"\0", start)
            name = data[start:end].decode("ascii", errors="replace")
        else:
            name = raw_name.rstrip(b"\0").decode("ascii", errors="replace")
        value = struct.unpack_from("<I", data, offset + 8)[0]
        section_number = struct.unpack_from("<h", data, offset + 12)[0]
        auxiliary = data[offset + 17]
        if (
            0 < section_number <= len(section_rows)
            and (name == symbol_base or name.startswith(f"?{symbol_base}@"))
        ):
            section_name, raw_pointer, raw_size = section_rows[section_number - 1]
            if section_name != b".text":
                raise ValueError(f"symbol {name} is in {section_name!r}, not .text")
            return data[raw_pointer + value : raw_pointer + raw_size]
        index += 1 + auxiliary
    raise ValueError(f"{path} has no function symbol for {symbol_base}")


def main() -> int:
    if len(sys.argv) != 3:
        print("usage: scripts/compare-function.py 0xADDRESS build/file.obj", file=sys.stderr)
        return 2
    address = canonical(sys.argv[1])
    obj = Path(sys.argv[2]).resolve()

    with FUNCTIONS.open(newline="", encoding="utf-8") as stream:
        row = next((item for item in csv.DictReader(stream) if item["address"] == address), None)
    if row is None:
        print(f"address is absent from function inventory: {address}", file=sys.stderr)
        return 1

    with KNOWN_SYMBOLS.open(newline="", encoding="utf-8") as stream:
        known = next((item for item in csv.DictReader(stream) if item["address"] == address), None)

    size = int(row["size"])
    expected = target_bytes(int(address, 16), size)
    symbol_base = row["proposed_name"] or (known and known["name"]) or row["current_name"]
    actual_section = coff_symbol_bytes(obj, symbol_base)
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
