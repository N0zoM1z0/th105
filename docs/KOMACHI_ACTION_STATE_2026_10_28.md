# Komachi action-state root (`0x005E20E0`), JP 1.06a

## Status and scope

`exact-first-komachi-action-state` is **canonical exact** from the
character-scoped [source](../src/characters/KomachiActionState.cpp) and
[checked receiver](../src/characters/KomachiActionState.hpp), under VC8 SP1
`/O2 /GS- /GR /EHsc /MT`.

- All **63,993 callable code bytes** (`[0x005E20E0, 0x005F1AD9)`) and the
  complete **65,176-byte** seven-table switch payload (`[0x005E20E0, 0x005F1F78)`)
  match with zero byte differences.
- All **1,864** COFF relocations agree: 915 `REL32` calls across 30 targets and
  949 `DIR32` fields. The 1,183 metadata bytes contain 7 switch tables (a
  two-destination card-expiration gate, three sparse action tables `34`/`41`/`31`,
  and three four-entry match-identifier tables), 120 destination words, 692
  index bytes and 11 alignment bytes.
- The owner audit is **107/107** (106 unique switch destinations plus `entry`).
  Raw CFG reaches all 16,310 instructions / 63,993 authored bytes with zero
  internal alignment holes.
- Code SHA-256: `bb737abb720d627a985ae38f3b3f11f0cabf31b7ad0b7f89ab7a6f809ea9b8bd`.
- Payload SHA-256: `20d83eff7214346536177a1391fa993ccf62081c1b9ebc5aa048edc005094204`.

Reproduce:

```bash
WINEDEBUG=-all DISPLAY= WAYLAND_DISPLAY= scripts/repo-python scripts/build.py --unit exact-first-komachi-action-state --compare --json
scripts/repo-python scripts/audit-giant-action-owners.py --unit exact-first-komachi-action-state komachi-vslot28 build/match-units/ExactFirst_KomachiActionState.obj --json
```

Private reports: `build/komachi-root-work/{canonical,owners}.json`.

### Key source-shape fixes for canonical equality

- **Byte direction parameter on `effect` (`0x00435240`)**: declaring the 4th
  argument as `unsigned char` removes redundant `movsx` casts in `201`/`203`/
  `224`/`225` and matches the `movzx` argument preparation used by `spawn`.
- **Preventing `facing_104` hoisting across trig calls**: reading `facing_104`
  directly (instead of through an `int` getter) in `emit801`, `swap820`, `730`
  and `214`, plus keeping `float dx` in `aim()`/`aim_short()`, restores
  `fild; fmulp` and exact per-call `movsx`/`movzx` reloads across `400..416`,
  `541..543`, `560..567`, `602` and `214`.
- **Inlining early-return helpers and post-switch `advance()`**: moving the
  shared `advance()` tail after `switch (action_id_13c)` for `0, 2, 4, 5, 9`
  and inlining `high_jump` (`208..212`), `air_normal_land` (`306..309`),
  `air_shot_landing` (`414..416`), `air811` (`507..508`), `swap820`
  (`540..543`) and `ring902` (`730`) restores all 106 unique switch
  destinations and every native tail-merge.
- **`case 730` (`ring902`) frame size and LIFO stack-slot packing**: writing
  `coord = static_cast<float>(n * 45.0 + base_angle); packet[0] = static_cast<float>(n * 45.0 + base_angle + jitter + 180.0);`
  without an intermediate `double angle` local prevents VC8 LICM from spilling
  `jitter + 180.0` to a `qword` temporary (restoring the `0x490` frame) while
  avoiding `fstp; fld` rounding. Hoisting `float coord;` before `switch
  (g_match_identifier)` with per-loop `for (float n = 0.0f; ...)` restores
  VC8's descending-weight LIFO slot packing (`esp+0x10` vs `esp+0x28`) across
  all 15 affected owners.
- **`case 405` nested air-landing guard**: writing `if (sequence_index_13e < 2)
  { if (static_cast<unsigned char>(crossed())) { ... return; } }` reorders the
  merge-block predecessors in VC8's `InsertAdditionalSplits`, restoring the
  local `mov ebx, 1` hoist at `+0x47FB` and eliminating the final 2-byte diff.

## Preserved target semantics

- Partial checked receiver (`KomachiActionStateView`) is pointer-only; full
  `Fighter` class layout, TU boundaries and several field meanings remain open.
- Direct actions `300`, `540`, `795`, `797`, `798` dispatch outside the three
  sparse action tables; the three four-entry match-identifier switches are tied
  to the battle setup writer in
  [GIANT_ROOT_REVIEW_2026_11_23.md](GIANT_ROOT_REVIEW_2026_11_23.md#what-the-byte-check-covers).
- All 40 crossed-surface and 24 on-surface consumers test `AL`; `562`/`602`/`605`
  use signed counters and `520`/`521` use signed level gates; `214` uses
  unordered `!(peer_x > self_x)` flight exits.

## Checked motion fields, 2026-11-23

`AnimationSequenceObjectView` exposes five checked floats at `+0xEC`, `+0xF0`,
`+0xF4`, `+0xF8` and `+0x100` (position, velocity and vertical acceleration),
also present in the exact Komachi initializer at `0x005F6700`. The final exact
`KomachiActionState.hpp` pins the full character-scoped receiver offsets with
compile-time assertions.

## Shared high-jump landing and ring frame, 2026-11-23

In `208..212`, all crossing paths converge on `set_action(10)` inside `212`
(`0x005E3837`) while `209`/`212`/`221` keep their distinct native switch entries
once inlined directly into the action switch. In `730`, removing the
intermediate `double` local prevented VC8 LICM from spilling `jitter + 180.0`
and recovered the native `0x490` frame and `esp+0x10`/`esp+0x28` slot packing.
