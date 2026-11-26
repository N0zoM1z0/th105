# TH10.5 reconstruction handoff

Target: original Japanese TH10.5 v1.06a, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Follow [AGENTS.md](../AGENTS.md), [shared tools](SHARED_TOOLS.md) and the
[reconstruction workflow](RE_WORKFLOW.md). Keep compiler/analyzer work serial.

## Completed: Alice Fighter `+0x28` (`0x004E9F50`)

`exact-first-alice-fighter-update` is canonically exact from the standalone
[typed source](../src/characters/AliceFighterActionState.cpp), under VC8 SP1
`/O2 /GS- /GR /EHsc /MT`.

- All 42,721 physical code bytes and the complete 44,072-byte owned switch
  payload `[0x004E9F50,0x004F4B78)` match with zero differences.
- All 1,380 relocations agree: 674 REL32 calls across 27 targets and 706 DIR32
  fields. Sixteen tables include 165 destination words and 685 indices.
- The owner audit is 104/104. Raw CFG reaches 11,169 instructions / 42,718 owned
  bytes. The three internal alignment bytes are compared and excluded from
  authored progress. Eight following `INT3` bytes align the next function.
- Payload SHA-256:
  `202e532a593f9c712518519e0c782ce177696ddb3ab401aaec86ec5a113c0f89`.

Reproduce with:

```bash
WINEDEBUG=-all DISPLAY= WAYLAND_DISPLAY= scripts/repo-python scripts/build.py --unit exact-first-alice-fighter-update --compare --json
scripts/repo-python scripts/audit-giant-action-owners.py --unit exact-first-alice-fighter-update alice-vslot28 build/match-units/ExactFirst_AliceFighterActionState.obj --json
```

Private current reports: `build/alice-root-work-codex/{canonical,owners}.json`.
The [Alice note](ALICE_FIGHTER_UPDATE_2026_10_25.md) records the combined entry
skip guard, callback-facing rereads, independent entry tests and packet homes.
570/571 preserve twelve-byte storage, count four and the unwritten fourth word;
original declarations and several field meanings remain unknown.

The comparator now handles a final internal jump and a nonvolatile bound derived
by unindexed LEA. Twenty-eight focused cases and fresh complete Alice, Marisa
and Sakuya comparisons pass. No shared gameplay layout or callee changed.

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

Continue with Tenshi `0x0063D3E0`, one bounded root at a time. Its 47,784-byte
callable is the smaller remaining Fighter root with a complete registered
hypothesis. Read `src/characters/TenshiActionState.cpp`,
`docs/TENSHI_ACTION_STATE_2026_10_28.md` and `exact-first-tenshi-action-state`
before changing source. The user wants every remaining giant completed
individually to canonical exactness; use `gpt-6.1-sol:` commit subjects.

Keep receiver layouts character-scoped. Recompare directly affected accepted
units after shared input changes.
