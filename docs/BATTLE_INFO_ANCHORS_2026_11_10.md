# Battle-info rendering indexes its anchor array

`BattleInfoRecordF8::render_470710` now uses `group_88[index]` directly instead
of maintaining a second pointer and decrementing it past the beginning of the
array after drawing index zero. The signed index still counts down through
zero, with the same early return for an initially negative index. No range
guard or new assumption about the fighter's state count was added.

An ordinary reverse index loop naturally regenerates the complete native
353-byte body at `0x470710`, SHA-256
`3bff89c56273da6a16af4369ad2af36243723d023b18d1a7852ea04cc7f31958`.
The existing 94-byte checked deque accessor also replays exactly. Complete
before/after COFF section contents and symbolic relocations are identical,
so the branch-local scale lookup and subsequent sprite receiver have not
changed. The separate sequence-container storage view is outside this change.

Only `cross-v106a-battle-info-record-render` selects the modified source;
there are no shared-header, provider, relocation or ledger edits. The fresh
full unit comparisons, identical section dumps and passing focused CI log are
in `build/frontier-battle-info-anchors-20261110/`. This removes unnecessary
source-level out-of-array pointer arithmetic while preserving existing local
exactness; it adds no function, byte or Factory acceptance credit.

## Effect emission uses the initialized record owner

The group-effect provider at `0x46F9F0` now reads the existing
`BattleInfoRecordF8` state and its `UiDesignObject` anchors. Its duplicate
partial record and position layouts have been removed. The initialized
`group_60` pointers are published by `BattleInfoRecordF8::initialize_46fd20`
through the design binder, and their real `x`/`y` fields supply the emission
coordinates. The existing `InfoEffectManager` is the same concrete
`CEffectManager<InfoEffectObject>` type, so its virtual spawn contract is
unchanged. The signed mode byte is tested only for zero here.

Normal and Story forwarding wrappers now select a record through the existing
`battle_records_498()` accessor rather than repeating the 0xF8 stride and
0x498 offset. Their callable symbols and argument contracts stay unchanged.
The provider remains a declaration-only derived view; no new record is
constructed and no virtual or data member is added to the owner.

Three dependent units were rebuilt serially. All five caller roots retain
exactness: 46EF40 (214 bytes), 46F820 (35), 471EC0 (78), 471F10 (215), and
472060 (31). The provider stays 61 versus 85 native bytes, unchanged at its
first-byte mismatch. Its entire COFF contents and relocations are identical.
Both caller objects retain all previous contents/relocations and additionally
emit the existing 7-byte address accessor (`lea eax,[ecx+498]; ret`) with its
compiler debug record. The accessor is inlined in the exact roots; it adds no
accepted function or Factory credit.

Before/intermediate/final build reports and full section dumps are in
`build/frontier-info-effect-owner-20261110/`. The focused CI gate passes in
`ci-final.log`. Native stack-slot reuse in the nonexact provider remains open;
this owner correction does not manufacture the missing coordinate frame.
