# Actual scenario-result tile, 2026-11-02

Original Japanese v1.06a SHA-256:
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.

ScenarioData.hpp uses actual global CTile for ScenarioResultResource +0x5C.
ScenarioResultConstructor.cpp removes its local color/tile class substitutes
and texture-setup receiver view. It invokes the actual set_texture_options
method with the existing arguments. ScenarioResultRuntime.cpp uses named
scale_x_88/scale_y_8c fields and the actual render method instead of byte-offset
helpers and a ProfileTileView cast. The outer resource views and unrelated
scenario sprite entries are not unified by this change.

The needed UiPrimitives.hpp include is retained for the existing UiDesignObject
layout. A diagnostic compile caught that dependency when the first private
control removed it; no incomplete compile was accepted. Compiler flags, storage
extents, expression ordering, native branch behavior and preservation settings
are unchanged.

Fresh before/after controls preserve complete constructor 0x454C70 / 298 bytes,
render 0x454890 / 187 bytes, destructor 0x454BF0 / 116 bytes and the five other
runtime methods. Constructor SHA-256:
90e375ff6e10b1db8c63ded6c2e7416e13314d6e09d831ecbf210a1c5c46829f.
The actual quoted-include closure has 12 units; all 22 accepted roots in 11
units rebuilt exact. The pending ScenarioData constructor retains its 1528-byte
candidate hash. The command-update root retains its independently reproduced
unqualified ?$basic_string_ctor relocation; it is still blocked, not a verified
native comparison. No unsupported binding was added to bypass that blocker.

Actual CTile's full hierarchy (247 unique RTTI bytes) and four-slot table match.
Constructor EH is 49 code bytes at 0x6BA840 plus 52 metadata bytes; destructor
EH is 49 at 0x6BA800 plus 52 metadata bytes. Both full regions and their native
CDesignBase/CTile cleanup targets match, totaling 202 support bytes. Equal
physical cleanup bodies do not establish an exclusive original nominal class.
No support, partial function or unresolved command bytes receive exact credit.

Private evidence: .analysis/frontier-scenario-result-real-tile-20261102/ and
build/frontier-scenario-result-real-tile-20261102/. Final default CI passed
962 tests (137.258 seconds), tracking, generated progress and whitespace. The
client timeout was reconciled against the zero exit marker and complete terminal
log without rerunning CI. Both diff checks passed. No target or generated binary
is committed.

Totals unchanged: 1426 exact / 443399 bytes, 1636 source-present, 1655 authored,
1826 mapped, 2075 excluded, 297 review and 813 units.
