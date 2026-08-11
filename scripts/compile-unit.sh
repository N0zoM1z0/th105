#!/usr/bin/env bash
set -euo pipefail

repo_root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
if [[ $# -ne 2 ]]; then
  echo "usage: scripts/compile-unit.sh src/file.cpp build/file.obj" >&2
  exit 2
fi

source_path="$(realpath "$1")"
output_path="$(realpath -m "$2")"
msvc_root="${TH105_MSVC8_ROOT:-$repo_root/.tools/msvc80-sp1}"
wine_prefix="${TH105_WINEPREFIX:-$repo_root/.tools/wine-msvc8}"
cl="$msvc_root/bin/cl.exe"

if [[ ! -f "$cl" ]]; then
  echo "missing VC8 SP1 toolchain; run scripts/bootstrap-tools.sh" >&2
  exit 1
fi

mkdir -p "$(dirname "$output_path")"

filter_preload_noise() {
  sed '/mhxtlib\.so.*wrong ELF class/d' >&2
}

if command -v wine >/dev/null && command -v winepath >/dev/null; then
  mkdir -p "$wine_prefix"
  export WINEPREFIX="$wine_prefix"
  export WINEARCH=win32
  export WINEDEBUG=-all
  path_to_windows() {
    winepath -w "$1" 2> >(filter_preload_noise)
  }
  compiler=(wine "$cl")
elif command -v wslpath >/dev/null && [[ -x /mnt/c/Windows/System32/cmd.exe ]]; then
  # WSL can execute PE files directly. This avoids requiring Wine when the
  # reconstruction workspace already runs beside the user's Windows tools.
  chmod +x "$cl"
  path_to_windows() {
    wslpath -w "$1"
  }
  compiler=("$cl")
else
  echo "neither Wine nor Windows interop is available for VC8 cl.exe" >&2
  exit 1
fi

source_win="$(path_to_windows "$source_path")"
output_win="$(path_to_windows "$output_path")"
src_include_win="$(path_to_windows "$repo_root/src")"
crt_include_win="$(path_to_windows "$msvc_root/include")"
sdk_include_win="$(path_to_windows "$msvc_root/PlatformSDK/Include")"

# This is the fast non-LTCG probe configuration. The final executable build
# will add /GL and link with /LTCG once its translation-unit set is recovered.
# A small number of recovered translation units demonstrably use /GS; opt in
# per probe without changing the default code generation of existing units.
gs_flag=/GS-
if [[ "${TH105_ENABLE_GS:-0}" == 1 ]]; then
  gs_flag=/GS
fi

"${compiler[@]}" \
  /nologo \
  /c \
  /O2 \
  "$gs_flag" \
  /GR \
  /EHsc \
  /MT \
  "/I$src_include_win" \
  "/I$crt_include_win" \
  "/I$sdk_include_win" \
  "/Fo$output_win" \
  "$source_win" \
  2> >(filter_preload_noise)
