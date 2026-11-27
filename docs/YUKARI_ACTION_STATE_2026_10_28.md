# Yukari action-state root `0x0057B030`

## Canonical exact match (2026-11-27)

`Yukari_dispatch_action_state_vslot28` (`0x0057B030`) is canonically exact under
VC8 SP1 `/O2 /GS- /GR /EHsc /MT` (`exact-first-yukari-action-state`) against JP
TH10.5 v1.06a SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`. This
completes all 15 Fighter primary vtable `+0x28` action-state roots.

- Callable code `[0x0057B030, 0x00588F02)`: **57,042 / 57,042** bytes exact
  (14,501 reachable instructions, zero unreachable alignment bytes, 140 RETs,
  SHA-256 `7caa43b9c69087875de1d8db150434733ad7b8a0fbd0d7bd245ee288f3db5db3`).
- Complete nine-table switch payload `[0x0057B030, 0x005893B8)`: **58,248 / 58,248**
  bytes exact (four sparse action tables `low`/`mid`/`high`/`special` with
  44/27/47/6 destinations plus five four-entry difficulty tables in `710`,
  `720`, `730`, `740`, `741`; 144 destination words, 623 index bytes, 7
  alignment bytes, SHA-256
  `8c76f4df41ea9627a161193cf132671508311cd6e04717a4314a7cb2390682af`).
- Relocations: all **1,769** agree (889 REL32 calls across 32 targets and 880
  DIR32 fields). Owner audit: **122/122** `instruction_edge_identical_owners`.

Reproduce:

```bash
WINEDEBUG=-all DISPLAY= WAYLAND_DISPLAY= scripts/repo-python scripts/build.py --unit exact-first-yukari-action-state --compare --json
scripts/repo-python scripts/audit-giant-action-owners.py --unit exact-first-yukari-action-state yukari-vslot28 build/match-units/ExactFirst_YukariActionState.obj --json
```

Private reports: `build/yukari-root-work/{canonical,owners}.json`.

### Key source-shape recoveries that closed the root

- **Typed checked receiver**: replaced `at<T>()` offset casts in
  [YukariActionState.hpp](../src/characters/YukariActionState.hpp) and
  [YukariActionState.cpp](../src/characters/YukariActionState.cpp) with checked
  typed members (`offsetof` static assertions), `signed char` facing on `spawn`,
  `unsigned char` facing on `effect`, member `dispatch_character_wave_handle`,
  and `+0x04` `YukariActionScratch::reset`.
- **Exact comparisons and arithmetic**: `--word_730 < 0` in `73`/`88`,
  `word_730 * 0.0025f` / `-word_732 * 0.0025f` in `89`, `field_6b8 < 0` in
  `200`, `sequence_index_13e < 3` in `203`, `frame_index_140 > 4` in `305`,
  `double a = field_740 * 5.0; ... a + (field_744 - 20.0) + n * 10.0 - 10.0` in
  `402`, duplicated `y_f0 = yukari_surface(this)` in both `facing_104 == 1`
  arms of `201`, `p[2] = 4.0f; p[1] = 0.25f;` in `launch826`/`launch910`,
  descending `case 3..0` order in `710`/`730`/`741`, `alpha <= 250` saturation
  in `750`, and `for (int i = 0; i < count; ++i)` in `burst910` (scheduling
  `word_738 = 1` before loop-counter setup).
- **VC8 `c2.dll:0x10B14E2A` `CONST(0) -> EBP` / `CONST(1) -> EBX` coloring**:
  tracing `c2.dll:0x10B14E2A` showed `CONST(6) -> EBP` and `CONST(4) -> EBX`
  split both `CONST(0)` and `CONST(1)`. Writing `case 2:` and `case 1:`
  separately in `action 720`'s difficulty switch gave `CONST(70)` `score = 1`
  (`lea ebp, [eax+0xa]`), cutting the post-split `CONST(0)` vs `CONST(1)`
  priority gap from 93 points to 6 (`-1458` vs `-1452`); unnesting the repeated
  `!frame_timer_142` frame guards into sequential
  `if (!frame_timer_142 && ...)` checks added `+8` points with zero extra code
  bytes, flipping `CONST(0)` ahead of `CONST(1)` so `0` takes `EBP` and `1`
  takes `EBX`. Splitting `entry(1)` and `entry(2)` into two `if` guards in
  `action 404` restored its shared `0x0057F6B5` `set_action_and_finalize(9)`
  tail.

## Preserved target semantics

- Partial checked receiver (`YukariActionStateView`) is pointer-only; full
  `Fighter` class layout, TU boundaries and several field meanings remain open.
- Prelude `998` emits paired `+10`/`-10` one-float packets at `(80, 130)`,
  `(60, 80)`, `(75, 140)` with `word_7a2 = 100`. Walk speed is `4.5`; normal
  jump `12.5`/`0.55`; high jumps use `0.65` gravity.
- `197..199` keep independent `981` packet lifetimes (`199` makes two checked
  deck calls at `+0x55C`); `201`/`224` landing clears vertical speed/gravity
  without clearing `velocity_x_f4`; `201`'s frame-70 spawn negates the low
  facing byte for direction while sign-extending it for `facing * 200`.
- `214` has five/six release states, turn `1`/`3`, acceleration `0.3`,
  unordered `!(peerX > selfX)` reversal checks in release sequences `3`/`4`,
  and captures unsigned effect facing before sine while reloading signed facing
  after cosine.
- `522`/`523` retain native `atan`/`sqrt` constants `37825`, `65025`, `128500`,
  `190800` and float speed temporaries; `565`/`566` distinguish time-counter vs
  frame-timer control; `720` reads `owner_168` Y (not `peer_170` Y); `710`
  initializes packet fields `1`/`2` outside each loop; `740` leaves its
  difficulty local uninitialized outside `0..3` as in the target binary.
- `656` loads vslot `+0x0C` and argument `5` before jumping into the shared
  call at `0x0057B867`; shower `856` (`606`/`656`) uses float `2^32` unsigned
  conversions and reloads signed facing after `RNG(300)`.
