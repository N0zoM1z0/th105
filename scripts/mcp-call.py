#!/usr/bin/env python3
"""Call one or more local Ghidra MCP tools over a single stdio session."""

from __future__ import annotations

import argparse
import asyncio
import json
from pathlib import Path
import re

from mcp import ClientSession, StdioServerParameters
from mcp.client.stdio import stdio_client


ROOT = Path(__file__).resolve().parents[1]


async def run(
    list_names: list[str], searches: list[str], calls: list[tuple[str, dict[str, object]]]
) -> None:
    server = StdioServerParameters(
        command="bash",
        args=[str(ROOT / "scripts" / "mcp-ghidra.sh")],
        cwd=ROOT,
    )
    async with stdio_client(server) as (read_stream, write_stream):
        async with ClientSession(read_stream, write_stream) as session:
            await session.initialize()
            tools = {tool.name: tool for tool in (await session.list_tools()).tools}
            for pattern in searches:
                print(json.dumps(sorted(name for name in tools if re.search(pattern, name))))
            for name in list_names:
                if name not in tools:
                    raise RuntimeError(f"unknown MCP tool: {name}")
                tool = tools[name]
                print(json.dumps({"name": name, "inputSchema": tool.inputSchema}, indent=2))
            for name, arguments in calls:
                if name not in tools:
                    raise RuntimeError(f"unknown MCP tool: {name}")
                result = await session.call_tool(name, arguments)
                output = [
                    item.text if item.type == "text" else item.model_dump(mode="json")
                    for item in result.content
                ]
                print(json.dumps({"tool": name, "isError": result.isError, "content": output}, indent=2))
                if result.isError:
                    raise RuntimeError(f"MCP tool failed: {name}")


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--schema", action="append", default=[], metavar="TOOL")
    parser.add_argument("--search", action="append", default=[], metavar="REGEX")
    parser.add_argument(
        "--call",
        action="append",
        nargs=2,
        default=[],
        metavar=("TOOL", "JSON"),
    )
    args = parser.parse_args()
    calls = [(name, json.loads(arguments)) for name, arguments in args.call]
    asyncio.run(run(args.schema, args.search, calls))


if __name__ == "__main__":
    main()
