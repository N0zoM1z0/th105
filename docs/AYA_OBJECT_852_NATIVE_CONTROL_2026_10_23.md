# AyaObject852 native check of the801 sequence-snapshot control

## Question and evidence

The resumed session uses original Japanese1.06a target SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Target/status/tracking checks pass. IDA still rejects the wrong-image session;
all new observations use the hash-attested PE and retained/fresh VC8 objects.
The bounded reconstruction root remains AyaObject update61A290 (19522 bytes).

The [801 experiment](AYA_OBJECT_801_FADE_SNAPSHOTS_2026_10_22.md) produced an
unselected explicit sequence snapshot. It fixes all scoped801 read observations,
but changes852's nested-facing multiplication in addition to other root paths.
Treating the x87 forms as automatically equivalent would be unjustified.

Target852 tests actor facing at61C98C and loads signed nested facing at61C999.
For facing-1,61C9A2..61C9B4 uses FILD, FLD374, FCHS, FMULP before the shared
FSTP to owner+6AC at61C9C4. The other arm at61C9B6 uses FILD then memory FMUL374.
The control changes instruction order and the positive arm to FLD/FILD/FMULP.
Neither whole852 nor the root is canonically matched by those observations.

## Fresh original-code execution

`scripts/audit-aya-object-852-native.py` executes the original root and each
candidate from its real entry to its real RET. It reuses the guarded903/901
math/animation fixture, with an explicit owner, target and nested-target graph.
Only the owner's four-byte6AC slot is newly permitted as an external write;
other unexpected writes still fail. No helper return is fabricated.

Each execution compares actor bytes, mutable parameter bytes, owner6AC bits,
ordered writes, helper calls, final x87 status/tag, and the live x87 registers,
status/tag and outgoing value at the owner-product memory-write hook. Stack
cleanup and callee-saved registers are checked on every actual return.

The matrix contains6528 cases:

- 6400 sequence0 cases: timers239/241, all pairs of signed facing bytes
  -128/-1/0/1/127,16 speed bit patterns and eight masked x87 precision/rounding
  control words. Speed patterns include signed zero/denormal, finite thresholds,
  largest signed finite values, signed infinity, quiet NaN and signalling NaN.
- 128 sequence0..3 controls with nonpositive owner/target health and both
  ordinary facing signs. These qualify early exits and actual math/frame paths.

Timers239/241 avoid all12/40/15 divisibility spawn guards; an explicit assertion
rejects a matrix that would enter them. Exactly6400 owner-product writes occur.
Target calls include6496 original4351C0 frame advances and32 original435160
oriented-motion calls, with real lookup/conversion helpers.

**Both selected source and the cached-sequence control have zero differences
across all6528 cases, including the owner-product x87 snapshots.** This resolves
the exercised non-spawning852 concern; it does not prove random/spawn paths,
arbitrary animation resources, unmasked exceptions or complete root equivalence.
The result does not erase the different instruction forms or earn exact credit.

## Selection and reproducibility

Game source and accepted ledgers remain unchanged. The control remains unselected:
853/861 operand-order changes,854 branch polarity/tail merging and complete
outside801 closure still require qualified evidence. The strict normal-flow
checker has not been weakened. The earlier private diagnostic located differences
but is not an acceptance proof.

A fresh configured VC8 build reproduces the selected full20136-byte payload:
`a2fafaa2de959366066d6d2a0f2ab794c4f5b2260c294312d2ed03d3cf6b3d9d`.
Metadata starts19668; the19522-byte canonical comparison remains nonexact at
hex offset22, target0F/sourceA1. No exact count/byte change or aggregate replay.

The cached control was restored from the prior archive only after archive and
member SHA256 checks. Its COFF SHA256 is
`6681b76d5a143fadd431e6aeb973087ea2c5298cae866df73946bf22f40ba891`;
full canonical payload20096 has SHA256
`b45c379032a0be5af68586aa11f4aa2a4ec2e1b3ad1f6301350b6a4b2ec4d45b`.
Source/recipe/retention evidence remains in `build/aya-801-fade-20261022/`.

```sh
# Restore just this reviewed control if its loose copy has been cleaned again.
tar -xzf build/aya-801-fade-20261022/completed-controls.tar.gz build/aya-801-fade-20261022/cached-sequence.obj
# The whole-root comparator is expected to report nonexact.
taskset -c 0 nice -n 10 python3 scripts/build.py --unit gpt-web-aya-object-vslot28-full-root --compare --json
taskset -c 0 nice -n 10 python3 scripts/audit-aya-object-852-native.py --control-object build/aya-801-fade-20261022/cached-sequence.obj --output build/aya-852-native-20261023/native.json
python3 scripts/audit-aya-object-predicate-widths.py
python3 scripts/validate-tracking.py --require-target
taskset -c 0 nice -n 10 python3 scripts/ci.py
git diff --check
```

Omit `--control-object` to audit the selected object only. The native receipt
records object hashes, complete executable bytes mapped at800000, original
helper hashes and the input-matrix hash. Reports stay under
`build/aya-852-native-20261023/`; executable artifacts are not committed.
