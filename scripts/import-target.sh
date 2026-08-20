#!/usr/bin/env bash
set -euo pipefail

repo_root=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd)

if [[ $# -ne 1 ]]; then
  echo "usage: $0 /path/to/original-japanese-1.06a/th105.exe" >&2
  exit 2
fi

source_exe=$1
python3 "$repo_root/scripts/verify-target.py" "$source_exe"
install -m 0644 "$source_exe" "$repo_root/resources/th105.exe"
python3 "$repo_root/scripts/verify-target.py"
