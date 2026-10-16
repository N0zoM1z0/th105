# Common Fighter root: native deque and genuine link context

The shared `Fighter_update_common_action_state @ 0x004740C0` remains
**nonexact** over its complete10219-byte target callable. All15 roster action
roots call it. This batch replaces its checked-container facade with the real
VC8 SDK member and closes a reproducible diagnostic link; it awards no authored
function, partial-byte or exact-byte credit.

## Observed target and retained source

The hash-attested Japanese1.06a target remains SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Its2799-instruction callable is `[4740C0,4768AB)`, with body SHA-256
`7def23cf4826d7511260e7d9ea8db18848c43a7b77939bb42724a29af117a0c6`.
The attached IDA still fails target attestation and is unused. This batch uses
the attested raw PE and compiler/linker output, with no database writes.

The root's source-local20-byte container at+55C is now
`std::deque<FighterSequenceSlot>`. The existing record has98hex-byte stride.
The actual SDK `operator[](unsigned)` reproduces target4399C0's complete94
bytes, including ordinary ECX receiver, stack index and RET4. Its canonical
SHA-256 is
`5e6d9bae7c00a857a51b7ca00c03b37c95e1986a9e389d56e35924b205f7491b`.
The root's sole index-zero read uses that real member. Only its local type and
unit-specific REL32 binding change; no shared C++ header or compiler profile
changes. Library provenance does not count as authored progress.

Fresh ordinary `/O2 /GS- /GR /EHsc /MT` comparison retains53/66 diagnostic
owners, metadata offset10296 and10801-byte section tail. The complete
canonical section tail, including switch metadata, is identical before/after:
`f72e0b9eed9f9ac5167af49873d7cd3a4c26712f7bdcd6c50b5249eeb5e6c045`.
The10219-byte comparison-window hash remains
`99563500433bccf1f68e7c256b438595de9cdcf5b18aee4816f19e69e1cda835`.
Whole comparison still fails at+14/4740D4; equal candidate hashes are neutrality
evidence, not target exactness.

A fresh72-case native animation smoke passes0 differences through genuine
RET, visiting121 target/root instructions with the original virtual/frame/
tree/sprite dependencies. Input SHA-256:
`2b98759c046fd80b96c7d876dc45d93f9c90fe55c4a23c53fd27624416fece50`.
The earlier6048 animation and14208 motion matrices are not rerun or expanded.
Their resource, geometry and numerical scope remains as documented in
[animation](COMMON_FIGHTER_NATIVE_ANIMATION_2026_10_17.md) and
[motion](COMMON_FIGHTER_NATIVE_MOTION_2026_10_17.md).

## Real source and library link

`scripts/probe-common-fighter-ltcg.py` builds the real root with `/GL`, keeps
the explicit SDK deque member in ordinary COFF, and links24 real game source
providers plus the pinned static VC8 CRT and Windows SDK libraries. There
are no stub bodies, code ABS symbols, manufactured callers, `/FORCE` options
or unresolved link inputs. The probe records source/object/image/map/tool/
library hashes, build commands, data bindings and separate dependency checks
under `build/common-fighter-ltcg/`.

Five source-local diagnostic partitions retain the actual required complete
method bodies plus their declarations, types, inline helpers and globals:

| Source | Retained out-of-class methods |
| --- | --- |
| CharacterObjectRuntime | advance_frame_and_dispatch |
| SharedBattlePhase | emit_fighter_effect_433cc0 |
| BattleBackgroundLayout | set_runtime_scalar |
| EventEffectState | set_event_id, emit_effect |
| EventEffectStateRuntime | publish_stage_state_469d50 |

Uncalled render, shutdown and phase bodies otherwise pull unrelated missing
definitions into the link. These are hypothesized diagnostic partitions,
not recovered original TU boundaries. A source-selection guard rejects changed
method inventories or unbalanced bodies. Shared sources and accepted profiles
are not edited.

Twenty-seven of28 selected dependency addresses canonically replay; all root
direct game dependencies are among the exact checks. Resource handle lookup
417800 remains the explicit nonexact exception, with its already documented
EH/private-vector residual. The source implementation is retained in full.
This diagnostic image is not executed and does not establish equivalence of
the complete event/resource graph.

Seventeen linker aliases connect existing bounded-view names to real
implementations at the same target addresses. These include declarations
whose source return/parameter spelling differs across views; they do not
prove uniquely original C++ declarations or unobserved return values. Map
normalization requires the alias and actual definition at the same linked
address and in the same object. Twelve unresolved game-data symbols bind only
to ledger-attested bytes in non-executable target sections; function bindings
and changed/unmapped data are rejected.

The actual SDK deque member is independently canonical94/94 before and after
linking. This closes its caller/callee ABI without the privately specialized
EDI/index-zero boundary seen in the earlier
[Aya link experiment](AYA_CPU_LINKED_ABI_2026_10_17.md).

## Linked root result and limits

The resulting root has10233 reachable callable bytes/2842 instructions plus
three trailing alignment bytes before metadata. Both switch dispatches close:
51 destinations/132 indices and15 destinations/109 indices. All207 direct
call sites resolve to16 source/runtime functions, with no unresolved indirect
exits or internal call targets. This is a complete diagnostic CFG inspection,
not a canonical root comparison or a native gameplay test.

The entry adds `PUSH EBP; MOV EBP,ESP; AND ESP,-8`, absent from the target.
The first action normalization remains `ADD EAX,-50` at linked offset24hex;
the target uses `SUB EAX,50` at1Ehex. Thus a closed real-body `/GL` link with
this source and opaque target-compatible deque boundary does not recover the
required lowering. It does not prove LTCG irrelevant or exhaust real source,
visibility, compiler or link contexts.

A private six-float-temporary control removes that aligned frame, but still
uses ADD-negative. It exposes eight candidate virtual tail jumps and several
direct tail jumps; its full candidate receiver/ABI closure is not claimed.
Earlier ordinary scalar narrowing already lost required rounding stores and
action799. The control is not retained in source or acceptance flags.

Two action-field accessor controls are also rejected: retaining the cached
action is byte-neutral; replacing it with repeated predicates drops53/66 to
52/66, losing action799 without a new identical owner. The remaining task is
the target's joint clamp/sequence physical ownership and switch lowering,
while preserving the observed rounding. Original source lifetimes and the
original link visibility remain unknown.

## Reproduce the current checkpoint

```bash
python3 scripts/build.py --unit gpt-web-fighter-common-action-state --compare --json
python3 scripts/audit-giant-action-owners.py fighter-common-action \
  build/match-units/GptWeb_FighterCommonActionState.obj \
  --unit gpt-web-fighter-common-action-state --json
python3 scripts/compare-unit-object.py cross-v106a-battle-info-record-render \
  build/match-units/GptWeb_FighterCommonActionState.obj --address 0x004399C0 --json
python3 scripts/audit-common-fighter-animation-paths.py \
  build/match-units/GptWeb_FighterCommonActionState.obj --smoke
python3 scripts/probe-common-fighter-ltcg.py
python3 scripts/ci.py
git diff --check
```

The first command intentionally returns mismatch. The SDK comparison returns
exact, smoke returns zero sampled differences, and the link probe reports the
diagnostic scope above. No unrelated accepted-unit or aggregate cold replay
is claimed.
