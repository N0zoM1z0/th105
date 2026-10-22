# Accent clipping bearing and coverage lifetime

Scope: `TextFont_draw_text_accent_dot @ 0x00411DF0`, Japanese1.06a target
SHA256 `56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Two source lifetimes are corrected from actual instructions. The selected
complete native body is now417 bytes/129 decoded instructions with a32-byte
frame, matching the target's size/frame. It remains **nonexact+6**; no exact
function or byte is added. The previous433-byte body is retained as a control.

## Target observations and the source correction

The hash-attested complete417-byte target decodes129 reachable instructions,
has one RET8 at411F8E and ends exclusively at411F91. Its SHA256 remains
`1bfd2e56e3163f29c0574f58ee41be36149f5c4defc91d62e8a9039e586bda33`.
The actual glyph411B80 caller at411DA6 uses ESI font and two DWORD coordinates.
There is no ABI, owner0x194/config0x128, header or calling-convention change.
IDA preflight rejects the other image; no IDA semantics or metadata writes
are used. Raw target bytes, actual call edges and instructions supply evidence.

At411E4E..411E68, EAX initially holds `font.ascent - firstMetrics.originY`.
The upper-bound sum adds first height, then topY; EAX still contains that
relative bearing at the upper clipping comparison. Only after that branch
does ADD EAX,EBX form absolute top and JS test its sign. The predecessor source
instead constructed absolute top before both tests. Its normal outputs agree
in the tested range, but the target-observed live bearing is lost.

The selected source therefore retains a used `bearing_top` in both checks:

```cpp
const int bearing_top = font->font_ascent_13c - metrics.gmptGlyphOrigin.y;
if (bearing_top + height + top_y >= static_cast<int>(font->surface_height_148) ||
    bearing_top + top_y < 0 || bytes == 0)
    return;
```

The target next saves the allocated byte-array base for deletion and places
the real coverage cursor in EDI before the second GDI call, at411E94. The same
cursor is passed as the raster destination and then advanced by pixel/row work.
The predecessor declared that cursor after GDI. The selected source establishes
`coverage = glyph` before GDI and passes the used cursor to it; array ownership
and eventual `delete[] glyph` remain separate. No inert variable or forced
register is added. This is the same kind of actual pointer lifetime that the
main glyph already required, now independently observed in accent itself.

These are reproducing source choices, not proof of original variable names or
spelling. First metrics still determine dimensions/stride/clipping; second
originY and unsigned half width determine destination. Real API results,
initial zero metrics, array size/release and per-pixel color reload policy stay
as recorded in the [original accent evidence](TEXT_FONT_ACCENT_2026_10_21.md).

## Complete contexts and controls

The existing genuine owner/render CIL image is first attested through its
ordinary accepted color comparison and actual renderer -> parser -> color
path. Its actual glyph100019A0 calls private accent100017E0 at10001BC6. The
entire433-byte CIL accent equals the predecessor native payload, after real
named call replay and address-field attestation. It does not recover the
target just by moving to that existing CIL context.

| Actual whole-source control | Full accent bytes / decoded | Canonical SHA256 prefix | Result |
| --- | ---: | --- | --- |
| Predecessor native and real CIL |433 /132|d0a47cc5|Nonexact+5|
| Relative bearing only, native and CIL |417 /129|ea76c99c|Nonexact+2; frame28|
| Relative bearing + early used coverage, native and CIL |417 /129|5a5cbf13|Selected native; nonexact+6; frame32|
| Also mutate the used topY coordinate explicitly |417 /129|5a5cbf13|Byte-neutral; spelling not selected|
| Positive remaining-count loops in the new lifetime phase |436 /136|e9a674ed|Unselected; not the target|

The countdown retest has a new independently observed clipping/cursor lifetime
phase; it is not a repetition of the older433-byte-context result. No compiler
flag, type, padding, fake return, source ABI facade or private export is added.
All controls include the real glyph and render callers. CIL controls include
real owner definitions and export only the ordinary renderer.

The selected complete canonical SHA256 is
`5a5cbf13767ef9a3b4e4a951ac2fdc945161813eea135f78cee5f031d9cf8a1b`.
All417 bytes remain in comparisons, including the skipped3-byte LEA at+253.
It has128 normally reachable instructions versus target129. The old source
had132 decoded/130 reachable and8 skipped bytes. The strict linked comparator
still rejects unaccounted unreachable instructions; diagnostics preserve them
and confer no linked acceptance or exception to that rule.

The current render CPP SHA256 is
`c51921db3773dc926ec3c4cccf470d86677a67c419e0b7e8a34b4d2beae27ecf`.
The ordinary native font unit/profile remains selected. Its six other complete
bodies and all five configured linked bodies retain their previous complete
hashes/extents; only accent changes. The six accepted functions persist after
the two relevant units are rebuilt cold and compared in full.

## Actual-instruction lifetime checks

Fresh Unicorn runs use the complete actual target and source instructions,
with explicit GDI query/raster and byte-array allocation/release observers.
The fixture checks arguments, zero metrics, first/second metric differences,
ignored second status, array ownership, ordered pixel/owner writes, final pixels,
normal RET8/ESP and callee-saved registers. The948 complete cases retain the
original matrix of table/fallback, clipping, query failure, zero-byte results,
changed second metrics and real zero-height #DE behavior. Fault engines are
fresh; no allocation-failure or actual GDI implementation is substituted.

Another112 prefixes vary originY/topY at INT32 limits. They execute the real
query and clipping instructions, then stop at the first actual new-array
entry or naturally return. No return from that allocation is fabricated,
and no out-of-range raster memory is accessed. These prefixes are not claimed
as full-RET coverage.

Two additional live snapshots are compared: EAX relative bearing, total and
six arithmetic flags immediately after the upper clipping CMP, and EDI coverage
immediately before the second GDI observer. All1060 cases preserve ordinary
effects in every source stage; the snapshots discriminate the lifetimes:

| Full/prefix source stage | Normal effects agree | Both live snapshots agree |
| --- | ---: | ---: |
| Predecessor |1060 /1060|56 /1060|
| Relative bearing only |1060 /1060|720 /1060|
| Selected relative bearing + early coverage |1060 /1060|1060 /1060|

The expected execution digest is
`6576993851ac8830aab95024b2cae5c7f55b31e9b64bebc97677b75c3a02ae2e`;
input digest is
`c187bf12430c7eab89cc2f48c2c807d0c8ba58977a2e223c962f2b7e3467fb0c`.
The final run reads the fresh configured public native object's complete
accent body and checks that it equals the reviewed early-coverage control.
This is bounded actual-instruction evidence under the explicit observer/buffer
contracts. It is not real GDI, arbitrary alias/overflow execution, allocation
failure, EH, full parent behavior, original source identity or exact matching.

## Reproduction and remaining work

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-text-font-render --compare --json
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-text-font-color-linked --compare --json
```

Mixed nonzero comparison exits remain expected for the pending functions.
The full selected accent must be417/5a5cbf13/nonexact+6; source-present remains
distinct from exact. Baseline/selected formal comparisons, complete CFGs,
canonical bodies, semantic/source/tool fingerprints and private native/CIL
control receipts are in `build/font-accent-cil-20261022/`. Recipes, including
the full execution audit, are in `.analysis/font-accent-cil-20261022/`.
Sixteen completed private object/image/map files are archived with every member
SHA256 checked before loose removal:1103801 ->274926 bytes. Configured public
inputs, canonical bodies and recipes stay present. Restore controls before
re-reading their images:

```bash
tar -xzf build/font-accent-cil-20261022/completed-controls.tar.gz \
  -C build/font-accent-cil-20261022
```

Early topY promotion and reuse of its argument home, first-width spilling,
pixel-loop placement and original compiler/TU ownership remain unresolved.
Length/frame recovery alone is not acceptance. Keep glyph's14-byte integer
residual, markup's8-byte frame residual and Reimu496540's larger source/physical
tail problem pending. Exact ledgers stay1381 functions/234914 bytes (10.99%);
the focused two-unit replay does not establish a new all-unit aggregate result.
