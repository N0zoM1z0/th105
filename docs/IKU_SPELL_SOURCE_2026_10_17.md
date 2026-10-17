# Iku actions600–610: eight staged C++ action bodies

> Current source: `src/characters/IkuActionStateUpper.cpp`. The original family
> file was consolidated after the measurements recorded below. Those receipts
> describe the earlier source; fresh combined-dispatch and preserved-family
> results are in [the unified upper-action checkpoint](IKU_UPPER_SOURCE_2026_10_17.md).

`src/characters/IkuSpellActions.cpp` recovers complete source hypotheses for
actions600/601/602/603/606/607/609/610 inside `Iku_dispatch_action_state_vslot28
@ 620920`. Together with the [object818 family](IKU_OBJECT818_SOURCE_2026_10_17.md),
12 of the root's110 nondefault action IDs now have staged bodies. The other98
and the root prelude/default still need complete source integration. The root
remains source-incomplete/nonexact; no implemented/match unit or partial byte
credit is added.

## Observed target facts

The only executable is Japanese TH10.5 v1.06a SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`,
root SHA-256 `abc831c6ccd95986bed811694f532ad8c8b92cb49702a7f6ce4de100b8a73dea`.
`scripts/audit-iku-spell-actions.py` re-attests the complete59038-byte root and
compressed action entries, then closes every direct edge from these eight
entries, assuming reviewed callees return normally. All1214 physical case
instructions are reached. The closure adds19 shared-tail instructions/27
bytes, giving1233 instructions/4739 unique bytes. These are regions of one
giant function, not eight compiler functions.

| Action | Physical entry | Physical bytes | Main source contract |
| --- | --- | ---: | --- |
| 600 | 62BDC2 | 336 | landing before texture; object850 |
| 601 | 62BF12 | 800 | rounded damping, signed counters, object851 and815 ring |
| 602 | 62C232 | 999 | object852 setup/ring and unsigned periodic offset |
| 603 | 62C619 | 397 | sequence1 counter>=32 skips animation advance; object853 |
| 606 | 62C7A6 | 373 | sequence1 entry changes action0; object856 |
| 607 | 62C91B | 317 | frame5/11 gates before animation advance; object857 |
| 609 | 62CA58 | 460 | sequence1 counter>=20 skips animation advance; object859 pair |
| 610 | 62CC24 | 1030 | signed counter%20 gates before advance; object860 triplets |

The contiguous physical interval `[62BDC2,62D02A)` has4712 bytes and20 static
spawn calls. The fact packet records every call, all27 x87 literal operands'
widths/values/addresses, loop carriers and threshold/branch witnesses. In
particular,601's effect height is the eight-byte190.0 at6C4D60, not a value
inferred from another action. Other source literals preserve their observed
float/double widths.

Both ring counters are int32 EDI, with a DWORD stack carrier loaded by FILD:
initial0, step45, signed bound<360, eight iterations. The decompiler's float
loop variable was a type hypothesis. Payload angle comparison uses the ordered
inclusive range0..180 for variant1; outside/unordered uses-1. The checker pins
both x87 status-word/branch sequences. The angle is not normalized modulo360.

601 rounds its velocity subtraction by double0.75 into a float before the
clamp, uses signed frame/WORD/byte tests and preserves+730 wrap. 602 preserves
the [previously proved](IKU_RANDOM_FLOAT_TYPES_2026_10_17.md) unsigned selector400
minus200 and keeps the conversion live through the X addition. Its selector500
Y computation and float store precede selector400. The accepted selector's
int-return interface is unchanged; the caller explicitly interprets it as
unsigned. Fresh `cross-v106a-outcome-random` comparison is canonical27/27.

## Source and working analysis

The new partial view inherits the existing animation interface without changing
the shared header. It uses a bool staging method to report handled actions;
it does not impersonate the void root or prove an original helper/TU boundary.
Every action was reviewed against raw instructions, including state reads
after callbacks, virtual dispatch, payload reuse and shared returns. Decompiler
output was used only as a hypothesis, without mechanical source transcription.

A sequential direct Ghidra read-only clone independently re-attests imported
PE identity, entry68B9D2, full mapped `.text`, root bytes,58 receiver components,
30 helper ABIs,177 virtual target sets and ST0/EAX conversion storage. Primary-project hashes remain unchanged; the clone is removed. There are no analysis metadata or target-byte writes in this batch.

## Native source checks

`scripts/probe-iku-spell-actions.py` uses the existing COFF execution machinery
with explicit family/interface parameters. The default object818 path retains
zero differences on its452-case regression and the same target-output SHA-256.
All generated sources/objects/receipts remain below `build/`. The new source
build uses SHA-pinned VC8 `/O2 /GS- /GR /EHsc /MT`; source/header/object hashes
are checked after native execution.

Both sides execute the genuine root prelude to the selected case. The source
side then invokes its compiled staging method on that actor state. Seed/warm
draws and MT/selectors are original instructions; cached seeds contain their
actual generated states. The fixture supplies a real checked texture deque,
flat stage, unexpired frames and zero wave handles. Indexed event23 is verified
as zero in the target table; both real event functions and the audio service's
real zero-handle return execute. No helper result or target instruction is
replaced. This reaches the actual effect115 arguments after event dispatch.

The final7833-case matrix has **zero differences** in the complete7B8 actor
view, helper arguments/order and intermediate+180 state, conversion inputs,
texture publication and full RNG-state digest. It reaches genuine RET in4156
cases, first spawn entry in3466, effect115 entry in192, action0 entry in1 and
next-block entry in18. Every observed boundary has an empty x87 stack and
unchanged control word; RET additionally checks stack+4 and callee-saved
registers. It visits904 original root instructions, including prelude/shared
tails, not all1233 family or15132 root instructions.

Input SHA-256:
`53a4e6491f2d525d87151ffa489c1183eeb830b3caadd608a8000f78fda079e7`;
target-output SHA-256:
`b5d60dc8310dabaf560772bd51c717233e602be618899d6470299f0d141d1b2f`.
The smaller741-case smoke passes as well. The signed-offset and early-offset
source controls differ16/741 and8/741 respectively.

The unsigned/signed counter tests include negative/overflowing WORD values,
signed byte184 limits, finite/NaN/infinite velocity values and frame6/7/11/12
clamps. The periodic602 axis reuses all36 genuine seeds, seven X positions,
both facings, counters5/35 and PC53/64; selector400 endpoints0/199/200/201/400
and the late-rounding discriminator at X1000 are retained. Threshold tests
include negative counter values and boundaries20/32/60/120. Effect coordinates
are checked for both facings, stage X boundaries and grounded/snap-to-ground Y.

The source controls deliberately change only602's unsigned offset type or
insert an observable float store before adding X. They must fail; neither
control is selected as reconstructed source. They diagnose a real transmitted
coordinate difference, not merely compiler scheduling.

```bash
python3 scripts/audit-iku-spell-actions.py > build/iku-spells-facts.json
python3 scripts/probe-iku-spell-actions.py > build/iku-spells-source-native.json
python3 scripts/probe-iku-spell-actions.py --smoke > build/iku-spells-source-smoke.json
python3 scripts/probe-iku-spell-actions.py --control signed-offset --smoke > build/iku-spells-signed-control.json
python3 scripts/probe-iku-spell-actions.py --control early-offset --smoke > build/iku-spells-early-control.json
python3 scripts/probe-iku-object818-actions.py --smoke > build/iku-spells-object818-regression.json
python3 scripts/build.py --unit cross-v106a-outcome-random --compare --json
```

The two changed-source control commands intentionally exit1. These checks do
not execute the object/effect/animation backend, later members of spawn pairs/
triplets or ring continuation after the first spawn. They do not prove expired
animation, nonzero audio/event contexts, FP exception/unwind behavior, all
action inputs, original compiler ownership or complete-root byte equality.
The next work remains full natural C++ integration across the large Iku root,
followed by a genuine whole-root unit and canonical comparison.
