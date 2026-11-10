# Identify the actual sprite-array cleanup, not an identical byte body

The complete seven-byte cleanup at421D30 is now classified as compiler-generated
from the real CSelect array callback. It was already fully compared as support
for the16-byte implicit CSpriteEx constructor. This adds only7 compiler bytes,
not an authored match or a second count of the constructor/RTTI/caller.

## Byte identity is insufficient

The full candidate inventory contains two seven-byte functions that match this
source destructor:40AD50 and421D30. Neither masks nor partial prefixes are used.
The gate records both matches and does not claim byte uniqueness.

The original29-byte array-construction site423348 instead identifies the
physical cleanup unambiguously. Its source COFF relocation names the actual
CSpriteEx destructor, paired with the unique16-byte CSpriteEx constructor at
41F6E0. Target count2, strideE8 and member+624 agree with the unchanged CSelect
source. That exact target site passes421D30, not40AD50. Complete CSpriteEx,
CSpriteBase and IColor hierarchy/RTTI evidence verifies the class ownership.
The source destructor's only relocation restores the actual IColor vtable.
All code, the complete RET boundary and the constructor/destructor pairing
are checked afresh. The old constructor proof remains independently required.

Only421D30 is selected. This does not establish exclusive original symbol
spelling or whether additional compiler aliases existed. The other identical
physical body gets no credit from this proof. CSelect's complete parent remains
nonexact, with its previously documented scheduling residual.

The public unit adds the real emitted destructor as a separate formal
comparison. No reconstruction source or compiler flags change. The preceding
IColor-tag correction and99-unit/242-function affected replay remain valid;
there is no reason to rerun unrelated native units for this selector addition.

Seven new tests reject substituting the identical40AD50 body, shortened/masked
code, wrong emitted destructor, missing paired constructor and a different
source owner. Together with the constructor's eight tests, all15 focused tests
pass. All334 unique actual byte corruption controls fail: both seven-byte
inventory bodies, constructor16, caller29 and the275 unique RTTI bytes.

The separate IEffectManager normal destructor is not emitted in this actual
CSelect object. It is not materialized with an artificial caller/export or
accepted from matching bytes. This is a closed missing-source-owner lead until
an actual source consumer provides that emitted body.

The existing constructor gate retains its own proof.
