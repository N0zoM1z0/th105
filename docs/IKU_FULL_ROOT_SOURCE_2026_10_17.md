# Iku's complete action-state root source

> Historical first complete-source checkpoint. The current
> [flat dispatch and ownership checkpoint](IKU_FLAT_DISPATCH_2026_10_17.md)
> supersedes the source hash, compiler topology and native results below.

`Iku_dispatch_action_state_vslot28 @ 620920` now has complete source in
`src/characters/IkuActionState.cpp`: all 110 nondefault action IDs, the original
prelude, early exits and common default. The actual entry is a void thiscall
method with no stack arguments. `implemented.csv` selects this source and the
new `gpt-web-iku-action-state` unit compares the entire target root. This is
source-present progress; canonical equality still fails at **+8**. No exact
or partial byte credit is added.

## Observed target and analysis facts

The sole target is original Japanese TH10.5 v1.06a, executable SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The callable `[620920,62EFBE)` is 59,038 bytes, SHA-256
`abc831c6ccd95986bed811694f532ad8c8b92cb49702a7f6ce4de100b8a73dea`.
`scripts/audit-iku-full-root.py` regenerates the selector map and normal-return
CFG directly from that hash-attested PE. It closes all 15,132 instructions,
131 returns and three indirect switches, with no unreached bytes. The 110
action entries plus default close 58,447 unique bytes; the remaining 591 bytes
are prelude/routing. These are overlapping control-flow unions, not separate
functions or additive progress. Call continuations are followed statically.

The switches at 620B1B/62374C/6290B3 use the original 33/42/35-entry tables
and compressed selector arrays; actions 300/560 have direct edges. Actions
209/221 genuinely share entry 621E55. Two alignment bytes follow the final
RET before the first table. The earlier
[boundary/action map](IKU_VSLOT28_BOUNDARY_ACTION_MAP_2026_10_02.md) remains
the ownership and extent reference.

A single direct Ghidra read-only clone independently re-attests imported
executable identity, entry point, mapped `.text`, root and saved ABI metadata:
58 access-backed fields, 30 ordinary callee models and 177 register-call
target sets. All nine primary-project file hashes remain unchanged; the
disposable clone is removed. IDA still has the wrong executable and is used
only for the failing metadata preflight. No target bytes are patched.
Decompiler output remains a private hypothesis, including its outstanding
spacebase warning.

## Recovered source and critical distinctions

The last 33 opening IDs are now implemented alongside the prior 77 bodies:

| Actions | Recovered behavior |
| --- | --- |
| 0--10 | Landing, independent two-sided braking, walking, jump entry and air/landing transitions |
| 197--199 | Sequence timeout, completion mode, facing and distinct dash entry velocities |
| 200--204, 223--226 | Input/time gates, ground/air motion, paired and periodic effects, transition order |
| 208--212, 220--222 | Crossing before gravity, protection flags, speed clamp and jump entry effects |
| 214/215 | Eight-way glide steering, heading wrap, costs, sequence exits and landing scratch reset |

The prelude writes WORD+7A0=0 and +7A2=117. It clears WORD+7B0 for own signed
life<1 or peer life<0, then decrements a positive count. Actions 150--158 set
BYTE+751 and may spawn object 998 with distinct offsets. Three independent
tests re-read action/coordinates after possible calls. Own WORD+186 or peer
WORD+48C then returns early. Unhandled actions call the genuine common root
4740C0. The source probe now executes this candidate prelude itself, rather
than supplying the original prelude to the candidate.

Raw instructions resolve several distinctions that a compact decompilation
would lose:

- Glide exit-facing uses ordered strict comparisons. In sequence 3/8,
  JP/JNE at 622823/622863/6229EA/622A54 reject unordered coordinates. An
  inverted `<=` condition would flip on NaN. The first opening smoke exposed
  this source mistake; corrected source retains facing for NaN.
- Periodic effect 124 stores the double `X+50` across two genuine MT calls,
  computes Y from the first remainder, then subtracts the second from that
  double carrier before the final float store. The target's QWORD stack
  carrier supports this width and lifetime.
- Actions 200/223 publish the protection flag on opposite sides of the
  landing call. Periodic effects occur before or after frame advance according
  to the action. Action 225 continues after an action-change call where 226
  returns. The source preserves these distinct orders.
- Glide uses DWORD+4B8, signed WORD heading/counters, one-step +/-360 wrapping,
  double 3/2.5 turns and real sine/cosine lookups. Its landing reset calls
  435110 with receiver **this+4**. Sequence 3/8 exits use the genuine frame
  setter through vslot +1C, not an invented direct store.
- Action 204 subtracts double-widened 0.35f; action 215 clamps both velocity
  signs without clearing the motion byte. The earlier unsigned 602 offset,
  310 double increment, 780 widened 0.95f and direct-X signed-zero contracts
  remain intact. See the [middle](IKU_MIDDLE_SOURCE_2026_10_17.md),
  [virtual ABI](IKU_VIRTUAL_CALLS_2026_10_17.md) and
  [random/float](IKU_RANDOM_FLOAT_TYPES_2026_10_17.md) records.

The C++ is a manually recovered source hypothesis with a partial receiver
view. Related bodies share private/status methods marked `__forceinline` so
the actual root compiles without artificial internal CALL boundaries. The
root's COFF contains **zero local CALL relocations**. These annotations do
not establish original source spelling, inlining phase, full class layout or
LTCG ownership. No assembly, byte bodies, padding, inert locals or fabricated
callee addresses are used.

## Whole-entry native evidence

The final source passes **0/26,783 differences** from each root's own entry.
New opening/prelude inputs are expanded; prior families contribute only their
existing smoke matrices and a small entry grid. Their older expanded matrices
and unrelated accepted units are not replayed. The final source also passed
the 4,898-case whole-entry opening smoke before the expanded run.

The probe runs actual target motion, frame, landing, RNG, counter, event/audio
and math helpers without injected helper returns. It compares the 7B8 actor,
call order/arguments/payloads, publication state, RNG/global effects, conversion
inputs, stack/callee saves at RET, empty x87 stack and preserved control word.
Both roots start from the same actor/stack/CPU fixture. The baseline fixture
uses a flat stage, explicit animation/resource state and zero event handles;
it is not arbitrary live gameplay.

| Target outcome | Cases |
| --- | ---: |
| Genuine root RET | 19,949 |
| First object spawn 465190 | 833 |
| First effect 435240 | 586 |
| First action change 45BFE0 | 2,096 |
| First next-block 45C220 | 90 |
| First sequence change 45C390 | 3,089 |
| First finalize 45D110 | 1 |
| First common-default entry 4740C0 | 108 |
| First cosine entry 4063D0, nonfinite heading | 30 |
| First abs entry 406330, NaN X | 1 |

This visits **10,231 of 15,132** target-root instructions. Execution stops
before those backend/runtime implementations; post-backend continuation,
later ring emissions, exceptional paths and complete gameplay equivalence
remain unverified. Static call continuations do not remove this limit.

Two candidate-source negative controls verify the new checks. Changing the
prelude's decrement to increment differs **60/60** cases, including blocked
early returns. Replacing ordered facing with inverted `<=` differs **28/48**
NaN-peer cases in action 214. Both collections are checked subsets of the
passing 26,783-case baseline; they do not replay that entire matrix. The
target and helper returns are unchanged in controls.

Final baseline receipts:

- C++ SHA-256, CRLF on disk:
  `a88f9b7563e07984bff7ff763c70b4180a1f7ae370b32e49ca0755bac4bae180`;
- input SHA-256:
  `c6a47d760c736661969a5d2b6fe04100afcc01a9546b86d7893545e93a551a60`;
- target-output SHA-256:
  `bbcaecf27d3c34d822fb62b645283098663fe93512cc714c46e33793b73313fb`.

Reports also retain compiler/header/object, probe/fixture and runtime hashes.
The native-tested object and canonical-unit object replay to identical bytes
for the entire root section tail using genuine relocations, despite different
COFF file hashes. Its SHA-256 is
`0f3ed243f6115379979d1bb26c4d97dbb36bdf4105dd1fe459448ae3320b7759`.

## Canonical comparison and remaining work

The pinned VC8 SP1 `/O2 /GS- /GR /EHsc /MT` unit resolves 32 genuine external
CALL symbols and 132 data keys, including the existing match-identifier
binding. Thirty-five new floating-literal keys have exact address/width/value
observations within this root. The literal gate passes 346 ledger literals,
597 explicit mappings and 943 target references. No existing literal row,
used binding, accepted source/header, compiler profile or object partition
changes. The new keys were absent from all prior unit mappings. Global
manifest/ledger hashes conservatively invalidate old cache receipts; this
checkpoint does not claim fresh aggregate totals or run a cold all-unit replay.

Canonical relocation replay completes without a relocation failure and then
reports a genuine whole-root mismatch at **620928 / +8**: target stack frame
`0x400`, candidate `0x2E8`. The candidate section tail is 37,623 bytes; CFG
inspection separates **36,703 callable bytes / 9,623 instructions / 106 RETs**
from 920 following table/selector bytes. No callable bytes are unreached in
that COFF CFG. It has six switch sites versus the target's three. These are
codegen diagnostics, not accepted helper/function boundaries.

The grouped source folds many physically distinct target cases. Next work
must recover target-backed case-specific source structure, float lifetimes
and dispatch lowering in this same root. A larger stack frame alone would
not establish a match; padding or inert locals are forbidden. This result
does not prove that LTCG prevents matching. Original TU/source ownership,
backend continuation, exceptions and full receiver layout remain unknown.
`matches.csv` and all exact counts are unchanged.

Reproduce only the needed focused checks:

```bash
python3 scripts/probe-iku-upper-actions.py --all-actions > build/iku-full-root-native.json
python3 scripts/build.py --unit gpt-web-iku-action-state --compare --json > build/iku-full-root-compare.json
python3 scripts/audit-iku-full-root.py --object build/match-units/GptWeb_IkuActionState.obj --native-object build/IkuActionState.obj > build/iku-full-root-facts.json
python3 scripts/probe-iku-upper-actions.py --opening --whole --smoke --control prelude-countdown > build/iku-full-root-countdown-control.json
python3 scripts/probe-iku-upper-actions.py --opening --whole --smoke --control unordered-face > build/iku-full-root-face-control.json
python3 scripts/check-match-literals.py --require-target
python3 scripts/validate-tracking.py --require-target
python3 scripts/ci.py
git diff --check
```

The local CI gate passes all 200 workflow tests, ledger/graph/literal audits
and generated-progress checks; `git diff --check` passes.

The canonical comparison and negative controls intentionally exit nonzero.
Generated objects/reports stay under `build/`, private analysis under
`.analysis/`. Run a fresh IDA metadata preflight before a new bounded work
unit; a wrong IDA image blocks that session, not hash-attested PE inspection.
