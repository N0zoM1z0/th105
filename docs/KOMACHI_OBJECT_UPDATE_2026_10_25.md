# KomachiObject complete update: 2026-10-25

`KomachiObject_update_action_state @ 0x005F9420` has a manual complete-body
source hypothesis and an early whole-function comparison. It is **not exact**.
Formal and independently compiled cold objects reproduce the complete28940-byte
canonical payload, SHA256
`cd3509de3d926e411f1423f100160834ab0766ac12879573124607f61bc90d9b`.
The target owns28520 bytes. Full unmasked comparison reports27184 differences,
first+8/5F9428: source frame0x48 versus target0x40. This remains a broad layout,
precision and physical-sharing residual; it is not a localized eight-byte
comparison failure or partial exact claim.

## Observed target and boundary

The executable is original Japanese1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The GUI IDA preflight rejects a different executable. No reads or writes use
that session. Raw target evidence is independently reproducible:

```sh
taskset -c 0 nice -n 10 scripts/repo-python scripts/audit-komachi-object-update.py --target-only
```

The existing RTTI-backed roster origin anchor binds KomachiObject primary
slot28 cell6C6004 to5F9420. Separate slot3C cell6C6018 points to600390, the
already retained initializer. Its source, seven-byte residual and unit remain
unchanged. Three INT3 bytes precede5F9420 after the independently reviewed
205-byte pair-emission helper5F9350.

Main `[5F9420,600102)` is27874 bytes, SHA256
`22f3ca6f2c23e5b1b9be280869a611f54930f55d447de2486e42367de76c48c2`.
All6780 instructions decode. CFG traversal reaches6773 instructions/27852
bytes,37 RET0s,315 direct calls to19 entries and six virtual calls. No edge
leaves the main span. Seven unreachable instructions account for22 explicitly
attested internal padding bytes:

| Address | Exact bytes |
| --- | --- |
|5FA5FD|8d4900|
|5FB93D|8d4900|
|5FE7BD|8d4900|
|5FF3A7|eb07|
|5FF3A9|8da42400000000|
|5FF74F|90|
|5FF90D|8d4900|

The audit checks this complete address/byte set. It neither masks these bytes
nor accepts additional unreachable instructions. The main size includes this
padding; reachable instruction bytes are reported separately.

The prologue aligns ESP to eight bytes and allocates0x40 bytes. It saves EBX,
EBP, ESI and EDI below the frame; this remains in ESI. There is no GS/EH frame.
The new header is a pointer-only primary-vtable call view. Never instantiate
or embed it as a recovered allocation. Nominal owner/return types and original
translation-unit boundaries remain unknown.

Complete `[5F9420,600388)` is28520 bytes, SHA256
`c5bed7baea5bbb97517f1bdebdaad6451db1491222180f16a705e767e8ae5b54`.
Its646 bytes after the main comprise MOV EDI,EDI alignment at600102,111
destination DWORDs/444 bytes and200 primary-remap bytes. Eight INT3 bytes
separate the payload from600390 and are excluded.

| Address | Destination DWORDs / remap |
| --- | ---: |
|600104|28|
|600174|200 remap bytes for800..999|
|60023C|5|
|600250|6|
|600268|5|
|60027C|4|
|60028C|6|
|6002A4|5|
|6002B8|6|
|6002D0|5|
|6002E4|5|
|6002F8|7|
|600314|14|
|60034C|4|
|60035C|4|
|60036C|7|

The27 explicit primary actions are800,801,810,811,812,815,817,820,821,822,
825,826,827,850,852,853,854,855,856,861,900,901,902,930,980,990,999. Other
remap entries reach the default frame continuation.

## Analysis hypothesis and manual implementation

One direct readonly/noanalysis Ghidra process ran with one CPU, CPU0/nice10 and
384MiB heap. It attested imported executable identity, PE entry, language/
compiler and all mapped section bytes before decompilation. The temporary
bounded function and declaration-only callee ABI views were read back; the
transaction rolled back and root metadata was read back again. All nine primary
project-file hashes agree before/after. The process terminated0 with its
attestation sentinel. Its3356-line output is a hypothesis, not selected source.

The manually written source uses numeric actions, typed offset accesses,
independent actual calls and consumed packet arrays. Raw instructions determine
field widths, signedness, control edges and publication epochs. It does not
mechanically translate decompiler temporaries. Declaration-only callees receive
no new implementation or exact credit. Existing accepted provider evidence is
reused only for reviewed call/return/storage contracts.

| Target | Physical calls | Working call view |
| --- | ---: | --- |
|5575C0|13|three-int repeated emission, AL result|
|435160|34|receiver+4, two float components|
|45C030|6|owner wave handle, unsigned index|
|4067D0|90|cdecl random roll, one int|
|4351C0|10|frame continuation, AL result|
|5F9350|10|owner-gated pair emission, AL result|
|406360 /4063D0|30 /10|quantized sine/cosine, float input/double ST0 result|
|4963A0|19|six-counter continuation, one int/AL result|
|64CCB0|63|unparented spawn, seven stack words|
|64CD00|5|conditional phase continuation, one int/AL result|
|435D60|5|stage height, this/ST0 result|
|435520|6|sprite UV size, two floats|
|406540 /406580|2 /4|cdecl atan2 /square, ST0 result|
|5F9310|5|descending surface predicate, caller consumes AL|
|4359D0|1|owner battle-layout scalar, float|
|4E0BF0 /53CBC0|1 each|heading adjustment /ping-pong update|

The source keeps unsigned random conversions, including the unusual unsigned
`roll(100)-50` conversion, and preserves actual floating loop counters. Wider
constants that originate as floats use their observed promoted float values.
Trigonometric results remain double through consumers. The854 square result
has a real qword lifetime across the second square call. Repeated817 position
updates and independent854 state checks remain separate.

A raw stack-depth traversal checks consistent incoming depths on6699 visited
instruction addresses, stopping at frame restoration. Every one of63 spawn
calls has a checked LEA/register-push witness for argument slot+20. Packet
addresses relative to aligned ESP are-64 at eight sites,-48 at29,-32 at16 and
-12 at10. Four independently consumed three-float source arrays retain these
storage groups; they are not frame padding. Their current generated frame0x48
still exceeds target0x40. Original lexical scopes, temporary reuse and remaining
allocation epochs are unproved. Private receipt: `target-packet-locations.json`.

## Early comparison and target-backed corrections

Receipts below are under `build/exact-first-komachi-object-update-20261025/`;
private raw/decompiler drivers, complete source snapshots and recipes are under
the corresponding `.analysis/` directory.

| Complete source/control | Full bytes | SHA256 prefix | Result |
| --- | ---: | --- | --- |
|First manual complete body|29056|bb6323b2|27592 differences; first+8, frame0x28|
|Review827 bounds/movement/entry exits|28940|13ea4aa1|27192 differences|
|Restore raw ordered outside guards|28940|bf2204f7|27185 differences;34 component calls restored|
|Four real consumed packet groups|28956|242042e5|27045 differences; frame0x48|
|Review801 velocity-packet ownership|28940|cd3509de|selected;27184 differences; frame0x48|

The827 first source incorrectly reused825's bounds and moved after the guard.
Raw5FCA68..5FCB63 establishes movement before the1680/-400/1360/-400 bounds,
then frame continuation and separate entry-phase1/2 retirement. This is corrected.
Several structured decompiler bounds also lose unordered semantics. The raw
FNSTSW/TEST AH,5/JNP and TEST AH,41/JE paths reject ordered outside values;
unordered comparisons continue. Explicit outside comparisons replace the first
source's ordered-conjunction rejection. These corrections follow instructions,
not a lower mismatch count.

All1002 selected section relocations replay. Formal and independent cold
full-payload hashes agree. The entire200-byte remap agrees, SHA256
`4263dbd9617462fb289d3fb3be165e8348154fe2ede1c45657d1fd17e3ca5c86`.
The source emits14 destination tables: the five identical destinations for
target811's table600268 instead become an ordinary range guard. The full
comparison includes every table/remap/alignment byte; candidate table dimensions
are diagnostic and cannot waive target equality.

Selected source has50 RETs versus37, five virtual calls versus six and64 spawn
calls versus63. The other18 direct-callee counts agree. Static per-case traversal
from all27 primary entries finds matching direct-callee counts for each case,
but this overapproximates feasible paths and is not execution equivalence.
Different physical sharing explains why aggregate counts differ:

- Target spawn5F9949 is shared by801/815/825/827/852/855/856/901. Source5F9941
  shares only the first six, and another source spawn5FE6F2 joins861/901.
- Target800 and801 have separate virtual frame calls; source joins both at
  5F9554. No source virtual operation is removed on the corresponding case path.

Keep these concrete groups for the next trial. Do not infer original source
spelling, a compiler-profile solution or standalone/LTCG impossibility from
matching call counts.

Generated-COFF-only negatives leave the PE and selected object unchanged. A
valid decoded first-instruction mutation changes the previously agreeing+0
byte55 to56: full differences rise to27185, first+0, SHA256
`42d3b4731f483bc6917d80e50e373b0fad28d170e0253c6bb88897b575b8794b`.
A separate last default-remap mutation for action997 changes valid index27 to0
at generated6003F1/+28625. Parsing succeeds and the complete payload hash
changes to`ed42c15cdcfa56353299b1de3374b1e91cc12745c9593494d6a2e105aa768ab1`.
Its difference count remains27184 because this emitted byte is beyond the
target extent; no extra agreeing-byte failure is claimed for that negative.
Seven synthetic tests cover all15 tables/200 indices, invalid indices, metadata
destinations, truncation, external CFG edges and exact unreachable-padding sets.

## Reproduction and continuation

Use locked repository Python and serial CPU0/nice10 jobs. The complete source
comparisons intentionally return1 while nonexact:

```sh
taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py --unit exact-first-komachi-object-update --compare --json
taskset -c 0 nice -n 10 scripts/repo-python scripts/audit-komachi-object-update.py
TH105_ENABLE_GS=0 TH105_FP_MODE=default TH105_INLINE_MODE=default \
  taskset -c 0 nice -n 10 scripts/compile-unit.sh src/characters/KomachiObjectUpdate.cpp build/komachi-object-update-cold.obj
taskset -c 0 nice -n 10 scripts/repo-python scripts/audit-komachi-object-update.py --object build/komachi-object-update-cold.obj
```

Changes are local source/header/audit/tests, one nonexact unit, mapping/source
selection and79 exclusively named literal aliases. No accepted unit references
these aliases. Shared headers/layouts/compiler settings and prior provider
implementations remain unchanged. Tracking records mapped1579/source1560 and
599 configured units/1567 functions. All1563 floating target references pass.
Accepted graph remains524 units/1412 functions; the prior Remilia checkpoint is
still the latest aggregate cold receipt. No new aggregate cold replay or exact
credit is claimed. No runtime matrix, assembly, byte-array source, inert local,
fake return, register forcing or padding was used.

Continue5F9420 from its genuine frame/packet lifetimes and the specific physical
call/return groups above. Each control must answer one raw-target question and
recompare the complete extent. Stop repeated neutral controls. Remaining
unknowns include complete execution equivalence, other scalar precision/
publication epochs, original expressions and nominal types, lexical scopes,
original TU/compiler context and faithful811 destination-table lowering.
