# TH10.5 reconstruction handoff

Current as of 2026-10-21. Phase: active ReimuObject496540 exact reconstruction.
Seven ordinary local retirement exits now preserve the observed state330
write-before-x87-pop lifetime and remove premature EBP1/EBX0 hoisting. The
new133192-input combined replay has zero output, ordered-write and retirement
state differences. The root still fails canonical equality at49655F/+31:
physical return/call sharing and source/TU context remain unresolved.
No new exact function is claimed. The latest accepted entry remains
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
and caller4937D0 ignoring EAX are observed. The void source return remains an
inference. The39853-byte main candidate is provisional; full comparison still
covers46138 physical bytes through4A197A, including46128 owned and10 alignment
bytes. Raw closure reconfirms10670 instructions,22 switches and68 target RETs.

Ordinary decrement/return replaces the generic retirement jump at seven
source sites:812's completed sector loop;821's compound owner gate;822's
channel112 gate; and855/869/903/904's existing compound bounds tests. No
predicate is split and no numeric value/local is introduced. Target4980E4
and49B8E7 decrement330 before popping a live x87 value; the new source now
matches sampled and full-matrix retirement states. All previous ordered-store
recoveries,902's eight asserted owner float publications and999's cleanup
remain in place. No shared header, selected profile, binding or ownership change.

| Selected artifact | SHA256 |
| --- | --- |
|CPP|`a2c44054550380596f67b5aced05f301cab26cd711ac5c22b68f06e64f162ef1`|
|Unchanged header|`6f469e6886959fd41ee6976b3c784c3df0c2e753ad4729a536764a3c8cd28b4b`|
|Formal COFF|`4ddca4f4ff71c900385602bad74f1159bdebcc1c01b2db8ffd7cee9c1e0f8118`|
|Whole46328-byte canonical source section|`7842896240c69e2d920e76b4c39262f8d43257faba0574d5bfcf849e92b28e8c`|
|Fixed46138-byte compared prefix|`fb49c2c120a902b1b59b50a82f31cfe931e6fdc98720385ebf726b147861a1d1`|

The root remains **nonexact at49655F/+31**, a jump displacement. It retains
its natural438h frame. Its source prefix before868 bytes of metadata is45460,
versus target table offset46140; do not treat the full-section size46328 as
callable size. Source71 RETs versus target68, RET-membership distance29 and
entry/default instruction-edge identity2/43 are diagnostics only. Source CFG
reaches10491 instructions. The separate real4963A0 stays **66/66 exact**,
canonicalad12b782. No matching/remote-exact row or partial credit is added.

Call sharing is still different: source432 physical calls versus target433.
The source shares an advance call for817/860/861 where the target has two.
Three World/wave pairs have905-only source membership and906-only target
membership under complete conservative static reachability. This is physical
partition evidence, not predicate feasibility or demonstrated wrong output.
Canonical return/call layout and original source/TU context remain open.

The combined `audit-reimu-object-retirement-fpu.py --stride 1` passes all133192
inputs, hashf46a849f, with zero output, object/owner/parameter ordered-write
and retirement-live-x87 differences. All16 prefix first-store sites execute;
each902 owner publication executes144 times and retains float spill/reload.
822's post-opaque parameter/heading pair retains static order but has zero
executions. This single affected-root pass includes the typed-store coverage;
no second full typed-store replay or historical19-command sweep is claimed.

The initial control's helper-entry sample passes0/3600. Its complete46328-byte
native root equals the formal object's at800000, hash24ce549b; the byte-bridge
receipt preserves that evidence without presenting it as a fresh formal-COFF
or full-matrix helper-x87 run. Its24/25 visited callees leave4359F0 unvisited.
The final auditor also retains the predecessor's22/3600 retirement differences
as a negative control. World/setup/wave/event/CRT continuations, arbitrary
aliases/resources/vtables, nonnull rendering and unmasked exceptions remain
outside this finite-prefix contract. Physical TOP/flags are not compared by
the retirement diagnostic; native returns retain their existing balance/ABI checks.

See [local-exit evidence and commands](REIMU_OBJECT_LOCAL_EXITS_2026_10_21.md)
and [the evidence index](REIMU_OBJECT_EVIDENCE.md). Current receipts and frozen
baseline/control/selected inputs are in `build/reimu-object-cleanup-20261021/`,
with corresponding private recipes under `.analysis/`. Five bulk reports are
verified and gzip-compressed, saving1142239 bytes; sources, COFFs, current
summaries and native receipts stay loose.

The predecessor CPP555da070/canonical88bd9c9b, its typed-store133192 receipt,
helper-visibility controls and split-retirement controls are historical with
their own pins. They do not establish a universal compiler or LTCG barrier.
The local-exit recovery improves observed lifetime/entry structure while
leaving the complete root's canonical exact objective unfinished.

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
