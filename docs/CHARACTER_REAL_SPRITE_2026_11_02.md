# Character uses the actual CSprite

## Accepted source relationship

Character462AB0 still compares as the complete557-byte constructor, SHA256
6843409d8f8d40e4f3ebf4d1bd9615a666c72f0abda652943492913297aaa5a5.
Its three sprites at33C,3D4 and570 now use the actual global CSprite, including
all nine virtual slots, instead of CharacterCtorSprite94 and its local
8-byte CharacterCtorColorView. The actual IColor interface remains4 bytes.

The existing th105::DesignTextureHandle value is moved unchanged from
DesignBaseLifetime.hpp to engine/TextureHandleValue.hpp. CSpriteBase now owns
that four-byte initializing value at+4 instead of unsigned int. Its existing
ordinary value_04(0) initialization is retained. The member has implicit trivial
copy/destruction, no resource-release behavior and no extra storage. Design
containers retain the same nominal value type and specialization names.
This is not proof of the original handle type's spelling or a global change
to the texture-loading API. No padding, register ABI, manual vptr, inline
assembly, EH-state writes or compiler flag was introduced.

The independent justification is the existing handle initialization and
container-copy evidence, combined with actual sprite texture writes/render
reads and RTTI ownership. A private actual-CSprite/scalar control reproduced
the old557-byte55da99cc candidate with its nine-byte initialization/EH ordering
difference. Giving CSpriteBase the existing initializing value restored the
whole557-byte canonical body. This replaces the earlier local-only inference;
it does not add exact credit.

## Actual owner evidence

The Character object now emits the actual CSprite/CSpriteBase/IColor RTTI
hierarchy:273 unique canonical bytes. All nine slots of table6C0668/36 match
native role identities. The canonical constructor loads that table at462AF0
and stores it to members33C/3D4/570 at462AFF/462B11/462B5F. The handle zero-store
at462AF5 precedes the EH-state-zero store at462AFB. The obsolete relocation
symbol is replaced by the actual global CSprite symbol, attesting all36 table
bytes instead of the old32-byte local-view prefix.

The existing complete main-function boundary and relocation contracts are
preserved. This check does not claim the entire Character unwind graph,
original complete Character nominal layout or full-program linkage.

## Affected validation

The actual quoted-include closure is148 units. All316 accepted roots in116
units were freshly compiled and compared with zero differences. Comparison
selection was reconciled numerically because manifest address casing varies;
316 is the complete count, not the first case-sensitive pass's281.
The remaining124 configured bodies in63 units were also checked. Fresh
before/after controls preserve all their hashes or existing failure categories.
Design loader40B000 still lacks a qualified EH binding and Scenario458440
still lacks its string-constructor boundary; both failures reproduce before
this change. Nonexact bodies receive no credit.

The CSprite16/7 and actual NetworkBase411 parent/full EH gates pass. The
CSpriteEx16/7 implicit-lifetime gate passes, including full Select EH461 and
metadata188; its main4247-byte constructor remains13 bytes nonexact. Generic
implicit lifetime17/1434, record cleanup2/23, InputPacket cleanup1/8 and implicit
design lifetime2/307 gates pass with refreshed source pins that include the
new header. No ownership rule or accepted whole-byte requirement is weakened.

Select rendering1497/163 and character update619/25 retain their full hashes;
all4 and12 bounded observer cases and negative controls pass. Actual Select
owner and design-color/table audits pass. Fighter cleanup465420 remains95
versus native96; this does not reopen its closed CSE-shaping lane.

Evidence: build/frontier-character-real-sprite-20261102/, including coverage.json,
owner-proof.json, replays/, nonexact/ and baseline-neighbors/. Private controls
are under the corresponding .analysis directory. Canonical entry replay:

    scripts/repo-python scripts/build.py --unit exact-first-character-constructor --compare --json
    scripts/repo-python scripts/csprite_lifetime_origins.py
    scripts/repo-python scripts/sprite_default_origins.py

Default CI passed958 tests in107.183 seconds (ci.exit=0); both diff checks
pass before the local checkpoint. Counts
remain1427 exact/443604 authored bytes,1636 source-present and812 units.
