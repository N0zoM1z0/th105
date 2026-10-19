# ReimuObject810/811/812 source and conditional loop evidence

This page records the e10e0c7 checkpoint. The
[815/816/817 follow-up](REIMU_OBJECT_815_817_2026_10_20.md) records current source
pins and expanded execution/argument evidence.

This extends the [b5855c6 projectile checkpoint](REIMU_OBJECT_PROJECTILES_2026_10_20.md)
inside authored `ReimuObject @496540`. The target remains original Japanese
1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Owned bytes remain46128 across three ranges; no new compiler boundary is inferred.

## Observed control flow and source hypotheses

The complete target CFG auditor is rerun:10670 instructions,22 switches,
404 actual direct CALLs to25 targets and68 RETs. The main-span shared-callee
ranker is rerun as candidate evidence, preserving its documented remote-chunk
limit. The new handwritten source covers the three top-level owners:

| Action | Target entry | Local span to next owner |
| --- | --- | ---: |
|810|49734C|1177|
|811|4977E5|1507|
|812|497DC8|1376|

These4060 local bytes include shared destinations; the spans are not original
functions or accepted partial exact units. Source now handles13 concrete arms
and real defaults, with28 concrete arms still unsupported. The coverage bool
remains separate from the original void update ABI.

810 has sequential independent sequence checks. A sequence0 next-block call
can enter sequence1 logic immediately. Speed subtracts1.5 and clamps/counts at
ordered **<=0**, then advances after signed state364 exceeds15. Sequence1/2
phase processing uses limit20 and may select3/return. Sequence2 uses real
steering, periodic three-word requests, and a **signed-byte** index check before
next-block. Sequence3/4 alpha underflow retires but continues into movement and
animation checks; alpha is explicitly cleared on those paths.

811's sequence0 has owner gating, fresh990 secondary setup and actual limit15
processing. Its periodic request draws **Y before X** through4067D0. This
routine computes `u32 / (UINT_MAX / range)`, not modulo; the actual routine and
MT next instructions execute. A zero index releases/selects2 and initiates
three same-buffer requests. Later calls and random360 draws remain conditional
caller-source hypotheses because native execution stops at the first request.
The second word is not reinitialized between those calls; callee mutation is
not ruled out. Sequence1 observes object pointer34C, copies its position and
parameter heading, and retires when that object's sequence is2. Sequence2
shrinks,3/4 fade channel111 before alpha, and5 moves/fades with alpha<=10
retirement without clearing alpha. The final lower Y bound is-120.

812 dispatches through a switch: its sequence0 next-block does **not** run
sequence1 during that same dispatch. Sequence1 clamps/counts at ordered<=0,
has periodic count3 requests and a state>3 burst, otherwise limit30/phase
selection. Sequence2 uses count3 periodic requests, real orientation lookup
and a directional component scaled by state370, clamped after subtracting.25;
limit3 can reset phase before select3 is checked. Sequence3/4 fade and advance
without movement or clearing velocities. Both810/812 use entry lower Y=-240.

Observed widths justify byte channel111 and a pointer view at34C; size388 and
all earlier offsets remain asserted. The pointer's original C++ class and
ownership spelling remain unknown. No accepted shared header, helper, compiler
profile, object partition or public relocation mapping changes.

The direct Ghidra C hypothesis rewrites810 bounds as ordered conjunctions and
prints growth as `scale>=1` with an else. Those forms do not preserve the raw
unordered cases. Source follows raw x87 flags; NaN position/scale cases remain
in the execution matrix. Ghidra types, array names and local sharing are not
promoted to original-source facts.

## Native evidence and limits

A fresh baseline build passes0/6292 before edits. The extended public audit
with `--sequences` passes **0/12032**, preserving all6292 earlier inputs.
Input SHA256 is
`91e44d77959e9f407096294b663e982af00c1c4516f4798ce902a9645bacdbff`.
The5740 new inputs comprise3780 state,360 zero-speed,24 growth,240 channel/alpha,
180 parent,40 shrink,192 orbit,420 bounds,72 random and432 timer cases.
They include both x87 precisions, unordered position/scale/speed, signed-byte
indices128/255, signed-short wrap, exact zero and timer thresholds, null/sequence2
parents and actual seeds0/5489/FFFFFFFF.

| Actual endpoint | Inputs |
| --- | ---: |
|Real RET with stack/callee-saved/x87 checks|11508|
|64CCB0 spawn entry|345|
|465190 owned spawn entry|75|
|435240 effect entry|26|
|496420 secondary setup entry|78|

These inputs visit1850 target root instruction addresses and1678 staging
addresses. Actual helpers include364 MT next calls,96 scaled random calls,
473 steering chains,2177 state6 timer entries and8861 animation advances.
The original MT seeder/orientation initializer generate fixtures. Actor388,
owner800,16 parameter bytes, distinct supplied object388 and its16 parameter
bytes, RNG state/index, helper trace, endpoint arguments/payload and x87
control word/TOP/tags are compared. Runtime writes to the supplied followed
object/parameters are rejected. No replacement helper return is supplied.

The null secondary fixture does not prove renderer destruction or a returning
setup. Generations stop at actual entry; arbitrary aliases, unmasked exceptions,
other animation resources, returning-world chains, all28 remaining arms and
full-root semantics/bytes remain open.

Current CRLF compilation pins under VC8 `/O2 /GS- /GR /EHsc /MT`:

| Artifact | SHA256 |
| --- | --- |
|Staging CPP|`5601557b4345423ba66ca6dc2d616700e317734d69ed8033bfa761c4584bb20e`|
|Staging header|`4de397f4b0ae9942bf9919f201e5a0bd3439a3e141b1e6a5f3b5dddb3afd5475`|
|Observed fresh object|`e1ce985e2d0e04bdc5c760cf1ca2ab97a11cc5543e4cc1005ff927e0e2cfdc2f`|
|7756-byte replay at800000|`f9bde16d1302dda5ee04af5f6b09d10d5804f1ff801310098859ac9fde285360`|

The object-only audit keeps build provenance unverified. Fresh compilation is
a separate local observation; this replay is not a target-equal root.

##812 loop caller contract

`scripts/audit-reimu-object-812-loop.py` checks the target and compiled source
without executing or making a world call return. The narrow instruction
interpreter starts a loop body with symbolic current sector and derives:

| Fact | Target | Source |
| --- | --- | --- |
|Loop head|49804E|80166D|
|Request instruction|4980B8|8016C5|
|Backedge|4980DE|8016EB|
|Unescaped float counter, baseline ESP offset|18h|10h|
|Four-word buffer, baseline ESP offset|90h|18h|
|Payload|current parameter0,0,2,sector*45+current parameter0|same expressions|
|Counter initialization / increment / exclusive limit|0 /1 /8|0 /1 /8|

It checks dword stores/loads, double1 increment, float8 bound, actual x87
FCOM/FNSTSW/TEST5/JNP polarity, reviewed initialization/backedge, no body branch or
extra call, receiver, action812, variant1, unsigned facing, position reads and
count4. All four payload words are written each iteration. The counter is
distinct from the passed payload and not overwritten by the body. Actual
callee64CCFB is RET1C, consistent with the seven argument words.

This establishes eight iterations **conditional on normal ABI returns that
preserve the unescaped caller counter**. It does not prove that a world request
returns. Each iteration rereads actor/parameter values; it does not assert
eight absolute angles relative to one immutable initial heading. The native
root matrix stops at the earlier count3 request. Five tests reject missing
loops, limit7, step2 and angle90 evidence and check the current target contract.

##808 compiler constant and wrong-source controls

The larger source hoists variant1 into EBP at800027 before the primary indexed
jump. The earlier808 checker starts at FLDZ and cannot infer that value from
its local window. Its first rejection is an audit context gap, not a source
behavior discrepancy. The extended checker decodes action-800, maximum199,
the byte-index/destination tables and808 entry80093E. All26 decoded nodes on
case-to-window paths preserve EBP through window8009AE; external calls are
conditional normal ABI returns. It supplies the observed constant to the local
buffer analysis and retains payload invalidation after the first call.

Four new tests distinguish unreachable clobbers and return-only epilogues from
real conditional/partial-register clobbers. The current positive808 audit
passes; a freshly compiled wrong second-word assignment is rejected for the
payload rewrite, after qualifying the hoisted constant. Original C++ local
identity and returning-world effects remain unknown.

Each of the first four controls compiles independently and runs all12032 native
inputs. The fifth is a fresh compiled808 caller regression check.

| Deliberate source error | Native differences /12032 | Caller audit |
| --- | ---: | --- |
|810 independent sequence1 `if` changed to `else if`|176|not needed|
|812 ordered speed `<=0` changed to `<0`|30|not needed|
|811 first32-range draw changed to MT modulo32|48|not needed|
|812 sector limit8 changed to7|0|rejects changed guard|
|808 between-call third-word assignment changed to second-word assignment|not rerun|rejects payload rewrite|

The seven-iteration control keeps the native first-request result unchanged.
Its compiler changes both the bound and guard form, which the caller checker
rejects. This is a phase-specific counterexample to extrapolating first-entry
native evidence, not a general classification of every possible loop spelling.
Generated reports and exact mutation/source pins remain below the build
directory; the selected source/header hashes above stay unchanged.

## Reproduction and database safety

```bash
taskset -c 0 nice -n 10 scripts/compile-unit.sh src/characters/ReimuObjectActionStateStaging.cpp build/reimu-object-sequences-20261020/candidate.obj
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-scalar-actions.py build/reimu-object-sequences-20261020/candidate.obj --sequences --output-dir build/reimu-object-sequences-20261020/positive
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-812-loop.py build/reimu-object-sequences-20261020/candidate.obj
python3 -m unittest discover -s tests -p 'test_reimu_object*py'
```

Fresh direct read-only Ghidra re-attests executable/import identity, entry,
mapped text, root extent and vtable. The128MiB/CPU0/nice10 export completes;
all nine primary DB pins remain unchanged and the alias is removed. The failed
IDA metadata preflight supplies no semantics. No factory adapter or byte patch
is used. Generated/private recipes stay below the matching build/analysis
directories; VC8 builds are serial. No root implementation row, match unit or
exact credit is added. Next recover815/816/817, then the other25 concrete arms.
Fighter478FA0 and Object-entry4A1CE0 checkpoints remain unchanged.
