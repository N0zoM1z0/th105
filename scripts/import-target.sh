#!/usr/bin/env bash
set -euo pipefail

repo_root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
if [[ $# -ne 1 ]]; then
  echo "usage: scripts/import-target.sh /path/to/th105.rar" >&2
  exit 2
fi
if ! command -v unrar >/dev/null; then
  echo "unrar is required for the original RAR4 archive" >&2
  exit 1
fi

archive="$(realpath "$1")"
temp_dir="$(mktemp -d)"
trap 'rm -rf -- "$temp_dir"' EXIT

unrar e -idq "$archive" th105c.exe "$temp_dir/"
python3 "$repo_root/scripts/verify-target.py" "$temp_dir/th105c.exe"
install -m 0644 "$temp_dir/th105c.exe" "$repo_root/resources/th105.exe"
echo "installed original Japanese executable at resources/th105.exe"
