#!/usr/bin/env bash
set -euo pipefail

repo_root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
ghidra_home="${GHIDRA_HOME:-$repo_root/.tools/ghidra_12.1_PUBLIC}"
mcp_root="${GHIDRA_MCP_ROOT:-$repo_root/.tools/src/ghidra-mcp}"
java_home="${TH105_JAVA_HOME:-/usr/lib/jvm/java-21-openjdk-amd64}"
java_bin="$java_home/bin/java"
project="${TH105_GHIDRA_PROJECT:-$repo_root/local/ghidra/th105.gpr}"
program="${TH105_GHIDRA_PROGRAM:-/th105.exe}"
bind="${TH105_GHIDRA_BIND:-127.0.0.1}"
port="${TH105_GHIDRA_PORT:-8089}"

mcp_jar="$(find "$mcp_root/target" -maxdepth 1 -type f -name 'GhidraMCP-*.jar' ! -name '*sources*' ! -name '*javadoc*' -print -quit)"
if [[ -z "$mcp_jar" || ! -x "$java_bin" || ! -d "$ghidra_home" || ! -f "$project" ]]; then
  echo "GhidraMCP prerequisites are missing; run scripts/bootstrap-tools.sh first." >&2
  exit 1
fi

classpath="$mcp_jar"
for jar in \
  "$ghidra_home"/Ghidra/Framework/*/lib/*.jar \
  "$ghidra_home"/Ghidra/Features/*/lib/*.jar \
  "$ghidra_home"/Ghidra/Processors/*/lib/*.jar \
  "$mcp_root"/target/lib/*.jar; do
  if [[ -f "$jar" ]]; then
    classpath="$classpath:$jar"
  fi
done

mkdir -p "$repo_root/.tools/config" "$repo_root/local/logs"
exec env \
  XDG_CONFIG_HOME="$repo_root/.tools/config" \
  JAVA_HOME="$java_home" \
  GHIDRA_MCP_FILE_ROOT="$repo_root" \
  "$java_bin" \
  -Xmx12g \
  -XX:+UseG1GC \
  -Dghidra.home="$ghidra_home" \
  -Dapplication.name=GhidraMCP \
  -classpath "$classpath" \
  com.xebyte.headless.GhidraMCPHeadlessServer \
  --bind "$bind" \
  --port "$port" \
  --project "$project" \
  --program "$program"
