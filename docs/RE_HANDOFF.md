# TH10.5 reconstruction handoff

Current as of 2026-10-20. Phase: checkpoint cleanup and handoff. No new
reconstruction scope is in flight. The latest selected change is the
ReimuObject850/853/854 store-order and local fade-return recovery below.
Live ledgers and fresh canonical comparisons override dated prose.

## Target, workflow and acceptance

Use only original Japanese TH10.5 v1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Read [AGENTS.md](../AGENTS.md), [architecture](ARCHITECTURE.md) and
[workflow](RE_WORKFLOW.md). Use one writable session, one bounded unit and
serial VC8 builds; keep heavy work at nice10/CPU0. Do not delegate matching.

```bash
git status --short
python3 scripts/verify-target.py
python3 scripts/check-ida-mcp.py
python3 scripts/report-reconstruction-status.py --summary
python3 scripts/validate-tracking.py --require-target
```

The target and tracking checks pass. IDA attestation fails with SHA256
`10350095bcf95edb59e03bee9849a2dc8a7714b4927ad5909c569c550fce6822`;
do not use that session's semantic data. Raw canonical PE inspection remains
available. Independently attest any direct Ghidra project before semantic
use, keep one process, and read back metadata changes. Do not use the factory
adapter or patch target bytes.

Nine current primary DB pins are retained in
`build/reimu-object-fade-order-20261020/primary-db-after.json`; they agree with
the preceding animation checkpoint. No Ghidra process or metadata write was
used for the fade recovery. Earlier saved loader/Object views and their
CALL_RETURN metadata are described in the archived handoff.

`implemented.csv` means source-present; `matches.csv` means accepted exact.
`claims.csv` remains header-only. Diagnostic windows, native fixtures and
successful compilation confer no partial exact credit. No cold aggregate
replay or new aggregate percentage is claimed. The user requests focused
affected checks, regular commit and push, and careful re-examination of old
assumptions when reconstruction resumes.

## Current ReimuObject update source phase

`ReimuObject_dispatch_action_state_vslot28 @496540` is source-present in
`src/characters/ReimuObjectActionStateStaging.cpp`, unit
`gpt-web-reimu-object-action-state`. Its primary vtable is6C40A4, cell6C40CC
at slot28, following opaque24. ECX/RET0 and caller4937D0 ignoring EAX are
observed; the source void return remains an inference. The39853-byte candidate
is provisional. Comparison covers46138 physical bytes through4A197A,
including46128 owned bytes and10 alignment bytes.

The selected850/853/854 change orders real angle X/Y/heading, scale X/Y and
velocity X/Y writes. Three negative-scale frame2 paths now decrement330 and
return locally. The8531.5f clamp keeps both writes conditional. Three72-byte
fade kernels and three12-byte zero-store pairs agree without masks:252
**diagnostic** bytes. The300-input finite native audit checks actual store
order, x87 state/status and RET/frontier outcomes; all pass. Three compiled
controls retain equal final outputs but fail event or private-kernel checks.

| Selected artifact | SHA256 |
| --- | --- |
| CPP | `08cc1a0f7815e8724ea5102369a42f522b21f4e5d360a07a9604fcb424293915` |
| Header | `6f469e6886959fd41ee6976b3c784c3df0c2e753ad4729a536764a3c8cd28b4b` |
| Frozen tested COFF | `82fee43c09f3c381f178a241ecb3b08a9e878cd94cd85fa1227defe11edf2dab` |
| Canonical45776-byte payload | `343089b74da3c9e70d871c25c15e84586cf380979c88e8339b72a46b8d45e015` |
| Native45776-byte payload at800000 | `1686c3b77f29036ca9f7b0ebbcb02a93a6844f335ba1bdf0cfe93123c9a58933` |

The final formal COFF is94e2457e; only timestamp bytes4/5 differ from the
frozen tested container. All other bytes agree. The root remains **nonexact
at49655F/+31** with natural438h frame,65 source RETs versus68 target RETs,
and owner diagnostics1/43. No root exact/remote_exact row or credit is added.
The actual separate4963A0 definition retains27 root REL32 references and
**66/66 canonical exact**, SHA256ad12b782. Other accepted Runtime-unit inputs
and their preceding57/62/73 receipts are unchanged; no unrelated replay here.

Full native execution passes0/133192, input SHA256
`f46a849ff57f64bb16e77fd0e28f7f51eee7238501c04049add99e7f77fc3b8b`.
All20 serial selected/negative/owner/runtime commands have expected exits.
All25 direct-callee partitions,29 indirect memberships and22 animation sites
remain. Preserved checks include999's792 original-code witnesses,869/901's128
lookup-return witnesses,3360 animation inputs, actual801/852 selector calls,
World540+180/four-joint cases, and the scoped812/900/901/804/caller audits.
Orientation400, alpha1170 and terrain288 retain expected results; terrain
includes48 hardware-unqualified nonfinite contexts.349 ledger literals,
775 mappings and1124 target references pass. Source/header/COFF/native/support
pins agree before and after execution.

Remaining limits: World first-pointer slots agree12/14 across19 witnesses;
822 health is targetF+190/sourceF+1A0 and900 completed sequence0 is targetF+164/
sourceF+104. Returning opaque graphs, arbitrary aliases/resources/vtables,
nonnull rendering and unmasked exceptions remain unproved. Global lookup
return types, original source spelling/TU ownership and remaining RET/register
lifetimes are open. Preserve the recovered999-only x87 cleanup and869/901
consumers; do not infer a globally recovered API from caller-side float views.

See [current fade-order evidence and commands](REIMU_OBJECT_FADE_ORDER_2026_10_20.md)
and [the evidence index](REIMU_OBJECT_EVIDENCE.md). Receipts are in
`build/reimu-object-fade-order-20261020/`; private recipes use the matching
`.analysis/` scope. The direction page corrects its historical native869/901
addresses to805E1E/80681C from frozen reports; current addresses are805E3B/
806839. The earlier address transcription did not change bytes or results.

## Other preserved checkpoints

These entries describe selected or accepted state; they are not an active
work queue. Detailed controls, pins and limitations remain in the linked pages
and [the October20 handoff snapshot](RE_HANDOFF_HISTORY_2026_10_20.md).

| Address / scope | State and remaining question | Evidence |
| --- | --- | --- |
| 478FA0 Reimu Fighter root | Declaration-only; complete genuine82808-byte payload remains nonexact at4791BD/+541. Selected source7650c8d3, payloadfbc0293d; all153 RET memberships agree.300/320 physical CALL ownership,616 effect preparation and720 request indexing remain open. | [616 completion](REIMU_616_SHARED_COMPLETION_2026_10_20.md), [300/320 controls](REIMU_300320_IDENTITY_CONTROLS_2026_10_20.md) |
| 4A1CE0 ReimuObject initializer | Source-present, nonexact;14 callable bytes differ in906/999, first4A2E20/+1140. Source3803a002,5440-byte payload65298d36;548 metadata bytes agree. | [Entry](REIMU_OBJECT_ENTRY_2026_10_19.md), [conversion/context](REIMU_OBJECT_CONVERSION_CONTEXT_2026_10_20.md) |
| 543670 YoumuObject initializer | Source-present, nonexact; preserve the short interface,902 order,29 distinct destinations/two switches.820/850 lifetimes and851's post-write read remain open. | [Word interface](YOUMU_ENTRY_SEQUENCE_WORD_2026_10_19.md) |
| 61F0B0 AyaObject initializer | Source-present; previous4859-byte envelope retains two differences. Low-word evidence supersedes the old11-site scheduling diagnosis. | [Word ABI](AYA_ENTRY_SEQUENCE_WORD_ABI_2026_10_19.md) |
| Reimu CPU root | Source-present probe, no exact acceptance. Preserve coupled terminal/helper execution and ordered floating-point policies. | [Archived current checkpoint](RE_HANDOFF_HISTORY_2026_10_20.md#current-reimu-cpu-root) |
| 46CA80 family1 pair | Source-present,557/542 nonexact at+18; scoped native coverage passes0/2638. | [Pair response](FAMILY1_PAIR_RESPONSE_2026_10_20.md) |
| 46DFF0 collision phase | Source-present,1449/1452 nonexact at+559; final conversion/register schedule unresolved. | [Collision phase](BATTLE_COLLISION_PHASE_2026_10_20.md) |
| 596370 Object action980 | Accepted323/323. Short selector argument supersedes the October2 scheduling/LTCG stop condition. | [Word ABI](OBJECT_ACTION980_WORD_ABI_2026_10_19.md) |
| 46DD40 family1 traversal | Accepted686/686; native checked list ownership recovered. | [Traversal](FAMILY1_OBJECT_CLASHES_2026_10_20.md) |
| 45C500 collision preparation | Accepted2156/2156; old2164-byte/frame34h residual was source lifetime. | [Preparation](COLLISION_GEOMETRY_PREPARATION_2026_10_19.md) |

Other loader, archive, package, gauge and auxiliary-sprite checkpoints remain
in the snapshot. Obtain accepted state from the live ledgers before changing
them. No standalone-object or LTCG impossibility follows from an unsuccessful
control or a compiler instruction count.

## Artifacts, reproduction and final gate

[Artifact retention and recovery](ARTIFACTS.md) describes the cleanup manifest,
lossless historical report compression, retained private inputs and caches.
The current source, selected/negative objects and regression reports remain
available. Preserve the canonical executable, compiler installations, primary
Ghidra project, frozen controls and private regeneration recipes. Old report
paths may have `.gz` copies; restore them before recipes that require plain JSON.

The detailed pre-cleanup operational record is archived; earlier archives are
[October18](RE_HANDOFF_HISTORY_2026_10_18.md),
[October2](RE_HANDOFF_HISTORY_2026_10_02.md) and
[September26](RE_HANDOFF_HISTORY_2026_09_26.md). Dated pages retain historical
pins, not automatically current commands, priorities or prototypes.

For the current mixed root/helper unit:

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py --unit gpt-web-reimu-object-action-state --compare --json
# Expected nonzero result:496540 mismatch+31,4963A0 exact66/66.
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-fade-order.py build/match-units/GptWeb_ReimuObjectActionState.obj --output build/reimu-object-fade-order-20261020/fade-replay.json
```

Before **every commit, push or pull request**, run in the finished worktree:

```bash
python3 scripts/ci.py
git diff --check
```

A local pass is mandatory; GitHub Actions does not substitute. Rerun after any
subsequent tracked edit. Commit stable work with `gpt-6.1-sol: ...`, push,
verify remote HEAD, and check the worktree is clean. Do not commit executables,
game data, databases, generated reports, toolchains or credentials.
