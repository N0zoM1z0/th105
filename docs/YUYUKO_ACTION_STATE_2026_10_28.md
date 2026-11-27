# Yuyuko action-state root `0x0055D850`

## Canonical exact match (2026-11-26)

`Yuyuko_dispatch_action_state_vslot28` (`0x0055D850`,
`exact-first-yuyuko-action-state`) is canonically exact from the
character-scoped [source](../src/characters/YuyukoActionState.cpp) and
[checked receiver](../src/characters/YuyukoActionState.hpp) under VC8 SP1
`/O2 /GS- /GR /EHsc /MT` against JP TH10.5 v1.06a SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.

- Callable code `[0x0055D850, 0x0056BD4B)`: **58,619** bytes (SHA-256
  `d42fe81e99b173281b6ccecb8e4f6c60ee89d5b0e1ac1cee244eb9f22cd12a47`). Raw CFG
  reaches all 14,783 instructions / 58,619 authored bytes with zero alignment
  holes.
- Complete five-table switch payload `[0x0055D850, 0x0056C168)`: **59,672**
  bytes (three sparse action tables `31`/`28`/`51` plus two four-entry
  difficulty tables in `710` and `720`; 118 destination words, 576 index bytes,
  5 alignment bytes; SHA-256
  `f8a241c5d1d735d0c660f406b87a4cb00545d31a0ca66b67b129f3afefe5afd9`).
- Relocations: all **1,714** agree (885 REL32 direct calls across 27 targets
  and 829 DIR32 fields). Owner audit: **109/109**
  `instruction_edge_identical_owners`.

Reproduce:

```bash
WINEDEBUG=-all DISPLAY= WAYLAND_DISPLAY= scripts/repo-python scripts/build.py --unit exact-first-yuyuko-action-state --compare --json
scripts/repo-python scripts/audit-giant-action-owners.py --unit exact-first-yuyuko-action-state yuyuko-vslot28 build/match-units/ExactFirst_YuyukoActionState.obj --json
```

Private reports: `build/yuyuko-root-work-codex/{canonical,owners}.json`.

### Resolution of the six local `1` constant intervals

Hardware-breakpoint tracing of VC8 C2's `InsertAdditionalSplits` (`0x10B15D50`)
on `c2.dll` (`497d1ffe57f75db8b458167bdea475f3962829e139b355a2672a4ef51c716413`)
pinpointed the exact cause of the final six diffs (`502`/`503`/`507`/`508`
missing `mov ebx, 1`, and `512`/`513` missing `mov edi, 1`):

- When `EBP = 90` was colored, the global `imm == 1` interval lost its last
  available register (`EBP`) and entered `InsertAdditionalSplits`, which
  greedily groups blocks into regions in layout order by scanning each block's
  predecessor list for the first compatible region.
- The high-switch dispatch block (`+0x6EC8..+0x6ED6`) uses
  `{EAX, EBX, EBP, ESI, EDI}`, leaving `ECX`/`EDX` free in its region (`reg 19`).
  Because cases `502`/`503`/`507`/`508` and `512`/`513` begin with non-call
  sequence guards, their entry blocks joined `reg 19`.
- With flat `&&` (`if (!sequence_index_13e && frame_index_140 >= 11 && crossed())`
  in `502`/`503`/`507`/`508`, and `if (!sequence_index_13e && crossed())` in
  `512`/`513`), the non-call guard edges (`reg 19`) appeared ahead of the
  `crossed()` call block's fresh region in the merge block's predecessor list,
  pulling the merge block back into `reg 19` and severing the local `1`
  intervals.
- Nesting the guards (`if (!sequence_index_13e) { if (frame_index_140 >= 11) { if (crossed()) ... } }`
  and `if (!sequence_index_13e) { if (crossed()) ... }`) places the call
  block's region first in the merge block's predecessor list, keeping
  `mov ebx, 1` (`502`/`503`/`507`/`508`) and `mov edi, 1` (`512`/`513`) intact
  and closing the downstream `710`/`720` table base and `low:11` alignment
  diffs.
- `scripts/coff_switch_payload.py` was narrowly extended to allow up to two
  selector-disjoint nonvolatile immediate loads (`mov edi, 3; mov bl, 0xff` at
  `+0x6ECF..+0x6ED4`) between `movzx` and `jmp` in compact switch dispatch,
  backed by positive and negative unit tests in `tests/test_coff_switch_payload.py`.

## Preserved target semantics

- Partial checked receiver (`YuyukoActionStateView`) is pointer-only; full
  `Fighter` class layout, TU boundaries and several field meanings remain open.
- Sine/cosine providers (`0x00406360`/`0x004063D0`) return `float`; effect
  direction is `unsigned char`; spawn direction is `signed char`; `on_surface`
  consumers test `AL`.
- `0x0056B99B..0x0056B9B0` and `0x0056BB6A..0x0056BB7F` write separate 16-bit
  fields (`word_76c = 0`, `word_76a = 1`, then `766`/`768`/`764 = 0`).
- Direct spawn expressions preserve outgoing direction before trig/RNG calls
  and signed facing reloads afterward (`0x4E8` native frame); negative integer
  offsets convert to `float` before subtraction (`fisub` in `302`/`304`/`305`,
  `562`, petal offsets); `651` follows `601` and `657` follows `607` in source
  to preserve stack-home order; `562` uses ordered landing gates and `720` uses
  an ordered `counter <= 100` wave limit.
