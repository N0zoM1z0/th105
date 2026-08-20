#!/usr/bin/env bash
set -euo pipefail

repo_root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
tools_dir="$repo_root/.tools"
downloads="$tools_dir/downloads"
msvc_root="$tools_dir/msvc80-sp1"
objdiff_root="$tools_dir/objdiff"

msvc_commit="cd5f81de4228351ed9ed5b2dc8059d57da8f554a"
objdiff_url="https://github.com/encounter/objdiff/releases/download/v3.8.0/objdiff-cli-linux-x86_64"
objdiff_sha256="bc1e047126f9c6914bd1695798175234642ab9eaf45e886f841b59a4231e1a81"

for command in curl git uv; do
  if ! command -v "$command" >/dev/null; then
    echo "missing prerequisite: $command" >&2
    exit 1
  fi
done

mkdir -p "$downloads" "$tools_dir"

download_checked() {
  local url="$1"
  local output="$2"
  local expected="$3"
  if [[ ! -f "$output" ]]; then
    curl --fail --location --retry 3 --output "$output" "$url"
  fi
  echo "$expected  $output" | sha256sum --check --status || {
    echo "checksum mismatch: $output" >&2
    exit 1
  }
}

if [[ ! -d "$msvc_root/.git" ]]; then
  git clone https://github.com/bananapizzuh/msvc80-sp1.git "$msvc_root"
fi
git -C "$msvc_root" fetch --quiet origin "$msvc_commit"
git -C "$msvc_root" checkout --quiet --detach "$msvc_commit"

if [[ "$(uname -m)" != "x86_64" ]]; then
  echo "the pinned objdiff CLI asset currently supports Linux x86_64 only" >&2
  exit 1
fi
if [[ ! -x "$objdiff_root/objdiff-cli" ]]; then
  archive="$downloads/objdiff-cli-linux-x86_64-v3.8.0"
  download_checked "$objdiff_url" "$archive" "$objdiff_sha256"
  mkdir -p "$objdiff_root"
  install -m 0755 "$archive" "$objdiff_root/objdiff-cli"
fi

if ! command -v reccmp-project >/dev/null || \
  [[ "$(reccmp-project --version 2>/dev/null || true)" != *"0.1.6"* ]]; then
  uv tool install --force reccmp==0.1.6
fi

echo "matching-tool bootstrap complete"
echo "semantic analysis is IDA Pro only; run python3 scripts/check-ida-mcp.py"
