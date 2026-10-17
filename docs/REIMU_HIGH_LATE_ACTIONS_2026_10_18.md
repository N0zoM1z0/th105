# Reimu:650..711 high families

## Target observations and source

Target is original Japanese TH10.5 v1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Parent `Reimu_dispatch_action_state_vslot28 @478FA0` remains81550 bytes
through48CE2E, SHA256
`dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6`.
Candidate/origin/name/source selection were rechecked: authored,
unclassified/declaration-only. No implementation or exact entry is added.

Eight physical bodies occupy `[48A24E,48BC4D)`:6655 bytes/1697 instructions,
SHA256 `b6650089952a0d46c7cedf81571051e8cc8d8bd58480ac254b33839bb53c78b4`.
Every retained instruction and table destination is checked against the PE.

|Action|Entry|Next physical entry|
|---|---|---|
|650|48A24E|48A451|
|651|48A451|48A69E|
|658|48A69E|48A982|
|669|48A982|48AE16|
|695|48AE16|48AF80|
|696|48AF80|48B034|
|710|48B034|48B659|
|711|48B659|48BC4D|

`ReimuActionStateHighLateCases.hpp` continues the same monolithic source
through711. Gaps call real4740C0; later actions remain pending. Bool is a
staging interface, not the original complete void ABI. Compact loops and
combined branches are source-shape hypotheses, with no compiler-sharing,
original spelling or canonical equality claim.

650/651 publish texture6/duration2 and land only in sequence4. Sequence1
advances/RET at counter>30/>60. Signed WORD730<5/<10 and signed counter%5==0
send850/853 before animation advancement, at x+signed-facing18,y+120.
Payloads are `[(730-2)*30,0,730%3]` / `[730*-45.0,0,730%3]`.651 then sends860
after clearing only the first two floats;730 increments after returning
requests. Gravity/crossing in sequences2/3 occurs before the shot tests for650
and after them for651. Crossing sets4/RET. Completion sets0 without another
texture publication. Frame2's event/effect precedes window(0,2/5,60) and the
secondary cycle, using shared tails4886BE/4888FB.

658 lands only in sequence3 and subtracts gravity in every sequence, checking
crossing only below3. Its sequence1 cutoff is>20; completion sets0 without
608's duration60 publication. Frame4 window/cycle/event/effect, frame5
velocities(-2,7.5)/AY0.3f and frame10 WORD730=1 retain their ordering. A
sequence3 node sets9 and continues. Positive730 decrements signed732 with
WORD wrap; nonpositive732 and734<3 send two858 payloads, first
`[734*10-80,0,0]`, then `[0,0,2]`. Wave11,732=6 and734 increment follow both
returning requests; the shared48925C tail uses the caller's live registers.

669 has no landing call. Sequence1 counter>=240 advances the block, sets
AY0.2f and returns. At<=180, even counters send three869 rays with
`[float(i*120.0+73C),30,3]`, then four with `[float(i*90.0-73C),30,3]`, then
add4 to73C. Multiples of8/10 append `[0,0,4]` / `[unsigned(random_roll(360)),0,5]`.
All use three floats, unlike619's four-float869 call. Ray y retains the exact
association `sin(-angle)*80 + (double(y)+100)`; x uses signed facing. Coordinates
and phase are re-read for each returning request. Sequences2/3 gravity/crossing
zero motion before height/set4/RET. Completion sets0/RET. A sequence1 node
executes real wave24/layout8. Frame2's secondary/event/effect precedes three
separate WORD clears at7C8/7CA/7CC. Later rays, modulo8/10 requests and those
post-world stores have raw instruction evidence only.

695's frame6 event55 precedes three140 effects, then141 and142. The last two
use argument5=-1 from live EBX;142 also uses unshifted y.696 subtracts double1.5
only for positive VX, then clamps negatives to+0. Signed zero/NaN behavior is
preserved. Frame3 sets VX20; frame4 sends event28.

710/711 land only in sequence6. Gravity/crossing in1..5 sets6/event30/RET;
711 shares710's48B079 tail. Completion sets700 and continues. A sequence1
node restores the three floats at780/784/788, now offset-asserted in the private
prefix. Sequence3 counter>=20, tested after advancement, quarters VX/VY and
sets AY0.1f/0 before RET. Sequence4 frame1 dispatches wave4 and indexes the
original `g_match_identifier @6FA894` with unsigned bounds0..3. Table order is:

|Mode|710 count / spacing|711 count / spacing / aim offset|
|---|---|---|
|0|3 /120|3 /60 /60|
|1|4 /90|4 /60 /90|
|2|6 /60|5 /45 /90|
|3|8 /45|6 /36 /90|

Each900 ray re-reads peer/self positions and signed facing, runs actual atan2,
and passes `[float(-aim-offset+i*spacing),4,0]`. Its y association is
`(sin(-angle)*100+y)+100`, distinct from669. Out-of-range modes emit nothing;
frame3 still sets AY0.1f. Later rays/count/spacing have instruction evidence,
not returning-manager proof. Native airborne landing also selects704, which
is included as an actual resource destination in this phase's fixture.

## Focused verification

```bash
scripts/compile-unit.sh src/characters/ReimuActionStateDispatch.cpp build/reimu-high-late/ReimuActionStateDispatch.obj
python3 scripts/audit-reimu-high-late-actions.py build/reimu-high-late/ReimuActionStateDispatch.obj
```

VC8 SP1 `/O2 /GS- /GR /EHsc /MT`, default FP/no injected environment,
produces43272 staged text bytes. Object SHA256
`272125a7171340f5643f1000ee9741d59fad00ecf8f24b79ac5c1180fb3a5f7f`.
`build-receipt.json` pins compiler/source/header/object hashes and a fresh
pre-edit3fed4be baseline. Old high-middle smoke remains0/91 with its original
four-float-only869 guard. The new subclass permits3/4, retaining aligned live
stack, complete count/content and target-versus-source comparison. Earlier
fixture classes and key domains are unchanged; this subclass adds704.

**0/6481 differences**, `build/reimu-high-late/native.json`, input SHA256
`a8b85f40550e88ea49c65b30b8cc9f02f88cd3d97991eb6a0847ece13fb076a8`:

|Cohort|Cases|
|---|---:|
|Motion/landing/completion/NaN|864|
|Sequence/counter/timer/frame nodes|2304|
|650/651 signed shot gates, WORD limits and facing|1152|
|669 signed cadence, phase, facing and240 cutoff|680|
|Both900 mode tables, unsigned bounds and peer geometry|600|
|Stored-motion floats and696 friction/NaN/signed zero|54|
|33 required original sites, both x87 precisions|66|
|Earlier high/middle/low/entry/common paths|748|
|Gaps/defaults and upper handoffs|13|

There are5162 genuine RETs,1251 actual465190 entry stops,46 effects,12 common
entries,1 set669 and9 pending.9788 target/6129 staged root instruction addresses
are sampled. Actual helpers run3610 texture publications,7216 checked deque
accesses,1045 waves,416 atan2 calls and5 layout publications. Shot/cadence/mode/
snapshot fixtures require their advertised original sites/requests.4096 actor
bytes, ordered calls/receivers/arguments, pointed payloads, manager slots,
world scalar, MT state and control word are compared. RET requires stack
delta4, saved registers and x87 TOP=0. No target bytes or callback results are
patched. PC53/PC64, flat surface, bounded read-only animation/texture IDs,
inactive indexed/secondary events and zero sound handles limit this proof.

Compiled wrong-source controls detect1/748 for619's count4->3 despite the
new subclass accepting both counts,40/680 for669's >=240->>240, and50/600 for
711 mode0's offset60->90. Control reports/build receipts remain; rejected
sources/objects are removed. These checks do not prove later volley counts.

Six old adapters rebuild with identical non-debug code/data/relocation
identities, sizes530,771,1562,4017,4409,11271; smokes pass0/9,0/88,0/64,0/99,
0/150,0/59. No full historical matrices or aggregate cold replay. Accepted
units, compiler/relocation ledgers and exact totals are unchanged.

## Analysis and next work

The previous direct Ghidra receipt already attests all23 remaining high
entries/instructions. This unit rechecks its eight table/body/instruction
ranges against the canonical PE and all9 primary database hashes unchanged;
`analysis-receipt.json` pins the reused receipt. No new Ghidra process or clone
is needed. Wrong-target IDA preflight is recorded and supplies no semantics.
Unused previous objects, baseline, rejected controls and caches are cleaned;
current objects and bounded receipts remain. Next continue720 at48BC4D.
Returning world/backend contexts, original full void ABI, CFG/relocations,
VC8/LTCG/TU provenance and all81550 canonical bytes remain root requirements.
