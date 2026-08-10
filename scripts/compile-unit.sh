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

mkdir -p "$(dirname "$output_path")" "$wine_prefix"
export WINEPREFIX="$wine_prefix"
export WINEARCH=win32
export WINEDEBUG=-all

filter_preload_noise() {
  sed '/mhxtlib\.so.*wrong ELF class/d' >&2
}

source_win="$(winepath -w "$source_path" 2> >(filter_preload_noise))"
output_win="$(winepath -w "$output_path" 2> >(filter_preload_noise))"
src_include_win="$(winepath -w "$repo_root/src" 2> >(filter_preload_noise))"
crt_include_win="$(winepath -w "$msvc_root/include" 2> >(filter_preload_noise))"
sdk_include_win="$(winepath -w "$msvc_root/PlatformSDK/Include" 2> >(filter_preload_noise))"

# This is the fast non-LTCG probe configuration. The final executable build
# will add /GL and link with /LTCG once its translation-unit set is recovered.
# A small number of recovered translation units demonstrably use /GS; opt in
# per probe without changing the default code generation of existing units.
gs_flag=/GS-
if [[ "${TH105_ENABLE_GS:-0}" == 1 ]]; then
  gs_flag=/GS
fi

wine "$cl" \
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
