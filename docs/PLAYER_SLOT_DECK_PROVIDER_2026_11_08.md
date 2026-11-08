# Shared player-slot deck provider

Nine calls across Scenario setup, normal match setup, profile deck update,
profile deck construction and network snapshot import now use the implemented
`PlayerSlotDeckView::copy_deck`, rather than five independent declaration-only
aliases for `0x431E50`. The shared header exposes the already-proved twenty
checked `deque<unsigned short>` members at +0x1AC in the 0x33C record. It is a
nonowning layout view; existing PlayerSlotRecord ownership and lifetime stay
with their current implementations.

Scenario setup now also names its destination as the actual checked deque
instead of opaque 20-byte storage. The optional output pointer, integer index,
return value and nine native call operands are unchanged. Existing signed
network/profile deque adapters remain explicit at their separate boundaries.

## Focused verification

The complete include closure contains seven units. All six accepted roots
remain exact, including the 47-byte provider, 119-byte Scenario setup, 521-byte
normal setup, 1,339-byte deck update and two number adapters. The three existing
nonexact roots retain their previous bodies: profile constructor, title-mode
preparation and client snapshot import.

The normal setup comparison additionally covers its complete 556-byte owned
section: callable521, three alignment bytes and the 32-byte switch table all
match the original. The nine source call relocations resolve to `0x431E50` at
the same native sites, including the two nonexact callers.

A fresh compile of the archived constructor source and final source produces
identical bytes and relocation roles in all 716 non-debug COFF sections,
including its remote EH code, metadata and RTTI. The title-mode control likewise
preserves all ten prior sections; including the real deque adds only the
unreferenced four-byte VC8 `_EEM_DS = 8` constant. Object-file CodeView paths
and section order are not runtime bytes. Snapshot handler, metadata and its
known cleanup mismatch were also rechecked. The constructor-dependent
compiler-origin proof for the 55-byte node helper at `0x43BBC0` passes its
fresh compile and complete-inventory comparison.

Evidence is in `.analysis/frontier-player-slot-deck-provider-20261108/` and
`build/frontier-player-slot-deck-provider-20261108/`. The final seven objects
have verified source/compiler provenance. This removes disconnected call
interfaces without adding authored exact credit.
