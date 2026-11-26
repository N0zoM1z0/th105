# TH10.5 reconstruction handoff

Target: original Japanese TH10.5 v1.06a, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Follow [AGENTS.md](../AGENTS.md), [shared tools](SHARED_TOOLS.md) and the
[reconstruction workflow](RE_WORKFLOW.md). Keep compiler/analyzer work serial.

## Completed: Sakuya Fighter `+0x28` (`0x004CADB0`)

`exact-first-sakuya-action-state` is canonically exact from the standalone
[typed source](../src/characters/SakuyaActionState.cpp), under VC8 SP1
`/O2 /GS- /GR /EHsc /MT`.

- All 75,042 physical code bytes and the complete 76,336-byte envelope
  `[0x004CADB0, 0x004DD7E0)` match with zero differences. Fourteen switches
  include 151 destination words and 683 byte indices.
- All 2,805 relocations agree: 1,148 REL32 calls across 31 targets and
  1,657 DIR32 relocations. The owner audit is 106/106; raw control flow
  reaches all 18,993 instructions / 74,937 owned bytes.
- The main inventory span stays 41,511 bytes. Ten separately hashed remote
  chunks contribute 33,451 bytes and now have `remote_exact=true`. The 105
  alignment bytes are compared and excluded from authored credit.
- Envelope SHA-256:
  `6ca4fc284871b25c320bfd93749f548b34b0b55122661caf137ab3efe6db138f`.

Reproduce with:

```bash
WINEDEBUG=-all DISPLAY= WAYLAND_DISPLAY= scripts/repo-python scripts/build.py --unit exact-first-sakuya-action-state --compare --json
scripts/repo-python scripts/audit-giant-action-owners.py --unit exact-first-sakuya-action-state sakuya-vslot28 build/match-units/ExactFirst_SakuyaActionState.obj --json
```

Private current reports: `build/sakuya-root-work-codex/{canonical,owners}.json`.
The [root note](SAKUYA_ACTION_STATE_2026_10_28.md) and
[playbook findings](GIANT_ACTION_ROOT_PLAYBOOK.md#sakuya-source-shape-findings)
cover the live float/double intermediates, repeated guards, compiler-extracted
remainders and difficulty switches. Twelve request homes reserve four floats
while passing count three; their fourth elements remain unwritten. Original
packet declarations and several field meanings remain unknown.

The existing switch comparator now accepts reviewed owned extents and the native
four-byte non-popping x87 stack store between a range compare and its guard.
Focused positive/negative cases and fresh complete Sakuya/Marisa comparisons
validate these changes. No shared gameplay layout or callee changed.

## Previously completed Fighter `+0x28` roots

- **Marisa (`0x004A3710`)**: 66,695 callable / 67,936 envelope bytes,
  125/125 owners, `exact-first-marisa-action-state` (`da319f04`).
- **Youmu (`0x00530200`)**: 37,692 callable / 38,816 envelope bytes,
  98/98 owners, `gpt-web-youmu-vslot28-full-root` (`7bad1ce8`).
- **Aya (`0x00602250`)**: 65,601 callable / 66,704 envelope bytes,
  107/107 owners, `exact-first-aya-action-state` (`c640faf9`).
- **Iku (`0x00620920`)**: 59,038 callable / 60,194 envelope bytes,
  109/109 owners, `gpt-web-iku-action-state` (`ee6a5e7f`).
- **Reimu (`0x00478FA0`)**: 81,550 callable / 82,924 envelope bytes,
  `neon-reimu-action-state-root` (`473165f6`).

## Next useful action

Continue with Alice `0x004E9F50`, one bounded root at a time. Its complete
41,721-byte source hypothesis / 44,080-byte envelope and existing switch map
provide the next smaller Fighter giant. Read
[the Alice note](ALICE_FIGHTER_UPDATE_2026_10_25.md),
`src/characters/AliceFighterActionState.cpp` and
`exact-first-alice-fighter-update` before selecting or changing source.
The user wants the remaining roots completed individually to canonical exactness.

Keep receiver layouts character-scoped. Recompare directly affected accepted
units if a future change touches shared inputs.
