# ReimuObject: virtual call roles, arguments and actual owner context

Scope is496540's complete owned normal CFG in Japanese1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Fresh target/status/tracking preflights pass; the different open IDA executable
is rejected. No reconstruction source, public header, compiler flag, layout or
accepted match changes. This checkpoint tests whether the physical call-count
differences hide a missing callback or incorrect virtual ABI.

## Every indirect call is resolved from actual instructions

Guarded-switch closure and backward reaching definitions resolve every indirect
call's loaded vtable byte slot and ECX receiver in the complete target/native
normal CFGs. All56 calls use the root object's vtable and root-this receiver.
The previous null-callee census did not distinguish these slot roles.

| Byte slot | Target physical sites | Native source physical sites |
| --- | ---: | ---: |
|0C|11|10|
|14|15|14|
|1C|1|1|
|20|2|2|
|Total|29|27|

All200 action labels800..999 and the out-of-range default have equal slot
sets. Slot-bearing method loads and receiver copies are followed through all
normal predecessor paths. Ordinary calls kill EAX/ECX/EDX; VC8 callee-saved
registers retain their ABI role. The sole extra ECX-preservation fact is the
actual4963A0 helper: its entire66-byte source body independently equals the
target, its normal CFG closes, and it has neither calls nor ECX-family writes.
No general thiscall ECX-preservation assumption is substituted for this proof.
Partial/unsupported writes, unresolved cycles or non-root receivers do not
qualify. This is register/slot evidence, not whole-root semantic equality.

## Argument values require the actual action path

The analysis fixes the primary switch destination for each relevant action,
while retaining its prelude and all nested guarded branches. Full-word MOV,
zeroing and constant LEA facts recover the nearest pushed argument to slots0C
and1C. Calls, ESP changes and stack writes are barriers to unproved argument
recovery. All10 argument-bearing action surfaces agree:

| Action | Slot | Values at its physical call sites |
| --- | --- | --- |
|801|0C|2|
|804|0C|2,2|
|810|0C|3|
|811|0C|0|
|812|0C|3,3|
|815|0C|1|
|817|0C|6,6|
|852|0C|2|
|858|1C|1|
|999|0C|5|

Native site804795 is shared by810/812/852. It passes3 for810/812 but2 for852;
the target uses4976E3 and49B02A separately. Treating one physical callsite as
one constant argument would have missed this distinction. Target811 derives0
with `LEA EDI,[EBX-3]`, source with `LEA EBX,[EDI-3]`; source858 similarly
derives1 from its actual zero-valued base. These are recovered machine values,
not inferred solely from the high-level expressions.

Two independently compiled, deliberately incorrect private source controls
test sensitivity. Swapping select/reset declarations moves the select slot
from0C to10 and is detected in exactly9 action surfaces. Changing only
`set_sequence_frame(1)` to2 preserves every slot surface but flags858's argument.
The66-byte helper stays exact in both controls. Neither altered ABI/source is
selected and no target bytes are patched. Per-action sets still do not prove
call order, loop counts, predicate equivalence, arbitrary aliasing or all modes.

## Action907: the remaining shared slot14 callback

Fresh execution of2048 sequence4 bounce cases agrees for actual target/source
instructions, ordered writes, outputs, normal returns, and logical x87 state at
bounce stores/callback entry. Coverage includes both facings, edge coordinates,
zero/positive/negative/NaN velocities, two control words and phase values0/6.
The target calls slot14 at4A0362 for256 horizontal cases and4A03CB for224
vertical cases. Source site809B2F handles all480. The other1568 cases call none.
The actual138-byte45C220 callback executes with the original ReimuObject
vtable; other admitted providers keep the audit's existing observer contracts.

This directly explains the apparent missing907 indirect call as a physical
two-to-one sharing difference within the admitted bounce behavior. It does not
accept the whole907 action, physical x87 TOP/exception flags, unmasked exceptions,
all resources/vtables, original TU ownership or the root's canonical bytes.

## The actual complete class is now a concrete context lead

Raw RTTI confirms COL6D9C8C, offset0, type descriptor6E7E2C and original name
`.?AVReimuObject@@`. Its hierarchy contains ReimuObject,
CharacterObjectEx<Reimu,ReimuObject>, CharacterObject, CObjectBase,
AttackObject, AnimationObject, AnimationObjectBase and Environment. The
nonzero observed offsets are CObjectBase330, AnimationObjectBase4 and
Environment130; other primary bases are at0.

The full vtable6C40A4 contains17 executable entries through byte slot40; the
next word is another noncode RTTI pointer. All17 destinations already have
source selections:13 are accepted exact, while496540,435740,435360 and4A1CE0
remain pending. The root is slot28; later slots include real render and
initialization providers omitted by the root's11-slot staging view.

Both actual vptr writes occur inside the519-byte493340 pool acquire:
instructions4933FC and493509, literal fields4933FF and49350B. The source uses
real allocation/placement reconstruction in `RosterObjectPools.cpp`. Its
constructor-facing hierarchy is deliberately narrow; the separate destructor
TU models the RTTI-proven CharacterObjectEx layer. These views do not establish
a source-generated complete17-slot owner merely because the individual pool
and destructor bodies match.

Next recover that real constructor/destructor/vtable owner context privately,
with genuine existing providers, and inspect the unexported virtual root.
The prior forced-export CIL prefix remains a measured failing alternative.
This is a new ownership lead rather than proof that vtable visibility will
solve the root. Keep the public constructor/destructor/root views and their
accepted units until the actual affected bodies and hierarchy compare.

## Reproduction and retained evidence

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-reimu-object-action-state --compare --json
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-907-bounce.py \
  build/match-units/GptWeb_ReimuObjectActionState.obj \
  --output build/reimu-object-virtual-surface-20261022/bounce.json
taskset -c 0 nice -n 10 python3 scripts/ci.py
git diff --check
```

The focused mixed unit still reports root45700/nonexact49655F/+31 and
counter66/66. Source SHA256 remains
`3b9e4896c3645bb1228db3b432a832154870c5639a80df6c02cb67ce2dba12cc`;
complete canonical source remains
`d0ff3d3259c823cc56e322c5e0ec238456d8b490c78b4a5336a249b45a405a58`.
Full private recipes `probe.py`, `negative_controls.py` and `vtable_context.py`
are under `.analysis/reimu-object-virtual-surface-20261022/`; receipts below
the corresponding `build/` directory include `final-formal.json`,
`virtual-surface.json`, `negative-controls.json`, `bounce.json` and
`vtable-context.json`, with before/after input hashes in the call packet.
The guarded source graph uses the existing public proof directly.

Only the root's evidence ledger and handoff change. Exact totals stay1376
functions/233560 bytes; no whole-root, new exact or aggregate cold claim is made.
