# TH10.5 reconstruction handoff

Target executable: original Japanese TH10.5 v1.06a, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Follow [AGENTS.md](../AGENTS.md), [the shared runtime](SHARED_TOOLS.md) and
[the reconstruction workflow](RE_WORKFLOW.md). Run compiler/analyzer jobs
serially and preserve this game's Wine prefix and private analysis state.

## Completed: Youmu Fighter `+0x28` action-state root (`0x00530200`)

`Youmu_dispatch_action_state_vslot28` is canonically exact in
`gpt-web-youmu-vslot28-full-root`, compiled with VC8 SP1
`/O2 /GS- /GR /EHsc /MT` from
[YoumuActionState.cpp](../src/characters/YoumuActionState.cpp).

- All 37,692 callable bytes and the complete 38,816-byte envelope
  (`0x00530200..0x005399A0`, exclusive end) match with zero differences.
  Metadata comprises three compact switches, action720's direct switch,
  707 byte indices, 103 destination words and the original alignment.
- All 1,126 relocations are replayed: 598 REL32 calls across 29 targets and
  528 DIR32 relocations. The owner audit is 98/98; raw control flow reaches
  all 9,912 instructions with no unresolved indirect exits.
- Callable SHA-256:
  `19f2d4fba4f6ea626b69a28f4717d0fcfae06ea97e95ddb24e656e0ea518ed74`.
  Complete envelope SHA-256:
  `07283bd567ce8a199d6d14db90f27218521b465e4a7a2954c231ae9b259b16b3`.

Reproduce acceptance with:

```bash
WINEDEBUG=-all DISPLAY= WAYLAND_DISPLAY= scripts/repo-python scripts/build.py --unit gpt-web-youmu-vslot28-full-root --compare --json
scripts/repo-python scripts/audit-giant-action-owners.py --unit gpt-web-youmu-vslot28-full-root youmu-vslot28 build/match-units/GptWeb_YoumuActionState.obj
```

The [giant-root playbook](GIANT_ACTION_ROOT_PLAYBOOK.md#youmu-source-shape-findings)
records the useful new findings: float member copies affected global stack
packing; cached opponent pointers changed load scheduling; and combining two
independent early exits changed both physical tail selection and volatile
register allocation. Original source spelling remains unknown.

`coff_switch_payload.py` now verifies action720's flag-preserving
`mov edx, immediate; lea ecx, [edx+disp]` between CMP and JA while protecting
the selector and rejecting jumps into that setup. Its 22 focused tests pass.
Existing Aya, Iku and Reimu objects retain complete canonical exact comparisons
with the updated verifier; these were object rechecks, not fresh compiler builds.

## Previously completed Fighter `+0x28` roots

- **Aya (`0x00602250`)**: 65,601 callable / 66,704 envelope bytes,
  107/107 owners, unit `exact-first-aya-action-state`.
- **Iku (`0x00620920`)**: 59,038 callable / 60,194 envelope bytes,
  109/109 owners, unit `gpt-web-iku-action-state` (`ee6a5e7f`).
- **Reimu (`0x00478FA0`)**: 81,550 callable / 82,924 envelope bytes,
  unit `neon-reimu-action-state-root` (`473165f6`).

## Next useful action

Apply the playbook and `scripts/giant-root-iterate.py` to another roster Fighter
root, for example Sakuya `0x004CADB0` or Marisa `0x004A3710`. Check its own
field widths and call arguments before transferring a source shape.

The four accepted roots retain character-scoped receiver views. A future shared
layout/header change must recompare its directly affected accepted units. No
shared gameplay header or callee implementation changed in the Youmu work.
