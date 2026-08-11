#!/usr/bin/env bash
set -euo pipefail

repo_root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
ghidra_home="${GHIDRA_HOME:-$repo_root/.tools/ghidra_12.1_PUBLIC}"
java_home="${JAVA_HOME:-/usr/lib/jvm/java-21-openjdk-amd64}"
archive="${1:-$repo_root/th105-analysis-e4a92b7-20260811.zip}"
output="${2:-$repo_root/.analysis/ghidra-analysis-bundle}"

if [[ ! -f "$archive" ]]; then
  echo "source archive not found: $archive" >&2
  exit 1
fi
if [[ ! -x "$ghidra_home/support/analyzeHeadless" ]]; then
  echo "headless Ghidra not found: $ghidra_home/support/analyzeHeadless" >&2
  exit 1
fi

mkdir -p "$repo_root/.analysis"
staging="$(mktemp -d "$repo_root/.analysis/ghidra-bundle.XXXXXX")"
trap 'rm -rf -- "$staging"' EXIT
env XDG_CONFIG_HOME="$repo_root/.tools/config" JAVA_HOME="$java_home" \
  "$ghidra_home/support/analyzeHeadless" \
  "$repo_root/local/ghidra" th105 \
  -process th105.exe \
  -readOnly \
  -noanalysis \
  -scriptPath "$repo_root/scripts/ghidra" \
  -postScript ExportAnalysisBundle.java "$staging"

if [[ ! -f "$staging/export-metadata.properties" ]]; then
  echo "headless Ghidra did not produce the analysis bundle" >&2
  exit 1
fi

archive_sha256="$(sha256sum "$archive" | awk '{print $1}')"
python3 "$repo_root/scripts/finalize-analysis-bundle.py" \
  "$staging" \
  --source-archive-name "$(basename "$archive")" \
  --source-archive-sha256 "$archive_sha256"

mkdir -p "$output"
cp -f "$staging"/* "$output"/
echo "analysis bundle written to $output"
