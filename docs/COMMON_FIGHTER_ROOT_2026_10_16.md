# Shared Fighter root: typed virtual tails, October16–17

The active major target is `Fighter_update_common_action_state @ 4740C0`,
the10219-byte CharacterEx method used by all15 roster action roots. It remains
nonexact. This pass adds receiver-domain evidence for its eight register tail
jumps, aligns the source call interface with already accepted animation
methods, and improves the independently attested Ghidra working model.
No function or partial authored bytes are credited as exact.

## Target observations

Only original Japanese1.06a SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is analyzed. IDA preflight still rejects the attached session; it is unused.
The raw callable is `[4740C0,4768AB)`, body SHA-256
`7def23cf4826d7511260e7d9ea8db18848c43a7b77939bb42724a29af117a0c6`.
The existing switch mapper independently validates both index/destination
tables. Raw traversal reaches all2799 instructions and10219 callable bytes.
The separate compiler metadata remains outside the authored callable extent.

The original eight register exits are:

| Jump site | Instruction | Observed function-pointer load |
| --- | --- | --- |
|474703| JMP EAX | receiver vtable+14 |
|47486D| JMP EAX | receiver vtable+14 |
|474A7B| JMP EAX | receiver vtable+14 |
|475584| JMP EDX | receiver vtable+14 |
|47563B| JMP EDX | receiver vtable+14 |
|476037| JMP EDX | receiver vtable+14 |
|4760BE| JMP EDX | receiver vtable+14 |
|476203| JMP EDX | receiver vtable+14 |

Every suffix restores EDI/ESI/EBX and removes the root's four-byte temporary
before jumping. Some suffixes reload ECX from ESI; the early guards retain
the original ECX. A forward register-provenance analysis over the complete
validated CFG, including all switch destinations and joins, proves ECX equals
the entry receiver at each exit and the target was loaded from that receiver's
vtable+14. CALL invalidates EAX/ECX/EDX; preserved EBX/ESI/EDI/EBP follow the
ordinary x86 ABI. Partial-register writes also invalidate pointer provenance.
The analysis does not infer branch feasibility or an x87 value model.

## Qualified receiver domain and source interface

The new read-only command
`python3 scripts/audit-common-fighter-indirect-tails.py --json` independently
checks sixteen distinct primary vtables: CharacterEx at6C3F94 and all fifteen
roster tables from the existing origin anchors. Each anchor's name must agree
with raw primary RTTI. Each hierarchy contains one CharacterEx descriptor
with PMD `(0,-1,0)`, requiring no receiver/base adjustment. Every table has:

| Slot | Target | Already accepted interface model |
| --- | --- | --- |
|+8|45BFE0| `int set_action(short)` |
|+C|45C390| `int select_sequence(int)` |
|+14|45C220| `unsigned char next_sequence_block()` |

**Inference:** for this reviewed receiver domain, all eight register exits
are tail calls to `AttackObject_next_sequence_block @ 45C220`. Their singleton
target is conditional on that domain and the stated calling convention.
Unreviewed receiver domains are not inferred. The original raw owner audit
continues to report its eight indirect exits; this supplementary qualification
does not erase them or alter the canonical comparator.

The common-root source now uses these existing result models instead of local
void declarations, and names slot14 as next_sequence_block. The root discards
all three results. This is interface consistency with independently accepted
callees, not proof of uniquely original C++ return spelling from ignored EAX.
No vtable slot, stack width, layout, numerical operation or side effect changes.

## Canonical and compiler controls

Fresh ordinary pinned VC8 builds before and after the interface correction
have the same canonical10219-byte comparison-window SHA-256:
`99563500433bccf1f68e7c256b438595de9cdcf5b18aee4816f19e69e1cda835`.
They retain53/66 instruction/edge-identical diagnostic owners, metadata+2838
and10801-byte COFF section tail. Complete comparison remains nonexact at+14;
owner counts and section length are not exact-byte credit.

One RTM14.0.50727.42 cl/c1xx/c2 control uses the same pinned SP1 headers and
unchanged `/O2 /GS- /GR /EHsc /MT` flags. It reproduces the same comparison
window and53/66 result, providing no reason to change compiler profile here.
Its exact binary/tool hashes and command are retained in the private build
receipt; it is not a new accepted compiler profile.

Two scalar controls narrow the shared rounded clamp value alone, or both that
value and its zero comparison scalar, to float. Both fall to52/66, remove
required rounding stores/reloads in55/56 and159..162, and lose action799.
They are rejected. Promoting the early clamp's zero comparison literal to
double is byte-neutral. None of these controls replaces the retained numerical
source or justifies fabricated spills, volatile locals or padding.

The remaining thirteen owners still concern switch SUB versus ADD-negative,
early versus late clamp ownership, and the73/75/88 sequence-selection owner.
The new receiver facts address indirect call identity, not those code-generation
residuals. Previous negative source matrices remain documented in the landing,
exit-phase and October2 records; do not repeat them without a new discriminator.

## Direct Ghidra working state

One Ghidra12.1 process at a time re-attests the executable identity, actual
entry68B9D2, image base, x86 Windows compiler and every mapped .text byte.
The root body hash and complete extent are checked independently.

The saved method view describes51 named physical fields in a7A4-byte prefix,
with a typed vtable prefix for the three called slots. This is a method view,
not a new claim about complete original class size. Fifteen direct helper
declarations retain their reviewed register/stack/result contracts. The root
is void with its receiver in ECX and no explicit stack arguments.

The eight qualified sites receive computed-call references to45C220 and
CALL_RETURN flow overrides as explicitly labeled receiver-domain inferences.
These are analysis metadata; original JMP opcodes and all target bytes remain
unchanged. A fresh process reads back the types, helper declarations, root
storage, eight references and overrides. The decompiled result remains a
hypothesis and is not pasted as reconstruction source.

The earlier PIC/unreachable-block warnings and the eight root-local virtual
tail warnings are gone. A warning at helper4351F8 remains outside this root;
its separate indirect behavior is not qualified by this packet.

Recipes/working data are under `.analysis/common-fighter-20261016/`. Reports
use `build/fighter-common-20261016-`: final-build/formal/owners, virtual-facts,
indirect-tails, RTM controls, and Ghidra save/readback logs. The canonical
root object stays in its configured match-unit path. Reproduce the main checks:

```bash
python3 scripts/build.py --unit gpt-web-fighter-common-action-state --json
python3 scripts/compare-unit-object.py gpt-web-fighter-common-action-state build/match-units/GptWeb_FighterCommonActionState.obj --json
python3 scripts/audit-giant-action-owners.py fighter-common-action build/match-units/GptWeb_FighterCommonActionState.obj --unit gpt-web-fighter-common-action-state --json
python3 scripts/audit-common-fighter-indirect-tails.py --json
```

The new receiver-flow tests reject volatile-call clobbers, conflicting incoming
paths, partial-register corruption, non-vptr loads, unvalidated switch tables,
LOOP receiver destruction, instruction-interior edges, and disagreeing/empty
vtable domains. They also exercise a singleton target in an agreeing domain.
These protect the analysis inference; canonical exact acceptance is unchanged.
