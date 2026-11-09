# InfoManager combo resource contracts

InfoManager initialization and teardown now call the shared combo resource
implementation used by loading and rendering. The independent six-slot
InfoComboResourceSubobject facade is removed. Normal initialization embeds the
proven 0x6C view at +100, with counter +488 and records +498 unchanged.

The combo release and outer base loader now have void contracts. Release calls
CDesignBase::virtual_cleanup through its actual +14 slot. Loading calls the
existing void combo provider rather than an undefined int-returning alias.
The original outer class declaration and upper/lower design facades remain
separate work.

## Target evidence

Raw Japanese 1.06a PE SHA-256:
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.

- Release `46A610` is exactly seven bytes: load the receiver's vptr, load +14,
  and jump to that method. Original construction at `46F634` gives this +100
  subobject CDesignBase's table `6C08AC`; its +14 entry is the existing void
  cleanup `40BB40`. That actual provider replays all 310 bytes.
- Release's two direct callers are `46E9BB` and `46F8AE`. Both replace EAX
  immediately after the call, at `46E9C0` and `46F8B3`.
- Combo loading ends with the actual output-parameter bind at `46AA53`, then
  restores saved registers and returns. Normal initialization calls it at
  `46EBB0` and overwrites EAX at `46EBB5`. The other incoming edge is the base
  loader's tail jump at `46E97C`.
- Story initialization is the base loader's only direct caller, at `471E56`;
  it overwrites EAX at `471E5B`. The only aligned nonexecutable pointer to this
  loader is the base table's +4 entry `6C3834`. Original RTTI identifies the
  base, normal and Story tables at `6C3830`, `6C3850` and `6C39D4`; their +4
  entries are `46E960`, `46EB90` and `471E50`, respectively. The latter two
  already implement void initialization. No observed consumer interprets an
  integer result from the corrected chain.

These are provider, receiver and consumer facts, not an inference that every
function ending in a tail call returns void. The raw E8/E9 census finds exactly
those five incoming edges; the static-pointer census retains the base slot.

## Focused validation

All fourteen units in the two changed headers' include closure were rebuilt.
Their 27 exact roots retain complete canonical equality, including the 7-byte
release, 33/60-byte base resource methods, 97-byte Story initialization and
119/171/30/228-byte normal lifetime/initialization group. Both full normal
lifetime EH sections and metadata match all 228 bytes.

All 516 existing non-debug COFF sections retain their bytes and relocation
roles, allowing only the three corrected method symbols. Three newly including
translation units each emit an unused four-byte deque block-size constant;
none references it. The two generated deque helper proofs and the emitted
normal scalar-deleting wrapper's RTTI/origin proof pass unchanged.

The Story update remains nonexact at 321/native323 bytes, and the full combo
loader remains unchanged at 427/native413. BattleInfoRecord update retains its
pre-existing unresolved local deque-iterator relocation; all of its COFF
sections are unchanged. No authored exact count changes.

Reproduction evidence is in
`.analysis/frontier-info-resource-contract-20261109/` and
`build/frontier-info-resource-contract-20261109/`: before/after unit reports,
complete-section checks, native reference census, provider replay and EH/origin
proofs. No input-migration source pins were updated.
