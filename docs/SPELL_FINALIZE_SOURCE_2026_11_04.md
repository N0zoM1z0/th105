# Spell selection finalization

The original `432200` body clears the 32-byte selected-value table, walks the
loaded short IDs and looks up each record through `432D20`. For a non-null
record with selector byte 1 it stores the ID's low byte at the record's
unsigned short index. The complete 260-byte native body has one three-byte
internal alignment instruction at `43223D`; the exact spell loader `432360`
calls it at `43239C`. The body hash and exact owner edge are pinned by the
focused `spell-finalize-selection-authored-106a` origin rule.

`SpellDataFinalize.cpp` replaces the previous unselected hand-expanded checked
iterator hypothesis with ordinary pinned-VC8 `std::deque<short>::iterator`
operations against the existing 20-byte deque layout. The source does not add
bounds checks or guards absent from the native root. Both mutable and const
iterator controls emit a 226-byte candidate against the 260-byte native body;
the first difference is the frame reservation at entry. Native VC8 retains a
self-container check and additional iterator/stack lifetime that this standalone
build optimizes away. Neither candidate is exact, and no matching-byte or
exception-path equivalence is claimed. Candidate receipts are under
`build/frontier-spell-finalize-natural-20261104/`.

Reproduce the whole-body comparison with `scripts/repo-python scripts/build.py
--unit exact-first-spell-finalize-natural --compare --json`; a mismatch is
expected. The native target and the targeted origin rule were checked. Exact
source spelling and original TU/LTCG context remain unknown.
