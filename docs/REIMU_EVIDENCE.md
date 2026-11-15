# Reimu root functions

Five large Reimu functions remain nonexact.

| Function | Address, bytes | Source | Unit |
| --- | --- | --- | --- |
| Action state (vslot 0x28) | 0x478FA0, 81,550 | staged parts in `src/characters/ReimuActionState*` | none |
| Action initializer | 0x491C40, 3,785 | `ReimuActionInitialization.cpp` | see [its note](REIMU_ACTION_INITIALIZATION_2026_10_25.md) |
| CPU policy | 0x48D390, 15,999 | `ReimuCpuActionPolicy.cpp` | `gpt-web-reimu-cpu-action-policy` |
| Object action state | 0x496540, 39,853 | `ReimuObjectActionStateStaging.cpp` | `gpt-web-reimu-object-action-state` |
| Object initializer | 0x4A1CE0, 4,892 | `ReimuObjectActionEntry.cpp` | `gpt-web-reimu-object-action-entry` |

## Action state 0x478FA0

The callable ends at 0x48CE2E. Its three primary jump tables have 45, 50 and
33 entries with 126 distinct destinations, including the shared default.
Actions 300 and 560 are dispatched outside the tables. The staged sources
cover the checked entry and actions up to 798 (low, middle and high
families); the later high path is missing, so the root has no unit.

A `/GL` + `/LTCG` link of the staged candidate with real providers produced the
same bytes as the plain COFF build. The residual is therefore not an LTCG
backend effect.

## Object action state 0x496540

- The receiver is in ECX, the function returns with `ret`, and it is reached
  through vslot 0x28. The caller 0x4937D0 ignores EAX, so the source uses
  `void`; that is inferred, not proven.
- The same-TU counter 0x4963A0 (66 bytes) is exact.
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

## CPU policy 0x48D390

The function has 4,126 instructions, four jump tables and 52 returns. Its wall
predicates are unordered float tests; write the ordered form the target tests
(see the patterns note).

## Object initializer 0x4A1CE0

The 548 bytes of metadata after the callable belong to this function, not to
the object root.

The per-checkpoint notes from October 17–25 were removed in the commit that
added this note; Git history keeps them.
