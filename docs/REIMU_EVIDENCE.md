# Reimu root functions

Two large Reimu roots are now 100% canonically exact; three remain nonexact.

| Function | Address, bytes | Status | Source | Unit / note |
| --- | --- | --- | --- | --- |
| Action state (vslot 0x28) | `0x00478FA0`, 81,550 (82,924 envelope) | **exact** | `ReimuActionStateRoot.cpp` | `neon-reimu-action-state-root` |
| Action initializer (vslot 0x3C) | `0x00491C40`, 3,785 (4,738 envelope) | **exact** | `ReimuActionInitialization.cpp` | `exact-first-reimu-action-initialization` ([note](REIMU_ACTION_INITIALIZATION_2026_10_25.md)) |
| CPU policy | `0x0048D390`, 15,999 | nonexact | `ReimuCpuActionPolicy.cpp` | `gpt-web-reimu-cpu-action-policy` |
| Object action state | `0x00496540`, 39,853 | nonexact | `ReimuObjectActionStateStaging.cpp` | `gpt-web-reimu-object-action-state` |
| Object initializer | `0x004A1CE0`, 4,892 | nonexact | `ReimuObjectActionEntry.cpp` | `gpt-web-reimu-object-action-entry` |

## Action state `0x00478FA0` (exact)

`Reimu_dispatch_action_state_vslot28` matches the complete 81,550-byte callable
and 82,924-byte switch envelope (`0x00478FA0..0x0048D38C`, 11 switch tables,
2,477 relocations) in standalone VC8 SP1 COFF (`neon-reimu-action-state-root`).
Key VC8 `c2.dll` patterns recovered here (post-switch
`advance_frame_and_dispatch()` with `break;`, `TailMerge` `saved_bytes`
separation of `214`/`404`, and `signed char` direction on
`spawn_owned_object_via_manager`) are documented in
[VC8_SOURCE_SHAPE_PATTERNS.md](VC8_SOURCE_SHAPE_PATTERNS.md) and
[GIANT_ACTION_ROOT_PLAYBOOK.md](GIANT_ACTION_ROOT_PLAYBOOK.md). The superseded
split files under `src/characters/ReimuActionState*.cpp/.hpp` and one-off LTCG
probe scripts were removed; Git history retains them.

## Object action state `0x00496540` (nonexact)

- The receiver is in ECX, the function returns with `ret`, and it is reached
  through vslot 0x28. The caller `0x004937D0` ignores EAX, so the source uses
  `void`; that is inferred, not proven.
- The same-TU counter `0x004963A0` (66 bytes) is exact.
- The entry hoists the constants EBX=1 and EBP=0. That choice follows the
  outgoing-argument shape of action 822.
- Action 908 needs its float-before-integer addition, which a 17-slot runtime
  owner view restores.
- At action 907 the target makes two physical calls where the source makes
  one. This is a code-generation difference, not a missing callback.
- Actions 869 and 901 use float lookup views at the call site. The double
  providers in `AngleLookup.cpp` stay unmatched.

These were tried without effect on the entry mismatch: linking 20 real object
providers (native-root and root-CIL modes), `/Zi`, replacing the four float
`fabs` calls with double `fabs`, and byte or signed formal widths for 822.

### Object action-state switch map (2026-11-23)

The complete `0x00496540` ownership extent remains one ReimuObject vslot
`+0x28` root with a 6,282-byte remote chunk. The top-level 200-byte action
selector map is reproduced 200/200 by the candidate source, with all 42
handler destination entries represented by COFF relocations. The current entry
comparison still differs at `+0x1F`. See
[ReimuObject switch and remote ownership](REIMU_OBJECT_ACTION_SWITCH_2026_11_23.md).

## CPU policy `0x0048D390` (nonexact)

The function has 4,126 instructions, four jump tables and 52 returns. Its wall
predicates are unordered float tests; write the ordered form the target tests
(see [VC8_SOURCE_SHAPE_PATTERNS.md](VC8_SOURCE_SHAPE_PATTERNS.md)).

## Object initializer `0x004A1CE0` (nonexact)

The 548 bytes of metadata after the callable belong to this function, not to
the object root.
