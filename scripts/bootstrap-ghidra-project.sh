#!/usr/bin/env bash
set -euo pipefail

repo_root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
ghidra_home="${GHIDRA_HOME:-$repo_root/.tools/ghidra_12.1_PUBLIC}"
java_home="${JAVA_HOME:-/usr/lib/jvm/java-21-openjdk-amd64}"

python3 "$repo_root/scripts/verify-target.py"
mkdir -p "$repo_root/local/ghidra" "$repo_root/.analysis" "$repo_root/.tools/config"

if [[ ! -f "$repo_root/local/ghidra/th105.gpr" ]]; then
  env XDG_CONFIG_HOME="$repo_root/.tools/config" JAVA_HOME="$java_home" \
    "$ghidra_home/support/analyzeHeadless" \
    "$repo_root/local/ghidra" th105 \
    -import "$repo_root/resources/th105.exe"
fi

"$repo_root/scripts/export-function-inventory.sh"
python3 "$repo_root/scripts/generate-tracking.py"
python3 "$repo_root/scripts/progress.py"
