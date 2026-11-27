# Udonge action-state root (`0x005BFD50`), JP 1.06a

## Status and scope

`exact-first-udonge-action-state` is **canonical exact** from the
character-scoped [source](../src/characters/UdongeActionState.cpp) and
[checked receiver](../src/characters/UdongeActionState.hpp), under VC8 SP1
`/O2 /GS- /GR /EHsc /MT`.

- All 66,787 callable code bytes (`[0x005BFD50, 0x005D0233)`) and the complete
  67,964-byte seven-table switch payload (`[0x005BFD50, 0x005D06CC)`) match
  with zero byte differences.
- All 1,878 COFF relocations agree: 902 `REL32` calls across 29 targets and
  976 `DIR32` fields. The 1,177 metadata bytes contain 7 switch tables, 121
  destination words, 688 index bytes and 5 alignment bytes (`90`, `90`, `90`,
  `8bff`).
- The owner audit is `104/104` (`103` unique switch destinations plus `entry`).
  Raw CFG reaches all 16,886 instructions / 66,787 authored bytes with zero
  internal alignment holes.
- Code SHA-256: `ab78b849a55e354b0495d31cc47568b41040607644445b82c68e980337b45c0f`.
- Payload SHA-256: `8f59f23a42efe00b3778ad1212e16f668c76b30296a98bdb60766ce46fb714c9`.

Reproduce with:

```bash
WINEDEBUG=-all DISPLAY= WAYLAND_DISPLAY= scripts/repo-python scripts/build.py --unit exact-first-udonge-action-state --compare --json
scripts/repo-python scripts/audit-giant-action-owners.py --unit exact-first-udonge-action-state udonge-vslot28 build/match-units/ExactFirst_UdongeActionState.obj --json
```

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

The dated notes below retain the earlier discovery and code-generation trials.

## Native evidence (2026-10-28 historical note)

The Japanese 1.06a target is hash-attested. Factory IDA metadata, entry,
inventory and mapped-byte samples matched the canonical image. The local MCP
preflight lacked its dependency, and the whole-root native decompiler failed;
these routes were skipped without installing software or repeatedly retrying.
Independently attested Ghidra action slices were diagnostic navigation aids.
Temporary functions and synthetic caller-interface views are not original
ABIs. Transactions rolled back with all nine primary database hashes unchanged.
One invalid action 205 slice and the whole prelude timeout were discarded;
action 205 is a native default, and the prelude was read from raw instructions.

Callable 5BFD50..5D0233 exclusive is 66787 bytes, SHA-256
ab78b849a55e354b0495d31cc47568b41040607644445b82c68e980337b45c0f.
All 16886 decoded instructions and 66787 bytes are reachable, with no unresolved
indirect exits. Seven jump tables resolve. Decoded direct calls:902 sites,
29 targets. A raw E8 byte scan counts 903, including a non-instruction match.
Full metadata ends at 5D06D0:67968 bytes, SHA-256
39932bd962af7d9ed375abf21880c69967ea7f79fc78ff59197b00914c829017.
Native aligned frame is 0x480. Sparse groups are 32/34/39; direct 300,520,795,797,798
are outside those tables. Native 9/11,209/221 and 210/222 share owners.

## Source observations

The pointer-only receiver extends the established animation virtual-slot view.
Helpers are declaration-only and confer no callee implementation credit.
The actual root receives this in ECX; synthetic slice interfaces do not replace
it. Root EBP=-1, CX=0 and EDI=30 were independently read from raw dispatch paths.

- Signed facing arithmetic is separated from unsigned low-byte spawn carriers.
  Negative offsets use native integer subtraction rather than float negation.
- Prelude independent 150..153/154..157/158 checks retain callback-sensitive
  reloads. The 859 periodic packets remain separately owned.
- Native 506 has only one 811 request, then a p2=4 store and wave 15. The apparently
  redundant escaped-packet store is retained, not expanded into a second spawn.
- Spell flash writes S48A=40 directly. It does not call Suika's4776C0 helper.
- 565..568 beam pairs reverse direction, not layer. Every paired packet reload,
  conditional upgrade and the final p2=5 mutation follows the native stores.
- 602/652 have three separately owned four-float orbit packets and float loops.
  Each sine/cosine call rereads p0. Request arguments now express the native
  outgoing preparation before sine, Y rounding before cosine and fresh signed
  facing after cosine. 710's900 orbit uses a different Y association.
- 606/607 reuse one three-float packet per action. Their ring layer is 1 for
  ordered 0<=angle<=180, otherwise-1. Initial 857 and subsequent 856 origins differ.
- 609 preserves the truncated-short velocity times 100 capture, action 97 landing,
  saturation branch, live entry checks and distinct 859 packet types.
- Cone checks capture peer Y as QWORD before each tangent call; the second X
  read uses a fresh peer after the call. A promoted scalar tangent result avoids
  an extra FST 32 while preserving this evaluation order. The tangent ABI remains
  the target-backed cdecl float(float), not a fabricated double-return interface.
  Inlining the second expression prematurely loaded the peer before the call;
  that trial was rejected. The separate 406430 dependency is now canonical
  exact 69/69; see ANGLE_TANGENT_2026_10_28.md. This does not credit the root.

## Diagnostics and remaining uncertainty

The emitted candidate retains all 32/34/39 sparse physical groups without
splitting a target group. Per-action direct-call and floating arithmetic-site
counts agree across all 110 labels. Action 406 still has one fewer virtual site:
its two native entry 1/entry2 reset-return owners merge in the emitted candidate.
Whole-root static call totals also differ due to shared tails. These are
omission diagnostics, not semantic or exactness proof.

All 92 caller-owned packet homes resolve with no unknown spawn payload sites.
All 41 crossed-surface and 8 on-surface result consumers test AL. The current
candidate frame is 0x488, eight bytes larger than native 0x480. Its home-offset
set is shifted by 8, and ten actions additionally have different per-action
home ownership even after subtracting that shift. Packet contents, reader
contracts, callback lifetimes, compiler temporary storage and TU/LTCG ownership
remain under review. No equivalence of packet ownership is claimed.

No assembly, copied target instructions, inert locals, fake ABI or padding
is used to force the comparison. Positional mismatch counts are not completion
percentages.

## Reproduction and current result

Only this new unit was compiled. Existing accepted receipts are unchanged.

taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py --unit exact-first-udonge-action-state --compare --json
    scripts/repo-python scripts/compare-giant-action-switches.py udonge-vslot28 build/match-units/ExactFirst_UdongeActionState.obj --json

Current complete candidate 67520 versus native 67968. First mismatch+8 at 5BFD58;
full unmasked differences 63788 including length. Canonical candidate SHA-256:
bcb914be8c7ca6ddf73e2dd8e85235f6340c3467628aec6d069117b2f3d27c30.

Five absent native-backed literal bindings were appended without changing
existing bindings. No shared accepted source or header was changed. Default CI
checks exact tooling and tracking without rebuilding the entire native corpus.

Private action slices, raw instructions and independent analysis attestations remain
in the same bounded build directory. The checked-in candidate is authoritative;
further refinements must be replayed against the complete canonical root.

## Action 214 facing comparisons, 2026-11-04

Native compares peer and own X in four flight-exit paths at
`0x005C1DE0`, `0x005C1E1F`, `0x005C1E82` and `0x005C1ECD`. Its status
checks flip facing only on the corresponding ordered strict comparison;
unordered operands take the other sequence. The previous negated `<=`
conditions also flipped on NaN. The four conditions now use ordered `>`.
Fresh VC8 emits ordered comparisons at object offsets `0x2259`, `0x229E`,
`0x2300` and `0x2351`; the second and fourth swap operand order and use a
different equivalent status mask. This local observation does not establish
whole-root or unmasked-exception equivalence.

The 66,787-byte callable remains nonexact from +8; the candidate section
tail is 67,520 bytes. The source remains unselected and adds no exact credit.

## Action 214 flight effect facing, 2026-11-05

Native `0x5C1D0E..0x5C1D7E` captures the unsigned effect-facing byte before sine, computes and rounds Y, then separately reloads signed facing after cosine for the X offset. The earlier candidate reused signed facing captured before both lookups. Ordinary locals now preserve both native read points; fresh VC8 output captures the effect byte at `0x21D2` and reloads signed facing at `0x2209`, after cosine. This establishes read order, not that the actual lookup changes facing or that ordinary gameplay differs. The 66787-byte root remains non-exact (candidate section tail 67784, first mismatch +8); no exact credit is claimed.

## Orbit 852 and 900 facing lifetimes, 2026-11-05

Native 852 spawns including `0x5CD8FC..0x5CD976` and `0x5CD9F0..0x5CDA6A`, and 900 spawns including `0x5CF45C..0x5CF4D4`, capture the unsigned spawn-facing byte before sine and reload signed facing after cosine for the X offset. The former candidate's shared helpers captured the signed value before sine as well. The two helpers now express the native read points with ordinary locals, preserving their distinct native Y associations. Fresh VC8 helper output reads direction before sine and signed facing after cosine for each. The 66787-byte root remains non-exact (candidate section tail 67876, first mismatch +67); its frame now matches the native 0x480, but no exact credit or ordinary-gameplay difference is claimed.

### Integer gate thresholds

The original signed timer gates at `0x5C3027`, `0x5CA05F`, `0x5CC1D1`, `0x5CC227`, and `0x5CDCC0` compare against 18, 30, 12, 20, and 120. Equivalent source forms, including the repeated skill cases sharing the 12/20 gates, recover the local compare-and-branch sequences without changing integer behavior. The complete candidate remains non-exact, with a 67,896-byte section.

Six repeated 25- and 180-frame gates at `0x5CA24C`, `0x5CA7C1`, `0x5CAD88`, `0x5CB344`, `0x5CC360`, and `0x5CC499` now use equivalent native threshold forms. Focused compilation recovers their local signed comparisons and branches. Integer behavior is unchanged; the 67,896-byte candidate remains non-exact.

The action 302 timer gate at `0x5C30A5` and signed skill-level checks including `0x5CC95B` and `0x5CCD4F` now use the equivalent native thresholds 24 and 4. The focused candidate recovers the corresponding local comparison and branch forms; inlining and shared layout also change, so no whole-function match is claimed. Integer behavior is unchanged and the candidate section is 67,672 bytes.
