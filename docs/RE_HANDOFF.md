# TH10.5 reconstruction handoff

This is the short operational handoff as of 2026-10-18. The live ledgers and
fresh canonical comparisons override dated prose. Older checkpoints are in
[the October archive](RE_HANDOFF_HISTORY_2026_10_02.md),
[the September archive](RE_HANDOFF_HISTORY_2026_09_26.md), and the focused
evidence notes linked below. Their former "current" and "next" instructions
are historical.

## Target and live state

- Target: original Japanese TH10.5 v1.06a, SHA-256
  `56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
  Never substitute 1.06 or a localized executable.
- Last checked ledger census: **4,023 provisional candidates**, with
  **1,542 authored / 1,415 excluded / 1,066 in review**; **1,455 mapped**,
  **1,436 source-present**, **1,333 exact / 225,099 exact bytes**, and
  **516 match units**. These are ledger/status totals, not a fresh aggregate
  cold replay. Recompute before quoting them.
- `config/claims.csv` remains header-only. `implemented.csv` means source
  present, and only `matches.csv` plus a reproducible canonical 100% unit
  supports exact credit. Candidate size and disassembler analysis do not prove
  function ownership or a compiler boundary.
- The local target passed `scripts/verify-target.py`. The attached IDA MCP
  still reported SHA-256 beginning `10350095` at this handoff, so its data
  cannot be used. Hash-attested raw PE analysis remains available. Existing
  direct Ghidra working databases under `.analysis/` were independently
  checked for target identity, entry and mapped `.text`; re-attest each
  database before a new bounded analysis unit. Do not use the factory adapter.

Run the preflight in [AGENTS.md](../AGENTS.md) before changing reconstruction
state. The source tree predates the corrected target; retained source is a
hypothesis until 1.06a instruction, ABI and comparison evidence support it.

## Active priority: Reimu action root

Current boss is `Reimu_dispatch_action_state_vslot28 @478FA0`, the largest
unimplemented authored candidate. Its81550-byte callable ends48CE2E, SHA256
dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6.
The11-switch CFG reaches20243 instructions/81488 bytes; the remaining62
bytes are nine proved loop-alignment gaps, retained in strict comparison.
There are1188 decoded E8s to32 targets and153 RETs. See
[the full entry/boundary record](REIMU_ACTION_ENTRY_2026_10_17.md).

`ReimuActionStatePrelude.cpp` stages the typed entry phase. It preserves
independent effect-action reads, signed facing versus unsigned direction,
WORD count wrap, and continued count/decrement processing after timer clear.
Native0/10584 covers actor bytes, exit categories and first callback arguments;
two wrong-source controls each fail1/9 smoke cases. The oracle stops before
callbacks or action dispatch. This helper is not an original boundary or the
target root. Root status/source selection remain unclassified/declaration-only;
no implementation/exact credit or shared compiler-profile change was made.

Direct Ghidra attests the full root and bounded method view, all11 dispatches,
entry stores and fallback/RET. All9 primary database files unchanged; clone
removed. Low0..10 are now staged in `ReimuActionStateLow.cpp`, using the
shared `ReimuActionStateStaging.hpp` prefix. Fresh native0/10700 executes
real landing, frame/block transitions, action setters and Reimu/CharacterEx
finalizers through genuine RET. Three source negatives detect1/88,1/88,3/88.
Case0's zero-velocity flag clear does not apply to2; capture selected action
across callbacks; use signed sequence>0 and full DWORD+6B8. Header extraction
keeps all530 entry text bytes/relocation identities; fresh0/10584 entry replay
passes. All3 launch sites occur20 times. Read-only graph and zero texture/
event-handle context limit this proof; no whole-root exact claim. See
[low-action evidence](REIMU_LOW_ACTIONS_2026_10_17.md).

Actions71..78 are now staged in `ReimuActionStateRecovery.cpp`:2619 physical
bytes/677 instructions plus shared tails. Fresh native0/4595 has4106 genuine
RET cases,414 stops at real effect wrapper435240 and75 at real owned-object
wrapper465190; all request arguments are compared without fabricated results.
Callback-returning requests, including the remaining landing layout/scratch
suffix, remain unproved. Preserve71's conditional second gravity subtraction,
73's signed WORD decrement wrap, two separate boundary calls, byte-facing
negation and event/spawn ordering. Two compiled negatives fail11/64 and84/4595.
The shared staging prefix adds offset-proved fields/vslots; affected entry and
0..10 rebuilds pass0/10584 and0/10700. Accepted units are unaffected. Direct
Ghidra independently attests the eight starts/shared exits; primary database
hashes unchanged and clone removed. See
[recovery-action evidence](REIMU_RECOVERY_ACTIONS_2026_10_17.md). Next recover
remaining Reimu families toward a complete root, and supply real effect/object
contexts before claiming their returning continuations.

Actions88/89/145 and197..204 are staged in `ReimuActionStateMovementAttack.cpp`:
4248 physical bytes/1111 instructions, plus shared exits. Fresh native0/4445
includes3881 RET cases and564 actual wrapper-entry request comparisons. Real
MT seeding/draws and2496 state bytes/index are checked; input/facing/completion/
frame-transition/random cohorts require their actual target branches. Corrected
fixtures keep200 on the surface and use single-sequence data for completion;
initial disconnected/non-advancing contexts are discarded. Two compiled
negatives each fail1/99. Shared prefix adds offset-proved peer/float/WORD/input
fields; entry/low/recovery rebuild/replay passes0/10584,0/10700,0/4595. No accepted
unit or exact credit changes. Ghidra attests all11 starts/two shared tails;
primary hashes unchanged and clone deleted. See
[movement/attack evidence](REIMU_MOVEMENT_ATTACK_ACTIONS_2026_10_17.md).
The remaining low208..226 plus direct300 are now staged in
`ReimuActionStateLateLow.cpp`:6652 physical bytes/1764 instructions. Direct300
starts47CBBD;226 ends there, while mid selection starts47CC5F. The mapper's
731-byte provisional226 span also contains162 direct300 bytes and47 selector
bytes; do not treat it as226 ownership. Native0/3414 has3294 genuine RET cases
and120 real435240 request-entry stops.214's flight steering uses target-run
orientation initialization, real sine/cosine/fabs/control-word helpers and
resource consumption; no callback result hooks. Negatives detect1/150 for
224's wrongly cleared AY and24/432 for214's180-degree equality boundary.
All four prior stages rebuild with identical text/non-debug data/relocation
identities; current smokes pass0/9,0/88,0/64,0/99, without full old replay.
No accepted unit or exact credit changes. Ghidra attests root/entries/shared
tails; primary hashes unchanged and clone deleted. See
[late-low evidence](REIMU_LATE_LOW_ACTIONS_2026_10_17.md).
All44 concrete low-table bodies plus direct300 now share five source fragments
with one monolithic `ReimuActionStateLowDispatch.cpp` entry/low method. It
runs entry processing before re-reading action, routes signed actions<=300,
calls real4740C0 for negative/gap/default cases and returns pending for>300
at the original47CC5F boundary. Its bool is a staging interface, not the
original void-root ABI. Native0/3122 includes1765 RETs (28 through real common
body),1036 common-entry stops,144 set669-entry stops,50 object998 requests,
48 effect requests and79 pending upper handoffs. Negatives fail1/59 and28/28.
All five old COFF text/data/relocation identities remain unchanged, plus
0/9,0/88,0/64,0/99,0/150 focused old-stage replays. The expanded64-key fixture
preserves old layouts byte-for-byte; Ghidra re-attests selector/default/handoff,
primary hashes unchanged and clone deleted. No source-present/exact credit.
See [integrated low evidence](REIMU_LOW_DISPATCH_INTEGRATION_2026_10_17.md).
The wider `ReimuActionStateDispatch.cpp` now directly adds301..310/320..322
through `ReimuActionStateMidNormalCases.hpp`:3798 physical bytes/1011 target
instructions plus shared exits. It keeps entry/low cases in the same method,
routes311..319 to real common code and leaves>322 pending. Native0/5729
includes5211 RETs,151 effect requests,313 object requests,42 common-entry
stops,1 set669-entry stop and11 pending handoffs.29 original branch sites
are required at both x87 precisions; object848 requests compare the pointed
three-float payload. Three compiled negatives fail1/104,6/864,2/1274.
Ground fixtures were corrected after negatives exposed premature native
landing transitions. The wider method also passes59 old-path smoke plus28
real common-return cases. All six prior COFF code/data/relocations are
identical after rebuild, and old smokes pass0/9,0/88,0/64,0/99,0/150,0/59.
The14-frame fixture preserves default graphs;19 structural tests pass.
Direct Ghidra re-attests entries/root;9 primary hashes unchanged, clone
removed. No root implementation/exact credit. See
[middle-group evidence](REIMU_MID_NORMAL_ACTIONS_2026_10_18.md).
The same monolithic method now adds400/401/402/404/406/408 through
`ReimuActionStateMidProjectileCases.hpp`:6469 target bytes/1570 instructions
plus shared tails, with>408 pending. Native0/2932 includes2321 RETs,13 effect
requests,575 object requests,11 common-entry stops,1 set669-entry stop and11
pending handoffs.624 real atan2 calls execute unchanged native math code;
592 range calls execute actual MT and572 scaled-counter calls retain phase/
WORD behavior.16 required target branch sites run at both x87 precisions.
The191-case integration cohort covers earlier middle/low/entry/common-return
paths in the changed method. Wrong speed/payload/cadence controls fail2/32,
8/60,8/60;408's corrected target launch speed is3.5f. All six older code/data/
relocation identities and focused smokes are preserved. Nine-sequence graphs
retain old default bytes;23 structural tests pass. Ghidra attests entries,
helpers/root/shared tails;9 primary files unchanged, clone deleted. Object/
effect requests still stop at actual wrapper entry, so second-shot/wave/
post-manager continuations remain unproved; no root implementation/exact credit.
See [projectile-group evidence](REIMU_MID_PROJECTILE_ACTIONS_2026_10_18.md).
The same method now adds410/412/414/416/418 via
`ReimuActionStateMidShotCases.hpp`:3649 target bytes/902 instructions plus
shared exits, with>418 pending. Native0/2217 includes1806 RETs,366 object
requests,23 effects,11 common-entry stops,1 set669-entry stop and10 pending
handoffs.288 atan2,363 scaled-counter and354 wave calls execute unchanged
native helpers;801's four-float and808's three-float/-1 requests are compared.
19 target branch sites run at both precisions. A251-case integration cohort
covers earlier paths; six older code/data/relocation identities and focused
smokes remain unchanged. Order/sign/counter-boundary negatives fail2/38,
1/50,3/50. Prior Ghidra410..418 readback is reused after rechecking root/body
bytes and all9 unchanged primary files; no new process/clone. Complete root,
returning world contexts and exact comparison remain pending; no implementation/
exact credit. See [shot-group evidence](REIMU_MID_SHOT_ACTIONS_2026_10_18.md).
The monolithic method now adds500/501/502/503/505/506/507/508 via
`ReimuActionStateMid500Cases.hpp`:12427 target bytes/2910 instructions plus
shared exits, with>508 pending. Native0/4522 includes3306 RETs,755 object
requests,440 effects,10 common-entry stops,1 set669-entry stop and10 pending
handoffs.1232 scaled-counter and1223 wave calls execute unchanged helpers;
810/811 first-volley three-float requests, separate live level checks,17C
stores, input-field selection and signed charge/tail boundaries are covered.
17 target branch sites run at both precisions. Wrong input/speed/cutoff
controls fail640/1728,2/72,208/1728. A301-case earlier-path integration cohort,
six old code/data/relocation identities and focused smokes pass; no historical
full replay or exact credit. Ghidra attests eight entries/root/shared exits;
9 primary files unchanged and clone removed. Subsequent volley requests and
returning world contexts remain unproved. See
[first500-family evidence](REIMU_MID_500_ACTIONS_2026_10_18.md).
The existing500-family source now also admits510/511/512/513:7201 target
bytes/1700 instructions plus shared exits. These use17C=8, wave20 and812's
level-specific3/4/5-angle groups, with>513 pending. Native0/2493 includes1844
RETs,399 object requests,232 effects,7 common-entry stops,1 set669 stop and10
pending handoffs;636 scaled-counter and627 wave calls execute actual helpers.
12 required target sites run at both precisions. Wrong wave/flag/angle
controls fail4/36,36/36,2/36. A373-case integration cohort and fresh0/72 old500
replay cover earlier paths; all six old code/data/relocation identities and
focused smokes remain unchanged. Direct Ghidra re-attests entries/root/shared
exits;9 primary files unchanged and clone deleted. Compact source loops versus
expanded target call sites, returning volleys/world contexts and whole-root
canonical matching remain unproved; no implementation/exact credit. See
[510-family evidence](REIMU_MID_510_ACTIONS_2026_10_18.md).
Eight further actions520/521/522/523/525/526/530/531 now join the same method:
5361 target bytes/1277 instructions, with>531 pending. Native0/3362 includes
1922 RETs,1399 object requests,18 effects,12 common-entry stops,1 set669 stop
and10 pending handoffs; a409-case cohort preserves earlier paths. First815/
816/817 payloads,17C flags, pre/post-advance gates and signed facing are
checked. Aerial522/523 use x+facing43,y+107, not the previous family's50/108.
523 sets9 through its own485DBE path;522 shares48748C. Twelve required sites
run at both precisions. Three compiled coordinate/speed/cutoff controls each
fail2/64; all six older COFF code/data/relocation identities and focused
smokes remain unchanged. Ghidra re-attests root/current/adjacent entries;
9 primary files unchanged, clone removed. Subsequent trajectories/pairs,
signed609 gating and waves after returning requests have raw instruction
evidence only; sqrt's18-byte binding is not dynamically executed. No root
implementation/exact credit. See
[520-family evidence](REIMU_MID_520_ACTIONS_2026_10_18.md).
540/541/545/546 now join the same method through546:4120 target bytes/949
instructions. Native0/5807 includes5256 RETs,511 object requests,18 effects,
11 common-entry stops,1 set669 stop and10 pending handoffs. Visual scale/NaN/
alpha-wrap,541 signed state counters, launch coordinates and first fan
payloads are checked;366 real sine/cosine pairs and1051 wave calls execute.
541 moves self x+facing100;540 uses peer x-facing180. Thirteen required
sites run at both precisions. Wrong alpha/source-coordinate/angle controls
fail8/40,50/200,1/40. A473-case integration cohort, six unchanged old COFF
identities and focused smokes preserve earlier paths. Prior direct Ghidra
readback covers these entries and is reused after rechecking root/body/table/
instruction bytes and all9 primary file hashes; no new process/clone.
Later fan iterations/returning manager contexts remain dynamically unproved;
no root implementation/exact credit. See
[540-family evidence](REIMU_MID_540_ACTIONS_2026_10_18.md).
550/551 and direct560 now join the same method through560:1496 target
bytes/378 instructions.550/551 share48749F; their1132-byte body ends48790B
before364 direct560 bytes and30 selector bytes. All50 non-default middle
keys/49 physical bodies now have source labels, checked against the canonical
table; this is branch coverage, not complete semantic or exact acceptance.
Native0/2665 includes1875 RETs,751 object requests,18 effects,11 common-entry
stops,1 set669 stop and9 pending handoffs.624 real random-roll/MT calls and
618 sine/cosine pairs execute. Preserve signed timer%3, negative ring radii,
four-float822 payloads and three-float825 payloads, separate live array fields,
alpha245 boundary and pre/post-advance nodes. The accepted random helper's
int interface is retained, with an unsigned conversion at this call site.
Three controls fail2/36,16/144,1/36. A513-case integration cohort, six unchanged
old COFF identities and focused smokes pass. Prior direct Ghidra readback is
reused after target/root/body/table/instruction and9 primary-file checks;
no new process/clone. Later ring iterations,25 grid requests and returning
manager paths remain dynamically unproved; TOP=0 gates are unchanged.
No root implementation/exact credit. See
[550/direct560 evidence](REIMU_MID_550_ACTIONS_2026_10_18.md).
First high561/565/566/600/601/602/604/605/606 now join the same method through606:
5325 target bytes/1380 instructions. Native0/6165 includes5578 RETs,514 object
requests,52 effects,11 common entries,1 set669 and9 pending handoffs. Thirty
required original sites run at both precisions;549 earlier-path integration
cases, six old COFF identities and focused smokes pass. Real texture publication
executes4212 times through8332 checked deque accesses, with both mapped manager
slots compared. Both player indices and self/peer duration branches run; no
helper result is fabricated. The private graph map grows to2 MiB for the larger
key domain; older fixtures/classes stay unchanged. Ground hold/cadence/node
contexts use y=0 because y=100 triggers the native landing helper's action9.
Preserve565/566 full-width held fields, double prediction, three friction rates,
signed60B gate, one-/three-float payloads and600..602 pre-advance cadence. Their
launch y offset is120, not112. Input/texture/angle controls fail64/144,96/96,2/108.
One direct Ghidra read-only clone re-attests root/entries/shared tails under
768 MiB/two CPUs;9 primary files unchanged, clone removed. Later world-returning
objects/window/cycle paths remain dynamically unproved; no root implementation
or exact credit. See
[first-high evidence](REIMU_HIGH_ENTRY_ACTIONS_2026_10_18.md).
608/609/610/612/614/616/619 now join the same method through619:4844 target
bytes/1211 instructions. Native0/6376 includes6001 RETs,319 object requests,
34 effects,12 common entries,1 set669 and9 pending. Twenty-nine required
original sites run at both precisions;657 earlier-path cases pass in an
18-destination-plus-input animation domain. The previous object also passes
that657-case domain. The private map returns to1 MiB; old fixtures/classes
stay unchanged. Sequence-window/secondary-cycle helpers each execute12 times;
all three window arguments are compared as12 bytes. Controls fail1/91,8/30,
336/840 for window outcome, signed flag and timer direction errors.
614's47FFA2 tail uses live EDI=3 here; assuming another caller's5 caused two
detected differences and was corrected. Preserve608 WORD decrement wrap,
612 signed BYTE184/alpha clamp,614 direct frame writes after sequence reset,
616 height300/280 and continuing120-frame transition, and619 widened51.4f.
Six old COFF identities/focused smokes remain unchanged. One Ghidra clone
attests all23 remaining high entries/instructions;9 primary hashes unchanged,
clone removed. Future groups may reuse after byte/primary-hash rechecks.
Active indexed windows, returning volleys/backend contexts, full void ABI
and canonical matching remain unproved; no implementation/exact credit. See
[608..619 evidence](REIMU_HIGH_MIDDLE_ACTIONS_2026_10_18.md).
650/651/658/669/695/696/710/711 now join the method through711:6655 target
bytes/1697 instructions. Native0/6481 includes5162 RETs,1251 object requests,
46 effects,12 common entries,1 set669 and9 pending. Thirty-three required
original sites run at both precisions;748 earlier-path cases pass. The fixture
adds actual native landing destination704; prior classes stay unchanged.
Preserve650/651 signed pre-advance shot gates and different gravity ordering,
658 unconditional gravity,669's >=240 cutoff/three-float869 payload and
710/711 stored-motion restores, reversed mode-table order and aim offsets.
669 and710 use different floating addition association for ray y. The new
869 subclass permits3/4 with full count/content checks; old619 remains4-only.
Controls detect1/748 for count4->3,40/680 for cutoff equality and50/600 for
711's mode0 offset. Six old COFF identities/focused smokes remain unchanged.
The reused direct Ghidra receipt is rechecked against all current bytes and
9 unchanged primary hashes; no new process/clone. Returning volleys/backend,
full void ABI and canonical matching remain unproved; no implementation/exact
credit. See [650..711 evidence](REIMU_HIGH_LATE_ACTIONS_2026_10_18.md).
720/730/740/760/770/795/797/798 now join the method through798:4562 target
bytes/1149 instructions. A target-table/source-label audit reconciles all128
nondefault keys (low44,mid50,high32,direct300/560); this is label coverage only.
Native0/11820 has10364 RETs,1400 object requests,30 effects,12 common entries,
1 set669 and13 pending. The last count includes eight740 undefined-stack
boundary cases: mode>3 in sequences1/6 reads original [ESP+B4] without an
entry-path initialization. Source leaves those paths pending; no guessed
value/target return is supplied. Thirty-four required-site cases,2267 real
MT draws and64 inactive finalization/WORD-copy calls pass. Prior baseline
agrees851/852 integration cases;798 intentionally changes from pending to
its newly recovered body. Preserve720's equality cutoffs/alpha behavior and
four-float901 payload,730's post-advance cadence/random conversions,740's
mode-dependent signed gates,760's cascading health phases and770's frame7
helper/store order.795/797/798 share different completion/landing tails.
Controls detect18/216 for720's variant,84/720 for760's else-if mistake and8/56
for740's cutoff equality. Six old non-debug COFF identities/smokes stay
unchanged. Ghidra evidence is reused after current byte/table and9 primary
hash checks; no new process/clone. No implementation/exact credit. See
[720..798 evidence](REIMU_HIGH_FINAL_ACTIONS_2026_10_18.md).
A reproducible source-shape probe now expands independent cases into three
source regions while preserving shared550/551. The untouched official mapper
finds45/50/33 table groups,126 unique destinations and0 target-group splits.
Compact staging has only21/24/23 groups/66 destinations. Generated C++ remains
under build/; selected source and old adapters are unchanged. The new object
has75836 text bytes,74560 bytes before the first table,1095 decoded calls and
146 RETs. Native0/894 passes (852 earlier paths,34 required sites,8 unresolved
740 boundaries). Owner comparison finds0/127 instruction/edge-identical blocks;
no implementation/exact credit. First diagnostic mismatch478FA8 is stack
allocation570h vs5A8h. Standard full comparison still lacks the complete root
relocation contract. See [source-shape diagnosis](REIMU_ACTION_SOURCE_SHAPE_2026_10_18.md).
510..513's wide angle loops are now twelve explicit requests per action,
with all three parameter floats reset and x/y/facing re-read per call. Separate
live level tests remain. Both the main compact build and three-region probe
pass0/3061 focused native cases. A separate unknown-live-in basic-block audit
checks all48 target/source payloads and12 inter-group level reloads without
executing/returning callbacks. Three compiled later-request errors pass0/36
first-request smoke but are rejected by static constraints. The two evidence
classes remain distinct. Source probe text is now79980, first table at78704,
with1131 decoded calls and unchanged126 primary destinations. Four action spans
grow3280->7320 versus target7201; no equality credit. Target still has1188
calls and81550 callable bytes; the remaining pre-table deficit is2846. First
diagnostic difference remains570h versus5A8h stack allocation. No accepted
source/header/profile/relocation change or aggregate replay. Nine primary
Ghidra hashes unchanged; obsolete probes/controls cleaned. See
[510 request-source evidence](REIMU_510_REQUEST_SHAPE_2026_10_18.md).
710/711 now have eight independent mode loops, with per-iteration payload
resets and fresh actor reads. Compact and three-region objects both pass0/2372
focused native cases. A separate unvalued-angle static contract accepts all8
target/source loops; compiled wrong-spacing/count controls pass first-request
0/600 but each fail the corresponding static mode. Source argument order
removes avoidable spills. The probe keeps126 primary destinations; its prefix
is80344 bytes, text81652,1158 decoded E8s and146 RETs. The two spans total3146
versus target3097. Stack remains5A8h versus570h; no exact credit. An opt-in
fixture bounds executable code within81550 and mapped switch data within the
reviewed original metadata end48D38C; old contracts remain fail-closed.
Old final/510 smokes and all48 510 packets still pass. No accepted-unit or
aggregate replay; all9 primary DB hashes unchanged. Baseline/control objects,
superseded generated source and caches are cleaned. See
[aimed-mode evidence](REIMU_AIMED_MODE_SHAPE_2026_10_18.md).
720 now has four independent mode loops, each with one360 draw, an unsigned
float32 base conversion and per-iteration reset of all four901 parameters.
Both current objects pass0/2098 native cases; all4 target/source static loop
contracts pass. Wrong-spacing/count controls pass first-request0/216 but each
fail the changed static mode. Previous710/711 and510 static constraints pass.
The expanded probe now has80764 pre-table bytes,82088 text bytes,1164 E8s,
149 RETs and8 switches. The720 span is1448 versus target1451; frame598h versus
570h is still the first diagnostic mismatch. Primary groups remain126; no
implementation/exact credit or aggregate replay. All9 primary DB files remain
unchanged; obsolete objects/control copies and caches are cleaned. See
[720 mode-source evidence](REIMU_720_MODE_SHAPE_2026_10_18.md).
730 now has four independent cadence/request bodies and a common fresh73C
increment. Both current objects pass0/3676 native cases, including128 extreme
signed counters with genuine native wrap; cadence5->6 is detected16/128.
Previous710/711/720 static loops and510 packet constraints still pass. The
candidate730 span is1322 versus target1320, with the two observed IDIVs and
one shared902 tail. Expanded prefix81288/text82628 has1171 E8s,149 RETs and9
switches; frame598h versus570h remains first mismatch. No implementation/exact
credit or aggregate replay. All9 primary hashes unchanged; superseded720
objects/control copies and caches cleaned. See
[730 mode-source evidence](REIMU_730_MODE_SHAPE_2026_10_18.md).
740 now has both explicit mode selectors and naturally unassigned locals for
out-of-range inputs. VC8 reproduces three same-slot fallback reads and the
fourth cutoff read; expanded uses the target'sESP+B4 (compactESP+18). A strict
constant/table/spill qualifier derives candidate pre-read stops; actual740
source no longer returns false there. Both objects pass0/5494 native cases,
including8 unknown boundaries. A cutoff=0 control passes0/56 valid cases but
fails qualification. With the existing zero-stack input, raw target/candidate
sequence1 genuinely divide-fault and sequence6 genuinely returns with equal
state; arbitrary stack contents remain unproved. Prior static contracts pass.
The expanded probe has81452 pre-table bytes/text82824,1171 E8s,150 RETs and
all11 target switches. Frame598h versus570h and full canonical contract remain
unresolved; no implementation/exact credit or aggregate replay. Nine primary
DB hashes unchanged; obsolete/control products and caches cleaned. See
[740 selectors/indeterminate locals](REIMU_740_MODE_SHAPE_2026_10_18.md).
An opt-in `--void-root` source probe now emits a real void/noargs thiscall
member with the full common default for action>798. Only its private header
changes; normal bool output is byte-identical. Native return contracts match
their COFF type and preserve real RET/ESP/saved-register/x87 checks. Void EAX
is unobserved as a result; old bool remains strict. The new object passes
0/1544 cases, with inputs for all128 nondefault actions,85 boundary-default samples,
16 genuine upper-common returns and8 indeterminate boundaries. Reintroducing
the upper early return is detected10/510. Old bool0/12 and0/8 and the earlier
static contracts pass. The void probe has81128 prefix/text82500,1167 E8s,
148 RETs and all11 switches; first difference remains frame598h versus570h.
No root source-present/exact credit or aggregate replay. Nine primary hashes
unchanged; superseded/control products and caches cleaned. See
[void/default candidate](REIMU_VOID_ROOT_2026_10_18.md).
The void probe now has an explicit probe-only relocation ledger/auditor. All
2449 records classify and replay strictly:1167 calls,1098 numeric operands,
14 local metadata addresses,163 code pointers and7 global reads. Calls and
numeric placements are checked against independent target observations and
existing anchors. Missing-call and same-value/wrong-address controls fail.
Nine unsigned conversions in550/551/602/720/730/740 now use the observed
dword2^32 correction: only9 raw text opcode bytes changeDC->D8, with no new
rounding stores or other code/layout change. Source-only literal sites9->0.
Fresh void0/1544, compact bool0/12 and0/8, and earlier static contracts pass.
Isolated fast/RTM probes did not fix the operand-width issue; neither is adopted.
Full root remains nonexact at478FA8/frame598h versus570h. The last source RET
is not its code end; callable/compiler ownership remains unproved. No exact
credit or aggregate replay;9 primary DB hashes unchanged and stale products
cleaned. See [root binding/operand evidence](REIMU_ROOT_RELOCATIONS_2026_10_18.md).
Nine action buffer lifetimes now follow observed stack pointer identities:
separate ordinary/random400/401/404/406 buffers, shared525/526 groups,
shared545/546 fan/final requests and shared669 loops. Arrays larger than8
bytes decrease112->109; frame598h->578h versus target570h. Whole-root CFG/ESP
propagation and all reaching argument writes preserve cross-case shared tails;
all9 action-entry buffer partitions pass; the earlier object fails all9.
Affected native0/6722, current void0/1544, compact0/12 and0/8, and prior static
contracts pass; returning world calls remain unproved.
Candidate prefix81384/text82756,1168 calls and2454 replayed relocations remain
nonexact, first478FA8. Case-order/single-switch controls keep598h and are not
adopted. No credit/aggregate replay;9 primary DB hashes unchanged and stale
products cleaned. See [request-buffer lifetimes](REIMU_REQUEST_BUFFER_LIFETIMES_2026_10_18.md).
550/551 now prepares both coordinate expressions directly in request arguments,
matching the observed pre-sine count/pointer/arg5/direction pushes. The extra
trajectory slot disappears into the normal m32 slot40; frame578h->570h equals
target. Strict first mismatch moves to478FB1/+11h, zero-register sharing.
Focused native0/1576, current void0/1544, compact0/12 and0/8, prior static loops
and all9 buffer partitions pass. Old578h source fails both preparation checks.
Source adjacent-table bounds and x87 stack-store tracking are corrected with
two regression fixtures; prior9 buffer conclusions remain valid. Prefix81364/
text82736,1168 calls and2456 replayed relocations are still nonexact. The grid
after eight object requests has static call-site evidence only; returning
world calls remain unproved. No credit/aggregate replay,9 primary DB hashes
unchanged; unused products cleaned. See [550 request/frame evidence](REIMU_550_REQUEST_FRAME_2026_10_18.md).
400/401/404/406 now captures BYTE750 mode before each path's shot-cost gate,
with independent cost/state/array/request/wave/WORD732 work and a two-to-zero
random loop. Target/source branch facts agree; the preceding source has four
cost-order failures. Expanded1178 calls/frame570h/prefix81668/text83040 remains
nonexact at478FB1 and exceeds callable/metadata bounds by118/116 bytes.
Ordinary audits/execution still reject that size. Explicit oversize mode is
read-only; compact void50584 supplies native evidence without owner claims.
All50584 canonical-replayed bytes/relocations equal the private0/2312 witness,
with unchanged native adapter. Fresh compact0/1544, bool0/12 and0/8, previous
static loops and9 buffer partitions pass. No callbacks fabricated or exact
credit;9 primary DB hashes unchanged and unused products cleaned. See
[projectile mode branches](REIMU_PROJECTILE_MODE_BRANCHES_2026_10_18.md).
619 now retains two sign-selected height/request expressions;695 spells the
three140 effects followed by141/142 as consecutive calls. All128 primary
action entries have a direct-callee site census: differing cardinalities
fall from five actions to three (400/404/406 wave sharing). 619 stack signs
and the67-instruction695 sequence are checked; its two differing PUSH
registers independently hold-1. Expanded prefix81716/text83088/frame570h,
1176 E8s and2465 qualified relocations remains nonexact at478FB1 and exceeds
callable/metadata by166/164 bytes. Read-only oversize only. Compact void50744
has fresh0/1010 integration, including13 inputs each for619/695; nine buffer
partitions pass. Later returned-world requests/effects remain unproved.
A private float-return control covers m32 zero but does not shrink code;
return type remains unresolved and no shared declaration changed. No credit
or aggregate replay;9 primary DB hashes unchanged, unused products cleaned.
See [call ownership and source structure](REIMU_CALL_OWNERS_2026_10_18.md).
The local action selector is now promoted to int, recovering the target
MOVSX/32-bit compare sequence. Expanded prefix81668/text83040 drops48 bytes,
frame570h/2465 qualified relocations/first478FB1 remain; callable/metadata
excess118/116 still prohibits execution. All65536 field values pass a
read-only selector-to-arm audit (21 selector instructions each), preserving
physical alias sets; a decoded-model bound control misroutes300/301.
Compact void50800 has fresh0/1520 integration/default inputs; nine buffer
partitions pass. Target300 starts47CBBD and320 starts47D96A, then shares the
47CC2B continuation. Source merges both complete bodies at47CBFE; this
explains three physical E8 deficits despite equal per-action counts.
Private live-reference and shared-default-goto controls are unselected;
the latter adds32 bytes. Final witnesses were rebuilt serially. No exact
credit/aggregate replay;9 primary DB hashes unchanged, unused products cleaned.
See [selector and direct-arm sharing](REIMU_SELECTOR_PROMOTION_2026_10_18.md).
Reimu now has a genuine /GL root +42 normal-COFF provider TU link:48 game
addresses compared, five existing nonexact providers explicit,45 same-target
aliases and17 attested data ABS bindings. The private4776C0 word setter is
15/15 and both existing excluded SDK deque witnesses94/100 agree before and
after linking; no authored credit. Independent typed replay checks2465 fields
and the exact1282 HIGHLOW inventory. All83040 canonical payload bytes equal
the ordinary witness, SHA7d56c77794ef794f7e3d5fa8d939b2784012eb4298a037e7f65becb8e00255d5.
All11 ordinary switches/CFG and nine buffer partitions transfer by complete
correspondence; no shared inspector relaxation or DLL execution. Prefix81668/
text83040/frame570h and first478FB1 persist;300/320 remain fully merged.
Two explicit-tail source controls add48 bytes; a fresh single-switch void
control adds32. None is selected. The present opaque-provider LTCG backend
context does not repair the source. Checked object caches avoid unchanged
recompilation. No exact/source selection or aggregate replay;9 primary hashes
unchanged, unused products cleaned. See [genuine link and full correspondence](REIMU_REAL_LINK_2026_10_18.md).
Latest entry lifetime checkpoint selects one raw unsigned direction snapshot
per998 request and inline rounded coordinate arguments, recovering all three
target MOVZX/raw-push/signed-register patterns. Entry text522 has0/10584 native
differences; compact void50816 has0/6722 across nine request families. The
current expanded ordinary/linked payloads remain83040 bytes and agree fully,
SHAef6cc2879b328bc86a22b274b1bce9b36acb5f3221818227069e7e073738b01b;
prefix81668/frame570h/first478FB1 and oversize118/116 persist. All11 switches
and nine buffer partitions qualify. No exact/source credit or aggregate replay.
The conservative private cache hashes every source header, so this fragment
edit recompiled45 objects; the three receipt command groups are not a compile
count. Removed73 superseded products/7161518 bytes; current witnesses and
primary databases retained. See [entry argument lifetimes](REIMU_PRELUDE_LIFETIMES_2026_10_18.md).
The preceding circular-request checkpoint emits distinct expanded arms in observed
target-owner order and recovers669's four request-tail arguments live across
both lookups. The old locals fail both circular-site preparation checks;
new source passes, preserving all nine buffer partitions/11 switches. Code
prefix81400/text82772/frame570h now fit the reviewed windows;20260 decoded,
20253 reachable instructions. Expanded native0/1528 integration/default/740
guarded inputs and0/1086 for669; no compact substitute or full historical
matrix. Genuine linked/ordinary82772-byte replay agrees fully, SHA
ab0a6c4ad164579c98f44af8031e84e5247dbf186cf20e6ae2554fdd1af53bca;
2464 fields/1281 HIGHLOWs. The separate12-byte next-owner INT3 alignment gap
is strictly qualified; payload comparison remains exact. First478FB1 persists,
now an immediate WORD7A0 store before delayed PUSH EDI. No exact/source credit.
Checked unchanged rebuild reuses45 objects without compilation. Superseded
compact/trial products cleaned;9 primary DB files unchanged. See
[circular lifetimes and owner order](REIMU_CIRCULAR_REQUEST_LIFETIMES_2026_10_18.md).
The preceding random-effect checkpoint keeps the m64 X-base snapshot and expresses
the two rounded random coordinates inside effect123's call. Direction/arg5
are now pending before the first real MT draw, and rounded Y before the
second. Actions208/211/220/221/222 pass0/400 expanded native inputs, including
five raw facings, both x87 precisions and X=2**25. Read-only MT-entry stack
observations reject the old named-coordinate source400/400; a separately
compiled float-X-base control fails50/400. Expanded integration/default/740
passes0/1528. Code prefix81304/text82676/frame570h fits both windows; all11
switches, nine buffer partitions and request preparations pass. Genuine
linked/ordinary82676-byte replay agrees fully, SHA
f9166f6a3ea904d0bcdb5a761bc0d22e2ccada0383f10c60282a27ac5e42ef73;
2463 fields/1281 HIGHLOWs and the separate12-byte INT3 gap qualify. First
478FB1 persists; no exact/source credit or aggregate replay.209/221 now share
advance47B5DD, corresponding to target47B51B. Superseded trial products were
cleaned; primary databases retained and hashes unchanged. See
[random-effect argument lifetimes](REIMU_RANDOM_EFFECT_LIFETIMES_2026_10_18.md).
The preceding effect124 checkpoint extends those lifetimes to223/224/225/226,
preserving the byte-negated unsigned outgoing direction for224/225. All720
effect123/124 lifetime inputs pass in the expanded ordinary root, plus1528
integration/default/guarded740 inputs. The old expanded source fails320/320
new lifetime observations; the wrong-direction staged control fails96/320.
Code prefix81544/text82916/frame570h now leaves6/8 bytes in the reviewed
windows. This grows240 bytes because whole-root sharing changes; no suffix
identity claim. All11 switches/nine buffer partitions/request preparations
pass. Genuine linked/ordinary payloads agree fully, SHA
2672556d0298e501e595aa4136b07195b9f55fea3d0b9a40a0d5d1ca9a6d66ed;
2468 fields/1281 HIGHLOWs and12-byte INT3 gap qualify. Source522/523 now have
separate advance4858D8/485CB8, as target48599F/485D75;209/221 still share.
Source has119 advance sites versus target121. First478FB1 persists; no exact
or source-present credit. Builds/native suites ran serially on one CPU at nice10;
no aggregate replay or Ghidra process. See
[effect124 lifetimes and sharing](REIMU_RANDOM124_LIFETIMES_2026_10_18.md).
The preceding214 checkpoint expresses rounded effect125 coordinates inside the
call, preserving unsigned direction/arg5 across sine and rounded Y across
cosine. Expanded root0/240 checks these pending arguments without modifying
helper results; the preceding object fails240/240. Staged0/240 plus720 real
RET steering/flight-exit inputs pass. Expanded integration/default/guarded740
passes0/1528. Code prefix81416/text82788/frame570h shrinks128 bytes; all11
switches/nine partitions/request preparations pass. Genuine linked/ordinary
payloads agree fully, SHA
63c73a0ec4f4f0acda5d8344faa2b2f2e30dacd6a8995bb1e59aeacff092ab02;
2467 fields/1281 HIGHLOWs and12-byte INT3 gap qualify. First strict target
difference moves to+18/478FB2: PUSH EDI now agrees, but the following zero
store uses XOR EDI/register storage instead of target's immediate WORD store.
No exact or source-present credit. Source advance sites remain119 versus121;
209/221 share47B5CD,522/523 stay separate485898/485C78,310 still joins215/797
at47BFCF.214's second resource gate has only local incoming CFG edges and no
entry from any of the11 switch tables. Same-target Yuyuko/Komachi repeat
the WORD736 comparison too; Udonge has one observed comparison. This supports
further source/context investigation, not an invented inline/volatile helper.
See [214 effect lifetimes and gate evidence](REIMU_FLIGHT_EFFECT_LIFETIMES_2026_10_18.md).
The preceding joint checkpoint recovers200/201/202/203's effect124 lifetimes and
545/546's four circular object821 preparations. All rounded geometry remains
inside the corresponding calls, with existing snapshots/arrays retained.
The preceding root fails160/160 new MT-entry observations; the movement-only
intermediate fails both821 preparation contracts. That intermediate exceeds
the callable/metadata windows190/188 bytes and is never executed. The joint
candidate fits again at prefix81544/text82916/frame570h. Expanded native0/4420
covers2732 for545/546,160 new movement lifetimes and1528 integration/default/
guarded740 inputs; staged0/909 covers movement/input/special coordinates.
All11 switches/nine default buffer partitions and five545/546/550/551/669
preparation contracts pass. Genuine linked/ordinary payloads agree fully, SHA
e14328a2455420de790de6089e123046fe083ce8f8b1a5f2f5265817df75d7e9;
2466 fields/1281 HIGHLOWs and12-byte INT3 gap qualify. Current strict first
is+17/478FB1(XOR EBX before PUSH EDI); the unselected intermediate's+134
does not describe the final candidate. No exact or source-present credit.
Source has119 advance sites versus target121, but its sharing changed:
209/221 share47B59E;522/523 share4859C6;215 uses47BFC8 while310/797 share
47D983. Target instead shares215/797 and separates310 and522/523. Six callee
cardinalities still differ; counts alone do not establish correct ownership.
See [movement and fan lifetimes](REIMU_MOVEMENT_AND_FAN_LIFETIMES_2026_10_18.md).
The preceding aim checkpoint retains rounded deltaX and computes rounded deltaY
inside atan2's call for400/401/404/406 and410/414(two sites each). Read-only
peer-Y-load observations require X already pending and equal to the actual
subsequent atan2 argument. Preceding source fails600/600; final expanded root
passes0/600(400 RET/200 object801 entries), plus0/1528 integration/default/
guarded740 inputs. Complete A/B replay changes only240 bytes inside those12
73-byte preparations; all other payload bytes, CALLs, branches and
metadata stay identical. Nine complete preparations equal raw target bytes
without normalization; the other three differ only in two register encodings.
This is local diagnostic evidence, with no exact or partial-byte credit.
Prefix81544/text82916/frame570h/first+17 remain. All11 switches/nine default
buffer partitions and five circular preparation contracts pass. Genuine
linked/ordinary payloads agree fully, SHA
826889ee7ec055e44def5cc1602de2fae75f58403e2332194ec3b20cd55dc0d3;
2466 fields/1281 HIGHLOWs and12-byte INT3 gap qualify. Prior call-sharing
observations remain valid by complete outside-preparation byte identity.
Root remains unclassified/declaration-only; no aggregate replay. See
[aim argument lifetimes](REIMU_AIM_ARGUMENT_LIFETIMES_2026_10_18.md).
The preceding bounded context probe exposes the real strict-FP atan2 source to
the genuine LTCG root link. Its ordinary anchor freshly matches63/63; adding
only /GL produces a65-byte math body with PUSH/POP ECX and shifted stack
displacements. All36 root math calls remain, frame570h and first+17 persist.
The lowest of11 tables is at offset81556; this private layout is not a
qualified callable boundary and the image is never executed. All51 original
object/library inputs and four base receipt/object/image/MAP hashes remain
unchanged. The selected root and ordinary exact math producer stay unchanged;
no provider-IR guard is relaxed. A raw-target ECX read-before-definition
search after the three differing signed-facing loads finds no incoming ECX
read before redefinition/return, under reviewed math/ftol2 contracts. This
does not recover original visibility or justify register constraints. No
root exact/source credit or aggregate replay. See
[the real-math visibility probe](REIMU_ATAN2_VISIBILITY_2026_10_18.md).
The latest checkpoint executes effect123 requests through the real manager
and returning root continuation, using a narrow native VC8 host under Wine.
It maps the attested target without changing any .text byte, resolves105 real
kernel32 imports and blocks65 others. Observed OS-data initialization plus
actual target CRT heap/thread routines support real allocation/locking; each
case constructs an actual4378F0 manager, borrows read-only untextured resource
headers, creates/finalizes one effect through435240/437C00, returns through
the root, then restores the headers and runs the actual437DF0 destructor.
Expanded native0/600 covers208/211/220/221/222, five facings, two speeds,
three X positions, two seeds and PC53/64. All6980 snapshot bytes per case
agree, including full actor/effect, MT state, count and observed FP control.
An independent target repeat agrees too; a compiled wrong post-effect
comparison fails480/600. Oversized single-arm controls are never executed.
Callable/metadata bounds, all11 stack/request contracts and immutable-code
checks remain mandatory. Main source/object/payload/first+17 stay unchanged;
no root exact/source credit or aggregate replay. See
[real effect returns](REIMU_EFFECT_RETURNS_2026_10_18.md).
Next extend the real backend to remaining effect and owned-object requests.
A fresh static recheck confirms300/320 still fully merge at source47CC02;
target retains distinct47CBBD/47D96A prefixes and shared47CC2B tail.
215/310/797 and522/523 still have different target/source incoming sets.
These are static ownership questions, not missing per-input behavior.
214's two target resource gates versus one candidate gate also need
source/visibility evidence; do not invent volatile reads or inert duplicate
conditions. Exact callable ownership and original visibility/profile remain
open before root acceptance.
Use `--cohort` for focused rechecks; no aggregate cold replay was run.
Obsolete unpinned disassembly exports (~18MB) and rejected/superseded object
files were removed; current bounded evidence and primary databases remain.
Obsolete common-root GL controls/provider objects and rejected Reimu control
objects were removed at this phase switch. Current Reimu evidence/object
remain; regenerate common link products before using its inspect mode.

## Shared Fighter root: preceding investigation

The current bounded boss is `Fighter_update_common_action_state @ 4740C0`,
the 10219-byte root used by all15 roster roots. Selected source stays at
CRLF SHA256 f53478cf4aa721094a153c2c94991430e7f89007321daf599345a4bcdff23265:
strict ordinary first+14/4740D4 and53/66 diagnostic owners. No exact credit
or source selection changed. See [linked tail and sharing evidence](COMMON_FIGHTER_LINKED_TAILS_2026_10_17.md).

Real one-root GL controls reuse24 genuine source providers, SDK deque and
pinned CRT. An unselected nested-switch/float/six-helper control has the
target51/15 destinations and8virtual/13direct tails,10247 reachable bytes
versus10219,200 E8s versus198, but only46/66 identical owners. Both extra
E8s reside in low:162: the candidate duplicates boundary/advance calls
instead of joining target action50. An ordinary explicit shared-goto control
still moves that continuation to162 and drops to51/66; do not adopt it.

The linked inspector now supports opt-in reviewed tail qualification and
complete diagnostic replay. It keeps raw exits, proves ECX receiver offsets,
the16-vtable target domain, full local epilogues and actual raw-equal bodies
for all3 direct callees. Only qualified E9 displacements normalize; all other
bytes remain significant. Default guards and accepted-unit rules stay intact.
`probe-common-fighter-ltcg.py --help` is now read-only; inspect mode reuses
hash/digest-checked providers. Nested strict first+14 persists. Direct Ghidra
attestation passed; all9 primary files unchanged, disposable clone removed.
An additional commuted-comparison control loses799 and falls to52/66;
it is rejected. Recovering the action50/162 x87 continuation still requires
new source/compiler evidence; do not repeat the existing negative matrices.

## Iku steering face tails: preceding selected checkpoint

`Iku_dispatch_action_state_vslot28 @ 620920` retains complete110-action
source, void thiscall prelude/default and one ascending switch. Target
`[620920,62EFBE)` is59038 bytes /15132 instructions /131 RETs, SHA256
abc831c6ccd95986bed811694f532ad8c8b92cb49702a7f6ce4de100b8a73dea.
Strict whole-root remains **nonexact +0x64 /620984**: target alone hoists
EDI=1. No exact/partial authored credit. Current evidence:
[17-action common surface exit](IKU_COMMON_SURFACE_EXIT_2026_10_17.md) and
[effect direction/argument ownership](IKU_EFFECT_DIRECTION_2026_10_17.md), now
[all six atan2 argument lifetimes](IKU_STEERING_ARGUMENT_LIFETIMES_2026_10_17.md),
plus [real animation completion](IKU_ADVANCE_CALLBACKS_2026_10_17.md) and
[object998 prelude ownership](IKU_PRELUDE_DIRECTION_2026_10_17.md), followed by
[signed zero gates](IKU_SIGNED_ZERO_GATES_2026_10_17.md) and
[steering face-entry contexts](IKU_FACING_TAIL_CONTEXTS_2026_10_17.md).

The latest bounded investigation keeps selected C++ and every canonical byte
unchanged. The extra730 face site is a split of the nonfixed Y lower-clamp
continuation: target store/discard paths join CALL62DC18, candidate calls
62D953/62D97F separately. Fresh whole-entry native0/4960 now checks raw
pre-face velocity/direction/sequence, control word,TOP and sticky exceptions,
as well as existing final state/call history. Target1920 common entries map
to candidate96 store/1824 discard entries; fixed clamps1920 each. All3840
entry contexts agree atTOP0.1120 geometry cases stop at real atan2 before
face entry. The two other730 face sites are outside this runtime scope.
Wrong duplicate-face control detects1920/1920; both retained examples have
identical final actor memory, so call-history checking matters.

Double Y-bound parameters are whole-section neutral; direct use of five
private typed coordinate fields across608 expressions is also whole-section
neutral with offset/prefix-size assertions. Neither changes the public
header. Commuted lower comparison adds a wrong-width double literal and is
rejected; sharing only finalY lower grows16 bytes and retains five face sites.
A fresh genuine GL/LTCG link reuses41/44 steps; only22 ordinary shared bytes
change around mode-load/Y-store scheduling, leaving all five face CALLs
unchanged. Strict first+64 persists. Five registered nonexact dependencies
and provisional abs adapter remain explicit; linked image is not executed.
These controls establish no general compiler/LTCG barrier. Direct readonly
768MiB/twoCPU Ghidra attests the185-byte clamp/tail and four target sites;
nine primary files unchanged, disposable clone removed. Do not repeat these
source shapes without new independent evidence. Joint source/compiler sharing,
initial constant1, effect outgoing join and310/409 sharing remain open.

The preceding selected changes replace200/223's signed input-product<1 and
214's signed resource482<1 with<=0, recovering target TEST/JG and WORD-zero
comparison operands.572/573 still compare against1 and retain<1. The first
two edits change only six bytes in the prior59462-byte section; the214 edit
then reduces the section to59458 and regroups sequence tails.214 leaves the
wrong shared201/214/567/568 CALL; its19 sequence sites are now local, as in
the target classification. Candidate{201,567,568,572,573,650} still differs
from target{201,224,562,563,567,568,650}. Target retains two resource tests
versus one candidate; no original-source or exact claim follows.

Final-source native0/10720 covers all three edits through real input/resource
helpers, including signed WORD wrap, nonoverflowing DWORD endpoints, zero
from either input factor and both real4/8 resource costs. A further0/432 on
the six regrouped actions reaches actual target shared CALL621734. Wrong
resource<0 detects1560/3520. The intermediate two-gate source's wrong product
<0 calibration detects594/7200 (200324/223270); that negative receipt is
explicitly historical, not a final-source replay. Final native/configured
whole sections agree. Fresh CFG/home/owner diagnostics follow below.
All six73-byte atan2 preparations retain target equality, at current candidate
628D55/628F64/629178/6293F1/62D822/62D9A9. Two sequential readonly768MiB/twoCPU
Ghidra clones attest the zero tests, unchanged572/573 tests and cost calls;
all nine primary files unchanged, both disposable clones removed. Initial
constant1 still loads late; first+64/620984 and the full95% goal persist.

The preceding a406a5e5 change captures a fresh raw direction DWORD inside each
of the three independent object998 branches, using signed-char conversion
only for the X offset. Target MOVZX/MOVSX dataflow now appears explicitly;
first spawn CALL aligns at620A0C, but target EDI=1 still precedes the outer
guard while candidate EBX=1 loads later. A named variant1 used by the flag
and all three calls is whole-section neutral and unselected. The section shrinks16 bytes
to59462; compiler regrouping also affects later vslot8 tails. No claim that
all suffix bytes stay unchanged. At that checkpoint, whole-entry native0/7086 covers5760
raw float/direction cases,336 guards and990 compact110-action routed entries.
Object998 is reached5832 times,648 per active action; wrong signed outgoing
direction detects2304/5760. Geometry cases stop at the real465190 entry;
post-spawn mutation/continuation and unmasked exceptions remain unproved.
Native/configured whole sections agree. All six73-byte atan2 preparations
still equal target at candidate628D45/628F54/629168/6293E1/62D825/62D9AC.
Read-only Ghidra re-attests the guard and three81-byte preparations, initial
constant and raw/signed uses; nine primary files unchanged, clone removed.

The preceding d6a5f127 checkpoint added real310/409 animation callbacks.
Their shared advancement site now lies at6245DD versus target624612/625893;
AL return width is already correct. The explicit409 failed-advance return
control was whole-section neutral at that checkpoint and unselected.
Its native0/1992 observed120/48 successes and912 normal RETs per action;
wrong409 action10 detected48/960. Original frame/block callbacks, real frame
application,13 byte pins and Sprite ECX/EAX guards executed without return
substitution or executable/vtable patch.436760/40C100 remain unclassified.
That runtime report is scoped to d6a5f127 and is not a fresh current-source
replay. Frame format2/nonzero texture/error/unmasked/final-backend behavior
remains unproved. No original-source or compiler-barrier conclusion follows.

The preceding d6a5f127 checkpoint's560/561/562/563 extension gives all six atan2 sites identical
complete73-byte target preparations. Four new spans start target628F2E/
62913B/62933E/6295A8 versus candidate628D55/628F64/629178/6293F1.
`emit_813_aimed` retains its rounded X local and reads peer Y as a field
reference in the call. Only80 bytes change from priorc8140ff0; every other
complete-section byte stays identical. Fresh whole-entry native0/5840 covers
the four affected actions, including480 real atan2-entry stops,120 each.
Wrong unsigned-facing calibration detects160/480. Argument fixtures use
ground Y0 versus airborne Y100 so real surface callbacks are respected.
Native/configured sections agree; Ghidra re-attests all four spans and leaves
nine primary files unchanged. Source/type/ABI provenance and whole exactness
remain unproved; this adds no exact or partial credit.

The precedingc8140ff0 checkpoint made730 retain its rounded X local and read
peer Y through a field reference
in the atan2 call. Target62DAC2/62DC40 and candidate62D835/62D9BC have identical
complete73-byte argument preparations, including the reused initialESP+10 home
and outgoing-X-before-Y order. These are internal diagnostics, not functions
or exact credit. Only40 bytes in the entire59478-byte canonical section change
from priorc9a1c3e4; every byte outside those two preparations stays identical.
Fresh whole-entry native0/4960 includes3840 real aim/clamp continuations and
1120 actual atan2-entry stops for signed zeros, cancellation, subnormals,
maximal finite, Inf/NaN geometry and five signed-byte facings under PC53/64.
Wrong unsigned-facing calibration detects368/1120. Native/configured sections
are identical. Earlier direct-expression/value-accessor controls add temporary
homes; direct field expressions instead choose FIMUL. None is selected.
Ghidra re-attests both preparations and the185-byte clamp interval; all nine
primary files unchanged and disposable clone removed. Five730 facing sites
versus four target remain unresolved.

The common height-ST0-to-Y / velocity-clear / return tail now has exactly
its target incoming set:6/7/8/9/220/307/308/309/404/406/414/415/416/417/795/797/798.
Target calls621044/621051 correspond to current candidate62ECAB/62ECB8. Source retains
all preceding callbacks and797/798's post-callback X=480/800 stores before
height lookup. The private inlined fan routine reports pending restoration
for404/406 so its callers can join; ground400/401/402 retain completed behavior.
No original helper return ABI/callable boundary is claimed. Public ABI/layout,
vtable, shared declarations/profiles/relocations remain unchanged; no local
CALLs are emitted. A label-inside-case8 control still placed the shared tail
near the end, grew32 bytes and remained nonexact+64; unselected.

Current source CRLF SHA256:
1bf7fcd437528a871e5297100389420fc000e791b6c0bdd54bd281303178a503.
Normalized full section59458 bytes, SHA256:
347e4d6cf2820eef3559e53f6dd2bab14cffe2065343113d4863875ffd00917b.
Candidate14990 reachable instructions /58296 instruction bytes in58302-byte
span, six internal alignment bytes,1156 following alignment/metadata bytes
(metadata starts58304),128 RETs,862 ordinary/177 register CALLs,33/42/35
tables, no local CALLs or external tails. Target865/177. Owner diagnostics
8/109 (2/4/5/10/204/215/303/696), not matches. Register-call count agreement
does not establish matching incoming sets or semantics. Frame400hex/84 natural
payload homes retain84 singleton/bijective conditional incoming-action/
physical-ordinal constraints,57 identity,182 spawn calls/190 action-site
records. Target/candidate pre-epilogue PCs14870/14734, states16959/16898.
These are not payload-value/path proofs.

Priorc9 source whole-entry native0/3252 covers the17 actions plus ground400/401/402:
2566 RETs and686 first backend entries per side (13 effect/511 action/
8 next-sequence/120 sequence/34 object),2040 target-root instructions.
Native/configured whole sections normalize identically. Inverting404/406's
caller status tests detects186/284,93 per action, on the matching subset.
Real helpers run without result replacement. Landing paths stop at their
first actual action/sequence callback; the subsequent common tail is static
instruction/flow evidence, **not post-callback native proof**. The bad-status
control instead detects erroneous restoration on normal completed paths.

At the preceding common-landing checkpoint, direct Ghidra re-attested identity,
entry, mapped .text, language/compiler/root and the complete28-byte tail in
one read-only768MiB/two-CPU clone. All nine primary files unchanged. Wrong-
image IDA remains rejected. Physical layout and other sharing still differ:
advancement107/106, height19/18, clear30/28, facing9/10 target/candidate.
Expanded ordinary counts differ only at730's five facing sites versus four;
count/incoming-set agreement is not value or exact proof. Earlier412/418 and
six-action effect groups retain their exact incoming sets in the current CFG.

The preceding effect-direction investigation at sourcec9a1c3e4 retained it unchanged.
Target416/417 read byte104 once: zero-extend for the outgoing DWORD, then
sign-extend the same low byte for the47-pixel offset. Keep both coordinate
float round trips. The expanded five-byte-boundary fixture passes0/2664 from
the real root; wrong outgoing sign extension detects624. Native and configured
whole sections remain identical. Early int capture retains six-way sharing
but grows32 bytes and still spills X. Direct branch argument expressions
remove that spill but split the group into five calls; explicit Y local is
byte-neutral. A genuine GL/LTCG control reuses43/44 objects, still emits58
whole-root effect sites and remains nonexact+64. All controls are unselected;
there is no general compiler/LTCG-barrier proof. Direct read-only Ghidra
attests all six preparation spans; nine primary files remain unchanged.
See the linked direction note for hashes, scope and reproduction. Retain the
current native proof objects and small genuine-provider cache; discard the
unselected root/link artifacts. No accepted-unit matrix was replayed.

Prior source-scoped evidence, retained in selected source where applicable:

- Source0e8c5e26 [frame7 boundaries](IKU_FRAME7_BOUNDARIES_2026_10_17.md):
  225<=7 /408>=7 match target CMP7/JG and CMP7/JL. Native0/512, wrong gates48.
  Neighboring320/321/322 gates already agreed; no mechanical predicate rewrite.
- Source4e852076 [frame4/event ownership](IKU_FRAME4_EVENT_OWNERSHIP_2026_10_17.md):
  305>=4 keeps4 live across calls and restores separate305/696 events.
  TargetBX/candidateDI;305 remains nonexact. Native0/256, wrong>=5 gate24.
  The180-byte696 physical owner remains diagnostic-identical in current source.
- Source83311acf [412/418 landing](IKU_LANDING_SHARED_CONTINUATION_2026_10_17.md):
  both share clear/height/vslot0C sequence2/return with exactly{412,418}.
  418's627256 JNZ enters CALL626080 after its ownECX setup. Native0/722,
  wrong sequence3 control10. An unselected RTM control remains nonexact+64;
  changing compiler alone did not resolve that checkpoint.
- Source69c43bf5 [effect62](IKU_EFFECT_SHARED_CONTINUATION_2026_10_17.md) and
  [sequence exits](IKU_SEQUENCE_EXIT_PHASE_2026_10_17.md):416/417/565..568 share
  one effect/next-sequence tail; native0/1584, wrong height536. 562/563/730
  native0/1728, wrong time gate16. Candidate still spills X at the effect join;
  target carries X into the outgoing argument store. Preserve416/417's explicit
  float round trip and565..568 raw-X signed zero. Wrappers/rounded double
  carrier and the17-byte duplicated sequence-tail label control are unselected.
- Source69c43bf5 [genuine link/visibility](IKU_PROVIDER_VISIBILITY_2026_10_17.md)
  closes59504 bytes/898 HIGHLOWs/863 ordinary calls with real game/SDK/CRT.
  It is not a link of the latest source. [MT state](IKU_MT_CALL_STATE_2026_10_17.md)
  isolates MT TU visibility and16 live-x87 call sites; noinline leaves the59488
  raw envelope identical. Actual helper native0/10016, different-seed2/2.
  Keep ordinary MT opacity; original flags/pass/formal ABI remain unknown.

On prior4e852076, /Z7 is whole59550-byte neutral; /Zi failed with PDB-manager
C1902 and has no comparison result. On-disk components report SP1 .762;
active-manager failure remains undiagnosed. No canonical compiler change.
Older native/link results remain scoped to their hashes; do not habitually
replay them. Retain the small genuine-provider cache and current proof objects.

Other contracts: [conditional exits/height](IKU_LANDING_ARGUMENT_OWNERSHIP_2026_10_17.md),
[glide](IKU_GLIDE_EXIT_OWNERSHIP_2026_10_17.md),
[steering](IKU_STEERING_CLAMPS_2026_10_17.md),
[virtual ABI](IKU_VIRTUAL_CALLS_2026_10_17.md),
[random/float](IKU_RANDOM_FLOAT_TYPES_2026_10_17.md).
Preserve unsigned602/live X addition,310 double increment,780 widened0.95f
truncation, ordered NaN, raw-X signed zero, branch-local730 limits6/4/5,
scratch receiverthis+4 and ftol ST0->EAX32. Header already uses native virtual
methods. Do not repeat source/flag controls without new independent evidence.

Next:730's duplicated facing suffix, initial constant1 lifetime, the effect
outgoing-argument join and310/409 advancement sharing. Do not repeat isolated
Y/accessor controls; their independent lifetime effects are now resolved.
Original C++/TU/inheritance/optimizer, full value/payload/exception equivalence
and post-backend behavior remain unknown. No accepted shared-unit change or
cold aggregate replay. Remove superseded private controls, objects and clones.

## Shared Fighter linked checkpoint

`Fighter_update_common_action_state @ 4740C0` is the current large shared root.
Its local20-byte checked container now uses real VC8 `std::deque` with the
94-byte target4399C0 member exact before/after a genuine link. The complete
ordinary10801-byte canonical section tail is unchanged; whole10219 comparison
remains nonexact+14/53 of66 diagnostic owners. Fresh animation smoke is0/72;
the older6048 animation and14208 motion matrices are not rerun.

The new public link probe closes24 real source providers plus pinned CRT/SDK
libraries, with27/28 selected dependency addresses exact; the retained
resource-handle lookup417800 is explicitly nonexact. Same-target source-view
aliases and12 attested non-executable data bindings are diagnostic, not proof
of original C++ declarations or runtime equivalence. Both linked switches and
all2842 instructions/10233 callable bytes close, with three alignment bytes.
The linked entry adds an aligned EBP frame and still uses ADD-negative in
place of target SUB. No float/flag change is retained. Remaining work is joint
clamp/sequence ownership and dispatch lowering with target rounding intact.
See [the source/linked ABI checkpoint](COMMON_FIGHTER_LINKED_ABI_2026_10_17.md).

## Aya CPU decision checkpoint

`Aya_update_cpu_action_policy @ 6126E0` now has complete target-reviewed source:
16032 callable bytes /4097 instructions, six validated switches and no
unresolved transfers. A strict bridge checks all4069 instructions/15910 bytes
of the default CPU target plus all632 metadata bytes. Aya adds only two61-byte
command branches, recovering ordered distance>320, native RNG thresholds20/2,
signed resource>=400 and command728 bits400/200hex. Direct Ghidra saves and
independently reads back void/ECX/no-stack-argument ABI, all4097 instructions,
switch refs and branch comments, with target bytes unchanged.

The selected source now reads signed counter764 through a natural inline
field accessor at four predicate paths. Action300's complete30-instruction/
141-byte owner and action305's24/111 owner recover their independent signed
WORD bounds; action320's0..90 and action404's0..10 guards also return. Shared
cleanup edges make action200 identical as well. All prior14 identical owners
survive, giving17/41 diagnostics. Whole16032 comparison remains nonexact+12E,
metadata16088 and section tail16713; no partial or exact authored credit.

Fresh native checks pass0/4164 counter/mode/resource/geometry,0/5000 finite
and0/470 command plus0/368 height cases through genuine RET, including native target-confirmed
positive stores. An unsigned accessor-return control fails32/32 negative
counter cases. Broad counter and stored-policy-roll accessor changes are
rejected despite higher local counts or some recovered arms; they disrupt
other observed instructions and ownership. Original source spelling/inlining
phase remains unknown. See [the current counter source checkpoint](AYA_CPU_COUNTER_READS_2026_10_17.md).

New policy0 native checks pass0/16160 with every target roll0..100, all1486
reachable target instructions and all38/43 sampled target/candidate selector
sites. Genuine seed1472677 produces third rawFFFFFFB6 and the rare roll100,
exercising the formerly unseen candidate61556F. Caller tracing records49
many-to-many pairs: the extra static calls are a joint split/merge ownership
problem, not five independent missing source statements. Timer setters and
lifted joins are full16713-byte-tail neutral; height accessor/predicate controls
are rejected. The selected source remains17/41/nonexact, with no new exact
credit. See [the native tail/endpoint evidence](AYA_CPU_POLICY_TAILS_2026_10_17.md).

Eleven opponent pointer carriers and the real checked VC8 deque remain.
Full genuine link inspection distinguishes the79-byte private EDI/index-zero
deque specialization from target4399C0's94-byte ECX/RET4 interface. An actual
SDK COFF instantiation replays94 bytes before and after linking. With the
current source and guarded all-float diagnostic, the latter context closes
16056 bytes /4079 instructions through all six switches, but retains119
selector sites versus target114 and five nested table destinations versus
six. No float/flag/partition control is promoted to the acceptance profile.
Remaining Aya work is complete control/float lifetime and shared store/x87 tail
matching with that verified dependency ABI. Prior evidence:
[linked ABI](AYA_CPU_LINKED_ABI_2026_10_17.md),
[source/dependencies](AYA_CPU_NATIVE_DEPENDENCIES_2026_10_17.md), and
[initial Aya root](AYA_CPU_ROOT_2026_10_17.md).
No shared C++ header/global ABI/relocation/profile or accepted-unit change.

## Shared Fighter action checkpoint

The shared root `Fighter_update_common_action_state @ 4740C0` remains a stable
10219-byte checkpoint used by all15 roster action roots. It retains53/66 diagnostic
owners and remains canonically nonexact+14, metadata+2838 and section tail10801.
The source's7A4 method view now names signed frame limit+14C from the already
exact62-byte frame-advance helper; layout and compiled bytes are unchanged.
A new native motion oracle executes all six original dependencies without
result hooks:0/14208 differences through genuine RET, comparing the actor,
calls, conversion inputs, stack and control word. It visits403/2799 target
instructions under flat-stage/unexpired-frame inputs, not complete gameplay.
A once-rounded action159 control changes velocity by one ULP and is detected;
wall-event inputs fail the explicit context guard. That is the earlier
[native motion checkpoint](COMMON_FIGHTER_NATIVE_MOTION_2026_10_17.md), not
a newly rerun matrix.

The previous common-root batch executes the original animation virtuals, frame/tree lookup
and untextured sprite updates for actions73/75/88:0/6048 sampled differences
through genuine RET, including actor/call/argument/conversion/stack/callee-save/
CW checks. It visits159/2799 target instructions in an explicit resource
fixture; coverage is not added to the old motion count. A NaN zero-test control
produces3/72 differences; missing wall-action context is rejected. Whole-root
comparison retains the same canonical window and53/66 owners. Complete-handler
inline extraction is neutral under nested dispatch and fails the required
owner topology under flat dispatch. See
[the native animation evidence and remaining blocker](COMMON_FIGHTER_NATIVE_ANIMATION_2026_10_17.md).

All2799 raw instructions and eight receiver-domain virtual tails remain
reviewed. Direct Ghidra saves/reads back the ECX/no-stack ABI,52 named data
fields plus the vptr, and helper/receiver evidence while preserving target
bytes. The next task is simultaneous clamp/sequence physical ownership and
SUB lowering with the required rounding retained. Failed source-order,
normalized-index, reference-clamp, complete-handler inline and earlier FP
controls are not retained.
No exact or partial byte credit. The prior receiver/control details remain in
[the complete common-root record](COMMON_FIGHTER_ROOT_2026_10_16.md).

The default CPU root `5F1F80` is a stable15910-byte source checkpoint. Its signed
policy selector and action300 store arms remain intact; whole comparison is
nonexact+12E, metadata+3E38, section tail16553 and15/41 diagnostic owners.
Earlier native controls have0/1408 boundary,0/5000 finite,0/16000 policy0 and
0/368 height differences. These are historical checkpoint results, not rerun
in this common-root batch. New counter320 controls preserve signed compares
but move the shared store/branch ownership; they are discarded. See
[the CPU source checkpoint](CPU_SOURCE_OWNERSHIP_2026_10_17.md). No unrelated
accepted-unit or aggregate cold replay is claimed.

The receive chain is fully implemented/linked; the connection checkpoint
retains target-backed handoff/DNS lifetimes and isolates a genuine84-byte
linked residual beginning+14C. Direct clear and RTM controls were negative.
Its ordinary524-byte connection and accepted14-byte callback are unchanged.
See [the connection record](NETWORK_UDP_CONNECTION_2026_10_16.md).

## Receive-chain link closure: connection and handshake worker

The complete UDP receive/connection subsystem is source-present.
`NetworkWinsock_start_connection @ 415340`
(160 instructions/542 bytes) and its actual native worker
`NetworkWinsock_connection_thread_entry @ 415D60` (286/1009) now have complete
source in the receive TU. Persistent request ownership/FFFF reuse, numeric/DNS
endpoint selection, stack handoff acknowledgement, auxiliary UDP socket,
endpoint/port probes, candidate rotation and state2/3/6 retries are closed.
A genuine mixed COFF/LTCG image now links the entire receive/request/connection
chain with actual peer-removal, acceptance and platform-thread implementations:
**zero missing link inputs**, with no source stubs or executable ABS bindings.
Preserving the real connection entry's external UI call surface restores its
linked542-byte body; ordinary connection524 and worker945 remain nonexact.
A target-backed two-native-packet control is992/1009 with frame860 versus870,
so the original storage is still unresolved, without added padding. The linked
callback remains a canonical14-byte diagnostic, and its configured ordinary
accepted replay is exact. No new exact credit. Ghidra types/ABI/body metadata
are saved and independently read back. The next major blocker is canonical
comparison of the fully linked receive roots: native EH/GS data ownership,
switch metadata and source packet storage, rather than missing implementations.
See [the connection, worker and real link evidence](NETWORK_UDP_CONNECTION_2026_10_16.md).

## UDP request and peer admission

`NetworkWinsock_receive_request @ 415560` now has complete source in the real
receive TU. All410 instructions/1355 bytes close; running, dual16-byte key and
peer-limit checks precede nested peer/callback guards. Existing peers receive
another acceptance; full capacity chooses the lowest positive peer report and
inspects at most four circular positions; free slots route through callback
slot+10 and preserve accept/reject/retry behavior. Packed reply holes, unused
redirect entries and peer report+1C remain untouched. Current observed reply
storage81 covers header13 plus the two known providers'68 bytes. Source is
1265/1355 nonexact; a genuine41C packet-type control is1281/1355, with frame460
versus target468, and is not retained as an invented storage claim. Private
key148 and checked access33 are canonical byte controls but remain in origin
review, without authored/source/exclusion credit. SDK IsEqualGUID provenance
cannot be distinguished from an equivalent wrapper. The actual native tree
insertion stage returns12 bytes and its iterator first component is consumed.
At that checkpoint the mixed-source link stopped on connection415340; the
connection/worker section above now closes all genuine inputs. No source
stub or executable ABS binding is used. Callback14 and all four affected
Winsock runtime helpers retain exactness. Ghidra request/control ABI metadata
is saved/read back. See [the policy, storage and provenance evidence](NETWORK_UDP_REQUEST_2026_10_16.md).

## UDP receive-loop source

`NetworkWinsock_receive_loop @ 41D7C0` now has **complete source**, together
with its real callback and file-local lookup/rejection/endpoint-list helpers.
The364-instruction/1424-byte target closes through its14-entry switch; the56
metadata bytes and four EH cleanups remain separate. Source main1456 plus56
metadata bytes is nonexact, first at+0x16 on frame470 versus890. Native peer
map/vector views, all opcode gates and manual versus scoped locks are
preserved. The actual caller naturally generates EAX lookup and ESI rejection;
no register facade or synthetic caller is used. Minimum21-byte forwarding
reply storage preserves its four untouched tail bytes. The accepted callback
stays14/14 with the full source and GS enabled. A genuine mixed-source LTCG
attempt resolves actual acceptance/peer-removal bodies and then stopped on missing
connection415340; the connection/worker section above now closes all inputs. Original reply capacity,
endpoint-helper/STL boundaries and TU remain open. No new exact credit.
Direct Ghidra owner types and complete caller ABI are saved/read back. See
[the opcode map, source and link boundary](NETWORK_WINSOCK_RECEIVE_2026_10_16.md).

## UDP connection acceptance

`NetworkWinsock_accept_connection @ 415AB0` now has complete source in
`src/network/NetworkWinsockAccept.cpp`. Its observed ECX sender, EDX owner,
stack packet and RET4 physically fit a normal fastcall definition, with no
register adapter or synthetic caller. The complete69-instruction/223-byte
handler copies the sender and clears the probe counter under the endpoint
lock, invokes callback slot0 under a nested callback lock, and changes
state3 to0 before reverse guard destruction. The packed12-byte packet view
preserves DWORD code+4, WORD length+8 and payload+C. Ordinary223/223 remains
nonexact on incoming-register saves and EH-state scheduling. A genuine
resolved223-byte LTCG control reproduces both target EH-state windows but
retains reversed entry saves; native linked EH/GS replay is not supported.
Original standard/private spelling and TU remain unknown. No exact credit
is added. Direct Ghidra metadata/types are saved and independently read back.
See [the ABI, EH facts and focused controls](NETWORK_UDP_ACCEPT_2026_10_16.md).

## UDP probe worker

`NetworkWinsock_probe_thread_entry @ 416F40` now has complete ordinary
stdcall source in `src/network/NetworkWinsockProbeThread.cpp`, retaining the
initializer's existing callback symbol. Raw closure covers201 instructions /
682 reachable bytes plus ten skipped internal alignment bytes through RET4.
It sends the five-byte opcode4 report, preserves dynamic checked peer-vector
accesses and manual locks, removes peers on the old counter>=10, transitions
primary state0 to6 on the same threshold, and uses a private local auto-reset
event for pacing. Selected minimum-storage source is664/692 nonexact. A real
41C pool-packet control is670 bytes; genuine fully resolved mixed COFF/LTCG
links with actual peer-removal source retain664/670. Original local storage,
aligned GS frame and report-value meaning remain open, with no new exact
credit. Direct Ghidra owner/peer types and full callback ABI/body are saved
and independently read back. See
[the behavior, callback registration and source controls](NETWORK_UDP_PROBE_WORKER_2026_10_16.md).

## UDP shutdown preparation

`NetworkWinsock_prepare_udp_shutdown @ 4130D0` now has complete source beside
its real shutdown caller in `src/network/NetworkWinsockShutdown.cpp`. The
46-instruction/149-byte target sends opcode0B under the native endpoint lock,
removes each dynamically counted peer and resets state144 to1. A genuine
file-local normal C++ helper naturally recovers the private ESI entry; the
existing caller remains175/175 exact. Preparation115/149 remains nonexact
because the target aligned0x42C GS packet-storage frame is unresolved. The
selected source uses only the established transmitted byte. Reusing the real
41C pool-buffer type produces150 bytes, and a fully resolved mixed COFF/LTCG
control with actual peer-removal/thread sources retains that150-byte shape;
it also encounters unsupported native GS-cookie data replay. No larger
buffer, padding or synthetic callee is retained, and this is no new exact
credit. Direct Ghidra owner/peer types, ESI preparation versus ECX caller
storage and complete extents are saved and independently read back. See
[the behavior, source controls and remaining storage question](NETWORK_UDP_PREPARE_SHUTDOWN_2026_10_16.md).

## UDP initialization and native worker ownership

`NetworkWinsock_initialize_udp @ 412E10` now has complete ordinary C++ source
in the same Winsock runtime/error TU. Full raw CFG closes149 instructions /
441 bytes, reached by two independently exact MenuConnect callers. Native
peer-vector assignment, duplicate16-byte key copy, Winsock/socket/bind failure
paths, prior-buffer and token cleanup, three native thread starts and the
first two priority15 calls are all implemented. Target only establishes AL0/1;
source bool is a hypothesis, and the older UI int-forwarding declaration is
not changed without reviewing its consumers. The ordinary POD-source result
is439/441 nonexact on aligned GS frame, private vector interface and API
pointer allocation. A full file-local bind helper naturally reproduces its
68-byte ECX/EAX body, now separately accepted as
`NetworkWinsock_bind_udp_socket @ 413080` at **68/68 canonical exact**. A resolved LTCG attempt stops on missing real callback
and wait link inputs; no replacement bodies or executable ABS bindings are
introduced. This neither proves LTCG necessary nor proves it would match.
Adding the actual caller preserves all three accepted runtime helpers at
148/47/84. Supported owner/key/peer types and physical caller/callee storage
are saved and independently read back in direct Ghidra. See
[the complete behavior, controls and remaining boundary](NETWORK_UDP_INITIALIZE_2026_10_16.md).

## Winsock reference lifetime

`NetworkWinsock_acquire_runtime @ 41DDC0` is canonical **148/148** from ordinary
C++ and its complete file-local error reporter. Full switch-resolved CFG owns
40 instructions; all103 adjacent dispatch bytes also replay exactly and earn
no authored credit. The zero-reference path calls WSAStartup twice with
version2/the same native WSADATA, ignores the first result and dispatches the
second failure through five observed texts. Success increments the shared
count; all paths release the native lock. The private helper naturally uses
ESI without an ABI facade. `NetworkWinsock_show_error @ 41DEF0` is also canonical **84/84**, with
its complete256-byte GS buffer and native formatting/dialog calls. All three
reviewed callers discard incidental EAX. No external private-register facade
is used. Direct Ghidra metadata is saved and independently read back.
`NetworkWinsock_release_runtime @ 41DEC0` is also canonical **47/47**. Its
10-instruction body decrements only a positive unsigned count and calls
WSACleanup only on transition to zero under the same lock. Adding this real
member of the source TU preserves the acquisition at148/148.
See [the complete control flow and comparison](NETWORK_WINSOCK_RUNTIME_2026_10_16.md).

## UDP client sender and real private-helper context

`NetworkWinsock_send_loop @ 416DB0` and its real native callback `416D90`
now have complete source in the same sender/helper TU. Full raw CFGs close
395/18 bytes. The worker creates/waits/closes its event, drains the locked token
deque, looks up packets, sends only unexpired packets and recycles every valid
token. Packet+14 now has the observed `timeout_ms_14` meaning, with zero
disabling expiry. The actual pinned SDK import library resolves the target's
ordinary sendto E8/thunk; strict source/target ordinal, symbol, library, thunk
and IAT checks join linked provenance. The complete worker is395/395 nonexact
on callee-save shrink wrapping; the callback is16/18 nonexact on scratch-frame
reservation. Their private ESI interface arises naturally from real source.
No new exact credit is added. Fresh focused replay preserves scene281,
pool98 and release167; all155 local CI tests pass. Original frame/optimizer
context remains open. See [the complete behavior and comparison evidence](NETWORK_UDP_SEND_WORKER_2026_10_16.md).

`NetworkWinsock_send_server @ 416B60` now shares the complete sender/helper
source in `src/network/NetworkWinsockSendClient.cpp`. Full raw CFG closes
168 instructions/all548 bytes. It checks the32-byte peer record before any
allocation, returns immediately for slot+10==-1, and rechecks the endpoint
under peer lock+120. Active requests enqueue opcode0D with the same token
replacement policy as the client. Source uses void: the inactive path has no
established meaningful EAX result, so no synthetic return value is added.
Ordinary548/548 remains nonexact at+42 on the private acquire call; the formal
two-sender mixed unit gives644/548 nonexact on inlining/context. All relocations
resolve, and the accepted shared release remains167/167 with both genuine
senders exported. Source layout assertions now include peer vector+108 and
lock+120. See [the behavior, ABI and full comparisons](NETWORK_WINSOCK_SEND_SERVER_2026_10_16.md).

`NetworkWinsock_send_client @ 416990` has complete source in
`src/network/NetworkWinsockSendClient.cpp`, alongside the actual acquire and
release member definitions. Full raw CFG closes145 instructions/all464 bytes.
Type0E packet/options/timestamp, locked endpoint copy, payload/size, native
token deque and optional old-token replacement precede SetEvent and its return.
Ordinary source is **465/464 nonexact**, with all relocations resolved.
The real caller makes LTCG naturally recover stack self for acquisition and
EAX self for release. Source stays normal C++ members; no private ABI facade
or dummy caller is added. Sender inlining still differs: native token push_back
is out of line in the target, but561 bytes with retained-source/list context.
See [the complete sender and context controls](NETWORK_WINSOCK_SEND_CLIENT_2026_10_16.md).

`CHandleManager_release_token @ 405200` is now canonical **167/167** in
`cross-v106a-network-winsock-send-client`. Full raw CFG independently closes
63 instructions; nine callers include two exact Title resource methods as well
as the UDP sender. Shared game policy checks low16 slot/high16 generation,
zeros matching generation and appends the free index under a manual lock;
it does not destroy payload. The source remains an ordinary C++ member.
The mixed link uses the existing ordinary unsigned-list instantiation and
naturally generates the private EAX receiver/RET4. A narrow `private_from`
contract verifies a unique source-owned, nonexported/nonaliased map entry,
fully closed source/target caller bodies and their unique direct E8 edge
(`416B01` in the original). Full callee CFG, calls, IATs and all167 bytes are
compared. The sender remains561/464 nonexact; selecting the accepted helper
still validates its real caller. See [the exact shared helper and contract](HANDLE_MANAGER_RELEASE_2026_10_16.md).

The original TU and token-queue inlining remain unresolved. Continue with the
remaining real UDP callers rather than adding fake callers or
ABI facades. Replay only affected accepted units during iteration; this batch
adds167 authored exact bytes without a fresh aggregate cold replay.

## UDP owner and packet-pool lifetime

`NetworkUdpPacketHandleManager_acquire @ 417660` now has complete native
C++ source in `src/network/NetworkWinsockSendClient.cpp`. Full raw CFG closes
125 instructions/all410 bytes. Two authored send paths `416990`/`416B60`
pass the pool+17C and output token on the stack. The source preserves zeroed
fresh packets, stable pointers, LIFO free-slot reuse, checked vectors and
16-bit slot/generation writes under a scoped lock. Reused payload is retained.
The focused ordinary candidate is **427/410 nonexact**, with every relocation
resolved. Ordinary GS-minus387 and resolved LTCG540/486 controls also differ;
the latter recover alignment but change inline/helper context and keep ECX
self. Its new real caller now naturally recovers stack self under LTCG, but
the helper still differs on inline/EH context. Keep the real member definition
and recover the remaining TU context rather
than adding private ABI facades. One new nonvirtual declaration leaves layout
and vtable order unchanged; a fresh pool-destructor rebuild remains98/98.
Ghidra physical stack parameters, token/payload types and full main extent
were saved and independently read back. See
[the complete behavior, EH and controls](NETWORK_UDP_PACKET_ACQUIRE_2026_10_16.md).

`NetworkUdpPacketHandleManager_dtor @ 413820` is canonical **98/98** in
`cross-v106a-network-udp-packet-pool`. RTTI identifies
`CHandleManager<NET_PACKET_UDP_BUFFER>`; packet allocation and native members
establish the real0x64-byte layout. Ordinary C++ member destruction matches
after a resolved mixed COFF/LTCG link: an ordinary VC8 `std::list<unsigned int>`
instantiation preserves its normal helper ABI, while the packet deque retains
the target's private ESI helper. Typed primary-vtable replay checks source and
target RTTI/entry identity plus exact HIGHLOW fields. Compiler-library source
and generated wrappers receive no authored credit. The original TU remains
unknown. See [the source, ownership and strict evidence](NETWORK_UDP_PACKET_POOL_2026_10_16.md).

The same source's constructor `413780` remains nonexact: the target has a
private stack receiver/RET4, while source keeps an ordinary C++ constructor.
Its linked EH surface is still unsupported. The owner is original `CNetworkUDP`,
source view `NetworkWinsockState314CtorView`: corrected native peer multimap+FC,
real packet manager+17C and separate owner event+1E0 give **354/357 ctor** and
**398/333 dtor**, both nonexact. The second tree+15C still lacks a concrete type.
Continue from native container/lifecycle context; do not invent private ABI
facades. Ghidra types, full extents and parameter storage were saved and read
back after independent target attestation.

Fresh native source also proves that owner scalar deleting wrapper `412C80`
is compiler-generated. Its canonical30/30 remains a configured witness, but
its former authored match/source credit is removed. Packet-pool wrapper
`4138B0` also reproduces30/30 and retains its prior compiler exclusion.
This batch adds98 authored exact bytes and removes30 compiler bytes: net68.
Revalidate only affected units during iteration; aggregate exact totals still
require a separate cold `--all` replay.

## Winsock receive-thread boundary

The related `NetworkWinsock_remove_peer @ 413170` and
`NetworkWinsock_find_peer @ 412A60` now have complete native vector/multimap
source in `src/network/NetworkWinsockPeerRemoval.cpp`. Full raw CFGs close
489/167 bytes and141/59 instructions. Exact server caller44F538 independently
establishes removal ownership/receiver; endpoint lookup is source-defined in
the same TU. Focused candidates are **440/489** and **162/167 nonexact**.
The target's large packet-storage/aligned GS frame and private compiler/iterator
context remain unresolved. One-byte protocol content is preserved without
guessing a larger buffer. A real LTCG control naturally generates lookup's EAX
receiver, but changes iterator inlining and still differs. Keep the paired
source together, retain real lock scopes and all five vector checks, and do
not replace the private entry with an external ABI facade. See
[the behavior, full comparisons and negative controls](NETWORK_WINSOCK_PEER_REMOVAL_2026_10_16.md).

`NetworkWinsock_receive_thread_entry @ 41D7B0` is canonical **14/14** in
`cross-v106a-network-winsock-receive-thread`. Native CreateThread registration
at412F7F passes the Winsock owner and stores worker+64/+68; ordinary C++ forwards
the pointer in ECX, calls the loop, returns zero and pops the parameter.

## Accepted exact unit: Application message loop

`Application_run_message_loop @ 0x00408120` is canonical **177/177** from
`src/platform/ApplicationMessageLoop.cpp`, unit
`cross-v106a-application-message-loop`. Full CFG closure reaches65 instructions;
a real28-byte MSG frame, running+4C, native message dispatch and the D3D idle
check/reset/four-millisecond event wait reproduce the complete callable on the
first source probe. All eleven relocation fields replay. Four new imports and
a dedicated HRESULT+1A4 mapping preserve existing backend permissions and shared
contracts. Ghidra metadata was saved/read back after independent target
attestation. See [the behavior and exact evidence](APPLICATION_MESSAGE_LOOP_2026_10_16.md).
Bootstrap and both singleton workers now have complete nonexact source;
WinMain retains its separate four-byte frame residual.

## Source checkpoint: WinMain

`WinMain @ 0x00665810` now has complete source in `src/platform/WinMain.cpp`,
unit `cross-v106a-winmain`. Raw CFG closure covers201 instructions/all695 bytes
through RET16. CRT ownership, version/archive strings, RTTI-backed scene/fade
allocations and exact option/shutdown callees establish authored identity.
The complete VC8 candidate is695/695 and differs in only eight stack-frame/home
bytes: target reservation270 versus source26C. Every branch, call and non-stack
byte agrees. Buffer capacity beyond260 and original frame ownership remain
unknown; no extra buffer bytes, fake local or alignment are added. RTM697 does
not resolve the frame difference. Direct Ghidra metadata was saved and read
back. This is source-present only, without exact credit. See
[the full behavior and bounded residual](WINMAIN_2026_10_16.md).
The message loop is exact; bootstrap `407DA0` is source-present/nonexact.

## Accepted exact unit: Application shutdown

`Application_shutdown @ 0x00407F80` is canonical **245/245** from
`src/platform/ApplicationShutdown.cpp`, unit
`cross-v106a-application-shutdown`. All 82 instructions are reached; its sole
indirect exit resolves to the PE-attested OLE32 CoUninitialize IAT tail jump.
The source preserves four thread joins, two SetEvent signals, explicit scene
locking, virtual scene deletion, CSceneManager/CFade callback shutdown/free,
and IME/subsystem teardown. Existing shared contracts and mappings did not
change. Direct Ghidra metadata was saved and read back after target attestation.
See [the ownership, layout and full comparison](APPLICATION_SHUTDOWN_2026_10_16.md).
The same chain's WinMain and bootstrap `407DA0` are source-present/nonexact.

## Accepted exact unit: Application startup options

`ApplicationStartupOptions_ctor @ 0x00407BB0` is canonical **54/54** from
`src/platform/ApplicationStartupOptions.cpp`, unit
`cross-v106a-application-startup-options`. Raw WinMain and bootstrap edges
establish the 40-byte option value, window/instance and callback pointers,
and graphics/input/audio/IME/cursor gates. Ordinary C++ defaults reproduce the
whole return-terminated extent; no relocation or shared accepted contract
changed. Unknown scalar/flag purposes retain offset names. Direct Ghidra
metadata was saved and read back after independent target attestation. See
[the layout, ownership and comparison evidence](APPLICATION_STARTUP_OPTIONS_2026_10_16.md).
WinMain `665810` and application bootstrap `407DA0` are source-present/nonexact.
Their observed control flow does not grant exact credit.

## Application bootstrap island

`Application_initialize_window_paths @ 0x0040D020` is canonical **137/137**
from the complete caller/private-helper TU `src/platform/ApplicationBootstrap.cpp`.
Ordinary static stdcall source naturally generates the observed ECX instance,
stack HWND and RET4, with a real char260 buffer and GS cookie. Bootstrap
`407DA0`, graphics `4147E0` and audio `418670` also have complete source and
independent authored ownership evidence, but remain **447/472**, **539/547**
and **561/583** respectively. Original frame/argument optimization remains open;
the diagnostic LTCG audio frame changes without reproducing the target ABI.
All four raw CFGs close their full callables. Direct Ghidra metadata is saved
and read back under independent target attestation. See
[the ABI, exact result and residuals](APPLICATION_BOOTSTRAP_2026_10_16.md).
Keep this closed TU together; no shared headers or earlier relocation
allowlists changed.

The native control/graphics COM thread entries `408800`/`408820` are now
canonical **28/28 each** from `src/platform/ApplicationThreadEntries.cpp`.
The same unit now includes scene-creation callback `408840`, canonical
**48/48**, which dispatches manager slot+10 using requested state+B0 and
publishes pending scene+80. Both earlier entries were replayed from the changed
object and remain exact.
Their ordinary Win32 callback signatures reproduce both full callables and
all import/worker relocations. No shared source or mapping changed. See
[the ownership, ABI and exact evidence](APPLICATION_THREAD_ENTRIES_2026_10_16.md).
The graphics singleton worker `4084F0` now has complete source, **401/401
nonexact**, in `src/platform/ApplicationGraphicsWorker.cpp`. Raw normal CFG383
plus table-referenced catch(int)/continuation18 close the entire callable;
the option branch reads startup flag at application+2D. Twenty differing bytes
remain in EH state-write ordering and two register choices. No exact credit
is added. See [the exception, layout and focused comparison evidence](APPLICATION_GRAPHICS_WORKER_2026_10_16.md).
The control worker `4081E0` now has complete source in
`src/platform/ApplicationControlWorker.cpp`, **787/771 nonexact**. Normal
CFG755 plus table-owned int-catch16 close the full771-byte callable. Its
three controlfp_s calls query state, select upward rounding200/mask300 and
reset default9001F; they do not select24-bit precision. Frame, stack cleanup,
tail sharing and EH-state scheduling remain unresolved. See
[the behavior, FP/EH facts and comparison](APPLICATION_CONTROL_WORKER_2026_10_16.md).
No exact credit is added for the worker.

## Accepted LTCG unit: Scene retirement

`Application_scene_disposal_thread_entry @ 408870` is canonical **281/281**
from real checked-list source in `src/platform/ApplicationSceneLifecycle.cpp`.
The native COFF candidate is278; genuine VC8 /GL+LTCG naturally generates the
target's aligned dual-EBP frame and full body. The new resolved linked-PE unit
pins tool/header/import-library inputs, proves export/map/CFG ownership and
replays every named call/data reference without masks or synthetic callees.
It is a comparison artifact, never an executed replacement image. See
[the source and exact evidence](APPLICATION_SCENE_LIFECYCLE_2026_10_16.md) and
[the linked comparison contract](LINKED_PE_MATCHING.md).

Its source producer `Application_commit_pending_scene @ 408080` remains
**189/148 nonexact** on frame/insertion ownership. Native12-byte list+84,
event+90 and scene hooks are recovered, with full source and independent
authored ownership. Private53-byte insertion `4089C0` and constant-count
Incsize `40C6D0` still have no new source/exact/exclusion credit. Recover original
template visibility before tuning that producer. Keep the paired TU together.
Fresh resolved `/Os`, `/Ob1` and `/GS` controls do not recover the producer's
outlined insertion. `/GS` changes `_Incsize` to153/154 with a different frame;
`/Ob1` leaves producer189 and callback281 unchanged. Verified shared growth
callers include independent device/audio pointer lists. These are bounded
negative/ownership observations only; see the visibility-controls table in
the scene-lifecycle evidence note before repeating those experiments.

## Accepted exact unit: Sprite texture setup

`CSpriteEx_set_texture_options @ 0x00407160` and
`SpriteTexture_initialize_rectangle @ 0x00407230` are canonical **193/193**
and **261/261** from `src/battle/SpriteTextureSetup.cpp`, unit
`cross-v106a-sprite-texture-setup`. The whole caller/helper TU supplies real
unsigned dimension locals, float UV/source-quad lifetimes and the observed
zero/color assignment order. A normal file-local static stdcall definition
lets VC8 naturally generate the helper's private EAX pointer and RET24; no
external fake ABI declaration, assembly or register directive was introduced.
This demonstrates that a private register entry alone does not prove an
LTCG-only blocker. Keep this closed TU together and replay both functions
after visibility or convention changes. Existing texture wrapper and CLogo
caller units were also replayed. See
[the exact evidence and reproduction](SPRITE_TEXTURE_SETUP_2026_10_16.md).

## Iku boundary and action-family reference

`Iku_dispatch_action_state_vslot28 @ 0x00620920` has a hash-attested complete
callable `[620920,62EFBE)`: **59,038 reachable bytes**, **15,132 instructions**,
131 returns, three compressed action switches, and no unreached bytes or
external direct jumps. The target body has 4,676 x87 instructions and no
`FSINCOS` or `FRNDINT`. The attested Ghidra decompilation drops some reachable
blocks and remains a private hypothesis. The root now has complete selected
source with a nonexact whole-root unit; see
[the current checkpoint](IKU_FULL_ROOT_SOURCE_2026_10_17.md). Boundary evidence:
[the boundary and action map](IKU_VSLOT28_BOUNDARY_ACTION_MAP_2026_10_02.md).

Target-to-target comparison of Iku actions 0–10 against Youmu established
shared helper topology but different constants and x87 zero lifetime; see
[the opening comparison](IKU_OPENING_ACTION_TARGET_COMPARISON_2026_10_02.md).
Actions 565–568 occupy 8,390 consecutive physical bytes and each has 14
static object-818 spawn call sites. They share cross-case tails; 567/568 add a
descending stage-crossing path. See
[the object-818 family evidence](IKU_565_568_OBJECT_818_FAMILY_2026_10_02.md).
The tracked `scripts/audit-iku-object-818-family.py` reproduces its diagnostic
JSON from the exact PE without a cached action-map report:

```bash
python3 scripts/audit-iku-object-818-family.py
```

All action families now have selected natural C++; the active task is whole-root
code generation with those verified payload, ABI, x87 and shared-tail facts.
TH08's VC7 inline `FSINCOS` is only a technique reference;
it does not establish an assembly requirement here, and this repository
forbids assembly for forced comparisons.

## Renderer source checkpoints

`CSprite_render @ 0x00406BE0` and `CSprite_render_fvf4142 @ 0x00406E50`
now have complete source in `src/ui/SpriteRender.cpp`. Both are 610-byte
CSprite primary-vtable entries, independently owned by the exact-backed
constructor and Menu cursor caller. The new origin rule adds two authored
roots / 1,220 bytes from the review queue. Each raw CFG closes all 210
instructions, and the target pair differs only in its FVF push. Fresh strict
VC8 candidates are 610 bytes with the first 541 canonical bytes equal; only
two COM method-loading/argument-scheduling windows remain nonexact. Their
16-byte frame and all floating geometry match, so do not conflate this lead
with the tile's unresolved frame reservation. The target-only checker is
`scripts/audit-sprite-render-family.py`; see
[the source, ownership and comparison evidence](SPRITE_PRIMARY_RENDER_2026_10_16.md).
No exact credit or accepted match-unit row was added. Original TU/inline
visibility and COM scheduling remain unknown.

`UiTileA4_render @ 0x004099F0` now has complete natural C++ source in
`src/ui/UiTileRender.cpp`. Fresh raw CFG closure reaches all 246 instructions /
756 bytes, and independently attested direct Ghidra sessions saved and read
back the `(float x, float y, int column, int row)` thiscall contract. The source
recovers float geometry/UV lifetimes, rotation and cached texture submission.
Strict FP with local exception scheduling off produces 756 bytes, nonexact at
+2: target frame 12 bytes versus candidate eight. The first 624 bytes differ
only in frame allocation and ESP homes; the tail also differs in COM method
load/push scheduling. No dummy stack slot or exact credit was added. See
[the source, controls and reproducible comparison](UI_TILE_RENDER_2026_10_16.md).
Existing shared headers and accepted match units were unchanged. Investigate
original inline/TU ownership before repeating the documented negative controls.

`CSpriteEx_finalize_render @ 0x00407AD0` also has complete ordinary source in
`src/battle/SpriteRenderFinalizer.cpp`, using the existing CSpriteEx layout.
All 67 instructions / 219 target bytes are reviewed. The 219-byte strict-FP
candidate is nonexact at +0x12 because it hoists the texture handle load/push.
All 43 x87 operations and the final 56-byte submission tail agree; this is
diagnostic evidence only. Normal submission-wrapper and handle-view probes
are byte-neutral, while plain strict FP and disabling global optimization
worsen codegen. See [the focused evidence](SPRITE_RENDER_FINALIZER_2026_10_16.md).
The original scheduling/TU phase remains unknown; no exact claim was added.
New RTM and ordinary base-submission-member controls reproduce the same
comparison bytes as the SP1 source; they do not explain the handle hoist.

TH075's local R182 evidence corroborates the 3600-entry angle-table policy,
but its integer-abs conversion order differs from TH105's float-phase path.
Do not transfer source or compiler assumptions between them.

## Other bounded nonexact leads

| Target | Current evidence and blocker |
| --- | --- |
| `Youmu_dispatch_action_state_vslot28 @ 0x00530200` | Source-present 37,692-byte root; latest canonical first mismatch `+0xCA`, 31/98 diagnostic owners. Physical return sharing, float lifetimes and TU context remain open. [Latest controls](YOUMU_SHARED_ZERO_RETURN_AND_CONTROLS_2026_10_02.md). |
| `AyaObject_update_action_state_vslot28 @ 0x0061A290` | Source-present 19,522-byte root; still nonexact at `+22`, with unresolved action-903 fade-tail/x87 scheduling and other cases. [Latest controls](AYA_OBJECT_903_FADE_TAIL_CONTROLS_2026_10_02.md). |
| `AyaObject_initialize_action_entry @ 0x0061F0B0` | Source-present 4,531-byte root; 11 target vslot+0x0C calls order `MOV ECX,ESI` before `PUSH EAX`, unlike the candidate. [Call scheduling](AYA_ENTRY_VSLOT0C_SCHEDULING_2026_10_02.md). |
| `YoumuObject_initialize_action_entry @ 0x00543670` | Source-present 5,159-byte root; nonexact at `+0x80`, with 6/30 diagnostic owners. [Load timing](YOUMU_OBJECT_ENTRY_LOAD_TIMING_2026_10_02.md). |
| `Fighter_update_common_action_state @ 0x004740C0` | Current priority; selected ordinary source remains nonexact at `+0x14`, 53/66 diagnostic owners. [Latest linked-tail and sharing evidence](COMMON_FIGHTER_LINKED_TAILS_2026_10_17.md). |
| `AnimationObject_prepare_render_transform @ 0x00435360` and `render_to_battle_scene @ 0x00435740` | Each candidate has the target size but differs in `FILD`/`PUSH EDI` scheduling; no exact claim. [Focused evidence](ANIMATION_RENDER_EDI_X87_SCHEDULING_2026_10_02.md). |
| `KomachiObject_emit_owner_gated_object_826_pair @ 0x005F9350` | Source-present 205-byte target, 203-byte candidate; call argument/register scheduling remains open. [Focused evidence](KOMACHI_PAIR_CALL_SCHEDULING_2026_10_02.md). |

Do not extrapolate a global VC8 flag, assembly need or LTCG explanation from
these local differences. Existing negative source/compiler probes are recorded
in the linked notes; repeat them only with new independent evidence. Recent
accepted exact anchors include
[fighter body collision](FIGHTER_BODY_COLLISION_2026_10_02.md) and
[three-axis sprite rotation](SPRITE_PIVOT_ROTATION_2026_10_02.md).
The separate origin/boundary review queue is documented in
[the focused review](ORIGIN_BOUNDARY_REVIEW_2026_09_26.md).

## Local state, artifacts and gate

The user's October 16 instruction is to prioritize reconstruction and avoid
routine full replays. Default to the current function/unit and accepted units
affected by shared changes. Reserve a cold all-unit replay for an intentional
aggregate verification checkpoint. The October 16 all-unit run was stopped
at the user's request after **113/464 units passed**; it is neither a completed
aggregate replay nor a comparison failure. The latest texture pair and its
affected callers had already passed focused comparisons and the local CI gate.

At the October 2 checkpoint the ignored `build/` directory was cleared, including old
objects, reports, caches, a CI virtual environment, and downloaded reference
copies. Compiled object/link products and Python bytecode scattered in
`.analysis/` were also removed; private probe source and Ghidra databases
remain. The October 16 render probes regenerate small objects/reports under
`build/`; private source and Ghidra state stay under `.analysis/`. Dated notes may name former `build/` report paths as reproduction
references; those files are absent until their commands are rerun. The pinned
official VC8 manual can be fetched and regenerated through
[the reference guide](VC8_REFERENCE.md). Private `.analysis/` Ghidra state and
`.tools/` compiler installations were preserved; neither is committed.
On October 16 the redundant `.tools/msvc80-rtm-media` extraction was removed
(247.84 MiB); the actual RTM compiler/header installation and its pinned
compiler hashes were preserved and checked before and after cleanup.
On October 17 the shared-root checkpoint removed another60.77MiB of obsolete
generated build products and reports. Only its current ordinary root, two
linked controls, evidence and24-provider cache were retained before CI;
the temporary Ghidra clone was also removed. Rebuild older report paths when
needed instead of treating them as retained current evidence.
Do not treat an old ignored report as a current comparison. Use a fresh
focused build/comparison for any source change, and run affected accepted
units after shared contract changes. A reported aggregate exact percentage
requires a cold `python3 scripts/verify-exact-units.py --all` run.

Before committing any future source, ledger, script, test or generated-progress
change, run the mandatory local gate in the finished worktree:

```bash
python3 scripts/ci.py
git diff --check
```

CI is target-independent and may recreate disposable Python caches under
`build/`; remove them again if preparing a clean handoff. Inspect `git status`
before pushing. The user explicitly requests commit **and push** at stable
checkpoints; verify remote main equals the intended local commit after pushing.
