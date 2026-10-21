# Native font glyph: source recovered, full span nonexact

`TextTextureFontView::draw_text_glyph @ 0x00411B80` now has genuine C++ source
in the actual font entry TU. Its complete624-byte target span compares against
647 bytes/192 source instructions, full-source canonical3e8ea4fa, nonexact at+3. This is a
source-present checkpoint with **no new exact credit**. All5,376 bounded
instruction-level observer cases pass; negative controls reject fixed-row
color and recomputed post-wrap output extents.

Only original Japanese TH10.5 v1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. Target/status/tracking preflights pass. IDA rejects its wrong open
executable; no database semantics/writes or original patches are used.

## Observed boundary, API and ABI

Full target SHA256:
`3e67460ec4d76b1bdf2e30566a9dc74d44c3d34116e847e49ea78667bfb93630`.
Raw traversal closes through RET12 at411DED. Of189 decoded instructions,
187 are reachable; the two skipped alignment instructions at411CD8..DF occupy
eight internal bytes. They remain in the whole624-byte comparison. The full source extent is independently inspected through its own RET. The
ordinary comparator records647 bytes of source extent and hashes the624-byte
compared prefix as97e6625a; independent complete647-byte relocation replay has
hash3e8ea4fa. Neither the prefix nor matching partial paths receive exact credit.
No compiler boundary is invented to hide the23-byte size difference. The current
strict linked-body gate rejects unaccounted unreachable bytes; it is unchanged.

The reviewed normal font entry412670 calls at412756 with font in EAX and
character/width-output/height-output stack words. The implementation retains
an ordinary nonvirtual C++ member declaration; it does not fabricate a register
ABI. Its actual accent callee411DF0 receives the same owner in ESI and two
stack coordinates, RET8. That helper remains a normal source declaration and
an unselected implementation hypothesis; it receives no source/exact credit.
The direct caller census covers tracked main instruction streams, not arbitrary
indirect entries or remote chunks.

The pinned PE import table identifies6C0010 as GDI32!GetGlyphOutlineA. Both
calls pass format5, a genuine20-byte GLYPHMETRICS object, and MAT2 at6FA594.
The pinned x86 SDK MAT2 has four4-byte FIXED members, total16 bytes. Initial
mapped bytes encode identity. Accent uses the different adjacent16-byte matrix
at6FA5A4; the retained accent source's shared-matrix assumption is unverified.
New relocation entries attest the actual IAT DWORD and full main matrix, with
no fabricated global definition or original initializer claim.

## Recovered behavior

The initial metrics are zero-initialized. Query failureFFFFFFFF returns before
cursor/output writes. Otherwise unsigned buffer bytes / metrics.height is
computed and masked with~3, before clipping or the zero-byte gate. Height0
therefore faults even when the query returned0; the source adds no guard.

Width/height are captured from the first metrics. Bottom is ascent-originY+
cursorY+height, and right is cursorX+originX+width. Bottom>=signed surface height
returns. Right>signed surface width either returns when wrap11E is0, or resets
cursorX to originX124+the full unsigned outline11D byte and advances cursorY by
font-height114+spacingY130. The already computed right/bottom are retained.
There is no added top/left clipping or post-wrap height check.

For nonzero bytes, allocate exactly that many unsigned chars and request the
raster into them. The second call's return status is ignored; its updated
origin and advance fields are used, while loop dimensions and stride retain
the first query values. The updated owner cursor determines destination140.

With an active table154, its row pointer starts at ascent-secondOriginY and
advances once per glyph row. With no table, fallback168 is read for pixels.
Each destination word is color OR `((0x0ff00000u * coverage) & 0xff000000u)`.
Source and destination advance by their respective strides; buffer deletion
precedes the accent call. This preserves target read/write policy rather than
normalizing alpha arithmetic or clipping.

Accent16C calls the observed provider with cursorX+signed advanceX/2 and
cursorY-fontHeight; signed division rounds toward zero. Then advanceX+
spacingX12C updates cursorX. Each nonnull output becomes the unsigned maximum
of its old value and the **pre-wrap** right/bottom, width before height.
Aliased outputs therefore retain the ordered writes.

The prefix header replaces only target-proven wrap and spacing bytes with
fields, preserving physical offsets and native list layout. The nominal glyph
metric/transform definitions also agree with the existing TU to avoid conflicting
C++ type definitions; full generated bodies remain byte-identical. The full owner
constructor/destructor/configuration remain in their separate, accepted TU;
no accepted owner source or declaration changes.

## Bounded verification and limits

Private Unicorn runs execute complete target and compiled source instructions.
They use explicit abstract GDI, byte-array allocation/release and accent callee
observers, checking both target-private and ordinary source argument locations.
Coverage includes short positive/negative glyph advances, changing second-call
metrics and failure result, table/fallback, wrap/outline/accent, clipped and
negative coordinates, zero-byte/failure/zero-height query results, and null,
separate or aliased outputs. Comparisons include ordered pixel/cursor/output
stores, logical calls, final bytes, ESP and saved registers.

All **5,376** selected cases pass. Genuine compiled controls fail:

| Wrong change | Failing cases | Detected effect |
| --- | --- | --- |
| retain first color row for every row | 816 | ordered stores and pixels |
| recompute right/bottom after wrap | 440 | ordered stores and output sizes |

Zero-height cases use fresh emulator instances and explicit divide-interrupt
observation; reusing a faulted Unicorn instance is not reliable. The harness
runs with bounded mapped buffers and abstract callees, not actual Win32 GDI.
Arbitrary aliases, protected-page read footprints, allocation failure,
unbounded coordinates and malformed metric contracts remain unclaimed.

The semantic source object and final current object produce identical complete
function bytes. Existing begin291/end168/text322 keep canonical728a7bf3/
e1daa198/7087f023; both texture candidates keep50731d79/15555b85. Their previous
regressions are not needlessly replayed when these full bytes are unchanged.
Glyph647 remains nonexact+3 on receiver, register/frame and provider context.
Actual accent/markup/blend closure is still needed before an honest whole-font
linked experiment; no fake linker providers or forced frame are introduced.

## Scope and reproduction

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-text-font-render --compare --json
# Expected comparison_failed: four configured nonexact spans, no resolver failure.
```

The new data keys also occur in the retained CompositeTextGlyph object, which
contains the accepted53-byte string predicate. That one conservative accepted
consumer is cold-rebuilt and remains53/53 exact. Source dependency and explicit
mapping/native-symbol audits find no other affected accepted units. Font and
texture nonaccepted units rebuild. No aggregate replay is claimed.

Glyph moves review->observed authored by its pinned complete hash, actual
font caller edge and game rendering policy, not by adjacency or GDI ownership.
`implemented.csv` gains one row; `matches.csv` is unchanged. Progress remains
a provisional-denominator ledger display, not a fresh aggregate verification.

Receipts, target/source disassembly, native and negative objects, final scoped
replay and semantic cases are under `build/font-glyph-20261021/`; recipes are
under `.analysis/font-glyph-20261021/`. Completed controls are compressed after
per-file hash readback. Final local gates:

```bash
python3 scripts/validate-tracking.py --require-target
taskset -c 0 nice -n 10 python3 scripts/ci.py
git diff --check
```

Next: real accent/markup1744/blend providers, then coherent full-font TU tuning.
The larger Reimu496540 root remains nonexact at49655F/+31.
