# Patchouli action-state root `0x0050F200`

## Canonical exact match (2026-11-26)

`Patchouli_dispatch_action_state_vslot28` (`0x0050F200`) is canonically exact
under VC8 SP1 `/O2 /GS- /GR /EHsc /MT` (`exact-first-patchouli-action-state`)
from the character-scoped [source](../src/characters/PatchouliActionState.cpp)
and [checked receiver](../src/characters/PatchouliActionState.hpp) against JP
TH10.5 v1.06a SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.

- Callable code `[0x0050F200, 0x0051C6B4)`: **54,452 physical bytes** (SHA-256
  `41430c00c554e7dc169692c56b41fd43f5ef1204700cb092bab6420f327ed944`). Raw CFG
  reaches 14,067 of 14,068 decoded instructions (**54,445 authored bytes**);
  seven unreachable loop-alignment bytes at `0x0050F8A9..0x0050F8AF` are
  compared and excluded from authored progress in
  `config/function-byte-exclusions.toml`.
- Complete four-table switch payload `[0x0050F200, 0x0051CB3A)`: **55,610 bytes**
  (leading `orbit710` four-entry difficulty table plus three sparse action
  tables with 32/43/32 destinations; 111 destination words, 711 index bytes, 3
  alignment bytes; SHA-256
  `d4d73f175e4f8b37667f04472df8c5db8cbec0ca20414d4107df08a007779043`).
- Relocations: all **1,651** agree (807 REL32 calls across 29 targets and 844
  DIR32 fields). Owner audit: **106/106** `instruction_edge_identical_owners`.

Reproduce:

```bash
WINEDEBUG=-all DISPLAY= WAYLAND_DISPLAY= scripts/repo-python scripts/build.py --unit exact-first-patchouli-action-state --compare --json
scripts/repo-python scripts/audit-giant-action-owners.py --unit exact-first-patchouli-action-state patchouli-vslot28 build/match-units/ExactFirst_PatchouliActionState.obj --json
```

Private reports: `build/patchouli-root-work-codex/{canonical,owners}.json`.

### Key source-shape recoveries that closed the root

1. **Carried x87 `0.0f` in `201`/`224`**: Separating the two
   `if (sequence_index_13e == 2)` guards (instead of nesting the velocity
   update inside the `landing()` guard) lets the prefix `0.0f` live range flow
   into both cases. Each adds one `Enterload` (`-2`) and two uses (`+4`),
   raising general `Color` (`c2.dll:0x10B0CF40`) interval spill cost from `0` to
   `+4` so VC8 keeps `0.0f` in `st(0)` across the switch (see
   [VC8_SOURCE_SHAPE_PATTERNS.md](VC8_SOURCE_SHAPE_PATTERNS.md#pinned-c2-x87-liveness-investigation-2026-11-26)).
2. **Distinct `210`/`222` owners**: Writing `case 209:`, `case 212:` and
   `case 221:` as separate cases matches VC8's 17-iteration `FgDoLateFlowOpts`
   (`0x10B2C950`) merge order, merging `209`/`212`/`221` while leaving `210` and
   `222` distinct at their native 255-byte spans (`0x00510D4A` and `0x005119C2`).
3. **Local branch, timer and operand shapes**: Reversing branch polarity in
   `10`, `200`, `500..503` (`byte_604 >= 3`) and `721` (`x_ec < 640.0f`,
   `x_ec > field_74c`); `< 1` in `414`/`567`/`568`; unsigned `> 0` on
   `field_6bc`/`6c0`/`6c4` in `545`/`546`; float `field_744 <= limit` in
   `580`/`581`; direct `(field_6c8 == 0 && word_736 > 10) || word_482 <= 0` in
   `214`; separate `entry(...)` guards in `214`/`415`; outer sequence guard with
   repeated timer checks in `197`/`198`/`308`/`401`/`406`; and `peer.x > x` /
   `peer.x < x` in the prefix facing check.

## Preserved target semantics

- Partial checked receiver (`PatchouliActionStateView`) is pointer-only; full
  `Fighter` class layout, TU boundaries and several field meanings remain open.
- Buff `7A4` reads `owner_168` and `peer_170` health (not self health); skill
  `606` uses signed-byte arithmetic; action `710` emits its orbit before the
  hitstop guard.
- All 40 `0x005F9310` crossed-surface consumers test `AL`; all 47 unsigned
  conversions use the float `2^32` bias. Effects take `unsigned char` direction
  while coordinate offsets use signed facing; ring `820` forwards the low byte
  of `word_730` (including `255` for `-1`).
- Surface rings in `540`/`541`/`797`/`798` spill `sine * 75 * 0.25` as a double
  before the surface query; `599` sign-extends `DX` at `0x00519FE6` before
  subtracting from `-20`; `602` uses positive sine and negative cosine; `603`
  request `853` adds `20` in world X.
- `561` and `798` skip emission/landing on unordered float comparisons; `581`
  has four independent level checks (`<= 3`, `<= 2`, `<= 0`, `>= 4`) with no
  invented fallback.
