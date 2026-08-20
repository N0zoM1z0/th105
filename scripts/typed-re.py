#!/usr/bin/env python3
"""Emit a target-pinned TH105 instruction/ABI evidence packet from IDA."""

from __future__ import annotations

import argparse
import asyncio
import csv
import hashlib
import json
from pathlib import Path
import struct
import subprocess
import tomllib
from typing import Any

from ida_mcp_client import IdaMcpError, call_json, open_session, require_target


ROOT = Path(__file__).resolve().parents[1]
TARGET = ROOT / "resources" / "th105.exe"


def target_bytes(data: bytes, address: int, size: int) -> bytes:
    pe = struct.unpack_from("<I", data, 0x3C)[0]
    section_count = struct.unpack_from("<H", data, pe + 6)[0]
    optional_size = struct.unpack_from("<H", data, pe + 20)[0]
    image_base = struct.unpack_from("<I", data, pe + 52)[0]
    sections = pe + 24 + optional_size
    rva = address - image_base
    for index in range(section_count):
        offset = sections + index * 40
        virtual_size, section_rva, raw_size, raw_offset = struct.unpack_from(
            "<IIII", data, offset + 8
        )
        if section_rva <= rva and rva + size <= section_rva + max(virtual_size, raw_size):
            relative = rva - section_rva
            raw_available = max(0, min(size, raw_size - relative))
            return data[raw_offset + relative : raw_offset + relative + raw_available] + bytes(
                size - raw_available
            )
    raise ValueError(f"range {address:#x}+{size:#x} is outside the PE image")


def ledger_row(address: int) -> dict[str, str]:
    with (ROOT / "config" / "functions.csv").open(newline="", encoding="utf-8") as stream:
        matches = [row for row in csv.DictReader(stream) if int(row["address"], 0) == address]
    if len(matches) != 1:
        raise ValueError(f"address 0x{address:08X} is absent or duplicated in functions.csv")
    return matches[0]


def verify_local_target() -> tuple[bytes, dict[str, Any]]:
    with (ROOT / "config" / "target.toml").open("rb") as stream:
        manifest = tomllib.load(stream)
    data = TARGET.read_bytes()
    expected = manifest["target"]
    if len(data) != expected["size"] or hashlib.sha256(data).hexdigest() != expected["sha256"]:
        raise ValueError("resources/th105.exe does not match config/target.toml")
    return data, manifest


async def collect(address: int, include_decompile: bool) -> dict[str, Any]:
    canonical = f"0x{address:08X}"
    async with open_session() as (session, _initialized):
        metadata = await require_target(session)
        calls = {
            "function": ("get_function_by_address", {"address": canonical}),
            "disassembly": ("disassemble_function", {"start_address": canonical}),
            "callers": ("get_callers", {"function_address": canonical}),
            "callees": ("get_callees", {"function_address": canonical}),
        }
        if include_decompile:
            calls["decompiler"] = ("decompile_function", {"address": canonical})
        output: dict[str, Any] = {"ida_target": metadata}
        for key, (tool, arguments) in calls.items():
            try:
                output[key] = await call_json(session, tool, arguments)
            except IdaMcpError as exc:
                output[key] = {
                    "available": False,
                    "reason": exc.reason,
                    "error": str(exc),
                }
        return output


def local_disassembly(address: int, size: int) -> str:
    completed = subprocess.run(
        [
            "objdump",
            "-D",
            "-Mintel,i386",
            f"--start-address={address:#x}",
            f"--stop-address={address + size:#x}",
            str(TARGET),
        ],
        cwd=ROOT,
        check=True,
        capture_output=True,
        text=True,
    )
    return completed.stdout


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("address", type=lambda raw: int(raw, 0))
    parser.add_argument("--decompile", action="store_true")
    parser.add_argument("--max-bytes", type=int, default=512)
    parser.add_argument("--json", action="store_true")
    args = parser.parse_args()
    try:
        data, manifest = verify_local_target()
        row = ledger_row(args.address)
        size = int(row["size"], 0)
        capture_size = min(size, args.max_bytes)
        ida = asyncio.run(collect(args.address, args.decompile))
        packet = {
            "schema": "th105-typed-re-v1",
            "target_sha256": manifest["target"]["sha256"],
            "address": row["address"],
            "candidate": {
                "size": size,
                "span_end": row["span_end"],
                "name": row["current_name"],
                "status": row["status"],
                "boundary_authority": "provisional_ida_candidate",
            },
            "exact_observations": {
                "captured_target_bytes": capture_size,
                "candidate_bytes_truncated": capture_size != size,
                "target_hex": target_bytes(data, args.address, capture_size).hex(),
                "objdump": local_disassembly(args.address, capture_size),
                **ida,
            },
            "interpretation_rule": (
                "IDA names/types/extents and decompiler output are hypotheses; "
                "reconcile complete target control flow before ledger changes"
            ),
        }
    except (
        IdaMcpError,
        OSError,
        KeyError,
        TypeError,
        ValueError,
        struct.error,
        subprocess.CalledProcessError,
    ) as exc:
        print(json.dumps({"ok": False, "error": str(exc)}, indent=2))
        return 1
    print(json.dumps(packet, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
