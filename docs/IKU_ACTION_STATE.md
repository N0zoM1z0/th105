# Iku action state `0x00620920` (exact)

`Iku_dispatch_action_state_vslot28` spans `[0x00620920, 0x0062EFBE)` (**59,038**
callable bytes; 15,132 instructions, 131 returns, 109/109 exact owners) and
complete switch envelope `[0x00620920, 0x0062F442)` (**60,194** bytes; three
compact byte-index switch tables with 33/42/35 entries, 712 index bytes,
original `8bff`/`90` alignment padding, and 1,770 relocations across 32 direct
call targets).

- **Status**: **100% canonically exact** under VC8 SP1 `/O2 /GS- /GR /EHsc /MT`
  in unit `gpt-web-iku-action-state`
  ([IkuActionState.cpp](../src/characters/IkuActionState.cpp)).
- **Callable SHA-256**: `abc831c6ccd95986bed811694f532ad8c8b92cb49702a7f6ce4de100b8a73dea`
- **Envelope SHA-256**: `d252f0bb5b25a4f07b03d35c6c258af3b374e236a39f03c86cdd6caee32cf98c`

## Key source shapes proven on this root

- Standalone typed `IkuActionStateView` and `IkuPeerView` layouts (with
  compile-time `offsetof` assertions) replace `byte_at`/`float_at` casts,
  removing aliasing barriers.
- Post-switch `advance_frame_and_dispatch()` reached via `break;` in
  `0, 2, 4, 5, 9, 740, 781` places the shared advance tail on `case 781`
  (`0x0062EACB`).
- Direct `unsigned char` (`emit_fighter_effect_433cc0`) and `signed char`
  (`spawn_owned_object_via_manager`) direction parameters plus `if/else` spawn
  branches for `1`/`-1` ring variants match target call counts and tail merges.
- Inlining `case 214` and `cases 400..406` directly into the `switch` removes
  early `return;` hops inside `__forceinline` helpers that reordered `L_ret`
  predecessors in `c2.dll:0x10B307E0` (`TailMerge`).
- Nested `if (frame_timer_142 == 0) { if (frame_index_140 == 14) ... }` in
  `404`/`406` restores `push 1` and upstream modulo-16 alignment so
  `c2.dll:0x10C56F50` (`WidenBranches`) preserves all three `disp = 116..121`
  6-byte `0F 85` forward branches (`603`, `740`, `797`).
- Integer gates use exact target literals (`>= 15`, `40`/`11`, `>= 4`); action
  `730` uses `switch (g_match_identifier)`; action `780` uses
  `+ static_cast<float>(word_738 + 100)` (`fiadd`); action `781` uses
  `1 - 2 * (static_cast<unsigned>(selector_random_roll(100)) < 50)` and
  `double step_y = field_73c`.

See [VC8_SOURCE_SHAPE_PATTERNS.md](VC8_SOURCE_SHAPE_PATTERNS.md) and
[GIANT_ACTION_ROOT_PLAYBOOK.md](GIANT_ACTION_ROOT_PLAYBOOK.md) for the reusable
compiler rules.
