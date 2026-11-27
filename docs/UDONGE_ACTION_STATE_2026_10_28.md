# Udonge action-state root (`0x005BFD50`), JP 1.06a

## Status and scope

`exact-first-udonge-action-state` is **canonical exact** from the
character-scoped [source](../src/characters/UdongeActionState.cpp) and
[checked receiver](../src/characters/UdongeActionState.hpp), under VC8 SP1
`/O2 /GS- /GR /EHsc /MT`.

- All **66,787 callable code bytes** (`[0x005BFD50, 0x005D0233)`) and the
  complete **67,964-byte** seven-table switch payload (`[0x005BFD50, 0x005D06CC)`)
  match with zero byte differences.
- All **1,878** COFF relocations agree: 902 `REL32` calls across 29 targets and
  976 `DIR32` fields. The 1,177 metadata bytes contain 7 switch tables, 121
  destination words, 688 index bytes and 5 alignment bytes (`90`, `90`, `90`,
  `8bff`).
- The owner audit is **104/104** (103 unique switch destinations plus `entry`).
  Raw CFG reaches all 16,886 instructions / 66,787 authored bytes with zero
  internal alignment holes.
- Code SHA-256: `ab78b849a55e354b0495d31cc47568b41040607644445b82c68e980337b45c0f`.
- Payload SHA-256: `8f59f23a42efe00b3778ad1212e16f668c76b30296a98bdb60766ce46fb714c9`.

Reproduce:

```bash
WINEDEBUG=-all DISPLAY= WAYLAND_DISPLAY= scripts/repo-python scripts/build.py --unit exact-first-udonge-action-state --compare --json
scripts/repo-python scripts/audit-giant-action-owners.py --unit exact-first-udonge-action-state udonge-vslot28 build/match-units/ExactFirst_UdongeActionState.obj --json
```

Private reports: `build/udonge-root-work/{canonical,owners}.json`.

### Key source-shape fixes for canonical equality

- **Checked typed receiver and ABI widths**: replaced `at<T>` offset casts and
  the 9 split `.inc` fragments with a self-contained typed
  `UdongeActionStateView` (with compile-time `offsetof` checks), `signed char`
  direction on `spawn` (`0x00465190`), `unsigned char` direction on `effect`
  (`0x00435240`), and `float` return types on `udonge_sine` / `udonge_cosine`.
- **Inlining early-return helpers and post-switch `advance()`**: moving the
  shared `advance()` tail after `switch (action_id_13c)` for `0, 2, 4, 5` and
  inlining early-return helpers (`normal_jump`, `recovery_jump`, `high_jump`,
  `update_beam_radius`, `shot800`, `shot801`, `shot816`, etc.) restores the
  native `0x480` stack frame, `L_ret` predecessor order, all 103 unique switch
  destinations, and every tail-merge.
- **`cases 525..528` cone check (`peer_in_cone`)**: fixed a semantic bug in the
  retained 1.06 scaffold where the hit packet wrote `p[1] = 1.0f` instead of
  the target's `p[2] = 1.0f` (`fstp [esp + 0x204]`), and replaced the `peer()`
  / `facing()` inline wrappers with direct `fighter_170->` / `facing_104`
  accesses so VC8 preserves `edi` across the first `udonge_tangent` call and
  reloads `fighter_170` after the second call.
- **Entry alpha scaling and `565..568` x87 operand order**: reading
  `float scale = field_7a8; float alpha = scale * word_7a6; byte_113 = static_cast<unsigned char>(alpha);`
  in the `word_174 > 0` prelude emits target `fld [esi+0x7a8]; fild [esp+0x18]; fnstcw; movzx; fmulp st(1)`
  while keeping `fld [esi+0x7b0]; fadd [esi+0x73c]` in `expand_cone` (`525..528`,
  `726`) and `fld [esi+0x73c]; fadd [esi+0x740]` in `565..568`.

## Preserved target semantics

- Partial checked receiver (`UdongeActionStateView`) is pointer-only; full
  `Fighter` class layout, TU boundaries and several field meanings remain open.
- Sparse tables have 32/34/39 destinations (`9`/`11`, `209`/`221`, `210`/`222`
  share owners); direct actions `300`, `520`, `795`, `797`, `798` dispatch
  outside those tables.
- `506` has a single `811` spawn followed by an escaped-packet `p[2] = 4` store
  and wave `15`; spell flash writes `word_48a = 40` directly; `565..568` beam
  pairs reverse direction (not layer) and keep every paired packet reload and
  final `p[2] = 5` store.
- `602`/`652` use three separately owned four-float orbit packets; `606`/`607`
  reuse one three-float packet per action with ring layer `1` for ordered
  `0 <= angle <= 180`, else `-1`; `609` preserves truncated-short velocity
  capture, action `97` landing and distinct `859` packet types.
- Cone checks capture peer Y as QWORD before each `cdecl float(float)` tangent
  call (`0x00406430`, separately exact 69/69) and reload `fighter_170`
  afterward; `214` flight exits use ordered `>` comparisons and capture
  unsigned direction before sine while reloading signed facing after cosine.
