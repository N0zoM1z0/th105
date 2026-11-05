# KomachiObject complete update: 2026-10-25

`KomachiObject_update_action_state @ 0x005F9420` has a manual complete-body
source hypothesis and an early whole-function comparison. It is **not exact**.
Formal and independently compiled cold objects reproduce the complete29072-byte
canonical payload, SHA256
`4746e929c5a0a34a4b593d44413c76e2128227d844464b90e3783d483dd23728`.
The target owns28520 bytes. Full unmasked comparison reports27294 differences,
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

This section records the first checkpoint `6fdd010`; the follow-up below
supersedes its selected hash and current residuals.

Receipts below are under `build/exact-first-komachi-object-update-20261025/`;
private raw/decompiler drivers, complete source snapshots and recipes are under
the corresponding `.analysis/` directory.

| Complete source/control | Full bytes | SHA256 prefix | Result |
| --- | ---: | --- | --- |
|First manual complete body|29056|bb6323b2|27592 differences; first+8, frame0x28|
|Review827 bounds/movement/entry exits|28940|13ea4aa1|27192 differences|
|Restore raw ordered outside guards|28940|bf2204f7|27185 differences;34 component calls restored|
|Four real consumed packet groups|28956|242042e5|27045 differences; frame0x48|
|Review801 velocity-packet ownership|28940|cd3509de|first checkpoint;27184 differences; frame0x48|

The827 first source incorrectly reused825's bounds and moved after the guard.
Raw5FCA68..5FCB63 establishes movement before the1680/-400/1360/-400 bounds,
then frame continuation and separate entry-phase1/2 retirement. This is corrected.
Several structured decompiler bounds also lose unordered semantics. The raw
FNSTSW/TEST AH,5/JNP and TEST AH,41/JE paths reject ordered outside values;
unordered comparisons continue. Explicit outside comparisons replace the first
source's ordered-conjunction rejection. These corrections follow instructions,
not a lower mismatch count.

At the first checkpoint all1002 selected section relocations replay. Formal and independent cold
full-payload hashes agree. The entire200-byte remap agrees, SHA256
`4263dbd9617462fb289d3fb3be165e8348154fe2ede1c45657d1fd17e3ca5c86`.
The source emits14 destination tables: the five identical destinations for
target811's table600268 instead become an ordinary range guard. The full
comparison includes every table/remap/alignment byte; candidate table dimensions
are diagnostic and cannot waive target equality.

At that checkpoint source has50 RETs versus37, five virtual calls versus six and64 spawn
calls versus63. The other18 direct-callee counts agree. Static per-case traversal
from all27 primary entries finds matching direct-callee counts for each case,
but this overapproximates feasible paths and is not execution equivalence.
Different physical sharing explains why aggregate counts differ:

- Target spawn5F9949 is shared by801/815/825/827/852/855/856/901. Source5F9941
  shares only the first six, and another source spawn5FE6F2 joins861/901.
- Target800 and801 have separate virtual frame calls; source joins both at
  5F9554. No source virtual operation is removed on the corresponding case path.

These are the concrete groups used by the follow-up. Do not infer original source
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

## Follow-up: rounded radius, facing epochs and811 lowering

This section records checkpoint `b342a30`; the next follow-up supersedes its
selected hash while retaining these scalar/table corrections.

Fresh receipts are under `build/komachi-update-sharing-20261025/`; complete
private controls are under the corresponding `.analysis/` directory. A fresh
baseline build reproduces the preceding checkpoint. IDA still rejects its
different executable; all new instruction evidence uses the hash-attested PE.

Raw801/825/852 all have a consumed float rounding boundary before multiplication
by the returned sine. The target sequences are FILD counter144, FMUL qword0.75,
FSTP DWORD temporary, FMUL that DWORD into the retained ST0 wave, then store378.
The three rounding stores are5F97A6,5FC421 and5FCF56; the corresponding wave
multiplies are5F97AA,5FC425 and5FCF5A. The previous source's association
`wave * counter * 0.75` did not represent this boundary. Real consumed
`double radius_wave` and `float radius_scale` locals now do. Each generated
path contains the observed FILD/FMUL/FSTP-DWORD/FMUL-DWORD/store378 sequence.
This corrects scalar semantics; the decision is not based on mismatch count.

Raw801 and852 reload signed byte104 after the cosine call before preparing
the sine argument. Raw825 instead captures that facing value as a qword at
5FC43B, reloads it after cosine at5FC46B and consumes it in both coordinate
operations. The source now distinguishes the uncaptured801/852 expression
from825's actual qword lifetime. This also restores independent800/801 virtual
frame calls: all six virtual calls are present without a shared call site.

For811, five distinct ordinary source arms each call `advance_six(0)` once.
VC8 retains a five-entry destination table and then shares its physical call.
The previous common-label spelling became a range guard. Neither version adds
an operation on any executed path. The new full object retains all15 table
dimensions28/5/6/5/4/6/5/6/5/5/7/14/4/4/7 and all200 primary-remap bytes.

| Complete control | Full bytes | SHA256 prefix | Differences / observation |
| --- | ---: | --- | --- |
|Explicit common velocity/final spawn tail|28548|54906cfd|26633; desired eight-state call group restored, but spawn60 versus63 and component33 versus34|
|Only856/901 join the final spawn call|28876|eb5bc04a|27287; spawn61 versus63; unselected|
|Three rounded radius scales|28956|b1040d19|27000; target scalar boundaries restored|
|Actual packets scoped separately per action|29528|1d80948b|28060; frame grows0x48 to0x160; unselected|
|Separate801/852 facing epochs|29020|d8c1e4f4|27199; six virtual calls restored|
|Independent811 source arms|29040|58b2730b|27205; all15 destination tables restored; second checkpoint|

The explicit common-tail candidate joins the target's eight-state spawn group
but also merges821/861 and two physical901 calls. Its near-target size does
not establish the target layout. The late-tail alternative also over-factors
calls. Keep both unselected and do not repeat these unchanged controls. Giving
each action only its actually consumed packet arrays also fails to recover
the target frame: VC8 allocates0x160, rather than reusing storage as hoped.
The selected source keeps the four original consumed arrays. No inert locals,
padding, forced registers, compiler-profile grid or runtime matrix is involved.

At that checkpoint formal and independent cold comparison reproduce full29040/58b2730b with
all1008 section relocations replayed. Source has51 RETs versus37 and64 spawn
calls versus63; frame0x48 still differs from0x40 at+8. The other18 direct-callee
counts agree, as do all six virtual calls and all15 table dimensions. Static
traversal from each of27 case entries finds matching direct-callee counts and
virtual-call counts, but still overapproximates feasible paths. Source spawn
5F9951 shares801/815/825/827/852/855; target5F9949 additionally shares856/901.
Source5FE742 still joins861/901 separately. These are current physical facts,
not an execution-equivalence or original-TU claim.

A fresh generated-object first-instruction negative changes agreeing+0 byte55
to56, remains parser-valid and fails with27206 differences, first+0, SHA256
`550ae3ff23d9e2365a06ba92984e91b4ca17e3f118bf9d32739aa83d570b0056`.
The selected object and canonical PE remain unchanged. Earlier first-checkpoint
negative hashes above retain their historical scope. Accepted units, literal
bindings, source-present count and exact ledgers do not change in this follow-up.

## Further follow-up: pre-call Y captures and physical frame reuse

New receipts are under `build/komachi-update-frame-epochs-20261025/`; the
corresponding private directory retains the stack-depth recipe and full source
controls. Fresh whole-function baseline replay reproduces29040/58b2730b.
No new Ghidra process or use of the rejected IDA session is involved.

The raw target captures Y as a qword before three stage-height calls, then
compares the returned ST0 against that saved value:

| Action/phase | Y qword store | Height call | Qword compare |
| --- | --- | --- | --- |
|810/0|5F9F4A|5F9F4E|5F9F53|
|812/0|5FAC3B|5FAC3F|5FAC44|
|812/2|5FAEA3|5FAEA7|5FAEAC|

The previous object instead called the helper, reloaded Y from this+F0 and
used FUCOMPP at each site. Explicit consumed `double y_before_height` captures
restore the target's before-call read and FSTP-qword/CALL/FCOMP-qword sequence.
The captures occur only on paths that actually call the height provider. An
initial bool carrier added SETNE/TEST pairs in812; direct equal-height branches
remove those materializations while preserving the same decisions.

Raw825 also reads facing before publishing radius378, then stores and pops
the qword at5FC43B. Moving the real source capture before the378 publication
restores FSTP rather than the previous FST that retained an extra x87 value.
It remains a consumed facing value, not a register/liveness forcing local.

The audit now separately reports adjacent qword store/height-call/same-slot
qword-compare facts. It pins the target's four reviewed triples: these three
and999's existing next-Y capture at5FFF7D/5FFF81/5FFF86. All four now appear in
the source object. This report is a narrow instruction observation, not a
behavioral matrix or a substitute for complete byte comparison. Five new
synthetic tests reject a float-width store, another stack slot, another callee
and a post-call store, while accepting the valid qword sequence.

The private depth traversal independently checks incoming stack depths and
every spawn packet's LEA/push/argument-slot witness. Frame64 versus72 is not
explained by simply counting source variables. Observed storage, relative to
the aligned entry ESP, is:

| Kind | Target offsets / physical call sites | Current source offsets / physical call sites |
| --- | --- | --- |
|Three-float packets|-64:8; -48:29; -32:16; -12:10|-48:31; -36:16; -24:9; -12:8|
|Wide group1|-32|-56|
|Wide group2|-48|-64|
|Wide group3|-64|-72|

After the field-epoch corrections, group1 in both objects has seven FSTP,
four FCOMP, one FLD and two FADD qword accesses; group2 has four FSTP/four FSUBR;
group3 has one FSTP/one FSUBR. These operation/width counts agree, not the byte
encodings or a proved allocation graph. Source packets occupy dense[-48,0)
storage with all three wide groups outside it. The target has noncontiguous
packet regions and reuses their storage for the wide values at different
epochs. Physical overlap does not prove original union types, declaration
counts, alias freedom or an LTCG barrier. No union, scratch byte array, fake
padding or compiler annotation is introduced to force that allocation.

| Complete control | Full bytes | SHA256 prefix | Full differences |
| --- | ---: | --- | ---: |
|Capture Y before the three height calls|29072|cc749637|27099|
|Direct812 height gates|29056|5dd32509|27244|
|825 facing capture before radius publication|29072|4746e929|27294|

The last is selected for the observed epochs and instruction forms, despite
its higher full difference count than the preceding checkpoint. Formal and
independent cold builds agree on full29072/4746e929 and all1008 relocation
replays. It remains nonexact at+8, frame0x48 versus0x40, with51 RETs versus37
and64 spawns versus63. All15 table dimensions/200 remap bytes, six virtual calls
and the other18 direct-callee counts agree. Per-case direct/virtual counts
remain equal under static overapproximation. The source still shares the
six-state826 tail at5F9951, while the target additionally shares856/901;
the separate source861/901 join is now5FE762.

A fresh generated-object first-instruction mutation55 to56 fails at+0, with
27295 differences, SHA256
`71ef97f6dac680772d4db0626727e04d56c0d0f884afb969e3ef1653ccb409dd`.
The selected object and PE remain unchanged. Twelve synthetic audit tests now
cover metadata, exact internal-padding sets and the height-capture diagnostic.
No accepted unit, shared header/layout, compiler setting, literal binding,
origin disposition or aggregate count changes. No new aggregate cold replay
or runtime equivalence is claimed.

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

Continue5F9420 from its genuine frame/temporary lifetimes and the current
physical call/return groups above. Close the tested explicit spawn joins and
per-action packet-scope forms absent new independent evidence. The three
height captures and825 facing publication are now explicit; do not repeat their
old after-call/after-publication controls. Allocation reuse needs new source-
ownership/visibility or temporary-lifetime evidence. Each control
must answer one raw-target question and recompare the complete extent. Stop
repeated neutral controls. Remaining
unknowns include complete execution equivalence, other scalar precision/
publication epochs, original expressions and nominal types, lexical scopes,
and original TU/compiler context. The811 table-lowering question is resolved
for this selected source/profile; it is not a general compiler recipe.

## Action 810 trail height capture, 2026-11-05

Native `0x005FA268..0x005FA295`, `0x005FA577..0x005FA5A4` and
`0x005FA79E..0x005FA7CB` retain `Y + 25.0` in a QWORD across the random
call before subtracting its result. The previous source stored that sum in a
float first, introducing an early rounding step. Each of the three paths now
uses a double capture and converts the subtraction result to float. Fresh VC8
emits the corresponding QWORD store/call/subtract sequence at `0xED4`,
`0x11D5` and `0x1444`. Random call order is unchanged. This does not establish
whole-root or unmasked-exception equivalence.

The 27,874-byte callable remains nonexact from +8; the candidate section
tail is 29,056 bytes. No exact credit is added.

## Actions 854 and 855 orbit layer, 2026-11-05

The target chooses layer 255 when the sine result is ordered and nonnegative, including exactly zero; it chooses layer 1 for negative or unordered results. The five native checks are `0x5FD40A..0x5FD423`, `0x5FD551..0x5FD56A`, `0x5FD843..0x5FD85C`, `0x5FD985..0x5FD99E` and `0x5FDA82..0x5FDA9B`. The prior negated `> 0` incorrectly chose layer 1 at zero. All five source checks now negate `>= 0`, preserving the native zero and unordered behavior. Fresh VC8 uses an equivalent comparison, including `test ah, 1` at candidate `0x41B1..0x41CB`. An initial two-site edit attempt failed its count assertion because there are five sites; no source change or result was credited from that attempt. The verified full 27874-byte root remains non-exact (candidate section tail 29056, first mismatch +8); no exact credit is claimed.

## Action 822 orbit layer, 2026-11-05

Unlike actions 854/855, the target action 822 check at `0x5FBFCB..0x5FBFE8` selects layer 1 for sine values at or below zero or unordered, and 255 for ordered positive values. The prior ordered `<=` missed the unordered case. The source now preserves this distinct behavior; focused compilation emits the equivalent `test ah, 0x41; jne` selection at `0x2C4D..0x2C6C`. The 27874-byte root remains non-exact (candidate section tail 29056, first mismatch +8); no exact credit is claimed.

## Action 853 trail facing, 2026-11-05

The target captures the unsigned trail-facing byte before either RNG(50) call at `0x5FD219..0x5FD238`; Y is computed between calls and X after the second. The earlier source computed the coordinates first and read facing afterward. An ordinary facing local now preserves the target lifetime; focused compilation captures it at `0x3F1C` before the first call while retaining the coordinate order. The full 27874-byte root remains non-exact (candidate section tail 29040, first mismatch +8); no exact credit is claimed.

## Action 820 trail facing, 2026-11-05

The target captures the unsigned facing byte before both RNG(50) calls at `0x5FB88E..0x5FB8B2`, computes Y between the calls, and computes X after the second. The previous source read facing only after both calls. A facing local now preserves the native order; focused VC8 compilation captures it at candidate `0x24F2` before the first call and retains the coordinate order. The full root remains non-exact; no exact credit is claimed.

## Actions 810 and 812 trail facing, 2026-11-05

Six trail paths capture unsigned facing after generating the packet but before the coordinate RNG calls: `0x5F9DB7`, `0x5FA249`, `0x5FA558`, `0x5FA77F`, `0x5FABBF` and `0x5FAE1E`. The first, fifth and sixth retain Y across RNG(100); the other three retain `Y + 25.0` across RNG(50), then use RNG(100) for X. Previously all six read facing after the coordinate RNG calls. The source now captures facing before those calls, and focused VC8 compilation confirms the six corresponding lifetimes. The root remains non-exact (27874-byte target, 28768-byte candidate section tail, first mismatch +8); no exact credit is claimed.

## Action 856 spawn facing, 2026-11-05

At `0x5FE17F..0x5FE1C0`, the target captures unsigned facing and both double-precision coordinate centers before the first RNG(60); it computes Y between the two calls and X after the second. The earlier source captured the centers but loaded facing after both calls. An unsigned-byte local now captures facing in the proper interval; focused VC8 output loads it at `0x4EFD` before either coordinate RNG call and keeps both QWORD centers. The full 27874-byte root remains non-exact (candidate section tail 28944, first mismatch +8); no exact credit is claimed.

## Burst speed arithmetic, 2026-11-05

The shared burst paths multiply the random value by the double-promoted `0.01f`, add the base and only then store the packet float. For example, native `0x5F9895..0x5F98B2` and `0x5F9E7D..0x5F9E9A` have no intervening float store. The previous source explicitly converted the product to float before the addition; the burst macro now retains the native expression, and focused VC8 output confirms multiply/add/store at `0xA38..0xA4F`. A check of the ordinary bounded RNG results found no final float difference for the two current base/range combinations; the correction is to the recorded arithmetic lifetime, not a claim of an observed gameplay difference. The full 27874-byte root remains non-exact (candidate section tail 28800, first mismatch +8); no exact credit is claimed.
