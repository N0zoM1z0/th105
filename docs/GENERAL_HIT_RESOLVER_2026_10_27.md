# General hit resolver 0x0046BF80

## State and target evidence

The Oct27 source correction in src/battle/GeneralHitResolver.cpp was
unselected/nonexact and added no ledger credit at that checkpoint. The Oct29
typed-dispatch and positive authored/source selection is recorded below.
The shared header and accepted consumers are unchanged; only this source is built.

The hash-attested PE has 1579 bytes through RET8 at 46C5A8, exclusive end46C5AB.
All395 decoded instructions are reachable, with25 physical calls including two
virtual calls. Native code SHA-256:
6b8c8e4f782020e3225e7aba799448ba3a4cc0cc6bffda61da9a9a52345d5f4e.
The accepted attack-candidate dispatcher46DA10 calls this member at46DB22 and
ignores EAX. This is a void thiscall with candidate and victim pointers.
No actual gameplay or exceptional floating-point inputs were executed.

Factory native IDA identity, entry68B9D2, ten mapped entry bytes and inventory
probe were freshly checked. The direct launcher still lacks mcp1.26.0.
Raw target instruction decoding supplies the decisive width/control-flow facts.

## Corrections to the retained hypothesis

- The practice gate is g_battle_input_gate at6FA888, field+24, not stale6E4E28.
- Candidate flags20,400 and1 read the current frame1A4. Remove the old artificial
  volatile access; ordinary alias-visible loads suffice.
- If alternate action38 is zero and neither victim flag1 nor2 is set, keep the
  initial selected action -1. Do not dispatch action0.
- Action36/38 and bias-derived results have unsigned16-bit values, while the
  final dispatch gate tests their signed low16 bits.
- The surface query is consumed through AL. Its existing int declaration is
  retained without assuming the other return bits are meaningful.
- The boosted quantity narrows the helper result to signed16 before multiplying
  by4 and dividing by3. It does not narrow the intermediate product.
- Deferred7C uses the separately computed signed resource quantity from frame32
  times owner4D0, subsequently scaled by owner4D8, not the hit quantity.
- The candidate flags are bit predicates; the original threshold guard and
  signed boundary predicates are kept explicitly. No volatile, fake locals,
  padding, assembly or target byte arrays are introduced.

The helper bindings remain independent. In particular45CED0 consumes the low16
argument, and45C0B0 already has an independent exact unit. Neither inherits
new credit from this caller.

## Complete comparisons and residual

The first corrected build was1570 bytes. Recovering the real action-value widths,
high-threshold-first path, signed resource lifetime and native bit predicates
produces1581 bytes versus1579. The selected payload SHA-256 is
146c4a5d34c3104bee8af1fc3545cd3a75b19b39f9178a44965e14dd7338ac06.
There are571 unequal compared byte positions, first at+449/46C141. The two-byte
size difference is NOT a two-byte mismatch claim.

Remaining differences include shared nonboost action assignment placement and
the deferred-resource x87 multiply/load schedule. Unsigned temporary variants
introduced an inline control-word conversion absent from the native body.
A signed16 resource local restores the native ftol call. Merely reordering
multiplication operands was byte-neutral. Combined versus nested action gates
and short-value mutation did not recover native branch sharing. These are
phase-scoped negative controls, not proof of LTCG or irrecoverable original TU.
Do not continue a spelling grid without independent caller/type/lifetime evidence.

Private scope: .analysis/frontier-46bf80-20261027/ and
build/frontier-46bf80-20261027/. public.obj, its relocs/preview, formal-public.json,
target.asm and target-audit.json preserve the complete comparison. The ordinary
compare-function.py invocation binds every direct callee using the rel32 mapping
in public.obj.preview.json and the complete symbol in public.obj.relocs.json.
The initial partial-symbol invocation failed lookup and is not a comparison.
Native builds use the pinned VC8 compile-unit.sh profile with GS disabled,
CPU0/nice10, and empty DISPLAY/WAYLAND_DISPLAY.

The mandatory final CI log is local-ci.log in this scope. This is a source
correction checkpoint, not a newly accepted exact function.


## 2026-10-29: typed virtual calls and positive source selection

Existing CBattleManager and AnimationSequenceObjectView declarations now supply
both virtual calls. The context is the manager's primary layout; vtable6C1504
slot2C points to472490, the real fighter-depletion callback already declared
by BattleManagerVirtuals.hpp. Native46C529 calls that slot with the victim.
Native46C577 calls the victim's action slot08; the existing sequence view
provides its short-action method, with the result ignored. The signed-low-word
dispatch gate ensures this narrowing preserves the selected action value.
No function-pointer cast, manually indexed vtable or invented calling convention
is needed. Shared headers and all other consumers remain unchanged.

The complete resulting1581-byte canonical candidate is byte-identical to the
Oct27 candidate146c4a5d above. First mismatch remains+449, with571 unequal
positions in the common prefix plus two extra source bytes,573 total when
length is included. The formal build's compared-prefix hash is different from
the full1581-byte section hash because its ledger bound is1579, not a new
candidate. No exact credit is earned.

A fresh closed native CFG again reaches395 instructions/all1579 bytes through
RET8, and independently verifies the exact46DA10 caller's E8 at46DB22. Its
threshold/action/practice/resource/depletion policy establishes authored game
ownership independently of equality. The function is now mapped/source-present
with an explicit reproducible exact-first-general-hit-resolver unit and a
body-hash/caller-backed origin rule. This removes one review row, not an
exclusion or an exact-byte award. Remaining action-block sharing and x87
schedule are the same bounded unknowns, not a reason for a new spelling grid.

Receipts: build/frontier-general-hit-virtuals-20261029/{formal-build,boundary,
compare}.json and ci.log. The private typed-call candidate and former whole
candidate are retained for direct equality checks. Default CI follows final
ledger/progress edits; only the affected unit is compiled.
