# Native outline blend: complete289/289 exact

`TextFont_blend_surface @ 0x004127C0` is canonical **289/289 bytes** under
ordinary VC8 COFF. A genuine file-local typed C++ helper in its actual font
render caller TU naturally receives font in EAX and source/destination on the
stack, with RET8. All95 decoded instructions and every byte of the target span
match, including the compiler-generated three skipped alignment bytes.

Full target/source SHA256:
`6c0d10cbbdbe63199d06e3a9bd44ee7ec11d4e128ab2a6ffbf74d42b1d86ce5b`.
Only original Japanese TH10.5 v1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. Required target/status/tracking preflights pass. IDA rejects its wrong
open executable; exact observations come from the hash-attested raw PE.

## Complete boundary, ABI and ownership evidence

The289-byte target ends in RET8 at4128DE..E0 before separate padding and the
hex decoder4128F0. The raw CFG reaches94 instructions. The only skipped bytes
inside this span are `8D 49 00` at41280D..0F, jumped over by41280B->412810.
They remain in the whole target/source comparison, and VC8 emits the same
instruction naturally. There is no source padding, copied byte sequence,
cropped tail or comparator waiver. Ordinary COFF owns the entire289-byte text
section through its RET. This leaf has no relocations, callee, jump table,
static storage, EH handler or unwind metadata to substitute.

The generic linked-PE closed-CFG validator still rejects these skipped bytes
as unaccounted; that gate is not weakened here. The accepted ordinary COFF
comparison includes them and proves equality of the entire native function
extent. It does not rely on a linked-PE alignment exemption.

The tracked candidate main-instruction census finds one call at41279F in
reviewed game font render412670. Its font parameter and application outline
policy establish authored ownership separately from nearby runtime code.
The retained member declaration was only a source hypothesis. The first normal
member implementation produced297 bytes/95 instructions, nonexact at+4 on
ECX entry and resulting loop/register context. Its114-byte pixel branch was
already identical, but that partial diagnostic was not exact credit.

Expressing the real definition as a normal `static unsigned char *__stdcall`
helper with its actual source caller recovers the complete target. The compiler
chooses EAX privately; no external register declaration, fake fastcall facade,
noinline annotation, inert local or assembly is used. The obsolete unused font
member declaration is removed. Original nominal spelling, original TU,
indirect/remote caller completeness and whether the original source intended
to expose the EAX result remain unknown. The selected signature exposes the
actual advanced destination cursor observed on all tested exits, including
empty-height paths; it does not invent a constant or shaping return.

## Observed pixel behavior

Height148, width14C and signed pitch150 are cached before writes. Both byte
pointers start one pitch into their planes. Only rows1..height-2 and
columns1..width-2 are processed; borders and row padding remain untouched.

For nonzero source alpha, the helper computes `min(alpha + 33, 256)`, writes
destination alpha255, then writes scaled source B, G and R in that order using
unsigned multiplication and a right shift8. Saturation begins at alpha223.
For zero source alpha, destination RGB stays intact. Destination alpha is
written four times: left alpha, maximum with right, maximum with above, then
maximum with below. These intermediate stores and sequential source reads are
preserved for overlapping planes. Row advancement uses the same signed pitch
for source and destination. Even when height<=2, EAX is destination+one pitch.

## Leaf execution and actual caller integration

All **4,608/4,608** actual target/source instruction cases agree with an
independent sequential pixel specification. It checks every byte write in
order, the whole64KiB plane, untouched font state, advanced EAX, ESP and saved
registers. Cases cover empty/interior sizes, positive/negative padded pitch,
eight alpha/color patterns, and separate/same/next-pixel/next-row plane overlap.
Threshold222/223 and propagation through overlapping writes are included.
Gain32 and clearing-retained-RGB controls fail864 and368 cases respectively.
Extreme overflowing dimensions and arbitrary font/stack aliases are outside
this bounded evidence; the complete canonical byte result remains separate.

The actual render caller stays322 bytes/115 instructions, now canonical
`4e41eb3ce0240706b40d0cb8bc27d73749c9a878312f42b66b06611adfa4b143`.
Its only byte change is ModRM at+299: `mov ECX,ESI` becomes `mov EAX,ESI` for
the genuine helper. It remains nonexact at+0 against the326-byte target.
Only **80 affected outlined caller cases** replay, all passing with the actual
complete289-byte blend executed80 times per side. They use interior4x8/pitch12
planes, colored glyph-observer writes, optional/aliased output pointers and
post-end destination replacement. Other CRT/GDI/markup providers remain
ABI-specific observers; no real GDI, EH unwinding or arbitrary-alias claim.
The previous13100-case broad observer sweep keeps its original phase scope.

The other nine previous font bodies remain unchanged, including markup1648,
color332, reset161, setter49 and accepted hex45. No unchanged parent/tag/text
sweep is repeated. Header removal affects exactly two predecessor accepted
units: gpt-web-text-font-render and gpt-web-text-font-owner. Both cold-build:
hex45 stays exact, owner ctor138/dtor210/configure439/config ctor67 remain exact,
and the compiler-only Tidy71 is still exact without authored credit. The one
nonaccepted header consumer, text-texture-runtime, rebuilds too; its full110/264
candidate hashes stay unchanged. Profiles, partitions and existing data/
relocation ledgers remain unchanged. No unrelated or aggregate exact replay
is claimed.

## Acceptance and reproduction

One authored exact function/289 bytes joins matches.csv. The font-render unit
has11 functions; its whole comparison intentionally exits comparison_failed
because nine candidates remain nonexact. Its independently accepted subset is
hex4128F0 and blend4127C0, both complete exact results.

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-text-font-render --compare --json
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-text-font-owner --compare --json
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-text-texture-runtime --compare --json
python3 scripts/validate-tracking.py --require-target
taskset -c 0 nice -n 10 python3 scripts/ci.py
git diff --check
```

Selected source/COFF/full289-byte proof, leaf/caller receipts and affected-unit
reports are retained in `build/font-blend-20261021/`; private recipes are in
`.analysis/font-blend-20261021/`. Completed controls may be compressed only
after per-file SHA readback verification.

Next: re-examine the glyph/setter/markup nominal-member hypotheses through real
caller visibility before assuming LTCG is required. Larger main functions,
their GS/EH ownership and the remaining save/frame residuals are still open.
Reimu496540 remains nonexact at49655F/+31.
