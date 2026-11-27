# Suika action-state root (`0x00598990`), JP 1.06a

## Status and scope

`exact-first-suika-action-state` is **canonical exact** from the
character-scoped [source](../src/characters/SuikaActionState.cpp) and
[checked receiver](../src/characters/SuikaActionState.hpp), under VC8 SP1
`/O2 /GS- /GR /EHsc /MT`.

- All **79,435 physical callable bytes** (`[0x00598990, 0x005ABFDB)`) and the
  complete **81,124-byte** twenty-table switch payload (`[0x00598990, 0x005AC674)`)
  match with zero byte differences.
- All **2,553** COFF relocations agree: 1,081 `REL32` calls across 37 targets
  and 1,472 `DIR32` fields. The 1,689 metadata bytes contain 20 switch tables,
  239 destination words, 726 index bytes and 7 alignment bytes (`90`, `90`, `90`,
  `8bff`, `8bff`).
- The owner audit is **114/114** (113 unique switch destinations plus `entry`).
  Raw CFG reaches 20,321 of 20,324 decoded instructions (**79,426 authored
  bytes**); three unreachable 3-byte VC8 loop-alignment `lea ecx, [ecx]`
  (`8d4900`) instructions at `0x005A09FD`, `0x005A5A5D` and `0x005A97CD` (9
  bytes total) are compared and excluded from authored progress in
  `config/function-byte-exclusions.toml`.
- Code SHA-256: `a1006a208fb62813cec2081c250f5825e88011ce834cff9e49e5d15d0164feb9`.
- Payload SHA-256: `adb2bc7f9936c61683a9028edb19fb3625c2b79c51890891995e6271d95c426c`.

Reproduce:

```bash
WINEDEBUG=-all DISPLAY= WAYLAND_DISPLAY= scripts/repo-python scripts/build.py --unit exact-first-suika-action-state --compare --json
scripts/repo-python scripts/audit-giant-action-owners.py --unit exact-first-suika-action-state suika-vslot28 build/match-units/ExactFirst_SuikaActionState.obj --json
```

Private reports: `build/suika-root-work/{canonical,owners}.json`.

### Key source-shape fixes for canonical equality

- **Checked typed receiver and ABI widths**: replaced `at<T>` casts and the 11
  split `.inc` fragments with a self-contained typed `SuikaActionStateView`
  (with compile-time `offsetof` checks), `signed char` direction on `spawn`
  (`0x00465190`), `unsigned char` direction on `effect` (`0x00435240`), and
  direct member declarations on `SuikaActionStateView` for
  `dispatch_character_wave_handle` (`0x0045C030`) and `forward_hit_quantity`
  (`0x0045C060`).
- **Semantic fixes against native instructions**: `case 412` resets to action
  `2` (not `0`); `cases 500`/`501` use `if (word_732 == 1) ... else ...`,
  restoring the `501 -> 500` tail-merge and clearing all 5 direct call deltas;
  fragment loops assign `word_730 = -1` / `1` and pass
  `static_cast<unsigned char>(word_730)`; `ground_face()` compares
  `x_ec > fighter_170->x_ec` and `x_ec < fighter_170->x_ec` directly.
- **Giant `605`/`730` and `603`/`608`/`710..751` control flow**: writing the
  numerical `case 6..14` surface checks inline (no shared helper), replacing the
  `button_active` helper with direct `if`/`else if`/`else` ladders (matching
  `ja` + reverse-order tail blocks), splitting `if (entry(k))` guards, and
  restoring native switch case ordering reproduce all 20 switch tables and all
  3 internal `lea ecx, [ecx]` loop alignments.
- **`cases 525`/`526` skill-level burst loops**: separating the second loop's
  `float m = 0.0f` from loop 1's `float n` and guarding the `do/while (m < count)`
  with `float limit = static_cast<float>(byte_609 + 5.0); float m = 0.0f; double count = limit; if (0.0 < limit)`
  keeps `double count` at `[esp+0x18..0x1f]` (fixing global `[esp+0x18]`/
  `[esp+0x1c]` slot allocation across the function) and schedules
  `fstp dword ptr [esp+0x20]` (`m = 0.0f`) at the exact native slot between
  `fstp dword ptr [esp+0x10]` and `fld dword ptr [esp+0x10]`.

## Preserved target semantics

- Partial checked receiver (`SuikaActionStateView`) is pointer-only; full
  `Fighter` class layout, TU boundaries and several field meanings remain open.
- Direct actions `300` and `560` dispatch outside the three sparse action
  tables (33/50/31 destinations); shared helper `0x00435160` receives `this + 4`.
- `547`/`562`/`708` retain narrowed velocity followed by QWORD predicted-Y
  captures; `605` runs the secondary cycle before its sequence window; grab
  `608` preserves peer action changes, live receiver reloads, vertical pose
  product order, and caller-owned packet reuse across repeated requests; `740`
  retains duplicate native gravity passes and cosine branch ordering.
- Spawn direction arithmetic uses signed byte values while spawn carriers
  preserve unsigned/signed byte widths (including layer `255` / `-1`).
