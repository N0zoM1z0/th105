# Alice Fighter update: complete source and early comparison

Target: original Japanese TH10.5 v1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Bounded root: **0x004E9F50**, Alice primary vtable slot 28 at 6C4C04.
The complete manual compiling hypothesis now has its first whole-function
comparison and a bounded callback-epoch correction. It remains identified and
unselected: no source-present or exact credit is added.

## Exact observations

The main callable is `[4E9F50,4F4631)`,42721 bytes, SHA256
`588194779ec2bba363702ac150979a064ce8bf77553bfa727b34951fc8788a89`.
The complete code/alignment/table payload ends at 4F4B80,44080 bytes, SHA256
`2bd6bb53be12d74e98f1fee7dfcedf2b1adcf71597fd89a9ce8185f4d0e1f823`.
The next independent candidate is Alice CPU policy 4F4B80.

A fresh instruction-start CFG traversal closes 11169 of 11170 decoded
instructions. The sole unreachable instruction is the three-byte alignment
`8D4900` at 4F28ED; no edge escapes the callable or lands inside an instruction.
This is conservative static reachability, not proof that each branch can
execute for a feasible game state. There are 128 RET 0 sites,674 direct calls to
27 entries, and 163 register-indirect calls. Entry aligns ESP to 8 and allocates
0x410 bytes, saves EBX/EBP/ESI/EDI and uses ESI as receiver. Original C++ owner
layout, packet lifetimes and TU partition remain unknown.

All 16 instruction-owned destination tables are closed, not just the three
primary action tables. They contain 165 DWORDs, each pointing at an instruction
start in this callable. The three primary byte remaps contain 685 bytes.

| Action region | Destination table / entries | Remap / bytes |
| --- | --- | --- |
| 0..226 |4F4634 /31 |4F46B0 /227 |
| 301..508 |4F4794 /34 |4F481C /208 |
| 521..770 |4F4914 /40 |4F49B4 /250 |

The pre-existing giant mapper independently retains 103 unique primary
physical destinations, including one shared default 4F44A5. Special actions
300/520/795/797/798 are direct branches outside those primary remaps.
The other 13 nested tables have lengths 5,5,5,5,5,5,5,5,4,4,4,4,4.
Every byte in the 1359-byte metadata tail is accounted for:660 destination
bytes,685 remap bytes and 14 pinned alignment bytes. The alignment ranges are
4F4631+3,4F4793+1,4F4AAE+2 and 4F4B78+8.

The public raw audit checks the full target hashes, candidate size, vtable
cell, complete instruction decoding, all edges, RET cleanup, all table
operands/destinations, remap indices, metadata coverage and alignment pins:

```sh
scripts/repo-python scripts/map-giant-action-switches.py alice-vslot28 --json
```

The audit reports evidence only. No masked comparison, local matching window,
source selection or original nominal identity follows from these checks.

## Dependencies and retained source

The 27 direct entries are the existing Fighter landing/motion, animation,
effect/event, object-spawn, counter, RNG and orientation families. Current
ledgers mark23 canonical exact. The two quantized lookups 406360/4063D0 and
shared Fighter update 4740C0 remain source-present/nonexact;68A1A0 is compiler
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

The source-missing report initially suggested Sakuya 4CADB0 because its main
span is 41511 bytes. Its ownership ledger already records ten remote chunks
and 74941 owned code bytes. Alice's complete contiguous callable and payload
are therefore the chosen next bounded representative; no Sakuya ownership is
changed or lost by this selection.

## Read-only analysis receipt and remaining work

IDA preflight still rejects the GUI's wrong executable SHA 10350095... . Raw
PE work is valid independently. One serial Ghidra process used 384MiB heap,
CPU 0/nice10, read-only/noanalysis and the existing primary project. Before
using its output, the script checked the exact executable hash, image base,
x86 Windows analysis target, entry 68B9D2 and every imported section's mapped
bytes against resources/th105.exe. Temporary root and dependency views were
read back, then rolled back; root removal was read back and all nine primary
project file hashes were unchanged.

The saved 5213-line decompiler output is a hypothesis with a stack-spacebase
warning and removed-block warnings, including unsigned conversion-correction
branches. It does not replace the raw CFG or recover original source locals.
Do not paste it mechanically or launch another database process just to reread
it. No analysis database state is the durable record.

Receipts are under `build/exact-first-alice-fighter-update-20261025/`:
`initial-map.json`, `raw-facts.json`, `target.asm`, `literals.json`,
`public-target-audit.json`, `ghidra-receipt.json`, `ghidra.log`, `decompile.txt`,
and `primary-db-before.json`/`primary-db-after.json`. All are local and excluded
from Git.

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

The first complete 3165-line draft compiled and was compared immediately,
before source-shape trials:43428 bytes, canonical SHA256
`0d7bfb04cd363ef3436e53c2156915431bacd6b5674fcb0066b7a446c803c477`.
The complete target is 44080 bytes;41945 unmasked positions differ, including
size, with the first mismatch 4E9F58 (frame 408 versus 410). All 16 table lengths
and three remap bounds already agree. This is a nonexact baseline, not a
matching percentage or behavioral equivalence result.

The configured ordinary VC8 O2/GS-off unit is
`exact-first-alice-fighter-update`. The public complete audit replays every
section relocation and compares all emitted bytes, including every tail byte;
it never masks fields, ignores extra emitted bytes or rebases destinations.
The three primary remap byte arrays also compare directly.

```sh
scripts/repo-python scripts/build.py --unit exact-first-alice-fighter-update --compare --json
```

All three comparisons intentionally return 1 for the nonexact hypothesis.
The mandatory local CI gate is separate and must pass before commit/push.
Fifteen new literal names are isolated aliases selected only by this new unit;
all predecessor relocation rows are unchanged. No accepted unit selects or
emits these new names and no accepted source/header/flags change. The target
floating relocation audit passes. This is not an aggregate cold replay claim.

## Callback epochs exposed by the first whole comparison

A per-action static reachable-call census narrowed the first complete source
to 400 plus virtual-call-group differences in 214/542/547/548. It ignores branch
predicates, so these counts alone establish neither path equivalence nor
missing behavior. Raw instruction review then found unsupported 400/401 shapes
in the retained scaffold:

- Native 400 selects sequence 4 and emits effect 62 before reloading facing for
  the 802 request. For example 4ED35B calls the effect and 4ED38E reloads byte 104.
  The draft cached facing before the sequence/effect calls. The complete source
  now reads the live field after each actual callback and keeps the 802/801
  requests separate, including their ordinary parameter arrays.
- Native 400's ordinary 801 request continues at 4ED47C after the scaled counter;
  native 401 continues at 4ED5BF. The draft returned immediately after both
  request suffixes. The complete source now retains the subsequent action and
  sequence/timer gates. The 802 branch keeps its separate returning suffix.
- The >=25 timer gate is sequence 4, not 0:400 writes EBX=4 at 4ED484 before the
  shared 4EDBE5 comparison;401 writes EBX=4 at 4ED5C7 before 4ED605. The register
  value is checked from actual predecessor paths, not inferred from a shared
  decompiler label. Native 401 also publishes DWORD180=1 at 4ED5AB before the
  counter call 4ED5B1; the source now preserves that order.

These are target-backed read/write/edge corrections. They do not prove that
an ordinary game effect flips facing or that an existing game path exposes
every possible callback mutation. No fabricated callback or injected helper
result is used as gameplay evidence.

The final 3135-line retained hypothesis emits 43572 bytes, canonical SHA256
`8dd4473aad05d259763114f8ce440b69cd5b6e24a9cd9656699a911a082bd506`.
Formal and independent fresh-object full audits agree. It remains nonexact+8,
41815 unmasked differences including the 508-byte size gap. Frame 418 versus 410,
121 versus 128 RETs,665 versus 674 physical direct calls and 157 versus 163
register-indirect calls remain. All 16 table lengths and all 685 primary remap
bytes agree. Other than 214/542/547/548 indirect-call memberships, the mapped
primary action groups now agree in their per-action direct and indirect call
counts. The five special direct-dispatch cases are outside that mapped-case
census and need their own instruction review. Inventory agreement is not exact
acceptance and does not waive any byte difference.

Remaining questions include the physical callback groups and lifetimes,
case 730's partially defined upper facing-argument bits, and the fourth word
transmitted by 570/571 count 4 requests. The draft leaves the fourth array
member ordinarily uninitialized rather than inventing a zero store; complete
predecessor/write/consumer analysis is still required. The complete source
must remain unselected until its instruction, ABI and default-domain review
supports selection. Do not infer LTCG impossibility or try padding the frame.

First/control source and focused call-ownership recipes remain in the matching
private analysis scope. The public source/unit/audit are the reproducible current
state; generated reports/objects stay out of Git.

## Narrow-facing control and native 214 routing correction

The admitted declaration question is now bounded rather than inferred from
callee byte loads. A fresh wide-direction FighterOwnedObjectSpawn build retains
canonical 66/66 at 465190. A separate genuine closed source changes only its
three direction declarations (wrapper declaration/definition and manager virtual
signature) from int to unsigned char. The existing fighter-owned-object-spawn
unit's object-override comparison is also 66/66, canonical SHA256
`80aab8cb379377dc179c3e1311599ab890885fa92ffd5ecf075ff6c3df15a7fc`.
Both views are admitted; original nominal width is not uniquely recovered.
Neither the accepted provider source nor its unit is changed.

A separate complete caller changes only its facing formal to unsigned char;
layer remains int. It emits 43464 bytes/SHA256
`b046bb878a37b2375bc3b731a6061773e60c03e97ff84e8fdf2edf306595ad19`,
41894 unequal positions. Frame 418,16 table lengths/685 remap bytes and the
214/542/547/548 callback membership gaps persist. The control is unselected;
the public caller keeps its admitted int-facing view. Do not sweep width
combinations or claim the original formal from this result. Receipts are
`width-provider-baseline.json`, `provider-facing-byte-comparison.json`,
`width-baseline-full-audit.json`, and `facing-byte-*` in the existing scope.
The separate source changes and exact compiler commands are retained privately.

The first whole comparison also directed review to 214. Exact instructions
show that the active sequence range 1..4 encloses its flight-end condition:
4EB474/4EB47D send states outside that range directly to 4EB8E1's landing check.
The retained source had placed the flight-end gate outside that range and
could reset scratch instead of checking landing for 0/5/6. The correction keeps
the gate inside the active motion block. It also restores the timer re-read
after event 31 at 4EB38C, live field 13E/F4 checks after each virtual sequence call,
and live heading/peer reads at the actual later uses. In particular the four
motion sequence checks 4EB61B..4EB6B0 reload their conditions between calls;
the former cached velocity/sequence pair did not express those epochs.

A small native execution check now starts at the real root for sequences 0/5/6
and both values 0/1 of input 6C8, with counter 736=20 and spirit 482=1. Native
4351C0 executes and returns normally: frame counter 0->1 stays below duration 3,
and timer 1->2. There is no injected helper result, callback or branch. Both
native and candidate stop before the first 5F9310 landing or 435110 scratch body.
All six inputs agree in boundary, receiver, the observed 0x800-byte owner prefix,
helper trace and empty x87 stack/control. Gravity produces -2.5 for 5/6 and
leaves -2 for 0. The old 8dd4473a object fails precisely the three input 6C8=0
cases by choosing scratch reset instead of landing. This proves these bounded
prefixes, not active-flight behavior, subsequent landing results or real-game
reachability of the fixture combinations.

The current 3018-line source retains only the 214 instruction/epoch correction;
it does not select the narrow-facing caller control. Formal and independent
fresh-object full comparisons now agree at 44012 bytes, SHA256
`4fa62a2b837aa5a89b3dac35f0b1327db2062d3ad6f6aa5c201be31d672090b0`.
There are 41449 unmasked differing positions including the 68-byte size gap.
Frame 418/410, RETs124/128, direct calls 672/674 and indirect calls 160/163 remain.
The four physical direct-callee discrepancies are stage height 14/16, stage
predicate 6/7, zero motion 26/28 and wave dispatch 52/49 (candidate/native).
All 16 table lengths and all 685 remap bytes agree.214's per-action indirect
inventory is now 14/14; remaining mapped-case callback differences are 542,
547 and 548. Counts still ignore predicates and do not replace the full byte
comparison. The source stays identified/unselected with no new exact or
source-present credit. No accepted unit input changes and no new aggregate
cold acceptance is claimed.

The intermediate `action214-live-fields.obj` and formal/cold objects all emit
4fa62a2b. The frozen `action214-before.obj` is the 8dd4473a predecessor. Continue
from the public complete source and these actual residuals; keep the width control
separate and avoid unproved packet-size changes.

## Separate 542 terminal guards and common 547/548 exit

Exact target instructions distinguish two 542 action 9 terminal paths.
4F1019..4F1032 tests the zero timer/frame counters and sequence 4, then reaches
4ED95D's action 9 call 4ED966 and RET. The subsequent 4F1038..4F1061 guards
sequence 8 and reaches its own action 9 call 4F1070 and RET. The complete source
now preserves these two guards instead of OR-ing the sequences into one call.
The neighboring 543 legitimately has one shared terminal call and is unchanged.

Native 547 threshold 4F1860..4F1867 (timer>=30) and 548 threshold 4F1A9D..4F1AA4
(timer>=50) both enter 4F1B00. Their successful landing tests converge at 4F1AEC:
zero motion 45AF40, height 435D60, store ownerF0, then common next-block virtual
call 4F1B07. One source exit label now preserves that common continuation for
these four paths. The label is a reconstruction of observed control flow;
it is not evidence of the original source spelling. No initialization, helper
return value, assembly or padding was added.

Each question was first compiled independently from the preceding complete
44012-byte/4fa62a2b source, followed immediately by a whole-payload comparison:

| Complete-source control | Canonical bytes | SHA256 | Unmasked differences |
| --- | ---: | --- | ---: |
| Separate 542 guards only |44024|b66f790d40bd3dab413888fb835f7ce5ee325d37b6e4004f09ea49c37c96dbdb|41324|
| Common 547/548 exit only |43976|4af800f87ba6a11a2d9324f8b90480075c43c57ef437671163f3c7785209f0f4|41578|
| Both retained |43996|2655274b9cd5c98ee3a873aea3fa6e3f36cadd4c21c9e0e86ce44103380eb07c|41484|

The 542-only control closes its per-action virtual-call membership gap 5/5;
only 547/548 remain 3/4. The 547/548-only control closes both 3/3 gaps; only 542
remains 5/4. Combining the supported structures closes all mapped-case direct
and indirect call-count differences. These are conservative reachable-site
counts without predicate feasibility, not call execution counts or semantic
acceptance. The five special direct-dispatch arms remain outside this census.

Formal and independent fresh-object audits agree on the combined payload.
The full strict 44080-byte target comparison still fails at+8, frame 418/410,
with 41484 differing positions including the 84-byte size gap. Physical totals
remain 122/128 RETs,672/674 direct calls and 158/163 indirect calls; some global
counts are farther from the target than before. All 16 table lengths and all 685
primary remap bytes still agree. The changes are retained for observed local
control-flow structure, not because of an aggregate similarity improvement.
Both new objects also pass all six previously bounded 214 native prefixes.
No implemented/exact ledger addition or aggregate cold claim is made.

Receipts in the existing build scope: `exit542-split-*`, `exit547-548-common-*`,
`exits-formal-*`, `exits-cold-*`, and `exits-baseline-full-audit.json`.
The private controls start from checkpoint 589d2468, and their commands/source
are frozen in the corresponding analysis scope. Current public source is 3022
lines. The terminal-structure questions are now closed; next inspect actual
stack/packet lifetimes and separately review the five special direct arms,
without repeating guard-spelling trials or shrinking packets to force a frame.

## Direct-dispatch coverage and packet extent control

Separate inspection now covers the five action roots omitted from the primary
remap census. Their native/candidate entries in the retained 2655274b object are:

| Action | Target entry | Candidate entry | Indirect sites, target/candidate |
| --- | --- | --- | --- |
|300|4EC479|4EC34F|1/1|
|520|4EF082|4EEF50|3/3|
|795|4F4439|4F43E7|2/2|
|797|4F4597|4F4504|2/2|
|798|4F44B4|4F444B|2/2|

The outer comparisons at 4EA134,4EC516,4EF479 and subtraction at 4F4496 recover
these direct entries independently of the remap bytes. Conservative reachable
counts for every direct callee agree too.300's native directional gate uses 0,
0.5 damping clamps only below zero, and frame 2 emits event 27.520 preserves the
two timer 6/3 request arms, increment-before/after-scaled10 order, post-request
sequence reload, landing height->zero->sequence 8 order and the later action0
callback followed by a fresh sequence read.795 uses gravity from double 6C2A70,
event 30->sequence 1->height->zero on landing, otherwise frame->action700.
797/798 share event 30->sequence 3->height->vy 0 landing but separately clamp x to
480/800 and finish with action 0/700. The actual float/double constants at
6C0578/6C0EB0 are 480;6C3B38/6C3B30 are 800. This closes the census omission
and a bounded instruction review, not full callback, NaN or execution proof.
Call counts across all reviewed actions still do not explain global physical
sharing differences. Receipt: `direct-arms-call-ownership.json`.

Packet evidence is now stronger than decompiler variable adjacency. Let B be
ESP after the complete native prologue.570's two 827 requests use B+78 and store
only B+78/7C/80;571 uses B+6C with stores B+6C/70/74. Both pass count 4, and the
wrapper 465190 forwards it. Manager 4FAAD0 reads that count at 4FAB27, allocates
count*4 bytes and calls pinned memcpy 68AA30 at 4FAB62 with byte count 16. Its
source-pointer copy leaves no basis for treating the transmitted fourth word
as a hidden count unit or an ignored argument. No fourth-word initialization
was found in these local request paths; its incoming value remains unknown.
Mutually exclusive local spans and potential compiler overlap do not prove
an original array declaration boundary.

After this write/span/consumer review, one private complete-source control
changes only the two local arrays from four to three floats, retaining the real
count 4 at every call. It naturally emits frame 410 and moves the first mismatch
from+8 to+17. The complete payload remains 43996, SHA256
`08ce1a46c4b6aabf5369587035a29bbf0110acad9860115ad79b6caa4d93972e`,
with 41499 differing positions. All 16 table lengths,685 remap bytes and per-action
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
its conservatively reachable action entries. It covers all 685 primary-remap
values plus 300/520/795/797/798, including shared defaults. All 690 per-action
call-count comparisons agree for both the preceding 2655274b and new 0a47fcc9
objects. The only three physical direct calls outside these entries are the
pre-dispatch object 998 requests; no indirect call site is left unowned.
This checks census coverage rather than predicate feasibility or behavior.

Physical partition differences persist even when aggregate counts agree.
For example the preceding candidate merges the wave 2 sites for 410/411, whereas
the target gives 410 its own site and shares 411/412/415/416 at 4EE6BD. Inspection
of those actual paths, rather than attempts to force their shared spelling,
finds three publication-order errors in the retained source:

| Request arm | Exact target order after spawn | Prior source difference |
| --- | --- | --- |
|410|wave 4EDE67 -> adjust 4EDE75 -> scale 4EDE7E -> dword 180=1 at 4EDE83|Wrote 180 before adjust/scale|
|411/412|wave 4EE6BD -> dword 180=1 at 4EE6C9 -> adjust 4EE6D1 -> scale 4EE6DA|Already correct|
|414|wave 4EE346 -> adjust 4EE354 -> dword 180=1 at 4EE35D -> scale 4EE363|Already correct|
|415/416|Same 4EE6BD common continuation as 411/412|Wrote 180 after adjust|

Only 410/415/416 source ordering changes. The historical 410 ledger note had
incorrectly placed its publication before adjust; that note is corrected by
this exact instruction review. The value is 1 in the observed target paths:
EBP is initialized to 1 at 4E9F73 and is preserved into these store sites. The
source also writes the same dword literal 1. No new call, flag, header, type,
initialization, source selection or byte mask is introduced.

A public reproducible static diagnostic now extracts the six action entries
from each complete payload's actual mid-switch metadata and enumerates local
request traces to RET. Calls are opaque fallthroughs, branch predicates are
unconstrained, and the recorded events are spawn/wave/adjust/scale and the
four-byte180 store. It checks ordering only: it neither executes nor injects
callback results, and it does not prove callback behavior, store-value dataflow
or whole-function equivalence. The new complete object passes all six; the
frozen preceding object fails precisely 410/415/416, a negative control for the
original error rather than a test that mirrors the new source text.

The single private complete-source correction was compared immediately, before
retention. Formal and independent fresh-object comparisons now agree on 44108
bytes, canonical SHA256
`0a47fcc9df818389722356ce1abdc02961d28d06aeb3c22d7e1c5eedaf3694bd`.
The strict whole 44080-byte target comparison remains nonexact at+8/frame418
versus 410, with 41308 unmasked differences including 28 extra candidate bytes.
Physical totals are 125/128 RETs,679/674 direct and 158/163 indirect calls. The
new global direct total is farther from target, although the corrected local
orders now agree; call totals are not an acceptance metric. All 16 table lengths
and 685 primary remap bytes still agree. Both independent objects also pass all
six bounded 214 execution prefixes. No exact/source-present credit is added.

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

The 197/198 zero-motion site partition is separately reviewed: both native
entries resolve->advance, branch through the same action700/status3 or
action0/optional1 paths, then gate zero motion at framecounter0/frame8 and
facing comparison at framecounter0/frame13. Native 197 zero call 4EA700 and 198
call 4EA77B remain distinct despite the source compiler sharing one. The local
field tests and callback order show no discrepancy requiring a source split.
Likewise 208 and 220 have separate native predicate calls 4EB1D4/4EBA0E and frame
calls 4EB235/4EBA6F. Both perform crossed-surface->action 10->height->zero on the
landing branch, then surface/positive-vy status 2, signed sequence>0 damping
clamped at-20, advance and the sequence 1/timer0 initialization. This is bounded
instruction review, not full execution or a reason to force distinct sites.

One independent operand-width issue is visible throughout the full caller.
All 42 native 5F9310 calls and all 7 native 435DC0 calls immediately TEST AL,AL.
The preceding 0a47fcc9 caller instead has 22+6 TEST EAX,EAX sites; another 20
already testAL. Inspection of the actual accepted providers resolves whether
this is a semantic error:435DC0's42-byte body returns through full EAX=1 at
435DDB or EAX=0 at 435DE4;5F9310's64-byte body returns through full EAX=1 at
5F933F or EAX=0 at 5F9349. Thus both wide and byte tests have the same truth value
for these real callees. Original nominal return width remains unproved; their
int declarations and accepted implementations are unchanged.

One complete-source control explicitly projects these results to unsigned char
at the 29 previously wide source expressions (22 crossed calls and 7 surface
calls, with 208/220 merged by compilation). Its whole canonical payload differs
from 0a47fcc9 in exactly 28 bytes, all opcode 85->84, changing TEST EAX,EAX to
TEST AL,AL. No instruction length, relocation, table, remap, call site, frame
allocation or other byte changes. The retained source expresses this observed
caller consumption without inventing a narrow external ABI. All 48 emitted
predicate sites now testAL; native has 49 because its 208/220 sites are separate.
The complete audit now reports each predicate call's immediate test register
for both target and candidate, leaving unrecognized next instructions explicit.
The diagnostic neither masks these opcodes nor changes the exactness decision.

Formal and independent fresh-object reports agree at 44108 bytes, SHA256
`1bbd8acb28131ca4c416f5a9f22b13a5ab62c6d6ab64c779dddbe809dc04ad66`.
The whole strict target comparison still fails at+8/frame418 versus 410,
41308 differing positions including 28 extra candidate bytes.125/128 RETs,
679/674 direct calls and 158/163 indirect calls are unchanged. All 16 table
lengths and 685 remap bytes agree, and all 690 primary/direct action call counts
remain aligned. Both fresh objects retain the six publication-order checks
and six 214 execution-prefix checks. No exact/source-present credit is added.

Receipts: `predicate-provider-target.asm` pins only the complete 42/64-byte
providers; `predicate-low-byte-*`, `predicate-formal-*`, `predicate-cold-*`,
`predicate-old-full-audit.json` and `sharing-predicate.json` retain the whole
comparisons and diagnostic widths. The 28-byte-only delta is recorded in
`predicate-low-byte-byte-delta.json`. Private `predicate-before.cpp` freezes
0a47fcc9; `predicate-low-byte.cpp` is the single 29-expression control. This
consumption question and the two reviewed site-sharing pairs are closed;
continue with independent lifetime/field-read evidence, not type permutations.

## Request-loop arithmetic and root case layout

The 525/526 request family now has a separate instruction review. Both native
entries resolve, clear 750 from 6C0/6C4, take the sequence 1/timer>15 block exit,
advance, and preserve the sequence 0/frame8 block->effect 62 early return. Their
first loops reload signed byte 609 after each spawn, then wave 3->publish 180=1->
adjust(200,120)->scale 50 and continue with fresh timer/frame/sequence checks.
The sequence 1/timer0 action0 branch returns; the sequence 2/frame2 second loops
finish through wave 4F0707, publish 4F070C and the shared adjust 4F1C94/scale4F1C9D
return tail. The source expresses those continuations and callback epochs;
site sharing alone supplies no reason to force common labels.

One actual arithmetic association differs in 526's first loop. Native 4F04E1
loads n and 4F04E5 doubles it with FADD ST0,ST0 before loading double 10 at 4F04E9.
4F04F7 adds the shared 2n for packet 0, then 4F0504 adds double 21 to the same 2n for
packet 1. The prior source's10.0+n+n instead makes two successive additions to
10 before separately doubling n for packet 1. The single private complete-source
control changes only this expression to(n+n)+10.0. Its output now has that
shared doubling before the 10 addition. For this first loop n starts at 0 and
increments exactly by 1 while n<signed 609+1<=128; all participating sums are
small exact integers. This restores observed arithmetic order without claiming
an input-domain numeric bug. The other loop expressions are unchanged.

An independent whole-source layout question is also tested. The retained
manual source had 400/500 blocks after 695/696, whereas the target's root entries
mostly follow numeric order. A private brace-aware parser extracts 108 root
case/default groups with 110 explicit numeric labels, keeps alias groups
intact, and records each group's original text hash. All group texts are
preserved by numeric permutation. Direct return/goto terminal depths are
checked;720/721/730's terminal switches, including every default return, are
reviewed separately. There is no root-case fallthrough to change. The previous
source ordering has 130 inverted pairs of native entry addresses; numeric order
has 9. This supports a controlled layout hypothesis; compiler tail sharing means
it does not prove the original lexical order. No register tie, dummy operation,
new local, padding, flag or header change is used.

Each property was first compared independently from complete 1bbd8acb:

| Complete control | Bytes | Canonical SHA256 | Unmasked differences |
| --- | ---: | --- | ---: |
|526 association only|44108|d43fa4a177db32e5589b7baaafb3cf61f4a09b3764d7dbf70083d9fba8d870cd|41336|
|Numeric case groups only|44068|95ad941925fe54aab7b6eef067025d388c1131fca4de56aa9636bd57391291d8|40625|
|Both retained|44068|ef85ed758ed4f74b556b501db87b407174f3af2028ba1cee383ef013d678feb1|40778|

Formal and independent fresh-object reports for the retained source agree.
The first destination table starts 42720 bytes from entry, versus 42724 target;
the complete strict payload comparison still fails at+8/frame418 versus 410.
It includes all 12 missing candidate bytes, without waiving the 8 target INT3
whose COFF/linker ownership remains separately unknown.125 prior RETs become
124 versus 128 target; direct calls 677/674 and indirect 158/163 still differ.
Some individual physical counts become farther from target. All 16 table
lengths and 685 remap bytes agree, all 690 action call counts agree, all 48 emitted
predicate tests useAL, publication ordering 6/6 passes and 214 execution-prefix
checks 6/6 pass. Neither similar payload size nor the layout hypothesis grants
implemented/exact credit. No accepted unit input changes or new aggregate cold
claim is made.

Receipts in the existing build scope: `counter-tail-baseline-full-audit.json`,
`loop526-association-*`, `case-order-numeric-*`, `case-order-association-*`,
`case-order-source-facts.json`, `layout-formal-*`, `layout-cold-*` and
`sharing-layout.json`. Private `case-order.py` is pinned to the frozen
`counter-tail-before.cpp` source and keeps the block hashes and terminal checks.
The retained public 3022-line source differs from its numeric permutation only
in the one 526 expression. These two controls are closed; continue from actual
field-read/lifetime evidence rather than another ordering or spelling sweep.

## Shared request intermediate and bounded checkpoint

A new dataflow check first inspects the currentef85ed75 candidate. In 525's
first loop it computes 2n, stores it to float at 4F00F2, then reloads the same
word at 4F00FB after stack pushes. In 526's second loop the analogous store/load
is 4F05D3/4F05DC. By contrast native 4F01B1..4F01DA and 4F064B..4F0674 keep 2n in
x87 while forming2+2n and 2n+21, with no float store of the intermediate. Dumps
are decoded from the complete function entry before selecting instructions;
stack pushes are retained so repeated ESP-relative slots are not mistaken for
different objects.

One private whole-source control replaces only those two temporary uses of
packet[1] with a genuine double twice_n=n*2.0, consumed by both final packet
fields. This removes the observed float store/reload in both loops. The local
is live and used; no frame padding, volatile tie, ABI declaration, loop bound,
callback, array extent or compiler option changes. The source spelling of the
original shared value remains unknown. Since these loops increment float n
from 0 while comparing against signed byte 609+1 or+3, body n is a small exact
integer 0..127 or 0..129. The old intermediate rounding was not a demonstrated
numeric behavior bug in that domain.

The complete control was compared immediately and emits 44032 bytes, SHA256
`4d312925be3f754e27ef0f963632f8034ca587c6b09be35dc7a7ff8aefd5bd1d`.
Formal and independent fresh-object full, publication-order and 214-prefix
reports agree. The full 44080-byte target comparison remains nonexact:41054
unmasked differing positions including 48 missing candidate bytes, first+8 and
frame 418/410. Code-to-first-table42684/42724,124/128 RETs,677/674 direct and
158/163 indirect calls remain. All 16 table lengths,685 remap bytes and 690
action call counts agree;48 predicate tests useAL. Publication checks 6/6 and
214 execution-prefix checks 6/6 still pass. Other x87 ordering/lifetimes remain
different: the candidate carries an extra constant 2 across spawn, whereas
the native calculation consumes its 2 while forming packet 0. Full x87
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

## Action 214 active steering prefix, 2026-11-04

A fresh build of the complete current source retains the 44,032-byte canonical
candidate SHA-256 `4d312925be3f754e27ef0f963632f8034ca587c6b09be35dc7a7ff8aefd5bd1d`.
A provenance-gated Unicorn observer executes both the original root and this
candidate through the actual `0x4351C0` nonready frame helper, then stops at
the first cdecl cosine lookup before its body. Across 432 combinations of
active sequences 1–4, directional input, facing, normal/slow turn rate and
three boundary angles, both roots agree with an independent steering model
and each other on object-prefix bytes and cosine argument. A mutation that
substitutes speed for the angle argument is detected. The six prior inactive
prefix cases continue to pass.

This first check is bounded prefix evidence only; it stops before cosine and does
not itself prove later behavior. No source-selection or exact credit is added.

### Native lookup execution

A second observer continues 864 active cases through the actual
native cosine and sine routines and their called runtime helpers, stopping
before the counter-adjust body. Both the original root and reconstructed
root agree on direction, angle, velocity, speed, call order and counter-adjust
arguments, and a wrong velocity-factor mutation is detected. Both use a
synthetic constant and varying 3600-entry lookup tables, not a table produced
by game startup; the source versions of the lookup helpers are not exercised. No
claim is made about actual table contents, subsequent effects or landing,
full-game execution, source selection or byte-exactness. Run
`scripts/repo-python -m unittest discover -s tests -p
'test_alice_action214*.py'`.

### Through counter adjustment

A third bounded observer continues through the actual native 74-byte counter
adjustment at `0x0046BF30` and stops before the next sequence, scratch-reset
or landing helper. Across 1,728 combinations including two counter values and
both synthetic lookup tables, original and reconstructed roots agree with an
independent model on counter/floor, sprite rotation, next boundary and sequence
argument. A changed adjustment amount is detected. The original angle and
counter helpers run in both traces; their source implementations are not tested
here. Tables remain synthetic, the next helper bodies are not executed and no
full-game or exact-root claim follows. Run `scripts/repo-python -m unittest
discover -s tests -p 'test_alice_action214*.py'`.

### Through landing and stage height

A further bounded observer executes the native landing predicate `0x005F9310`
and its actual stage-height lookup `0x00435D60` after the previously tested
frame, angle and counter helpers. On 648 combinations of direction, turning
rate, synthetic angle tables, height and three x positions, original and
reconstructed roots agree with an independent model; 96 reach the landed
scratch-reset boundary and the rest return from the root. An inverted landing
branch mutation is detected. The stage-height table is synthetic and flat,
and the chosen sequences avoid earlier sequence transitions. The scratch
reset/action body, real stage initialization and full game remain untested.
This does not select the source or change strict exact-byte credit.

### Through landed scratch reset

The 96 crossed-stage cases above now continue through the actual native
`0x00435110` scratch reset, stopping at the action-215 virtual call. Both
roots agree on nine reset fields and the action argument; an altered action
argument is detected. Initial scratch fields are seeded with nonzero sentinels
so this checks actual reset writes. Angle and flat terrain tables remain
synthetic; the action-215 body and full-game execution are not covered. The
root remains unselected and nonexact. All ten focused action-214 tests pass.

## Spawn layer argument width, 2026-11-05

The original action 418 effect-object requests at 4EE84A and 4EE967 push
`-1` as the complete 32-bit layer argument. The selected source had passed
`255` through the admitted int-layer declaration. Although both have the same
low byte, they are not the same forwarded 32-bit argument. The source now
passes `-1` at both sites.

The same native stack argument occurs at all 39 physical request sites for
objects 820, 827, 830, 851, 852, 854, 855, 856, 900, 901 and 902, including
shared tails. Forty further source sites use those requests and now pass `-1`.
This observation is about the actual argument bits, not the unknown original
formal type. The separately identified Alice manager reads only the low layer
byte at 4FAB76 and publishes it at 4FABA8, so no ordinary gameplay difference
is asserted for that manager.

A focused VC8 rebuild emits signed `push -1` at the changed sites. The full callable
remains nonexact from +8; the section tail is 43916 bytes versus the 42721-byte
native callable. The candidate remains unselected, with no exact credit.

## Skill-level switch signedness (2026-11-06)

Eight native switch sites beginning at `0x4EF0E0` sign-extend the byte at `0x605` before selecting cases 0 through 4. The input policy independently uses a signed view of the same field. The eight source switches now do likewise; the fresh candidate emits `movsx` at all eight sites. All 256 byte values still select the same paths because values outside 0–4 take the default. The full focused candidate remains nonexact (43916-byte section tail against a 42721-byte main span, first mismatch +8); no exact credit is claimed.

### Integer gate thresholds

Four original signed integer gates at `0x4F1992`, `0x4F24F1`, `0x4F29A1`, and `0x4F2EC7` compare against 10, 60, 80, and 480. Equivalent source forms recover their local comparison and branch instructions without changing integer behavior. The complete function remains non-exact; its candidate section is 43,916 bytes.

Four repeated timer gates at `0x4F00BE`, `0x4F03EE`, `0x4F1BC5`, and `0x4F1C11` compare against 15 or 12 in the original. Equivalent source forms recover their local signed comparisons and branches. Integer behavior is unchanged; the 43,916-byte candidate remains non-exact.

The timer gates at `0x4F250D` and `0x4F29BD` and spawn-count gate at `0x4F2B7A` now use the equivalent original bounds 18 and 7. Focused compilation recovers their local signed comparisons and branches. Integer behavior is unchanged; the complete candidate remains non-exact.

## Current raw-PE matching findings, 2026-11-26

The current target-backed corrections are in the complete, unselected Alice
source. Actions 308/309 must read facing inside each iteration of their six
object-849 requests. Native requests at `4ECC7B` and `4ECDF1` loop back through
`4ECBFA` and `4ECD6A`, respectively, with a fresh byte-104 load before the next request;
the former source cached facing across all six callbacks. Negating the converted
float index before multiplying by double 60 also preserves the native
`fild; fchs; fmul` calculation.

Action 321 passes zero to `478EE0` at `4ED056`, subtracts double 1.0 from
horizontal velocity (`6CD160`, used at `4ED077`), and stores float 10.0
(`6D6EEC`, loaded at `4ED0DA`). The former values 1, 0.5 and 7.5 were incorrect.
Action 402's stores at `4ED676`, `4ED684` and `4ED693` form `{0,0,7}`;
the former source transposed the last two elements.

The raw switch manifest now includes all thirteen nested tables: eight
five-destination difficulty tables and five four-destination story tables.
Together with the primary maps there are sixteen tables, 165 destination words
and 685 byte indices. Two nested tables occupy `[4F48EC,4F4914)`, between the
mid index map and the high destination table. The final table ends at `4F4B78`;
eight `INT3` bytes precede the next function at `4F4B80`. Map them with:

```bash
scripts/repo-python scripts/map-giant-action-switches.py alice-vslot28 --json
```

Private typed reconstruction recovers further useful source constraints:

- Independent timer/frame guards in 412, 507/508 and 414–416 preserve the native
  timer reads. Separate entry guards in 414–416 and 543 preserve time-counter
  lifetimes; cached sequence locals in 547/548 remove native comparisons.
- In 570/571, select the angle with `if (index > 0) ... else 0`, and assign
  packet element two once per conditional arm. Initializing either value before
  its branch adds stores absent from the target. These corrections retain the
  real count-four requests and their unwritten fourth word.
- Updating 310's velocity member directly before widening it for predictive
  landing recovers its native float temporary; an extra named float changes
  that temporary's home.

The current three-float-storage candidate recovers the native `0x410` frame
and the complete packet-home census. Restoring four floats to 570/571 produces
`0x418` and moves many unrelated homes, including the two request buffers.
This strengthens the twelve-byte storage hypothesis, but the original
array declaration remains unknown: the native manager really copies sixteen
bytes. No array change has been selected in the retained source.

The retained-source checkpoint's complete canonical comparison remains nonexact
at `+8`, `0x418/0x410`. The private typed candidate also remains nonexact despite
matching many local instruction paths: its physical tail sharing, call-site
counts and switch addresses differ. The unresolved areas include 404/406's
cached zero timer value, the shared 411/412/415/416 request suffix and 540's final
request. The internal three-byte alignment instruction and terminal eight-byte
alignment scope must be settled for full acceptance.

Current private evidence is in `build/alice-root-work-codex/`: `CURRENT.md`,
`target-map.json`, `checkpoint-canonical.json`, `local-facts-target.txt`,
`loop-facing-target.txt`, and the named typed-source comparison reports.
Reproduce the retained-source comparison with:

```bash
WINEDEBUG=-all DISPLAY= WAYLAND_DISPLAY= scripts/repo-python scripts/build.py --unit exact-first-alice-fighter-update --compare --json
```
