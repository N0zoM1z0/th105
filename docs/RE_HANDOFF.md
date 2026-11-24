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

## Active root lock — Reimu Fighter vslot28 (2026-11-24)

- **Only active target:** `Reimu_dispatch_action_state_vslot28` at `0x00478FA0` (81,550-byte callable). Do not select another function until this root receives formal exact acceptance.
- **Natural C++ candidate:** `src/characters/ReimuActionStateRoot.cpp`, declared by `src/characters/ReimuActionStateStaging.hpp`; `config/functions.csv` now points the root row at that source. The source is the full void-root candidate, not the earlier bool staging helper.
- **Focused evidence:** a fresh clean-HEAD VC8 `/O2 /GS-` replay compiles the natural C++ candidate to an 81,548-byte callable code prefix (target: 81,550 bytes; complete object `.text`: 82,920 bytes). Action 300 is emitted as a distinct `if/else` direct arm between the low-action table and the 301..560 table; the entry has the target `jg` then `je` branch polarity. The source-shape comparison retains all 126 target destination groups with zero split groups. Monitored direct-call counts have zero deltas, and root stack/buffer partition plus request-preparation audits report zero mismatches. The committed `ReimuActionStateRoot.cpp` is byte-for-byte object-text identical to the freshly generated fragment candidate. These are focused codegen/structure checks, not exact acceptance.
- **Provider ownership:** root call `0x004776C0` is bound to `private-reimu-word48a`, not the competing public leaf-setter view. This is recorded in `config/reimu-root-probe-bindings.toml` and is only a root-local provider choice. The shared action-advance call at `0x004351C0` is also named through the `CharacterObjectRuntime` view where that base runtime owns the operation.
- **Current codegen gap:** the first target mismatch is `0x004791E2`, in the relative displacement of the `jg` to the middle-table entry. The branch opcodes and `jg`/`je` polarity match the target: target branches to the middle-table entry at `0x0047CC5F` and direct action-300 body at `0x0047CBBD`; the candidate reaches `0x0047CC80` and `0x0047CBE0` respectively. The candidate code prefix is 2 bytes shorter than target. Action 320 remains 33 bytes short because the ordinary Reimu-view call is tail-merged into the action-300 frame-advance/set-action tail. Its flag test now uses a direct `byte_47e == directional_result_320` C++ comparison, which emits the target `cmp BYTE PTR [esi+0x47e], al` rather than the previous volatile-load/test pair. Target action 300 owns a distinct `0x004351C0` call at `0x0047CC17`; target action 320 owns another at `0x0047D9C4`. Both test the result, optionally call virtual `set_action(0)`, then branch to the shared event tail at `0x0047CC2B` (frame-timer/frame-index gate, event 27, and flag clear). Aggregate call counts alone can hide this ownership mismatch. An explicit `CharacterEx` base-method alias keeps the call local to action 320, but VC8 duplicates it at two local sites across the friction branch, yielding 124 vs 121 monitored calls and 78 bytes of stack-envelope excess; this spelling was rejected and restored. Action 416 is now 17 bytes short (down from 25) after expressing its sequence-0/sequence-2 gravity gates as a mutually exclusive `if/else-if`; the common path now precedes the out-of-line gravity block, matching the target's block order. Its remaining codegen difference is the frame-constant allocation (`mov ebp,4`/`mov ebx,1` in target versus an immediate compare and `lea ecx,[edi-2]` in the candidate). Action 414 is 1 byte long and action 541 is 3 bytes short; actions 301, 321, 418, 540, 545 and 546 retain their target spans. Action 740 remains semantically provisional. These are active root-local investigations, not padding opportunities.
- **Action 740 comparator refinement (2026-11-24):** rewrote the cadence/limit predicate from `word_730 < limit` to the equivalent `limit > word_730`. Fresh VC8 output now uses the target operand order `cmp edi,eax; jle` at the spawn-limit gate, rather than the candidate's former `cmp eax,edi; jge`. The focused root remains 81,548 callable bytes and action 740 remains 533/535 bytes; this aligns one real comparison sequence, not the whole action or its stack fallback semantics.
- **Exactness status:** **not exact**. The root is still locked; action 740 remains a known semantic risk. Do not award exact or implementation credit until the complete callable and its owned data pass the canonical Factory acceptance.
- **Recent commits:** `gpt-web: sync Reimu action300 branch source`; `gpt-web: align Reimu action300 branch polarity`; `gpt-web: record Reimu action 320 tail merge lead`; `gpt-web: model Reimu action 300 direct arm`; `gpt-web: share Reimu action 416 and 546 exit tail`; `gpt-web: align Reimu root call ownership and low dispatch`; `gpt-web: refine Reimu 414 and 416 exit paths`; `gpt-web: add Reimu vslot28 C++ root candidate`; `gpt-web: match Reimu action320 byte compare`; `gpt-web: align Reimu action416 gravity gates`.
- **Work rule:** keep this function locked, use focused root/provider replay only, and do not claim implementation/exact credit until the Factory accepts the complete root.
