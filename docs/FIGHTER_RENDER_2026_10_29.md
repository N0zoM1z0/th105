# Shared Fighter render transform, JP1.06a

45E6E0 now has complete selected570-byte C++ source. All fifteen roster primary
vtable slot34 anchors independently identify the shared authored body; see
config/roster-fighter-vtable-origin-anchors.toml. Ownership is unchanged.

Native SHA256:
1f3cbc48a0cc641a0472d763622a87eeeb5e3a3a35c80e9659d7c5d4feffcca3.
Source SHA256:
da3c9faddd8a05f8c2d9a9d4723065608c163a0e7b60cb70a4c080532c4d127a.
Only five bytes differ at offsets28..32. Target loads signed frame X to x87
before saving EDI; source saves EDI then loads the same value from its adjusted
stack displacement. All bytes from+33 through the complete RET agree. This is
not an exact function and contributes no exact-byte credit.

## Complete behavior and actual types

The method-facing view contains the real CEffectSprite at+4; its base CSpriteEx
is the receiver for all transforms. Signed frame offsets at frame158+4/+6 are
converted to float. Transform order is reset, facing X scale, pivoted X/Y scale,
three-angle rotation, negative frame pivot translation, then world translation.
Every required float32 rounding and signed facing conversion is retained.

Positive signed hitstop186 in the actual state32..95 hexadecimal gate adds
2-4*(hitstop%2) to world X. Branch-local translate calls naturally share their
native call suffix. No ternary/artificial precomputed world coordinate is used.
When own hitstop and peer48C are both zero, append the sprite to render history
at674 with blend2; a nonpositive countdown670 pops twice. The14-byte history
uses a real checked list of sprite-plus-blend entries and its period/divisor/
color fields, consistent with the complete Character lifetime reconstruction.
Finally the battle-layout singleton6FBCC0 transforms the sprite.

This is a pointer-only method view, not a new claim about unused fields or the
complete Fighter allocation. Shared headers and other selected units are unchanged.
The old private570-byte scheduling observation is reproduced with current
tracked sprite/layout types; no declaration/liveness or compiler-flag grid was
restarted and no instruction/padding workaround was introduced.

## Reproduce

scripts/repo-python scripts/build.py --unit exact-first-fighter-render --compare --json

Source:src/battle/FighterRender.cpp.
Formal receipt:build/frontier-fighter-render-20261029/formal-build.json.
Private full-section diagnostic:compare.json in the same directory.
