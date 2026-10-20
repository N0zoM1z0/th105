# TH10.5 reconstruction handoff

Current as of 2026-10-21. Phase: active ReimuObject496540 exact reconstruction.
The905..908 match-mode switches now follow the target's physical3/2/1/0 order;
all12 first-spawn packet stack offsets for906..908 are restored. Focused26342
inputs and3600 whole-root/helper samples pass. The root remains nonexact at
49655F/+31;905 packet placement,906/817 call sharing and return layout remain
open. No new exact function is claimed. The latest accepted entry remains
CDesignSprite40AEE0 at19/19, with its affected CDesignGage renderers60/68.
CGage41B3F0 remains nonexact in one multiplication load-order pair; binder404DF0
remains102/107 nonexact. Live ledgers and fresh comparisons override dated prose.

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

`ReimuObject_dispatch_action_state_vslot28 @496540` remains source-present in
`src/characters/ReimuObjectActionStateStaging.cpp`, unit
`gpt-web-reimu-object-action-state`. Vtable6C40A4/cell6C40CC slot28, ECX/RET0
and caller4937D0 ignoring EAX are observed. The void return remains inferred.
The provisional39853-byte main candidate and full46138-byte owned comparison
through4A197A are unchanged:46128 owned bytes plus10 alignment bytes. Raw target
closure still has10670 instructions,22 switches and68 RETs.

All four target match-mode tables index0/1/2/3 but physically order their
blocks3/2/1/0. Reordering those four complete source case bodies restores all12
native first-World packet offsets for906/907/908. Their four distinct packet
identities and payloads are retained;905's packet placement still differs.
Period tests, operations, outgoing arguments and breaks are unchanged.905's
four real live packets still feed its shared second-spawn/wave consumer.
Earlier local retirement exits, ordered stores and902 typed owner publications
remain. No shared header, profile, binding or ownership change.

| Selected artifact | SHA256 |
| --- | --- |
|CPP|`295be3bcbcb2b21cec2c0f09a3f56ae3dcd6fe268f1008b3ca80672598a99797`|
|Unchanged header|`6f469e6886959fd41ee6976b3c784c3df0c2e753ad4729a536764a3c8cd28b4b`|
|Formal COFF|`922a322ed8fd9c608c7a1144e63a13eb15a5bc394b3ad14199373028924d9f5c`|
|Whole46152-byte canonical source section|`7c16e018acfd53917697ba5d43c874868334adfa819526fc24fa09f71e22a714`|
|Fixed46138-byte compared prefix|`c49c7572b17f0baadaff6542d4a1a52b9b681f5cfeb55aaf02d0060d2f82a0d1`|

The root remains **nonexact49655F/+31**, a jump displacement; frame438h remains.
Source prefix45284 plus868 metadata bytes emits10446 decoded/10445 reachable
instructions,71 RETs and426 physical calls versus target433. Fourteen extra
payload bytes are not near-exact evidence. Call-membership distance9,
RET-distance29 and owner identity1/43 are diagnostics only. Same-TU4963A0
freshly stays **66/66 exact**, canonicalad12b782. No new exact/partial credit.

906 still shares three final-World/wave pairs kept private by the target;
817 advance still shares with860/861.905 retains its corrected call graph.
Source-to-source full instruction/edge diagnostics leave31/43 physical owners
identical. Six earlier owners only retarget the moved shared World tail;
951 changes temporary registers and the default owner gains a compiler NOP.
The shared seven-action18-byte post-World tail remains byte-equal. The complete
World-site check still rejects99 target versus96 source sites; its540 actual903
and180 retiring-request prefixes and conditional903 call graphs still agree.

Focused26342 inputs in24 affected high/final cohorts pass with zero output,
ordered-write and retirement-live-x87 differences, input6031e9a6. CPU0/nice10:
115.67s wall time, peak RSS198232KiB.3600 whole-root stride37 inputs and the
same3600 helper-entry inputs pass, inpute90a5943;4359F0 remains unvisited.
These samples do not execute all typed stores.902's static spill/reload and
822's heading pair remain; the post-opaque822 pair has zero executions.
Scoped905/907/908 passes12 actual first prefixes/conditional call graphs;
the default still rejects906.16 native packet observations confirm the12
restored slots. Original opaque World/driver/CRT returns are never fabricated.
Logical x87 diagnostics exclude physical TOP/flags.

The predecessor's full133192/hashf46a849f receipt belongs to CPP1c9a12c4 and
is not reissued or bridged to this changed root. Full native byte equality
bridges the order-control to the tested formal COFF and that COFF to the final
rebuild after CSV line-ending normalization. It preserves only the new scoped
receipts. No all-unit replay or aggregate percentage is claimed.

Four genuine906 argument/type/counter-scope/spawn-visibility controls reproduce
the predecessor's complete46148-byte b12eab22 body unchanged. Visible64CCB0
independently stays78/78. A905 case-scoped packet/shared-consumer control is
also byte-neutral against the new selection. They are unselected; no universal
source/compiler or LTCG barrier follows.906's earlier PUSH3 scheduling alone
does not establish argument-expression source spelling.

See [selector-order evidence](REIMU_OBJECT_SELECTOR_ORDER_2026_10_21.md),
[preceding905 packet join](REIMU_OBJECT_905_PACKET_JOIN_2026_10_21.md) and
[the evidence index](REIMU_OBJECT_EVIDENCE.md). Receipts and frozen inputs are
in `build/reimu-object-906-tail-20261021/`, with private recipes under the same
`.analysis/` scope.56 completed unselected files are compressed5248235->666168
bytes after SHA256 readback. Baseline/selected/order-control inputs stay loose;
primary databases/tools/target are retained. Original source/TU, arbitrary
aliases/resources/vtables, nonnull rendering, opaque continuations and
unmasked exceptions remain open.

## Other preserved checkpoints

These entries describe selected or accepted state; they are not an active
work queue. Detailed controls, pins and limitations remain in the linked pages
and [the October20 handoff snapshot](RE_HANDOFF_HISTORY_2026_10_20.md).

| Address / scope | State and remaining question | Evidence |
| --- | --- | --- |
| 40AEE0 CDesignSprite uniform scale | Newly accepted complete19/19; affected CDesignGage60/68 also replay exact. RTTI slot18 and factoryAC/member18 support typed writesA0/A4. First two parameter semantics and original method spelling remain open. | [Sprite scale](DESIGN_SPRITE_SCALE_2026_10_21.md) |
| 404DF0 texture-stage binding | Source-present102/107 nonexact at entry. Ordinary typed call preserves pre-lookup vptr capture and post-lookup device reload. Target common EBX/EBP saves/four-byte slot remain unresolved; source saves conditionally. Native0/160 stops atRET/lookup/device CALL/real null fault; wrong hoist80/160. Genuine closed CIL context also102; no compiler-impossibility claim. | [Texture binding](TEXTURE_STAGE_BINDING_2026_10_21.md) |
| 40AEA0/40AF30 CDesignGage render entries | Newly accepted complete60/68. Ordinary pragma-free O2 preserves enabled14, float sums04/08+0C/10, incoming offsets last and actual member+18 virtual call1C. Original base data ownership remains open; no shared-header change. | [Design gauge rendering](GAGE_DESIGN_RENDER_2026_10_21.md) |
| 41B3F0 CGage renderer | Complete source-present1010/323; live height reference restores41B549/41B54F. Strict comparison remains nonexact at41B580/+190: only two instructions/four bytes differ; other321 including full COM tail match. Fresh native0/4490 stops atRET or real texture-bind entry. New product/inheritance controls do not improve the residual. Original final operand/source/TU context remains open; no exact credit. | [Live-height context](GAGE_RENDER_CONTEXT_2026_10_21.md) |
| 40AD60/40BAC0 and40AF00/10/20 gauge family | Newly accepted56/64/11/11/11. RTTI and factory prove CGage member+18/value+A0; ordinary lifetime and color calls match all five bodies. Constructor/full runtime virtual recovery remains open. | [Gauge lifetimes](GAGE_LIFETIME_2026_10_20.md) |
| 40ADB0 CNumber normal destructor | Newly accepted40/40. An explicit embedded-tile destructor naturally restores member-before-base vptr order. All five affected lifetime functions compare exact; no shared-header/profile/layout change. | [Member lifetime](CNUMBER_MEMBER_DESTRUCTOR_2026_10_20.md) |
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
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-typed-stores.py build/match-units/GptWeb_ReimuObjectActionState.obj --output build/reimu-object-exact-20261020/typed-stores-replay.json
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
