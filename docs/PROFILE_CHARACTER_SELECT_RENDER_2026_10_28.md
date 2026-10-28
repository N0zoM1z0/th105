# Profile character selection render448420

Canonical exact205/205, SHA
61c6e991fbd91a94417e52080fc3ccaff07aa9471d67634af1d5098f5650b92d.
Unit exact-first-profile-character-select-render; receipt
build/frontier-448420-20261028/direct-item-expressions.json.
RTTI table6C2150 / COL6D8578 / type6E6D8C identifies CProfileCharacterSelect;
slot0C points directly to448420. All56 decoded instructions are reachable,
ending with the normal GuideOverlay render tail43F4C0. No missing cold block.

The existing0x288 owner layout supports stand texture04/sprite08, player9C,
design13C, item pointers170, column1B4, row1C8, guide1DC and final row count284.
The stand renders at(-64,0) if loaded. Cursor selection distinguishes the final
row (item2*count-1) from the normal grid (item2*row+column). Cursor y is rounded
to float after adding double8.0, scale is256.0f. Design, player profile at(0,0)
and guide follow in native order. No new shared-layout or primitive changes.

Direct repeated item expressions matter: a branch-local cached item pointer
produces199 bytes and first differs at+51 by retaining count in ECX across the
comparison. A single shared item pointer produces182 and merges the two x87
paths. Keeping the direct source expressions in each branch recovers the
native reloads and full205 bytes naturally. No extra loads, volatile fields,
register barriers or fake liveness are introduced. Both controls remain private.
