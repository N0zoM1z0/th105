# Actual sprites in Character cleanup and fighter resources

The standalone validator blocker recorded below is subsequently resolved by
CORE_CONTRACTS_REPAIR_2026_11_02.md; the native evidence here is unchanged.

Following the constructor's actual CSprite recovery, CharacterDestructor.cpp
uses the same global CSprite in its two direct sprites, handle/sprite resource
and sequence record. FighterCutinLifetime.cpp also uses CSprite instead of a
CSpriteBase-derived local five-float substitute. FighterResources.hpp replaces
its six-slot/opaque94-byte placeholder with actual CSprite. Resource setup
calls the real slot5 set_texture and uses named scale_x_88/scale_y_8c fields.
The actual header supplies all nine slots, typed vertices, geometry and handle.

Native connection comes from the exact Character constructor's publications
at33C/3D4/570, exact resource initialization463070/333 and cutin loader4651E0/199.
The face resource starts338 and its sprite33C; the cutin starts3D0 and its
sprite3D4. The cutin199-byte body keeps its original arguments and virtual-call
position. Changing the extent argument declarations to the actual signed
CSprite method does not change its compiled bytes. No new allocations,
resource-release logic, casts, volatile fields or EH manipulation were added.

All three affected manifest units were replayed. Existing exact roots45F680/132,
463070/333,4651E0/199 and4619C0/101 remain whole-byte exact. Spell-owner auxiliary
code57 and metadata60 also remain exact. Character cleanup462CE0 stays905 bytes
with its same one-byte SIB mismatch (source SHA352716b40062c2f2437d4d50ffb824ac3fdf14cc39725d1531342cf82b302e1f).
Fighter cleanup465420 stays95/native96, SHAec20e6887c5973fb782263084ec0588ec8ddc30152083108848a076b03c2e8e6.
Both closed code-shaping lanes remain closed; neither gains exact credit.
The emitted sequence-deque135 and Pat-deque125 ownership gates pass unchanged.

CoreContracts.hpp now checks actual CSprite size. The standalone compile-only
CoreContracts.cpp validator still fails on its pre-existing undefined
SequenceRecord4 assertion. A fresh HEAD-header control reproduces the same
three diagnostics; it is not claimed to pass and is not a native match unit.

The A0 cutin view is not a claim that every folded handle/sprite cleanup has
that original nominal owner or size. Native465420 touches the handle/sprite
prefix, which also occurs in a98-byte face resource; nominal/ICF identity is
not uniquely determined by that cleanup. Its provisional ledger row is unchanged.

Evidence is in build/frontier-character-resource-sprites-20261102/, including
fresh before/actual controls, formal unit receipts, both generated-origin gates,
spell-eh.json and core-baseline.log. No shared EffectSprite header, origin rule,
source/exact count or compiler profile changed in this step. Default CI and
both diff checks gate the local checkpoint.
