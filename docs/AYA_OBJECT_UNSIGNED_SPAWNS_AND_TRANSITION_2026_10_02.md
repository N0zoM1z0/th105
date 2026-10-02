# AyaObject unsigned spawn values and immediate sequence transition return

## Retained bounded result

**Observed:** `AyaObject_update_action_state_vslot28 @ 0x0061A290` retains
the reviewed `[61A290,61EED2)`, 19,522 bytes, in the original Japanese 1.06a
executable SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Callable SHA-256 remains
`18c813a20cea427b2c3577e2612e3f2e949a191ee2496dc9204331758bebb895`.
This follows [the quarter-motion/callback checkpoint](AYA_OBJECT_MOTION_AND_CALLBACK_READS_2026_10_02.md).

Retained source corrects852's unsigned random-value conversion/arithmetic,
including actual unsigned Y subtraction, and places its rate negation on
state374 before multiplication.853 now returns immediately after selecting7,
reloads owner after spawn, tests current sequence for5..8 after effect/motion
calls, adds its variant offset in the floating domain, and reads sequence1's
alpha before its floating updates. Shared declarations/ABI/helpers, compiler
flags, relocation mappings and object partition are unchanged.

Fresh configured whole-root request remains **nonexact at +0x22**, target
`0F` / candidate `19`. Candidate metadata starts19,276 (`+4B4C`) versus target
19,524 (`+4C44`): metadata gap500->248. Candidate section tail is19,744;
the requested19,522-byte comparison window includes246 bytes after candidate
metadata start. It is not a candidate-body hash. Raw diagnostics are3/34
(entry,980,default802), with33 destinations/zero target-group splits. Default
count2->3 reflects removal of post-RET alignment from that diagnostic span,
not a new default behavior or exact acceptance. No exact credit is added.

Retained LF source SHA-256:
`28348bff6af20041cf8c3eb1f4d404d33f1b7c293d90b87e5ce05d290c5881dd`.
Canonical19,522-byte candidate-window SHA-256:
`8d1b9b9902ea48c999c77858e59691ad4ca13a4c476b37b0bbf49adfbfdcd491`.

##852 unsigned conversion and arithmetic order

**Observed:** the three sequence0 emission gates use current time-counter
remainders12,40 and15, with counter reloads between possible spawn calls.
For the first two emissions, target converts the random EAX result as
unsigned before floating20-minus/15-minus and50-plus/35-plus. Its X values
in the third emission likewise use unsigned conversion before floating
-400-minus or1680-plus. The old source used signed integer arithmetic first.

The third emission's Y is different: at61C83A and61C891 target subtracts
integer180 from EAX **before unsigned conversion**. It then TESTs the wrapped
EAX, FILDs it as signed, and adds the DWORD2^32 correction at6D6EF8 on the
negative signed branch. These instructions implement conversion of the
wrapped unsigned32 value, not conversion of a signed negative result.

**Inferred and retained:** use local unsigned casts of the existing helper's
returned bits. Preserve `unsigned_roll - 180u` for Y; use floating constants
for the other offsets. This does not change the shared helper's decorated
signed declaration or claim that its original source prototype is known.
Natural VC8 generates the observed FILD/unsigned-correction sequence and
the corresponding FSUBR/FADD constants.

The selector helper27-byte body `[4067D0,4067EB)` has SHA-256
`fa098830aa6651a2a1ace442cc4e8c116fca3623f9e57be4e70f8a912168040b`.
**Observed:** it computes MT output divided by `UINT_MAX / limit`, using two
unsigned DIVs. It is not a modulo helper. At limit640 its possible quotient
range is0..640, including a rare upper640. No helper source is changed or
new helper exact credit claimed.

The bounded instruction model evaluates both target and candidate Y paths
for all641 possible post-call values. Both agree for641/641; old candidate
differs for180/641, exactly0..179. Its integer/correction arithmetic is exact
in53 bits; its final FSTP32 model explicitly uses nearest-even rounding.
This is not a whole-game execution or a proof of the game's global x87
control word. Integer wrap is independent of that rounding model.

| Random value | Target wrapped unsigned value | Target/new float, nearest-even | Old signed float |
| ---: | ---: | ---: | ---: |
|0|4294967116|4294967040|-180|
|179|4294967295|4294967296|-1|
|180|0|0|0|
|640|460|460|460|

Remaining physical differences include separate target angle-update bodies
for sequences2/3, whereas source/candidate share their OR-gated update, and
named coordinate lifetimes/argument scheduling. Similar finite outputs for
other small random values do not imply instruction equality.

##852 rate negation operand

**Observed:** negative-facing target loads signed nested facing with FILD,
loads state374 with FLD, applies FCHS to **state374**, then FMULP. The previous
candidate performed FMUL-memory first, then FCHS on its product. Source now
expresses `double(nested_facing) * -state374`, and VC8 naturally moves FCHS
before multiplication. The candidate still loads state before FILD facing,
so target/candidate operation order is not fully identical. This recovers the
negated operand/association without asserting full NaN, precision or immediate
exception closure, or adding assembly/environment flags.

##853 select7 returns before new-state work

**Observed:** target's sequence6 failure predicates converge at61CFB2,
select7 at61CFBB, then return at61CFC4 through a normal seven-instruction
epilogue. There is no subsequent sequence7 growth/movement or frame dispatch
on this path. Old source selected7, refreshed sequence, and could immediately
run sequence7 and frame work in the same invocation.

**Inferred and retained:** return after select7. Candidate select call61CFA8
is followed directly by the same epilogue operations, ending RET61CFB1.
The bounded raw proof rejects any intervening update/call. This is control-
flow recovery, not a canonical match of the whole action or root.

##853 owner, sequence and alpha reads

**Observed:** target reloads owner348 at61CB97 after spawn64CCB0 at61CB92,
then checks action603 and conditionally owner sequence>1. Old candidate used
the pre-spawn owner pointer. Source now captures current owner there. As in
820, baseline VC8 already short-circuited the owner-sequence load; the new
operation is the owner-pointer reload, not repair of an emitted unconditional
sequence read. No claim is made that the callee changes it in ordinary play.

Target gates sequences5/6/7/8 with current member-word reads at61CD8D,
61CE4B,61CF5E and61D020. The old source reused snapshots across intervening
effect/motion calls. These gates now read the member directly, preserving
target read boundaries without inventing volatile or callee mutations.
The earlier snapshot used for1..4 remains.

Target sequence1 loads alpha at61CBCC and compares with15 at61CBD2 before
angle/scale updates; its JBE consumes that comparison afterwards. A real
alpha-value capture used by the test and subtraction naturally restores this
MOV/CMP scheduling in the candidate, with no extra instruction or inert local.
Target's MT masked variant is converted before FADD2.0, so its source offset
is now2.0f rather than integer2u, as independently observed in820.

## Guard roles and controls

Both sides have124 masked guards and twelve in853. Candidate now physically
places its sequence5 heading-floor block before the state370 clamp; target
places it later. Thus the scanner reports two new853 ordinal leads that pair
unrelated conditions. Target guard ordinals0..11 correspond to candidate
`[1,2,3,4,5,0,6,7,8,9,10,11]`. Each paired compare operand form, mask and
LT/EQ/GT/UN edge truth table agrees. The existing902 ordinal/path lead remains.
These role checks do not prove complete value/exception closure.

| Sequential control | Metadata | Raw diagnostics |852 /853 spans |
| --- | ---: | ---: | --- |
| Fresh baseline |19024|2/34|1090 /1417|
|852 unsigned values |19156|2/34|1220 /1417|
|853 select7 return |19172|2/34|1220 /1434|
|853 current reads/float variant |19276|2/34|1220 /1538|
|852 negated state operand |19276|3/34|1222 /1538|
|853 early alpha, retained |19276|3/34|1222 /1538|

Target spans are1201 /1550. Counts/sizes are diagnostics only. Each change
follows independent target instruction/value/control evidence, with no
register forcing, inert storage or compiler-flag search.

## Reproduction and remaining work

### TH08 x87 reference and current instruction discriminator

**External source evidence:** rechecked TH08 HEAD
`d2a00f4acb4a13916e07a00bd13f714961714628` and the unchanged hashes recorded in
[the TH08 x87 reference](COMMON_FIGHTER_X87_AND_GHIDRA_2026_10_02.md).
`ZunMath.hpp` retains FSINCOS assembly; `AnmManager.cpp` retains a four-coordinate
FRNDINT assembly block. Its modern-port nearbyintf branch is not a VC7 exact
claim. TH08's build notes record that its VC7 sin/cos intrinsics did not fuse
into FSINCOS. This supports a specific special-instruction limitation, not
an assembly requirement for every x87 expression or for VC8.

**Observed:** the fresh raw packet decodes all4,630 instructions/all19,522
callable bytes in this Aya root and finds zero FSINCOS and zero FRNDINT.
The candidate's19,276-byte executable extent also has neither instruction.
The present unsigned conversion emits natural VC8 FILD/correction arithmetic;
both sides have77 FILD instructions, which is a count rather than equality
evidence. The state-negation fix likewise emits FCHS through ordinary source.
This scan covers the root body, not recursively every callee. It does not
prove all remaining x87 lifetimes/precision/exception behavior recoverable,
but it supplies no special-instruction reason to add assembly here.

```bash
python3 scripts/build.py --unit gpt-web-aya-object-vslot28-full-root --compare --json
python3 scripts/audit-giant-action-owners.py aya-object-vslot28 \
  build/match-units/GptWeb_AyaObjectActionState.obj \
  --unit gpt-web-aya-object-vslot28-full-root --json
```

Fresh configured reports are `build/aya-spawn-values-final-20261002.json`
and `build/aya-spawn-values-final-owners-20261002.json`; raw, guard and proof
reports share that prefix. Source-hashed private controls and decoded
instruction model are under `.analysis/aya-spawn-values-20261002/` and
`build/aya-spawn-values-20261002/controls-summary.json`. Existing-object
control reports have no configured build provenance and award no exact credit.

Full target traversal remains4,630 instructions/all19,522 bytes through
seven validated switches, with no unresolved indirect exit or unledgered
direct target. Previous quarter-motion, unordered predicates and callback/
alpha reads remain; exact ledgers are unchanged. IDA still fails on the wrong
attached executable; observations use the hash-verified PE. Remaining work
includes physical sharing/argument lifetimes, stack homes, remaining operands,
original helper types and TU/LTCG context. Full numerical/exception closure
is unknown. No aggregate cold replay is claimed.
