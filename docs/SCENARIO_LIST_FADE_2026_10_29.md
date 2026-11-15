# Scenario render-list fading

`CScenarioData::update_list` (0x455850, 431 bytes) is exact. The interpreter
0x458440 calls it at 0x4584A6, 0x4584B4 and 0x4585AD for the scenario's three
0x9C-entry lists. ECX is unused; the list is the RET4 stack argument.

Each entry has a resource handle at +0x000, a polymorphic 0x94-byte sprite at
+0x004, an unsigned alpha at +0x098 and a signed delta at +0x099.
- A positive delta raises alpha and saturates it at 255.
- Otherwise the entry is erased when alpha is strictly less than -delta;
  if not, the signed delta is added. Erasing returns the next checked
  iterator and skips coloring.
- Every surviving entry publishes alpha in the high colour byte (white RGB
  for a nonzero handle, black for zero), then the iterator advances.

## What made it exact

The target lays the delta > 0 branch out first, followed by the colour
publication. The other branch sits after that tail and jumps back into it.
That is VC8 cross-jumping two identical copies, so the source ends each
surviving branch with its own copy of the colour publication and `++it`, and
puts the erase in an `else if`. A single shared tail after the `if/else` puts
the second branch inline (418 bytes). Inverted comparisons and negative-first
branches also fail.

The emitted `std::list` erase helper matches 0x4555B0 (102 bytes); it is
compiler/library code and gets no authored credit.
