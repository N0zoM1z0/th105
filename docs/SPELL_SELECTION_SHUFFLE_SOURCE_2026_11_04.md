# Spell selection shuffle source

The 196-byte original `SpellDataOwner::shuffle_selection` at `432420` is now
selected from `src/battle/SpellDataShuffle.cpp`. Its original body and the call
at `432538` from the exact sequence-mode setter were independently pinned by
`spell-shuffle-authored-106a`.

The source takes the observed selection count once, then repeats 100 times:
choose an index with the existing random selector, read that checked deque
iterator, erase the element and push its value to the front. It uses an actual
pinned-VC8 deque iterator and a declaration-only layout view for the native
out-of-line deque erase and push-front methods. Those two helper entries are
already classified compiler-generated; this selection does not add helper
credit. Compile-time size checks cover both deque views. The random function
uses its existing `int` source ABI, with the original unsigned index conversion.

The full 196-byte canonical candidate differs at exactly seven byte positions,
all within `4324A4..4324AA`: target and compiler schedule the same stack
reservation and saved-value store in opposite order. The first mismatch is
+132; canonical candidate SHA-256 is
`3f6db2d0d80087a91b680bd25ceae2d8a77be6731bb28324252410aacc7f5465`.
It is not exact and gains no matching-byte credit. A function-scope deque view
produces an earlier mismatch; the selected branch-local view matches the native
zero-count lifetime. Switching the random declaration to the already-proved
signed API preserves the complete candidate bytes. Receipts are under
`build/frontier-spell-shuffle-source-20261104/`.

Reproduce with `scripts/repo-python scripts/build.py --unit
exact-first-spell-selection-shuffle --compare --json`; mismatch is expected.
No live game execution, original source spelling or full compiler context is
claimed.
