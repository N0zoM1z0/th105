#!/usr/bin/env python3
"""Exercise Ghidra through the MCP stdio protocol, not its HTTP API directly."""

from __future__ import annotations

import asyncio
import json
import os
from pathlib import Path

from mcp import ClientSession, StdioServerParameters
from mcp.client.stdio import stdio_client


ROOT = Path(__file__).resolve().parents[1]


async def check() -> None:
    server = StdioServerParameters(
        command="bash",
        args=[str(ROOT / "scripts" / "mcp-ghidra.sh")],
        cwd=ROOT,
        env=os.environ.copy(),
    )
    async with stdio_client(server) as (read_stream, write_stream):
        async with ClientSession(read_stream, write_stream) as session:
            initialized = await session.initialize()
            listed = await session.list_tools()
            names = [tool.name for tool in listed.tools]
            if "get_metadata" not in names:
                raise RuntimeError("GhidraMCP did not expose get_metadata")

            result = await session.call_tool("get_metadata", {"program": "th105.exe"})
            texts = [item.text for item in result.content if item.type == "text"]
            if not texts:
                raise RuntimeError("get_metadata returned no text content")
            metadata = json.loads(texts[0])
            if metadata.get("program_name") != "th105.exe":
                raise RuntimeError(f"unexpected program: {metadata!r}")

            print(
                json.dumps(
                    {
                        "protocol_version": initialized.protocolVersion,
                        "mcp_server": initialized.serverInfo.name,
                        "tool_count": len(names),
                        "called_tool": "get_metadata",
                        "result": metadata,
                    },
                    indent=2,
                )
            )


if __name__ == "__main__":
    asyncio.run(check())
