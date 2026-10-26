# Exact ScoreData persistence42D3F0

The complete function is canonical **1155/1155**. Two independent public VC8
builds reproduce target/candidate SHA-256
`7c1f377790ad3439955063dfdfabfd872385eb123a26da7c073baaab491ceb48`.
The first whole1155-byte source was compared immediately and had80 unequal
positions, first42D661. One real shared character-count variable, used both for
the serialized count and the loop bound, closes every difference. It introduces
no inert state, manual instructions, copied code or padding.

## Observed target and ABI

Only original Japanese1.06a SHA
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
was used. Fresh target/status/tracking checks passed. IDA again rejected the
10350095 executable; raw PE instructions supplied all semantic/boundary facts.
The1155-byte body decodes360 instructions,359 reached, through RET0 at42D872.
The sole unreachable operation is three-byte alignment at42D73D;13 following
INT3 bytes separate42D880. There are no escaping edges or indirect jumps.
The native aligned frame is3C with GS/EH cookie and handler6B7EF8. ECX is the
score receiver; there are no stack arguments or meaningful return contract.
Exact callers42E750 and4404F0 call at42E7A5 and44067D; the shutdown caller
43D670 calls at43D68C and receives no new classification credit.

The original names/TU remain unknown. Current source uses the shared bounded
ScoreData view, real12-byte CFileWriter and two real eight-byte array owners.
Adding the nonvirtual persist declaration changes no field layout. The
independently accepted6-byte header service43AA40 actually executes in the
audit and supplies0x6A; it is not replaced with an inlined constant.

## Complete behavior

An initialized byte+00 of zero returns before file, allocation or version work.
Otherwise construct the writer for `score.dat` with GENERIC_WRITE40000000,
share0,CREATE_ALWAYS2,attributes80. INVALID_HANDLE_VALUE becomes zero, but this
method continues serialization and calls WriteFile with that zero handle.

Allocate a512KiB serialization buffer. Write header code0x6A, flags+04 and the
three20-byte arrays+08/+1C/+30. Write unsigned size/key sequences for the sets
at+44 and+50, then size and key/value pairs for the map at+9C. Write a character
count of15. For each of those15 slots write its map size/pairs and vector size,
then all six DWORDs of every24-byte record. Traversal uses actual checked VC8
set/map/vector iterators, preserving all19 invalid-parameter call sites. Records
are neither filtered nor deduplicated here. The20-slot object capacity does not
change the15-slot persisted roster count.

Allocate a second512KiB buffer and call encoder4067F0 with serialized pointer/
byte count/output pointer/capacity. For each encoded byte i, store byte XOR
low_byte(7*i) at serialized_buffer[encoded_size-i-1]. Write that transformed
buffer with exactly encoded_size bytes. A zero encoder result still reaches
WriteFile with count0. Neither the write result nor file-open success causes a
new early return. Release encoded then serialized arrays and close a nonzero
handle. The source score object, including byte+00, is unchanged.
Array new665B8A and delete68AA26 are preserved independently; no inference of
allocation ownership is made solely from a free tail alias.

## Reproduction and independent checks

Source: `src/config/ScorePersist.cpp`.
Unit: `exact-first-score-persist`, pinned VC8 SP1 O2/GS enabled.

```bash
taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py --unit exact-first-score-persist --compare --json
scripts/repo-python scripts/audit-score-persist-target.py --object build/match-units/ExactFirst_ScorePersist.obj
```

Receipts: `build/frontier-42d3f0-20261026/formal-first.json`,
`formal-second.json`, `formal-audit-first.json`, `formal-audit-second.json` and
`target-audit.json`. Private first/control sources, full raw decode and replay
recipe are under `.analysis/frontier-42d3f0-20261026/`.
The audit covers inactive, populated, open-failure and zero-encoder cases.
The332-byte serialized fixture includes signed map values, the last persisted
slot14, deliberately populated but omitted slot15, duplicate-pair records with
different difficulty/statistics, and values300/255 above the defaults parser's
threshold. It verifies full serialization, transform inversion by the loader's
formula, WriteFile behavior, release order, unchanged score object, stack,
callee saves and FS0. API/allocation/encoder/iterator implementations are
observers; actual I/O, compression, allocation failure and EH unwinding are not
executed. Exactness refers to the whole callable, not a linked executable.

## Closed family TU control

A genuine TU includes all three complete public files: defaults, load and
persist. It preserves defaults2428/2428 SHAedf62017 and persist1155/1155
SHA7c1f3777. Load remains1666 bytes versus1672,564 unequal shared-extent positions,
missing6 bytes, first42F91B, SHA9979a9c5. Thus this direct definition-visibility
control is whole-payload neutral for every peer. Keep the question closed
without new independent evidence; it proves no general LTCG impossibility.
Reports: `family-tu-summary.json` and `family-*.log` under the current build
scope. Family TU source/object remain private and receive no extra match unit,
helper-origin or coverage credit.

The user's cleanup/handoff request arrived after this control was started.
The running build was allowed to finish, its result was captured, and the
already exact persistence result was finalized for durable handoff. No new
reconstruction frontier was opened afterward.

Both origin checks and the current-manifest cold replay pass:528 accepted units/
all1416 functions,389486 exact authored bytes. Final local CI is recorded in
`local-ci.log`. The handoff archive and cleanup are described in ARTIFACTS.md.
