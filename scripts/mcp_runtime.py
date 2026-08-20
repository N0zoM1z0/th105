#!/usr/bin/env python3
"""Provide a reproducible Python runtime for the repo's IDA MCP clients."""

from __future__ import annotations

from importlib.metadata import PackageNotFoundError, version
import os
import shutil
import sys


MCP_REQUIREMENT = "mcp==1.26.0"
BOOTSTRAP_MARKER = "TH105_IDA_MCP_UV_BOOTSTRAPPED"


def installed_mcp_version() -> str | None:
    try:
        return version("mcp")
    except PackageNotFoundError:
        return None


def bootstrap_command(uv: str, argv: list[str]) -> list[str]:
    return [
        uv,
        "run",
        "--quiet",
        "--no-project",
        "--with",
        MCP_REQUIREMENT,
        "python3",
        *argv,
    ]


def ensure_mcp_runtime() -> None:
    current = installed_mcp_version()
    if current == MCP_REQUIREMENT.removeprefix("mcp=="):
        return

    if os.environ.get(BOOTSTRAP_MARKER) == "1":
        raise RuntimeError(
            f"uv bootstrap did not provide {MCP_REQUIREMENT}; found {current or 'nothing'}"
        )

    uv = shutil.which("uv")
    if uv is None:
        raise RuntimeError(
            f"Python requires {MCP_REQUIREMENT} for IDA MCP; install uv or run in a compatible environment"
        )

    environment = os.environ.copy()
    environment[BOOTSTRAP_MARKER] = "1"
    command = bootstrap_command(uv, sys.argv)
    print(
        f"[th105] re-running with pinned IDA MCP runtime ({MCP_REQUIREMENT})",
        file=sys.stderr,
        flush=True,
    )
    os.execvpe(uv, command, environment)
