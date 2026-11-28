# TH10.5 reconstruction handoff

Target: original Japanese TH10.5 v1.06a, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Follow [AGENTS.md](../AGENTS.md), [shared tools](SHARED_TOOLS.md) and the
[reconstruction workflow](RE_WORKFLOW.md). Keep compiler/analyzer work serial.
Run `scripts/repo-python scripts/report-reconstruction-status.py --summary` or
read [PROGRESS.md](PROGRESS.md) for current ledger totals.

## Latest milestone: all 12 remaining Object `+0x3C` action-entry roots exact

All twelve remaining Object primary-vtable `+0x3C` (`initialize_action_entry`)
roots in JP TH10.5 v1.06a are now canonically exact under standalone VC8 SP1
`/O2 /GS- /GR /EHsc /MT` (zero byte differences across all **89,252** callable
bytes and all **93,544** complete switch-payload bytes, covering every switch
table, remap table, alignment pad, and tail jump to `0x00596370`):

| Character | Address | Callable B | Payload B | Tables | Match unit | Commit |
| --- | --- | ---: | ---: | ---: | --- | --- |
| Patchouli | `0x0052D200` | 10,831 | 11,180 | 2 | `exact-first-patchouli-object-entry` | `49e632de` |
| Yuyuko | `0x00578000` | 10,828 | 11,143 | 1 | `exact-first-yuyuko-object-entry` | `49e632de` |
| Marisa | `0x004C8050` | 10,126 | 10,532 | 2 | `exact-first-marisa-object-entry` | `d7e6e77e` |
| Suika | `0x005BD380` | 8,956 | 9,284 | 1 | `exact-first-suika-object-entry` | `fe2724fa` |
| Tenshi | `0x00657150` | 8,590 | 8,902 | 1 | `exact-first-tenshi-object-entry` | `fe2724fa` |
| Yukari | `0x005964C0` | 7,588 | 7,920 | 1 | `exact-first-yukari-object-entry` | `b75842dd` |
| Sakuya | `0x004E8060` | 6,538 | 6,868 | 1 | `exact-first-sakuya-object-entry` | `7e1d1c14` |
| Komachi | `0x00600390` | 6,216 | 6,540 | 2 | `exact-first-komachi-object-entry` | `57a2e172` |
| Youmu | `0x00543670` | 5,159 | 5,492 | 2 | `gpt-web-youmu-object-action-entry` | `7e1d1c14` |
| Remilia | `0x0055BE70` | 4,997 | 5,384 | 3 | `exact-first-remilia-object-entry` | `7e1d1c14` |
| Reimu | `0x004A1CE0` | 4,892 | 5,440 | 8 | `gpt-web-reimu-object-action-entry` | `7e1d1c14` |
| Aya | `0x0061F0B0` | 4,531 | 4,859 | 1 | `gpt-web-aya-object-action-entry` | `7e1d1c14` |

Key reusable VC8 `/O2` insights closing all twelve roots:

- **Checked typed views over raw `unsigned char *` offset macros**: removing
  `char *` aliasing barriers and explicit `float *const input` temporaries lets
  VC8 field-level CSE naturally emit `mov reg, edi; fld [reg]` across quantized
  trig calls (Patchouli, Yuyuko, Suika, Tenshi), restore `pop ebp` scheduling
  (Yukari), and recover native register allocation (Marisa).
- **Natural numeric `case` order without artificial cross-case `goto`s**: placing
  duplicate/shared cases in numeric order lets VC8 `TryTailMerge` fold identical
  arms automatically while advancing `c2.dll`'s round-robin register search
  pointer (`0x10D0F854`) identically to the original compile (Sakuya, Komachi,
  Youmu, Remilia, Reimu, Aya).

## Previous milestone: all 5/5 Fighter CPU `+0x58` action-policy roots exact

All five Fighter primary-vtable `+0x58` CPU action-policy roots in JP TH10.5
v1.06a are now canonically exact under standalone VC8 SP1
`/O2 /GS- /GR /EHsc /MT` (zero byte differences across all **80,524** callable
bytes and all **83,691** complete switch-payload bytes, covering all 33 switch
tables and 1,862 relocations):

| Character | Address | Callable B | Payload B | Tables | Match unit | Commit |
| --- | --- | ---: | ---: | ---: | --- | --- |
| Alice | `0x004F4B80` | 16,354 | 17,009 | 9 | `exact-first-alice-cpu-policy` | `a3637b5d` |
| Marisa | `0x004B4070` | 16,229 | 16,907 | 8 | `exact-first-marisa-cpu-policy` | `9130deb0` |
| Reimu | `0x0048D390` | 15,999 | 16,573 | 4 | `gpt-web-reimu-cpu-action-policy` | `0b71cd91` |
| Default (11 roster) | `0x005F1F80` | 15,910 | 16,541 | 6 | `gpt-web-default-cpu-action-policy` | `4bb6a057` |
| Aya | `0x006126E0` | 16,032 | 16,661 | 6 | `gpt-web-aya-cpu-action-policy` | `b75c42c0` |

Key patterns closing all five roots without `/LTCG` (natural C++ control flow
replacing synthetic `goto` labels, missing-`break;` fallthrough in nested
`switch (FRONT)` blocks, `do { ... } while (0)` in Reimu Phase 2, and
`case 414`'s `switch (FRONT)` exit structure in Default/Aya) are recorded in
[VC8_SOURCE_SHAPE_PATTERNS.md](VC8_SOURCE_SHAPE_PATTERNS.md).

```bash
WINEDEBUG=-all DISPLAY= WAYLAND_DISPLAY= scripts/repo-python scripts/build.py --unit gpt-web-aya-cpu-action-policy --compare --json
```

## Previous milestone: all 15/15 Fighter `+0x28` action-state roots exact

With `Yukari_dispatch_action_state_vslot28` (`0x0057B030`, commit `488f575e`),
every Fighter primary vtable `+0x28` action-state root in JP TH10.5 v1.06a is
now canonically exact under VC8 SP1 `/O2 /GS- /GR /EHsc /MT`, covering all
135 owned switch tables and zero byte differences against `resources/th105.exe`.

### Latest completed root: Yukari (`0x0057B030`)

`exact-first-yukari-action-state` reproduces [YukariActionState.cpp](../src/characters/YukariActionState.cpp)
and [YukariActionState.hpp](../src/characters/YukariActionState.hpp):

- Callable code `[0x0057B030, 0x00588F02)`: 57,042 bytes, 14,501 reachable
  instructions, zero alignment holes, SHA-256
  `7caa43b9c69087875de1d8db150434733ad7b8a0fbd0d7bd245ee288f3db5db3`.
- Complete nine-table switch payload `[0x0057B030, 0x005893B8)`: 58,248 bytes
  (144 destination words, 623 index bytes, 7 alignment bytes), SHA-256
  `8c76f4df41ea9627a161193cf132671508311cd6e04717a4314a7cb2390682af`.
- Relocations: 1,769 verified (889 REL32 calls across 32 targets, 880 DIR32
  fields). Owner audit: 122/122. Private reports:
  `build/yukari-root-work/{canonical,owners}.json`.

```bash
WINEDEBUG=-all DISPLAY= WAYLAND_DISPLAY= scripts/repo-python scripts/build.py --unit exact-first-yukari-action-state --compare --json
scripts/repo-python scripts/audit-giant-action-owners.py --unit exact-first-yukari-action-state yukari-vslot28 build/match-units/ExactFirst_YukariActionState.obj --json
```

See the [Yukari note](YUKARI_ACTION_STATE_2026_10_28.md) and
[VC8 source-shape patterns](VC8_SOURCE_SHAPE_PATTERNS.md) for the `c2.dll:0x10B14E2A`
global constant-coloring findings (`CONST(0) -> EBP`, `CONST(1) -> EBX`).

### Completed Fighter `+0x28` roots (15/15)

| Character | Address | Callable (owned) B | Payload B | Tables | Match unit | Commit | Note |
| --- | --- | ---: | ---: | ---: | --- | --- | --- |
| Reimu | `0x00478FA0` | 81,550 | 82,924 | 11 | `neon-reimu-action-state-root` | `473165f6` | [Reimu](REIMU_EVIDENCE.md) |
| Marisa | `0x004A3710` | 66,695 | 67,936 | 6 | `exact-first-marisa-action-state` | `da319f04` | [Marisa](MARISA_ACTION_STATE_2026_10_28.md) |
| Sakuya | `0x004CADB0` | 75,042 (74,937) | 76,336 | 14 | `exact-first-sakuya-action-state` | `8472f081` | [Sakuya](SAKUYA_ACTION_STATE_2026_10_28.md) |
| Alice | `0x004E9F50` | 42,721 (42,718) | 44,072 | 16 | `exact-first-alice-fighter-update` | `2256c156` | [Alice](ALICE_FIGHTER_UPDATE_2026_10_25.md) |
| Patchouli | `0x0050F200` | 54,452 (54,445) | 55,610 | 4 | `exact-first-patchouli-action-state` | `95e4fa05` | [Patchouli](PATCHOULI_ACTION_STATE_2026_10_27.md) |
| Youmu | `0x00530200` | 37,692 | 38,816 | 4 | `gpt-web-youmu-vslot28-full-root` | `7bad1ce8` | [Youmu](YOUMU_ACTION_STATE.md) |
| Remilia | `0x00545090` | 61,962 (61,959) | 63,316 | 16 | `exact-first-remilia-action-state` | `b602cc68` | [Remilia](REMILIA_ACTION_STATE_2026_10_28.md) |
| Yuyuko | `0x0055D850` | 58,619 | 59,672 | 5 | `exact-first-yuyuko-action-state` | `bd4e8f26` | [Yuyuko](YUYUKO_ACTION_STATE_2026_10_28.md) |
| Yukari | `0x0057B030` | 57,042 | 58,248 | 9 | `exact-first-yukari-action-state` | `488f575e` | [Yukari](YUKARI_ACTION_STATE_2026_10_28.md) |
| Suika | `0x00598990` | 79,435 (79,426) | 81,124 | 20 | `exact-first-suika-action-state` | `60926b84` | [Suika](SUIKA_ACTION_STATE_2026_10_28.md) |
| Udonge | `0x005BFD50` | 66,787 | 67,964 | 7 | `exact-first-udonge-action-state` | `20c38b34` | [Udonge](UDONGE_ACTION_STATE_2026_10_28.md) |
| Komachi | `0x005E20E0` | 63,993 | 65,176 | 7 | `exact-first-komachi-action-state` | `6cedde2f` | [Komachi](KOMACHI_ACTION_STATE_2026_10_28.md) |
| Aya | `0x00602250` | 65,601 | 66,704 | 7 | `exact-first-aya-action-state` | `c640faf9` | [Aya](AYA_EVIDENCE.md) |
| Iku | `0x00620920` | 59,038 | 60,194 | 3 | `gpt-web-iku-action-state` | `ee6a5e7f` | [Iku](IKU_ACTION_STATE.md) |
| Tenshi | `0x0063D3E0` | 47,784 (47,777) | 48,968 | 6 | `exact-first-tenshi-action-state` | `6d5aca6d` | [Tenshi](TENSHI_ACTION_STATE_2026_10_27.md) |

All reusable compiler rules and iteration tooling for giant switch roots live in
[GIANT_ACTION_ROOT_PLAYBOOK.md](GIANT_ACTION_ROOT_PLAYBOOK.md) and
[VC8_SOURCE_SHAPE_PATTERNS.md](VC8_SOURCE_SHAPE_PATTERNS.md).

## Recent Object `+0x28` update root checkpoints (nonexact, no exact credit)

- **AliceObject `0x004FCAB0`** (`gpt-web-alice-object-vslot28-full-root`, commit
  `f795970a`): clean typed view [AliceObjectUpdate.hpp](../src/characters/AliceObjectUpdate.hpp)
  and [AliceObjectUpdate.cpp](../src/characters/AliceObjectUpdate.cpp), exact
  63,248-byte section tail, 63,218/63,248 bytes matching (99.95%), 38/40 exact
  owners, first mismatch `+21,593` (`0x00501F09`). See
  [AliceObject note](ALICE_OBJECT_UPDATE_2026_10_28.md).
- **AyaObject `0x0061A290`** (`gpt-web-aya-object-vslot28-full-root`): typed
  `AnimationSpriteState` BGRA fields and `unsigned char` direction on
  `0x00435240` lifted [AyaObjectActionState.cpp](../src/characters/AyaObjectActionState.cpp)
  from 3/34 to **18/34** exact owners (28/34 at `+0` byte delta; remaining
  `+196 B` is `actions:861` not cascading `TryTailMerge` into `actions:826` in
  the full 34-case switch). See [Aya evidence](AYA_EVIDENCE.md) and the new
  [Object `+0x28` playbook section](GIANT_ACTION_ROOT_PLAYBOOK.md#7-roster-object-0x28-update-roots-reusable-workflow--lessons).

## Next useful action

Choose the next high-value target cluster from the canonical ledgers and verify
each function with strict zero-difference comparison before granting exact
credit:

- **Roster Object `+0x28` update roots** (e.g. Reimu `0x00496540`, Youmu
  `0x0053CEA0`, Sakuya, Marisa, Remilia, plus closing the parked `AliceObject`
  `0x004FCAB0` / `AyaObject` `0x0061A290` `c2.dll` residuals) — follow
  [Playbook Section 7](GIANT_ACTION_ROOT_PLAYBOOK.md#7-roster-object-0x28-update-roots-reusable-workflow--lessons)
  and [Section 8](GIANT_ACTION_ROOT_PLAYBOOK.md#8-roster-object-0x3c-action-entry-roots-1212-exact--reusable-checklist).
- **Remaining Fighter input-policy (`+0x50`) and control roots** (check for raw
  `char *` offset macros and out-of-order/goto cases per
  [VC8_SOURCE_SHAPE_PATTERNS.md](VC8_SOURCE_SHAPE_PATTERNS.md)).
- **Remaining scene, UI, audio, and LTCG clusters** (see parked residuals in
  [VC8_SOURCE_SHAPE_PATTERNS.md](VC8_SOURCE_SHAPE_PATTERNS.md#parked-residuals-tried-still-nonexact)
  and open private contexts in [ARTIFACTS.md](ARTIFACTS.md#private-inputs-still-in-use)).
