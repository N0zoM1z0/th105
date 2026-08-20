#!/usr/bin/env python3
"""Shared protocol-native client helpers for the registered IDA Pro MCP."""

from __future__ import annotations

from contextlib import AsyncExitStack, asynccontextmanager
import json
import os
from pathlib import Path
import subprocess
import tomllib
from typing import Any, AsyncIterator, TYPE_CHECKING

from mcp_runtime import ensure_mcp_runtime


if TYPE_CHECKING:
    from mcp import ClientSession, StdioServerParameters


ROOT = Path(__file__).resolve().parents[1]
DEFAULT_SERVER = "ida-pro-mcp"
REQUIRED_READ_TOOLS = (
    "check_connection",
    "get_metadata",
    "get_entry_points",
    "get_function_by_address",
    "disassemble_function",
    "decompile_function",
    "get_xrefs_to",
    "get_callers",
    "get_callees",
    "list_functions",
    "read_memory_bytes",
)


class IdaMcpError(RuntimeError):
    """A preflight or MCP result failed with a machine-readable reason."""

    def __init__(self, reason: str, message: str):
        super().__init__(message)
        self.reason = reason


def load_target() -> dict[str, Any]:
    with (ROOT / "config" / "target.toml").open("rb") as stream:
        return tomllib.load(stream)


def load_server(name: str = DEFAULT_SERVER) -> StdioServerParameters:
    from mcp import StdioServerParameters

    try:
        completed = subprocess.run(
            ["codex", "mcp", "get", name, "--json"],
            check=True,
            capture_output=True,
            text=True,
        )
        config = json.loads(completed.stdout)
    except (OSError, subprocess.CalledProcessError, json.JSONDecodeError) as exc:
        raise IdaMcpError("unavailable", f"cannot load Codex MCP {name!r}: {exc}") from exc

    if not config.get("enabled"):
        raise IdaMcpError("unavailable", f"Codex MCP {name!r} is disabled")
    transport = config.get("transport") or {}
    if transport.get("type") != "stdio" or not transport.get("command"):
        raise IdaMcpError("unavailable", f"Codex MCP {name!r} is not a stdio server")

    child_env = os.environ.copy()
    configured_env = transport.get("env")
    if isinstance(configured_env, dict):
        child_env.update({str(key): str(value) for key, value in configured_env.items()})

    return StdioServerParameters(
        command=str(transport["command"]),
        args=[str(arg) for arg in transport.get("args") or []],
        cwd=transport.get("cwd"),
        env=child_env,
    )


@asynccontextmanager
async def open_session(
    name: str = DEFAULT_SERVER,
) -> AsyncIterator[tuple[ClientSession, Any]]:
    ensure_mcp_runtime()
    from mcp import ClientSession
    from mcp.client.stdio import stdio_client

    server = load_server(name)
    stack = AsyncExitStack()
    try:
        read_stream, write_stream = await stack.enter_async_context(stdio_client(server))
        session = await stack.enter_async_context(ClientSession(read_stream, write_stream))
        initialized = await session.initialize()
    except IdaMcpError:
        await stack.aclose()
        raise
    except Exception as exc:
        await stack.aclose()
        raise IdaMcpError("unavailable", f"IDA MCP session failed: {exc}") from exc
    try:
        yield session, initialized
    finally:
        await stack.aclose()


def decode_tool_result(result: Any, tool: str) -> Any:
    texts = [item.text for item in result.content if item.type == "text"]
    if result.isError:
        detail = "; ".join(texts).strip()
        suffix = f": {detail}" if detail else ""
        raise IdaMcpError("tool_error", f"IDA MCP tool failed: {tool}{suffix}")
    if not texts:
        return None
    if len(texts) == 1:
        try:
            return json.loads(texts[0])
        except json.JSONDecodeError:
            return texts[0]
    decoded = []
    for value in texts:
        try:
            decoded.append(json.loads(value))
        except json.JSONDecodeError:
            decoded.append(value)
    return decoded


async def call_json(session: ClientSession, tool: str, arguments: dict[str, Any]) -> Any:
    try:
        result = await session.call_tool(tool, arguments)
    except Exception as exc:
        raise IdaMcpError("tool_error", f"IDA MCP call {tool} failed: {exc}") from exc
    return decode_tool_result(result, tool)


def parse_int(value: Any) -> int:
    if isinstance(value, int):
        return value
    if isinstance(value, str):
        return int(value, 0)
    raise ValueError(f"not an integer: {value!r}")


def validate_metadata(metadata: dict[str, Any]) -> None:
    expected = load_target()
    target = expected["target"]
    pe = expected["pe"]
    checks = {
        "sha256": (str(metadata.get("sha256", "")).lower(), target["sha256"].lower()),
        "md5": (str(metadata.get("md5", "")).lower(), target["md5"].lower()),
    }
    for field, (actual, wanted) in checks.items():
        if actual != wanted:
            raise IdaMcpError(
                "target_mismatch", f"IDA {field} mismatch: got {actual!r}, expected {wanted!r}"
            )

    numeric_checks = {
        "base": (metadata.get("base"), pe["image_base"]),
        "filesize": (metadata.get("filesize"), target["size"]),
    }
    for field, (actual_raw, wanted_raw) in numeric_checks.items():
        try:
            actual = parse_int(actual_raw)
            wanted = parse_int(wanted_raw)
        except (TypeError, ValueError) as exc:
            raise IdaMcpError("target_mismatch", f"invalid IDA {field}: {actual_raw!r}") from exc
        if actual != wanted:
            raise IdaMcpError(
                "target_mismatch",
                f"IDA {field} mismatch: got {actual:#x}, expected {wanted:#x}",
            )


async def require_target(session: ClientSession) -> dict[str, Any]:
    metadata = await call_json(session, "get_metadata", {})
    if not isinstance(metadata, dict):
        raise IdaMcpError("target_mismatch", f"unexpected IDA metadata: {metadata!r}")
    validate_metadata(metadata)
    return metadata
