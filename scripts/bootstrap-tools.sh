#!/usr/bin/env bash
set -euo pipefail

repo_root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
tools_dir="$repo_root/.tools"
downloads="$tools_dir/downloads"
ghidra_home="$tools_dir/ghidra_12.1_PUBLIC"
mcp_root="$tools_dir/src/ghidra-mcp"
maven_home="$tools_dir/apache-maven-3.9.16"

ghidra_url="https://github.com/NationalSecurityAgency/ghidra/releases/download/Ghidra_12.1_build/ghidra_12.1_PUBLIC_20260513.zip"
ghidra_sha256="aa5cbcbbf48f41ca185fce900e19592f1ade4cd5994eb6e0ede468dac8a6f302"
maven_url="https://archive.apache.org/dist/maven/maven-3/3.9.16/binaries/apache-maven-3.9.16-bin.tar.gz"
maven_sha256="80ffca22aed9e8b9713a232f3394fd81d7f20322df75efdb2b047dbd3e3a23bb"
mcp_commit="0e5f0a410c652cbb90aa30a953ce69b55a5d26a7"

for command in curl git java tar unzip uv; do
  if ! command -v "$command" >/dev/null; then
    echo "missing prerequisite: $command" >&2
    exit 1
  fi
done

if ! java -version 2>&1 | head -1 | grep -q '"21\.'; then
  echo "Ghidra 12.1 requires Java 21; set JAVA_HOME to a JDK 21 installation." >&2
  exit 1
fi

mkdir -p "$downloads" "$tools_dir/src" "$tools_dir/config"

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

if [[ ! -x "$ghidra_home/support/analyzeHeadless" ]]; then
  archive="$downloads/ghidra_12.1_PUBLIC_20260513.zip"
  download_checked "$ghidra_url" "$archive" "$ghidra_sha256"
  unzip -q "$archive" -d "$tools_dir"
fi

if [[ ! -x "$maven_home/bin/mvn" ]]; then
  archive="$downloads/apache-maven-3.9.16-bin.tar.gz"
  download_checked "$maven_url" "$archive" "$maven_sha256"
  tar -xzf "$archive" -C "$tools_dir"
fi

if [[ ! -d "$mcp_root/.git" ]]; then
  git clone https://github.com/bethington/ghidra-mcp.git "$mcp_root"
fi
git -C "$mcp_root" fetch --quiet origin "$mcp_commit"
git -C "$mcp_root" checkout --quiet --detach "$mcp_commit"

uv sync --directory "$mcp_root"
(
  cd "$mcp_root"
  export PATH="$maven_home/bin:$PATH"
  export XDG_CONFIG_HOME="$tools_dir/config"
  .venv/bin/python -m tools.setup ensure-prereqs --ghidra-path "$ghidra_home"
  .venv/bin/python -m tools.setup build
  .venv/bin/python -m tools.setup deploy --ghidra-path "$ghidra_home"
)

if ! command -v reccmp-project >/dev/null || [[ "$(reccmp-project --version 2>/dev/null || true)" != *"0.1.6"* ]]; then
  uv tool install --force reccmp==0.1.6
fi

echo "tool bootstrap complete"
echo "next: scripts/bootstrap-ghidra-project.sh"
