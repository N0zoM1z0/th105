# CBitmapData BMP loader: fresh boundary and source-form audit

Scope: original Japanese TH10.5 v1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Address `0x00419FF0`, authored/source-present in
`src/assets/CBitmapDataRuntime.cpp`, unit `gpt-web-cbitmap-data-runtime`.
This checkpoint adds **no exact credit**. Historical prose is a hypothesis;
current target instructions and fresh comparisons take precedence.

## Exact target observations

The callable is `[0x00419FF0,0x0041A8A6)`, **2230 bytes**, SHA256
`d02000b6f370ab70306453ff7cf7b7db73e184ed3533713c8a14c4d633c6f4df`.
`RET4` starts at `41A8A3`; `41A8A6` is its exclusive end, not its start.
Two alignment bytes `8B FF` follow. The five destination DWORDs at `41A8A8`
are `41A42B`, `41A493`, `41A60C`, `41A77C`, `41A84B`. The 25-byte index table
at `41A8BC` covers formats8..32 and ends exclusively at `41A8D5`. These45
metadata bytes are outside the callable and earn no authored-byte credit.

Raw decoding yields672 instructions. Normal CFG traversal reaches666;
six unreachable alignment instructions occupy21 bytes at `41A1F7`,
`41A1FE`, `41A53D`, `41A64D`, `41A6AD`, `41A6BD`. They remain in strict
comparison. Exception dispatch and remote EH funclets are outside this CFG
proof. Vtable `6D6E10`/COL `6DCFB0` identifies the CBitmapData runtime lane.

Ten direct CALLs comprise one `FileReaderOwner::open @40CF40`, seven
`operator new @665B8A` and two `free @68AA26`. Eight indirect CALLs cover
three reader deletions, two reads, seek, size and PNG fallback. Normal
cleanup expands the reader destructor; it has no direct `40CF20` calls.
The prolog allocates430h, preserves ESI as receiver, and places the palette
at steady-state ESP+44h. Its cookie/EH prolog does not imply a normal
`__security_check_cookie` CALL; none occurs in this body.

Three bounded direct Ghidra runs used a384MiB heap, CPU0/nice10, read-only
mode and disabled analysis. Each independently checked imported/raw hash,
image base, entry, language/compiler and the complete mapped .text against
the PE before decompilation, then checked root bytes again. Initial missing
callee prototypes corrupted stack recovery; an intermediate indirect-call
override also omitted explicit ECX receiver parameters. Both outputs were
rejected. Corrected receiver/stack signatures recover the magic-word read
and fallback correctly. Decompiler expressions remain hypotheses. All nine
primary database file hashes were unchanged; temporary aliases were removed.

## Correcting the old size and residual claims

The old **2197** was a whole COFF section tail: **2149 callable bytes +3
alignment +45 metadata**, not2197 bytes of recovered callable. Its real body
was81 bytes shorter than target. The previous statement that only stack
coloring/late inlining remained was not established.

The target palette pack masks red at word width, combines red/green, then
masks their combined value before the final shift and blue merge. The old
expression separately masked green and combined alpha earlier. Direct16
pixel stores also used byte masking followed by extension where target uses
word masking. These differences require source-expression investigation
alongside cleanup and register lifetimes.

Selected source now expresses staged RGB1555 quantization with `& ~7` and
uses scalar256-entry loops for both palette conversions. VC8 itself emits
four-entry unrolling; explicit repeated source assignments were unnecessary.
No class layout, calling convention, owner header or allocator changes.
This is a target-supported source hypothesis, not recovery of the original
C++ spelling or a semantic bug fix: the former expression is algebraically
equivalent for byte channels.

Fresh ordinary output is **2133 callable +3 alignment +45 metadata =2181**
bytes. The callable-size deficit is now97 bytes; the smaller section is
**not** progress toward an exact-size claim. Target-like mask dataflow is
recovered, while cleanup expansion, spill placement, alignment and scheduling
still differ. First strict mismatch remains `+10h / 41A000`, frame438h versus
430h. Source SHA256 is
`6f7df05fbaa93ce007b04d9ed3befeeb938ce9624c9bb436b7db779f36debd48`;
canonical complete section-tail SHA256 is
`630c5b9151d678505cf448c106ad38a0d30c267da3c08a119166b449977ec2a1`.

## Compiler controls and execution evidence

Private ordinary controls, all nonexact:

| Control | Callable / section bytes | Finding |
| --- | --- | --- |
| Old source |2149 /2197|Frame438h; three direct owner-destructor calls|
| Grouped palette16 expression |2133 /2181|Combined word-mask dataflow appears|
| Word accumulator; sequential destination updates |2149 /2197 each|Byte-first mask/extension remains|
| Magic word in a shorter block scope |2149 /2197|Complete payload unchanged|
| Real owner destructor visible, old expression |2172 /2217|Normal destructor calls inline; frame remains438h|
| Visible destructor plus grouped expression |2156 /2201|Inlining alone does not recover target allocation|
| Word accumulator with full word masks |2156 /2201|Still nonexact|
| Scalar palette16 loop |2156 /2201|Compiler emits four-entry unrolling|
| Word masks in direct16 pixels |2156 /2201|Removes byte-first mask sequence|
| RGB zero-test operand order |2156 /2201|Complete payload unchanged|
| Scalar loops for both palettes |2156 /2201|Four-entry unrolling remains|
| Same-width unsigned-long pixel/file-size types |2156 /2201|Complete payload unchanged from scalar loops|

A BMP-only TU with the unchanged five-slot class declaration was also linked
with the **real** `FileReader.cpp` and VC8 CRT under whole-program compilation
(`/GL` at compile, `/LTCG` at link). Exported root/open/global data preserve
public entry contracts. Old/new expressions yielded2168/2152 callable bytes,
both frame438h. Every root address field had a map/local reference mapping.
However, `open_package_file_entry` has no source provider and was explicitly
left unresolved using `/FORCE:UNRESOLVED`. These are **partial diagnostic
links**, not runnable artifacts or acceptance evidence. They do not prove
that the original TU/LTCG context is unrecoverable.

Instrumented x86 execution compares actual target and canonical candidate
instructions, with models for synchronous reader I/O, allocation/free,
reader deletion and PNG fallback. The149 cases comprise open failure, both
PNG outcomes,8/24/32-bit input crossed with six requested formats, four
image dimensions and both field18 values, plus two allocation-callback
mutation cases. The latter change format24 to32 after palette allocation
and exercise the otherwise unvisited indexed32 path; they are model stress
cases, not evidence that the real allocator performs this mutation. Compare return AL,32-byte bitmap
state, ordered I/O/allocation/deletion actions and every allocated payload,
including row padding. Both old and selected source pass0/149 differences.
The147 stable-format cases cover633 target instructions; adding the two
mutation cases covers661 instructions and287195 target steps. The five
unexercised normal instructions are the nonnull-reader failed-open deletion
block and the low-bit-depth default-format write. This is
bounded behavioral evidence, not exact comparison, exception-path coverage,
real OS/filesystem execution or proof for malformed/unbounded images.

## Receipts and next work

Fresh unit build/comparison:

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-cbitmap-data-runtime --compare --json
```

Overall result remains `comparison_failed`: BMP, PNG and file loaders are
nonexact. All five previously accepted siblings remain exact: constructor23,
scalar destructor47, normal destructor21, descriptor copy196 and PNG read
callback33 bytes. No match/implemented/origin/boundary ledger changed.

Private commands/scripts are in `.analysis/cbitmap-bmp-20261019/` and receipts
in `build/cbitmap-bmp-20261019/`: `target-facts.json`, target/candidate assembly,
`revised-unit.json`, `revised-shape.json`, `*-execution.json`, Ghidra logs and
nine-file before/after hashes, and `ltcg/commands.json`. These are local
investigation artifacts, not checked-in generated reports. The execution
harness is `execute-bmp.py`, SHA256
`e3998c65305beb8620387c7c4c4ade1c44d5d44901ceb6a982627f35f7fcd684`;
its selected-input name is `revised`.

Remaining work: recover why the target retains different palette/reader
lifetimes and fewer spill slots, audit the EH cleanup relationship, and find
supported original TU/provider context before claiming that LTCG is the
cause. Do not repeat byte-neutral scope/type/order controls without new
constraints. Keep the complete2230-byte callable boundary and separate45-byte
metadata contract. No cold-all replay or aggregate percentage is claimed.
