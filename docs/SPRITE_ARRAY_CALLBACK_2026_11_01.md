# Identify the actual sprite-array cleanup, not an identical byte body

The complete seven-byte cleanup at 421D30 is now classified as compiler-generated
from the real CSelect array callback. It was already fully compared as support
for the 16-byte implicit CSpriteEx constructor. This adds only 7 compiler bytes,
not an authored match or a second count of the constructor/RTTI/caller.

## Byte identity is insufficient

The full candidate inventory contains two seven-byte functions that match this
source destructor:40AD50 and 421D30. Neither masks nor partial prefixes are used.
The gate records both matches and does not claim byte uniqueness.

The original 29-byte array-construction site 423348 instead identifies the
physical cleanup unambiguously. Its source COFF relocation names the actual
CSpriteEx destructor, paired with the unique 16-byte CSpriteEx constructor at
41F6E0. Target count 2, strideE8 and member+624 agree with the unchanged CSelect
source. That exact target site passes 421D30, not 40AD50. Complete CSpriteEx,
CSpriteBase and IColor hierarchy/RTTI evidence verifies the class ownership.
The source destructor's only relocation restores the actual IColor vtable.
All code, the complete RET boundary and the constructor/destructor pairing
are checked afresh. The old constructor proof remains independently required.

Only 421D30 is selected. This does not establish exclusive original symbol
spelling or whether additional compiler aliases existed. The other identical
physical body gets no credit from this proof. CSelect's complete parent remains
nonexact, with its previously documented scheduling residual.

The public unit adds the real emitted destructor as a separate formal
comparison. No reconstruction source or compiler flags change. The preceding
IColor-tag correction and 99-unit/242-function affected replay remain valid;
there is no reason to rerun unrelated native units for this selector addition.

Seven new tests reject substituting the identical 40AD50 body, shortened/masked
code, wrong emitted destructor, missing paired constructor and a different
source owner. Together with the constructor's eight tests, all 15 focused tests
pass. All 334 unique actual byte corruption controls fail: both seven-byte
inventory bodies, constructor 16, caller 29 and the 275 unique RTTI bytes.

The separate IEffectManager normal destructor is not emitted in this actual
CSelect object. It is not materialized with an artificial caller/export or
accepted from matching bytes. This is a closed missing-source-owner lead until
an actual source consumer provides that emitted body.

The existing constructor gate retains its own proof.
