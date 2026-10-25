# Alice Fighter update: complete source and early comparison

Target: original Japanese TH10.5 v1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Bounded root: **0x004E9F50**, Alice primary vtable slot28 at6C4C04.
The complete manual compiling hypothesis now has its first whole-function
comparison and a bounded callback-epoch correction. It remains identified and
unselected: no source-present or exact credit is added.

## Exact observations

The main callable is `[4E9F50,4F4631)`,42721 bytes, SHA256
`588194779ec2bba363702ac150979a064ce8bf77553bfa727b34951fc8788a89`.
The complete code/alignment/table payload ends at4F4B80,44080 bytes, SHA256
`2bd6bb53be12d74e98f1fee7dfcedf2b1adcf71597fd89a9ce8185f4d0e1f823`.
The next independent candidate is Alice CPU policy4F4B80.

A fresh instruction-start CFG traversal closes11169 of11170 decoded
instructions. The sole unreachable instruction is the three-byte alignment
`8D4900` at4F28ED; no edge escapes the callable or lands inside an instruction.
This is conservative static reachability, not proof that each branch can
execute for a feasible game state. There are128 RET0 sites,674 direct calls to
27 entries, and163 register-indirect calls. Entry aligns ESP to8 and allocates
0x410 bytes, saves EBX/EBP/ESI/EDI and uses ESI as receiver. Original C++ owner
layout, packet lifetimes and TU partition remain unknown.

All16 instruction-owned destination tables are closed, not just the three
primary action tables. They contain165 DWORDs, each pointing at an instruction
start in this callable. The three primary byte remaps contain685 bytes.

| Action region | Destination table / entries | Remap / bytes |
| --- | --- | --- |
| 0..226 |4F4634 /31 |4F46B0 /227 |
| 301..508 |4F4794 /34 |4F481C /208 |
| 521..770 |4F4914 /40 |4F49B4 /250 |

The pre-existing giant mapper independently retains103 unique primary
physical destinations, including one shared default4F44A5. Special actions
300/520/795/797/798 are direct branches outside those primary remaps.
The other13 nested tables have lengths5,5,5,5,5,5,5,5,4,4,4,4,4.
Every byte in the1359-byte metadata tail is accounted for:660 destination
bytes,685 remap bytes and14 pinned alignment bytes. The alignment ranges are
4F4631+3,4F4793+1,4F4AAE+2 and4F4B78+8.

The public raw audit checks the full target hashes, candidate size, vtable
cell, complete instruction decoding, all edges, RET cleanup, all table
operands/destinations, remap indices, metadata coverage and alignment pins:

```sh
scripts/repo-python scripts/audit-alice-fighter-update-target.py
scripts/repo-python scripts/map-giant-action-switches.py alice-vslot28 --json
```

The audit reports evidence only. No masked comparison, local matching window,
source selection or original nominal identity follows from these checks.

## Dependencies and retained source

The27 direct entries are the existing Fighter landing/motion, animation,
effect/event, object-spawn, counter, RNG and orientation families. Current
ledgers mark23 canonical exact. The two quantized lookups406360/4063D0 and
shared Fighter update4740C0 remain source-present/nonexact;68A1A0 is compiler
float-to-integer support. This round did not cold replay accepted callees.
The raw report retains each call count and the current declaration/status;
callee evidence must still be checked when choosing the complete source view.

`src/characters/AliceActionStateScaffold.cpp` is an existing partial semantic
staging helper returning whether it handled a selected action. It is not this
root and must not be called or renamed into a purported complete native body.
`src/characters/Vslot28ActionStateRoots.hpp` is declaration-only. Neither
justifies selecting Alice in implemented.csv. The retained scaffold and the
Youmu Fighter implementation may guide hypotheses; all Alice differences,
call epochs, argument widths and continuations require its actual instructions.

The source-missing report initially suggested Sakuya4CADB0 because its main
span is41511 bytes. Its ownership ledger already records ten remote chunks
and74941 owned code bytes. Alice's complete contiguous callable and payload
are therefore the chosen next bounded representative; no Sakuya ownership is
changed or lost by this selection.

## Read-only analysis receipt and remaining work

IDA preflight still rejects the GUI's wrong executable SHA10350095... . Raw
PE work is valid independently. One serial Ghidra process used384MiB heap,
CPU0/nice10, read-only/noanalysis and the existing primary project. Before
using its output, the script checked the exact executable hash, image base,
x86 Windows analysis target, entry68B9D2 and every imported section's mapped
bytes against resources/th105.exe. Temporary root and dependency views were
read back, then rolled back; root removal was read back and all nine primary
project file hashes were unchanged.

The saved5213-line decompiler output is a hypothesis with a stack-spacebase
warning and removed-block warnings, including unsigned conversion-correction
branches. It does not replace the raw CFG or recover original source locals.
Do not paste it mechanically or launch another database process just to reread
it. No analysis database state is the durable record.

Receipts are under `build/exact-first-alice-fighter-update-20261025/`:
`initial-map.json`, `raw-facts.json`, `target.asm`, `literals.json`,
`public-target-audit.json`, `ghidra-receipt.json`, `ghidra.log`, `decompile.txt`,
and `primary-db-before.json`/`primary-db-after.json`. Private recipes are in the
corresponding `.analysis/` directory. All are local and excluded from Git.

The following source checkpoint supersedes that target-only planning step.
Original source spelling and full nominal layout remain unknown. No exactness
or standalone/LTCG impossibility has been established.


## Complete manual hypothesis and first comparison

`src/characters/AliceFighterActionState.cpp/.hpp` now provides the entire
pre-dispatch prefix, low/mid/high and five special action paths, plus the real
shared Fighter default. The pointer-only primary view uses the accepted
AnimationSequenceObjectView virtual prefix; it is never constructed or
embedded. Numeric states, typed offsets and declaration-only callees remain.
The existing partial scaffold guided reviewed low/mid hypotheses; it is not
called, renamed into the root, or substituted for the complete body. Saved
decompiler output guided investigation only; the new paths were written
manually against the raw instructions and operand-width literal observations.

The first complete3165-line draft compiled and was compared immediately,
before source-shape trials:43428 bytes, canonical SHA256
`0d7bfb04cd363ef3436e53c2156915431bacd6b5674fcb0066b7a446c803c477`.
The complete target is44080 bytes;41945 unmasked positions differ, including
size, with the first mismatch4E9F58 (frame408 versus410). All16 table lengths
and three remap bounds already agree. This is a nonexact baseline, not a
matching percentage or behavioral equivalence result.

The configured ordinary VC8 O2/GS-off unit is
`exact-first-alice-fighter-update`. The public complete audit replays every
section relocation and compares all emitted bytes, including every tail byte;
it never masks fields, ignores extra emitted bytes or rebases destinations.
The three primary remap byte arrays also compare directly.

```sh
scripts/repo-python scripts/build.py --unit exact-first-alice-fighter-update --compare --json
scripts/repo-python scripts/audit-alice-fighter-update.py
# Independent already-built object:
scripts/repo-python scripts/audit-alice-fighter-update.py --object build/exact-first-alice-fighter-update-20261025/cold.obj
```

All three comparisons intentionally return1 for the nonexact hypothesis.
The mandatory local CI gate is separate and must pass before commit/push.
Fifteen new literal names are isolated aliases selected only by this new unit;
all predecessor relocation rows are unchanged. No accepted unit selects or
emits these new names and no accepted source/header/flags change. The target
floating relocation audit passes. This is not an aggregate cold replay claim.

## Callback epochs exposed by the first whole comparison

A per-action static reachable-call census narrowed the first complete source
to400 plus virtual-call-group differences in214/542/547/548. It ignores branch
predicates, so these counts alone establish neither path equivalence nor
missing behavior. Raw instruction review then found unsupported400/401 shapes
in the retained scaffold:

- Native400 selects sequence4 and emits effect62 before reloading facing for
  the802 request. For example4ED35B calls the effect and4ED38E reloads byte104.
  The draft cached facing before the sequence/effect calls. The complete source
  now reads the live field after each actual callback and keeps the802/801
  requests separate, including their ordinary parameter arrays.
- Native400's ordinary801 request continues at4ED47C after the scaled counter;
  native401 continues at4ED5BF. The draft returned immediately after both
  request suffixes. The complete source now retains the subsequent action and
  sequence/timer gates. The802 branch keeps its separate returning suffix.
- The >=25 timer gate is sequence4, not0:400 writes EBX=4 at4ED484 before the
  shared4EDBE5 comparison;401 writes EBX=4 at4ED5C7 before4ED605. The register
  value is checked from actual predecessor paths, not inferred from a shared
  decompiler label. Native401 also publishes DWORD180=1 at4ED5AB before the
  counter call4ED5B1; the source now preserves that order.

These are target-backed read/write/edge corrections. They do not prove that
an ordinary game effect flips facing or that an existing game path exposes
every possible callback mutation. No fabricated callback or injected helper
result is used as gameplay evidence.

The final3135-line retained hypothesis emits43572 bytes, canonical SHA256
`8dd4473aad05d259763114f8ce440b69cd5b6e24a9cd9656699a911a082bd506`.
Formal and independent fresh-object full audits agree. It remains nonexact+8,
41815 unmasked differences including the508-byte size gap. Frame418 versus410,
121 versus128 RETs,665 versus674 physical direct calls and157 versus163
register-indirect calls remain. All16 table lengths and all685 primary remap
bytes agree. Other than214/542/547/548 indirect-call memberships, the mapped
primary action groups now agree in their per-action direct and indirect call
counts. The five special direct-dispatch cases are outside that mapped-case
census and need their own instruction review. Inventory agreement is not exact
acceptance and does not waive any byte difference.

Remaining questions include the physical callback groups and lifetimes,
case730's partially defined upper facing-argument bits, and the fourth word
transmitted by570/571 count4 requests. The draft leaves the fourth array
member ordinarily uninitialized rather than inventing a zero store; complete
predecessor/write/consumer analysis is still required. The complete source
must remain unselected until its instruction, ABI and default-domain review
supports selection. Do not infer LTCG impossibility or try padding the frame.

Current receipts in the existing build scope: `first-complete-*`,
`callback-epochs-*`, `formal-build.log`, `formal-full-audit.json`,
`cold-build.log`, `cold-full-audit.json`, `native-inventory.json`, and
`literal-impact.json`. First/control source and focused call-ownership recipes
remain in the matching private analysis scope. The public source/unit/audit
are the reproducible current state; generated reports/objects stay out of Git.


## Narrow-facing control and native214 routing correction

The admitted declaration question is now bounded rather than inferred from
callee byte loads. A fresh wide-direction FighterOwnedObjectSpawn build retains
canonical66/66 at465190. A separate genuine closed source changes only its
three direction declarations (wrapper declaration/definition and manager virtual
signature) from int to unsigned char. The existing fighter-owned-object-spawn
unit's object-override comparison is also66/66, canonical SHA256
`80aab8cb379377dc179c3e1311599ab890885fa92ffd5ecf075ff6c3df15a7fc`.
Both views are admitted; original nominal width is not uniquely recovered.
Neither the accepted provider source nor its unit is changed.

A separate complete caller changes only its facing formal to unsigned char;
layer remains int. It emits43464 bytes/SHA256
`b046bb878a37b2375bc3b731a6061773e60c03e97ff84e8fdf2edf306595ad19`,
41894 unequal positions. Frame418,16 table lengths/685 remap bytes and the
214/542/547/548 callback membership gaps persist. The control is unselected;
the public caller keeps its admitted int-facing view. Do not sweep width
combinations or claim the original formal from this result. Receipts are
`width-provider-baseline.json`, `provider-facing-byte-comparison.json`,
`width-baseline-full-audit.json`, and `facing-byte-*` in the existing scope.
The separate source changes and exact compiler commands are retained privately.

The first whole comparison also directed review to214. Exact instructions
show that the active sequence range1..4 encloses its flight-end condition:
4EB474/4EB47D send states outside that range directly to4EB8E1's landing check.
The retained source had placed the flight-end gate outside that range and
could reset scratch instead of checking landing for0/5/6. The correction keeps
the gate inside the active motion block. It also restores the timer re-read
after event31 at4EB38C, live field13E/F4 checks after each virtual sequence call,
and live heading/peer reads at the actual later uses. In particular the four
motion sequence checks4EB61B..4EB6B0 reload their conditions between calls;
the former cached velocity/sequence pair did not express those epochs.

A small native execution check now starts at the real root for sequences0/5/6
and both values0/1 of input6C8, with counter736=20 and spirit482=1. Native
4351C0 executes and returns normally: frame counter0->1 stays below duration3,
and timer1->2. There is no injected helper result, callback or branch. Both
native and candidate stop before the first5F9310 landing or435110 scratch body.
All six inputs agree in boundary, receiver, the observed0x800-byte owner prefix,
helper trace and empty x87 stack/control. Gravity produces -2.5 for5/6 and
leaves -2 for0. The old8dd4473a object fails precisely the three input6C8=0
cases by choosing scratch reset instead of landing. This proves these bounded
prefixes, not active-flight behavior, subsequent landing results or real-game
reachability of the fixture combinations.

```sh
scripts/repo-python scripts/audit-alice-fighter-action214-paths.py
# Negative control (expected exit1;3/6 differences):
scripts/repo-python scripts/audit-alice-fighter-action214-paths.py --object build/exact-first-alice-fighter-update-20261025/action214-before.obj
```

The current3018-line source retains only the214 instruction/epoch correction;
it does not select the narrow-facing caller control. Formal and independent
fresh-object full comparisons now agree at44012 bytes, SHA256
`4fa62a2b837aa5a89b3dac35f0b1327db2062d3ad6f6aa5c201be31d672090b0`.
There are41449 unmasked differing positions including the68-byte size gap.
Frame418/410, RETs124/128, direct calls672/674 and indirect calls160/163 remain.
The four physical direct-callee discrepancies are stage height14/16, stage
predicate6/7, zero motion26/28 and wave dispatch52/49 (candidate/native).
All16 table lengths and all685 remap bytes agree.214's per-action indirect
inventory is now14/14; remaining mapped-case callback differences are542,
547 and548. Counts still ignore predicates and do not replace the full byte
comparison. The source stays identified/unselected with no new exact or
source-present credit. No accepted unit input changes and no new aggregate
cold acceptance is claimed.

Current receipts use `action214-formal-*`, `action214-cold-*`,
`action214-live-fields-*` and `action214-old-negative-paths.json`.
The intermediate `action214-live-fields.obj` and formal/cold objects all emit
4fa62a2b. The frozen `action214-before.obj` is the8dd4473a predecessor. Continue
from the public complete source and these actual residuals; keep the width
control separate and avoid unproved packet-size changes.


## Separate542 terminal guards and common547/548 exit

Exact target instructions distinguish two542 action9 terminal paths.
4F1019..4F1032 tests the zero timer/frame counters and sequence4, then reaches
4ED95D's action9 call4ED966 and RET. The subsequent4F1038..4F1061 guards
sequence8 and reaches its own action9 call4F1070 and RET. The complete source
now preserves these two guards instead of OR-ing the sequences into one call.
The neighboring543 legitimately has one shared terminal call and is unchanged.

Native547 threshold4F1860..4F1867 (timer>=30) and548 threshold4F1A9D..4F1AA4
(timer>=50) both enter4F1B00. Their successful landing tests converge at4F1AEC:
zero motion45AF40, height435D60, store ownerF0, then common next-block virtual
call4F1B07. One source exit label now preserves that common continuation for
these four paths. The label is a reconstruction of observed control flow;
it is not evidence of the original source spelling. No initialization, helper
return value, assembly or padding was added.

Each question was first compiled independently from the preceding complete
44012-byte/4fa62a2b source, followed immediately by a whole-payload comparison:

| Complete-source control | Canonical bytes | SHA256 | Unmasked differences |
| --- | ---: | --- | ---: |
| Separate542 guards only |44024|b66f790d40bd3dab413888fb835f7ce5ee325d37b6e4004f09ea49c37c96dbdb|41324|
| Common547/548 exit only |43976|4af800f87ba6a11a2d9324f8b90480075c43c57ef437671163f3c7785209f0f4|41578|
| Both retained |43996|2655274b9cd5c98ee3a873aea3fa6e3f36cadd4c21c9e0e86ce44103380eb07c|41484|

The542-only control closes its per-action virtual-call membership gap5/5;
only547/548 remain3/4. The547/548-only control closes both3/3 gaps; only542
remains5/4. Combining the supported structures closes all mapped-case direct
and indirect call-count differences. These are conservative reachable-site
counts without predicate feasibility, not call execution counts or semantic
acceptance. The five special direct-dispatch arms remain outside this census.

Formal and independent fresh-object audits agree on the combined payload.
The full strict44080-byte target comparison still fails at+8, frame418/410,
with41484 differing positions including the84-byte size gap. Physical totals
remain122/128 RETs,672/674 direct calls and158/163 indirect calls; some global
counts are farther from the target than before. All16 table lengths and all685
primary remap bytes still agree. The changes are retained for observed local
control-flow structure, not because of an aggregate similarity improvement.
Both new objects also pass all six previously bounded214 native prefixes.
No implemented/exact ledger addition or aggregate cold claim is made.

Receipts in the existing build scope: `exit542-split-*`, `exit547-548-common-*`,
`exits-formal-*`, `exits-cold-*`, and `exits-baseline-full-audit.json`.
The private controls start from checkpoint589d2468, and their commands/source
are frozen in the corresponding analysis scope. Current public source is3022
lines. The terminal-structure questions are now closed; next inspect actual
stack/packet lifetimes and separately review the five special direct arms,
without repeating guard-spelling trials or shrinking packets to force a frame.


## Direct-dispatch coverage and packet extent control

Separate inspection now covers the five action roots omitted from the primary
remap census. Their native/candidate entries in the retained2655274b object are:

| Action | Target entry | Candidate entry | Indirect sites, target/candidate |
| --- | --- | --- | --- |
|300|4EC479|4EC34F|1/1|
|520|4EF082|4EEF50|3/3|
|795|4F4439|4F43E7|2/2|
|797|4F4597|4F4504|2/2|
|798|4F44B4|4F444B|2/2|

The outer comparisons at4EA134,4EC516,4EF479 and subtraction at4F4496 recover
these direct entries independently of the remap bytes. Conservative reachable
counts for every direct callee agree too.300's native directional gate uses0,
0.5 damping clamps only below zero, and frame2 emits event27.520 preserves the
two timer6/3 request arms, increment-before/after-scaled10 order, post-request
sequence reload, landing height->zero->sequence8 order and the later action0
callback followed by a fresh sequence read.795 uses gravity from double6C2A70,
event30->sequence1->height->zero on landing, otherwise frame->action700.
797/798 share event30->sequence3->height->vy0 landing but separately clamp x to
480/800 and finish with action0/700. The actual float/double constants at
6C0578/6C0EB0 are480;6C3B38/6C3B30 are800. This closes the census omission
and a bounded instruction review, not full callback, NaN or execution proof.
Call counts across all reviewed actions still do not explain global physical
sharing differences. Receipt: `direct-arms-call-ownership.json`.

Packet evidence is now stronger than decompiler variable adjacency. Let B be
ESP after the complete native prologue.570's two827 requests use B+78 and store
only B+78/7C/80;571 uses B+6C with stores B+6C/70/74. Both pass count4, and the
wrapper465190 forwards it. Manager4FAAD0 reads that count at4FAB27, allocates
count*4 bytes and calls pinned memcpy68AA30 at4FAB62 with byte count16. Its
source-pointer copy leaves no basis for treating the transmitted fourth word
as a hidden count unit or an ignored argument. No fourth-word initialization
was found in these local request paths; its incoming value remains unknown.
Mutually exclusive local spans and potential compiler overlap do not prove
an original array declaration boundary.

After this write/span/consumer review, one private complete-source control
changes only the two local arrays from four to three floats, retaining the real
count4 at every call. It naturally emits frame410 and moves the first mismatch
from+8 to+17. The complete payload remains43996, SHA256
`08ce1a46c4b6aabf5369587035a29bbf0110acad9860115ad79b6caa4d93972e`,
with41499 differing positions. All16 table lengths,685 remap bytes and per-action
call counts remain unchanged. This does not establish a correct three-element
source object: the real manager would read beyond it, and native stack reuse
could also explain overlapping extents. The control stays private/unselected;
public source keeps four floats with an ordinarily uninitialized fourth word.
The control is closed without a size/lifetime permutation search. Receipts:
`packet570-571-three-*`; the complete source and exact commands are retained
privately. No accepted source, header, flags, relocation or ledger selection
changed in this investigation.


## Action-owner partitions expose request-publication order

The next investigation partitions each physical direct/indirect call site by
its conservatively reachable action entries. It covers all685 primary-remap
values plus300/520/795/797/798, including shared defaults. All690 per-action
call-count comparisons agree for both the preceding2655274b and new0a47fcc9
objects. The only three physical direct calls outside these entries are the
pre-dispatch object998 requests; no indirect call site is left unowned.
This checks census coverage rather than predicate feasibility or behavior.

Physical partition differences persist even when aggregate counts agree.
For example the preceding candidate merges the wave2 sites for410/411, whereas
the target gives410 its own site and shares411/412/415/416 at4EE6BD. Inspection
of those actual paths, rather than attempts to force their shared spelling,
finds three publication-order errors in the retained source:

| Request arm | Exact target order after spawn | Prior source difference |
| --- | --- | --- |
|410|wave4EDE67 -> adjust4EDE75 -> scale4EDE7E -> dword180=1 at4EDE83|Wrote180 before adjust/scale|
|411/412|wave4EE6BD -> dword180=1 at4EE6C9 -> adjust4EE6D1 -> scale4EE6DA|Already correct|
|414|wave4EE346 -> adjust4EE354 -> dword180=1 at4EE35D -> scale4EE363|Already correct|
|415/416|Same4EE6BD common continuation as411/412|Wrote180 after adjust|

Only410/415/416 source ordering changes. The historical410 ledger note had
incorrectly placed its publication before adjust; that note is corrected by
this exact instruction review. The value is1 in the observed target paths:
EBP is initialized to1 at4E9F73 and is preserved into these store sites. The
source also writes the same dword literal1. No new call, flag, header, type,
initialization, source selection or byte mask is introduced.

A public reproducible static diagnostic now extracts the six action entries
from each complete payload's actual mid-switch metadata and enumerates local
request traces to RET. Calls are opaque fallthroughs, branch predicates are
unconstrained, and the recorded events are spawn/wave/adjust/scale and the
four-byte180 store. It checks ordering only: it neither executes nor injects
callback results, and it does not prove callback behavior, store-value dataflow
or whole-function equivalence. The new complete object passes all six; the
frozen preceding object fails precisely410/415/416, a negative control for the
original error rather than a test that mirrors the new source text.

```sh
scripts/repo-python scripts/audit-alice-fighter-publication-order.py
# Expected1, old complete2655274b object:
scripts/repo-python scripts/audit-alice-fighter-publication-order.py --object build/exact-first-alice-fighter-update-20261025/exits-cold.obj
```

The single private complete-source correction was compared immediately, before
retention. Formal and independent fresh-object comparisons now agree on44108
bytes, canonical SHA256
`0a47fcc9df818389722356ce1abdc02961d28d06aeb3c22d7e1c5eedaf3694bd`.
The strict whole44080-byte target comparison remains nonexact at+8/frame418
versus410, with41308 unmasked differences including28 extra candidate bytes.
Physical totals are125/128 RETs,679/674 direct and158/163 indirect calls. The
new global direct total is farther from target, although the corrected local
orders now agree; call totals are not an acceptance metric. All16 table lengths
and685 primary remap bytes still agree. Both independent objects also pass all
six bounded214 execution prefixes. No exact/source-present credit is added.

Receipts: `sharing-before.json`, `sharing-publication.json`,
`publication-order-*`, `publication-formal-*`, `publication-cold-*`, and
`publication-before-static.json`, all in the existing build scope. Private
`sharing.py` independently recovers the five direct-dispatch entries as well
as primary metadata and checks complete call ownership. The frozen predecessor
source is `publication-before.cpp`; the new private source is
`publication-order.cpp`. These local ordering questions are closed. Continue
from the remaining actual partitions and field-read epochs; do not force a
particular global call count or conflate local site sharing with behavior.


## Native predicate result-consumption width

The197/198 zero-motion site partition is separately reviewed: both native
entries resolve->advance, branch through the same action700/status3 or
action0/optional1 paths, then gate zero motion at framecounter0/frame8 and
facing comparison at framecounter0/frame13. Native197 zero call4EA700 and198
call4EA77B remain distinct despite the source compiler sharing one. The local
field tests and callback order show no discrepancy requiring a source split.
Likewise208 and220 have separate native predicate calls4EB1D4/4EBA0E and frame
calls4EB235/4EBA6F. Both perform crossed-surface->action10->height->zero on the
landing branch, then surface/positive-vy status2, signed sequence>0 damping
clamped at-20, advance and the sequence1/timer0 initialization. This is bounded
instruction review, not full execution or a reason to force distinct sites.

One independent operand-width issue is visible throughout the full caller.
All42 native5F9310 calls and all7 native435DC0 calls immediately TEST AL,AL.
The preceding0a47fcc9 caller instead has22+6 TEST EAX,EAX sites; another20
already testAL. Inspection of the actual accepted providers resolves whether
this is a semantic error:435DC0's42-byte body returns through full EAX=1 at
435DDB or EAX=0 at435DE4;5F9310's64-byte body returns through full EAX=1 at
5F933F or EAX=0 at5F9349. Thus both wide and byte tests have the same truth value
for these real callees. Original nominal return width remains unproved; their
int declarations and accepted implementations are unchanged.

One complete-source control explicitly projects these results to unsigned char
at the29 previously wide source expressions (22 crossed calls and7 surface
calls, with208/220 merged by compilation). Its whole canonical payload differs
from0a47fcc9 in exactly28 bytes, all opcode85->84, changing TEST EAX,EAX to
TEST AL,AL. No instruction length, relocation, table, remap, call site, frame
allocation or other byte changes. The retained source expresses this observed
caller consumption without inventing a narrow external ABI. All48 emitted
predicate sites now testAL; native has49 because its208/220 sites are separate.
The complete audit now reports each predicate call's immediate test register
for both target and candidate, leaving unrecognized next instructions explicit.
The diagnostic neither masks these opcodes nor changes the exactness decision.

Formal and independent fresh-object reports agree at44108 bytes, SHA256
`1bbd8acb28131ca4c416f5a9f22b13a5ab62c6d6ab64c779dddbe809dc04ad66`.
The whole strict target comparison still fails at+8/frame418 versus410,
41308 differing positions including28 extra candidate bytes.125/128 RETs,
679/674 direct calls and158/163 indirect calls are unchanged. All16 table
lengths and685 remap bytes agree, and all690 primary/direct action call counts
remain aligned. Both fresh objects retain the six publication-order checks
and six214 execution-prefix checks. No exact/source-present credit is added.

Receipts: `predicate-provider-target.asm` pins only the complete42/64-byte
providers; `predicate-low-byte-*`, `predicate-formal-*`, `predicate-cold-*`,
`predicate-old-full-audit.json` and `sharing-predicate.json` retain the whole
comparisons and diagnostic widths. The28-byte-only delta is recorded in
`predicate-low-byte-byte-delta.json`. Private `predicate-before.cpp` freezes
0a47fcc9; `predicate-low-byte.cpp` is the single29-expression control. This
consumption question and the two reviewed site-sharing pairs are closed;
continue with independent lifetime/field-read evidence, not type permutations.


## Request-loop arithmetic and root case layout

The525/526 request family now has a separate instruction review. Both native
entries resolve, clear750 from6C0/6C4, take the sequence1/timer>15 block exit,
advance, and preserve the sequence0/frame8 block->effect62 early return. Their
first loops reload signed byte609 after each spawn, then wave3->publish180=1->
adjust(200,120)->scale50 and continue with fresh timer/frame/sequence checks.
The sequence1/timer0 action0 branch returns; the sequence2/frame2 second loops
finish through wave4F0707, publish4F070C and the shared adjust4F1C94/scale4F1C9D
return tail. The source expresses those continuations and callback epochs;
site sharing alone supplies no reason to force common labels.

One actual arithmetic association differs in526's first loop. Native4F04E1
loads n and4F04E5 doubles it with FADD ST0,ST0 before loading double10 at4F04E9.
4F04F7 adds the shared2n for packet0, then4F0504 adds double21 to the same2n for
packet1. The prior source's10.0+n+n instead makes two successive additions to
10 before separately doubling n for packet1. The single private complete-source
control changes only this expression to(n+n)+10.0. Its output now has that
shared doubling before the10 addition. For this first loop n starts at0 and
increments exactly by1 while n<signed609+1<=128; all participating sums are
small exact integers. This restores observed arithmetic order without claiming
an input-domain numeric bug. The other loop expressions are unchanged.

An independent whole-source layout question is also tested. The retained
manual source had400/500 blocks after695/696, whereas the target's root entries
mostly follow numeric order. A private brace-aware parser extracts108 root
case/default groups with110 explicit numeric labels, keeps alias groups
intact, and records each group's original text hash. All group texts are
preserved by numeric permutation. Direct return/goto terminal depths are
checked;720/721/730's terminal switches, including every default return, are
reviewed separately. There is no root-case fallthrough to change. The previous
source ordering has130 inverted pairs of native entry addresses; numeric order
has9. This supports a controlled layout hypothesis; compiler tail sharing means
it does not prove the original lexical order. No register tie, dummy operation,
new local, padding, flag or header change is used.

Each property was first compared independently from complete1bbd8acb:

| Complete control | Bytes | Canonical SHA256 | Unmasked differences |
| --- | ---: | --- | ---: |
|526 association only|44108|d43fa4a177db32e5589b7baaafb3cf61f4a09b3764d7dbf70083d9fba8d870cd|41336|
|Numeric case groups only|44068|95ad941925fe54aab7b6eef067025d388c1131fca4de56aa9636bd57391291d8|40625|
|Both retained|44068|ef85ed758ed4f74b556b501db87b407174f3af2028ba1cee383ef013d678feb1|40778|

Formal and independent fresh-object reports for the retained source agree.
The first destination table starts42720 bytes from entry, versus42724 target;
the complete strict payload comparison still fails at+8/frame418 versus410.
It includes all12 missing candidate bytes, without waiving the8 target INT3
whose COFF/linker ownership remains separately unknown.125 prior RETs become
124 versus128 target; direct calls677/674 and indirect158/163 still differ.
Some individual physical counts become farther from target. All16 table
lengths and685 remap bytes agree, all690 action call counts agree, all48 emitted
predicate tests useAL, publication ordering6/6 passes and214 execution-prefix
checks6/6 pass. Neither similar payload size nor the layout hypothesis grants
implemented/exact credit. No accepted unit input changes or new aggregate cold
claim is made.

Receipts in the existing build scope: `counter-tail-baseline-full-audit.json`,
`loop526-association-*`, `case-order-numeric-*`, `case-order-association-*`,
`case-order-source-facts.json`, `layout-formal-*`, `layout-cold-*` and
`sharing-layout.json`. Private `case-order.py` is pinned to the frozen
`counter-tail-before.cpp` source and keeps the block hashes and terminal checks.
The retained public3022-line source differs from its numeric permutation only
in the one526 expression. These two controls are closed; continue from actual
field-read/lifetime evidence rather than another ordering or spelling sweep.


## Shared request intermediate and bounded checkpoint

A new dataflow check first inspects the currentef85ed75 candidate. In525's
first loop it computes2n, stores it to float at4F00F2, then reloads the same
word at4F00FB after stack pushes. In526's second loop the analogous store/load
is4F05D3/4F05DC. By contrast native4F01B1..4F01DA and4F064B..4F0674 keep2n in
x87 while forming2+2n and2n+21, with no float store of the intermediate. Dumps
are decoded from the complete function entry before selecting instructions;
stack pushes are retained so repeated ESP-relative slots are not mistaken for
different objects.

One private whole-source control replaces only those two temporary uses of
packet[1] with a genuine double twice_n=n*2.0, consumed by both final packet
fields. This removes the observed float store/reload in both loops. The local
is live and used; no frame padding, volatile tie, ABI declaration, loop bound,
callback, array extent or compiler option changes. The source spelling of the
original shared value remains unknown. Since these loops increment float n
from0 while comparing against signed byte609+1 or+3, body n is a small exact
integer0..127 or0..129. The old intermediate rounding was not a demonstrated
numeric behavior bug in that domain.

The complete control was compared immediately and emits44032 bytes, SHA256
`4d312925be3f754e27ef0f963632f8034ca587c6b09be35dc7a7ff8aefd5bd1d`.
Formal and independent fresh-object full, publication-order and214-prefix
reports agree. The full44080-byte target comparison remains nonexact:41054
unmasked differing positions including48 missing candidate bytes, first+8 and
frame418/410. Code-to-first-table42684/42724,124/128 RETs,677/674 direct and
158/163 indirect calls remain. All16 table lengths,685 remap bytes and690
action call counts agree;48 predicate tests useAL. Publication checks6/6 and
214 execution-prefix checks6/6 still pass. Other x87 ordering/lifetimes remain
different: the candidate carries an extra constant2 across spawn, whereas
the native calculation consumes its2 while forming packet0. Full x87
call-boundary equivalence is unproved; neither complete request-loop nor
whole-function execution equivalence is claimed.

Receipts: `fp-live-baseline-full-audit.json`, `fp-live-fragments.asm`,
`fp-live-shared-double-*`, `fp-live-formal-*`, `fp-live-cold-*` and
`sharing-fp-live.json` in the existing build scope. Private
`fp-live-before.cpp` freezesef85ed75; `fp-live-shared-double.cpp` is the single
control and retained source. No accepted input, exact/source-present ledger
selection or aggregate cold result changes.

The finite Alice source controls are now checkpointed. Remaining frame/array
extent and object/linker metadata ownership need independent evidence; no
standalone/LTCG impossibility claim follows. Keep the current complete source
unselected, preserve the strict comparison and do not iterate equivalent
spellings or re-run closed array/width/layout controls. Next work returns to a
complete medium representative with a distinct untried provenance question,
AyaObject61F0B0.
