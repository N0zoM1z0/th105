# Select portrait binding and object transform

## Accepted portrait binding41FB80

Complete258-byte canonical exact body:
e0b2e99dbf95b83e6413946a9acb8baf8de9519d0896bfda5e08015dccdc41ec.
Receipt: build/frontier-41fb80-20261028/scalar-handle-local.json.
All decoded instructions and the complete RET8 are reachable.

The method releases the selected portrait token, clears that token and its
effect-bank pointer, and stops for random character15. Other characters form
the canonical cha_%s.bmp path in a real260-byte local buffer, load the texture
through the verified four-byte class return, install the texture into the
selected0x94 polymorphic sprite, flip horizontal scale for side1, and publish
the matching character's effect-bank pair. The existing CSelect shared layout
fixes token48C, sprite494, effects7FC stride128 and selected pointers1954.

A class-valued local initially emitted260 bytes and retained the token in a
stack home. Converting the returned handle to the actual unsigned scalar
consumed by the sprite naturally emits the native returned-pointer load and
closes258/258, without changing the resource-loader ABI. Width/height and
buffer homes then agree naturally. No padding, artificial locals or manual
vtable dispatch was introduced. /GS remains enabled.

Only the new unit was built. Shared headers and existing caller contracts are
unchanged. The format string at6C0818 is independently pinned. No origin rule
excludes this game UI root. New authored exact credit:258 bytes.

## Nonexact object transform41FAD0

The neighboring154-byte transform is reconstructed using the existing
AnimationSpriteFrameView and CEffectSprite fields. It rounds signed-short
frame pivots to float, resets the sprite, translates by negative facing-scaled
X/negative Y pivots, then translates to the object position.

Natural output is154/native154, first+25: the sprite receiver LEA is scheduled
before rather than after the first x87 integer load. It remains unselected
and earns no exact credit. No source-coercion search was performed.
Receipt: build/frontier-41fb80-20261028/object-transform.json.
Both raw CFGs and transform pointer cells are recorded in boundary.json.
