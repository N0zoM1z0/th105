#!/usr/bin/env bash
set -euo pipefail

repo_root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
ghidra_home="${GHIDRA_HOME:-$repo_root/.tools/ghidra_12.1_PUBLIC}"
java_home="${JAVA_HOME:-/usr/lib/jvm/java-21-openjdk-amd64}"

if curl --silent --fail --max-time 1 http://127.0.0.1:8089/check_connection >/dev/null 2>&1; then
  echo "stop the GhidraMCP server before exporting the project inventory" >&2
  exit 1
fi

env XDG_CONFIG_HOME="$repo_root/.tools/config" JAVA_HOME="$java_home" \
  "$ghidra_home/support/analyzeHeadless" \
  "$repo_root/local/ghidra" th105 \
  -process th105.exe \
  -noanalysis \
  -scriptPath "$repo_root/scripts/ghidra" \
  -postScript ExportFunctionInventory.java "$repo_root/.analysis/ghidra-functions.csv"
