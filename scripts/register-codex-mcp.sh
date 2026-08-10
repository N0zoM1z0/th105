#!/usr/bin/env bash
set -euo pipefail

repo_root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
server_name="th105-ghidra"

if ! command -v codex >/dev/null 2>&1; then
  echo "codex is not installed or is not on PATH" >&2
  exit 1
fi

if codex mcp get "$server_name" >/dev/null 2>&1; then
  echo "$server_name is already registered:"
  codex mcp get "$server_name"
  exit 0
fi

codex mcp add "$server_name" -- bash "$repo_root/scripts/mcp-ghidra.sh"
echo "Start a new Codex session to load the MCP tool catalog."
