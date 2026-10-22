# Markup construction cleanup belongs to the deque insertion

Scope: `TextFont_parse_text_markup @ 0x00411FA0`, original Japanese1.06a
SHA256 `56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
This checkpoint identifies the fourth target cleanup state and its actual CIL
owner. It changes no reconstruction source, profile, ABI, boundary, origin
classification or exact acceptance. IDA preflight rejects the other open image;
all target observations below come from the hash-attested raw executable.

## Observed target construction and cleanup

The complete1744-byte main body retains SHA256
`6343d2d6639459aaeadb9de2acd74ecbb0be02f8a908e4b84af385f1daeccebb`.
Its sole RET8 is at41266D, ending exclusively at412670. Target and current
native source both receive font in EDX, height output in ECX and cursor/width
output in two stack words. A private previous next-step note incorrectly said
three stack words/RET12; that note is corrected. No ABI change follows.

The handler6BE2A8 refers to FuncInfo6E49EC and UnwindMap6E49CC:

| State | Previous state | Action | Observed role |
| --- | ---: | --- | --- |
|0|-1|6BE270 ->40F8E0|Deque destructor, receiver EBP-320|
|1|0|6BE27B ->401E00|Temporary string destructor, receiver EBP-2F8|
|2|1|6BE286 ->402810|Two-argument placement-construction failure cleanup|
|3|0|6BE29D ->4114C0|Ruby font destructor, receiver EBP-1B0|

Here EBP is the enclosing entry-frame coordinate used by the cleanup funclets,
not the normal body's repurposed EBP register. FuncInfo fields are
`19930522,4,6E49CC,0,0,0,0,0,1`. Handler46 bytes, FuncInfo36 bytes, unwind-map32
bytes and every action encoding are retained in the reproducible audit packet.
This is static ownership evidence, without a handler/unwinding equality claim.

Normal code412102 loads ECX from the deque map entry.412106/41210A save that
same pointer at fixed-frame+40/+60.412110 writes state2. For nonnull ECX, the
code initializes string capacity15, length0 and its first character0, then
calls4020D0 with the temporary string at fixed-frame+44 and range0/npos. The
map allocation immediately above requests28 bytes. This identifies placement
copy construction of a deque string element, rather than another font owner.

The failure action reads the two saved pointers at EBP-2FC and EBP-2DC, pushes
them, calls402810, discards8 argument bytes and returns.402810 itself is exactly
one `RET`, followed by15 INT3 alignment bytes. The current native COFF has the
same four-state graph `[-1,0,1,0]`; action2's REL32 explicitly names
`??3@YAXPAX0@Z`, the two-argument placement delete.

## External corroboration from the pinned VC8 headers

The selected SP1 headers provide a coherent source explanation:

- `deque`, lines810..827: `push_back` allocates the missing block, calls the
  allocator's `construct`, then increments the size.
- `xmemory`, lines48..54: `_Construct` converts the destination to `void*`
  and uses `::new (_Vptr) _T1(_Val)`.
- `new`, lines57..65: placement new returns its destination; the matching
  two-argument placement delete has an empty body.

The audit records each complete header SHA256. These headers corroborate the
operation and native relocation identity; they do not prove the original
header release or spelling of the game's source.

## Observed CIL ownership: three states plus one

The configured genuine owner/render CIL image is checked through the ordinary
accepted color comparison, including build provenance and the actual
renderer -> markup -> color path. Its parser10001E50 is1572 bytes. The actual
call10001F6E invokes the separately emitted156-byte `deque<string>::push_back`
at100027D0.

The parser's three-state graph is `[-1,0,0]`: deque, temporary string and font.
The outlined push_back has its **own** handler10003525 and FuncInfo1000451C,
with one state0 ->-1. Its action10003520 jumps to the real placement delete
at100010D0, whose complete body is the same single `RET`.

Thus the extra construction cleanup has moved into a called helper. It has
not disappeared from the image, and parser state counts alone do not establish
a missing authored local, a missing destructor, or deletion of the empty
cleanup. No exception execution or whole-function equivalence is established.
In particular, simply contracting a four-node graph to three would omit the
actual observed helper ownership.

## Shared one-byte body prevents a compiler-only exclusion

A raw E8/E9 census over the complete target `.text` finds30 references to
402810. Each decodes as two enclosing-frame loads/two pushes, E8, ADD ESP8
and RET. All-section, byte-position DWORD scanning finds one additional
reference: aligned `.rdata` slot6D6A74.

That pointer is slot5 of the seven-entry vtable at6D6A60. Its COL6DCBA0 names
`.?AVCDesignObjectBase@@` through the target RTTI type descriptor. This is a
shared authored virtual surface as well as a placement-delete destination,
consistent with identical-code folding. The single-byte equality cannot
separate their ownership.402810 stays `unknown/review`, with no durable
compiler-only name, exclusion, source selection or authored exact credit.

## Two concrete context controls

The existing comparison input includes `TextFontOwner.cpp` and
`TextFontRender.cpp` in one CIL TU. A new private control compiles those same
two real files separately with the identical SP1 O2/GL/GS/GR/EHsc/MT flags,
then links both real CIL objects, unchanged data bindings/CRT libraries and
the same sole renderer export. There are no synthetic private exports or
helper definitions. This differs from the previous native-owner control.

The separately compiled parser remains1572/frame788, with the actual outlined
push_back call. All four complete leaf payloads remain identical to the
configured context: color352/end168/reset162 exact and begin291 nonexact+59.
This source partition is not selected and does not identify the original TUs.

After the same-release msobj80 repair, a genuine RTM O2/GL/**Zi** compile is
also attempted with a distinct compiler PDB path. It still fails C1902 before
producing a completed CIL object, so the planned `/DEBUG` link is not reached.
The loader log positively identifies the RTM mspdb80.dll and c1xx.dll actually
loaded. It also reports unsupported RPC authentication service10; file-version
agreement alone does not establish a healthy manager/server connection. No
binary is patched or foreign manager copied. The exact environmental cause,
successful PDB context and its possible code-generation effect remain unknown.

## Reproduction and remaining work

Build the two configured units serially if their products are absent/stale,
then run the static audit:

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-text-font-render --json
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-text-font-color-linked --json
taskset -c 0 nice -n 10 python3 scripts/audit-text-font-markup-cleanup.py --json \
  > build/font-markup-cleanup.json
```

Private controls/recipes are in `.analysis/font-markup-guard-20261022/`;
full audit, command/tool hashes, loader logs and split-TU reports are in
`build/font-markup-guard-20261022/`, including the four full canonical leaf
receipts in `split-cil.json`. Four in-memory negative controls reject an
unsupported state count, try map, cyclic unwind edge and unterminated action;
the original four-state packet passes. No executable/database is patched.
Seven finished private split PE/COFF/map artifacts are archived with every
member SHA256 checked before loose removal:657821 ->163800 bytes. Configured
inputs stay present. Restore the control before re-reading its image:

```bash
tar -xzf build/font-markup-guard-20261022/completed-split-context.tar.gz \
  -C build/font-markup-guard-20261022
```

The selected native markup still differs+16:1728/frame788 versus1744/frame796.
Its current ABI and four cleanups already agree in role with the target.
Focus subsequent work on that native lifetime/frame residual or on an
independently evidenced real compiler context. Do not add dummy RAII, padding,
arguments or larger owner storage to force a state count. The CIL state split
is explained, rather than an independent reason to change authored behavior.

Strict ledgers remain1381 functions/234914 bytes out of2136806 authored bytes
(10.99%). The two relevant units receive a fresh serial cold replay of their
six accepted functions. This is no new aggregate all-unit cold replay claim.
