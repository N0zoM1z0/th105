# Player-slot profile load refinement

The original `0x00431AC0` function loads a profile string and fixed blocks, then
reads 20 card decks. The source now accesses the actual 20 deque members by
index in the natural loop, instead of carrying an incremented deque pointer.
The target's complete 728-byte body is SHA-256
`eb6b0f3cd77778190614684696f4b3b12f608e146dc2b3f88ce625f65cf43a61`.

A pinned VC8 /GS build emits 728 bytes, with resolved target comparison hash
`d9803d674411bd515e852adb1cb89775be7d8fec8833f47a474c42fc8fc16439`.
The complete resolved comparison has two unequal bytes, at +540 and +543:
the two inputs to one checked-deque bound addition are loaded in the reverse
order. The previous 723-byte pointer-loop candidate omitted a checked end
validation. Both field reads and the iterator check are retained naturally,
without synthetic guards or forced registers. This is nonexact and adds no
exact bytes. The reader-vtable pointer and EH-handler address are relocation
bindings only; full vtable/EH equivalence and live file behavior are not proven.

Reproduce with `scripts/repo-python scripts/build.py --unit
exact-first-player-slot-profile-load --compare --json`.
