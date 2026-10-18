# Reimu: restore bounded execution after receiver recovery

The expanded `478FA0` candidate fits the original callable and metadata windows
again. Two natural return-flow changes reduce its code prefix from81592 to81544
bytes and preserve the recovered actor+4 RNG receiver. This enables fresh
complete returning-manager smoke checks. First canonical difference remains
**+541**; there is no new exact or source-present root credit.

## Observed target control flow

The target is Japanese TH10.5 v1.06a, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Root `[478FA0,48CE2E)` is81550 bytes, SHA-256
`dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6`.
IDA metadata preflight rejects the other executable; observations here use
the attested raw PE. No database or target instruction is changed.

Action9 calls the descending-surface predicate at47970A and tests AL. Its
landing arm sets action10, reads surface height, clears motion and returns
at479739. Its other arm reaches frame advancement at47973C. Action0 also
branches to that tail, optionally through the x87 pop at47973A.

Action10 starts at47974B. After advancement at47975B, a false AL takes the
remote epilogue. A true AL compares the **DWORD** at actor+6B8 against zero
and takes one of two separate vslot+8 calls:47977A with0, or479786 with2.
The complete action interval through479790 is69 bytes.

## Source and compiler observations

Action9 now returns immediately after clearing landing motion, with frame
advancement following the conditional. Action10 spells out the two conditional
setter calls, replacing a single call with a ternary argument. These changes
preserve the C++ behavior, field widths, ABI, compiler flags and helper bodies.
There are no added operations or forced registers.

The action9-only control produces an81544-byte prefix/82916-byte payload.
It restores the target's shared landing tail for6/7/8/9: all four target
entries reach surface-height call479720 and motion-clear call47972D; all four
source entries reach479544 and479551 respectively. Two duplicate source
surface reads and two duplicate motion clears disappear. The common tail's
physical placement still differs: target places it near9, source near6.
The additional action10 control keeps those sizes and reproduces the target's
two setter sites and69-byte action extent. This is a source-shape observation,
not recovery of the unique original spelling or a local exact-match claim.

The final genuine ordinary object is SHA-256
`710094fe7ca95169efd3e53b66a41a8ab1f6ef1f44e83a9f4caea14ac920eca7`.
Its full canonical payload, the private native witness, and the genuine linked
payload agree over all82916 bytes, SHA-256
`a6dc1ccf19322b8ab5c431671d0d204d7b26b29c2c3f8c47292a1d332d44a6bc`.
The frame remains570h; source/target have20334/20243 reachable instructions.
All11 switches, eleven selected request-buffer contracts, and circular
preparation contracts pass without extending either window. All2464 fields
qualify:1176 calls,1104 numeric operands,14 metadata addresses,163 code pointers
and seven global addresses. The1281 HIGHLOW inventory and separate12-byte
INT3 linker gap remain required. The linked DLL is not executed.

The strict first difference is still the JNE displacement at4791BB, byte+541:
target destination489D6A, source489D49. Both destinations are identical
epilogues, but the displacement remains part of the strict comparison.

Fit does **not** establish complete target physical ownership. The first
instruction-shape difference follows action0: the shared0/9 advancement tail
is placed near0 in source and near9 in target. This is a placement difference,
not a duplicate or missing advancement. The old300/320,
215/310/797,410/414/416 and522/523 ownership differences remain. A fresh census
still finds equal reachable per-callee cardinalities for all128 nondefault
actions; these are neither dynamic counts nor matching-owner proof.

## Focused execution checks

`audit-reimu-void-root.py` adds two cohorts using existing low-action inputs:

| Cohort | Inputs | Required original paths |
| --- | ---: | --- |
|falling_returns|192|Action9 landing RET and nonlanding advancement|
|landing_action_returns|256|Action10 zero/nonzero DWORD setter branches|
|projectile_receivers|480|Actual actor+4 RNG receiver and stack arguments|

All928 comparisons pass with unmasked actor/MT/control/call/request snapshots.
The falling inputs include signed zeros, subnormals, infinities, quiet/signaling
NaNs, surface-adjacent heights and PC53/64. Action10 includes6B8 values0,1,65536
and-1, four animation transitions and PC53/64. Checks require both original
return paths to execute over each new cohort, in addition to per-input checks.

The initial action10 fixture correctly failed this coverage requirement: its
terminal block still had a next sequence. Terminal inputs now use the existing
`single_sequence` fixture option. The guard was retained. The successful input
SHA-256 is `cd254f4b6004678cac7959fb8d437f7cbeb19709b5b7125ed87fe496d0a64e43`.
The private object used for928 inputs has the same entire canonical payload as
the final genuine object; no duplicate execution is needed for filename/COFF
record differences.

Fresh complete returning-backend smoke checks use the final genuine object:
effect40/40, owned14/14 with50 objects, and circular5/5 with99 objects. Repeated
target processes reproduce every snapshot byte, and all candidate comparisons
have zero differences. These renew the bounded complete-return witnesses after
the receiver correction; old full matrices are not replayed or recredited.
The supplied resource/world/import limitations of those auditors still apply.

Reproduce with single-core, nice10 commands:

```sh
nice -n 10 taskset -c 0 python3 -B scripts/probe-reimu-action-ltcg.py
nice -n 10 taskset -c 0 python3 -B scripts/audit-reimu-void-root.py build/reimu-ltcg/ordinary.obj --cohort falling_returns --cohort landing_action_returns --cohort projectile_receivers
nice -n 10 taskset -c 0 python3 -B scripts/audit-reimu-effect-returns.py --smoke
nice -n 10 taskset -c 0 python3 -B scripts/audit-reimu-owned-returns.py --smoke
nice -n 10 taskset -c 0 python3 -B scripts/audit-reimu-circular-returns.py --smoke
```

Receipts are under `build/reimu-sharing-review/`; the current genuine cache is
`build/reimu-ltcg/`. Heavy jobs ran serially; returning-host child peak RSS was
308156KiB, approximately301MiB. All nine primary database files hash unchanged
using streamed reads. Obsolete controls, snapshots and native build products
are disposable after their receipts are retained.

Remaining work is target physical sharing,214's resource guards,740's bounded
unknown contexts, and broader world/runtime/exception coverage. Preserve the
strict callable/metadata guards while resolving these; fitting alone is not
canonical equality.
