# TH10.5 reconstruction handoff

Reconstruct the original Japanese TH10.5 v1.06a PE, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Follow [AGENTS.md](../AGENTS.md) and keep all work headless. Use the
[shared runtime](SHARED_TOOLS.md), this repository's Wine prefix and one
writable reconstruction scope at a time. Keep VC8 and Ghidra runs serial.
The hash-attested PE is sufficient for raw control-flow and byte work.
Attest an analysis session before using its database evidence.

For a reconstruction change, start from the live ledgers and target.

```bash
export DISPLAY= WAYLAND_DISPLAY=
git status --short
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/report-reconstruction-status.py --summary
scripts/repo-python scripts/validate-tracking.py --require-target
```

## Current large-function work

- **Sakuya Object update `0x004E0D30`** has complete selected source.
  The focused build first differs at `0x004E0D55`. The target owns 28,985
  callable bytes and a 29,476-byte envelope with seven tables. The
  29,480-byte candidate resolves 742 relocations and preserves all 17
  animation-advance call owners. The action 900 entry guard already
  pairs after rebasing. Its earlier Y loads change the x87 operand order
  in the later landing sum. Compare the memory definitions entering
  `c2.dll:0x10BAF600`. Action 853's sequence-6 alpha exit still reaches
  the 805 retirement copy. [Landing sum](SAKUYA_OBJECT_UPDATE_2026_10_25.md#the-entry-y-bounds-affect-the-landing-sum)
  and [retirement sharing](SAKUYA_OBJECT_UPDATE_2026_10_25.md#action-853-retirement-is-shared-with-action-805-in-the-rebuild).
- **Sakuya Object initializer `0x004E8060`** differs at 13 bytes in 803.
  Omitting 800 or 801 in scratch restores the original register choices.
  The 801 facing-byte load advances the allocator's search position
  before the 803 virtual-target load. [Allocator trace](SAKUYA_OBJECT_ENTRY_2026_10_24.md#the-allocator-carries-a-register-search-position-between-cases).
- **Komachi Fighter update `0x005E20E0`** has a complete configured
  candidate with seven tables. The first difference is `+0x2A`, where
  the target defines EBX before the card gate. That value reaches several
  action bodies. The VC8 graph also discovers the shared 209/212 flight
  through 212 first. Reimu `0x00478FA0` has partial sources in
  `src/characters/ReimuActionState*` and needs a selected whole-root unit.
  [Komachi card bound](KOMACHI_ACTION_STATE_2026_10_28.md#the-card-bound-is-live-across-the-dispatcher).

```bash
scripts/repo-python scripts/build.py --unit exact-first-sakuya-object-update --compare --json
scripts/repo-python scripts/build.py --unit exact-first-komachi-action-state --compare --json
```

Other open scopes include Alice CPU policy `0x004F4B80`, the roster
control-mode functions (including Aya `0x00616800` and Patchouli
`0x0051CB40`), the Marisa, Patchouli and Yuyuko object entries, Marisa
CPU dispatch `0x004B4070`, and scenario character install `0x00456EB0`
(one EH-state store).

For LTCG work, `MenuCursorState::update` at `0x0041FA20` takes a
propagated period from 35 callers. The angle lookups at `0x00406360` and
`0x004063D0` may share that context. The text-texture pair `0x00404D00`
and `0x004097A0` differs in the private width parameter. The gain
conversion `0x00418990` retains two additional float round-trips. The
ACK CIL context still needs the real IPacket providers. The design loader
differs in frame and body size. [Design loader context](DESIGN_LOADER_REAL_GAGE_2026_11_02.md).

## Verified examples to reuse

- **Shared Fighter `0x004740C0`** uses one action switch. Selector operand
  identity gives the original `SUB` encodings, and the switch exits
  recover the shared tail owners. [Compiler trace](COMMON_FIGHTER_VC8_LAYOUT_2026_11_23.md).
- **Info effect update `0x0065CB40`** recovers the early retirement
  through return ordering. A reference-based fade helper preserves both
  frame reads in 900–922. [Case note](INFO_EFFECT_UPDATE_2026_10_27.md#the-retirement-order-and-frame-references-that-match).
- **Youmu Fighter initializer `0x0053A1D0`** keeps independent publishing
  and reset paths in source. The first successful VC8 tail comparison
  saves a length that lets the second merge pass. [Case note](YOUMU_FIGHTER_ACTION_INITIALIZATION_2026_10_25.md#case-order-preserves-both-tail-merges).

Use the [TH075, EFZ and TH09 review](GIANT_ROOT_REVIEW_2026_11_23.md) and
[VC8 source-shape patterns](VC8_SOURCE_SHAPE_PATTERNS.md) for comparisons.
Locate divergences by reachable action and physical tail owner. A change
in an earlier action, global use or visible callee can change code elsewhere
in the same function. Prefer checked typed members where the access widths
and receiver layout are independently supported.

Run the [complete affected comparisons](RE_WORKFLOW.md#shared-change-replay)
after changing shared inputs. Exact credit comes from the full callable,
owned switch data and relocations recorded in the match unit. Generated
objects and listings can be rebuilt from their pinned inputs. Keep private
trace inputs when they are needed to reproduce a live lead.
[Local artifact policy](ARTIFACTS.md).
