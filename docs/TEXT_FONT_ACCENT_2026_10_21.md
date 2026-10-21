# Native font accent provider: source and ESI contract

The complete dot rasterizer `0x00411DF0` now has genuine source in the actual
glyph/text TU. Its file-local typed C++ definition naturally receives the font
in ESI and pops two coordinates, matching the observed target contract.
Source433/132 versus target417/129 remains **nonexact+5**. No authored exact
function or byte is added. All948 accent observer cases and all5,376 changed
glyph-caller cases pass.

Only original Japanese TH10.5 v1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. Target/status/tracking preflights pass; IDA rejects its wrong open
executable. Raw pinned PE instructions supply all accepted target observations.

## Observed target policy

The whole417-byte/129-instruction CFG is reachable, closing at RET8/411F8E.
Target SHA256:
`1bfd2e56e3163f29c0574f58ee41be36149f5c4defc91d62e8a9039e586bda33`.
Reviewed glyph411B80 calls at411DA6 with the ESI owner and two signed DWORD
coordinates. The raw main-candidate census finds that edge; it is not a claim
about arbitrary indirect or remote entries. Game font/surface/table ownership
and this actual caller establish authored policy independently of GDI origin.

The two GetGlyphOutlineA calls use dot2E, format5, a real20-byte metrics object
and the distinct16-byte MAT2 at6FA5A4. Main glyph uses6FA594. Both matrices have
identity initial bytes, but their different observed addresses are preserved;
the old retained accent implementation's shared address is not inherited.

Metrics are initially zero. QueryFFFFFFFF returns. Otherwise unsigned
bytes/firstHeight is masked with~3 before clipping or testing bytes0, so a
zero height still raises division by zero. First width/height determine loops;
first originY determines clipping. Return when top+height>=signed surface
height, top<0, or bytes0. There is no added horizontal or post-raster clip.

Allocate an unsigned-char array of exactly bytes and request the raster.
Ignore the second status; use its updated originY and **unsigned second width
>>1** to center destination140 around centerX. The loop dimensions and stride
remain from the first query. The target reloads the current first active154
word for each pixel, without the main glyph's row-color advancement. The
fallback branch reads168. Both paths preserve native alpha multiplication,
ordered stores, source/destination strides, then delete the byte array.
No cursor, dimension output, member list or GDI handle updates are added.

## Compiler contexts and remaining difference

A real ordinary member in the actual caller TU is434/135, canonical454a984a,
nonexact+3 with ECX receiver. The selected file-local stdcall definition is433/
132, full canonicald0a47cc5, and naturally uses target ESI. It is not an external
register facade or an exported helper. Its genuine caller passes the existing
ESI owner and no longer emits the ordinary member's ECX setup: glyph shrinks
647->645,192->191 instructions, full canonical51eb276d, still nonexact+3.
Original method-versus-file-local source spelling remains unknown.

Target promotes topY to EBX before the first API call and later reuses its
argument slot for height. Source keeps topY on the stack and promotes width/
height/stride differently. The remaining issue includes frame, register and
argument lifetimes; matching the receiver alone does not recover the function.
Two natural loop-count controls do not resolve it: mutable post-decrement is
416/129 with a different28-byte frame/CFG, and a positive remaining-count for
loop is441/136. Neither is selected. No frame filler, fake return, assembly,
forced register or inert local is used.

The formal comparator records complete433-byte source extent and compares the
417-byte target-sized prefix; the independent native COFF inspection replays
all433 bytes through RET8. Full zero-difference acceptance is not claimed for
a size coincidence, prefix or logical regression.

## Bounded actual-instruction regressions

Private Unicorn executes complete target/source bodies with explicit abstract
GDI and byte-array allocation/release observers. Cases vary first/second
metrics, raster failure result, table/fallback, top/center positions, zero-byte
query, query failure and zero-height divide. Divide cases use fresh emulators.
Ordered calls/stores, final pixels, unchanged owner, ESP and saved registers
agree in **948/948** cases. No real Win32 GDI, arbitrary alias, allocation-failure,
protected-page or unbounded-coordinate coverage is claimed.

Two genuine compiled controls are rejected:

| Wrong policy | Failing cases |
| --- | --- |
| center using captured first width | 170 |
| advance accent color by row | 120 |

The changed actual glyph caller is separately rerun with its new real ESI
accent call contract: all5,376 existing cases pass again. The helper boundary
uses abstract accent effects in that caller test; this is not a claim that a
real GDI integration test ran. Begin291/end168/text322 keep their previous
complete byte hashes. Texture110/264 candidates also remain byte-identical.

## Scope, ledger and reproduction

The source prefix removes the unused ordinary accent-member declaration; it
keeps physical layout unchanged. The new separate matrix key is appended to
the relocation ledger without changing any existing row or IAT binding.
Dependency, explicit-mapping and available native-symbol audits find no
accepted consumers. All predecessor accepted-unit definitions remain unchanged.
Only the two affected nonaccepted font/texture units rebuild; there is no
unrelated or aggregate cold replay.

The target417 moves from review to observed authored using its full hash and
actual glyph E8 edge. `implemented.csv` gains the genuine accent source;
`matches.csv` is unchanged. Progress remains a provisional-denominator ledger
snapshot. Both source/target full extents and current receipts are retained.

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-text-font-render --compare --json
# Expected comparison_failed: five nonexact functions, no resolver failure.
python3 scripts/validate-tracking.py --require-target
taskset -c 0 nice -n 10 python3 scripts/ci.py
git diff --check
```

Reports, full disassembly, frozen selected/control inputs and regression
receipts are under `build/font-accent-20261021/`; private recipes are under
`.analysis/font-accent-20261021/`. Completed controls are losslessly compressed
with per-file hash readback before loose deletion. Next: actual blend and
markup1744 providers, then coherent full-font linked/source-lifetime recovery.
Reimu496540 remains nonexact at49655F/+31.
