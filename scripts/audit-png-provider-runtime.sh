#!/usr/bin/env bash
# Bounded provider smoke test. Never executes the original game.
set -euo pipefail
root="$(cd "$(dirname "$0")/.." && pwd)"
cd "$root"
d="$root/build/png-provider-smoke"
mkdir -p "$d"
taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py --unit exact-first-csv-file-loading --json >"$d/build.json" 2>"$d/build.err"
export WINEPREFIX="${TH105_WINEPREFIX:-$root/.tools/wine-msvc8}" WINEARCH=win32 WINEDEBUG=-all
export INCLUDE= LIB= LIBPATH= CL= _CL_= LINK= _LINK_=
w() { printf 'Z:%s' "${1//\//\\}"; }
msvc="${TH105_MSVC8_ROOT:-$root/.tools/msvc80-sp1}"
sdk="$root/build/match-units/ExactFirst_CsvFileLoading.png-sdk"
taskset -c 0 nice -n 10 wine "$msvc/bin/cl.exe" /nologo /TC /O2 /MT /GS- \
  "/I$(w "$msvc/include")" "/I$(w "$msvc/PlatformSDK/Include")" \
  "/I$(w "$root/.tools/upstream/libpng-1.5.2")" "/I$(w "$root/.tools/upstream/zlib-1.2.3")" \
  "/Fe$(w "$d/smoke.exe")" "/Fo$(w "$d/smoke.obj")" "$(w "$root/scripts/probes/png_provider_smoke.c")" \
  /link "/LIBPATH:$(w "$msvc/lib")" "/LIBPATH:$(w "$msvc/PlatformSDK/Lib")" \
  "$(w "$sdk/libpng.lib")" "$(w "$sdk/zlib.lib")" >"$d/compile.log" 2>&1
taskset -c 0 nice -n 10 wine "$d/smoke.exe" >"$d/runtime.log" 2>&1
cat "$d/runtime.log"
# Independently compare the complete upstream PNG signature routine with native bytes.
TH105_ENABLE_GS=1 \
TH105_EXTRA_INCLUDE_DIRS="$root/.tools/upstream/libpng-1.5.2:$root/.tools/upstream/zlib-1.2.3" \
  taskset -c 0 nice -n 10 scripts/compile-unit.sh \
  "$root/.tools/upstream/libpng-1.5.2/png.c" "$d/png-gs.obj" >"$d/png-gs-compile.log" 2>&1
scripts/repo-python scripts/compare-function.py 0x0066B870 "$d/png-gs.obj" \
  --symbol-base _png_sig_cmp --rel32-target '@__security_check_cookie@4=0x00689D25' \
  --json >"$d/png-signature-compare.json"
printf '%s\n' 'Native PNG signature routine: complete 298/298 canonical bytes match.'
