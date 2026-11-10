# Actual GuideOverlay owner and independent sprite header

GuideOverlay now owns the real global CSprite at+8. Its load/render/update and
ordinary constructor/destructor all use that same class. The raw UiSprite94
vtable dispatch in load and the GuideSprite94 reinterpret casts in update are
removed. The separate GuideLifetimeView/GuideLifetimeSprite94 source file is
removed; the existing lifetime unit selects actual GuideOverlay.cpp definitions.
Other UiPrimitives users are not changed by this scope.

The load call uses ordinary C++ assignment in the argument:

sprite_08.set_texture(texture_04 = loaded, 0, 0, width, height);

This preserves the native receiver/value evaluation without saving or manually
calling a vtable pointer. Its complete179 bytes remain exact, as do render124,
update112 and constructor20. Destructor90/native92 keeps the same hash
40b7c204051af94d5a4d9806495760ac09e74de8e6469a5b0a37abcc74b35cbe;
its old handle-load CSE residual remains nonexact and is not forced.

## Header boundary

The actual sprite declarations are moved unchanged into engine/Sprite.hpp.
EffectSprite.hpp remains a compatibility wrapper: Collision.hpp followed by
the minimal sprite header. Existing battle consumers retain their declarations
and include ordering. GuideOverlay.hpp includes the minimal header directly.
A normalized source comparison confirms no sprite definition changed in the move.

The initial direct EffectSprite include exposed two pre-existing, incompatible
MatchSetup declarations: battle/GameMode.hpp and the legacy12-byte scenario
view in SelectScenario.hpp. They are not merged or renamed into claimed semantic
identity. Sprite definitions need neither MatchSetup nor Collision; isolating
that dependency permits the real Guide member without changing those views.
No class layout, native API, ABI, compiler flag or allocation behavior changes.

## Evidence and verification

The actual Guide object emits all273 unique bytes of CSprite/CSpriteBase/IColor
RTTI and all nine virtual roles of the36-byte CSprite table. The entire20-byte
Guide constructor is canonical, including member initialization at8/C. No
complete Guide destructor equality or full-program linkage claim follows.

Actual include closure:200 units. All388 accepted roots across163 units freshly
compile and compare exact. The remaining140 configured roots across77 units
retain their fresh before/after hashes or the existing failure category.
Scenario458440 still lacks its string-constructor call binding, reproduced with
HEAD sources. No matched prefix or nonexact body gains authored credit.

Six lifetime-origin families pass with reviewed pins extended to the moved
header. Select/default and implicit-design evidence also pins GuideOverlay.hpp.
Network constructor411/full EH197/metadata116 and destructor259/full EH169/
metadata100 remain exact. Select full EH461/metadata188 remains exact while its
main4247/13-byte mismatch is unchanged. Actual Select owner/design audits pass;
render4 and character12 finite cases/negative controls retain their nonexact
candidate hashes. Source guards and canonical whole-byte requirements are not
weakened to accommodate the header move.

Private bounded controls live in the corresponding .analysis scope. Reproduce Guide
bodies through cross-v106a-guide-overlay, exact-first-guide-overlay-update and
exact-first-guide-overlay-lifetime. Default CI and both diff checks gate the local
checkpoint. Counts remain1427 exact/443604 bytes,1636 source-present, 812 units;
this is source ownership consolidation, not new exact credit.
