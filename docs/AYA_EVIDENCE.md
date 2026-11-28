# Aya root functions

One large Aya root is now 100% canonically exact; four remain nonexact.

| Function | Address, bytes | Status | Source | Unit / note |
| --- | --- | --- | --- | --- |
| Action state (vslot 0x28) | `0x00602250`, 65,601 (66,704 envelope) | **exact** | `AyaActionState.cpp` | `exact-first-aya-action-state` |
| Control mode | `0x00616800`, 1,726 | nonexact | `AyaControlMode.cpp` | [control mode note](AYA_CONTROL_MODE_2026_10_24.md) |
| CPU policy | `0x006126E0`, 16,032 | nonexact | `AyaCpuActionPolicy.cpp` | `gpt-web-aya-cpu-action-policy` |
| Object action state | `0x0061A290`, 19,522 | nonexact | `AyaObjectActionState.cpp` | `gpt-web-aya-object-vslot28-full-root` |
| Object initializer | `0x0061F0B0`, 4,531 | nonexact | `AyaObjectActionEntry.cpp` | [entry ABI note](AYA_ENTRY_SEQUENCE_WORD_ABI_2026_10_19.md) |

## Action state `0x00602250` (exact)

`Aya_dispatch_action_state_vslot28` matches the complete **65,601**-byte
callable (`[0x00602250, 0x00612291)`, 16,856 reachable instructions, 107/107
exact owners, 8-byte aligned frame `0x3E8`) and **66,704**-byte switch envelope
(`[0x00602250, 0x006126E0)`, 3 compact byte-index tables of 33/27/48 entries
with 584 index bytes, 4 direct jump tables of 4/4/4/8 entries, original
`8d4900`/`90`/`8bff` alignment padding, and 2,133 relocations across 33 direct
call targets) under VC8 SP1 `/O2 /GS- /GR /EHsc /MT` in
`exact-first-aya-action-state`
([AyaActionState.cpp](../src/characters/AyaActionState.cpp)):

- **Callable SHA-256**: `04c7620574e00d6f05bb615a095188ee2c60e94cc9d94dbad2eed56b92ab7fd5`
- **Envelope SHA-256**: `42401b4701e475fbaab7d19a542aec6edbe503082a2a0dc2a2e22407e71903a3`
- **Key VC8 shapes proven**: standalone typed `AyaActionStateView`/`AyaPeerView`
  with compile-time `offsetof` assertions; `unsigned int` button counters
  (`0x6bc`/`0x6c0`/`0x6c4` `> 0`); inline `ORBIT_SPAWN` args in `740` (preventing
  `mov al` CSE); hoisted `float base;` + per-loop `for (float counter = 0.0f; ...)`
  in `720`/`721` (matching VC8's LIFO weight-sorted `esp+0x20`/`esp+0x10` stack
  packing across 14 cases); and `float dx` in `AIM_SHORT()` (preserving `529`'s
  `fld [esp+0x70]; fadd [esi+0xf0]`). See
  [VC8_SOURCE_SHAPE_PATTERNS.md](VC8_SOURCE_SHAPE_PATTERNS.md) and
  [GIANT_ACTION_ROOT_PLAYBOOK.md](GIANT_ACTION_ROOT_PLAYBOOK.md).

The superseded nonexact checkpoint log `AYA_ACTION_STATE_2026_10_28.md` and
unused `AyaActionState.hpp` were removed; Git history retains them.

## Object action state `0x0061A290` (nonexact)

The probe unit `gpt-web-aya-object-vslot28-full-root`
([AyaObjectActionState.cpp](../src/characters/AyaObjectActionState.cpp),
[AyaObjectActionView.hpp](../src/characters/AyaObjectActionView.hpp)) now reaches
**18/34** instruction/edge-identical owners (`entry`, `800`, `807`, `810`,
`811`, `817`, `820`, `822`, `825`, `826`, `850`, `851`, `853`, `854`, `862`,
`980`, `997`, `998`) and **28/34** owners at `+0` byte delta (including `801`,
`804`, `855`, `856`, `901`, `902`, and `903` whose remaining diffs are shifted
jump/switch-table targets or the `0x61a42c` vs `0x61a359` shared lifetime-return
exit). Section tail is 20,168 bytes against the 20,000-byte target envelope
(19,522-byte callable + `8bff` + 476-byte switch metadata across 7 tables).

Key source shapes proven on this root:
- **Typed BGRA fields in `AnimationSpriteState`** (`color_b_10c..color_a_10f` in
  [AnimationSpriteState.hpp](../src/battle/AnimationSpriteState.hpp)): replacing
  `reinterpret_cast<unsigned char *>(this)[0x113]` removed a `char *` aliasing
  barrier on `this`, immediately letting VC8 CSE `sequence_index_13e` into `cx`
  without jump-threading across `801`/`807`/`820`/`821`/`853`/`854` and fixing
  `903` `case 2/3/8` fade scheduling.
- **Byte-width direction ABI on `0x00435240`**: calling
  `emit_fighter_effect_433cc0` through a local view with `unsigned char
  direction` recovers `movzx; neg dl; push edx` in `850`/`851`; dropping
  `static_cast<double>` on `object_x_0e8` in `851` recovers `fisub dword ptr
  [esp+0x24]`.
- **Natural control-flow structure (no artificial `goto` joins)**: removing
  artificial `aya_sequence_two_frame_tail` / `aya903_store_fade` labels, using a
  single `if (sequence_index_13e == 1)` in `851` (preventing `mov ecx, esi`
  hoisting above `jle 0x61a41d` and fixing both `851` and `903 case 7`), writing
  `if (sprite_004.color_a_10f >= 20)` in `903 case 2/3` (so `case 2` hosts the
  shared `sub al, 0x14` tail), and matching `902`'s `(3, 1)` vs `(2, 0)` branch
  polarity closed `807`, `811`, `817`, `822`, `851`, `902`, and `903 case 0..8`.
- **Per-case `advance_frame_and_dispatch()`**: unlike Fighter `+0x28` roots,
  AyaObject places `if (advance_frame_and_dispatch()) --lifetime_330; return;`
  per case (hosted at `0x61a41d` inside `case 800`), not as a single post-switch
  footer; moving it after the `switch` regressed `800`/`810`/`852`.

Tried without closing the residual:
- `/O1` and `/O2 /Os` lose 8-byte stack alignment (`and esp, -8`) and diverge at
  entry. Keep `/O2`.
- Pre-regalloc `TryTailMerge` (`c2.dll:0x10B321E8`) skips target labels with
  `refcount > 0x64` (`100`). Routing `--lifetime_330; return;` through a single
  label dropped `L_ret` below 100 but still did not trigger the 196-byte
  `861 -> 826` merge in the full 34-case switch.
- Bisecting the 34-case switch showed `861` cleanly tail-merges all 196 bytes
  into `826` (`0x61c27e` + `0x61c2a7`) in the 12-case subset `800..817 + 826 +
  861`, and stops once `820`'s `sequence 4/6` block (`aya_stage_surface_height_at_x`
  + `double object_y`) or `821` is included; hoisting a single function-scope
  `double object_y` did not restore the merge in the full switch.

Open residuals:
- `actions:861` (`+196 B`, 3 diffs): unmerged 196-byte tail into `826`
  (`0x61c27e` / `0x61c2a7`).
- Local micro-diffs: `812` (`-2 B`, `fild; fmul [edi]` vs `fld [edi]; fild;
  fmulp`), `815`/`816` (`+0`/`-3 B`, `816` `owner_action == 529`
  `select_sequence(2)` merging into `815`), `821` (`-8 B`, `eax = [esi+0x144]`
  CSE across two frame-0 checks), `852` (`-6 B`, `fimul` vs duplicated `fild`),
  `903 case 9` (`0x61a359` vs `0x61a42c`), and `900`/`990` (`[esp+0x18]` vs
  `[esp+0x14]` rounding temp).

## CPU policy `0x006126E0` (nonexact)

The function has 4,097 instructions. Its counter reads are signed, and the
last comparison differed at +0x12E, in the selector-tail sharing.
