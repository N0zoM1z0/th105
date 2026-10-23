# AyaObject807/854 sequence and alpha lifetimes

## Target observations and selected source

Original Japanese1.06a executable SHA256:
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Target/status/tracking checks pass; wrong-image IDA remains rejected. New facts
come from the hash-attested PE and complete VC8 objects. Root61A290 remains the
bounded19522-byte callable; no whole-root exact acceptance is claimed.

Target807 loads WORD13E once at61A853, after the possible owner-spawn call, and
uses CX for its sequence1/0/2 decisions. The frame/retirement tail separately
reloads sequence after the frame helper. The selected source now snapshots the
word at that first location while retaining the fresh post-frame condition.
The previously selected live angle across alpha write is preserved.

Target854 similarly reads WORD13E at61D1F3 after sequence0's calls/movement.
For sequence1 it reads alpha at61D205 and compares it before both scale updates;
sequence2 uses the same captured CX. Selected C++ now snapshots sequence there
and snapshots alpha before the scale stores. The nonzero-phase next-block call
at61D183 genuinely continues into movement; it is not missing a source return.

No helper ABI/header/profile/object partition/relocation contract is changed.
The used snapshots restore observed reads without pretending to establish the
original C++ source spelling, callbacks or arbitrary concurrent observers.

## Why the previously rejected807 snapshot was retried

The earlier snapshot-only form altered x87 scheduling in other actions. The
independently target-proven angle lifetime fromc93029f supplies new context for
retrying it. With that lifetime retained, the new snapshot keeps4464 strictly
labelled normal-return graph nodes outside807 identical, without dead-carrier
or floating-operation allowances. The old failure was specific to its source
epoch; it did not establish that the target snapshot was unrecoverable.

After that step, adding854's prior-alpha snapshot keeps4481 other-path nodes
identical. Adding854's sequence snapshot also preserves4481 nodes relative to
that intermediate. These are successive old/new graph proofs, with switch
metadata/ordered edges checked and calls assumed to return normally. They do
not assert canonical equality or callback/exception equivalence.

## Original-code execution

The final object is replayed serially through original root, gate, math and
animation instructions with guarded callbacks:

| Scope | Cases | Stops | Final observed differences |
| --- | ---: | --- | --- |
|807 strict|3968|3524 RET /120 owner-spawn entry /324 effect entry|0|
|854 strict|3840|3744 RET /96 related-object spawn entry|0|
|801 affected-auditor replay|3840|3732 RET /36 spawn entry /72 effect entry|3012 previously known sequence reads only|

807 restores all2044 previous sequence-read trace differences while retaining
all688 corrected alpha-write live-x87 snapshots and the exact26-byte interval.
854 restores all3232 previous sequence-read differences and1776 alpha-read x87
snapshot differences. Selected807/854 are tested **without** an allow-read flag;
all recorded observations agree, including complete actor/parameter state,
ordered writes, helper calls, sequence read epochs, alpha snapshots and final
x87 status/tag. Actual returns check stack cleanup and callee-saved registers.
Spawn/effect prefixes compare original outgoing words, pointed-to payloads and
receivers, then stop before helper execution; no helper return is fabricated.

The inherited matrices cover sequence/phase transitions, owner action boundaries,
signed counter thresholds and wrap, timers, alpha thresholds, signed zero,
denormal, finite/infinite/quiet/signalling-NaN scale or angle inputs, and eight
masked x87 precision/rounding modes. This does not close arbitrary resources,
full spawn/effect execution, callbacks, unmasked exception delivery or the root.
No gameplay fault is inferred solely from the predecessor's read/snapshot timing.

## Reusable fade audit and remaining code-generation differences

`audit-aya-object-801-fade.py` now accepts `--action 801|854`, defaulting to801.
Its actual selected action determines the animation resource graph and expected
spawn ID.854 explicitly rejects any gate/effect path. The action is included
in input provenance; the existing801 replay still yields its documented3012
sequence-read differences and no alpha/effect differences. The allow-read option
remains explicit, and default mode still rejects any observed difference.

Final807 owner remains502 bytes/112 instructions versus target414/89.854 is
377/93 versus target378/93. Source holds sequence in AX rather than target CX,
and its branch-exclusive optimization/shared alpha-store placement differs.
The common frame tail is still physically duplicated/placed differently. Owner
counts and scoped native results do not earn exact credit.

The complete payload shrinks from20136 to20132 bytes; metadata begins19664.
Selected full canonical SHA256:
`17585ff8bc4fadd5f63619d3d52d470440955256a820ac76ca97daa7ee31f88f`.
The19522-byte comparison SHA256 is
`f5d2c6f06afa5b10440d058e324574dbe68e045bdf26f37d657c4622d0c61982`.
Configured comparison remains nonexact at hex offset22, target0F/source9B.
The three low-byte predicate consumers replay successfully; accepted totals and
source selection counts are unchanged. No aggregate cold replay is claimed.

## Reproduction and retained intermediate epochs

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py --unit gpt-web-aya-object-vslot28-full-root --compare --json
taskset -c 0 nice -n 10 python3 scripts/audit-aya-object-807-angle-lifetime.py --output build/aya-854-fade-20261023/807-selected-native.json
taskset -c 0 nice -n 10 python3 scripts/audit-aya-object-801-fade.py --action 854 --previous-object build/aya-854-fade-20261023/previous.obj --output build/aya-854-fade-20261023/854-selected-native.json
taskset -c 0 nice -n 10 python3 scripts/audit-aya-object-801-fade.py --allow-sequence-read-differences --output build/aya-854-fade-20261023/801-replay.json
python3 scripts/audit-aya-object-predicate-widths.py
python3 scripts/validate-tracking.py --require-target
taskset -c 0 nice -n 10 python3 scripts/ci.py
git diff --check
```

The whole-root comparator is expected to report nonexact. Previous object is
the savedc93029f epoch. Graph receipts in `build/aya-854-fade-20261023/` describe
three successive stages:807-snapshot,854-alpha and854-snapshot. Each intermediate
has frozen source/object/provenance and an outside-action graph result. Replay
a graph receipt with its recorded pair, rather than mixing object epochs.
Private binaries, reports and compiler/runtime inputs are not committed.
