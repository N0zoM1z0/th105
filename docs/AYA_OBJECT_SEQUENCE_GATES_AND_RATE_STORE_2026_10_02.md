# AyaObject sequence gates and direct rate store, 2026-10-02

## Bounded retained result

**Observed:** the unchanged callable for
`AyaObject_update_action_state_vslot28 @ 0x0061A290` is
`[61A290,61EED2)`,19,522 bytes, SHA-256
`18c813a20cea427b2c3577e2612e3f2e949a191ee2496dc9204331758bebb895`.
The canonical Japanese1.06a PE still verifies as
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
This follows [the unsigned-spawn/transition checkpoint](AYA_OBJECT_UNSIGNED_SPAWNS_AND_TRANSITION_2026_10_02.md).

Source now preserves852's separate sequence2/3 angle-update bodies, writes
the computed rate directly to owner+6AC without an extra float local/cast,
and spells the time<240 increment arm as target fallthrough before the
decrement arm. Shared helpers, class layouts, compiler flags, relocations,
object partition and exact ledgers are unchanged.

The fresh configured whole-root comparison remains **nonexact at+0x22**,
target0F/candidate33. Candidate metadata starts19,304 versus target19,524;
the metadata gap248->220 is a diagnostic, not accepted byte progress.
The19,522-byte candidate comparison window includes218 bytes after its
metadata start and must not be called a candidate-body hash. Its SHA-256 is
`60b68c7c14ed6fa44dc083880755b3fab4947d536650bebe74bdb9a0557e08b3`.
Retained LF source SHA-256 is
`745fed1ab7fc576a3299d2ab6e0e332dba2ccfef0e0bbe33ef9273f14b66b707`.

## Separate sequence updates and direct writeback

**Observed:** target61CA3A reads sequence once intoAX. Its sequence2 gate
leads to the angle update at61CA52..61CA64; the separate sequence3 gate at
61CA66 leads to the update at61CA72..61CA84. Both bodies independently
compare time with120, update angle with state370 and return on equality.
There is no intervening callback. The retained OR-gated source had folded
these bodies into one, which omitted one physical FADD/FSTP update body.

**Inferred and retained:** express the two source conditions independently.
This recovers the target's physical structure without inventing a numerical
difference between ordinary sequence2/3 invocations. VC8 still naturally
uses one sequence-word snapshot, as target does.

Target rate multiplication converges at61C9C4 on one FSTP32 to owner+6AC.
The previous source first assigned a float local with float casts in its
ternary arms. Its compiled join stored to a stack home, reloaded that float,
then stored the field. Directly assign the conditional double expression
to the actual float destination, retaining state374 negation before the
negative-facing multiplication. VC8 now emits the target direct field store.
This follows the observed rounding destination; no assembly, volatile,
inert local, register assignment, padding or environment flag is introduced.

**Observed interval diagnostic:** `[61C9C4,61CA86)` now agrees in all194
replayed bytes and all43 decoded instruction records at the same absolute
addresses. The interval includes rate writeback, sequence1 helper/threshold
work, and both sequence2/3 gates and updates. Its SHA-256 is
`5a198a591d119324951e2ac00d4c58fc14ac361b42147081d4159bc1e467e75b`.
This is a bounded interval comparison, not a standalone function, action852
match, or exact-ledger acceptance. Some interval branches leave it; their
destination instructions still differ outside this interval.

## Ramp fallthrough and rejected promotion

**Observed:** target61C8EC compares time with240 and uses JGE to enter the
later decay arm. Its fallthrough increments state374 before testing the
upper7 clamp. Source now uses time<240 for that fallthrough, preserving
the existing half-step arithmetic, float store/reload and strict comparisons.
All four852 masked comparison forms, masks and LT/EQ/GT/UN branch tables
agree by role/order. The scratch home remains targetESP+14 versus
candidateESP+18, and this control alone changes no metadata size.

An isolated promotion of the real nested-facing local from signed char to
int restores a single MOVSX before the branch, but also turns the negative
product into FIMUL of an integer stack home. Target instead FILDs facing,
FLDs state374, applies FCHS and FMULP. The smaller promoted control is
**rejected** despite its earlier integer conversion. It neither proves the
original local type nor resolves the target's floating evaluation order.
Retained source keeps the signed-char local; negative-facing operand load
order remains different and full exception/precision closure is unknown.

| Sequential control | Metadata | Raw owner diagnostics |852 span |
| --- | ---: | ---: | ---: |
| Fresh baseline |19276|3/34|1222|
| Separate sequence updates |19312|2/34|1256|
| Direct rate store |19304|2/34|1248|
| Target ramp fallthrough, retained |19304|2/34|1248|
| Promoted facing, rejected |19292|2/34|1237|

Target852 is1,201 bytes. Larger/smaller spans do not prove recovery. The
default802 diagnostic loses its former count because its final candidate
span includes post-RET `mov edi,edi` alignment; callable default instructions
remain unchanged. Entry/980 retain their raw diagnostics. All33 switch
destinations remain distinct, with zero target-group splits.

## Verification and remaining work

```bash
python3 scripts/build.py --unit gpt-web-aya-object-vslot28-full-root --compare --json
python3 scripts/audit-giant-action-owners.py aya-object-vslot28 \
  build/match-units/GptWeb_AyaObjectActionState.obj \
  --unit gpt-web-aya-object-vslot28-full-root --json
```

Configured reports are `build/aya-sequence-gates-final-20261002.json` and
`build/aya-sequence-gates-final-owners-20261002.json`; raw, guards and proof
reports share that prefix. Private controls and hash-bound interval checker
are below `.analysis/aya-sequence-gates-20261002/`; objects and
`controls-summary.json` are below `build/aya-sequence-gates-20261002/`.
Existing-object control reports have no configured build provenance.

Fresh raw traversal still reaches all4,630 target instructions/all19,522
bytes through seven validated switches. Guards remain124/124. Earlier two
853 ordinal leads retain their twelve-role pairing, and the902 path lead
remains. Rechecks retain both641-value unsigned Y proofs,853 select7's
immediate return and its postspawn owner reload. No aggregate cold replay
or new exact credit is claimed. CI and whitespace gates pass before commit.

Remaining852 differences include spawn-argument evaluation/scheduling and
named coordinate homes, signed-facing conversion timing, its FILD/FLD order,
scratch offsets, final movement receiver/register scheduling and decrement
register ownership. The194-byte interval demonstrates a natural source
recovery within this root; it does not settle original helper prototypes,
full floating/exception behavior, other actions, or TU/LTCG context.
IDA preflight still rejects the wrong attached executable; no IDA output,
factory adapter or target patch was used.
