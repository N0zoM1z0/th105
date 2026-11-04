# Connect menu rendering

The current-target `CMenuConnect` RTTI vtable owns the 752-byte render
function at `0x004418D0`; its four-entry switch table at `0x00441BC0`
dispatches states 1, 2 and shared 3/4. The source reconstructs the menu list,
selected cursor, design and footer, address/port digits, caret, list tile
and eight guide overlays using the target-backed layout and existing UI
interfaces. The layout view is not a claim about the original nominal source
spelling. The footer remains an out-of-line target-bound member interface.

Fresh pinned VC8 emits 768 bytes including the 16-byte switch table, equal
to the full native callable-plus-table length. Strict callable comparison
remains nonexact, first mismatch +116 in a branch displacement; the later
address-digit caret uses a different register allocation and comparison order.
Equal lengths are not a match, and no authored exact bytes are added.
The floating-point caret expression preserves the target's `x + 14` grouping.
The raw boundary tool cannot follow the indirect switch by itself; the four
native destinations are separately pinned in the origin rule. Full rendering
and exception behavior have not been exercised in the game.
