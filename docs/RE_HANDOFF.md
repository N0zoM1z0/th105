# TH10.5 reconstruction handoff

> Current workflow: follow the **Highest priority** section in `AGENTS.md`.
> Prefer affected exact comparisons and useful Markdown knowledge. Ordinary
> notes do not require full CI, native replay or document-hash/pin refreshes.
> Older broad validation instructions apply only when their impact is relevant.


2026-11-03: System-effect pool acquire `0x456B70` (499 bytes) now has natural typed source and an individual mapping. Exact tracked acquisition replays; source498 and cleanup EH remain nonexact/unproved. See `docs/SYSTEM_EFFECT_POOL_SOURCE_2026_11_03.md`.

2026-11-03: System-effect tracked release `0x436E60` (119 bytes) now has typed source and an individual mapping. Exact manager lifetime roots replay; source119 remains nonexact. See `docs/SYSTEM_EFFECT_RELEASE_SOURCE_2026_11_03.md`.

2026-11-03: Connect endpoint-history selection `0x443030` (157 bytes) is now individually mapped/source-present. Its exact action caller and sibling replay; source153 remains nonexact. See `docs/CONNECT_HISTORY_SOURCE_2026_11_03.md`.

2026-11-03: Vector length-error helper `0x40AAF0` (123 bytes) is compiler-generated, proved through real BGM CIL, native vector callers, full nonreturning throw/EH metadata and unique whole-body identity. No authored credit. See `docs/VECTOR_XLEN_ORIGIN_2026_11_03.md`.

2026-11-03: Exact source pins now have matching Git checkout line endings, and the changed BGM source pin was fully re-attested. Four affected origin rules pass; no counting change. See `docs/ORIGIN_SOURCE_EOL_2026_11_03.md`.

2026-11-03: Fighter outcome selector `0x45E120` (620 bytes) is now individually mapped/source-present. Two exact battle callers replay; source610 remains nonexact. See `docs/OUTCOME_SELECTOR_SOURCE_2026_11_03.md`.

2026-11-03: Battle outcome path B `0x46D610` (542 bytes) is now individually mapped/source-present. Exact sibling and dispatcher replay; source530 remains nonexact. See `docs/OUTCOME_B_SOURCE_2026_11_03.md`.

2026-11-03: Forwarded hit quantity `0x46C5B0` (301 bytes) now uses the actual typed BattleManager virtual callback and is individually mapped/source-present. Source299 remains nonexact; exact forwarding caller replays. See `docs/FORWARDED_HIT_SOURCE_2026_11_03.md`.

2026-11-03: Combo resource load `0x46A8C0` (413 bytes) is now individually mapped/source-present; exact InfoManager initialization replays. Source427 remains nonexact. See `docs/INFO_COMBO_SOURCE_2026_11_03.md`.

2026-11-03: Scenario label selection `0x455490` (276 bytes) is now individually mapped/source-present. The exact owned-string caller replays; source275 and cleanup EH remain nonexact/unproved. See `docs/SCENARIO_LABEL_SOURCE_2026_11_03.md`.

2026-11-03: Practice battle policy `0x428260` (553 callable bytes plus separate switch table) is now individually mapped/source-present; exact presentation caller replays. Source remains nonexact. See `docs/PRACTICE_POLICY_SOURCE_2026_11_03.md`.

2026-11-03: Story battle-info update `0x471930` (323 bytes) is now individually mapped/source-present. Existing exact InfoManager caller replays; source321 remains nonexact. See `docs/STORY_INFO_SOURCE_2026_11_03.md`.

2026-11-03: BGM master gain `0x403A30` (284 bytes) has complete source; original play/prepare/PCM roots remain exact. Its 357-byte CIL has an unaccounted unreachable gap, so comparison remains blocked and nonexact. See `docs/BGM_MASTER_GAIN_SOURCE_2026_11_03.md`.

2026-11-03: Existing BGM stream transition `0x402B70` (153 bytes) is now individually mapped and source-present; two exact caller roots replay. Real CIL emits 142 bytes and remains nonexact. See `docs/BGM_TRANSITION_SOURCE_2026_11_03.md`.

2026-11-03: Wave master gain `0x401C20` (192 bytes) now has complete source using both observed 32-slot arrays. Unforced CIL emits 242 bytes and remains nonexact; no exact credit. See `docs/WAVE_MASTER_GAIN_SOURCE_2026_11_03.md`.

2026-11-03: Wave per-handle gain `0x401CE0` (109 bytes) now has complete target-backed source. Actual unforced CIL emits 101 bytes and remains nonexact; exact config caller is unchanged. See `docs/WAVE_HANDLE_GAIN_SOURCE_2026_11_03.md`.

2026-11-03: Wave-service pointer deque back `0x4052B0` (91 bytes) is compiler-generated, verified by full body, real wave/acquire call graphs and unique inventory identity. The parents remain nonexact; no authored credit. See `docs/WAVE_POINTER_DEQUE_BACK_ORIGIN_2026_11_03.md`.

2026-11-03: Real CSV CIL deque<string> copy chains validate two physical compiler-generated helpers at `0x410ED0` (112 bytes) and `0x411040` (188 bytes). Const/nonconst source witnesses map to the same two native bodies; the forward child was already excluded. Parents remain unaccepted. No authored exact-byte credit; see `docs/CSV_DEQUE_COPY_ORIGINS_2026_11_03.md`.

Packet deque back 0x4179D0/82 is compiler-generated: whole body, real
source/native acquire call edges, three runtime calls and inventory uniqueness
pass; the acquire parent remains nonexact. Review291 / excluded2080; no authored
or exact credit. See PACKET_DEQUE_BACK_ORIGIN_2026_11_03.md.

Unsigned list growth 0x402700/165 is compiler-generated: actual BGM lifetime
CIL emission plus a separately exact native handle-manager caller, complete
root/EH/exception proof and inventory uniqueness. Source release itself is not
claimed exact. Review292 / excluded2079; no authored or exact credit. See
UNSIGNED_LIST_GROWTH_ORIGIN_2026_11_03.md.

The 154-byte 0x40C6D0 list growth helper is compiler-generated, proved from the
real exact BGM owner and complete body, EH and exception metadata. Review293 /
excluded2078; no authored or exact credit. See BGM_LIST_GROWTH_ORIGIN_2026_11_03.md.

The complete 102-byte 0x413E10 deque teardown is now independently classified
compiler-generated from a fresh exact resource-manager CIL owner, full unmasked
canonical body and inventory uniqueness. Review294 / excluded2077; no authored
or exact credit. See RESOURCE_DEQUE_TIDY_ORIGIN_2026_11_03.md.

Scene update, byte/float interpolation and easing now share the same actual
0x94-byte update receiver instead of separate method-only views. The exact update
801, float160 and easing131 roots remain exact across the complete three-unit
include closure; byte214/native211 remains unchanged and nonexact. No counts or
ABI/layout changes. See SCENE_SHARED_INTERPOLATION_RECEIVER_2026_11_03.md.

## Resumed after maintenance — November 3, 2026

The user requested documentation and storage cleanup, then paused the work.
They explicitly resumed the TH105 goal on November 3. The registered repository
connection, clean worktree, target hash and ledgers were verified before resuming.
The cleanup changed no game source, ABI, compiler profile or exactness claim.

The prior reconstruction checkpoint is `d55dfbaa` (system-effect release source;
no new authored exact match). Work was committed locally; no push was
performed by this session. Inspect live Git status before making further changes.

The preceding 3,147-line handoff is preserved verbatim in
[the November 3 archive](RE_HANDOFF_HISTORY_2026_11_03.md). Its dated narrative
and embedded older “current” totals are historical, not current instructions.
Earlier archives remain linked there and in [ARTIFACTS.md](ARTIFACTS.md).

## Current accepted state

Verified from the live ledgers at this checkpoint:

| Measure | Value |
| --- | ---: |
| Provisional candidates | 4027 |
| Authored / excluded / review | 1670 / 2084 / 273 |
| Mapped / source-present | 1841 / 1651 |
| Exact authored functions / bytes | 1426 / 443399 |
| Configured units / function entries | 822 / 1994 |
| Distinct units represented in matches.csv | 612 |

These are incremental totals, not a fresh whole-corpus replay. `implemented.csv`
means selected source exists; only `matches.csv` records whole-body canonical
exactness. Compiler/runtime/library helpers, aliases and data are not extra
authored credit. Some unselected sources also exist; absence from implemented.csv
alone does not mean there is no source. Use the live status report after changes.

Recent evidence:
- [CSprite texture options](SPRITE_TEXTURE_OPTIONS_SOURCE_2026_11_02.md): complete
  334-byte source, first mismatch +149. Six finite modeled-query observations
  and negative controls pass; no universal equivalence or exact credit.
- [Shared design owners](DESIGN_SHARED_OWNERS_2026_11_02.md): four real classes,
  four RTTI graphs and 28 slots; 17 accepted roots preserved. Alias/support body
  checks do not create new authored roots.
- [Implicit profile cleanup](PROFILE_IMPLICIT_CLEANUP_2026_11_02.md): the former
  205-byte authored destructor was correctly reclassified as compiler-generated.
  Historical larger authored totals must not be restored.

## Last private experiment — retained, not accepted

`.analysis/frontier-design-real-context-20261102/probe.py` builds a real source
provider combination for CDesignBase::load. Its output directory is
`build/frontier-design-real-context-20261102/`. The driver reports successful
compilation/linking, but whole-function comparison fails:
`linked body does not close through a complete RET boundary`.

The linked map places the root at 0x100038C0 and the next symbol at 0x10004370.
A RET4 ends the observed callable portion at 0x10004354; 28 trailing bytes are
candidate switch metadata. This is an observed 2736-byte symbol span, not an
accepted boundary or relocation proof. Source has an aligned EBP frame of
0x3F8 versus native 0x3E8, plus different register/liveness choices. Successful
linking and a similar prologue are not byte equality. EH, full switch ownership
and full relocations remain unverified; parsing is not the only known difference.

The private combination removes duplicate provider inclusions once and reuses a
direct renderer source body for the missing CGage virtual provider. Native
CGage slot 0x6D6A58 and CSprite slot 0x6C0684 both point to physical 0x406BE0.
That supports shared behavior, not unique original source spelling/TU ownership.
No wrapper, code-address binding, forced ABI or extra exact root was accepted.
Public loader source remains independently EH-blocked and nonexact.

A paired raw-PE/linked-image switch audit now validates both dense seven-entry
switches and all destination instruction boundaries. Native 0x40B000 has 2666
callable bytes, all 860 instructions reachable, followed by 8B FF alignment
and its separate table at 0x40BA6C. CIL has 2708 callable bytes, 856 reachable
instructions, one three-byte alignment gap and a separate 28-byte table. Both
have no unresolved indirect jump or internal call. A provenance-checked private
recipe is `.analysis/frontier-design-real-context-20261102/audit-switch.py`;
its receipt is `build/frontier-design-real-context-20261102/paired-switch-audit.json`.
It does not validate complete relocation/EH equality or confer any exact credit.
The natural CIL gauge initializer uses mode EAX but receives the object on stack
and RET16 (330 callable bytes); native uses ESI and RET12 (360 bytes). Do not
force an ABI or reopen the old spelling/flag grid to close that difference.

The related private title-acquire provider context and sprite-options experiment
are retained in the verified recovery bundle described in [ARTIFACTS.md](ARTIFACTS.md).
The earlier inspection was interrupted; the paired audit above was run after
the user resumed the goal. Do not reopen closed UV, x87, scratch-frame or source-spelling
lanes without independent new evidence. Consult the dated records and archive
before repeating any experiment.

## Bounded reconstruction workflow

1. Read AGENTS.md, this handoff, the relevant source and its evidence note.
2. Inspect status; preserve other sessions' changes and all six older worktrees.
3. Use scripts/repo-python. Keep reconstruction/matching in one bounded writable
   scope; do not delegate it or run concurrent VC8/Ghidra jobs. Use CPU0/nice10.
4. Make only target-backed naming/layout/source changes. Source presence and
   semantic observations do not imply exactness. No assembly, copied machine
   bytes, inert locals, artificial ABI/register recipes or parameter grids.
5. Replay directly affected accepted consumers after shared changes. Preserve
   unaffected receipts. No routine cold verify-exact-units --all run.

Before reconstruction or ledger changes:

```bash
git status --short
taskset -c 0 nice -n 10 scripts/repo-python scripts/verify-target.py
taskset -c 0 nice -n 10 scripts/repo-python scripts/report-reconstruction-status.py --summary
taskset -c 0 nice -n 10 scripts/repo-python scripts/validate-tracking.py --require-target
```

Only original Japanese TH105 v1.06a is valid: SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`,
size3129344, image base0x400000, entry0x68B9D2. Raw PE evidence remains available.
Factory-native IDA requires a fresh full target/five-sample/capability attestation
before using its semantics; old connectivity reports are not current proof.
The legacy check-ida-mcp.py is for the legacy bridge. Ghidra requires independent
import/entry/mapped-byte checks. Never patch the target.

Preserve the pinned Python environment, VC8 SP1 tools, target, analysis databases,
source recipes, frozen controls and accepted receipts. See README for dependency
pins and [ARTIFACTS.md](ARTIFACTS.md) for cleanup/recovery details.

Before a local commit, run the finished gate and both whitespace checks:

```bash
PYTHONDONTWRITEBYTECODE=1 taskset -c 0 nice -n 10 scripts/repo-python scripts/ci.py
git diff --check
git diff --cached --check
```

Default CI validates tooling and ledgers, not all native matches. Checkpoint
the system-effect pool checkpoint passed 1002 tests in 102.232 seconds; the gate
is recorded in `build/frontier-system-effect-pool-source-20261103/ci-final.log`. Commit prefix: `gpt-dots:`. Keep target
binaries, game data, tool installations, databases and credentials out of Git.

### 2026-11-03: broaden origin source EOL protection

The origin-source checkout test now covers `source_pins`, `source_sha256`, and `[[sources]]` anchor formats. Thirteen additional pinned source paths have explicit LF checkout attributes. Corrected two conflicting `InputManager.hpp` hashes to the actual LF bytes and replayed both affected native proofs successfully; see `docs/ORIGIN_SOURCE_EOL_2026_11_03.md`. No authored or exact-byte credit changed.

### 2026-11-03: use the real sprite rotation provider

`SystemEffectObjectBase::render_effect` at `0x00473CF0` now calls the existing `CSpriteEx::rotate_xyz` implementation at `0x00407680`, rather than a declared but undefined alias mapped to the same target. The six-float thiscall signature and target are unchanged. Fresh canonical comparisons for all five functions in `cross-v106a-system-effect-object` are exact, including render 222/222; receipt `build/frontier-system-effect-real-rotation-20261103/compare.json`. This removes one link obstacle but does not establish a complete integrated link or add exact-byte credit.

### 2026-11-03: real linked system-effect pool context

The rectangle renderer's line call now uses the existing `LinePrimitiveView::draw_line` provider at `0x00401180` rather than an undefined alias. Its two declarations have the same observed prefix and signature. The isolated `0x004012A0` comparison remains nonexact, with identical before/after canonical object hash and first mismatch; receipt `build/frontier-real-line-provider-20261103/`.

A private linked image assembled the actual system-effect pool and caller together with existing real providers and linked successfully. With the existing target-backed call identities, `0x00457110` is 97 bytes in this LTCG context versus 91 target bytes, mismatching at offset zero. Receipt `build/frontier-system-effect-pool-cil-20261103/providers4.log`. This does not supersede the separate non-LTCG exact 91/91 unit, establish the pool as exact, or add exact-byte credit. The pool provider's native body remains nonexact; do not infer callee byte equivalence from the linked caller mapping.

### 2026-11-03: connect info-effect provider

The normal and Story InfoManager effect wrappers now call the shared real `BattleInfoRecordEffectRuntimeView::emit_group_effect_46f9f0` declaration and implementation, rather than an undefined alias mapped to the same target. The common header preserves the existing target-backed layout. Fresh comparisons of both affected units remain exact for all five roots: `0x46EF40` 214, `0x46F820` 35, `0x471EC0` 78, `0x471F10` 215 and `0x472060` 31 bytes. The provider itself remains nonexact at 66/native85 with the same canonical object hash as its prior receipt. See `build/frontier-info-effect-real-provider-20261103/`. No new exact credit is claimed.

### 2026-11-03: restore ordinary-COFF review discovery

`rank-existing-object-review-symbols.py` now explicitly excludes named `.ltcg.obj` VC8 intermediates, which GNU `nm` cannot parse, and reports their count. It still fails on unexpected `nm` errors rather than silently discarding ordinary objects. A fresh scan covered 854 ordinary objects and excluded 42 LTCG intermediates. Three same-size rows all refer to the previously rejected package allocator `0x41D160`; the source-specific prior proof found a different native fingerprint, so no origin or exact credit is added. Discovery output is `build/frontier-review-discovery-20261103/rank.json` and remains provisional.

### 2026-11-03: register spell sequence preparation source

`Fighter::prepare_next_spell_sequence_entry` at `0x45DC90` is now classified authored and source-present using the complete 259-byte native body and two direct edges from the freshly exact 482-byte practice-control caller. Existing typed source emits257 bytes and remains nonexact; cleanup EH is not claimed exact. See `docs/SEQUENCE_PREPARATION_2026_10_28.md`. Canonical exact count and bytes remain unchanged.

### 2026-11-03: scripted fighter-input origin

The complete 753-byte `0x463E40` fighter input/state policy is classified authored from its pinned body and four call edges in two freshly exact round-init/pre-reset callers. Its sole indirect virtual tail remains outside this ownership proof. A later checkpoint below selects a retained typed candidate; neither that source nor the earlier 751-byte candidate is exact. See `docs/FIGHTER_SCRIPTED_INPUT_ORIGIN_2026_11_03.md`.

### 2026-11-03: scenario-event parser origin

The native `0x45A7A0` scenario CSV/event parser is classified authored from its pinned 543-byte span and fresh exact story/setup caller edges. The span includes two internal alignment bytes. The later source-selection checkpoint below resolves the initial EH address blocker and records the remaining nonexact comparison. See `docs/SCENARIO_EVENT_PARSER_ORIGIN_2026_11_03.md`.

### 2026-11-03: network replay-dispatch origin

The 566-byte network ACK/replay dispatch entry `0x44E460` is classified authored from its complete target body and freshly exact client/server caller edges. A later source-selection checkpoint below records the natural candidate; it remains nonexact and no EH or exact-byte credit is claimed. See `docs/NETWORK_SECONDARY_REPLAY_ORIGIN_2026_11_03.md`.

### 2026-11-03: battle information-record runtime origin

The complete 2,005-byte `0x46FF30` gauge/effect runtime is classified authored using its pinned native body and fresh exact normal/Story update caller edges. Existing private candidates remain nonexact and unselected; no source-present or exact-byte credit is claimed. See `docs/BATTLE_INFO_RUNTIME_ORIGIN_2026_11_03.md`.

### 2026-11-03: select scenario parser source

The earlier parser EH relocation blocker is resolved to its native handler address, without claiming EH equivalence. `exact-first-scenario-event-parser` now compares the complete candidate: source 518 versus target 543, first mismatch at frame size. The source is registered present, not exact. See `docs/SCENARIO_EVENT_PARSER_ORIGIN_2026_11_03.md`.

### 2026-11-03: scenario parser local lifetime

The selected parser now reuses the actual selected-value local for the following source-list value, as established in the prior analysis. This naturally restores the native `/GS` frame size `0x34`; the full candidate remains 518/native543, with first mismatch at `+0x33` and no exact/EH claim. See `docs/SCENARIO_EVENT_PARSER_ORIGIN_2026_11_03.md`.

### 2026-11-03: scenario parser native read order

The parser now checks the selected column before the CSV read, and retains distinct row count/remaining lifetimes as the native control flow does. The first 403 bytes match, but the complete source is 545/native543 bytes and still nonexact at source-list node/value scheduling. The natural nested-read control reintroduces the wrong frame and was rejected. No full-body or EH credit. See `docs/SCENARIO_EVENT_PARSER_ORIGIN_2026_11_03.md`.

### 2026-11-03: scenario parser iterators

The parser now materializes its genuine begin/end iterators for list assignment. Its generated function is 543/native543 bytes with the same 403-byte exact prefix, but two scheduling/register-allocation regions still differ. No whole-function or EH credit; see `docs/SCENARIO_EVENT_PARSER_ORIGIN_2026_11_03.md`.

### 2026-11-03: connect phase render provider

The Fighter phase render callback now uses the shared real `FighterPhaseRenderState` type and implementation instead of a declaration-only alias. Fresh canonical comparisons preserve all five phase roots and all six render-state roots, including `0x464A80` 71/71 and `0x45AA00` 333/333. The existing six-entry compiler-generated phase-render-list origin rule was rebuilt and replayed successfully. Receipts: `build/frontier-phase-real-render-provider-20261103/`. No new exact credit is claimed.

### 2026-11-03: connect embedded phase provider

The Fighter phase-finalize callback now uses the shared real `FighterEmbeddedState3d0Runtime` type and implementation instead of a declaration-only alias. Fresh canonical comparisons preserve all five phase roots and both embedded-state roots, including `0x464AD0` 71/71 and `0x4653F0` 45/45. Receipts: `build/frontier-phase-real-embedded-provider-20261103/`. No new exact credit is claimed.

### 2026-11-03: select scripted input source

The retained typed Fighter scripted-input policy at `0x463E40` is now selected with the real signed-short history deque, existing selector global and mapped helpers. Its initial whole-body comparison was 760/native753; the later control-flow checkpoint below improves this but remains nonexact. The original view-method aliases have since been replaced by real providers, but a complete link is not established. No exact bytes are added. See `docs/FIGHTER_SCRIPTED_INPUT_ORIGIN_2026_11_03.md`.

### 2026-11-03: connect scripted input helpers

The Fighter scripted-input body calls the actual input sampler and CPU selector implementations through their shared typed views. Fresh native comparisons preserve the 480/480 and 171/171 helper matches, while the parent initially remained 760/native753 with identical nonexact canonical object hash; the later checkpoint below improves the parent. No complete-link or new exact-byte claim. Receipts: `build/frontier-scripted-input-real-providers-20261103/`.

### 2026-11-03: scripted-input native control flow

The selected `0x463E40` source now uses the native direct random-threshold returns and publishes the snapshot timer in target order. Whole-body output is 753/native753 with only two differing bytes (`+0x22/+0x2F`), both from ECX versus EDX for the horizontal input multiplication. Reversing multiplication operands was byte-neutral; no register coercion or exact credit. See `docs/FIGHTER_SCRIPTED_INPUT_ORIGIN_2026_11_03.md`.

### 2026-11-03: connect CPU boundary provider

The Fighter CPU-input selector now calls the actual `Fighter::classify_fighter_x_boundary` implementation instead of a declaration-only alias. Fresh comparisons preserve the 171-byte CPU selector, four stage-geometry roots (including the 59-byte boundary classifier), and the scripted-input parent's unchanged 753/native753 nonexact two-byte residue. No complete-link or new exact credit is claimed. Receipts: `build/frontier-fighter-cpu-real-boundary-20261103/`.

### 2026-11-03: select network replay source

A typed ACK/replay request dispatcher is selected at `0x44E460`, with both native branches, real deque/packet lifetimes and target-address evidence for EH and vtables. Full canonical comparison is 566/native566 but 177 bytes differ, first at `+0x49` due to control-flow displacement. EH equivalence and an integrated link remain unproved. No exact credit. See `docs/NETWORK_SECONDARY_REPLAY_ORIGIN_2026_11_03.md`.

### 2026-11-03: unify ACK packet hierarchy

The ACK packet serializer/parser, senders and replay dispatcher now share one `NetworkAckInfoPacket40` with the RTTI-proven polymorphic offset-zero base. This corrects the serializer/parser TU's superseded non-polymorphic-base view and match-unit notes. Fresh comparisons preserve both exact serializer/parser roots and both exact senders; the constructor and replay dispatcher retain their identical prior nonexact hashes. See `docs/ACK_PACKET_BASE_2026_10_29.md`. No new exact credit or complete-link claim.

### 2026-11-03: share ACK type with secondary dispatchers

Client `0x44EE80` and Server `0x44FB40` secondary packet dispatchers now use the shared RTTI-backed ACK type and actual parser instead of stale non-polymorphic-base aliases. Fresh body comparisons preserve 582/582 and 532/532. No new exact credit or new cleanup-EH equivalence claim. See `docs/ACK_PACKET_BASE_2026_10_29.md`.

### 2026-11-03: shared replay IPacket base

The native replay RTTI identifies the same offset-zero `IPacket` base as ACK_INFO. Replay serialization, parsing, Client secondary dispatch and replay-request handling now share a single actual replay type with that base. All twelve packet-leaf exact roots, the Client dispatch and ACK exact roots/senders replay; the constructor and replay-request parent remain nonexact. No new exact credit. See `docs/ACK_PACKET_BASE_2026_10_29.md`.

### 2026-11-03: shared replay-request IPacket type

The native request-replay RTTI identifies the same offset-zero `IPacket` base. Its serializer/parser, Client/Server dispatchers and request handler now share the real request type, replacing prior incompatible base and virtual-method views. All twelve packet-leaf roots, three Client secondary roots and the Server dispatcher replay exactly; the request handler remains nonexact with its prior hash. No new exact credit or complete-link/EH claim. See `docs/ACK_PACKET_BASE_2026_10_29.md`.

### 2026-11-03: shared INPUT IPacket type

The native INPUT RTTI identifies the same offset-zero `IPacket` base. Packet-leaf serialization/parsing and Client/Server dispatchers now share the real INPUT type; all twelve packet-leaf roots, both dispatchers and the separate 110-byte replay request pump replay exactly. Corrected two request serializer/parser ledger signatures to the shared class name. The later checkpoint below reconciles the separate input constructor view in the network base; no new exact bytes or new EH claim. See `docs/ACK_PACKET_BASE_2026_10_29.md`.

### 2026-11-03: network-base real INPUT member

The network base now uses the shared RTTI-backed INPUT class through its compatibility typedef. Constructor, destructor, packet cleanup and sprite lifetimes replay exact; complete constructor/destructor remote EH and metadata, plus the two affected source-pinned origin proofs, also pass after renewing reviewed pins and checkout attributes. Receipts: `build/frontier-input-base-real-type-20261103/`. No new exact bytes.

### 2026-11-03: concrete packet vtable second slots

The ACK, replay, replay-request and INPUT concrete types now declare their existing parse methods virtual as required by native two-slot tables. At that checkpoint the common base parse declaration remained unresolved; the later inference below supersedes that source model. `scripts/audit-network-packet-vtables.py` checks four fresh source COFF tables, native slot addresses and offset-zero IPacket RTTI; `test_network_packet_vtables` rejects missing/swapped slots. Existing exact packet/dispatcher/base roots replay; both affected source-pinned origin rules and full network constructor/destructor EH/metadata also pass after the INPUT header pin renewal. No exact-byte gain. See `docs/ACK_PACKET_BASE_2026_10_29.md`.

### 2026-11-03: infer shared packet parse signature

The shared packet base now declares an inferred void parse slot. Removing artificial ACK returns preserves its full 183-byte native body, while both inspected callers ignore the return; all four packet vtables and previously exact affected roots replay, as do both pinned origin rules and full constructor/destructor EH and metadata. The original signature and base abstractness remain unproven, and integrated linking is not claimed. No exact-byte gain. See `docs/ACK_PACKET_BASE_2026_10_29.md`.

### 2026-11-03: remove unrelated packet casts

Both ACK senders and the request pump now use the RTTI-backed shared packet base instead of unrelated reinterpret-cast views. Their exact body comparisons and the four vtable checks pass; the ACK constructor retains its existing mismatch. No exact-byte gain or new EH/link claim. See `docs/ACK_PACKET_BASE_2026_10_29.md`.

### 2026-11-03: exact network replay request dispatch

The ACK/replay dispatcher at `0x44E460` now matches the complete 566-byte native body after correcting the independent tail-field publication order and using the shared packet base. Its complete remote cleanup code (59 bytes) and unwind/function metadata (52 bytes) also replay exactly. The pinned origin is authored; the two exact caller roots remain the ownership anchors. Integrated linking and runtime exception execution are not claimed. See `docs/NETWORK_SECONDARY_REPLAY_ORIGIN_2026_11_03.md`.

### 2026-11-03: exact scripted input policy

The complete Fighter scripted-input policy `0x463E40` now matches 753/753 by expressing its two direction checks directly, with no forced register or fake liveness. Four original caller edges and both exact caller bodies replay; the real input and CPU provider roots remain exact. The indirect virtual tail and integrated link remain unproved. See `docs/FIGHTER_SCRIPTED_INPUT_ORIGIN_2026_11_03.md`.

### 2026-11-03: classify script command advance

The 104-byte `0x405AC0` script cursor advance now has ordinary checked-iterator source; strict comparison remains blocked on the native private helper ABI and adds no exact credit. See `docs/SCRIPT_NEXT_COMMAND_SOURCE_2026_11_04.md`.

### 2026-11-03: classify battle policy bodies

Complete CFGs and exact caller edges established authored ownership of spell selection shuffle `0x432420` (196 bytes) and battle overlay rendering `0x4666A0` (670 bytes). Since that checkpoint, the shuffle source has been selected but remains nonexact, while the overlay is now fully exact. See `docs/ORIGIN_RECOVERY_2026_11_03.md` and `docs/BATTLE_RENDER_TAIL_EXACT_2026_11_04.md`.

### 2026-11-03: exact PNG loader

The linked PNG loader `0x41A910` now compares exactly for its complete 703-byte body by placing the real row-offset initialization before pixel allocation. Complete handler, cleanup funclet, FuncInfo and unwind map also replay exactly; the verified callback and target data bindings remain intact. The target version literal and linked provider version remain distinct; no runtime PNG decode-success claim. See `docs/PNG_LOADER_CONTEXT_2026_10_30.md`.

### 2026-11-03: scenario source-list reference

A real source-list reference in `0x45A7A0` reproduces native iterator preparation and reduces the full 543-byte candidate's differences from 25 to 16; the earlier node-preparation mismatch remains. Both exact callers and the generated-list origin rule replay. No exact-byte or EH claim. See `docs/SCENARIO_EVENT_PARSER_ORIGIN_2026_11_03.md`.

### 2026-11-03: classify network battle updates

Complete server/client battle-update CFGs and RTTI-backed primary virtual slots establish authored ownership at `0x426180` (247 bytes) and `0x426380` (267 bytes). Prior source candidates remain unselected and nonexact; no exact-byte gain. See `docs/BATTLE_NETWORK_UPDATE_2026_10_28.md`.

### 2026-11-03: classify replay and round policy

Replay-header read `0x429A30` is now 313/313 exact with complete EH replay; see `docs/REPLAY_HEADER_READ_EXACT_2026_11_04.md`. Battle-round reset `0x471180` is source-present but nonexact; see `docs/CONTINUE_ROUND_RESET_SOURCE_2026_11_04.md`.

### 2026-11-03: PNG provider version correction

The native PNG create-read path compares against its getter returning `1.5.2`. The previous `1.2.5` marker was actually passed to zlib initialization and does not prove native libpng version. The pinned 1.2.5 comparison provider rejects the original 1.5.2 argument in a bounded runtime probe, so it is not a runnable-equivalent PNG provider. The 703-byte game-function match remains a code/relocation result, not runtime equivalence. See `docs/PNG_PROVIDER_VERSION_2026_11_03.md`.

### 2026-11-03: update linked PNG provider

The linked context now uses official, source-locked libpng 1.5.2 and existing zlib 1.2.3. A reproducible Wine smoke test accepts the native version argument, checks the reconstructed info-prefix offsets and decodes a synthetic 1x1 PNG. All 14 accepted CSV/bitmap linked roots and both replay-codec roots remain exact; the affected CSV deque-copy origin rule replays. This removes the observed version rejection but does not establish full target-library or game-runtime equivalence. See `docs/PNG_PROVIDER_VERSION_2026_11_03.md`.

### 2026-11-03: native PNG source fingerprint

Official libpng 1.5.2 `png_sig_cmp` compiled with pinned VC8 `/O2 /GS` reproduces all 298 native bytes at `0x66B870`; the same 1.2.5 control is 297 bytes and nonexact. This strengthens, but does not prove, the native library release identification. The provider audit reproduces the exact comparison and smoke test. No authored bytes added. See `docs/PNG_PROVIDER_VERSION_2026_11_03.md`.

### 2026-11-03: verify PNG provider interfaces

Pinned libpng 1.5.2 source also reproduces the full native IO getter 13/13, create-read wrapper 35/35 and BGR setter 13/13. The provider audit now replays these alongside the 298-byte signature check and synthetic decode. These third-party bodies add no authored bytes and do not establish whole-library equivalence. See `docs/PNG_PROVIDER_VERSION_2026_11_03.md`.

### 2026-11-03: recover PNG zlib header context

The PNG provider now uses locked official zlib 1.2.5 headers while retaining the zlib 1.2.3 implementation, matching the observed original header-version argument. The real 1x1 decode passes; all 14 CSV/bitmap linked roots, two replay-codec roots and the affected origin proof replay. Pinned libpng 1.5.2 source also reproduces the full 756-byte native create-read body and 28-byte switch table with explicit relocation-role bindings. No whole-library equivalence or authored-byte gain is claimed. See `docs/PNG_PROVIDER_VERSION_2026_11_03.md`.

### 2026-11-03: verify zlib initialization

Pinned zlib 1.2.3 source reproduces the complete native inflate-init body `0x6678F0` (203/203 with explicit allocator/reset role bindings) and its `0x6679C0` wrapper (26/26). The provider audit now replays both along with PNG witnesses and the synthetic decode. This supports the mixed header/implementation context, not whole-library equivalence or authored credit. See `docs/PNG_PROVIDER_VERSION_2026_11_03.md`.

### 2026-11-03: classify profile-menu handlers

Exact dispatcher tail edges, complete body hashes and pinned original switch tables establish authored ownership for profile-menu primary `0x44BCF0` (256 bytes) and state-one `0x44CA80` (446 bytes). Switch-aware decoding reaches every body byte. Prior source candidates remain unselected/nonexact; no exact-byte gain. See `docs/ORIGIN_RECOVERY_2026_11_03.md`.

### Fighter base reset source registration (2026-11-03)

The complete 0x00460200 Fighter base reset source is now selected by
`exact-first-fighter-battle-reset` and classified authored from its full target
hash and the call from exact 0x004776D0. Its 1247-byte candidate remains
nonexact at +853 with 25 unequal bytes; no exact credit is added. The specific
origin rule, two directly related exact units, tracking and target-independent
CI were checked. The full origin census did not finish within the factory
command window, so this checkpoint does not claim a full census replay. See
`FIGHTER_BATTLE_RESET_2026_10_27.md` for the retained residual and boundaries.

### UI policy origins (2026-11-03)

Profile selection `427C60`, result-menu active update `4472A0` and key capture
`44B540` are authored by complete native bodies and exact owner edges. Their
prior source hypotheses remained nonexact at that checkpoint; `44B540` has
since been selected, still nonexact; the result update is also now selected.
Exact totals do not change. All three owner bodies were rebuilt exactly; the result owner's unit
still reports an overall mismatch on its separate constructor. The focused
origin rule, tracking and target-independent CI pass; a full origin census was
not replayed. See `ORIGIN_RECOVERY_2026_11_03.md`.

### Profile key capture source (2026-11-03)

The complete `44B540` keyboard/gamepad capture is now selected in its actual
class via `exact-first-profile-key-capture`. Its candidate remains 785/790
bytes with a 780-byte matching prefix and a different final return topology.
The exact owner and input provider units and target-independent CI replayed;
no exact byte credit is claimed. See `PROFILE_KEY_CAPTURE_SOURCE_2026_11_03.md`.

### Active result-menu source (2026-11-03)

The existing full `4472A0` result-menu policy is now individually selected by
`exact-first-result-menu-active`. The 620-byte candidate remains nonexact against
619 native bytes, first mismatch +81; EH cleanup is not proven exact. The exact
wrapper was rebuilt in the prior origin checkpoint and target-independent CI
passes. No exact bytes are added. See `RESULT_MENU_ACTIVE_SOURCE_2026_11_03.md`.

### Background transition setter (2026-11-03)

The complete `4654F0` background transition setter is authored and individually
selected. Its 407-byte native body and four-entry switch are pinned, with three
calls from exact battle-object dispatch. The source remains nonexact at +92;
its separate metadata receives no authored-byte credit. Exact transition-step
and dispatcher replays plus target-independent CI pass. The focused origin rule
passes; no full origin census was replayed. See
`BACKGROUND_SET_TRANSITION_SOURCE_2026_11_03.md`.

### Spell-selection finalization (2026-11-04)

The full `432200` spell-selection finalizer is now authored and individually
selected. The natural source uses the real checked VC8 deque iterator instead
of the earlier unselected hand-expanded iterator hypothesis. Its 226-byte
candidate remains nonexact against the 260-byte native body; the exact load
selector caller and target-independent CI pass. No exact bytes are added. The
focused origin rule passed; no full origin census was replayed. See
`SPELL_FINALIZE_SOURCE_2026_11_04.md`.

### Select scene entry (2026-11-04)

The existing complete `421120` character/stage selection entry is now
individually mapped and authored, using the full target hash and exact network
select caller at `426554`. The 783-byte candidate remains nonexact at +225.
All four network-select caller-unit bodies replay exact and target-independent
CI reports passed. The specific origin rule was checked; a full origin census
was not replayed. See `SELECT_SCENE_ENTRY_2026_10_28.md`.

### Script map cleanup origin (2026-11-04)

The full `405CD0` 56-byte script command-map cleanup is compiler-generated,
proved by a fresh genuine CIL source owner, exact destructor edge, whole-body
relocation replay and inventory uniqueness. The source erase role is bound to
the pinned native erase entry, but those larger erase implementations are not
claimed equal. Targeted proof, seven corruption controls and 1,013
target-independent CI tests passed. This adds no authored exact bytes; no full
origin census was replayed. See `SCRIPT_MAP_TIDY_ORIGIN_2026_11_04.md`.

### Package map cleanup origin (2026-11-04)

The full `41C8D0` 56-byte package-index map cleanup is compiler-generated,
proved by its real source-pinned CIL, exact archive-store destructor edge,
whole-body call-role replay and inventory uniqueness. The source erase role is
bound to the hash-pinned native erase entry; the erase implementations are not
claimed equal. Targeted proof, seven corruption controls and 1,018
target-independent CI tests passed. No authored exact bytes are added, and no
full origin census was replayed. See `PACKAGE_MAP_TIDY_ORIGIN_2026_11_04.md`.

### Scenario runtime reset (2026-11-04)

The complete `457E40` scenario state reset is authored and individually mapped
using its full target hash and exact story-page loader edge. Its current source
remains 339/334 and nonexact; the final system-effect tail is a separate
nonexact callee. All five same-TU exact roots, the exact loader and 1,018
target-independent CI checks pass. The focused origin rule was checked; no
full origin census was replayed. See `SCENARIO_RUNTIME_RESET_SOURCE_2026_11_04.md`.

### Spell selection shuffle (2026-11-04)

The authored `432420` selection shuffle is now individually source-selected,
using the actual VC8 checked iterator and target-observed out-of-line deque
methods. Its 196-byte candidate remains nonexact in seven scheduling bytes
at +132..+138. The exact mode setter and random provider replayed; all 1,018
target-independent CI checks pass. No exact-byte credit is added. See
`SPELL_SELECTION_SHUFFLE_SOURCE_2026_11_04.md`.

### Battle overlay exact (2026-11-04)

`4666A0` now matches the entire 670-byte original body after replacing the
old manual effect-vtable probe with the actual shared D3DX COM interface.
Configured and independent cold VC8 builds both compare exact. The five effect
lifetime roots and nine accepted manager roots, including the caller, replay;
the manager unit's separate `466F40` remains nonexact. This adds one authored
exact function / 670 bytes. See `BATTLE_RENDER_TAIL_EXACT_2026_11_04.md`.

### Shared sprite effect interface (2026-11-04)

Four previously exact sprite effect routines now use the shared
D3DX-compatible COM interface instead of a hand-declared vtable. All four,
their exact render-color caller, the battle overlay and five reset/lifetime
roots replay exact. The 1,018-test target-independent CI passed. This is
source cleanup only, with no new exact bytes. See
`SPRITE_EFFECT_D3DX_INTERFACE_2026_11_04.md`.

### Battle overlay real owner (2026-11-04)

The exact `4666A0` overlay is now the actual `BattleObjectManager` member, not a
separate receiver-view symbol. Its four typed vertices replace the same-size
opaque render area without changing the asserted owner layout. The caller and
provider now emit the same member symbol. A fresh cold build and all 18 accepted
roots in eight directly affected units replay exact; the prior nonexact `466F40`
remains unchanged. No integrated-link or new-byte claim is made. See
`BATTLE_RENDER_TAIL_EXACT_2026_11_04.md`.

2026-11-04: `CMenuPractice_update` at `0x00445D90` now has a complete
canonical 381/381-byte match in `src/ui/MenuPracticeUpdate.cpp`, using direct
indexed container expressions rather than the previously outlined size helper.
The target and candidate section hashes are equal; see
`docs/MENU_PRACTICE_UPDATE_2026_11_04.md`. Live-game behavior was not run.
The independent forced-recompile replay for `0x00445D90` subsequently passed
and was accepted after direct `build.py` invocations were routed through the
existing pinned `repo-python` environment. The 381 bytes are accepted exact.

2026-11-04: spell finalizer `0x00432200` now uses the deque member directly
for iterator endpoints. This natural source form reproduces the target frame
and checked owner comparison, but remains nonexact at 255/260 bytes, first
mismatch +3. See `docs/SPELL_FINALIZE_SOURCE_2026_11_04.md`.

2026-11-04: score observation update `0x0042D010` now locally compares 191/191
in two separately compiled objects, using direct checked-vector endpoints and
the same signed maximum predicate. Independent Factory exactness replay could
not start for the unregistered match; do not award exact credit. See
`docs/SCORE_OBSERVATIONS_MAXIMUM_2026_11_02.md`.

2026-11-04: score sequence-result update `0x0042CF70` now locally compares
159/159 in two separately compiled objects after using direct vector endpoints.
Independent Factory acceptance remains pending, so no exact credit is recorded.
See `docs/SCORE_SEQUENCE_RESULT_2026_11_04.md`.

2026-11-04: `PlayerSlotRecord::load_profile @ 0x00431AC0` uses natural indexed
deck access and has a reproducible probe: 728/native728, with only two resolved
operand bytes differing at +540/+543. It remains nonexact; full EH is unproven.
See `docs/PLAYER_SLOT_PROFILE_LOAD_2026_11_04.md`.

2026-11-04: spell finalizer `0x00432200` now locally compares 260/260 in two
separately compiled objects using natural zeroing and an integer ID, retaining
the direct checked-deque endpoints. Independent Factory acceptance remains
pending; no exact bytes are recorded. The exact loader caller remains exact.
See `docs/SPELL_FINALIZE_SOURCE_2026_11_04.md`.

2026-11-04: Komachi action 603 spawn-height expressions now preserve the
observed target grouping `random + (height + 20.0)` in both direction branches.
The full action root remains unselected/nonexact; see
`docs/KOMACHI_ACTION_STATE_2026_10_28.md`.


2026-11-08: Server input publication `0x0044F9A0` now uses actual short
values at the checked-deque boundaries, removing four int-to-short reference
casts. Full candidate407/native409 remains nonexact at +23; the same-TU exact
sender48/adaptive162 and unchanged ACK candidate78 were rechecked. The complete
CFG/call/field-width audit passes. See
`docs/SERVER_INPUT_PUBLICATION_SOURCE_2026_11_02.md` for the retained alternative
and evidence paths. Further matching needs value-lifetime/compiler-context
evidence, not a source-spelling grid.


2026-11-08: Profile load `0x00431AC0` now has complete local byte equality
for its 64-byte remote EH code, 60-byte unwind/FuncInfo metadata and 21-byte
reader cleanup, including all relocations. The main body remains 728/728 with
two differing operand bytes at +540/+543. No new exact credit is recorded.
See `docs/PLAYER_SLOT_PROFILE_LOAD_2026_11_04.md` for the resolved ownership and
reproduction; the remaining scope is the main-body load order and real reader
type, not an unknown EH layout.


2026-11-08: Profile load now uses the existing real `CFileReader` provider
instead of its duplicate reader class. Main728 retains exactly the prior two
differences, while complete EH and all five reader method bodies compare
equal. The source's namespaced RTTI string still differs from the target's
global class name. See `docs/PLAYER_SLOT_PROFILE_LOAD_2026_11_04.md`; no new
exact credit or shared-header change.


2026-11-08: `CFileReader` and `CPackageFileReader` now have their target-proved
global identities. All twelve RTTI records compare equal, and the 32-unit
consumer closure preserves its 47 accepted roots. Three dependent helper-origin
proofs and the reader checker pass. Profile load remains nonexact at its same
two operand bytes. See `docs/FILE_READER_GLOBAL_IDENTITY_2026_11_08.md`.


2026-11-08: System-effect tracked release `0x436E60` now implements the real
`TObjectManagerBase<SystemEffectObject, SystemEffectObjectBase>` member used
by its destructor and both Scenario callers. The duplicate callable receiver
and undefined Scenario alias are removed. All 27 affected units retain their
prior comparisons, including 34 accepted roots; release keeps its same two-byte
register residue. See `docs/SYSTEM_EFFECT_RELEASE_SOURCE_2026_11_03.md`.


2026-11-08: A representation-preserving sign-mask control for `0x46B8B0`
emits 173/native142 rather than recovering the target arithmetic shifts.
The selected 139-byte aggregate-mask source is restored; the complete unit
retains its three accepted roots and both previous nonexact candidates.
See `docs/COLLISION_SEMANTICS_2026_11_07.md`; no new exact credit.


2026-11-08: Real BGM CIL locally reproduces the complete 143-byte vector
insertion helper at `0x40DEE0`, including all five calls, closed CFG and unique
inventory identity. Four BGM and two Score exact roots replay. Exact Score
callers use `vector<int>` while BGM uses `vector<unsigned>`; preserve those
independent source types. The inner growth body remains 473/native475, and no
ledger or Factory acceptance status changes. See
`docs/VECTOR_INSERT_SHARED_BODY_2026_11_08.md`.


2026-11-08: Info-effect release `0x46EEB0` now defines the actual
`TObjectManagerBase<InfoEffectObject, EffectObjectBase>` member, and both
InfoManager binding callers use it. Five rebuilt units preserve 21 exact roots
and both prior nonexact bodies. A separate reverted trial exposed missing
AnimationObject virtual declarations: the shared effect header currently places
update at +0x10 instead of native +0x28. Recover that base contract before
merging the virtual consumer. See `docs/INFO_EFFECT_RELEASE_OWNER_2026_11_08.md`.


2026-11-08: The animation virtual-interface audit verifies complete RTTI for
five real classes but confirms their current emitted vtables are incomplete.
AttackObject/CharacterObject must retain abstract callbacks, and the roster
allocation view still differs from native CharacterObjectEx RTTI. Both int and
void action-finalizer controls reproduce the same complete bodies, so the
existing return types cannot alone establish the original override signatures.
No shared-header merge was made. See `docs/ANIMATION_VIRTUAL_CONTRACT_2026_11_08.md`.


2026-11-08: `CFileWriter` now has its native global identity. Five complete
method bodies, all four vtable slots and six RTTI records compare equal. The
29-unit shared-header closure preserves all 44 accepted roots, and three
source-dependent origin proofs pass. GameConfig save's complete 35-byte EH code
and 44-byte metadata also match; its main body retains only +579/+582.
See `docs/FILE_WRITER_GLOBAL_IDENTITY_2026_11_08.md`. No new exact credit.


2026-11-08: Profile save `0x4317A0` now has complete local equality for its
64-byte cleanup/EH code and 60-byte unwind metadata. Both 261-instruction
callable graphs close, with all 50 control transfers identical. Main-body
scheduling/register differences remain; no source or exact-ledger change.
See `docs/PROFILE_WRITER_CHECKED_DECK_2026_10_29.md`.


2026-11-08: Roster release `0x56DA90` now defines all fifteen real
`TObjectManagerBase<RosterObject, CharacterObject>` members, and the fifteen
preallocation callers use those members. All 129 accepted roots across the
nine focused units retain exact comparisons. Each emitted release body still
has its original two register differences; no new exact credit. See
`docs/ROSTER_RELEASE_OWNER_2026_11_08.md`.


2026-11-08: Client snapshot import now uses the existing ACK_INFO packet class,
proved by the original constructor, parser and primary-vtable dispatch chain.
Its 399-byte candidate is unchanged; the dispatcher and both codecs remain
exact. Complete handler27 and metadata44 match, but cleanup7/native13 adds a
separate known full-EH blocker. See
`docs/NETWORK_CLIENT_SNAPSHOT_IMPORT_2026_11_04.md`.


2026-11-08: Nine player-slot deck-copy calls now use the existing implemented
provider through one typed header. The seven-unit include closure retains six
accepted roots and all three previous nonexact bodies. Normal match setup's
complete 556-byte code/alignment/switch-table section also matches. Constructor
EH/RTTI section contents and relocation roles are unchanged. See
`docs/PLAYER_SLOT_DECK_PROVIDER_2026_11_08.md`.


2026-11-08: Snapshot lock cleanup has no demonstrated lifetime error: both
paths release the same critical-section member exactly once. Revealing the
real wrapper implementation naturally matches destructor13 and action8, but
grows the main body to 404/native399 and changes handler frame offsets. The
private control is not retained; original TU visibility remains the blocker.
See `docs/NETWORK_CLIENT_SNAPSHOT_IMPORT_2026_11_04.md`.


2026-11-08: Spell-sequence preparation now uses the existing FighterSequenceSlot
record through construction and enqueue, removing the duplicate stack type.
Both affected profiles preserve all section bytes and relocation roles; the
readiness118 and enqueue114 roots remain exact. Complete EH code44, metadata44
and record destructor8 now compare equal. The main body remains257/native259.
See `docs/SEQUENCE_PREPARATION_2026_10_28.md`.


2026-11-08: CInputManagerEx now overrides the base update instead of adding a
third virtual slot. The original two-slot table and all three emitted method
bodies compare equal. Nine actual derived-type consumers preserve all 13
accepted roots, and five affected compiler-origin proofs pass. Global class
identity and constructor-view unification remain separate work. See
`docs/INPUT_MANAGER_OVERRIDE_2026_11_08.md`.


2026-11-08: The actual network input endpoint now uses the existing shared
base60/endpoint48/cleanup19 implementations, removing independent constructor
views and the owner's incomplete implicit base9/endpoint23 definitions.
Eleven focused units preserve 15 accepted roots; parent411/EH197/metadata116
and five origin proofs pass. Global input-class identity remains separate.
See `docs/NETWORK_INPUT_CONSTRUCTOR_2026_10_29.md`.


2026-11-08: CInputManagerCluster now implements the original update override,
and selection construction/lifetime use the same shared input definitions.
The complete two-slot table, update1003, normal19 and scalar40 match locally.
All 12 distinct accepted roots across 20 units are preserved; four origin
proofs pass. Global input identity still requires a coordinated signature and
forward-declaration migration. See `docs/INPUT_CLUSTER_SHARED_OVERRIDE_2026_11_08.md`.


2026-11-09: Spell finalization now uses its actual short-deque member directly,
removing two obsolete casts from the prior layout view. Full local 260-byte and
71-byte caller comparisons are unchanged; acceptance and exact ledgers are untouched.
See `docs/SPELL_FINALIZE_SOURCE_2026_11_04.md`.

2026-11-09: GuideOverlay destruction now has complete local equality for
the 38-byte cleanup/handler, 44-byte unwind metadata and seven-byte real sprite
cleanup. The 90-byte main candidate still differs from the 92-byte target at
+40; the 20-byte constructor remains exact.
See `docs/GUIDE_OVERLAY_LIFETIME_2026_10_29.md`. The suspended global input
migration and its source-pin blocker remain untouched and uncommitted.


2026-11-09: Both ACK_INFO senders now use the existing shared UDP send provider
and its shared 0x200-byte prefix view, removing undefined caller aliases. Sender
269/341 and token release 167 remain exact; complete shared EH code 48,
metadata 44 and packet cleanup 19 also match. Two affected origin proofs pass.
See `docs/ACK_SEND_PROVIDER_2026_11_09.md`. Input migration remains separate.


2026-11-09: Primary protocol, state, continuation and replay sends now share the
existing UDP provider. Eight duplicate sender classes are gone; the server
packet wrapper's false integer result contract is corrected to void. Seven
units retain all 26 accepted roots and both prior nonexact results. The server
dispatcher's complete code/table564, EH56, metadata52 and cleanup8/19 also match.
See `docs/PROTOCOL_SEND_PROVIDER_2026_11_09.md`. No origin pins changed.


2026-11-09: UDP receive, acceptance and peer removal now share the native
INetworkUDPEventProc interface and existing default implementations. All six
slots have whole-method equality; five accepted roots and every affected
nonexact comparison are preserved. Two linked allocator proofs and the four
emitted-helper checks pass. See `docs/UDP_EVENT_INTERFACE_2026_11_09.md`.
The send-provider notes now explicitly describe 0x200 as a modeled prefix,
not the full native class size. Input migration remains untouched.


2026-11-09: Network construction and teardown now call the real callback
publication implementation instead of undefined cleanup aliases. A shared
state prefix joins publication, indexed checks and status reads across six
units; 17 authored exact roots and two compiler wrappers remain equal. Folded
EH35/metadata44 and factory EH38/metadata44 also match. The native Server-null
and Client-secondary-pointer destructor policies are preserved. See
`docs/NETWORK_CALLBACK_PUBLICATION_2026_11_09.md`. No origin pins changed;
the input migration remains separate.


2026-11-09: Constructor/lifetime views now inherit the real six-slot UDP
interface with Server slots 3/4 and Client slots 0-4 overridden. Three Client
notifications no longer promise incidental EAX values. Ten authored exact
roots and two compiler wrappers remain equal; full secondary tables, COLs and
inheritance geometry pass. Client dispatcher section624, EH70, metadata60 and
three packet cleanups also match. Primary-class and callback-implementation
view unification remains open. See `docs/DERIVED_UDP_CALLBACKS_2026_11_09.md`.
No source pins changed; the pending input migration is preserved.


2026-11-09: Queue advancement at 0x44EA80 now has the correct input-endpoint
owner and a shared implementation used by both Client pacing and Server
maintenance. Three units preserve eight accepted roots and the existing
573-byte pacing mismatch. All 318 original non-debug sections retain bytes
and relocation roles. The full network primary merge remains coupled to the
pending input member closure; it is not attempted here. See
`docs/NETWORK_INPUT_DELAY_OWNER_2026_11_09.md`.


2026-11-09: Server flush now calls the existing peer-removal implementation
instead of an undefined state alias. Seven units preserve 19 exact comparisons
and both pending peer bodies; all 323 existing non-debug sections are unchanged
after the call-symbol substitution. Both affected linked allocator proofs pass.
See `docs/NETWORK_PEER_REMOVAL_BINDING_2026_11_09.md`. No new exact credit;
the input migration remains separate.


2026-11-09: YoumuObject action 853 now preserves the shared tail's incoming
EBX=3: its last retirement guard checks sequence 3 instead of repeating 2.
Eight focused native executions pass; the old body fails both reset-counter
cases. Four common operations now call their existing exact implementations,
with all 48 native receiver offsets verified. Whole root 27024/native26576
remains nonexact. See `docs/YOUMU_OBJECT_UPDATE_2026_10_25.md`.


2026-11-09: The Youmu shared-tail follow-up found no further retirement fix.
Native incoming constants distinguish 812/853 at the shared guard; 812's second
phase-zero branch is intentional. Eight bounded motion/fade paths agree with
the unchanged candidate. See the shared-tail follow-up in
`docs/YOUMU_OBJECT_UPDATE_2026_10_25.md`. No source or exact-ledger change.


2026-11-09: Bitmap upload `0x41AE60` has a new bounded cursor-control result:
native pointer induction restores the local frame but remains nonexact in both
COFF and the actual reader/bitmap/PNG LTCG context. The two contexts produce
identical complete payloads. No source or exact-ledger change was retained;
see `docs/BITMAP_TEXTURE_LOADING_2026_10_30.md` before repeating this control.


2026-11-09: KomachiObject's four common operations now use their existing real
runtime providers. All 68 native receiver offsets are proved; the complete
28,816-byte candidate and all 85 non-debug sections are unchanged. Four provider
roots replay exact, while the parent remains nonexact. See
`docs/KOMACHI_OBJECT_UPDATE_2026_10_25.md`. Input migration remains untouched.


2026-11-09: Iku, Tenshi and Udonge object updates now use the four existing
runtime providers instead of twelve undefined aliases. Complete native CFGs
prove all 251 receiver offsets; all 339 non-debug sections and three complete
candidate payloads are unchanged. Four provider roots remain exact; parents
remain nonexact. See `docs/ROSTER_RUNTIME_PROVIDERS_2026_11_09.md`.


2026-11-09: Tenshi's quantized-trig return-type review found no justified
prototype change. Both native providers return a direct float-table load in
ST0; 81 calls across Tenshi, Iku and Udonge plus complete motion/tangent callers
show differing expression lifetimes without proving float versus double
return spelling. See the return-contract section in
`docs/TENSHI_OBJECT_UPDATE_2026_10_25.md`. Source and exact status are unchanged.


2026-11-09: Platform, audio and battle now share the actual eight-byte thread
handle declaration; network shutdown calls its real wait provider instead of
an undefined alias. All 40 affected root comparisons retain their results
(34 exact), with 711 COFF sections and both linked images unchanged apart from
export timestamps. Three affected origin proofs pass. See
`docs/SHARED_THREAD_HANDLE_2026_11_09.md`. No new exact credit; pending input
migration remains unchanged.


2026-11-09: Sakuya's three common runtime calls now use their real providers;
all 53 native receiver offsets are proved. The complete 29,228-byte candidate
and all 83 non-debug sections are unchanged; provider roots remain exact.
Review of 32 actions preserves the original shared-tail conditions, including
810's own-sequence redundancy and 849's branch-after-comparison edge. See
`docs/SAKUYA_OBJECT_UPDATE_2026_10_25.md`. No new exact credit or input changes.


2026-11-09: Fixed the configuration reader's emitted size virtual, which returned
zero instead of calling native GetFileSize. Its complete 13-byte provider and
all five virtual slots now match; the accepted loader remains 953/953 and all
180 other non-debug sections are unchanged. See the configuration-reader section
in `docs/SHARED_PLAIN_FILE_READER_2026_11_04.md`. No new exact credit or input
migration changes.


2026-11-09: Shared-tail review of Yukari, Yuyuko, Patchouli and Remilia found no
further source correction: all 198 reviewed lifetime ADD sites subtract one,
and shared known sequence guards preserve their incoming constants. The
Yukari 820 redundancy and Yuyuko 848 short circuit are native behavior. See
`docs/ROSTER_SHARED_TAIL_REVIEW_2026_11_09.md`. Factory access has recovered;
the pending input migration and its source-pin blocker remain unchanged.


2026-11-09: SCENE_ACK and TERMINATE now have the RTTI-proved IPacket base and
both native virtual slots. Their missing parsers are restored, and serializers
are real methods shared by callers. Four full method bodies and all eleven
previously exact roots match; both dispatchers' complete code/tables, EH and
metadata also match. See the small-packet section of
`docs/ACK_PACKET_BASE_2026_10_29.md`. No new exact credit or source-pin changes.


2026-11-09: REQ_INFO now uses its actual single-buffer serializer inside the
real four/five-argument UDP send; the old incorrect parameter counts had
canceled on the stack. REQ_INFO and DELAY now also have both RTTI-backed
virtual slots. All seventeen affected roots and complete dispatcher/EH checks
remain exact. See `docs/ACK_PACKET_BASE_2026_10_29.md`. The bounded packet
census adds no new physical exact methods; SCENE remains coupled to the
pending input/source-pin closure and is untouched.


2026-11-09: WinMain now constructs the actual shared CFade instead of a class
with undefined callbacks. Its RTTI-proved IFade base and empty shutdown slot
are restored; all five full providers and the complete table match. Nine
renderer roots remain exact, while the 695-byte WinMain candidate is unchanged
and nonexact. See `docs/SCENE_MANAGER_VIRTUAL_LEAVES_2026_10_28.md`.
No new exact credit, source-pin changes or input migration edits.


2026-11-09: WinMain now constructs the shared CSceneManager with its native
ISceneManager base. All five slots resolve to real implementations, including
the scene factory restored as a member. Five providers, the full factory
switch table, sixteen EH cleanup states and RTTI geometry match; WinMain's
695-byte nonexact candidate is unchanged. See
`docs/SCENE_MANAGER_VIRTUAL_LEAVES_2026_10_28.md`. No new exact credit or
source-pin changes; the pending input migration remains unchanged.


2026-11-09: Corrected the scenario-step wrapper from bool to signed byte after
verifying native 00/01/FF returns and the story caller's signed comparison.
Story now calls the real provider. A stale health-field reference also caused
its unit to fail compilation; the native-offset repair restores all six story
matches. Eight affected roots remain exact, continue/reset remains unchanged
and nonexact, and full story EH plus 295 COFF sections pass. See
`docs/SCENARIO_STATUS_CONTRACT_2026_11_09.md`. No source-pin or input edits.


2026-11-09: Sequence-effect reset now uses its actual CSprite member and one
shared void method; both callers resolve to that real implementation. Native
Character construction, sprite RTTI and both calls establish the offsets and
contract. All three complete roots and three color providers remain exact;
170 non-debug sections are unchanged. See
`docs/SEQUENCE_EFFECT_SPRITE_CONTRACT_2026_11_09.md`. No source-pin changes,
input migration edits or new exact credit.


2026-11-09: Native RTTI and the scene caller identify 470ED0 as Story's void
render callback. It now implements the actual +38 slot and calls the shared
provider instead of an undefined int alias; 45A2A0 and Ending share the void
scenario-render contract. All 21 affected roots, 233 non-debug sections and
complete Story EH remain exact/unchanged. See
`docs/STORY_RENDER_CONTRACT_2026_11_09.md`. Input migration and pins are
unchanged; no new exact credit.


2026-11-09: Call-contract triage rejects four misleading alias mismatches:
fade/replay statuses retain their native values, the shared one-word no-op
is genuine folding, and slot-finalization callers may discard its status.
Animation sequence return propagation still needs its full virtual-call
closure. See `docs/CALL_CONTRACT_TRIAGE_2026_11_09.md`. No source change.


2026-11-09: Animation return review closes 23 original bodies and all eleven
raw direct edges, plus the wrap dispatcher. The 53-table census separates
frame propagation from 35 distinct +3C finalizers; the dispatcher genuinely
consumes the next-frame/block byte statuses. Full indirect consumer typing is
still unresolved, so no family-wide int/void change was made. See
`docs/ANIMATION_RETURN_CONTRACT_2026_11_09.md`. Pending input work is unchanged.


2026-11-09: Recovered the audio scheduler's initialization and real global
lifecycle as an unselected source candidate. Natural global LTCG yields the
249-byte constructor shape at 418F00, but callback code-pointer and no-EH
destructor proof remain unsupported; no validator relaxation or exact claim.
Both accepted consumers remain exact, all other affected code is unchanged.
See `docs/AUDIO_SCHEDULER_INITIALIZATION_2026_11_09.md`. Input migration remains
untouched; no source pins or ledgers changed.


2026-11-09: Audio callback arithmetic no longer depends on the surrounding build
profile. Scoped FP environment access restores the native repeated drift
calculations and float constant in the real global context, changing 523 to 577
bytes against native 591. The selected 576-byte candidate and all 21 COFF sections
remain unchanged. The real callback pointer is traced but its provider is still
nonexact, so no new pointer exception or exact claim is made. See
`docs/AUDIO_SCHEDULER_INITIALIZATION_2026_11_09.md`. Input changes and pins remain
untouched.


2026-11-09: Title construction now embeds the actual shared CDesignBase rather
than a local five-slot opaque class, and its declared set_color virtual slot now
has the real shared-class provider. Title616 and color81 remain canonical, as do
the seven design-render/lookup roots, implicit lifetimes and all398 owned EH
bytes. See `docs/TITLE_DESIGN_OWNER_2026_11_09.md`. No shared header, input pin,
origin gate or exact count changed; the outer Title layout remains separate.


2026-11-09: CTitle now has one shared scene declaration across its factory,
constructor, destructor and all callbacks. Actual handle-value extraction keeps
both lifetimes exact; the missing empty virtual method is supplied. All nine
accepted roots, owned tables, complete1,105-byte EH closure and scalar origin
proof pass. The renderer's417-byte nonexact candidate is unchanged. See
`docs/TITLE_OUTER_OWNER_2026_11_09.md`. No new exact credit or input/source-pin edits.


2026-11-09: Added the application's real static initialization candidate.
The complete255-byte constructor, generated73-byte cleanup,139-byte EH closure,
initializer17 and all member helpers reproduce the pinned target. The current
paired-global proof cannot select a direct no-EH atexit body, so this remains
unselected with no new exact credit. See
`docs/APPLICATION_INITIALIZATION_2026_11_09.md`. The same data flow identifies
CSceneBase's alleged scene_id as a CFade pointer; that shared type correction
is the next bounded follow-up. Existing units, dirty input work and pins remain
unchanged.


2026-11-09: Corrected CSceneBase's supposed scene_id to the actual CFade pointer
and removed Opening's integer-to-pointer color access. All 29 scoped units keep
identical 3,482 non-debug sections; 36 exact roots and nine existing nonexact
results are unchanged. Complete Title/member/factory EH also passes. See
`docs/SCENE_BASE_FADE_POINTER_2026_11_09.md`. The Application direct no-EH callback
has no supported existing strict-selection route; no validator changes or
acceptance retries. Pending input changes and source pins remain untouched.


2026-11-09: Corrected the event-effect map's key from char to signed DWORD.
The old 72-byte wrapper match hid a wrong 114-byte generated callee; the shared
int-key reader/writer now emits the actual 105-byte find exactly. All three
native direct callers and eighteen bootstrap writes are confirmed. Five exact
roots and the existing bootstrap mismatch are unchanged, as are 363 consumer
sections apart from a separate SafeSEH handler-list ordering change. See
`docs/EVENT_EFFECT_KEY_WIDTH_2026_11_09.md`. No new authored exact credit, input
migration changes or source-pin updates.


2026-11-09: Replaced the character stage/BGM tree facade with real shared
map<int,unsigned char> readers. Native 45C320 performs an equality check after
lower-bound traversal; the actual generated find now matches all 105 bytes.
Both 72-byte wrappers remain exact, seven native caller sites and thirty map
initializations are confirmed, and all 348 bootstrap sections are unchanged.
See `docs/CHARACTER_POLICY_MAPS_2026_11_09.md`. No new authored exact count or
input/source-pin changes.


2026-11-09: Configuration BGM/SE setters now share void contracts with their
audio providers rather than propagating an incidental final EAX value. Native
menu and bootstrap call chains discard it. Roots 39/80/665 remain exact, the
menu's complete 688-byte section matches, and all 359 scoped non-debug sections
retain their bytes and relocation roles. Bootstrap's prior mismatch remains.
See `docs/CONFIG_VOLUME_CONTRACT_2026_11_09.md`. No new exact count, input
migration edits or source-pin changes.


2026-11-09: Combo loading/rendering and short-record color dispatch now share
the proven 0x6C layout and actual design/number types. Ten lookups use the real
118-byte bind_object_alt provider. Roots 413/156/572 remain exact; all 427 bytes
of the nonexact loader and 191 existing non-debug sections are unchanged. Both
generated deque helper proofs pass. See
`docs/INFO_COMBO_SHARED_OWNER_2026_11_09.md`. Outer lifetime interfaces, pending
input work and source pins remain untouched; no new exact count.


2026-11-09: Removed the independent combo resource facade from InfoManager's
normal initialization and teardown. The real shared receiver supplies loading
and void cleanup; the outer base loader also uses the provider's void contract.
Fourteen affected units retain 27 exact roots, 516 existing COFF sections and
228 bytes of normal lifetime EH. Actual cleanup310 and both generated-helper
and scalar-wrapper proofs pass. Two prior mismatches and the BattleInfoRecord
iterator-relocation blocker remain unchanged. See
`docs/INFO_RESOURCE_CONTRACT_2026_11_09.md`. No new exact credit or pending
input/source-pin edits.


2026-11-09: CFileList now owns real CTile elements, and rendering calls the
actual deque operator[] rather than rebinding at() to a different native body.
Youmu's reader now shares its constructor/writer's real history deque and
provides the separate at() helper. Both complete 94-byte providers match;
21 units retain 44 exact comparisons, full CTile RTTI/copy/scalar support and
FileList destructor EH. Five generated exclusions move to the actual Youmu
source; all affected origin proofs pass without changing classification totals.
Three previous mismatches remain. See
`docs/FILE_LIST_TILE_CONTAINER_2026_11_09.md`. Only the changed FileListFinalize
source pin is renewed; pending input work is preserved.


2026-11-09: Command gates now use the PAT loader's actual map and PatGroup
instead of the undefined lower_bound/node facade. Fixed stale Fighter field
names that prevented this source from compiling. Three affected units retain
ten exact roots (2,349 bytes), all 72 previous sections per object, and the
unchanged 950-byte front-card candidate; the real find provider is 105/105.
See `docs/COMMAND_GATE_PAT_OWNER_2026_11_09.md`. No new exact credit, source-pin
updates or changes to pending input work.

2026-11-09: Result and network replay reads now call the actual short-deque
operator[] provider instead of rebinding at(). Result-menu replay append now
uses deque push_back rather than the string-assignment facade. Five affected
units preserve eight exact roots and thirteen complete root/EH sections.
The accessor100, append119 and grow-map344 providers match in full; menu
update remains 620/native619 with mismatch +81. See
`docs/RESULT_REPLAY_DEQUE_CONTRACT_2026_11_09.md`. Pending input migration and
source pins are unchanged.

2026-11-09: Replay-request dispatch now prepends history values with the actual
deque push_front, matching native call 0x44E619 -> 0x42A4B0. The old push_back
source was incorrectly rebound to that address. Dispatcher566, actual
push_front122, grow-map344 and remote EH59/metadata52 all replay exactly.
See the November 9 section of
`docs/NETWORK_SECONDARY_REPLAY_ORIGIN_2026_11_03.md`. Input work is preserved.

2026-11-09: Music path selection and result value/label reads now use their
actual deque indexing providers instead of mismatched at() bindings. Six exact
music roots, the unchanged nonexact result root and fifteen complete root/EH
sections are preserved. String94 and integer100 providers match in full.
See `docs/UI_DEQUE_INDEX_PROVIDERS_2026_11_09.md`. Input work is untouched.

2026-11-09: Profile-deck availability/render/update now use the writers' actual
iterator deque instead of at() declaration-only receivers. Natural indexing
preserves both exact roots358/1339, the prior render2521 mismatch and five
complete root/EH sections. All three emitted 99-byte indexing providers match.
See `docs/PROFILE_DECK_INDEX_PROVIDER_2026_11_09.md`. Input work is preserved.

2026-11-09: ProfileDeckFilter now uses its real checked iterator-deque subscript.
The complete 1,375-byte callable, 1,396-byte owned extent with all five switch
relocations, and 99-byte provider remain exact. See
`docs/PROFILE_DECK_FILTER_2026_10_29.md`. Input migration work remains untouched.

2026-11-09: Result-menu active policy `0x4472A0` is now canonical exact across
all 619 authored bytes. Real container views and C++ installation semantics
restore the native selection, replay, profile and cancel paths. Full 38-byte
EH code, 44-byte metadata, five container providers and direct wrapper/menu
stack also replay exactly. See `docs/RESULT_MENU_ACTIVE_SOURCE_2026_11_03.md`.
The separate initialization body remains nonexact; input migration is untouched.

2026-11-09: INPUT packet serialization and replay consumption now use actual
short-deque subscripts instead of declaration-only `at()` aliases. All 13
affected functions remain locally byte-exact; 17 full root/EH sections are
unchanged and both 100-byte providers match. No new Factory acceptance or
progress credit is claimed. See `docs/RESULT_REPLAY_DEQUE_CONTRACT_2026_11_09.md`.

## November 9: correct input-vector accessor ownership

`0x43B300` is the actual input vector's compiler-generated subscript, not an
authored `at` method. The real provider remains locally exact 59/59; whole-body
inventory uniqueness and the native `0x6FCA2C` receiver are verified. Remove its
false authored credit. The selected-input caller remains exact 153/153, while
the 286-byte match-mode caller remains nonexact. Pending input migration files
and SHA pins are unchanged. See `INPUT_VECTOR_SUBSCRIPT_ORIGIN_2026_11_09.md`.

## November 9: spell selection shuffle is locally exact

The actual deque push-front provider closes `0x432420` at 196/196 without
changing flags or forcing the inliner. Complete push-front122, grow-map344,
independent erase108, and direct source-unit roots33/35 match. The original
out-of-line single-element erase edge must be retained; exposing it inline
instead produces a rejected 237-byte root. Local authored credit increases by
196 bytes; Factory acceptance is still separate from local equality. Pending
input work and SHA pins remain untouched. See
`SPELL_SELECTION_SHUFFLE_SOURCE_2026_11_04.md`.

## November 9: correct sequence push ownership

`0x45DBA0` is the actual 114-byte deque push-back provider, verified with the
shared FighterSequenceSlot, full inventory uniqueness and all three original
calls. Replace the hand-written implementation and its preparation caller with
the real standard member, and remove the mistaken authored credit. Readiness118
and all prior nonexact main-body hashes are preserved; preparation EH44,
metadata44 and cleanup8 remain exact. No new Factory acceptance is claimed;
pending input work is untouched. See `SEQUENCE_DEQUE_PROVIDER_2026_11_09.md`.

## November 9: correct PAT vector size ownership

`0x45C090` is the real compiler-generated PAT vector size provider, exact31/31
from the actual loader and the public provider. Its native loader/assign/insert
chain and whole-inventory uniqueness are verified. Remove the mistaken authored
credit; neighboring hit-scaling roots37/37 and37/37 remain unchanged. The larger
loader and insertion remain nonexact. No new Factory acceptance or input
migration/pin changes. See `PAT_VECTOR_SIZE_ORIGIN_2026_11_09.md`.

## November 9: actual CPU sequence receivers

Marisa and Alice CPU policies now read the real 0x98-byte sequence-record deque
at Fighter+55C instead of undefined short-pointer `at()` facades. All 47 native
receiver/read sites are verified and both emitted subscript providers match
94/94. Complete caller sections, switch payloads and relocation roles remain
unchanged and nonexact. No progress credit or input/pin changes. See
`CPU_SEQUENCE_OWNER_2026_11_09.md`.

## November 9: package path array ownership

The package node now pairs array new with actual array delete rather than a
CRT-free relocation alias. All thirteen affected units preserve their 43
comparison results, including the exact 43-byte destructor; four dependent
origin proofs pass. Pending input migration and its source pins are preserved.
See `PACKAGE_INDEX_ARRAY_DELETE_2026_11_09.md`.
