#!/usr/bin/env bash
set -euo pipefail

repo_root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
tools_dir="$repo_root/.tools"
downloads="$tools_dir/downloads"
ghidra_home="$tools_dir/ghidra_12.1_PUBLIC"
mcp_root="$tools_dir/src/ghidra-mcp"
maven_home="$tools_dir/apache-maven-3.9.16"
msvc_root="$tools_dir/msvc80-sp1"
objdiff_root="$tools_dir/objdiff"

ghidra_url="https://github.com/NationalSecurityAgency/ghidra/releases/download/Ghidra_12.1_build/ghidra_12.1_PUBLIC_20260513.zip"
ghidra_sha256="aa5cbcbbf48f41ca185fce900e19592f1ade4cd5994eb6e0ede468dac8a6f302"
maven_url="https://archive.apache.org/dist/maven/maven-3/3.9.16/binaries/apache-maven-3.9.16-bin.tar.gz"
maven_sha256="80ffca22aed9e8b9713a232f3394fd81d7f20322df75efdb2b047dbd3e3a23bb"
mcp_commit="0e5f0a410c652cbb90aa30a953ce69b55a5d26a7"
msvc_commit="cd5f81de4228351ed9ed5b2dc8059d57da8f554a"
objdiff_url="https://github.com/encounter/objdiff/releases/download/v3.8.0/objdiff-cli-linux-x86_64"
objdiff_sha256="bc1e047126f9c6914bd1695798175234642ab9eaf45e886f841b59a4231e1a81"

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

uv sync --directory "$mcp_root"
(
  cd "$mcp_root"
  export PATH="$maven_home/bin:$PATH"
  export XDG_CONFIG_HOME="$tools_dir/config"
  .venv/bin/python -m tools.setup ensure-prereqs --ghidra-path "$ghidra_home"
  .venv/bin/python -m tools.setup build
)

# Do not use tools.setup deploy here: it launches the Ghidra GUI. The
# repository fallback uses scripts/ghidra-mcp-server.sh and the bundle exports
# use analyzeHeadless, so the built headless JAR is sufficient.

if ! command -v reccmp-project >/dev/null || [[ "$(reccmp-project --version 2>/dev/null || true)" != *"0.1.6"* ]]; then
  uv tool install --force reccmp==0.1.6
fi

echo "tool bootstrap complete"
echo "next: scripts/bootstrap-ghidra-project.sh"
