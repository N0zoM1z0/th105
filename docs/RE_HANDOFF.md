# TH10.5 reconstruction handoff

Exact-first reconstruction checkpoint: 2026-10-24. Remilia input policy
`0x556070` and independently reviewed Tenshi `0x64B7A0`, Sakuya `0x4DF4B0`
Suika `0x5AED00` and Youmu `0x53B410` cold-replay exact. The five-function cohort
adds28530 code bytes; latest peer adds6017. Youmu matches its first complete
compiled source after a private source-composition syntax correction.
Required commit format:
`gpt-6.1-sol: ...`.

Current priority remains complete large-function exactness before gameplay
naming. Keep necessary types, offsets, numeric states, control flow and side
effects, and compare the entire function early. The read-only TH075 review is
in [the workflow](RE_WORKFLOW.md#exact-first-priority-from-the-th075-review).
Its VC7.1 compiler settings do not transfer to this VC8 target.

The renewed user direction is to prioritize complete medium/large functions,
compare the first complete source early, test one evidence-backed hypothesis
per trial, and switch candidates after repeated neutral controls. Follow a
successful representative through independently reviewed family differences.
Keep large execution matrices scoped to concrete ambiguities and defer naming,
beautification and abstraction. Compile serially at CPU0/nice10 and monitor
available memory/swap. Commit and push stable checkpoints only after local CI.

## Start here

Read [AGENTS.md](../AGENTS.md), [architecture](ARCHITECTURE.md),
[workflow](RE_WORKFLOW.md), relevant source and the scoped evidence before edits.
Use one writable session, one bounded scope, no subagents/concurrent VC8 builds;
claims.csv stays header-only. Heavy commands use CPU0/nice10.

Only original Japanese 1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.

```sh
git status --short
python3 scripts/verify-target.py
python3 scripts/check-ida-mcp.py
python3 scripts/report-reconstruction-status.py --summary
python3 scripts/validate-tracking.py --require-target
```

IDA still opens database SHA256
`10350095bcf95edb59e03bee9849a2dc8a7714b4927ad5909c569c550fce6822`.
Its failed preflight blocks that session's semantics and writes. Raw inspection
of the hash-attested target PE remains available. Independently attest any
Ghidra import and use at most one process; preserve primary analysis databases.

| Ledger layer | Current value |
| --- | ---: |
| Provisional candidates | 4024 |
| Authored / excluded / origin review | 1595 / 1418 / 1011 |
| Mapped / source-present | 1525 / 1507 |
| Accepted authored exact | 1386 functions / 263444 bytes |
| Provisional authored byte denominator | 2136806 |
| Match units / configured functions | 549 / 1517 |

These are ledger totals, without a new aggregate cold replay. Replay affected
accepted units after shared changes; aggregate claims require a cold
`python3 scripts/verify-exact-units.py --all`.

## Exact family peer: Youmu input policy 0x53B410

[Accepted peer/evidence](YOUMU_INPUT_POLICY_2026_10_24.md) closes1714
instructions/28 RETs/nine external tails and all8 table destinations. The first
complete compiled source matches6017 callable/full6052 payload bytes and121
relocations; formal and independent cold builds pass:

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py --unit exact-first-youmu-input-policy --compare --json
python3 scripts/audit-youmu-input-policy.py
```

Full canonical SHA256:
`050e801122ba3cee6da69fb3abdcca297922e24d08913ef938c1b4e42a962fa1`.
Three real slot0C sequence calls,540 continuation, changed command tiers,
air queued pack-only exit,double100.0/float90.0 and actual query/resource order
are independently reviewed. The generated table negative fails at+1784. No
compiler/profile search; previous accepted headers/sources are unchanged. Keep
the unrelated nonexact YoumuObject initializer parked as documented below.

## Exact family peer: Suika input policy 0x5AED00

[Accepted peer/evidence](SUIKA_INPUT_POLICY_2026_10_24.md) independently closes
1667 instructions/31 RETs/six external tails and all9 table destinations. The
first complete source matches5849 callable/full5888 payload bytes and117
relocations; formal and independent cold builds pass both commands:

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py --unit exact-first-suika-input-policy --compare --json
python3 scripts/audit-suika-input-policy.py
```

Full canonical SHA256:
`aad5c91e0526eabc05c81285aa78e1723f0adbccb30f92f8745ce47724f4940b`.
The generated-table negative fails at+16DC. +60D tier531/530, shared545 success,
air523/522 zero gates and508/507 tiers, record200-to650,160.0f and reordered
normal-air policy are independently reviewed. No source correction or compiler
search was needed. Earlier exact input sources remain unchanged. Continue the
other complete slot+0x50 peers with independent target review.

## Exact family peer: Sakuya input policy 0x4DF4B0

[Accepted peer/evidence](SAKUYA_INPUT_POLICY_2026_10_24.md) closes1687
instructions/33 RETs/six external tails and independently checks all10 table
entries. The first complete source matches5897 callable bytes and the full
5940-byte payload/120 relocations. Formal and independent cold builds pass:

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py --unit exact-first-sakuya-input-policy --compare --json
python3 scripts/audit-sakuya-input-policy.py
```

Full canonical SHA256:
`57689f32d9ee39731ad0682f45652b77a0f9c6e26323c9e879fe61a9504812c3`.
The generated-table negative fails at+170C. Ten queued commands, changed tier
fields/action pairs, air+608/+60C zero gates, repeated308/400 queries and90.0f
are target-reviewed. No compiler/profile search or source correction was needed.
Prior accepted inputs are unchanged. Continue complete slot+0x50 peers under
independent review and both callable/full-payload comparisons.

## Exact family peer: Tenshi input policy 0x64B7A0

[Accepted peer/evidence](TENSHI_INPUT_POLICY_2026_10_24.md) independently closes
1515 instructions/26 RETs/seven external tails. The5352-byte callable and full
5384-byte payload/108 relocations match after separate canonical and cold builds.
Replay both commands:

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py --unit exact-first-tenshi-input-policy --compare --json
python3 scripts/audit-tenshi-input-policy.py
```

Full canonical SHA256:
`20bb75cd53cebe9b7714eb97bc8fdd4160b2310e2599d38aaef74acbb2b064d5`.
A table-byte generated-object negative fails. Changed special-command tiers,
signed+82E gate, record207-to657, normal state200 transitions, absent Remilia
cleanup/shortcuts and140.0f distance are independently reviewed. Correcting
one copied541 fallback to the actual540 yields zero differences and the native
shared block; no flag/profile or register search. Prior exact inputs stay intact.

Next, continue another complete Fighter slot+0x50 peer from the two accepted
representatives, reviewing its actual changes before comparison. Keep views
pointer-only and do not normalize query/action-number differences or repeated
calls. RemiliaObject's initializer below remains nonexact and parked.

## Exact representative: Remilia input policy 0x556070

[Accepted source/evidence](REMILIA_INPUT_POLICY_2026_10_24.md) closes all1470
instructions/16 RETs/eight external tails. Both the5415-byte callable and the
complete5448-byte payload/112 relocations match after independent cold builds.
Replay both commands:

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py --unit exact-first-remilia-input-policy --compare --json
python3 scripts/audit-remilia-input-policy.py
```

The complete canonical SHA256 is
`aa8fea23fd443bab1f58993e3f8d41f3ee7d262b70f2ea3d5ec74a6e75c3dcec`.
A generated-object table-byte negative fails the full-payload audit. Source
retains numeric commands, offset fields and real repeated queries. Two initial
query/action-number mistakes were corrected from native pushes; removing an
eager queued-field cache recovers the native range guard. No compiler/profile
or hierarchy search was needed. Only the representative earns credit; callees
remain at their previous states. Never instantiate/embed its pointer-only views.

Next, review another complete Fighter primary slot+0x50 peer against this
representative, independently checking changed gates, command/action pairs,
offsets, ABI and exits. Preserve RemiliaObject's nonexact checkpoint below;
do not resume neutral initializer-register trials without new evidence.

## RemiliaObject initializer 0x55BE70

[Complete source/evidence](REMILIA_OBJECT_ENTRY_2026_10_24.md) covers the
4997-byte callable and full5384-byte payload, including all three destination
tables and the199-byte remap. Unit `exact-first-remilia-object-entry` freshly
builds and remains nonexact at+0x80. The selected full canonical SHA256 is
`d114fd28eaefcbc4fb8f1c8ebe1ceb7512661cdabb05624179ec85bab5be2aac`.
All21 conversion/virtual calls,42 RNG calls, seven motion calls, two spawns and
both replacements are present. Explicit used casts retain product rounding;
a double captures851's input float across its byte write without an extra spill.

Residuals are selector-call registers,901's shared heading-block placement and
the980 CALL+RET versus target tail JMP. Named-field versus offset access is
byte-neutral, and terminal/default controls regress the remap range. Do not
repeat these controls unchanged. The selected receiver is declaration-only;
never construct/embed it. No exact credit, runtime matrix or LTCG impossibility.

The subsequent input-policy representative above is exact; this initializer's
source and retained controls remain a separate nonexact checkpoint.
Read-only Ghidra was independently attested; all pinned primary DB
files are unchanged. Receipts/recipes are under
`build/exact-first-remilia-entry-20261024/` and
`.analysis/exact-first-remilia-entry-20261024/`.

## AyaObject update 0x61A290

The initializer and update now share
[AyaObjectActionView.hpp](../src/characters/AyaObjectActionView.hpp), removing
duplicate receiver declarations. Its 15 offset assertions and 0x388 prefix-size
assertion express a partial call view; never construct or embed it. The actual
primary vtable `0x6C624C` owns update slot+0x28 and initializer slot+0x3C.
Slot+0x0C consistently takes short. Aya's vtable `0x6C62D4`, published by the
constructor at `0x61861C`, and AyaObject both bind that slot to `0x45C390`.
No original complete allocation or TU identity is claimed.

| Method / unit | Callable / complete payload | Current result |
| --- | --- | --- |
| `0x61A290`, `gpt-web-aya-object-vslot28-full-root` | 19522 / 20000 | Nonexact +0x22 |
| `0x61F0B0`, `gpt-web-aya-object-action-entry` | 4531 / 4859 | Two differences: +0xBF7 / +0xBFF |

Current raw CRLF source SHA256:

- [Update](../src/characters/AyaObjectActionState.cpp): `15a6f13a5ea5a751fa7f6cec6dbffed628bd373e0bb29e984788f8bbefbe0a72`.
- [Initializer](../src/characters/AyaObjectActionEntry.cpp): `fa06d792237a849bb70c2cc7dc1a38e92bb0b8bcce056bb26c7914e945cd4280`.
- Shared header: `2ed12ce922918d59726cc45f0fcc8c514a43b3c1cec0b13c1a0f8a64ad8728c5`.

Both complete canonical payloads equal the preceding separate views:
update `5f2966cb6b34c844d210ac54e52894b5d510c17362c3fe2424c1d2de6b89c4ec`,
initializer `6f70b6f354fdff459a628bdfbf0a7a3c12fe854a65f95f6cf33731b5d606b066`.
Only receiver declarations, member qualifications and their unit-local symbol
aliases changed. Earlier runtime matrices retain their recorded scope; this
checkpoint proves machine-payload equality and makes no fresh runtime claim.

The selected update still has the partial807/817 frame-tail join, used817/822
angle captures and local double quantized lookup views. It has12 physical frame
helper calls versus target11. See the [selected evidence](AYA_OBJECT_PARTIAL_FRAME_TAIL_2026_10_23.md)
and [epoch index](AYA_OBJECT_EVIDENCE.md) for behavioral contracts and limitations.

A new retained lead defines the real frame/phase methods under the common
receiver. Both source orders reproduce helper `0x4351C0` 62/62 and `0x64CD00`
73/73, and reduce update's frame-helper calls12 to11. However, the update grows
to20032 bytes, SHA256 `23925cd489b690a45c7c49f04f52dacac967c01896200853c4ef95069d5655e6`,
and stays nonexact at+0x22; the initializer still differs at two bytes. This TU
is unselected. A matching call count is a diagnostic, not acceptance. Receipts:
`build/aya-joint-owner-20261024/summary.json` and its archive/restore manifest.

For continuation, compare which frame call disappeared in that TU with the
target's physical tail/return graph. The initializer's856 pointer register
lifetime remains unknown. Six common-receiver/ABI controls preserve the selected
payloads; an int sequence declaration regresses the initializer. Prior source
order, getter/lifetime, /Zi, FP-profile, hierarchy and linked-context controls are
recorded in [the initializer evidence](AYA_ENTRY_SEQUENCE_WORD_ABI_2026_10_19.md).
Do not repeat those unchanged trials. Later C2 patches remain untested; the
archived download listings and inspected Vista package did not yield a backend.

## Other open roots

| Root | Retained result | Evidence |
| --- | --- | --- |
| ReimuObject `0x496540` | Full45696, nonexact +0x1F; adjacent counter `0x4963A0` 66/66 exact | [Current index](REIMU_OBJECT_EVIDENCE.md), [owner/joint context](REIMU_OBJECT_WORD_OWNER_JOINT_CONTEXT_2026_10_23.md) |
| Reimu initializer `0x4A1CE0` | 14 differences; genuine joint CIL still nonexact | [Joint context](REIMU_OBJECT_WORD_OWNER_JOINT_CONTEXT_2026_10_23.md) |
| Youmu initializer `0x543670` | Callable5159/full5492; 21 register/preparation bytes differ; metadata agrees | [Current evidence](YOUMU_ENTRY_PHYSICAL_TAIL_2026_10_23.md) |
| AyaObject initializer `0x61F0B0` | Callable4531/full4859; two register bytes differ | [Current evidence](AYA_ENTRY_SEQUENCE_WORD_ABI_2026_10_19.md) |

Youmu's retained canonical SHA256 is
`d00f4fc4ceca80c8fc4510ff03dcf064e3188fa5dc33afc8e25815d880da413a`;
source SHA256 `66d01e60ca540b11515ebe4a58dc87f913ab340dd4845bcb1e992d9000c9be2d`.
Its physical copy count, read order and all332 metadata bytes must be retained.
Sequence selector `0x45C390` uses real checked `std::map::find`; its accepted
10-function native unit and independent short witness passed at `de8037a`.
Its 105-byte generated find remains excluded library code. No new replay of
that unit or the 592-case Youmu matrix is claimed here.

Other pending roots include Reimu Fighter `0x478FA0`, CGage `0x41B3F0`, loader
`0x40B000` and renderer `0x415050`. Font evidence remains in
[begin](TEXT_FONT_BEGIN_CONTEXT_2026_10_22.md),
[glyph](FONT_GLYPH_WINDOW_PROOF_2026_10_22.md),
[accent](TEXT_FONT_ACCENT_LIFETIMES_2026_10_22.md) and
[markup](FONT_MARKUP_CONSTRUCTION_CLEANUP_2026_10_22.md).
Older handoff detail is available at Git `4dd8436` and in the
[October23 narrative](RE_HANDOFF_HISTORY_2026_10_23.md).

## Artifacts and final gate

Generated artifacts belong under `build/`; private recipes/analysis under
`.analysis/`. Preserve compiler installs, target resources, primary analysis
state and the native-provider inputs referenced by retained CIL receipts.
Completed controls are archived only after every member's length/hash is
checked; per-scope `retention.json` files provide exact restore commands.
The cleanup inventory is `build/handoff-cleanup-20261024/retention.json`.
Legacy `.analysis/gpt-web` exports were archived with a restore command there;
six historical worktrees with uncommitted source were left untouched.
Do not use indiscriminate `git clean` or delete unknown analysis state.

Focused commands, run serially; both Aya comparisons currently return1 because
their recorded mismatches remain:

```sh
python3 scripts/build.py --unit gpt-web-aya-object-action-entry --compare --json
python3 scripts/build.py --unit gpt-web-aya-object-vslot28-full-root --compare --json
```

Before any commit, push or PR, run in the finished worktree:

```sh
python3 scripts/ci.py
git diff --check
```

The local gate is mandatory and must follow the final tracked edit. Target
observations, source hypotheses, runtime contracts and canonical acceptance
remain separate. No assembly, copied target arrays, inert locals, fake returns,
ABI lies or padding may be used to force a result.
