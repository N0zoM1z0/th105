# Reimu root: signed selector promotion and direct-arm sharing

## Target observations and source choice

This bounded unit remains `Reimu_dispatch_action_state_vslot28 @478FA0`,
callable `[478FA0,48CE2E)` (81550 bytes), original JP1.06a executable SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Callable SHA256 is
`dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6`.
The candidate/name/source ledgers remain authored/unclassified/declaration-only.
IDA preflight still identifies another target; it supplied no semantics.
Raw attested PE instructions and pinned VC8 SP1 COFF probes supply this work.
No analysis database was opened; all nine primary file hashes are unchanged.

Target selector `4791D4` loads WORD13C with `MOVSX EAX,[ESI+13C]`, then
`CMP EAX,300; JG; JE; CMP EAX,226; JA; MOVZX; JMP`.
The short local produced `MOVZX EAX,[ESI+13C]; CMP AX,300; JG`, followed
by another signed extension/comparison and another JG before the JE.
Changing the local `selected_action` from `const short` to `const int`
recovers the target's promoted load and low dispatch instruction sequence.
The field layout remains short; both local spellings represent the same
signed16 input values. Original source spelling remains unknown.

The target has six direct WORD13C receiver accesses, all at/before selector
entry. A private const-reference control did not reduce code or establish a
need for live action reads. It is unselected. The committed source continues
to capture the action value once after the entry prelude.

## Complete selector-domain audit

A read-only audit interprets only the decoded integer selector instructions
and qualified jump-table bytes, stopping at primary/direct arm entries or the
common-call entry. It uses the official target/candidate maps, separately
identifies the300/560 equality arms, and follows actual MOVSX/MOVZX, register
widths, LEA/arithmetic, x86 signed/unsigned flags, branches and table reads.
Unknown instructions, registers or reads outside the reviewed field/metadata
fail closed. No CPU, helper, world callback or oversized candidate executes.

All65536 WORD13C bit patterns, interpreted as signed16 actions, reach the
corresponding declared arm/default in both target and source models: zero
routing-membership mismatches,21 distinct selector instructions on each side.
Source labels sharing one physical entry are retained as a set rather than
overwriting one another. This proves selector-to-declared-arm membership;
body semantics and a physical owner bijection remain separate questions.
An isolated source-instruction-model bound300->301 control misroutes exactly
300 and301. This changes no executable/object bytes and is not a compiled or
native negative control. Full raw snapshots, model implementation and reports
remain under `build/reimu-live-action/`.

## Physical sharing found outside the primary tables

The source direct300 equality arm and primary320 table entry both reach
`47CBFE`. The preceding short-local object already shared these at `47CC0B`.
Target300 starts `47CBBD`, while target320 starts `47D96A`. Its119-byte
physical prefix ends at `47D9E1`, but its continuation belongs elsewhere:
`47D9CB JE 47CC2B`, or virtual set_action0 at `47D9DA` followed by
`47D9DC JMP 47CC2B`. The timer/frame/event27 continuation is shared with300.
Thus the target duplicates the landing/directional/advance prefix and shares
its later tail; the candidate merges the entire300/320 body. Their source
bodies currently differ only in equivalent byte47E truth-test spelling.

This accounts for three physical E8 deficits: landing473DD0,
directional478EE0 and advance4351C0 each have one fewer candidate call.
Per-action callee cardinalities can still agree, as the preceding census
showed. A primary-table-only uniqueness check misses this direct-arm merge.
Do not change target boundaries or add fake operations to split the candidate.
Recovering this sharing graph needs further source/compiler/LTCG evidence;
the observation alone does not prove that standalone COFF matching is impossible.

## Build, focused verification and remaining differences

Expanded current object SHA256:
`dca069721d99523fcb65b6d4af0dd1a03a4893bce37628d2ee4375acaad1c3b9`.
Code prefix81668/text83040 is48 bytes below the preceding81716/83088.
The unchanged mapper still finds126 unique primary destinations and zero
splits; the direct300/320 merge above lies outside that primary-only claim.
All2465 relocations qualify and replay:1176 calls,1105 numeric operands,
14 metadata addresses,163 local code pointers and7 global reads. Both root
frames remain570h, and all nine request-buffer partitions pass.
First strict mismatch remains +17/478FB1, zero-register sharing before
PUSH EDI. Code/text exceed callable/metadata bounds by118/116 bytes;
oversize mode remains read-only, with no acceptance or execution.

A private explicit common-default goto control increases the int candidate
by32 bytes to prefix81700/text83072 and retains the same first mismatch.
It is unselected; the generator is unchanged. Final selected witnesses were
rebuilt serially after two exploratory compiler invocations briefly overlapped.

Compact void object SHA256:
`9b747f8a104295b0295d1f03de4da5b5c596d823dcb7959d2670f0665b723432`,
text50800 (56 bytes above the preceding compact form). Fresh native replay
has **0/1520 differences**:1010 integration plus510 default inputs, digest
`c7eb7786df3d3bb4ef0033034538133b6932e70f2fca43d9190b665c5c5aa140`.
Stops are1230 RET,82 object requests,30 effects,177 common calls and1 set669.
Actual original helpers run through RET or the first real world boundary.
Later returned-world continuations remain unproved. Bool staging also builds.
No accepted unit, relocation allowlist, shared layout/header, source selection,
exact credit or aggregate cold replay changes.

```bash
python3 scripts/probe-reimu-action-source-shape.py --void-root --output-dir build/reimu-live-action/current-expanded
python3 scripts/audit-reimu-root-relocations.py --diagnostic-oversize build/reimu-live-action/current-expanded/ReimuActionStateDispatch.obj
python3 scripts/audit-reimu-root-stack.py --diagnostic-oversize --require-contracts build/reimu-live-action/current-expanded/ReimuActionStateDispatch.obj
python3 scripts/probe-reimu-action-source-shape.py --compact --void-root --output-dir build/reimu-live-action/current-compact
python3 scripts/audit-reimu-void-root.py build/reimu-live-action/current-compact/ReimuActionStateDispatch.obj --cohort integration --cohort defaults
```

Local source/compiler/build receipts pin the current inputs and serial builds.
Rejected controls and unused products are cleaned after retaining their facts.
Next prioritize the observed300/320 prefix/tail split and the remaining
source/compiler ownership and size differences before canonical acceptance.
