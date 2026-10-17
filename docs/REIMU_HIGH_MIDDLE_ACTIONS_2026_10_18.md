# Reimu:608..619 high families

## Target and source observations

Target is original Japanese TH10.5 v1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Parent `Reimu_dispatch_action_state_vslot28 @478FA0` remains81550 bytes
through48CE2E, SHA256
`dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6`.
Candidate/origin/name/source selection were rechecked: authored,
unclassified/declaration-only. No implementation or exact entry is added.

Seven physical bodies occupy `[488F62,48A24E)`:4844 bytes/1211 instructions,
SHA256 `4658a2571c833b36ef1262da7d21164d3d2ce586e0e56b1fdc0454b333522a67`.
Canonical table destinations and every instruction are rechecked.

|Action|Entry|Next physical entry|
|---|---|---|
|608|488F62|48928C|
|609|48928C|48939D|
|610|48939D|489478|
|612|489478|48975F|
|614|48975F|489C27|
|616|489C27|48A064|
|619|48A064|48A24E|

`ReimuActionStateHighMiddleCases.hpp` joins the same monolithic source
through619. Gaps use real4740C0; later actions remain pending. Its bool is
a staging interface, not the original complete void ABI. Compact C++ loops
and shared branches remain source-shape hypotheses; original TU spelling,
compiler sharing/expansion and provenance are not proved.

608 publishes texture6/duration2, applies gravity/crossing below sequence3,
and advances/RET at sequence1 counter>20. Completion publishes duration60.
Its post-advance frame4 window/event/effect setup precedes frame5 velocities
(-2,7.5)/AY0.3f and frame10's WORD730=1. After a sequence3 node's set9,
processing continues into the live signed WORD counters. Positive730
decrements732 with16-bit wrap; nonpositive732 and734<3 send two858 requests.
First payload is `[734*10-80,0,0]`, then all three floats become `[0,0,2]`.
Both use x+signed-facing78,y+120. Wave11 follows the returning requests,
then732=6 and734 increments. Coordinates/facing are read again per request.

609 advances/RET at sequence1 counter>40 or WORD738==1, and sequence2
counter>24. Its post-advance frame5 sends852 `[0,0,0]` at x+facing228,y+93,
then wave12.610 uses sequence1 >60, completion texture duration120 and
frame7's859 at x+facing280,y+93 with null pointer/count0, then wave13.

612 has no landing/texture call. Sequence0/frame1 initializes scales/color
and wave2, then frame>0 shrinks/widens scales and subtracts25 from alpha,
setting alpha0 at<=25. Sequence2 restores scales only at frame0 and applies
0.7f gravity while frame<3. Sequence3 clears nonzero state only for signed
BYTE184>0, then uses double y+VY prediction for height/zero/next-block/RET.
Post-advance frame3 invokes window(0,2,60), secondary cycle, WORD48A=40 and
event23. Sequence2 node moves to peer x-facing180,y150, velocities6/8 and
wave6; frame3 sets7.5/-24 without resource consumption.

614 lands in sequences0/3/4/7 and always applies gravity. Crossing below3
uses47FFA2: **this caller has EDI=3**, so the shared `PUSH EDI` sets3.
Initial source incorrectly reused another caller's5; the required branch
found two differences, retained in `initial-shared-tail.json`, and source
was corrected. Crossing above3/below7 sets7. Node4's signed count<2 loop
increments730, calls set_sequence(0), directly writes timer0/frame3, then
sends825; it does not call an invented frame setter. Other825 sites and
velocity/damping nodes retain their independent live tests and ordering.

616's seven-way sequence switch uses height300 prediction in1/2; a crossing
does zero motion,set3,y=height+280 and eight866 rays `[i*45,30,live2]`.
Sequence3 places y using the old73C offset, then adds2 and caps it20.
Sequences4/5 add widened0.2f horizontal speed, cap8, and settle at height300.
Sequence5 >=120 advances the block, sets velocities-4/4.5 and AY0.5, then
continues animation advancement.6/7 crossing sets8 and also continues.
Completion sets0/RET. Node1 sets VX0,VY25,AY0.7f and sends866 `[0,0,0]`,
argument5=-1, at height+150 before later window/event/effect processing.

619 uses sequence1 >=20 and completion set0/RET. Frame3 performs window/
event/effect setup; frame5 dispatches wave22 and seven869 rays with
`[float(double(51.4f)*i),0,0,i]`. Native sine>0 selects argument5=-1, otherwise1;
positions use current x,height+150. Entry timer900/count0/latch0 follow all
returning requests. Subsequent ray/pair requests and post-world continuations
have raw instruction evidence, not dynamic returning-call proof.

## Focused verification

```bash
scripts/compile-unit.sh src/characters/ReimuActionStateDispatch.cpp build/reimu-high-middle/ReimuActionStateDispatch.obj
python3 scripts/audit-reimu-high-middle-actions.py build/reimu-high-middle/ReimuActionStateDispatch.obj
```

Fresh pre-edit high-entry smoke passes0/108. The same previous-source object
passes0/657 with the new bounded animation domain. Eighteen actual staged/
directional action destinations plus each current input replace accumulated
unrelated action keys. The private map returns to1 MiB; earlier fixtures and
oracle classes are unchanged. Missing native destinations still fail closed.

VC8 SP1 `/O2 /GS- /GR /EHsc /MT`, default FP/no injected compiler environment,
produces38872 staged text bytes. Object SHA256
`205e11469d62456ecd154db79241aa897e438d4a4c2eba9f47417993538fb491`;
`build-receipt.json` pins compiler/source/header/object hashes and the separate
previous-commit baseline. The oracle separately pins its execution inputs.

**0/6376 differences**, `build/reimu-high-middle/native.json`, input SHA256
`b0a8b6fdcc9c6d635eecba390d0237e2e0088442775cb75bf22fa6e7ee083c4c`:

|Cohort|Cases|
|---|---:|
|Motion/landing/completion/NaN|756|
|Sequence/counter/timer/frame nodes|1764|
|608 signed timer wrap and shot gates|840|
|612 scales/alpha and signed state flag|430|
|616 height/velocity/counter and hover offset/NaN|1186|
|Strict/non-strict cutoffs and609's flag|576|
|Texture branches/completion|96|
|29 required original sites, both x87 precisions|58|
|Earlier high/middle/low/entry/common paths|657|
|Gaps/defaults and high handoffs|13|

6001 genuine RETs,319 real465190 entry stops,34 effects,12 common entries,
1 set669 and9 pending are compared.8695 target and5536 staged instruction
addresses are sampled. Actual helpers execute4998 texture publications,
9902 checked deque accesses,20 WORD48A writes,93 waves and12 each of indexed
sequence-window/secondary-cycle calls. All three window arguments are compared
as12 raw stack bytes, even when the inactive window has no state effect.
4096 actor bytes, ordered calls/receivers/arguments, pointed payloads, manager
slots, world scalar, MT state and control word are compared. Returns require
stack delta4, saved registers and x87 TOP=0. Arrays require live aligned stack
storage/count/content;859 explicitly requires null pointer/count0.

Compiled wrong-source controls fail1/91 for window outcome2->1,8/30 for
unsigned BYTE184 testing,336/840 for incrementing732 instead of decrementing.
Reports/private build receipts remain; rejected sources/objects are removed.
No helper/callback return is fabricated. Read-only animation/texture IDs,
flat surface, inactive indexed/secondary events, zero sound handles and masked
PC53/PC64 bound this proof. Active window/backend contexts, returning world
calls, complete floating exceptions and full-root equivalence remain unknown.

## Preservation and next work

Six old adapters rebuild with identical non-debug code/data and relocation
offset/type/symbol/value/section identities, sizes530,771,1562,4017,4409,11271.
Smokes pass0/9,0/88,0/64,0/99,0/150,0/59. No full historical matrices or cold
aggregate replay. No accepted unit depends on this private header, and accepted
source/profile/relocation ledgers and exact totals are unchanged.

One direct Ghidra read-only clone attests target/entry/base/Windows x86,
mapped.text/root and all23 remaining high entries/instructions, including the
current seven. `REIMU_HIGH_REMAINING_READBACK_PASSED` is in `ghidra.log`;
`analysis-receipt.json` pins table/body/log/script/primary hashes. All9 primary
files are unchanged; clone removed after a768 MiB/two-CPU run. Future groups
may reuse this evidence after rechecking their bytes and primary hashes.
Wrong-target IDA contributes no semantics. Obsolete objects/controls/caches are
cleaned. Next continue650 at48A24E. Complete void ABI, CFG/relocations,
VC8/LTCG/TU provenance, returning world contexts and all81550 canonical bytes
remain parent acceptance requirements.
