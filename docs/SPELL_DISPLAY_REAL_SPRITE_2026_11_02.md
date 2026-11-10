# Actual indexed spell-display sprite, 2026-11-02

Target SHA-256: 56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.

PlayerIndexedCallbackView now contains actual CSprite at +0x98. The partial
five-slot SpellDisplaySpriteView and its separate 0x90-byte storage tail are
removed. Its 0x154-byte record extent remains checked. The callback uses the
real set_texture_options method; the existing pointer-typed batch-resource
view is explicitly converted to its 32-bit texture-handle bits, as already done
by the profile-deck renderer. This does not rename or retype the shared spell
resource record or claim original nominal field types.

The complete 0x432DE0 / 234-byte callback remains canonical, SHA-256
a281085ddb3adc6f26539450b5ba6c085729b8df5574a499cd795bdc3b65c089.
Native sprite ownership and the two 0x94-byte member layout are corroborated by
the already accepted info-record constructor / cleanup context. No synthetic
constructor or RTTI emission is added to this callback TU.

The actual include closure has 18 units. All 21 accepted roots in 14 units pass
adopted comparisons; all eight other roots in seven units preserve their fresh
before/after hashes. No compiler flags, relocation manifest, origin rule or
ledger changes are needed. No new exact credit is claimed.

Final CI passed all 962 tests in 111.865 seconds. Both diff checks gate the local
checkpoint. Totals remain 1426 exact / 443399 bytes, source 1636, authored 1655,
mapped 1826, excluded 2076, review 296 and units 813.
