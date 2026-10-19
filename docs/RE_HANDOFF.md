# TH10.5 reconstruction handoff

Current as of 2026-10-20. This page contains operational state; detailed
checkpoints are in [the October 18 archive](RE_HANDOFF_HISTORY_2026_10_18.md),
[the October 2 archive](RE_HANDOFF_HISTORY_2026_10_02.md) and
[the September archive](RE_HANDOFF_HISTORY_2026_09_26.md). Live ledgers and
fresh canonical comparisons override historical prose.

## Target, workflow and acceptance

Use only original Japanese TH10.5 v1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Read [AGENTS.md](../AGENTS.md), [architecture](ARCHITECTURE.md) and
[workflow](RE_WORKFLOW.md) before changing reconstruction state. Use one
writable session, one bounded unit and serial VC8 builds. Keep heavy work at
nice10/CPU0; clean obsolete products periodically. Do not delegate matching.

```bash
git status --short
python3 scripts/verify-target.py
python3 scripts/check-ida-mcp.py
python3 scripts/report-reconstruction-status.py --summary
python3 scripts/validate-tracking.py --require-target
```

The target passes verification. The attached IDA session still reports a
SHA256 beginning `10350095`, so do not use its semantic data. Hash-attested
raw PE analysis is available. Independently re-attest any direct Ghidra
project before using it; do not use the factory adapter or patch target bytes.
The current primary includes the archive loader/template ABI views, three
typed Win32 import functions, the Reimu Object4892-byte entry and the separate
323-byte action980 continuation. The boolean loader return is explicitly AL:1.
The two Object functions use ECX:4/void/RET0; a CALL_RETURN analysis override on
the target-proven4A2F8B tail prevents the decompiler from expanding596370 into
the root. Changes are saved privately and reopened for readback before
promotion. Current nine-file pins are in
`build/object980-short-context-20261019/primary-db-after.json`;
`build/archive-loader-shape-20261019/primary-db-after.json` is the predecessor.
Target/mapped text and callable bytes remain unchanged.

Read the current ledger census with `report-reconstruction-status.py --summary`.
The family1 traversal checkpoint adds one independently replayed686-byte exact
authored function. Its542-byte pair provider is now source-present after full
native instruction/return coverage, but remains557/542 nonexact. The complete
collision-phase parent also remains nonexact; no cold aggregate verification
is asserted.
`claims.csv` remains header-only. Source presence, mapping and diagnostic
interval equality confer no exact credit. The Reimu CPU root remains
source-present in a probe unit with no exact result.

The user prioritizes the large Reimu root, requests commit **and push**, and
asks to avoid routine full historical/all-unit replays. Run focused affected
checks; a deliberate aggregate percentage claim requires a cold
`verify-exact-units.py --all`. The README already contains the requested
notice about ongoing reconstruction and the substantial work still needed.

## Current Reimu source checkpoint

Boss: `Reimu_dispatch_action_state_vslot28 @478FA0`, authored but still
unclassified/declaration-only. Callable `[478FA0,48CE2E)` is 81550 bytes,
SHA256 `dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6`.
The target CFG covers 20243 reachable instructions / 81488 code bytes, plus
62 bytes of proved alignment gaps, 1188 direct calls to 32 callees, 153 RETs
and 11 switches. See [boundary evidence](REIMU_ACTION_ENTRY_2026_10_17.md).
Do not promote staging methods to original compiler boundaries or add an
implemented/matches row without complete supporting evidence.

The current checkpoint restores602's frame-counter/timer/index-first firing
guard and600/601/602's wide facing carrier for effect115. Each selected argument
preparation now agrees with all16 target instructions/64 canonical bytes. The
carrier is used as signed-byte X input and unsigned direction; layout and helper
ABIs are unchanged. All1214 prior equal complete membership/multiplicity checks
survive.601/602/604 now join the target's slot14 majority group;605/608/651/658
remain different. A broader650/651 carrier control loses ten earlier landing
checks and is unselected. See [602 guard and direction evidence](REIMU_602_GUARD_AND_DIRECTION_2026_10_19.md).

Earlier416/546 action9 sharing,414's shared exit and the three distinct effect62
tails remain selected. Indirect totals220/219 still expose300/320's missing
physical copy; the earlier220/220 concealed an extra546 CALL. See
[shot/fan sharing](REIMU_SHOT_FAN_SHARED_EXIT_2026_10_19.md) and
[414 evidence](REIMU_414_SHARED_EXIT_2026_10_19.md). Local byte windows and correct
counts do not establish whole-root exactness.

Current pins:

| Artifact | Value |
| --- | --- |
| Ordinary object SHA256 | `fa172c304ff7bf7cf5291487bcbee9f71b009656ed8918b5ec0abf667a0eeff7` |
| Generated source SHA256 | `c9107448d21588ecd59f4b528b14ec7a82fb7d77a4f8c13d6b7c9f6f5c562481` |
| Ordinary/genuine canonical payload SHA256 | `6527316db79ea2e1e3dd600c057f6376b472fcf43f7f6d9f2f861dac716481a8` |
| Producer receipt SHA256 | `de9c95cd46d9bcbcbecee1034bc46214a5ae79e26e60875799fe7d2ab45e22c6` |
| Payload / prefix / frame | 82824 / 81452 / 570h |
| First strict mismatch | +541 / 4791BD, conditional-branch operand at 4791BB |

Genuine and ordinary payloads agree completely, including all2473 replayed
fields;1281 HIGHLOWs and eight separate linker alignment bytes qualify.
All11 switches and15 request-buffer contracts pass. Whole-root source has20254
reachable instructions versus target20243. Remaining direct partitions are
4351C0/435D60/45AF40/473DD0/478EE0. Three missing physical direct copies and
low9/300/320 sharing remain open. Genuine linking remains nonexact to target.

Fresh selected ordinary execution passes0/2675 integration/shot/nonflat cases
and0/210 cases covering602 firing/misses. The latter require120 actual MT/object854 entries
and90 RETs, with signed counts/five facings/three native-seeded states/two FP
precisions. Wrong count<14-><=14 source gives30/210 real mismatches; wrong602
unsigned X interpretation gives8/100 effect115 mismatches. The complete selected
payload also equals the private candidate passing0/480 actual next-sequence
threshold cases and0/100 effect115 entry cases. Independent bool staging through
606 passes0/2136 cadence/texture/required-branch cases. Code-identical/repeated
inputs are not additional unique coverage. Both real next-sequence tails are
sampled through320 callbacks and native root RETs; world requests stop at their
actual entries. Returning-world/resource graphs and indeterminate740 remain
outside the proof. No exact credit or all-unit replay is claimed.

New300/320 named-float controls separate landing/gate and reduce differing direct
partitions5->3, preserving all1209 prior equal checks. They still merge advance
and slot8 and use an incorrect temporary slot; they remain unselected. Named
input/result/root-scope forms for320 produce the same complete26d370eb payload.
The prior selected source and that control each pass0/606 actual-helper cases;
a wrong subtraction->addition source control gives88/606 differences. A fresh
c9107448 build now passes0/989 focused300/320/321 inputs, requiring321's actual
PUSH28/JMP47DA68->47CC49 event predecessor. Both CALL/RET memberships contain
all three actions. Wrong321 event28->27 still preserves1214 membership checks
but gives10/989 actual argument/trace mismatches. Twenty-five source controls
remain unselected: explicit
event joins lose that group, named locals/inline forms still miss the distinct
advance/slot8 copies, and720 lifetime forms do not reproduce target base24/
index20. Current720 base is18/index20. Full CFG/ESP analysis distinguishes
physical scalar reuse from inferred source ownership. See
[slot and three-action tail constraints](REIMU_300321_SLOT_CONTEXT_2026_10_19.md).
This does not prove a compiler/LTCG impossibility.
Returning-world callbacks, indeterminate740 reads and arbitrary world/resource
graphs remain outside these proofs. No exact credit or all-unit replay is claimed.

Earlier selected197/658 and198/608 surface landings, their real int sequence
parameter and complete slot+C partition remain preserved. See
[shared sequence landings](REIMU_SHARED_SEQUENCE_LANDINGS_2026_10_19.md).
The five explicit float conversions still retain target FIMUL operations in
89/545/546/550/551;202/203/225/226 still share action10 landing. Older listed/plain
82808-byte and RTM/SP1 controls, conditional full-CFG x87 dataflow and5752
actual-helper advancement cases belong to the predecessor source. They do not
prove the cause of the remaining sharing differences. See
[low9 call cloning](REIMU_LOW9_CALL_CLONING_2026_10_19.md) and
[x87/type evidence](REIMU_X87_OPERAND_TYPES_2026_10_18.md).

## Current ReimuObject entry initializer

Active root `ReimuObject_initialize_action_entry @4A1CE0` has complete
source in `src/characters/ReimuObjectActionEntry.cpp`, probe unit
`gpt-web-reimu-object-action-entry`, and no exact credit. RTTI/vtable6C40A4
slot3C proves ownership; raw CFG closes all1325 instructions/4892 bytes,
42 primary destinations, seven auxiliary switches,39 RETs and a596370 tail.
All65 direct CALLs to ten helpers retain their target multiplicities.

Five x-then-y chained scale assignments restore the822/903/904 return-copy
structure. Explicit906 sequence2/5 and3 edges into908's corresponding angle
tails then restore all548 adjacent metadata bytes and908's pointer/phase
schedule. Diagnostics are41/43, with no earlier equal owner lost; the
callable still ends4A2FFC without included alignment. Source SHA3803a002,
canonical5440-byte payload65298d36; strict first difference+1140/4A2E20.
Only14 callable bytes in906/999 remain different, in pointer/call registers
and preparation. A fresh build still reproduces these pins. The new bounded
execution audit passes0/672 through624 actual selector/frame/sprite-commit chains
and native RETs; wrong999 sequence and906 phase sources fail48/672 and28/672.
Five conversion-carrier controls preserve the entire65298d36 payload and are
unselected. This covers906/999 only, not whole-root semantics or exactness. See
[real selector execution evidence](REIMU_OBJECT_ENTRY_CALLS_2026_10_19.md).

A genuine `/GL`+`/LTCG` diagnostic DLL now closes through real ordinary
providers, a full private404E60 texture-size provider and CRT startup. Its
quantized lookup declarations/definitions consistently return double;
the refined oriented provider becomes nonexact and is not promoted.
Independent replay verifies all247 relocation fields,181 PE HIGHLOWs,
named direct providers, literal bits and local table/code-pointer roles.
The linked payload equals the ordinary65298d36 payload: the same14 body
bytes remain, with zero metadata differences and the target10h local frame.
This context is a negative control, not original-TU or exactness evidence.
No shared helper/header/profile/binding is changed.

Raw45C390->vslot1C45C180->45C110->436760->4073C0 forwarding does not construct
an integer status. A private natural void/short selector compares202/202,
but does not uniquely prove the original return type or add accepted credit.
Changing the large root's discarded selector result is byte-neutral. The
prior-source RTM/SP1 and typed-velocity controls are also byte-neutral;
reading908's angle before its phase into a float adds32 callable bytes.
On the joined source, pointer captures, physical inheritance and9064-first
ordering all preserve65298d36 and remain unselected.
The next joined-source audit also finds direct RNG expansion, named short
arguments, discarded void result, implicit bool guard, typed color alpha,
GS and correctly ordered `/O2 /Ob1` byte-neutral. An int selector argument
regresses to113 body differences; unsigned short changes frame and conversion
shape. Extra905/907 angle joins and902/905..907 state-one joins regress; do
not generalize906's successful goto form. Complete receipts are below
`build/reimu-object-entry-registers/`. Fresh source-ownership/lifetime controls
and current-source RTM still preserve the full65298d36 payload; source/commands
are under `.analysis/reimu-object-entry-source-20261019/` and
`build/reimu-object-entry-source-20261019/`. Reimu remains at14 body differences;
the root's remaining compiler context remains open.

See [ReimuObject entry evidence](REIMU_OBJECT_ENTRY_2026_10_19.md).

Current906/999 execution, negative and read-only Ghidra receipts are below
`build/reimu-entry-carriers-20261019/`, with private regeneration recipes under
the corresponding `.analysis/` directory. All nine primary database hashes stay
unchanged. Current Reimu compilation/link receipts are below
`build/reimu-object-entry-abi/`; preceding
receipts remain below `build/reimu-object-entry-lifetimes/` and
`build/reimu-object-entry/`. Previously checked raw/Ghidra RTTI establishes
eight entries including the complete object, with base offsets0/4/130h/330h.
Nine read-only Ghidra DB pins agree at that checkpoint and its alias is removed.
All23 accepted members across seven focused helper units replay exact at
the preceding source-recovery checkpoint; their inputs are unchanged here.
The effect unit's existing nonaccepted5F9350 probe remains nonexact. No cold
aggregate replay is claimed.

## Shared Object action980 exact checkpoint

`CharacterObject_continue_action_980 @596370` is now canonical323/323 under
the existing `gpt-web-object-action-980` unit. Changing only its local vslot0C
selector argument declaration from int to short restores the target call
preparation, superseding the October2 scheduling/LTCG stop condition. All82
instructions/323 bytes are reachable, with one RET, seven REL32s and seven
DIR32s. No shared header, compiler profile, layout or relocation binding changes.
The complete root4A1CE0 remains nonexact and receives no partial credit.

Direct Ghidra finds both function entries absent from the prior saved primary.
The raw-reconciled function views and registered tail are now saved and read
back. The root decompiler previously included51 external p-code instruction
addresses; function entries alone leave those51, while the verified CALL_RETURN
metadata makes the count zero. Reopened root/helper views both have zero
out-of-body p-code addresses. Decompiler text remains a hypothesis.

See [exact recovery and analysis safety](OBJECT_ACTION980_WORD_ABI_2026_10_19.md).

## Family1 pair source checkpoint

`CollisionContext_resolve_group_b_object_clash @46CA80` is now mapped and
source-present in `ObjectResponses.cpp`, with a function in the existing mixed
`cross-v106a-object-responses` probe. Raw CFG closes all137 instructions/542
bytes and eight RET8 sites. The source preserves signed priority words,
byte-slot wrap, the asymmetric right-source slot at46CB64 and the predicate
miss's no-reset bypass. The old prose/source remain hypotheses until checked;
the prior dispatcher matrix had not exercised46CB74.

Fresh native execution passes0/2638 signed-extrema/overlap/source-byte/alias
cases with every target/source instruction and physical return visited. Actual
predicate/extent/reset instructions run; making the exceptional slot symmetric
fails12/219 smoke cases. The single-box fixture does not cover all predicate
geometry or arbitrary game states. Read-only direct Ghidra re-attests root,
mapped text and both exact inbound calls; all nine primary DB hashes stay fixed.

Canonical comparison remains557/542, first+18; the late register/store schedule
and physical tail sharing differ. RTM/SP1, ordering/inline/shared-exit controls
and a genuine same-context dispatcher/pair TU do not close it. The latter keeps
the dispatcher686/686 exact. Original source/TU/compiler context remains open;
there is no demonstrated LTCG impossibility. The affected accepted147-byte
46C9E0 still replays exact;46C930 retains its earlier+52 residual. No new exact
credit or cold aggregate replay. See
[pair source, counterexample and limits](FAMILY1_PAIR_RESPONSE_2026_10_20.md).
Final reports are below `build/family1-pair-20261020/`.

## Family1 object traversal exact checkpoint

`BattleCollisionPhase_dispatch_family1_clashes @46DD40` now matches the full
**686/686** under `gpt-web-family1-object-clashes`. The192-instruction target
has one RET0,25 invalid-parameter sites and two genuine member calls to46CA80.
Native checked std::list<void*> replaces the old664-byte manual-iterator
hypothesis. Direct first-phase array indexing and begin-before-end lifetimes
naturally preserve the full list owner, saved node bindings and all checks.
Explicit pointer traversal is same-sized but remains nonexact.

The same-side pass filters frame50/100000h, frame4C/40h/80000h and byte1A0,
then skips equal payloads; the cross-side pass traverses both families with
its distinct gate/equality policy. Views pin list44/12-byte stride and actor
1A0/1A4, without asserting complete original classes. The dispatcher takes
ECX context/RET0; its pair call takes the same receiver and two slots/RET8.

Only46DD40 gains exact credit. The old compound origin rule now selects just
46CA80 and uses both newly matching inbound callers plus its prior eight reset
witnesses; authored/excluded census is unchanged. The private real-member
closure keeps686/686 while parent46DFF0 remains1449/1452, first+559. New narrow,
visibility and cap controls still do not close that parent or prove LTCG.
The subsequent pair review above selects46CA80 source without exact credit.

A226-record native matrix and inequality negative control exercise real pair/
geometry routines with bounded lists, filter flags, priorities, duplicate
payloads and overlap states. The environment is seeded by the original parent;
child game/helper results are not supplied. The read-only128MiB/CPU0 direct
Ghidra pass re-attests the root/inbound edge and reads back signatures; all
nine primary DB hashes remain unchanged. See
[exact source, execution and limitations](FAMILY1_OBJECT_CLASHES_2026_10_20.md).
Final reports are under `build/family1-clash-20261020/`; no cold aggregate claim.

## Battle collision phase source checkpoint

`BattleCollisionPhase_run @46DFF0` now has complete selected source in
`CollisionPhase.cpp` and the separate `gpt-web-battle-collision-phase` probe.
Raw CFG closes1452 bytes:1434 reachable bytes plus18 bytes of branch-skipped
alignment,449 decoded instructions,46 direct calls, two actual manager slot24h
calls and one RET0. Five exact parent pipelines and the already-authored origin
rule retain their witnesses; three exact geometry-call witnesses are
pinned. The adjacent family1 traversal is now independently exact; its
remaining pair resolver has a separate nonexact origin rule. No authored/
exclusion count change.

The old unselected file used volatile scheduling, manual sentinel assertions
and a free-function node facade. Native std::list<void*>, typed owned-object
iterators and native vector sizes reproduce all21 checked calls, seven Buynode
and seven Incsize sites. Actual getter4B9DA0 and canonical manager vtable6C40FC
support the virtual interface. Scoped fighter lifetime in the final guard
recovers the full1369-byte canonical prefix and target2Ch frame.

The root remains1449/1452, first+559/46E549. Its final low-word conversion and
register schedule are unresolved; no new exact row, padding or LTCG conclusion.
Native validation separates114 complete no-self-hit entries from396 explicit
2Ch-frame tail entries. Actual game/geometry/container/getter instructions run;
only validated node-allocation/free environment boundaries are callbacks.
The same-side hit effect/callback environment remains outside the fixture,
while its root callsite is inside the equal prefix. Native coverage, negative
controls and exact limitations are recorded in
[the complete phase evidence](BATTLE_COLLISION_PHASE_2026_10_20.md).

Final reports are under `build/collision-phase-20261020/`; private trials and
direct Ghidra scripts stay under `.analysis/collision-phase-20261020/`.
The read-only128MiB/CPU0 Ghidra pass re-attests target/mapped bytes/five callers,
reads back physical signatures and leaves all nine primary database hashes
unchanged. This is source-present progress; the preceding2156-byte geometry
match below remains exact. No shared headers or aggregate exact claim.

## Collision-frame preparation exact checkpoint

The 2026-10-20 continuation closes the complete
`CollisionGeometry_prepare_from_frame @45C500` at **2156/2156 canonical exact**
under `gpt-web-collision-geometry-preparation`. Hash-attested raw CFG accounts
for all645 instructions, two RET0s and the separate vector error jump40C350.
The ordinary `/O2 /GS- /GR /EHsc /MT` source recovers the full3Ch target frame;
all bytes hash to79b6295ec257dabdb090b1e3ae8943ccbfd2468fc9d438785215c75ddfec4dff.

The former2164-byte/frame34h blocker was source lifetime, not a demonstrated
LTCG limitation. Positive-facing descriptor paths require real aggregate
copies; direct groupA indexing gives the target independent scalar/scaled
inductions. A signed-char extension count remains live across helper calls
and both count publications, rather than rereading the object count. Explicit
cache-B if/else initialization brings the root to2156 bytes with two commuted
SIB differences; direct descriptor expressions remove those last differences.
A natural member entry also closes in private diagnostics, so exact code does
not uniquely recover original C++ spelling. No forced registers or byte edits.

All three affected geometry providers replay exact335/335,445/445 and1386/1386.
The previous one-argument fastcall ledger errors remain corrected to ECX member
receivers plus two/six stack slots. The complete root's full native cold/warm
matrix passes all1344 inputs/2688 calls per side, with621 normal-path
instructions visited on each side and actual geometry/angle/conversion/SSE2-ceil code;
resource/CPU data are fixture inputs, and invalid-container/throw paths remain
outside execution coverage. The vector error helper40C350 remains in origin
review: canonical caller-edge binding gives it no compiler exclusion or exact
credit. The new2156-byte root uses the canonical-exact authored baseline;
its superseded nonexact origin rule is removed.

See [geometry exact recovery, ABI and execution evidence](COLLISION_GEOMETRY_PREPARATION_2026_10_19.md).
Reproduction: focused `scripts/build.py --unit ... --compare --json` for the
caller unit above and `cross-v106a-collision-preparation`. Final reports are
`build/animation-state-20261019/formal-exact-root.json`,
`provider-exact-replay.json` and `native-exact.json`; trial sources/recipes stay
under `.analysis/animation-state-20261019/`. The prior direct read-only Ghidra
attestation remains recorded; this continuation uses fresh hash-attested PE
and COFF evidence, with no IDA semantics or factory adapter. No cold aggregate
replay or fresh aggregate exact-byte claim.

## Auxiliary-sprite provider exact checkpoint

`AnimationAuxiliarySprite_replace @45CD70` now matches344/344 under
`cross-v106a-animation-auxiliary-sprite`. All102 instructions/344 bytes are
reachable, with eight direct calls, one RET4 and INT3 boundaries. The target
allocates108h and naturally constructs/destroys an actual CSpriteEx member at
zero. The selected composed runtime view gives frame offsets atF0/F4, scales
atF8/FC, angle100 and the independently used x/y/facing fields atE8/EC/104.

Native checked `map.find(resource_id)->second->frames[0]` must remain one full
expression. Splitting a sequence pointer ends the real iterator lifetime too
early: the body remains344 bytes but has8h versus target0Ch locals and twelve
unequal bytes. Used rectangle snapshots across texture-vector at() recover
the target argument carriers; no artificial frame storage is added. Real
std::map/std::vector preserve complete equality. Native map find also matches
the already excluded105-byte45C320; no compiler credit is added.

The existing texture-provider ABI view is now shared by declaration only;
its193/193 and261/261 accepted bodies replay exact. Youmu856/902 now call the
accepted provider through its typed owner view. Its entire5488-byte canonical
payload remains594a91c1, with no owner/execution regression. Read
[provider boundary, lifetime and exact evidence](ANIMATION_AUXILIARY_SPRITE_2026_10_19.md).
No aggregate cold replay or authored percentage is claimed.

## Current YoumuObject entry initializer

Root543670 remains source-present/nonexact over5159 bytes. The selected
851 source now captures heading340, writes state344, then loads heading[2],
following the target's actual ordering. It calls the already matched45C390
through the existing int ABI facade. Fresh int and natural-short callee
builds both reproduce202/202; neither uniquely recovers the original C++
declaration. The new auxiliary layout/provider integration is byte-neutral;
shared texture-provider declarations are replayed as described above.

Source SHA7b0dac5f, canonical5488-byte payload594a91c1, prefix5156 and strict
first mismatch+80/5436F0. All23 prior equal owner diagnostics survive,29
primary destinations remain distinct, and the frame remains10h. Conversion
sites20/21 and RETs22/23 still expose820/850's different sharing.823 register
preparation,821's pointer handoff and851's remaining pointer/call registers
are open. Exact credit is unchanged.

The new native auditor passes0/592 inputs through592 actual45C390 selector,
frame, texture and commit chains on each side, with native RETs.588 inputs
use a separate read-only parameter buffer. Four additional851 ABI stress
inputs deliberately overlap heading[2]/state344: the target selects256, while
the old source09dd36f0 selects257 and fails4/592. The corrected source passes
all four. This distinguishes load order; it does not prove factory-owned
game objects can contain that overlap. All object bytes, selector arguments,
helper traces, x87 TOP/control word and nonvolatile registers are checked.

An unselected int-facade850-only control reaches the target21 conversions/23
RETs,5160-byte prefix, all332 metadata bytes, and only30 callable-byte
differences. It still retains the wrong851 value order. Combining the two
improvements merges850's physical copy; explicit dispatch captures preserve
counts but lose five older equal owners. Shared821/848 pointer and854 joins,
physical RTTI hierarchy, active payload constness, scalar argument lifetimes,
and inline helpers do not close the complete target. These are phase-scoped
controls, not a proved LTCG impossibility. Do not select the30-byte witness
while reinstating the old851 hypothesis.

Read [current source, execution and control evidence](YOUMU_ENTRY_CALLS_2026_10_19.md).
Earlier [sequence-word evidence](YOUMU_ENTRY_SEQUENCE_WORD_2026_10_19.md) and
[caller-width controls](YOUMU_CALLER_WIDTH_CONTROLS_2026_10_19.md) describe the
predecessor source. Private recipes/receipts are below
`.analysis/youmu-entry-carriers-20261019/` and
`build/youmu-entry-carriers-20261019/` (under8MiB combined). Two successful
read-only,128MiB/CPU0 Ghidra passes independently attest the target and Youmu
RTTI descriptors; all nine primary database hashes remain unchanged. The
first missing820-disassembly attempt failed closed and is retained separately.
IDA preflight still rejects the wrong open image; no IDA semantics are used.

## Youmu Fighter caller-width follow-up

The37692-byte root530200 remains source-present/nonexact, with31/98 owner
diagnostics, prefix37648 and canonical38772-byte payloade81b3c5f. All9912
target instructions/all37692 bytes are reachable. An independent four-slot
int view reproduces the baseline; a short view for all38 source selector
expressions is completely byte-neutral. No shared interface changes.

Uniform signed-char/plain-char or full-word spawn-control arguments regress
to4/98 or3/98, with the initial constant register assignment changing at+12.
Narrow control locals and a branch-local710 call-expression rewrite do not
recover the lost owners. These controls are unselected; a smaller root-size
deficit alone is not grounds to change the source.

Fresh bounded stack calculation proves target601 passesFFFFFFFF at536E7E,
while606's AL arithmetic leaves000000FF at538086. Both become the sameFF
byte in object+33C. The66-byte forwarding helper transfers words/RET1C;
the237-byte manager factory consumes the byte in its seventh/nine-stack-slot
interface/RET24. Direct read-only Ghidra checks the physical storage and both
callable hashes without inventing byte signedness. All nine primary DB pins
remain unchanged; current saved pins remain the action980 checkpoint's file.

See [caller-width evidence and limits](YOUMU_CALLER_WIDTH_CONTROLS_2026_10_19.md).
Private source/commands are under `.analysis/youmu-state-word-20261019/` and
`build/youmu-state-word-20261019/`. Exact credit and selected source remain
unchanged. Next bounded work returns to Reimu478FA0's remaining physical
sharing and argument lifetimes; these controls do not justify a global ABI
change or a categorical LTCG stop condition.

## Current AyaObject entry initializer

Aya root61F0B0 remains two bytes from its4531-byte target body. The local
vslot+0C sequence parameter is short: it recovers all19 virtual preparations,
including eight CALL EAX sites omitted by the earlier11-site cohort. Raw
callee45C390 consumes the low word of a four-byte stack slot. A natural short
provider in `scripts/probes/animation-sequence-word-abi.cpp` is202/202 using
the existing animation-sequence unit comparator, with no duplicate credit.
The shared int facade and all accepted units elsewhere are unchanged.

Source SHA5ca0fb42/canonical4859-byte payload6f70b6f3 differs only at
61FCA7/+BF7 and61FCAF/+BFF: action856 uses EAX for the same heading-pointer
load/FLD where target uses ECX. Every other byte and all metadata agree.
Owner diagnostics31/33 and an almost-identical payload are not exact credit.
Direct800/810 angle-field writes remove the double float-copy carrier without
changing any ordinary payload byte. The new genuine `/GL /LTCG` diagnostic now
has the target10h local frame and4532 metadata start. Independent replay of
all188 relocation fields and128 HIGHLOWs proves its complete4859-byte payload
equals the ordinary candidate: the same two ModRM bytes remain. There are
no placeholder functions, fabricated callers, ABS code bindings or float/double
symbol aliases. The image is unexecuted and does not prove the original TU.
See [sequence-word ABI evidence](AYA_ENTRY_SEQUENCE_WORD_ABI_2026_10_19.md).
A fresh384MiB/CPU0 read-only Ghidra pass attests imported/file identity,
entry, mapped text and the root before decompilation; nine DB pins agree and
its alias is removed. Current receipts are under `build/aya-entry-registers/`.
Fresh856 branch joins,
expanded target reads and852 scale chains are byte-neutral; a real two-float
direction value changes the frame, and int64 conversion introduces an unbound
`_ftol2` rather than testing the target call. Earlier action856 controls also
remain unselected: double Y offset, direct argument, EHa, raw word storage,
verified-offset inheritance and the inlined repeated operation. Sequence
snapshots/extra angle rounding regress the shape. Earlier
receipts are below `build/aya-entry-action856/`; nine read-only Ghidra DB
pins remain unchanged and its alias is removed. Two-byte register context
remains unknown; no exact credit.

The final5ca0fb42 getter audit is also byte-neutral for float value, const
reference and pointer member returns at856. Preserve the selected source;
receipts are under `build/aya-entry-getter/`. Aya remains nonexact; preserve
this checkpoint while the bounded BMP investigation below is active.

## Current CBitmapData BMP loader

Authored/source-present root@419FF0 has2230 callable bytes ending exclusively
at41A8A6; RET4 starts41A8A3. Its adjacent45-byte switch metadata is separate.
Fresh raw CFG reaches666/672 decoded instructions; six alignment instructions
remain in strict comparison. Three read-only Ghidra runs leave all nine
primary DB hashes unchanged; aliases are removed. See
[BMP boundary and source-form audit](CBITMAP_BMP_2026_10_19.md).

The old2197-byte section contained only2149 callable bytes, not2197. The
old claim that only stack coloring remained was unproved. Selected source
recovers combined word-mask RGB1555 dataflow and lets VC8 unroll scalar
palette loops. It emits2133 callable +3 alignment +45 metadata =2181 bytes,
still frame438h versus target430h and strict mismatch+10h. The larger97-byte
callable deficit is not an exact-size improvement. No new exact credit.

Both old and selected source pass149 modeled target/candidate execution
cases, with equal bitmap state, allocations, pixel data and cleanup actions.
The147 stable-format cases cover633 target instructions; two allocator
format-mutation stress cases extend coverage to661. These callbacks are model
assumptions, not observed real allocator behavior. All five accepted siblings remain exact.
Private ordinary controls and a real-FileReader diagnostic LTCG link remain
nonexact; the latter lacks the package-file helper provider and cannot support
acceptance. Receipts: `build/cbitmap-bmp-20261019/`.

The [EH/allocator follow-up](CBITMAP_BMP_EH_2026_10_19.md) now checks the
one-state reader-owner cleanup chain. Relocated8-byte unwind/36-byte FuncInfo
records agree;44 bytes of cleanup/handler code differ only at three stack
offset bytes. Entry-ESP analysis fixes the palette at-40Ch in target/source;
scalar workspace is48 versus56 bytes. The palette32 stage writes five scalar
slots in target versus seven in selected source. Color-member/iterator controls
reduce frame to42Ch but change induction and remain private/nonexact.

Selected TU now includes the real `<new>` array-allocation declarations, with
four unit-member mappings changed from scalar to array-new symbols. All five
accepted siblings and the canonical BMP payload remain unchanged. The paired
LTCG source-interface control differs only in seven allocator fields and still
has438h frame; its package helper remains unresolved. Current source SHA is
109e8b2c; receipts: `build/cbitmap-bmp-eh-20261019/`. No new exact credit.
Continue indexed table-address/base lifetime recovery and truthful provider
context. Reviewing40CF40 target (213 bytes) is a concrete dependency
step; actual package-entry CALL is41BFA0. Do not assume a compiler-phase cause.

The [reader-opening dependency review](FILEREADER_OWNER_OPEN_2026_10_19.md)
now maps/selects retained40CF40 source and independently classifies its213 bytes
as authored engine code. Its84-instruction CFG/two RET4 exits close; RTTI pins
plain/package readers and15 decoded callers. The66-case instruction model
agrees on reader bytes, owner/global state and call traces, covering83 target
instructions under nonnull-or-throw allocation. Exception cases compare call
prefixes, not OS unwinding. No new exact credit.

Formal `cross-v106a-file-reader` replay keeps its three accepted members exact
and records CF40 as212/213 at+0. The installed RTM control is byte-identical
to SP1 on this source. No source/header/flag changes are selected;
constructor/force-inline/nonthrowing/EH-mode controls remain private and fail
the full target. The related BMP unit retains all five accepted members.
Receipts: `build/filereader-open-20261019/`. The package-entry dependency now
has reviewed source, as recorded below; CF40/BMP remain nonexact.

## Current package-entry opener

The [package-entry review](PACKAGE_FILE_ENTRY_2026_10_19.md) closes the356-byte,
126-instruction `open_package_file_entry @41BFA0`, maps/selects its source and
classifies its game archive policy as authored. Raw target data proves that
the20-byte record's +04 is archive index and +0C is file offset; old field
names were incorrect. A shared node header corrects these roles without
changing layout or the accepted43-byte destructor. Singleton CRC hits skip
filename comparison; collision chains use stricmp. Outputs precede opening,
open failure retains them, and seek failure is ignored.

The243-case target/source instruction model agrees, covering122/126 root
instructions and all45 search-helper instructions. Locale/Win32 I/O are
modeled and invalid-vector cases stop at the CRT entry. Ordinary source is
283 bytes with public find105 and separate vector[]68. The target search
helper41C450 instead takes ESI/EAX/stack4. Its false standard-ABI mapping is
deliberately absent, so the new probe fails closed on that unresolved call.
No exact credit is added; the helper remains separately in origin review.

Real-source GL controls recover stack alignment and vector inlining but
produce333-byte opener/private find116. A complete reader/BMP link now closes
without unresolved symbols or force flags, using the already-exact CRC source
and real zlib/CRT providers. CF40 stays at its ordinary212-byte canonical hash;
BMP becomes2152 callable +45 metadata with the same438h frame, still different
from target2230/430h. Missing source declarations alone do not explain the
remaining mismatch. All12 accepted members across the four focused reader,
BMP, node and score-lookup units replay exact. Nine Ghidra database hashes are
unchanged. Receipts: `build/package-entry-20261019/`. The real second search
caller41BCF0 now has reviewed source below; helper visibility/partition still
prevents exact acceptance. No routine cold aggregate replay was run.

## Current package-index mutation

The [registration review](PACKAGE_INDEX_UPDATE_2026_10_19.md) closes all200
instructions/628 bytes of `register_package_file_entry @41BCF0`, called from
the archive loader41BA70 at41BC9D. Missing keys insert three temporary owners;
matching filenames update three scalars; hash collisions append an owned node.
Four EH states independently pin those three lifetimes and allocation rollback.
VC8 make_pair-by-value destroys a node too early, so selected source uses an
explicit pair expression. Node construction/copy bodies now accompany the
root and accepted destructor in `PackageFileIndexRuntime.cpp`.

Construction proves the path uses array new665B8A and strcpy_s, while exact
destruction uses CRT free. The old allocation inference in RE_WORKFLOW was
wrong and is corrected. Copying duplicates the path and copies the next
pointer; registration only copies fresh null-tail nodes. Physical layout is
unchanged. The67-case instruction model agrees, including six allocation
exception-boundary controls with matching root EH states and one null-allocation
case; coverage is181/200 root instructions. Insert/ASCII CRT/allocation behavior
is modeled, without OS unwinding or full tree-insertion execution.

Ordinary selected source559 remains nonexact. Internal-linkage types are
byte-neutral in the initial ordinary control. Real-source GL O2 controls are
703/707 bytes; an inline-copy/Ob1 control is630 bytes but still has four RETs
and different private helpers. None is selected. Standard find/constructor/
insert/pair-cleanup ABI mappings are deliberately absent; handler cookie-frame
offsets also differ by4. Node destructor43/43 is freshly replayed with this
unit's GS enabled; the related opener's243-case model passes on its fresh
object after the shared header change. Nine primary Ghidra hashes agree.
Receipts: `build/package-index-update-20261019/`. No exact credit is added.

The two old nonexact allocation interfaces at418D10 and415340 are now
corrected below. Recover archive-loader41BA70/input/global visibility before
revisiting reader/BMP code generation. Keep the private helper boundaries
unresolved until a complete honest caller/callee context reproduces them.

## Current allocation-interface correction

[Audio/network allocation evidence](ALLOCATOR_INTERFACES_2026_10_19.md) confirms
both418DD1 and4153FD call665B8A, the array-allocation forwarding entry. Source
now uses `new unsigned char[size]` with the real `<new>` declarations and
`??_U` bindings; observed CRT free calls remain. This repairs the old malloc
interface without adding failure handling. Both ordinary roots stay463/484
and524/542. All eight configured comparison payloads across the two affected
units are byte-identical to the fresh pre-edit controls; accepted callback
41D7B0 remains14/14 exact. The148/33 dependency controls remain in origin review.

A fresh real-source mixed network link has no unresolved implementations.
Its542-byte connection still has84 diagnostic differences, first+14C; native
EH/GS/worker-pointer hypotheses remain unaccepted. SFL's same-TU visibility
controls naturally reproduce its ECX path/stack-source/RET4 entry with an
ordinary static stdcall definition, without a custom ABI facade. Visible
reader destruction yields470 bytes; strict/fenv controls492, owner-body
visibility475/497. All retain frame110h versus target118h. None is selected,
and the original FP mode is unknown. These partial COFF contexts retain the
caller's unresolved `open_reader` alias; they are not complete Ogg links.

Nine Ghidra primary DB hashes remain unchanged. Receipts are under
`build/allocator-interface-20261019/` and `build/allocator-interface-network.*`.
No exact credit or cold aggregate replay is added. Before a genuine Ogg link,
replace its retained `open_reader` declaration-only alias with the independently
reviewed FileReaderOwner operation on the observed receiver prefix; do not
invent a source provider or a private register convention.

The seven remaining aliases have now been reviewed in the checkpoint below:
six are array expressions needing their proper declarations, while the gauge
function actually calls the scalar entry689DCB.

## Current exact fighter gauge binding

`BattleInfoRecordF8_bind_fighter @46FA90` is now canonical648/648 in
`gpt-web-battle-info-gauge-runtime`; the same object keeps both existing value
virtuals20/20 and27/27. This adds one exact authored function /648 bytes.
The [ownership/layout evidence](BATTLE_INFO_GAUGE_BINDING_2026_10_19.md) closes
all186 instructions through RET4 at46FD15, with complete body/payload SHA256
`e44f2c92e653701f1356ce5eb1cdb9a524d60e42e4cd381965b50bda800f985d`.

Old source used the wrong release family/order, read four bytes where target
consumes a signed word, and retained earlier field pointers across stages.
Correct scalar new/delete targets, release-before-allocation, real pointer/span
lifetimes, double/float endpoint stages and the observed UI binding receiver
at object+18 with its gauge slot+A0 recover the whole target. A flat view first
gave647 bytes; the supported receiver view gives648 without padding or a custom
ABI. Original UI subobject class identity remains unknown. All23 relocation
fields, including ten allocator/deallocator calls, five vptr stores and eight
literal references, replay completely. The local Fighter view changes no shared
layout. Nine Ghidra primary file hashes stay unchanged.

The other six loader probes now include real array-new declarations. Their
complete ordinary payloads are unchanged and remain nonexact: plain224/234,
encoded275/267, palette1007/1047 and247/243, wave250/247 and439/459. No runtime
or exclusion credit is added. Receipts: `build/array-declarations-20261019/`.
Only affected focused units are replayed; no cold aggregate claim is made.
The archive-loader input/global review is now below; private helper, EH and
translation-unit boundaries remain before reader/BMP code generation.

## Current package archive loader

`load_package_archive_impl @41BA70` is mapped/source-present, authored, and
still nonexact. The [loader review](PACKAGE_ARCHIVE_LOADER_2026_10_19.md) closes
629 bytes/204 reachable instructions, including the40CF30 stack-to-ECX wrapper,
archive-name/count publication, unchecked2/4-byte header reads, array ownership,
two-pass MT19937/rolling-byte decoding and packed offset/size/name registration.
Source uses a normal static typed helper and its real wrapper; VC8 naturally
emits the private ECX entry. Original path-buffer declaration remains unknown.

The store41BBB0 proves702914 is an unsigned32-bit archive count. Shared reader
source/header and relocation identity first used an unsigned count alias rather
than an unsupported pointer alias. All15 affected units were rebuilt serially;
all33 comparison outcomes are unchanged, including21 accepted exact functions.
Vector first/last addends4/8 are pinned and its two consuming units rechecked.
The MT seed/next functions are independently replayed in the focused batch.

The100-case actual target/selected-source instruction model agrees, with202/204
reachable target instructions covered; the omitted pair is the impossible
nil-vector arm after successful append. Four exception-call-boundary controls
compare live root EH states and call prefixes. Win32/STL/registration are
modeled; malformed/short-read inputs and OS unwinding remain outside the proof.
Ordinary source598/frame138h remains selected and fails closed on the ECX
vector call. Fresh current-source controls recover the target's full162-byte
ESI push_back when real native allocator<string>::destroy retains its stack
argument/RET4. That42-byte allocator was already compiler-excluded by the
CFileList/deque<string> native anchor; an unclassified function status was not
unknown origin. Only vector162 is newly excluded; fill170 remains in review.
Its target EH landing41D563 is required to see the allocator parameter use:
ordinary reach51 instructions expands to all66 through the observed FuncInfo.

Sixteen successful source-partition/normal-ABI controls retain a627/628-byte
aligned loader/frame148h, or differ further with native registration/MT. The
native owner produces the full helper; a minimal explicit instantiation of the
same real VC8 header method preserves it while keeping the owner in CIL.
`src/library/StdStringAllocator.cpp` has a dedicated formal42/42 compiler-only
unit and supplies native support to the existing linked lifetime unit; its
163/228 accepted bodies and complete EH replay remain exact. No authored exact
increment, padding, buffer resizing or false ordinary-probe binding is added.

Two minimal-library actual graphs each pass9 full scenarios/31 archive API
calls/194 registration entries, including8/12-archive fast-vector paths, native
containers, CRC/MT and complete destruction with no live allocations. The
native-owner pair also passes. Win32/allocator/ASCII stricmp are modeled; OS
unwind, full CRT startup, failures, concurrency and malformed input remain
outside this proof. Detailed controls and current pins:
[loader context review](PACKAGE_ARCHIVE_LOADER_CONTEXT_2026_10_19.md),
`build/archive-loader-shape-20261019/`.

The four function bodies, physical parameter storage/purges, explicit AL return
and real Win32 import prototypes now persist in the verified primary Ghidra
project. Earlier archive readbacks had only existed in temporary read-only
views. Decompilation remains a hypothesis with incomplete deeper callee/EH
models. Continue the whole629-byte caller's count-join/register/frame and source
partition constraints. Original path-buffer capacity and game-method ownership
remain unknown; the selected256-byte buffer is unchanged.

## Current physical archive store

The [store review](PACKAGE_ARCHIVE_STORE_2026_10_19.md) recovers the global
7028DC..702917: CCriticalSection at0, native names vector1C, native entry map2C,
count38. Separate source globals are replaced by one PackageArchiveStore with
real construction/destruction; original class name/inheritance and game-method
member ownership remain unknown. Loader, registration, opener and reader now
use its fields. The constructor41B8C0/163 and destructor41B980/228 are mapped,
source-present and authored, now formally exact163/163 and228/228. Actual startup6BE7B0 and
atexit6BEE60 callbacks establish the global lifecycle; destructor explicitly
clears names/map/count before automatic member destruction.

At the physical-owner source checkpoint, all17 affected units/36 outcomes
were unchanged, including22 accepted exact functions. Current-source loader100 cases pass again. Seven actual
whole-graph scenarios execute initialization, containers, CRC/MT,170 entry
registrations over11 archive API calls, and final destruction; target/source
allocation sequences agree and no owned allocation survives. Win32/allocator/
ASCII stricmp are modeled; full CRT startup, OS unwind, failures, concurrency
and malformed/short-read inputs remain outside this proof.

Adding the actual count consumer leaves loader627/frame148h. Native MT restores
seed61 but leaves that loader shape; native registration next gives595/frame138h.
Physical-owner ordinary internal source gives139/264 lifecycle functions and
is not selected. The fresh CIL graph using all selected real providers instead
has163/228 lifecycle bodies and complete private zero-difference replay of
both bodies, five cleanups, two handlers, FuncInfo and unwind tables.

The formal linked unit now uses real pinned static DLL CRT libraries and a
small actual Store/Node/Critical CIL aggregate, now with the real native
allocator header-method support. The strict lifecycle contract
attests native60-byte zero BSS ownership, real CRT initializer-table retention,
complete17/5-byte initializer/atexit helpers, unexported private entries, native
cookie/vtable identity and all associated cleanup EH code/data. Every supported
pointer field has exact HIGHLOW coverage; all other bytes remain compared.
Public cold build/comparison reports163/163 and228/228 exact: **391 authored
bytes added**, with no compiler startup/EH credit. Quoted .cpp dependencies and
native layout artifacts are now part of provenance.

The omitted vector<string> destructor41C200 is bounded57 bytes through RET at
41C238, followed by7 CC alignment bytes. Independent native VC8 symbol/body,
its real unwind callers and complete57-byte replay establish compiler template
ownership; it is a new candidate/exclusion, never authored exact credit.
All three existing accepted linked units (408870/281,413820/98,405200/167) and
Node41B850/43 remain exact after cold affected replays. All40 linked contract
tests pass under both supported Capstone versions. Receipts:
`build/archive-linked-contract/*-formal.json`; detailed contract and limits in
[the store review](PACKAGE_ARCHIVE_STORE_2026_10_19.md).

The lifetime exact-acceptance work used hash-attested PE comparison and the
prior read-only Ghidra evidence. The newer loader ABI checkpoint above persists
related metadata in the primary; use its current pins. Original class name/inheritance, TU partition and game-method
ownership remain unknown. Next continue loader629 private helper/EH/frame
context and reader/BMP/registration/opener residuals; these remain nonexact.

## Current Reimu CPU root

A second large Reimu root is now identified: `Reimu_update_cpu_action_policy`
@48D390, vslot+58. Callable `[48D390,49120F)` is15999 bytes, SHA256
`3bd363994e140603ae0ec249ffd3a36b1ae0448e72a389e417c4cc7a6d113e2d`.
All4126 instructions are reachable;157 calls target five helpers, four switch
tables close and52 RETs have balanced stacks. The callable ends before its NOP
and metadata. `giant-action-switches.toml` now pins19 action and21 policy
primary destinations plus two checked-front-record tables. Its full C++
candidate is now source-present in `src/characters/ReimuCpuActionPolicy.cpp`,
with probe unit `gpt-web-reimu-cpu-action-policy` and no exact credit. See
[CPU root evidence](REIMU_CPU_ROOT_2026_10_19.md).

Real target-to-target policy0 execution passes0/16000 finite cases, visiting
all1488 Reimu and1486 default policy0 instructions and confirming actual rolls
0..99. This supports shared selection logic, not whole-root equivalence.
An ABI-adapted default-source reference is canonical-byte-identical to the
fresh default object at the same replay address, but differs from Reimu on
1065/5000 complete-return cases. Its command728 and conditional-RNG differences
preclude selecting a blind source copy. The default comparator retains its
known+12E/5F20AE nonexact result.

The manual Reimu tree preserves actual helper execution and the corrected90
lower bound/180 equality. Its initial snapshot-source checkpoint is recorded
in [complete source evidence](REIMU_CPU_SOURCE_2026_10_19.md).
The action-counter checkpoint removes its scalar snapshot and reads the
signed764 field directly. This recovers separate signed bounds: decoded
entry-to-common word JA/JBE branches change52->0 (target0), while JL/JG
change38/2->92/55 (target97/56). These physical-interval counts are diagnostics,
not correctness scores. That candidate prefix/payload is15860/16401; strict
comparison first differs at+97/48D427 where a flag-preserving constant1 LEA is
hoisted ahead of JLE. The earlier+12E/302-byte-prefix result is historical.
See [counter-read evidence](REIMU_CPU_COUNTER_READS_2026_10_19.md) for those
controls. Direct read-only Ghidra analysis leaves
all nine primary DB pins unchanged; no IDA semantics were used.

The preceding source checkpoint cached policy0's full int selector result and
used explicit signed-word consumption. It reproduced target MOV ECX,EAX;
ordinal/encoding comparison of the whole candidate finds only this functional
instruction changed (plus genuine post-RET alignment). All47 metadata code
pointers preserve destinations. That source SHA256 is
`556098b785ef77ed7b8a49b55fa4c72cd4cf6e60f29dfc7dd88fca12baa3754a`,
canonical16401-byte payload
`70905d5a0663e6c41cbdc5dfd94a9ee56b8ed3a197011432c5270e87b2990ae4`.
Prefix/first mismatch remain15860/+97. See
[policy0/x87 evidence](REIMU_CPU_POLICY0_X87_2026_10_19.md).

That cache source has117 selector sites versus target121 and50 RETs versus52.
Policy0 CFG closure localizes all four missing selector copies: target37
sites/1488 instructions, candidate33/1359. Target76A has only stores and ECX
carries the result; this did not establish an original C++ local declaration.
The direct-field evidence below supersedes the earlier cache-only inference.
Counter reset/RNG preparation already matched; changing neutral store order
also causes undesired partial neutral/facing sharing and remains unselected.
The CPU probe now sets FPSW0/FPTAGFFFF explicitly and checks both TOP and tags
at the stop. Old reports did not attest empty tags and remain historical.
Fresh empty-entry replays pass0/21528 for Reimu, and0/21528 each for default/Aya
after this shared fixture correction. Reimu selection confirms real rolls0..100
and all1488 target instructions. All46420 observed selector entries/returns
per side are empty/TOP0; policy/timer writes show residual scheduling
differences outside those calls. A source-visible actual selector under/Ob1
remains27/27 and leaves the caller completely unchanged. No new exact credit
or aggregate cold replay is claimed.

Preceding terminal observations on the70905d5a payload pass0/16160
selection cases with both terminal and x87 collection. They visit all1488
target policy0 instructions and pair66 CALL/publication/RET records, with
50 target/49 source observed RETs. Caller correspondences have five
non-bijective components: both wrong merges and extra copies contribute to
the net four-selector deficit. Source4904B7/4904C3/4904CF alone serves six
target CALL/timer/RET paths, including bounds15/20/30 and policies9/10/11/12.
The opt-in `--selection-terminals` mode preserves genuine execution and rejects
unreviewed root RETs. An inline two-write operation is byte-identical;
expanded terminals and three cumulative range-gate controls remain unselected,
even where the entry's first302 bytes agree. Selected source and exact ledgers
were unchanged. See [terminal sharing](REIMU_CPU_TERMINAL_SHARING_2026_10_19.md).

The preceding field checkpoint reads signed76A directly. Ordinary VC8 eliminates all
reloads and retains MOV ECX,EAX while removing all44 non-target unsigned range
branches from reachable policy0. Twenty-one manual range gates are natural
field predicates; typed766/768 accesses and macro cleanup are independently
payload-identical. That source SHA256 is
`77234302d395e30a71dbded324b0696e142c0f53ff56cb0c2a34d590a03d7864`,
canonical16457-byte payload
`d3b9a02340e6c4611a46007991b816c5675310b7e1d2cd28221f9a08f2d6ed54`.
Prefix15916, first strict mismatch+12E/48D4BE is the JLE48D4BC displacement.
Root selectors/RETs are118/48 versus target121/52. Policy0 has1385 instructions,
34 selectors and46 RETs; target1488/37/50. All18 previously correct sampled
one-to-one CALL components remain correct; RET/publication memberships have
both gains and losses, not uniform improvement. Selected-shape selection
passes0/16160 with all1488 target instructions, real rolls0..100 and unchanged
empty selector x87 entries/returns. Fresh selected-object general/action-edge/
height suites pass0/51082, for0/67242 on selected canonical code overall.
Nine read-only Ghidra DB pins remain
unchanged. No exact credit is added. See
[signed selection field](REIMU_CPU_ROLL_FIELD_2026_10_19.md).

The preceding source also fixed two ordered wall predicates: negating
`x<240`/`x>1040` explicitly preserves unordered X behavior, while substituting
>=/<= did not. Actual-helper counterexamples select policy11/bound30 instead
of target policy0/bound60, or policy9/bound30 instead of policy0/bound10.
The new `--x-position-cases` matrix passes0/20200 with two independently
target-confirmed policy/timer/RNG controls. Prior finite-X/height suites did
not prove this case. Only eight TEST/Jcc instructions change among all4008
functional instruction ordinals; all other encodings/edges and47 metadata
pointer destinations remain identical after address replay. Source SHA256 is
`7102660c044b225578aeb52fb5379ef20925ed813f34e7ab6815e760384f01eb`,
canonical16461-byte payload
`4a4cb565b9c023fb82e6f4fbb01e63df711d3b3f59ce15fef1c1f9c52b581792`.
Prefix15920; strict+12E/48D4BE and selectors/RETs118/48 remain nonexact.
Fresh selection/general/height runs pass0/21528, for0/41728 including the new
exceptional-X matrix. All49 finite selector and63 coupled terminal records,
including publication/x87 observations, agree with the preceding source after
instruction-ordinal address replay. The primary instruction stream is unchanged
apart from eight local table addresses moving by4. Generated input arrays
totaling about12MB are removed; the public generator and trace recipes remain.
See [unordered wall evidence](REIMU_CPU_NAN_WALLS_2026_10_19.md).

Latest source completes the remaining two negative wall guards, separately
target-traced at48FE5A/48FE76 and490842/49085E (all TEST AH,5). Four guards
now preserve C0/C2 behavior. Only eight further TEST/Jcc instructions change;
all4008 functional positions/edges and47 metadata pointer destinations agree
after address replay, and the entire pre-policy0 code prefix is byte-identical.
Two longer TESTs consume prior compiler post-RET alignment. Source SHA256 is
`1d121503b98277c808727f58af725f13642dfe5ab78ee91bb03aa32b283876d5`,
canonical16461-byte payload
`07cb7a406e5c136ccd25e97287419f58e7b8b7eaccd502af81e0cb811fbac091`.
Prefix15920, strict+12E/48D4BE and selectors/RETs118/48 remain nonexact.
Fresh0/41728 selected cases preserve all49 finite selector and63 coupled
terminal records, including x87/publication observations. No exact credit.

On pre-checkpoint source7102660c, pinned RTM/SP1 and native-container COFF
controls are fully byte-identical. A genuine closed /GL link with exact SDK
deque94/94, three exact engine units and actual static CRT retains the wrong
aligned EBP frame. Narrowing only five exact-float copy aliases removes that
frame; full four-switch CFG and334-field replay prove its genuine/ordinary
16429-byte equality at ec562ac4, still nonexact to target. Controls are not
selected and linked images are not executed. This does not exclude other
original source/TU/LTCG contexts. See
[compiler phase and remaining wall evidence](REIMU_CPU_PHASE_2026_10_19.md).

The next checkpoint keeps that source/payload unchanged and adds a native
exceptional-height matrix with four target-confirmed qNaN/sNaN policy/timer
witnesses. Fresh0/20200 vectors preserve complete actor/RNG/helper results.
An ordinary inline input helper leaves the entire payload unchanged. Four
independent height cases and narrower independent peer cases overrun491450;
fenv_access(on) changes the12-byte frame to16 and also overruns. None is
executed or selected. Target EBP=2/EDI=400 lifetimes and its two peer-height
comparisons are recorded separately from source hypotheses in
[height and lifetime controls](REIMU_CPU_HEIGHT_CONTROLS_2026_10_19.md).
Replacing43 raw output-word accesses with existing32-bit typed members also
leaves the complete payload unchanged. Mixed output access spelling is not
the demonstrated cause of the remaining allocation/sharing differences.
`build/reimu-cpu-fields/` retains that fresh baseline/control and independent
read-only Ghidra attestation; nine DB hashes agree and its alias is removed.

## Next reconstruction work

The active bounded scope is YoumuObject's5159-byte initializer at543670.
Preserve the verified short interface, target902 order and29 distinct action
destinations/two switches. Recover real820/850 pointer/vptr lifetime and
conversion/return membership;851 must load its value after the state write
without merging into854. Read YOUMU_ENTRY_SEQUENCE_WORD_2026_10_19.md and
its earlier evidence before repeating controls. Do not transfer a prototype
to another root solely from an equal slot number.

Aya61F0B0 remains open at two bytes. Preserve its19 recovered preparations
and complete metadata. Read AYA_ENTRY_SEQUENCE_WORD_ABI_2026_10_19.md before
new controls; do not repeat its unchanged source/profile/helper probes.
Its old11-site scheduling diagnosis is superseded by the observed low-word
consumption and coupled caller/provider compiler evidence.

The Reimu CPU root remains open: use the complete candidate, coupled
terminal witnesses and original-helper execution to recover CALL/publication/RET sharing and genuine
constant/TU/register lifetimes. Keep direct signed764/76A reads and the observed
ECX forwarding. Absence of a machine reload does not prove an original local
cache. Do not repeat a missing live value at selector entry explanation without
new evidence. Preserve the corrected180 equality/RNG order. Do not count finite execution or
diagnostic branch counts as exact progress.
Preserve all four ordered wall negations and exceptional-X positive controls;
do not replace floating-point complements with opposite ordered relations.
Do not repeat the unchanged RTM/native-container/five-float-alias controls;
the latter restores an entry frame but not complete target sharing.
Do not repeat the unchanged input-helper/independent-height/fenv controls;
their negative results do not establish a unique original source spelling.
The43-write typed-output control is likewise completely byte-neutral.
The81KB action root remains an open priority with the constraints below.

1. Resolve action9's coupled landing/advance membership with new compiler/TU
   or source evidence. Explicit shared exits still split the correct
   0/2/9/71/72/74/145 advance group. The newest listed/plain, conditional x87
   and actual-entry proof excludes a missing cleanup on the exercised paths;
   repeating goto, branch inversion or constant-parameter controls is not useful.
2. Preserve the now-recovered 197/658 and 198/608 memberships. Their incoming
   ECX scheduling still differs. Resolve distinct 300/320 prefixes and the
   effect/landing/action-gate partitions.
3. Preserve recovered 465190 owned-object and 45C030 wave partitions and the
   202/203/225/226 common landing. Indirect counts remain target 220/source 219;
   only 410/416 have per-action deficits. Slot identities remain provisional.

The six differing direct partitions remain 4351C0, 435240, 435D60, 45AF40,
473DD0 and 478EE0; height/clear membership differences now concern low9 alone.
Total call counts alone can conceal incorrect memberships.
Read [coupled exit constraints](REIMU_LANDING_EXIT_CONSTRAINTS_2026_10_18.md)
and [shared action10 landing](REIMU_SHARED_ACTION10_LANDING_2026_10_18.md)
before repeating goto, switch, helper-visibility or reset controls. Earlier
/Os, /fp:fast and RTM probes emitted no FIMULs on the pre-conversion source.
The newest converted-source RTM control retains all seven FIMULs, but leaves
the same bad advance sharing as SP1. None is selected. Do not repeat unchanged
negative probes without new evidence.
Original source/TU visibility, remaining FP scheduling and whole-root equality
remain unknown. Other roots and prior accepted units are indexed in
[the archived handoff](RE_HANDOFF_HISTORY_2026_10_18.md).

## Artifacts, reproduction and final gate

`build/reimu-cpu-root/` retains the newest complete boundary packet, target
mapper output,16000-case bridge,5000-case rejected reference and metadata
readback receipts. The private Ghidra hypothesis is under
`.analysis/reimu-cpu-root-20261019/`; its copied working project is removed.
`build/reimu-cpu-source/` retains the full-source strict/native reports,
regression controls and unchanged primary DB pins. Its newer typed hypothesis
is under `.analysis/reimu-cpu-source-20261019/`; no copied project is retained.
`build/reimu-cpu-shape/` retains current field-read builds/native reports,
counter/selector CFG profiles and rejected controls. Its read-only typed
hypothesis is under `.analysis/reimu-cpu-shape-20261019/`; alias removed.
`build/reimu-cpu-policy0/` retains current full-width cache, normalized CFG,
selector/publication x87 observations, fresh three-root empty-tag replays and
the rejected helper-visibility control. Its384MiB read-only Ghidra recipe is
under `.analysis/reimu-cpu-policy0-20261019/`; no alias/project copy retained.
`build/reimu-cpu-setters/` retains the current coupled terminal/x87 witnesses,
closed policy0 CFG profiles and five rejected ordinary-C++ controls. Its
read-only Ghidra recipe is under `.analysis/reimu-cpu-setters-20261019/`;
nine DB pins remain unchanged and the project alias is removed.
`build/reimu-cpu-roll-field/` retains the selected field/natural-range source,
closed CFG profiles, fresh focused Reimu execution and rejected controls. Its
read-only recipe is under `.analysis/reimu-cpu-roll-field-20261019/`; all nine
DB pins remain unchanged and no alias/project copy is retained.
`build/reimu-cpu-geometry/` retains current ordered-wall source/normalization,
real exceptional-X counterexamples and target traces, related replays and
unselected peer/distance controls. Its read-only Ghidra recipe is under
`.analysis/reimu-cpu-geometry-20261019/`; all nine DB pins are unchanged and
the project alias is removed.
`build/reimu-cpu-phase/` retains latest selected replay/normalization, four
target wall traces, pinned RTM/native-container controls and qualified genuine
float-alias link recipes. Its read-only Ghidra recipe is under
`.analysis/reimu-cpu-phase-20261019/`; nine DB hashes remain unchanged and
the project alias is removed. The private linked images are not selected.
`build/reimu-cpu-controls/` retains the unchanged baseline, four rejected
input/height/environment controls, closed policy0 profiles and exceptional-Y
native witnesses. Its read-only Ghidra recipe is under
`.analysis/reimu-cpu-controls-20261019/`; nine DB pins remain unchanged and
the project alias is removed. Generated bulk input arrays are removed.
`build/aya-entry-context/` retains fresh caller/probe comparisons, the complete
4859-byte/two-difference packet, RTTI, unselected controls and genuine source/
CRT links. Its bounded read-only Ghidra recipe is under
`.analysis/aya-entry-context-20261019/`; all nine DB pins agree and the alias
is removed. Linked images are diagnostic and unexecuted.
`build/youmu-entry-word/` retains fresh target/vtable/selected source packets,
the23/30 owner diagnostic, real short-callee witness and rejected851 merge.
Its bounded read-only Ghidra recipe is under
`.analysis/youmu-entry-word-20261019/`; nine DB hashes agree and its alias is
removed. No new native or linked-image execution is claimed.
`build/reimu-ltcg/` retains the current 164-file genuine provider/cache set.
`build/reimu-next-sequence-20261019/` retains current602/600-family qualification,
selected native/bool-stage/negative receipts and the pinned8751b928 baseline.
Its `.analysis/reimu-next-sequence-20261019/` recipes cover all source controls,
raw guard/preparation comparisons and three direct read-only Ghidra checks;
all nine primary hashes remain unchanged. Keep the baseline and genuine cache;
regenerable unselected source/object copies are disposable.
`build/reimu-300320-slots-20261019/` retains the c9107448 compiler/source/header
baseline, fresh ordinary checks, full ESP/slot and mode-loop facts, three-action
native receipts, rejected-control summary and read-only DB pins. Private
regeneration recipes are below the corresponding `.analysis/` directory; keep
the frozen baseline and current genuine cache.
`build/reimu-300320-lifetimes-20261019/` retains preceding selected sharing,
relocation, preservation, native/negative, effect and bool-stage receipts.
Its `.analysis/reimu-300320-lifetimes-20261019/` recipes include two read-only
Ghidra checks; all nine primary DB hashes remain unchanged. Keep its pinned
46f97f0a baseline source/header for historical controls and the current genuine
cache. Regenerable unselected copies and native binary/snapshot bulk are cleaned.
`build/reimu-root-branches-20261019/` retains the selected414 sharing/relocation,
linked correspondence references, native/negative/effect and bool-stage receipts.
Its private recipes are under `.analysis/reimu-root-branches-20261019/`; the
read-only Ghidra audit preserves all nine primary hashes. Unselected object
copies and regenerable native binary/snapshot bulk are cleaned after checking;
keep the current genuine cache and selected ordinary object.
`build/reimu-low9-x87/` retains the newest cloning, listed/plain, RTM, full-CFG
and native-entry recipes/reports. Controls are unselected and disposable.
`build/reimu-sequence-landings/` retains the previous baseline/control recipes,
complete partition census, affected native adapter and qualification receipts.
`build/reimu-x87-state/` retains earlier focused receipts, native/static evidence,
private adapters and resource/cleanup records. Older generated report paths
may have been cleaned; regenerate them from the retained recipes and dated
notes. Never treat an old ignored report as a current comparison. Preserve
`resources/`, compiler installs and the primary Ghidra project.

The source checkpoint's genuine producer is:

```bash
nice -n 10 taskset -c 0 python3 -B scripts/probe-reimu-action-ltcg.py
```

It qualifies ordinary/linked correspondence and affected provider comparisons;
it does not accept the root. See the focused note for smaller sharing,
request-buffer and native commands. The current producer peaks about 313 MiB;
static/native qualification peaks about 291/151 MiB, serially on CPU0.

Before **every commit, push or pull request**, run in the finished worktree:

```bash
python3 scripts/ci.py
git diff --check
```

A local CI pass is mandatory; GitHub Actions does not substitute. Any later
source, ledger, script, test or generated-progress edit requires the gate again.
Remove disposable CI bytecode afterward. Commit stable work with
`gpt-6.1-sol: ...`, push, then verify the remote branch equals local HEAD and
check the worktree is clean. Do not commit executables, data, analysis
projects, generated reports, toolchains or credentials.
