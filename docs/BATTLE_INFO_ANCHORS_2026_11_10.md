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
