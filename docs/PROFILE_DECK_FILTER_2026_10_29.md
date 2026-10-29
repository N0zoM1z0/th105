# Deck-editor category selection, JP1.06a

449E90 is now canonical exact1375/1375. This credits the complete callable,
including its three-byte internal LEA alignment, not a matching prefix.
The independently replayed full1396-byte COFF extent is also identical:
1375 callable bytes, one NOP and the five-entry switch table at44A3F0.
The extra21 bytes receive no separate authored credit.

- Callable SHA256:9ece3485bd5240b9ec6f0be7dc67839bc3b121ddcae5940ec2e4937054194e2a.
- Complete owned SHA256:99c046095b6431f77ee83123d7dc49b1284200ba41a7e49fe7f52191ecca86ab.
- Raw CFG:404 reachable instructions,1372 reachable bytes, three strict
  alignment bytes at44A01D. Four RET4 exits, no omitted cold path.
- Exact deck-editor update44A410 calls this root at44A925. Native category
  stores, spell-record selectors, counts and UI behavior establish authored
  ownership independently of the successful comparison.

## Recovered behavior

Zero-count entries are erased before changing categories. The previous button
is disabled. Signed category0 shows common then character-local cards;1 shows
common cards;2 and3 select local records with selector1C equal to1 and2.
Category4 shows keys present in the current nonempty deck. For an empty deck,
it recursively selects3 when the old category was0, otherwise0, and returns.
Out-of-range categories do not clear the existing filtered deque. No new guard
or fallback is added.

The selected category field is stored and then used to enable its button.
The real MenuCursorState::bind_vertical implementation supplies input+3C,
the filtered count, zero selection/window and page size15. Availability is
queried using that newly reset cursor selection. A nonzero result displays its
selected record; otherwise the original eight UI controls are disabled in
native order.

The pointer-only view constructs no synthetic game objects. Spell and count
maps and the iterator deque use the pinned VC8 checked containers.4300B0 is
an out-of-line checked deque subscript, not deque.at: the bounded native body
has iterator guards but no range-exception helper. Its declaration-only
receiver therefore models operator[], with an8-byte iterator reference result.
No shared runtime header or existing consumer source changed.

## Comparisons

Initial source exposed an incorrect button-input assumption and inline at
exception edge. Native4300B0 and actual InputManager layout resolve these:
vertical is+3C, button0 is+40. Genuine MenuCursorBindings.cpp inclusion restores
the observed inline binding. Reading the stored category and passing the
cursor selection recover the remaining native dataflow naturally. No padding,
dummy liveness, volatile scratch, private register ABI or assembly was used.

Focused command:
scripts/repo-python scripts/build.py --unit exact-first-profile-deck-filter --compare --json

Formal receipt, full-relocation replay and CFG facts are retained under
build/frontier-profile-deck-filter-20261029/. Public source is
src/ui/ProfileDeckFilter.cpp. The full replay also relocates all five table
entries, beyond the callable ledger bound. Existing exact receipts remain
unchanged; default CI and diff checks validate the completed tracking update.
