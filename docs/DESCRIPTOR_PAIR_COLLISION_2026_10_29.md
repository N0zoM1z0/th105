# Descriptor and group-B collision predicates, JP1.06a

46BA10 and46BCA0 now have complete selected source. Neither is exact and no
new exact-byte credit is added. The preexisting independent origin rule pins
both full native hashes, their connecting call and nine exact-helper calls.

## Shape-pair predicate46BA10

Native252-byte SHA256:
3be2cc0099c532a34618e3294822af7e05ae13518319cfa40a2a0570b49e247f.
Selected252-byte SHA256:
6aa4877c05811598f24e932aed320dc9f14d758195aa949f86fe00615e1507f1.
First mismatch+9 is broad-phase load/save scheduling.

All bytes form the complete two-return RET16 body. Four coarse separation
values are ANDed; bit31 gates five short-circuited calls to the exact142-byte
point predicate46B8B0. They test the second shape's two box endpoints, its two
descriptor-offset points, and the first shape's initial point against the
second descriptor. A hit calls the exact110-byte pair-extent accumulator46B5E0
and returns1; otherwise it returns0. The retained source accurately expresses
these paths. Replacing the signed comparison with the observed bit31 test
restores the target AND/TEST/JNS path and full252-byte size, not exactness.

The same-TU visibility matters: the isolated function emits232 bytes, while
its real HitGeometry context emits250 before and252 after the bit31 correction.
No fake inline/noinline rule is added. Four accepted same-TU helpers remain
exact at142/248/67/110 bytes in the final formal build.

## Group-B pair traversal46BCA0

Native398-byte SHA256:
16e4c866f3f10ab7056cc41a4e7d29389a94e62799d33384c1d00b406e146e4b.
Selected398-byte SHA256:
374065bab8dd3f6e5c4e3e5558ab51c058137dabd780fa4edb758f45d02b97e6.
There are44 differing byte positions, starting+20. The remaining differences
are the placement of the saved second receiver and commutative broad-phase
operand scheduling, including the corresponding restore order.

The complete RET8 body uses signed-byte counts at+1B0 and signed-byte nested
indices. The actual group-B block contains five16-byte boxes at+1B4 before
group A begins+204, with five descriptor pointers at+318 before primary+32C.
The new pointer-only typed view preserves these offsets with static assertions;
it is not allocated or claimed as a complete CollisionObject class.

For each pair, two descriptors select46BA10; one descriptor selects46B7B0
with the shaped box first. Two plain boxes AND four separation values, check
bit31 and call46B3B0 on a hit. Every pair contributes through bitwise OR;
there is no early-success exit or added count clamp.

The old unselected traversal cached the first descriptor across helper calls
and kept common box pointers alive across branches. Native reloads the first
descriptor at each call and computes the boxes within their actual branch.
Restoring these lifetimes changes321 to354/360/379 bytes; typed arrays then
restore398 bytes and most of the full instruction stream. Replacing plain-box
pointer uses by repeated raw address arithmetic grows405 and is not selected.
The outer for spelling and a single-expression AND control are byte-neutral.
No register forcing, fabricated use, padding or native numerical test matrix
is introduced. Equal length is not acceptance.

## Commands and scope

scripts/repo-python scripts/build.py --unit cross-v106a-hit-geometry --compare --json
scripts/repo-python scripts/build.py --unit exact-first-group-b-pair-collision --compare --json

Receipts:build/frontier-descriptor-pairs-20261029/formal-shapes.json and
formal-groups.json. Selected source is HitGeometry.cpp plus the new isolated
GroupBPairCollision.cpp. GeometryGroups.cpp remains an unselected older
traversal hypothesis for this address; no shared header or existing caller
changes. The authored-origin rule is retained, with the connecting caller now
recorded as source-present. Original source/class/TU spelling remains unknown.
