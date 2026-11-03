# TH10.5 reconstruction handoff

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

The complete 753-byte `0x463E40` fighter input/state policy is classified authored from its pinned body and four call edges in two freshly exact round-init/pre-reset callers. Its sole indirect virtual tail remains outside this ownership proof. The earlier 751-byte candidate is not in the current tracked source tree; no source-present or exact credit is claimed. See `docs/FIGHTER_SCRIPTED_INPUT_ORIGIN_2026_11_03.md`.
