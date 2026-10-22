# AyaObject804 post-gate sequence reload

## Observed structure and selected change

Original Japanese1.06a target SHA256:
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Root61A290 remains the bounded reconstruction unit. Startup checks pass except
for the known wrong-image IDA rejection. New observations use the hash-attested
PE and complete native VC8 object.

Target804 first checks WORD13E at61A63F, calls the owner-state effect gate5575C0
at61A653, and tests AL. On its false return it **reloads WORD13E at61A660**;
JNE61A716 then skips the phase/counter/bounds handling for a nonzero sequence.
The retained source placed the gate and that handling inside one sequence0
condition and omitted this second load and branch.

The source now closes the first sequence0 block after the gate and uses a
second independent sequence0 condition. The compiled804 owner grows from324
bytes/71 instructions to the target338 bytes/73 instructions. Remaining owner
instruction/edge diagnostics are only the two branches to the shared next-block
return at target61BCF1 versus source-projected61A507. Both destinations have
the same qualified17-byte slot14/RET code, also rechecked by the900 exit audit.
This owner-level result is not canonical full-function acceptance.

## What the helper establishes

Fresh decoding of the200-byte5575C0 helper matters to interpretation. For mode0,
owner action outside50..149 takes its direct false return without object writes.
Eligible owner actions take the effect loops and, on normal completion, return
true; the caller then retires. Thus the missing reload is **not evidence that
the real false-return helper changes sequence**. No fabricated callback that
changes sequence and returns false was used to manufacture a gameplay failure.
The selected change restores the target's read placement and source structure.

## Original-code execution

`scripts/audit-aya-object-804-sequence-read.py` uses the guarded actual Aya
animation/math fixture. It observes root WORD13E reads with call/write epochs,
complete actor/parameter memory, ordered writes, helper calls and x87 state.
False-gate paths execute the original gate, oriented math and actual
next-block/frame helpers. Eligible-effect paths stop at original435240 entry,
recording its five outgoing words and receiver, before executing or returning
from the effect helper. No helper results are mocked.

3072 cases cover sequences0/1/2, phases0/1/5/6, owner actions49/50/149/150,
phase counter0/9, time1/61, X640/1381 and eight masked x87 precision/rounding
settings. Results:

- 2688 actual root returns, with stack/saved-register checks.
- 384 actual effect-entry prefixes, with argument/receiver checks.
- 0 selected differences.
- 384 predecessor differences, **sequence read traces only**; final memory,
 ordered writes, arguments and final x87 observations already agreed.

The fixture does not establish arbitrary resources, full effect execution,
virtual callbacks, unmasked exceptions or complete root equivalence.
The strict old/new graph outside804 agrees on4487 instruction-labelled nodes
without dead-carrier allowances; opaque calls are assumed to return normally.

## Affected audit relocation and replay

Adding the target's missing14-byte check moves action900's source entry from
root offset361B to3629. `audit-aya-object-900-scale-prefix.py` previously pinned
that source offset. It now derives900 from the independently mapped primary
switch owner, requires the unique900 group, and still asserts1773 bytes/412
instructions. Its JNE/JLE exits must share one destination with the exact
17-byte target slot14/RET body; arbitrary exits are not ignored. This resolves
placement from evidence rather than updating one stale constant to another.

The touched900 prefix fixture also uses the existing fail-closed native callback
wrapper and rethrows recorded hook errors before accepting results.
Relevant replays against the selected object all pass:

| Scope | Cases |
| --- | ---: |
|900 sequence4 original oriented-entry prefixes|3456|
|900 retirement/read/animation returns|10840|
|821 counter actual sine/frame returns|3300|
|903 sequence2/3 actual math/read epochs|3168|

Replay logs contain no swallowed callback exceptions. These are scoped checks,
not aggregate cold replay or validation of every retained source path.

## Canonical state and receipts

Full canonical payload20048-byte SHA256:
`00c1b4bc8129e1e0c2b8119a1d559bfccf1efa30d4bcd2a813e0d34a1d3e4b8a`.
Metadata begins19580 versus target19524. The19522-byte canonical comparison
still fails at offset34/hex22, target0F/candidate49; compared-window SHA256:
`1ecbc1ac0ac956ae929667fe11573ac06758b179d06a6800d98dd8205ba94ae8`.
The full root grows12 bytes because alignment absorbs part of the14-byte code
addition. Raw owner diagnostics are4/34; this is not an exact-count metric.
Exact totals remain1381 functions/234914 bytes. Shared ABI/header/helper/profile/
manifest/relocation contracts and accepted units are unchanged.

Receipts in `build/aya-804-sequence-read-20261022/`:
`selected-formal.json`, `selected-owner.json`, `selected-native.json`,
`outside804.json`, and the four scoped replay reports. The predecessor object
is from2d07f7c's source epoch.

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py --unit gpt-web-aya-object-vslot28-full-root --compare --json
taskset -c 0 nice -n 10 python3 scripts/audit-aya-object-804-sequence-read.py --previous-object build/aya-804-sequence-read-20261022/previous.obj
python3 scripts/audit-aya-object-normal-flow.py build/aya-804-sequence-read-20261022/previous.obj build/match-units/GptWeb_AyaObjectActionState.obj --exclude-action 804
taskset -c 0 nice -n 10 python3 scripts/audit-aya-object-900-scale-prefix.py
python3 scripts/ci.py
git diff --check
```

Configured comparison still exits1. The large-root objective remains open,
including other field/control discrepancies and physical shared-tail placement.
