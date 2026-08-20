#!/usr/bin/env python3
"""Verify the registered IDA MCP path and attest the exact TH105 1.06a image."""

from __future__ import annotations

import argparse
import asyncio
import json
from pathlib import Path
import struct
import tomllib

from ida_mcp_client import (
    DEFAULT_SERVER,
    IdaMcpError,
    REQUIRED_READ_TOOLS,
    call_json,
    open_session,
    parse_int,
    require_target,
)


ROOT = Path(__file__).resolve().parents[1]
TARGET_PATH = ROOT / "resources" / "th105.exe"
SAMPLE_ADDRESSES = (0x00401000, 0x0068B9D2, 0x00420000, 0x00570000, 0x006B0000)


def pe_bytes_at(image: bytes, address: int, size: int) -> bytes:
    if len(image) < 0x40 or image[:2] != b"MZ":
        raise IdaMcpError("target_mismatch", "canonical target is not a PE image")
    pe_offset = struct.unpack_from("<I", image, 0x3C)[0]
    if image[pe_offset : pe_offset + 4] != b"PE\0\0":
        raise IdaMcpError("target_mismatch", "canonical target lacks a PE signature")
    section_count = struct.unpack_from("<H", image, pe_offset + 6)[0]
    optional_size = struct.unpack_from("<H", image, pe_offset + 20)[0]
    optional = pe_offset + 24
    image_base = struct.unpack_from("<I", image, optional + 28)[0]
    section_table = optional + optional_size
    rva = address - image_base
    for index in range(section_count):
        offset = section_table + index * 40
        virtual_size, section_rva, raw_size, raw_offset = struct.unpack_from(
            "<IIII", image, offset + 8
        )
        relative = rva - section_rva
        if 0 <= relative and relative + size <= raw_size:
            return image[raw_offset + relative : raw_offset + relative + size]
        if 0 <= relative < virtual_size:
            raise IdaMcpError(
                "target_mismatch", f"attestation address {address:#x} has no raw bytes"
            )
    raise IdaMcpError("target_mismatch", f"attestation address {address:#x} is unmapped")


def parse_ida_bytes(value: object) -> bytes:
    if not isinstance(value, str):
        raise IdaMcpError("tool_error", f"unexpected IDA byte payload: {value!r}")
    try:
        return bytes(int(token, 16) for token in value.split())
    except ValueError as exc:
        raise IdaMcpError("tool_error", f"invalid IDA byte payload: {value!r}") from exc


async def check(server_name: str) -> dict[str, object]:
    with (ROOT / "config" / "target.toml").open("rb") as stream:
        manifest = tomllib.load(stream)
    expected_entry = parse_int(manifest["pe"]["entry_point"])
    image = TARGET_PATH.read_bytes()

    async with open_session(server_name) as (session, initialized):
        listed = await session.list_tools()
        names = {tool.name for tool in listed.tools}
        missing = sorted(set(REQUIRED_READ_TOOLS) - names)
        if missing:
            raise IdaMcpError("missing_tool", f"IDA MCP missing required tools: {missing}")

        connection = await call_json(session, "check_connection", {})
        if not isinstance(connection, str) or not connection.startswith("Successfully connected"):
            raise IdaMcpError("unavailable", f"IDA plugin is not connected: {connection!r}")
        metadata = await require_target(session)

        raw_entries = await call_json(session, "get_entry_points", {})
        entries = raw_entries if isinstance(raw_entries, list) else [raw_entries]
        if not any(
            isinstance(row, dict) and parse_int(row.get("address")) == expected_entry
            for row in entries
        ):
            raise IdaMcpError(
                "target_mismatch", f"IDA entry point does not include {expected_entry:#x}: {raw_entries!r}"
            )

        samples: list[dict[str, object]] = []
        for address in SAMPLE_ADDRESSES:
            expected = pe_bytes_at(image, address, 16)
            actual = parse_ida_bytes(
                await call_json(
                    session,
                    "read_memory_bytes",
                    {"memory_address": f"0x{address:08X}", "size": 16},
                )
            )
            if actual != expected:
                raise IdaMcpError(
                    "target_mismatch", f"IDA mapped bytes differ at 0x{address:08X}"
                )
            samples.append({"address": f"0x{address:08X}", "bytes": expected.hex()})

        first_page = await call_json(
            session, "list_functions", {"offset": 0, "count": 1}
        )
        probe_address = "0x00401000"
        function = await call_json(
            session, "get_function_by_address", {"address": probe_address}
        )
        disassembly = await call_json(
            session, "disassemble_function", {"start_address": probe_address}
        )
        decompiler = await call_json(
            session, "decompile_function", {"address": probe_address}
        )
        callers = await call_json(
            session, "get_callers", {"function_address": probe_address}
        )
        callees = await call_json(
            session, "get_callees", {"function_address": probe_address}
        )
        if not isinstance(disassembly, dict) or not disassembly.get("lines"):
            raise IdaMcpError("tool_error", "IDA disassembly semantic probe is empty")
        if not isinstance(decompiler, str) or not decompiler.strip():
            raise IdaMcpError("tool_error", "IDA decompiler semantic probe is empty")
        return {
            "ok": True,
            "protocol_version": initialized.protocolVersion,
            "mcp_server": initialized.serverInfo.name,
            "tool_count": len(names),
            "metadata": metadata,
            "entry_points": entries,
            "mapped_byte_attestation": samples,
            "function_inventory_probe": first_page,
            "semantic_probe": {
                "address": probe_address,
                "function": function,
                "disassembly_lines": len(disassembly["lines"]),
                "decompiler_characters": len(decompiler),
                "callers": len(callers) if isinstance(callers, list) else None,
                "callees": len(callees) if isinstance(callees, list) else None,
            },
            "boundary_rule": "IDA function extents are provisional until target control flow and comparison agree",
        }


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--server", default=DEFAULT_SERVER)
    args = parser.parse_args()
    try:
        output = asyncio.run(check(args.server))
    except (OSError, KeyError, TypeError, ValueError, tomllib.TOMLDecodeError) as exc:
        print(json.dumps({"ok": False, "reason": "target_mismatch", "error": str(exc)}, indent=2))
        raise SystemExit(1) from exc
    except IdaMcpError as exc:
        print(json.dumps({"ok": False, "reason": exc.reason, "error": str(exc)}, indent=2))
        raise SystemExit(1) from exc
    print(json.dumps(output, indent=2))


if __name__ == "__main__":
    main()
