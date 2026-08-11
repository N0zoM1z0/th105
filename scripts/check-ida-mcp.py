#!/usr/bin/env python3
"""Verify the registered IDA MCP protocol path and exact TH105 target."""

from __future__ import annotations

import argparse
import asyncio
import json

from ida_mcp_client import (
    DEFAULT_SERVER,
    IdaMcpError,
    REQUIRED_READ_TOOLS,
    call_json,
    open_session,
    parse_int,
    require_target,
)


WRAPPER = "0x0046A5B0"
TAIL_BODY = "0x00463610"


async def check(server_name: str) -> dict[str, object]:
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

        wrapper = await call_json(
            session, "get_function_by_address", {"address": WRAPPER}
        )
        disassembly = await call_json(
            session, "disassemble_function", {"start_address": WRAPPER}
        )
        tail = await call_json(
            session, "get_function_by_address", {"address": TAIL_BODY}
        )
        try:
            wrapper_size = parse_int(wrapper.get("size")) if isinstance(wrapper, dict) else -1
        except (TypeError, ValueError):
            wrapper_size = -1
        if not isinstance(wrapper, dict) or wrapper_size != 0xB:
            raise IdaMcpError(
                "boundary_conflict", f"unexpected {WRAPPER} wrapper metadata: {wrapper!r}"
            )
        lines = disassembly.get("lines", []) if isinstance(disassembly, dict) else []
        instructions = "\n".join(str(line.get("instruction", "")) for line in lines)
        if "463610" not in instructions.lower():
            raise IdaMcpError(
                "boundary_conflict", f"{WRAPPER} no longer tail-jumps to {TAIL_BODY}"
            )

        try:
            tail_size = parse_int(tail.get("size")) if isinstance(tail, dict) else -1
        except (TypeError, ValueError):
            tail_size = -1
        same_tail_owner = isinstance(tail, dict) and (
            tail.get("name") == wrapper.get("name") and tail_size == 0xB
        )
        return {
            "ok": True,
            "protocol_version": initialized.protocolVersion,
            "mcp_server": initialized.serverInfo.name,
            "tool_count": len(names),
            "metadata": metadata,
            "boundary_sentinel": {
                "wrapper": wrapper,
                "tail_query": tail,
                "ida_conflates_known_tail_body": same_tail_owner,
                "ledger_rule": "config/functions.csv remains authoritative",
            },
        }


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--server", default=DEFAULT_SERVER)
    args = parser.parse_args()
    try:
        output = asyncio.run(check(args.server))
    except IdaMcpError as exc:
        print(json.dumps({"ok": False, "reason": exc.reason, "error": str(exc)}, indent=2))
        raise SystemExit(1) from exc
    print(json.dumps(output, indent=2))


if __name__ == "__main__":
    main()
