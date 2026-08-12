#!/usr/bin/env bash
set -euo pipefail

repo_root="$(cd "$(dirname "${BASH_SOURCE[0]}")/../../../.." && pwd)"

usage() {
  echo "usage: compile-upstream-vc8.sh SOURCE OUTPUT [--include DIR]..." >&2
}

if [[ $# -lt 2 ]]; then
  usage
  exit 2
fi

source_path="$(realpath "$1")"
output_path="$(realpath -m "$2")"
shift 2

include_paths=("$(dirname "$source_path")")
while [[ $# -gt 0 ]]; do
  case "$1" in
    --include)
      if [[ $# -lt 2 ]]; then
        usage
        exit 2
      fi
      include_paths+=("$(realpath "$2")")
      shift 2
      ;;
    *)
      echo "unknown argument: $1" >&2
      usage
      exit 2
      ;;
  esac
done

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
crt_include_win="$(path_to_windows "$msvc_root/include")"
sdk_include_win="$(path_to_windows "$msvc_root/PlatformSDK/Include")"
include_flags=()
for include_path in "${include_paths[@]}"; do
  include_flags+=("/I$(path_to_windows "$include_path")")
done

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
  "${include_flags[@]}" \
  "/I$crt_include_win" \
  "/I$sdk_include_win" \
  "/Fo$output_win" \
  "$source_win" \
  2> >(filter_preload_noise)
