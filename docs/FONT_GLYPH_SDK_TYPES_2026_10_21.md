# Glyph SDK types and fresh coordinate controls

Scope: `TextTextureFontView_draw_text_glyph @ 0x00411B80`, original Japanese
TH10.5 v1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
This checkpoint adds **no exact credit**.

## Observed target and build facts

The fresh raw-PE packet in
`build/font-glyph-coordinate-20261021/baseline-facts.json` independently closes
the 624-byte candidate at RET12 `411DED`, ending exclusively at `411DF0`.
Its SHA256 is `3e67460ec4d76b1bdf2e30566a9dc74d44c3d34116e847e49ea78667bfb93630`.
All 189 instructions decode, 187 are reachable, and the eight skipped alignment
bytes at `411CD8..DF` remain in the comparison. Direct calls are array allocation,
array release and accent rendering; two indirect calls use the GDI IAT cell
`6C0010`. These are raw-byte observations, independent of the rejected IDA
session. The target/status/tracking preflights pass; IDA still opens the wrong
SHA256 `10350095bcf95edb59e03bee9849a2dc8a7714b4927ad5909c569c550fce6822`.

The new baseline reproduces glyph canonical SHA256
`a1f0b4e58a76926fa837cdd852256122752fea9e5c9226332fc02139a8ac7806`,
first differing at `411BD9 / +89`. All differences remain inside `+88..103`:
target loads ascent, subtracts the glyph origin and adds cached cursor Y;
source starts with cached cursor Y and adds ascent after subtracting the origin.
No boundary shortening or equality waiver is used.

## External corroboration and selected source

The pinned VC8 Platform SDK supplies a more precise API type than the retained
flattened `int` fields. `WinGDI.h:2512` declares `GLYPHMETRICS` with UINT black
box dimensions, a nested POINT origin and two short cell advances.
`WinDef.h:327` declares POINT with LONG x/y, and `WinNT.h:258` defines LONG as
`long`. These are SDK declarations, not proof of the game's nominal source.

`TextFontRender.cpp` now represents that nested pair with two `long` members.
The existing 20-byte size check is retained; origin offset 8 and cell-advance
offset 16 are asserted. Glyph and accent use the corresponding nested members.
No owner/header layout, calling convention, compiler profile, TU partition or
relocation binding changes.

Three serial controls are retained privately: native LONG fields, a meaningful
inline glyph-top calculation used at its three actual sites, and the native
nested POINT layout. Every control reproduces all 12 previous full canonical
function hashes and sizes. Only the SDK layout correction is selected; the
inline helper is not added to reconstruction source. This rules out those
specific type/inline controls as solutions at this source epoch, not other
source shapes or compiler contexts.

## Focused verification and remaining unknowns

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-text-font-render --compare --json
```

The selected-source report is
`build/font-glyph-coordinate-20261021/formal.json`. It reproduces all 12 baseline
hashes and extents: eight mismatches, accepted surface45/hex45/blend289 exact,
and the uncredited checked-character33 byte-equal origin-review helper.
Only this source's accepted unit is affected. No runtime sweep or aggregate
cold replay is presented as new evidence: the compared instruction streams
did not change. The earlier execution receipts retain their own source epochs.

Private reproduction/capture scripts and controls are in
`.analysis/font-glyph-coordinate-20261021/`. The original coordinate expression,
original TU/profile, real GDI, allocation failure and EH unwinding remain open.
The glyph is still nonexact. Larger font and Reimu roots are not advanced by
this type correction.

The subsequent [arithmetic/compiler controls](FONT_GLYPH_ARITHMETIC_CONTROLS_2026_10_22.md)
revalidate the selected source, isolate the top local without changing its loops,
and test actual SDK GDI declarations plus independently identified .42 compiler
components. Those controls reproduce the complete624-byte residual; `/Os` gives
579 bytes and differs at entry. No further source or exactness change is selected.
