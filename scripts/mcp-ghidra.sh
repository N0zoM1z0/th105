#!/usr/bin/env bash
set -euo pipefail

repo_root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
port="${TH105_GHIDRA_PORT:-8089}"
server_url="http://127.0.0.1:$port"
bridge="$repo_root/.tools/src/ghidra-mcp/.venv/bin/bridge-mcp-ghidra"
server_pid=""

cleanup() {
  if [[ -n "$server_pid" ]]; then
    kill "$server_pid" 2>/dev/null || true
    wait "$server_pid" 2>/dev/null || true
  fi
}
trap cleanup EXIT INT TERM

is_th105_server() {
  local metadata
  metadata="$(curl --silent --show-error --fail --max-time 2 "$server_url/get_metadata" 2>/dev/null)" || return 1
  [[ "$metadata" == *'"program_name":"th105.exe"'* ]]
}

if ! is_th105_server; then
  if curl --silent --fail --max-time 2 "$server_url/check_connection" >/dev/null 2>&1; then
    echo "Port $port is occupied by a different GhidraMCP program." >&2
    exit 1
  fi

  mkdir -p "$repo_root/local/logs"
  "$repo_root/scripts/ghidra-mcp-server.sh" \
    >>"$repo_root/local/logs/ghidra-mcp.log" 2>&1 &
  server_pid=$!

  for _ in $(seq 1 45); do
    if is_th105_server; then
      break
    fi
    if ! kill -0 "$server_pid" 2>/dev/null; then
      echo "GhidraMCP server exited during startup; see local/logs/ghidra-mcp.log." >&2
      exit 1
    fi
    sleep 1
  done

  if ! is_th105_server; then
    echo "Timed out waiting for GhidraMCP at $server_url." >&2
    exit 1
  fi
fi

if [[ ! -x "$bridge" ]]; then
  echo "GhidraMCP bridge is missing; run scripts/bootstrap-tools.sh first." >&2
  exit 1
fi

env \
  GHIDRA_MCP_URL="$server_url" \
  GHIDRA_MCP_REQUIRE_PROGRAM_SELECTORS=1 \
  PYTHONIOENCODING=utf-8 \
  "$bridge" --transport stdio --no-lazy
