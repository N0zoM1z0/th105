# TH10.5 reconstruction handoff

Current as of 2026-10-21. Phase: active ReimuObject496540 exact reconstruction.
817 sequence3 now captures its turn destination before RNG and reloads the
parameter pointer after the second RNG. A320-input native read/call/store
observer rejects the predecessor despite equal outputs/writes and passes
the selected body. Root remains nonexact49655F/+31, with RET-distance27 and
call-distance9.821's separate owner guards, descending modes and12 packet
slots remain.905 placement,906/817 sharing and908 post-wave load form stay open.
Latest accepted function remains CDesignNumber40BB00 at61/61. Live evidence
overrides historical prose.

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

## Current817 turn lifetime

The selected ordinary compound-assignment RNG expression recovers49910D's
parameter340 capture before RNG499118, the write through that old pointer and
499153's reload after RNG499139. No helper shim/hint or forced register is used.

| Selected artifact | SHA256 |
| --- | --- |
|CPP|`5210f5ab1662283e0b6f2ca5654cdb1fae5c07d2cfb4debb0609eeb064a35131`|
|Unchanged header|`6f469e6886959fd41ee6976b3c784c3df0c2e753ad4729a536764a3c8cd28b4b`|
|Tested formal COFF|`ab2088e8120fc786691e036e637668fc4191ec658b615ae86071b295b85af754`|
|Whole46160-byte canonical source|`f22ad394497f0f8731652c9cd1e2bf052763ed9d06b0a60877d3d64aeddd16ff`|
|Fixed46138-byte compared prefix|`33223535f5a455a67d6374e0e9ccbfcac1076606fb6343e071a82ac3641ba14f`|

New320 actual817 sequence3 paths execute both real RNG calls and RET, with
zero output/ordered-write/read-lifetime differences; old c79f3975 fails320
read lifetimes despite equal outputs. Fresh3600 stride37 retirement inputs
and12 scoped905/907/908 selector prefixes/conditional graphs pass. The root
retains438h frame,45292+868 bytes,10449 decoded instructions,426 calls/71 RETs
and nonexact+31;4963A0 remains66/66. No new exact or aggregate replay is claimed.

40/43 source-to-source instruction graphs remain identical;851/908 changes
are constant-register allocation. Complete root-owned static byte closures differ
only for817/851/908; entry49 bytes and metadata are identical.821/866 retain
the exact code closures behind their prior6720/256 receipts, with no new run.
RTM and predicate controls are unselected and do not prove a universal barrier.
See [817 pointer lifetime](REIMU_OBJECT_817_TURN_LIFETIME_2026_10_21.md) and
`build/reimu-object-817-tail-20261021/` for all current pins, scope and receipts.
29 unselected files are compressed2309585->303850 bytes after SHA256 readback.

## Preceding821 checkpoint: frozen c79f3975 source

The following source/object pins and execution receipts describe the frozen
predecessor, not fresh runs of the new817 source. Its821/866 code closures are
bridged above. Other historical full/input scopes are not reissued.

`ReimuObject_dispatch_action_state_vslot28 @496540` remains source-present in
`src/characters/ReimuObjectActionStateStaging.cpp`, unit
`gpt-web-reimu-object-action-state`. Vtable6C40A4/cell6C40CC slot28, ECX/RET0
and caller4937D0 ignoring EAX are observed. The void return remains inferred.
The provisional39853-byte main candidate and full46138-byte owned comparison
through4A197A are unchanged:46128 owned bytes plus10 alignment bytes. Raw target
closure still has10670 instructions,22 switches and68 RETs.

821's three existing owner action/frame/sequence conditions are now separate
ordinary guards. Target499C8D and499CA7 retire at4980E4/RET4980F7, shared with
812/822; the final signed-word comparison retires locally at499CB2/RET499CC5.
The compiler naturally recovers that first-two sharing. All three20-byte
write-through-RET tails agree; decrement precedes the x87 pop. Reads, tests,
short-circuit order and real return/decrement behavior remain. No assembly,
extra operation, type/ABI/header/profile/binding or ownership change.

| Selected artifact | SHA256 |
| --- | --- |
|CPP|`c79f39751d0a830a4bcb031c6018246ded12cdc1336a65512f73925c64660b5d`|
|Unchanged header|`6f469e6886959fd41ee6976b3c784c3df0c2e753ad4729a536764a3c8cd28b4b`|
|Formal COFF|`d336497b21863f18cce457aa292c8e4f5778b71d86253ff813a4edaf7a22cb30`|
|Whole46160-byte canonical source section|`f903cc3239079239e0c0fff3b6a55f7713966e47053276d0c2cb38d4814346ce`|
|Fixed46138-byte compared prefix|`b8c885e697245515081bd657fcbee04fd8b9d589f4e085700ff6acdf0defdc0e`|

The root remains **nonexact49655F/+31**, a jump displacement, with frame438h.
Source prefix45292 plus868 metadata bytes has10449 decoded/10448 reachable
instructions,426 calls and71 RETs versus target433 calls/68 RETs. RET-membership
distance29->27 reflects only812/822 becoming812/821/822. Call-distance9 and
owner identity2/43 are diagnostics, not exact/partial-byte credit. Twenty-two
extra source payload bytes are not near-exact evidence. Same-TU4963A0 stays
**66/66 exact**, canonicalad12b782. No new match or remote exact flag.

905's live packets/shared second-spawn/wave and descending905..908 cases
remain; all12 first-packet slots for906..908 stay matched, while905 differs.
906 still shares three final-World/wave pairs and817 shares advance with860/861.
Earlier local retirements, ordered stores and902 typed publications remain.

Full source-to-source instruction/edge diagnostics leave28/43 physical owners
identical. Other observed changes include loop alignment,901's jump over
padding,902/907 branch widths and default NOP removal. A second graph
check aligns identical instructions within each owner and checks all edges and
tables. Excluding recorded NOP forms,38/43 owners agree;821/901/902/907/908
differ. These are not relaxed canonical acceptance rules.

908's post-wave field374+word366 addition changes from the target/predecessor's
FLD-before-FILD/FADDP form to FILD/FADD-memory. The arithmetic still uses the
same fields, but that load/x87 form remains unresolved and its opaque
continuation is unexecuted. A real used heading snapshot is byte-neutral
and unselected. Do not claim that finite prefix replay certifies this window.

New `audit-reimu-object-821-owner-exits.py` passes6720 actual821 sequence3/4
inputs/hash71ff360c with zero output/write/retirement differences, correct
physical guard/RET sharing and equal20-byte tails. Signed limits, NaN/Inf and
two control words are included. Heading bits are checked at entry; the common
fixture accepts this optional input and retains default37.25. The predecessor
has zero numerical differences but is rejected for merging all three tails.
CPU0/nice10 run:16.78s wall, peak RSS139136KiB.

All256 existing owner-follow inputs/hashd8fe09ab pass;3600 whole-root and3600
helper-entry samples/hashe90a5943 pass.4359F0 remains unvisited. These samples
do not cover all typed stores;902 spill/reload and822 heading-pair static
checks remain, with zero post-opaque822 executions. Scoped905/907/908 passes12
first prefixes and conditional call graphs; default still rejects906. The
World report remains rejected99/96, while540 actual903/180 retiring prefixes,
903 conditional graphs and the shared18-byte post-call tail agree. Sixteen
actual packet prefixes preserve the12 matched906..908 offsets. No opaque
World/driver/CRT returns are fabricated; logical x87 excludes TOP/flags.

The older26342/133192 receipts belong to preceding source epochs and are not
reissued or bridged to this changed body. Complete46160-byte native equality
bridges the guard control to the tested formal COFF and final metadata-only
rebuild, preserving only the new scoped receipts. No all-unit replay or
aggregate exact percentage is claimed.

Private descending905 case-local double-spawn/wave control still has six
extra sites. A private float-packet API with actual unparented/parented bodies
is whole-root neutral against baseline7c16e018 and compares78/77 bytes exact;
the original pointee type is not unique from those bytes. No shared declaration
or ledger binding changes. Earlier source-shape controls remain phase-scoped;
none establishes a universal source/profile or LTCG barrier.

See [821 owner exits](REIMU_OBJECT_821_OWNER_EXITS_2026_10_21.md),
[preceding selector order](REIMU_OBJECT_SELECTOR_ORDER_2026_10_21.md) and
[the evidence index](REIMU_OBJECT_EVIDENCE.md). Receipts/frozen inputs are in
`build/reimu-object-905-lifetimes-20261021/`, with recipes under `.analysis/`.
26 completed unselected files are compressed2029617->262971 bytes after SHA256
readback; an initial ignored-heading receipt is explicitly invalidated in the
manifest. Baseline/selected/guard-control inputs stay loose; primary DBs,
canonical target and tools remain. Full canonical equality, original source/TU,
arbitrary aliases/resources/vtables and unmasked exceptions stay open.

## Bounded dependency follow-up; no new source selection

The next bounded batch keeps all selected program sources/headers/flags and
match rows unchanged. Komachi5F9350's full61-instruction205-byte target is
reclosed; it remains203-byte nonexact at+21. Raw owner7A8 signed clamp/decrement,
set10 and accepted reset accesses support its countdown view. Ten private
receiver/type/context/compiler controls keep all seven accepted effects siblings
exact; eight reproduce the whole203-byte baseline, two still fetch the first
manager too early. RTM/SP1 produce the same complete121-byte sine fixture,
nonexact+51h; the46-byte abs witness remains unclassified/diagnostic.

Two Reimu908 wide/reversed-addition controls are whole-body neutral against
selectedf903cc32. A consumed postcounter still has the wrong load form and
splits the common word update, so it is unselected. No new opaque-return
execution, numerical regression, authored exact credit or aggregate replay is
claimed. These scoped negatives do not prove a compiler or LTCG barrier.
See [Object helper follow-up](OBJECT_HELPER_CONTROLS_2026_10_21.md) for raw
addresses, canonical hashes, limits and retained input/report paths. Reimu's
current821/selector source phase and all preceding scoped receipts remain.

## CDesignNumber lifetime follow-up

RTTI vtable6D6AC0/COL6DCAB0 and factory40B7ED establish the completeE4 owner,
actual CNumber member+18 and CTile+40. The ordinary implicit outer destructor
in `src/ui/CNumberLifetime.cpp` now reproduces40BB00 **61/61**: member-owned
value release at+3C, tile/member/outer base cleanup and optional receiver free.
Canonical57f8ee28, source04da04d2, formal COFFc16db61d. The six-function sole
affected unit `gpt-web-cnumber-lifetime` is fully exact; no shared header,
profile, existing binding or accepted partition changes. One new physical
61-byte lifetime is accepted; no aggregate cold replay is claimed.

Raw rendering leads40AF80/40AFC0 call private414EB0 with their number pointer
in EAX; its floating continuation415050 receives that pointer in ESI. Those
bodies remain unselected. See [CDesignNumber lifetime](DESIGN_NUMBER_LIFETIME_2026_10_21.md)
for complete boundaries, target ownership, focused receipts and remaining
source/ABI unknowns. Reimu's821 guards and selector order remain unchanged.

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
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-817-turn-lifetime.py build/match-units/GptWeb_ReimuObjectActionState.obj --output build/reimu-object-817-turn-replay.json
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
