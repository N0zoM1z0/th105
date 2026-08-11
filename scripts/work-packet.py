#!/usr/bin/env python3
"""Capture one hash-bound, ledger-bounded TH105 reverse-engineering work packet."""

from __future__ import annotations

import argparse
import asyncio
import csv
from datetime import datetime, timezone
import hashlib
import json
import os
from pathlib import Path
import subprocess
import sys
import tomllib
from typing import Any

from mcp import ClientSession, StdioServerParameters
from mcp.client.stdio import stdio_client

from ida_mcp_client import (
    DEFAULT_SERVER,
    IdaMcpError,
    call_json,
    open_session,
    parse_int,
    require_target,
)
from workflow_manifest import (
    MANIFEST,
    ROOT,
    canonical_address,
    file_sha256,
    load_manifest,
    repository_path,
    unit_for_address,
    unit_input_digest,
)


FUNCTIONS = ROOT / "config" / "functions.csv"
CLAIMS = ROOT / "config" / "claims.csv"
TARGET = ROOT / "resources" / "th105.exe"
CACHE_ROOT = ROOT / ".analysis" / "work-packets"
IDA_TOOLS = {
    "check_connection",
    "get_metadata",
    "get_function_by_address",
    "disassemble_function",
    "decompile_function",
    "get_xrefs_to",
    "get_callers",
    "get_callees",
}
GHIDRA_TOOLS = {
    "get_metadata",
    "get_function_by_address",
    "disassemble_function",
    "decompile_function",
    "get_function_callers",
    "get_function_callees",
    "get_function_xrefs",
}


def read_rows(path: Path) -> list[dict[str, str]]:
    with path.open(newline="", encoding="utf-8") as stream:
        return list(csv.DictReader(stream))


def target_identity() -> dict[str, object]:
    with (ROOT / "config" / "target.toml").open("rb") as stream:
        config = tomllib.load(stream)
    target = config["target"]
    pe = config["pe"]
    actual_sha256 = file_sha256(TARGET)
    if actual_sha256 != target["sha256"]:
        raise RuntimeError(
            f"target SHA-256 mismatch: got {actual_sha256}, expected {target['sha256']}"
        )
    if TARGET.stat().st_size != target["size"]:
        raise RuntimeError("target file size mismatch")
    return {
        "sha256": target["sha256"],
        "md5": target["md5"],
        "filesize": target["size"],
        "image_base": pe["image_base"],
        "region": target["region"],
        "version": target["version"],
    }


def core_packet(address: str) -> dict[str, object] | None:
    completed = subprocess.run(
        [
            sys.executable,
            str(ROOT / "scripts" / "core-worklist.py"),
            "--explain",
            address,
            "--json",
        ],
        cwd=ROOT,
        capture_output=True,
        text=True,
    )
    if completed.returncode == 2:
        return None
    if completed.returncode != 0:
        raise RuntimeError(completed.stderr.strip() or completed.stdout.strip())
    value = json.loads(completed.stdout)
    if not isinstance(value, dict):
        raise RuntimeError("core-worklist returned an invalid packet")
    return value


def parse_backend_integer(raw: object) -> int:
    if isinstance(raw, str):
        value = raw.strip()
        try:
            return int(value, 0)
        except ValueError:
            return int(value, 16)
    return parse_int(raw)


def canonical_backend_boundary(
    raw: object,
) -> tuple[str | None, int | None, str | None]:
    if not isinstance(raw, dict):
        return None, None, None
    try:
        address = f"0x{parse_backend_integer(raw.get('address') or raw.get('entry_point')):08X}"
        if raw.get("size") is not None:
            return address, parse_backend_integer(raw["size"]), "backend_function_size"
        start = parse_backend_integer(raw.get("body_start"))
        end = parse_backend_integer(raw.get("body_end"))
        return address, end - start + 1, "backend_body_span"
    except (TypeError, ValueError):
        return None, None, None


async def collect_ida(address: str, server: str) -> dict[str, object]:
    async with open_session(server) as (session, initialized):
        names = {tool.name for tool in (await session.list_tools()).tools}
        missing = sorted(IDA_TOOLS - names)
        if missing:
            raise IdaMcpError("missing_tool", f"IDA MCP missing required tools: {missing}")
        connection = await call_json(session, "check_connection", {})
        if not isinstance(connection, str) or not connection.startswith(
            "Successfully connected"
        ):
            raise IdaMcpError("unavailable", f"IDA plugin is not connected: {connection!r}")
        before = await require_target(session)
        raw = {
            "function": await call_json(
                session, "get_function_by_address", {"address": address}
            ),
            "decompile": await call_json(
                session, "decompile_function", {"address": address}
            ),
            "disassembly": await call_json(
                session, "disassemble_function", {"start_address": address}
            ),
            "xrefs_to": await call_json(session, "get_xrefs_to", {"address": address}),
            "callers": await call_json(
                session, "get_callers", {"function_address": address}
            ),
            "callees": await call_json(
                session, "get_callees", {"function_address": address}
            ),
        }
        after = await require_target(session)
        identity_fields = ("sha256", "md5", "base", "filesize", "path", "module")
        if any(before.get(field) != after.get(field) for field in identity_fields):
            raise IdaMcpError(
                "target_mismatch", "IDA target metadata changed during packet capture"
            )
        return {
            "backend": "ida",
            "advisory": True,
            "protocol_version": initialized.protocolVersion,
            "server": initialized.serverInfo.name,
            "metadata_pre": before,
            "metadata_post": after,
            "backend_raw": raw,
            "limitations": [
                "IDA function chunks are advisory; the ledger boundary is authoritative.",
                "IDA MCP exposes no IDB UUID or analysis revision for strong cache freshness.",
                "get_callees substitutes for outgoing xrefs; completeness is backend-defined.",
            ],
        }


def decode_mcp_result(result: Any, tool: str) -> Any:
    if result.isError:
        raise RuntimeError(f"Ghidra MCP tool failed: {tool}")
    texts = [item.text for item in result.content if item.type == "text"]
    if len(texts) == 1:
        try:
            return json.loads(texts[0])
        except json.JSONDecodeError:
            return texts[0]
    values: list[object] = []
    for item in texts:
        try:
            values.append(json.loads(item))
        except json.JSONDecodeError:
            values.append(item)
    return values


async def collect_ghidra(address: str) -> dict[str, object]:
    server = StdioServerParameters(
        command="bash",
        args=[str(ROOT / "scripts" / "mcp-ghidra.sh")],
        cwd=ROOT,
        env=os.environ.copy(),
    )
    async with stdio_client(server) as (read_stream, write_stream):
        async with ClientSession(read_stream, write_stream) as session:
            initialized = await session.initialize()
            names = {tool.name for tool in (await session.list_tools()).tools}
            missing = sorted(GHIDRA_TOOLS - names)
            if missing:
                raise RuntimeError(f"Ghidra MCP missing required tools: {missing}")

            async def call(tool: str, arguments: dict[str, object]) -> object:
                if "program" not in arguments:
                    raise RuntimeError(f"strict Ghidra call lacks program selector: {tool}")
                result = await session.call_tool(tool, arguments)
                return decode_mcp_result(result, tool)

            selector = {"program": "th105.exe"}
            before = await call("get_metadata", dict(selector))
            if not isinstance(before, dict) or before.get("program_name") != "th105.exe":
                raise RuntimeError(f"unexpected Ghidra program metadata: {before!r}")
            raw = {
                "function": await call(
                    "get_function_by_address", {"address": address, **selector}
                ),
                "decompile": await call(
                    "decompile_function", {"address": address, **selector}
                ),
                "disassembly": await call(
                    "disassemble_function", {"address": address, **selector}
                ),
                "xrefs": await call(
                    "get_function_xrefs",
                    {"address": address, "offset": 0, "limit": 100, **selector},
                ),
                "callers": await call(
                    "get_function_callers",
                    {"address": address, "offset": 0, "limit": 100, **selector},
                ),
                "callees": await call(
                    "get_function_callees",
                    {"address": address, "offset": 0, "limit": 100, **selector},
                ),
            }
            after = await call("get_metadata", dict(selector))
            if before != after:
                raise RuntimeError("Ghidra metadata changed during packet capture")
            return {
                "backend": "ghidra",
                "advisory": True,
                "protocol_version": initialized.protocolVersion,
                "server": initialized.serverInfo.name,
                "target_attestation": (
                    "local exact target verification plus strict program='th105.exe' routing; "
                    "Ghidra metadata does not expose the target SHA-256"
                ),
                "metadata_pre": before,
                "metadata_post": after,
                "backend_raw": raw,
                "limitations": [
                    "Ghidra analysis output is advisory; the ledger boundary is authoritative.",
                    "Function xrefs are capped at 100 records in packet schema v1.",
                ],
            }


def comparison_state(address: str) -> dict[str, object]:
    manifest = load_manifest()
    found = unit_for_address(address, manifest)
    if found is None:
        return {"state": "unavailable", "reason": "no canonical match unit"}
    name, unit, function = found
    output = repository_path(str(unit["object"]), output=True)
    provenance_path = output.with_suffix(output.suffix + ".provenance.json")
    unit_summary = {
        "name": name,
        "kind": unit["kind"],
        "source": unit["source"],
        "object": unit["object"],
        "profile": unit["profile"],
        "enable_gs": unit["enable_gs"],
    }
    if not output.is_file() or not provenance_path.is_file():
        return {"state": "unavailable", "unit": unit_summary, "reason": "unit is not built"}
    provenance = json.loads(provenance_path.read_text(encoding="utf-8"))
    if provenance.get("target_sha256") != manifest["target_sha256"]:
        return {
            "state": "stale",
            "unit": unit_summary,
            "provenance": provenance,
            "reason": "provenance target attestation is missing or changed",
        }
    current_digest, _inputs = unit_input_digest(name, unit)
    if provenance.get("input_digest") != current_digest:
        return {
            "state": "stale",
            "unit": unit_summary,
            "provenance": provenance,
            "current_input_digest": current_digest,
        }

    command = [sys.executable, str(ROOT / "scripts" / "compare-function.py")]
    if function.get("contiguous_span"):
        command.append("--contiguous-span")
    if function.get("symbol_base"):
        command.extend(["--symbol-base", str(function["symbol_base"])])
    for mapping in function.get("rel32_targets", []):
        command.extend(["--rel32-target", str(mapping)])
    command.extend(["--json", address, str(output)])
    completed = subprocess.run(command, cwd=ROOT, capture_output=True, text=True)
    try:
        comparison = json.loads(completed.stdout)
    except json.JSONDecodeError as error:
        raise RuntimeError(f"structured comparator returned invalid JSON: {error}") from error
    return {
        "state": "fresh",
        "unit": unit_summary,
        "provenance": provenance,
        "command": command,
        "exit_code": completed.returncode,
        "result": comparison,
    }


def manifest_digests() -> dict[str, str]:
    paths = [
        FUNCTIONS,
        CLAIMS,
        ROOT / "config" / "core-functions.csv",
        ROOT / "config" / "core-dependencies.csv",
        ROOT / "config" / "core-types.csv",
        ROOT / "config" / "known-symbols.csv",
        ROOT / "config" / "reccmp-relocations.csv",
        MANIFEST,
    ]
    return {str(path.relative_to(ROOT)): file_sha256(path) for path in paths}


async def refresh(address: str, backend: str, server: str) -> dict[str, object]:
    ledger = next((row for row in read_rows(FUNCTIONS) if row["address"] == address), None)
    if ledger is None:
        raise RuntimeError(f"address is absent from function ledger: {address}")
    identity = target_identity()

    semantic: dict[str, object]
    if backend == "ida":
        semantic = await collect_ida(address, server)
    elif backend == "ghidra":
        semantic = await collect_ghidra(address)
    else:
        try:
            semantic = await collect_ida(address, server)
        except IdaMcpError as error:
            if error.reason == "target_mismatch":
                raise
            semantic = await collect_ghidra(address)
            semantic["ida_fallback_reason"] = {
                "reason": error.reason,
                "message": str(error),
            }

    ledger_size = int(ledger["size"])
    ledger_span_end = ledger["span_end"]
    raw_function = semantic.get("backend_raw", {})
    raw_function = (
        raw_function.get("function") if isinstance(raw_function, dict) else None
    )
    raw_entry, raw_size, raw_basis = canonical_backend_boundary(raw_function)
    boundary_state = "agrees"
    if raw_entry is None or raw_size is None:
        boundary_state = "backend_shape_unavailable"
    elif raw_entry != address or raw_size != ledger_size:
        boundary_state = f"{semantic['backend']}_boundary_conflict"

    packet: dict[str, object] = {
        "schema_version": 1,
        "request": {
            "address": address,
            "captured_utc": datetime.now(timezone.utc).isoformat().replace("+00:00", "Z"),
        },
        "target": identity,
        "authoritative_boundary": {
            "entry": address,
            "size": ledger_size,
            "span_end": ledger_span_end,
            "source": "config/functions.csv",
        },
        "analysis_boundary": {
            "entry": raw_entry,
            "size": raw_size,
            "basis": raw_basis,
            "state": boundary_state,
            "accepted": False,
        },
        "ledger": ledger,
        "core": core_packet(address),
        "semantic": semantic,
        "comparison": comparison_state(address),
        "manifests": manifest_digests(),
        "patterns": {
            "catalog": ".agents/skills/th105-re/references/exact-matching-patterns.md",
            "suggested": [],
        },
        "cache": {
            "advisory": True,
            "reason": "semantic databases expose no stable shared revision identity",
        },
    }
    encoded = json.dumps(packet, sort_keys=True, ensure_ascii=False).encode("utf-8")
    packet["cache"]["content_sha256"] = hashlib.sha256(encoded).hexdigest()  # type: ignore[index]
    return packet


def write_packet(address: str, packet: dict[str, object]) -> Path:
    directory = CACHE_ROOT / address
    directory.mkdir(parents=True, exist_ok=True)
    digest = packet["cache"]["content_sha256"]  # type: ignore[index]
    output = directory / f"{digest}.json"
    packet["cache"]["path"] = str(output.relative_to(ROOT))  # type: ignore[index]
    output.write_text(
        json.dumps(packet, indent=2, ensure_ascii=False) + "\n", encoding="utf-8"
    )
    return output


def cached_packet(address: str) -> dict[str, object]:
    directory = CACHE_ROOT / address
    candidates = sorted(directory.glob("*.json"), key=lambda path: path.stat().st_mtime)
    if not candidates:
        raise RuntimeError(f"no cached packet for {address}")
    value = json.loads(candidates[-1].read_text(encoding="utf-8"))
    value.setdefault("cache", {})["read_mode"] = "cached_advisory"
    return value


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("address")
    mode = parser.add_mutually_exclusive_group(required=True)
    mode.add_argument("--refresh", action="store_true")
    mode.add_argument("--cached", action="store_true")
    parser.add_argument("--backend", choices=("auto", "ida", "ghidra"), default="auto")
    parser.add_argument("--server", default=DEFAULT_SERVER)
    parser.add_argument(
        "--build",
        action="store_true",
        help="rebuild the canonical match unit before capturing comparison state",
    )
    args = parser.parse_args()
    try:
        address = canonical_address(args.address)
        if args.cached:
            packet = cached_packet(address)
        else:
            if args.build:
                manifest = load_manifest()
                found = unit_for_address(address, manifest)
                if found is None:
                    raise RuntimeError(f"no canonical match unit for {address}")
                name, _unit, _function = found
                completed = subprocess.run(
                    [sys.executable, str(ROOT / "scripts" / "build.py"), "--unit", name],
                    cwd=ROOT,
                )
                if completed.returncode != 0:
                    raise RuntimeError(f"match-unit build failed: {name}")
            packet = asyncio.run(refresh(address, args.backend, args.server))
            write_packet(address, packet)
        print(json.dumps(packet, indent=2, ensure_ascii=False))
        return 0
    except (IdaMcpError, OSError, RuntimeError, ValueError, json.JSONDecodeError) as error:
        reason = error.reason if isinstance(error, IdaMcpError) else "packet_error"
        print(
            json.dumps(
                {"ok": False, "reason": reason, "error": str(error)},
                indent=2,
                ensure_ascii=False,
            )
        )
        return 1


if __name__ == "__main__":
    raise SystemExit(main())
