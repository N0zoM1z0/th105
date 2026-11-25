# TH10.5 reconstruction handoff

Target executable: original Japanese TH10.5 v1.06a, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Follow [AGENTS.md](../AGENTS.md), [the shared runtime](SHARED_TOOLS.md) and
[the reconstruction workflow](RE_WORKFLOW.md). Keep this game's Wine prefix,
analysis projects and private worktrees; run compiler and analyzer jobs
serially.

## Completed: Iku Fighter `+0x28` action-state root (`0x00620920`)

`Iku_dispatch_action_state_vslot28` at `0x00620920` is now **100% canonically
exact** under VC8 SP1 `/O2 /GS- /GR /EHsc /MT` in match unit
`gpt-web-iku-action-state`:

- **Source**: [IkuActionState.cpp](../src/characters/IkuActionState.cpp)
  (standalone typed `IkuActionStateView` and `IkuPeerView` layouts with
  compile-time `offsetof` assertions; zero `goto` labels).
- **Exact envelope**: 59,038 callable bytes (15,132 instructions, 109/109
  instruction/edge-identical owners), 1,156 metadata bytes (3 compact
  byte-index switch tables: 33/42/35 entries, 712 index bytes, and original
  `8bff`/`90` alignment padding), total 60,194 bytes
  (`0x00620920..0x0062F442`), 1,770 relocations (865 direct calls across 32
  targets), zero byte differences.
- **Canonical SHA-256**: callable
  `abc831c6ccd95986bed811694f532ad8c8b92cb49702a7f6ce4de100b8a73dea`; complete
  60,194-byte switch envelope
  `d252f0bb5b25a4f07b03d35c6c258af3b374e236a39f03c86cdd6caee32cf98c`.
- **Verification**:
  ```bash
  WINEDEBUG=-all DISPLAY= WAYLAND_DISPLAY= scripts/repo-python scripts/build.py --unit gpt-web-iku-action-state --compare --json
  scripts/repo-python scripts/audit-giant-action-owners.py --unit gpt-web-iku-action-state iku-vslot28 build/match-units/GptWeb_IkuActionState.obj
  scripts/repo-python scripts/check-match-literals.py --require-target
  ```
- **Key VC8 `c2.dll` findings** (recorded in
  [VC8_SOURCE_SHAPE_PATTERNS.md](VC8_SOURCE_SHAPE_PATTERNS.md)):
  1. Standalone typed `IkuActionStateView`/`IkuPeerView` members replace
     `byte_at`/`float_at` casts, removing aliasing barriers and restoring
     target scheduling.
  2. Post-switch `advance_frame_and_dispatch()` with `break;` in `0, 2, 4, 5,
     9, 740, 781` places the shared advance tail in `case 781` (`0x62EACB`).
  3. Direct `unsigned char` (`emit_fighter_effect_433cc0`) and `signed char`
     (`spawn_owned_object_via_manager`) direction parameters, plus `if/else`
     spawn branches for the `1`/`-1` ring variants, recover exact call counts
     and tail merges.
  4. Inlining `case 214` and `cases 400..406` directly into the `switch`
     removes early `return;` hops inside `__forceinline` helpers that reordered
     `L_ret` predecessors in `c2.dll:0x10B307E0` (`TailMerge`), simultaneously
     restoring `214 -> 309`, `650 -> 201`, `406/416/417 -> 404`, and `414 -> 9`.
  5. Nested `if (frame_timer_142 == 0) { if (frame_index_140 == 14) ... }` in
     `404`/`406` restores `push 1` (not `push edi`), which restores the
     upstream modulo-16 alignment phase so `c2.dll:0x10C56F50`
     (`WidenBranches`) automatically keeps all three `disp = 116..121` forward
     branches (`603`, `740`, `797`) as 6-byte `0F 85`.
  6. Remaining single-case idioms: `switch (g_match_identifier)` in `730`,
     `+ static_cast<float>(word_738 + 100)` (`fiadd`) in `780`,
     `1 - 2 * (static_cast<unsigned>(selector_random_roll(100)) < 50)` and
     `double step_y = field_73c` in `781`, and removing `adjusted`/`acceleration`
     locals in `797`/`798`.

## Previously completed: Reimu Fighter `+0x28` action-state root (`0x00478FA0`)

`Reimu_dispatch_action_state_vslot28` (`0x00478FA0`, 81,550 callable / 82,924
envelope, 11 switch tables, 2,477 relocations) is 100% canonically exact in
`neon-reimu-action-state-root` (`473165f6`).

## Next useful action

Apply the same single-function exact-reconstruction workflow and VC8 `c2.dll`
patterns to the next roster Fighter `+0x28` action-state root (e.g., Marisa
`0x004A3DF0`, Sakuya, Alice, Patchouli, Youmu, Remilia, Yuyuko, Yukari, Suika,
Reisen, Aya, Komachi, or Tenshi).

## Open notes

- `IkuActionState.cpp` and `ReimuActionStateRoot.cpp` use character-scoped
  typed receiver views rather than a unified cross-character `Fighter` header.
  Any future shared-header unification must re-verify both
  `gpt-web-iku-action-state` and `neon-reimu-action-state-root` for zero
  differences.
- `scripts/probe-iku-action-ltcg.py` is a diagnostic LTCG probe that references
  `gpt-web-iku-action-state`; its old `AnimationSequenceObjectView` helper
  selection is superseded for exact matching now that standalone COFF
  `gpt-web-iku-action-state` is 100% exact.
