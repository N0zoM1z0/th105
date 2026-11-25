# TH10.5 reconstruction handoff

Continue the Reimu Fighter action-state root at `0x00478FA0`. The user asked
for one function at a time, headless execution, careful use of TH075 and
deep compiler/global analysis. Do not move to another function until this
root is finished. Use `gpt-6.1-sol: <summary>` for commit subjects.

The target is the original Japanese TH10.5 v1.06a executable, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Follow [AGENTS.md](../AGENTS.md), [the shared runtime](SHARED_TOOLS.md) and
[the reconstruction workflow](RE_WORKFLOW.md). Keep this game's Wine prefix,
analysis projects and private worktrees; run compiler and analyzer jobs
serially. The raw hash-attested PE supports byte and control-flow analysis
without a database. Attest any database session before using its evidence.

## Reimu root: current state

The selected source is [ReimuActionStateRoot.cpp](../src/characters/ReimuActionStateRoot.cpp),
with receiver declarations in [ReimuActionStateStaging.hpp](../src/characters/ReimuActionStateStaging.hpp).
It is a complete candidate, not a formally matched unit: `implemented.csv`
and `matches.csv` do not grant this root source-present or exact credit. Its
81,550-byte target callable has 11 owned switch tables; acceptance requires
strict comparison of the complete callable, its owned switch data and all
relocations in a reproducible match unit.

The latest selected `/O2 /GS-` object has an 81,532-byte code prefix and an
82,904-byte text payload. All 2,475 relocations resolve; the first target
mismatch remains `0x004791BD`. Recent cleanup simplified actions 0–8 and
77 and replaced action 416's manually indexed virtual call with
`next_sequence_block()`. Complete relocated payloads were unchanged by
those readability changes. The root is still far from byte equality: a
later first mismatch or matching case sizes alone is not progress credit.

For a fresh selected-root diagnostic:

```bash
export DISPLAY= WAYLAND_DISPLAY=
git status --short
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/report-reconstruction-status.py --summary
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/compile-unit.sh src/characters/ReimuActionStateRoot.cpp build/reimu-root-work/selected.obj
scripts/repo-python scripts/audit-reimu-root-relocations.py build/reimu-root-work/selected.obj --diagnostic-oversize
scripts/repo-python scripts/compare-giant-action-switches.py reimu-vslot28 build/reimu-root-work/selected.obj --json
```

The diagnostic audit resolves the complete object and reports a bounded
prefix comparison. It is not the exact-unit acceptance check. For `/GL`
context, `scripts/probe-reimu-action-ltcg.py --direct-root-source` builds
the tracked root and real provider closure; ordinary and linked payload
agreement from an earlier selected source did not establish target equality.
Do not run the full exact-unit suite without a stated repository-wide reason.

## Strong private candidate and remaining questions

The reproducible candidate is
`build/reimu-root-work/terra-byte-direction/650-independent-landings.cpp`,
with its private `ReimuActionStateStaging.hpp` and `bindings.toml` in the
same directory. It retains the readability cleanups, correct RNG draw
order and natural per-case landings. The companion
`416-typed-virtual.cpp` uses the ordinary typed virtual call and produces
the same complete relocated payload. These files are private experimental
inputs, not selected source.

Its code prefix is 81,532 bytes, versus 81,550 in the target. The audit
resolves all 2,477 relocations with no direct-call count deltas, and 105 of
128 physical switch rows have the target span. The first difference is
still `0x004791BD`. After resolving direct-call destinations and masking
relative jump immediates, actions 200–203, 208, 211, 220–225, 320–321 and
650–651 have no positional byte differences. Action 226 has two differing
switch-address bytes. Mapped branch checks agree for the listed cases
except one 650 external edge and three 226 dispatcher edges; these are
bounded diagnostics, not independent exact matches.

Recompile and inspect the retained control without changing tracked source:

```bash
scripts/compile-unit.sh build/reimu-root-work/terra-byte-direction/650-independent-landings.cpp build/reimu-root-work/terra-byte-direction/650-independent-landings.obj
scripts/repo-python scripts/audit-reimu-root-relocations.py build/reimu-root-work/terra-byte-direction/650-independent-landings.obj --bindings build/reimu-root-work/terra-byte-direction/bindings.toml --diagnostic-oversize
scripts/repo-python scripts/compare-giant-action-switches.py reimu-vslot28 build/reimu-root-work/terra-byte-direction/650-independent-landings.obj --json
scripts/repo-python build/reimu-root-work/terra-byte-direction/compare-650-spans.py
scripts/repo-python build/reimu-root-work/terra-byte-direction/compare-650-edges.py
```

The candidate's effect direction is declared as a byte in its private
header, unlike the selected `int` view. This hypothesis produces all 12
observed target `movzx`-then-byte-negate facing patterns; the selected
view produces none. The wrapper at `0x00435240` forwards the whole stack
slot, but pinned VC8 emits the same 52-byte wrapper for both int-to-int and
byte-to-byte declarations. The constructed sink's vtable at `0x006C1490`
points slot `+0x0C` to `0x00437C00`, which reads and stores only the low
direction byte. TH075's comparable helper uses a signed byte. Signed and
unsigned byte declarations generate identical full candidate payloads;
the original signedness and possible indirect sink replacement remain
unresolved. Reconcile the actual call chain and shared-header consumers
before selecting the type; do not create a mismatched C++ ABI for codegen.

The most useful next investigation is the shared advance tail. In the
private candidate, action 9's non-landing branch and action 77's five frame
checks jump into action 0's advance; the target retains local tails. At
VC8 `c2.dll:0x10B26CA8`, action 77's tests converge on its own graph block.
At `0x10C077B6`, their branch operands share a label with action 9 and
other cases. A hardware watch caught the first retarget at `0x10BF2BFD`,
with callers including `0x10BF315D`, `0x10BF327A`, `0x10B2857E` and
`0x10B2A347`. The debugger object replayed identically to the ordinary
candidate. The trace and script are
`build/common-vc8/reimu-byte-low-label-replace.log` and
`build/common-vc8/trace-reimu-byte-low-label-replace.py`; their input is
`build/reimu-root-work/terra-byte-direction/gate-advance.cpp`. Determine
why the earlier label is replaced and which target-backed global context
changes that decision. Merely inverting the action-77 gate reproduced the
same payload. Giving action 9 a distinct receiver declaration restored its
112-byte span but added an advance call and disturbed actions 71–72.

Other concrete constraints:

- Actions 201–203 and 224–226 draw `% 200` for Y before `% 100` for X;
  the selected source preserves that target-observed order. Actions 203,
  225 and 226 branch to action 202's landing sequence in the target.
- The target places the shared action-300/320 event gate at `0x0047CC2B`
  inside 300. A branch-local event check in the private candidate recovers
  that placement and keeps the complete direct-call counts equal.
- Independent 650/651 landing sequences let VC8 place their common tail in
  650, as in the target. The remaining 650 branch reaches candidate action
  416's 17-byte slot-20 tail instead of target action 520's byte-identical
  tail at `0x004852F6`. Landing copies on the selected integer-direction
  baseline duplicate height/reset calls, so do not promote them in isolation.
- Target action 200 checks `field_6b8` before calculating directed input;
  separate branch-local expressions match its normalized physical span in
  the private candidate. On the selected baseline, that edit alone worsened
  other spans. Action 214 still has separate control and x87 differences.
- Action 740's mode input can retain an out-of-range spill path. Consult
  `scripts/reimu_740_mode_facts.py` before changing it.

The [TH075/EFZ/TH09 review](GIANT_ROOT_REVIEW_2026_11_23.md) and
[VC8 source-shape patterns](VC8_SOURCE_SHAPE_PATTERNS.md) explain useful
cross-engine and compiler controls. Rich data identifies build `50727`,
not its exact patch level. Local VC8 RTM and SP1 controls both failed to
produce the target facing pattern with the integer declaration; `/Os`
changed switch lowering and is not supported by current target evidence.

## Other preserved work

Sakuya Object update `0x004E0D30` has a complete selected source and first
mismatch `0x004E0D55`; its landing-sum and retirement-tail questions are in
[the Sakuya note](SAKUYA_OBJECT_UPDATE_2026_10_25.md). Sakuya Object
initializer `0x004E8060` has an allocator-history issue documented in
[its entry note](SAKUYA_OBJECT_ENTRY_2026_10_24.md). Komachi Fighter update
`0x005E20E0` has a global EBX/card-bound issue described in
[its action-state note](KOMACHI_ACTION_STATE_2026_10_28.md). These are not
the active function. Preserve their analysis projects and private contexts.
Other unresolved input, loader and font contexts are listed in
[ARTIFACTS.md](ARTIFACTS.md).
