# AyaObject861 phase-counter scope correction

## Observed target and selected change

Original Japanese1.06a executable SHA256:
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Startup target/tracking checks pass. IDA remains rejected for wrong-image
identity; new evidence uses the hash-attested PE and complete VC8 COFF.
The bounded root is61A290, callable ledger size19522.

At61D5E4 the target initializes EDI=0 and compares WORD13E with DI. Its nonzero
JNE at61D5F2 goes directly to61C2A7, the sequence1 test, **past** the phase/count
handling61C27E..61C2A6. Sequence0 normal exits after its random/spawn preparation
jump to61C27E, so only that initial sequence0 path advances WORD364 and clears
phase/count at the signed threshold6.

The retained source placed this phase/count block after the sequence0 scope,
so nonzero sequences also incremented/reset it. The selected source moves the
existing block inside sequence0 after the spawn condition. This is a control-
flow correction with an observed final-state consequence, not a floating-point
code-generation inference. The original source's exact spelling remains unknown.

## Execution and negative control

`scripts/audit-aya-object-861-phase-scope.py` executes the actual root and original
math/animation helpers to RET for3072 cases. Inputs cover sequences1..4,
phases0/1/5/6, signed counters-32768/-1/0/4/5/6/32766/32767, alpha0/15/255 and
eight masked x87 precision/rounding settings. Every return checks stack cleanup
and callee-saved registers. Complete actor/parameter effects, calls and final
x87 status/tag are compared; phase/count writes are explicitly forbidden for
these nonzero sequences.

- Previous source:2304 cases write phase/count and have different final state.
- Selected source:0 phase/count writes and0 final-state differences.
- The existing sequence1 alpha/X write scheduling difference remains in768
  cases. The checker requires exactly the two observed disjoint writes exchanged
  with every value and subsequent write identical. It reports this difference;
  it does not claim equality of ordered traces, callback or exception observers.

Example: sequence1,phase1,counter0 leaves WORD364=0 in target; predecessor
changes it to1. Sequence1,phase6 behaves likewise. Threshold and wrap controls
also catch predecessor phase resets and signed counter changes.

## Complete canonical delta

The fresh configured root remains20136 bytes with metadata at19668. Its complete
canonical payload differs from the preceding checkpoint at **one byte only**:
root-relative33E8 changes45 to6E, the low displacement byte of JNE61D676.
Its destination advances from61D7C1 to61D7EA, skipping the41-byte phase/count
interval and landing on the memory sequence1 comparison. The audit also pins
the preceding14-byte guard to target61D5E4 and qualifies the skipped interval.
All other instructions, relocations, metadata and payload bytes are identical.
Thus sequence0's unchanged fallthrough retains its old instructions/control flow;
full sequence0 random/spawn behavior is not newly execution-proven here.

Strict instruction-labelled normal-return graphs outside861 agree on4466 nodes,
without carrier allowances or relaxed floating operations. Calls are opaque
normal returns for that graph check. Prior low-byte predicate checks also pass.
No shared helper/header/ABI/profile/partition/relocation changes occur.

Full canonical SHA256:
`fd8dc276b567f9d5fe846242204959697c489824250c9c29963313c6d4c04e0f`.
The19522-byte comparison SHA256 is
`818a3e370e1f2acbbb6ff8d8997be1d43daf76acc3a0bbbe710cc386ab878648`.
Canonical comparison remains nonexact at hex offset22, target0F/sourceA1.
No exact function/byte credit is added.

## Scale-add exploration that exposed the defect

`scripts/audit-aya-object-scale-adds.py` executes6216 scale cases:4144 for853
sequences2/3 and2072 for861 sequence1. It crosses16 scale and16 growth bit
patterns, including signed zero/denormal, finite rounding boundaries, infinity
and distinct quiet/signalling NaNs, with eight masked x87 environments. Extra
phase/alpha cases exposed the incorrect861 count scope.

Both the previous source and the old801 cached-sequence control agree with all
observed scale-store values and live x87 snapshots.853 complete observations
agree. In861 both old objects have16 final-actor differences, traced to364, and
2072 ordered-write differences. After the phase fix selected final actors agree;
2072 known alpha/X scheduling differences remain. The scale audit deliberately
reports those differences in diagnostic mode rather than calling the whole
path identical. The dedicated phase audit checks the scheduling difference's
exact shape over its larger counter matrix.

A separate target-motivated source control reverses the853 C++ addition operands
because target61CC2C loads370 before FADD11C. Its **entire20136-byte payload is
byte-neutral** to the old selected object; the edit is not retained. Explicit801
sequence caching can change this scheduling, but remains unselected pending
other control-flow/context closure. Its frozen source predates this861 fix:
rebase any future trial onto current source rather than replacing the whole file.

## Reproduction and limits

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py --unit gpt-web-aya-object-vslot28-full-root --compare --json
taskset -c 0 nice -n 10 python3 scripts/audit-aya-object-861-phase-scope.py --previous-object build/aya-scale-add-order-20261023/previous.obj --output build/aya-scale-add-order-20261023/phase-native.json
taskset -c 0 nice -n 10 python3 scripts/audit-aya-object-scale-adds.py --diagnostic --output build/aya-scale-add-order-20261023/selected-scale-native.json
python3 scripts/audit-aya-object-normal-flow.py build/aya-scale-add-order-20261023/previous.obj build/match-units/GptWeb_AyaObjectActionState.obj --exclude-action 861 --output build/aya-scale-add-order-20261023/outside861.json
python3 scripts/audit-aya-object-predicate-widths.py
python3 scripts/validate-tracking.py --require-target
taskset -c 0 nice -n 10 python3 scripts/ci.py
git diff --check
```

The full-root comparator is expected to report nonexact. Omit the previous
object option to replay selected phase cases only; the complete one-byte delta
check requires the retained predecessor. Reports/frozen controls stay under
`build/aya-scale-add-order-20261023/`. No arbitrary resources, complete random/
spawn paths, unmasked exception delivery or whole-root equivalence is proved.
