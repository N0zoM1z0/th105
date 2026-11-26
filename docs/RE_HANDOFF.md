# TH10.5 reconstruction handoff

Target executable: original Japanese TH10.5 v1.06a, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Follow [AGENTS.md](../AGENTS.md), [the shared runtime](SHARED_TOOLS.md) and
[the reconstruction workflow](RE_WORKFLOW.md). Run compiler/analyzer jobs
serially and preserve this game's Wine prefix and private analysis state.

## Completed: Marisa Fighter `+0x28` action-state root (`0x004A3710`)

`Marisa_dispatch_action_state_vslot28` is canonically exact in
`exact-first-marisa-action-state`, compiled with VC8 SP1
`/O2 /GS- /GR /EHsc /MT` from
[MarisaActionState.cpp](../src/characters/MarisaActionState.cpp).

- All 66,695 callable bytes and the complete 67,936-byte envelope
  (`0x004A3710..0x004B4070`, exclusive end) match with zero differences.
  Six switch tables include 137 destination words, 688 byte indices and
  the original alignment.
- All 1,929 relocations are replayed: 978 REL32 calls across 29 targets and
  951 DIR32 relocations. The owner audit is 125/125; raw control flow reaches
  all 16,999 instructions with no unresolved indirect exits.
- Callable SHA-256:
  `98fd68e00763955f64d7489b2a5cb04b20f209031d739a7e9117273080a45aa5`.
  Complete envelope SHA-256:
  `58dd1936fc5db5341cbf3e08d9f19beaa7d106ffbf84d82b673644da542c6447`.

Reproduce acceptance with:

```bash
WINEDEBUG=-all DISPLAY= WAYLAND_DISPLAY= scripts/repo-python scripts/build.py --unit exact-first-marisa-action-state --compare --json
scripts/repo-python scripts/audit-giant-action-owners.py --unit exact-first-marisa-action-state marisa-vslot28 build/match-units/ExactFirst_MarisaActionState.obj
```

The [root note](MARISA_ACTION_STATE_2026_10_28.md) and
[playbook findings](GIANT_ACTION_ROOT_PLAYBOOK.md#marisa-source-shape-findings)
cover the loop-counter scopes, double Y across spawn branches, independent
frame guards and physical tail selection. The three-float 307/308 arrays remain
partially initialized as observed; their original spelling and slot semantics
are unknown. Actions 730/732 correctly advance to 731/733.

Current private evidence is in `build/marisa-root-work-codex/{canonical,owners}.json`.
The standalone source replaces its old private header and nine fragments.
No shared gameplay header, callee implementation or accepted consumer changed.

## Previously completed Fighter `+0x28` roots

- **Youmu (`0x00530200`)**: 37,692 callable / 38,816 envelope bytes,
  98/98 owners, unit `gpt-web-youmu-vslot28-full-root` (`7bad1ce8`).
- **Aya (`0x00602250`)**: 65,601 callable / 66,704 envelope bytes,
  107/107 owners, unit `exact-first-aya-action-state` (`c640faf9`).
- **Iku (`0x00620920`)**: 59,038 callable / 60,194 envelope bytes,
  109/109 owners, unit `gpt-web-iku-action-state` (`ee6a5e7f`).
- **Reimu (`0x00478FA0`)**: 81,550 callable / 82,924 envelope bytes,
  unit `neon-reimu-action-state-root` (`473165f6`).

## Next useful action

Continue with Sakuya `0x004CADB0`, one bounded root at a time. Read its candidate
and reconstruct its own switch envelope before applying the playbook. The user
wants the remaining giant roots completed individually to canonical exactness.

The five accepted roots retain character-scoped receiver views. A future shared
layout/header change must recompare its directly affected accepted units.
