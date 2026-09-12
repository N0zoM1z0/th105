#!/usr/bin/env bash
# Compare exported and retained-only LTCG visibility for one real source TU.
# The unresolved DLLs are inspection artifacts: NEVER execute or accept them.
set -euo pipefail

if [[ $# -ne 2 ]]; then
  echo 'usage: scripts/probe-ltcg-visibility.sh SOURCE DECORATED_SYMBOL' >&2
  exit 2
fi

probe_root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
probe_source="$(realpath "$1")"
probe_symbol="$2"
probe_msvc="${TH105_MSVC8_ROOT:-$probe_root/.tools/msvc80-sp1}"
probe_prefix="${TH105_WINEPREFIX:-$probe_root/.tools/wine-msvc8}"
if [[ ! -f "$probe_source" || ! -f "$probe_msvc/bin/cl.exe" || ! -f "$probe_msvc/bin/link.exe" ]]; then
  echo 'missing source or pinned VC8 compiler/linker' >&2
  exit 2
fi
if [[ -z "$probe_symbol" ]]; then
  echo 'the decorated function symbol must not be empty' >&2
  exit 2
fi
for probe_tool in wine winepath objdump sha256sum; do
  if ! command -v "$probe_tool" >/dev/null; then
    echo "missing required tool: $probe_tool" >&2
    exit 2
  fi
done

mkdir -p "$probe_root/build"
probe_dir="$(mktemp -d "$probe_root/build/ltcg-visibility.XXXXXX")"
export WINEPREFIX="$probe_prefix"
export WINEARCH=win32
export WINEDEBUG=-all
probe_win() { winepath -w "$1"; }

echo "Non-executable, non-acceptance LTCG diagnostic: $probe_dir"
sha256sum "$probe_source" "$probe_msvc/bin/cl.exe" \
  "$probe_msvc/bin/c1xx.dll" "$probe_msvc/bin/c2.dll" \
  "$probe_msvc/bin/link.exe" > "$probe_dir/input-sha256.txt"

wine "$probe_msvc/bin/cl.exe" /nologo /c /O2 /GL /GS- /GR /EHsc /MT \
  "/I$(probe_win "$probe_root/src")" \
  "/I$(probe_win "$probe_msvc/include")" \
  "/I$(probe_win "$probe_msvc/PlatformSDK/Include")" \
  "/Fo$(probe_win "$probe_dir/main.obj")" "$(probe_win "$probe_source")" \
  > "$probe_dir/compile.log" 2>&1

# One compiler invocation, followed by two serial links of the same GL input.
# No fake callee definitions, custom ABI stubs or synthetic callers are added.
for probe_visibility in export include; do
  probe_case_dir="$probe_dir/$probe_visibility"
  mkdir -p "$probe_case_dir"
  if [[ "$probe_visibility" == export ]]; then
    probe_keep_flag="/EXPORT:$probe_symbol"
  else
    probe_keep_flag="/INCLUDE:$probe_symbol"
  fi
  wine "$probe_msvc/bin/link.exe" /nologo /DLL /NOENTRY /LTCG /NODEFAULTLIB \
    /FORCE:UNRESOLVED /OPT:NOICF "$probe_keep_flag" \
    "/MAP:$(probe_win "$probe_case_dir/probe.map")" \
    "/OUT:$(probe_win "$probe_case_dir/probe.dll")" \
    "$(probe_win "$probe_dir/main.obj")" \
    > "$probe_case_dir/link.log" 2>&1
  objdump -d -Mintel -j .text "$probe_case_dir/probe.dll" \
    > "$probe_case_dir/disassembly.txt"
done

echo "Inspection completed. Read both link logs and disassemblies in $probe_dir."
echo 'Success means tool completion only, not runnable output or canonical matching.'
