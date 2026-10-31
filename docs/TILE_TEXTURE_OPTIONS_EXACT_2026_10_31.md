# CTile texture options: complete canonical match

`0x004098E0` is **266/266 exact**, SHA256
`468f1bb43c61785642e6920148c91daed69bba0746a8a7d1a5d08e31c3ba7138`.
The normal ECX receiver and RET28, all branches, sole texture-size call and
five numeric literal references are checked by the unchanged linked comparator.
There are no EH regions, switch metadata or skipped alignment sites.

## Target evidence and source

Only original Japanese1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. Target/status/tracking checks passed. Factory-native IDA metadata,
entry, five mapped samples, inventory, complete disassembly/decompilation and
callers/callees were read; the samples were checked against the pinned PE.
Raw operands establish signed input dimensions/anchors, unsigned returned
texture dimensions, repeated independent denominator conversions and four
separate division/store operations. The native unsigned corrections use
float2^32 at6D6EF8; Z uses float0.5 at6CD140. Existing authored-origin evidence
and five native callers are unchanged. Decompiler EAX residue does not make
this void initializer return a value.

The original setter is extracted to `src/ui/CNumberTileTextureOptions.cpp`;
`CNumberRuntime.cpp` includes it and retains its other bodies. The initializer
now uses the actual `TitleResourceManager` declaration and global, replacing
the declaration-only equivalent query view. No layout/header is changed.
`CNumberTileTextureOptionsUnit.cpp` includes the real texture query and checked
token lookup. Public provider methods remain available as genuine normal
methods; there is no fake caller, custom ABI or noinline barrier.

An initial CIL build without scoped FP-environment access emitted242 bytes and
reused converted denominators. Native instructions independently convert each
unsigned denominator before its division. Scoped `fenv_access(on)` preserves
those operations and the native x87 store schedule, yielding the complete266
bytes. The setting ends after this method. It is a source/compiler-context
hypothesis, not a claim that the original source contained this pragma. No
volatile values, dummy slots, copied bytes, register forcing or option grid
was used. Earlier ordinary strict-float270/266 evidence is superseded only for
this genuine provider context.

## Validation

- `scripts/repo-python scripts/build.py --unit exact-first-tile-texture-options --compare --json`: exact266/266.
- `scripts/repo-python scripts/build.py --unit gpt-web-cnumber-runtime --compare --json`: accepted render414F10 stays312/312; initializer414E40 stays102/104 nonexact.
- Actual quoted-include dependency traversal identifies only those two units
  as affected. Shared query/lookup sources and headers are unchanged; other
  accepted receipts are preserved, not cold-replayed.

Receipts and IDA evidence are under `build/frontier-tile-cil-20261031/`;
the same-session metadata/mapped-byte check is retained under
`build/frontier-rectangle-cil-20261031/ida-preflight.json`. Private generation
recipes are under `.analysis/frontier-tile-cil-20261031/`.
Incremental totals are1545 exact functions /438021 bytes. No provider or
origin credit is added, and no runtime/general equivalence claim is made.

## Other bounded negative results

The interrupted Tenshi649330 experiment had actually finished compiling. Its
real-provider CIL still emits3252 bytes versus3268 target payload bytes, with
a direct-branch displacement mismatch at+0xA6 before any external relocation.
This is sufficient to reject exactness, not a full canonical equality report.
No source spelling control or production change was made.

Rectangle4012A0 with actual line/binder/lookup CIL emits410/native395. Complete
linked replay first differs at+9 because EDI remains shrink-wrapped; the actual
binder also inlines. This does not reopen the previously closed source-lifetime
lane. Both experiments remain private and add no exact credit.
