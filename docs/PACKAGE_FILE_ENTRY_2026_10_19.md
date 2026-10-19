# Package-entry opener, 2026-10-19

## Scope and target evidence

Observed against original Japanese 1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`:

- `open_package_file_entry @41BFA0` owns `[41BFA0,41C104)`, 356 bytes,
  SHA256 `0fe57031fa66c1e1141f945c79607ccd0d7cade48ba30ea4058b7c8c12a440c3`.
  All 126 decoded instructions are reachable in the static CFG; branches land
  on internal instruction starts. Both exits pop 12 argument bytes.
- The three arguments are filename, size-output pointer and offset-output
  pointer. Return is a file handle or zero. `FileReaderOwner_open @40CF40`
  calls it at `40CF87`, with outputs in its package-reader object.
- `41C450..41C4C5` is a separate 117-byte, 45-instruction search/copy helper,
  SHA256 `4ca7b126ac065046c073c205b40bea47487efb4b33af14c041ecf6f8bc8ab8a4`.
  Its observed entry takes the container in ESI, result buffer in EAX and key
  pointer on the stack, with RET4. The returned iterator is two dwords.
  Its two decoded callers are `41BCF0:41BD49` and `41BFA0:41BFDB`.

IDA preflight still rejects the attached database's different executable.
Direct Ghidra was independently attested for input hash, base, entry point,
language/compiler, complete mapped `.text` and root bytes before decompiling.
The private register/stack metadata was read back. Decompiled text was a
hypothesis, checked against raw instructions. All nine primary database file
hashes stayed unchanged; temporary read-only project aliases were removed.

## Observed data and behavior

The container at `702908` has a four-byte prefix, head pointer at +4 and size
at +8. Search nodes have left/parent/right at +0/+4/+8, unsigned key at +0C,
mapped value at +10, color at +24 and nil flag at +25. The mapped value is an
inline 20-byte record, not a pointer:

| Record offset | Observed role |
| --- | --- |
| +00 | owned filename pointer |
| +04 | archive filename index |
| +08 | entry size |
| +0C | absolute entry offset in that archive |
| +10 | next record in the hash-collision chain |

This corrects the retained `offset_04` and `key_0c` names. The destructor
already used only +00/+10, so its allocator behavior and layout do not change.
`702914`, used as a mode word by CF40, is outside this 12-byte container.

The filename vector is at `7028F8`, with first/last/end at +4/+8/+0C.
Elements stride 28 bytes: string storage at +4, length at +14 and capacity at
+18; capacities below 16 select inline storage. Checked vector indexing is
inlined in the target. The native VC8 map/vector/string source is a supported
container hypothesis; its physical sizes, checks and search semantics agree.
The compiler helper remains separately in origin review, without exclusion
or authored-byte credit from this checkpoint.

The target hashes `strlen(path)` bytes with the existing case-insensitive CRC
at `406930`. If no key matches, it returns zero without writing outputs. A
singleton record is accepted without comparing its filename. Only a record
with a non-null next pointer enters the `_stricmp @68B038` collision walk.
Exhausting that chain also returns without writing outputs.

On a hit, the archive index is captured before output publication. The size
and offset are written before opening. The selected archive name is passed to
`CreateFileA` through IAT `6C0098`, with access `80000000`, share1, null
security, OPEN_EXISTING3, flags80h and null template. INVALID_HANDLE_VALUE
becomes zero, leaving the published outputs intact. Otherwise the target
calls `SetFilePointer` through IAT `6C0090` with the output offset, null high
word and FILE_BEGIN0. The seek result is ignored; it returns the file handle.

## Source and compiler experiments

`src/assets/PackageFileEntry.cpp` now implements that policy with native
containers and the existing CRC symbol. `PackageFileIndexNode.hpp` shares the
corrected record declaration with the accepted destructor. No private source
calling convention is fabricated for the search helper.

| Private control | Complete root | Search helper / vector indexing |
| --- | --- | --- |
| Ordinary SP1, defined globals | 283 bytes | public ECX/sret-stack find105; separate vector[]68 |
| Ordinary SP1, external globals | 283 bytes | same root bytes and boundaries |
| Ordinary SP1, const views | 283 bytes | same root bytes; const-qualified symbols |
| Real-source SP1 GL link, exported opener | 333 bytes | private find116; vector indexing inlined |
| Complete reader/BMP dependency link | opener333; CF40 212; BMP2152 | private find116; target boundaries still differ |

GL reproduces the opener's eight-byte stack alignment and inlines checked
vector indexing. It specializes the search differently: its container becomes
a fixed global, key travels in EBX and no stack argument is popped. The target
retains a generic ESI container argument and stack key. This is a concrete
visibility/partition difference, not proof of a unique original TU or source
spelling. The second real caller, index insertion/update at `41BCF0`, remains
unreconstructed at this checkpoint; see the later
[registration/lifetime review](PACKAGE_INDEX_UPDATE_2026_10_19.md).
An installed RTM link attempt failed to load `msobj80.dll`;
it provides no RTM code-generation comparison.

The first private link used a simple equivalent CRC loop. On checking the
live mapping, the already accepted `case_insensitive_crc32` body was found in
`src/config/ScoreMusicLookup.cpp`; later links use that selected body. Its
ordinary full293-byte replay passes again. The complete dependency experiment
uses the selected BMP body, real FileReader and package sources, actual global
container definitions, the selected CRC body, a real table-getter provider,
vendored zlib CRC source and pinned CRT/SDK libraries. It links without
unresolved symbols or `/FORCE`. It is a function-context experiment, not a
standalone game build or original partition claim.

With the opener, CF40 and CRC exported to preserve their observed public
entry ABIs, the complete CF40 canonical payload is unchanged:
212 bytes, SHA256
`ac9caab6bf725b1f1aafb2bfa162717861bdfff8a27f3103450e2683a4df5c4c`.
All four HIGHLOW and three E8 fields have named owners; strict mismatch is
still +0. BMP has a 2152-byte callable plus45 metadata bytes (2197 total),
frame438h versus target430h, with first difference +10h. All19 translated
fields have map/local owners; diagnostic payload SHA256
`d8eac9b5385981664658f8e56992a36a7e253b4ee2aacf8620ab50f507fa5642`.
Completing these providers does not by itself recover the target frame or
code generation. These links earn no exact credit.

## Execution evidence and replay

Private Unicorn execution compares actual target instructions with the
selected ordinary root and its real compiled map/vector helpers. Both sides
execute the attested target CRC and table getter. In 243 cases, outputs,
return values, preserved registers, stack cleanup and ordered calls agree.
Fixtures include empty/missing/multi-node trees, true casefold-hash collisions
using `[`/`{`, singleton filename bypass, collision head/middle/tail/miss,
ASCII case comparisons, three archive indices, inline/heap strings, two input
stack alignments, shared size/offset outputs, open failure and ignored seek
failure. Three invalid-vector cases stop at the CRT invalid-parameter entry.

Coverage is 122/126 root instructions and all45 target search-helper
instructions. The three impossible-under-valid-iterator owner-check failure
calls and the continuation after the returning invalid-vector handler are
uncovered. `_stricmp` and Win32 I/O are modeled; locale behavior, real file I/O,
handler continuation and OS exception unwinding remain outside this evidence.

The selected source compiles in `gpt-web-package-file-entry`. Formal comparison
stops at `relocation.rel32.unknown_target` for the ordinary map-find helper:
mapping that incompatible ABI to41C450 would be false evidence. The extra
out-of-line vector call also has no target callable to bind. Data-address and
the three known external-call identities are recorded independently. No
percentage or first-byte exact comparison is claimed for this probe.

Focused fresh builds replay all12 accepted functions across
`gpt-web-package-file-index-runtime`, `gpt-web-score-music-lookup`,
`cross-v106a-file-reader` and `gpt-web-cbitmap-data-runtime` exactly, including
the43-byte destructor after its shared declaration changes. Existing CF40,
BMP, PNG and file-loader probes remain nonexact. The ordinary selected BMP
payload remains2181 bytes. No cold aggregate replay was run.

Receipts: `build/package-entry-20261019/target-cfg.json`, `incoming-edges.json`,
`execution.json`, `primary-db-before.json`, `primary-db-after.json`,
`selected-compare.json`, the four focused comparison reports, and
`reader-bmp/{commands.json,root-cfgs.json,cf40-audit.json}`. Private controls and
execution driver live under `.analysis/package-entry-20261019/`. Next recover
the genuine shared index-helper caller/ownership context, then revisit
reader construction and BMP workspace/EH lifetimes. The registration follow-up
above now supplies that second caller's source, with private ABI differences
still unresolved. No exact numerator changes.
