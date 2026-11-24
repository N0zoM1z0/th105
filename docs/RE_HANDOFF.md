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
- **Focused evidence:** a fresh VC8 `/O2 /GS-` replay compiles the natural C++ candidate to an 81,596-byte callable code prefix (target: 81,550 bytes; complete object `.text`: 82,968 bytes). The source-shape comparison retains all 126 target destination groups with zero split groups. Root stack/buffer partition and request-preparation audits previously reported zero mismatches; current focused changes are still provisional codegen work, not exact acceptance.
- **Provider ownership:** root call `0x004776C0` is bound to `private-reimu-word48a`, not the competing public leaf-setter view. This is recorded in `config/reimu-root-probe-bindings.toml` and is only a root-local provider choice. The shared action-advance call at `0x004351C0` is also named through the `CharacterObjectRuntime` view where that base runtime owns the operation.
- **Current codegen gap (fresh direct-root VC8 `/GL + /LTCG` replay):** the earliest mismatch is the `jne` displacement at `0x004791BD`: target branches to the shared epilogue at `0x00489D6A`, while the linked candidate branches to `0x00489D9A` (48 bytes later). The later selector `jg`/`je` still target `0x0047CC5F`/`0x0047CBBD`, while the candidate reaches `0x0047CC82`/`0x0047CBE0`. Action 300 emits the target x87 clamp sequence (`fldz; fcom st(1); fnstsw; fstp st(1); test ah,0x41`) and a 162-byte direct-arm span, but its entry is 35 bytes late. The **tracked** Action 320 source still uses the explicit vtable-slot view: its local span is 119/119 bytes and its `byte_47e`/`AL` comparison matches, but the virtual-slot load is EAX→EDX (target: EDX→EAX) and its event-27 tail is emitted locally after Action 320 rather than branching to `0x0047CC2B`. A temporary shared-label variant using natural `set_action(0)` produced the target EDX→EAX order, but ordinary VC8 duplicated the event tail; direct-root LTCG did not establish the required backward edge. A selector-switch experiment could coalesce the tail only by moving Action 320 into the low code region and adding selector dispatch. None of these variants is promoted. The complete tracked-root callable prefix is 46 bytes longer than target (81,596 vs 81,550). Action 414 is 5 bytes long, 416 is 21 bytes short, 541 is 3 bytes short, 546 matches its target span, and action 740 remains 533/535 bytes with the invalid-mode stack-spill path semantically provisional. These are root-local source/codegen differences, not padding opportunities.
- **Action 740 comparator refinement (2026-11-24):** rewrote the cadence/limit predicate from `word_730 < limit` to the equivalent `limit > word_730`. Fresh VC8 output now uses the target operand order `cmp edi,eax; jle` at the spawn-limit gate, rather than the candidate's former `cmp eax,edi; jge`. The focused root is currently 81,596 callable bytes and action 740 remains 533/535 bytes; this aligns one real comparison sequence, not the whole action or its stack fallback semantics.
- **Exactness status:** **not exact**. The root is still locked; action 740 remains a known semantic risk. Do not award exact or implementation credit until the complete callable and its owned data pass the canonical Factory acceptance.
- **Recent commits:** `gpt-web: sync Reimu action300 branch source`; `gpt-web: align Reimu action300 branch polarity`; `gpt-web: record Reimu action 320 tail merge lead`; `gpt-web: model Reimu action 300 direct arm`; `gpt-web: share Reimu action 416 and 546 exit tail`; `gpt-web: align Reimu root call ownership and low dispatch`; `gpt-web: refine Reimu 414 and 416 exit paths`; `gpt-web: add Reimu vslot28 C++ root candidate`; `gpt-web: match Reimu action320 byte compare`; `gpt-web: align Reimu action416 gravity gates`.
- **2026-11-24 focused continuation:** Action 320 remains the only active local target. The tracked typed vtable-slot `+8` view emits a 119-byte span and the direct `byte_47e`/`AL` comparison, but its load order and tail ownership still differ from the target. The shared-label `set_action(0)` experiment fixes the load order but does not yet preserve the target's single backward edge to the Action 300 tail. No assembly or padding is used.
- **Direct-root LTCG verification (2026-11-24):** `scripts/probe-reimu-action-ltcg.py --direct-root-source` now compiles and links the committed `src/characters/ReimuActionStateRoot.cpp` with its tracked `ReimuActionStateStaging.hpp`; `scripts/audit-reimu-linked-coff.py` accepts this distinct provenance schema and verifies both copied inputs. This corrects the older default shape replay, which generated `ReimuActionStateDispatch.cpp` from 19 fragments and did not compile the committed root TU. Fresh direct-root VC8 `/GL` replay and ordinary/linked payload correspondence pass (82,968-byte payload, 81,596-byte code prefix, 11 switches, zero buffer-partition mismatches); this remains diagnostic and not target exactness. The first direct-root byte mismatch is `0x004791BD` (`jne` destination `0x00489D9A` vs target `0x00489D6A`). Action 320 is 119/119 bytes and retains its own advance call, but the virtual `+8` slot load is EAX→EDX rather than target EDX→EAX, and the event-tail jump lands 35 bytes after target `0x0047CC2B`.
- **Direct-root LTCG evidence (2026-11-24):** `scripts/probe-reimu-action-ltcg.py --direct-root-source` compiles the tracked complete `ReimuActionStateRoot.cpp` and staging header, rather than substituting the older fragment-generated candidate. The independent linked-COFF audit passes for the tracked-root baseline: 82,968-byte payload, 1,189 direct-call relocations, 11 switches, zero buffer-partition mismatches, and exact linked/ordinary payload correspondence. This is not target exactness; the first target mismatch is `0x004791BD`. Reproduce with `scripts/probe-reimu-action-ltcg.py --direct-root-source --output-dir build/reimu-root-work/ltcg-direct-root-20261124`; the receipt and replay report are in that directory. The temporary shared-label LTCG experiment is separate and not the tracked source.
- **Action 740 input provenance:** `CSelectScenario::on_scene_enter` seeds `MatchSetup.game_type` from `GameConfig.default_game_type` at `0x006FC5FC`; the four-choice cursor updates that field over 0..3. `prepare_match_runtime_by_mode` publishes it into `MatchSetup.match_identifier_00`, and `BattleControllerSetup` copies it to `g_match_identifier` at `0x006FA894`. The original out-of-range stack-spill path is retained for invalid persisted values; the bounded mode constants and spill reads are separately checked by `scripts/reimu_740_mode_facts.py`.
- **Work rule:** keep this function locked, use focused root/provider replay only, and do not claim implementation/exact credit until the Factory accepts the complete root.
