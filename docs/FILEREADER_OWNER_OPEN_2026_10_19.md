# Reader-opening dependency at0x0040CF40

Scope: the shared reader-opening helper used by the2230-byte BMP loader and
other game asset/audio loaders. Original Japanese1.06a SHA256:
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The name `FileReaderOwner_open` is an inferred source label, not a PDB claim.
This checkpoint selects existing reviewed source; **it adds no exact credit**.

## Exact target facts

Callable `[0040CF40,0040D015)` is213 bytes, SHA256
`af6ace376e9c519262ef6ca5c5d464f7474e63eb78cac11d5495cbd84f8e1eab`.
All84 decoded instructions are normally reachable, no internal switch or
alignment gap occurs, and both exits are balanced RET4 at40D009/40D012.
INT3 padding starts40D015. Receiver is ECX, path is the first stack argument,
and the result is AL. Normal CFG/ESP propagation checks all call cleanup
contracts; memory faults and exception dispatch are outside that traversal.

The function deletes a previous owned reader, reads the zero/nonzero mode
word702914, then selects package or plain reader allocation. Allocation
sizes28 and12 agree with the observed derived/base field prefixes. The
mode word's original global type/owner is unknown; retained source's
`g_package_file_index` is an opaque32-bit alias, not proof of a pointer-valued
archive index. The source layout beyond the observed owner pointer protocol
is not independently established by this helper.

| Call | Site(s) | Observed contract |
| --- | --- | --- |
| Previous/failed reader virtual delete |40CF52,40CFFB|ECX reader, stack flags1, purge4|
| Scalar allocator689DCB |40CF5F,40CFA6|cdecl size28/12, pointer result|
| Package entry41BFA0 |40CF87|path, size-out, offset-out; stdcall purge12|
| KERNEL32 CreateFileA |40CFCE via IAT6C0098|path,1,1,0,3,80h,0; purge28|

Package output fields are handle+4, size+C, offset+10, absolute position+14,
and XOR byte+18=`byte((offset>>1)|23h)` when handle is nonzero. The read-count
word+8 and remaining padding are not initialized here. Plain INVALID_HANDLE
(-1) is normalized to0. A null file causes virtual deletion, owner reset to0
and false; nonzero returns true. Do not replace access1 with80000000h or
change the target's allocator/handle error policy.

Raw RTTI independently identifies the concrete families:

| Vtable | COL / type | Five slots |
| --- | --- | --- |
|6C0F34|6DCDC0 / `.?AVCFileReader@@`|41B890,40CED0,407C40,407C50,40CF00|
|6D6E28|6DCFF8 / `.?AVCPackageFileReader@@`|41B890,41C110,407C40,41C180,41B880|

The package hierarchy has two descriptors: itself and CFileReader at offset0.
Its custom archive/XOR initialization plus these reader families and game
loader callers support authored engine ownership independently of exactness.
Fifteen E8 callers were confirmed at decoded instruction starts in candidate
bodies; eleven are source-present asset/audio loaders, four remain unclassified.
None is currently exact. The new origin rule pins the full213-byte hash and
incoming game-loader edges rather than assigning ownership from auto-analysis.

A direct Ghidra read-only run independently attests imported/raw identity,
entry/base/language/compiler and the complete mapped .text before use, then
checks the root again. Calling-convention/signature metadata is read back;
prototype-constrained decompiler output remains a hypothesis. All nine primary
DB hashes stay unchanged; temporary project aliases are removed.

## Source and compiler controls

Existing `src/assets/FileReader.cpp` describes the same valid-allocation
protocol but initializes readers after their implicit default construction.
The selected header/source/profile are unchanged in this checkpoint. Fresh
ordinary output is212 callable bytes,81 instructions, SHA256
`ac9caab6bf725b1f1aafb2bfa162717861bdfff8a27f3103450e2683a4df5c4c`.
Its first mismatch is+0: target reserves an otherwise unreferenced stack word
with PUSH ECX and saves ESI/EDI before conditional paths. Candidate save
placement, allocation-null guards and vptr/initialization scheduling also
differ. The one-byte size deficit is not a one-byte reconstruction problem.

Target allocation guards enclose initialization, which is consistent with
inlined path constructors but does not prove original C++ construction syntax.
Private controls test that hypothesis without changing public interfaces:

| Control | Observation |
| --- | --- |
| Existing source, GS off/on and installed RTM control |212 bytes and identical complete canonical payload|
| Explicit nonnull initialization guards |212 bytes; different CFG, still mismatch+0|
| Path constructors, ordinary/inline/in-class definitions |249-byte open body with EH registration and an out-of-line package-constructor CALL absent from target|
| Constructor probe with EH disabled |171 bytes; package-constructor CALL still remains|
| Hypothetical nonthrowing package-entry declaration |171 bytes; does not recover inlining|
| Forced constructor inlining plus disabled EH |208 bytes; still mismatch+0|
| Forced constructor inlining plus hypothetical nonthrowing entry under normal EH |208 bytes; still mismatch+0|

The installed RTM compiler control has cl.exe SHA256
`3cbf4306526c06a07d09fd4785ac290c7ac7b52355944e7b377e08f5d8e7ece7`.
Its equality on this source does not establish the original compiler revision.
No constructor rewrite, force-inline attribute, nonthrowing declaration,
exception-mode change, inert local or padding is selected. A prior real-source
FileReader/BMP diagnostic LTCG link also retains the212-byte open shape. Its
package helper is unresolved, so it is not evidence of a complete original
provider context or of standalone matching being impossible.

## Execution evidence and formal selection

Private Unicorn execution compares actual target/canonical candidate
instructions with models for allocation, reader deletion, package opening and
CreateFileA. The66 cases cross plain/package mode, old-reader ownership,
null/invalid/valid handles and four offset patterns; two delete callbacks
change the mode before selection. Allocation and package-entry exception cases
stop at the call boundary and compare observable memory/trace prefixes, not
OS/C++ unwinding. All66 agree on return AL where returned, owner/global state,
full allocated reader bytes and ordered call/deletion snapshots. Normal RET4
and callee-saved registers are checked. Coverage is83/84 target instructions.
The remaining XOR ESI,ESI at40CFE5 belongs to the allocation-null path;
the model deliberately assumes nonnull-or-throw allocation. This is bounded
behavioral corroboration, not full runtime or exact-byte proof.

`FileReaderOwner_open` is now mapped/source-present and independently
classified authored. New explicit bindings cover the mode word and package
vtable; existing base-vtable/IAT bindings are reused. The allocator is bound
to689DCB, not the distinct665B8A forwarding entry used for arrays. The package
entry is41BFA0, not the unrelated40CF30/41BA70 path.

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit cross-v106a-file-reader --compare --json
```

The mixed unit returns `comparison_failed`: CF40 remains212/213 at+0. Its
three accepted members stay exact:407C40=4,40CF20=15,41B880=4 bytes. Related
CBitmapData replay also preserves its five accepted members; BMP/PNG/file
loaders remain nonexact. No matches row, source code, shared header, class
layout or compiler flag changes. All seven open-function relocation fields
are replayed explicitly; there is no ignored range/register normalization.

Private evidence is below `.analysis/filereader-open-20261019/` and
`build/filereader-open-20261019/`: target/source CFG and assembly, caller
inventory, typed Ghidra hypothesis/attestation and nine-file hashes, private
source controls, `execution.json`, `reviewed-unit.json`, and `bmp-replay.json`.
The source-selection and origin evidence are durable in the public ledgers.
No generated binary/report or analysis database is committed.

Next work should obtain the genuine package-entry/provider implementation at
41BFA0 and then re-evaluate constructor/whole-program context for CF40 and
BMP. Its lookup uses the293-byte path hash at406930 and a117-byte tree helper
at41C450; these are observed dependency edges, not new accepted boundaries or
ABI/source declarations. Keep the large loader as the end objective; do not
weaken matching or assert a sole LTCG cause from partial links.
