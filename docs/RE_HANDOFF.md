# TH10.5 reconstruction handoff

Target executable: original Japanese TH10.5 v1.06a, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Follow [AGENTS.md](../AGENTS.md), [the shared runtime](SHARED_TOOLS.md) and
[the reconstruction workflow](RE_WORKFLOW.md). Keep this game's Wine prefix,
analysis projects and private worktrees; run compiler and analyzer jobs
serially.

## Completed: Reimu Fighter `+0x28` action-state root (`0x00478FA0`)

`Reimu_dispatch_action_state_vslot28` at `0x00478FA0` is now **100% canonically
exact** under VC8 SP1 `/O2 /GS- /GR /EHsc /MT` in match unit
`neon-reimu-action-state-root`:

- **Source**: [ReimuActionStateRoot.cpp](../src/characters/ReimuActionStateRoot.cpp)
  with receiver declarations in
  [ReimuActionStateStaging.hpp](../src/characters/ReimuActionStateStaging.hpp).
- **Exact envelope**: 81,550 callable bytes (81,488 reachable code bytes + 9
  internal 16-byte loop-alignment gaps = 62 bytes), 1,374 metadata bytes (11
  owned switch tables, 163 jump-table entries, 716 index-table bytes, and
  original alignment padding), total 82,924 bytes
  (`0x00478FA0..0x0048D38C`), 2,477 relocations, zero byte differences.
- **Canonical SHA-256**: callable
  `dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6`; complete
  82,924-byte switch envelope
  `7b5fd9cde0df608689a7d13b8921c701597a5b952a19b75f0bfe9990cd141efc`.
- **Verification**:
  ```bash
  WINEDEBUG=-all DISPLAY= WAYLAND_DISPLAY= scripts/repo-python scripts/build.py --unit neon-reimu-action-state-root --compare --json
  scripts/repo-python scripts/audit-giant-action-owners.py --unit neon-reimu-action-state-root reimu-vslot28 build/match-units/Neon_ReimuActionStateRoot.obj
  scripts/repo-python scripts/check-match-literals.py --require-target
  ```
- **Key VC8 `c2.dll` findings** (recorded in
  [VC8_SOURCE_SHAPE_PATTERNS.md](VC8_SOURCE_SHAPE_PATTERNS.md)):
  1. Moving `advance_frame_and_dispatch();` after the `switch` and exiting
     cases `0, 2, 4, 5, 9` with `break;` causes `0x10B281E0` to place the
     shared advance tail immediately after `case 9` before x87 lowering,
     putting `fstp st(0)` at `0x47973A`, preventing `mov ecx, esi` hoisting in
     `case 9`, and restoring `0, 6, 9, 208` simultaneously. This pattern
     appears across all 13 roster Fighter `+0x28` roots (with Iku `case 781`
     taking the post-switch `break` tail).
  2. Removing the artificial `reimu_action_shared_landing_sequence3_tail`
     label right after `case 201` prevents `0x10B30B97`'s `saved_bytes`
     accumulator from raising `case 201`'s weight to 20 before `case 214` is
     scanned, keeping `case 214` (`0x47B936`) on `L_ret` while `case 404`
     (`0x47EDAB`) and `case 414` move onto `case 201`'s label after `case 226`.
  3. Declaring `spawn_owned_object_via_manager`'s direction parameter as
     `signed char` (and `emit_fighter_effect`'s as `unsigned char`) matches the
     byte-width direction ABI and recovers `push ebx` (`-1`) in action `730`.
  4. `scripts/coff_switch_payload.py` was extended to allow >64 KiB switch
     roots (up to 256 KiB), flag-preserving `mov edi, 5; lea ebp, [edi + disp]`
     between `cmp` and `ja` (action `616`), and full-CFG reaching-constant
     verification for register switch bounds across early returns (action `720`),
     with unit tests in [test_coff_switch_payload.py](../tests/test_coff_switch_payload.py)
     and re-verified on `gpt-web-fighter-common-action-state` and
     `exact-first-info-effect-update`.

## Next useful action

Apply the same exact-reconstruction workflow and VC8 patterns (post-switch
`advance_frame_and_dispatch()`, `signed char` spawn direction, natural
per-case landings without artificial early labels, and `coff_switch_payload.py`
multi-table envelopes) to the next single roster Fighter `+0x28` action-state
root (e.g., Marisa `0x004A3DF0` or Sakuya / Alice / Patchouli).

## Open notes

- `ReimuActionStateRoot.cpp` still retains a few local/intra-root labels
  (`reimu_action_300_320_event_gate`, `reimu_action410_*`, `reimu_action414_*`,
  `reimu_action416_*`, `reimu_shot_action9_exit`, `reimu_complete_action0_619`)
  and `ReimuActionStateStaging.hpp` remains a Reimu-scoped view rather than a
  unified cross-character `Fighter` header. Any future cleanup or shared-header
  unification must re-verify `neon-reimu-action-state-root` for 0 differences.
- The retained private control directory
  `build/reimu-root-work/terra-byte-direction/` is now superseded by the exact
  tracked `src/characters/ReimuActionStateRoot.cpp`.
