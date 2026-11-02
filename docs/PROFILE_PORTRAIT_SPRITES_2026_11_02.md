# Shared actual profile portrait sprites, 2026-11-02

Pinned original Japanese v1.06a SHA-256:
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.

ProfileMenuBaseDataLifetime.hpp now owns actual CSprite at +0x04. Its separate
ProfileIColorLifetime (which wrongly assigned the handle to an eight-byte color
base), sprite base and opaque-extension sprite class are removed. The shared
native IColor is four bytes; CSpriteBase owns the handle. Overall profile extent
0x33C, strings +0x98/+0xB4, input +0xD0 and decks +0x1AC stay unchanged.

The same actual CSprite type is used by PlayerSlotColor, NetworkResultFinalize,
InfoManagerNormalRender, ProfileUiLifecycle and ProfileUiInfrastructure. They
retain their independently observed profile/network offsets while replacing
manual-vtable facades or partial six/eight-slot interfaces with the complete
nine-slot interface. No missing broad owner layout is inferred from those
bounded pointer views. Existing input-manager and text-owner views stay intact.

## Validation

All 18 accepted roots in the eight-unit actual include closure remain whole
exact. This includes profile construction192/destruction205, player color461,
network finalization623, battle profile render753, profile frame359, shutdown129,
the score-defaults owner and Replay owners. Three additional Replay support
roots (208/27/5) retain fresh HEAD hashes. No accepted caller regresses.

The actual profile sprite's complete RTTI (273 bytes including standalone IColor
COL) and nine-slot table match. Full profile constructor and destructor EH each
contain 80 code bytes and 68 metadata bytes, 296 total. Whole string cleanup38
and implicit input cleanup5 are qualified at their observed native destinations.
Neither equal helper bytes nor common cleanup targets prove exclusive nominal
identity. These checks do not assert full-program linkage across all views.

Replay's source-pinned cleanup proof now records the reviewed profile header
and its new shared Sprite/Color/Handle dependencies. Its complete two-root /
32-byte gate passes; all 12 focused validator tests pass. No origin disposition
or exact/source totals change in this structural scope.

A separate provenance question remains: the profile destructor at0x42D320 has
an explicit empty source body and may admit a natural compiler-generated witness
from the real ScoreDefaults local object. That requires its own complete emission
and owner proof before any reclassification; this checkpoint does not infer an
original declaration or change accounting merely from the empty body.

Private scripts/reports: .analysis/frontier-profile-portrait-sprites-20261102/
and build/frontier-profile-portrait-sprites-20261102/. Final default CI passed
962 tests (101.251 seconds), tracking, generated progress and whitespace. Both
diff checks passed. No target or generated binary is committed.

Counts remain 1427 exact / 443604 bytes, 1637 source-present, 1656 authored,
1826 mapped, 2074 excluded, 297 review and 813 units.
