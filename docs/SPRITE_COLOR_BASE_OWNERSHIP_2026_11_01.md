# Shared sprite color-base ownership

## Correcting a real field-ownership error

IColor is the four-byte polymorphic interface. Texture value04 belongs to
CSpriteBase, not IColor. The already-proven CNumber lifetime and sequence
rotation116-byte implicit copy supplied independent evidence; native RTTI
confirms CSpriteEx -> CSpriteBase -> IColor. The native CSpriteEx copy450640
publishes CSpriteBase6C0654, copies texture04, then112 vertex bytes and two
float dimensions. It publishes CSpriteEx6C06E8 before copying its two xyz
quads and the final two floats. There is no initial IColor publication.

The older shared EffectSprite.hpp incorrectly assigned value04 and its zero
constructor to IColor. Its source emitted124 bytes with an extra IColor vptr
publication. Moving that genuine member/default initialization to CSpriteBase
produces the complete native118-byte implicit copy without writing a copy
constructor, vptr recipe, dummy member, register control or byte substitute.

Narrow direct-IColor views explicitly retain their real +4 field and zero
initialization. Their existing physical sprite/UI offsets do not move. Guide's
constructed sprite now derives from the actual CSpriteBase, preserving native
base-field initialization before final sprite publication. Initially flattening
that base produced a20-byte constructor scheduling regression; the genuine
intermediate base restores the accepted constructor rather than hiding it.

No new allocation size is inferred. Existing CSpriteBase80, CSpriteExE8,
CEffectSpriteE8 and all member offsets retain their typed extents. The older
IColor8 declaration is superseded. Historical comments naming4396A0 as merely
a CSpriteBase copy are also obsolete: that entire164-byte function is the CTile
copy, as its later dedicated reconstruction already establishes.

## Canonical result

Implicit CSpriteEx copy450640:118/118, SHA256
abec55c15f83a440aa3b3f65dd5220b72208abd7ab43b1871ab233fba31e8f0a.
Both actual RTTI-owned vtable relocations are resolved. The remaining110 bytes
are nonrelocation code, and the unchanged .70/24/no-tail origin gate proves
full-inventory uniqueness. Native vector assignment4663E0 calls this copy at
46641A. Actual background initialization4664A0 remains512/512, and the existing
186-byte vector assignment compiler anchor also freshly passes.

The copy is compiler-generated, not authored game code. Only one review entry
moves to excluded: excluded1952/review408. Authored exact1445/445336,
source1647, authored1667, mapped1815 and units769 stay unchanged.

## Affected verification

All121 source-dependency units were freshly rebuilt and compared serially on
CPU0/nice10. All277 unique selected authored exact functions are retained.
Pre-existing nonexact candidates remain unaccepted; no prefix credit is used.
Local compile mistakes were fixed and affected units rerun. The final per-unit
reports contain no missing accepted result, build error or exact regression.

All28 generated-origin rules whose source depends on EffectSprite.hpp freshly
replay without errors. The142 canonical scalar-wrapper bodies across51 owner
units were refreshed under final source/manifest inputs as well. This is an
explicitly bounded affected-header/provenance replay, not a cold all-exact run.

Original and private control sources remain in the same bounded analysis scope.

Reproduce the new copy and actual owner:

    scripts/repo-python scripts/build.py --unit exact-first-background-initialize --compare --json

No push. No change to exactness or origin thresholds.
