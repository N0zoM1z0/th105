# Sakuya Fighter action-state reconstruction, 2026-10-28

Complete113-action/default manual source is selected for4CADB0. Whole native
comparison remains nonexact; source presence is not exactness or equivalence.

The canonical Japanese1.06a target SHA256 is
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.
The provisional41511-byte entry span is not the full callable. Existing ownership
records independently hash ten remote chunks through4DD2D2 exclusive. All prior
chunk hashes still agree. The complete contiguous callable extent is75042 bytes,
SHA256 a7d5eb49423691b16358efbb5cb857867932c230a86798f84da233fe4207eb51.
Full callable plus metadata [4CADB0,4DD7E0) is76336 bytes, SHA256
6ca4fc284871b25c320bfd93749f548b34b0b55122661caf137ab3efe6db138f.

Raw linear decoding closes19016 instructions. Fourteen jump tables have31/38/38
primary dimensions and eleven4-entry secondary dimensions. Remaps cover227/226/
230 labels starting0/301/541. Direct300/540/795/797/798 augment108 sparse action
labels. The CFG reaches18993 instructions/74937 bytes, with159 RET0s and190
virtual call sites. The native frame is4D8 and aligned to8. The formal comparison
must use the full owned extent, not only the provisional entry span.

## Alignment correction

Earlier ownership excluded seven-byte LEAs at4D2839,4D2C79 and4D2E19 but still
counted the preceding short jumps at4D2C77 and4D2E17. Both are unreachable
alignment instructions. Their immediate predecessors unconditionally branch to
4D2C8C and4D2E2A. Complete traversal of all14 tables and direct edges reaches
neither short jump; they skip their following LEA to the16-byte boundaries
4D2C80/4D2E20. The two exclusion spans now include the short jumps and are hashed
as nine bytes each. Main excluded bytes are25, not21; owned bytes are74937,
not74941. All remote chunks and remote_exact=false remain unchanged.

This is correction of four compiler-alignment bytes in the denominator, not
new restoration progress. Full-payload byte comparison still includes every
alignment byte; no masking or altered acceptance boundary is introduced.

## Analysis route

Local IDA preflight still lacks its pinned MCP runtime; that session is unused.
The existing Factory-native IDA decompiler failure was not retried. A separate
Ghidra session through Factory repository Bash re-attested imported executable
identity, entry68B9D2, x86/Windows specification and every mapped .text byte before
bounded analysis. Known ordinary helper ABIs, including exact45E0E0, were read
back in the isolated project. Full navigation export completed377265 bytes and
the project saved, verified after a client timeout before any repeat operation.

Decompiler removed-block/spacebase warnings remain hypotheses to review against
raw instructions. No target bytes or IDA metadata changed. The initial Iku
project is untouched. Receipts and raw disassembly are in
build/frontier-4cadb0-20261028/{target-facts.json,target-facts.log,target.asm,ghidra.log};
private preparation is .analysis/frontier-4cadb0-20261028/.

## Complete source and replay

`src/characters/SakuyaActionState.cpp/.hpp` now provide all113 primary action
labels and the shared default, including pre-dispatch time-control effects,
movement, normals, skill/projectile requests, spells and story patterns. The
view is pointer-only; no complete Sakuya allocation/layout is asserted. Shared
sequence slots and ordinary direct-call ABIs retain their existing contracts.
The separate exact45E0E0 predicate uses its observed fastcall Boolean result.

Fresh raw RTTI readback: primary vtable6C4914, slot28 cell6C493C ->4CADB0;
COL6DA220 -> type descriptor6E8158, name at6E8160 `.?AVSakuya@@`.
All138 new relocation aliases are isolated to this unit. Literal bindings use
actual operand widths/IEEE bytes. Match selector6FA894 is freshly observed at
4DA8BC/4DAEA1/4DB4FB and later story sites; no global-layout claim is added.

The focused unit `exact-first-sakuya-action-state` uses VC8 SP1 O2/GS-off and
`owned_extent=true`, so formal comparison includes the main and ten remote
chunks, plus105 alignment bytes. `scripts/audit-sakuya-action-state.py` also
replays every section relocation and compares the entire76336-byte payload,
including14 native tables and three remaps, without masks.

Selected full source output77144 bytes, SHA256
410a41cea3c1b4150bfcab1264b176af6d88200da12bb8d1af004b5216110ad2.
First difference+8 /4CADB8 is frame4A8 versus native4D8; full payload has73221
unequal positions including length difference. Source has13 tables with primary
30/39/38 versus native31/38/38,163 returns versus159,184 virtual sites versus190.
The remap lengths227/226/230 agree, but contents and owner grouping differ.
No exact ledger entry or remote_exact promotion is made.

Bounded per-action traversal finds direct-call-site count differences only in
404/405 (counter helper2 native versus3 candidate) and567 (spawn3 versus2).
Floating-operation count differences remain in214 and404/405/406. These counts
are navigation diagnostics, not proof of semantic or byte equivalence. Native
567 has two identical argument branches, which this compiler merges.

Private frame/payload dataflow closes all113 action partitions with no unknown
payload pointers and95 request homes in both target and candidate. Native
frame1240 versus1192 differs by48 bytes; several native homes are16 bytes apart
although only three words are visibly initialized/passed. Original declaration
extent, lifetime and compiler sharing remain unknown. No inert fourth word or
padding is inserted to force the frame. All58 native and57 candidate surface
consumers, and8 native/7 candidate on-surface consumers, test AL. Physical
counts differ through shared tails and are not ABI changes.

Receipts: build/frontier-4cadb0-20261028/{formal-build.json,formal-audit.json,
target-audit.json,action-call-comparison.json,action-fp-comparison.json,
native-payload-homes.json,candidate-payload-homes.json,payload-review.log}.
Only this new unit was natively compiled; unchanged accepted receipts remain
incremental. The default repository gate is separate from native exact replay.

## Target-backed shared counter continuation

The native404/405 sequence1 tails join406 at4D0240 to publish730 and call the
counter once. Expressing that actual shared continuation removes the extra
reachable counter sites in404/405. The new selected full payload is77064 bytes,
SHA256 6e219ddc90d401d5c83da2667d60b72f2d518b7d980a4ab1e1c4cba1dd52edb8,
with73205 unequal positions, first+8 and frame4A8 unchanged. Returns reduce to161;
virtual sites184, tables13 and all95 request homes remain unchanged. Only567's
identical-branch spawn-site merge remains in the113-action direct-call census.
The four floating-operation census residuals remain. No exact credit follows
from smaller output or matching per-action call counts.

Updated selected receipts are formal-tail-build.json, formal-tail-audit.json
and tail-payload-review.log in the same build scope. Initial receipts remain
historical and are not the selected source result.
