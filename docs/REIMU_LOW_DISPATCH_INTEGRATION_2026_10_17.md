# Reimu: integrated entry and low dispatch source

## Scope and target observations

Only original Japanese1.06a is used, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The authored parent is `Reimu_dispatch_action_state_vslot28 @478FA0`,81550
bytes ending48CE2E, SHA256
`dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6`.
It remains unclassified/declaration-only, with no new implemented/exact credit.

`ReimuActionStateLowDispatch.cpp` now compiles entry handling and all44
concrete low-table bodies plus direct300 into **one method**. It directly
includes the same statement/case fragments used by the five smaller staging
adapters; it does not call those invented staging boundaries. Each action
body has one source of truth. Existing typed prefix layout and external
helper ABI remain unchanged.

The new method is a partial-source interface: bool=true completes this checked
entry/low path, while false means the unreconstructed mid/high source must
continue. It is not the original void root or a game-ready replacement. Once
the remaining source is recovered, the original complete void-root contract
and whole-function comparison are still required.

Fresh target instructions establish the order:

-Entry stores/gates/counter logic run first, including callback-capable effect
  paths and the action669 transition. Re-read the action afterward.
-4791D4 sign-extends WORD+13C;4791DB compares the resulting DWORD with300.
  Signed JG at4791E0 enters the mid selector47CC5F. JE4791E6 enters direct300
  at47CBBD, independently of the low table.
-For the remaining values, unsigned JA4791F1 after comparison with226 enters
  the default48CE1F. This includes negative actions and227..299. The low table
  dispatch is4791FE; its explicit bodies share the case headers below.
-Default48CE1F reloads ECX=this, calls the real common method4740C0 at48CE21,
  then restores the root frame and returns. No actor operation follows that
  call. The external member view is void/thiscall/no stack arguments, matching
  the reviewed common-root ABI.

The shared source fragments are `ReimuActionStatePreludeBody.hpp`,
`ReimuActionStateLowCases.hpp`, `ReimuActionStateRecoveryBody.hpp`,
`ReimuActionStateMovementAttackCases.hpp` and `ReimuActionStateLateLowCases.hpp`.
They intentionally contain method-context statements/cases rather than
standalone definitions. Prefix/low source order and captured action values
are preserved. The recovery block's original range guard stays in its small
adapter; the integrated switch supplies the same71..78 precondition.

## Focused reproduction and execution evidence

```bash
scripts/compile-unit.sh src/characters/ReimuActionStateLowDispatch.cpp build/reimu-low-dispatch/ReimuActionStateLowDispatch.obj
python3 scripts/audit-reimu-low-dispatch.py build/reimu-low-dispatch/ReimuActionStateLowDispatch.obj
```

Pinned VC8 SP1 `/O2 /GS- /GR /EHsc /MT`, default FP, with no injected compiler
environment produces11271 staging text bytes. This is a partial method's
code size, not a comparison against or replacement for the81550-byte root.
CRLF source SHA256 is
`0c6537cd5a1940b7d8c108927feb8f9705974b93d9109e35cb61158bbd95b03d`,
header SHA256
`a4b9aaa5a8a90e8ddeb6b64ae6f3b7c9ef39d70345bac902bc359af75f7778b1`,
and object SHA256
`8235f93e49ffb9ac1e02462337b857d7142125df2029e3d8e057ac0fdf75f698`.
The manual compiler/source/header/object receipt is
`build/reimu-low-dispatch/build-receipt.json`; the native oracle separately
attests its object input and does not itself attest compilation.

**0/3122 differences**, input SHA256
`a03943b61eda8569c5444cb8ac56c85fb08c674711934a9333e1692d5c5df613`:

|Cohort|Cases|
|---|---:|
|All45 concrete action bodies with entry/low composition|540|
|Required default transfers, including negative/gap actions|1036|
|Real returning common-function contexts|28|
|Entry timers/WORD wrap/health words/latches/gates/state|1440|
|Required original object998 requests|50|
|Required upper handoffs versus early entry gates|28|

1765 cases reach genuine native RET.1036 compare at actual common4740C0 entry,
144 at actual set-action669 entry,50 at actual object998 request and48 at
actual effect request. Another79 compare the pending state at the original
mid-selector entry against the source interface's genuine false RET. This
last category is a source-phase handoff, not execution of the missing upper
bodies or a claim that the original function returned there.

The28 common-return cases execute unchanged original4740C0 through RET:
actions-32768,-1,11,42,149,227,299, each with both flag states and masked
PC53/PC64. The other default contexts stop before entering that real callee;
they do not receive a substituted result. The source calls the real member
and completes afterward, and its default calling/return ABI is exercised by
the returning subset. The set669/object/effect categories likewise stop at
actual call entry without supplying a result or claiming the continuation.

The comparison samples2460 original-root and1745 staging instruction addresses.
It compares all4096 actor bytes, ordered external helper/receiver/argument
traces, physical x87 conversion inputs, MT state/index and control word. All
actual return paths, including the candidate's pending false return, require
stack delta4 and preserved EBX/ESI/EDI/EBP. x87 TOP must be zero. Original
pending paths retain the original live root frame, so they are not presented
as an identical machine-stack continuation of the staged method.

Source input words+7A0/+7A2 begin at-19/-23, rather than being preset to entry
outputs; both programs must publish the real0/85 stores. Timer/health gates
can clear a timer yet continue its decrement/counter processing; signed count
wrap and action669 still precede the later gates. Table/action/mid-selection
guards require the advertised endpoints rather than relying on the candidate
to declare itself handled. The explicit-entry low-table membership is checked
through target routing and the protected canonical root bytes.

Two compiled wrong-source controls are rejected: replacing `>300` with
`>=300` misroutes direct300 and fails1/59 smoke; replacing the default common
call with ordinary frame advancement fails28/28 common-return cases. These
are genuine compiled wrong behaviors, not fabricated helper results.

## Preservation and resource context

All five old adapters are freshly rebuilt after extraction. Their text,
non-debug code/data sections and every relocation's offset/type/symbol/value/
section identity are byte-identical to the previous checkpoint. Their text
sizes remain530,771,1562,4017,4409. Debug/file/timestamp metadata is excluded
only from this preservation check; canonical acceptance rules are unchanged.
The receipt is `build/reimu-low-dispatch/preserved-stages.json`.

Current focused old-stage replays pass0/9 entry,0/88 low,0/64 recovery,
0/99 movement/attack and0/150 late-low. Their full historical matrices are
not redundantly repeated. No accepted unit uses this private staging header,
and no accepted unit/compiler-profile/relocation-ledger change occurs.

The animation fixture expands to64 keys with computed nonoverlapping block/
frame ranges, keeping the old21/24-key layouts byte-identical across24 frame/
profile combinations. Fifteen structural tests include the64-key maximum and
six-frame/seven-sequence layout. Each new case supplies the45 low bodies,
auxiliary keys and its current input action, so invalid/gap actions do not
borrow another key's active frame accidentally.

As in the preceding phase, the table is produced by the original orientation
initializer and real cosine instructions; MT uses original seeding/draws.
Flat surface, zero texture/event handles, inactive secondary-event cycle,
finite phase angles and the supplied read-only animation graph still bound
the proof. Other math modes, floating exceptions and returning world/manager
contexts remain unproved. This is sampled behavior, not exhaustive gameplay
or canonical byte equality.

One direct Ghidra clone attests file SHA256, entry68B9D2, base400000, Windows
x86 language, mapped.text and full-root bytes. It reads back the root method
view, entry stores, selector edges, direct300, mid handoff, common call and
final RET. `REIMU_LOW_DISPATCH_READBACK_PASSED` is retained in the build log.
IDA preflight still rejects the unrelated loaded image and supplies no
semantics. All nine primary DB files remain hash-identical; the clone is
removed. Wrong controls and superseded objects are discarded after receipts.

Next recover mid/high bodies into this source path and resolve the remaining
returning world contexts. Keep original void ABI, complete CFG/relocations,
LTCG/TU provenance and the entire81550-byte comparison as the acceptance
requirements. No exact authored bytes are added by this integration.
