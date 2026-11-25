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
- **Action 300/320 shared-tail experiments (2026-11-24):** the source-shape generator's `--single-switch --void-root` path was compiled and then replayed through direct-root LTCG by temporarily substituting both generated root source and staging header; the tracked files were restored afterward. Its 81,548-byte callable prefix is 2 bytes shorter than target, retains all 126 switch destination groups with zero split groups, and the direct linked/ordinary payload audit passes (82,920-byte payload, 1,283 HIGHLOW fields, 11 switches, zero buffer-partition mismatches). It is not exact: first mismatch remains `0x004791BD` (target displacement byte `a9`, candidate `99`, 16-byte epilogue displacement delta); Action 300 entry is 20 bytes late and its x87 clamp differs (`fcomp qword` path vs target `fldz/fcom st(1)/fstp st(1)`); Action 320 is 41 bytes early and spans 162 vs target 119 because VC8 moves the shared event tail after Action 320 instead of retaining the target backward edge to `0x0047CC2B`. A case-order experiment moving Action 320 before Action 300 moves its code 3,335 bytes early and is rejected. Separate-switch goto variants, including `do/while`, `switch` completion and volatile event-tail field reads, still have VC8 move the tail after Action 320; volatile timer/index accesses also introduce extra register loads. The 81,548-byte volatile-zero experiment is also rejected because it changes Action 300's target x87 compare sequence. None of these experiments replaces the tracked root. Reproduce the best single-switch replay with `scripts/probe-reimu-action-source-shape.py --void-root --single-switch --output-dir build/reimu-root-work/source-shape-single-switch-20261124`, then the direct-root probe using that generated `ReimuActionStateDispatch.cpp` and `ReimuActionStateStaging.hpp` as temporary tracked inputs; the preserved direct replay is in `build/reimu-root-work/ltcg-action320-single-switch-20261124`.
- **Action 740 input provenance:** `CSelectScenario::on_scene_enter` seeds `MatchSetup.game_type` from `GameConfig.default_game_type` at `0x006FC5FC`; the four-choice cursor updates that field over 0..3. `prepare_match_runtime_by_mode` publishes it into `MatchSetup.match_identifier_00`, and `BattleControllerSetup` copies it to `g_match_identifier` at `0x006FA894`. The original out-of-range stack-spill path is retained for invalid persisted values; the bounded mode constants and spill reads are separately checked by `scripts/reimu_740_mode_facts.py`.
- **Work rule:** keep this function locked, use focused root/provider replay only, and do not claim implementation/exact credit until the Factory accepts the complete root.

## 2026-11-24 current continuation — Reimu single-switch root

The active tracked source `src/characters/ReimuActionStateRoot.cpp` remains the
full void-ABI, single-outer-switch natural C++ candidate. The tracked staging
header is unchanged. Action 300 and Action 320 use one source-level
`reimu_action_300_320_event_tail` label: both action bodies advance through
their own call sites and jump to the same event-27/reset tail. This is ordinary
C++ control flow, not duplicated code, inline assembly, or padding.

The function-scope `landing_sequence` spill has now been removed. Actions 197
and 198 share an explicit sequence-2 completion label; Actions 608 and 658
write sequence 3 in their own landing tails. This keeps the shared completion
behavior in natural C++ while removing a cross-case local that was forcing a
larger root layout.

Latest direct-root VC8 `/O2 /GS- /GL + LTCG` replay after that change:

- Target callable: 81,550 bytes; candidate callable: 81,564 bytes (14-byte
  excess). Complete replay payload: 82,936 bytes; 1,283 HIGHLOW fields;
  11 switches; linked and ordinary payloads agree; zero ordinary buffer
  partition mismatches.
- First mismatch remains `0x004791BD`: target displacement byte `a9`,
  candidate `a7`. The early shared-exit destination is now only 2 bytes apart,
  down from 16 bytes in the previous layout. This is not exact acceptance.
- Entry offsets for Actions 619, 650, 658, 710, 711, and 720 now align with
  their target entries. Action 616 is 2 bytes early and retains the audited
  seven-entry unsigned `(sequence - 1)` switch. Its two request sites have
  identical target/source stack-buffer partitions.
- Remaining large local layout differences include Action 416 (candidate
  span 922 vs target 959 bytes) and Action 608 (776 vs 810 bytes). These are
  the next source-level control-flow areas to investigate within this same
  function.
- The expanded source exceeds the old diagnostic envelope by 14 callable
  bytes and 12 metadata bytes. The root relocation/stack audit therefore ran
  explicitly in read-only `--diagnostic-oversize` mode. It recognized all 8
  auxiliary switch bounds, with zero buffer-partition and request-preparation
  mismatches. This mode is diagnostic only, not execution or exactness credit.

TH075 remains a structural reference only: its exact Reimu Fighter Advance
`0x0045DD70` (60,999 bytes) uses a shared `goto` label inside a switch under
VC7.1 `/Od /Ob0`. That supports natural C++ shared exits, not a compiler-profile
assumption for TH105's VC8 root.

**Lock unchanged:** `Reimu_dispatch_action_state_vslot28` at `0x00478FA0` is
the only active function. Continue until the complete callable and owned data
receive formal exact acceptance. Do not switch to another function. No ASM,
padding, or exactness claim is made by this checkpoint.

## 2026-11-24 Action616 default-continuation correction

The active function remains `Reimu_dispatch_action_state_vslot28` at
`0x00478FA0`; no function switch. Action 616's seven-entry sequence table is
indexed by signed `sequence - 1` and guarded by an unsigned upper-bound branch.
The nested table's `ja` target is **not** a function return: target
`0x00489C58` branches to `0x00489EF3`, where the shared post-switch action
continuation begins (`sub_4351C0` and subsequent frame/event handling).
Therefore `default: return;` was semantically wrong. The natural C++ source now
uses `default: break;`, preserving the continuation for out-of-range sequence
values.

Fresh direct-root VC8 `/O2 /GS- /GL + LTCG` replay after this correction:

- Candidate callable prefix: **81,564 bytes** (14 bytes beyond the 81,550-byte
  target); complete replay payload 82,936 bytes; 1,283 HIGHLOW fields; 11
  switches; all 126 target destination groups retained.
- Linked and ordinary replay payloads agree byte-for-byte; ordinary request
  buffer partition mismatches remain zero.
- The first whole-root mismatch remains `0x004791BD`, but the candidate byte is
  now `a7` against target `a9` (a 2-byte branch-displacement delta, previously
  `99`). This is not exact acceptance.
- Action 658's candidate entry and 740-byte span now exactly match the target;
  only 6 bytes differ. Action 619's entry and 490-byte span also align, with 6
  byte differences. Action 616 remains 2 bytes early at entry and spans 1,087
  versus 1,085 target bytes.
- Read-only diagnostic-oversize Action 616 stack/request audit: all 8 source
  auxiliary bounds qualify; two target and two source request sites use the
  same stack offsets `0x3F0` and `0x408`; zero buffer-partition mismatches and
  zero request-preparation mismatches.

The Action 616 default correction is a semantic fix, not an exactness claim.
The 14-byte callable excess and remaining byte differences are open; do not
widen the reviewed callable envelope or award canonical exact credit.

- **2026-11-24 shared landing-tail ownership correction:** the target root has two distinct natural C++ landing-tail owners, not one common tail for Actions 197/198/199. Action 197 branches to the tail in Action 658 (`0x0048A701`); Action 198 branches to the tail in Action 608 (`0x00488FD5`). Each caller carries sequence 2 or 3 in the same callee-saved register; the owning 608/658 case supplies 3. Action 199 has no reachable gravity/landing branch. The tracked C++ now expresses those two `goto` relationships with a function-local `landing_sequence` assigned on every reachable owner path. A focused ordinary VC8 compile retains all 126 destination groups with zero split groups and a 81,548-byte code prefix (target 81,550). Action 198 and Action 608 spans now both match exactly (305 and 810 bytes); their remaining 15 and 17 byte differences are relocation/layout displacements while their entry offsets are still displaced. Action 658 remains 740/740 bytes with 18 byte differences, chiefly because its entry and three shared destinations are not yet aligned. Action 616's post-switch default remains a continuation (`break`), not an early return. This is not root exactness.

## 2026-11-24 direct-root provenance and shared-landing checkpoint

- Fixed `scripts/probe-reimu-action-ltcg.py --direct-root-source` so its
  `ReimuRoot.cpp` copy preserves the tracked translation unit's exact bytes.
  The old unconditional LF-to-CRLF conversion made the linked-COFF auditor
  reject an otherwise valid direct-root link as `linked direct root source
  copy changed`. Fragment-generated probes retain their historical CRLF copy.
- The repaired direct-root VC8 `/GL + LTCG` probe now passes the complete
  linked/ordinary payload correspondence and provenance audit for the tracked
  root. Current payload is 82,920 bytes, callable code prefix 81,548 bytes,
  1,283 HIGHLOW fields, 11 switches, and zero ordinary buffer-partition
  mismatches. This is diagnostic, not target exactness.
- First target mismatch is still `0x004791BD` (`99` candidate vs `a9` target),
  a 16-byte early shared-exit destination. The current function-scope
  `landing_sequence` variable preserves Action197->658 and Action198->608
  landing-tail ownership, but direct-root layout places Actions 608/616 16
  bytes early and Action658 14 bytes early. A smaller natural-C++ register
  representation is the next focused experiment; no assembly or padding.

## 2026-11-24 Action520 shared next-sequence tail — current root focus

The only active function remains `Reimu_dispatch_action_state_vslot28` at
`0x00478FA0`. No function switch is permitted until the complete root receives
canonical exact acceptance.

The next-sequence return topology is now resolved at the instruction level:

- The target's shared slot-`+0x14` call is at `0x004852F6` (root-relative
  `0xC356`), immediately before the common epilogue. Eighteen branches reach
  it from `0x00479C22`, `0x0047A54D`, `0x0047D273`, `0x0047F714`,
  `0x0047FCAB`, `0x004800CB`, `0x00485DF3`, `0x00485E06`, `0x0048604F`,
  `0x00486062`, `0x004863A6`, `0x00488C65`, `0x00488FAB`, `0x004892B2`,
  `0x004892BF`, `0x004892D2`, `0x004893C0`, and `0x0048A282`.
- Action 410 has two distinct completion paths. Its first local call at
  `0x0047F59A` uses `mov edx,[esi]; mov eax,[edx+0x14]; call eax`, then its
  own epilogue. Its later sequence/counter path branches at `0x0047F714` to
  the Action520 shared call at `0x004852F6`. Actions 414 and 416 likewise
  must not have their first local call blindly merged with their shared path.
- The tracked natural-C++ baseline currently merges Action410's local call
  with the external shared-tail callers at ordinary-object offset `0x661D`
  (`mov eax,[esi]; mov edx,[eax+0x14]; call edx`). Action520's own local
  call remains separately emitted at `0xC338`. Thus the external edges land
  at the wrong tail even though the call instruction itself is valid.
- Action608 is a useful focused witness: its target and candidate spans are
  both 810 bytes and its 210 decoded instructions align. The target branch at
  `0x00488FAB` reaches `0x004852F6`; the candidate branch at object offset
  `0xFFFB` reaches `0x661D`. Sixteen of the 17 raw byte differences in this
  span are relative-call displacements caused by the entry offset; the
  remaining control-flow edge is the shared-tail ownership mismatch.
- The Action520/521 final-spawn backward edge is already represented by the
  tracked C++ baseline. Target Action521 jumps `0x0048561C -> 0x004852AD`;
  the candidate jumps `0xC65E -> 0xC2EF`. Do not rewrite that already-correct
  shared spawn tail while solving the separate next-sequence return tail.

Focused natural-C++ experiments were compiled in the ignored
`build/reimu-root-work/action616-codegen-experiments-20261124/` directory only;
none was promoted to tracked source:

- Routing the 14 external source call sites through an explicit Action520
  label caused VC8 to clone/move the tail into a later case, rather than
  preserving the target's Action520 ownership.
- Extracting the final Action520/521 spawn block into a new shared source
  label retained an 81,548-byte callable prefix, but the compiler placed the
  new label after Action521. This was rejected; the baseline already has the
  correct Action521-to-Action520 backward spawn edge.
- Changing Action410's first local `break` to `return` separated some control
  flow but moved the local tail into a later code region and shortened its
  mapped span. It is not a promoted fix.
- An alternate void-returning view for the same virtual slot did not prevent
  the compiler from coalescing the local and shared tails.

The current direct-root baseline remains 81,548 callable bytes versus the
81,550-byte target, retains all 126 destination groups with zero split groups,
and is still **not exact**. The next source experiment must preserve Action410's
local return as its own tail while making only the later branch callers reach
Action520's existing tail. No ASM, padding, or diagnostic-size widening.

## Action520/521 return-tail revalidation (2026-11-24)

The active function remains `ReimuActionStatePreludeView::run_action_dispatch_root()`; do not switch to another function until its whole callable region is exact. The currently focused mismatch is the shared `next_sequence_block()` return edge, not the Action520/521 projectile tail.

A fresh call-site count corrected an earlier suspicion: the existing natural C++ baseline already reproduces the Action520/521 fifth-spawn tail. Target Action521 contains exactly four `spawn_owned_object_via_manager` calls (`0x4853bb`, `0x48546d`, `0x4854f7`, `0x48559c`) and then jumps `0x48561c -> 0x4852ad`; the baseline candidate also contains exactly four Action521 spawn calls (`0xc3fe`, `0xc4b0`, `0xc53a`, `0xc5df`) and jumps `0xc65e -> 0xc2ef`, where Action520's shared fifth spawn, wave dispatch and frame advance begin. Preserve this baseline structure; do not rewrite or duplicate the fifth spawn.

The remaining concrete return-tail mismatch is that target external callers branch to the Action520-owned virtual call at `0x4852f6`, whereas the baseline candidate's corresponding external branches target the Action410 local completion call at `0x661d`. The candidate does already have a separate Action520-owned call at `0xc338` for Action520's own path, but external `next_sequence_block()` callers do not join it. Experiments that label the Action520 call and redirect 14 external callers cause VC8/LTCG to coalesce the call back into `0x661d`; Action521 also grows or shifts when its own terminal call is removed. These candidates remain isolated under ignored `build/reimu-root-work/action616-codegen-experiments-20261124/` and are not promoted.

Action410/414/416 each have a first local completion call followed by `break`, and a later sequence-1 call followed by `return`. The first three local paths must remain distinct; only the later calls join the Action520-owned return tail. Converting the first local `break` paths to `return` did not prevent the compiler's tail coalescing.

TH075's `ReimuFighterAdvanceF1183.cpp` demonstrates natural switch-owned shared labels (`goto native_shared_getter`) with the label in a trailing include. Its exact unit is built with VC7.1 `/Od /Ob0`; TH105's current root is built with VC8/LTCG optimization, so the idiom is useful evidence but not a drop-in codegen recipe.

Next experiment: keep the verified Action520/521 projectile tail unchanged, and isolate only the distinction between Action410's local virtual call and the Action520 shared virtual call. Continue using per-unit object builds and target-map comparisons; no full cold replay until a source candidate is close enough to justify the focused oracle run. No ASM, padding, byte grafts, or manual relocation edits.

## 2026-11-24 Action520 shared next-sequence owner recovered

The sole active function remains `Reimu_dispatch_action_state_vslot28` at
`0x00478FA0`; no other function may be selected before canonical exact
acceptance of this complete 81,550-byte root.

A focused VC8 ordinary-object experiment has now recovered the target's
shared return-tail ownership using natural C++ control flow:

- The target shared slot-`+0x14` tail is root-relative `0xC356`, exactly
  `0x360` bytes into Action520. The current candidate's Action520 begins at
  object offset `0xC018`; its shared slot call is at `0xC378`, also exactly
  `0x360` bytes into Action520. All 18 external sequence-completion edges now
  branch to `0xC378`, not to Action410's local effect epilogue at `0x661A`.
- The source keeps Action410, Action414 and Action416's first frame-three
  effect completions local by expressing their slot-`+0x14` calls through a
  typed C++ function pointer with the declared `unsigned char` return type.
  Their effect direction is carried as a register-held `int` after the
  original byte conversion. This prevents VC8 from absorbing the local effect
  completion into the shared sequence-completion tail. No assembly, padding,
  byte grafting or manual relocation edits are used.
- Action416's mapped body is now 959/959 bytes and its 235 decoded instructions
  match the target under the root-aware branch-owner normalization. Action520
  is 881/881 bytes and its 215 decoded instructions also match under that
  normalization. Action521 remains 794/794 bytes in the map.
- The complete candidate callable prefix is 81,596 bytes, 46 bytes beyond the
  81,550-byte target. All 126 target destination groups remain present with
  zero split groups. Action410 is still 964/975 bytes and Action414 is
  1,115/1,116 bytes; their remaining instruction/register differences and the
  rest of the root remain open. This is a substantial local topology recovery,
  **not** root exactness or oracle acceptance.
- This update supersedes the preceding baseline statement that the external
  sequence-completion edges still target Action410's `0x661D` tail. The
  promoted source now places those edges at Action520's own `0xC378` tail.

The promoted source was built with `scripts/compile-unit.sh` and checked only
with the root target-map/object comparison. No full cold replay was run. Keep
the active function lock unchanged and continue from the Action410/414
instruction frontiers; do not mark the root exact or change functions.

## 2026-11-24 Action404/414 action-nine tail recovered

Continue the same locked `Reimu_dispatch_action_state_vslot28` root; this is
not a function switch. The target's `set_action(9)` return tail at `0x0047EDAB`
is owned by Action404. Action414's sequence-one and sequence-three completion
branches both target that same tail.

The natural C++ source now makes the sequence-one branch jump to a label at
the sequence-three branch's `set_action(9); return;` block. VC8 emits both
branches to candidate offset `0x5E25`, the Action404-owned slot-`+0x08` call
and common epilogue. This replaces the previous duplicate local sequence-one
return path. The source change is a local `goto` between two existing
control-flow paths; no assembly or synthetic bytes are involved.

This also preserves the recovered Action520 shared sequence-completion tail:
its candidate owner is now at `0xC368`, exactly `0x360` bytes into Action520,
and the 18 external sequence-completion edges target that owner. The target
owner is root-relative `0xC356`, also `0x360` bytes into Action520.

The promoted focused object has an 81,580-byte callable prefix, 30 bytes over
the 81,550-byte target, 126 destination groups and zero split groups. Action416
remains 959/959 bytes with 235 normalized instructions exact; Action520 remains
881/881 with 215 normalized instructions exact; Action521 remains 794/794.
Action414's mapped span is now 1,102/1,116 bytes, Action410 remains 964/975,
and Action404 is 1,539/1,535. These are still open instruction/control-flow
frontiers; the root is not exact and has not received oracle acceptance.

Next work remains inside this root: close Action414's remaining register and
instruction differences, then Action410 and the surrounding drift. Keep the
full-function lock and avoid full cold replay; use only focused root object,
relocation, and affected-case checks.

## 2026-11-24 Action410 sequence-zero frame gate recovered

The active lock remains the single 81,550-byte
`Reimu_dispatch_action_state_vslot28` root. Action410 now uses a natural C++
sequence of guards around the frame-three effect and frame-eight follow-up:

- The sequence-nonzero path explicitly bypasses both sequence-zero frame gates.
  Timer-nonzero, wrong-frame, and byte-gate paths continue to the frame-eight
  check only within sequence zero. This preserves the original nested
  `sequence == 0 && timer == 0` semantics; do not collapse the sequence-nonzero
  edge into the frame-eight continuation.
- VC8 now emits the 16-bit timer load and `test ax, ax` before the frame-index
  comparison. It also emits the frame-index memory/word comparison directly,
  rather than loading the frame index into EAX first. This recovers the target's
  principal Action410 frame-gate register lifetime and branch structure.
- The candidate still compares `byte_750` with immediate zero after the
  compiler proves the timer is zero; the target compares it with `AL`. This is
  a remaining instruction-level difference, not exactness.
- Action410 maps to 970 bytes versus the target's 975 bytes. Its decoded
  instruction sequence has 245 instructions on both sides; the current
  root-aware normalized instruction ratio is about 0.93. The frame-three
  effect block is laid out as a local block later in Action410, and its x87 /
  register assignment still differs from the target. Keep working on those
  exact differences.
- The full candidate callable prefix remains 81,580 bytes (+30), with all 126
  target destination groups present and zero split groups. Action414 remains
  1,102/1,116 bytes; Action416 remains 959/959 bytes; Action520 remains
  881/881 bytes; Action521 remains 794/794 bytes. The root is not exact and
  has not received oracle acceptance.

Only the affected root object and case-map comparison were run; no full cold
replay was run. Continue on this same root and do not switch functions.

## 2026-11-24 Reimu root: shared Action0/2 and Action6-9 continuations

The active lock remains the single 81,550-byte
`Reimu_dispatch_action_state_vslot28` root. This checkpoint continues the same
function; do not switch to another function until the complete root is exact
and oracle-accepted.

Natural C++ control-flow recovery now covers another cluster:

- Action0 and Action2 share the same friction body and two distinct entries.
  Action2 is again a 27-byte entry stub into Action0's zero-velocity and
  friction continuations, rather than a duplicate full body.
- Action0's floating-point stack cleanup and normal frame-advance exits now
  route to Action9's common C++ labels. The emitted Action0/Action2 byte spans
  match the target exactly: 213/213 and 27/27.
- The Action6/7/8 landing-return sequence is shared with Action9's landing
  tail. Their spans now match exactly: 194/194, 158/158, and 158/158. Action9
  also matches its 112-byte target span. The common tail is represented by
  ordinary C++ labels and gotos; no assembly or padding was introduced.
- Action10 and Action306 also retain exact mapped spans in this candidate.
- Action410 remains 970/975 and Action414 remains 1,102/1,116. Action320
  remains 162/119, Action71 480/467, and Action72 180/184 in this checkpoint.
  The callable prefix is 81,612 bytes (+62) versus the 81,550-byte target;
  all 126 destination groups are present and no groups are split. The root is
  not exact and has not received oracle acceptance.

Validation was limited to compiling `ReimuActionStateRoot.cpp`, decoding its
root object, and comparing the mapped case spans/branches. No full cold replay
was run. Continue work only on this same root.

## 2026-11-25 Action410 timer/byte gate and effect block aligned

The active lock remains the single 81,550-byte
`Reimu_dispatch_action_state_vslot28` root. Action410 is still part of this
root; do not switch functions before the whole root is exact and oracle-
accepted.

Action410 now uses a natural C++ `switch (frame_timer_value)` with a zero arm
and a nonzero continuation, followed by an explicit unequal-byte effect body.
This recovers the target's timer/frame register lifetime and inline effect
layout without assembly or padding. The focused VC8 object maps Action410 to
exactly 975/975 bytes and decodes 245/245 instructions. After normalizing
relative calls and internal branch offsets, 241/245 instructions match; the
only four remaining differences are external branch destinations into the
shared Action520 tail and Action616 return tail. The frame-three x87/effect
sequence, vtable-slot call, frame-eight gate, and internal branches now match.

Those external destinations expose the next same-root layout work:

- Action520 is 881/881 bytes, but its candidate entry/tail is 66 bytes later
  than the target. Action410's branch to target `0x4852f6` therefore resolves
  to candidate `0x485338` (both are the Action520-owned shared completion tail).
- Action616's candidate return-tail owner is 96 bytes later than the target:
  target `0x489d6a`, candidate `0x489dca`. Its current mapped span is 1,091
  versus 1,085 target bytes.
- The earlier Action320 and Action321 spans remain 162/119 and 157/140,
  respectively. They account for 60 bytes of the +63 drift at Action410's
  entry; continue recovering these earlier same-root continuations before
  revisiting Action520/616 owner placement.

The candidate callable prefix is 81,676 bytes (+126), with all 126 target
unique destinations represented and zero split groups. Only the affected root
translation unit, its mapped case spans, and the Action410 instruction/branch
comparison were checked; no full cold replay was run. This checkpoint is not
whole-root exactness and has no oracle acceptance.

## 2026-11-25 Reimu shared event-index continuation

The only active function remains `Reimu_dispatch_action_state_vslot28` at
`0x00478FA0`. Keep this complete root locked until canonical exact acceptance;
Action 300/320/321 are internal frontiers, not separate function selections.

Action 300 and Action 320's frame-timer-zero/frame-3 event gate, plus Action
321's timer-zero/frame-2 event, now use one natural C++ event-index continuation.
The source records 27 or 28 in a function-local integer and routes to one
ordinary C++ call/flag-clear/return tail. No assembly, padding, byte grafts or
relocation edits are used. VC8 still specializes the constant event values
into separate call sequences, so target machine-level tail sharing is not yet
recovered; this remains a useful source-structure checkpoint, not an exact
claim.

A fresh direct-root VC8 `/O2 /GS- /GL + LTCG` link compiled the tracked
`ReimuActionStateRoot.cpp` and staging header. The linked/ordinary payloads
match byte-for-byte (83,000 bytes, 1,283 HIGHLOW fields, 11 switches), with
zero ordinary buffer-partition mismatches. All 126 target switch destination
groups remain represented with zero split groups. The candidate callable
prefix is 81,628 bytes versus the 81,550-byte target, 48 bytes shorter than
the preceding 81,676-byte candidate.

The focused case map now has target-sized spans for Actions 540 (653), 604
(363), 605 (443), 606 (360), 608 (810), and 658 (740). Span equality is not
byte exactness. Remaining visible frontiers include Action 320 (166/119),
Action 321 (161/140), Action 414 (1,102/1,116), Action 616 (1,087/1,085),
and Action 740 (533/535). Action 410 remains 975/975.

The first whole-root byte difference remains at `0x004791BD`, in the early
shared-return `jne`: target destination `0x00489D6A`; candidate root-relative
destination is 0x40 bytes later. The full root is not exact and has no Oracle
acceptance. This was a focused direct-root link and case-map comparison; no
full cold replay was run.

TH075's exact Reimu Fighter Advance uses the same broad natural-C++ `goto`
shared-tail idiom, but its VC7.1 `/Od /Ob0` profile is only a structural
reference, not a TH105 VC8/LTCG codegen recipe. Continue on this same root,
starting with the shared-return destination and the Action 320/321 tails.

## 2026-11-25 Action616 direction flow and Action650/651 landing owner

The active callable remains `Reimu_dispatch_action_state_vslot28` at
`0x00478FA0`. No function switch is permitted before canonical whole-function
exactness.

Action616's frame-zero effect now keeps the unsigned facing byte as the event
direction while explicitly converting it back to signed-char for the `* 24`
horizontal offset. This is ordinary C++ and preserves the signed/unsigned
split in the target. The focused destination map now gives Action616 exactly
1085/1085 bytes (previously 1087/1085); this is span equality, not byte
exactness.

Actions650 and 651 now share one natural C++ landing continuation. Both
sequence-window crossing paths route to `reimu_action_650_651_landing_tail`,
which performs stage-height assignment, velocity reset, sequence 4, and return.
The source label is owned after Action650; the VC8 optimizer schedules its
machine-code block with the later high action, so the mapped spans are 480/515
for Action650 and 624/589 for Action651. Their combined span remains 1104
bytes, equal to the target combined extent. This is a code-layout/ownership
mismatch, not a claimed exact recovery.

A fresh direct-root VC8 `/O2 /GS- /GL + LTCG` build compiled the tracked root
and staging header. The ordinary COFF and linked payload replay match exactly:
83,000 payload bytes, 1,283 HIGHLOW fields, 11 switches, zero buffer-partition
mismatches, all 126 target switch destination groups represented, and zero
split groups. The callable prefix is 81,628 bytes against 81,550 target bytes
(+78). The first whole-root mismatch remains `0x004791BD`: target `a9`,
candidate `e9`, a shared-return branch destination still 64 bytes late. The
linked image was not executed and this has no Oracle exactness acceptance.

Current focused frontiers: Action320 166/119, Action321 161/140, Action410
975/975, Action414 1102/1116, Action416 959/959, Action540 653/653, Action616
1085/1085, Action650 480/515, Action651 624/589, Action658 740/740, and
Action710 1573/1573. Equal spans do not imply equal bytes. Continue on this
same function; the next high-value work is the early shared-return edge and
the Action320/321 ownership/layout. No full cold replay was run.

## 2026-11-25 runtime-selected shared event continuation

The locked function remains `Reimu_dispatch_action_state_vslot28` at
`0x00478FA0`. The shared event index for Actions300/320/321 is now selected
once from the runtime action (`27` for 300/320, `28` for 321) and carried into
the common C++ dispatch tail. The directional-action result for Actions300
and 320 is likewise represented by one function-local result. This ordinary
C++ control/data-flow change makes VC8/LTCG retain a shared event-call tail
instead of emitting separate constant-specialized call/return bodies.

The focused callable prefix fell from 81,628 to 81,564 bytes, leaving only
14 bytes beyond the 81,550-byte target. All 126 target switch destination
groups remain represented with zero split groups. Focused spans are Action320
146/119, Action321 156/140, Action410 975/975, Action414 1102/1116, Action416
942/959, Action540 653/653, Action616 1085/1085, Action650 480/515, and
Action651 624/589. The Action650/651 shared landing owner remains one natural
C++ tail; its combined extent is unchanged. Span equality is not byte
exactness.

A fresh direct-root VC8 `/O2 /GS- /GL + LTCG` link was verified against the
exact tracked root source hash. The linked/ordinary replay payloads match
byte-for-byte: 82,936 payload bytes, 1,283 HIGHLOW fields, 11 switches, and
zero ordinary buffer-partition mismatches. The linked image was not executed;
there is no Oracle exactness acceptance. The first byte mismatch moved from
`0x004791BD` to the prologue at `0x00478FB2` (target `66`, candidate `33`),
where the compiler chooses a different zero-store/register allocation. The
remaining callable excess is 14 bytes.

A separate experiment reusing `landing_sequence` as the event-index local
caused the genuine direct-root link to fail on an unresolved deque operator
symbol; that experiment was discarded and is not part of the tracked source.
A byte-sized event-index variant also worsened the case map. Keep the
validated `const int` runtime-selected index variant. Continue on this same
root; next focus is the prologue register allocation and the remaining
Action320/321 tail placement. No full cold replay was run.

## 2026-11-25 shared-event tail layout experiment (continuation of vslot28)

The active function remains `Reimu_dispatch_action_state_vslot28` at
`0x00478FA0`; no other callable has been selected. A source-only control-flow
experiment hoisted the Action300/320/321 event gate into one shared tail whose
frame check depends on the selected action. This reduced the linked callable
prefix to 81,552 bytes versus the target's 81,550, with all 126 target switch
destination groups present and no split groups. It is only a length/layout
metric, not byte exactness.

Focused spans for this experiment: Action320 90/119, Action321 153/140,
Action410 975/975, Action414 1102/1116, Action416 942/959, Action540 653/653,
Action616 1085/1085, Action650 480/515, Action651 624/589. The 320/321 shared
tail currently merges an `advance_frame_and_dispatch` path that the target
keeps distinct; the candidate direct-call count is 1,186 versus 1,189 in the
target. Do not accept the short prefix as exactness.

A direct-root VC8 `/O2 /GS- /GL + LTCG` build completed. The ordinary COFF and
linked payload replay agree byte-for-byte (82,924 bytes, 1,283 HIGHLOW fields,
11 switches, zero ordinary buffer-partition mismatches). The target comparison
still fails at the start of the callable: `0x00478FB2` target `66` versus
candidate `33`, caused by the compiler choosing `xor edi,edi` plus a register
store for `word_7a0`, while the target uses an immediate zero store and keeps
`edi=0x55`. No Oracle exactness acceptance or DLL execution is claimed.

Next work remains inside this same function: recover the target's early
register/stack lifetime and its three distinct call sites without padding,
ASM, or synthetic helpers; then continue the 320/321 tail and 414/416 source
shape. No full cold replay was run.

## 2026-11-25 vslot28 prologue and 320/321 layout probes

The locked callable remains `Reimu_dispatch_action_state_vslot28` at
`0x00478FA0`. The best accepted source remains commit
`ab2503ec` (`gpt-web: tune Reimu shared event tail layout`): linked code prefix
81,552 bytes against 81,550 target, all 126 switch destination groups
represented, zero split groups. Its focused spans are Action320 90/119,
Action321 153/140, Action410 975/975, Action414 1102/1116, Action416 942/959,
Action540 653/653, Action616 1085/1085, Action650 480/515 and Action651
624/589. Do not infer exactness from the two-byte prefix difference.

Prologue experiments were run with ordinary VC8 objects and focused switch
maps, without ASM or padding:

- Passing the three no-payload arguments through the pointer overload
  (`static_cast<const float *>(0)`) did not change the prologue allocation;
  it increased prefix to 81,568. The pre-existing uncommitted edit to
  `ReimuActionStatePreludeBody.hpp` with these pointer casts is preserved, not
  discarded; it is a separate shared prelude fragment and is not part of the
  locked root's inline source.
- `register int` / `register short` copies of 85, reordering the two word
  stores, deriving zero as `word_7a2 - 85`, and changing the two word field
  declarations to unsigned all retained `xor edi,edi` plus `mov ebx,55`.
- Replacing the local action snapshot with direct `action_13c` reads moved the
  prefix to 81,648; making the snapshot `short` moved it to 81,536 but expanded
  Action321 to 195/140. Both were rejected.
- A mutable event-index assigned in each case moved prefix to 81,628;
  splitting the shared gate and call tail moved it to 81,596. Both were
  rejected in favor of the 81,552-byte shared conditional tail.
- Changing the spawn wrapper's direction parameter from `unsigned char` to
  `int` compiled and linked through the direct-root LTCG probe, but increased
  prefix to 81,564 and reduced candidate direct-call count from 1,186 to
  1,173 (target count 1,189). The staging declaration remains byte-sized.

The byte-sized baseline direct-root LTCG artifact remains
`build/reimu-root-work/session-20261125-best-prefix-81552/ltcg`: ordinary and
linked payloads agree byte-for-byte (82,924 bytes, 1,283 HIGHLOW fields, 11
switches, zero buffer-partition mismatches). The first target mismatch remains
`0x00478FB2`: target immediate word-zero store (`66`), candidate `xor edi,edi`
(`33`) followed by a register store. No Oracle exactness acceptance or DLL
execution is claimed. Continue on this same function; next investigate the
three object-spawn argument/register lifetimes and the Action320/321 shared
tail without weakening semantics. No full cold replay was run.

## 2026-11-25 Action404/406 branch-local wave increment recovery

Still the same `Reimu_dispatch_action_state_vslot28` callable. The target has
two `dispatch_character_wave_handle` calls in each of Actions404 and406; the
prior C++ caused VC8 to tail-merge each pair into one call. A shared
function-scope `register int reimu_frame_one = 1`, used by the first branch's
`word_732` increment and by Action416's frame-one checks, preserves the two
branch tails without ASM, padding, or helper extraction.

Focused map now reports Action404 1535/1535 and Action406 1413/1413. The whole
callable prefix remains 81,552/81,550 bytes; all 126 destination groups remain
represented with zero split groups. A fresh direct-root VC8 LTCG build
completed; the ordinary object and linked payload agree exactly. The
replayed direct-call field count improved from 1,186 to 1,188 (one below the
target's 1,189). The target/candidate `dispatch_character_wave_handle` call
count now agrees at 77. Action404/406 span equality does not prove byte
identity; the first root mismatch remains at `0x00478FB2` in the prologue.

Unresolved frontiers remain Action320 90/119, Action321 153/140, Action414
1102/1116, Action416 942/959, and the Action650/651 ownership split. Continue
only in this function. No full cold replay or Oracle exactness acceptance was
performed.

## 2026-11-25 direct-root verification of 9717394 checkpoint

Checkpoint `9717394b` restores the Reimu action-wave call sites and keeps the
active root as the only callable under reconstruction. The direct-root VC8
`/O2 /GS- /GL + LTCG` probe was rerun against that exact committed source at
`build/reimu-root-work/session-20261125-head9717394-restored/ltcg`.

The ordinary COFF and linked replay agree byte-for-byte: 82,924 payload bytes,
1,283 HIGHLOW fields, 11 switches, and zero ordinary buffer-partition
mismatches. Callable code prefix is 81,552 bytes versus 81,550 target. The
first target mismatch is unchanged at `0x00478FB2` (target immediate word-zero
store begins `66`; candidate begins `33 ff` and uses a register store). This
confirms internal replay consistency, not target exactness; no Oracle acceptance
or DLL execution is claimed.

The current focused map after the checkpoint has Action412 325/323,
Action414 1100/1116, Action416 942/959, while Action410 remains exact in span
(975/975). Action320/321 remain 90/119 and 153/140. The 126 destination groups
remain represented with zero split groups. Continue from this checkpoint on
the same `Reimu_dispatch_action_state_vslot28`; no full cold replay was run.


## 2026-11-25 shared Reimu sequence-3 landing continuation

Action 201, Action 224, and Action 414 now share one natural C++ continuation for
the grounded-height refresh and `set_sequence(3)`. Each case retains its own
pre-tail velocity/acceleration effects before jumping to the shared label.
Action 201 clears vertical velocity and acceleration; Action 224 clears only
vertical velocity; Action 414 calls the existing full velocity/acceleration
reset. This avoids duplicating the tail and gives the compiler a single
sequence-value lifetime.

The focused ordinary-COFF map remains 126 destination groups with zero split
groups. Current relevant case spans: Action 201 587/611, Action 224 581/579,
Action 414 1126/1116, Action 416 942/959. Action 414 is still not exact; its local
register lifetime is being tuned against the target's EDI=3 / EBP=4 sequence.
No full cold replay or Oracle acceptance was performed.


## 2026-11-25 Action414/416 shared register lifetimes

Action 416 now uses the same `landing_sequence` local as Action 414 for its
sequence-3 landing test, and the shared frame-one/frame-four locals remain
visible across both cases. This is a source-level lifetime consolidation, not
assembly or padding. The target uses EDI=3, EBP=4, and EBX=1 at the paired
action prologues; the focused map is recorded below for the next register
allocation iteration.

Current focused spans: Action 414 1126/1116 and Action 416 942/959; the complete
root map still has 126 destination groups and 0 split groups. Neither action
is declared exact. No full cold replay or Oracle acceptance was performed.


## 2026-11-25 shared sequence-3 landing tail and Action414 register lifetime

The locked callable remains `Reimu_dispatch_action_state_vslot28` at
`0x00478FA0`. The target has one sequence-3 landing continuation at
`0x0047AD16`: Action201 reaches it by fallthrough after zeroing vertical
velocity and acceleration, while Actions224 and 414 branch to it from
`0x0047C6ED` and `0x0047FA2A`. The continuation assigns stage-surface height,
sets sequence 3, and returns.

The natural C++ root now has one `reimu_action_shared_landing_sequence3_tail`
for all three paths. Action201 supplies velocity/acceleration zeroing,
Action224 supplies vertical-velocity zeroing, and Action414 calls the full
velocity/acceleration reset before joining the same tail. The tail carries the
shared `landing_sequence` value through `set_sequence`, so the candidate now
uses EDI for sequence 3 and EBP for frame 4 in Action414. Action414's frame-1
and frame-5 checks use their immediate constants rather than extending the
shared `frame_one` register lifetime.

The direct-root focused map reports target callable size 81,550 bytes,
candidate metadata start 81552 bytes,
126 target destination groups represented, and
0 split groups. Focused spans:
Action201: target 611 bytes, candidate 587 bytes at candidate offset 7238
Action224: target 579 bytes, candidate 581 bytes at candidate offset 13799
Action414: target 1116 bytes, candidate 1128 bytes at candidate offset 27135
Action416: target 959 bytes, candidate 942 bytes at candidate offset 28263

This is not whole-function exactness: equal destination coverage and close
spans do not establish byte equality. Continue on this same function; the
remaining work includes the Action414 local code shape, Action201's shared-tail
layout, and the root prologue mismatch. The linked-root probe was run in
`build/reimu-root-work/session-20261125-action414-dynamic-landing-no-frameone/ltcg`;
no DLL execution or Oracle exactness acceptance is claimed. No full cold replay
was run.


## 2026-11-25 Action201 fallthrough into the shared sequence-3 tail

The same locked `Reimu_dispatch_action_state_vslot28` now models Action201's
landing path as a true C++ fallthrough into
`reimu_action_shared_landing_sequence3_tail`: when the stage-crossing check
and sequence window succeed, Action201 zeros vertical velocity and
acceleration, then falls directly into the shared stage-height assignment and
`set_sequence(landing_sequence)`. Its non-landing path is kept in the `else`
arm and returns before the label. Actions224 and414 still branch to that same
owner after supplying their own velocity resets. This mirrors the target's
`0x0047AD08 -> 0x0047AD16` fallthrough and its two external incoming branches.

The focused ordinary-object map reports callable target size 81550 bytes, candidate metadata start 81620 bytes, 126 target destination groups, and 0 split groups. Focused spans:
Action201: target 611 bytes, candidate 587 bytes
Action224: target 579 bytes, candidate 581 bytes
Action414: target 1116 bytes, candidate 1128 bytes
Action416: target 959 bytes, candidate 973 bytes

A direct-root VC8/LTCG probe was rerun for this source in
`build/reimu-root-work/session-20261125-action201-fallthrough-shared-tail/ltcg`.
This remains a partial function recovery: no whole-function exactness or
Oracle acceptance is claimed. No full cold replay was run.


## 2026-11-25 shared EBP frame/sequence threshold

The active root now uses one natural C++ `frame_threshold` local across the
Action414/416 and Action507/508/512/513 families. It is assigned 4 in the
Reimu action pair and 5 in the related aerial-action family, matching the
target's EBP reuse (EBP=4 at 414/416; EBP=5 at 507/508/512/513). The focused
map now shows the latter family within one byte of target per case, and the
Action507 candidate begins with `mov ebp, 5; cmp [sequence], bp`.

Focused spans: Action414 1128/1116, Action416 942/959, Action507 1930/1929,
Action508 1896/1895, Action512 1845/1844, Action513 1890/1889. Action414 remains
non-exact: its threshold comparison still folds to immediate 4 rather than
materializing EBP=4 at the target point. Continue only on this root function.
No full cold replay or Oracle acceptance was performed.


## 2026-11-25 Action201 facing-gate hypothesis (superseded)

The initial hypothesis that Action201 compares its sequence against
`facing_104` was incorrect. The target at `0x0047ABCA` loads the sequence word
and executes `cmp ax, dx`; there is no facing-byte load on this path. Do not
use the facing snapshot as the semantic explanation for this comparison.

The Action201 effect-call direction hypothesis was also corrected later:
effects 125 and 126 use negative facing in Action201, while Action200's
corresponding effects use raw facing. The exact target argument sequences are
recorded in the following correction section.


## 2026-11-25 Action201 DX lifetime restored through the switch

Target Action201 begins at `0x0047ABCA` with `movzx eax, word ptr [esi+0x13e]`
followed by `cmp ax, dx`. DX is established as zero by the common prelude at
`0x00479121` (`xor edx, edx`), used by the timer and shared-state checks, and
then survives the action jump-table dispatch into Action201. The earlier
hypothesis that DX was stale from a virtual call was incorrect; there is no
such vtable load on this path.

The candidate-only `reimu_shared_event_index` calculation (27/28) before the
switch was the clobber: it overwrote EDX before Action201. The natural C++ root
now selects event 27 in the Action300/320 tail and event 28 in the Action321
tail, rather than precomputing a shared index before dispatch. Action201 now
compares its sequence directly against zero. This restores the target's DX
lifetime without inline assembly or padding.

Focused byte checks on the ordinary COFF object:
- 85 bytes from target `0x00479121` (the common timer prefix) match exactly.
- The first 25 bytes of Action201 match exactly, including `cmp ax, dx`,
  `mov edi, 3`, both conditional branches, `mov ecx, esi`, and the call opcode.
  The raw COFF call displacement remains a relocation and is not byte-compared.

The Action201 effect arguments remain corrected to negative facing. The target
at `0x0047ADAC` loads facing into ECX and negates CL before pushing it for
effect 125; at `0x0047ADE9` it loads facing into EDX and negates DL before
effect 126. Action201 effect 124 also retains negative facing. Action200's
effects 125/126 remain raw facing, matching their separate target sequences.

The focused ordinary-object map reports target callable size 81,550 bytes,
candidate metadata start 81,596 bytes, 126 target destination groups
represented, and zero split groups. Focused spans: Action200 581/591,
Action201 591/611, Action224 585/579, Action320 162/119, Action321 157/140,
Action322 247/247, Action410 975/975, Action414 1128/1116, and Action416
957/959. Action201 is substantially closer but is not exact; the full root is
not exact. No Oracle acceptance or full cold replay was performed. Continue
on the same locked `Reimu_dispatch_action_state_vslot28` function.


## 2026-11-25 Action201 inline landing and byte-effect argument setup

Action201's crossed-surface / sequence-below-3 branch owns its landing tail
directly in the case instead of jumping to the shared landing label used by
other actions. This is a natural C++ control-flow change, not assembly or
padding. The ordinary object contains the same 17-instruction landing shape
as the target from the has_crossed_stage_surface_while_descending result
through the virtual sequence setter and epilogue; relocated call and branch
displacements are excluded from the shape comparison.

The staging view now has an inline byte-direction adapter that forwards to the
existing int-direction effect helper. Action201 effects 125 and 126 use this
adapter, preserving their byte-width direction values until the original
int-parameter call. Focused instruction-shape comparison confirms both
argument-setup sequences match the target exactly through their helper calls:
14 instructions for effect 125 and 15 for effect 126. No assembly or padding
was introduced.

Focused checks on the current ordinary COFF object:
- Action201's first 25 bytes still match the target, including cmp ax, dx.
- The common timer/state-guard prefix still matches for 85 consecutive bytes.
- Action201 effects 125 and 126 each match the target instruction shape exactly.
- Action201's focused span is now 613/611 (candidate/target), two bytes over.
- The 126 target destination groups remain represented with zero split groups.

The effect-124 argument setup is now expressed through the same inline
byte-direction adapter used by effects 125/126. This recovers the target's
movzx edx, byte ptr [esi+0x104], x-base load, neg dl, and argument push
ordering. The focused ordinary-object comparison now has 174 instructions
and 611 bytes for both candidate and target; all normalized instruction
signatures match across the entire Action201 block, including register
choices, stack offsets, and non-relocated immediates. Absolute-address
constant operands and rel32 call destinations are normalized because the
COFF object still carries relocations. This is a full Action201 block
instruction-shape match, not a whole-root exactness claim.

The focused map still reports candidate metadata start 81,580 bytes against
the 81,550-byte target callable, with 126 target destination groups and zero
split groups. Other action spans remain outstanding (notably Actions200,
202, 224, 320, 321, and 414). No Oracle acceptance or full cold replay was
performed. Continue on the same locked Reimu_dispatch_action_state_vslot28
function.


## 2026-11-25 Action226 shared landing branch direction

The Action226 terminal-path correction remains in place: target code at
0x0047CBB0 compares the sequence against 3 and jumps to 0x0047B039, where the
preserved flags select the shared facing-transition/return path. A non-3
sequence exits; sequence 3 invokes the opponent-facing transition and exits.
There is no fallthrough from Action226 into Action300.

Action226's crossed-surface branch now uses the inverted C++ control-flow
shape: the nonlanding path is the body of an if (!crossed) block, followed by
a goto to the shared landing tail. This makes VC8 emit test al, al; jne to the
landing block, matching the target branch direction at 0x0047C9CE. The target
destination is the earlier shared tail at 0x0047AE4A; the candidate still
places that shared block later in the case span.

Focused ordinary-COFF map:
- Target callable: 81,550 bytes; candidate metadata start: 81,628 bytes.
- 126 target destination groups represented; zero split groups.
- Actions201, 202, 203, 224, and 225 retain exact candidate/target spans and
  identical normalized instruction signatures: 611/611 (174 instructions),
  545/545 (139), 429/429 (103), 579/579 (149), and 457/457 (118).
- Action226 improved from 723/731 to 727/731 bytes (181/178 instructions).
  Actions301 226/226, 302 701/699, 320 162/119, 321 157/140,
  322 247/247, 410 975/975, 414 1102/1116, and 416 957/959.

Remaining Action226 differences:
1. The shared landing block is still laid out after the Action226 condition
   rather than at the earlier target address 0x0047AE4A.
2. The target's frame-index-3 event-27 gate is inline at 0x0047CC2B; the
   candidate still jumps to an out-of-line event gate.
3. The candidate COFF jump-table operands lack final absolute table bases;
   these are link relocations and must be checked in linked replay.

No Oracle acceptance or full cold replay was performed. Continue on the same
locked Reimu_dispatch_action_state_vslot28 function.

## 2026-11-25 Action224 byte-direction effect setup

Action224 effects 124, 125, and 126 now use the byte-direction adapter. The
focused normalized instruction comparison is reduced to three case-entry
mismatches: the candidate uses `test ax, ax` and an immediate compare against
1, while the target uses the preserved zero in DX, materializes EDI=3, and
restores ECX=1 after the stage-surface helper call. All remaining 144
instruction signatures, including the three effect argument setups, match.
The focused span is 570/579 bytes (candidate/target), 147/149 instructions.
This is not an exact case or whole-root claim; the remaining mismatch is now
isolated to the root prelude's DX/EDI/ECX register lifetimes and the initial
sequence gate.

The ordinary COFF map still represents 126 target destination groups with
zero split groups. No Oracle acceptance or full cold replay was performed.
Continue on the same locked Reimu_dispatch_action_state_vslot28 function.


## 2026-11-25 Action416 frame-one register lifetime

Action416's frame-one threshold is now a short register local assigned from
the dispatch snapshot (`selected_action - 415`) after the sequence-3 landing
transition. The focused ordinary-object entry now materializes the target's
`EBP=4` and `EBX=1` thresholds in the same early sequence gates, while keeping
`EDI=3` for the landing sequence. This is a natural C++ lifetime experiment;
it does not yet make the whole action exact.

Focused spans after this change: Action201 587/611, Action224 581/579,
Action410 975/975, Action414 1128/1116, Action416 975/959. The 126 target
destination groups remain represented with zero split groups. Action416 is
now 16 bytes longer than target (the previous form was 17 bytes shorter), so
the remaining tail and effect-path layout still need alignment. No Oracle
acceptance or full cold replay was performed.

## 2026-11-25 byte-direction adapter replay

VC8 left 18 calls to `emit_fighter_effect_byte_direction` out of line, which
prevented the ordinary root relocation audit from resolving the real effect
call. The adapter now uses `__forceinline`, preserving its unsigned-byte
conversion and exposing the target's `0x00435240` calls directly. No accepted
unit depends on this staging header. The direct-root LTCG and ordinary COFF
replay agree for all 82,920 payload bytes and 2,477 qualified relocations.
The 126 target action groups remain unsplit. The callable is 81,548 bytes
against 81,550 in the target, and the first target difference remains at
`0x004791BD`. This replay includes the pre-existing uncommitted action 89
`word_7a2` read and does not establish a separate result for that edit.

The Action 89 field read is now checked independently. The target reads
the signed word at `0x0047A4AC` before converting it to float. Restoring
the constant conversion in a private build shortens this action from the
target's 379 bytes to 370 and introduces the `__real@42aa0000` relocation,
which is absent from the target root. Reading `word_7a2` restores the
379-byte action span and the relocation audit. The full root remains
nonexact at `0x004791BD`.

For actions 300 and 320, duplicating the event-27 gate in the 320 source
or spelling it as an early return produces the same complete relocated
section. VC8 places the 320 entry 3,423 bytes before its native location,
although the 321 span becomes 140/140 bytes. Guarding the existing shared
label inside 320 moves the first root difference to `0x00478FB2` and
produces an 81,536-byte callable. All three comparisons resolve their 2,476
relocations. The tracked shared-tail form remains selected.

The headless VC8 SP1 trace at `c2.dll:0x10B26CA8` reconstructs all 3,495
blocks in the compiler's depth-first postorder. In that graph, the event-27
gate is block 908. The traversal first enters it through block 1125 from
action 320, even though action 300 also reaches it from block 906. The
resulting block placement puts the gate with 320. The traced object's
complete relocated section has the same hash and first target mismatch as
the ordinary direct-root build. The original executable places the gate
at `0x0047CC2B`, inside action 300, and reaches it from action 320.
Reversing the action-320 advance condition and spelling both advance paths
with explicit jumps each reproduce the complete ordinary section byte for
byte, including its relocation replay. They do not change this traversal.

Duplicating the event-27 gate only on the non-advancing branch of action
300 changes the ownership: the 320 path now jumps back into 300, and both
320 and 321 have their native 119- and 140-byte spans. Action 320 also
emits the native x87 comparison and virtual-slot register order. The
complete callable grows to 81,660 bytes and the 226 owner span grows from
612 to 767 bytes against 731 native. Actions 400, 401, 406 and 500 also
change spans. The earliest relocated difference stays at `0x004791BD`.
The control shows that the 300 branch changes 320's physical block order;
the complete original layout still needs recovery.


The original landing edges for actions 203, 225 and 226 at `0x0047B13E`,
`0x0047C80E` and `0x0047C9CE` all branch to action 202's shared tail at
`0x0047AE4A`: clear motion, obtain the surface height, then set action 10.
The root source now shares that actual tail and preserves its call order.
With the existing action-300 form, the ordinary root has an 81,532-byte
callable and 2,475 resolved relocations; its first difference remains
`0x004791BD`. VC8 places the shared landing tail with action 226 instead
of 202, leaving their physical spans at 612/731 and 514/545 bytes.
The experimental action-300 form restores the 320 and 321 spans and,
with this corrected landing, reduces its callable to 81,596 bytes, but
still places the shared tail after 226. Recover the global block ordering
before selecting that experiment. A direct-root `/GL` link replays the full
82,904-byte payload identically to the ordinary object, including all 11
switches and 2,475 relocation fields; it retains the same target mismatch.

The four effect-124 paths in actions 202, 203, 225 and 226 draw the
Y offset (`% 200`) before the X offset (`% 100`) in the target. The
previous inline argument expressions compiled in the reverse order.
Explicit float locals restore the target draw order in all four paths;
the complete ordinary root remains 81,532 bytes with 2,475 resolved
relocations and its first mismatch at `0x004791BD`.

At the VC8 `0x10B26CA8` layout pass, a headless debugger trace of the
shared-label form reconstructs all 3,492 blocks in C2 postorder. The
switch visits action 226 first, whose block 900 discovers the shared
landing block 518; the compiled tail therefore resides with 226. With
four separately written landing tails, the same pass still has four
distinct blocks, and the final object places their common tail in 202.
Both traced objects replay identically to their ordinary builds. The
four-copy control has 80 target-sized owner spans versus 79 for the
shared-label form, but other owner spans move. Combining that control
with the action-300 gate experiment yields 202/226/320/321 spans of
549/728/119/140 bytes versus 545/731/119/140 in the target. Its complete
81,612-byte callable remains nonexact. Recover the late tail-merge
choice and remaining instruction differences before selecting it.

The same target draw order occurs at action 201 `0x0047AC89` and action
224 `0x0047C666`; the earlier candidate reversed both. Their effect-124
expressions now use the same explicit Y-then-X sequence. Action 200
already emitted that order and remains unchanged. The seven affected
actions all emit `% 200` followed by `% 100`; the complete ordinary root
still has an 81,532-byte callable and 2,475 resolved relocations.
A direct-root `/GL` link reproduces the entire ordinary payload. A
physical-owner scan found the same random-call counts and immediately
following constant divisors across the target and candidate switch spans.

The four-copy landing control keeps separate blocks through C2 layout at
`0x10B26CA8`. At `0x10C077B6`, only action 202's zero-motion call remains;
the later retained tail has the target owner. Both headless debug objects
replay identically to the ordinary four-copy object.

In the combined landing/action-300 control, the only excess direct-call
count is an extra `0x004351C0` advance in the action 71 physical span.
The source uses two declarations for that same callee: action 9 uses
`CharacterObjectRuntime`, while the other paths use the Reimu view.
Giving action 9 the same declaration as the others removes the call-count
delta and changes action 71 from 480/467 to 467/467 bytes. It moves
action 9 from 112/112 to 116/112 and leaves the complete callable at
81,596 bytes. Writing the low advances as separate calls moves the first
full-root difference from `0x004791BD` to `0x004791E8`, but changes the
71/72 spans and restores the extra advance call. Neither control is
selected; investigate late tail selection and x87 cleanup together.

Splitting the low advance calls only in action 0 or only in action 2
adds 160 or 144 callable bytes in the combined control. In each build
the action-2 physical span grows from 27 bytes to 151 or 162: C2 moves
a copy of the common horizontal-speed handling there. Splitting both
actions returns that span to 27, but leaves the separate 71/72 and
advance-call regressions noted above. The combined two-action build and
a build that also splits action 9 have identical complete replay hashes.
This isolates the source coupling to actions 0 and 2, not action 9.

The direct-call discrepancy was split by physical owner: the selected
root has one extra advance in action 71's span and one missing from
the span containing action 300. Combining the corrected 300 flow with
the single advance declaration makes every switch owner's advance-call
count agree with the target. Separately spelling only the normal advance
paths of both actions 0 and 2 leaves those counts intact. Action 2 then
replays all 27 bytes exactly in the complete object; actions 71, 72, 320
and 321 have no instruction-byte differences after masking relocation
and direct-branch fields. Action 0 still differs structurally around its
x87 cleanup and advance, and the complete root remains nonexact.

In the low-0/2 advance control, action 0's first structural mismatch is
the receiver load for `zero_velocity_acceleration`. A single headless
VC8 trace captures the same node at `0x10C077B6` and at emission
`0x10B2419F`: the late IR puts it after `fnstsw` and before the
conditional test, while the emitter puts it before the preceding x87
addition. The target loads the receiver only after the branch. The
debugger object replays byte-for-byte with the ordinary control. Recover
the original dependency or control-flow structure before altering the
local expression; a later scheduler moved this node.

Action 226's constant case tests and ternaries have been simplified,
and its nested landing path is indented. The complete ordinary payload
replays identically to the pre-cleanup build with all 2,475 relocations;
the function remains nonexact.

The low-0/2 advance control's early receiver load is selected by the
VC8 scheduler, not introduced by the encoder. A hardware watch catches
its node relink at `c2.dll:0x10C721D5–DA`, called from `0x10C0792F`.
At dequeue `0x10C72378`, the x87 add is ahead in the ready list with
priority `0xDC00`, but its earliest issue field is 1; the receiver move
has priority `0x0C00` and earliest issue 0. The current threshold is 0,
so the `0x10C72360` comparison skips the add and selects the move.
The traced complete payload matches the ordinary control. The target's
later move therefore needs a real dependency or different scheduling
context; a priority-only explanation is insufficient.

Action 225's constant comparisons and unreachable case-226 alternatives
have likewise been removed. Its complete ordinary root payload is
identical to the prior build after all 2,475 relocations are replayed.

TH075-style nested velocity branches preserve the target order of the
action-0 x87 comparison and receiver load: C2's late IR leaves the load
after the conditional branch. The control's shared advance nevertheless
lands in action 0 instead of the target's action 9. Making only action 0
or 2 use the nested form duplicates the shared velocity body in action 2;
a common explicit label also puts that body there.

For action 202, calling `emit_fighter_effect` directly with its actual
integer direction makes VC8 reproduce the target's argument preparation:
direction is pushed before the `% 200` and `% 100` draws. Explicit
float locals preserve the draw order but prepare the arguments later.
Applying the direct call to all six affected cases restores that local
shape, while changing the landing-tail merge and duplicating the reset
and surface calls. An explicit shared landing removes the extra calls
but places the tail in 226. Keep the committed semantic correction while
recovering these coupled compiler choices.

In the six-direct-effect control, action 202 and 203 retain separate
landing tails. Their final virtual slot-8 target uses EAX and EDX,
respectively; the target shared tail uses EDX. At VC8 allocator search
`0x10BDA65C`, the action-202 search starts at EAX, while action 203
starts at ECX. ECX is occupied at both sites, so action 203 selects EDX.
Hardware watches at `0x10BDA597` confirm both assignments, and the
debugger's complete replay matches the ordinary object. The tail-pair
comparison trace timed out before reaching the selected pair; the
register difference is not yet proof of why the merger retained both.
Trace the cursor immediately before action 202 next.

The last allocator requests before action 202 include action 201's
effect-126 direction, followed by action 202's virtual-table base. A
private control omitting that effect changes action 202's target search
start from EAX to ECX; ECX is occupied, so VC8 selects EDX and action 203
then branches to action 202's landing tail. Both control traces reproduce
their ordinary objects. This omission removes a real target call and is
only a causal diagnostic. Recover the action-201 direction expression
without dropping the effect, then check all landing owners.

A private same-translation-unit control exposes the real effect-wrapper
body while keeping its call out of line. That wrapper reproduces all 52
target bytes after the effect-sink relocation. The giant root's complete
83,032 raw bytes and all 2,479 relocation offsets, types and symbol names
are unchanged from the six-direct-effect control. This ordinary VC8
control does not establish the original link-time visibility.

With effect 126 retained, direct calls, explicit unsigned direction
captures, byte-then-negation, and a separately evaluated second Y value
all reproduce the same complete six-direct-effect payload. In action 201,
the target zero-extends the facing byte before negating its low byte;
the control negates a byte and zero-extends afterward. Recover the real
dataflow or compiler context behind this difference rather than omitting
the effect or inserting artificial state.

For action 201's effect-126 direction, the existing expression and the
byte-then-negation control enter `0x10C064F9` with 49,322 and 49,325
function nodes respectively. By `0x10C0661B` both have 22,100 nodes and
the direction lowers to the same negate (`0x23`) then zero-extension
(`0xC2`) sequence. Both debug objects replay identically to their ordinary
builds. The distinction is folded between these checkpoints; targeting
only later scheduling cannot reverse this source-level conversion.

The direction nodes remain high-level through `0x10C070A3` inside C2's
`0x10C06FA0` processing; the earlier call at `0x10C06FE8` does not lower
them. Hardware write watches on the same compile identify `0x10C476B1`
as the negate-node opcode write (`0x293` to `0x23`) and `0x10C475CB` as
the zero-extension write (`0x291` to `0xC2`). Both traced objects replay
the complete ordinary six-direct-effect payload. The next useful question
is which target-backed type or dataflow difference changes the high-level
node order or lowering inputs while retaining the effect and RNG behavior.

TH075 Reimu's analogous backward command state also spawns effects 125
and 126 with negated signed-byte facing, then plays sound 31. Its helper
declares a signed-byte direction. In TH105, `0x00435240` forwards the full
argument slot, but this alone does not determine its source type. Rewriting
effect 126 as unsigned subtraction followed by byte conversion replays the
complete six-direct-effect payload unchanged.

Removed constant macro-expansion conditions in action cases 0–5. The
selected root still replays the complete 82,904-byte payload identically
with all 2,475 relocations resolved; its first target difference remains
`0x004791BD`. This is a readability cleanup, not exact-match progress.
The same complete replay remains identical after simplifying the constant
velocity selections in actions 6–8.

Across the original root, 12 `movzx` facing-byte loads are followed within
seven disassembly lines by a byte negate of the same register. The selected
SP1 object and the six-direct-effect control have no such pattern under the
same ESI-based scan. A headless control with the existing VC8 RTM compiler
(`cl.exe` SHA-256 `3cbf4306526c06a07d09fd4785ac290c7ac7b52355944e7b377e08f5d8e7ece7`,
`c2.dll` SHA-256 `ebca6ef587d6e028b50cc79fe71dd6155230ecb51014295399e8f00e8865ff86`)
also has none. Its complete replay resolves 2,475 relocations, has an
81,544-byte callable prefix and first differs at `0x004791BD`; its root
payload differs from SP1. This comparison uses each local compiler's own
headers and does not identify the original compiler patch level.

An SP1 `/O2 /Os` control has no matching direction pattern either. It
changes the root `.text` from 82,904 to 73,289 bytes and the relocation
audit cannot identify the low switch table, so keep the existing `/O2`
profile while investigating the target's source and compiler context.

The sink constructed at `0x004378F0` installs primary vtable `0x006C1490`;
slot `+0x0C` points to `0x00437C00`, which reads the direction slot as a
byte and stores it at object offset `0x104`. A focused VC8 control shows
that both an `int`-to-`int` wrapper and an unsigned-byte-to-byte wrapper
produce the 52-byte `0x00435240` instruction shape; a byte-to-int wrapper
instead inserts a byte extension. Thus the wrapper alone does not settle
the original type.

In a private root/header copy, declaring the effect direction unsigned byte
produces all 12 target-style facing load/byte-negate patterns; the selected
int declaration produces none. The complete replay resolves all 2,476
relocations and retains 126 switch destinations, but its 81,556-byte prefix
still differs at `0x004791BD`. Combining that declaration with the existing
six-direct-effect control yields 81,644 bytes with all 2,478 relocations
resolved; actions 201–203 and 224–225 have the target physical spans, while
226 and 320–321 still do not. The declaration remains a hypothesis until
the full call chain, alternate sink implementations and shared consumers
are reconciled. Investigate the changed tail placement and effect calls before
selecting it.

Changing only the private effect declaration from unsigned byte to signed
byte gives an identical complete relocated payload, so these observations
do not distinguish signedness. TH075's signed byte is useful corroboration.
A raw `.text` scan finds 12 occurrences of the sink-global address
`0x006FBCB0`: one direct write at `0x00439062` and 11 direct reads. The
write follows construction of the `0x004378F0` sink; the slot-3 consumer
copies only the low direction byte. Check any indirect replacement and the
staging-header consumers before promoting a byte-typed declaration.

For the byte-direction plus six-direct-effect control, physical spans for
201–203 and 224–225 also agree byte-for-byte after normalizing relative jump
immediates and resolving direct-call destinations. Their jump destinations
and the complete function remain to be reconciled; 226 has 102 positional
differences under the same diagnostic, and 320 and 321 have 62 and 22.
The scratch comparison is `build/reimu-root-work/terra-byte-direction/compare-spans.py`.

With the byte-direction/six-direct control, spelling action 300's event
check inside the advancing branch makes VC8 retain the shared event gate
in action 300. The 81,580-byte candidate has all direct-call counts equal
to target and 100 of 128 physical switch rows have equal lengths. After
normalizing jump immediates and resolving call destinations, actions
201–203, 224–225 and 320–321 have no positional byte differences; action
226 has only two differing bytes in middle-switch metadata addresses.
This is diagnostic, not exact credit: the complete function, metadata,
branch destinations and remaining 28 row lengths still differ. A simpler
single event gate reproduces the prior 81,644-byte control exactly.
The successful control is `build/reimu-root-work/terra-byte-direction/gate-advance.cpp`;
its byte-direction header and bindings are in the same directory.

The byte-direction gate control retains the earlier advance-call coupling:
using the distinct `CharacterObjectRuntime` declaration at action 9 restores
its 112-byte target span but adds an extra `0x004351C0` call and changes
71/72 to 480/467 and 180/184 bytes. Using the common declaration leaves
9 at 116/112 but preserves the target's direct-call counts. Action 9's
conditional branch currently targets action 0's advance block; the target
branches to the local advance after its separate x87 cleanup entry.

In the byte-direction gate control, action 77's five failure branches go
to the advance in action 0, making each branch four bytes longer than the
local short branch in the target. Rewriting the same frame gate as explicit
negative tests and a local advance label reproduces the entire candidate
payload unchanged. Recovering the advance-tail owner requires a different
shared context, not merely reversing these conditions.

A further edge check maps target branch destinations into candidate rows
when the owning row has the same span. Under that mapping all conditional
and unconditional direct branches in 201–203, 224–225 and 320–321 reach
the corresponding local or shared location. Three dispatcher edges in
226 lead into unequal-length rows and remain unresolved by this check.
Full-root strict replay remains required.

The same branch-masked and call-resolved comparison finds zero positional
differences for low actions 1–8 and 71–76, 78. Actions 0, 9 and 77 remain
nonmatching; their shared advance and x87 cleanup placement need to be
solved together. These are physical-span diagnostics, not match units.

At C2 `0x10B26CA8`, the byte-direction gate control has 3,493 blocks and
its recorded order matches depth-first postorder. Action 77's five frame
tests and success path all point to its own block 334; the DFS first
reaches it from the first test. The emitted code later sends the failed
conditions to action 0's advance and retains a local advance for the
successful path. The debugger build replays identically to the ordinary
candidate, placing this divergence after the captured graph state.

At the later C2 `0x10C077B6` snapshot, each of action 77's five branch
nodes references the same label object through its opcode-`0x284` operand.
Within the first 10,000 linear nodes, 12 conditional branches reference
that label, including action 9's landing test and branches from other
recovery actions. The debug object replays identically to the ordinary
byte-direction gate control. This confirms that the late shared advance
is a cross-case decision; the earlier graph's action-77-local block alone
does not determine final placement.

A hardware watch armed at `0x10C0661B` catches the first action-77 branch
being retargeted: C2's `0x10BF2BFD` replaces its opcode-`0x284` operand,
whose old label differs from the shared late-IR label. The new operand
references that shared label. The captured C2 stack includes return sites
`0x10BF315D`, `0x10BF327A`, `0x10B2857E` and `0x10B2A347`; static code
shows a list splice and reference update rather than a final emitter-only
change. A later write zeroes the freed old operand and is memory cleanup.
The debug object has the same complete relocated hash as the ordinary
candidate. Trace the caller that selects these two labels next.

Simplified action 77's retained macro-expanded body to its actual reachable
conditions and operations. The selected root's full relocated payload is
unchanged, with all 2,475 relocations resolved; its first target difference
is still `0x004791BD`.

The best byte-direction gate candidate also replays identically after
incorporating the selected readability cleanups for actions 0–8, 77 and
225–226. Its cleaner source is
`build/reimu-root-work/terra-byte-direction/gate-clean-all.cpp`; it retains
all 2,477 resolved relocations and the 81,580-byte callable prefix. The
byte-typed header remains private pending cross-module ABI reconciliation.

Action 200's target checks `field_6b8` before evaluating directed input;
each branch reads and multiplies facing and `field_6b4` separately. In the
byte-direction gate candidate, replacing the captured effect direction with
the direct expression and evaluating directed input within each branch
makes all 591 bytes of the action-200 physical span agree after jump
normalization and call-target resolution. The complete candidate grows to
81,596 bytes, retains matching direct-call counts and changes several other
rows, including 400, 404, 500 and 540. The control is
`build/reimu-root-work/terra-byte-direction/200-directed-branch.cpp`.
On the selected integer-direction baseline, the branch-local change alone
moves 79 matching row lengths to 72; it remains an experimental source shape.

The `all-direct-direction.cpp` control applies the same direct facing
argument to target-backed effect-123/124 sites in actions 208, 211 and
220–223, following the action-200 branch-local input change. Its 81,532-byte
prefix has 2,477 resolved relocations, no direct-call count deltas and 103
of 128 equal-length physical rows. Actions 200–203, 208, 211, 220–225 and
320–321 have zero positional differences after jump normalization and
call-target resolution; 226 differs only in two switch-address bytes.
The first complete-root difference remains `0x004791BD`, and the original
callable is 81,550 bytes. The private byte-direction header remains an ABI
hypothesis; no exact credit is claimed.

Action 214 also prepares its effect direction before the trigonometric
calls. Replacing its byte temporary with a direct argument removes the
extra stack-byte preparation, but the candidate changes from 103 to 100
equal-length rows and action 214 remains 1,504/1,540 bytes. Keep it as
`214-direct-direction.cpp` while resolving that action's other control and
floating-point differences.

In the `all-direct-direction` control, spelling the 650 and 651 landing
sequences independently lets C2 place their shared 35-byte tail in 650,
as the target does. The resulting `650-independent-landings.cpp` keeps
an 81,532-byte prefix, all 2,477 resolved relocations, matching direct-call
counts and 105 of 128 equal-length rows. Both 650 and 651 have zero
positional differences after jump normalization and call resolution; 651's
mapped branches also agree. One 650 branch instead targets candidate
`0x0047FF92` versus target `0x004852F6`, so its shared destination needs
separate comparison. Previously aligned 200–225 and 320–321 spans remain
unchanged in this diagnostic.
