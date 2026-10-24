# Udonge action initializer: complete source, nonexact

`0x005D0E60`, Udonge Fighter primary slot+3C, now has complete selected source in
`src/characters/UdongeActionEntry.cpp/.hpp`. The pointer-only call view must never
be constructed or embedded. Numeric states and typed offset accesses remain
intentional; full nominal layout and original compiler/TU context are unknown.

## Current complete comparison

Formal and independent cold builds both emit **5118 bytes against5070 target**,
canonical SHA256
`3dc949e40be9fb85b71de6b164eeba5cf164f4afa8b0c911a7db10ad8013c0f4`.
First mismatch is **+0x16 /0x005D0E76**, targetE1/source13, a downstream regional
branch displacement. This size difference is not an unreconstructed-byte count.
All three destination counts28/31/19 and all211/250/234 remap bytes are retained;
the three remap byte arrays independently compare equal. Destination addresses
still differ with the callable layout. Source presence is not exact acceptance;
`matches.csv` and exact totals are unchanged.

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit exact-first-udonge-action-entry --compare --json
python3 scripts/audit-udonge-action-entry.py
taskset -c 0 nice -n 10 python3 scripts/audit-udonge-action-entry-paths.py
```

The first two commands return1 with this recorded mismatch. The last returns0
for ten scoped inputs. Both audits accept `--object` for an independent object
or a negative control. The full audit replays every emitted relocation and
requires complete payload length/byte equality; no callable or metadata bytes
are masked. No partial exact or aggregate cold-replay claim is made.

## Observed target identity, boundary and ABI

The original Japanese1.06a executable is pinned to SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Existing frozen RTTI/vtable origin anchors classify this root authored; vtable
cell `0x006C5E68` contains5D0E60. Its candidate was unclassified in the source
ledger, with no durable name/source selection before this work.

The4057-byte callable spans5D0E60..5D1E38 inclusive, SHA256
`ee9042f9ce3cce0eca2ffeced71d6ee622ed0aadd6c8e0c7a96dc5fed816c863`.
It decodes1023 instructions:1018 reachable instructions plus five unreachable
compiler alignment instructions totaling23 bytes. They are6-byte LEA at5D12BA,
7-byte LEA at5D1408, NOP at5D140F,7-byte LEA at5D1496 and3-byte LEA at5D149D.
Full CFG traversal accounts for exactly those alignment instructions and all
other edges; there are54 RET0 exits,65 direct calls, no indirect calls and no
external tail. No manual padding is added to source.

| Target region | Extent / size |
| --- | --- |
|Callable|5D0E60..5D1E38 /4057|
|Alignment|5D1E39..5D1E3B /3, `8d4900`|
|Low destination table|5D1E3C..5D1EAB /28 DWORDs|
|Low remap, actions4..214|5D1EAC..5D1F7E /211 BYTEs|
|Alignment|5D1F7F /1, `90`|
|Middle destination table|5D1F80..5D1FFB /31 DWORDs|
|Middle remap, actions302..551|5D1FFC..5D20F5 /250 BYTEs|
|Alignment|5D20F6..5D20F7 /2, `8bff`|
|High destination table|5D20F8..5D2143 /19 DWORDs|
|High remap, actions565..798|5D2144..5D222D /234 BYTEs|
|Following separation|5D222E..5D222F /2 INT3 bytes|

All78 destination entries land at decoded callable boundaries. Special300/301
and560/561 branches precede the regional tables. Full5070-byte payload SHA256:
`8f038ebad8a86ccfd5a48f007796421cd0d68b741fec384e4540cc905cb917aa`.

The root receives ECX, reserves16 local bytes and saves EBX/ESI/EDI. Native calls
comprise14 visual resets5D06D0,4 secondary-event cycles473F90,10 effect emits435240,
2 scalar publications4359D0,2 indexed events4359F0,30 motion clears45AF40,one
object request465190,one wave-handle dispatch45C030 andone common fallback477830.
The selected source has every count except visual-reset physical copies:17
versus14, and56 RETs versus54. Its extra copies implement the still-unmerged
71/73/74/145 acceleration/visual family. All three action-remap arrays agree;
these counts do not establish canonical equality.

The existing27-byte visual helper remains independently exact and unchanged.
The new local effect-call declaration exposes the target's byte-facing argument
carrier; it changes neither that helper's implementation nor existing int-facing
public declarations. The object request consumes seven ordinary four-byte stack
slots and returns with28-byte cleanup; its facing is explicitly zero-extended.

## Inferred source shape and bounded experiments

The retained Alice action-entry source is a family reference only. Udonge's
actual states, numeric fields, effect/event numbers and table ownership were
independently recovered. The first complete candidate was compiled/compared
before tuning. No decompiler text was mechanically pasted as source.

| Trial | Complete-payload result and evidence |
| --- | --- |
|00|Complete4818-byte source. Case-scoped real payload lets VC8 replace all14 visual-reset CALL/RET pairs with external tails. No exact claim.|
|01|Function-scope payload lifetime restores all14 visual CALLs and common fallback CALL. Full4846. This independently differs from SakuyaObject's case-local lifetime.|
|02|Use native per-case publications/returns instead of broad common-output labels. Full5126;30 target motion calls are still29, and visual-reset copies become17 rather than14.|
|03, rejected shape|A real float acceleration phi follows target's shared store hypothesis, but VC8 spills it and keeps17 physical copies. Full5150.|
|04, retained call view|Byte-facing effect arguments recover all30 motion-call copies and target direction/load forms. Full5142 in the phi context. Existing shared declarations are unchanged.|
|05, unselected|Independent early300/301 publication changes regional placement but does not recover the target layout. Full5142, different SHA.|
|06, unselected|Double acceleration removes the float spill but selects non-native QWORD literal loads and still keeps17 copies. Full5102. Size is not acceptance.|
|07, neutral|Place the shared acceleration labels at their native first-use arm. Entire output is byte-identical to04.|
|08, neutral|A typed offset-prefix view, with compiled offsetof checks, is byte-identical to04. Do not repeat the layout/spelling question.|
|Selected|Drop the rejected phi and retain the ordinary per-case02 body with the proven04 byte call view. Full5118, matching formal/cold SHA above. All ten scoped native controls pass.|

Private frozen recipes/sources are under
`.analysis/exact-first-udonge-entry-20261024/`; generated objects, full normalized
payloads, CFG/literal receipts and reports are under the corresponding `build/`
directory. These working artifacts are not committed. Source retains actual
function-scope float payload, signed WORD state writes, signed BYTE60E guard,
independent repeated callbacks and declaration-only helper interfaces. No asm,
copied machine bytes, inert locals, fake returns or ABI/register forcing is used.

The regional branch placement, three extra visual-reset copies and some x87
storage scheduling remain nonexact. Original source variables, complete owner
layout, TU visibility and standalone/LTCG ownership are unknown. Two neutral
controls are retained; switch to another complete representative unless new
independent evidence changes the question.

## Ten concrete native controls

Nine inputs execute the real target helpers and complete RET0. One308 input
stops at the real465190 object-request entry; that helper and all subsequent
behavior are outside the prefix. No helper result is injected.

- Four70 inputs distinguish positive, negative, zero and quiet-NaN saved motion.
  Target independently confirms signed WORD730 values-1/1/0/0.
- 145 clears heading12C while149 preserves the original37.5; both use the real
  visual reset helper.
- 308 confirms pre-callback payload `{9,-8,5}`, action848, actual x/y, zero-extended
  facing255, layer1 and count3 after the observed state publications.
- Three550 inputs distinguish skill3/4/-1. Target confirms WORD736 is1 only at4;
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
entry68B9D2, every raw-backed mapped section and root bytes. Temporary bounded
entry/call views are read back and rolled back; all nine primary database file
hashes remain unchanged. Decompiler output is a hypothesis, especially its
integer-typed float fields and shared-output reconstruction. Raw target bytes
are never patched.

Ghidra uses384MiB and CPU0/nice10. All builds and native controls are serial and
pinned likewise. Three new literal bindings are witnessed at6C3C70=float1.3,
6C3C68=float-12 and6C4798=float5.5. Existing bindings, shared headers, helper
implementations, accepted exact units, flags and authored-origin denominator
are unchanged. This is source-present progress only.
