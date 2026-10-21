# Native glyph ABI and cursor lifetimes:624 bytes, not exact

`TextTextureFontView_draw_text_glyph @ 0x00411B80` now has a genuine file-local
C++ implementation with the target's compiler-generated EAX font/RET12
contract. Complete source shrinks645->624 bytes/189 decoded instructions,
canonical `a1f0b4e58a76926fa837cdd852256122752fea9e5c9226332fc02139a8ac7806`.
It remains **nonexact at411BD9/+89**. No match or byte credit is added.

Only original Japanese TH10.5 v1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. Required target/status/tracking preflights pass; IDA rejects its wrong
open executable. Fresh raw-PE facts pin the target's complete624-byte hash:
`3e67460ec4d76b1bdf2e30566a9dc74d44c3d34116e847e49ea78667bfb93630`.
The189 decoded instructions include187 reachable instructions and8 skipped
alignment bytes at411CD8..DF. They remain in every complete comparison and are
generated naturally by the selected source; nothing is cropped or padded.

## Actual caller and recovered source lifetimes

The tracked candidate main-instruction census finds one direct call at412756
in reviewed render412670, with font in EAX and three stack words: character,
width_out and height_out. A normal file-local typed stdcall definition in that
actual TU naturally reproduces the private entry. The unused member declaration
is removed from the native font header; the existing durable descriptive name
is retained. Original nominal method/function spelling and original TU remain
unknown. Private register evidence alone is not treated as a LTCG requirement.

Changing visibility alone keeps645 bytes. Target instructions also establish
two real cursor lifetimes. The coverage cursor is initialized before the second
GDI call and supplied as its output buffer, remaining in a preserved register
for the following traversal; the allocation base remains available for delete.
That source lifetime recovers625 bytes and the target's register allocation.
Storing through the current destination and then advancing it, independently
of the RHS coverage increment, recovers the remaining native loop shape and
624 bytes. Both cursors are used for their real buffer ownership/traversal;
there is no inert local, register facade, assembly, fake provider or padding.

All source bytes outside the16-byte window+88..103 match. Inside it, four
instructions commute the lower-bound calculation:

| Target | Current source |
| --- | --- |
| load ascent into EDI | move cached cursorY from EDX to EDI |
| subtract metric originY | subtract metric originY |
| save cached height | save cached height |
| add cached cursorY | add ascent from the font |

The subsequent height addition and every later instruction are identical.
The operations produce the same bounded coordinate result, but their bytes
are different. Equal size, mathematical equivalence and a matching remainder
do not qualify the whole function as exact. Explicit top/cursor caches,
equivalent coordinate forms, unsigned-ascent/raw-DWORD extent controls and
RTM versus SP1 do not eliminate this residual. Those unselected hypotheses are
not added to the source or promoted to type facts.

The GDI import remains independently verified as GetGlyphOutlineA at6C0010.
Both calls use the16-byte MAT2 object at6FA594, distinct from the accent
transform. Current source retains signed clipping, pre-wrap extents, second-call
metric updates, native table-row advancement/fallback alpha writes, ESI accent
call and post-call cursor/output reloads from the earlier bounded recovery.

## Execution and affected caller

All **5,376/5,376** actual target/source glyph instruction cases pass with
explicit GDI, array and accent observers. This replay uses the real EAX glyph
and ESI accent contracts. It checks ordered query/raster arguments, zeroed
metrics, second-call writes, first-query failure, the actual zero-height DIV
exception, allocation/release, wrapped clipping, row colors, signed accent
half-width, optional/aliased output dimensions, final bytes and normal ABI
restoration. Callback assertions stop the emulator and are raised outside the
callback. Fresh fault engines are collected promptly to bound memory.
Real GDI, EH unwinding, allocation failure, arbitrary font/stack aliases and
unbounded overflowing coordinates are outside these observer tests.

The render caller remains322 bytes/115 instructions, canonical
`aed258a67b2d829a4c8352208eda1f506f255b0ee0798a0677d669aca790ef99`.
Only ModRM byte+258 changes: `mov ECX,ESI` becomes `mov EAX,ESI` for glyph.
The previously recovered EAX blend call is unchanged. Only **160 affected flat/outlined caller cases** replay, all passing. The80
outlined cases execute the real289-byte blend; glyph/GDI and other providers remain observers in those caller cases.
The standalone5376 cases execute the actual glyph separately. The broad old
caller/tag sweeps are not repeated or presented as new runtime coverage.

The other nine complete font bodies remain unchanged. Removing the unused
member declaration affects exactly two accepted units: font render and font
owner. Both cold-build: exact hex45/blend289 and owner ctor138/dtor210/
configure439/config ctor67 persist; compiler-only Tidy71 also stays exact.
The nonaccepted text-texture header consumer rebuilds and retains its110/264
full candidate hashes. No profile, public TU partition or existing data/
relocation ledger changes; exact totals remain the previous ledger snapshot,
with no aggregate cold replay claim.

## Genuine full-font GL diagnostic

A private analysis TU includes the actual public owner and render sources:

```cpp
#include "../../src/assets/TextFontOwner.cpp"
#include "../../src/assets/TextFontRender.cpp"
```

It compiles with the pinned native `/O2 /GL /GS /GR /EHsc /MT` configuration
and links through the existing `linked_pe.build_linked` machinery, exporting
the real render entry. All actual ctor/dtor/config/render/STL/runtime providers
resolve. The known main-window/MAT2 globals and real Win32 IAT slots use the
existing target-verified ABS **data** binding mechanism, which rejects code
addresses. There are no placeholder functions or executable ABS substitutions.
Original TU partition is not inferred from this analysis union.

Its raw linked glyph is624/189. Replaying its three actual E8 roles (array
new, array delete and the real accent helper) gives the identical canonical
`a1f0b4e5` body and the same arithmetic residual; glyph has no image-base
relocations. Thus this concrete experiment does not support blaming the
residual on absent LTCG. The linked caller becomes334/119 with an aligned EBP
frame, which is new source-context evidence, not a match for target326/120.

These are diagnostic observations only. The private analysis source is not a
reviewed ledger source/caller unit, full linker/parent EH ownership is not
qualified, and the generic linked closed-CFG gate still rejects the8 skipped
bytes. It is not weakened, bypassed for acceptance or used to grant any exact
credit. Original arithmetic typing/association and remaining private/TU/frame/
GS/EH questions stay open.

## Reproduction and handoff

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-text-font-render --compare --json
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-text-font-owner --compare --json
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-text-texture-runtime --compare --json
python3 scripts/function-origins.py --check
python3 scripts/validate-tracking.py --require-target
taskset -c 0 nice -n 10 python3 scripts/ci.py
git diff --check
```

The font-render comparison intentionally exits comparison_failed: glyph and
eight other candidates remain nonexact, while hex45/blend289 stay exact.
Selected source/COFF/full-function proofs,5376/160 receipts and genuine linked
metadata are retained in `build/font-glyph-local-20261021/`; private recipes are
in `.analysis/font-glyph-local-20261021/`. Unselected controls are archived only
after per-file SHA readback verification.

Next: continue exact recovery of the remaining coordinate expression and
setter/markup caller visibility, using the resolved native link as evidence
rather than assuming a nominal method/TU. Reimu496540 still first differs at
49655F/+31.
