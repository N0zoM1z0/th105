# TH10.5 reconstruction handoff

Target executable: original Japanese TH10.5 v1.06a, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Follow [AGENTS.md](../AGENTS.md), [the shared runtime](SHARED_TOOLS.md) and
[the reconstruction workflow](RE_WORKFLOW.md). Keep this game's Wine prefix,
analysis projects and private worktrees; run compiler and analyzer jobs
serially.

## Completed: Aya Fighter `+0x28` action-state root (`0x00602250`) and Giant-Root Playbook

`Aya_dispatch_action_state_vslot28` at `0x00602250` is now **100% canonically
exact** under VC8 SP1 `/O2 /GS- /GR /EHsc /MT` in match unit
`exact-first-aya-action-state`:

- **Source**: [AyaActionState.cpp](../src/characters/AyaActionState.cpp)
  (standalone typed `AyaActionStateView` and `AyaPeerView` layouts with
  compile-time `offsetof` assertions; obsolete `AyaActionState.hpp` removed).
- **Exact envelope**: 65,601 callable bytes (16,856 instructions, 107/107
  instruction/edge-identical owners), 1,103 metadata bytes (3 compact
  byte-index switch tables: 33/27/48 entries, 584 index bytes, plus 4 direct
  jump tables in actions `720`, `721`, `740`, `791..798`, and original
  `8d4900`/`90`/`8bff` alignment padding), total 66,704 bytes
  (`0x00602250..0x006126E0`), 2,133 relocations (1,011 direct calls across 33
  targets), zero byte differences.
- **Canonical SHA-256**: callable
  `04c7620574e00d6f05bb615a095188ee2c60e94cc9d94dbad2eed56b92ab7fd5`; complete
  66,704-byte switch envelope
  `42401b4701e475fbaab7d19a542aec6edbe503082a2a0dc2a2e22407e71903a3`.
- **Reusable methodology & tooling**:
  - [GIANT_ACTION_ROOT_PLAYBOOK.md](GIANT_ACTION_ROOT_PLAYBOOK.md) documents
    the reusable 5-step opening pass, shared Fighter offsets, VC8 `c2.dll`
    rules (`TailMerge`, `WidenBranches`, LIFO stack-slot packing), and
    promotion checklist.
  - [scripts/giant-root-iterate.py](../scripts/giant-root-iterate.py) provides
    single-command compile, per-owner audit, call-count census, and disassembly
    diffs for any root in `config/giant-action-switches.toml`.
  - [scripts/coff_switch_payload.py](../scripts/coff_switch_payload.py) now
    defers conditional jumps inside a register-bound span to the existing sound
    CFG reaching-constant check (`verify_cfg_register_bound`), with positive
    and negative unit tests in
    [tests/test_coff_switch_payload.py](../tests/test_coff_switch_payload.py).
- **Verification**:
  ```bash
  WINEDEBUG=-all DISPLAY= WAYLAND_DISPLAY= scripts/repo-python scripts/build.py --unit exact-first-aya-action-state --compare --json
  scripts/repo-python scripts/audit-giant-action-owners.py --unit exact-first-aya-action-state aya-vslot28 build/match-units/ExactFirst_AyaActionState.obj
  scripts/repo-python -m unittest tests/test_coff_switch_payload.py
  ```

## Previously completed Fighter `+0x28` action-state roots

- **Iku (`0x00620920`)**: `Iku_dispatch_action_state_vslot28` (59,038 callable /
  60,194 envelope, 3 switch tables, 109/109 exact owners, 1,770 relocations) is
  100% canonically exact in `gpt-web-iku-action-state` (`ee6a5e7f`).
- **Reimu (`0x00478FA0`)**: `Reimu_dispatch_action_state_vslot28` (81,550
  callable / 82,924 envelope, 11 switch tables, 2,477 relocations) is 100%
  canonically exact in `neon-reimu-action-state-root` (`473165f6`).

## Next useful action

Apply [GIANT_ACTION_ROOT_PLAYBOOK.md](GIANT_ACTION_ROOT_PLAYBOOK.md) and
[scripts/giant-root-iterate.py](../scripts/giant-root-iterate.py) to the next
roster Fighter `+0x28` action-state root (e.g., Marisa `0x004A3DF0`, Sakuya
`0x004CADB0`, Alice, Patchouli, Youmu, Remilia, Yuyuko, Yukari, Suika, Reisen,
Komachi, or Tenshi).

## Open notes

- `ReimuActionStateRoot.cpp`, `IkuActionState.cpp`, and `AyaActionState.cpp`
  use character-scoped typed receiver views rather than a unified
  cross-character `Fighter` header. Any future shared-header unification must
  re-verify all three exact units for zero differences.
- `scripts/probe-iku-action-ltcg.py` is a diagnostic LTCG probe that references
  `gpt-web-iku-action-state`; its old `AnimationSequenceObjectView` helper
  selection is superseded for exact matching now that standalone COFF
  `gpt-web-iku-action-state` is 100% exact.
