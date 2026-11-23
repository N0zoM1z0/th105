# Udonge action initializer at 0x005D0E60

`0x005D0E60`, Udonge Fighter primary slot+3C, now has complete selected source in
`src/characters/UdongeActionEntry.cpp/.hpp`. The pointer-only call view must never
be constructed or embedded. Numeric states and typed offset accesses remain
intentional; full nominal layout and original compiler/TU context are unknown.

## Current complete comparison

The selected VC8 SP1 build matches all 5,070 bytes after replaying 197
relocations. The comparison includes all three switch tables, including
78 destination words, 695 remap bytes and alignment.
Changing the final remap byte in any of the three tables in a copy of the
matched object preserves callable equality. The full comparison catches
each change at its own address.

```sh
DISPLAY= WAYLAND_DISPLAY= PATH="$PWD/.tools/factory-bin:$PATH" \
  scripts/repo-python scripts/build.py \
  --unit exact-first-udonge-action-entry --compare --json
```

Before the scheduling change, replacing 168 literal accesses with checked
receiver members produced identical canonical bytes across the complete
5,038-byte candidate. The members cover motion, facing, action ID and
phase state. Call sites that pass an unsigned direction still explicitly
convert the signed facing byte. The receiver view is local to this
translation unit.

## Ordering the horizontal multiply in cases 404 and 406

The native 404/406 entry at `0x005D18CD` restores EDI at `0x005D18D7` after
its first x87 store. Native 650 starts at `0x005D1CED`, restores EDI at
`0x005D1CF7` and computes both products locally. In the previous build,
404/406 restored EDI at `0x005D1901`. Case 650 jumped from
`0x005D1D09` into the 404/406 tail at `0x005D18FF`.

The pinned VC8 SP1 C2 carries both case-local multiply pairs at
`0x10C0661B`. At `0x10C077B6`, immediately after the pass at `0x10B2C950`,
the 650 pair has disappeared and the 404/406 pair survives. The read-only
headless trace emits the same complete candidate bytes. This is the same
late pass that shares Reimu's x87 tail.

Moving the horizontal multiplication just before the 404/406 write to
`+0x750` changes both arms. At `0x10C0661B`, the flag store now separates
the two multiply sequences in 404/406, while 650 has no flag store between
them. At `0x10C077B6`, all four multiply nodes retain their identities.
The traced build matches the full 5,070 bytes, including both native EDI
restores. Moving the horizontal operation earlier in 650 alone also
yields the same relocated bytes. Moving the vertical operation first
keeps the complete size and differs by four bytes in the affected arm.
A shared switch exit, staging the product in a temporary and reversing
multiplication operands either preserve the old result or move the join.
The retained source changes the order of two statements in 404/406.

## Observed target identity, boundary and ABI

The original Japanese 1.06a executable is pinned to SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Existing frozen RTTI/vtable origin anchors classify this root authored; vtable
cell `0x006C5E68` contains 5D0E60. Its candidate was unclassified in the source
ledger, with no durable name/source selection before this work.

The 4057-byte callable spans 5D0E60..5D1E38 inclusive, SHA256
`ee9042f9ce3cce0eca2ffeced71d6ee622ed0aadd6c8e0c7a96dc5fed816c863`.
It decodes 1023 instructions:1018 reachable instructions plus five unreachable
compiler alignment instructions totaling 24 bytes. They are 6-byte LEA at 5D12BA,
7-byte LEA at 5D1408, NOP at 5D140F,7-byte LEA at 5D1496 and 3-byte LEA at 5D149D.
Full CFG traversal accounts for exactly those alignment instructions and all
other edges; there are 54 RET 0 exits,65 direct calls, no indirect calls and no
external tail. No manual padding is added to source.

| Target region | Extent / size |
| --- | --- |
|Callable|5D0E60..5D1E38 /4057|
|Alignment|5D1E39..5D1E3B /3, `8d4900`|
|Low destination table|5D1E3C..5D1EAB /28 DWORDs|
|Low remap, actions 4..214|5D1EAC..5D1F7E /211 BYTEs|
|Alignment|5D1F7F /1, `90`|
|Middle destination table|5D1F80..5D1FFB /31 DWORDs|
|Middle remap, actions 302..551|5D1FFC..5D20F5 /250 BYTEs|
|Alignment|5D20F6..5D20F7 /2, `8bff`|
|High destination table|5D20F8..5D2143 /19 DWORDs|
|High remap, actions 565..798|5D2144..5D222D /234 BYTEs|
|Following separation|5D222E..5D222F /2 INT3 bytes|

All 78 destination entries land at decoded callable boundaries. Special 300/301
and 560/561 branches precede the regional tables. Full 5070-byte payload SHA256:
`8f038ebad8a86ccfd5a48f007796421cd0d68b741fec384e4540cc905cb917aa`.

The root receives ECX, reserves 16 local bytes and saves EBX/ESI/EDI. Native calls
comprise 14 visual resets 5D06D0,4 secondary-event cycles 473F90,10 effect emits 435240,
2 scalar publications 4359D0,2 indexed events 4359F0,30 motion clears 45AF40,one
object request 465190,one wave-handle dispatch 45C030 andone common fallback 477830.
The October candidate emitted 17 visual-reset copies and 56 RETs. The
71/73/74/145 acceleration and visual arms accounted for the additional copies.

The existing 27-byte visual helper remains independently exact and unchanged.
The new local effect-call declaration exposes the target's byte-facing argument
carrier; it changes neither that helper's implementation nor existing int-facing
public declarations. The object request consumes seven ordinary four-byte stack
slots and returns with 28-byte cleanup; its facing is explicitly zero-extended.

## Inferred source shape and bounded experiments

The retained Alice action-entry source is a family reference only. Udonge's
actual states, numeric fields, effect/event numbers and table ownership were
independently recovered. The first complete candidate was compiled/compared
before tuning. No decompiler text was mechanically pasted as source.

| Trial | Complete-payload result and evidence |
| --- | --- |
|00|Complete 4818-byte source. Case-scoped real payload lets VC8 replace all 14 visual-reset CALL/RET pairs with external tails. No exact claim.|
|01|Function-scope payload lifetime restores all 14 visual CALLs and common fallback CALL. Full 4846. This independently differs from SakuyaObject's case-local lifetime.|
|02|Use native per-case publications/returns instead of broad common-output labels. Full 5126;30 target motion calls are still 29, and visual-reset copies become 17 rather than 14.|
|03, rejected shape|A real float acceleration phi follows target's shared store hypothesis, but VC8 spills it and keeps 17 physical copies. Full 5150.|
|04, retained call view|Byte-facing effect arguments recover all 30 motion-call copies and target direction/load forms. Full 5142 in the phi context. Existing shared declarations are unchanged.|
|05, unselected|Independent early 300/301 publication changes regional placement but does not recover the target layout. Full 5142, different SHA.|
|06, unselected|Double acceleration removes the float spill but selects non-native QWORD literal loads and still keeps 17 copies. Full 5102. Size is not acceptance.|
|07, neutral|Place the shared acceleration labels at their native first-use arm. Entire output is byte-identical to 04.|
|08, neutral|A typed offset-prefix view, with compiled offsetof checks, is byte-identical to 04. Do not repeat the layout/spelling question.|
|October checkpoint|Drop the rejected phi and retain the ordinary per-case body with the byte call view. Full 5118. All ten scoped native controls pass.|

These working artifacts are not committed. Source retains actual function-scope
float payload, signed WORD state writes, signed BYTE60E guard, independent repeated
callbacks and declaration-only helper interfaces. No asm, copied machine bytes,
inert locals, fake returns or ABI/register forcing is used.

## Ten concrete native controls

Nine inputs execute the real target helpers and complete RET 0. One 308 input
stops at the real 465190 object-request entry; that helper and all subsequent
behavior are outside the prefix. No helper result is injected.

- Four 70 inputs distinguish positive, negative, zero and quiet-NaN saved motion.
  Target independently confirms signed WORD730 values-1/1/0/0.
- 145 clears heading 12C while 149 preserves the original 37.5; both use the real
  visual reset helper.
- 308 confirms pre-callback payload `{9,-8,5}`, action 848, actual x/y, zero-extended
  facing 255, layer 1 and count 3 after the observed state publications.
- Three 550 inputs distinguish skill 3/4/-1. Target confirms WORD736 is 1 only at 4;
  the guard is signed, not an unsigned interpretation of BYTEFF.

Actor bytes, helper receiver/call order, stack cleanup and x87 control/TOP/tags
agree in all ten inputs. Input-vector SHA256:
`54ab7131fa536d84527f77cfd2a7219a360cf18de565cdcbb7a7b922d1a16ea9`.
An intentionally unsigned skill-guard control fails exactly the skill-1 input;
it is not selected source. These are scoped semantics/ABI diagnostics, not a
whole-root gameplay or canonical equivalence proof.

## Analysis provenance and resource control

The mandatory IDA preflight rejects GUI SHA256
`10350095bcf95edb59e03bee9849a2dc8a7714b4927ad5909c569c550fce6822`.
No IDA semantic query/write is used. One direct read-only Ghidra run independently
attests executable/import hash, Windows x86 language/compiler, imagebase,
entry 68B9D2, every raw-backed mapped section and root bytes. Temporary bounded
entry/call views are read back and rolled back; all nine primary database file
hashes remain unchanged. Decompiler output is a hypothesis, especially its
integer-typed float fields and shared-output reconstruction. Raw target bytes
are never patched.

Ghidra uses 384MiB and CPU 0/nice10. All builds and native controls are serial and
pinned likewise. Three new literal bindings are witnessed at 6C3C70=float 1.3,
6C3C68=float-12 and 6C4798=float 5.5. Existing bindings, shared headers, helper
implementations, accepted exact units, flags and authored-origin denominator
are unchanged. This is source-present progress only.
