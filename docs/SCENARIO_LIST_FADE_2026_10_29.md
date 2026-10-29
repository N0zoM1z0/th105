# Scenario render-list fading, JP1.06a

455850 now has complete selected source for its431-byte native behavior.
Source418/native431 remains nonexact, first difference+38 in the branch extent.
Native SHA256:30d7262a2d4f9024b9f6854de92d0c5aef9f5b440182cb91ae57a9462bb67026.
Source SHA256:669b507da07a8a1decb83dcb6723cd4226d22ce8d0a142578da173de385b6b94.

The interpreter458440 calls it at4584A6,4584B4 and4585AD for the Scenario's
three9C-entry lists. ECX is unused and the actual list is the RET4 stack argument.
The pointer-only value view has a resource handle000, genuine polymorphic
94-byte sprite004, unsigned alpha098 and signed delta099. Its declared owned
destructor binds the independently accepted434C60 resource cleanup; no manual
vptr or list-node writes are introduced.

Positive delta saturates alpha at255. Nonpositive delta erases only when
alpha is strictly less than -delta; otherwise it adds the signed delta.
Thus an exact fade-to-zero boundary survives for this iteration, and zero
step with zero alpha remains in the list. Erasure returns the next checked
iterator and skips coloring/incrementing that removed element. Every surviving
entry receives alpha in the high color byte, with white RGB for a nonzero
resource handle or black RGB for a zero handle, then the iterator advances.

All431 native bytes through4559FC RET4 are reconciled. Ordinary source retains
all observed guards and both color paths, but the compiler lays out the merged
color path differently and emits418 bytes. An explicit else after the erase
branch is byte-neutral; reversed negative comparison and negative-first branch
controls give391/408 bytes and are not selected. No added checks, barriers,
register variables or padding are used to force the layout.

The actual emitted std::list erase helper independently compares102/102 to
4555B0, SHA425f246ce20c3aae4ae3c0fece4c72037417096745a7b4f012c5bcf28653b60f,
with ordinary destructor/operator-delete relocation. It was already excluded
as compiler/library ownership and receives no authored credit. The root itself
is now source-present and authored, but contributes zero exact bytes.

Reproduce with:
scripts/repo-python scripts/build.py --unit exact-first-scenario-list-fade --compare --json

Source:src/battle/ScenarioListFadeUpdate.cpp.
Receipt:build/frontier-scenario-list-update-20261029/formal.json.
No shared header, existing relocation or accepted consumer changes. Default CI
and progress regeneration validate this incremental selection, not a cold build.
