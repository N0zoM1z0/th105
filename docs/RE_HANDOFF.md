# TH10.5 reconstruction handoff

Cleanup checkpoint: 2026-10-24. The working source is ready for handoff;
this checkpoint adds no exact functions or bytes. Required commit format:
`gpt-6.1-sol: ...`.

Current priority remains complete large-function exactness before gameplay
naming. Keep necessary types, offsets, numeric states, control flow and side
effects, and compare the entire function early. The read-only TH075 review is
in [the workflow](RE_WORKFLOW.md#exact-first-priority-from-the-th075-review).
Its VC7.1 compiler settings do not transfer to this VC8 target.

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
| Mapped / source-present | 1519 / 1501 |
| Accepted authored exact | 1381 functions / 234914 bytes |
| Provisional authored byte denominator | 2136806 |
| Match units / configured functions | 543 / 1511 |

These are ledger totals, without a new aggregate cold replay. Replay affected
accepted units after shared changes; aggregate claims require a cold
`python3 scripts/verify-exact-units.py --all`.

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
