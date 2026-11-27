# TH10.5 reconstruction handoff

Target: original Japanese TH10.5 v1.06a, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Follow [AGENTS.md](../AGENTS.md), [shared tools](SHARED_TOOLS.md) and the
[reconstruction workflow](RE_WORKFLOW.md). Keep compiler/analyzer work serial.

## Completed: Yukari Fighter `+0x28` (`0x0057B030`) — All 15/15 Fighter `+0x28` roots exact

`exact-first-yukari-action-state` is canonical exact from the character-scoped
[source](../src/characters/YukariActionState.cpp) and
[checked receiver](../src/characters/YukariActionState.hpp), under VC8 SP1
`/O2 /GS- /GR /EHsc /MT`. With Yukari complete, all 15 Fighter primary vtable
`+0x28` action-state roots in JP TH10.5 v1.06a are now canonically exact.

- All 57,042 callable code bytes and the complete 58,248-byte nine-table switch
  payload `[0x0057B030, 0x005893B8)` match with zero differences.
- All 1,769 relocations agree: 889 REL32 calls across 32 targets and 880 DIR32
  fields. Nine tables contain 144 destination words, 623 index bytes and 7
  alignment bytes.
- The owner audit is 122/122. Raw CFG reaches all 14,501 decoded instructions /
  57,042 authored bytes with zero unreachable alignment bytes.
- Code SHA-256: `7caa43b9c69087875de1d8db150434733ad7b8a0fbd0d7bd245ee288f3db5db3`;
  payload SHA-256: `8c76f4df41ea9627a161193cf132671508311cd6e04717a4314a7cb2390682af`.

Reproduce with:

```bash
WINEDEBUG=-all DISPLAY= WAYLAND_DISPLAY= scripts/repo-python scripts/build.py --unit exact-first-yukari-action-state --compare --json
scripts/repo-python scripts/audit-giant-action-owners.py --unit exact-first-yukari-action-state yukari-vslot28 build/match-units/ExactFirst_YukariActionState.obj --json
```

Private results: `build/yukari-root-work/{canonical,owners}.json`.
The [Yukari note](YUKARI_ACTION_STATE_2026_10_28.md) records the checked typed
receiver, exact comparison/arithmetic recoveries (`73`/`88`, `89`, `200`, `201`,
`203`, `305`, `402`, `565`/`566`, `710`/`730`/`741`, `750`, `burst910` `for`
loop), and the `c2.dll:0x10B14E2A` global coloring resolution (separating
`case 2:` / `case 1:` in `720`'s difficulty switch plus unnesting sequential
`!frame_timer_142` guards to restore `CONST(0) -> EBP, CONST(1) -> EBX`, and
splitting `entry(1)`/`entry(2)` in `404` to restore its `0x57F6B5` shared tail).
No shared gameplay source, layout, compiler flags or comparator code changed.

## Completed: Remilia Fighter `+0x28` (`0x00545090`)

`exact-first-remilia-action-state` is canonical exact from the character-scoped
[source](../src/characters/RemiliaActionState.cpp) and
[checked receiver](../src/characters/RemiliaActionState.hpp), under VC8 SP1
`/O2 /GS- /GR /EHsc /MT`.

- All 61,962 physical callable bytes and the complete 63,316-byte sixteen-table
  switch payload `[0x00545090,0x005547E4)` match with zero differences.
- All 2,127 relocations agree: 967 REL32 calls across 31 targets and 1,160
  DIR32 fields. Sixteen tables contain 160 destination words, 709 index bytes
  and 5 alignment bytes.
- The owner audit is 103/103. Raw CFG reaches 15,972 of 15,973 decoded
  instructions / 61,959 authored bytes; one unreachable 3-byte VC8
  loop-alignment `lea ecx, [ecx]` instruction (`0x00551DAD..0x00551DAF`) is
  compared and excluded from authored progress.
- Code SHA-256: `cffbd3c34e8a10be85f5236a16afad7e035227df15bf420b9eb30599fce0092b`;
  payload SHA-256: `1c631b6ff3b591e2f96c1ad5de0957213a71855231e79d3768726acd1752c5a3`.

Reproduce with:

```bash
WINEDEBUG=-all DISPLAY= WAYLAND_DISPLAY= scripts/repo-python scripts/build.py --unit exact-first-remilia-action-state --compare --json
scripts/repo-python scripts/audit-giant-action-owners.py --unit exact-first-remilia-action-state remilia-vslot28 build/match-units/ExactFirst_RemiliaActionState.obj --json
```

Private results: `build/remilia-root-work/{canonical,owners}.json`.
The [Remilia note](REMILIA_ACTION_STATE_2026_10_28.md) records the checked typed
receiver, `signed char` direction/layer on `spawn` and `unsigned char` direction
on `effect`, `+0x04` `RemiliaActionScratch::oriented_components` and `owner_168`
wave-handle dispatch (`607`/`710`), post-switch `advance()` with separate
`208..212, 220..222` cases, loop/branch polarity fixes (`505`, `520`/`521`,
`530`/`531`, `565`/`566`/`720`, `730`/`731`, `741`), inlined `400`/`414`/`415`
paths, `double step = field_73c * 90.0;` scheduling in `710`, and the narrow
`coff_switch_payload.py` rule for `mov edi, 60` between `cmp` and `ja` (with
positive/negative unit tests and existing-object smoke). No shared gameplay
source, layout or compiler flags changed.

## Completed: Suika Fighter `+0x28` (`0x00598990`)

`exact-first-suika-action-state` is canonical exact from the character-scoped
[source](../src/characters/SuikaActionState.cpp) and
[checked receiver](../src/characters/SuikaActionState.hpp), under VC8 SP1
`/O2 /GS- /GR /EHsc /MT`.

- All 79,435 physical callable bytes and the complete 81,124-byte twenty-table
  switch payload `[0x00598990,0x005AC674)` match with zero differences.
- All 2,553 relocations agree: 1,081 REL32 calls across 37 targets and 1,472
  DIR32 fields. Twenty tables contain 239 destination words, 726 index bytes and
  7 alignment bytes.
- The owner audit is 114/114. Raw CFG reaches 20,321 of 20,324 decoded
  instructions / 79,426 authored bytes; three unreachable 3-byte VC8
  loop-alignment `lea ecx, [ecx]` instructions (`0x005A09FD`, `0x005A5A5D`,
  `0x005A97CD`, 9 bytes total) are compared and excluded from authored progress.
- Code SHA-256: `a1006a208fb62813cec2081c250f5825e88011ce834cff9e49e5d15d0164feb9`;
  payload SHA-256: `adb2bc7f9936c61683a9028edb19fb3625c2b79c51890891995e6271d95c426c`.

Reproduce with:

```bash
WINEDEBUG=-all DISPLAY= WAYLAND_DISPLAY= scripts/repo-python scripts/build.py --unit exact-first-suika-action-state --compare --json
scripts/repo-python scripts/audit-giant-action-owners.py --unit exact-first-suika-action-state suika-vslot28 build/match-units/ExactFirst_SuikaActionState.obj --json
```

Private results: `build/suika-root-work/{canonical,owners}.json`.
The [Suika note](SUIKA_ACTION_STATE_2026_10_28.md) records the checked typed
receiver (removing the 11 `.inc` fragments and `at<T>` casts), `signed char`/
`unsigned char` direction parameters on `spawn`/`effect`, the `case 412`
(`set_action_and_finalize(2)`) and `500`/`501` (`if (word_732 == 1) ... else`)
fixes, the inlined giant `605`/`730` surface/button ladders, and the `525`/`526`
`float limit = static_cast<float>(byte_609 + 5.0); float m = 0.0f; double count = limit; if (0.0 < limit)`
loop form that reproduces global `[esp+0x18]`/`[esp+0x1c]` slot assignment and
exact `fstp dword ptr [esp+0x20]` scheduling. No shared gameplay source, layout
or compiler flags changed.

## Completed: Udonge Fighter `+0x28` (`0x005BFD50`)

`exact-first-udonge-action-state` is canonical exact from the character-scoped
[source](../src/characters/UdongeActionState.cpp) and
[checked receiver](../src/characters/UdongeActionState.hpp), under VC8 SP1
`/O2 /GS- /GR /EHsc /MT`.

- All 66,787 callable code bytes and the complete 67,964-byte seven-table switch
  payload `[0x005BFD50,0x005D06CC)` match with zero differences.
- All 1,878 relocations agree: 902 REL32 calls across 29 targets and 976 DIR32
  fields. Seven tables contain 121 destination words, 688 index bytes and 5
  alignment bytes.
- The owner audit is 104/104. Raw CFG reaches all 16,886 instructions / 66,787
  authored bytes with zero unreachable alignment bytes.
- Code SHA-256: `ab78b849a55e354b0495d31cc47568b41040607644445b82c68e980337b45c0f`;
  payload SHA-256: `8f59f23a42efe00b3778ad1212e16f668c76b30296a98bdb60766ce46fb714c9`.

Reproduce with:

```bash
WINEDEBUG=-all DISPLAY= WAYLAND_DISPLAY= scripts/repo-python scripts/build.py --unit exact-first-udonge-action-state --compare --json
scripts/repo-python scripts/audit-giant-action-owners.py --unit exact-first-udonge-action-state udonge-vslot28 build/match-units/ExactFirst_UdongeActionState.obj --json
```

Private results: `build/udonge-root-work/{canonical,owners}.json`.
The [Udonge note](UDONGE_ACTION_STATE_2026_10_28.md) records the checked typed
receiver (removing the 9 `.inc` fragments and `at<T>` casts), `signed char` /
`unsigned char` direction parameters on `spawn`/`effect`, inlined early-return
helpers, the `cases 525..528` cone-hit packet fix (`p[2] = 1.0f` instead of
`p[1] = 1.0f`) plus direct `fighter_170->` / `facing_104` reads, and the
`word_174 > 0` prelude `float scale = field_7a8; float alpha = scale * word_7a6;`
form that simultaneously matches `entry` `fld; fild; fmulp`, `expand_cone`
`fld [0x7b0]; fadd [0x73c]` and `565..568` `fld [0x73c]; fadd [0x740]`. No
shared gameplay source, layout or compiler flags changed.

## Completed: Komachi Fighter `+0x28` (`0x005E20E0`)

`exact-first-komachi-action-state` is canonical exact from the character-scoped
[source](../src/characters/KomachiActionState.cpp) and
[checked receiver](../src/characters/KomachiActionState.hpp), under VC8 SP1
`/O2 /GS- /GR /EHsc /MT`.

- All 63,993 callable code bytes and the complete 65,176-byte seven-table switch
  payload `[0x005E20E0,0x005F1F78)` match with zero differences.
- All 1,864 relocations agree: 915 REL32 calls across 30 targets and 949 DIR32
  fields. Seven tables contain 120 destination words, 692 index bytes and 11
  alignment bytes.
- The owner audit is 107/107. Raw CFG reaches all 16,310 instructions / 63,993
  authored bytes with zero unreachable alignment bytes.
- Code SHA-256: `bb737abb720d627a985ae38f3b3f11f0cabf31b7ad0b7f89ab7a6f809ea9b8bd`;
  payload SHA-256: `20d83eff7214346536177a1391fa993ccf62081c1b9ebc5aa048edc005094204`.

Reproduce with:

```bash
WINEDEBUG=-all DISPLAY= WAYLAND_DISPLAY= scripts/repo-python scripts/build.py --unit exact-first-komachi-action-state --compare --json
scripts/repo-python scripts/audit-giant-action-owners.py --unit exact-first-komachi-action-state komachi-vslot28 build/match-units/ExactFirst_KomachiActionState.obj --json
```

Private results: `build/komachi-root-work/{canonical,owners}.json`.
The [Komachi note](KOMACHI_ACTION_STATE_2026_10_28.md) records the `unsigned
char` direction parameter on `effect`, inlined early-return helpers and
post-switch `advance()`, the `case 730` inline trig expression avoiding VC8
LICM `qword` spill and restoring LIFO `esp+0x10`/`esp+0x28` slot packing across
15 owners, and the nested `if (sequence_index_13e < 2) { if (crossed()) ... }`
guard in `case 405` that restored `mov ebx, 1` in VC8's
`InsertAdditionalSplits`. No shared gameplay source, layout or compiler flags
changed.

## Completed: Yuyuko Fighter `+0x28` (`0x0055D850`)

`exact-first-yuyuko-action-state` is canonical exact from the character-scoped
[source](../src/characters/YuyukoActionState.cpp) and
[checked receiver](../src/characters/YuyukoActionState.hpp), under VC8 SP1
`/O2 /GS- /GR /EHsc /MT`.

- All 58,619 callable code bytes and the complete 59,672-byte five-table switch
  payload `[0x0055D850,0x0056C168)` match with zero differences.
- All 1,714 relocations agree: 885 REL32 calls across 27 targets and 829 DIR32
  fields. Five tables contain 118 destination words, 576 index bytes and 5
  alignment bytes.
- The owner audit is 109/109. Raw CFG reaches all 14,783 instructions / 58,619
  authored bytes with zero unreachable alignment bytes.
- Code SHA-256: `d42fe81e99b173281b6ccecb8e4f6c60ee89d5b0e1ac1cee244eb9f22cd12a47`;
  payload SHA-256: `f8a241c5d1d735d0c660f406b87a4cb00545d31a0ca66b67b129f3afefe5afd9`.

Reproduce with:

```bash
WINEDEBUG=-all DISPLAY= WAYLAND_DISPLAY= scripts/repo-python scripts/build.py --unit exact-first-yuyuko-action-state --compare --json
scripts/repo-python scripts/audit-giant-action-owners.py --unit exact-first-yuyuko-action-state yuyuko-vslot28 build/match-units/ExactFirst_YuyukoActionState.obj --json
```

Private results: `build/yuyuko-root-work-codex/{canonical,owners}.json`.
The [Yuyuko note](YUYUKO_ACTION_STATE_2026_10_28.md) records the nested
`if (!sequence_index_13e)` / `if (frame_index_140 >= 11)` / `if (crossed())`
guards in `502`/`503`/`507`/`508` and `512`/`513` that reordered merge-block
predecessors in VC8's `InsertAdditionalSplits` greedy region grouping so the
local `EBX=1` and `EDI=1` intervals survive coloring, plus the narrow
`coff_switch_payload.py` dispatch-prefix rule for `mov edi, 3; mov bl, 0xff`
between `movzx` and `jmp` (with positive/negative unit tests and existing-object
smokes). No shared gameplay source, layout or compiler flags changed.

## Completed: Patchouli Fighter `+0x28` (`0x0050F200`)

`exact-first-patchouli-action-state` is canonical exact from the character-scoped
[source](../src/characters/PatchouliActionState.cpp) and
[checked receiver](../src/characters/PatchouliActionState.hpp), under VC8 SP1
`/O2 /GS- /GR /EHsc /MT`.

- All 54,452 physical code bytes and the complete 55,610-byte payload
  `[0x0050F200,0x0051CB3A)` match with zero differences.
- All 1,651 relocations agree: 807 REL32 calls across 29 targets and 844 DIR32
  fields. Four tables contain 111 destination words, 711 index bytes and 3
  alignment bytes.
- The owner audit is 106/106. Raw CFG reaches 14,067 instructions / 54,445
  authored bytes. Seven internal alignment bytes at `0x0050F8A9..0x0050F8AF`
  are compared and excluded from authored progress.
- Code SHA-256: `41430c00c554e7dc169692c56b41fd43f5ef1204700cb092bab6420f327ed944`;
  payload SHA-256: `d4d73f175e4f8b37667f04472df8c5db8cbec0ca20414d4107df08a007779043`.

Reproduce with:

```bash
WINEDEBUG=-all DISPLAY= WAYLAND_DISPLAY= scripts/repo-python scripts/build.py --unit exact-first-patchouli-action-state --compare --json
scripts/repo-python scripts/audit-giant-action-owners.py --unit exact-first-patchouli-action-state patchouli-vslot28 build/match-units/ExactFirst_PatchouliActionState.obj --json
```

Private results: `build/patchouli-root-work-codex/{canonical,owners}.json`.
The [Patchouli note](PATCHOULI_ACTION_STATE_2026_10_27.md) records the unnested
`201`/`224` sequence guards that lifted the prefix x87 zero interval's spill
cost above zero, the separate `209`/`212`/`221` cases that restored VC8's
native `FgDoLateFlowOpts` merge order so `210` and `222` stay distinct, and
the remaining branch/comparison fixes. No shared gameplay source, layout or
compiler flags changed.

## Completed: Tenshi Fighter `+0x28` (`0x0063D3E0`)

`exact-first-tenshi-action-state` is canonical exact from the character-scoped
[source](../src/characters/TenshiActionState.cpp) and
[checked receiver](../src/characters/TenshiActionState.hpp), under VC8 SP1
`/O2 /GS- /GR /EHsc /MT`.

- All 47,784 physical code bytes and the complete 48,968-byte payload
  `[0x0063D3E0,0x00649328)` match with zero differences.
- All 1,562 relocations agree: 789 REL32 calls across 43 targets and 773 DIR32
  fields. Six tables contain 120 destination words and 702 index bytes.
- The owner audit is 107/107. Raw CFG reaches 12,489 instructions / 47,777
  authored bytes. Seven internal alignment bytes are compared and excluded.
- The original 18-byte `std::sin(float)` helper remains separately exact and
  excluded from authored credit. The full class/TU and some field meanings
  remain unknown; observed unwritten fields stay unwritten.

Reproduce with:

```bash
WINEDEBUG=-all DISPLAY= WAYLAND_DISPLAY= scripts/repo-python scripts/build.py --unit exact-first-tenshi-action-state --compare --json
scripts/repo-python scripts/audit-giant-action-owners.py --unit exact-first-tenshi-action-state tenshi-vslot28 build/match-units/ExactFirst_TenshiActionState.obj --json
```

Private results: `build/tenshi-root-work-codex/{canonical,owners}.json`.
The [root note](TENSHI_ACTION_STATE_2026_10_27.md) records packet initialization,
callback argument order, independent guards and declaration lifetimes that
closed the function. The narrow switch-verifier addition passes focused
positive/negative cases and full existing-object Alice/Marisa/Sakuya smokes.
No shared gameplay source, layout or compiler flags changed.

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

All 15 Fighter `+0x28` action-state roots are now canonically exact. Choose the
next large target cluster (for example, Fighter `+0x2C` action-entry/update
roots, Object update roots, or remaining scene/battle functions) from the
canonical ledgers and verify with zero-difference comparison before granting
exact credit.
